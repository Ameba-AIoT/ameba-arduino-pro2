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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_BYTE_UTILS_H
#define AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_BYTE_UTILS_H

#include <stdint.h>
#include <sys/types.h>

#if !defined(__RTOS__)
#include <arpa/inet.h>
#endif

#include "osal_c/osal_compat.h"

namespace ameba::media
{

constexpr int FOURCC(unsigned char c1, unsigned char c2, unsigned char c3, unsigned char c4)
{
	return ((c1) << 24 | (c2) << 16 | (c3) << 8 | (c4));
}

template <size_t N>
constexpr int32_t FOURCC(const char (&s) [N])
{
	static_assert(N == 5, "fourcc: wrong length");
	return
		(unsigned char) s[0] << 24 |
		(unsigned char) s[1] << 16 |
		(unsigned char) s[2] << 8 |
		(unsigned char) s[3] << 0;
}

uint16_t U16_AT(const uint8_t *ptr);
uint32_t U32_AT(const uint8_t *ptr);
uint64_t U64_AT(const uint8_t *ptr);

uint16_t U16LE_AT(const uint8_t *ptr);
uint32_t U32LE_AT(const uint8_t *ptr);
uint64_t U64LE_AT(const uint8_t *ptr);

uint64_t Ntoh64(uint64_t x);
uint64_t Hton64(uint64_t x);

void MakeFourCCString(uint32_t x, char *s);

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_BYTE_UTILS_H

