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

#ifndef AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_MESSAGE_H
#define AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_MESSAGE_H

#include "osal_c/osal_types.h"

#include "cutils/rtinterfaces.h"
#include "cutils/rtreference.h"
#include "cutils/rtmessage_handler_types.h"
#include "cutils/rtmessage_types.h"
#include "cutils/rtstring.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RTMessageInternal RTMessageInternal;
typedef struct RTReplyTokenInternal RTReplyTokenInternal;

struct RTMessage {
	RT_IMPLEMENTS(RTReference);
	uint32_t ref_count;
	RTMessageInternal *internal;
};

struct RTReplyToken {
	RT_IMPLEMENTS(RTReference);
	uint32_t ref_count;
	RTReplyTokenInternal *internal;
};

RTMessage *RTMessage_Create();
RTMessage *RTMessage_CreateEx(uint32_t what, RTMessageHandler *handler);
rt_status_t RTMessage_Destroy(RTMessage *msg);

void RTMessage_Clear(RTMessage *msg);
void RTMessage_SetTarget(RTMessage *msg, RTMessageHandler *handler);
void RTMessage_SetWhat(RTMessage *msg, uint32_t what);
uint32_t RTMessage_What(const RTMessage *msg);

void RTMessage_SetInt32(RTMessage *msg, const char *name, int32_t value);
bool RTMessage_FindInt32(const RTMessage *msg, const char *name, int32_t *value);
void RTMessage_SetInt64(RTMessage *msg, const char *name, int64_t value);
bool RTMessage_FindInt64(const RTMessage *msg, const char *name, int64_t *value);
void RTMessage_SetSize(RTMessage *msg, const char *name, size_t value);
bool RTMessage_FindSize(const RTMessage *msg, const char *name, size_t *value);
void RTMessage_SetFloat(RTMessage *msg, const char *name, float value);
bool RTMessage_FindFloat(const RTMessage *msg, const char *name, float *value);
void RTMessage_SetDouble(RTMessage *msg, const char *name, double value);
bool RTMessage_FindDouble(const RTMessage *msg, const char *name, double *value);
void RTMessage_SetPointer(RTMessage *msg, const char *name, void *value);
bool RTMessage_FindPointer(const RTMessage *msg, const char *name, void **value);
void RTMessage_SetCString(RTMessage *msg, const char *name, char *s, ssize_t len);
void RTMessage_SetString(RTMessage *msg, const char *name, RTString *s);
bool RTMessage_FindString(const RTMessage *msg, const char *name, RTString **value);
void RTMessage_Deliver(RTMessage *msg);
rt_status_t RTMessage_Post(RTMessage *msg, int64_t delay_us);
rt_status_t RTMessage_PostAndWaitResponse(RTMessage *msg, RTMessage **response);
bool RTMessage_SenderWaitsResponse(RTMessage *msg, RTReplyToken **reply_token);
rt_status_t RTMessage_PostReply(RTMessage *msg, RTReplyToken *reply_token);
RTMessage *RTMessage_Duplicate(const RTMessage *msg);

RTReplyToken *RTReplyToken_Create(RTLooper *looper);
rt_status_t RTReplyToken_Destroy(RTReplyToken *token);
rt_status_t RTReplyToken_SetReply(RTReplyToken *token, RTMessage *msg);
bool RTReplyToken_RetrieveReply(RTReplyToken *token, RTMessage **reply);
RTLooper *RTReplyToken_GetLooper(const RTReplyToken *token);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_MESSAGE_H
