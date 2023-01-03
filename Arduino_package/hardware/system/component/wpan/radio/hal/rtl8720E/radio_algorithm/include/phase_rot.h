/*
 * phase_rot.h
 *
 *  Created on: 2021骞�11鏈�29鏃�
 *      Author: ran_wei
 */

#ifndef __RX_PHASE_ROT_H__
#define __RX_PHASE_ROT_H__

#include "ameba_common.h"

#define PHASE_ROTA_SIZE 64

typedef struct phase_rot {
	ae_int32x2 din;
	xtfloat phi_in;
	xtfloatx2 phi_acc;
	int32_t start;
	int32_t cnt;
	/*int32_t *din_buf_re;
	int32_t *din_buf_im;*/
	ae_int16x2 *din_buf;
	ae_int16x2 dout_buf[PHASE_ROTA_SIZE]__attribute__((aligned(8)));
} PHASE_ROT;

void rx_phase_rot_init(struct phase_rot *obj);
void rx_phase_rot_reset(struct phase_rot *obj);
void rx_phase_rot_run(struct phase_rot *obj);
void rx_phase_rot_tests_run(void);


#endif /*  */
