/*
 * pd_imp.h
 *
 *  Created on: 2021骞�10鏈�29鏃�
 *      Author: ran_wei
 */

#ifndef __PD_IMP_H__
#define __PD_IMP_H__

#include "ameba_common.h"

#define PD_IMP_MF_SIZE 16
struct pkt_detect_imp {
	ae_int16x8 din;
	uint32_t din_shift_opt;
	int32_t mf_buf_idx;
	ae_int16x8 mf_buf[PD_IMP_MF_SIZE]; // 4 points
	int32_t pwr_buf_idx;
	int32_t pwr_buf[PD_IMP_MF_SIZE];
	int32_t pwr_buf_sum;
	float32_t pwr_alpha;
	int32_t pwr;
	int32_t pwr_th;
	ae_int32x2 dc_out_sum_buf[PD_IMP_MF_SIZE];
	//ae_int32x2 dc_out_sum;
	ae_int32x2 dc_out_acc;
	float32_t dc_alpha;
	int32_t dc_th_low;
	int32_t dc_th_high;
	int32_t pd_judge_start;
	int32_t dc_hit_cnt;
	int32_t pd_hit_th;
	int32_t pd_hit;
};

void rx_pd_imp_init(struct pkt_detect_imp *obj);
void rx_pd_imp_reset(struct pkt_detect_imp *obj);
int32_t rx_pd_imp_run(struct pkt_detect_imp *obj, ae_int16x2 *din);
void pd_imp_run_ts(void);

#ifdef _PXP_
void pd_imp_runpxp_ts(void);
#endif
#endif /*  */
