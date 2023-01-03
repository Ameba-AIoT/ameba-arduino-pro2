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

#ifndef AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_DATA_BUFFER_H
#define AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_DATA_BUFFER_H

#include "osal_c/osal_types.h"
#include "cutils/rtinterfaces.h"
#include "cutils/rtreference.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RTDataBufferInternal RTDataBufferInternal;
typedef struct RTMessage RTMessage;

typedef struct {
	RT_IMPLEMENTS(RTReference);
	uint32_t ref_count;
	RTDataBufferInternal *internal;
} RTDataBuffer;

RTDataBuffer *RTDataBuffer_Create(void *data, size_t capacity, bool owns);
RTDataBuffer *RTDataBuffer_CreateAsCopy(size_t capacity, const void *data);
rt_status_t RTDataBuffer_Destroy(RTDataBuffer *self);

uint8_t *RTDataBuffer_GetBase(RTDataBuffer *self);
uint8_t *RTDataBuffer_GetData(RTDataBuffer *self);
size_t RTDataBuffer_Capacity(RTDataBuffer *self);
size_t RTDataBuffer_Size(RTDataBuffer *self);
size_t RTDataBuffer_Offset(RTDataBuffer *self);

void RTDataBuffer_SetRange(RTDataBuffer *self, size_t offset, size_t size);

RTMessage *RTDataBuffer_GetMeta(RTDataBuffer *self);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_DATA_BUFFER_H
