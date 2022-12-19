#ifndef __HIFI_RADIO_TRX_API_H__
#define __HIFI_RADIO_TRX_API_H__

#include "ameba_common.h"
#include "tx_oqpsk.h"

void hal_radio_trx_init(void);
void hal_radio_trx_cnt_reset(void);
void hal_radio_on(void);
void hal_radio_channel_set(uint32_t channel);
void hal_radio_power_set(uint32_t tx_power);
BOOL hal_radio_rx_cca_check(void);
BOOL hal_radio_rx_frame(void);
void hal_radio_rx_reset(void);
void hal_radio_rx_enable(void);
void hal_radio_rx_disable(void);
void hal_radio_rx_reset_buf_idx(void);

void hal_radio_tx_enable(void);
void hal_radio_tx_frame(uint8_t *tx_frame);
#endif
