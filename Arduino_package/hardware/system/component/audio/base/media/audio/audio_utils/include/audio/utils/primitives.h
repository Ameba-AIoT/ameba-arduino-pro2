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

#ifndef AMEBA_BASE_MEDIA_AUDIO_AUDIO_UTILS_INCLUDE_PRIMITIVES_H
#define AMEBA_BASE_MEDIA_AUDIO_AUDIO_UTILS_INCLUDE_PRIMITIVES_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * Expand and copy samples from unsigned 8-bit offset by 0x80 to signed 16-bit.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 *
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_i16_from_u8(int16_t *dst, const uint8_t *src, size_t count);

/**
 * Shrink and copy samples from signed 32-bit fixed-point Q0.31 to signed 16-bit Q0.15.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 *
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 * The conversion is done by truncation, without dithering, so it loses resolution.
 */
void memcpy_to_i16_from_i32(int16_t *dst, const int32_t *src, size_t count);

/**
 * Shrink and copy samples from single-precision floating-point to signed 16-bit.
 * Each float should be in the range -1.0 to 1.0.  Values outside that range are clamped,
 * refer to clamp16_from_float().
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 *
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 * The conversion is done by truncation, without dithering, so it loses resolution.
 */
void memcpy_to_i16_from_float(int16_t *dst, const float *src, size_t count);

/**
 * Copy samples from signed fixed-point packed 24 bit Q0.23 to signed fixed point 16 bit Q0.15.
 * The packed 24 bit output is stored in native endian format in a uint8_t byte array.
 * The data is truncated without rounding.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 *
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_i16_from_p24(int16_t *dst, const uint8_t *src, size_t count);

/* Copy samples from signed fixed-point 32-bit Q8.23 to signed fixed point 16-bit Q0.15.
 * The data is clamped, and truncated without rounding.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_i16_from_q8_23(int16_t *dst, const int32_t *src, size_t count);

/* Copy samples from signed fixed-point 16 bit Q0.15 to single-precision floating-point.
 * The output float range is [-1.0, 1.0) for the fixed-point range [0x8000, 0x7fff].
 * No rounding is needed as the representation is exact.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_float_from_i16(float *dst, const int16_t *src, size_t count);

/* Copy samples from unsigned fixed-point 8 bit to single-precision floating-point.
 * The output float range is [-1.0, 1.0) for the fixed-point range [0x00, 0xFF].
 * No rounding is needed as the representation is exact.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_float_from_u8(float *dst, const uint8_t *src, size_t count);

/* Copy samples from signed fixed-point packed 24 bit Q0.23 to single-precision floating-point.
 * The packed 24 bit input is stored in native endian format in a uint8_t byte array.
 * The output float range is [-1.0, 1.0) for the fixed-point range [0x800000, 0x7fffff].
 * No rounding is needed as the representation is exact.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_float_from_p24(float *dst, const uint8_t *src, size_t count);

/* Copy samples from signed fixed-point 32-bit Q0.31 to single-precision floating-point.
 * The float range is [-1.0, 1.0] for the fixed-point range [0x80000000, 0x7fffffff].
 * Rounding is done according to float_from_i32().
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_float_from_i32(float *dst, const int32_t *src, size_t count);

/* Copy samples from signed fixed-point 32-bit Q8.23 to single-precision floating-point.
 * The nominal output float range is [-1.0, 1.0) for the fixed-point
 * range [0xff800000, 0x007fffff]. The maximum output float range is [-256.0, 256.0).
 * No rounding is needed as the representation is exact for nominal values.
 * Rounding for overflow values is to nearest, ties to even.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_float_from_q8_23(float *dst, const int32_t *src, size_t count);

/* Shrink and copy samples from signed 16-bit to unsigned 8-bit offset by 0x80.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 * The conversion is done by truncation, without dithering, so it loses resolution.
 */
void memcpy_to_u8_from_i16(uint8_t *dst, const int16_t *src, size_t count);

/* Copy samples from float to unsigned 8-bit offset by 0x80.
 * Parameters:
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 * The conversion is done by truncation, without dithering, so it loses resolution.
 */
void memcpy_to_u8_from_float(uint8_t *dst, const float *src, size_t count);

/* Copy samples from signed fixed point 16 bit Q0.15 to signed fixed-point packed 24 bit Q0.23.
 * The packed 24 bit output is assumed to be a native-endian uint8_t byte array.
 * The output data range is [0x800000, 0x7fff00] (not full).
 * Nevertheless there is no DC offset on the output, if the input has no DC offset.
 *
 * \param dst     Destination buffer
 * \param src     Source buffer
 * \param count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_p24_from_i16(uint8_t *dst, const int16_t *src, size_t count);

/* Copy samples from single-precision floating-point to signed fixed-point packed 24 bit Q0.23.
 * The packed 24 bit output is assumed to be a native-endian uint8_t byte array.
 * The data is clamped and rounded to nearest, ties away from zero. See clamp24_from_float()
 * for details.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_p24_from_float(uint8_t *dst, const float *src, size_t count);

/* Shrink and copy samples from signed 32-bit fixed-point Q0.31
 * to signed fixed-point packed 24 bit Q0.23.
 * The packed 24 bit output is assumed to be a native-endian uint8_t byte array.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 * The conversion is done by truncation, without dithering, so it loses resolution.
 */
void memcpy_to_p24_from_i32(uint8_t *dst, const int32_t *src, size_t count);

/* Copy samples from signed fixed point 16-bit Q0.15 to signed fixed-point 32-bit Q0.31.
 * The output data range is [0x80000000, 0x7fff0000] at intervals of 0x10000.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_i32_from_i16(int32_t *dst, const int16_t *src, size_t count);

/* Copy samples from single-precision floating-point to signed fixed-point 32-bit Q0.31.
 * If rounding is needed on truncation, the fractional lsb is rounded to nearest,
 * ties away from zero. See clamp32_from_float() for details.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_i32_from_float(int32_t *dst, const float *src, size_t count);

/* Copy samples from signed fixed point 16-bit Q0.15 to signed fixed-point 32-bit Q8.23.
 * The output data range is [0xff800000, 0x007fff00] at intervals of 0x100.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_q8_23_from_i16(int32_t *dst, const int16_t *src, size_t count);

/* Copy samples from single-precision floating-point to signed fixed-point 32-bit Q8.23.
 * This copy will clamp the Q8.23 representation to [0xff800000, 0x007fffff] even though there
 * are guard bits available. Fractional lsb is rounded to nearest, ties away from zero.
 * See clamp24_from_float() for details.
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must either be completely separate (non-overlapping), or
 * they must both start at the same address.  Partially overlapping buffers are not supported.
 */
void memcpy_to_q8_23_from_float_with_clamp(int32_t *dst, const float *src, size_t count);

/* Copy samples from signed fixed point packed 24-bit Q0.23 to signed fixed-point 32-bit Q8.23.
 * The output data range is [0xff800000, 0x007fffff].
 *
 *  \param dst     Destination buffer
 *  \param src     Source buffer
 *  \param count   Number of samples to copy
 * The destination and source buffers must be completely separate.
 */
void memcpy_to_q8_23_from_p24(int32_t *dst, const uint8_t *src, size_t count);

/* Downmix pairs of interleaved stereo input 16-bit samples to mono output 16-bit samples.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of stereo frames to downmix
 * The destination and source buffers must be completely separate (non-overlapping).
 * The current implementation truncates the mean rather than dither, but this may change.
 */
void downmix_to_mono_i16_from_stereo_i16(int16_t *dst, const int16_t *src, size_t count);

void downmix_to_mono_i32_from_stereo_i32(int32_t *dst, const int32_t *src, size_t frames);

/* Upmix mono input 16-bit samples to pairs of interleaved stereo output 16-bit samples by
 * duplicating.
 * Parameters:
 *  dst     Destination buffer
 *  src     Source buffer
 *  count   Number of mono samples to upmix
 * The destination and source buffers must be completely separate (non-overlapping).
 */
void upmix_to_stereo_i16_from_mono_i16(int16_t *dst, const int16_t *src, size_t count);

static inline float float_from_u8(uint8_t uval)
{
	static const float scale = 1. / (float)(1UL << 7);

	return ((int)uval - 128) * scale;
}

static inline float float_from_i16(int16_t ival)
{
	static const float scale = 1. / (float)(1UL << 15);

	return ival * scale;
}

static inline float float_from_i32(int32_t ival)
{
	static const float scale = 1. / (float)(1UL << 31);

	return ival * scale;
}

static inline int32_t i32_from_p24(const uint8_t *packed24)
{
	return (packed24[0] << 8) | (packed24[1] << 16) | (packed24[2] << 24);
}

static inline float float_from_p24(const uint8_t *packed24)
{
	return float_from_i32(i32_from_p24(packed24));
}

static inline float float_from_q8_23(int32_t ival)
{
	static const float scale = 1. / (float)(1UL << 23);

	return ival * scale;
}

static inline int16_t clamp16_from_float(float f)
{
	static const float scale = 1 << 15;
	return roundf(fmaxf(fminf(f * scale, scale - 1.f), -scale));
}

/**
 * Clamp (aka hard limit or clip) a signed 32-bit sample to 16-bit range.
 */
static inline int16_t clamp16(int32_t sample)
{
	if ((sample >> 15) ^ (sample >> 31)) {
		sample = 0x7FFF ^ (sample >> 31);
	}
	return sample;
}

static inline uint8_t clamp8_from_float(float f)
{
	static const float offset = (float)((3 << (22 - 7)) + 1 /* to cancel -1.0 */);
	static const int32_t limneg = (0x11f << 22) /*zero*/;
	static const int32_t limpos = (0x11f << 22) /*zero*/ + 255;

	union {
		float f;
		int32_t i;
	} u;

	u.f = f + offset;
	if (u.i < limneg) {
		return 0;
	}
	if (u.i > limpos) {
		return 255;
	}
	return u.i;
}

static inline int32_t clamp24_from_float(float f)
{
	static const float scale = (float)(1 << 23);
	static const float limpos = 0x7fffff / scale;
	static const float limneg = -0x800000 / scale;

	if (f <= limneg) {
		return -0x800000;
	} else if (f >= limpos) {
		return 0x7fffff;
	}
	f *= scale;

	return f > 0 ? f + 0.5 : f - 0.5;
}

static inline int32_t clamp32_from_float(float f)
{
	static const float scale = (float)(1UL << 31);
	static const float limpos = 1.;
	static const float limneg = -1.;

	if (f <= limneg) {
		return -0x80000000; /* or 0x80000000 */
	} else if (f >= limpos) {
		return 0x7fffffff;
	}
	f *= scale;
	return f > 0 ? f + 0.5 : f - 0.5;
}

static inline float float_from_u4_28(uint32_t uval)
{
	static const float scale = 1. / (float)(1UL << 28);

	return uval * scale;
}

static inline uint16_t u4_12_from_float(float f)
{
	static const float scale = (float)(1 << 12);
	static const float limpos = 0xffff / scale;

	if (f <= 0.) {
		return 0;
	} else if (f >= limpos) {
		return 0xffff;
	}

	return f * scale + 0.5;
}

static inline uint32_t u4_28_from_float(float f)
{
	static const float scale = (float)(1 << 28);
	static const float limpos = 0xffffffffUL / scale;

	if (f <= 0.) {
		return 0;
	} else if (f >= limpos) {
		return 0xffffffff;
	}

	return f * scale + 0.5;
}

unsigned roundup(unsigned v);
__END_DECLS

#endif  // AMEBA_BASE_MEDIA_AUDIO_AUDIO_UTILS_INCLUDE_PRIMITIVES_H
