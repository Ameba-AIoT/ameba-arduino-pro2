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

#ifndef AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_ASR_H
#define AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_ASR_H


#include "osal_c/osal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct RTAsrEngine;

/**
 * @brief Defines information about asr parameters
 * @since 1.0
 * @version 1.0
 */
typedef struct {
	uint32_t frame_len;
	uint32_t pause_time;
	uint32_t max_timeout;
	int32_t param;
} RTAsrConfig;


/**
 * @brief Defines callbacks about asr
 * @since 1.0
 * @version 1.0
 */
struct RTAsrListener {
	void (*OnError)(int32_t errors);
	void (*OnInit)(int32_t status);
	void (*OnBeginningOfSpeech)(void);
	void (*OnEndOfSpeech)(void);
	void (*OnReadyForSpeech)(void);
	void (*OnResults)(int32_t state, int32_t cmd_index, const char *result);
};
typedef struct RTAsrListener RTAsrListener;

/**
* @brief Create RTAsrEngine.
*
* @return The pointer of struct RTAsrEngine.
* @since 1.0
* @version 1.0
*/
struct RTAsrEngine *RTAsrEngine_Create(void);

/**
 * @brief Init asr engine.
 *
 * @param engine is the pointer of struct RTAsrEngine.
 * @param config a {@link RTAsrConfig} instance used to configure engine.
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
rt_status_t RTAsrEngine_Init(struct RTAsrEngine *engine, const RTAsrConfig *config);

/**
 * @brief Regist the listener for listen asr info changed.
 *
 * @param engine is the pointer of struct RTAsrEngine.
 * @param listener is the pointer of struct RTAsrListener.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAsrEngine_RegistListener(struct RTAsrEngine *engine, struct RTAsrListener *listener);

/**
 * @brief Start asr engine.
 *
 * @param engine is the pointer of struct RTAsrEngine.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAsrEngine_Start(struct RTAsrEngine *engine);

/**
 * @brief Feed data to asr.
 *
 * @param engine is the pointer of struct RTAsrEngine.
 * @param in_buffer is the in buffer for asr, must be 16kHz 10ms(160) samples
 * @param length is the smaple numbers,  320bytes
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAsrEngine_Feed(struct RTAsrEngine *engine, uint8_t *in_buffer, uint32_t length);

/**
 * @brief Finish feed data to asr.
 *
 * @param engine is the pointer of struct RTAsrEngine.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAsrEngine_FeedEnd(struct RTAsrEngine *engine);

/**
 * @brief Set asr uniformity.
 *
 * @param engine is the pointer of struct RTAsrEngine.
 * @param type is the uniformity type.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAsrEngine_SetUniformity(struct RTAsrEngine *engine, int32_t type);

/**
 * @brief Regist the listener for listen asr info changed.
 *
 * @param engine is the pointer of struct RTAsrEngine.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAsrEngine_Reset(struct RTAsrEngine *engine);

/**
 * @brief Stop asr engine.
 *
 * @param engine is the pointer of struct RTAsrEngine.
 * @since 1.0
 * @version 1.0
 */
void RTAsrEngine_Stop(struct RTAsrEngine *engine);

/**
 * @brief Release asr engine.
 *
 * @param engine is the pointer of struct RTAsrEngine.
 * @since 1.0
 * @version 1.0
 */
void RTAsrEngine_Destroy(struct RTAsrEngine *engine);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_ASR_H