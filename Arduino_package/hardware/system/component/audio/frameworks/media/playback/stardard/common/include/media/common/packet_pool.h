/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_PACKET_POOL_H
#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_PACKET_POOL_H

#include <vector>

#include "osal_cxx/mutex.h"
#include "osal_cxx/condition.h"
#include "utils/list.h"
#include "utils/nocopyable.h"

#include "media/common/media_track.h"
#include "media/common/ts_parser.h"

namespace ameba::media
{

class Message;

class PacketPool : public RefPtr
{
public:
	explicit PacketPool(const sptr<MetaData> &meta);

	void SetFormat(const sptr<MetaData> &meta);

	virtual res_t Start(MetaData *params = NULL);
	virtual res_t Stop();
	virtual sptr<MetaData> GetFormat();

	virtual res_t Pause()
	{
		return ERROR_UNSUPPORTED;
	}

	virtual res_t ReadMultiple(
		std::vector<MediaBufferBase *> * /* buffers */, uint32_t /* max_num_buffers = 1 */,
		const MediaTrack::ReadProperties * /* properties = nullptr */)
	{
		return ERROR_UNSUPPORTED;
	}

	virtual bool SupportReadMultiple()
	{
		return false;
	}

	virtual bool SupportNonblockingRead()
	{
		return false;
	}

	void Clear();

	// Returns true if we have any packets including discontinuities
	bool HasBufferAvailable(res_t *final_result);

	// Returns true if we have packets that's not discontinuities
	bool HasDataBufferAvailable(res_t *final_result);

	// Returns true if packet pool has free space for more data
	bool HasFreeSpace(bool is_streaming);

	// Returns the number of available buffers. final_result is always OK
	// if this method returns non-0, or the final result if it returns 0.
	size_t GetAvailableBufferCount(res_t *final_result);

	// Returns the difference between the last and the first queued
	// presentation timestamps since the last discontinuity (if any).
	int64_t GetBufferedDurationUs(res_t *final_result);

	void QueueDataChunk(MediaBufferBase *buffer);

	void QueueDiscontinuity(
		TSParser::DiscontinuityType type,
		const sptr<Message> &extra,
		bool discard);

	void SignalEOS(res_t result);
	void GetEOS(res_t *result);

	res_t DequeueDataChunk(MediaBufferBase **buffer);
	void RequeueDataChunk(MediaBufferBase *buffer);

	bool IsFinished(int64_t duration) const;

	//void enable(bool enable);

protected:
	virtual ~PacketPool();

private:
	void mediaMetaToMessage(MediaBufferBase *mb);

	class DiscontinuitySegment
	{
	public:
		int64_t max_deque_time_us_, max_enque_time_us_;
		DiscontinuitySegment()
			: max_deque_time_us_(-1),
			  max_enque_time_us_(-1)
		{
		};

		void Clear()
		{
			max_deque_time_us_ = max_enque_time_us_ = -1;
		}
	};

	enum {
		kMaxNumBuffersForNonStreaming = 8,
		kMaxBufferDurationForStreaming = 1200, //ms
	};

	// Discontinuity segments are consecutive access units between
	// discontinuity markers. There should always be at least _ONE_
	// discontinuity segment, hence the various CHECKs in
	// PacketPool.cpp for non-empty()-ness.
	List<DiscontinuitySegment> discontinuity_segments_;

	Mutex lock_;
	Condition condition_;

	bool is_audio_;
	bool enabled_;
	sptr<MetaData> format_;
	int64_t last_queued_time_us_;
	List<MediaBufferBase *> media_buffers_;
	res_t eos_result_;
	sptr<Message> latest_enqueued_meta_;
	sptr<Message> latest_dequeued_meta_;

	bool WasFormatChange(int32_t discontinuity_type) const;

	DISALLOW_COPY_AND_MOVE(PacketPool);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_PACKET_POOL_H