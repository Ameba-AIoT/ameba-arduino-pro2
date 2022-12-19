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

#ifndef AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_LOOPER_H
#define AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_LOOPER_H

#include "osal_c/osal_types.h"

#include "cutils/rtmessage_types.h"
#include "cutils/rtmessage_handler_types.h"
#include "cutils/rtlooper_types.h"

#ifdef __cplusplus
extern "C" {
#endif

RTLooper *RTLooper_Create(const char *name);
rt_status_t RTLooper_Destroy(RTLooper *looper);

rt_status_t RTLooper_SetName(RTLooper *looper, const char *name);
const char *RTLooper_Name(const RTLooper *looper);

rt_status_t RTLooper_RegisterHandler(RTLooper *looper, RTMessageHandler *handler);
rt_status_t RTLooper_UnregisterHandler(RTLooper *looper, const rt_handler_id id);

rt_status_t RTLooper_Start(RTLooper *looper, bool run_local, int32_t priority);
rt_status_t RTLooper_Stop(RTLooper *looper);

rt_status_t RTLooper_Post(RTLooper *looper, RTMessage *msg, int64_t delay_us);

RTReplyToken *RTLooper_CreateReplyToken(RTLooper *looper);
rt_status_t RTLooper_PostReply(RTLooper *looper, RTReplyToken *reply_token, RTMessage *reply);
rt_status_t RTLooper_WaitResponse(RTLooper *looper, RTReplyToken *reply_token, RTMessage **response);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_LOOPER_H
