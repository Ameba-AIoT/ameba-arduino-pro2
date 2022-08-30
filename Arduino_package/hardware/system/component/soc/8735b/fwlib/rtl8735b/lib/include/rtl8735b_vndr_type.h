#ifndef _RTL8735B_VNDR_TYPE_H_
#define _RTL8735B_VNDR_TYPE_H_
#define VNDR_SHIFT_RSVD1                             0
#define VNDR_MASK_RSVD1                              ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */

/**************************************************************************//**
 * @defgroup VNDR_REG_LOW_PRI_INT_MODE
 * @brief                                            (@ 0X004)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD2                             0
#define VNDR_MASK_RSVD2                              ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_LOW_PRI_INT_IMR
 * @brief                                            (@ 0X008)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD3                             0
#define VNDR_MASK_RSVD3                              ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_LOW_PRI_INT_ISR
 * @brief                                            (@ 0X00C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD4                             0
#define VNDR_MASK_RSVD4                              ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
#define VNDR_SHIFT_RSVD5                             0
#define VNDR_MASK_RSVD5                              ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_ANACK_CAL_CTRL
 * @brief                                            (@ 0X014)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_VDR_ANACK_CAL_CMD                 31
#define VNDR_BIT_VDR_ANACK_CAL_CMD                   ((u32)0x00000001 << 31)                             /*!<R/W 0  1: polling ANACK Calibration enable and indicate busy when calibration is on going 0: calibration is done */
#define VNDR_SHIFT_VDR_ANACK_CAL_SEL                 24
#define VNDR_MASK_VDR_ANACK_CAL_SEL                  ((u32)0x00000003 << 24)                             /*!<R/W 0  00: caliabration of 4M for 32 cycles 01: calibration of 128K for 8 cycles 10: calibration of 32K(S1) for 8 cycles 11: rsvd */
#define VNDR_SHIFT_VDR_ANACK_CAL_RPT                 0
#define VNDR_MASK_VDR_ANACK_CAL_RPT                  ((u32)0x0000FFFF << 0)                              /*!<R 0  the calibration value of ANA clock where the calibration clock is bus generic clock. */
#define VNDR_SHIFT_RSVD6                             0
#define VNDR_MASK_RSVD6                              ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_RSVD7                             0
#define VNDR_MASK_RSVD7                              ((u32)0xFFFFFFFF << 0)                              /*!<-- 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_DATA_FIFO_SWAP_CTRL
 * @brief                                            (@ 0X020)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD8                             8
#define VNDR_MASK_RSVD8                              ((u32)0x00FFFFFF << 8)                              /*!<R/W 0  RSVD  */
#define VNDR_SHIFT_I2C3_RX_SHIFT_SWAP_EN             7
#define VNDR_BIT_I2C3_RX_BIT_SWAP_EN                 ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define VNDR_SHIFT_I2C3_TX_SHIFT_SWAP_EN             6
#define VNDR_BIT_I2C3_TX_BIT_SWAP_EN                 ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define VNDR_SHIFT_I2C2_RX_SHIFT_SWAP_EN             5
#define VNDR_BIT_I2C2_RX_BIT_SWAP_EN                 ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define VNDR_SHIFT_I2C2_TX_SHIFT_SWAP_EN             4
#define VNDR_BIT_I2C2_TX_BIT_SWAP_EN                 ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define VNDR_SHIFT_I2C1_RX_SHIFT_SWAP_EN             3
#define VNDR_BIT_I2C1_RX_BIT_SWAP_EN                 ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define VNDR_SHIFT_I2C1_TX_SHIFT_SWAP_EN             2
#define VNDR_BIT_I2C1_TX_BIT_SWAP_EN                 ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define VNDR_SHIFT_I2C0_RX_SHIFT_SWAP_EN             1
#define VNDR_BIT_I2C0_RX_BIT_SWAP_EN                 ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define VNDR_SHIFT_I2C0_TX_SHIFT_SWAP_EN             0
#define VNDR_BIT_I2C0_TX_BIT_SWAP_EN                 ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_I2C_DGLCH_CTRL
 * @brief                                            (@ 0X024)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD9                             0
#define VNDR_MASK_RSVD9                              ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
#define VNDR_SHIFT_RSVD10                            0
#define VNDR_MASK_RSVD10                             ((u32)0xFFFFFFFF << 0)                              /*!<-- 0   */
#define VNDR_SHIFT_RSVD11                            0
#define VNDR_MASK_RSVD11                             ((u32)0xFFFFFFFF << 0)                              /*!<-- 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_GDMA0_ISR
 * @brief                                            (@ 0X030)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD12                            6
#define VNDR_MASK_RSVD12                             ((u32)0x03FFFFFF << 6)                              /*!<-- 0   */
#define VNDR_SHIFT_GDMA0_CH5_ISR                     5
#define VNDR_BIT_GDMA0_CH5_ISR                       ((u32)0x00000001 << 5)                              /*!<R 0   */
#define VNDR_SHIFT_GDMA0_CH4_ISR                     4
#define VNDR_BIT_GDMA0_CH4_ISR                       ((u32)0x00000001 << 4)                              /*!<R 0   */
#define VNDR_SHIFT_GDMA0_CH3_ISR                     3
#define VNDR_BIT_GDMA0_CH3_ISR                       ((u32)0x00000001 << 3)                              /*!<R 0   */
#define VNDR_SHIFT_GDMA0_CH2_ISR                     2
#define VNDR_BIT_GDMA0_CH2_ISR                       ((u32)0x00000001 << 2)                              /*!<R 0   */
#define VNDR_SHIFT_GDMA0_CH1_ISR                     1
#define VNDR_BIT_GDMA0_CH1_ISR                       ((u32)0x00000001 << 1)                              /*!<R 0   */
#define VNDR_SHIFT_GDMA0_CH0_ISR                     0
#define VNDR_BIT_GDMA0_CH0_ISR                       ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_GDMA1_ISR
 * @brief                                            (@ 0X034)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD13                            6
#define VNDR_MASK_RSVD13                             ((u32)0x03FFFFFF << 6)                              /*!<-- 0   */
#define VNDR_SHIFT_GDMA1_CH5_ISR                     5
#define VNDR_BIT_GDMA1_CH5_ISR                       ((u32)0x00000001 << 5)                              /*!<R 0   */
#define VNDR_SHIFT_GDMA1_CH4_ISR                     4
#define VNDR_BIT_GDMA1_CH4_ISR                       ((u32)0x00000001 << 4)                              /*!<R 0   */
#define VNDR_SHIFT_GDMA1_CH3_ISR                     3
#define VNDR_BIT_GDMA1_CH3_ISR                       ((u32)0x00000001 << 3)                              /*!<R 0   */
#define VNDR_SHIFT_GDMA1_CH2_ISR                     2
#define VNDR_BIT_GDMA1_CH2_ISR                       ((u32)0x00000001 << 2)                              /*!<R 0   */
#define VNDR_SHIFT_GDMA1_CH1_ISR                     1
#define VNDR_BIT_GDMA1_CH1_ISR                       ((u32)0x00000001 << 1)                              /*!<R 0   */
#define VNDR_SHIFT_GDMA1_CH0_ISR                     0
#define VNDR_BIT_GDMA1_CH0_ISR                       ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_SGPIO_ISR
 * @brief                                            (@ 0X038)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD14                            1
#define VNDR_MASK_RSVD14                             ((u32)0x7FFFFFFF << 1)                              /*!<-- 0   */
#define VNDR_SHIFT_SGPIO0_ISR                        0
#define VNDR_BIT_SGPIO0_ISR                          ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_UART_ISR
 * @brief                                            (@ 0X03C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD15                            5
#define VNDR_MASK_RSVD15                             ((u32)0x07FFFFFF << 5)                              /*!<-- 0   */
#define VNDR_SHIFT_BT_UART_ISR                       4
#define VNDR_BIT_BT_UART_ISR                         ((u32)0x00000001 << 4)                              /*!<R 0   */
#define VNDR_SHIFT_UART3_ISR                         3
#define VNDR_BIT_UART3_ISR                           ((u32)0x00000001 << 3)                              /*!<R 0   */
#define VNDR_SHIFT_UART2_ISR                         2
#define VNDR_BIT_UART2_ISR                           ((u32)0x00000001 << 2)                              /*!<R 0   */
#define VNDR_SHIFT_UART1_ISR                         1
#define VNDR_BIT_UART1_ISR                           ((u32)0x00000001 << 1)                              /*!<R 0   */
#define VNDR_SHIFT_UART0_ISR                         0
#define VNDR_BIT_UART0_ISR                           ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_I2C_ISR
 * @brief                                            (@ 0X040)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD16                            4
#define VNDR_MASK_RSVD16                             ((u32)0x0FFFFFFF << 4)                              /*!<-- 0   */
#define VNDR_SHIFT_I2C3_ISR                          3
#define VNDR_BIT_I2C3_ISR                            ((u32)0x00000001 << 3)                              /*!<R 0   */
#define VNDR_SHIFT_I2C2_ISR                          2
#define VNDR_BIT_I2C2_ISR                            ((u32)0x00000001 << 2)                              /*!<R 0   */
#define VNDR_SHIFT_I2C1_ISR                          1
#define VNDR_BIT_I2C1_ISR                            ((u32)0x00000001 << 1)                              /*!<R 0   */
#define VNDR_SHIFT_I2C0_ISR                          0
#define VNDR_BIT_I2C0_ISR                            ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_SPI_ISR
 * @brief                                            (@ 0X044)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD17                            2
#define VNDR_MASK_RSVD17                             ((u32)0x3FFFFFFF << 2)                              /*!<-- 0   */
#define VNDR_SHIFT_SPI1_ISR                          1
#define VNDR_BIT_SPI1_ISR                            ((u32)0x00000001 << 1)                              /*!<R 0   */
#define VNDR_SHIFT_SPI0_ISR                          0
#define VNDR_BIT_SPI0_ISR                            ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_I2S_ISR
 * @brief                                            (@ 0X048)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD18                            2
#define VNDR_MASK_RSVD18                             ((u32)0x3FFFFFFF << 2)                              /*!<-- 0   */
#define VNDR_SHIFT_I2S1_ISR                          1
#define VNDR_BIT_I2S1_ISR                            ((u32)0x00000001 << 1)                              /*!<R 0   */
#define VNDR_SHIFT_I2S0_ISR                          0
#define VNDR_BIT_I2S0_ISR                            ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_WL_ISR
 * @brief                                            (@ 0X04C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSVD19                            4
#define VNDR_MASK_RSVD19                             ((u32)0x0FFFFFFF << 4)                              /*!<-- 0   */
#define VNDR_SHIFT_RF_OFF_ISR                        3
#define VNDR_BIT_RF_OFF_ISR                          ((u32)0x00000001 << 3)                              /*!<R 0  Without Use */
#define VNDR_SHIFT_RF_ON_ISR                         2
#define VNDR_BIT_RF_ON_ISR                           ((u32)0x00000001 << 2)                              /*!<R 0  Without Use */
#define VNDR_SHIFT_AHB_LOCAL_INT                     1
#define VNDR_BIT_AHB_LOCAL_INT                       ((u32)0x00000001 << 1)                              /*!<R 0  WL page3 interrupt */
#define VNDR_SHIFT_WLAN_PAGE0_INT                    0
#define VNDR_BIT_WLAN_PAGE0_INT                      ((u32)0x00000001 << 0)                              /*!<R 0   */
#define VNDR_SHIFT_RSVD20                            0
#define VNDR_MASK_RSVD20                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_RSVD21                            0
#define VNDR_MASK_RSVD21                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_RSVD22                            0
#define VNDR_MASK_RSVD22                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_RSVD23                            0
#define VNDR_MASK_RSVD23                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_GDMA_HSKS_CTRL
 * @brief                                            (@ 0X060)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_HS_GDMA_HSKS_CFG                  0
#define VNDR_MASK_HS_GDMA_HSKS_CFG                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  GDMA handshake signal mapping. Some peripherals can operate with either GDMA0 or GDMA1. This mapping decides DMA handshake signal connection. If Nth bit is 0, the peripheral's DMA handshake signal is connected to GDMA0; if Nth bit is 1, the peripheral's DMA handshake signal is connected to GDMA1. Peripheral and GDMA handshake signal connection option is as in below table. */
#define VNDR_SHIFT_RSVD24                            0
#define VNDR_MASK_RSVD24                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_RSVD25                            0
#define VNDR_MASK_RSVD25                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_RSVD26                            0
#define VNDR_MASK_RSVD26                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_MAILB0X_OUT_DATA                  0
#define VNDR_MASK_MAILB0X_OUT_DATA                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 010  Mailbox out data */
#define VNDR_SHIFT_RSVD27                            0
#define VNDR_MASK_RSVD27                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Reserved */
#define VNDR_SHIFT_RSVD28                            0
#define VNDR_MASK_RSVD28                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Reserved */
#define VNDR_SHIFT_RSVD29                            0
#define VNDR_MASK_RSVD29                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_RSVD30                            0
#define VNDR_MASK_RSVD30                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_RSVD31                            0
#define VNDR_MASK_RSVD31                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_RSVD32                            0
#define VNDR_MASK_RSVD32                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
#define VNDR_SHIFT_RSVD33                            0
#define VNDR_MASK_RSVD33                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Reserved */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_LX_CTRL0
 * @brief                                            (@ 0X090)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT__                                 19
#define VNDR_MASK__                                  ((u32)0x00001FFF << 19)                             /*!<R/W 0   */
#define VNDR_SHIFT_MII_LX_TIMEOUT_THRESHOLD          17
#define VNDR_MASK_MII_LX_TIMEOUT_THRESHOLD           ((u32)0x00000003 << 17)                             /*!<R/W 0  2'b00: 2^15 lexra clock cycles 2'b01: 2^13 lexra clock cycles 2'b10: 2^11 lexra clock cycles 2'b11: 2^9 lexra clock cycles */
#define VNDR_SHIFT_MII_LX_TIMEOUT_EN                 16
#define VNDR_BIT_MII_LX_TIMEOUT_EN                   ((u32)0x00000001 << 16)                             /*!<R/W 1  1:Enable */
#define VNDR_SHIFT_RSVD34                            10
#define VNDR_MASK_RSVD34                             ((u32)0x0000003F << 10)                             /*!<    */
#define VNDR_SHIFT_LX2_DMA_LOCK_DONE                 9
#define VNDR_BIT_LX2_DMA_LOCK_DONE                   ((u32)0x00000001 << 9)                              /*!<R 0  1'b1: lock is done. There is no dma transaction now. */
#define VNDR_SHIFT_LX2_DMA_LOCK_EN                   8
#define VNDR_BIT_LX2_DMA_LOCK_EN                     ((u32)0x00000001 << 8)                              /*!<R/W 0  1'b1: set gnt=0 to lock lexra dma function. */
#define VNDR_SHIFT_PCM1_LX_REQ_EN                    7
#define VNDR_BIT_PCM1_LX_REQ_EN                      ((u32)0x00000001 << 7)                              /*!<R/W 1  1: Enable */
#define VNDR_SHIFT_PCM0_LX_REQ_EN                    6
#define VNDR_BIT_PCM0_LX_REQ_EN                      ((u32)0x00000001 << 6)                              /*!<R/W 1  1: Enable */
#define VNDR_SHIFT_PCM_SPDUP_EN                      5
#define VNDR_BIT_PCM_SPDUP_EN                        ((u32)0x00000001 << 5)                              /*!<R/W 0  PCM speedup enable, only for test mode. */
#define VNDR_SHIFT_LX1_DMA_LOCK_DONE                 4
#define VNDR_BIT_LX1_DMA_LOCK_DONE                   ((u32)0x00000001 << 4)                              /*!<R 0  1'b1: lock is done. There is no dma transaction now. */
#define VNDR_SHIFT_LX1_DMA_LOCK_EN                   3
#define VNDR_BIT_LX1_DMA_LOCK_EN                     ((u32)0x00000001 << 3)                              /*!<R/W 0  1'b1: set gnt=0 to lock lexra dma function. */
#define VNDR_SHIFT_LX_BUS_TIMEOUT_THRESHOLD          1
#define VNDR_MASK_LX_BUS_TIMEOUT_THRESHOLD           ((u32)0x00000003 << 1)                              /*!<R/W 0  2'b00: 2^15 lexra clock cycles 2'b01: 2^13 lexra clock cycles 2'b10: 2^11 lexra clock cycles 2'b11: 2^9 lexra clock cycles */
#define VNDR_SHIFT_LX_BUS_TIMEOUT_EN                 0
#define VNDR_BIT_LX_BUS_TIMEOUT_EN                   ((u32)0x00000001 << 0)                              /*!<R/W 0  1:Enable */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_LX_CTRL1
 * @brief                                            (@ 0X094)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_R_LX1_TO_ADDR_MST                 0
#define VNDR_MASK_R_LX1_TO_ADDR_MST                  ((u32)0xFFFFFFFF << 0)                              /*!<R 0  The address when lexra master is hanged. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_LX_CTRL2
 * @brief                                            (@ 0X098)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_R_LX1_TO_ADDR_SLV                 0
#define VNDR_MASK_R_LX1_TO_ADDR_SLV                  ((u32)0xFFFFFFFF << 0)                              /*!<R 0  The address when lexra slave is hanged. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_LX_CTRL3
 * @brief                                            (@ 0X09C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_R_LX2_TO_ADDR_MST                 0
#define VNDR_MASK_R_LX2_TO_ADDR_MST                  ((u32)0xFFFFFFFF << 0)                              /*!<R 0  The address when lexra master is hanged. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_RSTN_RAM_0
 * @brief                                            (@ 0X0A0)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSTN_ACBB2_ITLV_A                 31
#define VNDR_BIT_RSTN_ACBB2_ITLV_A                   ((u32)0x00000001 << 31)                             /*!<R/W 0x0  mbist_acbb2_itlv_a 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SOML_STBC              30
#define VNDR_BIT_RSTN_ACBB2_SOML_STBC                ((u32)0x00000001 << 30)                             /*!<R/W 0x0  mbist_acbb2_soml_stbc 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_PTCSI                  29
#define VNDR_BIT_RSTN_ACBB2_PTCSI                    ((u32)0x00000001 << 29)                             /*!<R/W 0x0  mbist_acbb2_ptcsi 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_FFT_NOISE_POWER        28
#define VNDR_BIT_RSTN_ACBB2_FFT_NOISE_POWER          ((u32)0x00000001 << 28)                             /*!<R/W 0x0  mbist_acbb2_fft_noise_power 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_HWIGI_TXINFO_TABLE     27
#define VNDR_BIT_RSTN_ACBB2_HWIGI_TXINFO_TABLE       ((u32)0x00000001 << 27)                             /*!<R/W 0x0  mbist_acbb2_hwigi_txinfo_table 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_MF_2ND20               26
#define VNDR_BIT_RSTN_ACBB2_MF_2ND20                 ((u32)0x00000001 << 26)                             /*!<R/W 0x0  mbist_acbb2_mf_2nd20 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_MF_DELAY               25
#define VNDR_BIT_RSTN_ACBB2_MF_DELAY                 ((u32)0x00000001 << 25)                             /*!<R/W 0x0  mbist_acbb2_mf_delay 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SHARE_DELAY_SND        24
#define VNDR_BIT_RSTN_ACBB2_SHARE_DELAY_SND          ((u32)0x00000001 << 24)                             /*!<R/W 0x0  mbist_acbb2_share_delay_snd 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SHARE_DELAY_PRI        23
#define VNDR_BIT_RSTN_ACBB2_SHARE_DELAY_PRI          ((u32)0x00000001 << 23)                             /*!<R/W 0x0  mbist_acbb2_share_delay_pri 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SBD                    22
#define VNDR_BIT_RSTN_ACBB2_SBD                      ((u32)0x00000001 << 22)                             /*!<R/W 0x0  mbist_acbb2_sbd 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SBD_GI                 21
#define VNDR_BIT_RSTN_ACBB2_SBD_GI                   ((u32)0x00000001 << 21)                             /*!<R/W 0x0  mbist_acbb2_sbd_GI 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_DFS_PWDB_FIFO          20
#define VNDR_BIT_RSTN_ACBB2_DFS_PWDB_FIFO            ((u32)0x00000001 << 20)                             /*!<R/W 0x0  mbist_acbb2_dfs_pwdb_fifo 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_DFS_FFT_FIFO           19
#define VNDR_BIT_RSTN_ACBB2_DFS_FFT_FIFO             ((u32)0x00000001 << 19)                             /*!<R/W 0x0  mbist_acbb2_dfs_fft_fifo 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_RPT_KEEPER             18
#define VNDR_BIT_RSTN_ACBB2_RPT_KEEPER               ((u32)0x00000001 << 18)                             /*!<R/W 0x0  mbist_acbb2_rpt_keeper 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_ANAPAR                 17
#define VNDR_BIT_RSTN_ACBB2_ANAPAR                   ((u32)0x00000001 << 17)                             /*!<R/W 0x0  mbist_acbb2_anapar 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_RXAGC                  16
#define VNDR_BIT_RSTN_ACBB2_RXAGC                    ((u32)0x00000001 << 16)                             /*!<R/W 0x0  mbist_acbb2_rxagc 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_AXI_TXDMA              15
#define VNDR_BIT_RSTN_WLMAC_AXI_TXDMA                ((u32)0x00000001 << 15)                             /*!<R/W 0x0  mbist_wlmac_axi_txdma 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMCU_IRAM                   14
#define VNDR_BIT_RSTN_WLMCU_IRAM                     ((u32)0x00000001 << 14)                             /*!<R/W 0x0  mbist_wlmcu_iram 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMCU_ERAM1                  13
#define VNDR_BIT_RSTN_WLMCU_ERAM1                    ((u32)0x00000001 << 13)                             /*!<R/W 0x0  mbist_wlmcu_eram1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMCU_ERAM0                  12
#define VNDR_BIT_RSTN_WLMCU_ERAM0                    ((u32)0x00000001 << 12)                             /*!<R/W 0x0  mbist_wlmcu_eram0 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMCU_DRAM                   11
#define VNDR_BIT_RSTN_WLMCU_DRAM                     ((u32)0x00000001 << 11)                             /*!<R/W 0x0  mbist_wlmcu_dram 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_TXRPTBUFFER            10
#define VNDR_BIT_RSTN_WLMAC_TXRPTBUFFER              ((u32)0x00000001 << 10)                             /*!<R/W 0x0  mbist_wlmac_txrptbuffer 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_RXPKTBUFFER            9
#define VNDR_BIT_RSTN_WLMAC_RXPKTBUFFER              ((u32)0x00000001 << 9)                              /*!<R/W 0x0  mbist_wlmac_rxpktbuffer 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_TXPKTBUFFER1           8
#define VNDR_BIT_RSTN_WLMAC_TXPKTBUFFER1             ((u32)0x00000001 << 8)                              /*!<R/W 0x0  mbist_wlmac_txpktbuffer1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_TXPKTBUFFER0           7
#define VNDR_BIT_RSTN_WLMAC_TXPKTBUFFER0             ((u32)0x00000001 << 7)                              /*!<R/W 0x0  mbist_wlmac_txpktbuffer0 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_TXLLT                  6
#define VNDR_BIT_RSTN_WLMAC_TXLLT                    ((u32)0x00000001 << 6)                              /*!<R/W 0x0  mbist_wlmac_txllt 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_MACTX_FIFO             5
#define VNDR_BIT_RSTN_WLMAC_MACTX_FIFO               ((u32)0x00000001 << 5)                              /*!<R/W 0x0  mbist_wlmac_mactx_fifo 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_MACRX_FIFO             4
#define VNDR_BIT_RSTN_WLMAC_MACRX_FIFO               ((u32)0x00000001 << 4)                              /*!<R/W 0x0  mbist_wlmac_macrx_fifo 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_TKIPRC4                3
#define VNDR_BIT_RSTN_WLMAC_TKIPRC4                  ((u32)0x00000001 << 3)                              /*!<R/W 0x0  mbist_wlmac_tkiprc4 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_PSF                    2
#define VNDR_BIT_RSTN_WLMAC_PSF                      ((u32)0x00000001 << 2)                              /*!<R/W 0x0  mbist_wlmac_psf 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_RXBACAM                1
#define VNDR_BIT_RSTN_WLMAC_RXBACAM                  ((u32)0x00000001 << 1)                              /*!<R/W 0x0  mbist_wlmac_rxbacam 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_KEYSRCH                0
#define VNDR_BIT_RSTN_WLMAC_KEYSRCH                  ((u32)0x00000001 << 0)                              /*!<R/W 0x0  mbist_wlmac_keysrch 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_RSTN_RAM_1
 * @brief                                            (@ 0X0A4)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSTN_BT_04                        31
#define VNDR_BIT_RSTN_BT_04                          ((u32)0x00000001 << 31)                             /*!<R/W 0x0  mbist_bt_04 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_BT_03                        30
#define VNDR_BIT_RSTN_BT_03                          ((u32)0x00000001 << 30)                             /*!<R/W 0x0  mbist_bt_03 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_BT_02                        29
#define VNDR_BIT_RSTN_BT_02                          ((u32)0x00000001 << 29)                             /*!<R/W 0x0  mbist_bt_02 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RESERVED1                         28
#define VNDR_BIT_RESERVED1                           ((u32)0x00000001 << 28)                             /*!<R/W 0x0  -- */
#define VNDR_SHIFT_RESERVED2                         27
#define VNDR_BIT_RESERVED2                           ((u32)0x00000001 << 27)                             /*!<R/W 0x0  -- */
#define VNDR_SHIFT_RESERVED3                         26
#define VNDR_BIT_RESERVED3                           ((u32)0x00000001 << 26)                             /*!<R/W 0x0  -- */
#define VNDR_SHIFT_RESERVED4                         25
#define VNDR_BIT_RESERVED4                           ((u32)0x00000001 << 25)                             /*!<R/W 0x0  -- */
#define VNDR_SHIFT_RESERVED5                         24
#define VNDR_BIT_RESERVED5                           ((u32)0x00000001 << 24)                             /*!<R/W 0x0  -- */
#define VNDR_SHIFT_RESERVED6                         23
#define VNDR_BIT_RESERVED6                           ((u32)0x00000001 << 23)                             /*!<R/W 0x0  -- */
#define VNDR_SHIFT_RESERVED7                         22
#define VNDR_BIT_RESERVED7                           ((u32)0x00000001 << 22)                             /*!<R/W 0x0  -- */
#define VNDR_SHIFT_RESERVED8                         21
#define VNDR_BIT_RESERVED8                           ((u32)0x00000001 << 21)                             /*!<R/W 0x0  -- */
#define VNDR_SHIFT_RSTN_ACBB2_CCK_CCA                20
#define VNDR_BIT_RSTN_ACBB2_CCK_CCA                  ((u32)0x00000001 << 20)                             /*!<R/W 0x0  mbist_acbb2_cck_cca 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_TMETER                 19
#define VNDR_BIT_RSTN_ACBB2_TMETER                   ((u32)0x00000001 << 19)                             /*!<R/W 0x0  mbist_acbb2_Tmeter 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_PWSF                   18
#define VNDR_BIT_RSTN_ACBB2_PWSF                     ((u32)0x00000001 << 18)                             /*!<R/W 0x0  mbist_acbb2_pwsf 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_IQK_DPD                17
#define VNDR_BIT_RSTN_ACBB2_IQK_DPD                  ((u32)0x00000001 << 17)                             /*!<R/W 0x0  mbist_acbb2_iqk_dpd 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SYNC                   16
#define VNDR_BIT_RSTN_ACBB2_SYNC                     ((u32)0x00000001 << 16)                             /*!<R/W 0x0  mbist_acbb2_sync 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_NCTL                   15
#define VNDR_BIT_RSTN_ACBB2_NCTL                     ((u32)0x00000001 << 15)                             /*!<R/W 0x0  mbist_acbb2_nctl 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_VITERBI                14
#define VNDR_BIT_RSTN_ACBB2_VITERBI                  ((u32)0x00000001 << 14)                             /*!<R/W 0x0  mbist_acbb2_viterbi 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_BFEE                   13
#define VNDR_BIT_RSTN_ACBB2_BFEE                     ((u32)0x00000001 << 13)                             /*!<R/W 0x0  mbist_acbb2_Bfee 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SHARE_FEQ_IN_DELAY     12
#define VNDR_BIT_RSTN_ACBB2_SHARE_FEQ_IN_DELAY       ((u32)0x00000001 << 12)                             /*!<R/W 0x0  mbist_acbb2_share_feq_in_delay 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SHARE_FEQ_IN_T0        11
#define VNDR_BIT_RSTN_ACBB2_SHARE_FEQ_IN_T0          ((u32)0x00000001 << 11)                             /*!<R/W 0x0  mbist_acbb2_share_feq_in_t0 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_H_STS_PATH1            10
#define VNDR_BIT_RSTN_ACBB2_H_STS_PATH1              ((u32)0x00000001 << 10)                             /*!<R/W 0x0  mbist_acbb2_H_sts_path1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_H_STS_PATH0            9
#define VNDR_BIT_RSTN_ACBB2_H_STS_PATH0              ((u32)0x00000001 << 9)                              /*!<R/W 0x0  mbist_acbb2_H_sts_path0 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_PRECCA_POWCAL          8
#define VNDR_BIT_RSTN_ACBB2_PRECCA_POWCAL            ((u32)0x00000001 << 8)                              /*!<R/W 0x0  mbist_acbb2_precca_powcal 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_NOISE_POW              7
#define VNDR_BIT_RSTN_ACBB2_NOISE_POW                ((u32)0x00000001 << 7)                              /*!<R/W 0x0  mbist_acbb2_noise_pow 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_PILOT_TRACKING         6
#define VNDR_BIT_RSTN_ACBB2_PILOT_TRACKING           ((u32)0x00000001 << 6)                              /*!<R/W 0x0  mbist_acbb2_pilot_tracking 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_FOE_LLTF               5
#define VNDR_BIT_RSTN_ACBB2_FOE_LLTF                 ((u32)0x00000001 << 5)                              /*!<R/W 0x0  mbist_acbb2_foe_lltf 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_GI_BUFF                4
#define VNDR_BIT_RSTN_ACBB2_GI_BUFF                  ((u32)0x00000001 << 4)                              /*!<R/W 0x0  mbist_acbb2_gi_buff 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_DLY_512                3
#define VNDR_BIT_RSTN_ACBB2_DLY_512                  ((u32)0x00000001 << 3)                              /*!<R/W 0x0  mbist_acbb2_dly_512 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_FFTBUF                 2
#define VNDR_BIT_RSTN_ACBB2_FFTBUF                   ((u32)0x00000001 << 2)                              /*!<R/W 0x0  mbist_acbb2_fftbuf 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_FFT                    1
#define VNDR_BIT_RSTN_ACBB2_FFT                      ((u32)0x00000001 << 1)                              /*!<R/W 0x0  mbist_acbb2_fft 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_ITLV_B                 0
#define VNDR_BIT_RSTN_ACBB2_ITLV_B                   ((u32)0x00000001 << 0)                              /*!<R/W 0x0  mbist_acbb2_itlv_b 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_RSTN_RAM_2
 * @brief                                            (@ 0X0A8)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSTN_VOE_FBCU_OBUF_BUF1           31
#define VNDR_BIT_RSTN_VOE_FBCU_OBUF_BUF1             ((u32)0x00000001 << 31)                             /*!<R/W 0x0  mbist_voe_fbcu_obuf_buf1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_VOE_FBCU_OBUF_BUF0           30
#define VNDR_BIT_RSTN_VOE_FBCU_OBUF_BUF0             ((u32)0x00000001 << 30)                             /*!<R/W 0x0  mbist_voe_fbcu_obuf_buf0 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_VOE_SHARED_SRAM              29
#define VNDR_BIT_RSTN_VOE_SHARED_SRAM                ((u32)0x00000001 << 29)                             /*!<R/W 0x0  mbist_voe_shared_sram 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_VOEMCU_DTCM                  28
#define VNDR_BIT_RSTN_VOEMCU_DTCM                    ((u32)0x00000001 << 28)                             /*!<R/W 0x0  mbist_voemcu_dtcm 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_VOEMCU_ITCM_RAM              27
#define VNDR_BIT_RSTN_VOEMCU_ITCM_RAM                ((u32)0x00000001 << 27)                             /*!<R/W 0x0  mbist_voemcu_itcm_ram 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_CPU_ITCM_RAM                 26
#define VNDR_BIT_RSTN_CPU_ITCM_RAM                   ((u32)0x00000001 << 26)                             /*!<R/W 0x0  mbist_cpu_itcm_ram 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_CPU_PHT_BTB                  25
#define VNDR_BIT_RSTN_CPU_PHT_BTB                    ((u32)0x00000001 << 25)                             /*!<R/W 0x0  mbist_cpu_pht_btb 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_CPU_IC                       24
#define VNDR_BIT_RSTN_CPU_IC                         ((u32)0x00000001 << 24)                             /*!<R/W 0x0  mbist_cpu_ic 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_CPU_DC                       23
#define VNDR_BIT_RSTN_CPU_DC                         ((u32)0x00000001 << 23)                             /*!<R/W 0x0  mbist_cpu_dc 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_CPU_DTCM_RAM                 22
#define VNDR_BIT_RSTN_CPU_DTCM_RAM                   ((u32)0x00000001 << 22)                             /*!<R/W 0x0  mbist_cpu_dtcm_ram 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_SDMMC_PPBECC                 21
#define VNDR_BIT_RSTN_SDMMC_PPBECC                   ((u32)0x00000001 << 21)                             /*!<R/W 0x0  mbist_sdmmc_ppbecc 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_SDMMC_DMASB1                 20
#define VNDR_BIT_RSTN_SDMMC_DMASB1                   ((u32)0x00000001 << 20)                             /*!<R/W 0x0  mbist_sdmmc_dmasb1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_USBOTG                       19
#define VNDR_BIT_RSTN_USBOTG                         ((u32)0x00000001 << 19)                             /*!<R/W 0x0  mbist_usbotg 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_SDIO                         18
#define VNDR_BIT_RSTN_SDIO                           ((u32)0x00000001 << 18)                             /*!<R/W 0x0  mbist_sdio 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_MIPI                         17
#define VNDR_BIT_RSTN_MIPI                           ((u32)0x00000001 << 17)                             /*!<R/W 0x0  mbist_mipi 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_OSDBRIDGE                    16
#define VNDR_BIT_RSTN_OSDBRIDGE                      ((u32)0x00000001 << 16)                             /*!<R/W 0x0  mbist_osdbridge 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_OSDPAINTER                   15
#define VNDR_BIT_RSTN_OSDPAINTER                     ((u32)0x00000001 << 15)                             /*!<R/W 0x0  mbist_osdpainter 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_VIDEO_AMBA                   14
#define VNDR_BIT_RSTN_VIDEO_AMBA                     ((u32)0x00000001 << 14)                             /*!<R/W 0x0  mbist_video_amba 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ISP_DMA3                     13
#define VNDR_BIT_RSTN_ISP_DMA3                       ((u32)0x00000001 << 13)                             /*!<R/W 0x0  mbist_isp_dma3 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ISPH_VHDR_ADD                12
#define VNDR_BIT_RSTN_ISPH_VHDR_ADD                  ((u32)0x00000001 << 12)                             /*!<R/W 0x0  mbist_isph VHDR add 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ISPG                         11
#define VNDR_BIT_RSTN_ISPG                           ((u32)0x00000001 << 11)                             /*!<R/W 0x0  mbist_ispg 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ISPF                         10
#define VNDR_BIT_RSTN_ISPF                           ((u32)0x00000001 << 10)                             /*!<R/W 0x0  mbist_ispf 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ISPE                         9
#define VNDR_BIT_RSTN_ISPE                           ((u32)0x00000001 << 9)                              /*!<R/W 0x0  mbist_ispe 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ISPD                         8
#define VNDR_BIT_RSTN_ISPD                           ((u32)0x00000001 << 8)                              /*!<R/W 0x0  mbist_ispd 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ISPC                         7
#define VNDR_BIT_RSTN_ISPC                           ((u32)0x00000001 << 7)                              /*!<R/W 0x0  mbist_ispc 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ISPB                         6
#define VNDR_BIT_RSTN_ISPB                           ((u32)0x00000001 << 6)                              /*!<R/W 0x0  mbist_ispb 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ISPA                         5
#define VNDR_BIT_RSTN_ISPA                           ((u32)0x00000001 << 5)                              /*!<R/W 0x0  mbist_ispa 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_GMAC_SRAM                    4
#define VNDR_BIT_RSTN_GMAC_SRAM                      ((u32)0x00000001 << 4)                              /*!<R/W 0x0  mbist_gmac_sram 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_BT_CPU                       3
#define VNDR_BIT_RSTN_BT_CPU                         ((u32)0x00000001 << 3)                              /*!<R/W 0x0  mbist_bt_cpu 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_BT_07                        2
#define VNDR_BIT_RSTN_BT_07                          ((u32)0x00000001 << 2)                              /*!<R/W 0x0  mbist_bt_07 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_BT_06                        1
#define VNDR_BIT_RSTN_BT_06                          ((u32)0x00000001 << 1)                              /*!<R/W 0x0  mbist_bt_06 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_BT_05                        0
#define VNDR_BIT_RSTN_BT_05                          ((u32)0x00000001 << 0)                              /*!<R/W 0x0  mbist_bt_05 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_RSTN_RAM_3
 * @brief                                            (@ 0X0AC)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSTN_ENC_GROUP05_1                31
#define VNDR_BIT_RSTN_ENC_GROUP05_1                  ((u32)0x00000001 << 31)                             /*!<R/W 0x0  mbist_enc_group05_1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP04                  30
#define VNDR_BIT_RSTN_ENC_GROUP04                    ((u32)0x00000001 << 30)                             /*!<R/W 0x0  mbist_enc_group04 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP03_2                29
#define VNDR_BIT_RSTN_ENC_GROUP03_2                  ((u32)0x00000001 << 29)                             /*!<R/W 0x0  mbist_enc_group03_2 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP03_1                28
#define VNDR_BIT_RSTN_ENC_GROUP03_1                  ((u32)0x00000001 << 28)                             /*!<R/W 0x0  mbist_enc_group03_1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP02                  27
#define VNDR_BIT_RSTN_ENC_GROUP02                    ((u32)0x00000001 << 27)                             /*!<R/W 0x0  mbist_enc_group02 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP01                  26
#define VNDR_BIT_RSTN_ENC_GROUP01                    ((u32)0x00000001 << 26)                             /*!<R/W 0x0  mbist_enc_group01 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_RXI316_1P                    25
#define VNDR_BIT_RSTN_RXI316_1P                      ((u32)0x00000001 << 25)                             /*!<R/W 0x0  mbist_rxi316_1p 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_RXI316_2P                    24
#define VNDR_BIT_RSTN_RXI316_2P                      ((u32)0x00000001 << 24)                             /*!<R/W 0x0  mbist_rxi316_2p 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_PLATFORM_GRP                 23
#define VNDR_BIT_RSTN_PLATFORM_GRP                   ((u32)0x00000001 << 23)                             /*!<R/W 0x0  mbist_platform_grp 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_SHARE_MEM_BT                 22
#define VNDR_BIT_RSTN_SHARE_MEM_BT                   ((u32)0x00000001 << 22)                             /*!<R/W 0x0  mbist_share_mem_bt 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_ACLK                      21
#define VNDR_BIT_RSTN_NN_ACLK                        ((u32)0x00000001 << 21)                             /*!<R/W 0x0  mbist_nn_ACLK 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKSH_DIV2                20
#define VNDR_BIT_RSTN_NN_CLKSH_DIV2                  ((u32)0x00000001 << 20)                             /*!<R/W 0x0  mbist_nn_clkSh_div2 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G17               19
#define VNDR_BIT_RSTN_NN_CLKCORE_G17                 ((u32)0x00000001 << 19)                             /*!<R/W 0x0  mbist_nn_clkCore_g17 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G16               18
#define VNDR_BIT_RSTN_NN_CLKCORE_G16                 ((u32)0x00000001 << 18)                             /*!<R/W 0x0  mbist_nn_clkCore_g16 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G15               17
#define VNDR_BIT_RSTN_NN_CLKCORE_G15                 ((u32)0x00000001 << 17)                             /*!<R/W 0x0  mbist_nn_clkCore_g15 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G14               16
#define VNDR_BIT_RSTN_NN_CLKCORE_G14                 ((u32)0x00000001 << 16)                             /*!<R/W 0x0  mbist_nn_clkCore_g14 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G13               15
#define VNDR_BIT_RSTN_NN_CLKCORE_G13                 ((u32)0x00000001 << 15)                             /*!<R/W 0x0  mbist_nn_clkCore_g13 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G12               14
#define VNDR_BIT_RSTN_NN_CLKCORE_G12                 ((u32)0x00000001 << 14)                             /*!<R/W 0x0  mbist_nn_clkCore_g12 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G11               13
#define VNDR_BIT_RSTN_NN_CLKCORE_G11                 ((u32)0x00000001 << 13)                             /*!<R/W 0x0  mbist_nn_clkCore_g11 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G10               12
#define VNDR_BIT_RSTN_NN_CLKCORE_G10                 ((u32)0x00000001 << 12)                             /*!<R/W 0x0  mbist_nn_clkCore_g10 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G9                11
#define VNDR_BIT_RSTN_NN_CLKCORE_G9                  ((u32)0x00000001 << 11)                             /*!<R/W 0x0  mbist_nn_clkCore_g9 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G8                10
#define VNDR_BIT_RSTN_NN_CLKCORE_G8                  ((u32)0x00000001 << 10)                             /*!<R/W 0x0  mbist_nn_clkCore_g8 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G7                9
#define VNDR_BIT_RSTN_NN_CLKCORE_G7                  ((u32)0x00000001 << 9)                              /*!<R/W 0x0  mbist_nn_clkCore_g7 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G6                8
#define VNDR_BIT_RSTN_NN_CLKCORE_G6                  ((u32)0x00000001 << 8)                              /*!<R/W 0x0  mbist_nn_clkCore_g6 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G5                7
#define VNDR_BIT_RSTN_NN_CLKCORE_G5                  ((u32)0x00000001 << 7)                              /*!<R/W 0x0  mbist_nn_clkCore_g5 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G4                6
#define VNDR_BIT_RSTN_NN_CLKCORE_G4                  ((u32)0x00000001 << 6)                              /*!<R/W 0x0  mbist_nn_clkCore_g4 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G3                5
#define VNDR_BIT_RSTN_NN_CLKCORE_G3                  ((u32)0x00000001 << 5)                              /*!<R/W 0x0  mbist_nn_clkCore_g3 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G2                4
#define VNDR_BIT_RSTN_NN_CLKCORE_G2                  ((u32)0x00000001 << 4)                              /*!<R/W 0x0  mbist_nn_clkCore_g2 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G1                3
#define VNDR_BIT_RSTN_NN_CLKCORE_G1                  ((u32)0x00000001 << 3)                              /*!<R/W 0x0  mbist_nn_clkCore_g1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_NN_CLKCORE_G0                2
#define VNDR_BIT_RSTN_NN_CLKCORE_G0                  ((u32)0x00000001 << 2)                              /*!<R/W 0x0  mbist_nn_clkCore_g0 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_VOE_CPU_DCACHE               1
#define VNDR_BIT_RSTN_VOE_CPU_DCACHE                 ((u32)0x00000001 << 1)                              /*!<R/W 0x0  mbist_voe_cpu_dcache 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_VOE_CPU_ICACHE               0
#define VNDR_BIT_RSTN_VOE_CPU_ICACHE                 ((u32)0x00000001 << 0)                              /*!<R/W 0x0  mbist_voe_cpu_icache 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_RSTN_RAM_4
 * @brief                                            (@ 0X0B0)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED9                         16
#define VNDR_MASK_RESERVED9                          ((u32)0x0000FFFF << 16)                             /*!<R 0x0   */
#define VNDR_SHIFT_RSTN_BSTC_HWPAT                   15
#define VNDR_BIT_RSTN_BSTC_HWPAT                     ((u32)0x00000001 << 15)                             /*!<R/W 0x0  mbist_bstc_hwpat 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_RSA                          14
#define VNDR_BIT_RSTN_RSA                            ((u32)0x00000001 << 14)                             /*!<R/W 0x0  mbist_RSA 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP14                  13
#define VNDR_BIT_RSTN_ENC_GROUP14                    ((u32)0x00000001 << 13)                             /*!<R/W 0x0  mbist_enc_group14 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP13_2                12
#define VNDR_BIT_RSTN_ENC_GROUP13_2                  ((u32)0x00000001 << 12)                             /*!<R/W 0x0  mbist_enc_group13_2 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP13_1                11
#define VNDR_BIT_RSTN_ENC_GROUP13_1                  ((u32)0x00000001 << 11)                             /*!<R/W 0x0  mbist_enc_group13_1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP12_2                10
#define VNDR_BIT_RSTN_ENC_GROUP12_2                  ((u32)0x00000001 << 10)                             /*!<R/W 0x0  mbist_enc_group12_2 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP12_1                9
#define VNDR_BIT_RSTN_ENC_GROUP12_1                  ((u32)0x00000001 << 9)                              /*!<R/W 0x0  mbist_enc_group12_1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP11_2                8
#define VNDR_BIT_RSTN_ENC_GROUP11_2                  ((u32)0x00000001 << 8)                              /*!<R/W 0x0  mbist_enc_group11_2 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP11_1                7
#define VNDR_BIT_RSTN_ENC_GROUP11_1                  ((u32)0x00000001 << 7)                              /*!<R/W 0x0  mbist_enc_group11_1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP10_2                6
#define VNDR_BIT_RSTN_ENC_GROUP10_2                  ((u32)0x00000001 << 6)                              /*!<R/W 0x0  mbist_enc_group10_2 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP10_1                5
#define VNDR_BIT_RSTN_ENC_GROUP10_1                  ((u32)0x00000001 << 5)                              /*!<R/W 0x0  mbist_enc_group10_1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP09                  4
#define VNDR_BIT_RSTN_ENC_GROUP09                    ((u32)0x00000001 << 4)                              /*!<R/W 0x0  mbist_enc_group09 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP08                  3
#define VNDR_BIT_RSTN_ENC_GROUP08                    ((u32)0x00000001 << 3)                              /*!<R/W 0x0  mbist_enc_group08 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP07                  2
#define VNDR_BIT_RSTN_ENC_GROUP07                    ((u32)0x00000001 << 2)                              /*!<R/W 0x0  mbist_enc_group07 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP06                  1
#define VNDR_BIT_RSTN_ENC_GROUP06                    ((u32)0x00000001 << 1)                              /*!<R/W 0x0  mbist_enc_group06 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ENC_GROUP05_2                0
#define VNDR_BIT_RSTN_ENC_GROUP05_2                  ((u32)0x00000001 << 0)                              /*!<R/W 0x0  mbist_enc_group05_2 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_RSTN_ROM
 * @brief                                            (@ 0X0B4)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED10                        6
#define VNDR_BIT_RESERVED10                          ((u32)0x00000001 << 6)                              /*!<R 0x0   */
#define VNDR_SHIFT_RSTN_PLATFORM_ROM_GRP             6
#define VNDR_BIT_RSTN_PLATFORM_ROM_GRP               ((u32)0x00000001 << 6)                              /*!<R/W 0x0  mbist_platform_rom_grp 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_VOEMCU_ITCM_ROM              5
#define VNDR_BIT_RSTN_VOEMCU_ITCM_ROM                ((u32)0x00000001 << 5)                              /*!<R/W 0x0  mbist_voemcu_itcm_rom 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_VOEMCU_DTCM_ROM              4
#define VNDR_BIT_RSTN_VOEMCU_DTCM_ROM                ((u32)0x00000001 << 4)                              /*!<R/W 0x0  mbist_voemcu_dtcm_rom 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_CPU_ITCM_ROM                 3
#define VNDR_BIT_RSTN_CPU_ITCM_ROM                   ((u32)0x00000001 << 3)                              /*!<R/W 0x0  mbist_cpu_itcm_rom 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_CPU_DTCM_ROM                 2
#define VNDR_BIT_RSTN_CPU_DTCM_ROM                   ((u32)0x00000001 << 2)                              /*!<R/W 0x0  mbist_cpu_dtcm_rom 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_BT_01                        1
#define VNDR_BIT_RSTN_BT_01                          ((u32)0x00000001 << 1)                              /*!<R/W 0x0  mbist_bt_01 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMCU_IROM                   0
#define VNDR_BIT_RSTN_WLMCU_IROM                     ((u32)0x00000001 << 0)                              /*!<R/W 0x0  mbist_wlmcu_irom 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_CTRL_0
 * @brief                                            (@ 0X0B8)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED11                        12
#define VNDR_MASK_RESERVED11                         ((u32)0x000FFFFF << 12)                             /*!<-- 0x0   */
#define VNDR_SHIFT_ROM_RPT_SEL                       7
#define VNDR_MASK_ROM_RPT_SEL                        ((u32)0x0000001F << 7)                              /*!<R/W 0x0  select the BISR from the rom cell: //=========mbist_wlmcu_irom============ 5'b00000 : WLAN_rom_32768X32M32F80 //=========mbist_bt_01================ 5'b00001: rom32kx32_0 5'b00010:rom32kx32_1 5'b00011:rom8kx32 //=========mbist_cpu_dtcm_rom========== 5'b00100:tm9_rom_2048x64_0 5'b00101:tm9_rom_2048x64_1 5'b00110:tm9_rom_2048x64_2 5'b00111:tm9_rom_2048x64_3 5'b01000:tm9_rom_2048x64_4 //=========mbist_cpu_itcm_rom========== 5'b01001:tm9_rom_4096x64 //=========mbist_voemcu_dtcm_rom====== 5'b01010:VOE_rom_4096x32 //========mbist _voemcu_itcm_rom======= 5'b01011:VOE_rom_256x32m8F250 //========mbist_platform_rom_grp======== 5'b01100:platform_rom_16384x64_0 5'b01101:platform_rom_16384x64_1 5'b01110:platform_rom_16384x64_2 5'b01111:platform_rom_16384x64_3 5'b10000:platform_rom_16384x64_4 5'b10001:platform_rom_16384x64_5  */
#define VNDR_SHIFT_BIST_LOOP_MODE                    6
#define VNDR_BIT_BIST_LOOP_MODE                      ((u32)0x00000001 << 6)                              /*!<R/W 0x0  test looping capability 1: enable loop_mode 0: disable loop_mode */
#define VNDR_SHIFT_DYN_READ_EN                       5
#define VNDR_BIT_DYN_READ_EN                         ((u32)0x00000001 << 5)                              /*!<R/W 0x0  VDDR test enable 1: enable vddr test 0: disable vddr test */
#define VNDR_SHIFT_BIST_DRF_RESUME                   4
#define VNDR_BIT_BIST_DRF_RESUME                     ((u32)0x00000001 << 4)                              /*!<R/W 0x0  resume drf test: 1: stop waiting and resume drf test 0: keep waiting */
#define VNDR_SHIFT_BIST_DRF_MODE                     3
#define VNDR_BIT_BIST_DRF_MODE                       ((u32)0x00000001 << 3)                              /*!<R/W 0x0  enter DRF_MBIST mode 1: enable drf_mbist test 0: disable drf_mbist test */
#define VNDR_SHIFT_BIST_NRML_MODE                    2
#define VNDR_BIT_BIST_NRML_MODE                      ((u32)0x00000001 << 2)                              /*!<R/W 0x0  enter normal mbist mode 1: enable normal mbist test 0: disable normal mbist test */
#define VNDR_SHIFT_BIST_RSTN                         1
#define VNDR_BIT_BIST_RSTN                           ((u32)0x00000001 << 1)                              /*!<R/W 0x0  eable bist function 1: anable the bist block 0: keep in normal mode */
#define VNDR_SHIFT_BIST_CLK_EN_0                     0
#define VNDR_BIT_BIST_CLK_EN_0                       ((u32)0x00000001 << 0)                              /*!<R/W 0x0  eable bist clock for the mbist group 1: anable the bist clock 0: keep gating the clock */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_CTRL_1
 * @brief                                            (@ 0X0BC)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED12                        27
#define VNDR_MASK_RESERVED12                         ((u32)0x0000001F << 27)                             /*!<-- 0x0   */
#define VNDR_SHIFT_BIST_GRP_EN                       0
#define VNDR_MASK_BIST_GRP_EN                        ((u32)0x07FFFFFF << 0)                              /*!<R/W 0x0  enable each memory cell in one mbist group 1: enable the cell 0: disable the memory cell */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_CTRL_2
 * @brief                                            (@ 0X0C0)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED13                        0
#define VNDR_MASK_RESERVED13                         ((u32)0xFFFFFFFF << 0)                              /*!<R 0x0  Reserved */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_STATUS
 * @brief                                            (@ 0X0C4)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED14                        5
#define VNDR_MASK_RESERVED14                         ((u32)0x07FFFFFF << 5)                              /*!<R 0x0   */
#define VNDR_SHIFT_MBIST_START_PAUSE                 4
#define VNDR_BIT_MBIST_START_PAUSE                   ((u32)0x00000001 << 4)                              /*!<R 0x1  indicate whether the drf test is paused 1: test is paused and wait for the next pattern 0: ends waiting and continue the test */
#define VNDR_SHIFT_MBIST_NRML_DONE                   3
#define VNDR_BIT_MBIST_NRML_DONE                     ((u32)0x00000001 << 3)                              /*!<R 0x1  indicate whether the normal mbist test is done 1: normal_test is done 0: normal_test is not done */
#define VNDR_SHIFT_MBIST_NRML_FAIL                   2
#define VNDR_BIT_MBIST_NRML_FAIL                     ((u32)0x00000001 << 2)                              /*!<R 0x0  indicate whether the normal test fail 1: normal_test fail 0: normal_test not fail */
#define VNDR_SHIFT_MBIST_DRF_DONE                    1
#define VNDR_BIT_MBIST_DRF_DONE                      ((u32)0x00000001 << 1)                              /*!<R 0x1  indicate whether the drf_mbist test is done 1: drf_mbist test is done 0: drf_mbist test is not done */
#define VNDR_SHIFT_MBIST_DRF_FAIL                    0
#define VNDR_BIT_MBIST_DRF_FAIL                      ((u32)0x00000001 << 0)                              /*!<R 0x0  indicate whether the drf_mbist test fail 1: drf_mbist test fail 0: drf_mbist test not fail */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DONE_RAM_0
 * @brief                                            (@ 0X0C8)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_DONE_ACBB2_ITLV_A                 31
#define VNDR_BIT_DONE_ACBB2_ITLV_A                   ((u32)0x00000001 << 31)                             /*!<R 0x0  mbist_acbb2_itlv_a 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_SOML_STBC              30
#define VNDR_BIT_DONE_ACBB2_SOML_STBC                ((u32)0x00000001 << 30)                             /*!<R 0x0  mbist_acbb2_soml_stbc 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_PTCSI                  29
#define VNDR_BIT_DONE_ACBB2_PTCSI                    ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_acbb2_ptcsi 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_FFT_NOISE_POWER        28
#define VNDR_BIT_DONE_ACBB2_FFT_NOISE_POWER          ((u32)0x00000001 << 28)                             /*!<R 0x0  mbist_acbb2_fft_noise_power 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_HWIGI_TXINFO_TABLE     27
#define VNDR_BIT_DONE_ACBB2_HWIGI_TXINFO_TABLE       ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_acbb2_hwigi_txinfo_table 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_MF_2ND20               26
#define VNDR_BIT_DONE_ACBB2_MF_2ND20                 ((u32)0x00000001 << 26)                             /*!<R 0x0  mbist_acbb2_mf_2nd20 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_MF_DELAY               25
#define VNDR_BIT_DONE_ACBB2_MF_DELAY                 ((u32)0x00000001 << 25)                             /*!<R 0x0  mbist_acbb2_mf_delay 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_SHARE_DELAY_SND        24
#define VNDR_BIT_DONE_ACBB2_SHARE_DELAY_SND          ((u32)0x00000001 << 24)                             /*!<R 0x0  mbist_acbb2_share_delay_snd 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_SHARE_DELAY_PRI        23
#define VNDR_BIT_DONE_ACBB2_SHARE_DELAY_PRI          ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_acbb2_share_delay_pri 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_SBD                    22
#define VNDR_BIT_DONE_ACBB2_SBD                      ((u32)0x00000001 << 22)                             /*!<R 0x0  mbist_acbb2_sbd 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_SBD_GI                 21
#define VNDR_BIT_DONE_ACBB2_SBD_GI                   ((u32)0x00000001 << 21)                             /*!<R 0x0  mbist_acbb2_sbd_GI 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_DFS_PWDB_FIFO          20
#define VNDR_BIT_DONE_ACBB2_DFS_PWDB_FIFO            ((u32)0x00000001 << 20)                             /*!<R 0x0  mbist_acbb2_dfs_pwdb_fifo 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_DFS_FFT_FIFO           19
#define VNDR_BIT_DONE_ACBB2_DFS_FFT_FIFO             ((u32)0x00000001 << 19)                             /*!<R 0x0  mbist_acbb2_dfs_fft_fifo 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_RPT_KEEPER             18
#define VNDR_BIT_DONE_ACBB2_RPT_KEEPER               ((u32)0x00000001 << 18)                             /*!<R 0x0  mbist_acbb2_rpt_keeper 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_ANAPAR                 17
#define VNDR_BIT_DONE_ACBB2_ANAPAR                   ((u32)0x00000001 << 17)                             /*!<R 0x0  mbist_acbb2_anapar 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_RXAGC                  16
#define VNDR_BIT_DONE_ACBB2_RXAGC                    ((u32)0x00000001 << 16)                             /*!<R 0x0  mbist_acbb2_rxagc 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_AXI_TXDMA              15
#define VNDR_BIT_DONE_WLMAC_AXI_TXDMA                ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_wlmac_axi_txdma 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMCU_IRAM                   14
#define VNDR_BIT_DONE_WLMCU_IRAM                     ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_wlmcu_iram 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMCU_ERAM1                  13
#define VNDR_BIT_DONE_WLMCU_ERAM1                    ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_wlmcu_eram1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMCU_ERAM0                  12
#define VNDR_BIT_DONE_WLMCU_ERAM0                    ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_wlmcu_eram0 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMCU_DRAM                   11
#define VNDR_BIT_DONE_WLMCU_DRAM                     ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_wlmcu_dram 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_TXRPTBUFFER            10
#define VNDR_BIT_DONE_WLMAC_TXRPTBUFFER              ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_wlmac_txrptbuffer 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_RXPKTBUFFER            9
#define VNDR_BIT_DONE_WLMAC_RXPKTBUFFER              ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_wlmac_rxpktbuffer 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_TXPKTBUFFER1           8
#define VNDR_BIT_DONE_WLMAC_TXPKTBUFFER1             ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_wlmac_txpktbuffer1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_TXPKTBUFFER0           7
#define VNDR_BIT_DONE_WLMAC_TXPKTBUFFER0             ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_wlmac_txpktbuffer0 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_TXLLT                  6
#define VNDR_BIT_DONE_WLMAC_TXLLT                    ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_wlmac_txllt 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_MACTX_FIFO             5
#define VNDR_BIT_DONE_WLMAC_MACTX_FIFO               ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_wlmac_mactx_fifo 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_MACRX_FIFO             4
#define VNDR_BIT_DONE_WLMAC_MACRX_FIFO               ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_wlmac_macrx_fifo 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_TKIPRC4                3
#define VNDR_BIT_DONE_WLMAC_TKIPRC4                  ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_wlmac_tkiprc4 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_PSF                    2
#define VNDR_BIT_DONE_WLMAC_PSF                      ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_wlmac_psf 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_RXBACAM                1
#define VNDR_BIT_DONE_WLMAC_RXBACAM                  ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_wlmac_rxbacam 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMAC_KEYSRCH                0
#define VNDR_BIT_DONE_WLMAC_KEYSRCH                  ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_wlmac_keysrch 1: bist done for this mbist group 0: bist not done */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DONE_RAM_1
 * @brief                                            (@ 0X0CC)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_DONE_BT_04                        31
#define VNDR_BIT_DONE_BT_04                          ((u32)0x00000001 << 31)                             /*!<R 0x0  mbist_bt_04 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_BT_03                        30
#define VNDR_BIT_DONE_BT_03                          ((u32)0x00000001 << 30)                             /*!<R 0x0  mbist_bt_03 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_BT_02                        29
#define VNDR_BIT_DONE_BT_02                          ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_bt_02 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_RESERVED15                        28
#define VNDR_BIT_RESERVED15                          ((u32)0x00000001 << 28)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED16                        27
#define VNDR_BIT_RESERVED16                          ((u32)0x00000001 << 27)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED17                        26
#define VNDR_BIT_RESERVED17                          ((u32)0x00000001 << 26)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED18                        25
#define VNDR_BIT_RESERVED18                          ((u32)0x00000001 << 25)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED19                        24
#define VNDR_BIT_RESERVED19                          ((u32)0x00000001 << 24)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED20                        23
#define VNDR_BIT_RESERVED20                          ((u32)0x00000001 << 23)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED21                        22
#define VNDR_BIT_RESERVED21                          ((u32)0x00000001 << 22)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED22                        21
#define VNDR_BIT_RESERVED22                          ((u32)0x00000001 << 21)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_DONE_ACBB2_CCK_CCA                20
#define VNDR_BIT_DONE_ACBB2_CCK_CCA                  ((u32)0x00000001 << 20)                             /*!<R 0x0  mbist_acbb2_cck_cca 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_TMETER                 19
#define VNDR_BIT_DONE_ACBB2_TMETER                   ((u32)0x00000001 << 19)                             /*!<R 0x0  mbist_acbb2_Tmeter 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_PWSF                   18
#define VNDR_BIT_DONE_ACBB2_PWSF                     ((u32)0x00000001 << 18)                             /*!<R 0x0  mbist_acbb2_pwsf 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_IQK_DPD                17
#define VNDR_BIT_DONE_ACBB2_IQK_DPD                  ((u32)0x00000001 << 17)                             /*!<R 0x0  mbist_acbb2_iqk_dpd 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_SYNC                   16
#define VNDR_BIT_DONE_ACBB2_SYNC                     ((u32)0x00000001 << 16)                             /*!<R 0x0  mbist_acbb2_sync 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_NCTL                   15
#define VNDR_BIT_DONE_ACBB2_NCTL                     ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_acbb2_nctl 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_VITERBI                14
#define VNDR_BIT_DONE_ACBB2_VITERBI                  ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_acbb2_viterbi 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_BFEE                   13
#define VNDR_BIT_DONE_ACBB2_BFEE                     ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_acbb2_Bfee 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_SHARE_FEQ_IN_DELAY     12
#define VNDR_BIT_DONE_ACBB2_SHARE_FEQ_IN_DELAY       ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_acbb2_share_feq_in_delay 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_SHARE_FEQ_IN_T0        11
#define VNDR_BIT_DONE_ACBB2_SHARE_FEQ_IN_T0          ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_acbb2_share_feq_in_t0 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_H_STS_PATH1            10
#define VNDR_BIT_DONE_ACBB2_H_STS_PATH1              ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_acbb2_H_sts_path1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_H_STS_PATH0            9
#define VNDR_BIT_DONE_ACBB2_H_STS_PATH0              ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_acbb2_H_sts_path0 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_PRECCA_POWCAL          8
#define VNDR_BIT_DONE_ACBB2_PRECCA_POWCAL            ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_acbb2_precca_powcal 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_NOISE_POW              7
#define VNDR_BIT_DONE_ACBB2_NOISE_POW                ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_acbb2_noise_pow 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_PILOT_TRACKING         6
#define VNDR_BIT_DONE_ACBB2_PILOT_TRACKING           ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_acbb2_pilot_tracking 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_FOE_LLTF               5
#define VNDR_BIT_DONE_ACBB2_FOE_LLTF                 ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_acbb2_foe_lltf 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_GI_BUFF                4
#define VNDR_BIT_DONE_ACBB2_GI_BUFF                  ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_acbb2_gi_buff 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_DLY_512                3
#define VNDR_BIT_DONE_ACBB2_DLY_512                  ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_acbb2_dly_512 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_FFTBUF                 2
#define VNDR_BIT_DONE_ACBB2_FFTBUF                   ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_acbb2_fftbuf 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_FFT                    1
#define VNDR_BIT_DONE_ACBB2_FFT                      ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_acbb2_fft 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ACBB2_ITLV_B                 0
#define VNDR_BIT_DONE_ACBB2_ITLV_B                   ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_acbb2_itlv_b 1: bist done for this mbist group 0: bist not done */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DONE_RAM_2
 * @brief                                            (@ 0X0D0)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_DONE_VOE_FBCU_OBUF_BUF1           31
#define VNDR_BIT_DONE_VOE_FBCU_OBUF_BUF1             ((u32)0x00000001 << 31)                             /*!<R 0x0  mbist_voe_fbcu_obuf_buf1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_VOE_FBCU_OBUF_BUF0           30
#define VNDR_BIT_DONE_VOE_FBCU_OBUF_BUF0             ((u32)0x00000001 << 30)                             /*!<R 0x0  mbist_voe_fbcu_obuf_buf0 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_VOE_SHARED_SRAM              29
#define VNDR_BIT_DONE_VOE_SHARED_SRAM                ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_voe_shared_sram 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_VOEMCU_DTCM                  28
#define VNDR_BIT_DONE_VOEMCU_DTCM                    ((u32)0x00000001 << 28)                             /*!<R 0x0  mbist_voemcu_dtcm 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_VOEMCU_ITCM_RAM              27
#define VNDR_BIT_DONE_VOEMCU_ITCM_RAM                ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_voemcu_itcm_ram 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_CPU_ITCM_RAM                 26
#define VNDR_BIT_DONE_CPU_ITCM_RAM                   ((u32)0x00000001 << 26)                             /*!<R 0x0  mbist_cpu_itcm_ram 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_CPU_PHT_BTB                  25
#define VNDR_BIT_DONE_CPU_PHT_BTB                    ((u32)0x00000001 << 25)                             /*!<R 0x0  mbist_cpu_pht_btb 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_CPU_IC                       24
#define VNDR_BIT_DONE_CPU_IC                         ((u32)0x00000001 << 24)                             /*!<R 0x0  mbist_cpu_ic 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_CPU_DC                       23
#define VNDR_BIT_DONE_CPU_DC                         ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_cpu_dc 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_CPU_DTCM_RAM                 22
#define VNDR_BIT_DONE_CPU_DTCM_RAM                   ((u32)0x00000001 << 22)                             /*!<R 0x0  mbist_cpu_dtcm_ram 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_SDMMC_PPBECC                 21
#define VNDR_BIT_DONE_SDMMC_PPBECC                   ((u32)0x00000001 << 21)                             /*!<R 0x0  mbist_sdmmc_ppbecc 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_SDMMC_DMASB1                 20
#define VNDR_BIT_DONE_SDMMC_DMASB1                   ((u32)0x00000001 << 20)                             /*!<R 0x0  mbist_sdmmc_dmasb1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_USBOTG                       19
#define VNDR_BIT_DONE_USBOTG                         ((u32)0x00000001 << 19)                             /*!<R 0x0  mbist_usbotg 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_SDIO                         18
#define VNDR_BIT_DONE_SDIO                           ((u32)0x00000001 << 18)                             /*!<R 0x0  mbist_sdio 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_MIPI                         17
#define VNDR_BIT_DONE_MIPI                           ((u32)0x00000001 << 17)                             /*!<R 0x0  mbist_mipi 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_OSDBRIDGE                    16
#define VNDR_BIT_DONE_OSDBRIDGE                      ((u32)0x00000001 << 16)                             /*!<R 0x0  mbist_osdbridge 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_OSDPAINTER                   15
#define VNDR_BIT_DONE_OSDPAINTER                     ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_osdpainter 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_VIDEO_AMBA                   14
#define VNDR_BIT_DONE_VIDEO_AMBA                     ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_video_amba 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ISP_DMA3                     13
#define VNDR_BIT_DONE_ISP_DMA3                       ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_isp_dma3 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ISPH_VHDR_ADD                12
#define VNDR_BIT_DONE_ISPH_VHDR_ADD                  ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_isph VHDR add 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ISPG                         11
#define VNDR_BIT_DONE_ISPG                           ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_ispg 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ISPF                         10
#define VNDR_BIT_DONE_ISPF                           ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_ispf 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ISPE                         9
#define VNDR_BIT_DONE_ISPE                           ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_ispe 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ISPD                         8
#define VNDR_BIT_DONE_ISPD                           ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_ispd 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ISPC                         7
#define VNDR_BIT_DONE_ISPC                           ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_ispc 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ISPB                         6
#define VNDR_BIT_DONE_ISPB                           ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_ispb 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ISPA                         5
#define VNDR_BIT_DONE_ISPA                           ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_ispa 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_GMAC_SRAM                    4
#define VNDR_BIT_DONE_GMAC_SRAM                      ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_gmac_sram 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_BT_CPU                       3
#define VNDR_BIT_DONE_BT_CPU                         ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_bt_cpu 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_BT_07                        2
#define VNDR_BIT_DONE_BT_07                          ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_bt_07 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_BT_06                        1
#define VNDR_BIT_DONE_BT_06                          ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_bt_06 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_BT_05                        0
#define VNDR_BIT_DONE_BT_05                          ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_bt_05 1: bist done for this mbist group 0: bist not done */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DONE_RAM_3
 * @brief                                            (@ 0X0D4)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_DONE_ENC_GROUP05_1                31
#define VNDR_BIT_DONE_ENC_GROUP05_1                  ((u32)0x00000001 << 31)                             /*!<R 0x0  mbist_enc_group05_1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP04                  30
#define VNDR_BIT_DONE_ENC_GROUP04                    ((u32)0x00000001 << 30)                             /*!<R 0x0  mbist_enc_group04 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP03_2                29
#define VNDR_BIT_DONE_ENC_GROUP03_2                  ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_enc_group03_2 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP03_1                28
#define VNDR_BIT_DONE_ENC_GROUP03_1                  ((u32)0x00000001 << 28)                             /*!<R 0x0  mbist_enc_group03_1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP02                  27
#define VNDR_BIT_DONE_ENC_GROUP02                    ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_enc_group02 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP01                  26
#define VNDR_BIT_DONE_ENC_GROUP01                    ((u32)0x00000001 << 26)                             /*!<R 0x0  mbist_enc_group01 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_RXI316_1P                    25
#define VNDR_BIT_DONE_RXI316_1P                      ((u32)0x00000001 << 25)                             /*!<R 0x0  mbist_rxi316_1p 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_RXI316_2P                    24
#define VNDR_BIT_DONE_RXI316_2P                      ((u32)0x00000001 << 24)                             /*!<R 0x0  mbist_rxi316_2p 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_PLATFORM_GRP                 23
#define VNDR_BIT_DONE_PLATFORM_GRP                   ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_platform_grp 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_SHARE_MEM_BT                 22
#define VNDR_BIT_DONE_SHARE_MEM_BT                   ((u32)0x00000001 << 22)                             /*!<R 0x0  mbist_share_mem_bt 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_ACLK                      21
#define VNDR_BIT_DONE_NN_ACLK                        ((u32)0x00000001 << 21)                             /*!<R 0x0  mbist_nn_ACLK 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKSH_DIV2                20
#define VNDR_BIT_DONE_NN_CLKSH_DIV2                  ((u32)0x00000001 << 20)                             /*!<R 0x0  mbist_nn_clkSh_div2 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G17               19
#define VNDR_BIT_DONE_NN_CLKCORE_G17                 ((u32)0x00000001 << 19)                             /*!<R 0x0  mbist_nn_clkCore_g17 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G16               18
#define VNDR_BIT_DONE_NN_CLKCORE_G16                 ((u32)0x00000001 << 18)                             /*!<R 0x0  mbist_nn_clkCore_g16 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G15               17
#define VNDR_BIT_DONE_NN_CLKCORE_G15                 ((u32)0x00000001 << 17)                             /*!<R 0x0  mbist_nn_clkCore_g15 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G14               16
#define VNDR_BIT_DONE_NN_CLKCORE_G14                 ((u32)0x00000001 << 16)                             /*!<R 0x0  mbist_nn_clkCore_g14 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G13               15
#define VNDR_BIT_DONE_NN_CLKCORE_G13                 ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_nn_clkCore_g13 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G12               14
#define VNDR_BIT_DONE_NN_CLKCORE_G12                 ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_nn_clkCore_g12 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G11               13
#define VNDR_BIT_DONE_NN_CLKCORE_G11                 ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_nn_clkCore_g11 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G10               12
#define VNDR_BIT_DONE_NN_CLKCORE_G10                 ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_nn_clkCore_g10 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G9                11
#define VNDR_BIT_DONE_NN_CLKCORE_G9                  ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_nn_clkCore_g9 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G8                10
#define VNDR_BIT_DONE_NN_CLKCORE_G8                  ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_nn_clkCore_g8 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G7                9
#define VNDR_BIT_DONE_NN_CLKCORE_G7                  ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_nn_clkCore_g7 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G6                8
#define VNDR_BIT_DONE_NN_CLKCORE_G6                  ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_nn_clkCore_g6 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G5                7
#define VNDR_BIT_DONE_NN_CLKCORE_G5                  ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_nn_clkCore_g5 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G4                6
#define VNDR_BIT_DONE_NN_CLKCORE_G4                  ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_nn_clkCore_g4 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G3                5
#define VNDR_BIT_DONE_NN_CLKCORE_G3                  ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_nn_clkCore_g3 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G2                4
#define VNDR_BIT_DONE_NN_CLKCORE_G2                  ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_nn_clkCore_g2 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G1                3
#define VNDR_BIT_DONE_NN_CLKCORE_G1                  ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_nn_clkCore_g1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_NN_CLKCORE_G0                2
#define VNDR_BIT_DONE_NN_CLKCORE_G0                  ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_nn_clkCore_g0 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_VOE_CPU_DCACHE               1
#define VNDR_BIT_DONE_VOE_CPU_DCACHE                 ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_voe_cpu_dcache 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_VOE_CPU_ICACHE               0
#define VNDR_BIT_DONE_VOE_CPU_ICACHE                 ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_voe_cpu_icache 1: bist done for this mbist group 0: bist not done */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DONE_RAM_4
 * @brief                                            (@ 0X0D8)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED23                        16
#define VNDR_MASK_RESERVED23                         ((u32)0x0000FFFF << 16)                             /*!<R 0x0   */
#define VNDR_SHIFT_DONE_BSTC_HWPAT                   15
#define VNDR_BIT_DONE_BSTC_HWPAT                     ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_BSTC_HWPAT 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_RSA                          14
#define VNDR_BIT_DONE_RSA                            ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_RSA 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP14                  13
#define VNDR_BIT_DONE_ENC_GROUP14                    ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_enc_group14 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP13_2                12
#define VNDR_BIT_DONE_ENC_GROUP13_2                  ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_enc_group13_2 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP13_1                11
#define VNDR_BIT_DONE_ENC_GROUP13_1                  ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_enc_group13_1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP12_2                10
#define VNDR_BIT_DONE_ENC_GROUP12_2                  ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_enc_group12_2 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP12_1                9
#define VNDR_BIT_DONE_ENC_GROUP12_1                  ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_enc_group12_1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP11_2                8
#define VNDR_BIT_DONE_ENC_GROUP11_2                  ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_enc_group11_2 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP11_1                7
#define VNDR_BIT_DONE_ENC_GROUP11_1                  ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_enc_group11_1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP10_2                6
#define VNDR_BIT_DONE_ENC_GROUP10_2                  ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_enc_group10_2 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP10_1                5
#define VNDR_BIT_DONE_ENC_GROUP10_1                  ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_enc_group10_1 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP09                  4
#define VNDR_BIT_DONE_ENC_GROUP09                    ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_enc_group09 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP08                  3
#define VNDR_BIT_DONE_ENC_GROUP08                    ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_enc_group08 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP07                  2
#define VNDR_BIT_DONE_ENC_GROUP07                    ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_enc_group07 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP06                  1
#define VNDR_BIT_DONE_ENC_GROUP06                    ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_enc_group06 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_ENC_GROUP05_2                0
#define VNDR_BIT_DONE_ENC_GROUP05_2                  ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_enc_group05_2 1: bist done for this mbist group 0: bist not done */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DONE_ROM
 * @brief                                            (@ 0X0DC)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED24                        7
#define VNDR_MASK_RESERVED24                         ((u32)0x01FFFFFF << 7)                              /*!<R 0x0   */
#define VNDR_SHIFT_DONE_PLATFORM_ROM_GRP             6
#define VNDR_BIT_DONE_PLATFORM_ROM_GRP               ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_platform_rom_grp 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_VOEMCU_ITCM_ROM              5
#define VNDR_BIT_DONE_VOEMCU_ITCM_ROM                ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_voemcu_itcm_rom 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_VOEMCU_DTCM_ROM              4
#define VNDR_BIT_DONE_VOEMCU_DTCM_ROM                ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_voemcu_dtcm_rom 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_CPU_ITCM_ROM                 3
#define VNDR_BIT_DONE_CPU_ITCM_ROM                   ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_cpu_itcm_rom 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_CPU_DTCM_ROM                 2
#define VNDR_BIT_DONE_CPU_DTCM_ROM                   ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_cpu_dtcm_rom 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_BT_01                        1
#define VNDR_BIT_DONE_BT_01                          ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_bt_01 1: bist done for this mbist group 0: bist not done */
#define VNDR_SHIFT_DONE_WLMCU_IROM                   0
#define VNDR_BIT_DONE_WLMCU_IROM                     ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_wlmcu_irom 1: bist done for this mbist group 0: bist not done */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_0
 * @brief                                            (@ 0X0E0)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED25                        30
#define VNDR_MASK_RESERVED25                         ((u32)0x00000003 << 30)                             /*!<-- --   */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_MF_DELAY          29
#define VNDR_MASK_NRML_FAIL_ACBB2_MF_DELAY           ((u32)0x00000003 << 29)                             /*!<R 0x0  mbist_acbb2_mf_delay 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_SHARE_DELAY_SND   27
#define VNDR_MASK_NRML_FAIL_ACBB2_SHARE_DELAY_SND    ((u32)0x00000003 << 27)                             /*!<R 0x0  mbist_acbb2_share_delay_snd 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_SHARE_DELAY_PRI   25
#define VNDR_MASK_NRML_FAIL_ACBB2_SHARE_DELAY_PRI    ((u32)0x00000003 << 25)                             /*!<R 0x0  mbist_acbb2_share_delay_pri 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_SBD               24
#define VNDR_BIT_NRML_FAIL_ACBB2_SBD                 ((u32)0x00000001 << 24)                             /*!<R 0x0  mbist_acbb2_sbd 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_SBD_GI            23
#define VNDR_BIT_NRML_FAIL_ACBB2_SBD_GI              ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_acbb2_sbd_GI 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_DFS_PWDB_FIFO     22
#define VNDR_BIT_NRML_FAIL_ACBB2_DFS_PWDB_FIFO       ((u32)0x00000001 << 22)                             /*!<R 0x0  mbist_acbb2_dfs_pwdb_fifo 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_DFS_FFT_FIFO      19
#define VNDR_MASK_NRML_FAIL_ACBB2_DFS_FFT_FIFO       ((u32)0x00000007 << 19)                             /*!<R 0x0  mbist_acbb2_dfs_fft_fifo 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_RPT_KEEPER        18
#define VNDR_BIT_NRML_FAIL_ACBB2_RPT_KEEPER          ((u32)0x00000001 << 18)                             /*!<R 0x0  mbist_acbb2_rpt_keeper 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_ANAPAR            17
#define VNDR_BIT_NRML_FAIL_ACBB2_ANAPAR              ((u32)0x00000001 << 17)                             /*!<R 0x0  mbist_acbb2_anapar 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_RXAGC             16
#define VNDR_BIT_NRML_FAIL_ACBB2_RXAGC               ((u32)0x00000001 << 16)                             /*!<R 0x0  mbist_acbb2_rxagc 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_AXI_TXDMA         15
#define VNDR_BIT_NRML_FAIL_WLMAC_AXI_TXDMA           ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_wlmac_axi_txdma 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMCU_IRAM              14
#define VNDR_BIT_NRML_FAIL_WLMCU_IRAM                ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_wlmcu_iram 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMCU_ERAM1             13
#define VNDR_BIT_NRML_FAIL_WLMCU_ERAM1               ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_wlmcu_eram1 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMCU_ERAM0             12
#define VNDR_BIT_NRML_FAIL_WLMCU_ERAM0               ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_wlmcu_eram0 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMCU_DRAM              11
#define VNDR_BIT_NRML_FAIL_WLMCU_DRAM                ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_wlmcu_dram 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_TXRPTBUFFER       10
#define VNDR_BIT_NRML_FAIL_WLMAC_TXRPTBUFFER         ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_wlmac_txrptbuffer 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_RXPKTBUFFER       9
#define VNDR_BIT_NRML_FAIL_WLMAC_RXPKTBUFFER         ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_wlmac_rxpktbuffer 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_TXPKTBUFFER1      8
#define VNDR_BIT_NRML_FAIL_WLMAC_TXPKTBUFFER1        ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_wlmac_txpktbuffer1 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_TXPKTBUFFER0      7
#define VNDR_BIT_NRML_FAIL_WLMAC_TXPKTBUFFER0        ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_wlmac_txpktbuffer0 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_TXLLT             6
#define VNDR_BIT_NRML_FAIL_WLMAC_TXLLT               ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_wlmac_txllt 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_MACTX_FIFO        5
#define VNDR_BIT_NRML_FAIL_WLMAC_MACTX_FIFO          ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_wlmac_mactx_fifo 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_MACRX_FIFO        4
#define VNDR_BIT_NRML_FAIL_WLMAC_MACRX_FIFO          ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_wlmac_macrx_fifo 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_TKIPRC4           3
#define VNDR_BIT_NRML_FAIL_WLMAC_TKIPRC4             ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_wlmac_tkiprc4 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_PSF               2
#define VNDR_BIT_NRML_FAIL_WLMAC_PSF                 ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_wlmac_psf 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_RXBACAM           1
#define VNDR_BIT_NRML_FAIL_WLMAC_RXBACAM             ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_wlmac_rxbacam 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_WLMAC_KEYSRCH           0
#define VNDR_BIT_NRML_FAIL_WLMAC_KEYSRCH             ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_wlmac_keysrch 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_1
 * @brief                                            (@ 0X0E4)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_NRML_FAIL_ACBB2_SHARE_FEQ_IN_T0   31
#define VNDR_BIT_NRML_FAIL_ACBB2_SHARE_FEQ_IN_T0     ((u32)0x00000001 << 31)                             /*!<R 0x0  mbist_acbb2_share_feq_in_t0 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_H_STS_PATH1       30
#define VNDR_BIT_NRML_FAIL_ACBB2_H_STS_PATH1         ((u32)0x00000001 << 30)                             /*!<R 0x0  mbist_acbb2_H_sts_path1 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_H_STS_PATH0       29
#define VNDR_BIT_NRML_FAIL_ACBB2_H_STS_PATH0         ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_acbb2_H_sts_path0 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_PRECCA_POWCAL     28
#define VNDR_BIT_NRML_FAIL_ACBB2_PRECCA_POWCAL       ((u32)0x00000001 << 28)                             /*!<R 0x0  mbist_acbb2_precca_powcal 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_NOISE_POW         27
#define VNDR_BIT_NRML_FAIL_ACBB2_NOISE_POW           ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_acbb2_noise_pow 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_PILOT_TRACKING    25
#define VNDR_MASK_NRML_FAIL_ACBB2_PILOT_TRACKING     ((u32)0x00000003 << 25)                             /*!<R 0x0  mbist_acbb2_pilot_tracking 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_FOE_LLTF          24
#define VNDR_BIT_NRML_FAIL_ACBB2_FOE_LLTF            ((u32)0x00000001 << 24)                             /*!<R 0x0  mbist_acbb2_foe_lltf 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_GI_BUFF           23
#define VNDR_BIT_NRML_FAIL_ACBB2_GI_BUFF             ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_acbb2_gi_buff 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_DLY_512           21
#define VNDR_MASK_NRML_FAIL_ACBB2_DLY_512            ((u32)0x00000003 << 21)                             /*!<R 0x0  mbist_acbb2_dly_512 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_FFTBUF            19
#define VNDR_MASK_NRML_FAIL_ACBB2_FFTBUF             ((u32)0x00000003 << 19)                             /*!<R 0x0  mbist_acbb2_fftbuf 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_FFT               16
#define VNDR_MASK_NRML_FAIL_ACBB2_FFT                ((u32)0x00000007 << 16)                             /*!<R 0x0  mbist_acbb2_fft 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_ITLV_B            12
#define VNDR_MASK_NRML_FAIL_ACBB2_ITLV_B             ((u32)0x0000000F << 12)                             /*!<R 0x0  mbist_acbb2_itlv_b 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_ITLV_A            8
#define VNDR_MASK_NRML_FAIL_ACBB2_ITLV_A             ((u32)0x0000000F << 8)                              /*!<R 0x0  mbist_acbb2_itlv_a 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_SOML_STBC         7
#define VNDR_BIT_NRML_FAIL_ACBB2_SOML_STBC           ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_acbb2_soml_stbc 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_PTCSI             6
#define VNDR_BIT_NRML_FAIL_ACBB2_PTCSI               ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_acbb2_ptcsi 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_FFT_NOISE_POWER   3
#define VNDR_MASK_NRML_FAIL_ACBB2_FFT_NOISE_POWER    ((u32)0x00000007 << 3)                              /*!<R 0x0  mbist_acbb2_fft_noise_power 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_HWIGI_TXINFO_TABLE2
#define VNDR_BIT_NRML_FAIL_ACBB2_HWIGI_TXINFO_TABLE  ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_acbb2_hwigi_txinfo_table 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_MF_2ND20          0
#define VNDR_MASK_NRML_FAIL_ACBB2_MF_2ND20           ((u32)0x00000003 << 0)                              /*!<R 0x0  mbist_acbb2_mf_2nd20 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_2
 * @brief                                            (@ 0X0E8)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED26                        16
#define VNDR_MASK_RESERVED26                         ((u32)0x0000FFFF << 16)                             /*!<R --   */
#define VNDR_SHIFT_NRML_FAIL_MBIST_ACBB2_CCK_CCA     13
#define VNDR_MASK_NRML_FAIL_MBIST_ACBB2_CCK_CCA      ((u32)0x00000007 << 13)                             /*!<R 0x0  mbist_mbist_acbb2_cck_cca 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_TMETER            12
#define VNDR_BIT_NRML_FAIL_ACBB2_TMETER              ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_acbb2_Tmeter 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_PWSF              11
#define VNDR_BIT_NRML_FAIL_ACBB2_PWSF                ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_acbb2_pwsf 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_IQK_DPD           9
#define VNDR_MASK_NRML_FAIL_ACBB2_IQK_DPD            ((u32)0x00000003 << 9)                              /*!<R 0x0  mbist_acbb2_iqk_dpd 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_SYNC              8
#define VNDR_BIT_NRML_FAIL_ACBB2_SYNC                ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_acbb2_sync 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_NCTL              7
#define VNDR_BIT_NRML_FAIL_ACBB2_NCTL                ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_acbb2_nctl 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_VITERBI           3
#define VNDR_MASK_NRML_FAIL_ACBB2_VITERBI            ((u32)0x0000000F << 3)                              /*!<R 0x0  mbist_acbb2_viterbi 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_BFEE              1
#define VNDR_MASK_NRML_FAIL_ACBB2_BFEE               ((u32)0x00000003 << 1)                              /*!<R 0x0  mbist_acbb2_Bfee 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ACBB2_SHARE_FEQ_IN_DELAY0
#define VNDR_BIT_NRML_FAIL_ACBB2_SHARE_FEQ_IN_DELAY  ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_acbb2_share_feq_in_delay 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_3
 * @brief                                            (@ 0X0EC)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED27                        19
#define VNDR_MASK_RESERVED27                         ((u32)0x00001FFF << 19)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_GMAC_SRAM               17
#define VNDR_MASK_NRML_FAIL_GMAC_SRAM                ((u32)0x00000003 << 17)                             /*!<R 0x0  mbist_gmac_sram 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_BT_CPU                  13
#define VNDR_MASK_NRML_FAIL_BT_CPU                   ((u32)0x0000000F << 13)                             /*!<R 0x0  mbist_bt_cpu 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_BT_07                   12
#define VNDR_BIT_NRML_FAIL_BT_07                     ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_bt_07 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_BT_06                   11
#define VNDR_BIT_NRML_FAIL_BT_06                     ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_bt_06 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_BT_05                   10
#define VNDR_BIT_NRML_FAIL_BT_05                     ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_bt_05 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_BT_04                   6
#define VNDR_MASK_NRML_FAIL_BT_04                    ((u32)0x0000000F << 6)                              /*!<R 0x0  mbist_bt_04 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_BT_03                   1
#define VNDR_MASK_NRML_FAIL_BT_03                    ((u32)0x0000001F << 1)                              /*!<R 0x0  mbist_bt_03 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_BT_02                   0
#define VNDR_BIT_NRML_FAIL_BT_02                     ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_bt_02 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_4
 * @brief                                            (@ 0X0F0)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED28                        24
#define VNDR_MASK_RESERVED28                         ((u32)0x000000FF << 24)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_ISPC                    18
#define VNDR_MASK_NRML_FAIL_ISPC                     ((u32)0x0000003F << 18)                             /*!<R 0x0  mbist_ispc 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ISPB                    9
#define VNDR_MASK_NRML_FAIL_ISPB                     ((u32)0x000001FF << 9)                              /*!<R 0x0  mbist_ispb 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ISPA                    0
#define VNDR_MASK_NRML_FAIL_ISPA                     ((u32)0x000001FF << 0)                              /*!<R 0x0  mbist_ispa 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_5
 * @brief                                            (@ 0X0F4)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED29                        29
#define VNDR_MASK_RESERVED29                         ((u32)0x00000007 << 29)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_ISPG                    25
#define VNDR_MASK_NRML_FAIL_ISPG                     ((u32)0x0000000F << 25)                             /*!<R 0x0  mbist_ispg 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ISPF                    17
#define VNDR_MASK_NRML_FAIL_ISPF                     ((u32)0x000000FF << 17)                             /*!<R 0x0  mbist_ispf 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ISPE                    9
#define VNDR_MASK_NRML_FAIL_ISPE                     ((u32)0x000000FF << 9)                              /*!<R 0x0  mbist_ispe 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ISPD                    0
#define VNDR_MASK_NRML_FAIL_ISPD                     ((u32)0x000001FF << 0)                              /*!<R 0x0  mbist_ispd 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_6
 * @brief                                            (@ 0X0F8)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_NRML_FAIL_MIPI                    24
#define VNDR_MASK_NRML_FAIL_MIPI                     ((u32)0x000000FF << 24)                             /*!<R 0x0  mbist_mipi 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_OSDBRIDGE               23
#define VNDR_BIT_NRML_FAIL_OSDBRIDGE                 ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_osdbridge 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_OSDPAINTER              18
#define VNDR_MASK_NRML_FAIL_OSDPAINTER               ((u32)0x0000001F << 18)                             /*!<R 0x0  mbist_osdpainter 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_VIDEO_AMBA              13
#define VNDR_MASK_NRML_FAIL_VIDEO_AMBA               ((u32)0x0000001F << 13)                             /*!<R 0x0  mbist_video_amba 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ISP_DMA3                10
#define VNDR_MASK_NRML_FAIL_ISP_DMA3                 ((u32)0x00000007 << 10)                             /*!<R 0x0  mbist_isp_dma3 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ISPHVHDR                0
#define VNDR_MASK_NRML_FAIL_ISPHVHDR                 ((u32)0x000003FF << 0)                              /*!<R 0x0  mbist_isphVHDR 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_7
 * @brief                                            (@ 0X0FC)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_NRML_FAIL_VOE_CPU_ICACHE          30
#define VNDR_MASK_NRML_FAIL_VOE_CPU_ICACHE           ((u32)0x00000003 << 30)                             /*!<R 0x0  mbist_voe_cpu_icache 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_VOE_FBCU_OBUF_BUF1      29
#define VNDR_BIT_NRML_FAIL_VOE_FBCU_OBUF_BUF1        ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_voe_fbcu_obuf_buf1 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_VOE_FBCU_OBUF_BUF0      28
#define VNDR_BIT_NRML_FAIL_VOE_FBCU_OBUF_BUF0        ((u32)0x00000001 << 28)                             /*!<R 0x0  mbist_voe_fbcu_obuf_buf0 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_VOE_SHARED_SRAM         27
#define VNDR_BIT_NRML_FAIL_VOE_SHARED_SRAM           ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_voe_shared_sram 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_VOEMCU_DTCM             26
#define VNDR_BIT_NRML_FAIL_VOEMCU_DTCM               ((u32)0x00000001 << 26)                             /*!<R 0x0  mbist_voemcu_dtcm 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_VOEMCU_ITCM_RAM         25
#define VNDR_BIT_NRML_FAIL_VOEMCU_ITCM_RAM           ((u32)0x00000001 << 25)                             /*!<R 0x0  mbist_voemcu_itcm_ram 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_CPU_ITCM_RAM            20
#define VNDR_MASK_NRML_FAIL_CPU_ITCM_RAM             ((u32)0x0000001F << 20)                             /*!<R 0x0  mbist_cpu_itcm_ram 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_CPU_PHT_BTB             17
#define VNDR_MASK_NRML_FAIL_CPU_PHT_BTB              ((u32)0x00000007 << 17)                             /*!<R 0x0  mbist_cpu_pht_btb 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_CPU_IC                  13
#define VNDR_MASK_NRML_FAIL_CPU_IC                   ((u32)0x0000000F << 13)                             /*!<R 0x0  mbist_cpu_ic 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_CPU_DC                  10
#define VNDR_MASK_NRML_FAIL_CPU_DC                   ((u32)0x00000007 << 10)                             /*!<R 0x0  mbist_cpu_dc 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_CPU_DTCM_RAM            6
#define VNDR_MASK_NRML_FAIL_CPU_DTCM_RAM             ((u32)0x0000000F << 6)                              /*!<R 0x0  mbist_cpu_dtcm_ram 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_SDMMC_PPBECC            4
#define VNDR_MASK_NRML_FAIL_SDMMC_PPBECC             ((u32)0x00000003 << 4)                              /*!<R 0x0  mbist_sdmmc_ppbecc 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_SDMMC_DMASB1            2
#define VNDR_MASK_NRML_FAIL_SDMMC_DMASB1             ((u32)0x00000003 << 2)                              /*!<R 0x0  mbist_sdmmc_dmasb1 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_USBOTG                  1
#define VNDR_BIT_NRML_FAIL_USBOTG                    ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_usbotg 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_SDIO                    0
#define VNDR_BIT_NRML_FAIL_SDIO                      ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_sdio 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_8
 * @brief                                            (@ 0X100)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED30                        29
#define VNDR_MASK_RESERVED30                         ((u32)0x00000007 << 29)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G4           23
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G4            ((u32)0x0000003F << 23)                             /*!<R 0x0  mbist_nn_clkCore_g4 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G3           17
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G3            ((u32)0x0000003F << 17)                             /*!<R 0x0  mbist_nn_clkCore_g3 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G2           11
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G2            ((u32)0x0000003F << 11)                             /*!<R 0x0  mbist_nn_clkCore_g2 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G1           5
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G1            ((u32)0x0000003F << 5)                              /*!<R 0x0  mbist_nn_clkCore_g1 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G0           2
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G0            ((u32)0x00000007 << 2)                              /*!<R 0x0  mbist_nn_clkCore_g0 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_VOE_CPU_DCACHE          0
#define VNDR_MASK_NRML_FAIL_VOE_CPU_DCACHE           ((u32)0x00000003 << 0)                              /*!<R 0x0  mbist_voe_cpu_dcache 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_9
 * @brief                                            (@ 0X104)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED31                        25
#define VNDR_MASK_RESERVED31                         ((u32)0x0000007F << 25)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G11          23
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G11           ((u32)0x00000003 << 23)                             /*!<R 0x0  mbist_nn_clkCore_g11 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G10          21
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G10           ((u32)0x00000003 << 21)                             /*!<R 0x0  mbist_nn_clkCore_g10 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G9           18
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G9            ((u32)0x00000007 << 18)                             /*!<R 0x0  mbist_nn_clkCore_g9 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G8           14
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G8            ((u32)0x0000000F << 14)                             /*!<R 0x0  mbist_nn_clkCore_g8 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G7           10
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G7            ((u32)0x0000000F << 10)                             /*!<R 0x0  mbist_nn_clkCore_g7 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G6           8
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G6            ((u32)0x00000003 << 8)                              /*!<R 0x0  mbist_nn_clkCore_g6 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G5           0
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G5            ((u32)0x000000FF << 0)                              /*!<R 0x0  mbist_nn_clkCore_g5 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_10
 * @brief                                            (@ 0X108)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED32                        28
#define VNDR_MASK_RESERVED32                         ((u32)0x0000000F << 28)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_NN_ACLK                 27
#define VNDR_BIT_NRML_FAIL_NN_ACLK                   ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_nn_ACLK 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKSH_DIV2           25
#define VNDR_MASK_NRML_FAIL_NN_CLKSH_DIV2            ((u32)0x00000003 << 25)                             /*!<R 0x0  mbist_nn_clkSh_div2 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G17          23
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G17           ((u32)0x00000003 << 23)                             /*!<R 0x0  mbist_nn_clkCore_g17 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G16          20
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G16           ((u32)0x00000007 << 20)                             /*!<R 0x0  mbist_nn_clkCore_g16 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G15          14
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G15           ((u32)0x0000003F << 14)                             /*!<R 0x0  mbist_nn_clkCore_g15 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G14          10
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G14           ((u32)0x0000000F << 10)                             /*!<R 0x0  mbist_nn_clkCore_g14 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G13          8
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G13           ((u32)0x00000003 << 8)                              /*!<R 0x0  mbist_nn_clkCore_g13 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_NN_CLKCORE_G12          0
#define VNDR_MASK_NRML_FAIL_NN_CLKCORE_G12           ((u32)0x000000FF << 0)                              /*!<R 0x0  mbist_nn_clkCore_g12 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_11
 * @brief                                            (@ 0X10C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED33                        22
#define VNDR_MASK_RESERVED33                         ((u32)0x000003FF << 22)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_RXI316_1P               17
#define VNDR_MASK_NRML_FAIL_RXI316_1P                ((u32)0x0000001F << 17)                             /*!<R 0x0  mbist_rxi316_1p 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_RXI316_2P               14
#define VNDR_MASK_NRML_FAIL_RXI316_2P                ((u32)0x00000007 << 14)                             /*!<R 0x0  mbist_rxi316_2p 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_PLATFORM_GRP            6
#define VNDR_MASK_NRML_FAIL_PLATFORM_GRP             ((u32)0x000000FF << 6)                              /*!<R 0x0  mbist_platform_grp 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_SHARE_MEM_BT            0
#define VNDR_MASK_NRML_FAIL_SHARE_MEM_BT             ((u32)0x0000003F << 0)                              /*!<R 0x0  mbist_share_mem_bt 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_12
 * @brief                                            (@ 0X110)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED34                        27
#define VNDR_MASK_RESERVED34                         ((u32)0x0000001F << 27)                             /*!<-    */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP02             13
#define VNDR_MASK_NRML_FAIL_ENC_GROUP02              ((u32)0x00003FFF << 13)                             /*!<R 0x0  mbist_enc_group02 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP01             0
#define VNDR_MASK_NRML_FAIL_ENC_GROUP01              ((u32)0x00001FFF << 0)                              /*!<R 0x0  mbist_enc_group01 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_13
 * @brief                                            (@ 0X114)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP04             14
#define VNDR_MASK_NRML_FAIL_ENC_GROUP04              ((u32)0x0003FFFF << 14)                             /*!<R 0x0  mbist_enc_group04 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP03_2           2
#define VNDR_MASK_NRML_FAIL_ENC_GROUP03_2            ((u32)0x00000FFF << 2)                              /*!<R 0x0  mbist_enc_group03_2 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP03_1           0
#define VNDR_MASK_NRML_FAIL_ENC_GROUP03_1            ((u32)0x00000003 << 0)                              /*!<R 0x0  mbist_enc_group03_1 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_14
 * @brief                                            (@ 0X118)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED35                        24
#define VNDR_MASK_RESERVED35                         ((u32)0x000000FF << 24)                             /*!<-    */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP05_2           6
#define VNDR_MASK_NRML_FAIL_ENC_GROUP05_2            ((u32)0x0003FFFF << 6)                              /*!<R 0x0  mbist_enc_group05_2 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP05_1           0
#define VNDR_MASK_NRML_FAIL_ENC_GROUP05_1            ((u32)0x0000003F << 0)                              /*!<R 0x0  mbist_enc_group05_1 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_15
 * @brief                                            (@ 0X11C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED36                        28
#define VNDR_MASK_RESERVED36                         ((u32)0x0000000F << 28)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP08             22
#define VNDR_MASK_NRML_FAIL_ENC_GROUP08              ((u32)0x0000003F << 22)                             /*!<R 0x0  mbist_enc_group08 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP07             11
#define VNDR_MASK_NRML_FAIL_ENC_GROUP07              ((u32)0x000007FF << 11)                             /*!<R 0x0  mbist_enc_group07 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP06             0
#define VNDR_MASK_NRML_FAIL_ENC_GROUP06              ((u32)0x000007FF << 0)                              /*!<R 0x0  mbist_enc_group06 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_16
 * @brief                                            (@ 0X120)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED37                        15
#define VNDR_MASK_RESERVED37                         ((u32)0x0001FFFF << 15)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP09             0
#define VNDR_MASK_NRML_FAIL_ENC_GROUP09              ((u32)0x00007FFF << 0)                              /*!<R 0x0  mbist_enc_group09 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_17
 * @brief                                            (@ 0X124)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED38                        26
#define VNDR_MASK_RESERVED38                         ((u32)0x0000003F << 26)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP10_2           25
#define VNDR_BIT_NRML_FAIL_ENC_GROUP10_2             ((u32)0x00000001 << 25)                             /*!<R 0x0  mbist_enc_group10_2 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP10_1           0
#define VNDR_MASK_NRML_FAIL_ENC_GROUP10_1            ((u32)0x01FFFFFF << 0)                              /*!<R 0x0  mbist_enc_group10_1 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_18
 * @brief                                            (@ 0X128)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED39                        29
#define VNDR_MASK_RESERVED39                         ((u32)0x00000007 << 29)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP11_2           27
#define VNDR_MASK_NRML_FAIL_ENC_GROUP11_2            ((u32)0x00000003 << 27)                             /*!<R 0x0  mbist_enc_group11_2 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP11_1           0
#define VNDR_MASK_NRML_FAIL_ENC_GROUP11_1            ((u32)0x07FFFFFF << 0)                              /*!<R 0x0  mbist_enc_group11_1 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_19
 * @brief                                            (@ 0X12C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED40                        30
#define VNDR_MASK_RESERVED40                         ((u32)0x00000003 << 30)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP13_1           13
#define VNDR_MASK_NRML_FAIL_ENC_GROUP13_1            ((u32)0x0001FFFF << 13)                             /*!<R 0x0  mbist_enc_group13_1 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP12_2           9
#define VNDR_MASK_NRML_FAIL_ENC_GROUP12_2            ((u32)0x0000000F << 9)                              /*!<R 0x0  mbist_enc_group12_2 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP12_1           0
#define VNDR_MASK_NRML_FAIL_ENC_GROUP12_1            ((u32)0x000001FF << 0)                              /*!<R 0x0  mbist_enc_group12_1 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_NRML_FAIL_RAM_20
 * @brief                                            (@ 0X130)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED41                        23
#define VNDR_MASK_RESERVED41                         ((u32)0x000001FF << 23)                             /*!<R 0x0   */
#define VNDR_SHIFT_NRML_FAIL_BSTC_HWPAT              20
#define VNDR_MASK_NRML_FAIL_BSTC_HWPAT               ((u32)0x00000007 << 20)                             /*!<R 0x0  mbist_bstc_hwpat 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_RSA                     19
#define VNDR_BIT_NRML_FAIL_RSA                       ((u32)0x00000001 << 19)                             /*!<R 0x0  mbist_RSA 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP14             1
#define VNDR_MASK_NRML_FAIL_ENC_GROUP14              ((u32)0x0003FFFF << 1)                              /*!<R 0x0  mbist_enc_group14 1: memory normal test fail 0: memory normal test pass */
#define VNDR_SHIFT_NRML_FAIL_ENC_GROUP13_2           0
#define VNDR_BIT_NRML_FAIL_ENC_GROUP13_2             ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_enc_group13_2 1: memory normal test fail 0: memory normal test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_0
 * @brief                                            (@ 0X134)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED42                        30
#define VNDR_MASK_RESERVED42                         ((u32)0x00000003 << 30)                             /*!<-- --   */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_MF_DELAY           29
#define VNDR_MASK_DRF_FAIL_ACBB2_MF_DELAY            ((u32)0x00000003 << 29)                             /*!<R 0x0  mbist_acbb2_mf_delay 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_SHARE_DELAY_SND    27
#define VNDR_MASK_DRF_FAIL_ACBB2_SHARE_DELAY_SND     ((u32)0x00000003 << 27)                             /*!<R 0x0  mbist_acbb2_share_delay_snd 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_SHARE_DELAY_PRI    25
#define VNDR_MASK_DRF_FAIL_ACBB2_SHARE_DELAY_PRI     ((u32)0x00000003 << 25)                             /*!<R 0x0  mbist_acbb2_share_delay_pri 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_SBD                24
#define VNDR_BIT_DRF_FAIL_ACBB2_SBD                  ((u32)0x00000001 << 24)                             /*!<R 0x0  mbist_acbb2_sbd 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_SBD_GI             23
#define VNDR_BIT_DRF_FAIL_ACBB2_SBD_GI               ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_acbb2_sbd_GI 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_DFS_PWDB_FIFO      22
#define VNDR_BIT_DRF_FAIL_ACBB2_DFS_PWDB_FIFO        ((u32)0x00000001 << 22)                             /*!<R 0x0  mbist_acbb2_dfs_pwdb_fifo 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_DFS_FFT_FIFO       19
#define VNDR_MASK_DRF_FAIL_ACBB2_DFS_FFT_FIFO        ((u32)0x00000007 << 19)                             /*!<R 0x0  mbist_acbb2_dfs_fft_fifo 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_RPT_KEEPER         18
#define VNDR_BIT_DRF_FAIL_ACBB2_RPT_KEEPER           ((u32)0x00000001 << 18)                             /*!<R 0x0  mbist_acbb2_rpt_keeper 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_ANAPAR             17
#define VNDR_BIT_DRF_FAIL_ACBB2_ANAPAR               ((u32)0x00000001 << 17)                             /*!<R 0x0  mbist_acbb2_anapar 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_RXAGC              16
#define VNDR_BIT_DRF_FAIL_ACBB2_RXAGC                ((u32)0x00000001 << 16)                             /*!<R 0x0  mbist_acbb2_rxagc 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_AXI_TXDMA          15
#define VNDR_BIT_DRF_FAIL_WLMAC_AXI_TXDMA            ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_wlmac_axi_txdma 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMCU_IRAM               14
#define VNDR_BIT_DRF_FAIL_WLMCU_IRAM                 ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_wlmcu_iram 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMCU_ERAM1              13
#define VNDR_BIT_DRF_FAIL_WLMCU_ERAM1                ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_wlmcu_eram1 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMCU_ERAM0              12
#define VNDR_BIT_DRF_FAIL_WLMCU_ERAM0                ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_wlmcu_eram0 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMCU_DRAM               11
#define VNDR_BIT_DRF_FAIL_WLMCU_DRAM                 ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_wlmcu_dram 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_TXRPTBUFFER        10
#define VNDR_BIT_DRF_FAIL_WLMAC_TXRPTBUFFER          ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_wlmac_txrptbuffer 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_RXPKTBUFFER        9
#define VNDR_BIT_DRF_FAIL_WLMAC_RXPKTBUFFER          ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_wlmac_rxpktbuffer 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_TXPKTBUFFER1       8
#define VNDR_BIT_DRF_FAIL_WLMAC_TXPKTBUFFER1         ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_wlmac_txpktbuffer1 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_TXPKTBUFFER0       7
#define VNDR_BIT_DRF_FAIL_WLMAC_TXPKTBUFFER0         ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_wlmac_txpktbuffer0 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_TXLLT              6
#define VNDR_BIT_DRF_FAIL_WLMAC_TXLLT                ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_wlmac_txllt 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_MACTX_FIFO         5
#define VNDR_BIT_DRF_FAIL_WLMAC_MACTX_FIFO           ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_wlmac_mactx_fifo 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_MACRX_FIFO         4
#define VNDR_BIT_DRF_FAIL_WLMAC_MACRX_FIFO           ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_wlmac_macrx_fifo 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_TKIPRC4            3
#define VNDR_BIT_DRF_FAIL_WLMAC_TKIPRC4              ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_wlmac_tkiprc4 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_PSF                2
#define VNDR_BIT_DRF_FAIL_WLMAC_PSF                  ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_wlmac_psf 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_RXBACAM            1
#define VNDR_BIT_DRF_FAIL_WLMAC_RXBACAM              ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_wlmac_rxbacam 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_WLMAC_KEYSRCH            0
#define VNDR_BIT_DRF_FAIL_WLMAC_KEYSRCH              ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_wlmac_keysrch 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_1
 * @brief                                            (@ 0X138)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_DRF_FAIL_ACBB2_SHARE_FEQ_IN_T0    31
#define VNDR_BIT_DRF_FAIL_ACBB2_SHARE_FEQ_IN_T0      ((u32)0x00000001 << 31)                             /*!<R 0x0  mbist_acbb2_share_feq_in_t0 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_H_STS_PATH1        30
#define VNDR_BIT_DRF_FAIL_ACBB2_H_STS_PATH1          ((u32)0x00000001 << 30)                             /*!<R 0x0  mbist_acbb2_H_sts_path1 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_H_STS_PATH0        29
#define VNDR_BIT_DRF_FAIL_ACBB2_H_STS_PATH0          ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_acbb2_H_sts_path0 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_PRECCA_POWCAL      28
#define VNDR_BIT_DRF_FAIL_ACBB2_PRECCA_POWCAL        ((u32)0x00000001 << 28)                             /*!<R 0x0  mbist_acbb2_precca_powcal 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_NOISE_POW          27
#define VNDR_BIT_DRF_FAIL_ACBB2_NOISE_POW            ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_acbb2_noise_pow 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_PILOT_TRACKING     25
#define VNDR_MASK_DRF_FAIL_ACBB2_PILOT_TRACKING      ((u32)0x00000003 << 25)                             /*!<R 0x0  mbist_acbb2_pilot_tracking 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_FOE_LLTF           24
#define VNDR_BIT_DRF_FAIL_ACBB2_FOE_LLTF             ((u32)0x00000001 << 24)                             /*!<R 0x0  mbist_acbb2_foe_lltf 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_GI_BUFF            23
#define VNDR_BIT_DRF_FAIL_ACBB2_GI_BUFF              ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_acbb2_gi_buff 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_DLY_512            21
#define VNDR_MASK_DRF_FAIL_ACBB2_DLY_512             ((u32)0x00000003 << 21)                             /*!<R 0x0  mbist_acbb2_dly_512 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_FFTBUF             19
#define VNDR_MASK_DRF_FAIL_ACBB2_FFTBUF              ((u32)0x00000003 << 19)                             /*!<R 0x0  mbist_acbb2_fftbuf 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_FFT                16
#define VNDR_MASK_DRF_FAIL_ACBB2_FFT                 ((u32)0x00000007 << 16)                             /*!<R 0x0  mbist_acbb2_fft 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_ITLV_B             12
#define VNDR_MASK_DRF_FAIL_ACBB2_ITLV_B              ((u32)0x0000000F << 12)                             /*!<R 0x0  mbist_acbb2_itlv_b 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_ITLV_A             8
#define VNDR_MASK_DRF_FAIL_ACBB2_ITLV_A              ((u32)0x0000000F << 8)                              /*!<R 0x0  mbist_acbb2_itlv_a 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_SOML_STBC          7
#define VNDR_BIT_DRF_FAIL_ACBB2_SOML_STBC            ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_acbb2_soml_stbc 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_PTCSI              6
#define VNDR_BIT_DRF_FAIL_ACBB2_PTCSI                ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_acbb2_ptcsi 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_FFT_NOISE_POWER    3
#define VNDR_MASK_DRF_FAIL_ACBB2_FFT_NOISE_POWER     ((u32)0x00000007 << 3)                              /*!<R 0x0  mbist_acbb2_fft_noise_power 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_HWIGI_TXINFO_TABLE 2
#define VNDR_BIT_DRF_FAIL_ACBB2_HWIGI_TXINFO_TABLE   ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_acbb2_hwigi_txinfo_table 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_MF_2ND20           0
#define VNDR_MASK_DRF_FAIL_ACBB2_MF_2ND20            ((u32)0x00000003 << 0)                              /*!<R 0x0  mbist_acbb2_mf_2nd20 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_2
 * @brief                                            (@ 0X13C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED43                        16
#define VNDR_MASK_RESERVED43                         ((u32)0x0000FFFF << 16)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_MBIST_ACBB2_CCK_CCA      13
#define VNDR_MASK_DRF_FAIL_MBIST_ACBB2_CCK_CCA       ((u32)0x00000007 << 13)                             /*!<R 0x0  mbist_mbist_acbb2_cck_cca 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_TMETER             12
#define VNDR_BIT_DRF_FAIL_ACBB2_TMETER               ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_acbb2_Tmeter 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_PWSF               11
#define VNDR_BIT_DRF_FAIL_ACBB2_PWSF                 ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_acbb2_pwsf 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_IQK_DPD            9
#define VNDR_MASK_DRF_FAIL_ACBB2_IQK_DPD             ((u32)0x00000003 << 9)                              /*!<R 0x0  mbist_acbb2_iqk_dpd 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_SYNC               8
#define VNDR_BIT_DRF_FAIL_ACBB2_SYNC                 ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_acbb2_sync 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_NCTL               7
#define VNDR_BIT_DRF_FAIL_ACBB2_NCTL                 ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_acbb2_nctl 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_VITERBI            3
#define VNDR_MASK_DRF_FAIL_ACBB2_VITERBI             ((u32)0x0000000F << 3)                              /*!<R 0x0  mbist_acbb2_viterbi 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_BFEE               1
#define VNDR_MASK_DRF_FAIL_ACBB2_BFEE                ((u32)0x00000003 << 1)                              /*!<R 0x0  mbist_acbb2_Bfee 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ACBB2_SHARE_FEQ_IN_DELAY 0
#define VNDR_BIT_DRF_FAIL_ACBB2_SHARE_FEQ_IN_DELAY   ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_acbb2_share_feq_in_delay 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_3
 * @brief                                            (@ 0X140)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED44                        19
#define VNDR_MASK_RESERVED44                         ((u32)0x00001FFF << 19)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_GMAC_SRAM                17
#define VNDR_MASK_DRF_FAIL_GMAC_SRAM                 ((u32)0x00000003 << 17)                             /*!<R 0x0  mbist_gmac_sram 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_BT_CPU                   13
#define VNDR_MASK_DRF_FAIL_BT_CPU                    ((u32)0x0000000F << 13)                             /*!<R 0x0  mbist_bt_cpu 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_BT_07                    12
#define VNDR_BIT_DRF_FAIL_BT_07                      ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_bt_07 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_BT_06                    11
#define VNDR_BIT_DRF_FAIL_BT_06                      ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_bt_06 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_BT_05                    10
#define VNDR_BIT_DRF_FAIL_BT_05                      ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_bt_05 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_BT_04                    6
#define VNDR_MASK_DRF_FAIL_BT_04                     ((u32)0x0000000F << 6)                              /*!<R 0x0  mbist_bt_04 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_BT_03                    1
#define VNDR_MASK_DRF_FAIL_BT_03                     ((u32)0x0000001F << 1)                              /*!<R 0x0  mbist_bt_03 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_BT_02                    0
#define VNDR_BIT_DRF_FAIL_BT_02                      ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_bt_02 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_4
 * @brief                                            (@ 0X144)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED45                        24
#define VNDR_MASK_RESERVED45                         ((u32)0x000000FF << 24)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_ISPC                     18
#define VNDR_MASK_DRF_FAIL_ISPC                      ((u32)0x0000003F << 18)                             /*!<R 0x0  mbist_ispc 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ISPB                     9
#define VNDR_MASK_DRF_FAIL_ISPB                      ((u32)0x000001FF << 9)                              /*!<R 0x0  mbist_ispb 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ISPA                     0
#define VNDR_MASK_DRF_FAIL_ISPA                      ((u32)0x000001FF << 0)                              /*!<R 0x0  mbist_ispa 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_5
 * @brief                                            (@ 0X148)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED46                        29
#define VNDR_MASK_RESERVED46                         ((u32)0x00000007 << 29)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_ISPG                     25
#define VNDR_MASK_DRF_FAIL_ISPG                      ((u32)0x0000000F << 25)                             /*!<R 0x0  mbist_ispg 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ISPF                     17
#define VNDR_MASK_DRF_FAIL_ISPF                      ((u32)0x000000FF << 17)                             /*!<R 0x0  mbist_ispf 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ISPE                     9
#define VNDR_MASK_DRF_FAIL_ISPE                      ((u32)0x000000FF << 9)                              /*!<R 0x0  mbist_ispe 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ISPD                     0
#define VNDR_MASK_DRF_FAIL_ISPD                      ((u32)0x000001FF << 0)                              /*!<R 0x0  mbist_ispd 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_6
 * @brief                                            (@ 0X14C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_DRF_FAIL_MIPI                     24
#define VNDR_MASK_DRF_FAIL_MIPI                      ((u32)0x000000FF << 24)                             /*!<R 0x0  mbist_mipi 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_OSDBRIDGE                23
#define VNDR_BIT_DRF_FAIL_OSDBRIDGE                  ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_osdbridge 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_OSDPAINTER               18
#define VNDR_MASK_DRF_FAIL_OSDPAINTER                ((u32)0x0000001F << 18)                             /*!<R 0x0  mbist_osdpainter 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_VIDEO_AMBA               13
#define VNDR_MASK_DRF_FAIL_VIDEO_AMBA                ((u32)0x0000001F << 13)                             /*!<R 0x0  mbist_video_amba 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ISP_DMA3                 10
#define VNDR_MASK_DRF_FAIL_ISP_DMA3                  ((u32)0x00000007 << 10)                             /*!<R 0x0  mbist_isp_dma3 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ISPHVHDR                 0
#define VNDR_MASK_DRF_FAIL_ISPHVHDR                  ((u32)0x000003FF << 0)                              /*!<R 0x0  mbist_isphVHDR 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_7
 * @brief                                            (@ 0X150)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_DRF_FAIL_VOE_CPU_ICACHE           30
#define VNDR_MASK_DRF_FAIL_VOE_CPU_ICACHE            ((u32)0x00000003 << 30)                             /*!<R 0x0  mbist_voe_cpu_icache 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_VOE_FBCU_OBUF_BUF1       29
#define VNDR_BIT_DRF_FAIL_VOE_FBCU_OBUF_BUF1         ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_voe_fbcu_obuf_buf1 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_VOE_FBCU_OBUF_BUF0       28
#define VNDR_BIT_DRF_FAIL_VOE_FBCU_OBUF_BUF0         ((u32)0x00000001 << 28)                             /*!<R 0x0  mbist_voe_fbcu_obuf_buf0 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_VOE_SHARED_SRAM          27
#define VNDR_BIT_DRF_FAIL_VOE_SHARED_SRAM            ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_voe_shared_sram 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_VOEMCU_DTCM              26
#define VNDR_BIT_DRF_FAIL_VOEMCU_DTCM                ((u32)0x00000001 << 26)                             /*!<R 0x0  mbist_voemcu_dtcm 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_VOEMCU_ITCM_RAM          25
#define VNDR_BIT_DRF_FAIL_VOEMCU_ITCM_RAM            ((u32)0x00000001 << 25)                             /*!<R 0x0  mbist_voemcu_itcm_ram 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_CPU_ITCM_RAM             20
#define VNDR_MASK_DRF_FAIL_CPU_ITCM_RAM              ((u32)0x0000001F << 20)                             /*!<R 0x0  mbist_cpu_itcm_ram 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_CPU_PHT_BTB              17
#define VNDR_MASK_DRF_FAIL_CPU_PHT_BTB               ((u32)0x00000007 << 17)                             /*!<R 0x0  mbist_cpu_pht_btb 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_CPU_IC                   13
#define VNDR_MASK_DRF_FAIL_CPU_IC                    ((u32)0x0000000F << 13)                             /*!<R 0x0  mbist_cpu_ic 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_CPU_DC                   10
#define VNDR_MASK_DRF_FAIL_CPU_DC                    ((u32)0x00000007 << 10)                             /*!<R 0x0  mbist_cpu_dc 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_CPU_DTCM_RAM             6
#define VNDR_MASK_DRF_FAIL_CPU_DTCM_RAM              ((u32)0x0000000F << 6)                              /*!<R 0x0  mbist_cpu_dtcm_ram 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_SDMMC_PPBECC             4
#define VNDR_MASK_DRF_FAIL_SDMMC_PPBECC              ((u32)0x00000003 << 4)                              /*!<R 0x0  mbist_sdmmc_ppbecc 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_SDMMC_DMASB1             2
#define VNDR_MASK_DRF_FAIL_SDMMC_DMASB1              ((u32)0x00000003 << 2)                              /*!<R 0x0  mbist_sdmmc_dmasb1 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_USBOTG                   1
#define VNDR_BIT_DRF_FAIL_USBOTG                     ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_usbotg 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_SDIO                     0
#define VNDR_BIT_DRF_FAIL_SDIO                       ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_sdio 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_8
 * @brief                                            (@ 0X154)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED47                        29
#define VNDR_MASK_RESERVED47                         ((u32)0x00000007 << 29)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G4            23
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G4             ((u32)0x0000003F << 23)                             /*!<R 0x0  mbist_nn_clkCore_g4 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G3            17
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G3             ((u32)0x0000003F << 17)                             /*!<R 0x0  mbist_nn_clkCore_g3 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G2            11
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G2             ((u32)0x0000003F << 11)                             /*!<R 0x0  mbist_nn_clkCore_g2 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G1            5
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G1             ((u32)0x0000003F << 5)                              /*!<R 0x0  mbist_nn_clkCore_g1 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G0            2
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G0             ((u32)0x00000007 << 2)                              /*!<R 0x0  mbist_nn_clkCore_g0 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_VOE_CPU_DCACHE           0
#define VNDR_MASK_DRF_FAIL_VOE_CPU_DCACHE            ((u32)0x00000003 << 0)                              /*!<R 0x0  mbist_voe_cpu_dcache 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_9
 * @brief                                            (@ 0X158)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED48                        25
#define VNDR_MASK_RESERVED48                         ((u32)0x0000007F << 25)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G11           23
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G11            ((u32)0x00000003 << 23)                             /*!<R 0x0  mbist_nn_clkCore_g11 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G10           21
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G10            ((u32)0x00000003 << 21)                             /*!<R 0x0  mbist_nn_clkCore_g10 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G9            18
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G9             ((u32)0x00000007 << 18)                             /*!<R 0x0  mbist_nn_clkCore_g9 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G8            14
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G8             ((u32)0x0000000F << 14)                             /*!<R 0x0  mbist_nn_clkCore_g8 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G7            10
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G7             ((u32)0x0000000F << 10)                             /*!<R 0x0  mbist_nn_clkCore_g7 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G6            8
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G6             ((u32)0x00000003 << 8)                              /*!<R 0x0  mbist_nn_clkCore_g6 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G5            0
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G5             ((u32)0x000000FF << 0)                              /*!<R 0x0  mbist_nn_clkCore_g5 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_10
 * @brief                                            (@ 0X15C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED49                        28
#define VNDR_MASK_RESERVED49                         ((u32)0x0000000F << 28)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_NN_ACLK                  27
#define VNDR_BIT_DRF_FAIL_NN_ACLK                    ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_nn_ACLK 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKSH_DIV2            25
#define VNDR_MASK_DRF_FAIL_NN_CLKSH_DIV2             ((u32)0x00000003 << 25)                             /*!<R 0x0  mbist_nn_clkSh_div2 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G17           23
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G17            ((u32)0x00000003 << 23)                             /*!<R 0x0  mbist_nn_clkCore_g17 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G16           20
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G16            ((u32)0x00000007 << 20)                             /*!<R 0x0  mbist_nn_clkCore_g16 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G15           14
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G15            ((u32)0x0000003F << 14)                             /*!<R 0x0  mbist_nn_clkCore_g15 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G14           10
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G14            ((u32)0x0000000F << 10)                             /*!<R 0x0  mbist_nn_clkCore_g14 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G13           8
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G13            ((u32)0x00000003 << 8)                              /*!<R 0x0  mbist_nn_clkCore_g13 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_NN_CLKCORE_G12           0
#define VNDR_MASK_DRF_FAIL_NN_CLKCORE_G12            ((u32)0x000000FF << 0)                              /*!<R 0x0  mbist_nn_clkCore_g12 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_11
 * @brief                                            (@ 0X160)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED50                        22
#define VNDR_MASK_RESERVED50                         ((u32)0x000003FF << 22)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_RXI316_1P                17
#define VNDR_MASK_DRF_FAIL_RXI316_1P                 ((u32)0x0000001F << 17)                             /*!<R 0x0  mbist_rxi316_1p 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_RXI316_2P                14
#define VNDR_MASK_DRF_FAIL_RXI316_2P                 ((u32)0x00000007 << 14)                             /*!<R 0x0  mbist_rxi316_2p 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_PLATFORM_GRP             6
#define VNDR_MASK_DRF_FAIL_PLATFORM_GRP              ((u32)0x000000FF << 6)                              /*!<R 0x0  mbist_platform_grp 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_SHARE_MEM_BT             0
#define VNDR_MASK_DRF_FAIL_SHARE_MEM_BT              ((u32)0x0000003F << 0)                              /*!<R 0x0  mbist_share_mem_bt 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_12
 * @brief                                            (@ 0X164)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED51                        27
#define VNDR_MASK_RESERVED51                         ((u32)0x0000001F << 27)                             /*!<-    */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP02              13
#define VNDR_MASK_DRF_FAIL_ENC_GROUP02               ((u32)0x00003FFF << 13)                             /*!<R 0x0  mbist_enc_group02 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP01              0
#define VNDR_MASK_DRF_FAIL_ENC_GROUP01               ((u32)0x00001FFF << 0)                              /*!<R 0x0  mbist_enc_group01 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_13
 * @brief                                            (@ 0X168)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP04              14
#define VNDR_MASK_DRF_FAIL_ENC_GROUP04               ((u32)0x0003FFFF << 14)                             /*!<R 0x0  mbist_enc_group04 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP03_2            2
#define VNDR_MASK_DRF_FAIL_ENC_GROUP03_2             ((u32)0x00000FFF << 2)                              /*!<R 0x0  mbist_enc_group03_2 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP03_1            0
#define VNDR_MASK_DRF_FAIL_ENC_GROUP03_1             ((u32)0x00000003 << 0)                              /*!<R 0x0  mbist_enc_group03_1 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_14
 * @brief                                            (@ 0X16C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED52                        24
#define VNDR_MASK_RESERVED52                         ((u32)0x000000FF << 24)                             /*!<-    */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP05_2            6
#define VNDR_MASK_DRF_FAIL_ENC_GROUP05_2             ((u32)0x0003FFFF << 6)                              /*!<R 0x0  mbist_enc_group05_2 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP05_1            0
#define VNDR_MASK_DRF_FAIL_ENC_GROUP05_1             ((u32)0x0000003F << 0)                              /*!<R 0x0  mbist_enc_group05_1 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_15
 * @brief                                            (@ 0X170)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED53                        28
#define VNDR_MASK_RESERVED53                         ((u32)0x0000000F << 28)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP08              22
#define VNDR_MASK_DRF_FAIL_ENC_GROUP08               ((u32)0x0000003F << 22)                             /*!<R 0x0  mbist_enc_group08 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP07              11
#define VNDR_MASK_DRF_FAIL_ENC_GROUP07               ((u32)0x000007FF << 11)                             /*!<R 0x0  mbist_enc_group07 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP06              0
#define VNDR_MASK_DRF_FAIL_ENC_GROUP06               ((u32)0x000007FF << 0)                              /*!<R 0x0  mbist_enc_group06 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_16
 * @brief                                            (@ 0X174)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED54                        15
#define VNDR_MASK_RESERVED54                         ((u32)0x0001FFFF << 15)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP09              0
#define VNDR_MASK_DRF_FAIL_ENC_GROUP09               ((u32)0x00007FFF << 0)                              /*!<R 0x0  mbist_enc_group09 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_17
 * @brief                                            (@ 0X178)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED55                        26
#define VNDR_MASK_RESERVED55                         ((u32)0x0000003F << 26)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP10_2            25
#define VNDR_BIT_DRF_FAIL_ENC_GROUP10_2              ((u32)0x00000001 << 25)                             /*!<R 0x0  mbist_enc_group10_2 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP10_1            0
#define VNDR_MASK_DRF_FAIL_ENC_GROUP10_1             ((u32)0x01FFFFFF << 0)                              /*!<R 0x0  mbist_enc_group10_1 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_18
 * @brief                                            (@ 0X17C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED56                        29
#define VNDR_MASK_RESERVED56                         ((u32)0x00000007 << 29)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP11_2            27
#define VNDR_MASK_DRF_FAIL_ENC_GROUP11_2             ((u32)0x00000003 << 27)                             /*!<R 0x0  mbist_enc_group11_2 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP11_1            0
#define VNDR_MASK_DRF_FAIL_ENC_GROUP11_1             ((u32)0x07FFFFFF << 0)                              /*!<R 0x0  mbist_enc_group11_1 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_19
 * @brief                                            (@ 0X180)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED57                        30
#define VNDR_MASK_RESERVED57                         ((u32)0x00000003 << 30)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP13_1            13
#define VNDR_MASK_DRF_FAIL_ENC_GROUP13_1             ((u32)0x0001FFFF << 13)                             /*!<R 0x0  mbist_enc_group13_1 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP12_2            9
#define VNDR_MASK_DRF_FAIL_ENC_GROUP12_2             ((u32)0x0000000F << 9)                              /*!<R 0x0  mbist_enc_group12_2 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP12_1            0
#define VNDR_MASK_DRF_FAIL_ENC_GROUP12_1             ((u32)0x000001FF << 0)                              /*!<R 0x0  mbist_enc_group12_1 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_DRF_FAIL_RAM_20
 * @brief                                            (@ 0X184)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED58                        23
#define VNDR_MASK_RESERVED58                         ((u32)0x000001FF << 23)                             /*!<R 0x0   */
#define VNDR_SHIFT_DRF_FAIL_BSTC_HWPAT               20
#define VNDR_MASK_DRF_FAIL_BSTC_HWPAT                ((u32)0x00000007 << 20)                             /*!<R 0x0  mbist_bstc_hwpat 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_RSA                      19
#define VNDR_BIT_DRF_FAIL_RSA                        ((u32)0x00000001 << 19)                             /*!<R 0x0  mbist_RSA 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP14              1
#define VNDR_MASK_DRF_FAIL_ENC_GROUP14               ((u32)0x0003FFFF << 1)                              /*!<R 0x0  mbist_enc_group14 1: memory drf test fail 0: memory drf test pass */
#define VNDR_SHIFT_DRF_FAIL_ENC_GROUP13_2            0
#define VNDR_BIT_DRF_FAIL_ENC_GROUP13_2              ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_enc_group13_2 1: memory drf test fail 0: memory drf test pass */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_START_PAUSE_RAM_0
 * @brief                                            (@ 0X188)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RSTN_ACBB2_ITLV_A                 31
#define VNDR_BIT_RSTN_ACBB2_ITLV_A                   ((u32)0x00000001 << 31)                             /*!<R 0x0  mbist_acbb2_itlv_a 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SOML_STBC              30
#define VNDR_BIT_RSTN_ACBB2_SOML_STBC                ((u32)0x00000001 << 30)                             /*!<R 0x0  mbist_acbb2_soml_stbc 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_PTCSI                  29
#define VNDR_BIT_RSTN_ACBB2_PTCSI                    ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_acbb2_ptcsi 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_FFT_NOISE_POWER        28
#define VNDR_BIT_RSTN_ACBB2_FFT_NOISE_POWER          ((u32)0x00000001 << 28)                             /*!<R 0x0  mbist_acbb2_fft_noise_power 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_HWIGI_TXINFO_TABLE     27
#define VNDR_BIT_RSTN_ACBB2_HWIGI_TXINFO_TABLE       ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_acbb2_hwigi_txinfo_table 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_MF_2ND20               26
#define VNDR_BIT_RSTN_ACBB2_MF_2ND20                 ((u32)0x00000001 << 26)                             /*!<R 0x0  mbist_acbb2_mf_2nd20 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_MF_DELAY               25
#define VNDR_BIT_RSTN_ACBB2_MF_DELAY                 ((u32)0x00000001 << 25)                             /*!<R 0x0  mbist_acbb2_mf_delay 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SHARE_DELAY_SND        24
#define VNDR_BIT_RSTN_ACBB2_SHARE_DELAY_SND          ((u32)0x00000001 << 24)                             /*!<R 0x0  mbist_acbb2_share_delay_snd 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SHARE_DELAY_PRI        23
#define VNDR_BIT_RSTN_ACBB2_SHARE_DELAY_PRI          ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_acbb2_share_delay_pri 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SBD                    22
#define VNDR_BIT_RSTN_ACBB2_SBD                      ((u32)0x00000001 << 22)                             /*!<R 0x0  mbist_acbb2_sbd 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_SBD_GI                 21
#define VNDR_BIT_RSTN_ACBB2_SBD_GI                   ((u32)0x00000001 << 21)                             /*!<R 0x0  mbist_acbb2_sbd_GI 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_DFS_PWDB_FIFO          20
#define VNDR_BIT_RSTN_ACBB2_DFS_PWDB_FIFO            ((u32)0x00000001 << 20)                             /*!<R 0x0  mbist_acbb2_dfs_pwdb_fifo 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_DFS_FFT_FIFO           19
#define VNDR_BIT_RSTN_ACBB2_DFS_FFT_FIFO             ((u32)0x00000001 << 19)                             /*!<R 0x0  mbist_acbb2_dfs_fft_fifo 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_RPT_KEEPER             18
#define VNDR_BIT_RSTN_ACBB2_RPT_KEEPER               ((u32)0x00000001 << 18)                             /*!<R 0x0  mbist_acbb2_rpt_keeper 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_ANAPAR                 17
#define VNDR_BIT_RSTN_ACBB2_ANAPAR                   ((u32)0x00000001 << 17)                             /*!<R 0x0  mbist_acbb2_anapar 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_ACBB2_RXAGC                  16
#define VNDR_BIT_RSTN_ACBB2_RXAGC                    ((u32)0x00000001 << 16)                             /*!<R 0x0  mbist_acbb2_rxagc 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_AXI_TXDMA              15
#define VNDR_BIT_RSTN_WLMAC_AXI_TXDMA                ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_wlmac_axi_txdma 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMCU_IRAM                   14
#define VNDR_BIT_RSTN_WLMCU_IRAM                     ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_wlmcu_iram 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMCU_ERAM1                  13
#define VNDR_BIT_RSTN_WLMCU_ERAM1                    ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_wlmcu_eram1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMCU_ERAM0                  12
#define VNDR_BIT_RSTN_WLMCU_ERAM0                    ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_wlmcu_eram0 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMCU_DRAM                   11
#define VNDR_BIT_RSTN_WLMCU_DRAM                     ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_wlmcu_dram 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_TXRPTBUFFER            10
#define VNDR_BIT_RSTN_WLMAC_TXRPTBUFFER              ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_wlmac_txrptbuffer 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_RXPKTBUFFER            9
#define VNDR_BIT_RSTN_WLMAC_RXPKTBUFFER              ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_wlmac_rxpktbuffer 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_TXPKTBUFFER1           8
#define VNDR_BIT_RSTN_WLMAC_TXPKTBUFFER1             ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_wlmac_txpktbuffer1 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_TXPKTBUFFER0           7
#define VNDR_BIT_RSTN_WLMAC_TXPKTBUFFER0             ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_wlmac_txpktbuffer0 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_TXLLT                  6
#define VNDR_BIT_RSTN_WLMAC_TXLLT                    ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_wlmac_txllt 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_MACTX_FIFO             5
#define VNDR_BIT_RSTN_WLMAC_MACTX_FIFO               ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_wlmac_mactx_fifo 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_MACRX_FIFO             4
#define VNDR_BIT_RSTN_WLMAC_MACRX_FIFO               ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_wlmac_macrx_fifo 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_TKIPRC4                3
#define VNDR_BIT_RSTN_WLMAC_TKIPRC4                  ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_wlmac_tkiprc4 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_PSF                    2
#define VNDR_BIT_RSTN_WLMAC_PSF                      ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_wlmac_psf 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_RSTN_WLMAC_RXBACAM                1
#define VNDR_BIT_RSTN_WLMAC_RXBACAM                  ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_wlmac_rxbacam 1: release rstn for mbist logic, enable this mbist group 0: keep this mbist group logic in reset */
#define VNDR_SHIFT_START_PAUSE_WLMAC_KEYSRCH         0
#define VNDR_BIT_START_PAUSE_WLMAC_KEYSRCH           ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_wlmac_keysrch 1: drf test pause 0: drf test not paused */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_START_PAUSE_RAM_1
 * @brief                                            (@ 0X18C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_START_PAUSE_BT_04                 31
#define VNDR_BIT_START_PAUSE_BT_04                   ((u32)0x00000001 << 31)                             /*!<R 0x0  mbist_bt_04 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_START_PAUSE_BT_03                 30
#define VNDR_BIT_START_PAUSE_BT_03                   ((u32)0x00000001 << 30)                             /*!<R 0x0  mbist_bt_03 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_START_PAUSE_BT_02                 29
#define VNDR_BIT_START_PAUSE_BT_02                   ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_bt_02 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_RESERVED59                        28
#define VNDR_BIT_RESERVED59                          ((u32)0x00000001 << 28)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED60                        27
#define VNDR_BIT_RESERVED60                          ((u32)0x00000001 << 27)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED61                        26
#define VNDR_BIT_RESERVED61                          ((u32)0x00000001 << 26)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED62                        25
#define VNDR_BIT_RESERVED62                          ((u32)0x00000001 << 25)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED63                        24
#define VNDR_BIT_RESERVED63                          ((u32)0x00000001 << 24)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED64                        23
#define VNDR_BIT_RESERVED64                          ((u32)0x00000001 << 23)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED65                        22
#define VNDR_BIT_RESERVED65                          ((u32)0x00000001 << 22)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_RESERVED66                        21
#define VNDR_BIT_RESERVED66                          ((u32)0x00000001 << 21)                             /*!<R 0x0  -- */
#define VNDR_SHIFT_ACBB2_CCK_CCA                     20
#define VNDR_BIT_ACBB2_CCK_CCA                       ((u32)0x00000001 << 20)                             /*!<R 0x0  mbist_acbb2_cck_cca 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_TMETER                      19
#define VNDR_BIT_ACBB2_TMETER                        ((u32)0x00000001 << 19)                             /*!<R 0x0  mbist_acbb2_Tmeter 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_PWSF                        18
#define VNDR_BIT_ACBB2_PWSF                          ((u32)0x00000001 << 18)                             /*!<R 0x0  mbist_acbb2_pwsf 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_IQK_DPD                     17
#define VNDR_BIT_ACBB2_IQK_DPD                       ((u32)0x00000001 << 17)                             /*!<R 0x0  mbist_acbb2_iqk_dpd 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_SYNC                        16
#define VNDR_BIT_ACBB2_SYNC                          ((u32)0x00000001 << 16)                             /*!<R 0x0  mbist_acbb2_sync 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_NCTL                        15
#define VNDR_BIT_ACBB2_NCTL                          ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_acbb2_nctl 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_VITERBI                     14
#define VNDR_BIT_ACBB2_VITERBI                       ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_acbb2_viterbi 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_BFEE                        13
#define VNDR_BIT_ACBB2_BFEE                          ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_acbb2_Bfee 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_SHARE_FEQ_IN_DELAY          12
#define VNDR_BIT_ACBB2_SHARE_FEQ_IN_DELAY            ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_acbb2_share_feq_in_delay 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_SHARE_FEQ_IN_T0             11
#define VNDR_BIT_ACBB2_SHARE_FEQ_IN_T0               ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_acbb2_share_feq_in_t0 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_H_STS_PATH1                 10
#define VNDR_BIT_ACBB2_H_STS_PATH1                   ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_acbb2_H_sts_path1 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_H_STS_PATH0                 9
#define VNDR_BIT_ACBB2_H_STS_PATH0                   ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_acbb2_H_sts_path0 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_PRECCA_POWCAL               8
#define VNDR_BIT_ACBB2_PRECCA_POWCAL                 ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_acbb2_precca_powcal 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_NOISE_POW                   7
#define VNDR_BIT_ACBB2_NOISE_POW                     ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_acbb2_noise_pow 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_PILOT_TRACKING              6
#define VNDR_BIT_ACBB2_PILOT_TRACKING                ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_acbb2_pilot_tracking 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_FOE_LLTF                    5
#define VNDR_BIT_ACBB2_FOE_LLTF                      ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_acbb2_foe_lltf 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_GI_BUFF                     4
#define VNDR_BIT_ACBB2_GI_BUFF                       ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_acbb2_gi_buff 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_DLY_512                     3
#define VNDR_BIT_ACBB2_DLY_512                       ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_acbb2_dly_512 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_FFTBUF                      2
#define VNDR_BIT_ACBB2_FFTBUF                        ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_acbb2_fftbuf 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_FFT                         1
#define VNDR_BIT_ACBB2_FFT                           ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_acbb2_fft 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ACBB2_ITLV_B                      0
#define VNDR_BIT_ACBB2_ITLV_B                        ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_acbb2_itlv_b 1: drf test pause 0: drf test not paused */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_START_PAUSE_RAM_2
 * @brief                                            (@ 0X190)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_VOE_FBCU_OBUF_BUF1                31
#define VNDR_BIT_VOE_FBCU_OBUF_BUF1                  ((u32)0x00000001 << 31)                             /*!<R 0x0  mbist_voe_fbcu_obuf_buf1 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_VOE_FBCU_OBUF_BUF0                30
#define VNDR_BIT_VOE_FBCU_OBUF_BUF0                  ((u32)0x00000001 << 30)                             /*!<R 0x0  mbist_voe_fbcu_obuf_buf0 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_VOE_SHARED_SRAM                   29
#define VNDR_BIT_VOE_SHARED_SRAM                     ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_voe_shared_sram 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_VOEMCU_DTCM                       28
#define VNDR_BIT_VOEMCU_DTCM                         ((u32)0x00000001 << 28)                             /*!<R 0x0  mbist_voemcu_dtcm 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_VOEMCU_ITCM_RAM                   27
#define VNDR_BIT_VOEMCU_ITCM_RAM                     ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_voemcu_itcm_ram 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_CPU_ITCM_RAM                      26
#define VNDR_BIT_CPU_ITCM_RAM                        ((u32)0x00000001 << 26)                             /*!<R 0x0  mbist_cpu_itcm_ram 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_CPU_PHT_BTB                       25
#define VNDR_BIT_CPU_PHT_BTB                         ((u32)0x00000001 << 25)                             /*!<R 0x0  mbist_cpu_pht_btb 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_CPU_IC                            24
#define VNDR_BIT_CPU_IC                              ((u32)0x00000001 << 24)                             /*!<R 0x0  mbist_cpu_ic 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_CPU_DC                            23
#define VNDR_BIT_CPU_DC                              ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_cpu_dc 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_CPU_DTCM_RAM                      22
#define VNDR_BIT_CPU_DTCM_RAM                        ((u32)0x00000001 << 22)                             /*!<R 0x0  mbist_cpu_dtcm_ram 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_SDMMC_PPBECC                      21
#define VNDR_BIT_SDMMC_PPBECC                        ((u32)0x00000001 << 21)                             /*!<R 0x0  mbist_sdmmc_ppbecc 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_SDMMC_DMASB1                      20
#define VNDR_BIT_SDMMC_DMASB1                        ((u32)0x00000001 << 20)                             /*!<R 0x0  mbist_sdmmc_dmasb1 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_USBOTG                            19
#define VNDR_BIT_USBOTG                              ((u32)0x00000001 << 19)                             /*!<R 0x0  mbist_usbotg 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_SDIO                              18
#define VNDR_BIT_SDIO                                ((u32)0x00000001 << 18)                             /*!<R 0x0  mbist_sdio 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_MIPI                              17
#define VNDR_BIT_MIPI                                ((u32)0x00000001 << 17)                             /*!<R 0x0  mbist_mipi 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_OSDBRIDGE                         16
#define VNDR_BIT_OSDBRIDGE                           ((u32)0x00000001 << 16)                             /*!<R 0x0  mbist_osdbridge 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_OSDPAINTER                        15
#define VNDR_BIT_OSDPAINTER                          ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_osdpainter 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_VIDEO_AMBA                        14
#define VNDR_BIT_VIDEO_AMBA                          ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_video_amba 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ISP_DMA3                          13
#define VNDR_BIT_ISP_DMA3                            ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_isp_dma3 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ISPH_VHDR_ADD                     12
#define VNDR_BIT_ISPH_VHDR_ADD                       ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_isph VHDR add 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ISPG                              11
#define VNDR_BIT_ISPG                                ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_ispg 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ISPF                              10
#define VNDR_BIT_ISPF                                ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_ispf 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ISPE                              9
#define VNDR_BIT_ISPE                                ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_ispe 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ISPD                              8
#define VNDR_BIT_ISPD                                ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_ispd 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ISPC                              7
#define VNDR_BIT_ISPC                                ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_ispc 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ISPB                              6
#define VNDR_BIT_ISPB                                ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_ispb 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ISPA                              5
#define VNDR_BIT_ISPA                                ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_ispa 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_GMAC_SRAM                         4
#define VNDR_BIT_GMAC_SRAM                           ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_gmac_sram 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_BT_CPU                            3
#define VNDR_BIT_BT_CPU                              ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_bt_cpu 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_BT_07                             2
#define VNDR_BIT_BT_07                               ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_bt_07 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_BT_06                             1
#define VNDR_BIT_BT_06                               ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_bt_06 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_BT_05                             0
#define VNDR_BIT_BT_05                               ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_bt_05 1: drf test pause 0: drf test not paused */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_START_PAUSE_RAM_3
 * @brief                                            (@ 0X194)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_ENC_GROUP05_1                     31
#define VNDR_BIT_ENC_GROUP05_1                       ((u32)0x00000001 << 31)                             /*!<R 0x0  mbist_enc_group05_1 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP04                       30
#define VNDR_BIT_ENC_GROUP04                         ((u32)0x00000001 << 30)                             /*!<R 0x0  mbist_enc_group04 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP03_2                     29
#define VNDR_BIT_ENC_GROUP03_2                       ((u32)0x00000001 << 29)                             /*!<R 0x0  mbist_enc_group03_2 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP03_1                     28
#define VNDR_BIT_ENC_GROUP03_1                       ((u32)0x00000001 << 28)                             /*!<R 0x0  mbist_enc_group03_1 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP02                       27
#define VNDR_BIT_ENC_GROUP02                         ((u32)0x00000001 << 27)                             /*!<R 0x0  mbist_enc_group02 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP01                       26
#define VNDR_BIT_ENC_GROUP01                         ((u32)0x00000001 << 26)                             /*!<R 0x0  mbist_enc_group01 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_RXI316_1P                         25
#define VNDR_BIT_RXI316_1P                           ((u32)0x00000001 << 25)                             /*!<R 0x0  mbist_rxi316_1p 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_RXI316_2P                         24
#define VNDR_BIT_RXI316_2P                           ((u32)0x00000001 << 24)                             /*!<R 0x0  mbist_rxi316_2p 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_PLATFORM_GRP                      23
#define VNDR_BIT_PLATFORM_GRP                        ((u32)0x00000001 << 23)                             /*!<R 0x0  mbist_platform_grp 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_SHARE_MEM_BT                      22
#define VNDR_BIT_SHARE_MEM_BT                        ((u32)0x00000001 << 22)                             /*!<R 0x0  mbist_share_mem_bt 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_ACLK                           21
#define VNDR_BIT_NN_ACLK                             ((u32)0x00000001 << 21)                             /*!<R 0x0  mbist_nn_ACLK 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKSH_DIV2                     20
#define VNDR_BIT_NN_CLKSH_DIV2                       ((u32)0x00000001 << 20)                             /*!<R 0x0  mbist_nn_clkSh_div2 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G17                    19
#define VNDR_BIT_NN_CLKCORE_G17                      ((u32)0x00000001 << 19)                             /*!<R 0x0  mbist_nn_clkCore_g17 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G16                    18
#define VNDR_BIT_NN_CLKCORE_G16                      ((u32)0x00000001 << 18)                             /*!<R 0x0  mbist_nn_clkCore_g16 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G15                    17
#define VNDR_BIT_NN_CLKCORE_G15                      ((u32)0x00000001 << 17)                             /*!<R 0x0  mbist_nn_clkCore_g15 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G14                    16
#define VNDR_BIT_NN_CLKCORE_G14                      ((u32)0x00000001 << 16)                             /*!<R 0x0  mbist_nn_clkCore_g14 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G13                    15
#define VNDR_BIT_NN_CLKCORE_G13                      ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_nn_clkCore_g13 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G12                    14
#define VNDR_BIT_NN_CLKCORE_G12                      ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_nn_clkCore_g12 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G11                    13
#define VNDR_BIT_NN_CLKCORE_G11                      ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_nn_clkCore_g11 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G10                    12
#define VNDR_BIT_NN_CLKCORE_G10                      ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_nn_clkCore_g10 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G9                     11
#define VNDR_BIT_NN_CLKCORE_G9                       ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_nn_clkCore_g9 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G8                     10
#define VNDR_BIT_NN_CLKCORE_G8                       ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_nn_clkCore_g8 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G7                     9
#define VNDR_BIT_NN_CLKCORE_G7                       ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_nn_clkCore_g7 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G6                     8
#define VNDR_BIT_NN_CLKCORE_G6                       ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_nn_clkCore_g6 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G5                     7
#define VNDR_BIT_NN_CLKCORE_G5                       ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_nn_clkCore_g5 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G4                     6
#define VNDR_BIT_NN_CLKCORE_G4                       ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_nn_clkCore_g4 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G3                     5
#define VNDR_BIT_NN_CLKCORE_G3                       ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_nn_clkCore_g3 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G2                     4
#define VNDR_BIT_NN_CLKCORE_G2                       ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_nn_clkCore_g2 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G1                     3
#define VNDR_BIT_NN_CLKCORE_G1                       ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_nn_clkCore_g1 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_NN_CLKCORE_G0                     2
#define VNDR_BIT_NN_CLKCORE_G0                       ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_nn_clkCore_g0 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_VOE_CPU_DCACHE                    1
#define VNDR_BIT_VOE_CPU_DCACHE                      ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_voe_cpu_dcache 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_VOE_CPU_ICACHE                    0
#define VNDR_BIT_VOE_CPU_ICACHE                      ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_voe_cpu_icache 1: drf test pause 0: drf test not paused */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_START_PAUSE_RAM_4
 * @brief                                            (@ 0X198)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_RESERVED67                        16
#define VNDR_MASK_RESERVED67                         ((u32)0x0000FFFF << 16)                             /*!<R 0x0   */
#define VNDR_SHIFT_BSTC_HWPAT                        15
#define VNDR_BIT_BSTC_HWPAT                          ((u32)0x00000001 << 15)                             /*!<R 0x0  mbist_bstc_hwpat 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_RSA                               14
#define VNDR_BIT_RSA                                 ((u32)0x00000001 << 14)                             /*!<R 0x0  mbist_RSA 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP14                       13
#define VNDR_BIT_ENC_GROUP14                         ((u32)0x00000001 << 13)                             /*!<R 0x0  mbist_enc_group14 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP13_2                     12
#define VNDR_BIT_ENC_GROUP13_2                       ((u32)0x00000001 << 12)                             /*!<R 0x0  mbist_enc_group13_2 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP13_1                     11
#define VNDR_BIT_ENC_GROUP13_1                       ((u32)0x00000001 << 11)                             /*!<R 0x0  mbist_enc_group13_1 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP12_2                     10
#define VNDR_BIT_ENC_GROUP12_2                       ((u32)0x00000001 << 10)                             /*!<R 0x0  mbist_enc_group12_2 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP12_1                     9
#define VNDR_BIT_ENC_GROUP12_1                       ((u32)0x00000001 << 9)                              /*!<R 0x0  mbist_enc_group12_1 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP11_2                     8
#define VNDR_BIT_ENC_GROUP11_2                       ((u32)0x00000001 << 8)                              /*!<R 0x0  mbist_enc_group11_2 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP11_1                     7
#define VNDR_BIT_ENC_GROUP11_1                       ((u32)0x00000001 << 7)                              /*!<R 0x0  mbist_enc_group11_1 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP10_2                     6
#define VNDR_BIT_ENC_GROUP10_2                       ((u32)0x00000001 << 6)                              /*!<R 0x0  mbist_enc_group10_2 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP10_1                     5
#define VNDR_BIT_ENC_GROUP10_1                       ((u32)0x00000001 << 5)                              /*!<R 0x0  mbist_enc_group10_1 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP09                       4
#define VNDR_BIT_ENC_GROUP09                         ((u32)0x00000001 << 4)                              /*!<R 0x0  mbist_enc_group09 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP08                       3
#define VNDR_BIT_ENC_GROUP08                         ((u32)0x00000001 << 3)                              /*!<R 0x0  mbist_enc_group08 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP07                       2
#define VNDR_BIT_ENC_GROUP07                         ((u32)0x00000001 << 2)                              /*!<R 0x0  mbist_enc_group07 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP06                       1
#define VNDR_BIT_ENC_GROUP06                         ((u32)0x00000001 << 1)                              /*!<R 0x0  mbist_enc_group06 1: drf test pause 0: drf test not paused */
#define VNDR_SHIFT_ENC_GROUP05_2                     0
#define VNDR_BIT_ENC_GROUP05_2                       ((u32)0x00000001 << 0)                              /*!<R 0x0  mbist_enc_group05_2 1: drf test pause 0: drf test not paused */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_ROM_0
 * @brief                                            (@ 0X19C)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_REG_ROM_MISR_DOUT                 0
#define VNDR_MASK_REG_ROM_MISR_DOUT                  ((u32)0xFFFFFFFF << 0)                              /*!<R 0x0  reg_misr_dout */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_REG_MBIST_ROM_1
 * @brief                                            (@ 0X1A0)
 * @{
 *****************************************************************************/
#define VNDR_SHIFT_REG_ROM_MISR_DOUT                 0
#define VNDR_MASK_REG_ROM_MISR_DOUT                  ((u32)0xFFFFFFFF << 0)                              /*!<R 0x0  reg_misr_dout */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_VNDR
 * @{
 * @brief rtl8735b_VNDR Register Declaration
 *****************************************************************************/
typedef struct {
	__I  uint32_t VNDR_REG_RSVD1 ;                         /*!<   register,  Address offset: 0x000 */
	__I  uint32_t VNDR_REG_LOW_PRI_INT_MODE ;              /*!<   register,  Address offset: 0x004 */
	__I  uint32_t VNDR_REG_LOW_PRI_INT_IMR ;               /*!<   register,  Address offset: 0x008 */
	__I  uint32_t VNDR_REG_LOW_PRI_INT_ISR ;               /*!<   register,  Address offset: 0x00C */
	__I  uint32_t VNDR_REG_RSVD2 ;                         /*!<   register,  Address offset: 0x010 */
	__IO uint32_t VNDR_REG_ANACK_CAL_CTRL ;                /*!<   register,  Address offset: 0x014 */
	__IO uint32_t VNDR_REG_RSVD3 ;                         /*!<   register,  Address offset: 0x018 */
	__O  uint32_t VNDR_REG_RSVD4 ;                         /*!<   register,  Address offset: 0x01C */
	__IO uint32_t VNDR_REG_DATA_FIFO_SWAP_CTRL ;           /*!<   register,  Address offset: 0x020 */
	__I  uint32_t VNDR_REG_I2C_DGLCH_CTRL ;                /*!<   register,  Address offset: 0x024 */
	__O  uint32_t VNDR_REG_RSVD5 ;                         /*!<   register,  Address offset: 0x028 */
	__O  uint32_t VNDR_REG_RSVD6 ;                         /*!<   register,  Address offset: 0x02C */
	__I  uint32_t VNDR_REG_GDMA0_ISR ;                     /*!<   register,  Address offset: 0x030 */
	__I  uint32_t VNDR_REG_GDMA1_ISR ;                     /*!<   register,  Address offset: 0x034 */
	__I  uint32_t VNDR_REG_SGPIO_ISR ;                     /*!<   register,  Address offset: 0x038 */
	__I  uint32_t VNDR_REG_UART_ISR ;                      /*!<   register,  Address offset: 0x03C */
	__I  uint32_t VNDR_REG_I2C_ISR ;                       /*!<   register,  Address offset: 0x040 */
	__I  uint32_t VNDR_REG_SPI_ISR ;                       /*!<   register,  Address offset: 0x044 */
	__I  uint32_t VNDR_REG_I2S_ISR ;                       /*!<   register,  Address offset: 0x048 */
	__I  uint32_t VNDR_REG_WL_ISR ;                        /*!<   register,  Address offset: 0x04C */
	__IO uint32_t VNDR_REG_RSVD7 ;                         /*!<   register,  Address offset: 0x050 */
	__IO uint32_t VNDR_REG_RSVD8 ;                         /*!<   register,  Address offset: 0x054 */
	__IO uint32_t VNDR_REG_RSVD9 ;                         /*!<   register,  Address offset: 0x058 */
	__IO uint32_t VNDR_REG_RSVDA ;                         /*!<   register,  Address offset: 0x05C */
	__IO uint32_t VNDR_REG_GDMA_HSKS_CTRL ;                /*!<   register,  Address offset: 0x060 */
	__IO uint32_t VNDR_REG_RSVDB ;                         /*!<   register,  Address offset: 0x064 */
	__IO uint32_t VNDR_REG_RSVDC ;                         /*!<   register,  Address offset: 0x068 */
	__IO uint32_t VNDR_REG_RSVDD ;                         /*!<   register,  Address offset: 0x06C */
	__IO uint32_t VNDR_REG_RSVDE ;                         /*!<   register,  Address offset: 0x070 */
	__IO uint32_t VNDR_REG_RSVDF ;                         /*!<   register,  Address offset: 0x074 */
	__IO uint32_t VNDR_REG_RSVDG ;                         /*!<   register,  Address offset: 0x078 */
	__IO uint32_t VNDR_REG_RSVDH ;                         /*!<   register,  Address offset: 0x07C */
	__IO uint32_t VNDR_REG_RSVDI ;                         /*!<   register,  Address offset: 0x080 */
	__IO uint32_t VNDR_REG_RSVDJ ;                         /*!<   register,  Address offset: 0x084 */
	__IO uint32_t VNDR_REG_RSVDK ;                         /*!<   register,  Address offset: 0x088 */
	__IO uint32_t VNDR_REG_RSVDL ;                         /*!<   register,  Address offset: 0x08C */
	__IO uint32_t VNDR_REG_LX_CTRL0 ;                      /*!<   register,  Address offset: 0x090 */
	__I  uint32_t VNDR_REG_LX_CTRL1 ;                      /*!<   register,  Address offset: 0x094 */
	__I  uint32_t VNDR_REG_LX_CTRL2 ;                      /*!<   register,  Address offset: 0x098 */
	__I  uint32_t VNDR_REG_LX_CTRL3 ;                      /*!<   register,  Address offset: 0x09C */
	__IO uint32_t VNDR_REG_MBIST_RSTN_RAM_0 ;              /*!<   register,  Address offset: 0x0A0 */
	__IO uint32_t VNDR_REG_MBIST_RSTN_RAM_1 ;              /*!<   register,  Address offset: 0x0A4 */
	__IO uint32_t VNDR_REG_MBIST_RSTN_RAM_2 ;              /*!<   register,  Address offset: 0x0A8 */
	__IO uint32_t VNDR_REG_MBIST_RSTN_RAM_3 ;              /*!<   register,  Address offset: 0x0AC */
	__IO uint32_t VNDR_REG_MBIST_RSTN_RAM_4 ;              /*!<   register,  Address offset: 0x0B0 */
	__IO uint32_t VNDR_REG_MBIST_RSTN_ROM ;                /*!<   register,  Address offset: 0x0B4 */
	__IO uint32_t VNDR_REG_MBIST_CTRL_0 ;                  /*!<   register,  Address offset: 0x0B8 */
	__IO uint32_t VNDR_REG_MBIST_CTRL_1 ;                  /*!<   register,  Address offset: 0x0BC */
	__I  uint32_t VNDR_REG_MBIST_CTRL_2 ;                  /*!<   register,  Address offset: 0x0C0 */
	__I  uint32_t VNDR_REG_MBIST_STATUS ;                  /*!<   register,  Address offset: 0x0C4 */
	__I  uint32_t VNDR_REG_MBIST_DONE_RAM_0 ;              /*!<   register,  Address offset: 0x0C8 */
	__I  uint32_t VNDR_REG_MBIST_DONE_RAM_1 ;              /*!<   register,  Address offset: 0x0CC */
	__I  uint32_t VNDR_REG_MBIST_DONE_RAM_2 ;              /*!<   register,  Address offset: 0x0D0 */
	__I  uint32_t VNDR_REG_MBIST_DONE_RAM_3 ;              /*!<   register,  Address offset: 0x0D4 */
	__I  uint32_t VNDR_REG_MBIST_DONE_RAM_4 ;              /*!<   register,  Address offset: 0x0D8 */
	__I  uint32_t VNDR_REG_MBIST_DONE_ROM ;                /*!<   register,  Address offset: 0x0DC */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_0 ;         /*!<   register,  Address offset: 0x0E0 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_1 ;         /*!<   register,  Address offset: 0x0E4 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_2 ;         /*!<   register,  Address offset: 0x0E8 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_3 ;         /*!<   register,  Address offset: 0x0EC */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_4 ;         /*!<   register,  Address offset: 0x0F0 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_5 ;         /*!<   register,  Address offset: 0x0F4 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_6 ;         /*!<   register,  Address offset: 0x0F8 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_7 ;         /*!<   register,  Address offset: 0x0FC */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_8 ;         /*!<   register,  Address offset: 0x100 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_9 ;         /*!<   register,  Address offset: 0x104 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_10 ;        /*!<   register,  Address offset: 0x108 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_11 ;        /*!<   register,  Address offset: 0x10C */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_12 ;        /*!<   register,  Address offset: 0x110 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_13 ;        /*!<   register,  Address offset: 0x114 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_14 ;        /*!<   register,  Address offset: 0x118 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_15 ;        /*!<   register,  Address offset: 0x11C */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_16 ;        /*!<   register,  Address offset: 0x120 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_17 ;        /*!<   register,  Address offset: 0x124 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_18 ;        /*!<   register,  Address offset: 0x128 */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_19 ;        /*!<   register,  Address offset: 0x12C */
	__I  uint32_t VNDR_REG_MBIST_NRML_FAIL_RAM_20 ;        /*!<   register,  Address offset: 0x130 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_0 ;          /*!<   register,  Address offset: 0x134 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_1 ;          /*!<   register,  Address offset: 0x138 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_2 ;          /*!<   register,  Address offset: 0x13C */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_3 ;          /*!<   register,  Address offset: 0x140 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_4 ;          /*!<   register,  Address offset: 0x144 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_5 ;          /*!<   register,  Address offset: 0x148 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_6 ;          /*!<   register,  Address offset: 0x14C */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_7 ;          /*!<   register,  Address offset: 0x150 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_8 ;          /*!<   register,  Address offset: 0x154 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_9 ;          /*!<   register,  Address offset: 0x158 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_10 ;         /*!<   register,  Address offset: 0x15C */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_11 ;         /*!<   register,  Address offset: 0x160 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_12 ;         /*!<   register,  Address offset: 0x164 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_13 ;         /*!<   register,  Address offset: 0x168 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_14 ;         /*!<   register,  Address offset: 0x16C */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_15 ;         /*!<   register,  Address offset: 0x170 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_16 ;         /*!<   register,  Address offset: 0x174 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_17 ;         /*!<   register,  Address offset: 0x178 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_18 ;         /*!<   register,  Address offset: 0x17C */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_19 ;         /*!<   register,  Address offset: 0x180 */
	__I  uint32_t VNDR_REG_MBIST_DRF_FAIL_RAM_20 ;         /*!<   register,  Address offset: 0x184 */
	__I  uint32_t VNDR_REG_MBIST_START_PAUSE_RAM_0 ;       /*!<   register,  Address offset: 0x188 */
	__I  uint32_t VNDR_REG_MBIST_START_PAUSE_RAM_1 ;       /*!<   register,  Address offset: 0x18C */
	__I  uint32_t VNDR_REG_MBIST_START_PAUSE_RAM_2 ;       /*!<   register,  Address offset: 0x190 */
	__I  uint32_t VNDR_REG_MBIST_START_PAUSE_RAM_3 ;       /*!<   register,  Address offset: 0x194 */
	__I  uint32_t VNDR_REG_MBIST_START_PAUSE_RAM_4 ;       /*!<   register,  Address offset: 0x198 */
	__I  uint32_t VNDR_REG_MBIST_ROM_0 ;                   /*!<   register,  Address offset: 0x19C */
	__I  uint32_t VNDR_REG_MBIST_ROM_1 ;                   /*!<   register,          Address offset: 0x1A0 */
} VNDR_TypeDef;
/** @} */

#endif
