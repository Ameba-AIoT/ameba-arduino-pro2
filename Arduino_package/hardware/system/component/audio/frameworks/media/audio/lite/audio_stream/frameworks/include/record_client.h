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

/**
 * @addtogroup Audio
 * @{
 *
 * @brief Declares APIs for audio framework.
 *
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file audio_capturer.h
 *
 * @brief Provides the <b>RecordClient</b> class to implement operations related to audio capture.
 *
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_RECORD_CLIENT_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_RECORD_CLIENT_H

#include "osal_cxx/errors.h"
#include "osal_cxx/mutex.h"
#include "hardware/audio/audio_hw_manager.h"

#include "audio/audio_time.h"
#include "audio/audio_record.h"

namespace ameba::audio
{

/**
 * @brief Provides functions for applications to implement audio capturing.
 *
 * @since 1.0
 * @version 1.0
 */
class RecordClient
{
public:
	RecordClient();
	~RecordClient();

	/**
	 * @brief Init audio record.
	 *
	 * @param config a {@link RTAudioRecordConfig} instance used to configure record information.
	 * @return {@link res_t#OK}, {@link res_t#NO_ERROR}, {@link res_t#UNKNOWN_ERROR}, {@link res_t#NO_MEMORY}
	 * @since 1.0
	 * @version 1.0
	 */
	res_t Init(const RTAudioRecordConfig *config);

	/**
	 * @brief Start audio record.
	 *
	 * @return {@link res_t#OK}, {@link res_t#NO_ERROR}, {@link res_t#UNKNOWN_ERROR}, {@link res_t#INVALID_OPERATION}
	 * @since 1.0
	 * @version 1.0
	 */
	res_t Start();

	/**
	 * @brief Stop audio record.
	 *
	 * @since 1.0
	 * @version 1.0
	 */
	void     Stop();

	/**
	 * @brief Release audio record.
	 *
	 * @since 1.0
	 * @version 1.0
	 */
	void     Release();

	/**
	 * @brief Read audio data.
	 *
	 * @param buffer is the dst buffer of application.
	 * @param size is the dst buffer data bytes.
	 * @param blocking choice whether to block when read stuck, suggest:true.
	 * @return size of data read
	 * @since 1.0
	 * @version 1.0
	 */
	ssize_t  Read(void *buffer, size_t size, bool blocking = true);

	/**
	 * @brief Get buffer bytes for record.
	 *
	 * @return buffer bytes suggested to read for one period
	 * @since 1.0
	 * @version 1.0
	 */
	ssize_t  GetBufferSize();

	/**
	 * @brief Set samplerate of record.
	 *
	 * @param sample_rate the samplerate of record.
	 * @return {@link res_t#NO_ERROR}, {@link res_t#BAD_VALUE}
	 * @since 1.0
	 * @version 1.0
	 */
	res_t    SetSampleRate(uint32_t sample_rate);

	/**
	 * @brief Get samplerate of audio record.
	 *
	 * @return samplerate
	 * @since 1.0
	 * @version 1.0
	 */
	uint32_t    GetSampleRate() const
	{
		return sample_rate_;
	}

	/**
	 * @brief Set channel count of record.
	 *
	 * @param channel the channel count of record.
	 * @return {@link res_t#NO_ERROR}, {@link res_t#BAD_VALUE}
	 * @since 1.0
	 * @version 1.0
	 */
	res_t    SetChannelCount(uint32_t channel_count);

	/**
	 * @brief Get channel count of audio record.
	 *
	 * @return channel count of record.
	 * @since 1.0
	 * @version 1.0
	 */
	uint32_t    GetChannelCount() const
	{
		return channel_count_;
	}

	/**
	 * @brief Get format of audio record.
	 *
	 * @return format
	 * @since 1.0
	 * @version 1.0
	 */
	uint32_t    GetFormat() const
	{
		return format_;
	}

	/**
	 * @brief Set format of record.
	 *
	 * @param format {@link uint32_t} the format of record.
	 * @return {@link res_t#NO_ERROR}, {@link res_t#BAD_VALUE}
	 * @since 1.0
	 * @version 1.0
	 */
	res_t    SetFormat(uint32_t format);

	/**
	 * @brief Set volume of record.
	 * Not implemented. Reserved for future.
	 *
	 * @param volume volume of record, value[0.0~1.0], default 1.0.
	 * @return {@link res_t#NO_ERROR}, {@link res_t#BAD_VALUE}
	 * @since 1.0
	 * @version 1.0
	 */
	res_t SetVolume(float volume);

	/**
	 * @brief Get volume of record.
	 * Not implemented. Reserved for future.
	 *
	 * @return volume value of record. [0.0~1.0], default 1.0.
	 * @since 1.0
	 * @version 1.0
	 */
	float GetVolume();

	/**
	 * @brief Set mute of record.
	 * Not implemented. Reserved for future.
	 *
	 * @param muted mute status of record.<var>true</var> to mute,
	 *                                    <var>false</var> to unmute.
	 * @return {@link res_t#NO_ERROR}, {@link res_t#BAD_VALUE}
	 * @since 1.0
	 * @version 1.0
	 */
	res_t SetMute(bool muted);

	/**
	 * @brief GetTimeStamp of record.
	 * Not implemented. Reserved for future.
	 *
	 * @param timestamp Indicates a {@link RTAudioTimestamp} instance reference provided by the caller.
	 * @return {@link res_t#NO_ERROR}, {@link res_t#BAD_VALUE}
	 * @since 1.0
	 * @version 1.0
	 */
	res_t GetTimestamp(RTAudioTimestamp *timestamp);

	/**
	 * @brief get latency of record.
	 * Not implemented. Reserved for future.
	 *
	 * @return latency of audio record in buf bytes.
	 * @since 1.0
	 * @version 1.0
	 */
	uint32_t GetLatency();

	/**
	 * @brief set parameter of record.
	 *
	 *
	 * @return {@link res_t#NO_ERROR}, {@link res_t#BAD_VALUE}
	 * @since 1.0
	 * @version 1.0
	 */
	res_t SetParameters(const char *strs);


private:

	res_t                status_;
	bool                 is_active_;
	uint32_t             sample_rate_;
	uint32_t             channel_count_;
	uint32_t             format_;
	uint32_t             device_;

	struct AudioHwManager *audio_manager_;
	struct AudioHwAdapter *audio_adapter_;
	struct AudioHwCapture *audio_capture_;
	struct AudioHwAdapterDescriptor *desc_;
	AudioHwPort            capture_port_;

	Mutex                lock_;

	//DISALLOW_COPY_AND_MOVE(RecordClient);

};

}; // namespace ameba::audio

#endif // AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_RECORD_CLIENT_H
