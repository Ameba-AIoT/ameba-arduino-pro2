/*
 * Copyright (c) 2022 Realtek, LLC.
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
#ifndef AMEBA_FWK_MEDIA_SPEECH_SRC_RING_BUFFER_H
#define AMEBA_FWK_MEDIA_SPEECH_SRC_RING_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

typedef struct {
	uint8_t *source;
	uint32_t br;
	uint32_t bw;
	uint32_t buf_to_read;
	uint32_t length;
} RingBuffer_t;


void InitRingBuffer(RingBuffer_t *ringBuf, uint8_t *buf, uint32_t buf_len);

void DeInitRingBuffer(RingBuffer_t *ringBuf);

uint32_t WriteRingBuffer(uint8_t *buffer, uint32_t size, RingBuffer_t *ringBuf);

uint32_t ReadRingBuffer(uint8_t *buffer, uint32_t size, RingBuffer_t *ringBuf);

uint32_t GetReadableSize(RingBuffer_t *ringBuf);

uint32_t GetWritableSize(RingBuffer_t *ring_buf);

uint32_t GetRingBufferLength(RingBuffer_t *ringBuf);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_FWK_MEDIA_SPEECH_SRC_RING_BUFFER_H
