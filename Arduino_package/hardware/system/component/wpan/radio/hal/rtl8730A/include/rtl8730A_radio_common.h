#ifndef RTL8730A_ZIGBEE_COMMON_H
#define RTL8730A_ZIGBEE_COMMON_H

#ifdef  _cplusplus
extern "C" {
#endif

#include "ameba_soc.h"

#ifdef CONFIG_RLE1080_A_CUT
#define RTL8730A_ZGB_REG_BASE   (ZIGBEE_REG_BASE)
#else
#define RTL8730A_ZGB_REG_BASE   (ZIGBEE_REG_BASE + 0x0400)
#endif

#ifdef CONFIG_RLE1080_A_CUT
#define RTL8730A_BB_REG_BASE    (WIFI_REG_BASE)
#else
#define RTL8730A_BB_REG_BASE    (WIFI_REG_BASE + 0x10000)
#endif
	//#define FIFO_CACHEABLE_802154

	void set_zgb_bw(u32 bandwidth);
	void set_zgb_dac_clk(u32 bandwidth);
	void set_zgb_adc_clk(u32 bandwidth);
	void enable_zgb_tx_ifmod(void);
	void enable_zgb_rx_ifdemod(void);
	void disable_zgb_tx_ifmod(void);
	void disable_zgb_rx_ifdemod(void);
	void set_zgb_tx_freq_shift(u32 f_shift);
	void set_zgb_rx_freq_shift(u32 f_shift);
	void set_zgb_pwr(u32 power);
	void set_zgb_tx_length(u32 len_byte);
	u32 get_tx_ok_cnt(void);
	u32 get_rx_crc16_ok_cnt(void);
	u32 get_rx_crc16_fail_cnt(void);
	u32 get_rx_cca_ok_cnt(void);
	u32 get_rx_fa_cnt(void);
	void set_tx_ok_cnt(u32 tx_ok_cnt);
	void set_rx_crc16_ok_cnt(u32 crc16_ok_cnt);
	void set_rx_crc16_fail_cnt(u32 crc16_fail_cnt);
	void set_rx_cca_ok_cnt(u32 cca_ok_cnt);
	void set_rx_fa_cnt(u32 fa_cnt);

	void enable_clk_and_func(void);
	void switch_clk_to_zgb(void);
	void pta_enable_zgb(void);
	void zgb_rstb(void);
	u8 wlan_on(void);
	void load_zgb_bbreg(void);
	void load_wl_phyreg(void);

#ifdef  _cplusplus
}
#endif
#endif

