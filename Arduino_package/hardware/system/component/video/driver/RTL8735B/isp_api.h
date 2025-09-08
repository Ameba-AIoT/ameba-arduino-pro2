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
	short thr_basic[ALS_MAX_COL * ALS_MAX_ROW];
	short thr_advance[ALS_MAX_COL * ALS_MAX_ROW];
} als_data_t;

typedef struct als_config_s {
	unsigned short thr_color_to_gray;
	unsigned short thr_gray_to_color;
	unsigned short thr_color_ratio;
	unsigned short thr_valid_block;
	char mask[ALS_MAX_COL * ALS_MAX_ROW];
} als_config_t;

enum als_mode {
	ALS_MODE_RGB = 0,
	ALS_MODE_IR_ENTRY,
	ALS_MODE_IR_STABLE,
} ;

enum als_dbg_level {
	ALS_LOG_NONE = 0,
	ALS_LOG_SWITCH,
	ALS_LOG_BASIC,
	ALS_LOG_FULL
};

enum ae_status {
	AE_UNSTABLE = 0,
	AE_STABLE
};

int isp_get_AF_statis(af_statis_t *p_af_result);
int isp_get_AE_statis(ae_statis_t *p_ae_result, enum ISP_AE_statis_type type);
int isp_get_AE_meter(uint8_t *weight_array, int *p_weight_num);
int isp_set_AE_meter(uint8_t *weight_array, int p_weight_num);
int isp_get_AWB_statis(awb_statis_t *p_awb_result);
int isp_get_info(enum isp_reg_info info_type);
int isp_set_func(enum isp_func_switch func_type, int value);
int isp_get_etgain(void);
int isp_get_ae_if_stable(int *etgain, int delay_ms);
void als_set_dbg_level(enum als_dbg_level enable);
void als_get_version(void);
void als_get_statist(als_data_t *als_data);
int als_if_switch(als_config_t *als_config, als_data_t *als_data);
#endif
