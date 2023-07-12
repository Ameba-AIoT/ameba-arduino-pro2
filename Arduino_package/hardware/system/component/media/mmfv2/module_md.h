#ifndef _MODULE_MD_H
#define _MODULE_MD_H

#include <stdint.h>
#include "mmf2_module.h"
#include "hal_isp.h"
#include "md_api.h"
#include "eip_api.h"

#define CMD_MD_SET_PARAMS             	MM_MODULE_CMD(0x00)
#define CMD_MD_SET_MD_CONFIG      		MM_MODULE_CMD(0x01)
#define CMD_MD_GET_MD_CONFIG      		MM_MODULE_CMD(0x02)
#define CMD_MD_SET_MD_MASK      		MM_MODULE_CMD(0x03)
#define CMD_MD_GET_MD_MASK      		MM_MODULE_CMD(0x04)
#define CMD_MD_GET_MD_RESULT       		MM_MODULE_CMD(0x05)
#define CMD_MD_SET_OUTPUT				MM_MODULE_CMD(0x06)
#define CMD_MD_SET_DISPPOST				MM_MODULE_CMD(0x07)
#define CMD_MD_SET_TRIG_BLK				MM_MODULE_CMD(0x08)
#define CMD_MD_EN_AE_STABLE				MM_MODULE_CMD(0x09)
#define CMD_MD_SET_ADAPT_THR_MODE 		MM_MODULE_CMD(0x0A)
#define CMD_MD_SET_TIME_FILTER_INTERVAL	MM_MODULE_CMD(0x0B)
#define CMD_MD_SET_DETECT_INTERVAL		MM_MODULE_CMD(0x0C)
#define CMD_MD_SET_BGMODE				MM_MODULE_CMD(0x0D)
#define CMD_MD_SET_STATUS				MM_MODULE_CMD(0x0E)

#define CMD_MD_SET_MD_SENSITIVITY      	MM_MODULE_CMD(0x10)
#define CMD_MD_GET_MD_SENSITIVITY      	MM_MODULE_CMD(0x11)

#define MD_STATUS_START 0x00
#define MD_STATUS_STOP 	0x01
#define MD_SET_STOP 	0x02

typedef void (*md_disp_postprcess)(void *);

typedef struct md_ctx_s {
	void *parent;
	md_param_t params;
	md_config_t md_config;
	md_context_t *motion_detect_ctx;
	md_disp_postprcess disp_postproc;
	unsigned long md_time0;
	bool md_out_en;
	int md_status;
} md_ctx_t;

extern eip_statis_infor_t statis_info;

extern mm_module_t md_module;

#endif
