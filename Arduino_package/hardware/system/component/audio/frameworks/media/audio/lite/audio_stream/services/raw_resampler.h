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

#ifndef AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_RESAMPLER_H
#define AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_RESAMPLER_H

#include <stdint.h>
#include <sys/types.h>

#include "track_server_buffer_agent.h"
#include "hardware/audio/audio_hw_types.h"

#define DUMP_DATA 0
#define DUMP_DATA_SECONDS 5

namespace ameba::audio
{

class RawResampler
{
public:
	enum src_quality {
		QUALITY_DUMMY = 0,
		QUALITY_LOW = 1,
		QUALITY_MIDDLE = 2,
		QUALITY_HIGH = 3,
		QUALITY_VERY_HIGH = 4,
	};

	static const constexpr float FLOAT_VOLUME_GAIN = 1.0f;

	static RawResampler *Create(uint32_t format, int in_channel_count, int32_t sample_rate, src_quality quality = QUALITY_DUMMY);

	virtual ~RawResampler();

	virtual void DoInit() = 0;
	virtual void SetSampleRate(int32_t in_sample_rate);
	virtual void SetVolume(float left, float right);
	virtual void SetLocalTimeFreq(uint64_t freq);
	virtual void SetPTS(int64_t pts);
	virtual size_t Resample(int32_t *out, size_t out_frame_count,
							TrackServerBufferAgent *provider) = 0;

	virtual void Reset();
	virtual size_t GetFrameSizeUnreleased() const
	{
		return input_index_;
	}

	src_quality GetQuality() const
	{
		return quality_;
	}

protected:

	static const int k_num_phase_bits_ = 30;
	static const uint32_t k_phase_mask_ = (1LU << k_num_phase_bits_) - 1;
	static const double k_phase_muliplier_;

	RawResampler(int in_channel_count, int32_t sample_rate, src_quality quality);

	RawResampler(const RawResampler &);
	RawResampler &operator=(const RawResampler &);

	int64_t CalculateOutputPTS(int output_frame_index);

	const int32_t channel_count_;
	const int32_t sample_rate_;
	int32_t in_sample_rate_;
	TrackServerBufferAgent::Buffer buffer_agent_buf_;
	union {
		int16_t mVolume[2];
		uint32_t mVolumeRL;
	};
	int16_t target_volume_[2];
	size_t input_index_;
	int32_t phase_increment_;
	uint32_t phase_fraction_;
	uint64_t local_time_freq_;
	int64_t pts_;
#if DUMP_DATA
	char *dump_in_data_;
	char *dump_out_data_;
	int dumped_in_frames_;
	int dumped_out_frames_;
#endif

	inline size_t GetInFrameCountRequired(size_t out_frame_count)
	{
		return (static_cast<uint64_t>(out_frame_count) * in_sample_rate_
				+ (sample_rate_ - 1)) / sample_rate_;
	}

	inline float ClampFloatVol(float volume)
	{
		if (volume > FLOAT_VOLUME_GAIN) {
			return FLOAT_VOLUME_GAIN;
		} else if (volume >= 0.) {
			return volume;
		}
		return 0.;
	}

private:
	const src_quality quality_;
	static bool QualityIsSupported(src_quality quality);
	static void *InitRoutine(void *param);
	static uint32_t QualityMHz(src_quality quality);
};

} // namespace ameba::audio

#endif // AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_RESAMPLER_H
