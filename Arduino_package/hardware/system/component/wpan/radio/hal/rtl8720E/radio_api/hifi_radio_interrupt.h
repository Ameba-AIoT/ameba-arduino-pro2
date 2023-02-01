#ifndef __HIFI_RADIO_INTERRUPT__
#define __HIFI_RADIO_INTERRUPT__
#include <xtensa/hal.h>
#include <xtensa/xtruntime.h>

extern volatile int32_t g_zgb_isr_cnt;
extern volatile uint32_t g_isr[10][2];

void interrupt_802154_register(void);

#endif /*  */
