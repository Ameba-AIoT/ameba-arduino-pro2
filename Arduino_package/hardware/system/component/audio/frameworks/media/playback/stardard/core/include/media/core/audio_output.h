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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_AUDIO_OUTPUT_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_AUDIO_OUTPUT_H

#include "osal_cxx/mutex.h"
#include "audio/audio_track.h"

#include "audio_render_sink.h"

namespace ameba::media
{

class AudioOutput : public AudioRenderSink
{
public:
	AudioOutput();
	virtual ~AudioOutput();

	virtual bool IsReady() const
	{
		return audio_track_ != nullptr;
	}
	virtual ssize_t GetBufferSize() const;
	virtual ssize_t GetFrameCount() const;
	virtual ssize_t GetChannelCount() const;
	virtual ssize_t GetFrameSize() const;
	virtual uint32_t GetLatency() const;
	virtual float GetMSecsPerFrame() const;
	virtual res_t GetPosition(uint32_t *position) const;
	virtual int64_t GetPlayedOutDurationUs(int64_t now_us) const;
	virtual res_t GetFramesWritten(uint32_t *frames_written) const;
	virtual uint32_t GetSampleRate() const;
	virtual int64_t GetBufferDurationInUs() const;

	virtual res_t Open(
		uint32_t sample_rate, int channel_count, uint32_t channel_mask,
		uint32_t format, int buffer_count);

	virtual res_t Start();
	virtual ssize_t Write(const void *buffer, size_t size, bool blocking = true);
	virtual void Stop();
	virtual void Flush();
	virtual void Pause();
	virtual void Close();

	virtual res_t SetVolume(float left, float right);
	virtual void SetSpeed(float speed, float pitch);

private:
	enum State {
		STATE_ACTIVE,
		STATE_STOPPED,
		STATE_PAUSED,
		STATE_PAUSED_STATE_STOPPING,
		STATE_STATE_FLUSHED,
		STATE_STATE_STOPPING,
	};

	uint32_t             channel_count_;
	uint32_t             sample_rate_hz_;
	float                ms_per_frame_;
	size_t               frame_size_;
	uint32_t             format_;
	State                state_;
	Mutex                lock_;
	float                left_volume_;
	float                right_volume_;
	float                speed_;
	float                pitch_;

	struct RTAudioTrack *audio_track_;
};

}; // namespace ameba::media

#endif // AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_AUDIO_OUTPUT_H
