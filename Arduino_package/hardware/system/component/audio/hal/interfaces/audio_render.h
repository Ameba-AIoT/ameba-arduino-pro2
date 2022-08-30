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


#ifndef AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_RENDER_H
#define AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_RENDER_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "audio_stream.h"

__BEGIN_DECLS


/**
 * AudioRender is the abstraction interface for the audio output hardware.
 *
 * It provides information about various properties of the audio output
 * hardware driver.
 */
struct AudioRender {
	struct AudioHalStream common;

	/**
	 * @brief Get system latency of the current <b>AudioRender</b> object .
	 *
	 * @param stream Indicates the pointer to the audio render to operate.
	 * @return Returns the current render latency;
	 */
	uint32_t (*GetLatency)(const struct AudioRender *stream);

	/**
	 * @brief Get current render frames and timestamp of the current <b>AudioRender</b> object .
	 *
	 * @param stream Indicates the pointer to the audio render to operate.
	 * @param frames Indicates the pointer to the current render frames of the current <b>AudioRender</b> object.
	 * @param timestamp Indicates the pointer to the current timestamp of the current <b>AudioRender</b> object.
	 * @return Returns <b>0</b> if render frames and timestamp get successfully;
	 * returns a negative value otherwise.
	 */
	int (*GetPresentationPosition)(const struct AudioRender *stream, uint32_t *frames, struct timespec *timestamp);

	/**
	 * @brief Write data to sound card for the current <b>AudioRender</b> object .
	 *
	 * @param stream Indicates the pointer to the audio render to operate.
	 * @param buffer Indicates the pointer to the current render buffer need to write to driver of the current <b>AudioRender</b> object.
	 * @param bytes  Indicates the size of the buffer.
	 * @return Returns size written to driver;
	 * returns <b>0</b> value otherwise.
	 */
	ssize_t (*Write)(struct AudioRender *stream, const void *buffer, size_t bytes);

	int (*SetVolume)(struct AudioRender *stream, float left, float right);

	int (*Pause)(struct AudioRender *stream);

	int (*Resume)(struct AudioRender *stream);

	int (*Flush)(struct AudioRender *stream);
};

typedef struct AudioRender AudioRender;


__END_DECLS

#endif  // AMEBA_AUDIO_HAL_AUDIO_RENDER_H