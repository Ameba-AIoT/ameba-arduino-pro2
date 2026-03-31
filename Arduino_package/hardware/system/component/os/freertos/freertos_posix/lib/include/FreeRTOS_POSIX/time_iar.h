/* time.h standard header */
/* Copyright 2003-2017 IAR Systems AB. */
#ifndef _TIME
#define _TIME

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#include <ycheck.h>
#include <yvals.h>
#include <ysizet.h>

/* Check _DLIB_TIME_USES_64 setting */
#if __AEABI_PORTABILITY_INTERNAL_LEVEL && defined(_DLIB_TIME_USES_64)
  #error("_DLIB_TIME_USES_64 cannot be used together with _AEABI_PORTABILITY_LEVEL" )
#endif
#if defined(_NO_DEFINITIONS_IN_HEADER_FILES) && defined(_DLIB_TIME_USES_64)
  #error("_DLIB_TIME_USES_64 cannot be used with _NO_DEFINITIONS_IN_HEADER_FILES")
#endif

/* Set _DLIB_TIME_USES_64 if not set */
#ifndef _DLIB_TIME_USES_64
  #define _DLIB_TIME_USES_64 _DLIB_TIME_USES_64_DEFAULT
#elif _DLIB_TIME_USES_64 != 0 && _DLIB_TIME_USES_64 != 1
  #error("Defined _DLIB_TIME_USES_64 must be either 0 or 1")
#elif _DLIB_TIME_USES_64 && !_DLIB_TIME_ALLOW_64
  #error("Defined _DLIB_TIME_USES_64 requires _DLIB_TIME_ALLOW_64")
#endif

/* Include 32 or 64 bit specific time.h */
#if _DLIB_TIME_USES_64
  #include "time64.h"
#else 
  #include "time32.h"
#endif

#endif /* _TIME */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0576 */
