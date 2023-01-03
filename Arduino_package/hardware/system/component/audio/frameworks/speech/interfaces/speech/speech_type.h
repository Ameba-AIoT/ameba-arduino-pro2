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

/**
 * @addtogroup Speech
 * @{
 *
 * @brief Declares speech types and formats for speech framework.
 *
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file speech_type.h
 *
 * @brief Provides definition of the speech types and formats.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_TYPE_H
#define AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines all the speech error
 *
 * @since 1.0
 * @version 1.0
 */
enum {
	RTSPEECH_STATE_IDLE         = 0,
	RTSPEECH_STATE_RUNNING      = 1,
	RTSPEECH_STATE_STOPED       = 2,
};


/**
 * @brief Defines all the VAD status.
 *
 * @since 1.0
 * @version 1.0
 */
enum {
	RTSPEECH_VAD_STATUS_SPEEKING       = 0,
	RTSPEECH_VAD_STATUS_SLIENT         = 1,
};

/**
 * @brief Defines all the KWS status.
 *
 * @since 1.0
 * @version 1.0
 */
enum {
	RTSPEECH_KWS_STATUS_SPOTTING      = 0,
	RTSPEECH_KWS_STATUS_SPOTTED       = 1,
};

/**
 * @brief Defines all the ASR status.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum ASR_STATUS_t {
	RTSPEECH_ASR_STATUS_LISTENING     = 0,
	RTSPEECH_ASR_STATUS_RECOGNIZING   = 1,
	RTSPEECH_ASR_STATUS_RECOGNIZED    = 2,
	RTSPEECH_ASR_STATUS_UNRECOGNIZED  = 3,
} ASR_STATUS;

#ifdef __cplusplus
}
#endif


#endif // AMEBA_FWK_MEDIA_SPEECH_INTERFACES_SPEECH_SPEECH_TYPE_H
/** @} */
