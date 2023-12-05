#ifndef _MODULE_EIP_H
#define _MODULE_EIP_H

#include <stdint.h>
#include "mmf2_module.h"
#include "hal_isp.h"
#include "md_api.h"
#include "eip_api.h"
#include "eip_auto_wdr.h"

#define CMD_EIP_SET_PARAMS             	MM_MODULE_CMD(0x00)
#define CMD_EIP_SET_CONFIG  			MM_MODULE_CMD(0x01)
#define CMD_EIP_GET_CONFIG  			MM_MODULE_CMD(0x02)
#define CMD_EIP_SET_STATUS				MM_MODULE_CMD(0x03)
#define CMD_EIP_GET_STATIS_INFO			MM_MODULE_CMD(0x04)
#define CMD_EIP_SHOW_CONFIG				MM_MODULE_CMD(0x05)
#define CMD_EIP_AE_STABLE_EN  			MM_MODULE_CMD(0x06)

/*md control*/
#define CMD_EIP_SET_MD_EN      			MM_MODULE_CMD(0x10)
#define CMD_EIP_SET_MD_CONFIG      		MM_MODULE_CMD(0x11)
#define CMD_EIP_GET_MD_CONFIG      		MM_MODULE_CMD(0x12)
#define CMD_EIP_SET_MD_MASK      		MM_MODULE_CMD(0x13)
#define CMD_EIP_GET_MD_MASK      		MM_MODULE_CMD(0x14)
#define CMD_EIP_SET_MD_SENSITIVITY      MM_MODULE_CMD(0x15)
#define CMD_EIP_GET_MD_SENSITIVITY      MM_MODULE_CMD(0x16)
#define CMD_EIP_GET_MD_RESULT       	MM_MODULE_CMD(0x17)
#define CMD_EIP_SET_MD_DISPPOST			MM_MODULE_CMD(0x18)
#define CMD_EIP_SET_MD_OUTPUT			MM_MODULE_CMD(0x19)

/*auto wdr control*/
#define CMD_EIP_SET_AUTO_WDR_EN      	MM_MODULE_CMD(0x20)
#define CMD_EIP_SET_AUTO_WDR_CONFIG		MM_MODULE_CMD(0x21)
#define CMD_EIP_GET_AUTO_WDR_CONFIG		MM_MODULE_CMD(0x22)

#define EIP_STATUS_START 	0x00
#define EIP_STATUS_STOP 	0x01
#define EIP_SET_STOP 		0x02

typedef void (*md_disp_postprcess)(void *);

typedef struct eip_config_s {
	int en_ae_stable;
	int en_md;
	int en_auto_wdr;
} eip_config_t;

typedef struct eip_ctx_s {
	void *parent;
	eip_param_t params;
	eip_config_t eip_config;
	eip_statis_infor_t eip_statis_info;
	eip_Y_data_t Y_data;

	eip_ae_stable_t ae_stable;

	md_config_t md_config;
	md_context_t *motion_detect_ctx;
	md_result_t md_result;
	md_disp_postprcess md_disp_postproc;
	unsigned long md_time0;	
	bool md_out_en;

	eip_auto_wdr_t eip_auto_wdr;

	int eip_status;
} eip_ctx_t;

extern mm_module_t eip_module;

#endif
