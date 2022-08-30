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

#ifndef AMEBA_BASE_LOG_H
#define AMEBA_BASE_LOG_H

#include <stdbool.h>
#include <stddef.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/*
 * Log domain
 */
#ifndef LOG_DOMAIN
#define LOG_DOMAIN 0
#endif


/*
 * LOG_TAG is the local tag used for the following simplified
 * logging macros. You can change this preprocessor definition
 * before using the other macros to change the tag.
 */
#ifndef LOG_TAG
#define LOG_TAG NULL
#endif


/*
 * Normally we strip the effects of ALOGV (VERBOSE messages),
 * LOG_FATAL and LOG_FATAL_IF (FATAL assert messages) from the
 * release builds be defining NDEBUG.  You can modify this (for
 * example with "#define LOG_NDEBUG 0" at the top of your source
 * file) to change that behavior.
 */
#ifndef LOG_NDEBUG
#ifdef NDEBUG
#define LOG_NDEBUG 1
#else
#define LOG_NDEBUG 0
#endif
#endif

/*
 * Log level
 */
typedef enum {
	AMEBA_LOG_LEVEL_MIN = 0,
	AMEBA_LOG_VERBOSE = 2,
	AMEBA_LOG_DEBUG = 3,
	AMEBA_LOG_INFO = 4,
	AMEBA_LOG_WARN = 5,
	AMEBA_LOG_ERROR = 6,
	AMEBA_LOG_FATAL = 7,
	AMEBA_LOG_LEVEL_MAX,
} LogLevel;


/*
 * The actual log funcation
 */
int amebaLogPrint(LogLevel level, unsigned int domain, const char *tag, const char *fmt, ...)
__attribute__((__format__(printf, 4, 5)));

void amebaLogAssert(const char *cond, unsigned int domain, const char *tag, const char *fmt, ...)
__attribute__((__format__(printf, 4, 5)));

bool amebaLogIsLoggable(unsigned int domain, const char *tag, LogLevel level);

/* --------------------------------------------------------------------- */

#ifndef __predict_false
#define __predict_false(exp) __builtin_expect((exp) != 0, 0)
#endif


/* --------------------------------------------------------------------- */

/* XXX Macros to work around syntax errors in places where format string
 * arg is not passed to ALOG_ASSERT, LOG_ALWAYS_FATAL or LOG_ALWAYS_FATAL_IF
 * (happens only in debug builds).
 */

/* Returns 2nd arg.  Used to substitute default value if caller's vararg list
 * is empty.
 */
#define __ameba_second(dummy, second, ...) second

/* If passed multiple args, returns ',' followed by all but 1st arg, otherwise
 * returns nothing.
 */
#define __ameba_rest(first, ...) , ##__VA_ARGS__

#define amebaPrintAssert(cond, tag, ...)          \
  amebaLogAssert(cond, LOG_DOMAIN, tag,           \
              __ameba_second(0, ##__VA_ARGS__, NULL) \
                  __ameba_rest(__VA_ARGS__))



/*
 * Log a fatal error.  If the given condition fails, this stops program
 * execution like a normal assertion, but also generating the given message.
 * It is NOT stripped from release builds.  Note that the condition test
 * is -inverted- from the normal assert() semantics.
 */
#ifndef LOG_ALWAYS_FATAL_IF
#define LOG_ALWAYS_FATAL_IF(cond, ...)                           \
  ((__predict_false(cond))                                       \
       ? ((void)amebaPrintAssert(#cond, LOG_TAG, ##__VA_ARGS__)) \
       : (void)0)
#endif

#ifndef LOG_ALWAYS_FATAL
#define LOG_ALWAYS_FATAL(...) \
  (((void)amebaPrintAssert(NULL, LOG_TAG, ##__VA_ARGS__)))
#endif


/*
 * Versions of LOG_ALWAYS_FATAL_IF and LOG_ALWAYS_FATAL that
 * are stripped out of release builds.
 */

#if LOG_NDEBUG

#ifndef LOG_FATAL_IF
#define LOG_FATAL_IF(cond, ...) ((void)0)
#endif
#ifndef LOG_FATAL
#define LOG_FATAL(...) ((void)0)
#endif

#else

#ifndef LOG_FATAL_IF
#define LOG_FATAL_IF(cond, ...) LOG_ALWAYS_FATAL_IF(cond, ##__VA_ARGS__)
#endif
#ifndef LOG_FATAL
#define LOG_FATAL(...) LOG_ALWAYS_FATAL(__VA_ARGS__)
#endif

#endif

/*
 * Assertion that generates a log message when the assertion fails.
 * Stripped out of release builds.  Uses the current LOG_TAG.
 */
#ifndef ALOG_ASSERT
#define ALOG_ASSERT(cond, ...) LOG_FATAL_IF(!(cond), ##__VA_ARGS__)
#endif


/* --------------------------------------------------------------------- */

/*
 * C/C++ logging functions.  See the logging documentation for API details.
 *
 * We'd like these to be available from C code (in case we import some from
 * somewhere), so this has a C interface.
 *
 * The output will be correct when the log file is shared between multiple
 * threads and/or multiple processes so long as the operating system
 * supports O_APPEND.  These calls have mutex-protected data structures
 * and so are NOT reentrant.  Do not use LOG in a signal handler.
 */

/* --------------------------------------------------------------------- */

/*----------------------------------------------------------------------
|  ALOGV - Send a verbose log message using the current LOG_TAG.
|  Note: Verbose log output depends on the LOG_NDEBUG flag.
+---------------------------------------------------------------------*/
#ifndef ALOGV
#define __ALOGV(...) ((void)ALOG(LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#if LOG_NDEBUG
#define ALOGV(...)          \
  do {                      \
    if (false) {            \
      __ALOGV(__VA_ARGS__); \
    }                       \
  } while (false)
#else
#define ALOGV(...) __ALOGV(__VA_ARGS__)
#endif
#endif

#ifndef ALOGV_IF
#if LOG_NDEBUG
#define ALOGV_IF(cond, ...) ((void)0)
#else
#define ALOGV_IF(cond, ...)                                                  \
  ((__predict_false(cond)) ? ((void)ALOG(LOG_VERBOSE, LOG_TAG, __VA_ARGS__)) \
                           : (void)0)
#endif
#endif

/*----------------------------------------------------------------------
|  ALOGD - Send a debug log message using the current LOG_TAG.
+---------------------------------------------------------------------*/
#ifndef ALOGD
#define ALOGD(...) ((void)ALOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGD_IF
#define ALOGD_IF(cond, ...)                                                \
  ((__predict_false(cond)) ? ((void)ALOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__)) \
                           : (void)0)
#endif


/*----------------------------------------------------------------------
|  ALOGI - Send a info log message using the current LOG_TAG.
+---------------------------------------------------------------------*/
#ifndef ALOGI
#define ALOGI(...) ((void)ALOG(LOG_INFO, LOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGI_IF
#define ALOGI_IF(cond, ...)                                               \
  ((__predict_false(cond)) ? ((void)ALOG(LOG_INFO, LOG_TAG, __VA_ARGS__)) \
                           : (void)0)
#endif


/*----------------------------------------------------------------------
|  ALOGW - Send a warning log message using the current LOG_TAG.
+---------------------------------------------------------------------*/
#ifndef ALOGW
#define ALOGW(...) ((void)ALOG(LOG_WARN, LOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGW_IF
#define ALOGW_IF(cond, ...)                                               \
  ((__predict_false(cond)) ? ((void)ALOG(LOG_WARN, LOG_TAG, __VA_ARGS__)) \
                           : (void)0)
#endif


/*----------------------------------------------------------------------
|  ALOGE - Send an error log message using the current LOG_TAG.
+---------------------------------------------------------------------*/
#ifndef ALOGE
#define ALOGE(...) ((void)ALOG(LOG_ERROR, LOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGE_IF
#define ALOGE_IF(cond, ...)                                                \
  ((__predict_false(cond)) ? ((void)ALOG(LOG_ERROR, LOG_TAG, __VA_ARGS__)) \
                           : (void)0)
#endif


/*----------------------------------------------------------------------
|  ALOG - Basic log message macro.
|  Example:
|   ALOG(LOG_WARN, "FooBar", "Failed with error %d", errno);
+---------------------------------------------------------------------*/
#ifndef ALOG
#define ALOG(priority, tag, ...) ((void)amebaLogPrint(AMEBA_##priority, LOG_DOMAIN, tag, __VA_ARGS__))
#endif


__END_DECLS

#endif // AMEBA_BASE_LOG_H