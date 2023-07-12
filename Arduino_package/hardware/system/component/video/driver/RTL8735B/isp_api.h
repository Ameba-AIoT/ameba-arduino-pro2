#ifndef _ISP_API_H_
#define _ISP_API_H_

#include "hal_isp.h"

enum isp_reg_info {
	MIPI_FRAME_COUNT = 0,
	MIPI_PIXEL_COUNT,
	MIPI_LINE_COUNT,
	SYS_FRAME_COUNT,
	SYS_FRAME_IDLE,
	SYS_CONTROL1
};

enum isp_func_switch {
	ISP_FN_LSC = 0,
	ISP_FN_NR,
	ISP_FN_NPC,
	ISP_FN_EE,
	ISP_FN_GAMMA
};

int isp_get_AF_statis(af_statis_t *p_af_result);
int isp_get_AE_statis(ae_statis_t *p_ae_result);
int isp_get_AWB_statis(awb_statis_t *p_awb_result);
int isp_get_info(enum isp_reg_info info_type);
int isp_set_func(enum isp_func_switch func_type, int value);

#endif
