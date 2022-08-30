#ifndef _APP_FLAGS_H_
#define _APP_FLAGS_H_

#include "platform_opts_bt.h"
#if UPPER_STACK_VERSION == VERSION_2019
#include "bt_flags.h"
#elif UPPER_STACK_VERSION == VERSION_2021
#include "upperstack_config.h"
#endif

#define APP_MAX_LINKS                       4

#endif
