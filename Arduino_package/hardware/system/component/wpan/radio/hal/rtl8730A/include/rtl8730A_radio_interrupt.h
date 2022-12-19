#ifndef RTL8730A_ZIGBEE_INTRRUPT_H
#define RTL8730A_ZIGBEE_INTRRUPT_H
#include "rtl8730A_radio_common.h"

#ifdef  _cplusplus
extern "C" {
#endif

#include "ameba_soc.h"

	volatile extern uint32_t g_dma_rx_data[];
	volatile extern int32_t g_data_full_re[];
	volatile extern int32_t g_data_full_im[];

	volatile extern u32 g_intr_flag;

	void rtl8730A_zigbee_intr_register(void);


	static __inline void enable_intr_zgb_txbuf_almost_empty(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= 0x00000001;  /* 0x400F3810[0]: r_en_intr_zigbee_txbuf_almost_empty; */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		return;
	}

	static __inline void enable_intr_zgb_txbuf_empty(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= 0x00000002;  /* 0x400F3810[1]: r_en_intr_zigbee_txbuf_empty; */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		return;
	}

	static __inline void enable_intr_zgb_txbuf_underflow(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= 0x1 << 2;  /* 0x400F3810[2]: r_en_intr_zigbee_txbuf_underflow; */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		return;
	}

	static __inline void enable_intr_zgb_txbuf_overflow(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= 0x1 << 4;  /* 0x400F3810[4]: r_en_intr_zigbee_txbuf_overflow; */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		return;
	}

	static __inline void mask_intr_zgb_txbuf_almost_empty(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp &= ~0x1;  /* 0x400F3810[0]: r_en_intr_zigbee_txbuf_almost_empty; */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		return;
	}

	static __inline void enable_intr_zgb_rxbuf_almost_full(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= (0x1 << 8);  /* 0x400F3810[8]: INTER_ZIGBEE_RXBUF_ALMOST_FULL */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		return;
	}

	static __inline void enable_intr_zgb_rxbuf_underflow(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= (0x1 << 12);  /* 0x400F3810[12]: INTER_ZIGBEE_RXBUF_UNDERFLOW */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		return;
	}

	static __inline void enable_intr_zgb_rxbuf_overflow(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= (0x1 << 10);  /* 0x400F3810[10]: INTER_ZIGBEE_RXBUF_OVERFLOW */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		return;
	}

	static __inline void mask_intr_zgb_rxbuf_almost_full(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp &= ~(0x1 << 8);  /* 0x400F3810[8]: INTER_ZIGBEE_RXBUF_ALMOST_FULL; */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		return;
	}

	static __inline void enable_intr_zgb_aagc_done(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= (0x1 << 13);  /* 0x400F3810[13]: INTER_ZIGBEE_AAGC_DONE */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);

#ifdef CONFIG_RLE1080_A_CUT   //r_zigbee_hw_aagc_en = 0
		tmp = HAL_READ32(WIFI_REG_BASE, 0x1F00);
		tmp &= ~(0x1 << 29);
		HAL_WRITE32(WIFI_REG_BASE, 0x1F00, tmp);
#endif

		return;
	}

	static __inline void enable_intr_zgb_tx_stop(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= 0x00000020;  /* 0x400F3810[5]: r_en_intr_zigbee_tx_stop */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		//  tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		return;
	}

	static __inline void clear_zgb_interrupt_status(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x180C);
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x180C, tmp);
#ifndef CONFIG_RLE1080_A_CUT
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1820);
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1820, tmp);
#endif
		return;
	}

	static __inline void enable_intr_wl_cca_start(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= 0x02000000;  /* 0x400F3810[25]: WLAN_RX_START_INIT */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		//tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		return;
	}
	static __inline void enable_intr_wl_cca_stop(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		tmp |= 0x04000000;  /* 0x400F3810[26]: WLAN_RX_STOP_INIT */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1810, tmp);
		//tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1810);
		return;
	}


	static __inline void enable_intr_wl_R2R(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1824);
		tmp |= 0x1;  /* 0x400F3824[1]: MUX state=R2R */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1824, tmp);
		//  tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1824);
		return;
	}

	static __inline void enable_intr_cca_valid(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1824);
		tmp |= 0x00000010;  /* 0x400F3824[4]: MUX state=zigbee cca invalid */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1824, tmp);
		//tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1824);
		return;
	}

	static __inline void enable_intr_cca_valid_1(void)
	{
		u32 tmp;
		tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1824);
		tmp |= 0x00000020;  /* 0x400F3824[4]: MUX state=zigbee cca invalid */
		HAL_WRITE32(RTL8730A_ZGB_REG_BASE, 0x1824, tmp);
		//tmp = HAL_READ32(RTL8730A_ZGB_REG_BASE, 0x1824);
		return;
	}

#ifdef  _cplusplus
}
#endif
#endif
