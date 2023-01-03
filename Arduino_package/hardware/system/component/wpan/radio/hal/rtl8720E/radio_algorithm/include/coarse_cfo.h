/*
 * rx_coarse_cfo.h
 *
 *  Created on: 2021骞�11鏈�19鏃�
 *      Author: ran_wei
 */

#ifndef __RX_COARSE_CFO_H__
#define __RX_COARSE_CFO_H__


#include "ameba_common.h"

#define COARSE_CFO_DIN_NUM 256
#define CORDIC_ITER_NUM 9

struct fft64 {
	uint32_t din_wl;    /* fft杈撳叆鏁版嵁鐨勬�讳綅瀹� */
	uint32_t din_fl;    /* fft杈撳叆鏁版嵁鐨勫皬鏁颁綅瀹� */
	uint32_t dout_wl;    /* fft杈撳嚭鏁版嵁鐨勬�讳綅瀹� */
	uint32_t dout_fl;    /* fft杈撳嚭鏁版嵁鐨勫皬鏁颁綅瀹� */
	int32_t num_point;    /* fft鐐规暟 */
	int32_t w;
} ;

typedef struct coarse_cfo {
	int32_t start;
	int32_t done;
	int32_t sample_cnt;
	xtfloat delta_phi;
	ae_int16x2 din;
	ae_int16x2 *din_buf;
	int32_t cpe;
	int32_t sbd_idx;
	ae_int32x2 mf_buf4ch_est[64];
	int32_t mf_buf4ch_est_re[64];
	int32_t mf_buf4ch_est_im[64];
	int32_t fine_frac_en;  /* 榛樿涓�0锛宖ractional freq. estimation鍙仛涓�娆★紝鍘熸潵鍋氫袱娆� */
	int32_t int_freq_est_opt;  /* 0: fd;1:td*/
	ae_int32x2 dout4sbd[64];
} COARSE_CFO;

void rx_coarse_cfo_init(COARSE_CFO *ccfo);
void rx_coarse_cfo_reset(COARSE_CFO *obj);
int32_t rx_coarse_cfo_run(COARSE_CFO *obj);
void coarse_cfo_tests_run(void);
void fft_64point_test(void);
void cos_sin_tests();

#endif /*  */
