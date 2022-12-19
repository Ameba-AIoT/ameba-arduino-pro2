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

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_STREAM_RENDER_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_STREAM_RENDER_H

#include <stdint.h>

#include "audio/audio_time.h"
#include "hardware/audio/audio_hw_adapter.h"
#include "hardware/audio/audio_hw_render.h"
#include "osal_cxx/errors.h"

namespace ameba::audio
{

class AudioStreamRender
{
public:
	AudioStreamRender(AudioHwAdapter *adapter);

	virtual res_t        createRender(
		const struct AudioHwDeviceDescriptor *desc,
		const struct AudioHwSampleAttributes *attr);

	virtual              ~AudioStreamRender() { }

	res_t        GetRenderPosition(uint32_t *frames);

	virtual res_t        GetRenderPosition(uint64_t *frames);
	virtual res_t        GetPresentationPosition(uint64_t *frames, struct timespec *timestamp);
	virtual res_t        GetTimestamp(RTAudioTimestamp *timestamp);

	virtual ssize_t      Write(const void *buffer, size_t bytes);

	virtual size_t       GetFrameSize() const
	{
		return hal_frame_size_;
	}
	virtual uint32_t     GetFormat() const;
	virtual uint32_t     GetSampleRate() const;
	virtual size_t       GetBufferSize() const;
	virtual uint32_t     GetChannels() const;
	virtual int          SetParameters(const char *params) const;
	virtual int          Flush();
	virtual int          Standby();
	size_t               FramesWritten()
	{
		return frames_written_;
	}

private:
	AudioHwAdapter        *HalAdapter() const;

public:
	AudioHwAdapter         *audio_adapter_;
	AudioHwRender          *stream_render_;

protected:
	uint64_t             frames_written_; // reset by flush
	uint64_t             frames_written_at_standby_;
	uint64_t             render_position_; // reset by flush or standby
	int                  rate_multiplier_;
	bool                 hal_format_is_linear_pcm_;
	size_t               hal_frame_size_;
};

} // namespace ameba::audio

#endif // AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_STREAM_RENDER_H
