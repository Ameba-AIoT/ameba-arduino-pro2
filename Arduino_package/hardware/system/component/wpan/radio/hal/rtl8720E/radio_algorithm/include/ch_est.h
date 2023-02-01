/*
 * ch_est.h
 *
 *  Created on: 2021骞�11鏈�26鏃�
 *      Author: ran_wei
 */

#ifndef __RX_CH_EST_H__
#define __RX_CH_EST_H__

#include "ameba_common.h"
#define CE_BUF_SIZE 64

struct rx_ch_est {
	int32_t start;
	int32_t done;
	int32_t sbd_idx;
	ae_int32x2 *din_buf;
	ae_int16x2 est_out[CE_BUF_SIZE];
};

void rx_ch_est_init(struct rx_ch_est *obj);
void rx_ch_est_reset(struct rx_ch_est *obj);
int32_t rx_ch_est_run(struct rx_ch_est *obj);
void rx_ch_est_tests_run(void);

#endif /*  */
