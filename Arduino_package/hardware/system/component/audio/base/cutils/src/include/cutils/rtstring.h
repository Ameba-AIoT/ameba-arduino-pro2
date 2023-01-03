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

#ifndef AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_STRING_H
#define AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_STRING_H

#include "osal_c/osal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RTString RTString;

RTString *RTString_Create();
RTString *RTString_CreateAsCopyOther(const char *s);
RTString *RTString_CreateAsCopyOtherWithSize(const char *s, size_t size);
RTString *RTString_CreateAsCopy(RTString *from);
RTString *RTString_CreateAsCopyWithOffset(const RTString *from, size_t offset, size_t n);

rt_status_t RTString_Destroy(RTString *self);
size_t RTString_Size(RTString *self);
char *RTString_Str(RTString *self);
bool RTString_Empty(RTString *self);
rt_status_t RTString_SetTo(RTString *self, const char *s);
rt_status_t RTString_SetToWithSize(RTString *self, const char *s, size_t size);
rt_status_t RTString_SetToWithOffset(RTString *self, const RTString *from, size_t offset, size_t n);
void RTString_Clear(RTString *self);
void RTString_Trim(RTString *self);
void RTString_Erase(RTString *self, size_t start, size_t n);
rt_status_t RTString_Append(RTString *self, const char *s);
rt_status_t RTString_AppendWithSize(RTString *self, const char *s, size_t size);
rt_status_t RTString_AppendAsCopy(RTString *self, const RTString *from);
rt_status_t RTString_AppendAsCopyWithOffset(RTString *self, const RTString *from, size_t offset, size_t n);
rt_status_t RTString_AppendInt(RTString *self, int x);
rt_status_t RTString_AppendUnsigned(RTString *self, unsigned x);
rt_status_t RTString_AppendLong(RTString *self, long x);
rt_status_t RTString_AppendUnsignedLong(RTString *self, unsigned long x);
rt_status_t RTString_AppendLongLong(RTString *self, long long x);
rt_status_t RTString_AppendUnsignedLongLong(RTString *self, unsigned long long x);
rt_status_t RTString_AppendFloat(RTString *self, float x);
rt_status_t RTString_AppendDouble(RTString *self, double x);
rt_status_t RTString_AppendVoid(RTString *self, void *x);
ssize_t RTString_Find(RTString *self, const char *sub_string, size_t start);
void RTString_Insert(RTString *self, const RTString *from, size_t insertion_pos);
void RTString_InsertWithSize(RTString *self, const char *from, size_t size, size_t insertion_pos);
int RTString_Compare(RTString *self, const RTString *other);
int RTString_CompareIgnoreCase(RTString *self, const RTString *other);
void RTString_Tolower(RTString *self);
bool RTString_StartsWith(RTString *self, const char *prefix);

RTString *RTString_Printf(char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_STRING_H */
