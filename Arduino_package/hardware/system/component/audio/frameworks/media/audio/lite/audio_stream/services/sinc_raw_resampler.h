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

#ifndef AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_SINC_RAW_RESAMPLER_H
#define AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_SINC_RAW_RESAMPLER_H

#include <stdint.h>
#include <sys/types.h>
#include "log/log.h"

#include "raw_resampler.h"

namespace ameba::audio
{

class SincRawResampler : public RawResampler
{
public:
	SincRawResampler(int in_channel_count, int32_t sampleRate,
					 src_quality quality = QUALITY_HIGH);

	virtual ~SincRawResampler();

	virtual size_t Resample(int32_t *out, size_t out_frame_count,
							TrackServerBufferAgent *provider);
private:
	void DoInit();

	virtual void SetVolume(float left, float right);

	template<int CHANNELS>
	size_t Resample(int32_t *out, size_t out_frame_count,
					TrackServerBufferAgent *provider);

	template<int CHANNELS>
	inline void FilterCoefficient(
		int32_t *out, uint32_t phase, const int16_t *samples, uint32_t vRL);

	template<int CHANNELS>
	inline void Interpolate(
		int32_t &l, int32_t &r,
		const int32_t *coefs, size_t offset,
		int32_t lerp, const int16_t *samples);

	template<int CHANNELS>
	inline void read(int16_t *&impulse, uint32_t &phase_fraction,
					 const int16_t *in, size_t inputIndex);

	int16_t *state_;
	int16_t *im_pulse_;
	int16_t *ring_full_;
	int32_t volume_simd_[2];

	const int32_t *fir_coefs_;
	static const uint32_t fir_coefs_down_[];
	static const uint32_t fir_coefs_up_[];

	static const int32_t RESAMPLE_FIR_NUM_COEF       = 8;
	static const int32_t RESAMPLE_FIR_LERP_INT_BITS  = 7;

	struct Constants {
		int coefsBits;
		int cShift;
		uint32_t cMask;
		int pShift;
		uint32_t pMask;
		unsigned int half_num_coefs;
	};

	static Constants high_quality_constants_;
	static Constants very_high_quality_constants_;
	const Constants *constants_;

	static void *InitRoutine();
};

// ----------------------------------------------------------------------------
} // namespace ameba::audio

#endif
