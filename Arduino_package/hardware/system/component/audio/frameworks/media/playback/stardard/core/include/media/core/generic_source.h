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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_GENERIC_SOURCE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_GENERIC_SOURCE_H

#include <vector>

#include "media/common/media_buffer.h"
#include "media/common/media_track.h"
#include "media/demux/media_extractor.h"

#include "player_core.h"
#include "player_core_source.h"

namespace ameba::media
{

class PacketPool;
class DataSource;
class MediaBuffer;

class PlayerCore::GenericSource : public PlayerCore::Source
{
public:
	GenericSource(const sptr<Message> &notify);

	res_t SetDataSource(const char *url);
	res_t SetDataSource(const sptr<DataSource> &data_source);
	virtual void PrepareAsync();
	virtual void Start();
	virtual void Stop();
	virtual void Pause();
	virtual void Resume();
	virtual void Disconnect();
	virtual res_t FeedMoreTSData();
	virtual res_t DequeueDataChunk(MediaBufferBase **data_block);

protected:
	virtual ~GenericSource();

	virtual void OnMessage(const sptr<Message> &msg);
	virtual sptr<MetaData> GetFormatMeta();

private:
	enum {
		kMsgPrepareAsync    = 0x00530101,

		kMsgStart                 = 0x00530201,
		kMsgResume             = 0x00530206,
		kMsgRewind              = 0x00530207,

		kMsgReadBuffer        = 0x00530302,
		// streaming source
		kMsgUpdateBufferingStats      = 0x00530306,
		kMsgBufferingInfoUpdate = 0x00530307,
		kMsgPauseOnBufferingStart = 0x00530308,
		kMsgResumeOnBufferingEnd = 0x00530309,
	};

	struct TrackInfo {
		size_t mIndex;
		sptr<MediaTrack> track_;
		//keep the source packet , it is get from the demux
		sptr<PacketPool> packets_;
	};

	std::vector<sptr<MediaTrack> > tracks_;
	TrackInfo audio_track_info_;
	int32_t audio_data_count_;
	int64_t audio_time_us_;
	int64_t duration_us_;
	bool audio_is_vorbis_;

	RString uri_;

	bool disconnected_;
	sptr<DataSource> data_source_;
	sptr<MetaData> file_meta_;
	sptr<MediaExtractor> extractor_;

	bool started_;
	bool preparing_;
	bool rewinding_;
	int64_t bitrate_;

	mutable Mutex lock_;

	sptr<MessageLooper> looper_;

	std::vector<std::string> mimes_;

	bool is_streaming_;
	int buffering_initial_ms_;
	int buffering_resume_ms_;
	int32_t update_buffering_stats_count_;
	int32_t pre_buffer_percentage_;
	bool start_pause_on_buffering_;

private:
	void ResetDataSource();

	res_t InitForDataSource();

	void NotifyPreparedAndCleanup(res_t err);
	void FinishPrepareAsync();
	res_t StartSources();
	void OnPrepareAsync();

	res_t GetDuration(int64_t *duration_us);

	res_t Rewind(int64_t rewind_time_us);
	void OnRewind(const sptr<Message> &msg);
	res_t DoRewind(int64_t rewind_time_us);

	void PostReadBuffer();
	void ReadBuffer(int64_t rewind_time_us = -1ll, int64_t *actual_time_us = NULL, bool format_change = false);

	void ScheduleUpdateBufferingStats();
	void OnUpdateBufferingStats();
	void NotifyBufferingInfoUpdate(int32_t percentage);

	sptr<MetaData> GetFormatMeta_l();

	sptr<RBuffer> CopyMediaBufferToRBuffer(MediaBufferBase *mb);

	DISALLOW_COPY_AND_MOVE(GenericSource);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_GENERIC_SOURCE_H
