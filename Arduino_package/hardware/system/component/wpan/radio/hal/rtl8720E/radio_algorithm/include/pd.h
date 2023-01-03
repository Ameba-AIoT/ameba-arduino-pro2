/*
 * rx_pd.h
 *
 *  Created on: 2021-10-25
 *      Author: ran_wei
 */

#ifndef __RX_PD_H__
#define __RX_PD_H__
#include "common.h"
#include "lib.h"
#include "file_op.h"


#define PD_PREAMBLE_SIZE 64
#define PD_MF_BUF_SIZE 64
#define PD_SHIFT_OPT 0
#define PD_PWR_BUF_SIZE 64
#define PD_DC_OUT_SUM_BUF_SIZE 64
#define PD_IDC_BUF_SIZE 32
#define PD_IDC_OUT_ACC_SIZE 64

struct pkt_detect {
	ae_int32x2 din;
	uint32_t din_shift_opt;
	int32_t mf_buf_idx;
	ae_int32x2 mf_buf[PD_MF_BUF_SIZE + 1];
	int32_t pwr_buf_idx;
	int32_t pwr_buf[PD_PWR_BUF_SIZE];
	int32_t pwr_buf_sum;
	float32_t pwr_alpha;
	int32_t pwr;
	int32_t pwr_th;
	ae_int32x2 dc_out_sum_buf[PD_DC_OUT_SUM_BUF_SIZE];
	ae_int32x2 dc_out_sum;
	ae_int32x2 dc_out_acc;
	float32_t dc_alpha;
	int32_t dc_th_low;
	int32_t dc_th_high;
	int32_t pd_judge_start;
	int32_t dc_hit_cnt;
	int32_t pd_hit_th;
	int32_t pd_hit;
	ae_int32x2 idc_buf[PD_IDC_BUF_SIZE + 1];
	ae_int32x2 idc_out_acc[PD_IDC_OUT_ACC_SIZE];
};

void pd_test();
void pd_tests_run(void);

#endif /*  */
