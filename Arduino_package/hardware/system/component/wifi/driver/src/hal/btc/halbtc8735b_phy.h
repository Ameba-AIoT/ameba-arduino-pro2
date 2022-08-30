#ifndef __INC_HALBTC8735B_PHY_H
#define __INC_HALBTC8735B_PHY_H

#include "bt_intf.h"

uint32_t btc_set_gnt_bt_8735b(pta_type_t gnt_bt);
uint32_t btc_set_gnt_bt_with_clk_source_8735b(pta_type_t gnt_bt);
uint32_t btc_pta_init_8735b(void);
//uint32_t btc_set_single_tone_tx(uint8_t bStart);

#endif // __INC_HALBTC8735B_PHY_H
