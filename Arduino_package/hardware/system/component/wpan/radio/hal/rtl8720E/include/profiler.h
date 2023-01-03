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
 * profiler globals
 */

#ifndef INTEGRIT_PROFILER_H
#define INTEGRIT_PROFILER_H

//#include "types.h"

#ifdef COMPILER_XTENSA
#if XCHAL_HAVE_NX
#define CALL_OVERHEAD 18    /* 18 cycles on NX core */
#else
#define CALL_OVERHEAD 14    /* 14 cycles on LX core */
#endif
#include <xtensa/config/core.h>
#if XCHAL_HAVE_CCOUNT
#ifndef NO_XT_RSR_CCOUNT
#include <xtensa/tie/xt_timer.h>
#endif
#ifdef XT_RSR_CCOUNT
#define GETCLOCK() XT_RSR_CCOUNT()
#else
static unsigned long inline GETCLOCK(void)
{
	unsigned long r;
	__asm__ volatile("rsr.ccount %0" : "=r"(r));
	return r;
}
#endif
#endif
#else
#define CALL_OVERHEAD 0
#endif

#ifndef GETCLOCK
#include <time.h>
#define GETCLOCK() clock()
#endif

#if defined (COMPILER_XTENSA) && (MEM_MODEL==2)
/* use cache warming for MEM_MODEL=2 */
#define PROFILE(f)                        \
{                                         \
  if (noWarmup)                           \
  {                                       \
      uint32_t p0, p1;                    \
      xthal_dcache_all_writeback_inv();   \
      p0=GETCLOCK();                      \
      f; p1=GETCLOCK();                   \
      profiler_clk=p1-p0-CALL_OVERHEAD;   \
  }                                       \
  else                                    \
  {                                       \
     uint32_t p0, p1;                     \
     xthal_dcache_all_writeback_inv();    \
     f;                                   \
     p0=GETCLOCK();                       \
     f; p1=GETCLOCK();                    \
     profiler_clk=p1-p0-CALL_OVERHEAD;    \
  }                                       \
}
#else
#define PROFILE(f) {                \
  uint32_t p0, p1;                  \
  p0=GETCLOCK();                    \
  f; p1=GETCLOCK();                 \
  profiler_clk=p1-p0-CALL_OVERHEAD; }
#endif

extern uint32_t profiler_clk;
extern uint32_t profiler_cpm;
extern int      noWarmup;    /* global flag controlling cache warmup */

#endif /* INTEGRIT_PROFILER_H */
