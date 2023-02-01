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


#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_AUDIO_UTILS_INCLUDE_MINIFLOAT_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_AUDIO_UTILS_INCLUDE_MINIFLOAT_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <math.h>

__BEGIN_DECLS

#define EXPONENT_BITS   3
#define EXPONENT_MAX    ((1 << EXPONENT_BITS) - 1)
#define EXCESS          ((1 << EXPONENT_BITS) - 2)

#define MANTISSA_BITS   13
#define MANTISSA_MAX    ((1 << MANTISSA_BITS) - 1)
#define HIDDEN_BIT      (1 << MANTISSA_BITS)
#define ONE_FLOAT       ((float) (1 << (MANTISSA_BITS + 1)))

#define MINIFLOAT_MAX   ((EXPONENT_MAX << MANTISSA_BITS) | MANTISSA_MAX)

#if EXPONENT_BITS + MANTISSA_BITS != 16
#error EXPONENT_BITS and MANTISSA_BITS must sum to 16
#endif

typedef uint16_t gain_minifloat_t;

typedef uint32_t gain_minifloat_packed_t;

#define GAIN_FLOAT_ZERO         0.0f
#define GAIN_FLOAT_UNITY        1.0f

#define GAIN_MINIFLOAT_UNITY    0xE000

static inline gain_minifloat_packed_t gain_minifloat_pack(gain_minifloat_t left,
		gain_minifloat_t right)
{
	return (right << 16) | left;
}

static inline gain_minifloat_t gain_minifloat_unpack_left(gain_minifloat_packed_t packed)
{
	return packed & 0xFFFF;
}

static inline gain_minifloat_t gain_minifloat_unpack_right(gain_minifloat_packed_t packed)
{
	return packed >> 16;
}

#define GAIN_MINIFLOAT_PACKED_UNITY gain_minifloat_pack(GAIN_MINIFLOAT_UNITY, GAIN_MINIFLOAT_UNITY)


static inline gain_minifloat_t gain_from_float(float v)
{
	if (isnan(v) || v <= 0.0f) {
		return 0;
	}
	if (v >= 2.0f) {
		return MINIFLOAT_MAX;
	}
	int exp;
	float r = frexpf(v, &exp);
	if ((exp += EXCESS) > EXPONENT_MAX) {
		return MINIFLOAT_MAX;
	}
	if (-exp >= MANTISSA_BITS) {
		return 0;
	}
	int mantissa = (int)(r * ONE_FLOAT);
	return exp > 0 ? (exp << MANTISSA_BITS) | (mantissa & ~HIDDEN_BIT) :
		   (mantissa >> (1 - exp)) & MANTISSA_MAX;
}

static inline float float_from_gain(gain_minifloat_t a)
{
	int mantissa = a & MANTISSA_MAX;
	int exponent = (a >> MANTISSA_BITS) & EXPONENT_MAX;
	return ldexpf((exponent > 0 ? HIDDEN_BIT | mantissa : mantissa << 1) / ONE_FLOAT,
				  exponent - EXCESS);
}

__END_DECLS

#endif
