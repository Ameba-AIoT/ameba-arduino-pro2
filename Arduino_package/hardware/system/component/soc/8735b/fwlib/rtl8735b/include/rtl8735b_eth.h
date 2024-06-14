/*****************************************************************************
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
/// Defines the header of vlantag (ctag)
#define ETH_C_VLAN_HDR                  0x8100279F
/// Defines the header of vlantag (stag)
#define ETH_S_VLAN_HDR                  0x88A8279F

/**
  \brief  Defines FEMAC IDR0 register (0x0)
*/
#define FEMAC_IDR0_SHIFT_IDR0           24
#define FEMAC_IDR0_BIT_IDR0             ((u32)0x000000FF << 24)
#define FEMAC_IDR0_SHIFT_IDR1           16
#define FEMAC_IDR0_BIT_IDR1             ((u32)0x000000FF << 16)
#define FEMAC_IDR0_SHIFT_IDR2           8
#define FEMAC_IDR0_BIT_IDR2             ((u32)0x000000FF << 8)
#define FEMAC_IDR0_SHIFT_IDR3           0
#define FEMAC_IDR0_BIT_IDR3             ((u32)0x000000FF << 0)

/**
  \brief  Defines FEMAC IDR4 register (0x4)
*/
#define FEMAC_IDR4_SHIFT_IDR4           24
#define FEMAC_IDR4_BIT_IDR4             ((u32)0x000000FF << 24)
#define FEMAC_IDR4_SHIFT_IDR5           16
#define FEMAC_IDR4_BIT_IDR5             ((u32)0x000000FF << 16)

/**
  \brief  Defines FEMAC Interrupt Status/Mask register (0x3C)
*/
// IMR
#define FEMAC_IMR_SHIFT_SWINT       26
#define FEMAC_IMR_BIT_SWINT         ((u32)0x00000001 << 26)
#define FEMAC_IMR_SHIFT_TDU         25
#define FEMAC_IMR_BIT_TDU           ((u32)0x00000001 << 25)
#define FEMAC_IMR_SHIFT_LINKCHG         24
#define FEMAC_IMR_BIT_LINKCHG           ((u32)0x00000001 << 24)
#define FEMAC_IMR_SHIFT_TER         23
#define FEMAC_IMR_BIT_TER           ((u32)0x00000001 << 23)
#define FEMAC_IMR_SHIFT_TOK             22
#define FEMAC_IMR_BIT_TOK               ((u32)0x00000001 << 22)
#define FEMAC_IMR_SHIFT_RDU         21
#define FEMAC_IMR_BIT_RDU           ((u32)0x00000001 << 21)
#define FEMAC_IMR_SHIFT_RER_OVF         20
#define FEMAC_IMR_BIT_RER_OVF           ((u32)0x00000001 << 20)
#define FEMAC_IMR_SHIFT_RER_RUNT    18
#define FEMAC_IMR_BIT_RER_RUNT      ((u32)0x00000001 << 18)
#define FEMAC_IMR_SHIFT_CNT_WRAP    17
#define FEMAC_IMR_BIT_CNT_WRAP      ((u32)0x00000001 << 17)
#define FEMAC_IMR_SHIFT_ROK             16
#define FEMAC_IMR_BIT_ROK               ((u32)0x00000001 << 16)
// ISR
#define FEMAC_ISR_SHIFT_SWINT       10
#define FEMAC_ISR_BIT_SWINT         ((u32)0x00000001 << 10)
#define FEMAC_ISR_SHIFT_TDU         9
#define FEMAC_ISR_BIT_TDU           ((u32)0x00000001 << 9)
#define FEMAC_ISR_SHIFT_LINKCHG     8
#define FEMAC_ISR_BIT_LINKCHG       ((u32)0x00000001 << 8)
#define FEMAC_ISR_SHIFT_TER         7
#define FEMAC_ISR_BIT_TER           ((u32)0x00000001 << 7)
#define FEMAC_ISR_SHIFT_TOK         6
#define FEMAC_ISR_BIT_TOK           ((u32)0x00000001 << 6)
#define FEMAC_ISR_SHIFT_RDU         5
#define FEMAC_ISR_BIT_RDU           ((u32)0x00000001 << 5)
#define FEMAC_ISR_SHIFT_RER_OVF         4
#define FEMAC_ISR_BIT_RER_OVF           ((u32)0x00000001 << 4)
#define FEMAC_ISR_SHIFT_RER_RUNT    2
#define FEMAC_ISR_BIT_RER_RUNT      ((u32)0x00000001 << 2)
#define FEMAC_ISR_SHIFT_CNT_WRAP    1
#define FEMAC_ISR_BIT_CNT_WRAP      ((u32)0x00000001 << 1)
#define FEMAC_ISR_SHIFT_ROK         0
#define FEMAC_ISR_BIT_ROK           ((u32)0x00000001 << 0)

/**
  \brief  Defines FEMAC Receive Configuration register (0x44)
*/
#define FEMAC_RC_SHIFT_AER              5
#define FEMAC_RC_MASK_AER               ((u32)0x00000001 << 5)
#define FEMAC_RC_SHIFT_AR               4
#define FEMAC_RC_MASK_AR                ((u32)0x00000001 << 4)
#define FEMAC_RC_SHIFT_AB               3
#define FEMAC_RC_MASK_AB                ((u32)0x00000001 << 3)
#define FEMAC_RC_SHIFT_AM               2
#define FEMAC_RC_MASK_AM                ((u32)0x00000001 << 2)
#define FEMAC_RC_SHIFT_APM              1
#define FEMAC_RC_MASK_APM               ((u32)0x00000001 << 1)
#define FEMAC_RC_SHIFT_AAP              0
#define FEMAC_RC_MASK_AAP               ((u32)0x00000001 << 0)

/**
  \brief  Defines FEMAC Media Status register (0x58)
*/
#define FEMAC_MS_SHIFT_SPEED            27
#define FEMAC_MS_BIT_SPEED              ((u32)0x00000003 << 27)
#define FEMAC_MS_SHIFT_LINKB            26
#define FEMAC_MS_BIT_LINKB              ((u32)0x00000001 << 26)
#define FEMAC_MS_SHIFT_FULLDUP          22
#define FEMAC_MS_BIT_FULLDUP            ((u32)0x00000003 << 22)
#define FEMAC_MS_SHIFT_NWCOMPLETE       21
#define FEMAC_MS_BIT_NWCOMPLETE         ((u32)0x00000003 << 21)

/**
  \brief  Defines FEMAC MII access register (0x5C)
*/
#define FEMAC_MIIA_SHIFT_FLAG           31
#define FEMAC_MIIA_BIT_FLAG             ((u32)0x00000001 << 31)
#define FEMAC_MIIA_SHIFT_PHY_ADDR       26
#define FEMAC_MIIA_MASK_PHY_ADDR        ((u32)0x0000001F << 26)
#define FEMAC_MIIA_SHIFT_MDIO_BUSY      25
#define FEMAC_MIIA_BIT_MDIO_BUSY        ((u32)0x00000001 << 25)
#define FEMAC_MIIA_SHIFT_REG_ADDR       16
#define FEMAC_MIIA_MASK_REG_ADDR        ((u32)0x0000001F << 16)
#define FEMAC_MIIA_SHIFT_DATA           0
#define FEMAC_MIIA_MASK_DATA            ((u32)0x0000FFFF << 0)

/**
  \brief  Defines FEMAC Tx command descriptor
*/
#define FEMAC_TX_DSC_SHIFT_OWN          31
#define FEMAC_TX_DSC_BIT_OWN            ((u32)0x00000001 << 31)
#define FEMAC_TX_DSC_SHIFT_EOR          30
#define FEMAC_TX_DSC_BIT_EOR            ((u32)0x00000001 << 30)
#define FEMAC_TX_DSC_SHIFT_FS           29
#define FEMAC_TX_DSC_BIT_FS             ((u32)0x00000001 << 29)
#define FEMAC_TX_DSC_SHIFT_LS           28
#define FEMAC_TX_DSC_BIT_LS             ((u32)0x00000001 << 28)
#define FEMAC_TX_DSC_SHIFT_CRC          23
#define FEMAC_TX_DSC_BIT_CRC            ((u32)0x00000001 << 23)

/**
  \brief  Defines FEMAC Rx command descriptor
*/
#define FEMAC_RX_DSC_SHIFT_OWN          31
#define FEMAC_RX_DSC_BIT_OWN            ((u32)0x00000001 << 31)
#define FEMAC_RX_DSC_SHIFT_EOR          30
#define FEMAC_RX_DSC_BIT_EOR            ((u32)0x00000001 << 30)

/**
  \brief  Defines FEPHY register page number
*/
#define FEPHY_REG_PAGE_0                0x0
#define FEPHY_REG_PAGE_A40              0xA40
#define FEPHY_REG_PAGE_A41              0xA41
#define FEPHY_REG_PAGE_A42              0xA42
#define FEPHY_REG_PAGE_A43              0xA43
#define FEPHY_REG_PAGE_A46              0xA46
#define FEPHY_REG_PAGE_A4A              0xA4A
#define FEPHY_REG_PAGE_A4E              0xA4E
#define FEPHY_REG_PAGE_A60              0xA60
#define FEPHY_REG_PAGE_AA0              0xAA0
#define FEPHY_REG_PAGE_BC0              0xBC0

/**
  \brief  Defines FEPHY Page 0xA46 Reg 20
*/
#define FEPHY_REG_SHIFT_FUSE_RDY        0
#define FEPHY_REG_MASK_FUSE_RDY         ((u32)0x00000001 << 0)

#define FEPHY_IDAC_DEFAULT              0x6


/**
  \brief  Defines the FEPHY register address
*/
enum fephy_reg_addr {
	FEPHY_REG_ADDR_0        = 0,
	FEPHY_REG_ADDR_1        = 1,
	FEPHY_REG_ADDR_2        = 2,
	FEPHY_REG_ADDR_3        = 3,
	FEPHY_REG_ADDR_4        = 4,
	FEPHY_REG_ADDR_5        = 5,
	FEPHY_REG_ADDR_6        = 6,
	FEPHY_REG_ADDR_7        = 7,
	FEPHY_REG_ADDR_8        = 8,
	FEPHY_REG_ADDR_9        = 9,
	FEPHY_REG_ADDR_10       = 10,
	FEPHY_REG_ADDR_11       = 11,
	FEPHY_REG_ADDR_12       = 12,
	FEPHY_REG_ADDR_13       = 13,
	FEPHY_REG_ADDR_14       = 14,
	FEPHY_REG_ADDR_15       = 15,
	FEPHY_REG_ADDR_16       = 16,
	FEPHY_REG_ADDR_17       = 17,
	FEPHY_REG_ADDR_18       = 18,
	FEPHY_REG_ADDR_19       = 19,
	FEPHY_REG_ADDR_20       = 20,
	FEPHY_REG_ADDR_21       = 21,
	FEPHY_REG_ADDR_22       = 22,
	FEPHY_REG_ADDR_23       = 23,
	FEPHY_REG_ADDR_24       = 24,
	FEPHY_REG_ADDR_25       = 25,
	FEPHY_REG_ADDR_26       = 26,
	FEPHY_REG_ADDR_27       = 27,
	FEPHY_REG_ADDR_28       = 28,
	FEPHY_REG_ADDR_29       = 29,
	FEPHY_REG_ADDR_30       = 30,
	FEPHY_REG_ADDR_31       = 31,
};

/**
  \brief  Defines Ethernet interrupt event.
*/
enum  eth_int_event_e {
	EthIntRok       = 0,
	EthIntCntWrap   = 1,
	EthIntRerRunt   = 2,
	EthIntRerOvf    = 3,
	EthIntRdu       = 4,
	EthIntTok       = 5,
	EthIntTer       = 6,
	EthIntLinkUp    = 7,
	EthIntLinkDown  = 8,
	EthIntTdu       = 9,
	EthIntSwInt     = 10
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

enum  eth_sys_hw_ctrl_e {
	eth_sys_hw_fephy_ip,
	eth_sys_hw_femac_ip,
	eth_sys_hw_uabg_en,
	eth_sys_hw_uahv_en,
	eth_sys_hw_fephy_en,
	eth_sys_hw_lx_en
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
	void (*hal_eth_irq_unreg)(void);
	void (*hal_eth_set_desc_num)(hal_eth_adapter_t *peth_adapter, u8 tx_desc_no, u8 rx_desc_no);
	void (*hal_eth_set_desc_addr)(hal_eth_adapter_t *peth_adapter, u8 *tx_desc, u8 *rx_desc);
	void (*hal_eth_set_pkt_buf)(hal_eth_adapter_t *peth_adapter, u8 *tx_pkt_buf, u8 *rx_pkt_buf);
	void (*hal_eth_set_mac_addr)(hal_eth_adapter_t *peth_adapter, u8 *addr);
	void (*hal_eth_get_mac_addr)(hal_eth_adapter_t *peth_adapter, u8 *addr);
//	hal_status_t (*hal_eth_init)(hal_eth_adapter_t *peth_adapter);
//	void (*hal_eth_deinit)(hal_eth_adapter_t *peth_adapter);
	s32(*hal_eth_write_data)(hal_eth_adapter_t *peth_adapter, u8 *data, u32 size);
	u32(*hal_eth_send_pkt)(hal_eth_adapter_t *peth_adapter);
	u32(*hal_eth_receive_pkt)(hal_eth_adapter_t *peth_adapter);
	u32(*hal_eth_read_data)(hal_eth_adapter_t *peth_adapter, u8 *data, u32 size);
	u32(*hal_eth_get_link_status)(hal_eth_adapter_t *peth_adapter);
	void (*hal_eth_set_link)(hal_eth_adapter_t *peth_adapter, s32 speed, s32 duplex);
	void (*hal_eth_callback_hook)(hal_eth_adapter_t *peth_adapter, eth_callback_t pcallback);
	void (*hal_eth_task_yield_hook)(hal_eth_adapter_t *peth_adapter, eth_task_yield task_yield);
	u16(*hal_eth_rd_phy_reg)(hal_eth_adapter_t *peth_adapter, u16 page, u16 reg_addr);
	u32(*hal_eth_wr_phy_reg)(hal_eth_adapter_t *peth_adapter, u16 page, u16 reg_addr, u16 data);
//    void (*hal_eth_detect_phy_state)(hal_eth_adapter_t *peth_adapter);
	void (*hal_eth_phy_eee_ctrl)(hal_eth_adapter_t *peth_adapter, u8 en);
	uint32_t reserved[12];  // reserved space for next ROM code version function table extending.
} hal_eth_func_stubs_t;



/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_ethernet_rom_func ETHERNET HAL ROM APIs.
 * @ingroup hs_hal_ethernet
 * @{
 */
void hal_rtl_eth_irq_reg(irq_handler_t irq_handler);
void hal_rtl_eth_irq_unreg(void);
void hal_rtl_eth_set_desc_num(hal_eth_adapter_t *peth_adapter, u8 tx_desc_no, u8 rx_desc_no);
void hal_rtl_eth_set_desc_addr(hal_eth_adapter_t *peth_adapter, u8 *tx_desc, u8 *rx_desc);
void hal_rtl_eth_set_pkt_buf(hal_eth_adapter_t *peth_adapter, u8 *tx_pkt_buf, u8 *rx_pkt_buf);
void hal_rtl_eth_set_mac_addr(hal_eth_adapter_t *peth_adapter, u8 *addr);
void hal_rtl_eth_get_mac_addr(hal_eth_adapter_t *peth_adapter, u8 *addr);
//hal_status_t hal_rtl_eth_init(hal_eth_adapter_t *peth_adapter);
//void hal_rtl_eth_deinit(hal_eth_adapter_t *peth_adapter);
s32 hal_rtl_eth_write_data(hal_eth_adapter_t *peth_adapter, u8 *data, u32 size);
u32 hal_rtl_eth_send_pkt(hal_eth_adapter_t *peth_adapter);
u32 hal_rtl_eth_receive_pkt(hal_eth_adapter_t *peth_adapter);
u32 hal_rtl_eth_read_data(hal_eth_adapter_t *peth_adapter, u8 *data, u32 size);
u32 hal_rtl_eth_get_link_status(hal_eth_adapter_t *peth_adapter);
void hal_rtl_eth_set_link(hal_eth_adapter_t *peth_adapter, s32 speed, s32 duplex);
void hal_rtl_eth_callback_hook(hal_eth_adapter_t *peth_adapter, eth_callback_t pcallback);
void hal_rtl_eth_task_yield_hook(hal_eth_adapter_t *peth_adapter, eth_task_yield task_yield);
u16 hal_rtl_eth_rd_phy_reg(hal_eth_adapter_t *peth_adapter, u16 page, u16 reg_addr);
u32 hal_rtl_eth_wr_phy_reg(hal_eth_adapter_t *peth_adapter, u16 page, u16 reg_addr, u16 data);
//void hal_rtl_eth_detect_phy_state(hal_eth_adapter_t *peth_adapter);
void hal_rtl_eth_phy_eee_ctrl(hal_eth_adapter_t *peth_adapter, u8 en);

/** @} */ /* End of group hs_hal_ethernet_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */
/** @} */ /* End of group hs_hal_ethernet */

#ifdef  __cplusplus
}
#endif

#endif  // #ifndef _RTL8735B_ETH_H_


