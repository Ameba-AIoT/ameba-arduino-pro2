#ifndef COARSE_CFO_H
#define COARSE_CFO_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "zigbee_lib.h"
#include "fft_64point.h"
#include <arm_neon.h>

#define COARSE_CFO_DIN_NUM 256

typedef struct _COARSE_CFO {
	int32_t dout4sbd_re[64] __attribute__((aligned(64)));
	int32_t dout4sbd_im[64] __attribute__((aligned(64)));
	float32_t delta_phi;
	int32_t *din_buf_re;
	int32_t *din_buf_im;
	int32_t sbd_idx;
	int32_t fine_frac_en;  /* 默认为0，fractional freq. estimation只做一次，原来做两次 */
	int32_t int_freq_est_opt;  /* 0: fd;1:td*/
} COARSE_CFO;

void coarse_cfo_init(COARSE_CFO *ccfo);
void coarse_cfo_reset(COARSE_CFO *obj);
void coarse_cfo_run(COARSE_CFO *obj);


#ifdef  __cplusplus
}
#endif
#endif



