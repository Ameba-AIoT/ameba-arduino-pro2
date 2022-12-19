#ifndef ZIGBEE_LIB_H
#define ZIGBEE_LIB_H
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <arm_neon.h>

#define DEBUG_PRINTF(format,...)    do { \
		printf("@@##FUNC:%s[%d]: "format, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
	} while(0);
#if 1
#define DEBUG_LOG(format,...)

#else
#define DEBUG_LOG(format,...)   do { \
		printf("@@##FUNC:%s[%d]: "format, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
	} while(0);
#endif
#define CORDIC_ITER_NUM 9
#define RX_USE_BUF

#define ABS(value) (((value) >= 0) ? (value) : -(value))
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define PI_FXP 1024
#define HALF_PI_FXP 512


typedef enum _RET {
	RET_ERROR = -1,
	RET_SUCCESS,
	RET_FAIL,
	RET_INVALID_PARAM,
} RET_VAL;


void zigbee_test(void);
static __inline int32_t calc_mag(int32x2_t cin, int32_t frac_bits)
{
	int32_t max_val, min_val, magnitude, output;
	int32x2_t v_frac;
	v_frac = vdup_n_s32(frac_bits);
	cin = vshl_s32(cin, v_frac);
	cin = vabs_s32(cin);
	max_val = MAX(vget_lane_s32(cin, 0), vget_lane_s32(cin, 1));
	min_val = MIN(vget_lane_s32(cin, 0), vget_lane_s32(cin, 1));
	magnitude = (((max_val << 4) - max_val) >> 4) + ((min_val * 15) >> 5);
	if (magnitude < max_val) {
		magnitude = max_val;
	}
	output = magnitude >> frac_bits;
	return output;
}

static __inline int32_t calc_mag0(int32x2_t cin)
{
	int32_t max_val, min_val, output;
	int32_t *pv = (int32_t *)&cin;
	cin = vabs_s32(cin);
	max_val = MAX(pv[0], pv[1]);
	min_val = MIN(pv[0], pv[1]);
	output = (((max_val << 4) - max_val) >> 4) + ((min_val * 15) >> 5);
	if (output < max_val) {
		output = max_val;
	}
	return output;
}

static __inline int32_t calc_mag1(int32_t din_re, int32_t din_im)
{
	int32_t max_val, min_val, output;
	din_re = ABS(din_re);
	din_im = ABS(din_im);
	max_val = MAX(din_re, din_im);
	min_val = MIN(din_re, din_im);
	output = (((max_val << 4) - max_val) >> 4) + ((min_val * 15) >> 5);
	if (output < max_val) {
		output = max_val;
	}
	return output;
}

/* num is the real times of 128bit  */
static __inline void zero_128bit_buf(void *buf, int32_t num)
{
	int32_t i;
	int32x4_t *pvq = (int32x4_t *)buf;
	int32x4_t vq_zero = {0, 0, 0, 0};
	for (i = 0; i < num; i++) {
		vst1q_s32((int32_t *)&pvq[i], vq_zero);
	}
	return;
}

static __inline int32_t disambiguity_theta_fxp(int32_t theta, int32_t pi_fxp)
{
	theta &= (pi_fxp * 2 - 1);
	if (theta > pi_fxp) {
		theta -= (pi_fxp * 2);
	}
	return theta;
}

/* 将theta转到[-pi, pi] */
static __inline int32_t disambiguity_theta(int32_t theta)
{
	theta = theta & 0x7ff;    /* 取余，控制theta在0~2pi, 比mod取余节约40us左右*/
	if (theta > PI_FXP) {
		theta = theta - 2 * PI_FXP;    /* theta:-pi~pi */
	}
	return theta;
}


static __inline int32_t calc_mag_sp(int32_t re, int32_t im, int32_t frac_bits)
{
	int32_t max_v, min_v, magnitude;
	re = abs(re) << frac_bits;
	im = abs(im) << frac_bits;
	max_v = MAX(re, im);
	min_v = MIN(re, im);
	magnitude = (((max_v << 4) - max_v) >> 4) + ((min_v * 15) >> 5);
	if (magnitude < max_v) {
		magnitude = max_v;
	}
	return (magnitude >> frac_bits);
}

/* 向下取整函数 */
static __inline int32_t ffloor(float din)
{
	if (din < 0) {
		if (((int32_t)din - din) == 0) {
			return ((int32_t)din);
		}
		return ((int32_t)din - 1);
	} else {
		return ((int32_t)din);
	}
}

/* 四舍五入函数 */
static __inline int32_t fround(float din)
{
	if (din < 0 && ((int32_t)(din + 0.5) - (din + 0.5)) == 0) {
		return ffloor(din - 0.5);
	}
	return ffloor(din + 0.5);
}

#endif
