#ifndef SCO_TRACKING_H
#define SCO_TRACKING_H

#ifdef  __cplusplus
extern "C" {
#endif
#include <arm_neon.h>
#include <stdint.h>

#if 0//ndef RX_USE_BUF

struct sco_track {
	int32x2_t din_buf[66];
	int32x2_t din;
	int32_t mu;
	int32_t trigger;
	int32_t base_point;
	float32_t ph_acc;
	int32_t chest_done;
	int32x2_t *chip_ideal;
	int32_t valid;
	float32_t delta_phi;
	int32_t idx_sco;
};

void sco_tracking_init(struct sco_track *obj);
void sco_tracking_reset(struct sco_track *obj);
void sco_tracking_run_sync_mode0(struct sco_track *obj);
void sco_tracking_run_sync_mode1(struct sco_track *obj);
void sco_tracking_run(struct sco_track *obj);
void sco_tracking_test(void);
#else
#define SCO_PREDATA_SIZE 17
#define SCO_DATABUF_SIZE 18
#define SCO_DINBUF_SIZE 16
struct sco_track {
	int32_t pre_data_re_odd[SCO_PREDATA_SIZE] __attribute__((aligned(64)));
	int32_t pre_data_im_odd[SCO_PREDATA_SIZE] __attribute__((aligned(64)));
	int32_t pre_data_re_even[SCO_PREDATA_SIZE] __attribute__((aligned(64)));
	int32_t pre_data_im_even[SCO_PREDATA_SIZE] __attribute__((aligned(64)));

	int32_t data_buf_re_odd[SCO_DATABUF_SIZE] __attribute__((aligned(64)));
	int32_t data_buf_im_odd[SCO_DATABUF_SIZE] __attribute__((aligned(64)));
	int32_t data_buf_re_even[SCO_DATABUF_SIZE] __attribute__((aligned(64)));
	int32_t data_buf_im_even[SCO_DATABUF_SIZE] __attribute__((aligned(64)));

	int32_t chip_ideal_pre_re_even[16] __attribute__((aligned(64)));
	int32_t chip_ideal_pre_im_odd[16] __attribute__((aligned(64)));

	int32_t *din_buf_re_odd;
	int32_t *din_buf_im_odd;
	int32_t *din_buf_re_even;
	int32_t *din_buf_im_even;
	int32_t valid;
	int32_t mu;
	int32_t base_point;
	int32_t ph_acc;
	int32_t trigger;
	int32_t *chip_ideal_re_even;
	int32_t *chip_ideal_im_odd;
};

void sco_tracking_init(struct sco_track *obj);
void sco_tracking_reset(struct sco_track *obj);
void sco_tracking_run(struct sco_track *obj);
void sco_tracking_test(void);

#endif
#ifdef  __cplusplus
}
#endif
#endif
