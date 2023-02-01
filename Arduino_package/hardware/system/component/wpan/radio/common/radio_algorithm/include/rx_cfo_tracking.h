#ifndef CFO_TRACKING_H
#define CFO_TRACKING_H

#ifdef  __cplusplus
extern "C" {
#endif
#include <arm_neon.h>
#include <stdint.h>

struct cfo_track {
	int32_t valid;
	int32_t din_re;
	int32_t din_im;
	float32_t loop_filter_state;
	float32_t loop_filter_out;
	float32_t K1;
	float32_t K2;
};


void cfo_tracking_init(struct cfo_track *obj);
void cfo_tracking_reset(struct cfo_track *obj);
void cfo_tracking_run(struct cfo_track *obj);

#ifdef  __cplusplus
}
#endif
#endif

