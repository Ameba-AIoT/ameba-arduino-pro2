#ifndef _RTL8735B_SGPIO_TYPE_H_
#define _RTL8735B_SGPIO_TYPE_H_

/**************************************************************************//**
 * @defgroup SGPIO_RXTMR_CTRL
 * @brief  RX Timer Control Register                 (@ 0X000)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXTMREDGE_SEL                    8
#define SGPIO_MASK_RXTMREDGE_SEL                     ((u32)0x00000003 << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXTMR_CRST                       1
#define SGPIO_BIT_RXTMR_CRST                         ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXTMR_CEN                        0
#define SGPIO_BIT_RXTMR_CEN                          ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXPRVAL
 * @brief  RX Maximum Prescale Register              (@ 0X004)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXPRVAL                          0
#define SGPIO_MASK_RXPRVAL                           ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXPRTC
 * @brief  RX Timer Prescale Register                (@ 0X008)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXPRTC                           0
#define SGPIO_MASK_RXPRTC                            ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXTC
 * @brief  RX Timer Counter Register                 (@ 0X00C)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXTC                             0
#define SGPIO_MASK_RXTC                              ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXMC
 * @brief  Position Counter Register                 (@ 0X010)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RX_POSSTOP_EN                    15
#define SGPIO_BIT_RX_POSSTOP_EN                      ((u32)0x00000001 << 15)                             /*!<R/W 0   */
#define SGPIO_SHIFT_RX_POSRST_EN                     14
#define SGPIO_BIT_RX_POSRST_EN                       ((u32)0x00000001 << 14)                             /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR0MULSTOP_EN                 13
#define SGPIO_BIT_RX_MR0MULSTOP_EN                   ((u32)0x00000001 << 13)                             /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR0MULRST_EN                  12
#define SGPIO_BIT_RX_MR0MULRST_EN                    ((u32)0x00000001 << 12)                             /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR2SCLK_EN                    11
#define SGPIO_BIT_RX_MR2SCLK_EN                      ((u32)0x00000001 << 11)                             /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR2STOP_EN                    10
#define SGPIO_BIT_RX_MR2STOP_EN                      ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR2RST_EN                     9
#define SGPIO_BIT_RX_MR2RST_EN                       ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR2I_EN                       8
#define SGPIO_BIT_RX_MR2I_EN                         ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR1SCLK_EN                    7
#define SGPIO_BIT_RX_MR1SCLK_EN                      ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR1STOP_EN                    6
#define SGPIO_BIT_RX_MR1STOP_EN                      ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR1RST_EN                     5
#define SGPIO_BIT_RX_MR1RST_EN                       ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR1I_EN                       4
#define SGPIO_BIT_RX_MR1I_EN                         ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR0SCLK_EN                    3
#define SGPIO_BIT_RX_MR0SCLK_EN                      ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR0STOP_EN                    2
#define SGPIO_BIT_RX_MR0STOP_EN                      ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR0RST_EN                     1
#define SGPIO_BIT_RX_MR0RST_EN                       ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR0I_EN                       0
#define SGPIO_BIT_RX_MR0I_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXMR0
 * @brief  RX Match Register 0                       (@ 0X014)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXMR0                            0
#define SGPIO_MASK_RXMR0                             ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXMR1
 * @brief  RX Match Register 1                       (@ 0X018)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXMR1                            0
#define SGPIO_MASK_RXMR1                             ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXMR2
 * @brief  RX Match Register 2                       (@ 0X01C)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXMR2                            0
#define SGPIO_MASK_RXMR2                             ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_CAP_CTRL
 * @brief  Capture Control Register                  (@ 0X020)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_CAP_CMPVAL                       16
#define SGPIO_MASK_CAP_CMPVAL                        ((u32)0x0000FFFF << 16)                             /*!<R/W 0   */
#define SGPIO_SHIFT_CAPVALID_EN                      8
#define SGPIO_BIT_CAPVALID_EN                        ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_CAP_CMPVAL_SEL                   7
#define SGPIO_BIT_CAP_CMPVAL_SEL                     ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SGPIO_SHIFT_CAP_RXTCSTOP_EN                  6
#define SGPIO_BIT_CAP_RXTCSTOP_EN                    ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SGPIO_SHIFT_CAP_RXTCRST_EN                   5
#define SGPIO_BIT_CAP_RXTCRST_EN                     ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SGPIO_SHIFT_CAPRE_EN                         4
#define SGPIO_BIT_CAPRE_EN                           ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SGPIO_SHIFT_CAPFE_EN                         3
#define SGPIO_BIT_CAPFE_EN                           ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SGPIO_SHIFT_CAPSRC_SEL                       2
#define SGPIO_BIT_CAPSRC_SEL                         ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SGPIO_SHIFT_CAPI_EN                          1
#define SGPIO_BIT_CAPI_EN                            ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SGPIO_SHIFT_CAP_EN                           0
#define SGPIO_BIT_CAP_EN                             ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_CAPR
 * @brief  Capture Register                          (@ 0X024)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_CAPR                             0
#define SGPIO_MASK_CAPR                              ((u32)0x0000FFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULTMR_CTRL
 * @brief  Multiple Timer Control Register           (@ 0X028)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULMODE_EN                       8
#define SGPIO_MASK_MULMODE_EN                        ((u32)0x00000003 << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULTMR_CRST                      1
#define SGPIO_BIT_MULTMR_CRST                        ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULTMR_CEN                       0
#define SGPIO_BIT_MULTMR_CEN                         ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULPRVAL
 * @brief  Multiple Maximum Prescale Register        (@ 0X02C)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULPRVAL                         0
#define SGPIO_MASK_MULPRVAL                          ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULPRTC
 * @brief  Multiple Timer Prescale Register          (@ 0X030)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULPRTC                          0
#define SGPIO_MASK_MULPRTC                           ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULTC
 * @brief  Multiple Timer Counter Register           (@ 0X034)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULTC                            0
#define SGPIO_MASK_MULTC                             ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULMC
 * @brief  Multiple Match Control Register           (@ 0X038)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MUL_DMA_UNFLI_EN                 14
#define SGPIO_BIT_MUL_DMA_UNFLI_EN                   ((u32)0x00000001 << 14)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_DMA_START                    13
#define SGPIO_BIT_MUL_DMA_START                      ((u32)0x00000001 << 13)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_DMA_EN                       12
#define SGPIO_BIT_MUL_DMA_EN                         ((u32)0x00000001 << 12)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_FMODE_EN                     11
#define SGPIO_BIT_MUL_FMODE_EN                       ((u32)0x00000001 << 11)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MCNTSTOP_EN                  10
#define SGPIO_BIT_MUL_MCNTSTOP_EN                    ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MCNTRST_EN                   9
#define SGPIO_BIT_MUL_MCNTRST_EN                     ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MCNTI_EN                     8
#define SGPIO_BIT_MUL_MCNTI_EN                       ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MR0MCNT_EN                   7
#define SGPIO_BIT_MUL_MR0MCNT_EN                     ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MR0CAPSRC_EN                 6
#define SGPIO_BIT_MUL_MR0CAPSRC_EN                   ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MR0RXSTOP_EN                 5
#define SGPIO_BIT_MUL_MR0RXSTOP_EN                   ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MR0RXRST_EN                  4
#define SGPIO_BIT_MUL_MR0RXRST_EN                    ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MR0SCLK_EN                   3
#define SGPIO_BIT_MUL_MR0SCLK_EN                     ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MR0STOP_EN                   2
#define SGPIO_BIT_MUL_MR0STOP_EN                     ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MR0RST_EN                    1
#define SGPIO_BIT_MUL_MR0RST_EN                      ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MR0I_EN                      0
#define SGPIO_BIT_MUL_MR0I_EN                        ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULMR01GP0
 * @brief  Multiple Match Register 0 & 1 For Group 0 (@ 0X03C)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULMR1_GP0                       16
#define SGPIO_MASK_MULMR1_GP0                        ((u32)0x0000FFFF << 16)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MULMR0_GP0                       0
#define SGPIO_MASK_MULMR0_GP0                        ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULMR23GP0
 * @brief  Multiple Match Register 2 & 3 For Group 0 (@ 0X040)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULMR3_GP0                       16
#define SGPIO_MASK_MULMR3_GP0                        ((u32)0x0000FFFF << 16)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MULMR2_GP0                       0
#define SGPIO_MASK_MULMR2_GP0                        ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULMR01GP1
 * @brief  Multiple Match Register 0 & 1 For Group 1 (@ 0X044)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULMR1_GP1                       16
#define SGPIO_MASK_MULMR1_GP1                        ((u32)0x0000FFFF << 16)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MULMR0_GP1                       0
#define SGPIO_MASK_MULMR0_GP1                        ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULMR23GP1
 * @brief  Multiple Match Register 2 & 3 For Group 1 (@ 0X048)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULMR3_GP1                       16
#define SGPIO_MASK_MULMR3_GP1                        ((u32)0x0000FFFF << 16)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MULMR2_GP1                       0
#define SGPIO_MASK_MULMR2_GP1                        ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MUL_MCNT
 * @brief  Multiple Match Counter Register           (@ 0X04C)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MUL_MCNT                         0
#define SGPIO_MASK_MUL_MCNT                          ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULEMR
 * @brief  External Match Control Register           (@ 0X050)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXBIMC2                          25
#define SGPIO_MASK_RXBIMC2                           ((u32)0x00000003 << 25)                             /*!<R/W 0   */
#define SGPIO_SHIFT_RXBIMC1                          23
#define SGPIO_MASK_RXBIMC1                           ((u32)0x00000003 << 23)                             /*!<R/W 0   */
#define SGPIO_SHIFT_RXBIMC0                          21
#define SGPIO_MASK_RXBIMC0                           ((u32)0x00000003 << 21)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MULBIMC3                         19
#define SGPIO_MASK_MULBIMC3                          ((u32)0x00000003 << 19)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MULBIMC2                         17
#define SGPIO_MASK_MULBIMC2                          ((u32)0x00000003 << 17)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MULBIMC1                         15
#define SGPIO_MASK_MULBIMC1                          ((u32)0x00000003 << 15)                             /*!<R/W 0   */
#define SGPIO_SHIFT_BIOUT_MODE                       13
#define SGPIO_MASK_BIOUT_MODE                        ((u32)0x00000003 << 13)                             /*!<R/W 0   */
#define SGPIO_SHIFT_BIOUT_EN                         12
#define SGPIO_BIT_BIOUT_EN                           ((u32)0x00000001 << 12)                             /*!<R/W 0   */
#define SGPIO_SHIFT_RXEMC2                           10
#define SGPIO_MASK_RXEMC2                            ((u32)0x00000003 << 10)                             /*!<R/W 0   */
#define SGPIO_SHIFT_RXEMC1                           8
#define SGPIO_MASK_RXEMC1                            ((u32)0x00000003 << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXEMC0                           6
#define SGPIO_MASK_RXEMC0                            ((u32)0x00000003 << 6)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULEMC3                          4
#define SGPIO_MASK_MULEMC3                           ((u32)0x00000003 << 4)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULEMC2                          2
#define SGPIO_MASK_MULEMC2                           ((u32)0x00000003 << 2)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULEMC1                          0
#define SGPIO_MASK_MULEMC1                           ((u32)0x00000003 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_DATA_CTRL
 * @brief  Data Control Register                     (@ 0X054)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_TXDATA_DIR                       8
#define SGPIO_BIT_TXDATA_DIR                         ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXDATA_DIR                       7
#define SGPIO_BIT_RXDATA_DIR                         ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SGPIO_SHIFT_PATTERN_MATCH_IE                 6
#define SGPIO_BIT_PATTERN_MATCH_IE                   ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SGPIO_SHIFT_PATTERN_MATCH_MODE               5
#define SGPIO_BIT_PATTERN_MATCH_MODE                 ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXDATASRC_SEL                    4
#define SGPIO_BIT_RXDATASRC_SEL                      ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULLOAD_IE                       3
#define SGPIO_BIT_MULLOAD_IE                         ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXLOAD_IE                        2
#define SGPIO_BIT_RXLOAD_IE                          ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULSFT_IE                        1
#define SGPIO_BIT_MULSFT_IE                          ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXSFT_IE                         0
#define SGPIO_BIT_RXSFT_IE                           ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXDATA
 * @brief  RX Data Register                          (@ 0X058)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXDATA                           0
#define SGPIO_MASK_RXDATA                            ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXDATA_DP
 * @brief  RX Data Duplicate Register                (@ 0X05C)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXDATA_DP                        0
#define SGPIO_MASK_RXDATA_DP                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXPOSR
 * @brief  RX Position Register                      (@ 0X060)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXPOSRST                         8
#define SGPIO_MASK_RXPOSRST                          ((u32)0x0000001F << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXPOSTC                          0
#define SGPIO_MASK_RXPOSTC                           ((u32)0x0000001F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_RXDATAMASK
 * @brief  RX Data Mask Register                     (@ 0X064)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_RXDATAMASK                       0
#define SGPIO_MASK_RXDATAMASK                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULDATA
 * @brief  Multiple Data Register                    (@ 0X068)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULDATA                          0
#define SGPIO_MASK_MULDATA                           ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULDATA_DP
 * @brief  Multiple Data Duplicate Register          (@ 0X06C)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULDATA_DP                       0
#define SGPIO_MASK_MULDATA_DP                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULPOSR
 * @brief  Multiple Position Register                (@ 0X070)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULPOSRST                        8
#define SGPIO_MASK_MULPOSRST                         ((u32)0x0000001F << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULPOSTC                         0
#define SGPIO_MASK_MULPOSTC                          ((u32)0x0000001F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_MULFDATA
 * @brief  Multiple FIFO Data Register               (@ 0X074)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MULFDATA                         0
#define SGPIO_MASK_MULFDATA                          ((u32)0xFFFFFFFF << 0)                              /*!<W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_IS
 * @brief  SGPIO Interrupt Status Register           (@ 0X078)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MUL_DMA_UNFL_IS                  11
#define SGPIO_BIT_MUL_DMA_UNFL_IS                    ((u32)0x00000001 << 11)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MULMCNT_IS                       10
#define SGPIO_BIT_MULMCNT_IS                         ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define SGPIO_SHIFT_PATTERN_MATCH_IS                 9
#define SGPIO_BIT_PATTERN_MATCH_IS                   ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULLOAD_IS                       8
#define SGPIO_BIT_MULLOAD_IS                         ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXLOAD_IS                        7
#define SGPIO_BIT_RXLOAD_IS                          ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULSFT_IS                        6
#define SGPIO_BIT_MULSFT_IS                          ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXSFT_IS                         5
#define SGPIO_BIT_RXSFT_IS                           ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SGPIO_SHIFT_CAPI_IS                          4
#define SGPIO_BIT_CAPI_IS                            ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MR0I_IS                      3
#define SGPIO_BIT_MUL_MR0I_IS                        ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR2I_IS                       2
#define SGPIO_BIT_RX_MR2I_IS                         ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR1I_IS                       1
#define SGPIO_BIT_RX_MR1I_IS                         ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR0I_IS                       0
#define SGPIO_BIT_RX_MR0I_IS                         ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_GF
 * @brief  SGPIO Glitch Filter Register              (@ 0X07C)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_GF                               0
#define SGPIO_MASK_GF                                ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_OUTPUT
 * @brief  SGPIO Output Register                     (@ 0X080)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_OUTPUT                           0
#define SGPIO_BIT_OUTPUT                             ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SGPIO_IM
 * @brief  SGPIO Interrupt Mask Register             (@ 0X084)
 * @{
 *****************************************************************************/
#define SGPIO_SHIFT_MUL_DMA_UNFL_IM                  11
#define SGPIO_BIT_MUL_DMA_UNFL_IM                    ((u32)0x00000001 << 11)                             /*!<R/W 0   */
#define SGPIO_SHIFT_MULMCNT_IM                       10
#define SGPIO_BIT_MULMCNT_IM                         ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define SGPIO_SHIFT_PATTERN_MATCH_IM                 9
#define SGPIO_BIT_PATTERN_MATCH_IM                   ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULLOAD_IM                       8
#define SGPIO_BIT_MULLOAD_IM                         ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXLOAD_IM                        7
#define SGPIO_BIT_RXLOAD_IM                          ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MULSFT_IM                        6
#define SGPIO_BIT_MULSFT_IM                          ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RXSFT_IM                         5
#define SGPIO_BIT_RXSFT_IM                           ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define SGPIO_SHIFT_CAPI_IM                          4
#define SGPIO_BIT_CAPI_IM                            ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define SGPIO_SHIFT_MUL_MR0I_IM                      3
#define SGPIO_BIT_MUL_MR0I_IM                        ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR2I_IM                       2
#define SGPIO_BIT_RX_MR2I_IM                         ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR1I_IM                       1
#define SGPIO_BIT_RX_MR1I_IM                         ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SGPIO_SHIFT_RX_MR0I_IM                       0
#define SGPIO_BIT_RX_MR0I_IM                         ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_SGPIO
 * @{
 * @brief rtl8735b_SGPIO Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t SGPIO_RXTMR_CTRL ;                       /*!<  RX Timer Control Register register,  Address offset: 0x000 */
	__IO uint32_t SGPIO_RXPRVAL ;                          /*!<  RX Maximum Prescale Register register,  Address offset: 0x004 */
	__IO uint32_t SGPIO_RXPRTC ;                           /*!<  RX Timer Prescale Register register,  Address offset: 0x008 */
	__IO uint32_t SGPIO_RXTC ;                             /*!<  RX Timer Counter Register register,  Address offset: 0x00C */
	__IO uint32_t SGPIO_RXMC ;                             /*!<  Position Counter Register register,  Address offset: 0x010 */
	__IO uint32_t SGPIO_RXMR0 ;                            /*!<  RX Match Register 0 register,  Address offset: 0x014 */
	__IO uint32_t SGPIO_RXMR1 ;                            /*!<  RX Match Register 1 register,  Address offset: 0x018 */
	__IO uint32_t SGPIO_RXMR2 ;                            /*!<  RX Match Register 2 register,  Address offset: 0x01C */
	__IO uint32_t SGPIO_CAP_CTRL ;                         /*!<  Capture Control Register register,  Address offset: 0x020 */
	__IO uint32_t SGPIO_CAPR ;                             /*!<  Capture Register register,  Address offset: 0x024 */
	__IO uint32_t SGPIO_MULTMR_CTRL ;                      /*!<  Multiple Timer Control Register register,  Address offset: 0x028 */
	__IO uint32_t SGPIO_MULPRVAL ;                         /*!<  Multiple Maximum Prescale Register register,  Address offset: 0x02C */
	__IO uint32_t SGPIO_MULPRTC ;                          /*!<  Multiple Timer Prescale Register register,  Address offset: 0x030 */
	__IO uint32_t SGPIO_MULTC ;                            /*!<  Multiple Timer Counter Register register,  Address offset: 0x034 */
	__IO uint32_t SGPIO_MULMC ;                            /*!<  Multiple Match Control Register register,  Address offset: 0x038 */
	__IO uint32_t SGPIO_MULMR01GP0 ;                       /*!<  Multiple Match Register 0 & 1 For Group 0 register,  Address offset: 0x03C */
	__IO uint32_t SGPIO_MULMR23GP0 ;                       /*!<  Multiple Match Register 2 & 3 For Group 0 register,  Address offset: 0x040 */
	__IO uint32_t SGPIO_MULMR01GP1 ;                       /*!<  Multiple Match Register 0 & 1 For Group 1 register,  Address offset: 0x044 */
	__IO uint32_t SGPIO_MULMR23GP1 ;                       /*!<  Multiple Match Register 2 & 3 For Group 1 register,  Address offset: 0x048 */
	__IO uint32_t SGPIO_MUL_MCNT ;                         /*!<  Multiple Match Counter Register register,  Address offset: 0x04C */
	__IO uint32_t SGPIO_MULEMR ;                           /*!<  External Match Control Register register,  Address offset: 0x050 */
	__IO uint32_t SGPIO_DATA_CTRL ;                        /*!<  Data Control Register register,  Address offset: 0x054 */
	__IO uint32_t SGPIO_RXDATA ;                           /*!<  RX Data Register register,  Address offset: 0x058 */
	__IO uint32_t SGPIO_RXDATA_DP ;                        /*!<  RX Data Duplicate Register register,  Address offset: 0x05C */
	__IO uint32_t SGPIO_RXPOSR ;                           /*!<  RX Position Register register,  Address offset: 0x060 */
	__IO uint32_t SGPIO_RXDATAMASK ;                       /*!<  RX Data Mask Register register,  Address offset: 0x064 */
	__IO uint32_t SGPIO_MULDATA ;                          /*!<  Multiple Data Register register,  Address offset: 0x068 */
	__IO uint32_t SGPIO_MULDATA_DP ;                       /*!<  Multiple Data Duplicate Register register,  Address offset: 0x06C */
	__IO uint32_t SGPIO_MULPOSR ;                          /*!<  Multiple Position Register register,  Address offset: 0x070 */
	__O  uint32_t SGPIO_MULFDATA ;                         /*!<  Multiple FIFO Data Register register,  Address offset: 0x074 */
	__IO uint32_t SGPIO_IS ;                               /*!<  SGPIO Interrupt Status Register register,  Address offset: 0x078 */
	__IO uint32_t SGPIO_GF ;                               /*!<  SGPIO Glitch Filter Register register,  Address offset: 0x07C */
	__IO uint32_t SGPIO_OUTPUT ;                           /*!<  SGPIO Output Register register,  Address offset: 0x080 */
	__IO uint32_t SGPIO_IM ;                               /*!<  SGPIO Interrupt Mask Register register,         Address offset: 0x084 */
} SGPIO_TypeDef;
/** @} */

#endif
