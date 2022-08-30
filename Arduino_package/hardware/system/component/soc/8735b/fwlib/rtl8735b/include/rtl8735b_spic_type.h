#ifndef _RTL8735B_SPIC_TYPE_H_
#define _RTL8735B_SPIC_TYPE_H_

/**************************************************************************//**
 * @defgroup SPIC_CTRLR0
 * @brief  SPIC Control Register 0                   (@ 0X000)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_PRM_2ND_PHASE                     31
#define SPIC_BIT_PRM_2ND_PHASE                       ((u32)0x00000001 << 31)                             /*!<R/W 0   */
#define SPIC_SHIFT_CMD_DDR_EN                        30
#define SPIC_BIT_CMD_DDR_EN                          ((u32)0x00000001 << 30)                             /*!<R/W 0   */
#define SPIC_SHIFT_DATA_DDR_EN                       29
#define SPIC_BIT_DATA_DDR_EN                         ((u32)0x00000001 << 29)                             /*!<R/W 0   */
#define SPIC_SHIFT_ADDR_DDR_EN                       28
#define SPIC_BIT_ADDR_DDR_EN                         ((u32)0x00000001 << 28)                             /*!<R/W 0   */
#define SPIC_SHIFT_CK_MTIMES                         23
#define SPIC_MASK_CK_MTIMES                          ((u32)0x0000001F << 23)                             /*!<R/W 0x2   */
#define SPIC_SHIFT_FAST_RD                           22
#define SPIC_BIT_FAST_RD                             ((u32)0x00000001 << 22)                             /*!<R/W 0   */
#define SPIC_SHIFT_CMD_CH                            20
#define SPIC_MASK_CMD_CH                             ((u32)0x00000003 << 20)                             /*!<R/W 0   */
#define SPIC_SHIFT_DATA_CH                           18
#define SPIC_MASK_DATA_CH                            ((u32)0x00000003 << 18)                             /*!<R/W 0   */
#define SPIC_SHIFT_ADDR_CH                           16
#define SPIC_MASK_ADDR_CH                            ((u32)0x00000003 << 16)                             /*!<R/W 0   */
#define SPIC_SHIFT_TMOD                              8
#define SPIC_MASK_TMOD                               ((u32)0x00000003 << 8)                              /*!<R/W 0   */
#define SPIC_SHIFT_SCPOL                             7
#define SPIC_BIT_SCPOL                               ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SPIC_SHIFT_SCPH                              6
#define SPIC_BIT_SCPH                                ((u32)0x00000001 << 6)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_CTRLR1
 * @brief  SPIC Control Register 1                   (@ 0X004)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_NDF                               0
#define SPIC_MASK_NDF                                ((u32)0x00000FFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_SSIENR
 * @brief  SPIC Enable Register                      (@ 0X008)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_ATCK_CMD                          1
#define SPIC_BIT_ATCK_CMD                            ((u32)0x00000001 << 1)                              /*!<W 0   */
#define SPIC_SHIFT_SPIC_EN                           0
#define SPIC_BIT_SPIC_EN                             ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_SER
 * @brief  Slave Enable Register                     (@ 0X010)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_SER                               0
#define SPIC_BIT_SER                                 ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_BAUDR
 * @brief  Baud Rate Select Register                 (@ 0X014)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_SCKDV                             0
#define SPIC_MASK_SCKDV                              ((u32)0x00000FFF << 0)                              /*!<R/W 0x8   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_TXFTLR
 * @brief  Transmit FIFO Threshold Level             (@ 0X018)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_TFT                               0
#define SPIC_MASK_TFT                                ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_RXFTLR
 * @brief  Receive FIFO Threshold Level              (@ 0X01C)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_RFT                               0
#define SPIC_MASK_RFT                                ((u32)0x000000FF << 0)                              /*!<R/W 0x3F   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_TXFLR
 * @brief  Transmit FIFO Level Register              (@ 0X020)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_TXTFL                             0
#define SPIC_MASK_TXTFL                              ((u32)0x000000FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_RXFLR
 * @brief  Receive FIFO Level Register               (@ 0X024)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_RXTFL                             0
#define SPIC_MASK_RXTFL                              ((u32)0x000000FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_SR
 * @brief  Status Register                           (@ 0X028)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_DCOL                              6
#define SPIC_BIT_DCOL                                ((u32)0x00000001 << 6)                              /*!<R 0   */
#define SPIC_SHIFT_TXE                               5
#define SPIC_BIT_TXE                                 ((u32)0x00000001 << 5)                              /*!<R 0   */
#define SPIC_SHIFT_RFF                               4
#define SPIC_BIT_RFF                                 ((u32)0x00000001 << 4)                              /*!<R 0   */
#define SPIC_SHIFT_RFNE                              3
#define SPIC_BIT_RFNE                                ((u32)0x00000001 << 3)                              /*!<R 0   */
#define SPIC_SHIFT_TFE                               2
#define SPIC_BIT_TFE                                 ((u32)0x00000001 << 2)                              /*!<R 1   */
#define SPIC_SHIFT_TFNF                              1
#define SPIC_BIT_TFNF                                ((u32)0x00000001 << 1)                              /*!<R 1   */
#define SPIC_SHIFT_BUSY                              0
#define SPIC_BIT_BUSY                                ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_IMR
 * @brief  Interrupt Mask Register                   (@ 0X02C)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_TXSIM                             9
#define SPIC_BIT_TXSIM                               ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define SPIC_SHIFT_ACEIM                             8
#define SPIC_BIT_ACEIM                               ((u32)0x00000001 << 8)                              /*!<R/W 1   */
#define SPIC_SHIFT_BYEIM                             7
#define SPIC_BIT_BYEIM                               ((u32)0x00000001 << 7)                              /*!<R/W 1   */
#define SPIC_SHIFT_WBEIM                             6
#define SPIC_BIT_WBEIM                               ((u32)0x00000001 << 6)                              /*!<R/W 1   */
#define SPIC_SHIFT_FSEIM                             5
#define SPIC_BIT_FSEIM                               ((u32)0x00000001 << 5)                              /*!<R/W 1   */
#define SPIC_SHIFT_RXFIM                             4
#define SPIC_BIT_RXFIM                               ((u32)0x00000001 << 4)                              /*!<R/W 1   */
#define SPIC_SHIFT_RXOIM                             3
#define SPIC_BIT_RXOIM                               ((u32)0x00000001 << 3)                              /*!<R/W 1   */
#define SPIC_SHIFT_RXUIM                             2
#define SPIC_BIT_RXUIM                               ((u32)0x00000001 << 2)                              /*!<R/W 1   */
#define SPIC_SHIFT_TXOIM                             1
#define SPIC_BIT_TXOIM                               ((u32)0x00000001 << 1)                              /*!<R/W 1   */
#define SPIC_SHIFT_TXEIM                             0
#define SPIC_BIT_TXEIM                               ((u32)0x00000001 << 0)                              /*!<R/W 1   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_ISR
 * @brief  Interrupt Status Register                 (@ 0X030)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_RXSIS                             10
#define SPIC_BIT_RXSIS                               ((u32)0x00000001 << 10)                             /*!<R 0   */
#define SPIC_SHIFT_TXSIS                             9
#define SPIC_BIT_TXSIS                               ((u32)0x00000001 << 9)                              /*!<R 0   */
#define SPIC_SHIFT_ACEIS                             8
#define SPIC_BIT_ACEIS                               ((u32)0x00000001 << 8)                              /*!<R 0   */
#define SPIC_SHIFT_BYEIS                             7
#define SPIC_BIT_BYEIS                               ((u32)0x00000001 << 7)                              /*!<R 0   */
#define SPIC_SHIFT_WBEIS                             6
#define SPIC_BIT_WBEIS                               ((u32)0x00000001 << 6)                              /*!<R 0   */
#define SPIC_SHIFT_FSEIS                             5
#define SPIC_BIT_FSEIS                               ((u32)0x00000001 << 5)                              /*!<R 0   */
#define SPIC_SHIFT_RXFIS                             4
#define SPIC_BIT_RXFIS                               ((u32)0x00000001 << 4)                              /*!<R 0   */
#define SPIC_SHIFT_RXOIS                             3
#define SPIC_BIT_RXOIS                               ((u32)0x00000001 << 3)                              /*!<R 0   */
#define SPIC_SHIFT_RXUIS                             2
#define SPIC_BIT_RXUIS                               ((u32)0x00000001 << 2)                              /*!<R 0   */
#define SPIC_SHIFT_TXOIS                             1
#define SPIC_BIT_TXOIS                               ((u32)0x00000001 << 1)                              /*!<R 0   */
#define SPIC_SHIFT_TXEIS                             0
#define SPIC_BIT_TXEIS                               ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_RISR
 * @brief  Raw Interrupt Status Register             (@ 0X034)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_ACEIR                             8
#define SPIC_BIT_ACEIR                               ((u32)0x00000001 << 8)                              /*!<R 1   */
#define SPIC_SHIFT_BYEIR                             7
#define SPIC_BIT_BYEIR                               ((u32)0x00000001 << 7)                              /*!<R 1   */
#define SPIC_SHIFT_WBEIR                             6
#define SPIC_BIT_WBEIR                               ((u32)0x00000001 << 6)                              /*!<R 1   */
#define SPIC_SHIFT_FSEIR                             5
#define SPIC_BIT_FSEIR                               ((u32)0x00000001 << 5)                              /*!<R 1   */
#define SPIC_SHIFT_RXFIR                             4
#define SPIC_BIT_RXFIR                               ((u32)0x00000001 << 4)                              /*!<R 1   */
#define SPIC_SHIFT_RXOIR                             3
#define SPIC_BIT_RXOIR                               ((u32)0x00000001 << 3)                              /*!<R 1   */
#define SPIC_SHIFT_RXUIR                             2
#define SPIC_BIT_RXUIR                               ((u32)0x00000001 << 2)                              /*!<R 1   */
#define SPIC_SHIFT_TXOIR                             1
#define SPIC_BIT_TXOIR                               ((u32)0x00000001 << 1)                              /*!<R 1   */
#define SPIC_SHIFT_TXEIR                             0
#define SPIC_BIT_TXEIR                               ((u32)0x00000001 << 0)                              /*!<R 1   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_TXOICR
 * @brief  Transmit FIFO Overflow Interrupt Clear Register (@ 0X038)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_TXOICR                            0
#define SPIC_BIT_TXOICR                              ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_RXOICR
 * @brief  Receive FIFO Overflow Interrupt Clear Register (@ 0X03C)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_RXOICR                            0
#define SPIC_BIT_RXOICR                              ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_RXUICR
 * @brief  Receive FIFO Underflow Interrupt Clear Register (@ 0X040)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_RXUICR                            0
#define SPIC_BIT_RXUICR                              ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_FAEICR
 * @brief  Frame Alignment Interrupt Clear Register  (@ 0X044)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_FAEICR                            0
#define SPIC_BIT_FAEICR                              ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_ICR
 * @brief  Interrupt Clear Register                  (@ 0X048)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_ICR                               0
#define SPIC_BIT_ICR                                 ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_DMACR
 * @brief  DMA Control Register                      (@ 0X04C)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_TX_DMAC_EN                        1
#define SPIC_BIT_TX_DMAC_EN                          ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SPIC_SHIFT_RX_DMAC_EN                        0
#define SPIC_BIT_RX_DMAC_EN                          ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_DMATDLR
 * @brief  DMA Transmit Data Level Register          (@ 0X050)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_DMATDL                            0
#define SPIC_MASK_DMATDL                             ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_DMARDLR
 * @brief  DMA Receive Data Level Register           (@ 0X054)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_DMARDL                            0
#define SPIC_MASK_DMARDL                             ((u32)0x000000FF << 0)                              /*!<R/W 0x3F   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_IDR
 * @brief  Identification Code Register              (@ 0X058)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_IDCODE                            0
#define SPIC_MASK_IDCODE                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0x0203FF01   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_SPIC_VER
 * @brief  SPIC Version Register                     (@ 0X05C)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_SPIC_VERSION                      0
#define SPIC_MASK_SPIC_VERSION                       ((u32)0xFFFFFFFF << 0)                              /*!<R 0x01160927   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_DR_WORD
 * @brief  Data Register                             (@ 0X060)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_WORD                              0
#define SPIC_MASK_WORD                               ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_DR_HALF_WORD
 * @brief  Data Register                             (@ 0X060)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_HALF_WORD                         0
#define SPIC_MASK_HALF_WORD                          ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_DR_BYTE
 * @brief  Data Register                             (@ 0X060)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_BYTE                              0
#define SPIC_MASK_BYTE                               ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_READ_FAST_SINGLE
 * @brief  Fast Read Command Register                (@ 0X0E0)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_FRD_CMD                           0
#define SPIC_MASK_FRD_CMD                            ((u32)0x0000FFFF << 0)                              /*!<R/W 0x0B0B   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_READ_DUAL_DATA
 * @brief  Dual Read Command Register                (@ 0X0E4)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_RD_DUAL_O_CMD                     0
#define SPIC_MASK_RD_DUAL_O_CMD                      ((u32)0x000000FF << 0)                              /*!<R/W 0x3B   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_READ_DUAL_ADDR_DATA
 * @brief  Dual IO Read Command Register             (@ 0X0E8)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_RD_DUAL_IO_CMD                    0
#define SPIC_MASK_RD_DUAL_IO_CMD                     ((u32)0x000000FF << 0)                              /*!<R/W 0xBB   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_READ_QUAD_DATA
 * @brief  Quad Read Command Register                (@ 0X0EC)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_RD_QUAD_O_CMD                     0
#define SPIC_MASK_RD_QUAD_O_CMD                      ((u32)0x000000FF << 0)                              /*!<R/W 0x6B   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_READ_QUAD_ADDR_DATA
 * @brief  Quad IO Read Command Register             (@ 0X0F0)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_PRM_VALUE                         16
#define SPIC_MASK_PRM_VALUE                          ((u32)0x000000FF << 16)                             /*!<R/W 0xA5   */
#define SPIC_SHIFT_RD_QUAD_IO_CMD                    0
#define SPIC_MASK_RD_QUAD_IO_CMD                     ((u32)0x000000FF << 0)                              /*!<R/W 0xEB   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_WRITE_SINGLE
 * @brief  Single IO Page Program Command Register   (@ 0X0F4)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_WR_CMD                            0
#define SPIC_MASK_WR_CMD                             ((u32)0x0000FFFF << 0)                              /*!<R/W 0x0202   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_WRITE_DUAL_DATA
 * @brief  Dual Page Program Command Register        (@ 0X0F8)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_RD_DUAL_IO_CMD                    0
#define SPIC_MASK_RD_DUAL_IO_CMD                     ((u32)0x000000FF << 0)                              /*!<R/W 0xA2   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_WRITE_DUAL_ADDR_DATA
 * @brief  Dual IO Page Program Command Register     (@ 0X0FC)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_WR_DUAL_II_CMD                    0
#define SPIC_MASK_WR_DUAL_II_CMD                     ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_WRITE_QUAD_DATA
 * @brief  Quad Page Program Command Register        (@ 0X100)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_WR_QUAD_I_CMD                     0
#define SPIC_MASK_WR_QUAD_I_CMD                      ((u32)0x000000FF << 0)                              /*!<R/W 0x32   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_WRITE_QUAD_ADDR_DATA
 * @brief  Quad IO Page Program Command Register     (@ 0X104)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_WR_QUAD_II_CMD                    0
#define SPIC_MASK_WR_QUAD_II_CMD                     ((u32)0x000000FF << 0)                              /*!<R/W 0x38   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_WRITE_ENABLE
 * @brief  Write Enable Command Register             (@ 0X108)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_WR_EN_CMD                         0
#define SPIC_MASK_WR_EN_CMD                          ((u32)0x0000FFFF << 0)                              /*!<R/W 0x0606   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_READ_STATUS
 * @brief  Read Status Command Register              (@ 0X10C)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_RD_ST_CMD                         0
#define SPIC_MASK_RD_ST_CMD                          ((u32)0x0000FFFF << 0)                              /*!<R/W 0x0505   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_CTRLR2
 * @brief  SPIC Control Register 2                   (@ 0X110)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_CS_ACTIVE_HOLD                    12
#define SPIC_MASK_CS_ACTIVE_HOLD                     ((u32)0x00000003 << 12)                             /*!<R/W 0   */
#define SPIC_SHIFT_RX_FIFO_ENTRY                     8
#define SPIC_MASK_RX_FIFO_ENTRY                      ((u32)0x0000000F << 8)                              /*!<R/W 0x6   */
#define SPIC_SHIFT_TX_FIFO_ENTRY                     4
#define SPIC_MASK_TX_FIFO_ENTRY                      ((u32)0x0000000F << 4)                              /*!<R/W 0x6   */
#define SPIC_SHIFT_SEQ_EN                            3
#define SPIC_BIT_SEQ_EN                              ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SPIC_SHIFT_SO_DNUM                           0
#define SPIC_BIT_SO_DNUM                             ((u32)0x00000001 << 0)                              /*!<R/W 1   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_FBAUDR
 * @brief  Fast Read Baud Rate Select Register       (@ 0X114)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_FSCKDV                            0
#define SPIC_MASK_FSCKDV                             ((u32)0x00000FFF << 0)                              /*!<R/W 1   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_ADDR_LENGTH
 * @brief  Address Byte Length Register              (@ 0X118)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_ADDR_PHASE_LENGTH                 0
#define SPIC_MASK_ADDR_PHASE_LENGTH                  ((u32)0x00000007 << 0)                              /*!<R/W 0x3   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_AUTO_LENGTH
 * @brief  Auto Mode Address Byte Length Register    (@ 0X11C)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_CS_H_WR_DUM_LEN                   28
#define SPIC_MASK_CS_H_WR_DUM_LEN                    ((u32)0x0000000F << 28)                             /*!<R/W 0x2   */
#define SPIC_SHIFT_CS_H_RD_DUM_LEN                   26
#define SPIC_MASK_CS_H_RD_DUM_LEN                    ((u32)0x00000003 << 26)                             /*!<R/W 0x2   */
#define SPIC_SHIFT_AUTO_DUM_LEN                      18
#define SPIC_MASK_AUTO_DUM_LEN                       ((u32)0x000000FF << 18)                             /*!<R/W 0   */
#define SPIC_SHIFT_AUTO_ADDR_LENGTH                  16
#define SPIC_MASK_AUTO_ADDR_LENGTH                   ((u32)0x00000003 << 16)                             /*!<R/W 0x3   */
#define SPIC_SHIFT_RD_DUMMY_LENGTH                   0
#define SPIC_MASK_RD_DUMMY_LENGTH                    ((u32)0x00000FFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_VALID_CMD
 * @brief  Valid Command Register                    (@ 0X120)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_CTRLR0_CH                         12
#define SPIC_BIT_CTRLR0_CH                           ((u32)0x00000001 << 12)                             /*!<R/W 0   */
#define SPIC_SHIFT_PRM_EN                            11
#define SPIC_BIT_PRM_EN                              ((u32)0x00000001 << 11)                             /*!<R/W 0   */
#define SPIC_SHIFT_WR_BLOCKING                       9
#define SPIC_BIT_WR_BLOCKING                         ((u32)0x00000001 << 9)                              /*!<R/W 1   */
#define SPIC_SHIFT_WR_QUAD_II                        8
#define SPIC_BIT_WR_QUAD_II                          ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SPIC_SHIFT_WR_QUAD_I                         7
#define SPIC_BIT_WR_QUAD_I                           ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SPIC_SHIFT_WR_DUAL_II                        6
#define SPIC_BIT_WR_DUAL_II                          ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SPIC_SHIFT_WR_DUAL_I                         5
#define SPIC_BIT_WR_DUAL_I                           ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SPIC_SHIFT_RD_QUAD_IO                        4
#define SPIC_BIT_RD_QUAD_IO                          ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SPIC_SHIFT_RD_QUAD_O                         3
#define SPIC_BIT_RD_QUAD_O                           ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SPIC_SHIFT_RD_DUAL_IO                        2
#define SPIC_BIT_RD_DUAL_IO                          ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SPIC_SHIFT_RD_DUAL_I                         1
#define SPIC_BIT_RD_DUAL_I                           ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SPIC_SHIFT_FRD_SINGLE                        0
#define SPIC_BIT_FRD_SINGLE                          ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_FLASH_SIZE
 * @brief  Write Enable Command Register             (@ 0X124)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_FLASH_SIZE                        0
#define SPIC_MASK_FLASH_SIZE                         ((u32)0x0000000F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SPIC_FLUSH_FIFO
 * @brief  Read Status Command Register              (@ 0X128)
 * @{
 *****************************************************************************/
#define SPIC_SHIFT_FLUSH_FIFIO                       0
#define SPIC_BIT_FLUSH_FIFIO                         ((u32)0x00000001 << 0)                              /*!<W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_SPIC
 * @{
 * @brief rtl8735b_SPIC Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t SPIC_CTRLR0 ;                            /*!<  SPIC Control Register 0 register,  Address offset: 0x000 */
	__IO uint32_t SPIC_CTRLR1 ;                            /*!<  SPIC Control Register 1 register,  Address offset: 0x004 */
	__IO uint32_t SPIC_SSIENR ;                            /*!<  SPIC Enable Register register,  Address offset: 0x008 */
	__I  uint32_t SPIC_RESERVED ;                          /*!<   register,  Address offset: 0x00C */
	__IO uint32_t SPIC_SER ;                               /*!<  Slave Enable Register register,  Address offset: 0x010 */
	__IO uint32_t SPIC_BAUDR ;                             /*!<  Baud Rate Select Register register,  Address offset: 0x014 */
	__IO uint32_t SPIC_TXFTLR ;                            /*!<  Transmit FIFO Threshold Level register,  Address offset: 0x018 */
	__IO uint32_t SPIC_RXFTLR ;                            /*!<  Receive FIFO Threshold Level register,  Address offset: 0x01C */
	__I  uint32_t SPIC_TXFLR ;                             /*!<  Transmit FIFO Level Register register,  Address offset: 0x020 */
	__I  uint32_t SPIC_RXFLR ;                             /*!<  Receive FIFO Level Register register,  Address offset: 0x024 */
	__I  uint32_t SPIC_SR ;                                /*!<  Status Register register,  Address offset: 0x028 */
	__IO uint32_t SPIC_IMR ;                               /*!<  Interrupt Mask Register register,  Address offset: 0x02C */
	__I  uint32_t SPIC_ISR ;                               /*!<  Interrupt Status Register register,  Address offset: 0x030 */
	__I  uint32_t SPIC_RISR ;                              /*!<  Raw Interrupt Status Register register,  Address offset: 0x034 */
	__I  uint32_t SPIC_TXOICR ;                            /*!<  Transmit FIFO Overflow Interrupt Clear Register register,  Address offset: 0x038 */
	__I  uint32_t SPIC_RXOICR ;                            /*!<  Receive FIFO Overflow Interrupt Clear Register register,  Address offset: 0x03C */
	__I  uint32_t SPIC_RXUICR ;                            /*!<  Receive FIFO Underflow Interrupt Clear Register register,  Address offset: 0x040 */
	__I  uint32_t SPIC_FAEICR ;                            /*!<  Frame Alignment Interrupt Clear Register register,  Address offset: 0x044 */
	__I  uint32_t SPIC_ICR ;                               /*!<  Interrupt Clear Register register,  Address offset: 0x048 */
	__IO uint32_t SPIC_DMACR ;                             /*!<  DMA Control Register register,  Address offset: 0x04C */
	__IO uint32_t SPIC_DMATDLR ;                           /*!<  DMA Transmit Data Level Register register,  Address offset: 0x050 */
	__IO uint32_t SPIC_DMARDLR ;                           /*!<  DMA Receive Data Level Register register,  Address offset: 0x054 */
	__I  uint32_t SPIC_IDR ;                               /*!<  Identification Code Register register,  Address offset: 0x058 */
	__I  uint32_t SPIC_SPIC_VER ;                          /*!<  SPIC Version Register register,  Address offset: 0x05C */
	__IO uint32_t SPIC_DR_WORD ;                           /*!<  Data Register register,  Address offset: 0x060 */
	__IO uint32_t RSVD0[31];                               /*!<  Reserved,  Address offset:0x64-0xDC */
	__IO uint32_t SPIC_READ_FAST_SINGLE ;                  /*!<  Fast Read Command Register register,  Address offset: 0x0E0 */
	__IO uint32_t SPIC_READ_DUAL_DATA ;                    /*!<  Dual Read Command Register register,  Address offset: 0x0E4 */
	__IO uint32_t SPIC_READ_DUAL_ADDR_DATA ;               /*!<  Dual IO Read Command Register register,  Address offset: 0x0E8 */
	__IO uint32_t SPIC_READ_QUAD_DATA ;                    /*!<  Quad Read Command Register register,  Address offset: 0x0EC */
	__IO uint32_t SPIC_READ_QUAD_ADDR_DATA ;               /*!<  Quad IO Read Command Register register,  Address offset: 0x0F0 */
	__IO uint32_t SPIC_WRITE_SINGLE ;                      /*!<  Single IO Page Program Command Register register,  Address offset: 0x0F4 */
	__IO uint32_t SPIC_WRITE_DUAL_DATA ;                   /*!<  Dual Page Program Command Register register,  Address offset: 0x0F8 */
	__IO uint32_t SPIC_WRITE_DUAL_ADDR_DATA ;              /*!<  Dual IO Page Program Command Register register,  Address offset: 0x0FC */
	__IO uint32_t SPIC_WRITE_QUAD_DATA ;                   /*!<  Quad Page Program Command Register register,  Address offset: 0x100 */
	__IO uint32_t SPIC_WRITE_QUAD_ADDR_DATA ;              /*!<  Quad IO Page Program Command Register register,  Address offset: 0x104 */
	__IO uint32_t SPIC_WRITE_ENABLE ;                      /*!<  Write Enable Command Register register,  Address offset: 0x108 */
	__IO uint32_t SPIC_READ_STATUS ;                       /*!<  Read Status Command Register register,  Address offset: 0x10C */
	__IO uint32_t SPIC_CTRLR2 ;                            /*!<  SPIC Control Register 2 register,  Address offset: 0x110 */
	__IO uint32_t SPIC_FBAUDR ;                            /*!<  Fast Read Baud Rate Select Register register,  Address offset: 0x114 */
	__IO uint32_t SPIC_ADDR_LENGTH ;                       /*!<  Address Byte Length Register register,  Address offset: 0x118 */
	__IO uint32_t SPIC_AUTO_LENGTH ;                       /*!<  Auto Mode Address Byte Length Register register,  Address offset: 0x11C */
	__IO uint32_t SPIC_VALID_CMD ;                         /*!<  Valid Command Register register,  Address offset: 0x120 */
	__IO uint32_t SPIC_FLASH_SIZE ;                        /*!<  Write Enable Command Register register,  Address offset: 0x124 */
	__O  uint32_t SPIC_FLUSH_FIFO ;                        /*!<  Read Status Command Register register,          Address offset: 0x128 */
} SPIC_TypeDef;
/** @} */

#endif
