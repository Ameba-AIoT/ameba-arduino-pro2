#ifndef RX_ML_DETECT_IMP_H
#define RX_ML_DETECT_IMP_H

//#include <arm_neon.h>
#include "ameba_common.h"
#include "trx_common.h"
#include "file_op.h"
#include <math.h>


#define MF_BUF_NUM 64 /* value = 64 */

#define ML_DIN_SIZE 64
#define ML_CHIP_SIZE 64
#define ML_BUF_SIZE 64
#define ML_BUF_COL 64
#define ML_HC_ROW 64
#define ML_HC_COL 16

struct rx_ml_detect_imp {
	ae_int16x2 *din_buf;
	ae_int16x2 chip_ideal[ML_HC_COL][ML_HC_ROW]__attribute__((aligned(8)));
	ae_int16x2 chip[ML_HC_COL][ML_HC_ROW];
	ae_int16x2 *chip_tap;
	int32_t start;
	int32_t dout_valid;
	int32_t sample_cnt;
	int32_t dout;
	ae_int16x2 dout4cfo[ML_BUF_COL];
	ae_int16x2 dout4sfo[ML_BUF_COL];
	int32_t is_init;
	int32_t chest_done;
	ae_int16x2 H[ML_BUF_SIZE][ML_BUF_COL];
	ae_int16x2 hc[ML_HC_COL][ML_HC_ROW]__attribute__((aligned(16)));
	int32_t chhc[ML_HC_COL];
	int32_t yhc[ML_HC_COL];
	ae_int16x2 yh[ML_HC_ROW];
	ae_int16x2 CY[ML_BUF_COL + 1]__attribute__((aligned(16)));
	int32_t symb_idx_pre;
	ae_int16x2 dout4sco[ML_BUF_COL]__attribute__((aligned(8)));
};

static inline int32_t calc_mag_int32(int32_t re, int32_t im)
{
	int32_t max_v, min_v, magnitude;
	re = XT_ABS(re);
	im = XT_ABS(im);
	max_v = XT_MAX(re, im);
	min_v = XT_MIN(re, im);
	magnitude = (((max_v << 4) - max_v) >> 4) + ((min_v * 15) >> 5);
	if (magnitude < max_v) {
		magnitude = max_v;
	}
	return (magnitude);
}
void rx_ml_detect_imp_init(struct rx_ml_detect_imp *obj, ae_int16 *chip_ideal_re, ae_int16 *chip_ideal_im);
void rx_ml_detect_imp_destroy(struct rx_ml_detect_imp *obj);
void rx_ml_detect_imp_reset(struct rx_ml_detect_imp *obj);
void rx_ml_detect_imp_run(struct rx_ml_detect_imp *obj);
void rx_ml_detect_imp_test_run(void);

#endif

