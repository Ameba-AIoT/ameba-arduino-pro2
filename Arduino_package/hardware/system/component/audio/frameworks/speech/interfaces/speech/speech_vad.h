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

#ifndef AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_VAD_H
#define AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_VAD_H


#include "osal_c/osal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct RTVadEngine;

/**
 * @brief Defines information about vad parameters
 * @since 1.0
 * @version 1.0
 */
typedef struct {
	uint32_t frame_len;
	int32_t param;
} RTVadConfig;


/**
 * @brief Defines callbacks about vad
 * @since 1.0
 * @version 1.0
 */
struct RTVadListener {
	void (*OnError)(int32_t errors);
	void (*OnInit)(int32_t status);
	void (*OnVadStart)(void);
	void (*OnVadEnd)(void);
	void (*OnBufferReceived)(uint8_t *bytes, uint32_t len);
};
typedef struct RTVadListener RTVadListener;

/**
* @brief Create RTVadEngine.
*
* @return The pointer of struct RTVadEngine.
* @since 1.0
* @version 1.0
*/
struct RTVadEngine *RTVadEngine_Create(void);

/**
 * @brief Init vad engine.
 *
 * @param engine is the pointer of struct RTVadEngine.
 * @param config a {@link RTVadConfig} instance used to configure engine.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_NO_INIT | the init is not done.
 * OSAL_ERR_INVALID_OPERATION | the config value is not proper.
 * OSAL_ERR_NO_MEMORY | the memory alloc for engine is fail.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTVadEngine_Init(struct RTVadEngine *engine, const RTVadConfig *config);

/**
 * @brief Regist the listener for listen vad info changed.
 *
 * @param engine is the pointer of struct RTVadEngine.
 * @param listener is the pointer of struct RTVadListener.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTVadEngine_RegistListener(struct RTVadEngine *engine, struct RTVadListener *listener);

/**
 * @brief Start vad engine.
 *
 * @param engine is the pointer of struct RTVadEngine.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTVadEngine_Start(struct RTVadEngine *engine);

/**
 * @brief Feed data to vad.
 *
 * @param engine is the pointer of struct RTVadEngine.
 * @param in_buffer is the in buffer for vad. 4ms 16kHz, sized 64 samples,
 * @param out_buffer is the out buffer from vad. 4ms 16kHz, sized 64 samples,
 * @param length is the smaple numbers, 128bytes
 * @return Returns a the vad result, 0 represent sil , 1 represent speech audio
 * @since 1.0
 * @version 1.0
 */
int32_t RTVadEngine_Feed(struct RTVadEngine *engine, uint8_t *in_buffer, uint8_t *out_buffer, uint32_t length);

/**
 * @brief Regist the listener for listen vad info changed.
 *
 * @param engine is the pointer of struct RTVadEngine.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTVadEngine_Reset(struct RTVadEngine *engine);

/**
 * @brief Stop vad engine.
 *
 * @param engine is the pointer of struct RTVadEngine.
 * @since 1.0
 * @version 1.0
 */
void RTVadEngine_Stop(struct RTVadEngine *engine);

/**
 * @brief Release vad engine.
 *
 * @param engine is the pointer of struct RTVadEngine.
 * @since 1.0
 * @version 1.0
 */
void RTVadEngine_Destroy(struct RTVadEngine *engine);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_VAD_H