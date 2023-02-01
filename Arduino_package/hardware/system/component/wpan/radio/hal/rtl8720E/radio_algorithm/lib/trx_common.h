/*
 * rx_common.h
 *
 *  Created on: 2021骞�11鏈�25鏃�
 *      Author: ran_wei
 */

#ifndef __TRX_COMMON_H__
#define __TRX_COMMON_H__

#include "ameba_common.h"

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
extern ae_int16 *g_sym_shape_real_imp;
extern ae_int16 *g_sym_shape_imag_imp;
extern ae_int16x2 *g_sym_shape_imp;
extern uint8_t g_chip_map_imp[CHIP_MAP_GOUP][CHIP_MAP_LEN];

#define DIN_WL 10
#define DOUT_WL 7

extern const int32_t lut_pi_fxp;
extern const int32_t lut_half_pi_fxp;

extern const int32_t g_cos_lut[];

static inline int32_t get_cos(int32_t phase)
{
	return g_cos_lut[phase + 512];
}

static inline int32_t get_sin(int32_t phase)
{
	phase += 256;
	if (phase >= 512) {
		phase -= 1024;
	}
	return -g_cos_lut[phase + 512];
}

static inline int32_t disambiguity_theta_fxp(int32_t theta, int32_t pi_fxp)
{
	theta &= (pi_fxp * 2 - 1);
	//theta %= (pi_fxp * 2);

	if (theta > pi_fxp) {
		theta -= (pi_fxp * 2);
	}
	return theta;
}

void get_symbol_shape_imp(void);

#endif /*  */
