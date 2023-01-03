#ifndef PHASE_ROTATION_H
#define PHASE_ROTATION_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <arm_neon.h>

#define PHASE_ROTA_SIZE 16

extern int32_t g_first_data_sym;
typedef struct _PHASE_ROT {
	int32_t dout_buf_re_odd[PHASE_ROTA_SIZE] __attribute__((aligned(64)));
	int32_t dout_buf_im_odd[PHASE_ROTA_SIZE] __attribute__((aligned(64)));
	int32_t dout_buf_re_even[PHASE_ROTA_SIZE] __attribute__((aligned(64)));
	int32_t dout_buf_im_even[PHASE_ROTA_SIZE] __attribute__((aligned(64)));

	int32x2_t din;
	float32_t phi_in;
	float32x4_t phi_acc;
	float32x4_t phi_acc_odd;
	float32x4_t phi_acc_even;
	int32_t start;
	int32_t cnt;
	int32_t *din_buf_re_even;
	int32_t *din_buf_im_even;
	int32_t *din_buf_re_odd;
	int32_t *din_buf_im_odd;
	int32_t is_first_symbol;
} PHASE_ROT;


void rx_phase_acc(PHASE_ROT *obj);
void rx_phase_rot_run(PHASE_ROT *obj);
void rx_phase_rot_init(PHASE_ROT *obj);
void rx_phase_rot_reset(PHASE_ROT *obj);
void rx_phase_rot_tests_run(void);


#ifdef  __cplusplus
}
#endif
#endif


