/*
 * rx_sbd.h
 *
 *  Created on: 2021骞�11鏈�25鏃�
 *      Author: ran_wei
 */

#ifndef __RX_SBD_H__
#define __RX_SBD_H__
#include "ameba_common.h"
#include "trx_common.h"

#define SBD_MF_SIZE 64
#define SBD_CSD_SIZE 64

struct rx_sbd {
	int32_t start;
	int32_t done;
	int32_t is_boundary;
	int32_t cnt;
	ae_int32x2 *din_buf;
	ae_int32x2 mf_buf[SBD_MF_SIZE];
	int32_t is_sbd_ready;
	int32_t sbd_idx_from_tdcfo;
	//ae_int32x2 preamble[SBD_MF_SIZE];
};
void rx_sbd_init(struct rx_sbd *obj);
void rx_sbd_reset(struct rx_sbd *obj);
void rx_sbd_run(struct rx_sbd *obj);
void rx_sbd_test(void);

#endif /*  */
