/**************************************************************************//**
 * @file      rtl8195bhp_i2c_type.h
 * @brief
 * @version   V1.00
 * @date      2017-11-1 10:11:11
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

#ifndef _RTL8735B_I2C_TYPE_H_
#define _RTL8735B_I2C_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif


/**************************************************************************//**
 * @defgroup I2C_TYPE_CON
 * @brief  I2C Control Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_SLV_DIS_1                          7
#define I2C_BIT_SLV_DIS_1                            ((u32)0x00000001 << 7)                              /*!<R/W 1  This bit controls whether I2C has its slave 1 disabled. If this bit is set (slave is disabled), I2C Module functions only as a master and does not perform any action that requires a slave. 0: slave1 is enabled 1: slave1 is disabled */
#define I2C_SHIFT_SLV_DIS                            6
#define I2C_BIT_SLV_DIS                              ((u32)0x00000001 << 6)                              /*!<R/W 1  This bit controls whether I2C has its slave disabled. If this bit is set (slave is disabled), I2C Module functions only as a master and does not perform any action that requires a slave. 0: slave is enabled 1: slave is disabled */
#define I2C_SHIFT_RSTRT_EN                           5
#define I2C_BIT_RSTRT_EN                             ((u32)0x00000001 << 5)                              /*!<R/W 1  Determines whether RESTART conditions may be sent when acting as a master. Some older slaves do not support handling RESTART conditions; however, RESTART conditions are used in several I2C Module operations. 0: disable 1: enable */
#define I2C_SHIFT_MST_10BIT_ADDR                     4
#define I2C_BIT_MST_10BIT_ADDR                       ((u32)0x00000001 << 4)                              /*!<R/W 1  This bit controls whether the I2C Module starts its transfers in 7- or 10-bit addressing mode when acting as a master. 0: 7-bit addressing 1: 10-bit addressing */
#define I2C_SHIFT_SLV_10BIT_ADDR                     3
#define I2C_BIT_SLV_10BIT_ADDR                       ((u32)0x00000001 << 3)                              /*!<R/W 1  When acting as a slave, this bit controls whether the I2C Module responds to 7- or 10-bit addresses. 0: 7-bit addressing. The I2C Module ignores transactions that involve 10-bit addressing; for 7-bit addressing, only the lower 7 bits of the SAR register are compared. 1: 10-bit addressing. The I2C Module responds to only 10-bit addressing transfers that match the full 10 bits of the SAR register. */
#define I2C_SHIFT_SPD                                1
#define I2C_MASK_SPD                                 ((u32)0x00000003 << 1)                              /*!<R/W 0x3  These bits control at which speed the I2C Module operates; its setting is relevant only if one is operating the I2C Module in master mode. 1: standard mode (0 to 100 kbit/s) 2: fast mode (<=400 kbit/s) 3: high speed mode (<=3.4 Mbit/s) */
#define I2C_SHIFT_MST_MOD                            0
#define I2C_BIT_MST_MOD                              ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls whether the I2C Module master is enabled. 0: master disabled 1: master enabled */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_TAR
 * @brief  I2C Target Address Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_TAR_10BIT_ADDR                     12
#define I2C_BIT_TAR_10BIT_ADDR                       ((u32)0x00000001 << 12)                             /*!<R/W 1  This bit controls whether the I2C Module starts its transfers in 7-or 10-bit addressing mode when acting as a master. 0: 7-bit addressing 1: 10-bit addressing */
#define I2C_SHIFT_SPEC                               11
#define I2C_BIT_SPEC                                 ((u32)0x00000001 << 11)                             /*!<R/W 0  This bit indicates whether software performs a General Call or START BYTE command. 0: ignore bit 10 GC_OR_STARTand use TAR normally 1: perform special I2C command as specified in GC_OR_STARTbit */
#define I2C_SHIFT_GC_START_BYTE                      10
#define I2C_BIT_GC_START_BYTE                        ((u32)0x00000001 << 10)                             /*!<R/W 0  If bit 11 (SPECIAL) is set to 1, then this bit indicates whether a General Call or START byte command is to be performed by the I2C Module. 0: General Call Address - after issuing a General Call, only writes may be performed. Attempting to issue a read command results in setting bit 6 (TX_ABRT) of the RAW_INTR_STATregister. The I2C Module remains in General Call mode until the SPECIALbit value (bit 11) is cleared. 1: START BYTE */
#define I2C_SHIFT_TAR                                0
#define I2C_MASK_TAR                                 ((u32)0x000003FF << 0)                              /*!<R/W 0x55  This is the target address for any master transaction. When transmitting a General Call, these bits are ignored. To generate a START BYTE, the CPU needs to write only once into these bits.  */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_SAR
 * @brief  I2C Slave Address Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_SAR                                0
#define I2C_MASK_SAR                                 ((u32)0x000003FF << 0)                              /*!<R/W 0x55  The sar holds the slave address when the I2C is operating as a slave. For 7-bit addressing, only SAR[6:0] is used.This register can be written only when the I2C interface is disabled, which corresponds to the ENABLEregister being set to 0. Writes at other times have no effect. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_HS_MADDR
 * @brief  I2C High Speed Master Code Address Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_HS_MADDR                           0
#define I2C_MASK_HS_MADDR                            ((u32)0x00000007 << 0)                              /*!<R/W 1  This bit field holds the value of the I2C HS mode master code. HS-mode master codes are reserved 8-bit codes (00001xxx) that are not used for slave addressing or other purposes. Each master has its unique master code; up to eight highspeed mode masters can be present on the same I2C bus system. Valid values are from 0 to 7. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DAT_CMD
 * @brief  I2C Data Buffer and Command Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_NULL_DAT                           11
#define I2C_BIT_NULL_DAT                             ((u32)0x00000001 << 11)                             /*!<W 0  ([11:8] exist if DMA_MODE= 0) This bit controls whether to transfer slave address only. If it's set to 1, then hardware only sends a slave address to bus without data. 1: Send data only without sending slave address. 0: Normal operation. This bit will NOT influence any transfer sequence. */
#define I2C_SHIFT_RSTRT                              10
#define I2C_BIT_RSTRT                                ((u32)0x00000001 << 10)                             /*!<W 0  This bit controls whether a RESTART is issued before the byte is sent or received. 1 : If RESTART_EN is 1, a RESTART is issued before the data is sent/received (according to the value of CMD), regardless of whether or not the transfer direction is changing from the previous command; if RESTART_EN is 0, a STOP followed by a START is issued instead. 0 : If RESTART_EN is 1, a RESTART is issued only if the transfer direction is changing from the previous command; if RESTART_EN is 0, a STOP followed by a START is issued instead. */
#define I2C_SHIFT_STP                                9
#define I2C_BIT_STP                                  ((u32)0x00000001 << 9)                              /*!<W 0  This bit controls whether a STOP is issued after the byte is sent or received. 1 : STOP is issued after this byte, regardless of whether or not the Tx FIFO is empty. If the Tx FIFO is not empty, the master immediately tries to start a new transfer by issuing a START and arbitrating for the bus. 0 : STOP is not issued after this byte, regardless of whether or not the Tx FIFO is empty. If the Tx FIFO is not empty, the master continues the current transfer by sending/receiving data bytes according to the value of the CMD bit. If the Tx FIFO is empty, the master holds the SCL line low and stalls the bus until a new command is available in the Tx FIFO. */
#define I2C_SHIFT_CMD                                8
#define I2C_BIT_CMD                                  ((u32)0x00000001 << 8)                              /*!<W 0  This bit controls whether a read or a write is performed. This bit does not control the direction when the I2C Module acts as a slave. It controls only the direction when it acts as a master. 1 = Read 0 = Write */
#define I2C_SHIFT_DAT                                0
#define I2C_MASK_DAT                                 ((u32)0x000000FF << 0)                              /*!<R/W 0  This register contains the data to be transmitted or received on the I2C bus. If you are writing to this register and want to perform a read, bits 7:0 (DAT) are ignored by the I2C Module. However, when you read this register, these bits return the value of data received on the I2C Module interface. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_SS_SCL_HCNT
 * @brief  Standard Speed I2C Clock SCL High Count Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_HCNT                               0
#define I2C_MASK_HCNT                                ((u32)0x0000FFFF << 0)                              /*!<R/W 0x190  This register sets the SCL clock high-period count for standard speed. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_SS_SCL_LCNT
 * @brief  Standard Speed I2C Clock SCL Low Count Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_LCNT                               0
#define I2C_MASK_LCNT                                ((u32)0x0000FFFF << 0)                              /*!<R/W 0x1D6  This register sets the SCL clock low period count for standard speed. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_FS_SCL_HCNT
 * @brief  Fast Speed I2C Clock SCL High Count Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_HCNT                               0
#define I2C_MASK_HCNT                                ((u32)0x0000FFFF << 0)                              /*!<R/W 0x3C  This register sets the SCL clock high-period count for fast speed. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_FS_SCL_LCNT
 * @brief  Fast Speed I2C Clock SCL Low Count Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_LCNT                               0
#define I2C_MASK_LCNT                                ((u32)0x0000FFFF << 0)                              /*!<R/W 0x82  This register sets the SCL clock low period count for fast speed. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_HS_SCL_HCNT
 * @brief  High Speed I2C Clock SCL High Count Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_HCNT                               0
#define I2C_MASK_HCNT                                ((u32)0x0000FFFF << 0)                              /*!<R/W 0x6  This register sets the SCL clock high period count for high speed. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_HS_SCL_LCNT
 * @brief  High Speed I2C Clock SCL Low Count Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_LCNT                               0
#define I2C_MASK_LCNT                                ((u32)0x0000FFFF << 0)                              /*!<R/W 0x10  This register sets the SCL clock low period count for high speed. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_INTR_STAT
 * @brief  I2C Interrupt Status Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_INTR_DMA_I2C_DONE                       15
#define I2C_BIT_INTR_DMA_I2C_DONE                         ((u32)0x00000001 << 15)                             /*!<R 0  (Active if DMA_MODE = 1) */
#define I2C_SHIFT_INTR_MS_CODE_DET                        14
#define I2C_BIT_INTR_MS_CODE_DET                          ((u32)0x00000001 << 14)                             /*!<R 0  (Active in HS mode) */
#define I2C_SHIFT_INTR_ADDR1_MATCH                        13
#define I2C_BIT_INTR_ADDR1_MATCH                          ((u32)0x00000001 << 13)                             /*!<R 0  (Active w/wo clock src) */
#define I2C_SHIFT_INTR_ADDR0_MATCH                        12
#define I2C_BIT_INTR_ADDR0_MATCH                          ((u32)0x00000001 << 12)                             /*!<R 0  (Active w/wo clock src) */
#define I2C_SHIFT_INTR_GEN_CALL                           11
#define I2C_BIT_INTR_GEN_CALL                             ((u32)0x00000001 << 11)                             /*!<R 0   */
#define I2C_SHIFT_INTR_STRT_DET                           10
#define I2C_BIT_INTR_STRT_DET                             ((u32)0x00000001 << 10)                             /*!<R 0   */
#define I2C_SHIFT_INTR_STP_DET                            9
#define I2C_BIT_INTR_STP_DET                              ((u32)0x00000001 << 9)                              /*!<R 0   */
#define I2C_SHIFT_INTR_ACT                                8
#define I2C_BIT_INTR_ACT                                  ((u32)0x00000001 << 8)                              /*!<R 0   */
#define I2C_SHIFT_INTR_RX_DONE                            7
#define I2C_BIT_INTR_RX_DONE                              ((u32)0x00000001 << 7)                              /*!<R 0   */
#define I2C_SHIFT_INTR_TX_ABRT                            6
#define I2C_BIT_INTR_TX_ABRT                              ((u32)0x00000001 << 6)                              /*!<R 0   */
#define I2C_SHIFT_INTR_RD_REQ                             5
#define I2C_BIT_INTR_RD_REQ                               ((u32)0x00000001 << 5)                              /*!<R 0   */
#define I2C_SHIFT_INTR_TX_EMPTY                           4
#define I2C_BIT_INTR_TX_EMPTY                             ((u32)0x00000001 << 4)                              /*!<R 0   */
#define I2C_SHIFT_INTR_TX_OVER                            3
#define I2C_BIT_INTR_TX_OVER                              ((u32)0x00000001 << 3)                              /*!<R 0   */
#define I2C_SHIFT_INTR_RX_FULL                            2
#define I2C_BIT_INTR_RX_FULL                              ((u32)0x00000001 << 2)                              /*!<R 0   */
#define I2C_SHIFT_INTR_RX_OVER                            1
#define I2C_BIT_INTR_RX_OVER                              ((u32)0x00000001 << 1)                              /*!<R 0   */
#define I2C_SHIFT_INTR_RX_UNDER                           0
#define I2C_BIT_INTR_RX_UNDER                             ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_INTR_MSK
 * @brief  I2C Interrupt Mask Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_M_DMA_I2C_DONE                       15
#define I2C_BIT_M_DMA_I2C_DONE                         ((u32)0x00000001 << 15)                             /*!<R/W 1   */
#define I2C_SHIFT_M_MS_CODE_DET                        14
#define I2C_BIT_M_MS_CODE_DET                          ((u32)0x00000001 << 14)                             /*!<R/W 1   */
#define I2C_SHIFT_M_ADDR1_MATCH                        13
#define I2C_BIT_M_ADDR1_MATCH                          ((u32)0x00000001 << 13)                             /*!<R/W 1  (active only if SLAVE_DISABLE_1 is 0) */
#define I2C_SHIFT_M_ADDR0_MATCH                        12
#define I2C_BIT_M_ADDR0_MATCH                          ((u32)0x00000001 << 12)                             /*!<R/W 1   */
#define I2C_SHIFT_M_GEN_CALL                           11
#define I2C_BIT_M_GEN_CALL                             ((u32)0x00000001 << 11)                             /*!<R/W 1   */
#define I2C_SHIFT_M_STRT_DET                           10
#define I2C_BIT_M_STRT_DET                             ((u32)0x00000001 << 10)                             /*!<R/W 1   */
#define I2C_SHIFT_M_STP_DET                            9
#define I2C_BIT_M_STP_DET                              ((u32)0x00000001 << 9)                              /*!<R/W 1   */
#define I2C_SHIFT_M_ACT                                8
#define I2C_BIT_M_ACT                                  ((u32)0x00000001 << 8)                              /*!<R/W 1   */
#define I2C_SHIFT_M_RX_DONE                            7
#define I2C_BIT_M_RX_DONE                              ((u32)0x00000001 << 7)                              /*!<R/W 1   */
#define I2C_SHIFT_M_TX_ABRT                            6
#define I2C_BIT_M_TX_ABRT                              ((u32)0x00000001 << 6)                              /*!<R/W 1   */
#define I2C_SHIFT_M_RD_REQ                             5
#define I2C_BIT_M_RD_REQ                               ((u32)0x00000001 << 5)                              /*!<R/W 1   */
#define I2C_SHIFT_M_TX_EMPTY                           4
#define I2C_BIT_M_TX_EMPTY                             ((u32)0x00000001 << 4)                              /*!<R/W 1   */
#define I2C_SHIFT_M_TX_OVER                            3
#define I2C_BIT_M_TX_OVER                              ((u32)0x00000001 << 3)                              /*!<R/W 1   */
#define I2C_SHIFT_M_RX_FULL                            2
#define I2C_BIT_M_RX_FULL                              ((u32)0x00000001 << 2)                              /*!<R/W 1   */
#define I2C_SHIFT_M_RX_OVER                            1
#define I2C_BIT_M_RX_OVER                              ((u32)0x00000001 << 1)                              /*!<R/W 1   */
#define I2C_SHIFT_M_RX_UNDER                           0
#define I2C_BIT_M_RX_UNDER                             ((u32)0x00000001 << 0)                              /*!<R/W 1   */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_RAW_INTR_STAT
 * @brief  I2C Raw Interrupt Status Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_RAW_DMA_I2C_DONE                       15
#define I2C_BIT_RAW_DMA_I2C_DONE                         ((u32)0x00000001 << 15)                             /*!<R 0  Indicates whether I2C DMA operation is done. */
#define I2C_SHIFT_RAW_MS_CODE_DET                        14
#define I2C_BIT_RAW_MS_CODE_DET                          ((u32)0x00000001 << 14)                             /*!<R 0  Indicates whether master code is detected. */
#define I2C_SHIFT_RAW_ADDR1_MATCH                        13
#define I2C_BIT_RAW_ADDR1_MATCH                          ((u32)0x00000001 << 13)                             /*!<R 0  Indicates whether an address matches with slave address 1 when acting as a slave. */
#define I2C_SHIFT_RAW_ADDR0_MATCH                        12
#define I2C_BIT_RAW_ADDR0_MATCH                          ((u32)0x00000001 << 12)                             /*!<R 0  Indicates whether an address matches with slave address 0 when acting as a slave. */
#define I2C_SHIFT_RAW_GEN_CALL                           11
#define I2C_BIT_RAW_GEN_CALL                             ((u32)0x00000001 << 11)                             /*!<R 0  Set only when a General Call address is received and it is acknowledged. It stays set until it is cleared either by disabling I2C Module or when the CPU reads bit 0 of the CLR_GEN_CALL register. The received data is stored in the Rx buffer. */
#define I2C_SHIFT_RAW_STRT_DET                           10
#define I2C_BIT_RAW_STRT_DET                             ((u32)0x00000001 << 10)                             /*!<R 0  Indicates whether a START or RESTART condition has occurred on the I2C interface regardless of whether I2C Module is operating in slave or master mode. */
#define I2C_SHIFT_RAW_STP_DET                            9
#define I2C_BIT_RAW_STP_DET                              ((u32)0x00000001 << 9)                              /*!<R 0  Indicates whether a STOP condition has occurred on the I2C interface regardless of whether I2C Module is operating in slave or master mode. */
#define I2C_SHIFT_RAW_ACT                                8
#define I2C_BIT_RAW_ACT                                  ((u32)0x00000001 << 8)                              /*!<R 0  This bit captures I2C Module activity and stays set until it is cleared. There are four ways to clear it: - Disabling the I2C Module - Reading the CLR_ACTIVITY register - Reading the CLR_INTR register - System reset Once this bit is set, it stays set unless one of the four methods is used to clear it. Even if the I2C Module module is idle, this bit remains set until cleared, indicating that there was activity on the bus. */
#define I2C_SHIFT_RAW_RX_DONE                            7
#define I2C_BIT_RAW_RX_DONE                              ((u32)0x00000001 << 7)                              /*!<R 0  When the I2C Module is acting as a slave-transmitter, this bit is set to 1 if the master does not acknowledge a transmitted byte. This occurs on the last byte of the transmission, indicating that the transmission is done. */
#define I2C_SHIFT_RAW_TX_ABRT                            6
#define I2C_BIT_RAW_TX_ABRT                              ((u32)0x00000001 << 6)                              /*!<R 0  This bit indicates if I2C Module, as an I2C transmitter, is unable to complete the intended actions on the contents of the transmit FIFO. This situation can occur both as an I2C master or an I2C slave, and is referred to as a Transmit Abort. When this bit is set to 1, the TX_ABRT_SOURCE register indicates the reason why the transmit abort takes places */
#define I2C_SHIFT_RAW_RD_REQ                             5
#define I2C_BIT_RAW_RD_REQ                               ((u32)0x00000001 << 5)                              /*!<R 0  This bit is set to 1 when I2C Module is acting as a slave and another I2C master is attempting to read data from I2C Module. The I2C Module holds the I2C bus in a wait state (SCL=0) until this interrupt is serviced, which means that the slave has been addressed by a remote master that is asking for data to be transferred. The processor must respond to this interrupt and then write the requested data to the DATA_CMD register. This bit is set to 0 just after the processor reads the CLR_RD_REQ register. */
#define I2C_SHIFT_RAW_TX_EMPTY                           4
#define I2C_BIT_RAW_TX_EMPTY                             ((u32)0x00000001 << 4)                              /*!<R 0  This bit is set to 1 when the transmit buffer is at or below the threshold value set in the TX_TL register. It is automatically cleared by hardware when the buffer level goes above the threshold. When the ENABLE bit 0 is 0, the TX FIFO is flushed and held in reset. There the TX FIFO looks like it has no data within it, so this bit is set to 1, provided there is activity in the master or slave state machines. When there is no longer activity, then with en=0, this bit is set to 0. */
#define I2C_SHIFT_RAW_TX_OVER                            3
#define I2C_BIT_RAW_TX_OVER                              ((u32)0x00000001 << 3)                              /*!<R 0  Set during transmit if the transmit buffer is filled to TX_BUFFER_DEPTH and the processor attempts to issue another I2C command by writing to the DATA_CMD register. When the module is disabled, this bit keeps its level until the master or slave state machines go into idle, and when en goes to 0, this interrupt is cleared. */
#define I2C_SHIFT_RAW_RX_FULL                            2
#define I2C_BIT_RAW_RX_FULL                              ((u32)0x00000001 << 2)                              /*!<R 0  Set when the receive buffer reaches or goes above the RX_TL threshold in the rx_tl register. It is automatically cleared by hardware when buffer level goes below the threshold. If the module is disabled (ENABLE[0]=0), the RX FIFO is flushed and held in reset; therefore the RX FIFO is not full. So this bit is cleared once the ENABLE bit 0 is programmed with a 0, regardless of the activity that continues. */
#define I2C_SHIFT_RAW_RX_OVER                            1
#define I2C_BIT_RAW_RX_OVER                              ((u32)0x00000001 << 1)                              /*!<R 0  Set if the receive buffer is completely filled to RX_BUFFER_DEPTH and an additional byte is received from an external I2C device. The I2C Module acknowledges this, but any data bytes received after the FIFO is full are lost. If the module is disabled (ENABLE[0]=0), this bit keeps its level until the master or slave state machines go into idle, and when en goes to 0, this interrupt is cleared. */
#define I2C_SHIFT_RAW_RX_UNDER                           0
#define I2C_BIT_RAW_RX_UNDER                             ((u32)0x00000001 << 0)                              /*!<R 0  Set if the processor attempts to read the receive buffer when it is empty by reading from the data_cmd register. If the module is disabled (ENABLE[0]=0), this bit keeps its level until the master or slave state machines go into idle, and when en goes to 0, this interrupt is cleared. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_RX_TL
 * @brief  I2C Receive FIFO Threshold Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_RX_TL                              0
#define I2C_MASK_RX_TL                               ((u32)0x000000FF << 0)                              /*!<R/W 0xB  Receive FIFO Threshold Level Controls the level of entries (or above) that triggers the RX_FULLinterrupt (bit 2 in RAW_INTR_STAT register). The valid range is 0-255, with the additional restriction that hardware does not allow this value to be set to a value larger than the depth of the buffer. If an attempt is made to do that, the actual value set will be the maximum depth of the buffer.A value of 0 sets the threshold for 1 entry, and a value of 255 sets the threshold for 256 entries. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_TX_TL
 * @brief  I2C Transmit FIFO Threshold Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_TX_TL                              0
#define I2C_MASK_TX_TL                               ((u32)0x000000FF << 0)                              /*!<R/W 0x3  Transmit FIFO Threshold Level Controls the level of entries (or below) that trigger the TX_EMPTYinterrupt (bit 4 in RAW_INTR_STAT register). The valid range is 0-255, with the additional restriction that it may not be set to value larger than the depth of the buffer. If an attempt is made to do that, the actual value set will be the maximum depth of the buffer.A value of 0 sets the threshold for 0 entries, and a value of 255 sets the threshold for 255 entries. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_INTR
 * @brief  Clear Combined and Individual Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_INTR                           0
#define I2C_BIT_CLR_INTR                             ((u32)0x00000001 << 0)                              /*!<R 0  Read this register to clear the combined interrupt, all individual interrupts, and the TX_ABRT_SOURCE register. This bit does not clear hardware clearable interrupts but software clearable interrupts. Refer to Bit 9 of the TX_ABRT_SOURCE register for an exception to clearing TX_ABRT_SOURCE. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_RX_UNDER
 * @brief  Clear RX_UNDER Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_RX_UNDER                       0
#define I2C_BIT_CLR_RX_UNDER                         ((u32)0x00000001 << 0)                              /*!<R 0  Read this register to clear the rx_under interrupt (bit 0) of the raw_intr_stat register */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_RX_OVER
 * @brief  Clear RX_OVER Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_RX_OVER                        0
#define I2C_BIT_CLR_RX_OVER                          ((u32)0x00000001 << 0)                              /*!<R 0  Read this register to clear the rx_over interrupt (bit 1) of the raw_intr_stat register */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_TX_OVER
 * @brief  Clear TX_OVER Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_TX_OVER                        0
#define I2C_BIT_CLR_TX_OVER                          ((u32)0x00000001 << 0)                              /*!<R 0  Read this register to clear the tx_over interrupt (bit 3) of the raw_intr_stat register. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_RD_REQ
 * @brief  Clear RD_REQ Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_RD_REQ                         0
#define I2C_BIT_CLR_RD_REQ                           ((u32)0x00000001 << 0)                              /*!<R 0  Read this register to clear the rd_req interrupt (bit 5) of the raw_intr_stat register */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_TX_ABRT
 * @brief  Clear TX_ABRT Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_TX_ABRT                        0
#define I2C_BIT_CLR_TX_ABRT                          ((u32)0x00000001 << 0)                              /*!<R 0  Read this register to clear the tx_abrt interrupt (bit 6) of the raw_intr_stat register, and the tx_abrt_src register.This also releases the tx fifo from the flushed/reset state, allowing more writes to the TX FIFO. Refer to Bit 9 of the tx_abrt_src register for an exception to clearing tx_abrt_src. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_RX_DONE
 * @brief  Clear RX_DONE Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_RX_DONE                        0
#define I2C_BIT_CLR_RX_DONE                          ((u32)0x00000001 << 0)                              /*!<R 0  Read this register to clear the rx_done interrupt (bit 7) of the raw_intr_stat register */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_ACT
 * @brief  Clear ACTIVITY Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_ACT                            0
#define I2C_BIT_CLR_ACT                              ((u32)0x00000001 << 0)                              /*!<R 0  Reading this register clears the activity interrupt if the I2C is not active anymore. If the I2C module is still active on the bus, the activity interrupt bit continues to be set. It is automatically cleared by hardware if the module is disabled and if there is no further activity on the bus. The value read from this register to get status of the activity interrupt (bit 8) of the raw_intr_stat register. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_STP_DET
 * @brief  Clear STOP_DET Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_STP_DET                        0
#define I2C_BIT_CLR_STP_DET                          ((u32)0x00000001 << 0)                              /*!<R 0  Read this register to clear the stop_det interrupt (bit 9) of the raw_intr_stat register. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_STRT_DET
 * @brief  Clear START_DET Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_STRT_DET                       0
#define I2C_BIT_CLR_STRT_DET                         ((u32)0x00000001 << 0)                              /*!<R 0  Read this register to clear the start_det interrupt (bit 10) of the raw_intr_stat register. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_GEN_CALL
 * @brief  Clear GEN_CALL Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_GEN_CALL                       0
#define I2C_BIT_CLR_GEN_CALL                         ((u32)0x00000001 << 0)                              /*!<R 0  Read this register to clear the gen_call interrupt (bit 11) of raw_intr_stat register */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_ENABLE
 * @brief  I2C Enable Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_ABRT                               1
#define I2C_BIT_ABRT                                 ((u32)0x00000001 << 1)                              /*!<R/W 0  Abort I2C current transfer is done w/o flush Tx/Rx FIFO */
#define I2C_SHIFT_EN                                 0
#define I2C_BIT_EN                                   ((u32)0x00000001 << 0)                              /*!<R/W 0  Controls whether the I2C Module is enabled. 0: Disables I2C Module (TX and RX FIFOs are held in an erased state) 1: Enables I2C Module */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_STS
 * @brief  I2C Status Reigster
 * @{
 *****************************************************************************/
#define I2C_SHIFT_STS_BUS_STS                            11
#define I2C_MASK_STS_BUS_STS                             ((u32)0x00000003 << 11)                             /*!<R/W 0  Show current I2C bus status 00 indicates I2C bus is in idle 01: I2C bus is in address phase 10: I2C bus is in data phase 11: I2C bus is in clock stretch phase */
#define I2C_SHIFT_STS_SLV_HOLD_RX_FULL                   10
#define I2C_BIT_STS_SLV_HOLD_RX_FULL                     ((u32)0x00000001 << 10)                             /*!<R 0  1: I2C module is holding I2C bus low (clock stretch) because of RX FIFO full in slave mode. */
#define I2C_SHIFT_STS_SLV_HOLD_TX_EMPTY                  9
#define I2C_BIT_STS_SLV_HOLD_TX_EMPTY                    ((u32)0x00000001 << 9)                              /*!<R 0  1: I2C module is holding I2C bus low (clock stretch) because of TX FIFO empty in slave mode. */
#define I2C_SHIFT_STS_MST_HOLD_RX_FULL                   8
#define I2C_BIT_STS_MST_HOLD_RX_FULL                     ((u32)0x00000001 << 8)                              /*!<R 0  1: I2C module is holding I2C bus low (clock stretch) because of RX FIFO full in master mode. */
#define I2C_SHIFT_STS_MST_HOLD_TX_EMPTY                  7
#define I2C_BIT_STS_MST_HOLD_TX_EMPTY                    ((u32)0x00000001 << 7)                              /*!<R 0  1: I2C module is holding I2C bus low (clock stretch) because of TX FIFO empty in master mode. */
#define I2C_SHIFT_STS_SLV_ACT                            6
#define I2C_BIT_STS_SLV_ACT                              ((u32)0x00000001 << 6)                              /*!<R 0  Slave FSM Activity Status. When the Slave Finite State Machine (FSM) is not in the IDLE state, this bit is set. 0: Slave FSM is in IDLE state so the Slave part of I2C Module is not Active 1: Slave FSM is not in IDLE state so the Slave part of I2C Module is Active */
#define I2C_SHIFT_STS_MST_ACT                            5
#define I2C_BIT_STS_MST_ACT                              ((u32)0x00000001 << 5)                              /*!<R 0  Master FSM Activity Status. When the Master Finite State Machine (FSM) is not in the IDLE state, this bit is set. 0: Master FSM is in IDLE state so the Master part of I2C Module is not Active 1: Master FSM is not in IDLE state so the Master part of I2C Module is Active */
#define I2C_SHIFT_STS_RFF                                4
#define I2C_BIT_STS_RFF                                  ((u32)0x00000001 << 4)                              /*!<R 0  Receive FIFO CompletelyFull. When the receive FIFO iscompletely full, this bit is set. When the receive FIFO contains one or more empty location, this bit is cleared. 0: Receive FIFO is not full 1: Receive FIFO is full */
#define I2C_SHIFT_STS_RFNE                               3
#define I2C_BIT_STS_RFNE                                 ((u32)0x00000001 << 3)                              /*!<R 0  Receive FIFO Not Empty. This bit is set when the receive FIFO contains one or more entries; it is cleared when the receive FIFO is empty. 0: Receive FIFO is empty 1: Receive FIFO is not empty */
#define I2C_SHIFT_STS_TFE                                2
#define I2C_BIT_STS_TFE                                  ((u32)0x00000001 << 2)                              /*!<R 1  Transmit FIFO Completely Empty. When the transmit FIFO is completely empty, this bit is set. When it contains one or morevalid entries, this bit is cleared. This bit field does not request an interrupt. 0: Transmit FIFO is not empty 1: Transmit FIFO is empty */
#define I2C_SHIFT_STS_TFNF                               1
#define I2C_BIT_STS_TFNF                                 ((u32)0x00000001 << 1)                              /*!<R 1  Transmit FIFO Not Full. Set when the transmit FIFO contains one or more empty locations, and is cleared when the FIFO is full. 0: Transmit FIFO is full 1: Transmit FIFO is not full */
#define I2C_SHIFT_STS_ACT                                0
#define I2C_BIT_STS_ACT                                  ((u32)0x00000001 << 0)                              /*!<R 0  I2C Activity Status. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_TXFLR
 * @brief  I2C Transmit FIFO Level Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_TXFLR                              0
#define I2C_MASK_TXFLR                               ((u32)0x0000001F << 0)                              /*!<R 0  Transmit FIFO Level. Contains the number of valid data entries in the transmit FIFO. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_RXFLR
 * @brief  I2C Receive FIFO Level Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_RXFLR                              0
#define I2C_MASK_RXFLR                               ((u32)0x0000001F << 0)                              /*!<R 0  Receive FIFO Level. Contains the number of valid data entries in the receive FIFO. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_SDA_HOLD
 * @brief  I2C SDA Hold Time Length Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_SDA_HOLD                           0
#define I2C_MASK_SDA_HOLD                            ((u32)0x0000FFFF << 0)                              /*!<R/W 1  Sets the required SDA hold timein units of clk period. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_TX_ABRT_SRC
 * @brief  I2C Transmit Abort Source Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_SLVRD_INTX                         15
#define I2C_BIT_SLVRD_INTX                           ((u32)0x00000001 << 15)                             /*!<R 0  1: When the processor side responds to a slave mode request for data to be transmitted to a remote master and user writes a 1 in cmd(bit 8) of dat_cmd register. */
#define I2C_SHIFT_SLV_ARBLOST                        14
#define I2C_BIT_SLV_ARBLOST                          ((u32)0x00000001 << 14)                             /*!<R 0  1: Slave lost the bus while transmitting data to a remote master. Tx_abrt_src[12] is set at the same time. */
#define I2C_SHIFT_SLVFLUSH_TXFIFO                    13
#define I2C_BIT_SLVFLUSH_TXFIFO                      ((u32)0x00000001 << 13)                             /*!<R 0  1: Slave has received a read command and some data exists in the TX FIFO so the slave issues a tx_abrt interrupt to flush old data in TX FIFO. */
#define I2C_SHIFT_ARB_LOST                           12
#define I2C_BIT_ARB_LOST                             ((u32)0x00000001 << 12)                             /*!<R 0  1: Master has lost arbitration, or if tx_abrt_src[14] is also set, then the slave transmitter has lost arbitration. */
#define I2C_SHIFT_MST_DIS                            11
#define I2C_BIT_MST_DIS                              ((u32)0x00000001 << 11)                             /*!<R 0  1: User tries to initiate a Master operation with the Master mode disabled. */
#define I2C_SHIFT_NORSTRT_10BIT_RD                   10
#define I2C_BIT_NORSTRT_10BIT_RD                     ((u32)0x00000001 << 10)                             /*!<R 0  1: The restart is disabled (rstrt_en bit (con[5]) = 0) and the master sends a read command in 10-bit addressing mode. */
#define I2C_SHIFT_NORSTRT_SBYTE                      9
#define I2C_BIT_NORSTRT_SBYTE                        ((u32)0x00000001 << 9)                              /*!<R 0  1: The restart is disabled (rstrt_en bit con[5]) = 0) and the user is trying to send a START Byte. */
#define I2C_SHIFT_NORSTRT_HS                         8
#define I2C_BIT_NORSTRT_HS                           ((u32)0x00000001 << 8)                              /*!<R 0  1: The restart is disabled (rstrt_en bit (con[5]) = 0) and the user is trying to use the master to transfer data in High Speed mode. */
#define I2C_SHIFT_SBYTE_ACKDET                       7
#define I2C_BIT_SBYTE_ACKDET                         ((u32)0x00000001 << 7)                              /*!<R 0  1: Master has sent a START Byte and the START Byte was acknowledged (wrong behavior). */
#define I2C_SHIFT_HS_ACKDET                          6
#define I2C_BIT_HS_ACKDET                            ((u32)0x00000001 << 6)                              /*!<R 0  1: Master is in High Speed mode and the High Speed Master code was acknowledged (wrong behavior). */
#define I2C_SHIFT_GCALL_RD                           5
#define I2C_BIT_GCALL_RD                             ((u32)0x00000001 << 5)                              /*!<R 0  1: I2C Module in master mode sent a General Call but the user programmed the byte following the General Call to be a read from the bus (dat_cmd[9] is set to 1). */
#define I2C_SHIFT_GCALL_NACK                         4
#define I2C_BIT_GCALL_NACK                           ((u32)0x00000001 << 4)                              /*!<R 0  1: I2C Module in master mode sent a General Call and no slave on the bus acknowledged the General Call. */
#define I2C_SHIFT_TXDAT_NACK                         3
#define I2C_BIT_TXDAT_NACK                           ((u32)0x00000001 << 3)                              /*!<R 0  1: This is a master-mode only bit. Master has received an acknowledgement for the address, but when it sent data byte(s) following the address, it did not receive an acknowledge from the remote slave(s). */
#define I2C_SHIFT_ADDR2_10BIT_NACK                   2
#define I2C_BIT_ADDR2_10BIT_NACK                     ((u32)0x00000001 << 2)                              /*!<R 0  1: Master is in 10-bit address mode and the second address byte of the 10-bit address was not acknowledged by any slave. */
#define I2C_SHIFT_ADDR1_10BIT_NACK                   1
#define I2C_BIT_ADDR1_10BIT_NACK                     ((u32)0x00000001 << 1)                              /*!<R 0  1: Master is in 10-bit address mode and the first 10-bit address byte was not acknowledged by any slave. */
#define I2C_SHIFT_ADDR_7BIT_NACK                     0
#define I2C_BIT_ADDR_7BIT_NACK                       ((u32)0x00000001 << 0)                              /*!<R 0  1: Master is in 7-bit addressing mode and the address sent was not acknowledged by any slave. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_SLV_DAT_NACK
 * @brief  I2C Generate Slave Data NACK Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_SLV_DAT_NACK                       0
#define I2C_BIT_SLV_DAT_NACK                         ((u32)0x00000001 << 0)                              /*!<R/W 0  Generate NACK. This NACK generation only occurs when I2C Module is a slavereceiver. If this register is set to a value of 1, it can only generate a NACK after a data byte is received; hence, the data transfer is aborted and the data received is not pushed to the receive buffer. When the register is set to a value of 0, it generates NACK/ACK, depending on normal criteria. 1 = generate NACK after data byte received 0 = generate NACK/ACK normally */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DMA_CR
 * @brief  I2C DMA Control Reigster
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DMA_TDMAE                              1
#define I2C_BIT_DMA_TDMAE                                ((u32)0x00000001 << 1)                              /*!<R/W 0  Transmit DMA Enable. This bit enables/disables the transmit FIFO DMA channel. 0 = Transmit DMA disabled 1 = Transmit DMA enabled */
#define I2C_SHIFT_DMA_RDMAE                              0
#define I2C_BIT_DMA_RDMAE                                ((u32)0x00000001 << 0)                              /*!<R/W 0  Receive DMA Enable. This bit enables/disables the receive FIFO DMA channel. 0 = Receive DMA disabled 1 = Receive DMA enabled  */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DMA_TDLR
 * @brief  I2C DMA Transmit Data Level Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DMA_TDLR                               0
#define I2C_MASK_DMA_TDLR                                ((u32)0x0000000F << 0)                              /*!<R/W 0  Transmit Data Level. This bit field controls the level at which a DMA request is made by the transmit logic. It is equal to the watermark level; that is, the dma_tx_req signal is generated when the number of valid data entries in the transmit FIFO is equal to or below this field value, and tdmae= 1. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DMA_RDLR
 * @brief  I2C DMA Receive Data Level Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DMA_RDLR                               0
#define I2C_MASK_DMA_RDLR                                ((u32)0x0000000F << 0)                              /*!<R/W 0  Receive Data Level. This bit field controls the level at which a DMA request is made by the receive logic. The watermark level = DMARDL+1; that is, dma_rx_req is generated when the number of valid data entries in the receive FIFO is equal to or more than this field value + 1, and RDMAE =1. For instance, when DMARDLis 0, then dma_rx_req is asserted when 1 or more data entries are present in the receive FIFO. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_SDA_SETUP
 * @brief  I2C SDA Setup Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_SDA_SETUP                          0
#define I2C_MASK_SDA_SETUP                           ((u32)0x000000FF << 0)                              /*!<R/W 0x38  SDA Setup. It is recommended that if the required delay is 1000ns, then for an clk frequency of 10 MHz, SDA_SETUP should be programmed to a value of 11. SDA_SETUP must be programmed with a minimum value of 2. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_ACK_GEN_CALL
 * @brief  I2C ACK General Call Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_ACK_GEN_CALL                       0
#define I2C_BIT_ACK_GEN_CALL                         ((u32)0x00000001 << 0)                              /*!<R/W 1  ACK General Call. When set to 1, I2C Module responds with a ACK (by asserting data_oe) when it receives a General Call. When set to 0, the I2C Module does not generate General Call interrupts. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_EN_STS
 * @brief  I2C Enable Status Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DMA_DIS_STS                        3
#define I2C_MASK_DMA_DIS_STS                         ((u32)0x00000003 << 3)                              /*!<R 0  DMA_DISABLE_WHILE_BUSY. 00: No ill disable event is active 01: I2C is disable while busy in legacy mode 10: I2C is disable while busy in DMA mode 11: I2C is disable while busy in Descriptor mode */
#define I2C_SHIFT_SLV_RX_DAT_LOST                    2
#define I2C_BIT_SLV_RX_DAT_LOST                      ((u32)0x00000001 << 2)                              /*!<R 0  Slave Received Data Lost. This bit indicates if a Slave-Receiver operation has been aborted with at least one data byte received from an I2C transfer due to the setting of enable from 1 to 0. */
#define I2C_SHIFT_SLV_DIS_IN_BUSY                    1
#define I2C_BIT_SLV_DIS_IN_BUSY                      ((u32)0x00000001 << 1)                              /*!<R 0  Slave Disabled While Busy (Transmit, Receive). This bit indicates if a potential or active Slave operation has been aborted due to the setting of the ENABLE register from 1 to 0. */
#define I2C_SHIFT_EN_STS                                 0
#define I2C_BIT_EN_STS                                   ((u32)0x00000001 << 0)                              /*!<R 0  Enable Status. This bit always reflects the value driven on the output port en. When read as 1, I2C Module is deemed to be in an enabled state. When read as 0, I2C Module is deemed completely inactive. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DMA_CMD
 * @brief  I2C DMA Command Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DMA_RSTRT                              7
#define I2C_BIT_DMA_RSTRT                                ((u32)0x00000001 << 7)                              /*!<R/W 0  This bit controls whether a RESTART is issued before the byte is sent or received when DMA mode is enabled. */
#define I2C_SHIFT_DMA_STP                                6
#define I2C_BIT_DMA_STP                                  ((u32)0x00000001 << 6)                              /*!<R/W 0  This bit controls whether a STOP is issued after the byte is sent or received.  */
#define I2C_SHIFT_DMA_CMD                                5
#define I2C_BIT_DMA_CMD                                  ((u32)0x00000001 << 5)                              /*!<R/W 0  This bit controls whether a read or a write is performed. This bit does not control the direction when the I2C Module acts as a slave. It controls only the direction when it acts as a master. 1 = Read 0 = Write */
#define I2C_SHIFT_DMA_EN                                 0
#define I2C_BIT_DMA_EN                                   ((u32)0x00000001 << 0)                              /*!<R/W 0  Set to enable DMA mode. Clear when transfer is done. */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DMA_LEN
 * @brief  I2C DMA Transfer Data Length Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DMA_TR_LEN                             16
#define I2C_MASK_DMA_TR_LEN                              ((u32)0x0000FFFF << 16)                             /*!<R 0  DMA mode transfer bytes(Read only) */
#define I2C_SHIFT_DMA_LEN                                0
#define I2C_MASK_DMA_LEN                                 ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DMA transfer data length(R/W) */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DMA_MOD
 * @brief  I2C DMA Mode Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DMA_MOD                            0
#define I2C_MASK_DMA_MOD                             ((u32)0x00000003 << 0)                              /*!<R/W 0  DMA operation mode 0 is for legacy mode 1 is for DMA with control register 2 is for DMA with transfer descriptor */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_SLP
 * @brief  I2C Sleep Control Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_SLP_CLK_GATED                      1
#define I2C_BIT_SLP_CLK_GATED                        ((u32)0x00000001 << 1)                              /*!<R 0  I2C clock has been gated (Read Only) */
#define I2C_SHIFT_CLK_CTRL                           0
#define I2C_BIT_CLK_CTRL                             ((u32)0x00000001 << 0)                              /*!<R/W 0  I2C clock control, write 1 controller would gate I2C clock until I2C slave is enable and reset synchronized register procedure is done */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DAT_FLTR_RSTS_L
 * @brief  Data Filter Resistor Low Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DAT_FLTR_RSTS_L                    0
#define I2C_MASK_DAT_FLTR_RSTS_L                     ((u32)0x000FFFFF << 0)                              /*!<R/W 0  Data Filter Resistor Low */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DAT_FLTR_RSTS_M
 * @brief  Data Filter Resistor Main Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DAT_FLTR_RSTS_M                    0
#define I2C_MASK_DAT_FLTR_RSTS_M                     ((u32)0x000FFFFF << 0)                              /*!<R/W 0  Data Filter Resistor Main */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLK_FLTR_RSTS_L
 * @brief  Clock Filter Resistor Low Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLK_FLTR_RSTS_L                    0
#define I2C_MASK_CLK_FLTR_RSTS_L                     ((u32)0x000FFFFF << 0)                              /*!<R/W 0  Clock Filter Resistor Low */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLK_FLTR_RSTS_M
 * @brief  Clock Filter Resistor Main Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLK_FLTR_RSTS_M                    0
#define I2C_MASK_CLK_FLTR_RSTS_M                     ((u32)0x000FFFFF << 0)                              /*!<R/W 0  Clock Filter Resistor Main */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DAT_FLTR_CAP_L
 * @brief  Data Filter Capacitor Low Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DAT_FLTR_CAP_L                     0
#define I2C_MASK_DAT_FLTR_CAP_L                      ((u32)0x000FFFFF << 0)                              /*!<R/W 0  Data Filter Capacitor Low */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_DAT_FLTR_CAP_M
 * @brief  Data Filter Capacitor Main Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DAT_FLTR_CAP_M                     0
#define I2C_MASK_DAT_FLTR_CAP_M                      ((u32)0x0000001F << 0)                              /*!<R/W 0  Data Filter Capacitor Main */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLK_FLTR_CAP_L
 * @brief  Clock Filter Capacitor Low Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLK_FLTR_CAP_L                     0
#define I2C_MASK_CLK_FLTR_CAP_L                      ((u32)0x000FFFFF << 0)                              /*!<R/W 0  Clock Filter Capacitor Low */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLK_FLTR_CAP_M
 * @brief  Clock Filter Capacitor Main Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLK_FLTR_CAP_M                     0
#define I2C_MASK_CLK_FLTR_CAP_M                      ((u32)0x0000001F << 0)                              /*!<R/W 0  Clock Filter Capacitor Main */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_ADDR_MATCH
 * @brief  Clear I2C ADDR_MATCH Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_ADDR_MATCH                     0
#define I2C_BIT_CLR_ADDR_MATCH                       ((u32)0x00000001 << 0)                              /*!<R/W 0  Address match interrupts raw status, and read clear. ADDR_MATCH_* raw status clear 0:addr_match_raw */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_CLR_DMA_DONE
 * @brief  Clear I2C DMA_DONE Interrupt Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_CLR_DMA_DONE                       0
#define I2C_BIT_CLR_DMA_DONE                         ((u32)0x00000001 << 0)                              /*!<R/W 0  dma_i2c_done_intr interrupts raw status, and read clear 0: rx_packet_miss_raw */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_FLTR
 * @brief  I2C Bus Filter Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_DIG_FLTR_EN                        8
#define I2C_BIT_DIG_FLTR_EN                          ((u32)0x00000001 << 8)                              /*!<R/W 0  I2C module digital filter slection (enable) */
#define I2C_SHIFT_DIG_FLTR_DEG                       0
#define I2C_MASK_DIG_FLTR_DEG                        ((u32)0x0000000F << 0)                              /*!<R/W 0  I2C module digital filter degree */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_SAR1
 * @brief  I2C Slave Address 1 Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_SAR1                               0
#define I2C_MASK_SAR1                                ((u32)0x0000007F << 0)                              /*!<R/W 0x12  I2C Second Slave Address */
/** @} */

/**************************************************************************//**
 * @defgroup I2C_TYPE_VER
 * @brief  I2C Component Version Register
 * @{
 *****************************************************************************/
#define I2C_SHIFT_VER                                0
#define I2C_MASK_VER                                 ((u32)0xFFFFFFFF << 0)                              /*!<R 0x5245414C  I2C module version number (0x5245414C) */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_I2C_TYPE
 * @{
 * @brief rtl8735b_I2C_TYPE Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t I2C_CON ;                                /*!<  I2C Control Register register,  Address offset: 0x000 */
	__IO uint32_t I2C_TAR ;                                /*!<  I2C Target Address Register register,  Address offset: 0x004 */
	__IO uint32_t I2C_SAR  ;                               /*!<  I2C Slave Address Register register,  Address offset: 0x008 */
	__IO uint32_t I2C_HS_MADDR ;                           /*!<  I2C High Speed Master Code Address Register register,  Address offset: 0x00C */
	__IO uint32_t I2C_DAT_CMD ;                            /*!<  I2C Data Buffer and Command Register register,  Address offset: 0x010 */
	__IO uint32_t I2C_SS_SCL_HCNT ;                        /*!<  Standard Speed I2C Clock SCL High Count Register register,  Address offset: 0x014 */
	__IO uint32_t I2C_SS_SCL_LCNT ;                        /*!<  Standard Speed I2C Clock SCL Low Count Register register,  Address offset: 0x018 */
	__IO uint32_t I2C_FS_SCL_HCNT ;                        /*!<  Fast Speed I2C Clock SCL High Count Register register,  Address offset: 0x01C */
	__IO uint32_t I2C_FS_SCL_LCNT ;                        /*!<  Fast Speed I2C Clock SCL Low Count Register register,  Address offset: 0x020 */
	__IO uint32_t I2C_HS_SCL_HCNT ;                        /*!<  High Speed I2C Clock SCL High Count Register register,  Address offset: 0x024 */
	__IO uint32_t I2C_HS_SCL_LCNT ;                        /*!<  High Speed I2C Clock SCL Low Count Register register,  Address offset: 0x028 */
	__I  uint32_t I2C_INTR_STAT ;                          /*!<  I2C Interrupt Status Register register,  Address offset: 0x02C */
	__IO uint32_t I2C_INTR_MSK ;                           /*!<  I2C Interrupt Mask Register register,  Address offset: 0x030 */
	__I  uint32_t I2C_RAW_INTR_STAT ;                      /*!<  I2C Raw Interrupt Status Register register,  Address offset: 0x034 */
	__IO uint32_t I2C_RX_TL ;                              /*!<  I2C Receive FIFO Threshold Register register,  Address offset: 0x038 */
	__IO uint32_t I2C_TX_TL ;                              /*!<  I2C Transmit FIFO Threshold Register register,  Address offset: 0x03C */
	__IO uint32_t I2C_CLR_INTR ;                           /*!<  Clear Combined and Individual Interrupt Register register,  Address offset: 0x040 */
	__IO uint32_t I2C_CLR_RX_UNDER ;                       /*!<  Clear RX_UNDER Interrupt Register register,  Address offset: 0x044 */
	__IO uint32_t I2C_CLR_RX_OVER ;                        /*!<  Clear RX_OVER Interrupt Register register,  Address offset: 0x048 */
	__IO uint32_t I2C_CLR_TX_OVER ;                        /*!<  Clear TX_OVER Interrupt Register register,  Address offset: 0x04C */
	__IO uint32_t I2C_CLR_RD_REQ ;                         /*!<  Clear RD_REQ Interrupt Register register,  Address offset: 0x050 */
	__IO uint32_t I2C_CLR_TX_ABRT ;                        /*!<  Clear TX_ABRT Interrupt Register register,  Address offset: 0x054 */
	__IO uint32_t I2C_CLR_RX_DONE ;                        /*!<  Clear RX_DONE Interrupt Register register,  Address offset: 0x058 */
	__IO uint32_t I2C_CLR_ACT ;                            /*!<  Clear ACTIVITY Interrupt Register register,  Address offset: 0x05C */
	__IO uint32_t I2C_CLR_STP_DET ;                        /*!<  Clear STOP_DET Interrupt Register register,  Address offset: 0x060 */
	__IO uint32_t I2C_CLR_STRT_DET ;                       /*!<  Clear START_DET Interrupt Register register,  Address offset: 0x064 */
	__IO uint32_t I2C_CLR_GEN_CALL ;                       /*!<  Clear GEN_CALL Interrupt Register register,  Address offset: 0x068 */
	__IO uint32_t I2C_ENABLE ;                             /*!<  I2C Enable Register register,  Address offset: 0x06C */
	__IO uint32_t I2C_STS ;                                /*!<  I2C Status Reigster register,  Address offset: 0x070 */
	__I  uint32_t I2C_TXFLR ;                              /*!<  I2C Transmit FIFO Level Register register,  Address offset: 0x074 */
	__I  uint32_t I2C_RXFLR ;                              /*!<  I2C Receive FIFO Level Register register,  Address offset: 0x078 */
	__IO uint32_t I2C_SDA_HOLD ;                           /*!<  I2C SDA Hold Time Length Register register,  Address offset: 0x07C */
	__IO uint32_t I2C_TX_ABRT_SRC ;                        /*!<  I2C Transmit Abort Source Register register,  Address offset: 0x080 */
	__IO uint32_t I2C_SLV_DAT_NACK ;                       /*!<  I2C Generate Slave Data NACK Register register,  Address offset: 0x084 */
	__IO uint32_t I2C_DMA_CR ;                             /*!<  I2C DMA Control Reigster register,  Address offset: 0x088 */
	__IO uint32_t I2C_DMA_TDLR ;                           /*!<  I2C DMA Transmit Data Level Register register,  Address offset: 0x08C */
	__IO uint32_t I2C_DMA_RDLR ;                           /*!<  I2C DMA Receive Data Level Register register,  Address offset: 0x090 */
	__IO uint32_t I2C_SDA_SETUP ;                          /*!<  I2C SDA Setup Register register,  Address offset: 0x094 */
	__IO uint32_t I2C_ACK_GEN_CALL ;                       /*!<  I2C ACK General Call Register register,  Address offset: 0x098 */
	__IO uint32_t I2C_EN_STS ;                             /*!<  I2C Enable Status Register register,  Address offset: 0x09C */
	__IO uint32_t I2C_DMA_CMD ;                            /*!<  I2C DMA Command Register register,  Address offset: 0x0A0 */
	__IO uint32_t I2C_DMA_LEN ;                            /*!<  I2C DMA Transfer Data Length Register register,  Address offset: 0x0A4 */
	__IO uint32_t I2C_DMA_MOD ;                            /*!<  I2C DMA Mode Register register,  Address offset: 0x0A8 */
	__IO uint32_t I2C_SLP ;                                /*!<  I2C Sleep Control Register register,  Address offset: 0x0AC */
	__IO uint32_t RSVD0[2];                                /*!<  Reserved,  Address offset:0xB0-0xB4 */
	__IO uint32_t I2C_DAT_FLTR_RSTS_L ;                    /*!<  Data Filter Resistor Low Register register,  Address offset: 0x0B8 */
	__IO uint32_t I2C_DAT_FLTR_RSTS_M ;                    /*!<  Data Filter Resistor Main Register register,  Address offset: 0x0BC */
	__IO uint32_t I2C_CLK_FLTR_RSTS_L ;                    /*!<  Clock Filter Resistor Low Register register,  Address offset: 0x0C0 */
	__IO uint32_t I2C_CLK_FLTR_RSTS_M ;                    /*!<  Clock Filter Resistor Main Register register,  Address offset: 0x0C4 */
	__IO uint32_t I2C_DAT_FLTR_CAP_L ;                     /*!<  Data Filter Capacitor Low Register register,  Address offset: 0x0C8 */
	__IO uint32_t I2C_DAT_FLTR_CAP_M ;                     /*!<  Data Filter Capacitor Main Register register,  Address offset: 0x0CC */
	__IO uint32_t I2C_CLK_FLTR_CAP_L ;                     /*!<  Clock Filter Capacitor Low Register register,  Address offset: 0x0D0 */
	__IO uint32_t I2C_CLK_FLTR_CAP_M ;                     /*!<  Clock Filter Capacitor Main Register register,  Address offset: 0x0D4 */
	__IO uint32_t RSVD1[3];                                /*!<  Reserved,  Address offset:0xD8-0xE0 */
	__IO uint32_t I2C_CLR_ADDR_MATCH ;                     /*!<  Clear I2C ADDR_MATCH Interrupt Register register,  Address offset: 0x0E4 */
	__IO uint32_t I2C_CLR_DMA_DONE ;                       /*!<  Clear I2C DMA_DONE Interrupt Register register,  Address offset: 0x0E8 */
	__IO uint32_t I2C_FLTR ;                               /*!<  I2C Bus Filter Register register,  Address offset: 0x0EC */
	__IO uint32_t RSVD2;                                  /*!<  Reserved,  Address offset:0xF0 */
	__IO uint32_t I2C_SAR1 ;                               /*!<  I2C Slave Address 1 Register register,  Address offset: 0x0F4 */
	__IO uint32_t RSVD3;                                  /*!<  Reserved,  Address offset:0xF8 */
	__I  uint32_t I2C_VER ;                                /*!<  I2C Component Version Register register,            Address offset: 0x0FC */
} I2C_TypeDef;
/** @} */

#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8735B_I2C_TYPE_H_

