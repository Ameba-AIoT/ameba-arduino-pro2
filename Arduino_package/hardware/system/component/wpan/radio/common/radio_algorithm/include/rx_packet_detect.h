#ifndef RX_PACKET_DETECT_H
#define RX_PACKET_DETECT_H

#ifdef  __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <arm_neon.h>
#include <string.h>
#include "zigbee_types.h"
#include "complex_lib.h"


#define PD_PREAMBLE_SIZE 64
#define PD_MF_BUF_SIZE 16
#define PD_SHIFT_OPT 0
#define PD_PWR_BUF_SIZE 16
#define PD_DC_OUT_SUM_BUF_SIZE 16
#if CCA_IS_DCFI
#define PD_CPX_SIZE 16 //32
#define DC_DCFI_LOW 12 // 3/16 * PD_CPX_SIZE   12
#define DC_DCFI_HIGH 28 // 7/16 * PD_CPX_SIZE
#endif

struct pkt_detect {
#if CCA_IS_DCFI
	int32x4_t mf_buf_re[PD_MF_BUF_SIZE] __attribute__((aligned(64)));
	int32x4_t mf_buf_im[PD_MF_BUF_SIZE] __attribute__((aligned(64)));
	int64_t cpx_out_buf_re[PD_CPX_SIZE] __attribute__((aligned(64)));
	int64_t cpx_out_buf_im[PD_CPX_SIZE] __attribute__((aligned(64)));
	int64_t cpx_th_buf[PD_CPX_SIZE] __attribute__((aligned(64)));
#else
	int32x4_t mf_buf_re[PD_MF_BUF_SIZE] __attribute__((aligned(64)));
	int32x4_t mf_buf_im[PD_MF_BUF_SIZE] __attribute__((aligned(64)));

#endif
	int32_t pwr_buf[PD_PWR_BUF_SIZE] __attribute__((aligned(64)));
	int32x2_t dc_out_sum_buf[PD_DC_OUT_SUM_BUF_SIZE] __attribute__((aligned(64)));

#if CCA_IS_DCFI
	uint64_t din_shift_opt;
	int64_t cpx_out_sum_re;
	int64_t cpx_out_sum_im;
	int32_t cpx_buf_idx;
	int64_t cpx_th_sum;
	int64_t cpx_out;
	int64_t cpx_th;
	float32_t dc_dcfi_high;
	float32_t dc_dcfi_low;
#else
	int32_t din_shift_opt;
#endif
	int32x2_t din;
	int32_t mf_buf_idx;
	int32_t pwr_buf_idx;
	int32_t pwr_buf_sum;
	float32_t pwr_alpha;
	int32_t pwr;
	int32_t pwr_th;
	int32x2_t dc_out_sum;
	int32x2_t dc_out_acc;
	float32_t dc_alpha;
	int32_t dc_th_low;
	int32_t dc_th_high;
	int32_t dc_hit_cnt;
	int32_t pd_hit_th;
	int32_t pd_hit;
};

void pd_fixpt_init(struct pkt_detect *obj);
void pd_fixpt_reset(struct pkt_detect *obj);
int32_t pd_fixpt_run(struct pkt_detect *obj, int32x4_t *din_re, int32x4_t *din_im);

void pd_tests_run(void);

#ifdef  __cplusplus
}
#endif

#endif
