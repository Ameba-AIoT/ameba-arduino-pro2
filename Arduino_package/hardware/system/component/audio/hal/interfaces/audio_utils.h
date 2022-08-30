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

#ifndef AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_UTILS_H
#define AMEBA_HARDWARE_INTERFACES_HARDWARE_AUDIO_AUDIO_UTILS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "cutils/bitops.h"

#include "audio_types.h"

__BEGIN_DECLS

static inline size_t GetAudioBytesPerSample(AudioFormat format)
{
	size_t size = 0;

	switch (format) {
	case AUDIO_FORMAT_PCM_32_BIT:
		size = sizeof(int32_t);
		break;
	case AUDIO_FORMAT_PCM_24_BIT:
		size = sizeof(uint8_t) * 3;
		break;
	case AUDIO_FORMAT_PCM_16_BIT:
		size = sizeof(int16_t);
		break;
	case AUDIO_FORMAT_PCM_8_BIT:
		size = sizeof(uint8_t);
		break;
	default:
		break;
	}
	return size;
}

static inline bool AudioIsLinearPCM(AudioFormat format)
{
	return ((format & AUDIO_FORMAT_MAIN_MASK) == AUDIO_FORMAT_PCM);
}

static inline AudioFormat AudioGetMainFormat(AudioFormat format)
{
	return (AudioFormat)(format & AUDIO_FORMAT_MAIN_MASK);
}

static inline bool AudioCheckValidFormat(AudioFormat format)
{
	switch (format & AUDIO_FORMAT_MAIN_MASK) {
	case AUDIO_FORMAT_PCM:
		switch (format) {
		case AUDIO_FORMAT_PCM_16_BIT:
		case AUDIO_FORMAT_PCM_8_BIT:
		case AUDIO_FORMAT_PCM_32_BIT:
		case AUDIO_FORMAT_PCM_24_BIT:
			return true;
		default:
			return false;
		}

	default:
		return false;
	}
}

__END_DECLS

#endif  // AMEBA_MEDIA_AUDIO_CORE_H