/*
 * Copyright (c) 2021 Realtek, LLC.
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

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIOLITE_INTERFACES_AUDIO_AUDIO_RECORD_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIOLITE_INTERFACES_AUDIO_AUDIO_RECORD_H

#include "audio/audio_type.h"
#include "osal_c/osal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct RTAudioRecord;

/**
 * @brief Defines information about audio capture parameters, including the sampling
 * rate (Hz), number of audio channels, audio codec format, bit rate, and portPin.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
	/** sample rate of record
	 * [amebalite] 8000, 11025, 22050, 24000, 32000, 44100, 48000, 88200, 96000
	 * [amebaSmart] 8000, 11025, 22050, 24000, 32000, 44100, 48000, 88200, 96000
	 * [amebad]to be supported */
	uint32_t sample_rate;
	/** channel count of record
	 * [amebalite] mode(no_afe_pure_data) for amic: 1,2,3;
	 *             mode(do_afe_only_out) for amic: 1,2;
	 *             mode(no_afe_all_data) for amic: 3,4,5;
	 *             mode(do_afe_all_data) for amic: 4;
	 * [amebaSmart]supports 1,2,3, more to be supported
	 * [amebad]to be supported */
	uint32_t channel_count;
	/** format of record
	 * [amebalite]supports RTAUDIO_FORMAT_PCM_16_BIT, RTAUDIO_FORMAT_PCM_32_BIT,RTAUDIO_FORMAT_PCM_8_24_BIT
	 * [amebaSmart]supports RTAUDIO_FORMAT_PCM_16_BIT, more to be supported
	 * [amebad]to be supported */
	uint32_t format;
	/** device of record, supports RTPIN_IN_MIC*/
	uint32_t device;
} RTAudioRecordConfig;

/**
* @brief Create RTAudioRecord.
*/
struct RTAudioRecord *RTAudioRecord_Create(void);

/**
 * @param record is the pointer of struct RTAudioRecord.
 * @brief Release RTAudioRecord.
 */
void RTAudioRecord_Destroy(struct RTAudioRecord *record);

/**
 * @brief Init audio record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @param config a {@link RTAudioRecordConfig} instance used to configure record information.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_NO_INIT | the init is not done.
 * OSAL_ERR_INVALID_OPERATION | the config value is not proper.
 * OSAL_ERR_NO_MEMORY | the memory alloc for record is fail.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAudioRecord_Init(struct RTAudioRecord *record, const RTAudioRecordConfig *config);

/**
 * @brief Start audio record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | should not start now.
 * OSAL_ERR_DEAD_OBJECT | the ipc is dead.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAudioRecord_Start(struct RTAudioRecord *record);

/**
 * @brief Stop audio record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @since 1.0
 * @version 1.0
 */
void RTAudioRecord_Stop(struct RTAudioRecord *record);

/**
 * @brief Release audio record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @since 1.0
 * @version 1.0
 */
void RTAudioRecord_Destroy(struct RTAudioRecord *record);

/**
 * @brief Read audio data.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @param buffer is the dst buffer of application.
 * @param size is the dst buffer data bytes.
 * @param blocking choice whether to block when read stuck, suggest:true.
 * @return size of data read
 * @since 1.0
 * @version 1.0
 */
ssize_t RTAudioRecord_Read(struct RTAudioRecord *record, void *buffer, size_t size, bool blocking);

/**
 * @brief Get buffer bytes for record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @return buffer bytes suggested to read for one period
 * @since 1.0
 * @version 1.0
 */
ssize_t RTAudioRecord_GetBufferSize(struct RTAudioRecord *record);

/**
 * @brief Set samplerate of record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @param sample_rate the sample_rate of record.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | param not supported.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAudioRecord_SetSampleRate(struct RTAudioRecord *record, uint32_t sample_rate);

/**
 * @brief Get samplerate of audio record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @return samplerate
 * @since 1.0
 * @version 1.0
 */
uint32_t RTAudioRecord_GetSampleRate(struct RTAudioRecord *record);

/**
 * @brief Set channel count of record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @param channel_count the channel count of record.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | param not supported.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAudioRecord_SetChannelCount(struct RTAudioRecord *record, uint32_t channel_count);

/**
 * @brief Get channel count of audio record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @return channel count of record.
 * @since 1.0
 * @version 1.0
 */
uint32_t RTAudioRecord_GetChannelCount(struct RTAudioRecord *record);

/**
 * @brief Get format of audio record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @return format
 * @since 1.0
 * @version 1.0
 */
uint32_t RTAudioRecord_GetFormat(struct RTAudioRecord *record);

/**
 * @brief Set format of record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @param format supports RTAUDIO_FORMAT_PCM_16_BIT,
 * RTAUDIO_FORMAT_PCM_8_24_BIT, RTAUDIO_FORMAT_PCM_32_BIT.
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | param not supported.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAudioRecord_SetFormat(struct RTAudioRecord *record, uint32_t format);

/**
 * @brief Set format of record.
 *
 * @param record is the pointer of struct RTAudioRecord.
 * @param strs supports AMIC settings like:"adc0_sel_amic_num=0;adc1_sel_amic_num=1;
 * adc2_sel_amic_num=2;adc3_sel_amic_num=3;adc4_sel_amic_num=4;
 * adc5_sel_amic_num=5;adc6_sel_amic_num=6;adc7_sel_amic_num=7"
 * @return Returns a value listed below: \n
 * rt_status_t | Description
 * ----------------------| -----------------------
 * OSAL_OK | the operation is successful.
 * OSAL_ERR_INVALID_OPERATION | param not supported.
 * @since 1.0
 * @version 1.0
 */
rt_status_t RTAudioRecord_SetParameters(struct RTAudioRecord *audio_record, const char *strs);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_AUDIO_AUDIO_RECORD