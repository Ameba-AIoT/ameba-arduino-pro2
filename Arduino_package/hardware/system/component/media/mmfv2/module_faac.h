#ifndef _MODULE_FAAC_H
#define _MODULE_FAAC_H

#include <stdint.h>
#include "mmf2_module.h"

#include "faac.h"

#define CMD_FAAC_SET_PARAMS          MM_MODULE_CMD(0x00)  // set parameter
#define CMD_FAAC_GET_PARAMS          MM_MODULE_CMD(0x01)  // get parameter
#define CMD_FAAC_SAMPLERATE          MM_MODULE_CMD(0x02)
#define CMD_FAAC_CHANNEL             MM_MODULE_CMD(0x03)
#define CMD_FAAC_BITLENGTH           MM_MODULE_CMD(0x04)
#define CMD_FAAC_MEMORY_SIZE         MM_MODULE_CMD(0x07)
#define CMD_FAAC_BLOCK_SIZE          MM_MODULE_CMD(0x08)
#define CMD_FAAC_MAX_FRAME_SIZE      MM_MODULE_CMD(0x09)
#define CMD_FAAC_INIT_MEM_POOL       MM_MODULE_CMD(0x0a)
#define CMD_FAAC_RESET               MM_MODULE_CMD(0x0b)
#define CMD_FAAC_STOP                MM_MODULE_CMD(0x0c)

#define CMD_FAAC_APPLY               MM_MODULE_CMD(0x20)  // for hardware module

typedef struct faac_param_s {
	uint32_t sample_rate;	// 8000
	uint32_t channel;		// 1
	uint32_t bit_length;	// 16
	uint32_t output_format;	// 16
	uint32_t mpeg_version;	// 16

	uint32_t mem_total_size;
	uint32_t mem_block_size;
	uint32_t mem_frame_size;
	//...
} faac_params_t;

typedef struct faac_ctx_s {
	void *parent;

	faacEncHandle faac_enc;

	void *mem_pool;
	faac_params_t params;

	uint8_t *cache;
	uint32_t cache_idx;
	uint32_t stop;

	int samples_input;
	int max_bytes_output;
} faac_ctx_t;

extern mm_module_t faac_module;

#endif
