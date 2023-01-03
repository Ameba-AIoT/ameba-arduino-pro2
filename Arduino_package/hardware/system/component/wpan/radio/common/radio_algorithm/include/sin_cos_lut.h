#ifndef SIN_COS_LUT_H
#define SIN_COS_LUT_H
#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DIN_WL 10
#define DOUT_WL 7

extern const int32_t lut_pi_fxp;
extern const int32_t lut_half_pi_fxp;
extern const int32_t g_cos_lut[];

static __inline int32_t get_cos(int32_t phase)
{
	return g_cos_lut[phase + 512];
}

static __inline int32_t get_sin(int32_t phase)
{
	phase += 256;
	if (phase >= 512) {
		phase -= 1024;
	}
	return -g_cos_lut[phase + 512];
}

void sin_cos_lut_tests(void);

#ifdef  __cplusplus
}
#endif
#endif

