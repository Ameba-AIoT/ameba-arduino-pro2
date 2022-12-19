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

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_LINEAR_RAW_RESAMPLER_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_LINEAR_RAW_RESAMPLER_H

#include <stdint.h>
#include <sys/types.h>
#include "log/log.h"

#include "raw_resampler.h"

namespace ameba::audio
{

class LinearRawResampler : public RawResampler
{
public:
	LinearRawResampler(int in_channel_count, int32_t sample_rate);
	virtual size_t Resample(int32_t *out_data, size_t output_frame_count, TrackServerBufferAgent *buffer_agent);

private:
	void DoInit() {}
	size_t Mono16bitResample(int32_t *out_data, size_t output_frame_count, TrackServerBufferAgent *buffer_agent);
	size_t Stereo16bitResample(int32_t *out_data, size_t output_frame_count, TrackServerBufferAgent *buffer_agent);

	static inline int32_t Interp(int32_t x0, int32_t x1, uint32_t f)
	{
		return x0 + (((x1 - x0) * (int32_t)(f >> s_pre_interp_bits)) >> s_num_interp_bits);
	}
	static inline void Advance(size_t *index, uint32_t *frac, uint32_t inc)
	{
		*frac += inc;
		*index += (size_t)(*frac >> k_num_phase_bits_);
		*frac &= k_phase_mask_;
	}

	static const int s_num_interp_bits = 15;
	static const int s_pre_interp_bits = k_num_phase_bits_ - s_num_interp_bits;
	int mX0L;
	int mX0R;
};

// ----------------------------------------------------------------------------
} // namespace ameba::audio

#endif
