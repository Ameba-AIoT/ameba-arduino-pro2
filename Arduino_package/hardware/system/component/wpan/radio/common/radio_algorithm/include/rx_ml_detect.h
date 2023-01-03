#ifndef RX_ML_DETECT_H
#define RX_ML_DETECT_H

#ifdef  __cplusplus
extern "C" {
#endif
#include <arm_neon.h>

#define ML_BUF_SIZE 64
#define CHHC_SIZE 16
#define YHC_SIZE 16
#define ML_H_SIZE 64
#define ML_C0_SIZE 64
#define ML_CHIP_COL 16
#define ML_CHIP_ROW 64
#define ML_HC_COL 16
#define ML_CH_TAP_SHIFT_NUM 5
#define ML_C0_SHIFT_NUM 5
#define ML_VV_CHIP_NUM 5
#define ML_DOUT4SCO_NUM 16
#define ML_CY_SIZE 16
#define CFO_TRACKING 1
#define CFO_TRACKING_OPT 1  //if CFO_TRACKING_OPT is 0, ML_OPT must be 0
#define ML_OPT 1

struct rx_ml_detect {
	int32x2_t chip[16][64] __attribute__((aligned(64)));
	int32_t chip_ideal_re[16][64] __attribute__((aligned(64)));
	int32_t chip_ideal_im[16][64] __attribute__((aligned(64)));
	int32_t chip_ideal_im_hc[16][64] __attribute__((aligned(64)));
	int32_t hc_re[16][64] __attribute__((aligned(64)));
	int32_t hc_im[16][64] __attribute__((aligned(64)));
	int32_t chhc[CHHC_SIZE] __attribute__((aligned(64)));
	int32_t yhc[YHC_SIZE] __attribute__((aligned(64)));
	int32_t H_re[64][64] __attribute__((aligned(64)));
	int32_t H_im[64][64] __attribute__((aligned(64)));
	int32_t C0_re[64][64] __attribute__((aligned(64)));
	int32_t C0_im[64][64] __attribute__((aligned(64)));
	int32_t CY_re[ML_CY_SIZE] __attribute__((aligned(64)));
	int32_t CY_im[ML_CY_SIZE] __attribute__((aligned(64)));
	int32x2_t dout4sco[ML_DOUT4SCO_NUM] __attribute__((aligned(64)));
	int32_t dout4sco_im_odd[ML_DOUT4SCO_NUM] __attribute__((aligned(64)));
	int32_t dout4sco_re_even[ML_DOUT4SCO_NUM] __attribute__((aligned(64)));

	int32_t din_re;
	int32_t din_im;
	int32_t *chip_re;
	int32_t *chip_im;
	int32_t chest_done;
	//int32_t sample_cnt;
	int32_t start;
	int32_t dout_valid;
	int32_t isInit;
	int32_t symb_idx_pre;
	int32_t dout4cfo_re;
	int32_t dout4cfo_im;
	int32_t *din_buf_re_odd;
	int32_t *din_buf_im_odd;
	int32_t *din_buf_re_even;
	int32_t *din_buf_im_even;
	int32_t *ch_tap_re;
	int32_t *ch_tap_im;
	int32_t dout;
	int32_t simplify_en;
	int32_t ce_tap_size;
};

void rx_ml_detect_init(struct rx_ml_detect *obj, int32_t *chip_ideal_re, int32_t *chip_ideal_im);
void rx_ml_detect_destroy(struct rx_ml_detect *obj);
void rx_ml_detect_reset(struct rx_ml_detect *obj);
void rx_ml_detect_run(struct rx_ml_detect *obj);
void rx_ml_detect_test_run(void);


#ifdef  __cplusplus
}
#endif
#endif

