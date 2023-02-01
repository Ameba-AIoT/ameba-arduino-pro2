#ifndef COMPLEX_LIB_H
#define COMPLEX_LIB_H

#include <arm_neon.h>

#define CMPLX_REAL 0
#define CMPLX_IMAG 1
#define CCA_IS_DCFI 0

#define CORDIC_ITER_NUM 9
extern int32_t cordic_pi;
extern int32_t cordic_phase_wl;
extern int32_t cordic_phase_tbl[];

#if CCA_IS_DCFI
static inline int64x2_t complex_s64_conj(int64x2_t v)
{
	int64_t *p = (int64_t *)&v;
	p[CMPLX_IMAG] = -p[CMPLX_IMAG];
	return v;
}

static inline int64x2_t complex_s64_mul(int64x2_t a, int64x2_t b)
{
	int64x2_t ret;
	int64_t a_real, a_imag, b_real, b_imag, c_real, c_imag;
	a_real = vgetq_lane_s64(a, 0);
	a_imag = vgetq_lane_s64(a, 1);
	b_real = vgetq_lane_s64(b, 0);
	b_imag = vgetq_lane_s64(b, 1);

	c_real = a_real * b_real - a_imag * b_imag;
	c_imag = a_real * b_imag + a_imag * b_real;

	ret = vsetq_lane_s64(c_real, ret, 0);
	ret = vsetq_lane_s64(c_imag, ret, 1);

	return ret;
}
#endif

static inline int32x2_t complex_s32_conj(int32x2_t v)
{
	int32_t *p = (int32_t *)&v;
	p[CMPLX_IMAG] = -p[CMPLX_IMAG];
	return v;
}

static inline int32x2_t complex_s32_mul(int32x2_t a, int32x2_t b)
{
	int32x2_t ret;
	int32x2_t b_neg, b_revt;
	b_neg = vneg_s32(b);
	b_neg = vset_lane_s32(vget_lane_s32(b, 0), b_neg, 0);
	b_revt = vrev64_s32(b);
	b_neg = vmul_s32(a, b_neg);
	b_revt = vmul_s32(a, b_revt);
	ret = vpadd_s32(b_neg, b_revt);
	return ret;
}

static __inline int32x2_t cmplx_s32_mul(int32x2_t va, int32x2_t vb)
{
	int32x2_t v_ret = {0, 0};
	int32_t *pv_a = (int32_t *)&va;
	int32_t *pv_b = (int32_t *)&vb;
	int32_t *pv_ret = (int32_t *)&v_ret;
	pv_ret[CMPLX_REAL] = pv_a[CMPLX_REAL] * pv_b[CMPLX_REAL] -
						 pv_a[CMPLX_IMAG] * pv_b[CMPLX_IMAG];
	pv_ret[CMPLX_IMAG] = pv_a[CMPLX_REAL] * pv_b[CMPLX_IMAG] +
						 pv_a[CMPLX_IMAG] * pv_b[CMPLX_REAL];
	return v_ret;
}

static __inline int32x4_t cmplx_mulq_re(int32x4_t *a, int32x4_t *b, int32x4_t *c, int32x4_t *d)
{
	int32x4_t ret;
	ret = vmulq_s32(*a, *c);
	ret = vmlsq_s32(ret, *b, *d);
	return ret;
}

static __inline int32x4_t cmplx_mulq_im(int32x4_t *a, int32x4_t *b, int32x4_t *c, int32x4_t *d)
{
	int32x4_t ret;
	ret = vmulq_s32(*a, *d);
	ret = vmlaq_s32(ret, *b, *c);
	return ret;
}
static inline void vrevertq_s32(int32x4_t *v)
{
	int32_t *p = (int32_t *)v;
	p[0] = p[0] ^ p[3];
	p[3] = p[0] ^ p[3];
	p[0] = p[0] ^ p[3];
	p[1] = p[1] ^ p[2];
	p[2] = p[1] ^ p[2];
	p[1] = p[1] ^ p[2];
	return;
}

static __inline int32_t calc_complex_re(int32_t a_re, int32_t a_im, int32_t b_re, int32_t b_im)
{
	return (a_re * b_re - a_im * b_im);
}

static __inline int32_t calc_complex_im(int32_t a_re, int32_t a_im, int32_t b_re, int32_t b_im)
{
	return (a_re * b_im + a_im * b_re);
}

static __inline int32_t calc_s32x4_sum(int32x4_t *v)
{
	int32_t *ptr = (int32_t *)v;
	return (ptr[0] + ptr[1] + ptr[2] + ptr[3]);
}

static __inline int32x2_t cmplx_s32_conj(int32x2_t v)
{
	int32_t *ptr = (int32_t *)&v;
	ptr[1] = -ptr[1];
	return v;
}

static __inline int32x2_t cmplx_s32(int32_t a, int32_t b)
{
	int32x2_t ret = {0, 0};
	int32_t *ptr = (int32_t *)&ret;
	ptr[0] = a;
	ptr[1] = b;
	return ret;
}

static __inline void vq_set_s32(int32_t a, int32_t b, int32_t c, int32_t d, int32x4_t *v)
{
	int32_t *ptr = (int32_t *)v;
	ptr[0] = a;
	ptr[1] = b;
	ptr[2] = c;
	ptr[3] = d;
	return;
}

static __inline void vq_get_s32(int32x4_t *v, int32_t *a, int32_t *b, int32_t *c, int32_t *d)
{
	int32_t *ptr = (int32_t *)v;
	*a = ptr[0];
	*b = ptr[1];
	*c = ptr[2];
	*d = ptr[3];
	return;
}

static __inline int32_t cordic(int32_t y, int32_t x, int32_t wf)
{
	int32_t theta, i, d, x1, y1;
	x = x << wf;
	y = y << wf;
	if (y == 0) {
		return (x >= 0 ? 0 : (-cordic_pi));
	} else if (x == 0) {
		return (y > 0 ? (cordic_pi >> 1) : -(cordic_pi >> 1));
	}

	theta = 0;
	x1 = x;
	if ((x < 0) && (y > 0)) {
		theta += (cordic_pi >> 1);
		x = y;
		y = -x1;
	} else if ((x < 0) && (y < 0)) {
		theta -= (cordic_pi >> 1);
		x = -y;
		y = x1;
	}
	for (i = 0; i < CORDIC_ITER_NUM; i++) {
		d = (y >= 0 ? -1 : 1);
		x1 = x - d * (y >> i);
		y1 = y + d * (x >> i);
		theta -= d * cordic_phase_tbl[i];
		x = x1;
		y = y1;
	}
	if ((theta >= cordic_pi) || (theta < -cordic_pi)) {
		theta =  -cordic_pi;
	}
	return theta;
}

static __inline int32_t floor2int(float32_t din)
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

static __inline int32_t cordic_float(float32_t y, float32_t x)
{
	int32_t theta, i, d;
	float32_t x1, y1;
	if (y == 0) {
		return (x >= 0 ? 0 : (-cordic_pi));
	} else if (x == 0) {
		return (y > 0 ? (cordic_pi >> 1) : -(cordic_pi >> 1));
	}

	theta = 0;
	x1 = x;
	if ((x < 0) && (y > 0)) {
		theta += (cordic_pi >> 1);
		x = y;
		y = -x1;
	} else if ((x < 0) && (y < 0)) {
		theta -= (cordic_pi >> 1);
		x = -y;
		y = x1;
	}
	for (i = 0; i < CORDIC_ITER_NUM; i++) {
		d = (y >= 0 ? -1 : 1);
		x1 = x - d * (floor2int(y) >> i);
		y1 = y + d * (floor2int(x) >> i);
		theta -= d * cordic_phase_tbl[i];
		x = x1;
		y = y1;
	}
	if ((theta >= cordic_pi) || (theta < -cordic_pi)) {
		theta =  -cordic_pi;
	}
	return theta;
}
#endif