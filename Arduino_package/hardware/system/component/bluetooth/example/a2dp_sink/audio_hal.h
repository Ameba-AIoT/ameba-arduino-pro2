/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
* @file     audio_hal.h
* @brief    Source file for audio hal wrapper.
* @details  api function.
* @author   sherman
* @date     2021-06-10
* @version  v1.0
* *************************************************************************************
*/
#ifndef _AUDIO_HAL_H_
#define _AUDIO_HAL_H_

#include "a2dp_app_debug.h"
#include "ameba_soc.h"
#include "osdep_service.h"

/** @brief typedef struct audio_hal_ops */
struct audio_hal_ops {
	bool (*hal_audio_init)(unsigned int channels, unsigned int rate, unsigned int bits, unsigned int period_size, unsigned int period_count);
	void (*hal_audio_deinit)(void);
	void (*hal_audio_start)(void);
	void (*hal_audio_stop)(void);
	void (*hal_audio_pause)(void);
	void (*hal_audio_resume)(void);
	void (*hal_audio_play)(void *buffer, uint16_t size);
	int32_t (*hal_audio_set_volume)(float volume);
	float (*hal_audio_get_volume)(void);
	void (*hal_audio_set_mute)(bool muted);
	bool (*hal_audio_get_muted)(void);
	void (*hal_audio_set_sample_rate)(uint32_t sample_rate);
	uint32_t (*hal_audio_get_sample_rate)(void);
	void (*hal_audio_set_channel_count)(uint32_t channel_count);
	uint32_t (*hal_audio_get_channel_count)(void);
	long (*hal_audio_get_buffer_size)(void);
};

#endif // _AUDIO_HAL_H_