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

#ifndef AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_STREAM_H
#define AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_STREAM_H

#include <stdint.h>
#include <sys/cdefs.h>

#include "audio_types.h"

__BEGIN_DECLS


struct AudioHalStream {

	/**
	 * @brief Return the sampling rate in Hz for a <b>AudioHalStream</b> object .
	 *
	 * @param stream Indicates the pointer to the audio hal stream to operate.
	 * @return Returns the sampling rate for the stream
	 * returns <b>0</b> value otherwise.
	 * @see setSampleRate
	 */
	uint32_t (*GetSampleRate)(const struct AudioHalStream *stream);

	/**
	 * @brief Set the sampling rate in Hz to a <b>AudioHalStream</b> object .
	 *
	 * @param stream Indicates the pointer to the audio hal stream to operate.
	 * @param rate Indicates the sampling rate set to the audio hal stream.
	 * @return Returns returns <b>0</b> value.
	 * @see getSampleRate
	 */
	int (*SetSampleRate)(struct AudioHalStream *stream, uint32_t rate);

	/**
	 * @brief Get size of input/output buffer in bytes for this stream for a <b>AudioHalStream</b> object ,It should be a multiple of the frame size
	 *
	 * @param stream Indicates the pointer to the audio hal stream to operate.
	 * @return Returns the buffer size  for the stream to render/capture
	 */
	size_t (*GetBufferSize)(const struct AudioHalStream *stream);

	/**
	 * @brief Return the channel mask for a <b>AudioHalStream</b> object .
	 *
	 * @param stream Indicates the pointer to the audio hal stream to operate.
	 * @return Returns the channel mask for the stream
	 * @see setChannels
	 */
	uint32_t (*GetChannels)(const struct AudioHalStream *stream);

	/**
	 * @brief Set the channel mask to a <b>AudioHalStream</b> object .
	 *
	 * @param stream Indicates the pointer to the audio hal stream to operate.
	 * @param channel Indicates the channel mask set to the audio hal stream.
	 * @return Returns returns <b>0</b> value.
	 * @see getChannels
	 */
	int (*SetChannels)(const struct AudioHalStream *stream, uint32_t channel);

	/**
	 * @brief Return the audio format for a <b>AudioHalStream</b> object .
	 *
	 * @param stream Indicates the pointer to the audio hal stream to operate.
	 * @return Returns the audio format for the stream
	 * @see setFormat
	 */
	AudioFormat(*GetFormat)(const struct AudioHalStream *stream);

	/**
	 * @brief Set the audio format to a <b>AudioHalStream</b> object .
	 *
	 * @param stream Indicates the pointer to the audio hal stream to operate.
	 * @param format Indicates the audio format set to the audio hal stream.
	 * @return Returns returns <b>0</b> value.
	 * @see getFormat
	 */
	int (*SetFormat)(struct AudioHalStream *stream, AudioFormat format);

	int (*Standby)(struct AudioHalStream *stream);

	/** dump the state of the audio input/output device */
	int (*Dump)(const struct AudioHalStream *stream, int fd);

	/** Return the set of device(s) which this stream is connected to */
	//audio_devices_t (*get_device)(const struct AudioHalStream *stream);

	// int (*set_device)(struct AudioHalStream *stream, audio_devices_t device);

	int (*SetParameters)(struct AudioHalStream *stream, const char *kvPairs);

	/*
	 * Returns a pointer to a heap allocated string. The caller is responsible
	 * for freeing the memory for it using free().
	 */
	char *(*GetParameters)(const struct AudioHalStream *stream, const char *keys);
};

typedef struct AudioHalStream AudioHalStream;


__END_DECLS

#endif  // AMEBA_AUDIO_HAL_AUDIO_STREAM_H