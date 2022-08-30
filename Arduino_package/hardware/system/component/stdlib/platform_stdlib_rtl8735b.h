#ifndef PLATFORM_STDLIB_RTL8195BHP_H
#define PLATFORM_STDLIB_RTL8195BHP_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
}
# include <atomic>
# define _Atomic(X) std::atomic< X >
#else
#include <stdatomic.h>
#endif

#endif //PLATFORM_STDLIB_RTL8195BHP_H
