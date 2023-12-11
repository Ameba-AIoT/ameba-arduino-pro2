#ifndef EIP_AUTO_WDR_H
#define EIP_AUTO_WDR_H

#include "eip_api.h"

typedef struct eip_auto_wdr_config_s {
	int wdr_weight_thr1;
	int wdr_weight_thr2;
	int wdr_weight_thr3;
	int wdr_max_level;
	int wdr_min_level;
	int wdr_duration;
} eip_auto_wdr_config_t;

typedef struct eip_auto_wdr_s {
	int wdr_weight;
	int wdr_status;
	int wdr_cur_level;
	int wdr_target_level;
	int sat_level;
	eip_statis_infor_t *statis_info;
	eip_auto_wdr_config_t wdr_config;
	SemaphoreHandle_t task_stop_sema;
	int task_stop_flag;
} eip_auto_wdr_t;

void eip_auto_wdr_get_version(void);
void eip_auto_wdr_show_info(eip_auto_wdr_t *auto_wdr);
void eip_auto_wdr_task_start(eip_statis_infor_t *statis_info, eip_auto_wdr_t *auto_wdr);
void eip_auto_wdr_task_stop(eip_auto_wdr_t *auto_wdr);

#endif	// EIP_AUTO_WDR_H
