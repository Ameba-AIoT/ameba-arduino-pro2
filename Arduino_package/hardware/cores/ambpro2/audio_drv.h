#ifndef audio_drv_h
#define audio_drv_h

#include <stdint.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <diag.h>
#include "mmf2_module.h"
#include "module_audio.h"
#include "audio_api.h"

// Audio
mm_context_t* audioInit(void);

mm_context_t* audioDeinit(mm_context_t *p);

void audioClose(mm_context_t *p);

void audioOpen(mm_context_t *p, int sample_rate, int word_length, int mic_gain, int dmic_l_gain, int dmic_r_gain, int use_mic_type, int channel, int enable_aec);

// AAC (Advanced Audio Codec)
mm_context_t* AACInit(void);

mm_context_t* AACDeinit(void *p);

void AACOpen(mm_context_t *p, uint32_t sample_rate, uint32_t channel, uint32_t bit_length, uint32_t output_format, uint32_t mpeg_version, uint32_t mem_total_size, uint32_t mem_block_size, uint32_t mem_frame_size);

void AACStop(mm_context_t *p);

int AACSetParams(void *p, uint32_t sample_rate, uint32_t channel, uint32_t bit_length, uint32_t output_format, uint32_t mpeg_version, uint32_t mem_total_size, uint32_t mem_block_size, uint32_t mem_frame_size);

int AACSetQueueLength(void *p);

int AACInitQueueItems(void *p);

int AACInitMemPool(void *p);

int AACApply(void *p);

// Functions externed from module_aac
extern int aac_control(void *p, int cmd, int arg);
extern void *aac_destroy(void *p);
extern void *aac_create(void *parent);

#endif