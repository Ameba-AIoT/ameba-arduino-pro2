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

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_BUFFER_PROVIDERS_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_BUFFER_PROVIDERS_H

#include <stdint.h>
#include <sys/types.h>

#include "hardware/audio/audio_hw_types.h"
#include "raw_resampler_public.h"
#include "sonic.h"
#include "track_server_buffer_agent.h"

namespace ameba::audio
{

// ----------------------------------------------------------------------------

class PassthruBufferAgent : public TrackServerBufferAgent
{
public:
	PassthruBufferAgent() : track_buffer_agent_(NULL) { }

	virtual      ~PassthruBufferAgent() { }

	virtual void Reset() { }

	virtual void SetBufferAgent(TrackServerBufferAgent *p)
	{
		track_buffer_agent_ = p;
	}

protected:
	TrackServerBufferAgent       *track_buffer_agent_;
};

class CopyBufferAgent : public PassthruBufferAgent
{
public:

	CopyBufferAgent(size_t input_frame_size, size_t output_frame_size,
					size_t buffer_frame_count);
	virtual       ~CopyBufferAgent();

	virtual res_t GetNextAvailBuffer(Buffer *buffer, int64_t pts);
	virtual void  ReleaseHandledBuffer(Buffer *buffer);

	virtual void  Reset();

	virtual void  CopyFrames(void *dst, const void *src, size_t frames) = 0;

protected:
	const size_t                   input_frame_size_;
	const size_t                   output_frame_size_;
private:
	TrackServerBufferAgent::Buffer buffer_;
	const size_t                   local_buffer_frame_count_;
	void                          *local_buffer_data_;
	size_t                         consumed_;
};

class ReformatBufferAgent : public CopyBufferAgent
{
public:
	ReformatBufferAgent(int32_t channel_count,
						uint32_t input_format, uint32_t output_format,
						size_t buffer_frame_count);
	virtual void CopyFrames(void *dst, const void *src, size_t frames);

protected:
	const uint32_t                 channel_count_;
	const uint32_t              input_format_;
	const uint32_t              output_format_;
};

class TimestretchBufferAgent : public PassthruBufferAgent
{
public:
	TimestretchBufferAgent(int32_t channelCount,
						   uint32_t format, uint32_t sampleRate,
						   const AudioPlaybackRate &playbackRate);
	virtual ~TimestretchBufferAgent();

	// Overrides AudioBufferProvider methods
	virtual res_t GetNextAvailBuffer(Buffer *buffer, int64_t pts);
	virtual void  ReleaseHandledBuffer(Buffer *buffer);

	// Overrides PassthruBufferAgent
	virtual void  Reset();

	virtual res_t SetPlaybackRate(const AudioPlaybackRate &playbackRate);

	// processes frames
	// dstBuffer is where to place the data
	// dstFrames [in/out] is the desired frames (return with actual placed in buffer)
	// srcBuffer is the source data
	// srcFrames [in/out] is the available source frames (return with consumed)
	virtual void ProcessFrames(void *dstBuffer, size_t *dstFrames,
							   const void *srcBuffer, size_t *srcFrames);

protected:
	const uint32_t       channel_count_;
	const uint32_t       format_;
	const uint32_t       sample_rate_; // const for now (TODO change this)
	const size_t         frame_size_;
	AudioPlaybackRate    playback_rate_;

private:
	TrackServerBufferAgent::Buffer buffer_;          // for upstream request
	size_t               local_buffer_frame_count_;  // size of local buffer
	void                *local_buffer_data_;        // internally allocated buffer for data returned
	// to caller
	size_t               remaining_;              // remaining data in local buffer
	sonicStream          sonic_stream_;            // handle to sonic timestretch object
	//FIXME: this dependency should be abstracted out
	bool                 fallback_fail_err_shown_; // log fallback error only once
	bool                 audio_playback_rate_valid_; // flag for current parameters validity
};
// ----------------------------------------------------------------------------
} // namespace ameba

#endif // AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_BUFFER_PROVIDERS_H
