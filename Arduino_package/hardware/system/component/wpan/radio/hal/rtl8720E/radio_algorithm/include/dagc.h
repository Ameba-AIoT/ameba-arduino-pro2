/*
 * rx_dagc.h
 *
 *  Created on: 2021骞�11鏈�18鏃�
 *      Author: ran_wei
 */

#ifndef __RX_DAGC_H__
#define __RX_DAGC_H__

#include "ameba_common.h"
#define RX_DAGC_BUF 256
struct rx_dagc {
	int32_t start;
	int32_t done;
	int32_t sample_cnt;
	int32_t pwr_acc;
	int32_t dagc_gain;
	int32_t target_level;
	ae_int16x2 din;
	ae_int16x2 dout;
	ae_int16x2 din_buf[RX_DAGC_BUF]__attribute__((aligned(16)));
};

void rx_dagc_reset(struct rx_dagc *obj);
void rx_dagc_init(struct rx_dagc *obj);
void rx_dagc_run(struct rx_dagc *obj);
void rx_dagc_test(void);

#endif /*  */
