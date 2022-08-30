#ifndef _MODULE_RTKNN_H
#define _MODULE_RTKNN_H

#include <stdint.h>

#include "nn_api.h"
#include "ssd_post_process.h"

#define VERIFY_API 0

#if VERIFY_API==0
#include "nn_model_info.h"
#endif


#define CMD_RTKNN_SET_MODEL_ID     	MM_MODULE_CMD(0x00)  // set parameter
#define CMD_RTKNN_SET_MODEL     	MM_MODULE_CMD(0x01)  // set parameter
#define CMD_RTKNN_SET_PARAMS     	MM_MODULE_CMD(0x02)  // set parameter
#define CMD_RTKNN_SET_WIDTH     	MM_MODULE_CMD(0x03)
#define CMD_RTKNN_SET_HEIGHT     	MM_MODULE_CMD(0x04)
#define CMD_RTKNN_SET_PREPROC     	MM_MODULE_CMD(0x05)
#define CMD_RTKNN_SET_POSTPROC     	MM_MODULE_CMD(0x06)
#define CMD_RTKNN_SET_FPS			MM_MODULE_CMD(0x07)
#define CMD_RTKNN_SET_SETOBJECT     MM_MODULE_CMD(0x08)

#define CMD_RTKNN_GET_PARAMS     	MM_MODULE_CMD(0x10)  // get parameter
#define CMD_RTKNN_GET_HWVER     	MM_MODULE_CMD(0x11)

#define CMD_RTKNN_APPLY				MM_MODULE_CMD(0x20)  // for hardware module

typedef struct rtknn_param_s {
	struct MODEL_INFO_S info;
	struct cvRect_S roi;

	int in_width, in_height, in_channel;
	int in_fps;

	int model_id;
	uint8_t *model;
	int m_width, m_height;
	int m_permute;

} rtknn_params_t;

typedef int (*rtknn_preproc_t)(void *, void *, void *, void *, uint32_t);
typedef int (*rtknn_postproc_t)(void *, void *);
typedef int (*rtknn_setoject_t)(void *);

typedef struct rtknn_ctx_s {
	void *parent;

	rtknn_params_t params;

	rtknn_preproc_t pre_process;
	rtknn_postproc_t post_process;
	rtknn_setoject_t set_object;

	int model_id;
	uint8_t *model;

	uint32_t last_tick;	// for control processing FPS
} rtknn_ctx_t;

typedef struct rtknn_res_s {
	float result[MAX_DETECT_OBJ_NUM * 6];
	int obj_num;
} rtknn_res_t;

extern mm_module_t rtknn_module;

#endif
