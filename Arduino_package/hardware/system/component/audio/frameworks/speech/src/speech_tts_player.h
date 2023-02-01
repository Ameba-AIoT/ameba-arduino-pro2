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

#ifndef AMEBA_FWK_MEDIA_SPEECH_SRC_SPEECH_UTILS_H
#define AMEBA_FWK_MEDIA_SPEECH_SRC_SPEECH_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"

typedef struct {
	uint32_t source;
	uint32_t length;
} TTS_source;

void PlayAudioSource(void);

void PauseAudioSource(void);

void PlayTtsSource(int cmd);

void PlayTTSData(uint32_t source, uint32_t length);

void tts_player_init(void);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_FWK_MEDIA_SPEECH_SRC_SPEECH_UTILS_H