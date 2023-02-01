/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from PanKore
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_OUTPUT_TRACK_H
#define AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_OUTPUT_TRACK_H

#include "osal_cxx/errors.h"
#include "track_base.h"
#include "string.h"
#include "audio/audio_time.h"
#include "hardware/audio/audio_hw_types.h"
#include "track_shared.h"

namespace ameba::audio
{
class OutputThreadBase;

class OutTrack : public ThreadBase::TrackBase
{
public:
	OutTrack(OutputThreadBase *thread,
			 uint32_t type,
			 uint32_t sampleRate,
			 uint32_t format,
			 uint32_t channel_count,
			 size_t frame_count);
	virtual             ~OutTrack();

	virtual res_t       TrackBufferCheck() const;
	virtual res_t       Start();
	virtual void        Stop();
	void        Pause();
	void        Flush();
	void        Destroy();
	int         GetTrackMask() const
	{
		return track_mask_;
	}
	virtual uint32_t    GetSampleRate()  const;
	uint32_t    CategoryType() const
	{
		return stream_type_;
	}
	virtual res_t       GetTimestamp(RTAudioTimestamp *timestamp);
	res_t       SetParameters(const char *params);

protected:

	friend class OutputThreadBase;
	friend class MixerSingleThread;

	OutTrack(const OutTrack &);
	OutTrack &operator = (const OutTrack &);

	virtual res_t       GetNextAvailBuffer(TrackServerBufferAgent::Buffer *buffer, int64_t pts = kInvalidPTS);
	virtual size_t      ReadyFramesSize() const;
	virtual size_t      ReleasedFramesSize() const;
	void        SetWorkBuffer(int16_t *buffer)
	{
		work_buffer_ = buffer;
	}
	int16_t     *GetWorkBuffer() const
	{
		return work_buffer_;
	}

	bool        IsPausing() const
	{
		return track_state_ == PAUSING;
	}
	bool        IsPaused() const
	{
		return track_state_ == PAUSED;
	}
	bool        IsReady() const;
	void        SetPause()
	{
		track_state_ = PAUSED;
	}
	void        Reset();
	void        InvalidWhenThreadExit();
	bool        IsPlayDone(size_t frames_written, size_t audio_hal_frames);

protected:

	enum {FS_INVALID, FS_FILLING, FS_FILLED, FS_ACTIVE};
	mutable uint8_t     filling_up_status_;
	int8_t              retry_count_;

	int                 track_mask_;
	bool                reset_done_;
	uint32_t            stream_type_;
	int16_t            *work_buffer_;
	size_t              complete_frames_;
private:
	AudioTrackServerProxy  *audio_track_server_proxy_;
	bool                resume_to_stopping_;

};
}
#endif // AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_OUTPUT_TRACK_H