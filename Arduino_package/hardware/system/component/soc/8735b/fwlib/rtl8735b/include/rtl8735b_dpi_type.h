#ifndef _RTL8735B_DPI_TYPE_H_
#define _RTL8735B_DPI_TYPE_H_

/**************************************************************************//**
 * @defgroup DPI_CRT_CTL
 * @brief  CRT_CTL                                   (@ 0X000)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_MCK_CKE_SEL                        30
#define DPI_BIT_MCK_CKE_SEL                          ((u32)0x00000001 << 30)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CLK_TEN_VALUE                      29
#define DPI_BIT_CLK_TEN_VALUE                        ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CLK_TEN_MODE                       28
#define DPI_BIT_CLK_TEN_MODE                         ((u32)0x00000001 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_FORCE_RSTN                         27
#define DPI_BIT_FORCE_RSTN                           ((u32)0x00000001 << 27)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_RSTN_VALUE                         26
#define DPI_BIT_RSTN_VALUE                           ((u32)0x00000001 << 26)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_FIFO_RST_INI_TX                    23
#define DPI_MASK_FIFO_RST_INI_TX                     ((u32)0x00000007 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_FIFO_RST_INI_RX                    20
#define DPI_MASK_FIFO_RST_INI_RX                     ((u32)0x00000007 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CA_DDR3_MODE                       19
#define DPI_BIT_CA_DDR3_MODE                         ((u32)0x00000001 << 19)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_FORCE_CKE_1                        18
#define DPI_BIT_FORCE_CKE_1                          ((u32)0x00000001 << 18)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_CKE_1_VALUE                        17
#define DPI_BIT_CKE_1_VALUE                          ((u32)0x00000001 << 17)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_FORCE_CS                           16
#define DPI_BIT_FORCE_CS                             ((u32)0x00000001 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_VALUE                           15
#define DPI_BIT_CS_VALUE                             ((u32)0x00000001 << 15)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_FORCE_CS_1                         14
#define DPI_BIT_FORCE_CS_1                           ((u32)0x00000001 << 14)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_1_VALUE                         13
#define DPI_BIT_CS_1_VALUE                           ((u32)0x00000001 << 13)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_PAD_DDR2_MODE                      12
#define DPI_BIT_PAD_DDR2_MODE                        ((u32)0x00000001 << 12)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_FORCE_CKE                          11
#define DPI_BIT_FORCE_CKE                            ((u32)0x00000001 << 11)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_CKE_VALUE                          10
#define DPI_BIT_CKE_VALUE                            ((u32)0x00000001 << 10)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_PIN_MUX_LPDDR3_2CELL               9
#define DPI_BIT_PIN_MUX_LPDDR3_2CELL                 ((u32)0x00000001 << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_PIN_MUX_LPDDR3_1CELL               8
#define DPI_BIT_PIN_MUX_LPDDR3_1CELL                 ((u32)0x00000001 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_PIN_MUX_LPDDR2_2CELL               7
#define DPI_BIT_PIN_MUX_LPDDR2_2CELL                 ((u32)0x00000001 << 7)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_PIN_MUX_LPDDR2_1CELL               6
#define DPI_BIT_PIN_MUX_LPDDR2_1CELL                 ((u32)0x00000001 << 6)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_PIN_MUX_DDR3                       5
#define DPI_BIT_PIN_MUX_DDR3                         ((u32)0x00000001 << 5)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_PIN_MUX_MODE                       4
#define DPI_BIT_PIN_MUX_MODE                         ((u32)0x00000001 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_LPDDR_EN                           3
#define DPI_BIT_LPDDR_EN                             ((u32)0x00000001 << 3)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DAT_RATE_SEL                       2
#define DPI_BIT_DAT_RATE_SEL                         ((u32)0x00000001 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DDR2_EN                            1
#define DPI_BIT_DDR2_EN                              ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DDR3_MODE                          0
#define DPI_BIT_DDR3_MODE                            ((u32)0x00000001 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PLL_CTL0
 * @brief  PLL_CTL0                                  (@ 0X004)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_TMUX_DCG_EN                        28
#define DPI_BIT_TMUX_DCG_EN                          ((u32)0x00000001 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CA_AFIFO_DCG_EN                    23
#define DPI_BIT_CA_AFIFO_DCG_EN                      ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CA_AFIFO_DCG_CNT                   20
#define DPI_MASK_CA_AFIFO_DCG_CNT                    ((u32)0x00000007 << 20)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_MCK_CLK_EN                         0
#define DPI_MASK_MCK_CLK_EN                          ((u32)0x00001FFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PLL_CTL1
 * @brief  PLL_CTL1                                  (@ 0X008)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_MCK_MC_EN                          31
#define DPI_BIT_MCK_MC_EN                            ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_REG_FIX_DIV1                       30
#define DPI_BIT_REG_FIX_DIV1                         ((u32)0x00000001 << 30)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_REG_CRT_PWROFF_DIS                 29
#define DPI_BIT_REG_CRT_PWROFF_DIS                   ((u32)0x00000001 << 29)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_CLK_OE                             16
#define DPI_MASK_CLK_OE                              ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_OESYNC_OP_SEL_FIX                  13
#define DPI_BIT_OESYNC_OP_SEL_FIX                    ((u32)0x00000001 << 13)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_OESYNC_OP_SEL                      0
#define DPI_MASK_OESYNC_OP_SEL                       ((u32)0x00001FFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PLL_CTL2
 * @brief  PLL_CTL2                                  (@ 0X00C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_REG_CTS_FIFO_SYNC_CNT              29
#define DPI_MASK_REG_CTS_FIFO_SYNC_CNT               ((u32)0x00000007 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_PRBS_EN                            28
#define DPI_BIT_PRBS_EN                              ((u32)0x00000001 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_NC_SEL                             26
#define DPI_MASK_NC_SEL                              ((u32)0x00000003 << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_NC_CLK_DIV_SEL                     24
#define DPI_MASK_NC_CLK_DIV_SEL                      ((u32)0x00000003 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_NC_PRBS13_SEED                     11
#define DPI_MASK_NC_PRBS13_SEED                      ((u32)0x00001FFF << 11)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_NC_PRBS13_EN                       10
#define DPI_BIT_NC_PRBS13_EN                         ((u32)0x00000001 << 10)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_NC_PRBS13_INVS                     9
#define DPI_BIT_NC_PRBS13_INVS                       ((u32)0x00000001 << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_NC_PRBS13_MAX                      8
#define DPI_BIT_NC_PRBS13_MAX                        ((u32)0x00000001 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_PLL_DUM                            0
#define DPI_MASK_PLL_DUM                             ((u32)0x000000FF << 0)                              /*!<R/W 0xF  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PLL_PI0
 * @brief  PLL_PI0                                   (@ 0X010)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_POST_PI_SEL3                       24
#define DPI_MASK_POST_PI_SEL3                        ((u32)0x0000001F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_SEL2                       16
#define DPI_MASK_POST_PI_SEL2                        ((u32)0x0000001F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_SEL1                       8
#define DPI_MASK_POST_PI_SEL1                        ((u32)0x0000001F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_SEL0                       0
#define DPI_MASK_POST_PI_SEL0                        ((u32)0x0000001F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PLL_PI1
 * @brief  PLL_PI1                                   (@ 0X014)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_POST_PI_SEL                        24
#define DPI_MASK_POST_PI_SEL                         ((u32)0x0000001F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_SEL6                       16
#define DPI_MASK_POST_PI_SEL6                        ((u32)0x0000001F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_SEL5                       8
#define DPI_MASK_POST_PI_SEL5                        ((u32)0x0000001F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_SEL4                       0
#define DPI_MASK_POST_PI_SEL4                        ((u32)0x0000001F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PLL_CTL3
 * @brief  PLL_CTL3                                  (@ 0X018)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_V11_LDO_VSEL                       29
#define DPI_MASK_V11_LDO_VSEL                        ((u32)0x00000007 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKREF_SEL                          28
#define DPI_BIT_CKREF_SEL                            ((u32)0x00000001 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_RS                         27
#define DPI_BIT_POST_PI_RS                           ((u32)0x00000001 << 27)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_RL                         25
#define DPI_MASK_POST_PI_RL                          ((u32)0x00000003 << 25)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_PI_BIAS                       23
#define DPI_MASK_POST_PI_BIAS                        ((u32)0x00000003 << 23)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PLL_SEL_CPMODE                     22
#define DPI_BIT_PLL_SEL_CPMODE                       ((u32)0x00000001 << 22)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_PLL_LDO_VSEL                       19
#define DPI_MASK_PLL_LDO_VSEL                        ((u32)0x00000007 << 19)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PLL_DBUG_EN                        18
#define DPI_BIT_PLL_DBUG_EN                          ((u32)0x00000001 << 18)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_PDIV                               16
#define DPI_MASK_PDIV                                ((u32)0x00000003 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_LPF_SR                             13
#define DPI_MASK_LPF_SR                              ((u32)0x00000007 << 13)                             /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_LPF_CP                             12
#define DPI_BIT_LPF_CP                               ((u32)0x00000001 << 12)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_LOOP_PI_ISEL                       8
#define DPI_MASK_LOOP_PI_ISEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0x6  RSVD */
#define DPI_SHIFT_ICP                                4
#define DPI_MASK_ICP                                 ((u32)0x0000000F << 4)                              /*!<R/W 0xC  RSVD */
#define DPI_SHIFT_CCO_KVCO                           2
#define DPI_BIT_CCO_KVCO                             ((u32)0x00000001 << 2)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_CCO_BAND                           0
#define DPI_MASK_CCO_BAND                            ((u32)0x00000003 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_SSC0
 * @brief  SSC0                                      (@ 0X01C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_OC_DONE_DELAY                      8
#define DPI_MASK_OC_DONE_DELAY                       ((u32)0x0000003F << 8)                              /*!<R/W 0x3F  RSVD */
#define DPI_SHIFT_HS_OC_STOP_DIFF                    6
#define DPI_MASK_HS_OC_STOP_DIFF                     ((u32)0x00000003 << 6)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_SEL_OC_MODE                        4
#define DPI_MASK_SEL_OC_MODE                         ((u32)0x00000003 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_SSC_FLAG_INIT                      3
#define DPI_BIT_SSC_FLAG_INIT                        ((u32)0x00000001 << 3)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ORDER                              2
#define DPI_BIT_ORDER                                ((u32)0x00000001 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_EN_SSC                             1
#define DPI_BIT_EN_SSC                               ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_BYPASS_PI                          0
#define DPI_BIT_BYPASS_PI                            ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_SSC1
 * @brief  SSC1                                      (@ 0X020)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_GRAN_AUTO_RST                      23
#define DPI_BIT_GRAN_AUTO_RST                        ((u32)0x00000001 << 23)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DOT_GRAN                           20
#define DPI_MASK_DOT_GRAN                            ((u32)0x00000007 << 20)                             /*!<R/W 0x4  RSVD */
#define DPI_SHIFT_GRAN_SET                           0
#define DPI_MASK_GRAN_SET                            ((u32)0x0007FFFF << 0)                              /*!<R/W 0x21FB  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_SSC2
 * @brief  SSC2                                      (@ 0X024)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_F_CODE_T                           16
#define DPI_MASK_F_CODE_T                            ((u32)0x000007FF << 16)                             /*!<R/W 0x50A  RSVD */
#define DPI_SHIFT_F_CODE                             0
#define DPI_MASK_F_CODE                              ((u32)0x000007FF << 0)                              /*!<R/W 0x5ED  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_SSC3
 * @brief  SSC3                                      (@ 0X028)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_OC_EN                              26
#define DPI_BIT_OC_EN                                ((u32)0x00000001 << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_OC_STEP_SET                        16
#define DPI_MASK_OC_STEP_SET                         ((u32)0x000003FF << 16)                             /*!<R/W 0x28  RSVD */
#define DPI_SHIFT_N_CODE_T                           8
#define DPI_MASK_N_CODE_T                            ((u32)0x000000FF << 8)                              /*!<R/W 0x1A  RSVD */
#define DPI_SHIFT_N_CODE                             0
#define DPI_MASK_N_CODE                              ((u32)0x000000FF << 0)                              /*!<R/W 0x19  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_WDOG
 * @brief  WDOG                                      (@ 0X02C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_TIME2_RST_WIDTH                    12
#define DPI_MASK_TIME2_RST_WIDTH                     ((u32)0x00000003 << 12)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_TIME_RDY_CKOUT                     8
#define DPI_MASK_TIME_RDY_CKOUT                      ((u32)0x00000003 << 8)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_TIME0_CK                           4
#define DPI_MASK_TIME0_CK                            ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_F390K                              1
#define DPI_MASK_F390K                               ((u32)0x00000003 << 1)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_WD_ENABLE                          0
#define DPI_BIT_WD_ENABLE                            ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_CMD
 * @brief  DCC_CMD                                   (@ 0X030)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_CMD_DSP_DBG_SEL                31
#define DPI_BIT_DCC_CMD_DSP_DBG_SEL                  ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_CMD_DUTY_SEL                   29
#define DPI_BIT_DCC_CMD_DUTY_SEL                     ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_CMD_DSP_STOP                   28
#define DPI_BIT_DCC_CMD_DSP_STOP                     ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_CMD_DIV                        24
#define DPI_MASK_DCC_CMD_DIV                         ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_CMD_INT_GAIN                   16
#define DPI_MASK_DCC_CMD_INT_GAIN                    ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_CMD_DUTY                       8
#define DPI_MASK_DCC_CMD_DUTY                        ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_CMD_DUTY_PRESETB               4
#define DPI_MASK_DCC_CMD_DUTY_PRESETB                ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_CMD_DUTY_PRESETA               0
#define DPI_MASK_DCC_CMD_DUTY_PRESETA                ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_DQS_0
 * @brief  DCC_DQS_0                                 (@ 0X034)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_DQS_DUTY_SEL                   29
#define DPI_BIT_DCC_DQS_DUTY_SEL                     ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_DQS_DSP_STOP                   28
#define DPI_BIT_DCC_DQS_DSP_STOP                     ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_DQS_DIV                        24
#define DPI_MASK_DCC_DQS_DIV                         ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQS_INT_GAIN                   16
#define DPI_MASK_DCC_DQS_INT_GAIN                    ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY                       8
#define DPI_MASK_DCC_DQS_DUTY                        ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY_PRESETB               4
#define DPI_MASK_DCC_DQS_DUTY_PRESETB                ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY_PRESETA               0
#define DPI_MASK_DCC_DQS_DUTY_PRESETA                ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_DQS_1
 * @brief  DCC_DQS_1                                 (@ 0X038)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_DQS_DUTY_SEL                   29
#define DPI_BIT_DCC_DQS_DUTY_SEL                     ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_DQS_DSP_STOP                   28
#define DPI_BIT_DCC_DQS_DSP_STOP                     ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_DQS_DIV                        24
#define DPI_MASK_DCC_DQS_DIV                         ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQS_INT_GAIN                   16
#define DPI_MASK_DCC_DQS_INT_GAIN                    ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY                       8
#define DPI_MASK_DCC_DQS_DUTY                        ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY_PRESETB               4
#define DPI_MASK_DCC_DQS_DUTY_PRESETB                ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY_PRESETA               0
#define DPI_MASK_DCC_DQS_DUTY_PRESETA                ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_DQS_2
 * @brief  DCC_DQS_2                                 (@ 0X03C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_DQS_DUTY_SEL                   29
#define DPI_BIT_DCC_DQS_DUTY_SEL                     ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_DQS_DSP_STOP                   28
#define DPI_BIT_DCC_DQS_DSP_STOP                     ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_DQS_DIV                        24
#define DPI_MASK_DCC_DQS_DIV                         ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQS_INT_GAIN                   16
#define DPI_MASK_DCC_DQS_INT_GAIN                    ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY                       8
#define DPI_MASK_DCC_DQS_DUTY                        ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY_PRESETB               4
#define DPI_MASK_DCC_DQS_DUTY_PRESETB                ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY_PRESETA               0
#define DPI_MASK_DCC_DQS_DUTY_PRESETA                ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_DQS_3
 * @brief  DCC_DQS_3                                 (@ 0X040)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_DQS_DUTY_SEL                   29
#define DPI_BIT_DCC_DQS_DUTY_SEL                     ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_DQS_DSP_STOP                   28
#define DPI_BIT_DCC_DQS_DSP_STOP                     ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_DQS_DIV                        24
#define DPI_MASK_DCC_DQS_DIV                         ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQS_INT_GAIN                   16
#define DPI_MASK_DCC_DQS_INT_GAIN                    ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY                       8
#define DPI_MASK_DCC_DQS_DUTY                        ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY_PRESETB               4
#define DPI_MASK_DCC_DQS_DUTY_PRESETB                ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_DQS_DUTY_PRESETA               0
#define DPI_MASK_DCC_DQS_DUTY_PRESETA                ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_DQ_0
 * @brief  DCC_DQ_0                                  (@ 0X044)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_DQ_DUTY_SEL                    29
#define DPI_BIT_DCC_DQ_DUTY_SEL                      ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_DQ_DSP_STOP                    28
#define DPI_BIT_DCC_DQ_DSP_STOP                      ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_DQ_DIV                         24
#define DPI_MASK_DCC_DQ_DIV                          ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQ_INT_GAIN                    16
#define DPI_MASK_DCC_DQ_INT_GAIN                     ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY                        8
#define DPI_MASK_DCC_DQ_DUTY                         ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY_PRESETB                4
#define DPI_MASK_DCC_DQ_DUTY_PRESETB                 ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY_PRESETA                0
#define DPI_MASK_DCC_DQ_DUTY_PRESETA                 ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_DQ_1
 * @brief  DCC_DQ_1                                  (@ 0X048)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_DQ_DUTY_SEL                    29
#define DPI_BIT_DCC_DQ_DUTY_SEL                      ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_DQ_DSP_STOP                    28
#define DPI_BIT_DCC_DQ_DSP_STOP                      ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_DQ_DIV                         24
#define DPI_MASK_DCC_DQ_DIV                          ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQ_INT_GAIN                    16
#define DPI_MASK_DCC_DQ_INT_GAIN                     ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY                        8
#define DPI_MASK_DCC_DQ_DUTY                         ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY_PRESETB                4
#define DPI_MASK_DCC_DQ_DUTY_PRESETB                 ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY_PRESETA                0
#define DPI_MASK_DCC_DQ_DUTY_PRESETA                 ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_DQ_2
 * @brief  DCC_DQ_2                                  (@ 0X04C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_DQ_DUTY_SEL                    29
#define DPI_BIT_DCC_DQ_DUTY_SEL                      ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_DQ_DSP_STOP                    28
#define DPI_BIT_DCC_DQ_DSP_STOP                      ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_DQ_DIV                         24
#define DPI_MASK_DCC_DQ_DIV                          ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQ_INT_GAIN                    16
#define DPI_MASK_DCC_DQ_INT_GAIN                     ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY                        8
#define DPI_MASK_DCC_DQ_DUTY                         ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY_PRESETB                4
#define DPI_MASK_DCC_DQ_DUTY_PRESETB                 ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY_PRESETA                0
#define DPI_MASK_DCC_DQ_DUTY_PRESETA                 ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_DQ_3
 * @brief  DCC_DQ_3                                  (@ 0X050)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_DQ_DUTY_SEL                    29
#define DPI_BIT_DCC_DQ_DUTY_SEL                      ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_DQ_DSP_STOP                    28
#define DPI_BIT_DCC_DQ_DSP_STOP                      ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_DQ_DIV                         24
#define DPI_MASK_DCC_DQ_DIV                          ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQ_INT_GAIN                    16
#define DPI_MASK_DCC_DQ_INT_GAIN                     ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY                        8
#define DPI_MASK_DCC_DQ_DUTY                         ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY_PRESETB                4
#define DPI_MASK_DCC_DQ_DUTY_PRESETB                 ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_DQ_DUTY_PRESETA                0
#define DPI_MASK_DCC_DQ_DUTY_PRESETA                 ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_CK_0
 * @brief  DCC_CK_0                                  (@ 0X054)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_CK_DUTY_SEL                    29
#define DPI_BIT_DCC_CK_DUTY_SEL                      ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_CK_DSP_STOP                    28
#define DPI_BIT_DCC_CK_DSP_STOP                      ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_CK_DIV                         24
#define DPI_MASK_DCC_CK_DIV                          ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_CK_INT_GAIN                    16
#define DPI_MASK_DCC_CK_INT_GAIN                     ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_CK_DUTY                        8
#define DPI_MASK_DCC_CK_DUTY                         ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_CK_DUTY_PRESETB                4
#define DPI_MASK_DCC_CK_DUTY_PRESETB                 ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_CK_DUTY_PRESETA                0
#define DPI_MASK_DCC_CK_DUTY_PRESETA                 ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_CK_1
 * @brief  DCC_CK_1                                  (@ 0X058)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_CK_DUTY_SEL                    29
#define DPI_BIT_DCC_CK_DUTY_SEL                      ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_CK_DSP_STOP                    28
#define DPI_BIT_DCC_CK_DSP_STOP                      ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_CK_DIV                         24
#define DPI_MASK_DCC_CK_DIV                          ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_CK_INT_GAIN                    16
#define DPI_MASK_DCC_CK_INT_GAIN                     ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_CK_DUTY                        8
#define DPI_MASK_DCC_CK_DUTY                         ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_CK_DUTY_PRESETB                4
#define DPI_MASK_DCC_CK_DUTY_PRESETB                 ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_CK_DUTY_PRESETA                0
#define DPI_MASK_DCC_CK_DUTY_PRESETA                 ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CRT_CTL_2
 * @brief  CRT_CTL_2                                 (@ 0X060)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_MCK_TEST_CLK_SEL                   28
#define DPI_MASK_MCK_TEST_CLK_SEL                    ((u32)0x0000000F << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ALERT_CHK_EN                       3
#define DPI_BIT_ALERT_CHK_EN                         ((u32)0x00000001 << 3)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TOPREG_CLK_DIS                     1
#define DPI_BIT_TOPREG_CLK_DIS                       ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_RWREG_CLK_DIS                      0
#define DPI_BIT_RWREG_CLK_DIS                        ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_AFIFO_STR_0
 * @brief  AFIFO_STR_0                               (@ 0X080)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_RD_STR_NUM_3                   28
#define DPI_MASK_DQS_RD_STR_NUM_3                    ((u32)0x00000007 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DQ_RD_STR_NUM_3                    24
#define DPI_MASK_DQ_RD_STR_NUM_3                     ((u32)0x00000007 << 24)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DQS_RD_STR_NUM_2                   20
#define DPI_MASK_DQS_RD_STR_NUM_2                    ((u32)0x00000007 << 20)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DQ_RD_STR_NUM_2                    16
#define DPI_MASK_DQ_RD_STR_NUM_2                     ((u32)0x00000007 << 16)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DQS_RD_STR_NUM_1                   12
#define DPI_MASK_DQS_RD_STR_NUM_1                    ((u32)0x00000007 << 12)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DQ_RD_STR_NUM_1                    8
#define DPI_MASK_DQ_RD_STR_NUM_1                     ((u32)0x00000007 << 8)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_DQS_RD_STR_NUM_0                   4
#define DPI_MASK_DQS_RD_STR_NUM_0                    ((u32)0x00000007 << 4)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_DQ_RD_STR_NUM_0                    0
#define DPI_MASK_DQ_RD_STR_NUM_0                     ((u32)0x00000007 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_AFIFO_STR_1
 * @brief  AFIFO_STR_1                               (@ 0X084)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_BYPASS_EN_RX                       21
#define DPI_BIT_BYPASS_EN_RX                         ((u32)0x00000001 << 21)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_BYPASS_EN_TX                       20
#define DPI_BIT_BYPASS_EN_TX                         ((u32)0x00000001 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_FORCE_RST_N_RX                     19
#define DPI_BIT_FORCE_RST_N_RX                       ((u32)0x00000001 << 19)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_FORCE_RST_N_TX                     18
#define DPI_BIT_FORCE_RST_N_TX                       ((u32)0x00000001 << 18)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_REF_RST_EN_RX                      17
#define DPI_BIT_REF_RST_EN_RX                        ((u32)0x00000001 << 17)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_REF_RST_EN_TX                      16
#define DPI_BIT_REF_RST_EN_TX                        ((u32)0x00000001 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CMD_RD_STR_NUM_SEL_H               8
#define DPI_MASK_CMD_RD_STR_NUM_SEL_H                ((u32)0x000000FF << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CMD_EX_RD_STR_NUM                  4
#define DPI_MASK_CMD_EX_RD_STR_NUM                   ((u32)0x00000007 << 4)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_CMD_RD_STR_NUM                     0
#define DPI_MASK_CMD_RD_STR_NUM                      ((u32)0x00000007 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_AFIFO_STR_2
 * @brief  AFIFO_STR_2                               (@ 0X088)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RX_RD_STR_NUM_3                    12
#define DPI_MASK_RX_RD_STR_NUM_3                     ((u32)0x00000007 << 12)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_RX_RD_STR_NUM_2                    8
#define DPI_MASK_RX_RD_STR_NUM_2                     ((u32)0x00000007 << 8)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_RX_RD_STR_NUM_1                    4
#define DPI_MASK_RX_RD_STR_NUM_1                     ((u32)0x00000007 << 4)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_RX_RD_STR_NUM_0                    0
#define DPI_MASK_RX_RD_STR_NUM_0                     ((u32)0x00000007 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CRT_RST_CTL
 * @brief  CRT_RST_CTL                               (@ 0X08C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_PLL_BG_LPF                         11
#define DPI_BIT_PLL_BG_LPF                           ((u32)0x00000001 << 11)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_PLL_BG                             9
#define DPI_MASK_PLL_BG                              ((u32)0x00000003 << 9)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_PLL_BG_RST_N                       8
#define DPI_BIT_PLL_BG_RST_N                         ((u32)0x00000001 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_POW_LDO_V11                        5
#define DPI_BIT_POW_LDO_V11                          ((u32)0x00000001 << 5)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_POW_LDO_PLL                        4
#define DPI_BIT_POW_LDO_PLL                          ((u32)0x00000001 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_PTR_RST_N                          3
#define DPI_BIT_PTR_RST_N                            ((u32)0x00000001 << 3)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_RST_N                              2
#define DPI_BIT_RST_N                                ((u32)0x00000001 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_PLL_SSC_DIG_RST_N                  1
#define DPI_BIT_PLL_SSC_DIG_RST_N                    ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_PLL_LDO_RST_N                      0
#define DPI_BIT_PLL_LDO_RST_N                        ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_AFIFO_STR_SEL
 * @brief  AFIFO_STR_SEL                             (@ 0X094)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CMD_RD_STR_NUM_SEL                 0
#define DPI_MASK_CMD_RD_STR_NUM_SEL                  ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PLL_PI2
 * @brief  PLL_PI2                                   (@ 0X098)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_POST_PI_SEL10                      24
#define DPI_MASK_POST_PI_SEL10                       ((u32)0x0000001F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_SEL9                       16
#define DPI_MASK_POST_PI_SEL9                        ((u32)0x0000001F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_SEL8                       8
#define DPI_MASK_POST_PI_SEL8                        ((u32)0x0000001F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_SEL7                       0
#define DPI_MASK_POST_PI_SEL7                        ((u32)0x0000001F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PLL_CTL4
 * @brief  PLL_CTL4                                  (@ 0X09C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CLK_PI_CTRL                        31
#define DPI_BIT_CLK_PI_CTRL                          ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DLY_SEL                            24
#define DPI_MASK_DLY_SEL                             ((u32)0x0000001F << 24)                             /*!<R/W 0x10  RSVD */
#define DPI_SHIFT_DLY_SEL_CK1                        16
#define DPI_MASK_DLY_SEL_CK1                         ((u32)0x0000001F << 16)                             /*!<R/W 0x10  RSVD */
#define DPI_SHIFT_EN_POST_PI                         0
#define DPI_MASK_EN_POST_PI                          ((u32)0x00003FFF << 0)                              /*!<R/W 0x3FFF  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PLL_PI3
 * @brief  PLL_PI3                                   (@ 0X0A0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_POST_PI_SEL12                      8
#define DPI_MASK_POST_PI_SEL12                       ((u32)0x0000001F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_POST_PI_SEL11                      0
#define DPI_MASK_POST_PI_SEL11                       ((u32)0x0000001F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_CS
 * @brief  DCC_CS                                    (@ 0X0A4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_CS_DSP_DBG_SEL                 31
#define DPI_BIT_DCC_CS_DSP_DBG_SEL                   ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_CS_DUTY_SEL                    29
#define DPI_BIT_DCC_CS_DUTY_SEL                      ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_CS_DSP_STOP                    28
#define DPI_BIT_DCC_CS_DSP_STOP                      ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_CS_DIV                         24
#define DPI_MASK_DCC_CS_DIV                          ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_CS_INT_GAIN                    16
#define DPI_MASK_DCC_CS_INT_GAIN                     ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_CS_DUTY                        8
#define DPI_MASK_DCC_CS_DUTY                         ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_CS_DUTY_PRESETB                4
#define DPI_MASK_DCC_CS_DUTY_PRESETB                 ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_CS_DUTY_PRESETA                0
#define DPI_MASK_DCC_CS_DUTY_PRESETA                 ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DCC_CS1
 * @brief  DCC_CS1                                   (@ 0X0A8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_CS_1_DSP_DBG_SEL               31
#define DPI_BIT_DCC_CS_1_DSP_DBG_SEL                 ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_CS_1_DUTY_SEL                  29
#define DPI_BIT_DCC_CS_1_DUTY_SEL                    ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DCC_CS_1_DSP_STOP                  28
#define DPI_BIT_DCC_CS_1_DSP_STOP                    ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCC_CS_1_DIV                       24
#define DPI_MASK_DCC_CS_1_DIV                        ((u32)0x00000007 << 24)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_CS_1_INT_GAIN                  16
#define DPI_MASK_DCC_CS_1_INT_GAIN                   ((u32)0x0000001F << 16)                             /*!<R/W 0x5  RSVD */
#define DPI_SHIFT_DCC_CS_1_DUTY                      8
#define DPI_MASK_DCC_CS_1_DUTY                       ((u32)0x0000007F << 8)                              /*!<R/W 0x38  RSVD */
#define DPI_SHIFT_DCC_CS_1_DUTY_PRESETB              4
#define DPI_MASK_DCC_CS_1_DUTY_PRESETB               ((u32)0x00000007 << 4)                              /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DCC_CS_1_DUTY_PRESETA              0
#define DPI_MASK_DCC_CS_1_DUTY_PRESETA               ((u32)0x00000007 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PLL_CTL5
 * @brief  PLL_CTL5                                  (@ 0X0AC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_PWROFF_PWR_WAIT_CYCLE              12
#define DPI_MASK_PWROFF_PWR_WAIT_CYCLE               ((u32)0x00000007 << 12)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PWROFF_RD_WAIT_CYCLE               9
#define DPI_MASK_PWROFF_RD_WAIT_CYCLE                ((u32)0x00000007 << 9)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PWROFF_WR_WAIT_CYCLE               6
#define DPI_MASK_PWROFF_WR_WAIT_CYCLE                ((u32)0x00000007 << 6)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_RW_PWROFF_MODE                     4
#define DPI_MASK_RW_PWROFF_MODE                      ((u32)0x00000003 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CA_PWROFF_MODE                     2
#define DPI_MASK_CA_PWROFF_MODE                      ((u32)0x00000003 << 2)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_DLY_0
 * @brief  ADR_DLY_0                                 (@ 0X100)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR07_DLY_SEL                      28
#define DPI_MASK_ADR07_DLY_SEL                       ((u32)0x0000000F << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR06_DLY_SEL                      24
#define DPI_MASK_ADR06_DLY_SEL                       ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR05_DLY_SEL                      20
#define DPI_MASK_ADR05_DLY_SEL                       ((u32)0x0000000F << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR04_DLY_SEL                      16
#define DPI_MASK_ADR04_DLY_SEL                       ((u32)0x0000000F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR03_DLY_SEL                      12
#define DPI_MASK_ADR03_DLY_SEL                       ((u32)0x0000000F << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR02_DLY_SEL                      8
#define DPI_MASK_ADR02_DLY_SEL                       ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR01_DLY_SEL                      4
#define DPI_MASK_ADR01_DLY_SEL                       ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR00_DLY_SEL                      0
#define DPI_MASK_ADR00_DLY_SEL                       ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_DLY_1
 * @brief  ADR_DLY_1                                 (@ 0X104)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR15_DLY_SEL                      28
#define DPI_MASK_ADR15_DLY_SEL                       ((u32)0x0000000F << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR14_DLY_SEL                      24
#define DPI_MASK_ADR14_DLY_SEL                       ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR13_DLY_SEL                      20
#define DPI_MASK_ADR13_DLY_SEL                       ((u32)0x0000000F << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR12_DLY_SEL                      16
#define DPI_MASK_ADR12_DLY_SEL                       ((u32)0x0000000F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR11_DLY_SEL                      12
#define DPI_MASK_ADR11_DLY_SEL                       ((u32)0x0000000F << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR10_DLY_SEL                      8
#define DPI_MASK_ADR10_DLY_SEL                       ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR09_DLY_SEL                      4
#define DPI_MASK_ADR09_DLY_SEL                       ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR08_DLY_SEL                      0
#define DPI_MASK_ADR08_DLY_SEL                       ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_DLY_2
 * @brief  ADR_DLY_2                                 (@ 0X108)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ALERT_DLY_SEL                      28
#define DPI_MASK_ALERT_DLY_SEL                       ((u32)0x0000000F << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TEN_DLY_SEL                        24
#define DPI_MASK_TEN_DLY_SEL                         ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR16_DLY_SEL                      20
#define DPI_MASK_ADR16_DLY_SEL                       ((u32)0x0000000F << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_BA2_DLY_SEL                        16
#define DPI_MASK_BA2_DLY_SEL                         ((u32)0x0000000F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_BA1_DLY_SEL                        12
#define DPI_MASK_BA1_DLY_SEL                         ((u32)0x0000000F << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_BA0_DLY_SEL                        8
#define DPI_MASK_BA0_DLY_SEL                         ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR5_EXT_DLY_SEL                   4
#define DPI_MASK_ADR5_EXT_DLY_SEL                    ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR4_EXT_DLY_SEL                   0
#define DPI_MASK_ADR4_EXT_DLY_SEL                    ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CMD_DLY_0
 * @brief  CMD_DLY_0                                 (@ 0X10C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CS_N_1_DLY_SEL                     26
#define DPI_MASK_CS_N_1_DLY_SEL                      ((u32)0x0000000F << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_N_DLY_SEL                       20
#define DPI_MASK_CS_N_DLY_SEL                        ((u32)0x0000000F << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_DLY_SEL                        16
#define DPI_MASK_ODT_DLY_SEL                         ((u32)0x0000000F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_WE_N_DLY_SEL                       12
#define DPI_MASK_WE_N_DLY_SEL                        ((u32)0x0000000F << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAS_N_DLY_SEL                      8
#define DPI_MASK_CAS_N_DLY_SEL                       ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_RAS_N_DLY_SEL                      4
#define DPI_MASK_RAS_N_DLY_SEL                       ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE_DLY_SEL                        0
#define DPI_MASK_CKE_DLY_SEL                         ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CMD_DLY_1
 * @brief  CMD_DLY_1                                 (@ 0X110)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CKE_1_DLY_SEL                      28
#define DPI_MASK_CKE_1_DLY_SEL                       ((u32)0x0000000F << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DDR4_CS_N_DLY_SEL                  24
#define DPI_MASK_DDR4_CS_N_DLY_SEL                   ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ALERT_1_DLY_SEL                    20
#define DPI_MASK_ALERT_1_DLY_SEL                     ((u32)0x0000000F << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_PARITY_1_DLY_SEL                   16
#define DPI_MASK_PARITY_1_DLY_SEL                    ((u32)0x0000000F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_PARITY_DLY_SEL                     12
#define DPI_MASK_PARITY_DLY_SEL                      ((u32)0x0000000F << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DDR4_BG0_DLY_SEL                   8
#define DPI_MASK_DDR4_BG0_DLY_SEL                    ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DDR4_CKE_DLY_SEL                   4
#define DPI_MASK_DDR4_CKE_DLY_SEL                    ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ACT_N_DLY_SEL                      0
#define DPI_MASK_ACT_N_DLY_SEL                       ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_OE_CTL
 * @brief  PAD_OE_CTL                                (@ 0X114)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR54_1TO1                         31
#define DPI_BIT_ADR54_1TO1                           ((u32)0x00000001 << 31)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCK_1_OE                           28
#define DPI_BIT_DCK_1_OE                             ((u32)0x00000001 << 28)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DCK_OE                             27
#define DPI_BIT_DCK_OE                               ((u32)0x00000001 << 27)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_CKE_OE                             26
#define DPI_BIT_CKE_OE                               ((u32)0x00000001 << 26)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_RAS_N_OE                           25
#define DPI_BIT_RAS_N_OE                             ((u32)0x00000001 << 25)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_CAS_N_OE                           24
#define DPI_BIT_CAS_N_OE                             ((u32)0x00000001 << 24)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_WE_N_OE                            23
#define DPI_BIT_WE_N_OE                              ((u32)0x00000001 << 23)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_ODT_OE                             22
#define DPI_BIT_ODT_OE                               ((u32)0x00000001 << 22)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_RESET_N_OE                         21
#define DPI_BIT_RESET_N_OE                           ((u32)0x00000001 << 21)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_BK2_OE                             20
#define DPI_BIT_BK2_OE                               ((u32)0x00000001 << 20)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_BK1_OE                             19
#define DPI_BIT_BK1_OE                               ((u32)0x00000001 << 19)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_BK0_OE                             18
#define DPI_BIT_BK0_OE                               ((u32)0x00000001 << 18)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_EXT_ADR5_OE                        17
#define DPI_BIT_EXT_ADR5_OE                          ((u32)0x00000001 << 17)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_EXT_ADR4_OE                        16
#define DPI_BIT_EXT_ADR4_OE                          ((u32)0x00000001 << 16)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR15_OE                           15
#define DPI_BIT_ADR15_OE                             ((u32)0x00000001 << 15)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR14_OE                           14
#define DPI_BIT_ADR14_OE                             ((u32)0x00000001 << 14)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR13_OE                           13
#define DPI_BIT_ADR13_OE                             ((u32)0x00000001 << 13)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR12_OE                           12
#define DPI_BIT_ADR12_OE                             ((u32)0x00000001 << 12)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR11_OE                           11
#define DPI_BIT_ADR11_OE                             ((u32)0x00000001 << 11)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR10_OE                           10
#define DPI_BIT_ADR10_OE                             ((u32)0x00000001 << 10)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR09_OE                           9
#define DPI_BIT_ADR09_OE                             ((u32)0x00000001 << 9)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR08_OE                           8
#define DPI_BIT_ADR08_OE                             ((u32)0x00000001 << 8)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR07_OE                           7
#define DPI_BIT_ADR07_OE                             ((u32)0x00000001 << 7)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR06_OE                           6
#define DPI_BIT_ADR06_OE                             ((u32)0x00000001 << 6)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR05_OE                           5
#define DPI_BIT_ADR05_OE                             ((u32)0x00000001 << 5)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR04_OE                           4
#define DPI_BIT_ADR04_OE                             ((u32)0x00000001 << 4)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR03_OE                           3
#define DPI_BIT_ADR03_OE                             ((u32)0x00000001 << 3)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR02_OE                           2
#define DPI_BIT_ADR02_OE                             ((u32)0x00000001 << 2)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR01_OE                           1
#define DPI_BIT_ADR01_OE                             ((u32)0x00000001 << 1)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR00_OE                           0
#define DPI_BIT_ADR00_OE                             ((u32)0x00000001 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_OE_CTL_EX
 * @brief  PAD_OE_CTL_EX                             (@ 0X118)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ODT_FORCE                          31
#define DPI_BIT_ODT_FORCE                            ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ACT_N_OE                           17
#define DPI_BIT_ACT_N_OE                             ((u32)0x00000001 << 17)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DDR4_TEN_OE                        16
#define DPI_BIT_DDR4_TEN_OE                          ((u32)0x00000001 << 16)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DDR4_ALERT0_OE                     15
#define DPI_BIT_DDR4_ALERT0_OE                       ((u32)0x00000001 << 15)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DDR4_ALERT1_OE                     14
#define DPI_BIT_DDR4_ALERT1_OE                       ((u32)0x00000001 << 14)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DDR4_CKE_OE                        13
#define DPI_BIT_DDR4_CKE_OE                          ((u32)0x00000001 << 13)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DDR4_BG0_OE                        12
#define DPI_BIT_DDR4_BG0_OE                          ((u32)0x00000001 << 12)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_PARITY_OE                          11
#define DPI_BIT_PARITY_OE                            ((u32)0x00000001 << 11)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_PARITY_1_OE                        10
#define DPI_BIT_PARITY_1_OE                          ((u32)0x00000001 << 10)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_ADR16_OE                           9
#define DPI_BIT_ADR16_OE                             ((u32)0x00000001 << 9)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_DDR4_CS_N_OE                       8
#define DPI_BIT_DDR4_CS_N_OE                         ((u32)0x00000001 << 8)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_CKE_1_OE                           2
#define DPI_BIT_CKE_1_OE                             ((u32)0x00000001 << 2)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_CS_N_1_OE                          1
#define DPI_BIT_CS_N_1_OE                            ((u32)0x00000001 << 1)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_CS_N_OE                            0
#define DPI_BIT_CS_N_OE                              ((u32)0x00000001 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_ALERT_SEL_0
 * @brief  PAD_ALERT_SEL_0                           (@ 0X11C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ALERT_SEL_0                        0
#define DPI_MASK_ALERT_SEL_0                         ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_ALERT_SEL_1
 * @brief  PAD_ALERT_SEL_1                           (@ 0X120)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ALERT_SEL_1                        0
#define DPI_MASK_ALERT_SEL_1                         ((u32)0x0000000F << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_ALERT1_SEL_0
 * @brief  PAD_ALERT1_SEL_0                          (@ 0X124)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ALERT_1_SEL_0                      0
#define DPI_MASK_ALERT_1_SEL_0                       ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0x80000000  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_ALERT1_SEL_1
 * @brief  PAD_ALERT1_SEL_1                          (@ 0X128)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ALERT_1_SEL_1                      0
#define DPI_MASK_ALERT_1_SEL_1                       ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_IDDQ
 * @brief  PAD_IDDQ                                  (@ 0X12C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_IDDQ                               0
#define DPI_MASK_IDDQ                                ((u32)0x00000FFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_CTRL_PROG
 * @brief  PAD_CTRL_PROG                             (@ 0X130)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZCTRL_FILTER_EN                    31
#define DPI_BIT_ZCTRL_FILTER_EN                      ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DZQ_UP_SEL                         28
#define DPI_MASK_DZQ_UP_SEL                          ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DZQ_AUTO_UP                        27
#define DPI_BIT_DZQ_AUTO_UP                          ((u32)0x00000001 << 27)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZCTRL_CLK_SEL                      25
#define DPI_MASK_ZCTRL_CLK_SEL                       ((u32)0x00000003 << 25)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_ZCTRL_START                        24
#define DPI_BIT_ZCTRL_START                          ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZCOMP_MODE                         23
#define DPI_BIT_ZCOMP_MODE                           ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZCTRL_MODE                         20
#define DPI_MASK_ZCTRL_MODE                          ((u32)0x00000007 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RZQ_EXT_R240                       19
#define DPI_BIT_RZQ_EXT_R240                         ((u32)0x00000001 << 19)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DZQ_REF_UP                         18
#define DPI_BIT_DZQ_REF_UP                           ((u32)0x00000001 << 18)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RZQ_COMP_INV                       17
#define DPI_BIT_RZQ_COMP_INV                         ((u32)0x00000001 << 17)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RZQ_CAL_EN                         16
#define DPI_BIT_RZQ_CAL_EN                           ((u32)0x00000001 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RVD                                15
#define DPI_BIT_RVD                                  ((u32)0x00000001 << 15)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZCTR_NCYC                          8
#define DPI_MASK_ZCTR_NCYC                           ((u32)0x0000007F << 8)                              /*!<R/W 0xC  RSVD */
#define DPI_SHIFT_ZQ_CAL_CMD                         7
#define DPI_BIT_ZQ_CAL_CMD                           ((u32)0x00000001 << 7)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZCTR_NCYC_LRG                      0
#define DPI_MASK_ZCTR_NCYC_LRG                       ((u32)0x0000007F << 0)                              /*!<R/W 0x19  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ZQ_NOCD2
 * @brief  ZQ_NOCD2                                  (@ 0X13C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZQ_OVWR_NOCD_DATA                  8
#define DPI_MASK_ZQ_OVWR_NOCD_DATA                   ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZQ_ENA_NOCD2                       0
#define DPI_BIT_ZQ_ENA_NOCD2                         ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_ZCTRL_STATUS
 * @brief  PAD_ZCTRL_STATUS                          (@ 0X140)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZCTRL_STATUS                       0
#define DPI_MASK_ZCTRL_STATUS                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_ZCTRL_RESULT
 * @brief  PAD_ZCTRL_RESULT                          (@ 0X144)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZCTRL_RESULT                       0
#define DPI_MASK_ZCTRL_RESULT                        ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_ZCTRL_RESULT_D
 * @brief  PAD_ZCTRL_RESULT_D                        (@ 0X148)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZCTRL_RESULT_DBG                   0
#define DPI_MASK_ZCTRL_RESULT_DBG                    ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_RZCTRL_STATUS
 * @brief  PAD_RZCTRL_STATUS                         (@ 0X14C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RZQ_480CODE                        1
#define DPI_MASK_RZQ_480CODE                         ((u32)0x0000001F << 1)                              /*!<R/W 0xF  RSVD */
#define DPI_SHIFT_RZQ_CAL_DONE                       0
#define DPI_BIT_RZQ_CAL_DONE                         ((u32)0x00000001 << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_DQS_CTRL
 * @brief  dq_dqs_ctrl                               (@ 0X150)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_TEN_EN                             24
#define DPI_BIT_TEN_EN                               ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_OE_SIG                         3
#define DPI_BIT_DQS_OE_SIG                           ((u32)0x00000001 << 3)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_DQ_LATCH_EN                        2
#define DPI_BIT_DQ_LATCH_EN                          ((u32)0x00000001 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TRIG_DQS                           1
#define DPI_BIT_TRIG_DQS                             ((u32)0x00000001 << 1)                              /*!<W 0  RSVD */
#define DPI_SHIFT_DQS_OE_FRC_EN                      0
#define DPI_BIT_DQS_OE_FRC_EN                        ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CMD_ADR_PH
 * @brief  CMD_ADDR_PH                               (@ 0X154)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CKE_1_PH_EN                        30
#define DPI_BIT_CKE_1_PH_EN                          ((u32)0x00000001 << 30)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE_PH_EN                          29
#define DPI_BIT_CKE_PH_EN                            ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_1_PH_EN                         28
#define DPI_BIT_CS_1_PH_EN                           ((u32)0x00000001 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_PH_EN                           27
#define DPI_BIT_CS_PH_EN                             ((u32)0x00000001 << 27)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CMD_PH_EN                          26
#define DPI_BIT_CMD_PH_EN                            ((u32)0x00000001 << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE_1_GEARDOWN                     24
#define DPI_BIT_CKE_1_GEARDOWN                       ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE_GEARDOWN                       23
#define DPI_BIT_CKE_GEARDOWN                         ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_1_GEARDOWN                      22
#define DPI_BIT_CS_1_GEARDOWN                        ((u32)0x00000001 << 22)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_GEARDOWN                        21
#define DPI_BIT_CS_GEARDOWN                          ((u32)0x00000001 << 21)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CMD_GEARDOWN                       20
#define DPI_BIT_CMD_GEARDOWN                         ((u32)0x00000001 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE_1_PH_SEL                       16
#define DPI_MASK_CKE_1_PH_SEL                        ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE_PH_SEL                         12
#define DPI_MASK_CKE_PH_SEL                          ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_1_PH_SEL                        8
#define DPI_MASK_CS_1_PH_SEL                         ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_PH_SEL                          4
#define DPI_MASK_CS_PH_SEL                           ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CMD_PH_SEL                         0
#define DPI_MASK_CMD_PH_SEL                          ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_PAT_IN0
 * @brief  DQ_PAT_IN0                                (@ 0X158)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_PAT_IN                          0
#define DPI_MASK_DQ_PAT_IN0                           ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_PAT_IN1
 * @brief  DQ_PAT_IN1                                (@ 0X15C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_PAT_IN                          0
#define DPI_MASK_DQ_PAT_IN1                           ((u32)0x0000000F << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_WRLVL_DQS_DATA
 * @brief  WRLVL_DQS_DATA                            (@ 0X160)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_WRLVL_DQSDATA                      0
#define DPI_MASK_WRLVL_DQSDATA                       ((u32)0x000000FF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_TEST_CTRL0
 * @brief  TEST_CTRL0                                (@ 0X164)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_LBK_MODE                           30
#define DPI_MASK_LBK_MODE                            ((u32)0x00000003 << 30)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_LBK_SET                            29
#define DPI_BIT_LBK_SET                              ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DATA_EN_CHK                        28
#define DPI_BIT_DATA_EN_CHK                          ((u32)0x00000001 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TOP_DBG_SEL                        25
#define DPI_MASK_TOP_DBG_SEL                         ((u32)0x00000007 << 25)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RW_DBG_SEL0                        20
#define DPI_MASK_RW_DBG_SEL0                         ((u32)0x00000003 << 20)                             /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_TEST_CTRL1
 * @brief  TEST_CTRL1                                (@ 0X168)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DCC_DSP_DBG_SEL                    26
#define DPI_BIT_DCC_DSP_DBG_SEL                      ((u32)0x00000001 << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DBG_DLL_SEL                        24
#define DPI_BIT_DBG_DLL_SEL                          ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQSEN_DBG_SEL                      22
#define DPI_MASK_DQSEN_DBG_SEL                       ((u32)0x00000003 << 22)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RW_DBG_SEL1                        20
#define DPI_MASK_RW_DBG_SEL1                         ((u32)0x00000003 << 20)                             /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_HALF_CYC_DET
 * @brief  HAF_CYC_DET                               (@ 0X16C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DET_CLK_ENABLE                     15
#define DPI_BIT_DET_CLK_ENABLE                       ((u32)0x00000001 << 15)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DET_ENABLE                         14
#define DPI_BIT_DET_ENABLE                           ((u32)0x00000001 << 14)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DET_DONE                           13
#define DPI_BIT_DET_DONE                             ((u32)0x00000001 << 13)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DET_RESULT                         0
#define DPI_MASK_DET_RESULT                          ((u32)0x00001FFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL1
 * @brief  READ_CTRL1                                (@ 0X170)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RDDATA_EN_DLY_SEL                  28
#define DPI_MASK_RDDATA_EN_DLY_SEL                   ((u32)0x00000003 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_NCON_3T_MODE                       27
#define DPI_BIT_NCON_3T_MODE                         ((u32)0x00000001 << 27)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_NCON_2T_MODE                       26
#define DPI_BIT_NCON_2T_MODE                         ((u32)0x00000001 << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RD_DLY_FOLLOW_DQ0                  10
#define DPI_BIT_RD_DLY_FOLLOW_DQ0                    ((u32)0x00000001 << 10)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_LAT_EN_FORCE_SEL                9
#define DPI_BIT_DQ_LAT_EN_FORCE_SEL                  ((u32)0x00000001 << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_LAT_EN_FORCE_SIG                8
#define DPI_BIT_DQ_LAT_EN_FORCE_SIG                  ((u32)0x00000001 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_RD_FIFO                         0
#define DPI_MASK_TM_RD_FIFO                          ((u32)0x0000003F << 0)                              /*!<R/W 0x2  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_TX_RPT_CTRL
 * @brief  TX_RPT_CTRL                               (@ 0X174)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CKE_1_RPT_DEC                      27
#define DPI_BIT_CKE_1_RPT_DEC                        ((u32)0x00000001 << 27)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE_1_RPT_ADD                      26
#define DPI_BIT_CKE_1_RPT_ADD                        ((u32)0x00000001 << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE_RPT_DEC                        25
#define DPI_BIT_CKE_RPT_DEC                          ((u32)0x00000001 << 25)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE_RPT_ADD                        24
#define DPI_BIT_CKE_RPT_ADD                          ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_1_RPT_DEC                       23
#define DPI_BIT_CS_1_RPT_DEC                         ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_1_RPT_ADD                       22
#define DPI_BIT_CS_1_RPT_ADD                         ((u32)0x00000001 << 22)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_RPT_DEC                         21
#define DPI_BIT_CS_RPT_DEC                           ((u32)0x00000001 << 21)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_RPT_ADD                         20
#define DPI_BIT_CS_RPT_ADD                           ((u32)0x00000001 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CA_RPT_DEC                         19
#define DPI_BIT_CA_RPT_DEC                           ((u32)0x00000001 << 19)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CA_RPT_ADD                         18
#define DPI_BIT_CA_RPT_ADD                           ((u32)0x00000001 << 18)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RX_RPT_DEC                         17
#define DPI_BIT_RX_RPT_DEC                           ((u32)0x00000001 << 17)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RX_RPT_ADD                         16
#define DPI_BIT_RX_RPT_ADD                           ((u32)0x00000001 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_RPT_DEC_3                      15
#define DPI_BIT_DQS_RPT_DEC_3                        ((u32)0x00000001 << 15)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_RPT_ADD_3                      14
#define DPI_BIT_DQS_RPT_ADD_3                        ((u32)0x00000001 << 14)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_RPT_DEC_2                      13
#define DPI_BIT_DQS_RPT_DEC_2                        ((u32)0x00000001 << 13)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_RPT_ADD_2                      12
#define DPI_BIT_DQS_RPT_ADD_2                        ((u32)0x00000001 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_RPT_DEC_1                      11
#define DPI_BIT_DQS_RPT_DEC_1                        ((u32)0x00000001 << 11)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_RPT_ADD_1                      10
#define DPI_BIT_DQS_RPT_ADD_1                        ((u32)0x00000001 << 10)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_RPT_DEC_0                      9
#define DPI_BIT_DQS_RPT_DEC_0                        ((u32)0x00000001 << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_RPT_ADD_0                      8
#define DPI_BIT_DQS_RPT_ADD_0                        ((u32)0x00000001 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_RPT_DEC_3                       7
#define DPI_BIT_DQ_RPT_DEC_3                         ((u32)0x00000001 << 7)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_RPT_ADD_3                       6
#define DPI_BIT_DQ_RPT_ADD_3                         ((u32)0x00000001 << 6)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_RPT_DEC_2                       5
#define DPI_BIT_DQ_RPT_DEC_2                         ((u32)0x00000001 << 5)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_RPT_ADD_2                       4
#define DPI_BIT_DQ_RPT_ADD_2                         ((u32)0x00000001 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_RPT_DEC_1                       3
#define DPI_BIT_DQ_RPT_DEC_1                         ((u32)0x00000001 << 3)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_RPT_ADD_1                       2
#define DPI_BIT_DQ_RPT_ADD_1                         ((u32)0x00000001 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_RPT_DEC_0                       1
#define DPI_BIT_DQ_RPT_DEC_0                         ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_RPT_ADD_0                       0
#define DPI_BIT_DQ_RPT_ADD_0                         ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_SHIFT_CTRL
 * @brief  CAL_SHIFT_CTRL                            (@ 0X178)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CAL_LEAD3                          28
#define DPI_MASK_CAL_LEAD3                           ((u32)0x00000007 << 28)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_CAL_LEAD2                          24
#define DPI_MASK_CAL_LEAD2                           ((u32)0x00000007 << 24)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_CAL_LEAD1                          20
#define DPI_MASK_CAL_LEAD1                           ((u32)0x00000007 << 20)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_CAL_LEAD0                          16
#define DPI_MASK_CAL_LEAD0                           ((u32)0x00000007 << 16)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_CAL_LAG3                           12
#define DPI_MASK_CAL_LAG3                            ((u32)0x00000007 << 12)                             /*!<R/W 0x6  RSVD */
#define DPI_SHIFT_CAL_LAG2                           8
#define DPI_MASK_CAL_LAG2                            ((u32)0x00000007 << 8)                              /*!<R/W 0x6  RSVD */
#define DPI_SHIFT_CAL_LAG1                           4
#define DPI_MASK_CAL_LAG1                            ((u32)0x00000007 << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CAL_LAG0                           0
#define DPI_MASK_CAL_LAG0                            ((u32)0x00000007 << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DT_SET0
 * @brief  DT_SET0                                   (@ 0X17C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DTN_CLK                            20
#define DPI_MASK_DTN_CLK                             ((u32)0x00000003 << 20)                             /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_DTP_CLK                            16
#define DPI_MASK_DTP_CLK                             ((u32)0x00000003 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DTN_DQS                            12
#define DPI_MASK_DTN_DQS                             ((u32)0x0000000F << 12)                             /*!<R/W 0xF  RSVD */
#define DPI_SHIFT_DTP_DQS                            8
#define DPI_MASK_DTP_DQS                             ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DTN_DQ                             4
#define DPI_MASK_DTN_DQ                              ((u32)0x0000000F << 4)                              /*!<R/W 0xF  RSVD */
#define DPI_SHIFT_DTP_DQ                             0
#define DPI_MASK_DTP_DQ                              ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ODT_TTCP0_SET0
 * @brief  ODT_TTCP0_SEL0                            (@ 0X180)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ODT_TTCP_SET_3_PRE                 24
#define DPI_MASK_ODT_TTCP_SET_3_PRE                  ((u32)0x0000003F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_2_PRE                 16
#define DPI_MASK_ODT_TTCP_SET_2_PRE                  ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_1_PRE                 8
#define DPI_MASK_ODT_TTCP_SET_1_PRE                  ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_0_PRE                 0
#define DPI_MASK_ODT_TTCP_SET_0_PRE                  ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ODT_TTCP1_SET0
 * @brief  ODT_TTCP1_SEL0                            (@ 0X184)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ODT_TTCP_SET_7_PRE                 24
#define DPI_MASK_ODT_TTCP_SET_7_PRE                  ((u32)0x0000003F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_6_PRE                 16
#define DPI_MASK_ODT_TTCP_SET_6_PRE                  ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_5_PRE                 8
#define DPI_MASK_ODT_TTCP_SET_5_PRE                  ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_4_PRE                 0
#define DPI_MASK_ODT_TTCP_SET_4_PRE                  ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ODT_TTCN0_SET0
 * @brief  ODT_TTCN0_SEL0                            (@ 0X188)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ODT_TTCN_SET_3_PRE                 24
#define DPI_MASK_ODT_TTCN_SET_3_PRE                  ((u32)0x0000003F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_2_PRE                 16
#define DPI_MASK_ODT_TTCN_SET_2_PRE                  ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_1_PRE                 8
#define DPI_MASK_ODT_TTCN_SET_1_PRE                  ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_0_PRE                 0
#define DPI_MASK_ODT_TTCN_SET_0_PRE                  ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ODT_TTCN1_SET0
 * @brief  ODT_TTCN1_SEL0                            (@ 0X18C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ODT_TTCN_SET_7_PRE                 24
#define DPI_MASK_ODT_TTCN_SET_7_PRE                  ((u32)0x0000003F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_6_PRE                 16
#define DPI_MASK_ODT_TTCN_SET_6_PRE                  ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_5_PRE                 8
#define DPI_MASK_ODT_TTCN_SET_5_PRE                  ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_4_PRE                 0
#define DPI_MASK_ODT_TTCN_SET_4_PRE                  ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCDP0_SET0
 * @brief  OCDP0_SET0                                (@ 0X190)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_OCDP_SET_3_PRE                     24
#define DPI_MASK_OCDP_SET_3_PRE                      ((u32)0x0000003F << 24)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_2_PRE                     16
#define DPI_MASK_OCDP_SET_2_PRE                      ((u32)0x0000003F << 16)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_1_PRE                     8
#define DPI_MASK_OCDP_SET_1_PRE                      ((u32)0x0000003F << 8)                              /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_0_PRE                     0
#define DPI_MASK_OCDP_SET_0_PRE                      ((u32)0x0000003F << 0)                              /*!<R/W 0x26  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCDP1_SET0
 * @brief  OCDP1_SET0                                (@ 0X194)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_OCDP_SET_7_PRE                     24
#define DPI_MASK_OCDP_SET_7_PRE                      ((u32)0x0000003F << 24)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_6_PRE                     16
#define DPI_MASK_OCDP_SET_6_PRE                      ((u32)0x0000003F << 16)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_5_PRE                     8
#define DPI_MASK_OCDP_SET_5_PRE                      ((u32)0x0000003F << 8)                              /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_4_PRE                     0
#define DPI_MASK_OCDP_SET_4_PRE                      ((u32)0x0000003F << 0)                              /*!<R/W 0x26  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCDN0_SET0
 * @brief  OCDN0_SET0                                (@ 0X198)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_OCDP_SET_7_PRE                     24
#define DPI_MASK_OCDP_SET_7_PRE                      ((u32)0x0000003F << 24)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_6_PRE                     16
#define DPI_MASK_OCDP_SET_6_PRE                      ((u32)0x0000003F << 16)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_5_PRE                     8
#define DPI_MASK_OCDP_SET_5_PRE                      ((u32)0x0000003F << 8)                              /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_4_PRE                     0
#define DPI_MASK_OCDP_SET_4_PRE                      ((u32)0x0000003F << 0)                              /*!<R/W 0x26  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCDN1_SET0
 * @brief  OCDN1_SET0                                (@ 0X19C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_OCDN_SET_7_PRE                     24
#define DPI_MASK_OCDN_SET_7_PRE                      ((u32)0x0000003F << 24)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDN_SET_6_PRE                     16
#define DPI_MASK_OCDN_SET_6_PRE                      ((u32)0x0000003F << 16)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDN_SET_5_PRE                     8
#define DPI_MASK_OCDN_SET_5_PRE                      ((u32)0x0000003F << 8)                              /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDN_SET_4_PRE                     0
#define DPI_MASK_OCDN_SET_4_PRE                      ((u32)0x0000003F << 0)                              /*!<R/W 0x26  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ODT_TTCP0_SET1
 * @brief  ODT_TTCP0_SEL1                            (@ 0X1A0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ODT_TTCP_SET_3                     24
#define DPI_MASK_ODT_TTCP_SET_3                      ((u32)0x0000003F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_2                     16
#define DPI_MASK_ODT_TTCP_SET_2                      ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_1                     8
#define DPI_MASK_ODT_TTCP_SET_1                      ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_0                     0
#define DPI_MASK_ODT_TTCP_SET_0                      ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ODT_TTCP1_SET1
 * @brief  ODT_TTCP1_SEL1                            (@ 0X1A4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ODT_TTCP_SET_7                     24
#define DPI_MASK_ODT_TTCP_SET_7                      ((u32)0x0000003F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_6                     16
#define DPI_MASK_ODT_TTCP_SET_6                      ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_5                     8
#define DPI_MASK_ODT_TTCP_SET_5                      ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCP_SET_4                     0
#define DPI_MASK_ODT_TTCP_SET_4                      ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ODT_TTCN0_SET1
 * @brief  ODT_TTCN0_SEL1                            (@ 0X1A8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ODT_TTCN_SET_3                     24
#define DPI_MASK_ODT_TTCN_SET_3                      ((u32)0x0000003F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_2                     16
#define DPI_MASK_ODT_TTCN_SET_2                      ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_1                     8
#define DPI_MASK_ODT_TTCN_SET_1                      ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_0                     0
#define DPI_MASK_ODT_TTCN_SET_0                      ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ODT_TTCN1_SET1
 * @brief  ODT_TTCN1_SEL1                            (@ 0X1AC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ODT_TTCN_SET_7                     24
#define DPI_MASK_ODT_TTCN_SET_7                      ((u32)0x0000003F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_6                     16
#define DPI_MASK_ODT_TTCN_SET_6                      ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_5                     8
#define DPI_MASK_ODT_TTCN_SET_5                      ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_TTCN_SET_4                     0
#define DPI_MASK_ODT_TTCN_SET_4                      ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCDP0_SET1
 * @brief  OCDP0_SET1                                (@ 0X1B0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_OCDP_SET_3                         24
#define DPI_MASK_OCDP_SET_3                          ((u32)0x0000003F << 24)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_2                         16
#define DPI_MASK_OCDP_SET_2                          ((u32)0x0000003F << 16)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_1                         8
#define DPI_MASK_OCDP_SET_1                          ((u32)0x0000003F << 8)                              /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_0                         0
#define DPI_MASK_OCDP_SET_0                          ((u32)0x0000003F << 0)                              /*!<R/W 0x26  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCDP1_SET1
 * @brief  OCDP1_SET1                                (@ 0X1B4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_OCDP_SET_7                         24
#define DPI_MASK_OCDP_SET_7                          ((u32)0x0000003F << 24)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_6                         16
#define DPI_MASK_OCDP_SET_6                          ((u32)0x0000003F << 16)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_5                         8
#define DPI_MASK_OCDP_SET_5                          ((u32)0x0000003F << 8)                              /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDP_SET_4                         0
#define DPI_MASK_OCDP_SET_4                          ((u32)0x0000003F << 0)                              /*!<R/W 0x26  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCDN0_SET1
 * @brief  OCDN0_SET1                                (@ 0X1B8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_OCDN_SET_3                         24
#define DPI_MASK_OCDN_SET_3                          ((u32)0x0000003F << 24)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDN_SET_2                         16
#define DPI_MASK_OCDN_SET_2                          ((u32)0x0000003F << 16)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDN_SET_1                         8
#define DPI_MASK_OCDN_SET_1                          ((u32)0x0000003F << 8)                              /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDN_SET_0                         0
#define DPI_MASK_OCDN_SET_0                          ((u32)0x0000003F << 0)                              /*!<R/W 0x26  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCDN1_SET1
 * @brief  OCDN1_SET1                                (@ 0X1BC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_OCDN_SET_7                         24
#define DPI_MASK_OCDN_SET_7                          ((u32)0x0000003F << 24)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDN_SET_6                         16
#define DPI_MASK_OCDN_SET_6                          ((u32)0x0000003F << 16)                             /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDN_SET_5                         8
#define DPI_MASK_OCDN_SET_5                          ((u32)0x0000003F << 8)                              /*!<R/W 0x26  RSVD */
#define DPI_SHIFT_OCDN_SET_4                         0
#define DPI_MASK_OCDN_SET_4                          ((u32)0x0000003F << 0)                              /*!<R/W 0x26  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_ODT_SEL_0
 * @brief  DQ_ODT_DEL_0                              (@ 0X1C0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_1_TTCN_SEL                      12
#define DPI_MASK_DQ_1_TTCN_SEL                       ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_0_TTCN_SEL                      8
#define DPI_MASK_DQ_0_TTCN_SEL                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_1_TTCP_SEL                      4
#define DPI_MASK_DQ_1_TTCP_SEL                       ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_0_TTCP_SEL                      0
#define DPI_MASK_DQ_0_TTCP_SEL                       ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_ODT_SEL_1
 * @brief  DQ_ODT_DEL_1                              (@ 0X1C4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_1_TTCN_SEL                      12
#define DPI_MASK_DQ_1_TTCN_SEL                       ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_0_TTCN_SEL                      8
#define DPI_MASK_DQ_0_TTCN_SEL                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_1_TTCP_SEL                      4
#define DPI_MASK_DQ_1_TTCP_SEL                       ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_0_TTCP_SEL                      0
#define DPI_MASK_DQ_0_TTCP_SEL                       ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_OCD_SEL_0
 * @brief  DQ_OCD_SEL_0                              (@ 0X1C8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_1_OCDN_SEL                      12
#define DPI_MASK_DQ_1_OCDN_SEL                       ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_0_OCDN_SEL                      8
#define DPI_MASK_DQ_0_OCDN_SEL                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_1_OCDP_SEL                      4
#define DPI_MASK_DQ_1_OCDP_SEL                       ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_0_OCDP_SEL                      0
#define DPI_MASK_DQ_0_OCDP_SEL                       ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_OCD_SEL_1
 * @brief  DQ_OCD_SEL_1                              (@ 0X1CC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_1_OCDN_SEL                      12
#define DPI_MASK_DQ_1_OCDN_SEL                       ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_0_OCDN_SEL                      8
#define DPI_MASK_DQ_0_OCDN_SEL                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_1_OCDP_SEL                      4
#define DPI_MASK_DQ_1_OCDP_SEL                       ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_0_OCDP_SEL                      0
#define DPI_MASK_DQ_0_OCDP_SEL                       ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_P_ODT_SEL_0
 * @brief  DQS_P_ODT_SEL_0                           (@ 0X1D0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_P_1_TTCN_SEL                   12
#define DPI_MASK_DQS_P_1_TTCN_SEL                    ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_0_TTCN_SEL                   8
#define DPI_MASK_DQS_P_0_TTCN_SEL                    ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_1_TTCP_SEL                   4
#define DPI_MASK_DQS_P_1_TTCP_SEL                    ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_0_TTCP_SEL                   0
#define DPI_MASK_DQS_P_0_TTCP_SEL                    ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_P_ODT_SEL_1
 * @brief  DQS_P_ODT_SEL_1                           (@ 0X1D4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_P_1_TTCN_SEL                   12
#define DPI_MASK_DQS_P_1_TTCN_SEL                    ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_0_TTCN_SEL                   8
#define DPI_MASK_DQS_P_0_TTCN_SEL                    ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_1_TTCP_SEL                   4
#define DPI_MASK_DQS_P_1_TTCP_SEL                    ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_0_TTCP_SEL                   0
#define DPI_MASK_DQS_P_0_TTCP_SEL                    ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_N_ODT_SEL_0
 * @brief  DQS_N_ODT_SEL_0                           (@ 0X1D8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_N_1_TTCN_SEL                   12
#define DPI_MASK_DQS_N_1_TTCN_SEL                    ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_0_TTCN_SEL                   8
#define DPI_MASK_DQS_N_0_TTCN_SEL                    ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_1_TTCP_SEL                   4
#define DPI_MASK_DQS_N_1_TTCP_SEL                    ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_0_TTCP_SEL                   0
#define DPI_MASK_DQS_N_0_TTCP_SEL                    ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_N_ODT_SEL_1
 * @brief  DQS_N_ODT_SEL_1                           (@ 0X1DC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_N_1_TTCN_SEL                   12
#define DPI_MASK_DQS_N_1_TTCN_SEL                    ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_0_TTCN_SEL                   8
#define DPI_MASK_DQS_N_0_TTCN_SEL                    ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_1_TTCP_SEL                   4
#define DPI_MASK_DQS_N_1_TTCP_SEL                    ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_0_TTCP_SEL                   0
#define DPI_MASK_DQS_N_0_TTCP_SEL                    ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_OCD_SEL_0
 * @brief  DQS_OCD_SEL_0                             (@ 0X1E0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_N_1_OCDN_SEL                   28
#define DPI_MASK_DQS_N_1_OCDN_SEL                    ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_0_OCDN_SEL                   24
#define DPI_MASK_DQS_N_0_OCDN_SEL                    ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_1_OCDP_SEL                   20
#define DPI_MASK_DQS_N_1_OCDP_SEL                    ((u32)0x00000007 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_0_OCDP_SEL                   16
#define DPI_MASK_DQS_N_0_OCDP_SEL                    ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_1_OCDN_SEL                   12
#define DPI_MASK_DQS_P_1_OCDN_SEL                    ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_0_OCDN_SEL                   8
#define DPI_MASK_DQS_P_0_OCDN_SEL                    ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_1_OCDP_SEL                   4
#define DPI_MASK_DQS_P_1_OCDP_SEL                    ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_0_OCDP_SEL                   0
#define DPI_MASK_DQS_P_0_OCDP_SEL                    ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_OCD_SEL_1
 * @brief  DQS_OCD_SEL_1                             (@ 0X1E4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_N_1_OCDN_SEL                   28
#define DPI_MASK_DQS_N_1_OCDN_SEL                    ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_0_OCDN_SEL                   24
#define DPI_MASK_DQS_N_0_OCDN_SEL                    ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_1_OCDP_SEL                   20
#define DPI_MASK_DQS_N_1_OCDP_SEL                    ((u32)0x00000007 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_N_0_OCDP_SEL                   16
#define DPI_MASK_DQS_N_0_OCDP_SEL                    ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_1_OCDN_SEL                   12
#define DPI_MASK_DQS_P_1_OCDN_SEL                    ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_0_OCDN_SEL                   8
#define DPI_MASK_DQS_P_0_OCDN_SEL                    ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_1_OCDP_SEL                   4
#define DPI_MASK_DQS_P_1_OCDP_SEL                    ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_P_0_OCDP_SEL                   0
#define DPI_MASK_DQS_P_0_OCDP_SEL                    ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CKE_OCD_SEL
 * @brief  CKE_OCD_SEL                               (@ 0X1E8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CKE_1_OCDN_SEL                     12
#define DPI_MASK_CKE_1_OCDN_SEL                      ((u32)0x00000007 << 12)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_CKE_1_OCDP_SEL                     8
#define DPI_MASK_CKE_1_OCDP_SEL                      ((u32)0x00000007 << 8)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_CKE_OCDN_SEL                       4
#define DPI_MASK_CKE_OCDN_SEL                        ((u32)0x00000007 << 4)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_CKE_OCDP_SEL                       0
#define DPI_MASK_CKE_OCDP_SEL                        ((u32)0x00000007 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_OCD_SEL
 * @brief  ADR_OCD_SEL                               (@ 0X1EC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CS_1_OCDN_SEL                      28
#define DPI_MASK_CS_1_OCDN_SEL                       ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_1_OCDP_SEL                      24
#define DPI_MASK_CS_1_OCDP_SEL                       ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_OCDN_SEL                        12
#define DPI_MASK_CS_OCDN_SEL                         ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_OCDP_SEL                        8
#define DPI_MASK_CS_OCDP_SEL                         ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CK_OCD_SEL
 * @brief  CK_OCD_SEL                                (@ 0X1F0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CK_N_1_OCDN_SEL                    28
#define DPI_MASK_CK_N_1_OCDN_SEL                     ((u32)0x00000007 << 28)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_CK_N_0_OCDN_SEL                    24
#define DPI_MASK_CK_N_0_OCDN_SEL                     ((u32)0x00000007 << 24)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_CK_N_1_OCDP_SEL                    20
#define DPI_MASK_CK_N_1_OCDP_SEL                     ((u32)0x00000007 << 20)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_CK_N_0_OCDP_SEL                    16
#define DPI_MASK_CK_N_0_OCDP_SEL                     ((u32)0x00000007 << 16)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_CK_P_1_OCDN_SEL                    12
#define DPI_MASK_CK_P_1_OCDN_SEL                     ((u32)0x00000007 << 12)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_CK_P_0_OCDN_SEL                    8
#define DPI_MASK_CK_P_0_OCDN_SEL                     ((u32)0x00000007 << 8)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_CK_P_1_OCDP_SEL                    4
#define DPI_MASK_CK_P_1_OCDP_SEL                     ((u32)0x00000007 << 4)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_CK_P_0_OCDP_SEL                    0
#define DPI_MASK_CK_P_0_OCDP_SEL                     ((u32)0x00000007 << 0)                              /*!<R/W 0x2  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_BUS_0
 * @brief  PAD_BUS_0                                 (@ 0X1F4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_EN_DCC                             31
#define DPI_BIT_EN_DCC                               ((u32)0x00000001 << 31)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_PD_CK                              30
#define DPI_BIT_PD_CK                                ((u32)0x00000001 << 30)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_EN_DMYI                            29
#define DPI_BIT_EN_DMYI                              ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_VREF_SEL                           28
#define DPI_BIT_VREF_SEL                             ((u32)0x00000001 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_VREF_RANGE                         27
#define DPI_BIT_VREF_RANGE                           ((u32)0x00000001 << 27)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_VREF_S                             21
#define DPI_MASK_VREF_S                              ((u32)0x0000003F << 21)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_VREF_CURRENTSEL                    19
#define DPI_MASK_VREF_CURRENTSEL                     ((u32)0x00000003 << 19)                             /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_VREF_PD                            18
#define DPI_BIT_VREF_PD                              ((u32)0x00000001 << 18)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_PAD_BUS_0                          0
#define DPI_MASK_PAD_BUS_0                           ((u32)0x0003FFFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_BUS_1
 * @brief  PAD_BUS_1                                 (@ 0X1F8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_PD_CK_1                            31
#define DPI_BIT_PD_CK_1                              ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_PAD_BUS_1                          0
#define DPI_MASK_PAD_BUS_1                           ((u32)0x0000007F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_BUS_2
 * @brief  PAD_BUS_2                                 (@ 0X1FC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_VREF_RANGE_2                       23
#define DPI_BIT_VREF_RANGE_2                         ((u32)0x00000001 << 23)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_VREF_S_2                           17
#define DPI_MASK_VREF_S_2                            ((u32)0x0000003F << 17)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_VREF_PD_2                          16
#define DPI_BIT_VREF_PD_2                            ((u32)0x00000001 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_VREF_RANGE_1                       15
#define DPI_BIT_VREF_RANGE_1                         ((u32)0x00000001 << 15)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_VREF_S_1                           9
#define DPI_MASK_VREF_S_1                            ((u32)0x0000003F << 9)                              /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_VREF_PD_1                          8
#define DPI_BIT_VREF_PD_1                            ((u32)0x00000001 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_VREF_RANGE_0                       7
#define DPI_BIT_VREF_RANGE_0                         ((u32)0x00000001 << 7)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_VREF_S_0                           1
#define DPI_MASK_VREF_S_0                            ((u32)0x0000003F << 1)                              /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_VREF_PD_0                          0
#define DPI_BIT_VREF_PD_0                            ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ZQ_TRIM
 * @brief  ZQ_TRIM                                   (@ 0X200)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_R480_TRIM                          0
#define DPI_BIT_R480_TRIM                            ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCD_SEL_0
 * @brief  OCD_SEL_0                                 (@ 0X204)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR00_OCDN_SEL                     28
#define DPI_MASK_ADR00_OCDN_SEL                      ((u32)0x00000007 << 28)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR00_OCDP_SEL                     24
#define DPI_MASK_ADR00_OCDP_SEL                      ((u32)0x00000007 << 24)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR01_OCDN_SEL                     20
#define DPI_MASK_ADR01_OCDN_SEL                      ((u32)0x00000007 << 20)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR01_OCDP_SEL                     16
#define DPI_MASK_ADR01_OCDP_SEL                      ((u32)0x00000007 << 16)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR02_OCDN_SEL                     12
#define DPI_MASK_ADR02_OCDN_SEL                      ((u32)0x00000007 << 12)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR02_OCDP_SEL                     8
#define DPI_MASK_ADR02_OCDP_SEL                      ((u32)0x00000007 << 8)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR03_OCDN_SEL                     4
#define DPI_MASK_ADR03_OCDN_SEL                      ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR03_OCDP_SEL                     0
#define DPI_MASK_ADR03_OCDP_SEL                      ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCD_SEL_1
 * @brief  OCD_SEL_1                                 (@ 0X208)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR04_OCDN_SEL                     28
#define DPI_MASK_ADR04_OCDN_SEL                      ((u32)0x00000007 << 28)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR04_OCDP_SEL                     24
#define DPI_MASK_ADR04_OCDP_SEL                      ((u32)0x00000007 << 24)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR05_OCDN_SEL                     20
#define DPI_MASK_ADR05_OCDN_SEL                      ((u32)0x00000007 << 20)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR05_OCDP_SEL                     16
#define DPI_MASK_ADR05_OCDP_SEL                      ((u32)0x00000007 << 16)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR06_OCDN_SEL                     12
#define DPI_MASK_ADR06_OCDN_SEL                      ((u32)0x00000007 << 12)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR06_OCDP_SEL                     8
#define DPI_MASK_ADR06_OCDP_SEL                      ((u32)0x00000007 << 8)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR07_OCDN_SEL                     4
#define DPI_MASK_ADR07_OCDN_SEL                      ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR07_OCDP_SEL                     0
#define DPI_MASK_ADR07_OCDP_SEL                      ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCD_SEL_2
 * @brief  OCD_SEL_2                                 (@ 0X20C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR08_OCDN_SEL                     28
#define DPI_MASK_ADR08_OCDN_SEL                      ((u32)0x00000007 << 28)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR08_OCDP_SEL                     24
#define DPI_MASK_ADR08_OCDP_SEL                      ((u32)0x00000007 << 24)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR09_OCDN_SEL                     20
#define DPI_MASK_ADR09_OCDN_SEL                      ((u32)0x00000007 << 20)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR09_OCDP_SEL                     16
#define DPI_MASK_ADR09_OCDP_SEL                      ((u32)0x00000007 << 16)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR10_OCDN_SEL                     12
#define DPI_MASK_ADR10_OCDN_SEL                      ((u32)0x00000007 << 12)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR10_OCDP_SEL                     8
#define DPI_MASK_ADR10_OCDP_SEL                      ((u32)0x00000007 << 8)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR11_OCDN_SEL                     4
#define DPI_MASK_ADR11_OCDN_SEL                      ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR11_OCDP_SEL                     0
#define DPI_MASK_ADR11_OCDP_SEL                      ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCD_SEL_3
 * @brief  OCD_SEL_3                                 (@ 0X210)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR12_OCDN_SEL                     28
#define DPI_MASK_ADR12_OCDN_SEL                      ((u32)0x00000007 << 28)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR12_OCDP_SEL                     24
#define DPI_MASK_ADR12_OCDP_SEL                      ((u32)0x00000007 << 24)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR13_OCDN_SEL                     20
#define DPI_MASK_ADR13_OCDN_SEL                      ((u32)0x00000007 << 20)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR13_OCDP_SEL                     16
#define DPI_MASK_ADR13_OCDP_SEL                      ((u32)0x00000007 << 16)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR14_OCDN_SEL                     12
#define DPI_MASK_ADR14_OCDN_SEL                      ((u32)0x00000007 << 12)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR14_OCDP_SEL                     8
#define DPI_MASK_ADR14_OCDP_SEL                      ((u32)0x00000007 << 8)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR15_OCDN_SEL                     4
#define DPI_MASK_ADR15_OCDN_SEL                      ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR15_OCDP_SEL                     0
#define DPI_MASK_ADR15_OCDP_SEL                      ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCD_SEL_4
 * @brief  OCD_SEL_4                                 (@ 0X214)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR16_OCDN_SEL                     28
#define DPI_MASK_ADR16_OCDN_SEL                      ((u32)0x00000007 << 28)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR16_OCDP_SEL                     24
#define DPI_MASK_ADR16_OCDP_SEL                      ((u32)0x00000007 << 24)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR_EXT_4_OCDN_SEL                 20
#define DPI_MASK_ADR_EXT_4_OCDN_SEL                  ((u32)0x00000007 << 20)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR_EXT_4_OCDP_SEL                 16
#define DPI_MASK_ADR_EXT_4_OCDP_SEL                  ((u32)0x00000007 << 16)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR_EXT_5_OCDN_SEL                 12
#define DPI_MASK_ADR_EXT_5_OCDN_SEL                  ((u32)0x00000007 << 12)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ADR_EXT_5_OCDP_SEL                 8
#define DPI_MASK_ADR_EXT_5_OCDP_SEL                  ((u32)0x00000007 << 8)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_BA0_OCDN_SEL                       4
#define DPI_MASK_BA0_OCDN_SEL                        ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_BA0_OCDP_SEL                       0
#define DPI_MASK_BA0_OCDP_SEL                        ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCD_SEL_5
 * @brief  OCD_SEL_5                                 (@ 0X218)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_BA1_OCDN_SEL                       28
#define DPI_MASK_BA1_OCDN_SEL                        ((u32)0x00000007 << 28)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_BA1_OCDP_SEL                       24
#define DPI_MASK_BA1_OCDP_SEL                        ((u32)0x00000007 << 24)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_BA2_OCDN_SEL                       20
#define DPI_MASK_BA2_OCDN_SEL                        ((u32)0x00000007 << 20)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_BA2_OCDP_SEL                       16
#define DPI_MASK_BA2_OCDP_SEL                        ((u32)0x00000007 << 16)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_RAS_OCDN_SEL                       12
#define DPI_MASK_RAS_OCDN_SEL                        ((u32)0x00000007 << 12)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_RAS_OCDP_SEL                       8
#define DPI_MASK_RAS_OCDP_SEL                        ((u32)0x00000007 << 8)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_CAS_OCDN_SEL                       4
#define DPI_MASK_CAS_OCDN_SEL                        ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_CAS_OCDP_SEL                       0
#define DPI_MASK_CAS_OCDP_SEL                        ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCD_SEL_6
 * @brief  OCD_SEL_6                                 (@ 0X21C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_WE_OCDN_SEL                        28
#define DPI_MASK_WE_OCDN_SEL                         ((u32)0x00000007 << 28)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_WE_OCDP_SEL                        24
#define DPI_MASK_WE_OCDP_SEL                         ((u32)0x00000007 << 24)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ODT_OCDN_SEL                       20
#define DPI_MASK_ODT_OCDN_SEL                        ((u32)0x00000007 << 20)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ODT_OCDP_SEL                       16
#define DPI_MASK_ODT_OCDP_SEL                        ((u32)0x00000007 << 16)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_RST_OCDN_SEL                       12
#define DPI_MASK_RST_OCDN_SEL                        ((u32)0x00000007 << 12)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_RST_OCDP_SEL                       8
#define DPI_MASK_RST_OCDP_SEL                        ((u32)0x00000007 << 8)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_PAR_OCDN_SEL                       4
#define DPI_MASK_PAR_OCDN_SEL                        ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_PAR_OCDP_SEL                       0
#define DPI_MASK_PAR_OCDP_SEL                        ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCD_SEL_7
 * @brief  OCD_SEL_7                                 (@ 0X220)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_PAR1_OCDN_SEL                      28
#define DPI_MASK_PAR1_OCDN_SEL                       ((u32)0x00000007 << 28)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_PAR1_OCDP_SEL                      24
#define DPI_MASK_PAR1_OCDP_SEL                       ((u32)0x00000007 << 24)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ACT_OCDN_SEL                       20
#define DPI_MASK_ACT_OCDN_SEL                        ((u32)0x00000007 << 20)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ACT_OCDP_SEL                       16
#define DPI_MASK_ACT_OCDP_SEL                        ((u32)0x00000007 << 16)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_DDR4_BG0_OCDN_SEL                  12
#define DPI_MASK_DDR4_BG0_OCDN_SEL                   ((u32)0x00000007 << 12)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_DDR4_BG0_OCDP_SEL                  8
#define DPI_MASK_DDR4_BG0_OCDP_SEL                   ((u32)0x00000007 << 8)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_TEN_OCDN_SEL                       4
#define DPI_MASK_TEN_OCDN_SEL                        ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_TEN_OCDP_SEL                       0
#define DPI_MASK_TEN_OCDP_SEL                        ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_OCD_SEL_8
 * @brief  OCD_SEL_8                                 (@ 0X224)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ALERT_OCDN_SEL                     28
#define DPI_MASK_ALERT_OCDN_SEL                      ((u32)0x00000007 << 28)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ALERT_OCDP_SEL                     24
#define DPI_MASK_ALERT_OCDP_SEL                      ((u32)0x00000007 << 24)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ALERT1_OCDN_SEL                    20
#define DPI_MASK_ALERT1_OCDN_SEL                     ((u32)0x00000007 << 20)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_ALERT1_OCDP_SEL                    16
#define DPI_MASK_ALERT1_OCDP_SEL                     ((u32)0x00000007 << 16)                             /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ODT_SEL_0
 * @brief  ODT_SEL_0                                 (@ 0X228)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CA_TTCN_SEL                        4
#define DPI_MASK_CA_TTCN_SEL                         ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_CA_TTCP_SEL                        0
#define DPI_MASK_CA_TTCP_SEL                         ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CKE_ODT_SEL
 * @brief  CKE_ODT_SEL                               (@ 0X22C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CKE_1_TTCN_SEL                     12
#define DPI_MASK_CKE_1_TTCN_SEL                      ((u32)0x00000007 << 12)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_CKE_1_TTCP_SEL                     8
#define DPI_MASK_CKE_1_TTCP_SEL                      ((u32)0x00000007 << 8)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_CKE_TTCN_SEL                       4
#define DPI_MASK_CKE_TTCN_SEL                        ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_CKE_TTCP_SEL                       0
#define DPI_MASK_CKE_TTCP_SEL                        ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_ODT_SEL
 * @brief  ADR_ODT_SEL                               (@ 0X230)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CS_1_TTCN_SEL                      28
#define DPI_MASK_CS_1_TTCN_SEL                       ((u32)0x00000007 << 28)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_CS_1_TTCP_SEL                      24
#define DPI_MASK_CS_1_TTCP_SEL                       ((u32)0x00000007 << 24)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_CS_TTCN_SEL                        12
#define DPI_MASK_CS_TTCN_SEL                         ((u32)0x00000007 << 12)                             /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_CS_TTCP_SEL                        8
#define DPI_MASK_CS_TTCP_SEL                         ((u32)0x00000007 << 8)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_RST_TTCN_SEL                       4
#define DPI_MASK_RST_TTCN_SEL                        ((u32)0x00000007 << 4)                              /*!<R/W 0x1  RSVD */
#define DPI_SHIFT_RST_TTCP_SEL                       0
#define DPI_MASK_RST_TTCP_SEL                        ((u32)0x00000007 << 0)                              /*!<R/W 0x1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CLK_ODT_SEL
 * @brief  CLK_ODT_SEL                               (@ 0X234)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CK_1_TTCN_SEL                      12
#define DPI_MASK_CK_1_TTCN_SEL                       ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CK_1_TTCP_SEL                      8
#define DPI_MASK_CK_1_TTCP_SEL                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CK_TTCN_SEL                        4
#define DPI_MASK_CK_TTCN_SEL                         ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CK_TTCP_SEL                        0
#define DPI_MASK_CK_TTCP_SEL                         ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DPI_CTRL_0
 * @brief  DPI_CTRL_0                                (@ 0X238)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_EN_CRC                             29
#define DPI_BIT_EN_CRC                               ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_2T_WR_PRE                          28
#define DPI_BIT_2T_WR_PRE                            ((u32)0x00000001 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DATA_PRE                           21
#define DPI_BIT_DATA_PRE                             ((u32)0x00000001 << 21)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DATA_INIT                          20
#define DPI_BIT_DATA_INIT                            ((u32)0x00000001 << 20)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_CAL_DQSEN_UPDATE_ENA               19
#define DPI_BIT_CAL_DQSEN_UPDATE_ENA                 ((u32)0x00000001 << 19)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_CAL_DQSEN_MODE                     17
#define DPI_MASK_CAL_DQSEN_MODE                      ((u32)0x00000003 << 17)                             /*!<R/W 0x3  RSVD */
#define DPI_SHIFT_2T_RD_PRE                          15
#define DPI_BIT_2T_RD_PRE                            ((u32)0x00000001 << 15)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_REF_CMD_SEL                        14
#define DPI_BIT_REF_CMD_SEL                          ((u32)0x00000001 << 14)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_REF_UPDATE_DLY                     8
#define DPI_MASK_REF_UPDATE_DLY                      ((u32)0x0000003F << 8)                              /*!<R/W 0x20  RSVD */
#define DPI_SHIFT_CAL_SET_MODE                       4
#define DPI_MASK_CAL_SET_MODE                        ((u32)0x00000003 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_RST_FIFO_MODE                      2
#define DPI_MASK_RST_FIFO_MODE                       ((u32)0x00000003 << 2)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_FW_SET_MODE                        0
#define DPI_MASK_FW_SET_MODE                         ((u32)0x00000003 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DPI_CTRL_1
 * @brief  DPI_CTRL_1                                (@ 0X23C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_WRITE_EN_4                         31
#define DPI_BIT_WRITE_EN_4                           ((u32)0x00000001 << 31)                             /*!<W 0  RSVD */
#define DPI_SHIFT_SET_REG_VALID                      30
#define DPI_BIT_SET_REG_VALID                        ((u32)0x00000001 << 30)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_3                         7
#define DPI_BIT_WRITE_EN_3                           ((u32)0x00000001 << 7)                              /*!<W 0  RSVD */
#define DPI_SHIFT_FW_SET_RD_DET                      6
#define DPI_BIT_FW_SET_RD_DET                        ((u32)0x00000001 << 6)                              /*!<W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_2                         5
#define DPI_BIT_WRITE_EN_2                           ((u32)0x00000001 << 5)                              /*!<W 0  RSVD */
#define DPI_SHIFT_FW_SET_CAL_RANGE                   4
#define DPI_BIT_FW_SET_CAL_RANGE                     ((u32)0x00000001 << 4)                              /*!<W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_1                         3
#define DPI_BIT_WRITE_EN_1                           ((u32)0x00000001 << 3)                              /*!<W 0  RSVD */
#define DPI_SHIFT_FW_SET_RD_DLY                      2
#define DPI_BIT_FW_SET_RD_DLY                        ((u32)0x00000001 << 2)                              /*!<W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_0                         1
#define DPI_BIT_WRITE_EN_0                           ((u32)0x00000001 << 1)                              /*!<W 0  RSVD */
#define DPI_SHIFT_FW_SET_WR_DLY                      0
#define DPI_BIT_FW_SET_WR_DLY                        ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DPI_CTRL_2
 * @brief  DPI_CTRL_2                                (@ 0X240)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RST_DQSEN_CAL                      31
#define DPI_BIT_RST_DQSEN_CAL                        ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_SET_REG_VALID_MODE                 28
#define DPI_BIT_SET_REG_VALID_MODE                   ((u32)0x00000001 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RST_3POINT_MODE                    26
#define DPI_MASK_RST_3POINT_MODE                     ((u32)0x00000003 << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RST_DQSEN_MODE                     24
#define DPI_MASK_RST_DQSEN_MODE                      ((u32)0x00000003 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ALERT_ENA                          23
#define DPI_BIT_ALERT_ENA                            ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ALERT_1_ENA                        22
#define DPI_BIT_ALERT_1_ENA                          ((u32)0x00000001 << 22)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RD_UPDATE_DLY                      16
#define DPI_MASK_RD_UPDATE_DLY                       ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RD_UPDATE_DLY_RX                   8
#define DPI_MASK_RD_UPDATE_DLY_RX                    ((u32)0x0000001F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_PWROFF_CMD_GATE                    4
#define DPI_MASK_PWROFF_CMD_GATE                     ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_DELAY_SEL                       1
#define DPI_MASK_CS_DELAY_SEL                        ((u32)0x00000007 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_DELAY_EN                        0
#define DPI_BIT_CS_DELAY_EN                          ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_INT_CTRL
 * @brief  INT_CTRL                                (@ 0X254)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_WRITE_EN_14                        29
#define DPI_BIT_WRITE_EN_14                          ((u32)0x00000001 << 29)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_DQS_BURST_ERR_EN               28
#define DPI_BIT_INT_DQS_BURST_ERR_EN                 ((u32)0x00000001 << 28)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_13                        27
#define DPI_BIT_WRITE_EN_13                          ((u32)0x00000001 << 27)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_TM_DQSEN_EN                    26
#define DPI_BIT_INT_TM_DQSEN_EN                      ((u32)0x00000001 << 26)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_12                        25
#define DPI_BIT_WRITE_EN_12                          ((u32)0x00000001 << 25)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_FIFO_PTR_EN                    24
#define DPI_BIT_INT_FIFO_PTR_EN                      ((u32)0x00000001 << 24)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_11                        23
#define DPI_BIT_WRITE_EN_11                          ((u32)0x00000001 << 23)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_ZQ_EN                          22
#define DPI_BIT_INT_ZQ_EN                            ((u32)0x00000001 << 22)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_8                         17
#define DPI_BIT_WRITE_EN_8                           ((u32)0x00000001 << 17)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_ALERT_EN                       16
#define DPI_BIT_INT_ALERT_EN                         ((u32)0x00000001 << 16)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_7                         15
#define DPI_BIT_WRITE_EN_7                           ((u32)0x00000001 << 15)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_PLL_EN                         14
#define DPI_BIT_INT_PLL_EN                           ((u32)0x00000001 << 14)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_6                         13
#define DPI_BIT_WRITE_EN_6                           ((u32)0x00000001 << 13)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_CPU_3_EN                       12
#define DPI_BIT_INT_CPU_3_EN                         ((u32)0x00000001 << 12)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_5                         11
#define DPI_BIT_WRITE_EN_5                           ((u32)0x00000001 << 11)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_CPU_2_EN                       10
#define DPI_BIT_INT_CPU_2_EN                         ((u32)0x00000001 << 10)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_4                         9
#define DPI_BIT_WRITE_EN_4                           ((u32)0x00000001 << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_CPU_1_EN                       8
#define DPI_BIT_INT_CPU_1_EN                         ((u32)0x00000001 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_3                         7
#define DPI_BIT_WRITE_EN_3                           ((u32)0x00000001 << 7)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_CPU_0_EN                       6
#define DPI_BIT_INT_CPU_0_EN                         ((u32)0x00000001 << 6)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_2                         5
#define DPI_BIT_WRITE_EN_2                           ((u32)0x00000001 << 5)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_FW_CLR_DQS_INT                     4
#define DPI_BIT_FW_CLR_DQS_INT                       ((u32)0x00000001 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_1                         3
#define DPI_BIT_WRITE_EN_1                           ((u32)0x00000001 << 3)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_INT_CAL_BDY_EN                     2
#define DPI_BIT_INT_CAL_BDY_EN                       ((u32)0x00000001 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_WRITE_EN_0                         1
#define DPI_BIT_WRITE_EN_0                           ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_EN                             0
#define DPI_BIT_DQS_EN                               ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_INT_STATUS_0
 * @brief  INT_STATUS_0                                (@ 0X258)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_BURST_ERR_INT_3                15
#define DPI_BIT_DQS_BURST_ERR_INT_3                  ((u32)0x00000001 << 15)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_BURST_ERR_INT_2                14
#define DPI_BIT_DQS_BURST_ERR_INT_2                  ((u32)0x00000001 << 14)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_BURST_ERR_INT_1                13
#define DPI_BIT_DQS_BURST_ERR_INT_1                  ((u32)0x00000001 << 13)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_BURST_ERR_INT_0                12
#define DPI_BIT_DQS_BURST_ERR_INT_0                  ((u32)0x00000001 << 12)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQSEN_EARLY_INT_3               11
#define DPI_BIT_TM_DQSEN_EARLY_INT_3                 ((u32)0x00000001 << 11)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQSEN_EARLY_INT_2               10
#define DPI_BIT_TM_DQSEN_EARLY_INT_2                 ((u32)0x00000001 << 10)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQSEN_EARLY_INT_1               9
#define DPI_BIT_TM_DQSEN_EARLY_INT_1                 ((u32)0x00000001 << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQSEN_EARLY_INT_0               8
#define DPI_BIT_TM_DQSEN_EARLY_INT_0                 ((u32)0x00000001 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQSEN_LATE_INT_3                7
#define DPI_BIT_TM_DQSEN_LATE_INT_3                  ((u32)0x00000001 << 7)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQSEN_LATE_INT_2                6
#define DPI_BIT_TM_DQSEN_LATE_INT_2                  ((u32)0x00000001 << 6)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQSEN_LATE_INT_1                5
#define DPI_BIT_TM_DQSEN_LATE_INT_1                  ((u32)0x00000001 << 5)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQSEN_LATE_INT_0                4
#define DPI_BIT_TM_DQSEN_LATE_INT_0                  ((u32)0x00000001 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_INT_3                          3
#define DPI_BIT_DQS_INT_3                            ((u32)0x00000001 << 3)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_INT_2                          2
#define DPI_BIT_DQS_INT_2                            ((u32)0x00000001 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_INT_1                          1
#define DPI_BIT_DQS_INT_1                            ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_INT_0                          0
#define DPI_BIT_DQS_INT_0                            ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CS_EMPH_CTRL
 * @brief  CS_EMPH_CTRL                              (@ 0X298)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CS1_SLEWRATE                       29
#define DPI_BIT_CS1_SLEWRATE                         ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS1_DLY_EMPH                       24
#define DPI_MASK_CS1_DLY_EMPH                        ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS1_EN_EMPHN                       20
#define DPI_MASK_CS1_EN_EMPHN                        ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CS1_EN_EMPHP                       16
#define DPI_MASK_CS1_EN_EMPHP                        ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CS_SLEWRATE                        12
#define DPI_MASK_CS_SLEWRATE                         ((u32)0x00000003 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_DLY_EMPH                        8
#define DPI_MASK_CS_DLY_EMPH                         ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CS_EN_EMPHN                        4
#define DPI_MASK_CS_EN_EMPHN                         ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CS_EN_EMPHP                        0
#define DPI_MASK_CS_EN_EMPHP                         ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CS_SEL_EMPH_CTL
 * @brief  CS_SEL_EMPH_CTL                           (@ 0X29C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CS1_SEL_EMPHN                      20
#define DPI_MASK_CS1_SEL_EMPHN                       ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CS1_SEL_EMPHP                      16
#define DPI_MASK_CS1_SEL_EMPHP                       ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CS_SEL_EMPHN                       4
#define DPI_MASK_CS_SEL_EMPHN                        ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CS_SEL_EMPHP                       0
#define DPI_MASK_CS_SEL_EMPHP                        ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DDR4_CS_EMPH_CTL
 * @brief  DDR4_CS_EMPH_CTL                          (@ 0X2A0)
 * @{
 *****************************************************************************/
#define DPI_DDR4_SHIFT_CS_SEL_EMPHN                       20
#define DPI_DDR4_MASK_CS_SEL_EMPHN                        ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_DDR4_SHIFT_CS_SEL_EMPHP                       16
#define DPI_DDR4_MASK_CS_SEL_EMPHP                        ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_DDR4_SHIFT_CS_SLEWRATE                        12
#define DPI_DDR4_MASK_CS_SLEWRATE                         ((u32)0x00000003 << 12)                             /*!<R/W 0  RSVD */
#define DPI_DDR4_SHIFT_CS_DLY_EMPH                        8
#define DPI_DDR4_MASK_CS_DLY_EMPH                         ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_DDR4_SHIFT_CS_EN_EMPHN                        4
#define DPI_DDR4_MASK_CS_EN_EMPHN                         ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_DDR4_SHIFT_CS_EN_EMPHP                        0
#define DPI_DDR4_MASK_CS_EN_EMPHP                         ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CK_EMPH_CTL
 * @brief  CK_EMPH_CTL                               (@ 0X2A4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CK1_SLEWRATE                       29
#define DPI_BIT_CK1_SLEWRATE                         ((u32)0x00000001 << 29)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CK1_DLY_EMPH                       24
#define DPI_MASK_CK1_DLY_EMPH                        ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CK1_EN_EMPHN                       20
#define DPI_MASK_CK1_EN_EMPHN                        ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CK1_EN_EMPHP                       16
#define DPI_MASK_CK1_EN_EMPHP                        ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CK_SLEWRATE                        12
#define DPI_MASK_CK_SLEWRATE                         ((u32)0x00000003 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CK_DLY_EMPH                        8
#define DPI_MASK_CK_DLY_EMPH                         ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CK_EN_EMPHN                        4
#define DPI_MASK_CK_EN_EMPHN                         ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CK_EN_EMPHP                        0
#define DPI_MASK_CK_EN_EMPHP                         ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CK_SEL_EMPH_CTL
 * @brief  CK_SEL_EMPH_CTL                           (@ 0X2A8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CK1_SEL_EMPHN                      20
#define DPI_MASK_CK1_SEL_EMPHN                       ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CK1_SEL_EMPHP                      16
#define DPI_MASK_CK1_SEL_EMPHP                       ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CK_SEL_EMPHN                       4
#define DPI_MASK_CK_SEL_EMPHN                        ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_CK_SEL_EMPHP                       0
#define DPI_MASK_CK_SEL_EMPHP                        ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_EMPH_CTL_0
 * @brief  ADR_EMPH_CTL_0                            (@ 0X2AC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR_SLEWRATE_1                     28
#define DPI_MASK_ADR_SLEWRATE_1                      ((u32)0x00000003 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR_DLY_EMPH_1                     24
#define DPI_MASK_ADR_DLY_EMPH_1                      ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR_EN_EMPHN_1                     20
#define DPI_MASK_ADR_EN_EMPHN_1                      ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_EN_EMPHP_1                     16
#define DPI_MASK_ADR_EN_EMPHP_1                      ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_SLEWRATE_0                     12
#define DPI_MASK_ADR_SLEWRATE_0                      ((u32)0x00000003 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR_DLY_EMPH_0                     8
#define DPI_MASK_ADR_DLY_EMPH_0                      ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR_EN_EMPHN_0                     4
#define DPI_MASK_ADR_EN_EMPHN_0                      ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_EN_EMPHP_0                     0
#define DPI_MASK_ADR_EN_EMPHP_0                      ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_EMPH_CTL_1
 * @brief  ADR_EMPH_CTL_1                            (@ 0X2B0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR_SLEWRATE_1                     28
#define DPI_MASK_ADR_SLEWRATE_1                      ((u32)0x00000003 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR_DLY_EMPH_1                     24
#define DPI_MASK_ADR_DLY_EMPH_1                      ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR_EN_EMPHN_1                     20
#define DPI_MASK_ADR_EN_EMPHN_1                      ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_EN_EMPHP_1                     16
#define DPI_MASK_ADR_EN_EMPHP_1                      ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_SLEWRATE_0                     12
#define DPI_MASK_ADR_SLEWRATE_0                      ((u32)0x00000003 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR_DLY_EMPH_0                     8
#define DPI_MASK_ADR_DLY_EMPH_0                      ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ADR_EN_EMPHN_0                     4
#define DPI_MASK_ADR_EN_EMPHN_0                      ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_EN_EMPHP_0                     0
#define DPI_MASK_ADR_EN_EMPHP_0                      ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_SEL_EMPH_CTL_0
 * @brief  ADR_SEL_EMPH_CTL_0                        (@ 0X2B4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR_SEL_EMPHN_1                    20
#define DPI_MASK_ADR_SEL_EMPHN_1                     ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_SEL_EMPHP_1                    16
#define DPI_MASK_ADR_SEL_EMPHP_1                     ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_SEL_EMPHN_0                    4
#define DPI_MASK_ADR_SEL_EMPHN_0                     ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_SEL_EMPHP_0                    0
#define DPI_MASK_ADR_SEL_EMPHP_0                     ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_SEL_EMPH_CTL_1
 * @brief  ADR_SEL_EMPH_CTL_1                        (@ 0X2B8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ADR_SEL_EMPHN_1                    20
#define DPI_MASK_ADR_SEL_EMPHN_1                     ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_SEL_EMPHP_1                    16
#define DPI_MASK_ADR_SEL_EMPHP_1                     ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_SEL_EMPHN_0                    4
#define DPI_MASK_ADR_SEL_EMPHN_0                     ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_ADR_SEL_EMPHP_0                    0
#define DPI_MASK_ADR_SEL_EMPHP_0                     ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_EMPH_SEL_0
 * @brief  ADR_EMPH_SEL_0                            (@ 0X2BC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_A15_EMPH_SEL                       30
#define DPI_MASK_A15_EMPH_SEL                        ((u32)0x00000003 << 30)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A14_EMPH_SEL                       28
#define DPI_MASK_A14_EMPH_SEL                        ((u32)0x00000003 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A13_EMPH_SEL                       26
#define DPI_MASK_A13_EMPH_SEL                        ((u32)0x00000003 << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A12_EMPH_SEL                       24
#define DPI_MASK_A12_EMPH_SEL                        ((u32)0x00000003 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A11_EMPH_SEL                       22
#define DPI_MASK_A11_EMPH_SEL                        ((u32)0x00000003 << 22)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A10_EMPH_SEL                       20
#define DPI_MASK_A10_EMPH_SEL                        ((u32)0x00000003 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A9_EMPH_SEL                        18
#define DPI_MASK_A9_EMPH_SEL                         ((u32)0x00000003 << 18)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A8_EMPH_SEL                        16
#define DPI_MASK_A8_EMPH_SEL                         ((u32)0x00000003 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A7_EMPH_SEL                        14
#define DPI_MASK_A7_EMPH_SEL                         ((u32)0x00000003 << 14)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A6_EMPH_SEL                        12
#define DPI_MASK_A6_EMPH_SEL                         ((u32)0x00000003 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A5_EMPH_SEL                        10
#define DPI_MASK_A5_EMPH_SEL                         ((u32)0x00000003 << 10)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_A4_EMPH_SEL                        8
#define DPI_MASK_A4_EMPH_SEL                         ((u32)0x00000003 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_A3_EMPH_SEL                        6
#define DPI_MASK_A3_EMPH_SEL                         ((u32)0x00000003 << 6)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_A2_EMPH_SEL                        4
#define DPI_MASK_A2_EMPH_SEL                         ((u32)0x00000003 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_A1_EMPH_SEL                        2
#define DPI_MASK_A1_EMPH_SEL                         ((u32)0x00000003 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_A0_EMPH_SEL                        0
#define DPI_MASK_A0_EMPH_SEL                         ((u32)0x00000003 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_EMPH_SEL_1
 * @brief  ADR_EMPH_SEL_1                            (@ 0X2C0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ACT_EMPH_SEL                       30
#define DPI_MASK_ACT_EMPH_SEL                        ((u32)0x00000003 << 30)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RST_EMPH_SEL                       28
#define DPI_MASK_RST_EMPH_SEL                        ((u32)0x00000003 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_WE_EMPH_SEL                        26
#define DPI_MASK_WE_EMPH_SEL                         ((u32)0x00000003 << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RAS_EMPH_SEL                       24
#define DPI_MASK_RAS_EMPH_SEL                        ((u32)0x00000003 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_PAR1_EMPH_SEL                      22
#define DPI_MASK_PAR1_EMPH_SEL                       ((u32)0x00000003 << 22)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_PAR_EMPH_SEL                       20
#define DPI_MASK_PAR_EMPH_SEL                        ((u32)0x00000003 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_EMPH_SEL                       18
#define DPI_MASK_ODT_EMPH_SEL                        ((u32)0x00000003 << 18)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE1_EMPH_SEL                      16
#define DPI_MASK_CKE1_EMPH_SEL                       ((u32)0x00000003 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CKE_EMPH_SEL                       14
#define DPI_MASK_CKE_EMPH_SEL                        ((u32)0x00000003 << 14)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAS_EMPH_SEL                       12
#define DPI_MASK_CAS_EMPH_SEL                        ((u32)0x00000003 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_BA2_EMPH_SEL                       10
#define DPI_MASK_BA2_EMPH_SEL                        ((u32)0x00000003 << 10)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_BA1_EMPH_SEL                       8
#define DPI_MASK_BA1_EMPH_SEL                        ((u32)0x00000003 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_BA0_EMPH_SEL                       6
#define DPI_MASK_BA0_EMPH_SEL                        ((u32)0x00000003 << 6)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_AD1_5_EMPH_SEL                     4
#define DPI_MASK_AD1_5_EMPH_SEL                      ((u32)0x00000003 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_AD1_4_EMPH_SEL                     2
#define DPI_MASK_AD1_4_EMPH_SEL                      ((u32)0x00000003 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_A16_EMPH_SEL                       0
#define DPI_MASK_A16_EMPH_SEL                        ((u32)0x00000003 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_ADR_EMPH_SEL_2
 * @brief  ADR_EMPH_SEL_2                            (@ 0X2C4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ALERT1_EMPH_SEL                    8
#define DPI_MASK_ALERT1_EMPH_SEL                     ((u32)0x00000003 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ALERT_EMPH_SEL                     6
#define DPI_MASK_ALERT_EMPH_SEL                      ((u32)0x00000003 << 6)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DDR4_TEN_EMPH_SEL                  4
#define DPI_MASK_DDR4_TEN_EMPH_SEL                   ((u32)0x00000003 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DDR4_CKE_EMPH_SEL                  2
#define DPI_MASK_DDR4_CKE_EMPH_SEL                   ((u32)0x00000003 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DDR4_BG0_EMPH_SEL                  0
#define DPI_MASK_DDR4_BG0_EMPH_SEL                   ((u32)0x00000003 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_CTRL_ZPROG
 * @brief  PAD_CTRL_ZPROG                            (@ 0X2E8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZPROG_3                            24
#define DPI_MASK_ZPROG_3                             ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_2                            16
#define DPI_MASK_ZPROG_2                             ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_1                            8
#define DPI_MASK_ZPROG_1                             ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_0                            0
#define DPI_MASK_ZPROG_0                             ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_CTRL_ZPROG_1
 * @brief  PAD_CTRL_ZPROG_1                          (@ 0X2EC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZPROG_3                            24
#define DPI_MASK_ZPROG_3                             ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_2                            16
#define DPI_MASK_ZPROG_2                             ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_1                            8
#define DPI_MASK_ZPROG_1                             ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_0                            0
#define DPI_MASK_ZPROG_0                             ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_CTRL_ZPROG_2
 * @brief  PAD_CTRL_ZPROG_2                          (@ 0X2F0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZPROG_3                            24
#define DPI_MASK_ZPROG_3                             ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_2                            16
#define DPI_MASK_ZPROG_2                             ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_1                            8
#define DPI_MASK_ZPROG_1                             ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_0                            0
#define DPI_MASK_ZPROG_0                             ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_CTRL_ZPROG_3
 * @brief  PAD_CTRL_ZPROG_3                          (@ 0X2F4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZPROG_3                            24
#define DPI_MASK_ZPROG_3                             ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_2                            16
#define DPI_MASK_ZPROG_2                             ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_1                            8
#define DPI_MASK_ZPROG_1                             ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_0                            0
#define DPI_MASK_ZPROG_0                             ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_CTRL_ZPROG_4
 * @brief  PAD_CTRL_ZPROG_4                          (@ 0X2F8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZPROG_3                            24
#define DPI_MASK_ZPROG_3                             ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_2                            16
#define DPI_MASK_ZPROG_2                             ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_1                            8
#define DPI_MASK_ZPROG_1                             ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_0                            0
#define DPI_MASK_ZPROG_0                             ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_CTRL_ZPROG_5
 * @brief  PAD_CTRL_ZPROG_5                          (@ 0X2FC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZPROG_3                            24
#define DPI_MASK_ZPROG_3                             ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_2                            16
#define DPI_MASK_ZPROG_2                             ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_1                            8
#define DPI_MASK_ZPROG_1                             ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_0                            0
#define DPI_MASK_ZPROG_0                             ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_CTRL_ZPROG_6
 * @brief  PAD_CTRL_ZPROG_6                          (@ 0X300)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZPROG_3                            24
#define DPI_MASK_ZPROG_3                             ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_2                            16
#define DPI_MASK_ZPROG_2                             ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_1                            8
#define DPI_MASK_ZPROG_1                             ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_0                            0
#define DPI_MASK_ZPROG_0                             ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_CTRL_ZPROG_7
 * @brief  PAD_CTRL_ZPROG_7                          (@ 0X304)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_ZPROG_3                            24
#define DPI_MASK_ZPROG_3                             ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_2                            16
#define DPI_MASK_ZPROG_2                             ((u32)0x0000003F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_1                            8
#define DPI_MASK_ZPROG_1                             ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_ZPROG_0                            0
#define DPI_MASK_ZPROG_0                             ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_NOCD2_ZPROG
 * @brief  PAD_NOCD2_ZPROG                           (@ 0X308)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_NOCD2_ZPROG_1                      8
#define DPI_MASK_NOCD2_ZPROG_1                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_NOCD2_ZPROG_0                      0
#define DPI_MASK_NOCD2_ZPROG_0                       ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_NOCD2_ZPROG_1
 * @brief  PAD_NOCD2_ZPROG_1                         (@ 0X30C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_NOCD2_ZPROG_1                      8
#define DPI_MASK_NOCD2_ZPROG_1                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_NOCD2_ZPROG_0                      0
#define DPI_MASK_NOCD2_ZPROG_0                       ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_NOCD2_ZPROG_2
 * @brief  PAD_NOCD2_ZPROG_2                         (@ 0X310)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_NOCD2_ZPROG_1                      8
#define DPI_MASK_NOCD2_ZPROG_1                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_NOCD2_ZPROG_0                      0
#define DPI_MASK_NOCD2_ZPROG_0                       ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_NOCD2_ZPROG_3
 * @brief  PAD_NOCD2_ZPROG_3                         (@ 0X314)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_NOCD2_ZPROG_1                      8
#define DPI_MASK_NOCD2_ZPROG_1                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_NOCD2_ZPROG_0                      0
#define DPI_MASK_NOCD2_ZPROG_0                       ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_NOCD2_ZPROG_4
 * @brief  PAD_NOCD2_ZPROG_4                         (@ 0X318)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_NOCD2_ZPROG_1                      8
#define DPI_MASK_NOCD2_ZPROG_1                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_NOCD2_ZPROG_0                      0
#define DPI_MASK_NOCD2_ZPROG_0                       ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_NOCD2_ZPROG_5
 * @brief  PAD_NOCD2_ZPROG_5                         (@ 0X31C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_NOCD2_ZPROG_1                      8
#define DPI_MASK_NOCD2_ZPROG_1                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_NOCD2_ZPROG_0                      0
#define DPI_MASK_NOCD2_ZPROG_0                       ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_NOCD2_ZPROG_6
 * @brief  PAD_NOCD2_ZPROG_6                         (@ 0X320)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_NOCD2_ZPROG_1                      8
#define DPI_MASK_NOCD2_ZPROG_1                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_NOCD2_ZPROG_0                      0
#define DPI_MASK_NOCD2_ZPROG_0                       ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PAD_NOCD2_ZPROG_7
 * @brief  PAD_NOCD2_ZPROG_7                         (@ 0X324)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_NOCD2_ZPROG_1                      8
#define DPI_MASK_NOCD2_ZPROG_1                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_NOCD2_ZPROG_0                      0
#define DPI_MASK_NOCD2_ZPROG_0                       ((u32)0x0000003F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_OCD_SEL2_0
 * @brief  DQ_OCD_SEL2_0                             (@ 0X328)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_7_OCDN_SEL                      28
#define DPI_MASK_DQ_7_OCDN_SEL                       ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_6_OCDN_SEL                      24
#define DPI_MASK_DQ_6_OCDN_SEL                       ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_7_OCDP_SEL                      20
#define DPI_MASK_DQ_7_OCDP_SEL                       ((u32)0x00000007 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_6_OCDP_SEL                      16
#define DPI_MASK_DQ_6_OCDP_SEL                       ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_5_OCDN_SEL                      12
#define DPI_MASK_DQ_5_OCDN_SEL                       ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_4_OCDN_SEL                      8
#define DPI_MASK_DQ_4_OCDN_SEL                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_5_OCDP_SEL                      4
#define DPI_MASK_DQ_5_OCDP_SEL                       ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_4_OCDP_SEL                      0
#define DPI_MASK_DQ_4_OCDP_SEL                       ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_OCD_SEL2_1
 * @brief  DQ_OCD_SEL2_1                             (@ 0X32C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_7_OCDN_SEL                      28
#define DPI_MASK_DQ_7_OCDN_SEL                       ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_6_OCDN_SEL                      24
#define DPI_MASK_DQ_6_OCDN_SEL                       ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_7_OCDP_SEL                      20
#define DPI_MASK_DQ_7_OCDP_SEL                       ((u32)0x00000007 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_6_OCDP_SEL                      16
#define DPI_MASK_DQ_6_OCDP_SEL                       ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_5_OCDN_SEL                      12
#define DPI_MASK_DQ_5_OCDN_SEL                       ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_4_OCDN_SEL                      8
#define DPI_MASK_DQ_4_OCDN_SEL                       ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_5_OCDP_SEL                      4
#define DPI_MASK_DQ_5_OCDP_SEL                       ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_4_OCDP_SEL                      0
#define DPI_MASK_DQ_4_OCDP_SEL                       ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_OCD_SEL2_0
 * @brief  DQS_OCD_SEL2_0                            (@ 0X330)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_7_OCDN_SEL                     28
#define DPI_MASK_DQS_7_OCDN_SEL                      ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_6_OCDN_SEL                     24
#define DPI_MASK_DQS_6_OCDN_SEL                      ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_7_OCDP_SEL                     20
#define DPI_MASK_DQS_7_OCDP_SEL                      ((u32)0x00000007 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_6_OCDP_SEL                     16
#define DPI_MASK_DQS_6_OCDP_SEL                      ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_5_OCDN_SEL                     12
#define DPI_MASK_DQS_5_OCDN_SEL                      ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_4_OCDN_SEL                     8
#define DPI_MASK_DQS_4_OCDN_SEL                      ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_5_OCDP_SEL                     4
#define DPI_MASK_DQS_5_OCDP_SEL                      ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_4_OCDP_SEL                     0
#define DPI_MASK_DQS_4_OCDP_SEL                      ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_OCD_SEL2_1
 * @brief  DQS_OCD_SEL2_1                            (@ 0X334)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_7_OCDN_SEL                     28
#define DPI_MASK_DQS_7_OCDN_SEL                      ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_6_OCDN_SEL                     24
#define DPI_MASK_DQS_6_OCDN_SEL                      ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_7_OCDP_SEL                     20
#define DPI_MASK_DQS_7_OCDP_SEL                      ((u32)0x00000007 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_6_OCDP_SEL                     16
#define DPI_MASK_DQS_6_OCDP_SEL                      ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_5_OCDN_SEL                     12
#define DPI_MASK_DQS_5_OCDN_SEL                      ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_4_OCDN_SEL                     8
#define DPI_MASK_DQS_4_OCDN_SEL                      ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_5_OCDP_SEL                     4
#define DPI_MASK_DQS_5_OCDP_SEL                      ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_4_OCDP_SEL                     0
#define DPI_MASK_DQS_4_OCDP_SEL                      ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL2
 * @brief  READ_CTRL2                                (@ 0X408)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_EN_ODT_3_STG                       24
#define DPI_BIT_EN_ODT_3_STG                         ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_FORCE_SEL                      23
#define DPI_BIT_ODT_FORCE_SEL                        ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_FORCE_SIG                      22
#define DPI_BIT_ODT_FORCE_SIG                        ((u32)0x00000001 << 22)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_ODT_EN_ODD                      3
#define DPI_BIT_TM_ODT_EN_ODD                        ((u32)0x00000001 << 3)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_TM_ODT_EN_SEL                      1
#define DPI_MASK_TM_ODT_EN_SEL                       ((u32)0x00000003 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_ODT_EN_DLY                      0
#define DPI_BIT_TM_ODT_EN_DLY                        ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL2_1
 * @brief  READ_CTRL2_1                              (@ 0X40C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_EN_ODT_3_STG                       24
#define DPI_BIT_EN_ODT_3_STG                         ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_FORCE_SEL                      23
#define DPI_BIT_ODT_FORCE_SEL                        ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_ODT_FORCE_SIG                      22
#define DPI_BIT_ODT_FORCE_SIG                        ((u32)0x00000001 << 22)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_ODT_EN_ODD                      3
#define DPI_BIT_TM_ODT_EN_ODD                        ((u32)0x00000001 << 3)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_TM_ODT_EN_SEL                      1
#define DPI_MASK_TM_ODT_EN_SEL                       ((u32)0x00000003 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_ODT_EN_DLY                      0
#define DPI_BIT_TM_ODT_EN_DLY                        ((u32)0x00000001 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL3
 * @brief  READ_CTRL3                                (@ 0X410)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQSEN_CAL_OFFSET4                  25
#define DPI_BIT_DQSEN_CAL_OFFSET4                    ((u32)0x00000001 << 25)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQSEN_DQS_INV                      24
#define DPI_BIT_DQSEN_DQS_INV                        ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_MCK_RX_INV_SEL                     23
#define DPI_BIT_MCK_RX_INV_SEL                       ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQSEN_CAL_SEL                      22
#define DPI_BIT_DQSEN_CAL_SEL                        ((u32)0x00000001 << 22)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_EARLY_SEL                      21
#define DPI_BIT_DQS_EARLY_SEL                        ((u32)0x00000001 << 21)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQS_CAL_PRE                     16
#define DPI_MASK_TM_DQS_CAL_PRE                      ((u32)0x0000001F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQSEN_EARLY_PH                  8
#define DPI_MASK_TM_DQSEN_EARLY_PH                   ((u32)0x0000003F << 8)                              /*!<R/W 0xB  RSVD */
#define DPI_SHIFT_TM_DQSEN_LATE_PH                   0
#define DPI_MASK_TM_DQSEN_LATE_PH                    ((u32)0x0000003F << 0)                              /*!<R/W 0xB  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL3_1
 * @brief  READ_CTRL3_1                              (@ 0X414)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQSEN_CAL_OFFSET4                  25
#define DPI_BIT_DQSEN_CAL_OFFSET4                    ((u32)0x00000001 << 25)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQSEN_DQS_INV                      24
#define DPI_BIT_DQSEN_DQS_INV                        ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_MCK_RX_INV_SEL                     23
#define DPI_BIT_MCK_RX_INV_SEL                       ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQSEN_CAL_SEL                      22
#define DPI_BIT_DQSEN_CAL_SEL                        ((u32)0x00000001 << 22)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_EARLY_SEL                      21
#define DPI_BIT_DQS_EARLY_SEL                        ((u32)0x00000001 << 21)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQS_CAL_PRE                     16
#define DPI_MASK_TM_DQS_CAL_PRE                      ((u32)0x0000001F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQSEN_EARLY_PH                  8
#define DPI_MASK_TM_DQSEN_EARLY_PH                   ((u32)0x0000003F << 8)                              /*!<R/W 0xB  RSVD */
#define DPI_SHIFT_TM_DQSEN_LATE_PH                   0
#define DPI_MASK_TM_DQSEN_LATE_PH                    ((u32)0x0000003F << 0)                              /*!<R/W 0xB  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL6
 * @brief  READ_CTRL6                                (@ 0X418)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_TM_ODT_EN                          0
#define DPI_MASK_TM_ODT_EN                           ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0xFE  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL6_1
 * @brief  READ_CTRL6_1                              (@ 0X41C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_TM_ODT_EN                          0
#define DPI_MASK_TM_ODT_EN                           ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0xFE  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY0
 * @brief  DQS_IN_DLY0                               (@ 0X420)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_3                24
#define DPI_MASK_FW_RD_DLY_POS_SEL_3                 ((u32)0x0000001F << 24)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_2                16
#define DPI_MASK_FW_RD_DLY_POS_SEL_2                 ((u32)0x0000001F << 16)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_1                8
#define DPI_MASK_FW_RD_DLY_POS_SEL_1                 ((u32)0x0000001F << 8)                              /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_0                0
#define DPI_MASK_FW_RD_DLY_POS_SEL_0                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY0_1
 * @brief  DQS_IN_DLY0_1                             (@ 0X424)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_3                24
#define DPI_MASK_FW_RD_DLY_POS_SEL_3                 ((u32)0x0000001F << 24)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_2                16
#define DPI_MASK_FW_RD_DLY_POS_SEL_2                 ((u32)0x0000001F << 16)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_1                8
#define DPI_MASK_FW_RD_DLY_POS_SEL_1                 ((u32)0x0000001F << 8)                              /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_0                0
#define DPI_MASK_FW_RD_DLY_POS_SEL_0                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY1
 * @brief  DQS_IN_DLY1                               (@ 0X428)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_7                24
#define DPI_MASK_FW_RD_DLY_POS_SEL_7                 ((u32)0x0000001F << 24)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_6                16
#define DPI_MASK_FW_RD_DLY_POS_SEL_6                 ((u32)0x0000001F << 16)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_5                8
#define DPI_MASK_FW_RD_DLY_POS_SEL_5                 ((u32)0x0000001F << 8)                              /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_4                0
#define DPI_MASK_FW_RD_DLY_POS_SEL_4                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY1_1
 * @brief  DQS_IN_DLY1_1                             (@ 0X42C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_7                24
#define DPI_MASK_FW_RD_DLY_POS_SEL_7                 ((u32)0x0000001F << 24)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_6                16
#define DPI_MASK_FW_RD_DLY_POS_SEL_6                 ((u32)0x0000001F << 16)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_5                8
#define DPI_MASK_FW_RD_DLY_POS_SEL_5                 ((u32)0x0000001F << 8)                              /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_4                0
#define DPI_MASK_FW_RD_DLY_POS_SEL_4                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY1_DBI
 * @brief  DQS_IN_DLY1_DBI                           (@ 0X430)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_8                0
#define DPI_MASK_FW_RD_DLY_POS_SEL_8                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY1_DBI_1
 * @brief  DQS_IN_DLY1_DBI_1                         (@ 0X434)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_POS_SEL_8                0
#define DPI_MASK_FW_RD_DLY_POS_SEL_8                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY2
 * @brief  DQS_IN_DLY2                               (@ 0X438)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_3                24
#define DPI_MASK_FW_RD_DLY_NEG_SEL_3                 ((u32)0x0000001F << 24)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_2                16
#define DPI_MASK_FW_RD_DLY_NEG_SEL_2                 ((u32)0x0000001F << 16)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_1                8
#define DPI_MASK_FW_RD_DLY_NEG_SEL_1                 ((u32)0x0000001F << 8)                              /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_0                0
#define DPI_MASK_FW_RD_DLY_NEG_SEL_0                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY2_1
 * @brief  DQS_IN_DLY2_1                             (@ 0X43C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_3                24
#define DPI_MASK_FW_RD_DLY_NEG_SEL_3                 ((u32)0x0000001F << 24)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_2                16
#define DPI_MASK_FW_RD_DLY_NEG_SEL_2                 ((u32)0x0000001F << 16)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_1                8
#define DPI_MASK_FW_RD_DLY_NEG_SEL_1                 ((u32)0x0000001F << 8)                              /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_0                0
#define DPI_MASK_FW_RD_DLY_NEG_SEL_0                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY3
 * @brief  DQS_IN_DLY3                               (@ 0X440)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_7                24
#define DPI_MASK_FW_RD_DLY_NEG_SEL_7                 ((u32)0x0000001F << 24)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_6                16
#define DPI_MASK_FW_RD_DLY_NEG_SEL_6                 ((u32)0x0000001F << 16)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_5                8
#define DPI_MASK_FW_RD_DLY_NEG_SEL_5                 ((u32)0x0000001F << 8)                              /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_4                0
#define DPI_MASK_FW_RD_DLY_NEG_SEL_4                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY3_1
 * @brief  DQS_IN_DLY3_1                             (@ 0X444)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_7                24
#define DPI_MASK_FW_RD_DLY_NEG_SEL_7                 ((u32)0x0000001F << 24)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_6                16
#define DPI_MASK_FW_RD_DLY_NEG_SEL_6                 ((u32)0x0000001F << 16)                             /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_5                8
#define DPI_MASK_FW_RD_DLY_NEG_SEL_5                 ((u32)0x0000001F << 8)                              /*!<R/W 0xA  RSVD */
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_4                0
#define DPI_MASK_FW_RD_DLY_NEG_SEL_4                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY3_DBI
 * @brief  DQS_IN_DLY3_DBI                           (@ 0X448)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_8                0
#define DPI_MASK_FW_RD_DLY_NEG_SEL_8                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQS_IN_DLY3_DBI_1
 * @brief  DQS_IN_DLY3_DBI_1                         (@ 0X44C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_RD_DLY_NEG_SEL_8                0
#define DPI_MASK_FW_RD_DLY_NEG_SEL_8                 ((u32)0x0000001F << 0)                              /*!<R/W 0xA  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_VALID_WIN_DET_PFIFO
 * @brief  VALID_WIN_DET_PFIFO                       (@ 0X450)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RX_LAG_DET_PFIFO                   9
#define DPI_MASK_RX_LAG_DET_PFIFO                    ((u32)0x000001FF << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_RX_LEAD_DET_PFIFO                  0
#define DPI_MASK_RX_LEAD_DET_PFIFO                   ((u32)0x000001FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_VALID_WIN_DET_PFIFO_1
 * @brief  VALID_WIN_DET_PFIFO_1                     (@ 0X454)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RX_LAG_DET_PFIFO                   9
#define DPI_MASK_RX_LAG_DET_PFIFO                    ((u32)0x000001FF << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_RX_LEAD_DET_PFIFO                  0
#define DPI_MASK_RX_LEAD_DET_PFIFO                   ((u32)0x000001FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_VALID_WIN_DET_NFIFO
 * @brief  VALID_WIN_DET_NFIFO                       (@ 0X458)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RX_LAG_DET_NFIFO                   9
#define DPI_MASK_RX_LAG_DET_NFIFO                    ((u32)0x000001FF << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_RX_LEAD_DET_NFIFO                  0
#define DPI_MASK_RX_LEAD_DET_NFIFO                   ((u32)0x000001FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_VALID_WIN_DET_NFIFO_1
 * @brief  VALID_WIN_DET_NFIFO_1                     (@ 0X45C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RX_LAG_DET_NFIFO                   9
#define DPI_MASK_RX_LAG_DET_NFIFO                    ((u32)0x000001FF << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_RX_LEAD_DET_NFIFO                  0
#define DPI_MASK_RX_LEAD_DET_NFIFO                   ((u32)0x000001FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_DLY_0
 * @brief  DQ_DLY_0                                  (@ 0X460)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ7_DLY_SEL                        28
#define DPI_MASK_DQ7_DLY_SEL                         ((u32)0x0000000F << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ6_DLY_SEL                        24
#define DPI_MASK_DQ6_DLY_SEL                         ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ5_DLY_SEL                        20
#define DPI_MASK_DQ5_DLY_SEL                         ((u32)0x0000000F << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ4_DLY_SEL                        16
#define DPI_MASK_DQ4_DLY_SEL                         ((u32)0x0000000F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ3_DLY_SEL                        12
#define DPI_MASK_DQ3_DLY_SEL                         ((u32)0x0000000F << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ2_DLY_SEL                        8
#define DPI_MASK_DQ2_DLY_SEL                         ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ1_DLY_SEL                        4
#define DPI_MASK_DQ1_DLY_SEL                         ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ0_DLY_SEL                        0
#define DPI_MASK_DQ0_DLY_SEL                         ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_DLY_0_1
 * @brief  DQ_DLY_0_1                                (@ 0X464)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ7_DLY_SEL                        28
#define DPI_MASK_DQ7_DLY_SEL                         ((u32)0x0000000F << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ6_DLY_SEL                        24
#define DPI_MASK_DQ6_DLY_SEL                         ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ5_DLY_SEL                        20
#define DPI_MASK_DQ5_DLY_SEL                         ((u32)0x0000000F << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ4_DLY_SEL                        16
#define DPI_MASK_DQ4_DLY_SEL                         ((u32)0x0000000F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ3_DLY_SEL                        12
#define DPI_MASK_DQ3_DLY_SEL                         ((u32)0x0000000F << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ2_DLY_SEL                        8
#define DPI_MASK_DQ2_DLY_SEL                         ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ1_DLY_SEL                        4
#define DPI_MASK_DQ1_DLY_SEL                         ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ0_DLY_SEL                        0
#define DPI_MASK_DQ0_DLY_SEL                         ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_DLY_1
 * @brief  DQ_DLY_1                                  (@ 0X468)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_OE_DLY_SEL                     8
#define DPI_MASK_DQS_OE_DLY_SEL                      ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_DLY_SEL                         4
#define DPI_MASK_DM_DLY_SEL                          ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_DLY_SEL                        0
#define DPI_MASK_DQS_DLY_SEL                         ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_DLY_1_1
 * @brief  DQ_DLY_1_1                                (@ 0X46C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_OE_DLY_SEL                     8
#define DPI_MASK_DQS_OE_DLY_SEL                      ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_DLY_SEL                         4
#define DPI_MASK_DM_DLY_SEL                          ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_DLY_SEL                        0
#define DPI_MASK_DQS_DLY_SEL                         ((u32)0x0000000F << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_OUT_0
 * @brief  CAL_OUT_0                                 (@ 0X470)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CAL_RD_DLY_OUT                     0
#define DPI_MASK_CAL_RD_DLY_OUT                      ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_OUT_0_1
 * @brief  CAL_OUT_0_1                               (@ 0X474)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CAL_RD_DLY_OUT                     0
#define DPI_MASK_CAL_RD_DLY_OUT                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_WR_FIFO_0
 * @brief  WR_FIFO_0                                 (@ 0X478)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_WR_ADR_POS                         0
#define DPI_MASK_WR_ADR_POS                          ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_WR_FIFO_0_1
 * @brief  WR_FIFO_0_1                               (@ 0X47C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_WR_ADR_POS                         0
#define DPI_MASK_WR_ADR_POS                          ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_WR_FIFO_1
 * @brief  WR_FIFO_1                                 (@ 0X480)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_WR_ADR_NEG                         0
#define DPI_MASK_WR_ADR_NEG                          ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_WR_FIFO_1_1
 * @brief  WR_FIFO_1_1                               (@ 0X484)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_WR_ADR_NEG                         0
#define DPI_MASK_WR_ADR_NEG                          ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_RD_FIFO_0
 * @brief  RD_FIFO_0                                 (@ 0X488)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RD_ADR_POS                         0
#define DPI_MASK_RD_ADR_POS                          ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_RD_FIFO_0_1
 * @brief  RD_FIFO_0_1                               (@ 0X48C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RD_ADR_POS                         0
#define DPI_MASK_RD_ADR_POS                          ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_RD_FIFO_1
 * @brief  RD_FIFO_1                                 (@ 0X490)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RD_ADR_NEG                         0
#define DPI_MASK_RD_ADR_NEG                          ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_RD_FIFO_1_1
 * @brief  RD_FIFO_1_1                               (@ 0X494)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RD_ADR_NEG                         0
#define DPI_MASK_RD_ADR_NEG                          ((u32)0xFFFFFFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DBI_FIFO
 * @brief  DBI_FIFO                                  (@ 0X498)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RW_ADR_DBI                         0
#define DPI_MASK_RW_ADR_DBI                          ((u32)0x0000FFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DBI_FIFO_1
 * @brief  DBI_FIFO_1                                (@ 0X49C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_RW_ADR_DBI                         0
#define DPI_MASK_RW_ADR_DBI                          ((u32)0x0000FFFF << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_INT_STATUS_1
 * @brief  INT_STATUS_1                              (@ 0X4A0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CAL_RBDY_INT_NEG                   24
#define DPI_MASK_CAL_RBDY_INT_NEG                    ((u32)0x000000FF << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_LBDY_INT_NEG                   16
#define DPI_MASK_CAL_LBDY_INT_NEG                    ((u32)0x000000FF << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_RBDY_INT_POS                   8
#define DPI_MASK_CAL_RBDY_INT_POS                    ((u32)0x000000FF << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_LBDY_INT_POS                   0
#define DPI_MASK_CAL_LBDY_INT_POS                    ((u32)0x000000FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_INT_STATUS_1_1
 * @brief  INT_STATUS_1_1                            (@ 0X4A4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CAL_RBDY_INT_NEG                   24
#define DPI_MASK_CAL_RBDY_INT_NEG                    ((u32)0x000000FF << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_LBDY_INT_NEG                   16
#define DPI_MASK_CAL_LBDY_INT_NEG                    ((u32)0x000000FF << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_RBDY_INT_POS                   8
#define DPI_MASK_CAL_RBDY_INT_POS                    ((u32)0x000000FF << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_LBDY_INT_POS                   0
#define DPI_MASK_CAL_LBDY_INT_POS                    ((u32)0x000000FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_INT_STATUS_3
 * @brief  INT_STATUS_3                              (@ 0X4A8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CAL_RBDY_INT3_NEG                   21
#define DPI_BIT_CAL_RBDY_INT3_NEG                     ((u32)0x00000001 << 21)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_LBDY_INT3_NEG                   20
#define DPI_BIT_CAL_LBDY_INT3_NEG                     ((u32)0x00000001 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_RBDY_INT3_POS                   19
#define DPI_BIT_CAL_RBDY_INT3_POS                     ((u32)0x00000001 << 19)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_LBDY_INT3_POS                   18
#define DPI_BIT_CAL_LBDY_INT3_POS                     ((u32)0x00000001 << 18)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_FIFO_PTR_INT3_NEG                   9
#define DPI_MASK_FIFO_PTR_INT3_NEG                    ((u32)0x000001FF << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_FIFO_PTR_INT3_POS                   0
#define DPI_MASK_FIFO_PTR_INT3_POS                    ((u32)0x000001FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_INT_STATUS_3_1
 * @brief  INT_STATUS_3_1                            (@ 0X4AC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CAL_RBDY_INT3_NEG                   21
#define DPI_BIT_CAL_RBDY_INT3_NEG                     ((u32)0x00000001 << 21)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_LBDY_INT3_NEG                   20
#define DPI_BIT_CAL_LBDY_INT3_NEG                     ((u32)0x00000001 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_RBDY_INT3_POS                   19
#define DPI_BIT_CAL_RBDY_INT3_POS                     ((u32)0x00000001 << 19)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_LBDY_INT3_POS                   18
#define DPI_BIT_CAL_LBDY_INT3_POS                     ((u32)0x00000001 << 18)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_FIFO_PTR_INT3_NEG                   9
#define DPI_MASK_FIFO_PTR_INT3_NEG                    ((u32)0x000001FF << 9)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_FIFO_PTR_INT3_POS                   0
#define DPI_MASK_FIFO_PTR_INT3_POS                    ((u32)0x000001FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PRBS_TMUX4
 * @brief  PRBS_TMUX4                                (@ 0X4B8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_TEST                           31
#define DPI_BIT_DQS_TEST                             ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ5_SEL                            28
#define DPI_MASK_DQ5_SEL                             ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ4_SEL                            24
#define DPI_MASK_DQ4_SEL                             ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ3_SEL                            20
#define DPI_MASK_DQ3_SEL                             ((u32)0x00000007 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ2_SEL                            16
#define DPI_MASK_DQ2_SEL                             ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ1_SEL                            12
#define DPI_MASK_DQ1_SEL                             ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ0_SEL                            8
#define DPI_MASK_DQ0_SEL                             ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PRBS_TMUX4_1
 * @brief  PRBS_TMUX4_1                              (@ 0X4BC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_TEST                           31
#define DPI_BIT_DQS_TEST                             ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ5_SEL                            28
#define DPI_MASK_DQ5_SEL                             ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ4_SEL                            24
#define DPI_MASK_DQ4_SEL                             ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ3_SEL                            20
#define DPI_MASK_DQ3_SEL                             ((u32)0x00000007 << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ2_SEL                            16
#define DPI_MASK_DQ2_SEL                             ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ1_SEL                            12
#define DPI_MASK_DQ1_SEL                             ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ0_SEL                            8
#define DPI_MASK_DQ0_SEL                             ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PRBS_TMUX5
 * @brief  PRBS_TMUX5                                (@ 0X4C0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DATA_PRBS11_INVS                   31
#define DPI_BIT_DATA_PRBS11_INVS                     ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DATA_PRBS11_SEED                   16
#define DPI_MASK_DATA_PRBS11_SEED                    ((u32)0x000007FF << 16)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DM_SEL                             8
#define DPI_MASK_DM_SEL                              ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ7_SEL                            4
#define DPI_MASK_DQ7_SEL                             ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ6_SEL                            0
#define DPI_MASK_DQ6_SEL                             ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_PRBS_TMUX5_1
 * @brief  PRBS_TMUX5_1                              (@ 0X4C4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DATA_PRBS11_INVS                   31
#define DPI_BIT_DATA_PRBS11_INVS                     ((u32)0x00000001 << 31)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DATA_PRBS11_SEED                   16
#define DPI_MASK_DATA_PRBS11_SEED                    ((u32)0x000007FF << 16)                             /*!<R/W 1  RSVD */
#define DPI_SHIFT_DM_SEL                             8
#define DPI_MASK_DM_SEL                              ((u32)0x00000007 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ7_SEL                            4
#define DPI_MASK_DQ7_SEL                             ((u32)0x00000007 << 4)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ6_SEL                            0
#define DPI_MASK_DQ6_SEL                             ((u32)0x00000007 << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_RW_EMPH_CTL
 * @brief  RW_EMPH_CTL                               (@ 0X4C8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_SLEWRATE                       28
#define DPI_MASK_DQS_SLEWRATE                        ((u32)0x00000003 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_DLY_EMPH                       24
#define DPI_MASK_DQS_DLY_EMPH                        ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_SLEWRATE                        12
#define DPI_MASK_DQ_SLEWRATE                         ((u32)0x00000003 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_DLY_EMPH                        8
#define DPI_MASK_DQ_DLY_EMPH                         ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_RW_EMPH_CTL_1
 * @brief  RW_EMPH_CTL_1                             (@ 0X4CC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_SLEWRATE                       28
#define DPI_MASK_DQS_SLEWRATE                        ((u32)0x00000003 << 28)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_DLY_EMPH                       24
#define DPI_MASK_DQS_DLY_EMPH                        ((u32)0x0000000F << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_SLEWRATE                        12
#define DPI_MASK_DQ_SLEWRATE                         ((u32)0x00000003 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_DLY_EMPH                        8
#define DPI_MASK_DQ_DLY_EMPH                         ((u32)0x0000000F << 8)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_RW_SEL_EMPH_CTL
 * @brief  RW_SEL_EMPH_CTL                           (@ 0X4D0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_SEL_EMPHN                      20
#define DPI_MASK_DQS_SEL_EMPHN                       ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_DQS_SEL_EMPHP                      16
#define DPI_MASK_DQS_SEL_EMPHP                       ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_DQ_SEL_EMPHN                       4
#define DPI_MASK_DQ_SEL_EMPHN                        ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_DQ_SEL_EMPHP                       0
#define DPI_MASK_DQ_SEL_EMPHP                        ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_RW_SEL_EMPH_CTL_1
 * @brief  RW_SEL_EMPH_CTL_1                         (@ 0X4D4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_SEL_EMPHN                      20
#define DPI_MASK_DQS_SEL_EMPHN                       ((u32)0x0000000F << 20)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_DQS_SEL_EMPHP                      16
#define DPI_MASK_DQS_SEL_EMPHP                       ((u32)0x0000000F << 16)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_DQ_SEL_EMPHN                       4
#define DPI_MASK_DQ_SEL_EMPHN                        ((u32)0x0000000F << 4)                              /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_DQ_SEL_EMPHP                       0
#define DPI_MASK_DQ_SEL_EMPHP                        ((u32)0x0000000F << 0)                              /*!<R/W 0x7  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_IO_CTL_0
 * @brief  DQ_IO_CTL_0                               (@ 0X4D8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_OE_SIG                          24
#define DPI_MASK_DQ_OE_SIG                           ((u32)0x000000FF << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_OE_FRC_EN                       16
#define DPI_MASK_DQ_OE_FRC_EN                        ((u32)0x000000FF << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_IE_SIG                          8
#define DPI_MASK_DQ_IE_SIG                           ((u32)0x000000FF << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_IE_FRC_EN                       0
#define DPI_MASK_DQ_IE_FRC_EN                        ((u32)0x000000FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_IO_CTL_0_1
 * @brief  DQ_IO_CTL_0_1                             (@ 0X4DC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_OE_SIG                          24
#define DPI_MASK_DQ_OE_SIG                           ((u32)0x000000FF << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_OE_FRC_EN                       16
#define DPI_MASK_DQ_OE_FRC_EN                        ((u32)0x000000FF << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_IE_SIG                          8
#define DPI_MASK_DQ_IE_SIG                           ((u32)0x000000FF << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_IE_FRC_EN                       0
#define DPI_MASK_DQ_IE_FRC_EN                        ((u32)0x000000FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_IO_CTL_1
 * @brief  DQ_IO_CTL_1                               (@ 0X4E0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_PAT_OUT                         24
#define DPI_MASK_DQ_PAT_OUT                          ((u32)0x000000FF << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_PAT_OUT                         23
#define DPI_BIT_DM_PAT_OUT                           ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_OE_SIG                          3
#define DPI_BIT_DM_OE_SIG                            ((u32)0x00000001 << 3)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_OE_FRC_EN                       2
#define DPI_BIT_DM_OE_FRC_EN                         ((u32)0x00000001 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_IE_SIG                          1
#define DPI_BIT_DM_IE_SIG                            ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_IE_FRC_EN                       0
#define DPI_BIT_DM_IE_FRC_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_IO_CTL_1_1
 * @brief  DQ_IO_CTL_1_1                             (@ 0X4E4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQ_PAT_OUT                         24
#define DPI_MASK_DQ_PAT_OUT                          ((u32)0x000000FF << 24)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_PAT_OUT                         23
#define DPI_BIT_DM_PAT_OUT                           ((u32)0x00000001 << 23)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_OE_SIG                          3
#define DPI_BIT_DM_OE_SIG                            ((u32)0x00000001 << 3)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_OE_FRC_EN                       2
#define DPI_BIT_DM_OE_FRC_EN                         ((u32)0x00000001 << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_IE_SIG                          1
#define DPI_BIT_DM_IE_SIG                            ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DM_IE_FRC_EN                       0
#define DPI_BIT_DM_IE_FRC_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_DBG_CTRL
 * @brief  READ_DBG_CTRL                             (@ 0X4E8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_BURST_MON_WAIT_TIME            26
#define DPI_MASK_DQS_BURST_MON_WAIT_TIME             ((u32)0x0000000F << 26)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_RD_DBG_SEL1                        21
#define DPI_MASK_RD_DBG_SEL1                         ((u32)0x0000001F << 21)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RD_DBG_SEL0                        16
#define DPI_MASK_RD_DBG_SEL0                         ((u32)0x0000001F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_RD_DLY_OUT_SEL                 12
#define DPI_MASK_CAL_RD_DLY_OUT_SEL                  ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TX_WDATA_MASK                      10
#define DPI_BIT_TX_WDATA_MASK                        ((u32)0x00000001 << 10)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_DM_PD_EN                       8
#define DPI_MASK_DQS_DM_PD_EN                        ((u32)0x00000003 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_PD_EN                           0
#define DPI_MASK_DQ_PD_EN                            ((u32)0x000000FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_DBG_CTRL_1
 * @brief  READ_DBG_CTRL_1                           (@ 0X4EC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_BURST_MON_WAIT_TIME            26
#define DPI_MASK_DQS_BURST_MON_WAIT_TIME             ((u32)0x0000000F << 26)                             /*!<R/W 0x7  RSVD */
#define DPI_SHIFT_RD_DBG_SEL1                        21
#define DPI_MASK_RD_DBG_SEL1                         ((u32)0x0000001F << 21)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_RD_DBG_SEL0                        16
#define DPI_MASK_RD_DBG_SEL0                         ((u32)0x0000001F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_CAL_RD_DLY_OUT_SEL                 12
#define DPI_MASK_CAL_RD_DLY_OUT_SEL                  ((u32)0x00000007 << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TX_WDATA_MASK                      10
#define DPI_BIT_TX_WDATA_MASK                        ((u32)0x00000001 << 10)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_DM_PD_EN                       8
#define DPI_MASK_DQS_DM_PD_EN                        ((u32)0x00000003 << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQ_PD_EN                           0
#define DPI_MASK_DQ_PD_EN                            ((u32)0x000000FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_MON
 * @brief  MON                                       (@ 0X4F0)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CAL_FTUN_UNDER_FLG                 30
#define DPI_BIT_CAL_FTUN_UNDER_FLG                   ((u32)0x00000001 << 30)                             /*!<R 0  RSVD */
#define DPI_SHIFT_CAL_FTUN_OVER_FLG                  29
#define DPI_BIT_CAL_FTUN_OVER_FLG                    ((u32)0x00000001 << 29)                             /*!<R 0  RSVD */
#define DPI_SHIFT_CAL_FTUN_BOTH_HIT_FLG              28
#define DPI_BIT_CAL_FTUN_BOTH_HIT_FLG                ((u32)0x00000001 << 28)                             /*!<R 0  RSVD */
#define DPI_SHIFT_FW_TM_DQS_EN_FTUN                  24
#define DPI_MASK_FW_TM_DQS_EN_FTUN                   ((u32)0x0000000F << 24)                             /*!<R 0x3  RSVD */
#define DPI_SHIFT_DQS_EN_DLY_SEL_PH                  16
#define DPI_MASK_DQS_EN_DLY_SEL_PH                   ((u32)0x0000003F << 16)                             /*!<R 0x10  RSVD */
#define DPI_SHIFT_MON_BURST_CNT                      4
#define DPI_MASK_MON_BURST_CNT                       ((u32)0x0000000F << 4)                              /*!<R 0  RSVD */
#define DPI_SHIFT_MON_DQS_CNT                        0
#define DPI_MASK_MON_DQS_CNT                         ((u32)0x0000000F << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_MON_1
 * @brief  MON_1                                     (@ 0X4F4)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_CAL_FTUN_UNDER_FLG                 30
#define DPI_BIT_CAL_FTUN_UNDER_FLG                   ((u32)0x00000001 << 30)                             /*!<R 0  RSVD */
#define DPI_SHIFT_CAL_FTUN_OVER_FLG                  29
#define DPI_BIT_CAL_FTUN_OVER_FLG                    ((u32)0x00000001 << 29)                             /*!<R 0  RSVD */
#define DPI_SHIFT_CAL_FTUN_BOTH_HIT_FLG              28
#define DPI_BIT_CAL_FTUN_BOTH_HIT_FLG                ((u32)0x00000001 << 28)                             /*!<R 0  RSVD */
#define DPI_SHIFT_FW_TM_DQS_EN_FTUN                  24
#define DPI_MASK_FW_TM_DQS_EN_FTUN                   ((u32)0x0000000F << 24)                             /*!<R 0x3  RSVD */
#define DPI_SHIFT_DQS_EN_DLY_SEL_PH                  16
#define DPI_MASK_DQS_EN_DLY_SEL_PH                   ((u32)0x0000003F << 16)                             /*!<R 0x10  RSVD */
#define DPI_SHIFT_MON_BURST_CNT                      4
#define DPI_MASK_MON_BURST_CNT                       ((u32)0x0000000F << 4)                              /*!<R 0  RSVD */
#define DPI_SHIFT_MON_DQS_CNT                        0
#define DPI_MASK_MON_DQS_CNT                         ((u32)0x0000000F << 0)                              /*!<R 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_LS_SEL
 * @brief  CAL_LS_SEL                                (@ 0X4F8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_PRE_SHIFT_SEL_7                    28
#define DPI_MASK_PRE_SHIFT_SEL_7                     ((u32)0x00000007 << 28)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_6                    24
#define DPI_MASK_PRE_SHIFT_SEL_6                     ((u32)0x00000007 << 24)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_5                    20
#define DPI_MASK_PRE_SHIFT_SEL_5                     ((u32)0x00000007 << 20)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_4                    16
#define DPI_MASK_PRE_SHIFT_SEL_4                     ((u32)0x00000007 << 16)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_3                    12
#define DPI_MASK_PRE_SHIFT_SEL_3                     ((u32)0x00000007 << 12)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_2                    8
#define DPI_MASK_PRE_SHIFT_SEL_2                     ((u32)0x00000007 << 8)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_1                    4
#define DPI_MASK_PRE_SHIFT_SEL_1                     ((u32)0x00000007 << 4)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_0                    0
#define DPI_MASK_PRE_SHIFT_SEL_0                     ((u32)0x00000007 << 0)                              /*!<R/W 0x2  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_LS_SEL_1
 * @brief  CAL_LS_SEL_1                              (@ 0X4FC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_PRE_SHIFT_SEL_7                    28
#define DPI_MASK_PRE_SHIFT_SEL_7                     ((u32)0x00000007 << 28)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_6                    24
#define DPI_MASK_PRE_SHIFT_SEL_6                     ((u32)0x00000007 << 24)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_5                    20
#define DPI_MASK_PRE_SHIFT_SEL_5                     ((u32)0x00000007 << 20)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_4                    16
#define DPI_MASK_PRE_SHIFT_SEL_4                     ((u32)0x00000007 << 16)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_3                    12
#define DPI_MASK_PRE_SHIFT_SEL_3                     ((u32)0x00000007 << 12)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_2                    8
#define DPI_MASK_PRE_SHIFT_SEL_2                     ((u32)0x00000007 << 8)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_1                    4
#define DPI_MASK_PRE_SHIFT_SEL_1                     ((u32)0x00000007 << 4)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_PRE_SHIFT_SEL_0                    0
#define DPI_MASK_PRE_SHIFT_SEL_0                     ((u32)0x00000007 << 0)                              /*!<R/W 0x2  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_LS_SEL_DBI
 * @brief  CAL_LS_SEL_DBI                            (@ 0X500)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_PRE_SHIFT_SEL_8                    0
#define DPI_MASK_PRE_SHIFT_SEL_8                     ((u32)0x00000007 << 0)                              /*!<R/W 0x2  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_LS_SEL_DBI_1
 * @brief  CAL_LS_SEL_DBI_1                          (@ 0X504)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_PRE_SHIFT_SEL_8                    0
#define DPI_MASK_PRE_SHIFT_SEL_8                     ((u32)0x00000007 << 0)                              /*!<R/W 0x2  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_RS_SEL
 * @brief  CAL_RS_SEL                                (@ 0X508)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_POST_SHIFT_SEL_7                   28
#define DPI_MASK_POST_SHIFT_SEL_7                    ((u32)0x00000007 << 28)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_6                   24
#define DPI_MASK_POST_SHIFT_SEL_6                    ((u32)0x00000007 << 24)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_5                   20
#define DPI_MASK_POST_SHIFT_SEL_5                    ((u32)0x00000007 << 20)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_4                   16
#define DPI_MASK_POST_SHIFT_SEL_4                    ((u32)0x00000007 << 16)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_3                   12
#define DPI_MASK_POST_SHIFT_SEL_3                    ((u32)0x00000007 << 12)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_2                   8
#define DPI_MASK_POST_SHIFT_SEL_2                    ((u32)0x00000007 << 8)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_1                   4
#define DPI_MASK_POST_SHIFT_SEL_1                    ((u32)0x00000007 << 4)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_0                   0
#define DPI_MASK_POST_SHIFT_SEL_0                    ((u32)0x00000007 << 0)                              /*!<R/W 0x2  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_RS_SEL_1
 * @brief  CAL_RS_SEL_1                              (@ 0X50C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_POST_SHIFT_SEL_7                   28
#define DPI_MASK_POST_SHIFT_SEL_7                    ((u32)0x00000007 << 28)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_6                   24
#define DPI_MASK_POST_SHIFT_SEL_6                    ((u32)0x00000007 << 24)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_5                   20
#define DPI_MASK_POST_SHIFT_SEL_5                    ((u32)0x00000007 << 20)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_4                   16
#define DPI_MASK_POST_SHIFT_SEL_4                    ((u32)0x00000007 << 16)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_3                   12
#define DPI_MASK_POST_SHIFT_SEL_3                    ((u32)0x00000007 << 12)                             /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_2                   8
#define DPI_MASK_POST_SHIFT_SEL_2                    ((u32)0x00000007 << 8)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_1                   4
#define DPI_MASK_POST_SHIFT_SEL_1                    ((u32)0x00000007 << 4)                              /*!<R/W 0x2  RSVD */
#define DPI_SHIFT_POST_SHIFT_SEL_0                   0
#define DPI_MASK_POST_SHIFT_SEL_0                    ((u32)0x00000007 << 0)                              /*!<R/W 0x2  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_RS_SEL_DBI
 * @brief  CAL_RS_SEL_DBI                            (@ 0X510)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_POST_SHIFT_SEL_8                   0
#define DPI_MASK_POST_SHIFT_SEL_8                    ((u32)0x00000007 << 0)                              /*!<R/W 0x2  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_CAL_RS_SEL_DBI_1
 * @brief  CAL_RS_SEL_DBI_1                          (@ 0X514)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_POST_SHIFT_SEL_8                   0
#define DPI_MASK_POST_SHIFT_SEL_8                    ((u32)0x00000007 << 0)                              /*!<R/W 0x2  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_IO_CTL_2
 * @brief  DQ_IO_CTL_2                               (@ 0X518)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQM_OE_TIME                        12
#define DPI_MASK_DQM_OE_TIME                         ((u32)0x0000000F << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DATA_INV                           0
#define DPI_MASK_DATA_INV                            ((u32)0x000001FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_DQ_IO_CTL_2_1
 * @brief  DQ_IO_CTL_2_1                             (@ 0X51C)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQM_OE_TIME                        12
#define DPI_MASK_DQM_OE_TIME                         ((u32)0x0000000F << 12)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DATA_INV                           0
#define DPI_MASK_DATA_INV                            ((u32)0x000001FF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL_4
 * @brief  READ_CTRL_4                               (@ 0X520)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_DQSEN_FTUN_UPD                  1
#define DPI_BIT_FW_DQSEN_FTUN_UPD                    ((u32)0x00000001 << 1)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_FW_RD_TE_UPD                       0
#define DPI_BIT_FW_RD_TE_UPD                         ((u32)0x00000001 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL_4_1
 * @brief  READ_CTRL_4_1                             (@ 0X524)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_FW_DQSEN_FTUN_UPD                  1
#define DPI_BIT_FW_DQSEN_FTUN_UPD                    ((u32)0x00000001 << 1)                              /*!<R/W 1  RSVD */
#define DPI_SHIFT_FW_RD_TE_UPD                       0
#define DPI_BIT_FW_RD_TE_UPD                         ((u32)0x00000001 << 0)                              /*!<R/W 1  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL_0_0
 * @brief  READ_CTRL_0_0                             (@ 0X5F8)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_RC1IN_DLY_SEL                  26
#define DPI_MASK_DQS_RC1IN_DLY_SEL                   ((u32)0x0000001F << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_GLITCH_DLY_PH                  20
#define DPI_MASK_DQS_GLITCH_DLY_PH                   ((u32)0x0000000F << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQ_LAT_DLY                      16
#define DPI_MASK_TM_DQ_LAT_DLY                       ((u32)0x0000000F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_FIFO_DLY_SEL                   14
#define DPI_MASK_DQS_FIFO_DLY_SEL                    ((u32)0x00000003 << 14)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_EN_DLY_SEL                     8
#define DPI_MASK_DQS_EN_DLY_SEL                      ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQS_EN                          2
#define DPI_MASK_TM_DQS_EN                           ((u32)0x0000001F << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQS_EN_FTUN                     0
#define DPI_MASK_TM_DQS_EN_FTUN                      ((u32)0x00000003 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup DPI_READ_CTRL_0_1
 * @brief  READ_CTRL_0_1                             (@ 0X5FC)
 * @{
 *****************************************************************************/
#define DPI_SHIFT_DQS_RC1IN_DLY_SEL                  26
#define DPI_MASK_DQS_RC1IN_DLY_SEL                   ((u32)0x0000001F << 26)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_GLITCH_DLY_PH                  20
#define DPI_MASK_DQS_GLITCH_DLY_PH                   ((u32)0x0000000F << 20)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQ_LAT_DLY                      16
#define DPI_MASK_TM_DQ_LAT_DLY                       ((u32)0x0000000F << 16)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_FIFO_DLY_SEL                   14
#define DPI_MASK_DQS_FIFO_DLY_SEL                    ((u32)0x00000003 << 14)                             /*!<R/W 0  RSVD */
#define DPI_SHIFT_DQS_EN_DLY_SEL                     8
#define DPI_MASK_DQS_EN_DLY_SEL                      ((u32)0x0000003F << 8)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQS_EN                          2
#define DPI_MASK_TM_DQS_EN                           ((u32)0x0000001F << 2)                              /*!<R/W 0  RSVD */
#define DPI_SHIFT_TM_DQS_EN_FTUN                     0
#define DPI_MASK_TM_DQS_EN_FTUN                      ((u32)0x00000003 << 0)                              /*!<R/W 0x3  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_DPI
 * @{
 * @brief rtl8735b_DPI Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t DPI_CRT_CTL ;                            /*!<  CRT_CTL register,  Address offset: 0x000 */
	__IO uint32_t DPI_PLL_CTL0 ;                           /*!<  PLL_CTL0 register,  Address offset: 0x004 */
	__IO uint32_t DPI_PLL_CTL1 ;                           /*!<  PLL_CTL1 register,  Address offset: 0x008 */
	__IO uint32_t DPI_PLL_CTL2 ;                           /*!<  PLL_CTL2 register,  Address offset: 0x00C */
	__IO uint32_t DPI_PLL_PI0 ;                            /*!<  PLL_PI0 register,  Address offset: 0x010 */
	__IO uint32_t DPI_PLL_PI1 ;                            /*!<  PLL_PI1 register,  Address offset: 0x014 */
	__IO uint32_t DPI_PLL_CTL3 ;                           /*!<  PLL_CTL3 register,  Address offset: 0x018 */
	__IO uint32_t DPI_SSC0 ;                               /*!<  SSC0 register,  Address offset: 0x01C */
	__IO uint32_t DPI_SSC1 ;                               /*!<  SSC1 register,  Address offset: 0x020 */
	__IO uint32_t DPI_SSC2 ;                               /*!<  SSC2 register,  Address offset: 0x024 */
	__IO uint32_t DPI_SSC3 ;                               /*!<  SSC3 register,  Address offset: 0x028 */
	__IO uint32_t DPI_WDOG ;                               /*!<  WDOG register,  Address offset: 0x02C */
	__IO uint32_t DPI_DCC_CMD ;                            /*!<  DCC_CMD register,  Address offset: 0x030 */
	__IO uint32_t DPI_DCC_DQS_0 ;                          /*!<  DCC_DQS_0 register,  Address offset: 0x034 */
	__IO uint32_t DPI_DCC_DQS_1 ;                          /*!<  DCC_DQS_1 register,  Address offset: 0x038 */
	__IO uint32_t DPI_DCC_DQS_2 ;                          /*!<  DCC_DQS_2 register,  Address offset: 0x03C */
	__IO uint32_t DPI_DCC_DQS_3 ;                          /*!<  DCC_DQS_3 register,  Address offset: 0x040 */
	__IO uint32_t DPI_DCC_DQ_0 ;                           /*!<  DCC_DQ_0 register,  Address offset: 0x044 */
	__IO uint32_t DPI_DCC_DQ_1 ;                           /*!<  DCC_DQ_1 register,  Address offset: 0x048 */
	__IO uint32_t DPI_DCC_DQ_2 ;                           /*!<  DCC_DQ_2 register,  Address offset: 0x04C */
	__IO uint32_t DPI_DCC_DQ_3 ;                           /*!<  DCC_DQ_3 register,  Address offset: 0x050 */
	__IO uint32_t DPI_DCC_CK_0 ;                           /*!<  DCC_CK_0 register,  Address offset: 0x054 */
	__IO uint32_t DPI_DCC_CK_1 ;                           /*!<  DCC_CK_1 register,  Address offset: 0x058 */
	__IO uint32_t RSVD0;                                  /*!<  Reserved,  Address offset:0x5C */
	__IO uint32_t DPI_CRT_CTL_2 ;                          /*!<  CRT_CTL_2 register,  Address offset: 0x060 */
	__IO uint32_t RSVD1[7];                                /*!<  Reserved,  Address offset:0x64-0x7C */
	__IO uint32_t DPI_AFIFO_STR_0 ;                        /*!<  AFIFO_STR_0 register,  Address offset: 0x080 */
	__IO uint32_t DPI_AFIFO_STR_1 ;                        /*!<  AFIFO_STR_1 register,  Address offset: 0x084 */
	__IO uint32_t DPI_AFIFO_STR_2 ;                        /*!<  AFIFO_STR_2 register,  Address offset: 0x088 */
	__IO uint32_t DPI_CRT_RST_CTL ;                        /*!<  CRT_RST_CTL register,  Address offset: 0x08C */
	__IO uint32_t RSVD2;                                  /*!<  Reserved,  Address offset:0x90 */
	__IO uint32_t DPI_AFIFO_STR_SEL ;                      /*!<  AFIFO_STR_SEL register,  Address offset: 0x094 */
	__IO uint32_t DPI_PLL_PI2 ;                            /*!<  PLL_PI2 register,  Address offset: 0x098 */
	__IO uint32_t DPI_PLL_CTL4 ;                           /*!<  PLL_CTL4 register,  Address offset: 0x09C */
	__IO uint32_t DPI_PLL_PI3 ;                            /*!<  PLL_PI3 register,  Address offset: 0x0A0 */
	__IO uint32_t DPI_DCC_CS ;                             /*!<  DCC_CS register,  Address offset: 0x0A4 */
	__IO uint32_t DPI_DCC_CS1 ;                            /*!<  DCC_CS1 register,  Address offset: 0x0A8 */
	__IO uint32_t DPI_PLL_CTL5 ;                           /*!<  PLL_CTL5 register,  Address offset: 0x0AC */
	__IO uint32_t RSVD3[20];                               /*!<  Reserved,  Address offset:0xB0-0xFC */
	__IO uint32_t DPI_ADR_DLY_0 ;                          /*!<  ADR_DLY_0 register,  Address offset: 0x100 */
	__IO uint32_t DPI_ADR_DLY_1 ;                          /*!<  ADR_DLY_1 register,  Address offset: 0x104 */
	__IO uint32_t DPI_ADR_DLY_2 ;                          /*!<  ADR_DLY_2 register,  Address offset: 0x108 */
	__IO uint32_t DPI_CMD_DLY_0 ;                          /*!<  CMD_DLY_0 register,  Address offset: 0x10C */
	__IO uint32_t DPI_CMD_DLY_1 ;                          /*!<  CMD_DLY_1 register,  Address offset: 0x110 */
	__IO uint32_t DPI_PAD_OE_CTL ;                         /*!<  PAD_OE_CTL register,  Address offset: 0x114 */
	__IO uint32_t DPI_PAD_OE_CTL_EX ;                      /*!<  PAD_OE_CTL_EX register,  Address offset: 0x118 */
	__IO uint32_t DPI_PAD_ALERT_SEL_0 ;                    /*!<  PAD_ALERT_SEL_0 register,  Address offset: 0x11C */
	__IO uint32_t DPI_PAD_ALERT_SEL_1 ;                    /*!<  PAD_ALERT_SEL_1 register,  Address offset: 0x120 */
	__IO uint32_t DPI_PAD_ALERT1_SEL_0 ;                   /*!<  PAD_ALERT1_SEL_0 register,  Address offset: 0x124 */
	__IO uint32_t DPI_PAD_ALERT1_SEL_1 ;                   /*!<  PAD_ALERT1_SEL_1 register,  Address offset: 0x128 */
	__IO uint32_t DPI_PAD_IDDQ ;                           /*!<  PAD_IDDQ register,  Address offset: 0x12C */
	__IO uint32_t DPI_PAD_CTRL_PROG ;                      /*!<  PAD_CTRL_PROG register,  Address offset: 0x130 */
	__IO uint32_t RSVD4[2];                                /*!<  Reserved,  Address offset:0x134-0x138 */
	__IO uint32_t DPI_ZQ_NOCD2 ;                           /*!<  ZQ_NOCD2 register,  Address offset: 0x13C */
	__IO uint32_t DPI_PAD_ZCTRL_STATUS ;                   /*!<  PAD_ZCTRL_STATUS register,  Address offset: 0x140 */
	__I  uint32_t DPI_PAD_ZCTRL_RESULT ;                   /*!<  PAD_ZCTRL_RESULT register,  Address offset: 0x144 */
	__I  uint32_t DPI_PAD_ZCTRL_RESULT_D ;                 /*!<  PAD_ZCTRL_RESULT_D register,  Address offset: 0x148 */
	__IO uint32_t DPI_PAD_RZCTRL_STATUS ;                  /*!<  PAD_RZCTRL_STATUS register,  Address offset: 0x14C */
	__IO uint32_t DPI_DQ_DQS_CTRL ;                        /*!<  dq_dqs_ctrl register,  Address offset: 0x150 */
	__IO uint32_t DPI_CMD_ADR_PH ;                         /*!<  CMD_ADDR_PH register,  Address offset: 0x154 */
	__I  uint32_t DPI_DQ_PAT_IN0 ;                         /*!<  DQ_PAT_IN0 register,  Address offset: 0x158 */
	__I  uint32_t DPI_DQ_PAT_IN1 ;                         /*!<  DQ_PAT_IN1 register,  Address offset: 0x15C */
	__I  uint32_t DPI_WRLVL_DQS_DATA ;                     /*!<  WRLVL_DQS_DATA register,  Address offset: 0x160 */
	__IO uint32_t DPI_TEST_CTRL0 ;                         /*!<  TEST_CTRL0 register,  Address offset: 0x164 */
	__IO uint32_t DPI_TEST_CTRL1 ;                         /*!<  TEST_CTRL1 register,  Address offset: 0x168 */
	__IO uint32_t DPI_HALF_CYC_DET ;                       /*!<  HAF_CYC_DET register,  Address offset: 0x16C */
	__IO uint32_t DPI_READ_CTRL1 ;                         /*!<  READ_CTRL1 register,  Address offset: 0x170 */
	__IO uint32_t DPI_TX_RPT_CTRL ;                        /*!<  TX_RPT_CTRL register,  Address offset: 0x174 */
	__IO uint32_t DPI_CAL_SHIFT_CTRL ;                     /*!<  CAL_SHIFT_CTRL register,  Address offset: 0x178 */
	__IO uint32_t DPI_DT_SET0 ;                            /*!<  DT_SET0 register,  Address offset: 0x17C */
	__IO uint32_t DPI_ODT_TTCP0_SET0 ;                     /*!<  ODT_TTCP0_SEL0 register,  Address offset: 0x180 */
	__IO uint32_t DPI_ODT_TTCP1_SET0 ;                     /*!<  ODT_TTCP1_SEL0 register,  Address offset: 0x184 */
	__IO uint32_t DPI_ODT_TTCN0_SET0 ;                     /*!<  ODT_TTCN0_SEL0 register,  Address offset: 0x188 */
	__IO uint32_t DPI_ODT_TTCN1_SET0 ;                     /*!<  ODT_TTCN1_SEL0 register,  Address offset: 0x18C */
	__IO uint32_t DPI_OCDP0_SET0 ;                         /*!<  OCDP0_SET0 register,  Address offset: 0x190 */
	__IO uint32_t DPI_OCDP1_SET0 ;                         /*!<  OCDP1_SET0 register,  Address offset: 0x194 */
	__IO uint32_t DPI_OCDN0_SET0 ;                         /*!<  OCDN0_SET0 register,  Address offset: 0x198 */
	__IO uint32_t DPI_OCDN1_SET0 ;                         /*!<  OCDN1_SET0 register,  Address offset: 0x19C */
	__IO uint32_t DPI_ODT_TTCP0_SET1 ;                     /*!<  ODT_TTCP0_SEL1 register,  Address offset: 0x1A0 */
	__IO uint32_t DPI_ODT_TTCP1_SET1 ;                     /*!<  ODT_TTCP1_SEL1 register,  Address offset: 0x1A4 */
	__IO uint32_t DPI_ODT_TTCN0_SET1 ;                     /*!<  ODT_TTCN0_SEL1 register,  Address offset: 0x1A8 */
	__IO uint32_t DPI_ODT_TTCN1_SET1 ;                     /*!<  ODT_TTCN1_SEL1 register,  Address offset: 0x1AC */
	__IO uint32_t DPI_OCDP0_SET1 ;                         /*!<  OCDP0_SET1 register,  Address offset: 0x1B0 */
	__IO uint32_t DPI_OCDP1_SET1 ;                         /*!<  OCDP1_SET1 register,  Address offset: 0x1B4 */
	__IO uint32_t DPI_OCDN0_SET1 ;                         /*!<  OCDN0_SET1 register,  Address offset: 0x1B8 */
	__IO uint32_t DPI_OCDN1_SET1 ;                         /*!<  OCDN1_SET1 register,  Address offset: 0x1BC */
	__IO uint32_t DPI_DQ_ODT_SEL_0 ;                       /*!<  DQ_ODT_DEL_0 register,  Address offset: 0x1C0 */
	__IO uint32_t DPI_DQ_ODT_SEL_1 ;                       /*!<  DQ_ODT_DEL_1 register,  Address offset: 0x1C4 */
	__IO uint32_t DPI_DQ_OCD_SEL_0 ;                       /*!<  DQ_OCD_SEL_0 register,  Address offset: 0x1C8 */
	__IO uint32_t DPI_DQ_OCD_SEL_1 ;                       /*!<  DQ_OCD_SEL_1 register,  Address offset: 0x1CC */
	__IO uint32_t DPI_DQS_P_ODT_SEL_0 ;                    /*!<  DQS_P_ODT_SEL_0 register,  Address offset: 0x1D0 */
	__IO uint32_t DPI_DQS_P_ODT_SEL_1 ;                    /*!<  DQS_P_ODT_SEL_1 register,  Address offset: 0x1D4 */
	__IO uint32_t DPI_DQS_N_ODT_SEL_0 ;                    /*!<  DQS_N_ODT_SEL_0 register,  Address offset: 0x1D8 */
	__IO uint32_t DPI_DQS_N_ODT_SEL_1 ;                    /*!<  DQS_N_ODT_SEL_1 register,  Address offset: 0x1DC */
	__IO uint32_t DPI_DQS_OCD_SEL_0 ;                      /*!<  DQS_OCD_SEL_0 register,  Address offset: 0x1E0 */
	__IO uint32_t DPI_DQS_OCD_SEL_1 ;                      /*!<  DQS_OCD_SEL_1 register,  Address offset: 0x1E4 */
	__IO uint32_t DPI_CKE_OCD_SEL ;                        /*!<  CKE_OCD_SEL register,  Address offset: 0x1E8 */
	__IO uint32_t DPI_ADR_OCD_SEL ;                        /*!<  ADR_OCD_SEL register,  Address offset: 0x1EC */
	__IO uint32_t DPI_CK_OCD_SEL ;                         /*!<  CK_OCD_SEL register,  Address offset: 0x1F0 */
	__IO uint32_t DPI_PAD_BUS_0 ;                          /*!<  PAD_BUS_0 register,  Address offset: 0x1F4 */
	__IO uint32_t DPI_PAD_BUS_1 ;                          /*!<  PAD_BUS_1 register,  Address offset: 0x1F8 */
	__IO uint32_t DPI_PAD_BUS_2 ;                          /*!<  PAD_BUS_2 register,  Address offset: 0x1FC */
	__IO uint32_t DPI_ZQ_TRIM ;                            /*!<  ZQ_TRIM register,  Address offset: 0x200 */
	__IO uint32_t DPI_OCD_SEL_0 ;                          /*!<  OCD_SEL_0 register,  Address offset: 0x204 */
	__IO uint32_t DPI_OCD_SEL_1 ;                          /*!<  OCD_SEL_1 register,  Address offset: 0x208 */
	__IO uint32_t DPI_OCD_SEL_2 ;                          /*!<  OCD_SEL_2 register,  Address offset: 0x20C */
	__IO uint32_t DPI_OCD_SEL_3 ;                          /*!<  OCD_SEL_3 register,  Address offset: 0x210 */
	__IO uint32_t DPI_OCD_SEL_4 ;                          /*!<  OCD_SEL_4 register,  Address offset: 0x214 */
	__IO uint32_t DPI_OCD_SEL_5 ;                          /*!<  OCD_SEL_5 register,  Address offset: 0x218 */
	__IO uint32_t DPI_OCD_SEL_6 ;                          /*!<  OCD_SEL_6 register,  Address offset: 0x21C */
	__IO uint32_t DPI_OCD_SEL_7 ;                          /*!<  OCD_SEL_7 register,  Address offset: 0x220 */
	__IO uint32_t DPI_OCD_SEL_8 ;                          /*!<  OCD_SEL_8 register,  Address offset: 0x224 */
	__IO uint32_t DPI_ODT_SEL_0 ;                          /*!<  ODT_SEL_0 register,  Address offset: 0x228 */
	__IO uint32_t DPI_CKE_ODT_SEL ;                        /*!<  CKE_ODT_SEL register,  Address offset: 0x22C */
	__IO uint32_t DPI_ADR_ODT_SEL ;                        /*!<  ADR_ODT_SEL register,  Address offset: 0x230 */
	__IO uint32_t DPI_CLK_ODT_SEL ;                        /*!<  CLK_ODT_SEL register,  Address offset: 0x234 */
	__IO uint32_t DPI_DPI_CTRL_0 ;                         /*!<  DPI_CTRL_0 register,  Address offset: 0x238 */
	__IO uint32_t DPI_DPI_CTRL_1 ;                         /*!<  DPI_CTRL_1 register,  Address offset: 0x23C */
	__IO uint32_t DPI_DPI_CTRL_2 ;                         /*!<  DPI_CTRL_2 register,  Address offset: 0x240 */
	__IO uint32_t RSVD5[4];                               /*!<  Reserved,  Address offset:0x244-0x250 */
	__IO uint32_t DPI_INT_CTRL ;                           /*!<  DPI_INT_CTRL register,  Address offset: 0x254 */
	__IO uint32_t DPI_INT_STATUS_0 ;                       /*!<  DPI_INT_STATUS_0 register,  Address offset: 0x258 */
	__IO uint32_t RSVD10[15];                              /*!<  Reserved,  Address offset:0x25C-0x294 */
	__IO uint32_t DPI_CS_EMPH_CTRL ;                       /*!<  CS_EMPH_CTRL register,  Address offset: 0x298 */
	__IO uint32_t DPI_CS_SEL_EMPH_CTL ;                    /*!<  CS_SEL_EMPH_CTL register,  Address offset: 0x29C */
	__IO uint32_t DPI_DDR4_CS_EMPH_CTL ;                   /*!<  DDR4_CS_EMPH_CTL register,  Address offset: 0x2A0 */
	__IO uint32_t DPI_CK_EMPH_CTL ;                        /*!<  CK_EMPH_CTL register,  Address offset: 0x2A4 */
	__IO uint32_t DPI_CK_SEL_EMPH_CTL ;                    /*!<  CK_SEL_EMPH_CTL register,  Address offset: 0x2A8 */
	__IO uint32_t DPI_ADR_EMPH_CTL_0 ;                     /*!<  ADR_EMPH_CTL_0 register,  Address offset: 0x2AC */
	__IO uint32_t DPI_ADR_EMPH_CTL_1 ;                     /*!<  ADR_EMPH_CTL_1 register,  Address offset: 0x2B0 */
	__IO uint32_t DPI_ADR_SEL_EMPH_CTL_0 ;                 /*!<  ADR_SEL_EMPH_CTL_0 register,  Address offset: 0x2B4 */
	__IO uint32_t DPI_ADR_SEL_EMPH_CTL_1 ;                 /*!<  ADR_SEL_EMPH_CTL_1 register,  Address offset: 0x2B8 */
	__IO uint32_t DPI_ADR_EMPH_SEL_0 ;                     /*!<  ADR_EMPH_SEL_0 register,  Address offset: 0x2BC */
	__IO uint32_t DPI_ADR_EMPH_SEL_1 ;                     /*!<  ADR_EMPH_SEL_1 register,  Address offset: 0x2C0 */
	__IO uint32_t DPI_ADR_EMPH_SEL_2 ;                     /*!<  ADR_EMPH_SEL_2 register,  Address offset: 0x2C4 */
	__IO uint32_t RSVD6[8];                                /*!<  Reserved,  Address offset:0x2C8-0x2E4 */
	__IO uint32_t DPI_PAD_CTRL_ZPROG ;                     /*!<  PAD_CTRL_ZPROG register,  Address offset: 0x2E8 */
	__IO uint32_t DPI_PAD_CTRL_ZPROG_1 ;                   /*!<  PAD_CTRL_ZPROG_1 register,  Address offset: 0x2EC */
	__IO uint32_t DPI_PAD_CTRL_ZPROG_2 ;                   /*!<  PAD_CTRL_ZPROG_2 register,  Address offset: 0x2F0 */
	__IO uint32_t DPI_PAD_CTRL_ZPROG_3 ;                   /*!<  PAD_CTRL_ZPROG_3 register,  Address offset: 0x2F4 */
	__IO uint32_t DPI_PAD_CTRL_ZPROG_4 ;                   /*!<  PAD_CTRL_ZPROG_4 register,  Address offset: 0x2F8 */
	__IO uint32_t DPI_PAD_CTRL_ZPROG_5 ;                   /*!<  PAD_CTRL_ZPROG_5 register,  Address offset: 0x2FC */
	__IO uint32_t DPI_PAD_CTRL_ZPROG_6 ;                   /*!<  PAD_CTRL_ZPROG_6 register,  Address offset: 0x300 */
	__IO uint32_t DPI_PAD_CTRL_ZPROG_7 ;                   /*!<  PAD_CTRL_ZPROG_7 register,  Address offset: 0x304 */
	__IO uint32_t DPI_PAD_NOCD2_ZPROG ;                    /*!<  PAD_NOCD2_ZPROG register,  Address offset: 0x308 */
	__IO uint32_t DPI_PAD_NOCD2_ZPROG_1 ;                  /*!<  PAD_NOCD2_ZPROG_1 register,  Address offset: 0x30C */
	__IO uint32_t DPI_PAD_NOCD2_ZPROG_2 ;                  /*!<  PAD_NOCD2_ZPROG_2 register,  Address offset: 0x310 */
	__IO uint32_t DPI_PAD_NOCD2_ZPROG_3 ;                  /*!<  PAD_NOCD2_ZPROG_3 register,  Address offset: 0x314 */
	__IO uint32_t DPI_PAD_NOCD2_ZPROG_4 ;                  /*!<  PAD_NOCD2_ZPROG_4 register,  Address offset: 0x318 */
	__IO uint32_t DPI_PAD_NOCD2_ZPROG_5 ;                  /*!<  PAD_NOCD2_ZPROG_5 register,  Address offset: 0x31C */
	__IO uint32_t DPI_PAD_NOCD2_ZPROG_6 ;                  /*!<  PAD_NOCD2_ZPROG_6 register,  Address offset: 0x320 */
	__IO uint32_t DPI_PAD_NOCD2_ZPROG_7 ;                  /*!<  PAD_NOCD2_ZPROG_7 register,  Address offset: 0x324 */
	__IO uint32_t DPI_DQ_OCD_SEL2_0 ;                      /*!<  DQ_OCD_SEL2_0 register,  Address offset: 0x328 */
	__IO uint32_t DPI_DQ_OCD_SEL2_1 ;                      /*!<  DQ_OCD_SEL2_1 register,  Address offset: 0x32C */
	__IO uint32_t DPI_DQS_OCD_SEL2_0 ;                     /*!<  DQS_OCD_SEL2_0 register,  Address offset: 0x330 */
	__IO uint32_t DPI_DQS_OCD_SEL2_1 ;                     /*!<  DQS_OCD_SEL2_1 register,  Address offset: 0x334 */
	__IO uint32_t RSVD7[52];                               /*!<  Reserved,  Address offset:0x338-0x404 */
	__IO uint32_t DPI_READ_CTRL2 ;                         /*!<  READ_CTRL2 register,  Address offset: 0x408 */
	__IO uint32_t DPI_READ_CTRL2_1 ;                       /*!<  READ_CTRL2_1 register,  Address offset: 0x40C */
	__IO uint32_t DPI_READ_CTRL3 ;                         /*!<  READ_CTRL3 register,  Address offset: 0x410 */
	__IO uint32_t DPI_READ_CTRL3_1 ;                       /*!<  READ_CTRL3_1 register,  Address offset: 0x414 */
	__IO uint32_t DPI_READ_CTRL6 ;                         /*!<  READ_CTRL6 register,  Address offset: 0x418 */
	__IO uint32_t DPI_READ_CTRL6_1 ;                       /*!<  READ_CTRL6_1 register,  Address offset: 0x41C */
	__IO uint32_t DPI_DQS_IN_DLY0 ;                        /*!<  DQS_IN_DLY0 register,  Address offset: 0x420 */
	__IO uint32_t DPI_DQS_IN_DLY0_1 ;                      /*!<  DQS_IN_DLY0_1 register,  Address offset: 0x424 */
	__IO uint32_t DPI_DQS_IN_DLY1 ;                        /*!<  DQS_IN_DLY1 register,  Address offset: 0x428 */
	__IO uint32_t DPI_DQS_IN_DLY1_1 ;                      /*!<  DQS_IN_DLY1_1 register,  Address offset: 0x42C */
	__IO uint32_t DPI_DQS_IN_DLY1_DBI ;                    /*!<  DQS_IN_DLY1_DBI register,  Address offset: 0x430 */
	__IO uint32_t DPI_DQS_IN_DLY1_DBI_1 ;                  /*!<  DQS_IN_DLY1_DBI_1 register,  Address offset: 0x434 */
	__IO uint32_t DPI_DQS_IN_DLY2 ;                        /*!<  DQS_IN_DLY2 register,  Address offset: 0x438 */
	__IO uint32_t DPI_DQS_IN_DLY2_1 ;                      /*!<  DQS_IN_DLY2_1 register,  Address offset: 0x43C */
	__IO uint32_t DPI_DQS_IN_DLY3 ;                        /*!<  DQS_IN_DLY3 register,  Address offset: 0x440 */
	__IO uint32_t DPI_DQS_IN_DLY3_1 ;                      /*!<  DQS_IN_DLY3_1 register,  Address offset: 0x444 */
	__IO uint32_t DPI_DQS_IN_DLY3_DBI ;                    /*!<  DQS_IN_DLY3_DBI register,  Address offset: 0x448 */
	__IO uint32_t DPI_DQS_IN_DLY3_DBI_1 ;                  /*!<  DQS_IN_DLY3_DBI_1 register,  Address offset: 0x44C */
	__IO uint32_t DPI_VALID_WIN_DET_PFIFO ;                /*!<  VALID_WIN_DET_PFIFO register,  Address offset: 0x450 */
	__IO uint32_t DPI_VALID_WIN_DET_PFIFO_1 ;              /*!<  VALID_WIN_DET_PFIFO_1 register,  Address offset: 0x454 */
	__IO uint32_t DPI_VALID_WIN_DET_NFIFO ;                /*!<  VALID_WIN_DET_NFIFO register,  Address offset: 0x458 */
	__IO uint32_t DPI_VALID_WIN_DET_NFIFO_1 ;              /*!<  VALID_WIN_DET_NFIFO_1 register,  Address offset: 0x45C */
	__IO uint32_t DPI_DQ_DLY_0 ;                           /*!<  DQ_DLY_0 register,  Address offset: 0x460 */
	__IO uint32_t DPI_DQ_DLY_0_1 ;                         /*!<  DQ_DLY_0_1 register,  Address offset: 0x464 */
	__IO uint32_t DPI_DQ_DLY_1 ;                           /*!<  DQ_DLY_1 register,  Address offset: 0x468 */
	__IO uint32_t DPI_DQ_DLY_1_1 ;                         /*!<  DQ_DLY_1_1 register,  Address offset: 0x46C */
	__I  uint32_t DPI_CAL_OUT_0 ;                          /*!<  CAL_OUT_0 register,  Address offset: 0x470 */
	__IO uint32_t DPI_CAL_OUT_0_1 ;                        /*!<  CAL_OUT_0_1 register,  Address offset: 0x474 */
	__I  uint32_t DPI_WR_FIFO_0 ;                          /*!<  WR_FIFO_0 register,  Address offset: 0x478 */
	__I  uint32_t DPI_WR_FIFO_0_1 ;                        /*!<  WR_FIFO_0_1 register,  Address offset: 0x47C */
	__I  uint32_t DPI_WR_FIFO_1 ;                          /*!<  WR_FIFO_1 register,  Address offset: 0x480 */
	__I  uint32_t DPI_WR_FIFO_1_1 ;                        /*!<  WR_FIFO_1_1 register,  Address offset: 0x484 */
	__I  uint32_t DPI_RD_FIFO_0 ;                          /*!<  RD_FIFO_0 register,  Address offset: 0x488 */
	__I  uint32_t DPI_RD_FIFO_0_1 ;                        /*!<  RD_FIFO_0_1 register,  Address offset: 0x48C */
	__I  uint32_t DPI_RD_FIFO_1 ;                          /*!<  RD_FIFO_1 register,  Address offset: 0x490 */
	__I  uint32_t DPI_RD_FIFO_1_1 ;                        /*!<  RD_FIFO_1_1 register,  Address offset: 0x494 */
	__I  uint32_t DPI_DBI_FIFO ;                           /*!<  DBI_FIFO register,  Address offset: 0x498 */
	__I  uint32_t DPI_DBI_FIFO_1 ;                         /*!<  DBI_FIFO_1 register,  Address offset: 0x49C */
	__IO uint32_t DPI_INT_STATUS_1 ;                       /*!<  INT_STATUS_1 register,  Address offset: 0x4A0 */
	__IO uint32_t DPI_INT_STATUS_1_1 ;                     /*!<  INT_STATUS_1_1 register,  Address offset: 0x4A4 */
	__IO uint32_t DPI_INT_STATUS_3 ;                       /*!<  INT_STATUS_3 register,  Address offset: 0x4A8 */
	__IO uint32_t DPI_INT_STATUS_3_1 ;                     /*!<  INT_STATUS_3_1 register,  Address offset: 0x4AC */
	__IO uint32_t RSVD8[2];                                /*!<  Reserved,  Address offset:0x4B0-0x4B4 */
	__IO uint32_t DPI_PRBS_TMUX4 ;                         /*!<  PRBS_TMUX4 register,  Address offset: 0x4B8 */
	__IO uint32_t DPI_PRBS_TMUX4_1 ;                       /*!<  PRBS_TMUX4_1 register,  Address offset: 0x4BC */
	__IO uint32_t DPI_PRBS_TMUX5 ;                         /*!<  PRBS_TMUX5 register,  Address offset: 0x4C0 */
	__IO uint32_t DPI_PRBS_TMUX5_1 ;                       /*!<  PRBS_TMUX5_1 register,  Address offset: 0x4C4 */
	__IO uint32_t DPI_RW_EMPH_CTL ;                        /*!<  RW_EMPH_CTL register,  Address offset: 0x4C8 */
	__IO uint32_t DPI_RW_EMPH_CTL_1 ;                      /*!<  RW_EMPH_CTL_1 register,  Address offset: 0x4CC */
	__IO uint32_t DPI_RW_SEL_EMPH_CTL ;                    /*!<  RW_SEL_EMPH_CTL register,  Address offset: 0x4D0 */
	__IO uint32_t DPI_RW_SEL_EMPH_CTL_1 ;                  /*!<  RW_SEL_EMPH_CTL_1 register,  Address offset: 0x4D4 */
	__IO uint32_t DPI_DQ_IO_CTL_0 ;                        /*!<  DQ_IO_CTL_0 register,  Address offset: 0x4D8 */
	__IO uint32_t DPI_DQ_IO_CTL_0_1 ;                      /*!<  DQ_IO_CTL_0_1 register,  Address offset: 0x4DC */
	__IO uint32_t DPI_DQ_IO_CTL_1 ;                        /*!<  DQ_IO_CTL_1 register,  Address offset: 0x4E0 */
	__IO uint32_t DPI_DQ_IO_CTL_1_1 ;                      /*!<  DQ_IO_CTL_1_1 register,  Address offset: 0x4E4 */
	__IO uint32_t DPI_READ_DBG_CTRL ;                      /*!<  READ_DBG_CTRL register,  Address offset: 0x4E8 */
	__IO uint32_t DPI_READ_DBG_CTRL_1 ;                    /*!<  READ_DBG_CTRL_1 register,  Address offset: 0x4EC */
	__I  uint32_t DPI_MON ;                                /*!<  MON register,  Address offset: 0x4F0 */
	__I  uint32_t DPI_MON_1 ;                              /*!<  MON_1 register,  Address offset: 0x4F4 */
	__IO uint32_t DPI_CAL_LS_SEL ;                         /*!<  CAL_LS_SEL register,  Address offset: 0x4F8 */
	__IO uint32_t DPI_CAL_LS_SEL_1 ;                       /*!<  CAL_LS_SEL_1 register,  Address offset: 0x4FC */
	__IO uint32_t DPI_CAL_LS_SEL_DBI ;                     /*!<  CAL_LS_SEL_DBI register,  Address offset: 0x500 */
	__IO uint32_t DPI_CAL_LS_SEL_DBI_1 ;                   /*!<  CAL_LS_SEL_DBI_1 register,  Address offset: 0x504 */
	__IO uint32_t DPI_CAL_RS_SEL ;                         /*!<  CAL_RS_SEL register,  Address offset: 0x508 */
	__IO uint32_t DPI_CAL_RS_SEL_1 ;                       /*!<  CAL_RS_SEL_1 register,  Address offset: 0x50C */
	__IO uint32_t DPI_CAL_RS_SEL_DBI ;                     /*!<  CAL_RS_SEL_DBI register,  Address offset: 0x510 */
	__IO uint32_t DPI_CAL_RS_SEL_DBI_1 ;                   /*!<  CAL_RS_SEL_DBI_1 register,  Address offset: 0x514 */
	__IO uint32_t DPI_DQ_IO_CTL_2 ;                        /*!<  DQ_IO_CTL_2 register,  Address offset: 0x518 */
	__IO uint32_t DPI_DQ_IO_CTL_2_1 ;                      /*!<  DQ_IO_CTL_2_1 register,  Address offset: 0x51C */
	__IO uint32_t DPI_READ_CTRL_4 ;                        /*!<  READ_CTRL_4 register,  Address offset: 0x520 */
	__IO uint32_t DPI_READ_CTRL_4_1 ;                      /*!<  READ_CTRL_4_1 register,  Address offset: 0x524 */
	__IO uint32_t RSVD9[52];                               /*!<  Reserved,  Address offset:0x528-0x5F4 */
	__IO uint32_t DPI_READ_CTRL_0_0 ;                      /*!<  READ_CTRL_0_0 register,  Address offset: 0x5F8 */
	__IO uint32_t DPI_READ_CTRL_0_1 ;                      /*!<  READ_CTRL_0_1 register,         Address offset: 0x5FC */
} DPI_TypeDef;
/** @} */

#endif
