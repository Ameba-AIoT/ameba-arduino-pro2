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

#define ALS_MAX_COL	5	//not recommed for adjusting this value
#define ALS_MAX_ROW	5 //not recommed for adjusting this value

typedef struct als_data_s {
	short Thr_Basic[ALS_MAX_COL * ALS_MAX_ROW];
	short Thr_Advance[ALS_MAX_COL * ALS_MAX_ROW];
} als_data_t;

typedef struct als_config_s {
	short Thr_Color_to_Gray;
	short Thr_Gray_to_Color;
	short Thr_Color_Ratio;
	short Thr_Valid_Block;
	char Mask[ALS_MAX_COL * ALS_MAX_ROW];
} als_config_t;

enum als_dbg_level {
	ALS_DBG_NONE = 0,
	ALS_DBG_SWITCH,
	ALS_DBG_STATIS_BASIC,
	ALS_DBG_STATIS_FULL
};

enum als_AeStatus {
	ALS_AE_UNSTABLE = 0,
	ALS_AE_STABLE
};

int isp_get_AF_statis(af_statis_t *p_af_result);
int isp_get_AE_statis(ae_statis_t *p_ae_result);
int isp_get_AWB_statis(awb_statis_t *p_awb_result);
int isp_get_info(enum isp_reg_info info_type);
int isp_set_func(enum isp_func_switch func_type, int value);
int isp_get_etgain(void);
int isp_get_AE_ifstable(int *sETGainOri, int iDealyMs);
void als_set_dbglevel(enum als_dbg_level enable);
void als_get_version(void);
void als_get_statist(als_data_t *als_data);
int als_ifSwitch(als_config_t *als_config, als_data_t *als_data);
int isp_get_ifAEstable(int *sETGainOri, int iDealyMs);
#endif
