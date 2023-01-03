/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup OSAL
 * @{
 *
 * @brief Declares the structures and interfaces for the Operating System Abstraction Layer (OSAL) module.
 *
 * The OSAL module provide a unified interfaces that adapter to different OS. The interfaces include the
 * memory management, thread, mutex, semaphore, time.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file time.h
 *
 * @brief Declares time interfaces.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_TIME_H
#define AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_TIME_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/time.h>

#include "osal_c/osal_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int64_t nsecs_t;  // nano seconds

static CONSTEXPR int64_t SEC_TO_NANOSEC = 1000000000;
static CONSTEXPR int64_t SEC_TO_MICROSEC = 1000000;
static CONSTEXPR int64_t SEC_TO_MILLISEC = 1000;
static CONSTEXPR int64_t MILLISEC_TO_NANOSEC = 1000000;
static CONSTEXPR int64_t MICROSEC_TO_NANOSEC = 1000;

static CONSTEXPR inline nsecs_t secToNanosec(nsecs_t secs)
{
	return secs * SEC_TO_NANOSEC;
}

static CONSTEXPR inline nsecs_t millisecToNanosec(nsecs_t secs)
{
	return secs * MILLISEC_TO_NANOSEC;
}

static CONSTEXPR inline nsecs_t microsecToNanosec(nsecs_t secs)
{
	return secs * MICROSEC_TO_NANOSEC;
}

static CONSTEXPR inline nsecs_t nanosecToSec(nsecs_t secs)
{
	return secs / SEC_TO_NANOSEC;
}

static CONSTEXPR inline nsecs_t nanosecToMillisec(nsecs_t secs)
{
	return secs / MILLISEC_TO_NANOSEC;
}

static CONSTEXPR inline nsecs_t nanosecToMicrosec(nsecs_t secs)
{
	return secs / MICROSEC_TO_NANOSEC;
}

static CONSTEXPR inline nsecs_t s2ns(nsecs_t s)
{
	return secToNanosec(s);
}
static CONSTEXPR inline nsecs_t ms2ns(nsecs_t s)
{
	return millisecToNanosec(s);
}
static CONSTEXPR inline nsecs_t us2ns(nsecs_t s)
{
	return microsecToNanosec(s);
}
static CONSTEXPR inline nsecs_t ns2s(nsecs_t s)
{
	return nanosecToSec(s);
}
static CONSTEXPR inline nsecs_t ns2ms(nsecs_t s)
{
	return nanosecToMillisec(s);
}
static CONSTEXPR inline nsecs_t ns2us(nsecs_t s)
{
	return nanosecToMicrosec(s);
}

static CONSTEXPR inline nsecs_t seconds(nsecs_t v)
{
	return s2ns(v);
}
static CONSTEXPR inline nsecs_t milliseconds(nsecs_t v)
{
	return ms2ns(v);
}
static CONSTEXPR inline nsecs_t microseconds(nsecs_t v)
{
	return us2ns(v);
}

enum {
	SYSTEM_TIME_REALTIME = 0,  // system-wide realtime clock
	SYSTEM_TIME_MONOTONIC = 1, // monotonic time since unspecified starting point
	SYSTEM_TIME_PROCESS = 2,   // high-resolution per-process clock
	SYSTEM_TIME_THREAD = 3,    // high-resolution per-thread clock
	SYSTEM_TIME_BOOTTIME = 4   // same as SYSTEM_TIME_MONOTONIC, but including CPU suspend time
};

// return the system-time according to the specified clock
#ifdef __cplusplus
nsecs_t systemTime(int clock = SYSTEM_TIME_MONOTONIC);
#else
nsecs_t systemTime(int clock);
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_TIME_H
/** @} */
