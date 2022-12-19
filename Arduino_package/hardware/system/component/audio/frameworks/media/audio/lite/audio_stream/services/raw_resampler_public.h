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

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_RAW_RESAMPLER_PUBLIC_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_RAW_RESAMPLER_PUBLIC_H

#include <stdint.h>
#include <math.h>

namespace ameba::audio
{

#define AUDIO_RESAMPLER_DOWN_RATIO_MAX    256
#define AUDIO_RESAMPLER_UP_RATIO_MAX      65536
#define AUDIO_TIMESTRETCH_SPEED_MIN       0.01f
#define AUDIO_TIMESTRETCH_SPEED_MAX       20.0f
#define AUDIO_TIMESTRETCH_SPEED_NORMAL    1.0f
#define AUDIO_TIMESTRETCH_SPEED_MIN_DELTA 0.0001f
#define AUDIO_TIMESTRETCH_PITCH_MIN       0.25f
#define AUDIO_TIMESTRETCH_PITCH_MAX       4.0f
#define AUDIO_TIMESTRETCH_PITCH_NORMAL    1.0f
#define AUDIO_TIMESTRETCH_PITCH_MIN_DELTA 0.0001f

enum AudioTimestretchStretchMode : int32_t {
	AUDIO_TIMESTRETCH_STRETCH_DEFAULT            = 0,
	AUDIO_TIMESTRETCH_STRETCH_SPEECH             = 1,
};

#define TIMESTRETCH_SONIC_SPEED_MIN 0.1f
#define TIMESTRETCH_SONIC_SPEED_MAX 6.0f

enum AudioTimestretchFallbackMode : int32_t {
	AUDIO_TIMESTRETCH_FALLBACK_CUT_REPEAT     = -1,
	AUDIO_TIMESTRETCH_FALLBACK_DEFAULT        = 0,
	AUDIO_TIMESTRETCH_FALLBACK_MUTE           = 1,
	AUDIO_TIMESTRETCH_FALLBACK_FAIL           = 2,
};

struct AudioPlaybackRate {
	float speed;
	float pitch;
	enum AudioTimestretchStretchMode  stretch_mode;
	enum AudioTimestretchFallbackMode fallback_mode;
};

static const AudioPlaybackRate AUDIO_PLAYBACK_RATE_DEFAULT = {
	AUDIO_TIMESTRETCH_SPEED_NORMAL,
	AUDIO_TIMESTRETCH_PITCH_NORMAL,
	AUDIO_TIMESTRETCH_STRETCH_DEFAULT,
	AUDIO_TIMESTRETCH_FALLBACK_DEFAULT
};

static inline bool IsAudioPlaybackRateEqual(const AudioPlaybackRate &pr1,
		const AudioPlaybackRate &pr2)
{
	return fabs(pr1.speed - pr2.speed) < AUDIO_TIMESTRETCH_SPEED_MIN_DELTA &&
		   fabs(pr1.pitch - pr2.pitch) < AUDIO_TIMESTRETCH_PITCH_MIN_DELTA &&
		   pr1.stretch_mode == pr2.stretch_mode &&
		   pr1.fallback_mode == pr2.fallback_mode;
}

static inline bool IsAudioPlaybackRateValid(const AudioPlaybackRate &playbackRate)
{
	if (playbackRate.fallback_mode == AUDIO_TIMESTRETCH_FALLBACK_FAIL &&
		(playbackRate.stretch_mode == AUDIO_TIMESTRETCH_STRETCH_SPEECH ||
		 playbackRate.stretch_mode == AUDIO_TIMESTRETCH_STRETCH_DEFAULT)) {

		return playbackRate.speed >= TIMESTRETCH_SONIC_SPEED_MIN &&
			   playbackRate.speed <= TIMESTRETCH_SONIC_SPEED_MAX &&
			   playbackRate.pitch >= AUDIO_TIMESTRETCH_PITCH_MIN &&
			   playbackRate.pitch <= AUDIO_TIMESTRETCH_PITCH_MAX;
	} else {
		return playbackRate.speed >= AUDIO_TIMESTRETCH_SPEED_MIN &&
			   playbackRate.speed <= AUDIO_TIMESTRETCH_SPEED_MAX &&
			   playbackRate.pitch >= AUDIO_TIMESTRETCH_PITCH_MIN &&
			   playbackRate.pitch <= AUDIO_TIMESTRETCH_PITCH_MAX;
	}
}

// An upper bound for the number of destination frames possible from srcFrames
// after sample rate conversion.  This may be used for buffer sizing.
static inline size_t destinationFramesPossible(size_t srcFrames, uint32_t srcSampleRate,
		uint32_t dstSampleRate)
{
	if (srcSampleRate == dstSampleRate) {
		return srcFrames;
	}
	uint64_t dstFrames = (uint64_t)srcFrames * dstSampleRate / srcSampleRate;
	return dstFrames > 2 ? dstFrames - 2 : 0;
}

static inline size_t SourceFramesNeeded(
	uint32_t src_sample_rate, size_t dst_frames_required, uint32_t dst_sample_rate)
{
	return src_sample_rate == dst_sample_rate ? dst_frames_required :
		   size_t((uint64_t)dst_frames_required * src_sample_rate / dst_sample_rate + 1 + 1);
}

static inline size_t SourceFramesNeededWithTimestretch(
	uint32_t src_sample_rate, size_t dst_frames_required, uint32_t dst_sample_rate,
	float speed)
{
	size_t required = SourceFramesNeeded(src_sample_rate, dst_frames_required, dst_sample_rate);
	return required * (double)speed + 1 + 1;
}

#define AUDIO_PROCESSING_MUSIC_RATE 40000

static inline bool isMusicRate(uint32_t sample_rate)
{
	return sample_rate >= AUDIO_PROCESSING_MUSIC_RATE;
}

} // namespace ameba::audio

#endif
