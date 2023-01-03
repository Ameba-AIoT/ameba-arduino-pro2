#ifndef __AMEBA_COMMON_H__
#define __AMEBA_COMMON_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "common.h"
#include "profiler.h"
#include "file_op.h"
#include "lib.h"
#include "types.h"
#include "zigbee_test.h"
#include "loguart.h"

#define PRINT printf
#if defined(_DEBUG)
#define DEBUG_PRINT(format,...)  do { \
                                    printf("--%s:%d--"format,__FUNCTION__, __LINE__, ##__VA_ARGS__); \
                                } \
                                while(0);
#else
#define DEBUG_PRINT(format,...)
#endif

#define SYSTEM_CTRL_BASE        0x4100C000
#define KM4_SIMULATION_STAGE_REG        0x188
#define WIFI_REG_BASE 0x40010000
#define ZIGBEE_REG_BASE 0x42000000  //rxbuf:0x42000000, txbuf:0x42001000, zgb_cr:0x42001C00

#define ZGB_FUNC_EN 0x000
#define ZGB_RXBUF_CTRL 0x008
#define ZGB_IMR0_OFST 0x010
#define ZGB_ISR0 0x0c
#define ZGB_TRX_REQ 0x01c
#define ZGB_ISR1 0x020
#define ZGB_IMR1_OFST 0x024

#if 1//def _PXP_

#define HAL_READ32(base, addr)              (*((volatile uint32_t*)(base + addr)))
#define HAL_WRITE32(base, addr, value32)    ((*((volatile uint32_t*)(base + addr))) = (value32))

#define TIME_AFTER(a,b) ((int64_t)(b) - (int64_t)(a) < 0)
#define TIME_BEFORE(a,b) ((int64_t)(b) - (int64_t)(a) > 0)
#define ZGB_INTR_NUM 26
static inline void DelayUs(uint32_t us)
{
	uint64_t cntvct;

	cntvct = (uint64_t)(GETCLOCK() + 400 * us);

	while (TIME_BEFORE(GETCLOCK(), cntvct)) {
		XT_NOP();
	}
}

#endif
#endif
