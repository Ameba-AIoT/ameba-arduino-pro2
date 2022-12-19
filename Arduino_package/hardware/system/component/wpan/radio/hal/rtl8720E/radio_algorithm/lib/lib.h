/*
 * inline_func.h
 *
 *  Created on: 2021年10月26日
 *      Author: ran_wei
 */

#ifndef __INLINE_FUNC_H__
#define __INLINE_FUNC_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRACE(A, B, C) //printf
#define DEBUG_LOG1(A, B) printf((A), (B))
static inline void print_int16x4(ae_int16x4 *p)
{
	ae_int16 *pp = (ae_int16 *)p;
	printf("(%d, %d, %d, %d)\n", (int32_t)pp[0], (int32_t)pp[1], (int32_t)pp[2], (int32_t)pp[3]);
}
static inline void print_int32x2(ae_int32x2 *p)
{
	ae_int32 *pp = (ae_int32 *)p;
	printf("(%d,%d)\n", (int32_t)pp[0], (int32_t)pp[1]);
}

static __inline int32_t calc_mag(ae_int32x2 cin)
{
	int32_t max_val, min_val, magnitude;
	//cin = AE_SRLA32(cin, frac_bits);
	cin = AE_ABS32(cin);
	max_val = XT_MAX(AE_MOVAD32_L(cin), AE_MOVAD32_H(cin));
	min_val = XT_MIN(AE_MOVAD32_L(cin), AE_MOVAD32_H(cin));
	magnitude = (((max_val << 4) - max_val) >> 4) + ((min_val * 15) >> 5);
	if (magnitude < max_val) {
		magnitude = max_val;
	}
	//output = magnitude >> frac_bits;
	return magnitude;
}

static inline ae_int32x4 ae_mul_int32x4(ae_int32x4 a, ae_int32x4 b)
{
	ae_int32x2 d0, d1, d2, d3, m0, m1;
	ae_int32x4 ret;
	AE_L32X2X2_I(d0, d1, &a, 0);
	AE_L32X2X2_I(d2, d3, &b, 0);
	m0 = AE_INT32X2_MUL_INT32X2(d2, d0);
	m1 = AE_INT32X2_MUL_INT32X2(d3, d1);
	AE_S32X2X2_I(m0, m1, &ret, 0);
	return ret;

}

static inline int16_t calc_complex_re(int16_t a_re, int16_t a_im, int16_t b_re, int16_t b_im)
{
	return (a_re * b_re - a_im * b_im);
}

static inline int16_t calc_complex_im(int16_t a_re, int16_t a_im, int16_t b_re, int16_t b_im)
{
	return (a_re * b_im + a_im * b_re);
}

static inline int32_t calc_mag_sp(int32_t re, int32_t im, int32_t frac_bits)
{
	int32_t max_v, min_v, magnitude;
	re = abs(re) << frac_bits;
	im = abs(im) << frac_bits;
	max_v = fmax(re, im);
	min_v = fmin(re, im);
	magnitude = (((max_v << 4) - max_v) >> 4) + ((min_v * 15) >> 5);
	if (magnitude < max_v) {
		magnitude = max_v;
	}
	return (magnitude >> frac_bits);
}

/*
 * calculate two 16-bit complex mag, return two value
 * */
#if 0
static __inline ae_int16x4 calc_mag_int16x8(ae_int16x8 *ocin)
{

	ae_int16x4 qcin0, qcin1, qabs0, qabs1, qabsrvt0, qabsrvt1, qmax0, qmin0, qmax1, qmin0, qmax, qmin;
	ae_int16x4 qmax_shift, qmin_shift, qcst15, qmag;
	ae_int32x2 vmul0, vmul1;
	AE_L16X4X2_X(qcin0, qcin1, ocin, 0);
	qabs0 = AE_ABS16(qcin0);
	qabs1 = AE_ABS16(qcin1);
	qabsrvt0 = AE_SEL16_2301(qabs0, qabs0);
	qabsrvt0 = AE_SEL16_2301(qabs0, qabs0);
	qmax0 = AE_INT16X4_MAX(qabs0, qabsrvt0);
	qmin0 = AE_INT16X4_MIN(qabs0, qabsrvt0);
	qmax1 = AE_INT16X4_MAX(qabs1, qabsrvt1);
	qmin1 = AE_INT16X4_MIN(qabs1, qabsrvt1);
	qmax = AE_SEL16_6420(qmax0, qmax1);
	qmin = AE_SEL16_6420(qmin0, qmin1);

	qmax_shift = AE_SRLA16(qmax, -4);
	qmax_shift = AE_SUB16(qmax_shift, qmax);
	qmax_shift = AE_SRLI16(qmax_shift, 4);
	qcst15 = AE_MOVDA16(15);
	AE_MUL16X4(vmul0, vmul1, qmin, qcst15);
	//qmin_shift = AE_CVT16X4_vector(d0);
	qmin_shift = AE_SEL16_6420(vmul0, vmul1);
	qmag = AE_ADD16(qmax_shift, q_min_shift);
	return qmag;

}
#endif
#endif /*  */
