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
#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIOLITE_INTERFACES_AUDIO_AUDIO_TRACK_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIOLITE_INTERFACES_AUDIO_AUDIO_TRACK_H

//#include "cutils/osal_mutex.h"
#include "audio_manager.h"
#include "audio_time_stamp.h"

__BEGIN_DECLS

typedef struct {
	uint32_t sample_rate;
	uint32_t channel_count;
	uint32_t format;
	enum AudioPortPin device;
	uint32_t period_size;
} AudioTrackConfig;

struct AudioTrack;

struct AudioTrack *AudioTrack_Create(void);
int32_t AudioTrack_Destroy(struct AudioTrack *track);
int32_t AudioTrack_Init(struct AudioTrack *audiotrack, const AudioTrackConfig *config);
int32_t AudioTrack_Start(struct AudioTrack *audiotrack);
void AudioTrack_Stop(struct AudioTrack *audiotrack);
void AudioTrack_Pause(struct AudioTrack *audiotrack);
void AudioTrack_Flush(struct AudioTrack *audiotrack);
void AudioTrack_Release(struct AudioTrack *audiotrack);
ssize_t AudioTrack_Write(struct AudioTrack *audiotrack, const void *buffer, size_t size);
ssize_t AudioTrack_GetBufferSize(struct AudioTrack *audiotrack);

int32_t AudioTrack_SetVolume(struct AudioTrack *audiotrack, float volume);
float AudioTrack_GetVolume(struct AudioTrack *audiotrack);
int32_t AudioTrack_SetMute(struct AudioTrack *audiotrack, bool muted);
bool AudioTrack_GetMuted(struct AudioTrack *audiotrack);

int32_t AudioTrack_SetSampleRate(struct AudioTrack *audiotrack, uint32_t sample_rate);
uint32_t AudioTrack_GetSampleRate(struct AudioTrack *audiotrack);
int32_t AudioTrack_SetFormat(struct AudioTrack *audiotrack, uint32_t format);
uint32_t AudioTrack_GetFormat(struct AudioTrack *audiotrack);
int32_t AudioTrack_SetChannelCount(struct AudioTrack *audiotrack, uint32_t channel);
uint32_t AudioTrack_GetChannelCount(struct AudioTrack *audiotrack);
int32_t AudioTrack_GetTimestamp(struct AudioTrack *audiotrack, AudioTimestamp *timestamp);
uint32_t AudioTrack_GetLatency(struct AudioTrack *audiotrack);

__END_DECLS

#endif  // AMEBA_FWK_MEDIA_AUDIO_AUDIOLITE_INTERFACES_AUDIO_AUDIO_TRACK_H
