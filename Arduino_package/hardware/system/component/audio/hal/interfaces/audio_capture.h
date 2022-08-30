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


#ifndef AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_CAPTURE_H
#define AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_CAPTURE_H

#include <stdint.h>
#include <sys/cdefs.h>

#include "audio_stream.h"

__BEGIN_DECLS


struct AudioCapture {
	/**
	 * Common methods of the audio stream in.  This *must* be the first member of AudioCapture
	 * as users of this structure will cast a AudioHalStream to AudioCapture pointer in contexts
	 * where it's known the AudioHalStream references an AudioCapture.
	 */
	struct AudioHalStream common;

	/**
	 * @brief Get current capture frames and timestamp of the current <b>AudioCapture</b> object .
	 *
	 * @param stream Indicates the pointer to the audio capture to operate.
	 * @param frames Indicates the pointer to the current capture frames of the current <b>AudioCapture</b> object.
	 * @param timestamp Indicates the pointer to the current timestamp of the current <b>AudioCapture</b> object.
	 * @return Returns <b>0</b> if capture frames and timestamp get successfully;
	 * returns a negative value otherwise.
	 */
	int (*GetCapturePosition)(const struct AudioCapture *stream, uint32_t *frames, struct timespec *timestamp);

	/**
	 * @brief Get system latency of the current <b>AudioCapture</b> object .
	 *
	 * @param stream Indicates the pointer to the audio capture to operate.
	 * @return Returns the current capture latency;
	 */
	uint32_t (*GetLatency)(const struct AudioCapture *stream);

	/**
	 * @brief Read data from sound card for the current <b>AudioCapture</b> object .
	 *
	 * @param stream Indicates the pointer to the audio capture to operate.
	 * @param buffer Indicates the pointer to the current capture buffer need to read data from driver of the current <b>AudioCapture</b> object.
	 * @param bytes  Indicates the size of the buffer.
	 * @return Returns  the data size read from driver;
	 * returns <b>0</b> value otherwise.
	 */
	ssize_t (*Read)(struct AudioCapture *stream, void *buffer, size_t bytes);
};

typedef struct AudioCapture AudioCapture;

size_t GetInputBufferSize(uint32_t sample_rate, AudioFormat format, uint32_t channel_count);

__END_DECLS

#endif  // AMEBA_AUDIO_HAL_AUDIO_CAPTURE_H