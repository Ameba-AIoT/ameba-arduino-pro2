#ifndef _MODULE_OPUSD_H
#define _MODULE_OPUSD_H

#include <stdint.h>
#include "mmf2_module.h"

#include "opus.h"

#define CMD_OPUSD_SET_PARAMS     		MM_MODULE_CMD(0x00)  // set parameter
#define CMD_OPUSD_GET_PARAMS     		MM_MODULE_CMD(0x01)  // get parameter
#define CMD_OPUSD_SAMPLERATE 			MM_MODULE_CMD(0x02)
#define CMD_OPUSD_CHANNEL				MM_MODULE_CMD(0x03)
#define CMD_OPUSD_STREAM_TYPE			MM_MODULE_CMD(0x04)
#define CMD_OPUSD_RESET					MM_MODULE_CMD(0x05)


#define CMD_OPUSD_APPLY					MM_MODULE_CMD(0x20)  // for hardware module


typedef struct opusd_param_s {
	uint32_t sample_rate;	// 8000
	uint32_t channel;		// 1
	uint32_t bit_length;	// 16
	uint32_t frame_size_in_msec; //20
	uint32_t opus_application;
	uint8_t  with_opus_enc;

	int samples_input;
	int max_bytes_output;
} opusd_params_t;

typedef void (*opusd_parser_t)(void *, void *, int);

typedef struct opusd_ctx_s {
	void *parent;

	OpusDecoder    *opus_dec;

	opusd_params_t params;

	uint16_t data_cache_len;
	uint16_t data_cache_size;
	uint8_t *data_cache;

	uint32_t *frame_len_buf;
	int32_t max_frame_in_chache;
	int32_t last_frame_idx;

	uint8_t *decode_buf;

	opusd_parser_t parser;
} opusd_ctx_t;

extern mm_module_t opusd_module;

#endif