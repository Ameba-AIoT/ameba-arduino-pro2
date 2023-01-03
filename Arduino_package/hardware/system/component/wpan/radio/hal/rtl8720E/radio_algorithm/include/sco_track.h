/*
 * sco_track.h
 *
 *  Created on: 2021骞�11鏈�29鏃�
 *      Author: ran_wei
 */

#ifndef __SCO_TRACK_H__
#define __SCO_TRACK_H__
#include "trx_common.h"

#define SCO_PREDATA_SIZE 65
#define SCO_DATABUF_SIZE 66
#define SCO_DINBUF_SIZE 64
struct sco_track {
	ae_int16x2 *din_buf;
	int32_t valid;
	int16_t mu;
	int32_t base_point;
	int32_t ph_acc;
	int32_t chest_done;
	int32_t sample_cnt;
	int32_t trigger;
	xtfloat delta_phi;
	ae_int16x2 pre_data[SCO_PREDATA_SIZE];
	ae_int16x2 data_buf[SCO_DATABUF_SIZE];
	ae_int16x2 *chip_ideal;
	ae_int16x2 chip_ideal_pre[SCO_DATABUF_SIZE]__attribute__((aligned(8)));
};

void rx_sco_track_init(struct sco_track *obj);
void rx_sco_track_reset(struct sco_track *obj);
void rx_sco_track_run(struct sco_track *obj);
void sco_tracking_test(void);


#endif /*  */
