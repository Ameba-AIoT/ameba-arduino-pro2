#ifndef AEC_H
#define AEC_H

#include <stdint.h>

#if defined(CONFIG_PLATFORM_8195BHP) 
#include "AEC_8195b.h"
#else
#include "AEC_original.h"
#endif
#endif // AEC_H
