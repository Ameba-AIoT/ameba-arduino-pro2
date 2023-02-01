/**************************************************************************//**
 * @file    hal_eth.h
 * @brief   The HAL API implementation for Ethernet MAC controller
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
#ifndef _HAL_ETH_H_
#define _HAL_ETH_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hal_ethernet ETHERNET
 * @{
 * brief The ETHERNET HAL RAM APIs. These APIs is provided for user application to control the Ethernet MAC hardware.
 */

#if defined(CONFIG_MII_EN) && (CONFIG_MII_EN == 1)
void hal_eth_irq_unreg(void);
void hal_eth_set_mac_addr(u8 *addr);
void hal_eth_get_mac_addr(u8 *addr);
void hal_eth_set_desc_num(u8 tx_desc_no, u8 rx_desc_no);
void hal_eth_set_desc_addr(u8 *tx_desc, u8 *rx_desc);
void hal_eth_set_pkt_buf(u8 *tx_pkt_buf, u8 *rx_pkt_buf);
hal_status_t hal_eth_init(void);
void hal_eth_deinit(void);
s32 hal_eth_write_data(u8 *data, u32 size);
u32 hal_eth_send_pkt(void);
u32 hal_eth_receive_pkt(void);
u32 hal_eth_read_data(u8 *data, u32 size);
u32 hal_eth_get_link_status(void);
void hal_eth_set_link(s32 speed, s32 duplex);
void hal_eth_callback_hook(eth_callback_t pcallback);
void hal_eth_task_yield_hook(eth_task_yield task_yield);
u16 hal_eth_rd_phy_reg(u16 page, u16 reg_addr);
u32 hal_eth_wr_phy_reg(u16 page, u16 reg_addr, u16 data);
void hal_eth_detect_phy_state(void);
void hal_eth_phy_eee_ctrl(u8 en);
#endif
/** @} */ /* End of group hal_ethernet */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_ETH_H_"


