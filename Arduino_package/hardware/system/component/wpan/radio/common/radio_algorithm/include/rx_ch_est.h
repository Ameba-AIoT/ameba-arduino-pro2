#ifndef RX_CH_EST_H
#define RX_CH_EST_H

#ifdef  __cplusplus
extern "C" {
#endif
#include <arm_neon.h>
#define CE_BUF_SIZE 64

struct rx_ch_est {
	int32_t est_out_re[CE_BUF_SIZE] __attribute__((aligned(64)));
	int32_t est_out_im[CE_BUF_SIZE] __attribute__((aligned(64)));
	int32_t done;
	int32_t sbd_idx;
	int32_t *din_buf_re;
	int32_t *din_buf_im;
	int32_t ce_tap_size;
};

void rx_ch_est_init(struct rx_ch_est *obj);
void rx_ch_est_reset(struct rx_ch_est *obj);
int32_t rx_ch_est_run(struct rx_ch_est *obj);
void rx_ch_est_tests_run(void);

#ifdef  __cplusplus
}
#endif
#endif


