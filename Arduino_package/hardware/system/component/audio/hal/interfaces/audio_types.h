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

#ifndef AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_TYPES_H
#define AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/cdefs.h>

#include "cutils/bitops.h"

__BEGIN_DECLS

#define AUDIO_ADC0_CHOSE_AMIC         "adc0_sel_amic_num"
#define AUDIO_ADC1_CHOSE_AMIC         "adc1_sel_amic_num"
#define AUDIO_ADC2_CHOSE_AMIC         "adc2_sel_amic_num"
#define AUDIO_ADC3_CHOSE_AMIC         "adc3_sel_amic_num"

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
	AUDIO_FORMAT_AAC_MAIN   = 0x1000001u, /**< AAC main */
	AUDIO_FORMAT_AAC_LC     = 0x1000002u, /**< AAC LC */
	AUDIO_FORMAT_AAC_LD     = 0x1000003u, /**< AAC LD */
	AUDIO_FORMAT_AAC_ELD    = 0x1000004u, /**< AAC ELD */
	AUDIO_FORMAT_AAC_HE_V1  = 0x1000005u, /**< AAC HE_V1 */
	AUDIO_FORMAT_AAC_HE_V2  = 0x1000006u, /**< AAC HE_V2 */
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

enum {
	AUDIO_IO_ID_INVALID = -1,
};

typedef int32_t AudioAdapterId;
typedef int32_t AudioIoId;


enum AudioPortDirection {
	PORT_OUT    = 0x1u, /**< Output port */
	PORT_IN     = 0x2u, /**< Input port */
	PORT_OUT_IN = 0x3u, /**< Input/output port, supporting both audio input and output */
};

struct AudioPort {
	enum AudioPortDirection dir; /**< Audio port type. For details, see {@link AudioPortDirection} */
	uint32_t port_id;             /**< Audio port ID */
	const char *port_name;        /**< Audio port name */
};

struct AudioAdapterDescriptor {
	const char *adapterName; /**< Name of the audio adapter */
	uint32_t portNum;        /**< Number of ports supported by an audio adapter */
	struct AudioPort *ports; /**< List of ports supported by an audio adapter */
};

/**
 * @brief Enumerates the pin of an audio adapter.
 */
enum AudioPortPin {
	PIN_NONE        = 0x0u,       /**< Invalid pin */
	PIN_OUT_SPEAKER = 0x1u,       /**< Speaker output pin */
	PIN_OUT_HEADSET = 0x2u,       /**< Wired headset pin for output */
	PIN_OUT_LINEOUT = 0x4u,       /**< Line-out pin */
	PIN_OUT_HDMI    = 0x8u,       /**< HDMI output pin */
	PIN_IN_MIC      = 0x8000001u, /**< Microphone input pin */
	PIN_IN_HS_MIC   = 0x8000002u, /**< Wired headset microphone pin for input */
	PIN_IN_LINEIN   = 0x8000004u, /**< Line-in pin */
};

/**
 * @brief Defines the audio device descriptor.
 */
struct AudioDeviceDescriptor {
	uint32_t port_id;        /**< Audio port ID */
	enum AudioPortPin pins; /**< Pins of audio ports (input and output). For details, see {@link AudioPortPin}. */
	const char *desc;       /**< Audio device name */
};

/**
 * @brief Enumerates the audio category.
 */
enum AudioCategory {
	AUDIO_IN_MEDIA = 0,     /**< Media */
	AUDIO_IN_COMMUNICATION, /**< Communications */
};

/**
 * @brief Defines audio sampling attributes.
 */
struct AudioSampleAttributes {
	enum AudioCategory type; /**< Audio type. For details, see {@link AudioCategory} */
	bool interleaved;        /**< Interleaving flag of audio data */
	AudioFormat format; /**< Audio data format. For details, see {@link AudioFormat}. */
	uint32_t sample_rate;     /**< Audio sampling rate */
	uint32_t channel_count;   /**< Number of audio channels. For example, for the mono channel, the value is 1,
                              * and for the stereo channel, the value is 2.
                              */
	uint32_t period_size;
};

/**
 * @brief Defines the audio port capability.
 */
struct AudioPortCapability {
	uint32_t device_type;                     /**< Device type (output or input) */
	uint32_t device_id;                       /**< Device ID used for device binding */
	bool hardware_mode;                       /**< Whether to support device binding */
	uint32_t format_num;                      /**< Number of the supported audio formats */
	AudioFormat *formats;               /**< Supported audio formats. For details, see {@link AudioFormat}. */
	uint32_t sample_rate_masks;                /**< Supported audio sampling rates (8 kHz, 16 kHz, 32 kHz, and 48 kHz) */
	AudioChannelMask channel_masks;      /**< Audio channel layout mask of the device. For details, see {@link AudioChannelMask}.*/
	uint32_t channel_count;                   /**< Supported maximum number of audio channels */
};

__END_DECLS

#endif  // AMEBA_AUDIO_HAL_AUDIO_TYPES_H