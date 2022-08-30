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

#include "audio_manager.h"

#include "audio_time_stamp.h"

typedef struct {
	uint32_t sample_rate;
	uint32_t channel_count;
	uint32_t format;
	enum AudioPortPin device;
	uint32_t period_size;
} AudioRecordConfig;

struct AudioRecord {
	int32_t record_status;
	bool      is_active;
	uint32_t sample_rate;
	uint32_t channel_count;
	uint32_t record_format;
	uint32_t period_size;
	enum AudioPortPin record_port_pin;

	struct AudioManager *audio_manager;
	struct AudioAdapter *audio_adapter;
	struct AudioCapture *audio_capture;
	struct AudioAdapterDescriptor *cap_desc;
	struct AudioPort record_port;

};

struct AudioRecord *AudioRecord_Create(void);
int32_t AudioRecord_Destroy(struct AudioRecord *track);
int32_t AudioRecord_Init(struct AudioRecord *audio_record, const AudioRecordConfig *config);
int32_t AudioRecord_Start(struct AudioRecord *audio_record);
void AudioRecord_Stop(struct AudioRecord *audio_record);
void AudioRecord_Release(struct AudioRecord *audio_record);
ssize_t AudioRecord_Read(struct AudioRecord *audio_record, void *buffer, size_t size);
ssize_t AudioRecord_GetBufferSize(struct AudioRecord *audio_record);

int32_t AudioRecord_SetSampleRate(struct AudioRecord *audio_record, uint32_t sample_rate);
uint32_t AudioRecord_GetSampleRate(struct AudioRecord *audio_record);
int32_t AudioRecord_SetChannelCount(struct AudioRecord *audio_record, uint32_t channel_count);
uint32_t AudioRecord_GetChannelCount(struct AudioRecord *audio_record);
uint32_t AudioRecord_GetFormat(struct AudioRecord *audio_record);
int32_t AudioRecord_SetFormat(struct AudioRecord *audio_record, uint32_t format);

int32_t AudioRecord_SetVolume(struct AudioRecord *audio_record, float volume);
float AudioRecord_GetVolume(struct AudioRecord *audio_record);
int32_t AudioRecord_SetMute(struct AudioRecord *audio_record, bool muted);
bool AudioRecord_GetMuted(struct AudioRecord *audio_record);
int32_t AudioRecord_GetTimestamp(struct AudioRecord *audio_record, AudioTimestamp *timestamp);
uint32_t AudioRecord_GetLatency(struct AudioRecord *audio_record);
uint32_t AudioRecord_SetParameters(struct AudioRecord *audio_record, const char *str_pairs);
#endif // AMEBA_AUDIO_AUDIO_RECORD