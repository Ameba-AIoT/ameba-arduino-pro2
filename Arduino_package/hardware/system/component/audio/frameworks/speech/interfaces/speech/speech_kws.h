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

#ifndef AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_KWS_H
#define AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_KWS_H


#include "osal_c/osal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct RTKwsEngine;

/**
 * @brief Defines information about kws parameters
 * @since 1.0
 * @version 1.0
 */
typedef struct {
	uint32_t frame_len;
	int32_t param;
} RTKwsConfig;


/**
 * @brief Defines callbacks about kws
 * @since 1.0
 * @version 1.0
 */
struct RTKwsListener {
	void (*OnError)(int32_t errors);
	void (*OnInit)(int32_t status);
	void (*OnWakeup)(void);
	void (*OnReadyForSpeech)(void);
};
typedef struct RTKwsListener RTKwsListener;

/**
* @brief Create RTKwsEngine.
*
* @return The pointer of struct RTKwsEngine.
* @since 1.0
* @version 1.0
*/
struct RTKwsEngine *RTKwsEngine_Create(void);

/**
 * @brief Init kws engine.
 *
 * @param engine is the pointer of struct RTKwsEngine.
 * @param config a {@link RTKwsConfig} instance used to configure engine.
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
rt_status_t RTKwsEngine_Init(struct RTKwsEngine *engine, const RTKwsConfig *config);

/**
 * @brief Regist the listener for listen kws info changed.
 *
 * @param engine is the pointer of struct RTKwsEngine.
 * @param listener is the pointer of struct RTKwsListener.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTKwsEngine_RegistListener(struct RTKwsEngine *engine, struct RTKwsListener *listener);

/**
 * @brief Start kws engine.
 *
 * @param engine is the pointer of struct RTKwsEngine.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTKwsEngine_Start(struct RTKwsEngine *engine);

/**
 * @brief Set kws word.
 *
 * @param engine is the pointer of struct RTKwsEngine.
 * @param key_word is the key word for kws.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTKwsEngine_SetKwsWord(struct RTKwsEngine *engine, const char *key_word);

/**
 * @brief Feed data to kws.
 *
 * @param engine is the pointer of struct RTKwsEngine.
 * @param in_buffer is the in buffer for kws. must be 16kHz 20ms(320) samples
 * @param length is the smaple numbers,  640 bytes.
 * @return Return the kws result,
 * 0, no kws
 * 1, first key word kws
 * 2, second key word kws
 * @since 1.0
 * @version 1.0
 */
int32_t RTKwsEngine_Feed(struct RTKwsEngine *engine, uint8_t *in_buffer, uint32_t length);

/**
 * @brief Regist the listener for listen kws info changed.
 *
 * @param engine is the pointer of struct RTKwsEngine.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTKwsEngine_Reset(struct RTKwsEngine *engine);

/**
 * @brief Stop kws engine.
 *
 * @param engine is the pointer of struct RTKwsEngine.
 * @since 1.0
 * @version 1.0
 */
void RTKwsEngine_Stop(struct RTKwsEngine *engine);

/**
 * @brief Release kws engine.
 *
 * @param engine is the pointer of struct RTKwsEngine.
 * @since 1.0
 * @version 1.0
 */
void RTKwsEngine_Destroy(struct RTKwsEngine *engine);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_KWS_H