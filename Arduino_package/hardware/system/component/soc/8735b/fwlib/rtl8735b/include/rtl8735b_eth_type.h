/**************************************************************************//**
 * @file    rtl8735b_ethernet_type.h
 * @brief    The register definitions of Ethernet MAC controller.
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

#ifndef _RTL8735B_ETHERNET_TYPE_H_
#define _RTL8735B_ETHERNET_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_ETHERNET_REG_TYPE

/**
 * @addtogroup hs_hal_ethernet_reg ETHERNET Registers.
 * @ingroup hs_hal_ethernet
 * @{
 */

/**
  \brief Union type to access ethernet_idr0 (@ 0x00000000).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000000) MAC ID Register 1                                          */

	struct {
		__IOM uint32_t idr3       : 8;            /*!< [7..0] 4th byte of MAC ID                                                 */
		__IOM uint32_t idr2       : 8;            /*!< [15..8] 3rd byte of MAC ID                                                */
		__IOM uint32_t idr1       : 8;            /*!< [23..16] 2nd byte of MAC ID                                               */
		__IOM uint32_t idr0       : 8;            /*!< [31..24] 1st byte of MAC ID                                               */
	} b;                                        /*!< bit fields for ethernet_idr0 */
} ethernet_idr0_t, *pethernet_idr0_t;

/**
  \brief Union type to access ethernet_idr4 (@ 0x00000004).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000004) MAC ID Register 2                                          */

	struct {
		__IM  uint32_t            : 16;
		__IOM uint32_t idr5       : 8;            /*!< [23..16] 6th byte of MAC ID                                               */
		__IOM uint32_t idr4       : 8;            /*!< [31..24] 5th byte of MAC ID                                               */
	} b;                                        /*!< bit fields for ethernet_idr4 */
} ethernet_idr4_t, *pethernet_idr4_t;

/**
  \brief Union type to access ethernet_txok_rxok (@ 0x00000010).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000010) TxRx Ok Counter Register                                   */

	struct {
		__IOM uint32_t rxok       : 16;           /*!< [15..0] 16-bit counter of Rx Ok packets. Rolls over automatically.
                                                   Write to clear.                                                           */
		__IOM uint32_t txok       : 16;           /*!< [31..16] 16-bit counter of Tx Ok packets. Rolls over automatically.
                                                   Write to clear.                                                           */
	} b;                                        /*!< bit fields for ethernet_txok_rxok */
} ethernet_txok_rxok_t, *pethernet_txok_rxok_t;

/**
  \brief Union type to access ethernet_txerr_rxerr (@ 0x00000014).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000014) TxRx Error Counter Register                                */

	struct {
		__IOM uint32_t rxerr      : 16;           /*!< [15..0] 16-bit counter of Rx error packets. Rolls over automatically.
                                                   Write to clear.                                                           */
		__IOM uint32_t txerr      : 16;           /*!< [31..16] 16-bit counter of Tx error packets. Rolls over automatically.
                                                   Write to clear.                                                           */
	} b;                                        /*!< bit fields for ethernet_txerr_rxerr */
} ethernet_txerr_rxerr_t, *pethernet_txerr_rxerr_t;

/**
  \brief Union type to access ethernet_com (@ 0x00000038).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000038) Command Register                                           */

	struct {
		__IOM uint32_t rst        : 1;            /*!< [0..0] Reset: Setting to 1 forces the Ethernet module to a software
                                                   reset state which disables the transmitter and receiver,
                                                   reinitializes the FIFOs, triggers interrupt Swint for RISC
                                                   to reset the system buffer pointer to the initial value
                                                   Tx/Rx FDP. This bit is 1 during the reset operation, and
                                                   is cleared to 0 by the Ethernet Module when the reset operation
                                                   is complete.                                                              */
		__IOM uint32_t rxchksum   : 1;            /*!< [1..1] Receive checksum offload enable. 1: Enable. 0: Disable.            */
		__IOM uint32_t rxvlan     : 1;            /*!< [2..2] Receive VLAN de-tagging enable. 1: Enable. 0: Disable.             */
		__IOM uint32_t rxjumbo    : 1;            /*!< [3..3] 1: support jumbo packet receiving. The maximum packet
                                                   size is 16384 Bytes (0x4000). 0: Does not support jumbo
                                                   packet receiving.                                                         */
	} b;                                        /*!< bit fields for ethernet_com */
} ethernet_com_t, *pethernet_com_t;

/**
  \brief Union type to access ethernet_isr_imr (@ 0x0000003C).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x0000003C) Interrupt Status & Interrupt Mask Register                 */

	struct {
		__IOM uint32_t isr_rok    : 1;            /*!< [0..0] Interrupt status of Rx ok. Write 1 to clear                        */
		__IOM uint32_t isr_cnt_wrap : 1;          /*!< [1..1] Interrupt status of Tx/Rx counter wrap interrupt. Write
                                                   1 to clear                                                                */
		__IOM uint32_t isr_rer_runt : 1;          /*!< [2..2] Interrupt status of Rx error caused by runt error characterized
                                                   by the frame length in bytes being less than 64 bytes.
                                                   Write 1 to clear                                                          */
		__IM  uint32_t            : 1;
		__IOM uint32_t isr_rer_ovf : 1;           /*!< [4..4] Interrupt status of Rx FIFO overflow. Write 1 to clear             */
		__IOM uint32_t isr_rdu    : 1;            /*!< [5..5] Interrupt status of Rx descriptor ring1 is unavailable.
                                                   Write 1 to clear                                                          */
		__IOM uint32_t isr_tok    : 1;            /*!< [6..6] Interrupt status of Tx ok. Write 1 to clear                        */
		__IOM uint32_t isr_ter    : 1;            /*!< [7..7] Interrupt status of Tx error. Write 1 to clear                     */
		__IOM uint32_t isr_linkchg : 1;           /*!< [8..8] Interrupt status of link change. Write 1 to clear                  */
		__IOM uint32_t isr_tdu    : 1;            /*!< [9..9] Interrupt status of Tx descriptor ring1 is unavailable.
                                                   Write 1 to clear                                                          */
		__IOM uint32_t isr_swint  : 1;            /*!< [10..10] Interrupt status of software interrupt pending. Write
                                                   1 to clear                                                                */
		__IOM uint32_t isr_rdu2   : 1;            /*!< [11..11] Interrupt status of Rx descriptor ring2 is unavailable.
                                                   Write 1 to clear                                                          */
		__IOM uint32_t isr_rdu3   : 1;            /*!< [12..12] Interrupt status of Rx descriptor ring3 is unavailable.
                                                   Write 1 to clear                                                          */
		__IOM uint32_t isr_rdu4   : 1;            /*!< [13..13] Interrupt status of Rx descriptor ring4 is unavailable.
                                                   Write 1 to clear                                                          */
		__IOM uint32_t isr_rdu5   : 1;            /*!< [14..14] Interrupt status of Rx descriptor ring5 is unavailable.
                                                   Write 1 to clear                                                          */
		__IOM uint32_t isr_rdu6   : 1;            /*!< [15..15] Interrupt status of Rx descriptor ring6 is unavailable.
                                                   Write 1 to clear                                                          */
		__IOM uint32_t imr_rok    : 1;            /*!< [16..16] Interrupt mask of Rx ok                                          */
		__IOM uint32_t imr_cnt_wrap : 1;          /*!< [17..17] Interrupt mask of Tx/Rx counter wrap interrupt                   */
		__IOM uint32_t imr_rer_runt : 1;          /*!< [18..18] Interrupt mask of Rx error caused by runt error characterized
                                                   by the frame length in bytes being less than 64 bytes                     */
		__IM  uint32_t            : 1;
		__IOM uint32_t imr_rer_ovf : 1;           /*!< [20..20] Interrupt mask of Rx FIFO overflow                               */
		__IOM uint32_t imr_rdu    : 1;            /*!< [21..21] Interrupt mask of Rx descriptor ring1 is unavailable             */
		__IOM uint32_t imr_tok    : 1;            /*!< [22..22] Interrupt mask of Tx ok                                          */
		__IOM uint32_t imr_ter    : 1;            /*!< [23..23] Interrupt mask of Tx error                                       */
		__IOM uint32_t imr_linkchg : 1;           /*!< [24..24] Interrupt mask of link change                                    */
		__IOM uint32_t imr_tdu    : 1;            /*!< [25..25] Interrupt mask of Tx descriptor ring1 is unavailable             */
		__IOM uint32_t imr_swint  : 1;            /*!< [26..26] Interrupt mask of software interrupt pending                     */
		__IOM uint32_t imr_rdu2   : 1;            /*!< [27..27] Interrupt mask of Rx descriptor ring2 is unavailable             */
		__IOM uint32_t imr_rdu3   : 1;            /*!< [28..28] Interrupt mask of Rx descriptor ring3 is unavailable             */
		__IOM uint32_t imr_rdu4   : 1;            /*!< [29..29] Interrupt mask of Rx descriptor ring4 is unavailable             */
		__IOM uint32_t imr_rdu5   : 1;            /*!< [30..30] Interrupt mask of Rx descriptor ring5 is unavailable             */
		__IOM uint32_t imr_rdu6   : 1;            /*!< [31..31] Interrupt mask of Rx descriptor ring6 is unavailable             */
	} b;                                        /*!< bit fields for ethernet_isr_imr */
} ethernet_isr_imr_t, *pethernet_isr_imr_t;

/**
  \brief Union type to access ethernet_tc (@ 0x00000040).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000040) Transmit Configuration Register                            */

	struct {
		__IOM uint32_t r_tx_nopadding : 1;        /*!< [0..0] 1: HW does not pad short packet (< 60B). 0: HW pads short
                                                   packet to 64B.                                                            */
		__IM  uint32_t            : 7;
		__IOM uint32_t lbk        : 2;            /*!< [9..8] The loopback function must be independent of the link
                                                   state. 2'b00: normal operation 2'b01: Loopback mode_R2T
                                                   (lbkmode_r2t) : 2'b10: Reserved 2'b11: Loopback mode (lbk_mode).          */
		__IOM uint32_t ifg        : 3;            /*!< [12..10] InterFrameGap Time: This field allows the user to adjust
                                                   the interframe gap time longer than the standard: 9.6 us
                                                   for 10Mbps, 960 ns for 100Mbps. The time can be programmed
                                                   from 9.6 us to 14.4 us (10Mbps) and 960ns to 1440ns (100Mbps)             */
	} b;                                        /*!< bit fields for ethernet_tc */
} ethernet_tc_t, *pethernet_tc_t;

/**
  \brief Union type to access ethernet_rc (@ 0x00000044).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000044) Receive Configuration Register                             */

	struct {
		__IOM uint32_t aap        : 1;            /*!< [0..0] Set to 1 to accept all packets with physical destination
                                                   address, 0 to reject                                                      */
		__IOM uint32_t apm        : 1;            /*!< [1..1] Set to 1 to accept physical match packets, 0 to reject.            */
		__IOM uint32_t am         : 1;            /*!< [2..2] Set to 1 to accept multicast packets, 0 to reject.                 */
		__IOM uint32_t ab         : 1;            /*!< [3..3] Set to 1 to accept broadcast packets, 0 to reject                  */
		__IOM uint32_t ar         : 1;            /*!< [4..4] Accept Runt: This bit allows the receiver to accept packets
                                                   that are smaller than 64 bytes. The packet must be at least
                                                   8 bytes long to be accepted as a runt. Set to 1 to accept
                                                   runt packets.                                                             */
		__IOM uint32_t aer        : 1;            /*!< [5..5] Accept Error Packet When set to 1, all packets with CRC
                                                   error, alignment error, and/or collided fragments will
                                                   be accepted; When set to 0, all packets with CRC error,
                                                   alignment error, and/or collided fragments will be rejected.              */
		__IOM uint32_t aflow      : 1;            /*!< [6..6] Accept flow control : When set to 1, flow control packet
                                                   will also be received & DMA to rx buffer for debug. Default
                                                   is 0                                                                      */
	} b;                                        /*!< bit fields for ethernet_rc */
} ethernet_rc_t, *pethernet_rc_t;

/**
  \brief Union type to access ethernet_ms (@ 0x00000058).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000058) Media Status Register                                      */

	struct {
		__IOM uint32_t refclk_on  : 1;            /*!< [0..0] 1: REF_CLK on 0: REF_CLK off                                       */
		__IOM uint32_t refclk_phase : 1;          /*!< [1..1] 1: TXEN/TXD are transitioned in the falling edge; RXD
                                                   are also sampled in the falling edge 0: TXEN/TXD are transitioned
                                                   in the rising edge; RXD are also sampled in the rising
                                                   edge                                                                      */
		__IM  uint32_t            : 4;
		__IOM uint32_t gmac_md_mst : 1;           /*!< [6..6] 1: GMAC is used to be MDIO master. 0: GMAC is used to
                                                   be MDIO slave.                                                            */
		__IOM uint32_t reg_rmii2mii_en : 1;       /*!< [7..7] 1: transfer MII signals to RMII signals This function
                                                   is only valid in MII mode.                                                */
		__IM  uint32_t            : 2;
		__IOM uint32_t force_spd_mode : 1;        /*!< [10..10] 1: gmac is in force speed mode. 0: gmac speed status
                                                   is from md operation.                                                     */
		__IOM uint32_t rgmii_tx_encode_sts : 1;   /*!< [11..11] This bit is valid only in phy mode. 0: Does not support
                                                   rgmii in band status(link status, speed and duplex mode
                                                   of the PHY) by encoding txd. 1: Supports rgmii in band
                                                   status(link status, speed and duplex mode of the PHY) by
                                                   encoding txd.                                                             */
		__IOM uint32_t rgmii_rx_decode_sts : 1;   /*!< [12..12] 0: Does not support rgmii in band status (link status,
                                                   speed and duplex mode of the PHY) by decoding rxd. 1: Supports
                                                   rgmii in band status (link status, speed and duplex mode
                                                   of the PHY) by decoding rxd.                                              */
		__IOM uint32_t gmac_phy_mode : 1;         /*!< [13..13] 1: in phy mode. 0: not in phy mode.                              */
		__IM  uint32_t            : 1;
		__IOM uint32_t gmac_sel_phyif_0 : 1;      /*!< [15..15] 1: phy interface 0.works. 0: phy interface 1 works.              */
		__IOM uint32_t force_spd  : 2;            /*!< [17..16] Force gmac in 10/100/GIGA mode. 2'b00: 100M 2'b01:
                                                   10M 2'b10: GIGA 2'b11: not force mode.                                    */
		__IOM uint32_t forcelink  : 1;            /*!< [18..18] Force gmac in link ok mode. 1'b1: force gmac in linkok.
                                                   1'b0: link status is from MDIO auto-polling.                              */
		__IOM uint32_t forcedfulldup : 1;         /*!< [19..19] Force gmac operates at full duplex mode. 1'b1: force
                                                   gmac in full duplex mode. 1'b0: duplex status is from MDIO
                                                   auto-polling. Not means gmac is in half duplex mode.                      */
		__IOM uint32_t sel_mii    : 1;            /*!< [20..20] Indicates in mii mode.                                           */
		__IOM uint32_t nwcomplete : 1;            /*!< [21..21] Nway complete                                                    */
		__IOM uint32_t fulldupreg : 1;            /*!< [22..22] Indicates Full duplex mode from mdio results.                    */
		__IOM uint32_t sel_rgmii  : 1;            /*!< [23..23] Selects RGMII interface                                          */
		__IOM uint32_t rxpf       : 1;            /*!< [24..24] Pause Flag 1 = Ethernet module is in backoff state
                                                   because a pause packet received. 0 = pause state is clear.                */
		__IOM uint32_t txpf       : 1;            /*!< [25..25] Tx Pause frame 1 = Ethernet module has sent a pause
                                                   packet. 0 = the Ethernet module has sent a timer done packet.             */
		__IOM uint32_t linkb      : 1;            /*!< [26..26] Inverse of Link status. 0 = Link OK. 1 = Link Fail.              */
		__IOM uint32_t speed_10   : 1;            /*!< [27..27] {SPEED_1000, SPEED_10} 00: 100Mbps, 01: 10Mbps                   */
		__IOM uint32_t speed_1000 : 1;            /*!< [28..28] {SPEED_1000, SPEED_10} 10: 1000Mbps, 11: not allowed             */
		__IOM uint32_t txfce      : 1;            /*!< [29..29] Tx Flow Control Enable 1 = tx flow control enabled.
                                                   0 = tx flow control disabled.                                             */
		__IOM uint32_t rxfce      : 1;            /*!< [30..30] RX Flow control Enable: The flow control is enabled
                                                   in full-duplex mode only. Packets are dropped if buffer
                                                   is exhausted. Default is 0. 1 = Rx Flow Control Enabled.
                                                   0 = Rx Flow Control Disabled.                                             */
		__IOM uint32_t force_trxfce : 1;          /*!< [31..31] Force Tx/RX Flow Control: 1 = enabled Flow control
                                                   in the absence of NWAY. 0 = disables Flow control in the
                                                   absence of NWAY.                                                          */
	} b;                                        /*!< bit fields for ethernet_ms */
} ethernet_ms_t, *pethernet_ms_t;

/**
  \brief Union type to access ethernet_miia (@ 0x0000005C).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x0000005C) MII Access Register                                        */

	struct {
		__IOM uint32_t data       : 16;           /*!< [15..0] Defines the MII resgister data.                                   */
		__IOM uint32_t regaddr    : 5;            /*!< [20..16] Defines the MII register address.                                */
		__IM  uint32_t            : 1;
		__IOM uint32_t disable_auto_polling : 1;  /*!< [22..22] Disable auto polling feature of mdio operation. 0:
                                                   HW auto polling PCS status. 1: HW does not auto polling
                                                   PCS status.                                                               */
		__IM  uint32_t            : 3;
		__IOM uint32_t phyaddr    : 5;            /*!< [30..26] Defines the Phy address for the MII.                             */
		__IOM uint32_t flag       : 1;            /*!< [31..31] Flag bit, used to identify access to MII register 1:
                                                   Write data to MII register. Turns to 0 automatically upon
                                                   completion of MAC writing to the specified MII register.
                                                   0: Read data from MII register. Turns to 1 automatically
                                                   upon completion of MAC reading the specified MII register.                */
	} b;                                        /*!< bit fields for ethernet_miia */
} ethernet_miia_t, *pethernet_miia_t;

/**
  \brief Union type to access ethernet_vlan (@ 0x00000064).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000064) VLAN Register                                              */

	struct {
		__IM  uint32_t            : 15;
		__IOM uint32_t tdsc_vlan_type : 1;        /*!< [15..15] 1: tx_vlan_action field in the Tx command descriptor
                                                   is for s-tag. 0: tx_vlan_action field in the Tx command
                                                   descriptor is for c-tag.                                                  */
		__IOM uint32_t stag_pid   : 16;           /*!< [31..16] Set the s-tag protocol identifier.                               */
	} b;                                        /*!< bit fields for ethernet_vlan */
} ethernet_vlan_t, *pethernet_vlan_t;

/**
  \brief Union type to access ethernet_txfdp1 (@ 0x00001300).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00001300) Tx 1st Descriptor Ring Address Register                    */

	struct {
		__IOM uint32_t txfdp1     : 32;           /*!< [31..0] Tx 1st priority Descriptor Pointer to the Tx Ring.                */
	} b;                                        /*!< bit fields for ethernet_txfdp1 */
} ethernet_txfdp1_t, *pethernet_txfdp1_t;

/**
  \brief Union type to access ethernet_txcdo1 (@ 0x00001304).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00001304) Tx 1st Current Descriptor Offset Register                  */

	struct {
		__IOM uint32_t txcdo1     : 12;           /*!< [11..0] Tx 1st priority current descriptor offset: FDP+CDO =
                                                   current descriptor pointer. CDO increments by 16 bytes
                                                   each time.                                                                */
	} b;                                        /*!< bit fields for ethernet_txcdo1 */
} ethernet_txcdo1_t, *pethernet_txcdo1_t;

/**
  \brief Union type to access ethernet_rxfdp1 (@ 0x000013F0).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x000013F0) Rx 1st Descriptor Ring Address Register                    */

	struct {
		__IOM uint32_t rxfdp1     : 32;           /*!< [31..0] Rx 1st queue Descriptor Pointer to the Rx Ring.                   */
	} b;                                        /*!< bit fields for ethernet_rxfdp1 */
} ethernet_rxfdp1_t, *pethernet_rxfdp1_t;

/**
  \brief Union type to access ethernet_rxrs1cdo1 (@ 0x000013F4).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x000013F4) Rx 1st Descriptor Ring Size & 1st Current Descriptor
                                                                  Offset Register                                            */

	struct {
		__IOM uint32_t rxringsize_1_h : 4;        /*!< [3..0] This is the bit[11:8] of RxRingSize1.                              */
		__IM  uint32_t            : 4;
		__IOM uint32_t rxringsize_1_l : 8;        /*!< [15..8] This is the total number of descriptors in the Rx descriptor
                                                   rings of 1st queue. (bit[7:0] of RxRingSize1) Act as bit
                                                   mask, eg. RxRingSize [11:0]: 0000_0000_1111: 16 descriptors
                                                   0000_0001_1111: 32 descriptors 0000_0011_1111: 64 descriptors
                                                   0000_0111_1111: 128 descriptors 0000_1111_1111: 256 descriptors
                                                   0001_1111_1111: 512 descriptors 0011_1111_1111: 1024 descriptors
                                                   0111_1111_1111: 2048 descriptors 1111_1111_1111: 4096 descriptors
                                                   Any other value in this register yields undefined results.                */
		__IOM uint32_t rxcdo1     : 12;           /*!< [27..16] Rx Current Descriptor Offset of 1st queue: RxFDP +
                                                   RxCDO = current descriptor pointer. CDO increments by 16
                                                   each time (each increment is one byte).                                   */
	} b;                                        /*!< bit fields for ethernet_rxrs1cdo1 */
} ethernet_rxrs1cdo1_t, *pethernet_rxrs1cdo1_t;

/**
  \brief Union type to access ethernet_rx_pse_des_thres_1_h (@ 0x0000142C).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x0000142C) PHY Mode Clock Phase Control Register                      */

	struct {
		__IM  uint32_t            : 5;
		__IOM uint32_t phy_mode_clk_phase_chg : 1;/*!< [5..5] Changes the clock phase in the PHY mode                            */
	} b;                                        /*!< bit fields for ethernet_rx_pse_des_thres_1_h */
} ethernet_rx_pse_des_thres_1_h_t, *pethernet_rx_pse_des_thres_1_h_t;

/**
  \brief Union type to access ethernet_etnrxcpu1 (@ 0x00001430).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00001430) Rx Ring1 Threshold Register                                */

	struct {
		__IOM uint32_t etnrxcpu1  : 32;           /*!< [31..0] Rx ring1 threshold settings                                       */
	} b;                                        /*!< bit fields for ethernet_etnrxcpu1 */
} ethernet_etnrxcpu1_t, *pethernet_etnrxcpu1_t;

/**
  \brief Union type to access ethernet_io_cmd (@ 0x00001434).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00001434) I/O Command Register 0                                     */

	struct {
		__IOM uint32_t txfn1st    : 1;            /*!< [0..0] 1st Priority DMA-Ethernet Transmit enable. 1: Enable.
                                                   0: Disable.                                                               */
		__IOM uint32_t txfn2nd    : 1;            /*!< [1..1] 2nd Priority DMA-Ethernet Transmit enable. 1: Enable.
                                                   0: Disable.                                                               */
		__IOM uint32_t txfn3rd    : 1;            /*!< [2..2] 3rd Priority DMA-Ethernet Transmit enable. 1: Enable.
                                                   0: Disable.                                                               */
		__IOM uint32_t txfn4th    : 1;            /*!< [3..3] 4th Priority DMA-Ethernet Transmit enable. 1: Enable.
                                                   0: Disable.                                                               */
		__IOM uint32_t te         : 1;            /*!< [4..4] Tx Enable                                                          */
		__IOM uint32_t re         : 1;            /*!< [5..5] Rx Enable                                                          */
		__IOM uint32_t reg_int_timer_sel : 2;     /*!< [7..6] RXPktTimer, TXPktTimer Unit (TU)                                   */
		__IOM uint32_t rxintmitigation_l : 3;     /*!< [10..8] This sets the number of packets received before RxOK
                                                   interrupt is triggered. 0000: 1 pkt 0001: 4 pkts 0010:
                                                   8 pkts 0011: 12 pkts 0100: 16 pkts 0101: 20 pkts 0110:
                                                   24 pkts 0111: 28 pkts                                                     */
		__IOM uint32_t rxfth      : 2;            /*!< [12..11] Rx Threshold: Specifies the threshold level in the
                                                   Rx FIFO to begin the transmission. When the byte count
                                                   of the data in the Rx FIFO reaches this level, (or the
                                                   FIFO contains at least one complete packet or the end of
                                                   a packet) the Ethernet module will transmit this packet.
                                                   00: 1024 Bytes. 01: 128 Bytes. 10: 256 Bytes. 11: 512 Bytes.              */
		__IOM uint32_t rxpkttimer_l : 3;          /*!< [15..13] Timer to trigger RxOK interrupt before receipt of RxIntMitigation
                                                   pkts. 0000: no timer set 0001~1111: the timer interval
                                                   defining a multiple of TU Ex: 011 = timer interval set
                                                   to 3 x 4 =12 TU This only applies to packets of size larger
                                                   than 128 bytes. Once RxOK is asserted the timer mechanism
                                                   is reinitialized. For ingress pkt which is short than 128B,
                                                   RxOK interrupt asserts after DMA completes.                               */
		__IOM uint32_t txintmitigation_l : 3;     /*!< [18..16] This sets the number of packets received before TxOK
                                                   interrupt is triggered. 0000: 1 pkt 0001: 4 pkts 0010:
                                                   8 pkts 0011: 12 pkts 0100: 16 pkts 0101: 20 pkts 0110:
                                                   24 pkts 0111: 28 pkts                                                     */
		__IOM uint32_t tsh        : 2;            /*!< [20..19] Tx Threshold: Specifies the threshold level in the
                                                   Tx FIFO to begin the transmission. When the byte count
                                                   of the data in the Tx FIFO reaches this level, (or the
                                                   FIFO contains at least one complete packet or the end of
                                                   a packet) the Ethernet module will transmit this packet.
                                                   00: 128 Bytes. 01: 256 Bytes. 10: 512 Bytes. 11: 1024 Bytes.              */
		__IOM uint32_t rxintmitigation_h : 1;     /*!< [21..21] See bit[19:8]                                                    */
		__IOM uint32_t rxpkttimer_h : 1;          /*!< [22..22] See bit[15:13]                                                   */
		__IOM uint32_t txintmitigation_h : 1;     /*!< [23..23] See bit[18:16]                                                   */
		__IOM uint32_t txpkttimer : 4;            /*!< [27..24] Timer to trigger TxOK interrupt before receipt of TxIntMitigation
                                                   pkts. 0000: no timer set 0001~1111: the timer interval
                                                   defining a multiple of TU Ex: 0011 = timer interval sets
                                                   to 3 x 4 =12 TU Once TxOK is asserted the timer mechanism
                                                   is reinitialized.                                                         */
		__IOM uint32_t en_early_tx : 1;           /*!< [28..28] 0: disable, 1: enable. Disable early tx by GAMC while
                                                   tx command descriptor.IPCS, UDPCS or TCPCS are set to high.               */
		__IOM uint32_t max_dma_sel_h : 1;         /*!< [29..29] See bit[31]                                                      */
		__IOM uint32_t shortdesformat : 1;        /*!< [30..30] Short descriptor format 1: tx/rx descriptor will use
                                                   old format (4 x 32-bit each item) 0: use new format to
                                                   support sram mapping.                                                     */
		__IOM uint32_t max_dma_sel_l : 1;         /*!< [31..31] Select the dma burst size on bus. 00: 16 DW (1DW =
                                                   4 Bytes) 01: 32 DW 10: 64 DW 11: 128DW.                                   */
	} b;                                        /*!< bit fields for ethernet_io_cmd */
} ethernet_io_cmd_t, *pethernet_io_cmd_t;

/**
  \brief Union type to access ethernet_io_cmd1 (@ 0x00001438).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00001438) I/O Command Register 1                                     */

	struct {
		__IM  uint32_t            : 8;
		__IOM uint32_t txfn5th    : 1;            /*!< [8..8] 5th Priority DMA-Ethernet Transmit enable. 1: Enable.
                                                   0: Disable.                                                               */
		__IM  uint32_t            : 5;
		__IOM uint32_t Tx_hl_pri_se : 2;          /*!< [15..14] 2'b00: TX ring uses strict priority. 2'b01: TX ring
                                                   uses high and low queue priority. Inside high queue, tx
                                                   ring is round robin. Inside low queue, tx ring is round
                                                   robin. Strict priority is used for high and low queue selection.
                                                   2'b10 and 2'b11: Reserved.                                                */
		__IOM uint32_t rxring1    : 1;            /*!< [16..16] Ethernet-DMA Receive Ring1 enable. 1: Enable. 0: Disable.        */
		__IOM uint32_t rxring2    : 1;            /*!< [17..17] Ethernet-DMA Receive Ring2 enable. 1: Enable. 0: Disable.        */
		__IOM uint32_t rxring3    : 1;            /*!< [18..18] Ethernet-DMA Receive Ring3 enable. 1: Enable. 0: Disable.        */
		__IOM uint32_t rxring4    : 1;            /*!< [19..19] Ethernet-DMA Receive Ring4 enable. 1: Enable. 0: Disable.        */
		__IOM uint32_t rxring5    : 1;            /*!< [20..20] Ethernet-DMA Receive Ring5 enable. 1: Enable. 0: Disable.        */
		__IOM uint32_t rxring6    : 1;            /*!< [21..21] Ethernet-DMA Receive Ring6 enable. 1: Enable. 0: Disable.        */
		__IM  uint32_t            : 2;
		__IOM uint32_t en_1gb     : 1;            /*!< [24..24] 1: support 1GB addressing in lx master bus. 0: Not
                                                   support.                                                                  */
		__IOM uint32_t en_rx_mring : 1;           /*!< [25..25] Enable rx multiple rings. 1: rx using multiple rings.
                                                   max: 6 rings (ring1 to ring6). 0: rx using single ring
                                                   (ring1 only).                                                             */
		__IOM uint32_t rxokint_msk_128b : 1;      /*!< [26..26] 1: For ingress pkt which is short than 128B, RxOK interrupt
                                                   asserts after DMA completes (compatible issue). 0: For
                                                   ingress pkt which is short than 128B, RxOK interrupt does
                                                   not assert after DMA completes.                                           */
		__IOM uint32_t en_precise_dma : 1;        /*!< [27..27] 0: disable precise DMA transfer. 1: enable precise
                                                   DMA transfer.                                                             */
		__IOM uint32_t dsc_format_extra : 3;      /*!< [30..28] Extra descriptor format. SW should set this field before
                                                   set io_cmd.te or io_cmd.re to 1.                                          */
	} b;                                        /*!< bit fields for ethernet_io_cmd1 */
} ethernet_io_cmd1_t, *pethernet_io_cmd1_t;

/** @} */ /* End of group hs_hal_ethernet_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_ETHERNET_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8735B_ETHERNET_TYPE_H_

