#ifndef __HIFI_RADIO_COMMON_H__
#define __HIFI_RADIO_COMMON_H__

#include "tx_oqpsk.h"

void reset_802154_rx_buf(void);
void enable_802154_clk(void);
void rstb_802154(void);
void set_802154_bw(uint32_t bandwidth);
void set_802154_dac_clk(uint32_t bandwidth);
void switch_to_802154_channel_setting(uint32_t channel_num);
void set_802154_pwr(uint32_t power);
void set_802154_cca_0(void);
void set_802154_rx_req_0(void);
void set_802154_rxidle(void);
void set_802154_rx(void);
void disable_802154_rx(void);
void enable_802154_AAGC_DONE(void);
void enable_802154_WLAN_RX_START_INIT(void);
void enable_802154_WLAN_RX_STOP_INIT(void);
void enable_802154_WLAN_R2R(void);
void enable_802154_CCA_INVALID(void);
void enable_802154_RXBUF_ALMOST_FULL(void);
void enable_802154_RXBUF_OVERFLOW(void);
void enable_802154_RXBUF_UNDERFLOW(void);
void clear_802154_interrupt_status(void);
void coexit_802154_setting(void);

void set_802154_tx_length(uint32_t len_byte);
void up_802154_tx_trigger(void);
void down_802154_tx_trigger(void);
void set_802154_tx(void);
void enable_802154_TX_STOP(void);

#endif
