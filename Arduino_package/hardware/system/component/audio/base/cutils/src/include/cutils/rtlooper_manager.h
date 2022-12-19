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

#ifndef AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_LOOPER_MANAGER_H
#define AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_LOOPER_MANAGER_H

#include "osal_c/osal_types.h"

#include "cutils/rtlooper_types.h"

#ifdef __cplusplus
extern "C" {
#endif

rt_handler_id RTLooperManager_RegisterHandler(RTLooper *looper, RTMessageHandler *handler);
void RTLooperManager_UnregisterHandler(const rt_handler_id handler_id);
void RTLooperManager_Deinit();

#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_LOOPER_MANAGER_H
