#ifndef RX_INTERPOLATOR_H
#define RX_INTERPOLATOR_H

#include <stdint.h>
#include <arm_neon.h>
#include <string.h>
#include "zigbee_types.h"

#ifdef  __cplusplus
extern "C" {
#endif
#define INTER_DIN_SIZE 66
#define INTER_DOUT_SIZE 64
#define INTER_DOUT_ODD_EVEN_SIZE 4
typedef struct rx_interpolator {
	int32_t din_buf_re[INTER_DIN_SIZE] __attribute__((aligned(64)));
	int32_t din_buf_im[INTER_DIN_SIZE] __attribute__((aligned(64)));
	int32_t dout_buf_re[INTER_DIN_SIZE] __attribute__((aligned(64)));
	int32_t dout_buf_im[INTER_DIN_SIZE] __attribute__((aligned(64)));

	int32x4_t dout_buf_re_odd[INTER_DOUT_ODD_EVEN_SIZE] __attribute__((aligned(64)));
	int32x4_t dout_buf_im_odd[INTER_DOUT_ODD_EVEN_SIZE] __attribute__((aligned(64)));
	int32x4_t dout_buf_re_even[INTER_DOUT_ODD_EVEN_SIZE] __attribute__((aligned(64)));
	int32x4_t dout_buf_im_even[INTER_DOUT_ODD_EVEN_SIZE] __attribute__((aligned(64)));
	int32_t mu;
	int32_t dagc_gain;
} INTERPOLATOR;

void interpolator_init(struct rx_interpolator *obj);
void interpolator_reset(struct rx_interpolator *obj);
void interpolator_run(struct rx_interpolator *obj);
void rx_interpolator_tests_run(void);


#ifdef  __cplusplus
}
#endif
#endif