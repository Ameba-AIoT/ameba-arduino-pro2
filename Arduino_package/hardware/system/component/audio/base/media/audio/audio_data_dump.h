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

#include <stdio.h>
#include "osal_c/osal_mem.h"

#define ID_RIFF 0x46464952
#define ID_WAVE 0x45564157
#define ID_FMT  0x20746d66
#define ID_DATA 0x61746164
#define FORMAT_PCM 1

struct wav_header {
	uint32_t riff_id;
	uint32_t riff_sz;
	uint32_t riff_fmt;
	uint32_t fmt_id;
	uint32_t fmt_sz;
	uint16_t audio_format;
	uint16_t num_channels;
	uint32_t sample_rate;
	uint32_t byte_rate;
	uint16_t block_align;
	uint16_t bits_per_sample;
	uint32_t data_id;
	uint32_t data_sz;
};

struct AudioDataInfo {
	struct wav_header header;
	FILE *file;
	int frames;
	int dump_count; //-1 - will stop dump at Stop()
};

//define DUMP_AUDIO_DATA
#ifdef DUMP_AUDIO_DATA

static struct AudioDataInfo *CreateAudioDataInfo(int channels, int rate, char *file_path, int count)
{
	RTLOGD("[Dump]CreateAudioDataInfo channels: %d, rate: %d, path: %s, d_count: %d", channels, rate, file_path, count);
	struct AudioDataInfo *audio_data_info = (struct AudioDataInfo *)OsalMemAlloc(sizeof(struct AudioDataInfo));
	memset(audio_data_info, 0, sizeof(struct AudioDataInfo));

	if (!audio_data_info) {
		RTLOGE("[Dump]calloc AudioDataInfo failed!");
		return NULL;
	}

	audio_data_info->file = fopen(file_path, "wb");
	if (!audio_data_info->file) {
		RTLOGE("[Dump]Unable to create file '%s'\n", file_path);
		OsalMemFree(audio_data_info);
		return NULL;
	}

	audio_data_info->dump_count = count;

	/* leave enough room for header */
	fseek(audio_data_info->file, sizeof(struct wav_header), SEEK_SET);

	audio_data_info->header.riff_id = ID_RIFF;
	audio_data_info->header.riff_sz = 0;
	audio_data_info->header.riff_fmt = ID_WAVE;
	audio_data_info->header.fmt_id = ID_FMT;
	audio_data_info->header.fmt_sz = 16;
	audio_data_info->header.audio_format = FORMAT_PCM;
	audio_data_info->header.num_channels = channels;
	audio_data_info->header.sample_rate = rate;
	audio_data_info->header.bits_per_sample = 16;
	audio_data_info->header.byte_rate = (audio_data_info->header.bits_per_sample / 8) * audio_data_info->header.num_channels * audio_data_info->header.sample_rate;
	audio_data_info->header.block_align = audio_data_info->header.num_channels * (audio_data_info->header.bits_per_sample / 8);
	audio_data_info->header.data_id = ID_DATA;

	//RTLOGD("[Dump]AudioDataInfo ok!");
	return audio_data_info;
}

static void DeleteAudioDataInfo(struct AudioDataInfo *audio_data_info)
{
	RTLOGD("[Dump]DeleteAudioDataInfo");
	if (audio_data_info) {
		if (audio_data_info->file) {
			fclose(audio_data_info->file);
		}
		OsalMemFree(audio_data_info);
	}
}

static int DumpAudioData(struct AudioDataInfo *audio_data_info, const void *buffer, size_t bytes)
{
	//RTLOGD("[Dump]DumpAudioData bytes: %zu", bytes);
	if (audio_data_info == NULL) {
		RTLOGE("file error, can not capture audio data");
		return 0;
	}

	if (!audio_data_info || !audio_data_info->file) {
		RTLOGE("file error, can not capture audio data");
		return 0;
	}

	if (fwrite(buffer, 1, bytes, audio_data_info->file) != bytes) {
		RTLOGE("[Dump]Error writing audio data");
		return 0;
	}
	fflush(audio_data_info->file);
	audio_data_info->frames += bytes / (audio_data_info->header.num_channels * (audio_data_info->header.bits_per_sample / 8));
	return 1;
}

static void DumpAudioDataWavHeader(struct AudioDataInfo *audio_data_info)
{
	RTLOGD("[Dump]DumpAudioDataWavHeader");
	if (!audio_data_info || !audio_data_info->file) {
		RTLOGE("[Dump]file error, can not write wav header");
		return;
	}
	RTLOGV("total frames:%d, block align:%d", audio_data_info->frames, audio_data_info->header.block_align);
	audio_data_info->header.data_sz = audio_data_info->frames * audio_data_info->header.block_align;
	audio_data_info->header.riff_sz = audio_data_info->header.data_sz + sizeof(audio_data_info->header) - 8;
	fseek(audio_data_info->file, 0, SEEK_SET);
	fwrite(&audio_data_info->header, sizeof(struct wav_header), 1, audio_data_info->file);
}

#endif
