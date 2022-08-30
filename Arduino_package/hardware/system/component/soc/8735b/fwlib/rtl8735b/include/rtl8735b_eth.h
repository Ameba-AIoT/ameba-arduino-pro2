/**************************************************************************//**
 * @file    rtl8735b_eth.h
 * @brief    The HAL related definition and macros for Ethernet MAC controller.
 *           Includes Registers and data type definition.
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
#ifndef _RTL8735B_ETH_H_
#define _RTL8735B_ETH_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_ethernet ETHERNET
 * @ingroup 8735bh_hal
 * @{
 * @brief The ETHERNET HAL module of the HS platform.
 */

#include "rtl8735b_eth_type.h"


/// Defines the packet buffer size
#define ETH_PKT_BUFF_SZ                 1600
/// Defines the MAC address length
#define ETH_MAC_ADDR_LEN                6

/// Defines the delay period when checking the own bit of the Tx/Rx descriptors
#define ETH_OWN_BIT_UPDATE_PERIOD       10
/// Defines the max. timeout value when checking the flag of MDIO operations
#define ETH_TIMEOUT_CNT_MAX             1000000

/// Defines the usage of Ethernet PHY 8201F
#define ETH_PHY_8201F_USE               1
/// Defines the PHY address
#define ETH_PHY_ADDR                    0x1

/// Defines the header of vlantag (ctag)
#define ETH_C_VLAN_HDR                  0x8100279F
/// Defines the header of vlantag (stag)
#define ETH_S_VLAN_HDR                  0x88A8279F

/// Defines the address of PHY register 0
#define ETH_PHY_REG0_ADDR               0x0
/// Defines the address of PHY register 1
#define ETH_PHY_REG1_ADDR               0x1
/// Defines the address of PHY register 31
/// Defines the address of PHY register 2
#define ETH_PHY_REG2_ADDR               0x2

#define ETH_PHY_REG31_ADDR              0x1F
/// Defines the default value when reading PHY's register
#define ETH_PHY_REG_DEFAULT_VALUE       0x0

/// Defines the bit definition of PHY register 0
#define ETH_PHY_SPEED_MSB               BIT6
#define ETH_PHY_DUPLEX_MODE             BIT8
#define ETH_PHY_RESTART_NWAY            BIT9
#define ETH_PHY_NWAY_EN                 BIT12
#define ETH_PHY_SPEED_LSB               BIT13
#define ETH_PHY_SW_RESET                BIT15

/// Defines the bit definition of PHY register 1
#define ETH_PHY_LINK_STATUS             BIT2
#define ETH_PHY_NWAY_COMPLETE           BIT5



/**
  \brief  Defines Ethernet pinmux selection.
*/
enum  eth_pin_sel_e {
	EthPinSel0      = 0,
	EthPinSel1      = 1
};
typedef uint8_t eth_pin_sel_t;

/**
  \brief  Defines Ethernet interface selection (MAC <-> PHY).
*/
enum  eth_if_sel_e {
	EthMiiMode      = 0,
	EthRmiiMode     = 1
};
typedef uint8_t eth_if_sel_t;

/**
  \brief  Defines Ethernet interrupt event.
*/
enum  eth_int_event_e {
	EthTxDone       = 0,
	EthRxDone       = 1,
	EthLinkUp       = 2,
	EthLinkDown     = 3,
	EthRx_RDU         = 4
};

/**
  \brief  Defines the InterFrameGap time.
*/
enum  eth_ifg_time_e {
	eth_ifg_time_0     = 0,
	eth_ifg_time_1     = 1,
	eth_ifg_time_2     = 2,
	eth_ifg_time_3     = 3,  // 9.6 us for 10 Mbps, 960 ns for 100 Mbps
	eth_ifg_time_4     = 4,
	eth_ifg_time_5     = 5,
	eth_ifg_time_6     = 6,
	eth_ifg_time_7     = 7
};

/**
  \brief  Defines the type of loopback function.
*/
enum  eth_lbk_fun_e {
	eth_normal_op       = 0,
	eth_r2t_lbk         = 1,
	eth_t2r_lbk         = 3
};

/**
  \brief  Defines the link speed.
*/
enum  eth_link_speed_e {
	eth_speed_100       = 0,
	eth_speed_10        = 1
};

/**
  \brief  Defines the link status.
*/
enum  eth_link_status_e {
	eth_link_up         = 0,
	eth_link_down       = 1
};

/**
  \brief  Defines the duplex mode.
*/
enum  eth_duplex_mode_e {
	eth_half_duplex     = 0,
	eth_full_duplex     = 1
};

/**
  \brief  Defines the n-way status.
*/
enum  eth_nway_status_e {
	eth_nway_incompleted    = 0,
	eth_nway_completed      = 1
};

/**
  \brief  Defines the operation for PHY's register.
*/
enum  eth_phy_reg_op_e {
	eth_phy_reg_read    = 0,
	eth_phy_reg_write   = 1
};

/**
  \brief  Defines Tx VLAN action.
*/
enum  eth_vlan_action_e {
	eth_vlan_hdr_intact     = 0,
	eth_vlan_hdr_insert     = 1,
	eth_vlan_hdr_remove     = 2,
	eth_vlan_hdr_remark_vid = 3
};

/**
  \brief  Defines the type of ethernet packet.
*/
enum  eth_packet_type_e {
	eth_pkt_ethernet        = 0,
	eth_pkt_ipv4            = 1,
	eth_pkt_ipv4_pptp       = 2,
	eth_pkt_ipv4_icmp       = 3,
	eth_pkt_ipv4_igmp       = 4,
	eth_pkt_ipv4_tcp        = 5,
	eth_pkt_ipv4_udp        = 6,
	eth_pkt_ipv6            = 7,
	eth_pkt_icmpv6          = 8,
	eth_pkt_ipv6_tcp        = 9,
	eth_pkt_ipv6_udp        = 10
};


/**
  \brief  Ethernet callback function for interrupt event.
*/
typedef void (*eth_callback_t)(u32 event, u32 data);
/**
  \brief  Callback function to make OS do a context-switch while waiting.
*/
typedef void (*eth_task_yield)(void);


/**
  \brief  The structure of Tx descriptor.
*/
typedef struct hal_eth_tx_desc_s {
	u32 dw1;    // offset 0
	u32 addr;   // offset 4
	u32 dw2;    // offset 8
	u32 dw3;    // offset 12
	u32 dw4;    // offset 16
} hal_eth_tx_desc_t, *phal_eth_tx_desc_t;

/**
  \brief  The structure of Rx descriptor.
*/
typedef struct hal_eth_rx_desc_s {
	u32 dw1;    // offset 0
	u32 addr;   // offset 4
	u32 dw2;    // offset 8
	u32 dw3;    // offset 12
} hal_eth_rx_desc_t, *phal_eth_rx_desc_t;

/**
  \brief  The data structure for Ethernet HAL operations.
*/
typedef struct hal_eth_adapter_s {
	ETHERNET_Type *base_addr;
	u32 int_mask;
	eth_if_sel_t if_sel;
	eth_pin_sel_t pin_sel;
	u8 tx_desc_num;
	u8 rx_desc_num;
	volatile u8 *tx_desc_addr;
	volatile u8 *rx_desc_addr;
	volatile u8 *tx_pkt_buf;
	volatile u8 *rx_pkt_buf;
	eth_callback_t callback;
	eth_task_yield task_yield;
	void (*dcache_invalidate_by_addr)(uint32_t *addr, int32_t dsize);   /*! callback function to do the D-cache invalidate  */
	void (*dcache_clean_by_addr)(uint32_t *addr, int32_t dsize);    /*! callback function to do the D-cache clean  */
	u8 mac_id[6];
} hal_eth_adapter_t, *phal_eth_adapter_t;

/**
  \brief  The data structure of the stubs function for the Ethernet HAL functions in ROM
*/
typedef struct hal_eth_func_stubs_s {
	io_pin_t *eth_pin_table;
	hal_status_t (*hal_eth_pin_ctrl)(eth_pin_sel_t pin_sel, BOOL en);
	void (*hal_eth_set_interface)(eth_if_sel_t if_sel);
	void (*hal_eth_irq_handler)(void);
	void (*hal_eth_irq_reg)(irq_handler_t irq_handler);
	void (*hal_eth_irq_unreg)(void);
	void (*hal_eth_set_desc_num)(hal_eth_adapter_t *peth_adapter, u8 tx_desc_no, u8 rx_desc_no);
	void (*hal_eth_set_desc_addr)(hal_eth_adapter_t *peth_adapter, u8 *tx_desc, u8 *rx_desc);
	void (*hal_eth_set_pkt_buf)(hal_eth_adapter_t *peth_adapter, u8 *tx_pkt_buf, u8 *rx_pkt_buf);
	void (*hal_eth_set_mac_addr)(hal_eth_adapter_t *peth_adapter, u8 *addr);
	void (*hal_eth_get_mac_addr)(hal_eth_adapter_t *peth_adapter, u8 *addr);
	hal_status_t (*hal_eth_init)(hal_eth_adapter_t *peth_adapter, eth_if_sel_t if_sel, eth_pin_sel_t pin_sel);
	void (*hal_eth_deinit)(hal_eth_adapter_t *peth_adapter);
	s32(*hal_eth_write_data)(hal_eth_adapter_t *peth_adapter, u8 *data, u32 size);
	u32(*hal_eth_send_pkt)(hal_eth_adapter_t *peth_adapter);
	u32(*hal_eth_receive_pkt)(hal_eth_adapter_t *peth_adapter);
	u32(*hal_eth_read_data)(hal_eth_adapter_t *peth_adapter, u8 *data, u32 size);
	u32(*hal_eth_get_link_status)(hal_eth_adapter_t *peth_adapter);
	void (*hal_eth_set_link)(hal_eth_adapter_t *peth_adapter, s32 speed, s32 duplex);
	void (*hal_eth_callback_hook)(hal_eth_adapter_t *peth_adapter, eth_callback_t pcallback);
	void (*hal_eth_task_yield_hook)(hal_eth_adapter_t *peth_adapter, eth_task_yield task_yield);
	uint32_t reserved[12];  // reserved space for next ROM code version function table extending.
} hal_eth_func_stubs_t;



/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_ethernet_rom_func ETHERNET HAL ROM APIs.
 * @ingroup hs_hal_ethernet
 * @{
 */

hal_status_t hal_eth_pin_ctrl_rtl8735b(eth_pin_sel_t pin_sel, BOOL en);
void hal_eth_set_interface_rtl8735b(eth_if_sel_t if_sel);
void hal_eth_irq_reg_rtl8735b(irq_handler_t irq_handler);
void hal_eth_irq_unreg_rtl8735b(void);
void hal_eth_set_desc_num_rtl8735b(hal_eth_adapter_t *peth_adapter, u8 tx_desc_no, u8 rx_desc_no);
void hal_eth_set_desc_addr_rtl8735b(hal_eth_adapter_t *peth_adapter, u8 *tx_desc, u8 *rx_desc);
void hal_eth_set_pkt_buf_rtl8735b(hal_eth_adapter_t *peth_adapter, u8 *tx_pkt_buf, u8 *rx_pkt_buf);
void hal_eth_set_mac_addr_rtl8735b(hal_eth_adapter_t *peth_adapter, u8 *addr);
void hal_eth_get_mac_addr_rtl8735b(hal_eth_adapter_t *peth_adapter, u8 *addr);
hal_status_t hal_eth_init_rtl8735b(hal_eth_adapter_t *peth_adapter, eth_if_sel_t if_sel, eth_pin_sel_t pin_sel);
void hal_eth_deinit_rtl8735b(hal_eth_adapter_t *peth_adapter);
s32 hal_eth_write_data_rtl8735b(hal_eth_adapter_t *peth_adapter, u8 *data, u32 size);
u32 hal_eth_send_pkt_rtl8735b(hal_eth_adapter_t *peth_adapter);
u32 hal_eth_receive_pkt_rtl8735b(hal_eth_adapter_t *peth_adapter);
u32 hal_eth_read_data_rtl8735b(hal_eth_adapter_t *peth_adapter, u8 *data, u32 size);
u32 hal_eth_get_link_status_rtl8735b(hal_eth_adapter_t *peth_adapter);
void hal_eth_set_link_rtl8735b(hal_eth_adapter_t *peth_adapter, s32 speed, s32 duplex);
void hal_eth_callback_hook_rtl8735b(hal_eth_adapter_t *peth_adapter, eth_callback_t pcallback);
void hal_eth_task_yield_hook_rtl8735b(hal_eth_adapter_t *peth_adapter, eth_task_yield task_yield);

/** @} */ /* End of group hs_hal_ethernet_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */
/** @} */ /* End of group hs_hal_ethernet */

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _RTL8735B_ETH_H_"


