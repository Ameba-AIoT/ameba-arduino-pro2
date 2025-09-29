#ifndef AMB_ARD_LOG_H
#define AMB_ARD_LOG_H

#include <stdio.h>

#define ARD_LOG_OFF 3
#define ARD_LOG_ERR 2
#define ARD_LOG_INF 1
#define ARD_LOG_ALL 0

#if defined(Arduino_LOGS_ALL)
#define ARD_LOG_LEVEL ARD_LOG_ALL
#elif defined(Arduino_LOGS_ERR)
#define ARD_LOG_LEVEL ARD_LOG_ERR
#elif defined(Arduino_LOGS_INFO)
#define ARD_LOG_LEVEL ARD_LOG_INF
#else
// No flag defined (e.g., "Disable all"): default to OFF
#define ARD_LOG_LEVEL ARD_LOG_OFF
#endif

#define amb_ard_printf(level, ...) \
    if ((level == ARD_LOG_LEVEL) || (ARD_LOG_LEVEL == ARD_LOG_ALL)) \
    printf(__VA_ARGS__)

#endif
