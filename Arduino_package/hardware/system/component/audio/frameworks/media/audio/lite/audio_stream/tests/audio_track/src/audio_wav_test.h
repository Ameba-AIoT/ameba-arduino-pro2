#ifndef AUDIO_WAV_TEST
#define AUDIO_WAV_TEST

#include <stdint.h>
#include <stddef.h>

#include "FreeRTOS.h"

//#define FF_OPS

#define  MEM_DEBUG_INFO_INIT() \
	unsigned int heap_start;\
	unsigned int heap_end;\
	unsigned int heap_min_ever_free;\
    printf("[Mem]mem debug info init \n");\
	heap_start = xPortGetFreeHeapSize();
#define  MEM_DEBUG_INFO_DUMP() { \
    heap_end = xPortGetFreeHeapSize();\
	heap_min_ever_free = xPortGetMinimumEverFreeHeapSize();\
	printf("[Mem]start (0x%x), end (0x%x), ", heap_start, heap_end);\
    printf(" diff (%d), peak (%d) \n", heap_start - heap_end, heap_start - heap_min_ever_free);\
}

#ifdef __cplusplus
extern "C" {
#endif

int track_test(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif