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


#ifndef AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_ADAPTER_H
#define AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_ADAPTER_H

#include <stdint.h>
#include <sys/cdefs.h>

#include "cutils/osal_mutex.h"
#include "audio_render.h"
#include "audio_capture.h"

__BEGIN_DECLS


struct AudioAdapter {
	int (*SetParameters)(struct AudioAdapter *adapter, const char *kv_pairs);

	char *(*GetParameters)(const struct AudioAdapter *adapter,
						   const char *keys);

	/**
	 * @brief Set volume to <b>AudioCapture</b> object of <b>AudioAdapter</b> object .
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param volume Indicates the volume need set to <b>AudioCapture</b> object.
	 * @return Returns <b>0</b> if the volume is set successfully;
	 * returns a negative value otherwise.
	 * @see getCaptureVolume
	 */
	int (*SetCaptureVolume)(const struct AudioAdapter *adapter, float volume);

	/**
	 * @brief Get volume of <b>AudioCapture</b> object of <b>AudioAdapter</b> object .
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param volume Indicates the volume need to get from <b>AudioCapture</b> object.
	 * @return Returns <b>0</b> if the volume get successfully;
	 * returns a negative value otherwise.
	 * @see setCaptureVolume
	 */
	int (*GetCaptureVolume)(const struct AudioAdapter *adapter, float *volume);

	/**
	 * @brief Set volume to <b>AudioRender</b> object of <b>AudioAdapter</b> object .
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param volume Indicates the volume need set to <b>AudioRender</b> object.
	 * @return Returns <b>0</b> if the volume is set successfully;
	 * returns a negative value otherwise.
	 * @see getRenderVolume
	 */
	int (*SetRenderVolume)(const struct AudioAdapter *adapter, float volume);

	/**
	 * @brief Get volume of <b>AudioRender</b> object of <b>AudioAdapter</b> object .
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param volume Indicates the volume need to get from <b>AudioRender</b> object.
	 * @return Returns <b>0</b> if the volume get successfully;
	 * returns a negative value otherwise.
	 * @see SetRenderVolume
	 */
	int (*GetRenderVolume)(const struct AudioAdapter *adapter, float *volume);

	/**
	 * @brief Set mute status to <b>AudioRender</b> object of <b>AudioAdapter</b> object .
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param muted Indicates the muted status need to set to hardware.
	 * @return Returns <b>0</b> if the muted is set successfully;
	 * returns a negative value otherwise.
	 * @see getRenderMute
	 */
	int (*SetRenderMute)(const struct AudioAdapter *adapter, bool muted);

	/**
	 * @brief Get current mute status to <b>AudioRender</b> object of <b>AudioAdapter</b> object .
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param muted Indicates the current muted status of the hardware .
	 * @return Returns <b>0</b> if the muted status is got successfully;
	 * returns a negative value otherwise.
	 * @see setRenderMute
	 */
	int (*GetRenderMute)(const struct AudioAdapter *adapter, bool *muted);

	/**
	 * @brief Set mute status to <b>AudioCapture</b> object of <b>AudioAdapter</b> object .
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param muted Indicates the muted status need to set to hardware.
	 * @return Returns <b>0</b> if the muted is set successfully;
	 * returns a negative value otherwise.
	 * @see getCaptureMute
	 */
	int (*SetCaptureMute)(const struct AudioAdapter *adapter, bool muted);

	/**
	 * @brief Get current mute status to <b>AudioCapture</b> object of <b>AudioAdapter</b> object .
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param muted Indicates the current muted status of the hardware .
	 * @return Returns <b>0</b> if the muted status is got successfully;
	 * returns a negative value otherwise.
	 * @see setCaptureMute
	 */
	int (*GetCaptureMute)(const struct AudioAdapter *adapter, bool *muted);

	size_t (*GetInputBufferSize)(const struct AudioAdapter *adapter, const struct AudioSampleAttributes *attrs);

	/**
	 * @brief Creates an <b>AudioRender</b> object.
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param desc Indicates the pointer to the descriptor of the audio adapter to start.
	 * @param attrs Indicates the pointer to the audio sampling attributes to open.
	 * @param render Indicates the double pointer to the <b>AudioRender</b> object.
	 * @return Returns <b>0</b> if the <b>AudioRender</b> object is created successfully;
	 * returns a negative value otherwise.
	 * @see GetPortCapability
	 * @see DestroyRender
	 */
	int (*CreateRender)(struct AudioAdapter *adapter,
						const struct AudioDeviceDescriptor *desc,
						const struct AudioSampleAttributes *attrs,
						struct AudioRender **render);

	/**
	 * @brief Destroys an <b>AudioRender</b> object.
	 *
	 * @attention Do not destroy the object during audio rendering.
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param render Indicates the pointer to the <b>AudioRender</b> object to operate.
	 * @return Returns <b>0</b> if the <b>AudioRender</b> object is destroyed; returns a negative value otherwise.
	 * @see CreateRender
	 */
	void (*DestroyRender)(struct AudioAdapter *adapter,
						  struct AudioRender *render);

	/**
	 * @brief Creates an <b>AudioCapture</b> object.
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param desc Indicates the pointer to the descriptor of the audio adapter to start.
	 * @param attrs Indicates the pointer to the audio sampling attributes to open.
	 * @param capture Indicates the double pointer to the <b>AudioCapture</b> object.
	 * @return Returns <b>0</b> if the <b>AudioCapture</b> object is created successfully;
	 * returns a negative value otherwise.
	 * @see GetPortCapability
	 * @see DestroyCapture
	 */
	int (*CreateCapture)(struct AudioAdapter *adapter,
						 const struct AudioDeviceDescriptor *desc,
						 const struct AudioSampleAttributes *attrs,
						 struct AudioCapture **capture);
	//audio_source_t source);

	/**
	 * @brief Destroys an <b>AudioCapture</b> object.
	 *
	 * @attention Do not destroy the object during audio capturing.
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param capture Indicates the pointer to the <b>AudioCapture</b> object to operate.
	 * @return Returns <b>0</b> if the <b>AudioCapture</b> object is destroyed; returns a negative value otherwise.
	 * @see CreateCapture
	 */
	void (*DestroyCapture)(struct AudioAdapter *adapter,
						   struct AudioCapture *capture);

	/**
	 * @brief Obtains the capability set of the port driver for the audio adapter.
	 *
	 * @param adapter Indicates the pointer to the audio adapter to operate.
	 * @param port Indicates the pointer to the port.
	 * @param capability Indicates the pointer to the capability set to obtain.
	 * @return Returns <b>0</b> if the capability set is successfully obtained; returns a negative value otherwise.
	 */
	int32_t (*GetPortCapability)(struct AudioAdapter *adapter, const struct AudioPort *port, struct AudioPortCapability *capability);
};

typedef struct AudioAdapter AudioAdapter;


struct PrimaryAudioAdapter {
	struct AudioAdapter adapter;

	OSAL_DECLARE_MUTEX(lock);
	struct PrimaryAudioRender *output;
	struct PrimaryAudioCapture *input;
};

struct AudioAdapter *GetAudioAdapterFuncs(void);

__END_DECLS

#endif  // AMEBA_AUDIO_HAL_AUDIO_ADAPTER_H
