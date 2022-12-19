/* ------------------------------------------------------------------------ */
/* Copyright (c) 2020 by Cadence Design Systems, Inc. ALL RIGHTS RESERVED.  */
/* These coded instructions, statements, and computer programs ('Cadence    */
/* Libraries') are the copyrighted works of Cadence Design Systems Inc.     */
/* Cadence IP is licensed for use with Cadence processor cores only and     */
/* must not be used for any other processors and platforms. Your use of the */
/* Cadence Libraries is subject to the terms of the license agreement you   */
/* have entered into with Cadence Design Systems, or a sublicense granted   */
/* to you by a direct Cadence licensee.                                     */
/* ------------------------------------------------------------------------ */
/*  IntegrIT, Ltd.   www.integrIT.com, info@integrIT.com                    */
/*                                                                          */
/* NatureDSP_Baseband Library                                               */
/*                                                                          */
/* This library contains copyrighted materials, trade secrets and other     */
/* proprietary information of IntegrIT, Ltd. This software is licensed for  */
/* use with Cadence processor cores only and must not be used for any other */
/* processors and platforms. The license to use these sources was given to  */
/* Cadence, Inc. under Terms and Condition of a Software License Agreement  */
/* between Cadence, Inc. and IntegrIT, Ltd.                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2009-2020 IntegrIT, Limited.                      */
/*                      All Rights Reserved.                                */
/* ------------------------------------------------------------------------ */
/*
 * Portable data types.
 * Basic data types are supplied as a part of library API. This header
 * provides access to portable data types for generic utility modules of
 * the test environment, which may be unaware of the library under test.
 */

#ifndef __TYPES_H
#define __TYPES_H
#include "common.h"

typedef struct _ae_int16x2 {
	int16_t re;  //low bit
	int16_t im;  //high bit
} ae_int16x2;

static inline ae_int16x2 AE_MOVAD16X2(ae_int16 re, ae_int16 im)
{
	ae_int16x2 ret;
	ret.re = re;
	ret.im = im;
	return ret;
}

static inline void AE_SET16X2(ae_int16x2 *p, ae_int16 re, ae_int16 im)
{
	p->re = re;
	p->im = im;
}

#endif /* __TYPES_H */
