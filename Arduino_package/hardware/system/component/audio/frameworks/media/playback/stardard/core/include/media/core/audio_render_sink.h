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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_AUDIO_RENDER_SINK_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_AUDIO_RENDER_SINK_H

#include "osal_cxx/errors.h"
#include "osal_cxx/refptr.h"

#include "audio/audio_type.h"

namespace ameba::media
{

#define CHANNEL_MASK_USE_CHANNEL_ORDER 0

#define DEFAULT_AUDIOSINK_BUFFERCOUNT 4

#define AUDIO_SINK_MIN_DEEP_BUFFER_DURATION_US 5000000

class AudioRenderSink : public RefPtr
{
public:
	virtual             ~AudioRenderSink() {}
	virtual bool        IsReady() const = 0; // audio output is open and ready
	virtual ssize_t     GetBufferSize() const = 0;
	virtual ssize_t     GetFrameCount() const = 0;
	virtual ssize_t     GetChannelCount() const = 0;
	virtual ssize_t     GetFrameSize() const = 0;
	virtual uint32_t    GetLatency() const = 0;
	virtual float       GetMSecsPerFrame() const = 0;
	virtual res_t    GetPosition(uint32_t *position) const = 0;
	//virtual res_t    getTimestamp(AudioTimestamp &ts) const = 0;
	virtual int64_t     GetPlayedOutDurationUs(int64_t now_us) const = 0;
	virtual res_t    GetFramesWritten(uint32_t *frames_written) const = 0;
	virtual uint32_t    GetSampleRate() const = 0;
	virtual int64_t     GetBufferDurationInUs() const = 0;

	// If no callback is specified, use the "write" API below to submit
	// audio data.
	virtual res_t    Open(
		uint32_t sample_rate, int channel_count, uint32_t channel_mask,
		uint32_t format = RTAUDIO_FORMAT_PCM_16_BIT,
		int buffer_count = DEFAULT_AUDIOSINK_BUFFERCOUNT) = 0;

	virtual res_t    Start() = 0;

	/* Input parameter |size| is in byte units stored in |buffer|.
	 * Data is copied over and actual number of bytes written (>= 0)
	 * is returned, or no data is copied and a negative status code
	 * is returned (even when |blocking| is true).
	 * When |blocking| is false, AudioRenderSink will immediately return after
	 * part of or full |buffer| is copied over.
	 * When |blocking| is true, AudioRenderSink will wait to copy the entire
	 * buffer, unless an error occurs or the copy operation is
	 * prematurely stopped.
	 */
	virtual ssize_t     Write(const void *buffer, size_t size, bool blocking = true) = 0;

	virtual void        Stop() = 0;
	virtual void        Flush() = 0;
	virtual void        Pause() = 0;
	virtual void        Close() = 0;
	virtual res_t       SetVolume(float left, float right) = 0;
	virtual void        SetSpeed(float speed, float pitch) = 0;
};

}; // namespace ameba::media

#endif // AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_AUDIO_RENDER_SINK_H