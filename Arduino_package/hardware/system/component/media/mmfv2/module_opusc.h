#ifndef _MODULE_OPUSC_H
#define _MODULE_OPUSC_H

#include <stdint.h>
#include "mmf2_module.h"

#include "opus.h"

#define CMD_OPUSC_SET_PARAMS     		MM_MODULE_CMD(0x00)  // set parameter
#define CMD_OPUSC_GET_PARAMS     		MM_MODULE_CMD(0x01)  // get parameter
#define CMD_OPUSC_SAMPLERATE 			MM_MODULE_CMD(0x02)
#define CMD_OPUSC_CHANNEL				MM_MODULE_CMD(0x03)
#define CMD_OPUSC_BITLENGTH				MM_MODULE_CMD(0x04)
#define CMD_OPUSC_MEMORY_SIZE			MM_MODULE_CMD(0x07)
#define CMD_OPUSC_BLOCK_SIZE			MM_MODULE_CMD(0x08)
#define CMD_OPUSC_MAX_FRAME_SIZE		MM_MODULE_CMD(0x09)
#define CMD_OPUSC_INIT_MEM_POOL			MM_MODULE_CMD(0x0a)
#define CMD_OPUSC_RESET		        	MM_MODULE_CMD(0x0b)
#define CMD_OPUSC_STOP		        	MM_MODULE_CMD(0x0c)

#define CMD_OPUSC_APPLY					MM_MODULE_CMD(0x20)  // for hardware module

typedef struct opusc_param_s {
	uint32_t sample_rate;	// 8000
	uint32_t channel;		// 1
	uint32_t bit_length;	// 16
	uint32_t complexity;
	uint32_t use_framesize;

	//VBR CBR setting
	uint32_t bitrate; //default 25000
	uint32_t enable_vbr;
	uint32_t vbr_constraint;
	uint32_t packetLossPercentage;

	uint32_t opus_application;

	int samples_input;
	int max_bytes_output;
	//...

} opusc_params_t;

typedef struct opusc_ctx_s {
	void *parent;

	OpusEncoder    *opus_enc;

	void *mem_pool;
	opusc_params_t params;

	uint8_t *cache;
	uint32_t cache_idx;
	uint32_t stop;
} opusc_ctx_t;

extern mm_module_t opusc_module;

#endif
