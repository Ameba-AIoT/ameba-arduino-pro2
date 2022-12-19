#ifndef RX_SBD_H
#define RX_SBD_H

#ifdef  __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <arm_neon.h>

#define SBD_DIN_SIZE 256
#define SBD_MF_SIZE 64
#define SBD_CSD_SIZE 64

struct rx_sbd {
	int32_t mf_buf_re[SBD_MF_SIZE] __attribute__((aligned(64)));
	int32_t mf_buf_im[SBD_MF_SIZE] __attribute__((aligned(64)));
	int32_t start;
	int32_t done;
	int32_t is_boundary;
	int32_t cnt;
	int32_t *din_buf_re;
	int32_t *din_buf_im;
	int32_t is_sbd_ready;
	int32_t sbd_idx_from_tdcfo;
};

void rx_sbd_init(struct rx_sbd *obj);
void rx_sbd_reset(struct rx_sbd *obj);
void rx_sbd_run(struct rx_sbd *obj);
void rx_sbd_test(void);


#ifdef  __cplusplus
}
#endif
#endif


