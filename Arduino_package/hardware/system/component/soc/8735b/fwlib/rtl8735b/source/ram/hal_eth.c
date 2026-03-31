/**************************************************************************//**
 * @file    hal_eth.c
 * @brief   The Ethernet HAL API functions
 * @version V1.00
 * @date    2017-07-20
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/
#include "hal_eth.h"
#include "hal_pinmux.h"
#include "hal_cache.h"
#include "hal_sys_ctrl.h"



#if defined(CONFIG_MII_EN) && (CONFIG_MII_EN == 1)
/**
 * @addtogroup hs_hal_ethernet ETHERNET
 * @{
 */

extern hal_eth_func_stubs_t hal_eth_stubs;

extern hal_eth_adapter_t *peth_adapt;
extern volatile hal_eth_tx_desc_t *peth_tx_desc;
extern volatile hal_eth_rx_desc_t *peth_rx_desc;
extern volatile u8 *peth_tx_pkt_buf;
extern volatile u8 *peth_rx_pkt_buf;
volatile u32 tx_ok_int_cnt = 0;
volatile u32 rx_ok_int_cnt = 0;
volatile u32 tdu_cnt = 0;
volatile u32 rdu_cnt = 0;


/**
  * @brief The global Ethernet HAL adapter.
  */
hal_eth_adapter_t eth_adapter;



void hal_eth_irq_unreg(void)
{
	hal_eth_stubs.hal_eth_irq_unreg();
}


/**
 *  @brief To set the ethernet MAC address.
 *
 *  @param[in]  addr The specified MAC address.
 *
 *  @returns    void.
 */
void hal_eth_set_mac_addr(u8 *addr)
{
	hal_eth_stubs.hal_eth_set_mac_addr(&eth_adapter, addr);
}


/**
 *  @brief To get the ethernet MAC address.
 *
 *  @param[in]  addr The buffer of MAC address.
 *
 *  @returns    void.
 */
void hal_eth_get_mac_addr(u8 *addr)
{
	hal_eth_stubs.hal_eth_get_mac_addr(&eth_adapter, addr);
}


/**
 *  @brief To set the Tx/Rx descriptor number.
 *
 *  @param[in]  tx_desc_no The specified Tx descriptor number.
 *  @param[in]  rx_desc_no The specified Rx descriptor number.
 *
 *  @returns    void.
 */
void hal_eth_set_desc_num(u8 tx_desc_no, u8 rx_desc_no)
{
	hal_eth_stubs.hal_eth_set_desc_num(&eth_adapter, tx_desc_no, rx_desc_no);
}


/**
 *  @brief To set the start address of Tx/Rx descriptor ring.
 *
 *  @param[in]  tx_desc The start address of Tx descriptor ring.
 *  @param[in]  rx_desc The start address of Rx descriptor ring.
 *
 *  @returns    void.
 */
void hal_eth_set_desc_addr(u8 *tx_desc, u8 *rx_desc)
{
	hal_eth_stubs.hal_eth_set_desc_addr(&eth_adapter, tx_desc, rx_desc);
}


/**
 *  @brief To set the start address of Tx/Rx packet buffer.
 *
 *  @param[in]  tx_pkt_buf The start address of Tx packet buffer.
 *  @param[in]  rx_pkt_buf The start address of Rx packet buffer.
 *
 *  @returns    void.
 */
void hal_eth_set_pkt_buf(u8 *tx_pkt_buf, u8 *rx_pkt_buf)
{
	hal_eth_stubs.hal_eth_set_pkt_buf(&eth_adapter, tx_pkt_buf, rx_pkt_buf);
}


void hal_eth_sys_hw_ctrl(u8 hw_id, u8 en)
{
	AON_TypeDef *aon = AON;
	SYSON_S_TypeDef *syson_s = SYSON_S;
	volatile uint32_t val;


	if (en) {
		switch (hw_id) {
		case eth_sys_hw_femac_ip:
			// enable GMAC & GMAC SCLK
			val = syson_s->SYSON_S_REG_SYS_RMII_CTRL;
			val |= SYSON_S_BIT_SYS_RMII_SCLK_GEN | SYSON_S_BIT_SYS_RMII_CLK_EN | SYSON_S_BIT_SYS_RMII_EN;
			syson_s->SYSON_S_REG_SYS_RMII_CTRL = val;
			break;
		case eth_sys_hw_uabg_en:
			// enable bandgap
			val = syson_s->SYSON_S_REG_SYS_OTG_CTRL;
			val |= SYSON_S_BIT_SYS_UABG_EN;
			syson_s->SYSON_S_REG_SYS_OTG_CTRL = val;
			break;
		case eth_sys_hw_uahv_en:
			// enable bandgap power
			val = syson_s->SYSON_S_REG_SYS_OTG_CTRL;
			val |= SYSON_S_BIT_SYS_UAHV_EN;
			syson_s->SYSON_S_REG_SYS_OTG_CTRL = val;
			break;
		case eth_sys_hw_fephy_en:
			// enable IBX to FEPHY
			val = syson_s->SYSON_S_REG_SYS_OTG_CTRL;
			val |= SYSON_S_BIT_USB_IBX2MIPI_EN;
			syson_s->SYSON_S_REG_SYS_OTG_CTRL = val;
			// disable isolation FEPHY digital to analog
			val = aon->AON_REG_AON_ISO_CTRL;
			val &= ~(AON_BIT_FEPHY_ISO);
			aon->AON_REG_AON_ISO_CTRL = val;
			// enable FEPHY power state
			val = aon->AON_REG_AON_ISO_CTRL;
			val |= AON_BIT_FEPHY_POW_STATE;
			aon->AON_REG_AON_ISO_CTRL = val;
			// enable FEPHY IP function
			val = aon->AON_REG_AON_ISO_CTRL;
			val |= AON_BIT_FEPHY_RSTB_L;
			aon->AON_REG_AON_ISO_CTRL = val;
			break;
		case eth_sys_hw_lx_en:
			// enable LX bus & LX bus clock
			val = syson_s->SYSON_S_REG_SYS_PLATFORM_CTRL0;
			val |= SYSON_S_BIT_LXBUS_CLK_EN | SYSON_S_BIT_LXBUS_EN;
			syson_s->SYSON_S_REG_SYS_PLATFORM_CTRL0 = val;
			break;
		default:
			break;
		}
	} else {
		switch (hw_id) {
		case eth_sys_hw_fephy_ip:
			// disable FEPHY IP function
			val = aon->AON_REG_AON_ISO_CTRL;
			val &= ~(AON_BIT_FEPHY_RSTB_L);
			aon->AON_REG_AON_ISO_CTRL = val;
			break;
		case eth_sys_hw_femac_ip:
			// disable GMAC & GMAC SCLK
			val = syson_s->SYSON_S_REG_SYS_RMII_CTRL;
			val &= ~(SYSON_S_BIT_SYS_RMII_SCLK_GEN | SYSON_S_BIT_SYS_RMII_CLK_EN | SYSON_S_BIT_SYS_RMII_EN);
			syson_s->SYSON_S_REG_SYS_RMII_CTRL = val;
			break;
		default:
			break;
		}
	}
}


void MII_IRQHandler(void);
void MII_IRQHandler(void)
{
	ethernet_isr_imr_t isr_imr;


	isr_imr.w = peth_adapt->base_addr->isr_imr;

	// Rx OK
	if (isr_imr.b.isr_rok) {
		peth_adapt->base_addr->isr_imr |= FEMAC_ISR_BIT_ROK;
		rx_ok_int_cnt++;
		if ((peth_adapt->callback) != NULL) {
			peth_adapt->callback(EthIntRok, 0);
		}
	}
	// Rx FIFO full
	if (isr_imr.b.isr_rer_ovf) {
		peth_adapt->base_addr->isr_imr |= FEMAC_ISR_BIT_RER_OVF;
		DBG_MII_WARN("Rx FIFO full\r\n");
	}
	// Tx OK
	if (isr_imr.b.isr_tok) {
		tx_ok_int_cnt++;
//        peth_adapt->base_addr->isr_imr |= FEMAC_ISR_BIT_TOK;
		if ((peth_adapt->callback) != NULL) {
			peth_adapt->callback(EthIntTok, 0);
		}
	}
	// TDU
	if (isr_imr.b.isr_tdu) {
		peth_adapt->base_addr->isr_imr |= FEMAC_ISR_BIT_TDU;
		tdu_cnt++;
	}
	// Link change
	if (isr_imr.b.isr_linkchg) {
		peth_adapt->base_addr->isr_imr |= FEMAC_ISR_BIT_LINKCHG;
		if ((peth_adapt->callback) != NULL) {
			if (!(peth_adapt->base_addr->ms_b.linkb)) {
				peth_adapt->callback(EthIntLinkUp, 0);
			} else {
				peth_adapt->callback(EthIntLinkDown, 0);
			}
		}
	}
	// RDU
	if (isr_imr.b.isr_rdu) {
		DBG_MII_WARN("RDU (0x%08X)\r\n", peth_adapt->base_addr->isr_imr);
		tdu_cnt++;
		if ((peth_adapt->callback) != NULL) {
			peth_adapt->callback(EthIntRok, 0);
		}
		peth_adapt->base_addr->isr_imr |= FEMAC_ISR_BIT_RDU;
	}
	// CNT_WRAP
	if (isr_imr.b.isr_cnt_wrap) {
		peth_adapt->base_addr->isr_imr |= FEMAC_ISR_BIT_CNT_WRAP;
	}
	// RER_RUNT
	if (isr_imr.b.isr_rer_runt) {
		peth_adapt->base_addr->isr_imr |= FEMAC_ISR_BIT_RER_RUNT;
		DBG_MII_INFO("Runt pkt\r\n");
	}
	// TER
	if (isr_imr.b.isr_ter) {
		peth_adapt->base_addr->isr_imr |= FEMAC_ISR_BIT_TER;
		DBG_MII_WARN("TER (0x%08X)\r\n", peth_adapt->base_addr->isr_imr);
	}
	// others
	if (((isr_imr.w) & BIT10) ||
		((isr_imr.w) & BIT11) ||
		((isr_imr.w) & BIT12) ||
		((isr_imr.w) & BIT13) ||
		((isr_imr.w) & BIT14) ||
		((isr_imr.w) & BIT15)) {
		DBG_MII_WARN("other ISR (%08X), %08X\r\n", isr_imr.w, peth_adapt->base_addr->isr_imr);
		peth_adapt->base_addr->isr_imr = 0x3D70000
										 | BIT10 | BIT11 | BIT12 | BIT13 | BIT14 | BIT15;
	}

	hal_irq_clear_pending(MII_IRQn);

	__DSB();
	taskYIELD();
}


__weak void hal_eth_otp_lock(void);
__weak void hal_eth_otp_unlock(void);
__weak void hal_eth_otp_lock(void)
{
}
__weak void hal_eth_otp_unlock(void)
{
}


/**
 *  @brief To initialize the Ethernet controller.
 *
 *  @param[in]  N/A
 *
 *  @returns    The result.
 */
#if 0
hal_status_t hal_eth_init(void)
{
	eth_adapter.dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;
	eth_adapter.dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;

	return hal_eth_stubs.hal_eth_init(&eth_adapter);
}
#else
hal_status_t hal_eth_init(void)
{
#if 0
	SYSON_S_TypeDef *syson_s = SYSON_S;
	AON_TypeDef *aon = AON;
	volatile uint32_t val;
#endif
	hal_eth_adapter_t *peth_adapter = &eth_adapter;
	ETHERNET_Type *peth;
	u32 i, start_us;
	u16 tmp;
	u8 rd_data = 0;
#define TIMEOUT_US  100000000


	eth_adapter.dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;
	eth_adapter.dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;

	if (peth_adapter == NULL) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return HAL_ERR_PARA;
	}

	peth_adapt = peth_adapter;
	peth_adapt->base_addr = ETHERNET_BASE;
	peth = peth_adapt->base_addr;

	hal_rtl_eth_irq_reg((irq_handler_t)MII_IRQHandler);
	hal_irq_set_priority(MII_IRQn, MII_IRQPri);

	// enable bandgap
	hal_eth_sys_hw_ctrl(eth_sys_hw_uabg_en, ENABLE);
	hal_delay_us(500);
	// enable bandgap power
	hal_eth_sys_hw_ctrl(eth_sys_hw_uahv_en, ENABLE);
	hal_delay_us(100);
	hal_eth_sys_hw_ctrl(eth_sys_hw_fephy_en, ENABLE);
	hal_eth_sys_hw_ctrl(eth_sys_hw_lx_en, ENABLE);
	hal_eth_sys_hw_ctrl(eth_sys_hw_femac_ip, ENABLE);

	/* disable auto-polling */
	peth->miia_b.disable_auto_polling = 1;
	hal_delay_ms(500);

	/* reset MAC */
	peth->com_b.rst = 1;
	do {
	} while (peth->com_b.rst);

	tmp = hal_eth_rd_phy_reg(FEPHY_REG_PAGE_BC0, FEPHY_REG_ADDR_23);
	tmp = tmp & 0xFF00;
	hal_eth_otp_lock();
	rd_data = hal_otp_byte_rd_syss(0x497);
	hal_eth_otp_unlock();
	if (rd_data & BIT4) {
		// set default idac value = 0x6 (bit[7:4]: idac_fine_mdix, bit[3:0]: idac_fine_mdi)
		hal_eth_wr_phy_reg(FEPHY_REG_PAGE_BC0, FEPHY_REG_ADDR_23, tmp | 0x66);
	} else {
		// load from OTP
		rd_data &= 0xF;
		hal_eth_wr_phy_reg(FEPHY_REG_PAGE_BC0, FEPHY_REG_ADDR_23, tmp | ((rd_data << 4) | rd_data));
	}
	hal_delay_ms(40);  // wait for FEPHY clock stable
	tmp = hal_eth_rd_phy_reg(FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20);
	tmp |= 0x1;  // set bit[0]: fuse_rdy = 1
	hal_eth_wr_phy_reg(FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20, tmp);
	DBG_MII_INFO("Now, FEPHY fuse_rdy= %d\r\n", hal_eth_rd_phy_reg(FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20) & 0x1);
	hal_delay_ms(100);
	// restart AN, clear powerDown state and clear isolation: with Pause flow control ability = 1
	hal_eth_wr_phy_reg(FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_4, 0x05E1);
	hal_eth_wr_phy_reg(FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_0, 0x3300);
	hal_delay_ms(200);
	// check if bit[2:0] phy_status = LAN_ON (0x3)
	tmp = hal_eth_rd_phy_reg(FEPHY_REG_PAGE_A42, FEPHY_REG_ADDR_16);
	DBG_MII_INFO("PHY status = %d\r\n", tmp & 0x7);
	// read PCS status  (for debug info)
	tmp = hal_eth_rd_phy_reg(FEPHY_REG_PAGE_A60, FEPHY_REG_ADDR_16);
	DBG_MII_INFO("pcs_state = %d\r\n", tmp & 0xFF);
	// enable phy mode EEE
	hal_eth_phy_eee_ctrl(ENABLE);

	/* Tx settings */
	peth->ms_b.reg_rmii2mii_en = 0;
	peth->ms_b.refclk_on = 0;  // REFCLK off
	peth->tc_b.ifg = eth_ifg_time_3;
	peth->tc_b.lbk = eth_normal_op;

	/* Rx settings */
	peth->idr0 = ((peth_adapter->mac_id[0]) << 24) | ((peth_adapter->mac_id[1]) << 16) | ((peth_adapter->mac_id[2]) << 8) | (peth_adapter->mac_id[3]);
	peth->idr4 = ((peth_adapter->mac_id[4]) << 24) | ((peth_adapter->mac_id[5]) << 16);
//    peth->rc = 0x3F;  // Accept error/runt/broadcast/multicast packets, etc.
	peth->rc = 0xF;  // Accept broadcast/multicast packets, etc.
	peth->com_b.rxjumbo = 1;  // Support jumbo packet
	peth->etnrxcpu1 = 0x01010100;

	/* I/O command */
	peth->io_cmd1 = 0x31000000;  // Extra desc. format = 011, support 1GB addressing
	peth->io_cmd = 0x40081000;  // short desc. format = 1, Tx & Rx FIFO threshold = 256 bytes

	peth_tx_desc = (hal_eth_tx_desc_t *)(peth_adapter->tx_desc_addr);
	peth_rx_desc = (hal_eth_rx_desc_t *)(peth_adapter->rx_desc_addr);
	peth->txfdp1 = (u32)peth_tx_desc;
	peth->rxfdp1 = (u32)peth_rx_desc;

	peth_tx_pkt_buf = peth_adapter->tx_pkt_buf;
	peth_rx_pkt_buf = peth_adapter->rx_pkt_buf;

	if (peth_adapter->dcache_invalidate_by_addr != NULL) {
		peth_adapter->dcache_invalidate_by_addr((uint32_t *)peth_tx_desc, (int32_t)((peth_adapter->tx_desc_num) * sizeof(hal_eth_tx_desc_t)));
		peth_adapter->dcache_invalidate_by_addr((uint32_t *)peth_rx_desc, (int32_t)((peth_adapter->rx_desc_num) * sizeof(hal_eth_rx_desc_t)));
	}
	/* initialize Tx descriptors */
	for (i = 0; i < (peth_adapter->tx_desc_num); i++) {
		if (i == ((peth_adapter->tx_desc_num) - 1)) {
			peth_tx_desc[i].dw1 = BIT30;
		} else {
			peth_tx_desc[i].dw1 = 0;
		}
		peth_tx_desc[i].addr = (u32)(peth_tx_pkt_buf + (i * ETH_PKT_BUFF_SZ));
		peth_tx_desc[i].dw2 = (eth_vlan_hdr_remove << 25) | (ETH_C_VLAN_HDR & 0xFFFF);
		peth_tx_desc[i].dw3 = 0;
		peth_tx_desc[i].dw4 = 0;
	}

	/* initialize Rx descriptors */
	for (i = 0; i < (peth_adapter->rx_desc_num); i++) {
		if (i == ((peth_adapter->rx_desc_num) - 1)) {
			peth_rx_desc[i].dw1 = BIT31 | BIT30 | ETH_PKT_BUFF_SZ;
		} else {
			peth_rx_desc[i].dw1 = BIT31 | ETH_PKT_BUFF_SZ;
		}
		peth_rx_desc[i].addr = (u32)(peth_rx_pkt_buf + (i * ETH_PKT_BUFF_SZ));
		peth_rx_desc[i].dw2 = 0;
		peth_rx_desc[i].dw3 = 0;
	}
	if (peth_adapter->dcache_clean_by_addr != NULL) {
		peth_adapter->dcache_clean_by_addr((uint32_t *)peth_tx_desc, (int32_t)((peth_adapter->tx_desc_num) * sizeof(hal_eth_tx_desc_t)));
		peth_adapter->dcache_clean_by_addr((uint32_t *)peth_rx_desc, (int32_t)((peth_adapter->rx_desc_num) * sizeof(hal_eth_rx_desc_t)));
	}

	/* enable Tx & Rx */
	peth->io_cmd_b.te = 1;
	peth->io_cmd_b.re = 1;

	/* isr & imr */
	peth_adapt->int_mask = FEMAC_IMR_BIT_TDU | FEMAC_IMR_BIT_LINKCHG
						   | FEMAC_IMR_BIT_TER | FEMAC_IMR_BIT_TOK | FEMAC_IMR_BIT_RER_OVF
						   | FEMAC_IMR_BIT_RER_RUNT | FEMAC_IMR_BIT_CNT_WRAP | FEMAC_IMR_BIT_ROK
						   | 0xFFFF;
	peth->isr_imr = peth_adapt->int_mask;

	/* enable auto-polling */
	peth->miia_b.disable_auto_polling = 0;

	/* Wait MAC's link is up */
	start_us = hal_read_curtime_us();
	do {
		if ((TIMEOUT_US == 0) || ((peth->ms_b.linkb) == eth_link_up)) {
			break;
		} else {
			if ((TIMEOUT_US != HAL_WAIT_FOREVER) && hal_is_timeout(start_us, TIMEOUT_US)) {
				DBG_MII_ERR("Wait MAC's link up timeout !!\r\n");
				return HAL_TIMEOUT;
			} else {
				if (peth_adapter->task_yield != NULL) {
					(peth_adapter->task_yield)();
				}
			}
		}
	} while (1);

	/* Get MAC's link info. */
	switch (((peth->ms) & 0x18000000) >> 27) {
	case eth_speed_100:
		if ((peth->ms_b.fulldupreg) == eth_full_duplex) {
			DBG_MII_INFO("MAC's link info.: 100 Mb/s, Full duplex\r\n");
		} else {
			DBG_MII_INFO("MAC's link info.: 100 Mb/s, Half duplex\r\n");
		}
		break;
	case eth_speed_10:
		if ((peth->ms_b.fulldupreg) == eth_full_duplex) {
			DBG_MII_INFO("MAC's link info.: 10 Mb/s, Full duplex\r\n");
		} else {
			DBG_MII_INFO("MAC's link info.: 10 Mb/s, Half duplex\r\n");
		}
		break;
	default:
		DBG_MII_INFO("MAC's link speed: %d\r\n", ((peth->ms) & 0x1800000) >> 2);
		break;
	}
	DBG_MII_INFO("Link status = %04X\r\n", hal_eth_rd_phy_reg(FEPHY_REG_PAGE_A43, FEPHY_REG_ADDR_26));

	/* enable Rx ring1 */
	peth->io_cmd1_b.rxring1 = 1;


	return HAL_OK;
}
#endif

#if 0
/**
 *  @brief To initialize the Ethernet controller with force speed mode (100Mbps/Full duplex).
 *
 *  @param[in]  if_sel The interface between the MAC and PHY.
 *  @param[in]  pin_sel The pinmux selection.
 *
 *  @returns    The result.
 */
hal_status_t hal_eth_init_force_spd(eth_if_sel_t if_sel, eth_pin_sel_t pin_sel)
{
	hal_status_t ret;
	io_pin_t *pin_list;


	hal_dbg_port_disable();

#if ((CHIP_VER <= CHIP_C_CUT) && (defined(CONFIG_BUILD_RAM)))
	pin_list = (io_pin_t *)&eth_pin_table_patch[(if_sel * 30) + (pin_sel * 15)];
#else
	pin_list = (io_pin_t *)&hal_eth_stubs.eth_pin_table[(if_sel * 30) + (pin_sel * 15)];
#endif
	ret = hal_pinmux_register(pin_list, PID_ETH);
	if (ret == HAL_OK) {
		eth_adapter.dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;
		eth_adapter.dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;
		return hal_eth_init_force_spd_rtl8735b(&eth_adapter, if_sel, pin_sel);
	} else {
		return ret;
	}
}
#endif


/**
 *  @brief To de-initialize the Ethernet controller.
 *
 *  @param None
 *
 *  @returns    void.
 */
void hal_eth_deinit(void)
{
	eth_adapter.dcache_invalidate_by_addr = NULL;
	eth_adapter.dcache_clean_by_addr = NULL;
#if 0
	hal_eth_stubs.hal_eth_deinit(&eth_adapter);
#else
	hal_eth_adapter_t *peth_adapter = &eth_adapter;

	if (peth_adapter == NULL) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}

	// disable FEPHY IP function
	hal_eth_sys_hw_ctrl(eth_sys_hw_fephy_ip, DISABLE);
	/* disable interrupt & clear all pending interrupts */
	peth_adapter->base_addr->isr_imr = 0xFFFF;
	hal_rtl_eth_irq_unreg();
	hal_eth_sys_hw_ctrl(eth_sys_hw_femac_ip, DISABLE);
#endif
}


/**
 *  @brief To write "size" bytes of data from "data" to the Tx packet buffer.
 *
 *  @param[in]  data The buffer of packet data.
 *  @param[in]  size The size of the packet data.
 *
 *  @returns    The number of bytes written, or (-1) if errors.
 */
s32 hal_eth_write_data(u8 *data, u32 size)
{
	return hal_eth_stubs.hal_eth_write_data(&eth_adapter, data, size);
}


/**
 *  @brief To send the packet from Tx packet buffer.
 *
 *  @param None
 *
 *  @returns    The packet size.
 */
u32 hal_eth_send_pkt(void)
{
	return hal_eth_stubs.hal_eth_send_pkt(&eth_adapter);
}


/**
 *  @brief To receive a packet into the Rx packet buffer.
 *
 *  @param None
 *
 *  @returns    The packet size, or 0 if no packet received.
 */
u32 hal_eth_receive_pkt(void)
{
	return hal_eth_stubs.hal_eth_receive_pkt(&eth_adapter);
}


/**
 *  @brief To read packet data from Rx packet buffer to the "data" buffer.
 *
 *  @param[in]  data A buffer for the packet data.
 *  @param[in]  size The specified length (in bytes) to be read.
 *
 *  @returns    The actual size (in bytes) of data read.
 */
u32 hal_eth_read_data(u8 *data, u32 size)
{
	return hal_eth_stubs.hal_eth_read_data(&eth_adapter, data, size);
}


/**
 *  @brief To get the link status.
 *
 *  @param None
 *
 *  @returns    1 for link up, 0 for link down.
 */
u32 hal_eth_get_link_status(void)
{
	return hal_eth_stubs.hal_eth_get_link_status(&eth_adapter);
}


/**
 *  @brief To set the link speed and duplex mode.
 *
 *  @param[in]  speed The specified link speed.
 *  @param[in]  duplex The specifed duplex mode.
 *
 *  @returns    void.
 */
void hal_eth_set_link(s32 speed, s32 duplex)
{
	hal_eth_stubs.hal_eth_set_link(&eth_adapter, speed, duplex);
}


/**
 *  @brief To hook a callback function for Ethernet MAC controller interrupt.
 *
 *  @param[in]  pcallback The callback function.
 *
 *  @returns    void
 */
void hal_eth_callback_hook(eth_callback_t pcallback)
{
	hal_eth_stubs.hal_eth_callback_hook(&eth_adapter, pcallback);
}


/**
 *  @brief To hook a callback function to make OS do a context-switch while waiting.
 *
 *  @param[in]  task_yield The callback function.
 *
 *  @returns    void.
 */
void hal_eth_task_yield_hook(eth_task_yield task_yield)
{
	hal_eth_stubs.hal_eth_task_yield_hook(&eth_adapter, task_yield);
}


/**
 *  @brief To read the specified FEPHY register
 *
 *  @param[in]  page The specified page number.
 *  @param[in]  reg_addr The specified register address.
 *
 *  @returns    The register value.
 */
u16 hal_eth_rd_phy_reg(u16 page, u16 reg_addr)
{
	return hal_eth_stubs.hal_eth_rd_phy_reg(&eth_adapter, page, reg_addr);
}


/**
 *  @brief To write "data" value to the specified FEPHY register
 *
 *  @param[in]  page The specified page number.
 *  @param[in]  reg_addr The specified register address.
 *  @param[in]  data The specified data value.
 *
 *  @returns    0.
 */
u32 hal_eth_wr_phy_reg(u16 page, u16 reg_addr, u16 data)
{
	return hal_eth_stubs.hal_eth_wr_phy_reg(&eth_adapter, page, reg_addr, data);
}


/**
 *  @brief To check the ethernet PHY's state.
 *
 *  @param[in]  void
 *
 *  @returns    void
 */
void hal_eth_detect_phy_state(void)
{
#if 0
	hal_eth_stubs.hal_eth_detect_phy_state(&eth_adapter);
#else
	hal_eth_adapter_t *peth_adapter = &eth_adapter;
	u16 tmp1 = 0;
	u16 tmp2 = 0;
	SYSON_S_TypeDef *syson_s = SYSON_S;
	AON_TypeDef *aon = AON;
	volatile uint32_t val;


	if (peth_adapter == NULL) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}

	// check phy_status
	tmp1 = hal_eth_rd_phy_reg(FEPHY_REG_PAGE_A42, FEPHY_REG_ADDR_16);
	// check fuse_rdy
	tmp2 = hal_eth_rd_phy_reg(FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20);
	if ((tmp1 & 0x7) == 0x1) {
		DBG_MII_WARN("FEPHY fault event detected !\r\n");
		DBG_MII_WARN("phy_status = 0x%X\r\n", (tmp1 & 0x7));
		DBG_MII_WARN("fuse_rdy = 0x%X\r\n", (tmp2 & 0x1));
		/* recover surge fault */
		// enable bandgap
		hal_eth_sys_hw_ctrl(eth_sys_hw_uabg_en, ENABLE);
		hal_delay_us(500);
		// enable bandgap power
		hal_eth_sys_hw_ctrl(eth_sys_hw_uahv_en, ENABLE);
		hal_delay_us(100);
		hal_eth_sys_hw_ctrl(eth_sys_hw_fephy_en, ENABLE);
		hal_delay_ms(45);  // wait for FEPHY clock stable
		hal_eth_wr_phy_reg(FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20, 0x3);  // set bit[0]: fuse_rdy = 1, bit[1]: rg_ext_ini_done = 1
#if 0
		tmp1 = hal_eth_rd_phy_reg(FEPHY_REG_PAGE_A42, FEPHY_REG_ADDR_16);
		if ((tmp1 & 0x7) == 0x3) {
			DBG_MII_INFO("phy_status is LAN_ON...\r\n");
		} else {
			DBG_MII_INFO("phy_status isn't LAN_ON !!\r\n");
		}
#endif
		hal_delay_ms(100);
		// check phy_status
		tmp1 = hal_eth_rd_phy_reg(FEPHY_REG_PAGE_A42, FEPHY_REG_ADDR_16);
		// check fuse_rdy
		tmp2 = hal_eth_rd_phy_reg(FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20);
		DBG_MII_INFO("After phy patch:\r\n");
		DBG_MII_INFO("phy_status = 0x%X\r\n", (tmp1 & 0x7));
		DBG_MII_INFO("fuse_rdy = 0x%X\r\n", (tmp2 & 0x1));
		// restart AN
		hal_eth_wr_phy_reg(FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_0, 0x3300);
		hal_delay_ms(200);
	}
#endif
}


/**
 *  @brief To enable/disable the EEE functionality of FEPHY
 *
 *  @param[in] en  Enable control: 0: disable, 1: enable.
 *
 *  @returns    void
 */
void hal_eth_phy_eee_ctrl(u8 en)
{
	hal_eth_stubs.hal_eth_phy_eee_ctrl(&eth_adapter, en);
}

/** @} */ /* End of group hs_hal_ethernet */


#endif  // end of "#if defined(CONFIG_MII_EN) && (CONFIG_MII_EN == 1)"


