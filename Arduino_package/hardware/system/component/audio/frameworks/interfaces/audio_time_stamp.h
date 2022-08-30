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


#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIOLITE_INTERFACES_AUDIO_AUDIO_TIMESTAMP_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIOLITE_INTERFACES_AUDIO_AUDIO_TIMESTAMP_H

#include <time.h>

typedef struct AudioTimestamp {
	uint32_t        position; // a frame position in AudioTrack::getPosition() units
	struct timespec time_spec;// corresponding CLOCK_MONOTONIC when frame is expected to present
} AudioTimestamp;

#endif // AMEBA_AUDIO_TIMESTAMP_H
