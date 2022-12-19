#ifndef RX_ML_DETECT_OPT_H
#define RX_ML_DETECT_OPT_H


#include "ameba_common.h"
#if 0
#define FS_4M 4
#define SFD_LEN 8
#define PREAMBLE_LEN 32
#define FRM_LEN_SIZE 7
#define SYMBOL_GRP 4
#define CHIP_MAP_LEN 32
#define CHIP_MAP_GOUP 16
#define CHIP_EXPAN 8
#define CHIP_BUF_SIZE 64
#define SQRT2_2 (sqrt((float)2) / 2)
#define BYTE2BITS 8
#define UINT2BITS 32
#define MF_BUF_NUM 64 /* value = 64 */


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
#define ML_DOUT4SCO_NUM 64
#define ML_CY_SIZE 64

struct rx_ml_detect {
	int32_t din_re;
	int32_t din_im;
	ae_int32x2 chip[16][64];
	int32_t *chip_re;
	int32_t *chip_im;
	int32_t chip_ideal_re[16][64];
	int32_t chip_ideal_im[16][64];
	int32_t chip_ideal_im_hc[16][64];
	int32_t chest_done;
	int32_t sample_cnt;
	int32_t start;
	int32_t dout_valid;
	int32_t isInit;
	int32_t symb_idx_pre;
	int32_t dout4cfo_re;
	int32_t dout4cfo_im;
	int32_t hc_re[16][64];
	int32_t hc_im[16][64];
	int32_t chhc[CHHC_SIZE];
	int32_t yhc[YHC_SIZE];
	int32_t din_buf_re[ML_BUF_SIZE];
	int32_t din_buf_im[ML_BUF_SIZE];
	int32_t *ch_tap_re;
	int32_t *ch_tap_im;
	int32_t H_re[64][64];
	int32_t H_im[64][64];
	int32_t C0_re[64][64];
	int32_t C0_im[64][64];
	int32_t CY_re[ML_CY_SIZE];
	int32_t CY_im[ML_CY_SIZE];
	int32_t dout;
	int32_t dout4sco_re[ML_DOUT4SCO_NUM];
	int32_t dout4sco_im[ML_DOUT4SCO_NUM];
	int32_t simplify_en;
};

void rx_ml_detect_init(struct rx_ml_detect *obj, int32_t *chip_ideal_re, int32_t *chip_ideal_im);
void rx_ml_detect_destroy(struct rx_ml_detect *obj);
void rx_ml_detect_reset(struct rx_ml_detect *obj);
void rx_ml_detect_run(struct rx_ml_detect *obj);
void rx_ml_detect_test_run(void);

void rx_ml_detect_test_run(void);
#endif
#endif

