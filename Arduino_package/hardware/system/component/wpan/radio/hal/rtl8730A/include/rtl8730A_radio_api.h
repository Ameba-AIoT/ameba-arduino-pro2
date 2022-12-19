#ifndef ZIGBEE_API_H
#define ZIGBEE_API_H

#ifdef  _cplusplus
extern "C" {
#endif

#include "ameba_soc.h"

	void enable_zigbee_trx_setting(void);
	void disable_zigbee_trx_setting(void);
	void switch_to_wlan_channel_setting(u32 channel_num);
	void enable_wlan_trx_setting(void);
	void disable_wlan_trx_setting(void);
	void switch_to_zigbee_channel_setting(u32 channel_num);
	void tdma_wlan_slot_setting(u32 channel_num);
	void tdma_zigbee_slot_setting(u32 channel_num);
	void zigbee_rxidle_setting(void);
	void zigbee_rx_setting(void);
	void zigbee_rx_buffer_0(void);
	void zigbee_set_cca_0(void);
	void set_rx_req_0(void);
	void zigbee_tx_setting(void);

#ifdef  _cplusplus
}
#endif
#endif

