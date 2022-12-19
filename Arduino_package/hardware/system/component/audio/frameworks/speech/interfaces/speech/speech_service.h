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

#ifndef AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_service_H
#define AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_service_H

#ifdef __cplusplus
extern "C" {
#endif
#include "speech_type.h"
#include "osal_c/osal_types.h"


struct RTSpeechService;


/**
 * @brief Defines information about speech capture parameters
 * @since 1.0
 * @version 1.0
 */
typedef struct {
	bool    auto_tts;
	int32_t param;
} RTSpeechServiceConfig;

/**
 * @brief Defines callbacks about speech
 * @since 1.0
 * @version 1.0
 */
struct SpeechCallback {
	void (*kws_callback)(int32_t status);
	void (*vad_callback)(int32_t status);
	void (*asr_callback)(int32_t status, int32_t cmd);
	void (*state_callback)(int32_t error);
};

typedef struct SpeechCallback SpeechCallback;

/**
* @brief Create RTSpeechService.
*
* @return The pointer of struct RTSpeechService.
* @since 1.0
* @version 1.0
*/
struct RTSpeechService *RTSpeechService_Create(void);

/**
 * @brief Init speech service.
 *
 * @param service is the pointer of struct RTSpeechService.
 * @param config a {@link RTSpeechServiceConfig} instance used to configure service information.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_NO_INIT | the init is not done.
 * OSAL_ERR_INVALID_OPERATION | the config value is not proper.
 * OSAL_ERR_NO_MEMORY | the memory alloc for service is fail.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTSpeechService_Init(struct RTSpeechService *service, const RTSpeechServiceConfig *config);

/**
 * @brief Speech service start.
 *
 * @param service is the pointer of struct RTSpeechService.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTSpeechService_Start(struct RTSpeechService *service);

/**
 * @brief Regist the callback for get speech status.
 *
 * @param callback is the pointer of struct SpeechCallback.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTSpeechService_RegistCallback(struct RTSpeechService *service, struct SpeechCallback *callback);

rt_status_t RTSpeechService_Pause(struct RTSpeechService *speech_service);
rt_status_t RTSpeechService_Resume(struct RTSpeechService *speech_service);

/**
 * @brief Stop speech service.
 *
 * @param service is the pointer of struct RTSpeechService.
 * @since 1.0
 * @version 1.0
 */
void RTSpeechService_Stop(struct RTSpeechService *service);

/**
 * @brief Release speech service.
 *
 * @param service is the pointer of struct RTSpeechService.
 * @since 1.0
 * @version 1.0
 */
void RTSpeechService_Destroy(struct RTSpeechService *service);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_service_H