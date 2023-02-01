/*
 * Copyright (c) 2021 Realtek, LLC.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_BASE_MEDIA_AUDIO_AUDIO_UTILS_INCLUDE_AUDIO_UTILS_BASE_TYPES_H
#define AMEBA_BASE_MEDIA_AUDIO_AUDIO_UTILS_INCLUDE_AUDIO_UTILS_BASE_TYPES_H

#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * @brief Enumerates the audio format type.
 *
 * describes an audio streaming type.
 */
typedef enum AudioFormat {
	AUDIO_FORMAT_INVALID             = 0xFFFFFFFFu,
	AUDIO_FORMAT_DEFAULT             = 0,
	AUDIO_FORMAT_PCM                 = 0x00000000u,
	AUDIO_FORMAT_MAIN_MASK           = 0xFF000000u,
	AUDIO_FORMAT_SUB_MASK            = 0x00FFFFFFu,

	AUDIO_FORMAT_PCM_8_BIT  = 0x1u,       /**< 8-bit PCM */
	AUDIO_FORMAT_PCM_16_BIT = 0x2u,       /**< 16-bit PCM */
	AUDIO_FORMAT_PCM_24_BIT = 0x3u,       /**< 24-bit PCM */
	AUDIO_FORMAT_PCM_32_BIT = 0x4u,       /**< 32-bit PCM */
	AUDIO_FORMAT_PCM_FLOAT  = 0x5u,       /**< float PCM */
	AUDIO_FORMAT_PCM_24_BIT_PACKED = 0x6u,/**< 24-bit PCM */
	AUDIO_FORMAT_PCM_8_24_BIT = 0x7u,     /**< 8-24-bit PCM */

} AudioFormat;

/**
 * @brief Enumerates the audio channel mask.
 *
 * A mask describes an audio channel position.
 */
typedef enum AudioChannelMask {
	AUDIO_CHANNEL_NONE                      = 0x0u,

	AUDIO_CHANNEL_FRONT_LEFT  = 0x1u,  /**< Front left channel */
	AUDIO_CHANNEL_FRONT_RIGHT = 0x2u,  /**< Front right channel */
	AUDIO_CHANNEL_MONO        = 0x1u, /**< Mono channel */
	AUDIO_CHANNEL_STEREO      = 0x3u, /**< Stereo channel, consisting of front left and front right channels */
} AudioChannelMask;

/**
 * @brief Enumerates the audio category.
 */
enum AudioCategory {
	AUDIO_IN_MEDIA = 0,     /**< Media */
	AUDIO_IN_COMMUNICATION, /**< Communications */
	AUDIO_IN_SPEECH,
	AUDIO_IN_BEEP,
	AUDIO_CATEGORY_MAX_NUM,
};

__END_DECLS

#endif  // AMEBA_BASE_MEDIA_AUDIO_AUDIO_UTILS_INCLUDE_AUDIO_UTILS_BASE_TYPES_H