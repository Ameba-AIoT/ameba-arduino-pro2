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

#include "rpc/rpc_struct.h"
#include "ipc_message_queue.h"

#define SAMPLE_FREQ									16000
#define KWS_BUFF_LEN								SAMPLE_FREQ * 0.02 * 2  //kws frame shift 20ms
#define VAD_BUFF_LEN 								SAMPLE_FREQ * 0.004 * 2 // 4ms
#define ASR_BUFF_LEN								SAMPLE_FREQ * 0.01 * 2  // 10ms
#define VAD_RIGHT_MARGIN_FRAMES						25

#define AUDIO_ENABLE_AFE							1
#define AUDIO_ENABLE_MODULE							1 // if set module enable, must set AUDIO_ENABLE_AFE is 1

#define RPC_FEED_DISABLE							0
#define SPEECH_AUTO_FEED							0
#define DUMP_KWS_DATA								0
#define TEST_DATA									0
#define ENABLE_MIC									1

#ifdef ARM_CORE_CM4
#define SPEECH_RPC_MODE (BLOCK_MODE | (RPC_NP_DSP << 1))
#elif defined(RSICV_CORE_KR4)
#define SPEECH_RPC_MODE (BLOCK_MODE | (RPC_AP_DSP << 1))
#endif

#define DEFAULT_STACK_SIZE 							8192
#define RING_BUFFER_SIZE							4096
#define RECORD_SIZE									3072
#define SPEECH_DATA_CHANNEL 						0 // TODO: need redefine with IPC

typedef enum SPEECH_STATE_t {
	SPEECH_NOT_WAKEUP = 0,
	SPEECH_WAKEUPED,  //local Wakeuped, but svr not ready
	SPEECH_VAD_SIL,
	SPEECH_VAD_SIL_TO_SPEECH,
	SPEECH_VAD_SPEECH,
	SPEECH_VAD_RIGHT_MARGIN,
	SPEECH_VAD_SPEECH_TO_SIL,
	SPEECH_END,
} SPEECH_STATE;

typedef enum VAD_STATE_t {
	VAD_SIL,
	VAD_SIL_TO_SPEECH,
	VAD_SPEECH,
	VAD_RIGHT_MARGIN,
	VAD_SPEECH_TO_SIL,
} VAD_STATE;


#ifdef __cplusplus
}
#endif

#endif // AMEBA_FWK_MEDIA_SPEECH_SRC_SPEECH_UTILS_H