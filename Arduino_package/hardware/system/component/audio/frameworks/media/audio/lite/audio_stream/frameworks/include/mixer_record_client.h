/*
 * Copyright (c) 2021 Realtek, LLC.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_RECORD_CLIENT_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_RECORD_CLIENT_H

#include "audio/audio_time.h"
#include "audio/audio_record.h"
#include "audio_system.h"
#include "osal_cxx/errors.h"
#include "osal_cxx/mutex.h"
#include "osal_cxx/refptr.h"

namespace ameba::audio
{

// ----------------------------------------------------------------------------

struct audio_track_cblk_t;
class AudioRecordClientProxy;
class RecordTrack;
// ----------------------------------------------------------------------------

class RecordClient
{
public:
	class Buffer
	{
	public:
		size_t      frame_count;
		size_t      size;

		union {
			void       *raw;
			short      *i16;
			int8_t     *i8;
		};
	};

	enum transfer_type {
		TRANSFER_DEFAULT,
		TRANSFER_OBTAIN,
		TRANSFER_SYNC,
	};

	RecordClient();
	~RecordClient();

	ssize_t     GetBufferSize();
	ssize_t     GetMinBufferBytes(uint32_t sampleRate, uint32_t format, uint32_t channel_count);
	res_t       Init(const RTAudioRecordConfig *config);

	res_t       initCheck() const
	{
		return status_;
	}
	uint32_t    latency() const
	{
		return latency_;
	}
	uint32_t    GetFormat() const
	{
		return format_;
	}
	res_t       SetFormat(uint32_t format);
	uint32_t    GetChannelCount() const
	{
		return channel_count_;
	}
	res_t       SetChannelCount(uint32_t channel_count);
	size_t      GetframeCount() const
	{
		return frame_count_;
	}
	size_t      GetFrameSize() const
	{
		return frame_size_;
	}
	res_t       SetVolume(float volume);
	float       GetVolume();
	res_t       SetMute(bool muted);
	res_t       GetTimestamp(RTAudioTimestamp *timestamp);
	uint32_t    GetLatency();
	res_t       SetParameters(const char *strs);
	uint32_t    GetInputSource() const
	{
		return source_type_;
	}
	res_t       Start();
	void        Stop();
	void        Release();
	bool        Stopped() const;
	uint32_t    GetSampleRate() const
	{
		return sample_rate_;
	}
	res_t       SetSampleRate(uint32_t sample_rate);
	res_t       GetPosition(uint32_t *position) const;
	res_t       GetAvailableBuffer(Buffer *audioBuffer, int32_t waitCount,
								   size_t *nonContig = NULL);
	void        ReleaseBuffer(const Buffer *audioBuffer);
	ssize_t     Read(void *buffer, size_t size, bool blocking = true);

private:
	res_t       GetAvailableBuffer(Buffer *audioBuffer, const OsalTimespec *requested,
								   OsalTimespec *elapsed = NULL, size_t *nonContig = NULL);
	RecordClient(const RecordClient &other);
	RecordClient &operator = (const RecordClient &other);

	res_t       OpenRecordLocked(size_t epoch);
	res_t       RestoreRecordLocked(const char *from);

	mutable Mutex           lock_;
	bool                    active_;
	uint32_t                notification_frames_req_;
	uint32_t                notification_frames_act_;
	bool                    refresh_remaining_;
	uint32_t                remaining_frames_;
	uint32_t                observed_sequence_;

	uint32_t                new_position_;
	uint32_t                update_period_;

	res_t                   status_;

	size_t                  frame_count_;
	size_t                  req_frame_count_;
	uint32_t                sample_rate_;
	uint32_t                format_;
	uint32_t                channel_count_;
	size_t                  frame_size_;
	uint32_t                latency_;
	transfer_type           transfer_;

	sptr<RecordTrack>       record_track_;
	audio_track_cblk_t     *cblk_;

	sptr<AudioRecordClientProxy> proxy_;

	bool                    is_in_overrun_;

private:
	uint32_t                sequence_;
	int                     client_uid_;
	pid_t                   client_pid_;
	uint32_t                source_type_;
};
};
#endif
