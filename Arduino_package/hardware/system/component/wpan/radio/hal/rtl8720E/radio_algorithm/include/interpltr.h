/*
 * interpltr.h
 *
 *  Created on: 2021骞�11鏈�26鏃�
 *      Author: ran_wei
 */

#ifndef __RX_INTERPLTR_H__
#define __RX_INTERPLTR_H__

#include "ameba_common.h"


#define INTER_DIN_SIZE 66
#define INTER_DOUT_SIZE 64
typedef struct rx_interpolator {
	int32_t mu;
	//ae_int32x2 din;
	//ae_int32x2 dout;
	//ae_int32x2 dout_pre;
	int32_t dagc_gain;
	//ae_int32x2 xseq[3];
	//ae_int32x2 interp_filter_state[2];
	//int32_t din_cnt;
	ae_int16x2 din_buf[INTER_DIN_SIZE]__attribute__((aligned(8)));
	ae_int16x2 dout_buf[INTER_DOUT_SIZE]__attribute__((aligned(8)));
	ae_int16x2 dout;
} INTERPOLATOR;

void rx_interpltr_init(struct rx_interpolator *obj);
void rx_interpltr_reset(struct rx_interpolator *obj);
void rx_interpltr_run(struct rx_interpolator *obj);
void rx_interpolator_tests_run(void);


#endif /*  */
