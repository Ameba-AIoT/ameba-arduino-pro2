#ifndef _MODULE_AAC_H
#define _MODULE_AAC_H

#include <stdint.h>
#include "mmf2_module.h"

#include "aacenc_lib.h"

#define CMD_AAC_SET_PARAMS          MM_MODULE_CMD(0x00)  // set parameter
#define CMD_AAC_GET_PARAMS          MM_MODULE_CMD(0x01)  // get parameter
#define CMD_AAC_SAMPLERATE          MM_MODULE_CMD(0x02)
#define CMD_AAC_CHANNEL             MM_MODULE_CMD(0x03)
#define CMD_AAC_BITLENGTH           MM_MODULE_CMD(0x04)
#define CMD_AAC_MEMORY_SIZE         MM_MODULE_CMD(0x07)
#define CMD_AAC_BLOCK_SIZE          MM_MODULE_CMD(0x08)
#define CMD_AAC_MAX_FRAME_SIZE      MM_MODULE_CMD(0x09)
#define CMD_AAC_INIT_MEM_POOL       MM_MODULE_CMD(0x0a)
#define CMD_AAC_RESET               MM_MODULE_CMD(0x0b)
#define CMD_AAC_STOP                MM_MODULE_CMD(0x0c)

#define CMD_AAC_APPLY               MM_MODULE_CMD(0x20)  // for hardware module

//AAC header type
typedef enum {
	AAC_TYPE_RAW    = TT_MP4_RAW,   // For AAC raw pqacket
	AAC_TYPE_ADTS   = TT_MP4_ADTS,  // For AAC with ADTS header
} AAC_TRANSPORT_TYPE;

//AAC audio object type
typedef enum {
	AAC_AOT_LC      = AOT_AAC_LC,       // MP4 Low Complexity
	AAC_AOT_SBR     = AOT_SBR,          // MP4 LC + Spectral Band Replication (HE-AAC v1)
	AAC_AOT_PS      = AOT_PS,           // MP4 LC + SBR + Parametric Stereo (HE-AAC v2)

	AAC_AOT_ER_LD   = AOT_ER_AAC_LD,    // Error Resilient(ER) AAC LowDelay
	AAC_AOT_ER_ELD  = AOT_ER_AAC_ELD,   // Enhanced Low Delay
} AAC_AOT_TYPE;

typedef struct aac_param_s {
	AAC_TRANSPORT_TYPE trans_type;  // Transport Type
	AAC_AOT_TYPE object_type;       // Audio Object Type
	uint32_t sample_rate;           // 8000
	uint32_t channel;               // 1
	uint32_t bitrate;

	uint32_t mem_total_size;
	uint32_t mem_block_size;
	uint32_t mem_frame_size;
	//...
} aac_params_t;

typedef struct aac_ctx_s {
	void *parent;

	HANDLE_AACENCODER fdkaac_enc;
	AACENC_InfoStruct enc_info;
	TRANSPORT_TYPE trans_type;
	AUDIO_OBJECT_TYPE object_type;

	void *mem_pool;
	aac_params_t params;

	uint8_t *cache;
	uint32_t cache_idx;
	uint32_t stop;
	uint32_t max_cache_size;
} aac_ctx_t;

extern mm_module_t aac_module;

#endif
