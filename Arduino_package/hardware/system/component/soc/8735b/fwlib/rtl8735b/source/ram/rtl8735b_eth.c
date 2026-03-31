/*****************************************************************************
 * @file    rtl8735b_eth.c
 * @brief    This file implements the Ethernet HAL functions.
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
#include "cmsis.h"
#include "hal_eth.h"
#include "hal_timer.h"
#include "platform_stdlib.h"
#include "hal_otp.h"



#if defined(CONFIG_MII_EN) && (CONFIG_MII_EN == 1)

//void MII_IRQHandler (void);


/**
 * @addtogroup hs_hal_ethernet ETHERNET
 * @{
 */
/**
  * @brief The global common data structure for Ethernet HAL operations.
  */
hal_eth_adapter_t *peth_adapt;
/**
  * @brief The start address of Tx descriptor ring.
  */
volatile hal_eth_tx_desc_t *peth_tx_desc;
/**
  * @brief The start address of Rx descriptor ring.
  */
volatile hal_eth_rx_desc_t *peth_rx_desc;
/**
  * @brief The start address of Tx packet buffer.
  */
volatile u8 *peth_tx_pkt_buf;
/**
  * @brief The start address of Rx packet buffer.
  */
volatile u8 *peth_rx_pkt_buf;
/**
  * @brief The index of current available Tx descriptor.
  */
volatile u8 eth_tx_desc_wptr = 0;
/**
  * @brief The index of current available Rx descriptor.
  */
volatile u8 eth_rx_desc_rptr = 0;
/**
  * @brief The size of the packet to be transmitted.
  */
volatile u32 curr_data_len = 0;



/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_ethernet_rom_func ETHERNET HAL ROM APIs.
 * @ingroup hs_hal_ethernet
 * @{
 * @brief The ETHERNET HAL ROM APIs. The user application(in RAM space) should not call these APIs directly.
 *        There is another set of ETHERNET HAL APIs in the RAM space is provided for the user application.
 */

/**
  * @brief The stubs functions table to exports ETHERNET HAL functions in ROM.
  */
const hal_eth_func_stubs_t hal_eth_stubs = {
	.hal_eth_irq_unreg = hal_rtl_eth_irq_unreg,
	.hal_eth_set_desc_num = hal_rtl_eth_set_desc_num,
	.hal_eth_set_desc_addr = hal_rtl_eth_set_desc_addr,
	.hal_eth_set_pkt_buf = hal_rtl_eth_set_pkt_buf,
	.hal_eth_set_mac_addr = hal_rtl_eth_set_mac_addr,
	.hal_eth_get_mac_addr = hal_rtl_eth_get_mac_addr,
//    .hal_eth_init = hal_rtl_eth_init,
//    .hal_eth_deinit = hal_rtl_eth_deinit,
	.hal_eth_write_data = hal_rtl_eth_write_data,
	.hal_eth_send_pkt = hal_rtl_eth_send_pkt,
	.hal_eth_receive_pkt = hal_rtl_eth_receive_pkt,
	.hal_eth_read_data = hal_rtl_eth_read_data,
	.hal_eth_get_link_status = hal_rtl_eth_get_link_status,
	.hal_eth_set_link = hal_rtl_eth_set_link,
	.hal_eth_callback_hook = hal_rtl_eth_callback_hook,
	.hal_eth_task_yield_hook = hal_rtl_eth_task_yield_hook,
	.hal_eth_rd_phy_reg = hal_rtl_eth_rd_phy_reg,
	.hal_eth_wr_phy_reg = hal_rtl_eth_wr_phy_reg,
//    .hal_eth_detect_phy_state = hal_rtl_eth_detect_phy_state,
	.hal_eth_phy_eee_ctrl = hal_rtl_eth_phy_eee_ctrl
};


#if 0
void hal_rtl_eth_en_ctrl(u8 en)
{
	SYSON_S_TypeDef *syson_s = SYSON_S;
	volatile uint32_t val;


	if (en == ENABLE) {
		// enable GMAC & GMAC SCLK
		val = syson_s->SYSON_S_REG_SYS_RMII_CTRL;
		val |= SYSON_S_BIT_SYS_RMII_SCLK_GEN | SYSON_S_BIT_SYS_RMII_CLK_EN | SYSON_S_BIT_SYS_RMII_EN;
		syson_s->SYSON_S_REG_SYS_RMII_CTRL = val;
	} else {
		// disable GMAC & GMAC SCLK
		val = syson_s->SYSON_S_REG_SYS_RMII_CTRL;
		val &= ~(SYSON_S_BIT_SYS_RMII_SCLK_GEN | SYSON_S_BIT_SYS_RMII_CLK_EN | SYSON_S_BIT_SYS_RMII_EN);
		syson_s->SYSON_S_REG_SYS_RMII_CTRL = val;
	}
}
#endif

#if 0
void MII_IRQHandler(void)
{
	ethernet_isr_imr_t isr_imr;


	hal_irq_clear_pending(MII_IRQn);

	isr_imr.w = peth_adapt->base_addr->isr_imr;
	if ((isr_imr.b.isr_rok) && ((peth_adapt->int_mask) & BIT16)) {
		peth_adapt->int_mask &= (~BIT16);
//        DBG_MII_INFO("(R)\r\n");
		if ((peth_adapt->callback) != NULL) {
			peth_adapt->callback(EthIntRok, 0);
		}
	}

	if ((isr_imr.b.isr_rer_ovf) && ((peth_adapt->int_mask) & BIT20)) {
		peth_adapt->int_mask &= (~BIT4);
//        DBG_MII_INFO("Rx FIFO overflow\r\n");
	}

	if ((isr_imr.b.isr_tok) && ((peth_adapt->int_mask) & BIT22)) {
//        DBG_MII_INFO("(T)\r\n");
		peth_adapt->int_mask &= (~BIT22);
		if ((peth_adapt->callback) != NULL) {
			peth_adapt->callback(EthTxDone, 0);
		}
	}

	if ((isr_imr.b.isr_linkchg) && ((peth_adapt->int_mask) & BIT24)) {
		if ((peth_adapt->callback) != NULL) {
			if (!(peth_adapt->base_addr->ms_b.linkb)) {
				peth_adapt->callback(EthIntLinkUp, 0);
			} else {
				peth_adapt->callback(EthIntLinkDown, 0);
			}
		}
	}

	peth_adapt->base_addr->isr_imr = (peth_adapt->int_mask) | 0xFFFF;
	__DSB();
}
#endif


void hal_rtl_eth_irq_reg(irq_handler_t irq_handler)
{
	hal_irq_disable(MII_IRQn);
	__ISB();
	// Register Ethernet IRQ handler
	hal_irq_set_vector(MII_IRQn, (uint32_t)irq_handler);
	hal_irq_clear_pending(MII_IRQn);
	hal_irq_enable(MII_IRQn);
}


void hal_rtl_eth_irq_unreg(void)
{
	hal_irq_disable(MII_IRQn);
	__ISB();
	hal_irq_set_vector(MII_IRQn, (uint32_t)NULL);
}


/**
 *  @brief To set the Tx/Rx descriptor number.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  tx_desc_no The specified Tx descriptor number.
 *  @param[in]  rx_desc_no The specified Rx descriptor number.
 *
 *  @returns    void.
 */
void hal_rtl_eth_set_desc_num(hal_eth_adapter_t *peth_adapter, u8 tx_desc_no, u8 rx_desc_no)
{
	if ((peth_adapter == NULL) || (tx_desc_no == 0) || (rx_desc_no == 0)) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}
	if (((tx_desc_no * sizeof(hal_eth_tx_desc_t)) % 32) || ((rx_desc_no * sizeof(hal_eth_rx_desc_t)) % 32)) {
		DBG_MII_ERR("The size of Tx/Rx descriptor ring must be 32-Byte alignment !!\r\n");
		return;
	}

	peth_adapter->tx_desc_num = tx_desc_no;
	peth_adapter->rx_desc_num = rx_desc_no;
}


/**
 *  @brief To set the start address of Tx/Rx descriptor ring.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  tx_desc The start address of Tx descriptor ring.
 *  @param[in]  rx_desc The start address of Rx descriptor ring.
 *
 *  @returns    void.
 */
void hal_rtl_eth_set_desc_addr(hal_eth_adapter_t *peth_adapter, u8 *tx_desc, u8 *rx_desc)
{
	if ((peth_adapter == NULL) || (tx_desc == NULL) || (rx_desc == NULL)) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}
	if ((((u32)tx_desc) & 0x1F) || (((u32)rx_desc) & 0x1F)) {
		DBG_MII_ERR("The descriptor address must be 32-Byte alignment !!\r\n");
		return;
	}

	peth_adapter->tx_desc_addr = tx_desc;
	peth_adapter->rx_desc_addr = rx_desc;
}


/**
 *  @brief To set the start address of Tx/Rx packet buffer.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  tx_pkt_buf The start address of Tx packet buffer.
 *  @param[in]  rx_pkt_buf The start address of Rx packet buffer.
 *
 *  @returns    void.
 */
void hal_rtl_eth_set_pkt_buf(hal_eth_adapter_t *peth_adapter, u8 *tx_pkt_buf, u8 *rx_pkt_buf)
{
	if ((peth_adapter == NULL) || (tx_pkt_buf == NULL) || (rx_pkt_buf == NULL)) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}
	if ((((u32)tx_pkt_buf) & 0x1F) || (((u32)rx_pkt_buf) & 0x1F)) {
		DBG_MII_ERR("The packet buffer address must be 32-Byte alignment !!\r\n");
		return;
	}

	peth_adapter->tx_pkt_buf = tx_pkt_buf;
	peth_adapter->rx_pkt_buf = rx_pkt_buf;
}


/**
 *  @brief To set the ethernet MAC address.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  addr The specified MAC address.
 *
 *  @returns    void.
 */
void hal_rtl_eth_set_mac_addr(hal_eth_adapter_t *peth_adapter, u8 *addr)
{
	if ((peth_adapter == NULL) || (addr == NULL)) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}

	memcpy((void *)(peth_adapter->mac_id), addr, ETH_MAC_ADDR_LEN);
}


/**
 *  @brief To get the ethernet MAC address.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  addr The buffer of MAC address.
 *
 *  @returns    void.
 */
void hal_rtl_eth_get_mac_addr(hal_eth_adapter_t *peth_adapter, u8 *addr)
{
	if ((peth_adapter == NULL) || (addr == NULL)) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}

	memcpy((void *)addr, peth_adapter->mac_id, ETH_MAC_ADDR_LEN);
}

#if 0
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
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  if_sel The interface between the MAC and PHY.
 *  @param[in]  pin_sel The pinmux selection.
 *
 *  @returns    The result.
 */
hal_status_t hal_rtl_eth_init(hal_eth_adapter_t *peth_adapter)
{
	SYSON_S_TypeDef *syson_s = SYSON_S;
	AON_TypeDef *aon = AON;
	volatile uint32_t val;
	ETHERNET_Type *peth;
	u32 i, start_us;
	u16 tmp;
	u8 rd_data = 0;
#define TIMEOUT_US  100000000


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
	val = syson_s->SYSON_S_REG_SYS_OTG_CTRL;
	val |= SYSON_S_BIT_SYS_UABG_EN;
	syson_s->SYSON_S_REG_SYS_OTG_CTRL = val;
	hal_delay_us(500);
	// enable bandgap power
	val = syson_s->SYSON_S_REG_SYS_OTG_CTRL;
	val |= SYSON_S_BIT_SYS_UAHV_EN;
	syson_s->SYSON_S_REG_SYS_OTG_CTRL = val;
	hal_delay_us(100);
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
	// enable LX bus & LX bus clock
	val = syson_s->SYSON_S_REG_SYS_PLATFORM_CTRL0;
	val |= SYSON_S_BIT_LXBUS_CLK_EN | SYSON_S_BIT_LXBUS_EN;
	syson_s->SYSON_S_REG_SYS_PLATFORM_CTRL0 = val;

	hal_rtl_eth_en_ctrl(ENABLE);

	/* disable auto-polling */
	peth->miia_b.disable_auto_polling = 1;
	hal_delay_ms(500);

	/* reset MAC */
	peth->com_b.rst = 1;
	do {
	} while (peth->com_b.rst);

	tmp = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_BC0, FEPHY_REG_ADDR_23);
	tmp = tmp & 0xFF00;
	hal_eth_otp_lock();
	rd_data = hal_otp_byte_rd_syss(0x497);
	hal_eth_otp_unlock();
	if (rd_data & BIT4) {
		// set default idac value = 0x6 (bit[7:4]: idac_fine_mdix, bit[3:0]: idac_fine_mdi)
		hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_BC0, FEPHY_REG_ADDR_23, tmp | 0x66);
	} else {
		// load from OTP
		rd_data &= 0xF;
		hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_BC0, FEPHY_REG_ADDR_23, tmp | ((rd_data << 4) | rd_data));
	}
	hal_delay_ms(40);  // wait for FEPHY clock stable
	tmp = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20);
	tmp |= 0x1;  // set bit[0]: fuse_rdy = 1
	hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20, tmp);
	DBG_MII_INFO("Now, FEPHY fuse_rdy= %d\r\n", hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20) & 0x1);
	hal_delay_ms(100);
	// restart AN, clear powerDown state and clear isolation: with Pause flow control ability = 1
	hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_4, 0x05E1);
	hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_0, 0x3300);
	hal_delay_ms(200);
	// check if bit[2:0] phy_status = LAN_ON (0x3)
	tmp = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A42, FEPHY_REG_ADDR_16);
	DBG_MII_INFO("PHY status = %d\r\n", tmp & 0x7);
	// read PCS status  (for debug info)
	tmp = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A60, FEPHY_REG_ADDR_16);
	DBG_MII_INFO("pcs_state = %d\r\n", tmp & 0xFF);
	// enable phy mode EEE
	hal_rtl_eth_phy_eee_ctrl(peth_adapter, ENABLE);

	/* Tx settings */
	peth->ms_b.reg_rmii2mii_en = 0;
	peth->ms_b.refclk_on = 0;  // REFCLK off
	peth->tc_b.ifg = eth_ifg_time_3;
	peth->tc_b.lbk = eth_normal_op;

	/* Rx settings */
	peth->idr0 = ((peth_adapter->mac_id[0]) << 24) | ((peth_adapter->mac_id[1]) << 16) | ((peth_adapter->mac_id[2]) << 8) | (peth_adapter->mac_id[3]);
	peth->idr4 = ((peth_adapter->mac_id[4]) << 24) | ((peth_adapter->mac_id[5]) << 16);
	peth->rc = 0x3F;  // Accept error/runt/broadcast/multicast packets, etc.
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

	/* initialize Tx descriptors */
	for (i = 0; i < (peth_adapter->tx_desc_num); i++) {
		if (i == ((peth_adapter->tx_desc_num) - 1)) {
			peth_tx_desc[i].dw1 = BIT30;
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
	peth_adapt->int_mask = BIT24 | BIT22 | BIT20 | BIT16 | 0xFFFF;
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
	DBG_MII_INFO("Link status = %04X\r\n", hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A43, FEPHY_REG_ADDR_26));

	/* enable Rx ring1 */
	peth->io_cmd1_b.rxring1 = 1;


	return HAL_OK;
}


/**
 *  @brief To de-initialize the Ethernet controller.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *
 *  @returns    void.
 */
void hal_rtl_eth_deinit(hal_eth_adapter_t *peth_adapter)
{
	AON_TypeDef *aon = AON;
	volatile uint32_t val;


	if (peth_adapter == NULL) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}

	// disable FEPHY IP function
	val = aon->AON_REG_AON_ISO_CTRL;
	val &= ~(AON_BIT_FEPHY_RSTB_L);
	aon->AON_REG_AON_ISO_CTRL = val;
	/* disable interrupt & clear all pending interrupts */
	peth_adapter->base_addr->isr_imr = 0xFFFF;
	hal_rtl_eth_irq_unreg();
	hal_rtl_eth_en_ctrl(DISABLE);
}
#endif


/**
 *  @brief To write "size" bytes of data from "data" to the Tx packet buffer.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  data The buffer of packet data.
 *  @param[in]  size The size of the packet data.
 *
 *  @returns    The number of bytes written, or (-1) if errors.
 */
s32 hal_rtl_eth_write_data(hal_eth_adapter_t *peth_adapter, u8 *data, u32 size)
{
	ETHERNET_Type *peth;
	u32 wait_us = 0;
	u32 dw1 = 0;
//    u8 tx_serach_idx = eth_tx_desc_wptr;


	if ((peth_adapter == NULL) || (data == NULL) || (size == 0)) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return -1;
	}
	if (((u32)data) & 0x1F) {
		DBG_MII_ERR("The data buffer address must be 32-Byte alignment !!\r\n");
		return -1;
	}

	peth = peth_adapter->base_addr;

	// wait until OWN bit = 0
	peth_tx_desc = (hal_eth_tx_desc_t *)(peth_adapt->tx_desc_addr);
	peth_adapter->dcache_invalidate_by_addr((u32 *)peth_tx_desc, 64);
	if ((((volatile u32)(peth_tx_desc[0].dw1)) & BIT31) != 0) {	// OWN bit == 1
		while (1) {
			peth_adapter->dcache_invalidate_by_addr((u32 *)peth_tx_desc, 64);
			if ((((volatile u32)(peth_tx_desc[0].dw1)) & BIT31) == 0) { // OWN bit == 0
				break;
			}
			hal_delay_us(100);
			wait_us++;
			if (wait_us > 100) {
				DBG_MII_WARN("wait Tx desc own bit timeout !!\r\n");
				break;
			}
		}
	}

	// CPU uses peth_tx_desc
	if (peth_adapter->dcache_invalidate_by_addr != NULL) {
		peth_adapter->dcache_invalidate_by_addr((uint32_t *)peth_tx_desc, (int32_t)((peth_adapter->tx_desc_num) * sizeof(hal_eth_tx_desc_t)));
	}
	/* check if current Tx descriptor is available */
	dw1 = ((volatile u32)(peth_tx_desc[0].dw1));
	if ((dw1 & BIT31) == 0) {
		peth_adapter->dcache_clean_by_addr((uint32_t *)data, size);

		peth_tx_desc[0].dw1 = (BIT31 | BIT30 | BIT29 | BIT28 | BIT23 | size);
		peth_tx_desc[0].addr = (u32)data;
		peth_tx_desc[0].dw2 = (eth_vlan_hdr_remove << 25) | (ETH_C_VLAN_HDR & 0xFFFF);
		peth_tx_desc[0].dw3 = 0;
		peth_tx_desc[0].dw4 = 0;

		if (peth_adapter->dcache_clean_by_addr != NULL) {
			peth_adapter->dcache_clean_by_addr((uint32_t *)peth_tx_desc, (int32_t)((peth_adapter->tx_desc_num) * sizeof(hal_eth_tx_desc_t)));
		}

		curr_data_len += size;
	} else {
#if 0
		if (peth_adapter->dcache_clean_by_addr != NULL) {
			peth_adapter->dcache_clean_by_addr((uint32_t *)peth_tx_pkt_buf, (int32_t)((peth_adapter->tx_desc_num) * ETH_PKT_BUFF_SZ));
			peth_adapter->dcache_clean_by_addr((uint32_t *)peth_tx_desc, (int32_t)((peth_adapter->tx_desc_num) * sizeof(hal_eth_tx_desc_t)));
		}

		peth_adapt->int_mask |= BIT22;
		peth->isr_imr = peth_adapt->int_mask;
		/* enable Tx ring1 */
		peth->io_cmd_b.txfn1st = 1;
#endif
		DBG_MII_WARN("Tx descriptor ring is full !! (dw1 = 0x%08X\r\n", dw1);

#if 0
		dbg_printf("0x1300 = 0x%08X\r\n", peth->txfdp1);
		dbg_printf("0x1304 = 0x%08X\r\n", peth->txcdo1);

		u32 i = 0;
		for (i = 0; i < 1; i++) {
			dbg_printf("Tx desc %d\r\n", i);
			dbg_printf("dw1 = 0x%08X\r\n", peth_tx_desc[i].dw1);
			dbg_printf("addr = 0x%08X\r\n", peth_tx_desc[i].addr);
			dbg_printf("dw2 = 0x%08X\r\n", peth_tx_desc[i].dw2);
			dbg_printf("dw3 = 0x%08X\r\n", peth_tx_desc[i].dw3);
			dbg_printf("dw4 = 0x%08X\r\n", peth_tx_desc[i].dw4);
		}
#endif

		return 0;
	}


	return size;
}


/**
 *  @brief To send the packet from Tx packet buffer.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *
 *  @returns    The packet size.
 */
u32 hal_rtl_eth_send_pkt(hal_eth_adapter_t *peth_adapter)
{
	ETHERNET_Type *peth = peth_adapter->base_addr;
	u32 size = curr_data_len;


	peth->io_cmd_b.txfn1st = 1;
	curr_data_len = 0;


	return size;
}


/**
 *  @brief To receive a packet into the Rx packet buffer.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *
 *  @returns    The packet size, or 0 if no packet received.
 */
u32 hal_rtl_eth_receive_pkt(hal_eth_adapter_t *peth_adapter)
{
	ETHERNET_Type *peth = peth_adapter->base_addr;
	u32 rx_len = 0;
	u8 rx_serach_idx = eth_rx_desc_rptr;


	// D-Cache sync (Invalidate)
	if (peth_adapter->dcache_invalidate_by_addr != NULL) {
		peth_adapter->dcache_invalidate_by_addr((uint32_t *)peth_rx_desc, (int32_t)((peth_adapter->rx_desc_num) * sizeof(hal_eth_rx_desc_t)));
	}

	/* check if current Rx descriptor is available */
	if ((((volatile u32)(peth_rx_desc[rx_serach_idx].dw1)) & BIT31) == 0) {
		rx_len = (peth_rx_desc[rx_serach_idx].dw1) & 0xFFF;
	} else {
//        peth_adapt->int_mask |= (BIT16 | BIT4);
//        peth->isr_imr = peth_adapt->int_mask;

		return 0;
	}


	return rx_len;
}


/**
 *  @brief To read packet data from Rx packet buffer to the "data" buffer.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  data A buffer for the packet data.
 *  @param[in]  size The specified length (in bytes) to be read.
 *
 *  @returns    The actual size (in bytes) of data read.
 */
u32 hal_rtl_eth_read_data(hal_eth_adapter_t *peth_adapter, u8 *data, u32 size)
{
	ETHERNET_Type *peth;
	u8 read_idx = eth_rx_desc_rptr;


	if ((peth_adapter == NULL) || (data == NULL) || (size == 0)) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return 0;
	}
	peth = peth_adapter->base_addr;

	// D-Cache sync (Invalidate)
	if (peth_adapter->dcache_invalidate_by_addr != NULL) {
		peth_adapter->dcache_invalidate_by_addr((uint32_t *)(peth_rx_desc[read_idx].addr), (int32_t)ETH_PKT_BUFF_SZ);
	}
	memcpy((void *)data, (void *)((peth_rx_desc[read_idx].addr) + 2), size);

	if (read_idx == ((peth_adapter->rx_desc_num) - 1)) {
		peth_rx_desc[read_idx].dw1 = BIT31 | BIT30 | ETH_PKT_BUFF_SZ;
	} else {
		peth_rx_desc[read_idx].dw1 = BIT31 | ETH_PKT_BUFF_SZ;
	}
	peth_rx_desc[read_idx].dw2 = 0;
	peth_rx_desc[read_idx].dw3 = 0;
	if (peth_adapter->dcache_clean_by_addr != NULL) {
		peth_adapter->dcache_clean_by_addr((uint32_t *)peth_rx_desc, (int32_t)((peth_adapter->rx_desc_num) * sizeof(hal_eth_rx_desc_t)));
	}

	if (read_idx == ((peth_adapter->rx_desc_num) - 1)) {
		eth_rx_desc_rptr = 0;
	} else {
		eth_rx_desc_rptr++;
	}

	peth_adapt->int_mask |= BIT16;
	peth->isr_imr = peth_adapt->int_mask;
	peth->io_cmd1_b.rxring1 = 1;  // enable Rx ring1


	return size;
}


/**
 *  @brief To get the link status.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *
 *  @returns    1 for link up, 0 for link down.
 */
u32 hal_rtl_eth_get_link_status(hal_eth_adapter_t *peth_adapter)
{
	ETHERNET_Type *peth = peth_adapter->base_addr;


	if ((peth->ms_b.linkb) == eth_link_up) {
		return 1;
	} else {
		return 0;
	}
}


/**
 *  @brief To set the link speed and duplex mode.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  speed The specified link speed.
 *  @param[in]  duplex The specifed duplex mode.
 *
 *  @returns    void.
 */
void hal_rtl_eth_set_link(hal_eth_adapter_t *peth_adapter, s32 speed, s32 duplex)
{
	ETHERNET_Type *peth;


	if (peth_adapter == NULL) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}
	peth = peth_adapter->base_addr;

	switch (speed) {
	case 1:
		if (duplex == eth_full_duplex) {
			hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_4, 0x05E1);  // force link at 100F
		} else {
			hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_4, 0x04E1);  // force link at 100H
		}
		break;
	case 0:
		if (duplex == eth_full_duplex) {
			hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_4, 0x0461);  // force link at 10F
		} else {
			hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_4, 0x0421);  // force link at 10H
		}
		break;
	default:
		break;
	}
	hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_0, 0x3300);  // restart AN
	hal_delay_ms(4000);
	DBG_MII_INFO("Link status = %04X\r\n", hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A43, FEPHY_REG_ADDR_26));

#if 0
	/* Get MAC's link info. */
	switch (((peth->ms) & 0x18000000) >> 27) {
	case eth_speed_100:
		if ((peth->ms_b.fulldupreg) == eth_full_duplex) {
			dbg_printf("MAC's link info.: 100 Mb/s, Full duplex\r\n");
		} else {
			dbg_printf("MAC's link info.: 100 Mb/s, Half duplex\r\n");
		}
		break;
	case eth_speed_10:
		if ((peth->ms_b.fulldupreg) == eth_full_duplex) {
			dbg_printf("MAC's link info.: 10 Mb/s, Full duplex\r\n");
		} else {
			dbg_printf("MAC's link info.: 10 Mb/s, Half duplex\r\n");
		}
		break;
	default:
		dbg_printf("MAC's link speed: %d\r\n", ((peth->ms) & 0x1800000) >> 2);
		break;
	}
#endif
}


/**
 *  @brief To hook a callback function for Ethernet MAC controller interrupt.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  pcallback The callback function.
 *
 *  @returns    void
 */
void hal_rtl_eth_callback_hook(hal_eth_adapter_t *peth_adapter, eth_callback_t pcallback)
{
	if ((peth_adapter == NULL) || (pcallback == NULL)) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}

	peth_adapter->callback = pcallback;
}


/**
 *  @brief To hook a callback function to make OS do a context-switch while waiting.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  task_yield The callback function.
 *
 *  @returns    void.
 */
void hal_rtl_eth_task_yield_hook(hal_eth_adapter_t *peth_adapter, eth_task_yield task_yield)
{
	if ((peth_adapter == NULL) || (task_yield == NULL)) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}

	peth_adapter->task_yield = task_yield;
}


/**
 *  @brief To read the specified FEPHY register
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  page The specified page number.
 *  @param[in]  reg_addr The specified register address.
 *
 *  @returns    The register value.
 */
u16 hal_rtl_eth_rd_phy_reg(hal_eth_adapter_t *peth_adapter, u16 page, u16 reg_addr)
{
	u8 phy_id = (u8)((HAL_READ32(SYSON_S_BASE, 0x100) >> 8) & 0x1F);
	u32 i = 0;
	u16 rd_data = 0;


	if (reg_addr > 0x1F) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return 0;
	}

	if (page > 0) {
		// Switch to the specified page by register 31
		HAL_WRITE32(ETHERNET_BASE, 0x5C, (1 << 31) | (phy_id << 26) | (0x1F << 16) | page);
		hal_delay_us(70);  // wait for command complete
		while (HAL_READ32(ETHERNET_BASE, 0x5C) & (BIT31 | BIT25)) {
			hal_delay_us(1);
			i++;
			if (i > ETH_TIMEOUT_CNT_MAX) {
				DBG_MII_ERR("W operation timeout !! (0x5C = %08X)\r\n", HAL_READ32(ETHERNET_BASE, 0x5C));
				break;
			}
		}
	}

	i = 0;
	HAL_WRITE32(ETHERNET_BASE, 0x5C, (0 << 31) | (phy_id << 26) | (reg_addr << 16));
	hal_delay_us(70);  // wait for command complete
	while ((HAL_READ32(ETHERNET_BASE, 0x5C) & BIT25) || ((HAL_READ32(ETHERNET_BASE, 0x5C) & BIT31) == 0)) {
		hal_delay_us(1);
		i++;
		if (i > ETH_TIMEOUT_CNT_MAX) {
			DBG_MII_ERR("R operation timeout !! (0x5C = %08X)\r\n", HAL_READ32(ETHERNET_BASE, 0x5C));
			break;
		}
	}
	rd_data = (u16)(HAL_READ32(ETHERNET_BASE, 0x5C) & 0xFFFF);

	if (page > 0) {
		// Switch to page 0
		i = 0;
		HAL_WRITE32(ETHERNET_BASE, 0x5C, (1 << 31) | (phy_id << 26) | (0x1F << 16));
		hal_delay_us(70);  // wait for command complete
		while (HAL_READ32(ETHERNET_BASE, 0x5C) & (BIT31 | BIT25)) {
			hal_delay_us(1);
			i++;
			if (i > ETH_TIMEOUT_CNT_MAX) {
				DBG_MII_ERR("W operation timeout !! (0x5C = %08X)\r\n", HAL_READ32(ETHERNET_BASE, 0x5C));
				break;
			}
		}
	}


	return rd_data;
}


/**
 *  @brief To write "data" value to the specified FEPHY register
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in]  page The specified page number.
 *  @param[in]  reg_addr The specified register address.
 *  @param[in]  data The specified data value.
 *
 *  @returns    0.
 */
u32 hal_rtl_eth_wr_phy_reg(hal_eth_adapter_t *peth_adapter, u16 page, u16 reg_addr, u16 data)
{
	u8 phy_id = (u8)((HAL_READ32(SYSON_S_BASE, 0x100) >> 8) & 0x1F);
	u32 i = 0;


	if (reg_addr > 0x1F) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return 0;
	}

	if (page > 0) {
		// Switch to the specified page by register 31
		HAL_WRITE32(ETHERNET_BASE, 0x5C, (1 << 31) | (phy_id << 26) | (0x1F << 16) | page);
		hal_delay_us(70);  // wait for command complete
		while (HAL_READ32(ETHERNET_BASE, 0x5C) & (BIT31 | BIT25)) {
			hal_delay_us(1);
			i++;
			if (i > ETH_TIMEOUT_CNT_MAX) {
				DBG_MII_ERR("W operation timeout_a !! (0x5C = %08X)\r\n", HAL_READ32(ETHERNET_BASE, 0x5C));
				break;
			}
		}
	}

	i = 0;
	HAL_WRITE32(ETHERNET_BASE, 0x5C, (1 << 31) | (phy_id << 26) | (reg_addr << 16) | data);
	hal_delay_us(70);  // wait for command complete
	while (HAL_READ32(ETHERNET_BASE, 0x5C) & (BIT31 | BIT25)) {
		hal_delay_us(1);
		i++;
		if (i > ETH_TIMEOUT_CNT_MAX) {
			DBG_MII_ERR("W operation timeout_b !! (0x5C = %08X)\r\n", HAL_READ32(ETHERNET_BASE, 0x5C));
			break;
		}
	}

	if (page > 0) {
		// Switch to page 0
		i = 0;
		HAL_WRITE32(ETHERNET_BASE, 0x5C, (1 << 31) | (phy_id << 26) | (0x1F << 16));
		hal_delay_us(70);  // wait for command complete
		while (HAL_READ32(ETHERNET_BASE, 0x5C) & (BIT31 | BIT25)) {
			hal_delay_us(1);
			i++;
			if (i > ETH_TIMEOUT_CNT_MAX) {
				DBG_MII_ERR("W operation timeout_c !! (0x5C = %08X)\r\n", HAL_READ32(ETHERNET_BASE, 0x5C));
				break;
			}
		}
	}


	return 0;
}

#if 0
/**
 *  @brief To check the ethernet PHY's state.
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *
 *  @returns    void
 */
void hal_rtl_eth_detect_phy_state(hal_eth_adapter_t *peth_adapter)
{
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
	tmp1 = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A42, FEPHY_REG_ADDR_16);
	// check fuse_rdy
	tmp2 = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20);
	if ((tmp1 & 0x7) == 0x1) {
		DBG_MII_WARN("FEPHY fault event detected !\r\n");
		DBG_MII_WARN("phy_status = 0x%X\r\n", (tmp1 & 0x7));
		DBG_MII_WARN("fuse_rdy = 0x%X\r\n", (tmp2 & 0x1));
		/* recover surge fault */
		// enable bandgap
		val = syson_s->SYSON_S_REG_SYS_OTG_CTRL;
		val |= SYSON_S_BIT_SYS_UABG_EN;
		syson_s->SYSON_S_REG_SYS_OTG_CTRL = val;
		hal_delay_us(500);
		// enable bandgap power
		val = syson_s->SYSON_S_REG_SYS_OTG_CTRL;
		val |= SYSON_S_BIT_SYS_UAHV_EN;
		syson_s->SYSON_S_REG_SYS_OTG_CTRL = val;
		hal_delay_us(100);
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

		hal_delay_ms(45);  // wait for FEPHY clock stable
		hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20, 0x3);  // set bit[0]: fuse_rdy = 1, bit[1]: rg_ext_ini_done = 1
#if 0
		tmp1 = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A42, FEPHY_REG_ADDR_16);
		if ((tmp1 & 0x7) == 0x3) {
			DBG_MII_INFO("phy_status is LAN_ON...\r\n");
		} else {
			DBG_MII_INFO("phy_status isn't LAN_ON !!\r\n");
		}
#endif
		hal_delay_ms(100);
		// check phy_status
		tmp1 = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A42, FEPHY_REG_ADDR_16);
		// check fuse_rdy
		tmp2 = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A46, FEPHY_REG_ADDR_20);
		DBG_MII_INFO("After phy patch:\r\n");
		DBG_MII_INFO("phy_status = 0x%X\r\n", (tmp1 & 0x7));
		DBG_MII_INFO("fuse_rdy = 0x%X\r\n", (tmp2 & 0x1));
		// restart AN
		hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_0, 0x3300);
		hal_delay_ms(200);
	}
}
#endif

/**
 *  @brief To enable/disable the EEE functionality of FEPHY
 *
 *  @param[in]  peth_adapter The ETHERNET adapter.
 *  @param[in] en  Enable control: 0: disable, 1: enable.
 *
 *  @returns    void
 */
void hal_rtl_eth_phy_eee_ctrl(hal_eth_adapter_t *peth_adapter, u8 en)
{
	u16 tmp = 0;


	if (peth_adapter == NULL) {
		DBG_MII_ERR("Invalid parameter !!\r\n");
		return;
	}

	// enable phy mode EEE
	if (en) {
		tmp = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A43, FEPHY_REG_ADDR_17);
		hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A43, FEPHY_REG_ADDR_17, tmp | 0x20);
	} else {
		tmp = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A43, FEPHY_REG_ADDR_17);
		hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A43, FEPHY_REG_ADDR_17, tmp & (~(0x20)));
	}

	// enable MMD reg 100M EEE ability
	hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A41, FEPHY_REG_ADDR_13, 0x7);
	hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A41, FEPHY_REG_ADDR_14, 0x3C);
	hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A41, FEPHY_REG_ADDR_13, 0x4007);
	if (en) {
		tmp = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A41, FEPHY_REG_ADDR_14);
		tmp = tmp & 0xFFF9;
		hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A41, FEPHY_REG_ADDR_14, tmp | 0x2);
	} else {
		tmp = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A41, FEPHY_REG_ADDR_14);
		tmp = tmp & 0xFFF9;
		hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A41, FEPHY_REG_ADDR_14, tmp);
	}

	// restart AN
	tmp = hal_rtl_eth_rd_phy_reg(peth_adapter, FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_0);
	hal_rtl_eth_wr_phy_reg(peth_adapter, FEPHY_REG_PAGE_A40, FEPHY_REG_ADDR_0, tmp | 0x1200);
	hal_delay_ms(200);
}


/** @} */ /* End of group hs_hal_ethernet_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/** @} */ /* End of group hs_hal_ethernet */
#endif  // end of "#if defined(CONFIG_MII_EN) && (CONFIG_MII_EN == 1)"


