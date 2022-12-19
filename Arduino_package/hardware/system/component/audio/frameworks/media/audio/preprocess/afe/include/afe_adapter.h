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

#ifndef AMEBA_COMPONENT_AUDIO_HAL_SRC_PREPROCESS_AFE_ADAPTER_H
#define AMEBA_COMPONENT_AUDIO_HAL_SRC_PREPROCESS_AFE_ADAPTER_H

#include <stdint.h>

#define AFE_SUPPORT_FRAME_LENGTH 256
#define AFE_SUPPORT_SAMPLING_RATE 16000

int RTAUDIO_AFE_Init(int rate, int frame_length);
int RTAUDIO_AFE_Process(short int *mic1, short int *mic2, short int *ref, short int *out);
void RTAUDIO_AFE_Destroy(void);

#endif