/**************************************************************************//**
 * @file     ethernet_api.c
 * @brief    This file implement the Ethernet HAL API.
 *
 * @version  V1.00
 * @date     2017-06-22
 *
 * @note
 *
 ******************************************************************************
 * @attention
 *
 * Copyright(c) 2007 - 2022 Realtek Corporation. All rights reserved.
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
#include "ethernet_api.h"
#include "ethernet_ex_api.h"
#include "hal_eth.h"



#if defined(CONFIG_MII_EN) && (CONFIG_MII_EN == 1)

void ethernet_irq_hook(ethernet_callback callback)
{
	if (callback == NULL) {
		DBG_MII_ERR("ethernet_irq_hook(): Invalid parameter !!\r\n");
		return;
	}

	hal_eth_callback_hook(callback);
}


void ethernet_task_yield_hook(ethernet_task_yield task_yield)
{
	if (task_yield == NULL) {
		DBG_MII_ERR("ethernet_task_yield_hook(): Invalid parameter !!\r\n");
		return;
	}

	hal_eth_task_yield_hook(task_yield);
}


/* Set the numbers of Tx/Rx descriptor */
void ethernet_set_descnum(uint8_t txdescCnt, uint8_t rxdescCnt)
{
	if ((txdescCnt == 0) || (rxdescCnt == 0)) {
		DBG_MII_ERR("ethernet_set_descnum(): Invalid parameter !!\r\n");
		return;
	}
	if (((txdescCnt * ETH_TX_DESC_SIZE) % 32) || ((rxdescCnt * ETH_RX_DESC_SIZE) % 32)) {
		DBG_MII_ERR("ethernet_set_descnum(): The size of Tx/Rx descriptor ring must be 32-Byte alignment !!\r\n");
		return;
	}

	hal_eth_set_desc_num(txdescCnt, rxdescCnt);
}


/* Set the start address of Tx/Rx descriptor and packet buffer */
void ethernet_trx_pre_setting(uint8_t *TxDescAddr, uint8_t *RxDescAddr, uint8_t *pTxPktBuf, uint8_t *pRxPktBuf)
{
	if ((TxDescAddr == NULL) || (RxDescAddr == NULL) || (pTxPktBuf == NULL) || (pRxPktBuf == NULL)) {
		DBG_MII_ERR("ethernet_trx_pre_setting(): Invalid parameter !!\r\n");
		return;
	}
	if ((((uint32_t)TxDescAddr) & 0x1F) || (((uint32_t)RxDescAddr) & 0x1F) || (((uint32_t)pTxPktBuf) & 0x1F) || (((uint32_t)pRxPktBuf) & 0x1F)) {
		DBG_MII_ERR("ethernet_trx_pre_setting(): The address must be 32-Byte alignment !!\r\n");
		return;
	}

	hal_eth_set_desc_addr(TxDescAddr, RxDescAddr);
	hal_eth_set_pkt_buf(pTxPktBuf, pRxPktBuf);
}


// Set the ethernet address
void ethernet_set_address(char *mac)
{
	if (mac == NULL) {
		DBG_MII_ERR("ethernet_set_address(): Invalid parameter !!\r\n");
		return;
	}

	hal_eth_set_mac_addr((u8 *)mac);
}


void ethernet_detect_phy_state(void)
{
	hal_eth_detect_phy_state();
}


void ethernet_phy_eee_ctrl(uint8_t en)
{
	hal_eth_phy_eee_ctrl(en);
}


int ethernet_init(void)
{
	return hal_eth_init();
}

#if 0
int ethernet_init_force_spd(void)
{
	return hal_eth_init_force_spd(ETH_IF_SEL, ETH_PIN_SEL);
}
#endif

void ethernet_free(void)
{
	hal_eth_deinit();
}


// write size bytes from data to ethernet buffer
// return num bytes written
// or -1 if size is too big
int ethernet_write(const char *data, int size)
{
	if ((data == NULL) || (size == 0)) {
		DBG_MII_ERR("ethernet_write(): Invalid parameter !!\r\n");
		return 0;
	}
	if (size > ETH_PKT_MAX_SIZE) {
		DBG_MII_ERR("ethernet_write(): The size is too big !!\r\n");
		return (-1);
	}

	return hal_eth_write_data((u8 *)data, size);
}


// send ethernet write buffer, returning the packet size sent
int ethernet_send(void)
{
	return hal_eth_send_pkt();
}


// recieve from ethernet buffer, returning packet size, or 0 if no packet
int ethernet_receive(void)
{
	return hal_eth_receive_pkt();
}


// read size bytes in to data, return actual num bytes read (0..size)
// if data == NULL, throw the bytes away
int ethernet_read(char *data, int size)
{
	if ((data == NULL) || (size == 0)) {
		DBG_MII_ERR("ethernet_read(): Invalid parameter !!\r\n");
		return 0;
	}

	return hal_eth_read_data((u8 *)data, size);
}


// get the ethernet address
void ethernet_address(char *mac)
{
	if (mac == NULL) {
		DBG_MII_ERR("ethernet_address(): Invalid parameter !!\r\n");
		return;
	}

	hal_eth_get_mac_addr((u8 *)mac);
}


// see if the link is up
int ethernet_link(void)
{
	return hal_eth_get_link_status();
}


// force link settings
void ethernet_set_link(int speed, int duplex)
{
	hal_eth_set_link(speed, duplex);
}
#endif  // end of "#if defined(CONFIG_MII_EN) && (CONFIG_MII_EN == 1)"



