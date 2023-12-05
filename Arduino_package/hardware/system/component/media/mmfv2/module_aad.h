#ifndef _MODULE_AAD_H
#define _MODULE_AAD_H

#include <stdint.h>
#include "mmf2_module.h"

#include "aacdecoder_lib.h"

#define CMD_AAD_SET_PARAMS          MM_MODULE_CMD(0x00)  // set parameter
#define CMD_AAD_GET_PARAMS          MM_MODULE_CMD(0x01)  // get parameter
#define CMD_AAD_SAMPLERATE          MM_MODULE_CMD(0x02)
#define CMD_AAD_CHANNEL             MM_MODULE_CMD(0x03)
#define CMD_AAD_TRANSPORT_TYPE      MM_MODULE_CMD(0x04)
#define CMD_AAD_RESET               MM_MODULE_CMD(0x05)
#define CMD_AAD_STOP                MM_MODULE_CMD(0x06)


#define CMD_AAD_APPLY				MM_MODULE_CMD(0x20)  // for hardware module

//AAD header type
typedef enum {
	AAD_TYPE_RAW        = 0,    // For AAC without AU-header (not from AAC rtp packet header)
	AAD_TYPE_ADTS       = 2,    // For AAC with ADTS header
	AAD_TYPE_RTP_RAW    = 3,    // For AAC with AU-header (from AAC rtp packet header)
} AAD_TRANSPORT_TYPE;

//AAD audio object type
typedef enum {
	AAD_AOT_LC      = AOT_AAC_LC,       // MP4 Low Complexity
	AAD_AOT_SBR     = AOT_SBR,          // MP4 LC + Spectral Band Replication (HE-AAC v1)
	AAD_AOT_PS      = AOT_PS,           // MP4 LC + SBR + Parametric Stereo (HE-AAC v2)

	AAD_AOT_ER_LD   = AOT_ER_AAC_LD,    // Error Resilient(ER) AAC LowDelay
	AAD_AOT_ER_ELD  = AOT_ER_AAC_ELD,   // Enhanced Low Delay
} AAD_AOT_TYPE;

typedef struct {
	uint8_t *data;          // data bits
	uint32_t size;          // buffer size in bytes
	uint32_t numBit;        // number of bits in buffer
	uint32_t currentBit;    // current bit position in bit stream
	//uint32_t numByte;     // number of bytes read/written (only file)
} AAD_Config;

typedef struct aad_param_s {
	AAD_TRANSPORT_TYPE trans_type;  // Transport Type
	AAD_AOT_TYPE object_type;       // Audio Object Type
	uint32_t sample_rate;	        // 8000
	uint32_t channel;		        // 1
} aad_params_t;

typedef void (*aad_parser_t)(void *, void *, int);

typedef struct aad_ctx_s {
	void *parent;

	HANDLE_AACDECODER aad;
	uint32_t aadflag;
	AAD_Config *aadconfig;
	TRANSPORT_TYPE trans_type;
	AUDIO_OBJECT_TYPE object_type;

	aad_params_t params;

	uint16_t data_cache_len;
	uint16_t data_cache_size;
	uint8_t *data_cache;
	uint8_t *decode_buf;

	aad_parser_t parser;
	uint32_t stop;
} aad_ctx_t;

extern mm_module_t aad_module;

#endif