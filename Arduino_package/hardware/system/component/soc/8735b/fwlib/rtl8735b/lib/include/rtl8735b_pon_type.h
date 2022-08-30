#ifndef _RTL8735B_PON_TYPE_H_
#define _RTL8735B_PON_TYPE_H_
#include "platform_conf.h"

/**************************************************************************//**
 * @defgroup PON_REG_PON_SYSON_CTRL
 * @brief                                            (@ 0X000)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PERIPLL_CTRL_SEL                   20
#define PON_BIT_PERIPLL_CTRL_SEL                     ((u32)0x00000001 << 20)                             /*!<R/W 0  1: PERIPLL control comes from PON register 0x018bit[10:5], 0x020[31:16], 0: PERIPLL control comes from hardware logic mux(as what we have done in TEST chip). */
#define PON_SHIFT_SYSPLL_CTRL_SEL                    19
#define PON_BIT_SYSPLL_CTRL_SEL                      ((u32)0x00000001 << 19)                             /*!<R/W 0  1: SYSPLL control comes from PON register 0x008bit[10:5], 0x010[31:16], 0: SYSPLL control comes from hardware logic mux(as what we have done in TEST chip). */
#define PON_SHIFT_PERIPLL_GATE                       18
#define PON_BIT_PERIPLL_GATE                         ((u32)0x00000001 << 18)                             /*!<R/W 0  0: PeriPLL gating */
#define PON_SHIFT_SYSPLL_GATE                        17
#define PON_BIT_SYSPLL_GATE                          ((u32)0x00000001 << 17)                             /*!<R/W 0  0: SYSPLL gating */
#define PON_SHIFT_PER1_RST_N                         16
#define PON_BIT_PER1_RST_N                           ((u32)0x00000001 << 16)                             /*!<R/W 1  0: Peri1 reset */
#define PON_SHIFT_PER0_RST_N                         15
#define PON_BIT_PER0_RST_N                           ((u32)0x00000001 << 15)                             /*!<R/W 1  0: Peri0 reset */
#define PON_SHIFT_BUS1_RST_N                         14
#define PON_BIT_BUS1_RST_N                           ((u32)0x00000001 << 14)                             /*!<R/W 1  0: Bus1 reset */
#define PON_SHIFT_BUS0_RST_N                         13
#define PON_BIT_BUS0_RST_N                           ((u32)0x00000001 << 13)                             /*!<R/W 1  0: Bus0 reset */
#define PON_SHIFT_PLATFORM_EN                        12
#define PON_BIT_PLATFORM_EN                          ((u32)0x00000001 << 12)                             /*!<R/W 0  1: enable platform */
#define PON_SHIFT_TM9_EN                             11
#define PON_BIT_TM9_EN                               ((u32)0x00000001 << 11)                             /*!<R/W 0  1: enable TM9 ; 0: reset */
#define PON_SHIFT_PLATFORM_CLK_EN                    10
#define PON_BIT_PLATFORM_CLK_EN                      ((u32)0x00000001 << 10)                             /*!<R/W 0  1: enable HS platform clock ; */
#define PON_SHIFT_TM9_CLK_EN                         9
#define PON_BIT_TM9_CLK_EN                           ((u32)0x00000001 << 9)                              /*!<R/W 0  1: enable TM9 clock ; 0: reset */
#define PON_SHIFT_ISO_PERIPLL                        8
#define PON_BIT_ISO_PERIPLL                          ((u32)0x00000001 << 8)                              /*!<R/W 1  1: isolation PeriPLL to PON domain; 0: disable isolation */
#define PON_SHIFT_ISO_SYSPLL                         7
#define PON_BIT_ISO_SYSPLL                           ((u32)0x00000001 << 7)                              /*!<R/W 1  1: isolation SYSPLL to PON domain; 0: disable isolation */
#define PON_SHIFT_VENDOR_REG_EN                      6
#define PON_BIT_VENDOR_REG_EN                        ((u32)0x00000001 << 6)                              /*!<R/W 0  1: enable VENDOR register */
#define PON_SHIFT_VENDOR_CLK_EN                      5
#define PON_BIT_VENDOR_CLK_EN                        ((u32)0x00000001 << 5)                              /*!<R/W 0  1: enable VENDOR register clock */
#define PON_SHIFT_SYSON_REG_EN                       4
#define PON_BIT_SYSON_REG_EN                         ((u32)0x00000001 << 4)                              /*!<R/W 0  1: enable SYSON register */
#define PON_SHIFT_SYSON_CLK_EN                       2
#define PON_BIT_SYSON_CLK_EN                         ((u32)0x00000001 << 2)                              /*!<R/W 0  1: enable SYSON register clock */
#define PON_SHIFT_SYSON_LPC_EN                       1
#define PON_BIT_SYSON_LPC_EN                         ((u32)0x00000001 << 1)                              /*!<R/W 0  System on domain large power 0:Disable, 1: Enable */
#define PON_SHIFT_SYSON_SPC_EN                       0
#define PON_BIT_SYSON_SPC_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 0  System on domain small power 0:Disable, 1: Enable */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_SYSPLL_CTRL0
 * @brief                                            (@ 0X004)
 * @{
 *****************************************************************************/
#define PON_SHIFT_POW_ERC_SYS                        31
#define PON_BIT_POW_ERC_SYS                          ((u32)0x00000001 << 31)                             /*!<R/W 0  erc enable. */
#define PON_SHIFT_POW_DIV_IN_SYS                     30
#define PON_BIT_POW_DIV_IN_SYS                       ((u32)0x00000001 << 30)                             /*!<R/W 0  input divider enable (need pwl signal) 0 ->1 */
#define PON_SHIFT_POW_PLL_SYS                        29
#define PON_BIT_POW_PLL_SYS                          ((u32)0x00000001 << 29)                             /*!<R/W 0  (need pwl signal) 0 ->1 */
#define PON_SHIFT_REG_CP_BIA_SYS                     26
#define PON_MASK_REG_CP_BIA_SYS                      ((u32)0x00000007 << 26)                             /*!<R/W 000  charge pump current selection . Default=10uA CP current select : 000: Icp=10uA, 001: Icp=15uA, 010: Icp=20uA, 011: Icp=25uA; 100: Icp=30uA, 101: Icp=35uA, 110: Icp=40uA, 111: Icp=450uA;  */
#define PON_SHIFT_DOGENB_SYS                         25
#define PON_BIT_DOGENB_SYS                           ((u32)0x00000001 << 25)                             /*!<R/W 0  0: watch dog on, 1: watch dog off */
#define PON_SHIFT_REG_PS_SYS                         22
#define PON_MASK_REG_PS_SYS                          ((u32)0x00000007 << 22)                             /*!<R/W 000   */
#define PON_SHIFT_REG_PSEN_SYS                       21
#define PON_BIT_REG_PSEN_SYS                         ((u32)0x00000001 << 21)                             /*!<R/W 1  phase selector enable */
#define PON_SHIFT_REG_CP_SET_SYS                     19
#define PON_MASK_REG_CP_SET_SYS                      ((u32)0x00000003 << 19)                             /*!<R/W 11  Cp selection. Default=6p 00: Cp=3p, 01: Cp=4p, 10: Cp=5p, 11: Cp=6p */
#define PON_SHIFT_REG_RS_SET_SYS                     16
#define PON_MASK_REG_RS_SET_SYS                      ((u32)0x00000007 << 16)                             /*!<R/W 101  Rs selection. Default=7k 000: Rs=15k, 001: Rs=13k, 010: Rs=11k, 011: Rs=9k, 100: Rs=7k, 101: Rs=5k, 110: Rs=3k, 111: Rs=1k;  */
#define PON_SHIFT_REG_CS_SEL_SYS                     14
#define PON_MASK_REG_CS_SEL_SYS                      ((u32)0x00000003 << 14)                             /*!<R/W 10  Cs selection. Default=60p 00: Cs=30p, 01: Cs=40p, 10: Cs=50p, 11: Cs=60p */
#define PON_SHIFT_REG_FREF_EDGE_SYS                  13
#define PON_BIT_REG_FREF_EDGE_SYS                    ((u32)0x00000001 << 13)                             /*!<R/W 1  0:fref, 1:frefb */
#define PON_SHIFT_REG_CK_EN_SYS                      12
#define PON_BIT_REG_CK_EN_SYS                        ((u32)0x00000001 << 12)                             /*!<R/W 1  output clk enable */
#define PON_SHIFT_REG_CK_EN_D2_SYS                   11
#define PON_BIT_REG_CK_EN_D2_SYS                     ((u32)0x00000001 << 11)                             /*!<R/W 0  output clk div 2 enable */
#define PON_SHIFT_REG_CK_OUT_SEL_SYS0                8
#define PON_MASK_REG_CK_OUT_SEL_SYS0                 ((u32)0x00000007 << 8)                              /*!<R/W 000  reserved */
#define PON_SHIFT_REG_XTAL_MANUAL_MODE_SYS           7
#define PON_BIT_REG_XTAL_MANUAL_MODE_SYS             ((u32)0x00000001 << 7)                              /*!<R/W 1  reg_xtal_maunal_mode. Default=0 0: reg_xtal_sel<3:0> is controlled by REG, xtal_div_sel is controlled by mapping table. 1: reg_xtal_sel<3:0>=4'b1111, xtal_div_sel is controlled by reg_xtal_div_sel_maunal<1:0> */
#define PON_SHIFT_REG_XTAL_DIV_SEL_MANUAL_SYS        5
#define PON_MASK_REG_XTAL_DIV_SEL_MANUAL_SYS         ((u32)0x00000003 << 5)                              /*!<R/W 00  input divider selection in xtal maunal mode. Default=00 00=/1, 01=/2, 1X=/4 */
#define PON_SHIFT_REG_VC_THL_SYS                     3
#define PON_MASK_REG_VC_THL_SYS                      ((u32)0x00000003 << 3)                              /*!<R/W 00  VC voltage, Default=00 00: VC=1/4Vdd, 01: VC=1/2Vdd, 10=3/4Vdd, 11: VC=Vdd */
#define PON_SHIFT_C3_SET_SYS                         1
#define PON_MASK_C3_SET_SYS                          ((u32)0x00000003 << 1)                              /*!<R/W 0   */
#define PON_SHIFT_R3_SET_SYS                         0
#define PON_BIT_R3_SET_SYS                           ((u32)0x00000001 << 0)                              /*!<R/W 1  Rs selection. Default=1k 0: 0 Ohm, 1: 1k Ohm */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_SYSPLL_CTRL1
 * @brief                                            (@ 0X008)
 * @{
 *****************************************************************************/
#define PON_SHIFT_REG_XTAL_SEL_SYS                   28
#define PON_MASK_REG_XTAL_SEL_SYS                    ((u32)0x0000000F << 28)                             /*!<R 0000  xtal selection, Default=40MHz 0000= 40MHz, 0001= 25MHz, 0010= 13MHz, 0011= 19.2MHz 0100= 20MHz, 0101= 26MHz, 0110= 38.4MHz, 0111= 17.664MHz 1000= 16MHz, 1001= 14.138MHz, 1010= 12MHz, 1011= 52MHz 1100= 48MHz, 1101= 27MHz, 1110= 24MHz, 1111= none  */
#define PON_SHIFT_REG_FREQ_SEL_SYS                   24
#define PON_MASK_REG_FREQ_SEL_SYS                    ((u32)0x0000000F << 24)                             /*!<R/W 0000  output clk selection, Default=500MHz 0000= 400MHz, 0001= 300MHz, 0010= X, 0011= X, 0100= 216MHz, 0101=196.608MHz, 0110=192MHz, 0111= 180.632MHz, 1000= 148.5MHz, 1001= X, 1010= X, 1011= X, 1100= X, 1101= X, 1110= X, 1111= 500MHz  */
#define PON_SHIFT_TBASE_FREQ_SYS                     20
#define PON_MASK_TBASE_FREQ_SYS                      ((u32)0x0000000F << 20)                             /*!<R/W 0000   */
#define PON_SHIFT_STEP_FREQ_SYS                      16
#define PON_MASK_STEP_FREQ_SYS                       ((u32)0x0000000F << 16)                             /*!<R/W 0000  step size selection for switching freq. */
#define PON_SHIFT_TRIG_FREQ_SYS                      15
#define PON_BIT_TRIG_FREQ_SYS                        ((u32)0x00000001 << 15)                             /*!<R/W 0  freq. step up or step down enable */
#define PON_SHIFT_BB_DBG_SEL_AFE_SDM_SYS             11
#define PON_MASK_BB_DBG_SEL_AFE_SDM_SYS              ((u32)0x0000000F << 11)                             /*!<R/W 0000   */
#define PON_SHIFT_DIVN_SDM_SYS                       5
#define PON_MASK_DIVN_SDM_SYS                        ((u32)0x0000003F << 5)                              /*!<R/W 1010  500M 40M: 001010 26M: 010001 300M 40M: 000101 26M: 001001 */
#define PON_SHIFT_REG_CK_OUT_SEL_SYS1                1
#define PON_MASK_REG_CK_OUT_SEL_SYS1                 ((u32)0x0000000F << 1)                              /*!<R/W 0000  output divider selection. Default=0000 0000=/1, 1000=/2 or /4, 1100=/8, 1110=/16, 1111=/32 */
#define PON_SHIFT_ICP_HALF_SYS                       0
#define PON_BIT_ICP_HALF_SYS                         ((u32)0x00000001 << 0)                              /*!<R/W 1  charge pump current half or not 0: no half 1: half */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_SYSPLL_CTRL2
 * @brief                                            (@ 0X00C)
 * @{
 *****************************************************************************/
#define PON_SHIFT_STEP_SYS                           19
#define PON_MASK_STEP_SYS                            ((u32)0x00001FFF << 19)                             /*!<R/W 0000000000000  ssc step size selection. */
#define PON_SHIFT_TBASE_SYS                          7
#define PON_MASK_TBASE_SYS                           ((u32)0x00000FFF << 7)                              /*!<R/W 000000000000  ssc freq selection */
#define PON_SHIFT_EN_SSC_SYS                         6
#define PON_BIT_EN_SSC_SYS                           ((u32)0x00000001 << 6)                              /*!<R/W 0  ssc enable. Default=0 */
#define PON_SHIFT_PLL_SYS2                           0
#define PON_MASK_PLL_SYS2                            ((u32)0x0000003F << 0)                              /*!<R/W 000000   */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_SYSPLL_CTRL3
 * @brief                                            (@ 0X010)
 * @{
 *****************************************************************************/
#define PON_SHIFT_F0F_SDM_SYS                        19
#define PON_MASK_F0F_SDM_SYS                         ((u32)0x00001FFF << 19)                             /*!<R/W 0000000000000  500M 40M: 0_0000_0000_0000 26M: 1_1011_0001_0100 300M 40M: 0_0000_0000_0000 26M: 0_1001_1101_1001 */
#define PON_SHIFT_F0N_SDM_SYS                        16
#define PON_MASK_F0N_SDM_SYS                         ((u32)0x00000007 << 16)                             /*!<R/W 100  500M 40M: 100 26M: 011 300M 40M: 100 26M: 100 */
#define PON_SHIFT_ORDER_SDM_SYS                      15
#define PON_BIT_ORDER_SDM_SYS                        ((u32)0x00000001 << 15)                             /*!<R/W 0  SDM order */
#define PON_SHIFT_PLL_SYS3                           0
#define PON_MASK_PLL_SYS3                            ((u32)0x00007FFF << 0)                              /*!<R/W 000000000000000   */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_PERIPLL_CTRL0
 * @brief                                            (@ 0X014)
 * @{
 *****************************************************************************/
#define PON_SHIFT_POW_ERC_PERI                       31
#define PON_BIT_POW_ERC_PERI                         ((u32)0x00000001 << 31)                             /*!<R/W 0  erc enable. */
#define PON_SHIFT_POW_DIV_IN_PERI                    30
#define PON_BIT_POW_DIV_IN_PERI                      ((u32)0x00000001 << 30)                             /*!<R/W 0  input divider enable (need pwl signal) 0 ->1 */
#define PON_SHIFT_POW_PLL_PERI                       29
#define PON_BIT_POW_PLL_PERI                         ((u32)0x00000001 << 29)                             /*!<R/W 0  (need pwl signal) 0 -> 1 */
#define PON_SHIFT_REG_CP_BIA_PERI                    26
#define PON_MASK_REG_CP_BIA_PERI                     ((u32)0x00000007 << 26)                             /*!<R/W 000  charge pump current selection . Default=10uA CP current select : 000: Icp=10uA, 001: Icp=15uA, 010: Icp=20uA, 011: Icp=25uA; 100: Icp=30uA, 101: Icp=35uA, 110: Icp=40uA, 111: Icp=450uA;  */
#define PON_SHIFT_DOGENB_PERI                        25
#define PON_BIT_DOGENB_PERI                          ((u32)0x00000001 << 25)                             /*!<R/W 0  0: watch dog on, 1: watch dog off */
#define PON_SHIFT_REG_PS_PERI                        22
#define PON_MASK_REG_PS_PERI                         ((u32)0x00000007 << 22)                             /*!<R/W 000   */
#define PON_SHIFT_REG_PSEN_PERI                      21
#define PON_BIT_REG_PSEN_PERI                        ((u32)0x00000001 << 21)                             /*!<R/W 1  phase selector enable */
#define PON_SHIFT_REG_CP_SET_PERI                    19
#define PON_MASK_REG_CP_SET_PERI                     ((u32)0x00000003 << 19)                             /*!<R/W 11  Cp selection. Default=6p 00: Cp=3p, 01: Cp=4p, 10: Cp=5p, 11: Cp=6p */
#define PON_SHIFT_REG_RS_SET_PERI                    16
#define PON_MASK_REG_RS_SET_PERI                     ((u32)0x00000007 << 16)                             /*!<R/W 101  Rs selection. Default=7k 000: Rs=15k, 001: Rs=13k, 010: Rs=11k, 011: Rs=9k, 100: Rs=7k, 101: Rs=5k, 110: Rs=3k, 111: Rs=1k;  */
#define PON_SHIFT_REG_CS_SEL_PERI                    14
#define PON_MASK_REG_CS_SEL_PERI                     ((u32)0x00000003 << 14)                             /*!<R/W 10  Cs selection. Default=60p 00: Cs=30p, 01: Cs=40p, 10: Cs=50p, 11: Cs=60p */
#define PON_SHIFT_REG_FREF_EDGE_PERI                 13
#define PON_BIT_REG_FREF_EDGE_PERI                   ((u32)0x00000001 << 13)                             /*!<R/W 1  0:fref, 1:frefb */
#define PON_SHIFT_REG_CK_EN_PERI                     12
#define PON_BIT_REG_CK_EN_PERI                       ((u32)0x00000001 << 12)                             /*!<R/W 1  output clk enable */
#define PON_SHIFT_REG_CK_EN_D2_PERI                  11
#define PON_BIT_REG_CK_EN_D2_PERI                    ((u32)0x00000001 << 11)                             /*!<R/W 0  output clk div 4 enable */
#define PON_SHIFT_REG_CK_OUT_SEL_PERI0               8
#define PON_MASK_REG_CK_OUT_SEL_PERI0                ((u32)0x00000007 << 8)                              /*!<R/W 000  reserved */
#define PON_SHIFT_REG_XTAL_MANUAL_MODE_PERI          7
#define PON_BIT_REG_XTAL_MANUAL_MODE_PERI            ((u32)0x00000001 << 7)                              /*!<R/W 1  reg_xtal_maunal_mode. Default=0 0: reg_xtal_sel<3:0> is controlled by REG, xtal_div_sel is controlled by mapping table. 1: reg_xtal_sel<3:0>=4'b1111, xtal_div_sel is controlled by reg_xtal_div_sel_maunal<1:0> */
#define PON_SHIFT_REG_XTAL_DIV_SEL_MANUAL_PERI       5
#define PON_MASK_REG_XTAL_DIV_SEL_MANUAL_PERI        ((u32)0x00000003 << 5)                              /*!<R/W 00  input divider selection in xtal maunal mode. Default=00 00=/1, 01=/2, 1X=/4 */
#define PON_SHIFT_REG_VC_THL_PERI                    3
#define PON_MASK_REG_VC_THL_PERI                     ((u32)0x00000003 << 3)                              /*!<R/W 00  VC voltage, Default=00 00: VC=1/4Vdd, 01: VC=1/2Vdd, 10=3/4Vdd, 11: VC=Vdd */
#define PON_SHIFT_C3_SET_PERI                        1
#define PON_MASK_C3_SET_PERI                         ((u32)0x00000003 << 1)                              /*!<R/W 0   */
#define PON_SHIFT_R3_SET_PERI                        0
#define PON_BIT_R3_SET_PERI                          ((u32)0x00000001 << 0)                              /*!<R/W 1  Rs selection. Default=1k 0: 0 Ohm, 1: 1k Ohm */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_PERIPLL_CTRL1
 * @brief                                            (@ 0X018)
 * @{
 *****************************************************************************/
#define PON_SHIFT_REG_XTAL_SEL_PERI                  28
#define PON_MASK_REG_XTAL_SEL_PERI                   ((u32)0x0000000F << 28)                             /*!<R 0000  xtal selection, Default=40MHz 0000= 40MHz, 0001= 25MHz, 0010= 13MHz, 0011= 19.2MHz 0100= 20MHz, 0101= 26MHz, 0110= 38.4MHz, 0111= 17.664MHz 1000= 16MHz, 1001= 14.138MHz, 1010= 12MHz, 1011= 52MHz 1100= 48MHz, 1101= 27MHz, 1110= 24MHz, 1111= none  */
#define PON_SHIFT_REG_FREQ_SEL_PERI                  24
#define PON_MASK_REG_FREQ_SEL_PERI                   ((u32)0x0000000F << 24)                             /*!<R/W 0000  output clk selection, Default=400MHz 0000= 400MHz, 0001= X, 0010= X, 0011= X, 0100= 216MHz, 0101=196.608MHz, 0110=192MHz, 0111= 180.632MHz, 1000= 148.5MHz,1001= X, 1010= X, 1011= X, 1100= X, 1101= X, 1110= X, 1111= 500MHz  */
#define PON_SHIFT_TBASE_FREQ_PERI                    20
#define PON_MASK_TBASE_FREQ_PERI                     ((u32)0x0000000F << 20)                             /*!<R/W 0000   */
#define PON_SHIFT_STEP_FREQ_PERI                     16
#define PON_MASK_STEP_FREQ_PERI                      ((u32)0x0000000F << 16)                             /*!<R/W 0000  step size selection for switching freq. 0000: 2^5 0001: 2^6 0010: 2^7 0011: 2^8 0100: 2^9 0101: 2^10 0110: 2^11 0111: 2^12 */
#define PON_SHIFT_TRIG_FREQ_PERI                     15
#define PON_BIT_TRIG_FREQ_PERI                       ((u32)0x00000001 << 15)                             /*!<R/W 0  freq. step up or step down enable */
#define PON_SHIFT_BB_DBG_SEL_AFE_SDM_PERI            11
#define PON_MASK_BB_DBG_SEL_AFE_SDM_PERI             ((u32)0x0000000F << 11)                             /*!<R/W 0000   */
#define PON_SHIFT_DIVN_SDM_PERI                      5
#define PON_MASK_DIVN_SDM_PERI                       ((u32)0x0000003F << 5)                              /*!<R/W 1000  400M 40M: 001000 26M: 001101  */
#define PON_SHIFT_REG_CK_OUT_SEL_PERI1               1
#define PON_MASK_REG_CK_OUT_SEL_PERI1                ((u32)0x0000000F << 1)                              /*!<R/W 0000  output divider selection. Default=0000 0000=/1, 1000=/2 or /4, 1100=/8, 1110=/16, 1111=/32 */
#define PON_SHIFT_ICP_HALF_PERI                      0
#define PON_BIT_ICP_HALF_PERI                        ((u32)0x00000001 << 0)                              /*!<R/W 1  charge pump current half or not 0: no half 1: half */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_PERIPLL_CTRL2
 * @brief                                            (@ 0X01C)
 * @{
 *****************************************************************************/
#define PON_SHIFT_STEP_PERI                          19
#define PON_MASK_STEP_PERI                           ((u32)0x00001FFF << 19)                             /*!<R/W 0000000000000  ssc step size selection. */
#define PON_SHIFT_TBASE_PERI                         7
#define PON_MASK_TBASE_PERI                          ((u32)0x00000FFF << 7)                              /*!<R/W 000000000000  ssc freq selection */
#define PON_SHIFT_EN_SSC_PERI                        6
#define PON_BIT_EN_SSC_PERI                          ((u32)0x00000001 << 6)                              /*!<R/W 0  ssc enable. Default=0 */
#define PON_SHIFT_PLL_PERI2                          0
#define PON_MASK_PLL_PERI2                           ((u32)0x0000003F << 0)                              /*!<R/W 000000   */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_PERIPLL_CTRL3
 * @brief                                            (@ 0X020)
 * @{
 *****************************************************************************/
#define PON_SHIFT_F0F_SDM_PERI                       19
#define PON_MASK_F0F_SDM_PERI                        ((u32)0x00001FFF << 19)                             /*!<R/W 0000000000000  400M 40M: 0_0000_0000_0000 26M: 0_0010_0111_0110 */
#define PON_SHIFT_F0N_SDM_PERI                       16
#define PON_MASK_F0N_SDM_PERI                        ((u32)0x00000007 << 16)                             /*!<R/W 000  400M 40M: 000 26M: 011  */
#define PON_SHIFT_ORDER_SDM_PERI                     15
#define PON_BIT_ORDER_SDM_PERI                       ((u32)0x00000001 << 15)                             /*!<R/W 0  SDM order */
#define PON_SHIFT_PLL_PERI3                          0
#define PON_MASK_PLL_PERI3                           ((u32)0x00007FFF << 0)                              /*!<R/W 000000000000000   */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_FUNC_EN_CTRL
 * @brief                                            (@ 0X024)
 * @{
 *****************************************************************************/
#define PON_SHIFT_GPIO_EN                            3
#define PON_BIT_GPIO_EN                              ((u32)0x00000001 << 3)                              /*!<R/W 0  1: Enable PON GPIO block */
#define PON_SHIFT_PWM_EN                             2
#define PON_BIT_PWM_EN                               ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable PWM block */
#define PON_SHIFT_TIMER0_EN                          1
#define PON_BIT_TIMER0_EN                            ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable TIMER0 block */
#define PON_SHIFT_UART0_EN                           0
#define PON_BIT_UART0_EN                             ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable UART0 block */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_PLL_DBG
 * @brief                                            (@ 0X028)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PLL_TEST                           13
#define PON_MASK_PLL_TEST                            ((u32)0x00000007 << 13)                             /*!<R/W 000   */
#define PON_SHIFT_REG0X_TEST                         12
#define PON_BIT_REG0X_TEST                           ((u32)0x00000001 << 12)                             /*!<R/W 0  0 = ckmon , 1 = ckmon/4 */
#define PON_SHIFT_POW_DIV4                           11
#define PON_BIT_POW_DIV4                             ((u32)0x00000001 << 11)                             /*!<R/W 1  pow of divider4 */
#define PON_SHIFT_ISO                                10
#define PON_BIT_ISO                                  ((u32)0x00000001 << 10)                             /*!<R/W 0  1 for ISO ck_fref/ck_frefb */
#define PON_SHIFT_REF_CLK_SEL                        9
#define PON_BIT_REF_CLK_SEL                          ((u32)0x00000001 << 9)                              /*!<R/W 0  xtal clk from 0 special route 1 APR */
#define PON_SHIFT_CK_MON_EN                          8
#define PON_BIT_CK_MON_EN                            ((u32)0x00000001 << 8)                              /*!<R/W 0  ckmon enable */
#define PON_SHIFT_CK_SEL                             4
#define PON_MASK_CK_SEL                              ((u32)0x0000000F << 4)                              /*!<R/W 0000  ckmon clk sel 1111:CK_400M_ISP 1110:READY_400M 1101:CK_ISPS 1100:READY_ISPS 1011:CK_300M_SYS 1010:READY_300M 1001:CK_240M_ENC 1000:READY_240M_ENC 0111:CK_80M_PERI 0110:READY_80M_PERI 0101:CK_98P304M_I2S 0100:CK_24P576M_I2S 0011:READY_I2S 0010:CK_45P158M_PCM 0001:READY_45P158M_PCM 0000:TL */
#define PON_SHIFT_APGIO_DRIVE                        2
#define PON_MASK_APGIO_DRIVE                         ((u32)0x00000003 << 2)                              /*!<R/W 11  AGPIO driving sel */
#define PON_SHIFT_GPO                                1
#define PON_BIT_GPO                                  ((u32)0x00000001 << 1)                              /*!<R/W 0  AGPIO CLK SEL 0=external 1=pll */
#define PON_SHIFT_GPE                                0
#define PON_BIT_GPE                                  ((u32)0x00000001 << 0)                              /*!<R/W 0  AGPIO enable */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_FUNC_CLK_CTRL
 * @brief                                            (@ 0X02C)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DUMMY_GPIO                         27
#define PON_MASK_DUMMY_GPIO                          ((u32)0x0000001F << 27)                             /*!<R/W 0   */
#define PON_SHIFT_INTR_CLK_GPIO_SEL                  26
#define PON_BIT_INTR_CLK_GPIO_SEL                    ((u32)0x00000001 << 26)                             /*!<R/W 0  Interrupt Clock Select 0:APB CLK 1:32kHz */
#define PON_SHIFT_SCLK_GPIO_EN                       25
#define PON_BIT_SCLK_GPIO_EN                         ((u32)0x00000001 << 25)                             /*!<R/W 0  1: Enable GPIO Sclock */
#define PON_SHIFT_PCLK_GPIO_EN                       24
#define PON_BIT_PCLK_GPIO_EN                         ((u32)0x00000001 << 24)                             /*!<R/W 0  1: Enable GPIO Pclock */
#define PON_SHIFT_RSVD1                              23
#define PON_BIT_RSVD1                                ((u32)0x00000001 << 23)                             /*!<R/W 0   */
#define PON_SHIFT_DUMMY_PWM                          21
#define PON_MASK_DUMMY_PWM                           ((u32)0x00000003 << 21)                             /*!<R/W 0   */
#define PON_SHIFT_INTR_CLK_PWM_SEL                   20
#define PON_BIT_INTR_CLK_PWM_SEL                     ((u32)0x00000001 << 20)                             /*!<R/W 0  Interrupt Clock Select 0:APB CLK 1:TIMER0 CLK */
#define PON_SHIFT_SCLK_PWM_SEL                       18
#define PON_MASK_SCLK_PWM_SEL                        ((u32)0x00000003 << 18)                             /*!<R/W 00  PWM Sclock Select 00:32KHz(S1) 01:IRC_4MHz(ANA_CLK) 10:PERI_PLL_40MHz 11:RSVD */
#define PON_SHIFT_SCLK_PWM_EN                        17
#define PON_BIT_SCLK_PWM_EN                          ((u32)0x00000001 << 17)                             /*!<R/W 0  1: Enable PWM Sclock */
#define PON_SHIFT_PCLK_PWM_EN                        16
#define PON_BIT_PCLK_PWM_EN                          ((u32)0x00000001 << 16)                             /*!<R/W 0  1: Enable PWM Pclock */
#define PON_SHIFT_RSVD2                              15
#define PON_BIT_RSVD2                                ((u32)0x00000001 << 15)                             /*!<R/W 0   */
#define PON_SHIFT_DUMMY_TIMER0                       13
#define PON_MASK_DUMMY_TIMER0                        ((u32)0x00000003 << 13)                             /*!<R/W 0   */
#define PON_SHIFT_INTR_CLK_TIMER0_SEL                12
#define PON_BIT_INTR_CLK_TIMER0_SEL                  ((u32)0x00000001 << 12)                             /*!<R/W 0  Interrupt Clock Select 0:APB CLK 1:TIMER0 CLK */
#define PON_SHIFT_SCLK_TIMER0_SEL                    10
#define PON_MASK_SCLK_TIMER0_SEL                     ((u32)0x00000003 << 10)                             /*!<R/W 00  TIMER0 Sclock Select 00:32KHz(S1) 01:IRC_4MHz(ANA_CLK) 10:PERI_PLL_40MHz 11:RSVD */
#define PON_SHIFT_SCLK_TIMER0_EN                     9
#define PON_BIT_SCLK_TIMER0_EN                       ((u32)0x00000001 << 9)                              /*!<R/W 0  1: Enable TIMER0 Sclock */
#define PON_SHIFT_PCLK_TIMER0_EN                     8
#define PON_BIT_PCLK_TIMER0_EN                       ((u32)0x00000001 << 8)                              /*!<R/W 0  1: Enable TIMER0 Pclock */
#define PON_SHIFT_RSVD3                              7
#define PON_BIT_RSVD3                                ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define PON_SHIFT_DUMMY_UART0                        5
#define PON_MASK_DUMMY_UART0                         ((u32)0x00000003 << 5)                              /*!<R/W 0   */
#define PON_SHIFT_SCLK_UART0_SEL                     3
#define PON_MASK_SCLK_UART0_SEL                      ((u32)0x00000003 << 3)                              /*!<R/W 00  UART0 Sclock Select 00:IRC_4MHz(ANA_CLK) 01:PERI_PLL_40MHz 10:XTAL Clock 40MHz 11:RSVD */
#define PON_SHIFT_SCLK_UART0_EN                      2
#define PON_BIT_SCLK_UART0_EN                        ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable UART0 Sclock */
#define PON_SHIFT_PCLK_UART0_EN                      1
#define PON_BIT_PCLK_UART0_EN                        ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable UART0 Pclock */
#define PON_SHIFT_UART0_BD_EN                        0
#define PON_BIT_UART0_BD_EN                          ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable UART0 bus domain */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_BT_CTRL
 * @brief                                            (@ 0X030)
 * @{
 *****************************************************************************/
#define PON_SHIFT_BT_SEL                             4
#define PON_BIT_BT_SEL                               ((u32)0x00000001 << 4)                              /*!<R/W 0  0: Internal, 1:External */
#define PON_SHIFT_BT_MP_I2C_EN                       3
#define PON_BIT_BT_MP_I2C_EN                         ((u32)0x00000001 << 3)                              /*!<R/W 0  1: Enable */
#define PON_SHIFT_40MCLK_BT_EN                       2
#define PON_BIT_40MCLK_BT_EN                         ((u32)0x00000001 << 2)                              /*!<R/W 0  1: enable BT 40MHz clock */
#define PON_SHIFT_32KCLK_BT_EN                       1
#define PON_BIT_32KCLK_BT_EN                         ((u32)0x00000001 << 1)                              /*!<R/W 0  1: enable BT 32kHz clock */
#define PON_SHIFT_BT_EN                              0
#define PON_BIT_BT_EN                                ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enale BT block; 0: Reset BT block */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_UART_INTR_STS
 * @brief                                            (@ 0X034)
 * @{
 *****************************************************************************/
#define PON_SHIFT_UART0_ISR                          0
#define PON_BIT_UART0_ISR                            ((u32)0x00000001 << 0)                              /*!<R 0  UART0 Interrupt Status */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_WDT_RST_CTRL
 * @brief                                            (@ 0X038)
 * @{
 *****************************************************************************/
#define PON_SHIFT_RSVD4                              5
#define PON_MASK_RSVD4                               ((u32)0x07FFFFFF << 5)                              /*!<R/W 0   */
#define PON_SHIFT_SYSON_WDT_RST_MSK                  4
#define PON_BIT_SYSON_WDT_RST_MSK                    ((u32)0x00000001 << 4)                              /*!<R/W 0  1: Enable WDOG_RST to reset SYSON block */
#define PON_SHIFT_CPU_WDT_RST_MSK                    3
#define PON_BIT_CPU_WDT_RST_MSK                      ((u32)0x00000001 << 3)                              /*!<R/W 0  0: Enable WDOG_RST to trigger CPU wram reset 1: Enable WDOG_RST to trigger CPU cold reset */
#define PON_SHIFT_WLON_WDT_RST_MSK                   2
#define PON_BIT_WLON_WDT_RST_MSK                     ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable WDOG_RST to reset WLON block */
#define PON_SHIFT_PON_WDT_RST_MSK                    1
#define PON_BIT_PON_WDT_RST_MSK                      ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable WDOG_RST to reset PON block */
#define PON_SHIFT_AON_WDT_RST_MSK                    0
#define PON_BIT_AON_WDT_RST_MSK                      ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable WDOG_RST to reset AON block */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_BUS_CTRL
 * @brief                                            (@ 0X03C)
 * @{
 *****************************************************************************/
#define PON_SHIFT_SRAM1_RET                          3
#define PON_BIT_SRAM1_RET                            ((u32)0x00000001 << 3)                              /*!<R/W 0  1: SRAM1 Retention Mode */
#define PON_SHIFT_SRAM1_SD                           2
#define PON_BIT_SRAM1_SD                             ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Shutdown SRAM1 */
#define PON_SHIFT_SRAM0_RET                          1
#define PON_BIT_SRAM0_RET                            ((u32)0x00000001 << 1)                              /*!<R/W 0  1: SRAM0 Retention Mode */
#define PON_SHIFT_SRAM0_SD                           0
#define PON_BIT_SRAM0_SD                             ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Shutdown SRAM0 */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_PLL_DIVIDER_CTRL
 * @brief                                            (@ 0X040)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DIVIDER_PERI                       15
#define PON_MASK_DIVIDER_PERI                        ((u32)0x0000001F << 15)                             /*!<R/W 0  Div:N+1,N=0~31 */
#define PON_SHIFT_DIVIDER_C6                         10
#define PON_MASK_DIVIDER_C6                          ((u32)0x0000001F << 10)                             /*!<R/W 0x5  Div:N+1,N=0~31, >= 5 to C6 divider register and invalid number(<5) write to the register will be ignored. */
#define PON_SHIFT_DIVIDER_C5                         5
#define PON_MASK_DIVIDER_C5                          ((u32)0x0000001F << 5)                              /*!<R/W 0x2  Div:N+1,N=0~31, >= 2 to C5 divider registe and invalid number (<2)write to the register will be ignored. */
#define PON_SHIFT_DIVIDER_SYS                        0
#define PON_MASK_DIVIDER_SYS                         ((u32)0x0000001F << 0)                              /*!<R/W 0  Div:N+1,N=0~31 */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_SUPER_SEC_EF_CTRL
 * @brief                                            (@ 0X044)
 * @{
 *****************************************************************************/
#define PON_SHIFT_SEC_SUPER_SEC_OTP_LOCK             0
#define PON_BIT_SEC_SUPER_SEC_OTP_LOCK               ((u32)0x00000001 << 0)                              /*!<R/W 1 Once 0  Lock OTP Super Secure Zone 1: Lock OTP Super Secure zone; 0: Unlock OTP Super Secure zone "When this bit is written to '1', this bit cannot be written to "0", unless the platform reset. */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_BOOT_STATE
 * @brief                                            (@ 0X048)
 * @{
 *****************************************************************************/
#define PON_SHIFT_BOOT_STATE                         0
#define PON_MASK_BOOT_STATE                          ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   For SW use */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_BOOT_STATE1
 * @brief                                            (@ 0X04C)
 * @{
 *****************************************************************************/
#define PON_SHIFT_UUID3                              24
#define PON_MASK_UUID3                               ((u32)0x000000FF << 24)                             /*!<R/W Once 0xFF   For SW use */
#define PON_SHIFT_UUID2                              16
#define PON_MASK_UUID2                               ((u32)0x000000FF << 16)                             /*!<R/W Once 0xFF   For SW use */
#define PON_SHIFT_UUID1                              8
#define PON_MASK_UUID1                               ((u32)0x000000FF << 8)                              /*!<R/W Once 0xFF   For SW use */
#define PON_SHIFT_UUID0                              0
#define PON_MASK_UUID0                               ((u32)0x000000FF << 0)                              /*!<R/W Once 0xFF   For SW use */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_GPIOF_0_1_CTRL
 * @brief                                            (@ 0X050)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PON_GPIO1_SLEW_RATE                28
#define PON_BIT_PON_GPIO1_SLEW_RATE                  ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO1_DRIVING                  26
#define PON_MASK_PON_GPIO1_DRIVING                   ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO1_SMT_EN                   25
#define PON_BIT_PON_GPIO1_SMT_EN                     ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable PON GPIO1 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO1_PULL_CTRL                22
#define PON_MASK_PON_GPIO1_PULL_CTRL                 ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO1_PINMUX_SEL               16
#define PON_MASK_PON_GPIO1_PINMUX_SEL                ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: ADC1 0001: I2C1_SCL 0010: 0011: RFE_CTRL_0 0100: 0101: 0110:UART1_CTS 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define PON_SHIFT_PON_GPIO0_SLEW_RATE                12
#define PON_BIT_PON_GPIO0_SLEW_RATE                  ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO0_DRIVING                  10
#define PON_MASK_PON_GPIO0_DRIVING                   ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO0_SMT_EN                   9
#define PON_BIT_PON_GPIO0_SMT_EN                     ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable PON GPIO0 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO0_PULL_CTRL                6
#define PON_MASK_PON_GPIO0_PULL_CTRL                 ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO0_PINMUX_SEL               0
#define PON_MASK_PON_GPIO0_PINMUX_SEL                ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: ADC0 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_GPIOF_2_3_CTRL
 * @brief                                            (@ 0X054)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PON_GPIO3_SLEW_RATE                28
#define PON_BIT_PON_GPIO3_SLEW_RATE                  ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO3_DRIVING                  26
#define PON_MASK_PON_GPIO3_DRIVING                   ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO3_SMT_EN                   25
#define PON_BIT_PON_GPIO3_SMT_EN                     ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable PON GPIO3 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO3_PULL_CTRL                22
#define PON_MASK_PON_GPIO3_PULL_CTRL                 ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO3_PINMUX_SEL               16
#define PON_MASK_PON_GPIO3_PINMUX_SEL                ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: ADC3 0001: 0010: 0011: RFE_CTRL_2 0100: SDIO_D2 0101: 0110:UART1_IN 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define PON_SHIFT_PON_GPIO2_SLEW_RATE                12
#define PON_BIT_PON_GPIO2_SLEW_RATE                  ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO2_DRIVING                  10
#define PON_MASK_PON_GPIO2_DRIVING                   ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO2_SMT_EN                   9
#define PON_BIT_PON_GPIO2_SMT_EN                     ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable PON GPIO2 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO2_PULL_CTRL                6
#define PON_MASK_PON_GPIO2_PULL_CTRL                 ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO2_PINMUX_SEL               0
#define PON_MASK_PON_GPIO2_PINMUX_SEL                ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: ADC2 0001: I2C1_SDA 0010: 0011: RFE_CTRL_1 0100: 0101: 0110:UART1_RTS 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_GPIOF_4_5_CTRL
 * @brief                                            (@ 0X058)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PON_GPIO5_SLEW_RATE                28
#define PON_BIT_PON_GPIO5_SLEW_RATE                  ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO5_DRIVING                  26
#define PON_MASK_PON_GPIO5_DRIVING                   ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO5_SMT_EN                   25
#define PON_BIT_PON_GPIO5_SMT_EN                     ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable PON GPIO5 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO5_PULL_CTRL                22
#define PON_MASK_PON_GPIO5_PULL_CTRL                 ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO5_PINMUX_SEL               16
#define PON_MASK_PON_GPIO5_PINMUX_SEL                ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: 0011: 0100:SDIO_D0 0101:SPI_1_MISO 0110:TPIU_DATA_0 0111: 1000: SPI_3_MISO 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define PON_SHIFT_PON_GPIO4_SLEW_RATE                12
#define PON_BIT_PON_GPIO4_SLEW_RATE                  ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO4_DRIVING                  10
#define PON_MASK_PON_GPIO4_DRIVING                   ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO4_SMT_EN                   9
#define PON_BIT_PON_GPIO4_SMT_EN                     ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable PON GPIO4 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO4_PULL_CTRL                6
#define PON_MASK_PON_GPIO4_PULL_CTRL                 ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO4_PINMUX_SEL               0
#define PON_MASK_PON_GPIO4_PINMUX_SEL                ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: 0010: 0011: 0100: SDIO_D1 0101: 0110:UART1_OUT 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_GPIOF_6_7_CTRL
 * @brief                                            (@ 0X05C)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PON_GPIO7_SLEW_RATE                28
#define PON_BIT_PON_GPIO7_SLEW_RATE                  ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO7_DRIVING                  26
#define PON_MASK_PON_GPIO7_DRIVING                   ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO7_SMT_EN                   25
#define PON_BIT_PON_GPIO7_SMT_EN                     ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable PON GPIO7 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO7_PULL_CTRL                22
#define PON_MASK_PON_GPIO7_PULL_CTRL                 ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO7_PINMUX_SEL               16
#define PON_MASK_PON_GPIO7_PINMUX_SEL                ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: PWM1 0011: JTAG_TDI 0100:SDIO_CMD 0101:SPI_1_MOSI 0110:TPIU_DATA_2 0111: BT_JTAG_TDI 1000: SPI_3_MOSI 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define PON_SHIFT_PON_GPIO6_SLEW_RATE                12
#define PON_BIT_PON_GPIO6_SLEW_RATE                  ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO6_DRIVING                  10
#define PON_MASK_PON_GPIO6_DRIVING                   ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO6_SMT_EN                   9
#define PON_BIT_PON_GPIO6_SMT_EN                     ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable PON GPIO6 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO6_PULL_CTRL                6
#define PON_MASK_PON_GPIO6_PULL_CTRL                 ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO6_PINMUX_SEL               0
#define PON_MASK_PON_GPIO6_PINMUX_SEL                ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: 0010: PWM0 0011: JTAG_TDO 0100:SDIO_CLK 0101:SPI_1_SCL 0110:TPIU_DATA_1 0111: BT_JTAG_TDO 1000: SPI_3_SCL 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_GPIOF_8_9_CTRL
 * @brief                                            (@ 0X060)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PON_GPIO9_SLEW_RATE                28
#define PON_BIT_PON_GPIO9_SLEW_RATE                  ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO9_DRIVING                  26
#define PON_MASK_PON_GPIO9_DRIVING                   ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO9_SMT_EN                   25
#define PON_BIT_PON_GPIO9_SMT_EN                     ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable PON GPIO9 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO9_PULL_CTRL                22
#define PON_MASK_PON_GPIO9_PULL_CTRL                 ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO9_PINMUX_SEL               16
#define PON_MASK_PON_GPIO9_PINMUX_SEL                ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: SGPIO 0010: PWM3 0011: JTAG_CLK/SWD_CK 0100: 0101:SPI_1_CS1 0110:TPIU_CLK 0111: BT_JTAG_CLK/SWD_CK 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define PON_SHIFT_PON_GPIO8_SLEW_RATE                12
#define PON_BIT_PON_GPIO8_SLEW_RATE                  ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO8_DRIVING                  10
#define PON_MASK_PON_GPIO8_DRIVING                   ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO8_SMT_EN                   9
#define PON_BIT_PON_GPIO8_SMT_EN                     ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable PON GPIO8 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO8_PULL_CTRL                6
#define PON_MASK_PON_GPIO8_PULL_CTRL                 ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO8_PINMUX_SEL               0
#define PON_MASK_PON_GPIO8_PINMUX_SEL                ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: 0010: PWM2 0011: 0100:SDIO_D3 0101:SPI_1_CS0 0110:TPIU_DATA_3 0111: 1000: SPI_3_CS 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_GPIOF_10_11_CTRL
 * @brief                                            (@ 0X064)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PON_GPIO11_SLEW_RATE               28
#define PON_BIT_PON_GPIO11_SLEW_RATE                 ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO11_DRIVING                 26
#define PON_MASK_PON_GPIO11_DRIVING                  ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO11_SMT_EN                  25
#define PON_BIT_PON_GPIO11_SMT_EN                    ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable PON GPIO11 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO11_PULL_CTRL               22
#define PON_MASK_PON_GPIO11_PULL_CTRL                ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO11_PINMUX_SEL              16
#define PON_MASK_PON_GPIO11_PINMUX_SEL               ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: PWM5 0011: JTAG_TRST 0100: 0101:I2S0_MCK 0110: 0111: BT_JTAG_TRST 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define PON_SHIFT_PON_GPIO10_SLEW_RATE               12
#define PON_BIT_PON_GPIO10_SLEW_RATE                 ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO10_DRIVING                 10
#define PON_MASK_PON_GPIO10_DRIVING                  ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO10_SMT_EN                  9
#define PON_BIT_PON_GPIO10_SMT_EN                    ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable PON GPIO10 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO10_PULL_CTRL               6
#define PON_MASK_PON_GPIO10_PULL_CTRL                ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO10_PINMUX_SEL              0
#define PON_MASK_PON_GPIO10_PINMUX_SEL               ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: 0010: PWM4 0011: JTAG_TMS/SWD_IO 0100: 0101:SPI_1_CS2 0110: TPIU_CTRL 0111: BT_JTAG_TMS/SWD_IO 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_GPIOF_12_13_CTRL
 * @brief                                            (@ 0X068)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PON_GPIO13_SLEW_RATE               28
#define PON_BIT_PON_GPIO13_SLEW_RATE                 ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO13_DRIVING                 26
#define PON_MASK_PON_GPIO13_DRIVING                  ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO13_SMT_EN                  25
#define PON_BIT_PON_GPIO13_SMT_EN                    ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable PON GPIO13 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO13_PULL_CTRL               22
#define PON_MASK_PON_GPIO13_PULL_CTRL                ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO13_PINMUX_SEL              16
#define PON_MASK_PON_GPIO13_PINMUX_SEL               ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: PWM7 0011: 0100: 0101: I2S0_CLK 0110:UART1_OUT 0111: 1000:VOE_JTAG_TMS/SWD_IO 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define PON_SHIFT_PON_GPIO12_SLEW_RATE               12
#define PON_BIT_PON_GPIO12_SLEW_RATE                 ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO12_DRIVING                 10
#define PON_MASK_PON_GPIO12_DRIVING                  ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO12_SMT_EN                  9
#define PON_BIT_PON_GPIO12_SMT_EN                    ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable PON GPIO12 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO12_PULL_CTRL               6
#define PON_MASK_PON_GPIO12_PULL_CTRL                ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO12_PINMUX_SEL              0
#define PON_MASK_PON_GPIO12_PINMUX_SEL               ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: 0010: PWM6 0011: 0100: 0101:I2S0_SD_RX 0110:UART1_IN 0111: 1000:VOE_JTAG_CLK/SWD_CK 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_GPIOF_14_15_CTRL
 * @brief                                            (@ 0X06C)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PON_GPIO15_SLEW_RATE               28
#define PON_BIT_PON_GPIO15_SLEW_RATE                 ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO15_DRIVING                 26
#define PON_MASK_PON_GPIO15_DRIVING                  ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO15_SMT_EN                  25
#define PON_BIT_PON_GPIO15_SMT_EN                    ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable PON GPIO15 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO15_PULL_CTRL               22
#define PON_MASK_PON_GPIO15_PULL_CTRL                ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO15_PINMUX_SEL              16
#define PON_MASK_PON_GPIO15_PINMUX_SEL               ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: SGPIO_TX 0010: PWM9 0011: 0100: 0101:I2S0_WS 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define PON_SHIFT_PON_GPIO14_SLEW_RATE               12
#define PON_BIT_PON_GPIO14_SLEW_RATE                 ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO14_DRIVING                 10
#define PON_MASK_PON_GPIO14_DRIVING                  ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO14_SMT_EN                  9
#define PON_BIT_PON_GPIO14_SMT_EN                    ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable PON GPIO14 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO14_PULL_CTRL               6
#define PON_MASK_PON_GPIO14_PULL_CTRL                ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO14_PINMUX_SEL              0
#define PON_MASK_PON_GPIO14_PINMUX_SEL               ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: SGPIO 0010: PWM8 0011: 0100: 0101:I2S0_SD_TX0 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_PON_GPIOF_16_17_CTRL
 * @brief                                            (@ 0X070)
 * @{
 *****************************************************************************/
#define PON_SHIFT_PON_GPIO17_SLEW_RATE               28
#define PON_BIT_PON_GPIO17_SLEW_RATE                 ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO17_DRIVING                 26
#define PON_MASK_PON_GPIO17_DRIVING                  ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO17_SMT_EN                  25
#define PON_BIT_PON_GPIO17_SMT_EN                    ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable PON GPIO17 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO17_PULL_CTRL               22
#define PON_MASK_PON_GPIO17_PULL_CTRL                ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO17_PINMUX_SEL              16
#define PON_MASK_PON_GPIO17_PINMUX_SEL               ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: PWM11 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define PON_SHIFT_PON_GPIO16_SLEW_RATE               12
#define PON_BIT_PON_GPIO16_SLEW_RATE                 ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define PON_SHIFT_PON_GPIO16_DRIVING                 10
#define PON_MASK_PON_GPIO16_DRIVING                  ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define PON_SHIFT_PON_GPIO16_SMT_EN                  9
#define PON_BIT_PON_GPIO16_SMT_EN                    ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable PON GPIO16 Schmitt trigger; 1: enable */
#define PON_SHIFT_PON_GPIO16_PULL_CTRL               6
#define PON_MASK_PON_GPIO16_PULL_CTRL                ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define PON_SHIFT_PON_GPIO16_PINMUX_SEL              0
#define PON_MASK_PON_GPIO16_PINMUX_SEL               ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: 0010: PWM10 0011: 0100: 0101:SPI_1_CS3 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_RMA_CTRL0
 * @brief                                            (@ 0X074)
 * @{
 *****************************************************************************/
#define PON_SHIFT_RMA_STATE                          8
#define PON_MASK_RMA_STATE                           ((u32)0x000000FF << 8)                              /*!<R 0x0  0x00 (normal state, default value) 0xA0(RMA0) 0xA1(RMA1) 0xA2(RMA2) */
#define PON_SHIFT_PWD_EN                             0
#define PON_MASK_PWD_EN                              ((u32)0x000000FF << 0)                              /*!<R/W Once 0x0  password write enable 0x65(ASCII: e) is to enable write magic number 0x00 is default value */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_RMA_CTRL1
 * @brief                                            (@ 0X078)
 * @{
 *****************************************************************************/
#define PON_SHIFT_SSZ_RMA_LOCK                       1
#define PON_BIT_SSZ_RMA_LOCK                         ((u32)0x00000001 << 1)                              /*!<R/W Once 0x0  SSZ RMA lock (1 to enable lock) */
#define PON_SHIFT_SZ_RMA_LOCK                        0
#define PON_BIT_SZ_RMA_LOCK                          ((u32)0x00000001 << 0)                              /*!<R/W Once 0x0  SZ RMA lock (1 to enable lock) */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_BT_CNTRL
 * @brief                                            (@ 0X084)
 * @{
 *****************************************************************************/
#define PON_SHIFT_TMCK_BT_ROM                        11
#define PON_BIT_TMCK_BT_ROM                          ((u32)0x00000001 << 11)                             /*!<R/W 0x0  internal timing bypass BT_ROM */
#define PON_SHIFT_DVSE_BT_ROM                        10
#define PON_BIT_DVSE_BT_ROM                          ((u32)0x00000001 << 10)                             /*!<R/W 0x0  delay option enable BT_ROM */
#define PON_SHIFT_DVS_BT_ROM                         6
#define PON_MASK_DVS_BT_ROM                          ((u32)0x0000000F << 6)                              /*!<R/W 0x0  delay option BT_ROM */
#define PON_SHIFT_TMCK_BT_RAM                        5
#define PON_BIT_TMCK_BT_RAM                          ((u32)0x00000001 << 5)                              /*!<R/W 0x0  internal timing bypass BT_RAM */
#define PON_SHIFT_DVSE_BT_RAM                        4
#define PON_BIT_DVSE_BT_RAM                          ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable BT_RAM */
#define PON_SHIFT_DVS_BT_RAM                         0
#define PON_MASK_DVS_BT_RAM                          ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option BT_RAM */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_GMAC_CNTRL
 * @brief                                            (@ 0X088)
 * @{
 *****************************************************************************/
#define PON_SHIFT_NAP_GMAC_SRAM1                     13
#define PON_BIT_NAP_GMAC_SRAM1                       ((u32)0x00000001 << 13)                             /*!<R/W 0x0  nap: light sleep gmac_sram1 */
#define PON_SHIFT_TMCK_GMAC_SRAM1                    12
#define PON_BIT_TMCK_GMAC_SRAM1                      ((u32)0x00000001 << 12)                             /*!<R/W 0x0  internal timing bypass gmac_sram1 */
#define PON_SHIFT_DVSE_GMAC_SRAM1                    11
#define PON_BIT_DVSE_GMAC_SRAM1                      ((u32)0x00000001 << 11)                             /*!<R/W 0x0  delay option enable gmac_sram1 */
#define PON_SHIFT_DVS_GMAC_SRAM1                     7
#define PON_MASK_DVS_GMAC_SRAM1                      ((u32)0x0000000F << 7)                              /*!<R/W 0x0  delay option gmac_sram1 */
#define PON_SHIFT_NAP_GMAC_SRAM0                     6
#define PON_BIT_NAP_GMAC_SRAM0                       ((u32)0x00000001 << 6)                              /*!<R/W 0x0  nap: light sleep gmac_sram0 */
#define PON_SHIFT_TMCK_GMAC_SRAM0                    5
#define PON_BIT_TMCK_GMAC_SRAM0                      ((u32)0x00000001 << 5)                              /*!<R/W 0x0  internal timing bypass gmac_sram0 */
#define PON_SHIFT_DVSE_GMAC_SRAM0                    4
#define PON_BIT_DVSE_GMAC_SRAM0                      ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable gmac_sram0 */
#define PON_SHIFT_DVS_GMAC_SRAM0                     0
#define PON_MASK_DVS_GMAC_SRAM0                      ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option gmac_sram0 */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_ISP_CNTRL_0
 * @brief                                            (@ 0X08C)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_ISPF                          29
#define PON_BIT_DVSE_ISPF                            ((u32)0x00000001 << 29)                             /*!<R/W 0x0  delay option enable ispf */
#define PON_SHIFT_DVS_ISPF                           25
#define PON_MASK_DVS_ISPF                            ((u32)0x0000000F << 25)                             /*!<R/W 0x0  delay option ispf */
#define PON_SHIFT_DVSE_ISPE                          24
#define PON_BIT_DVSE_ISPE                            ((u32)0x00000001 << 24)                             /*!<R/W 0x0  delay option enable ispe */
#define PON_SHIFT_DVS_ISPE                           20
#define PON_MASK_DVS_ISPE                            ((u32)0x0000000F << 20)                             /*!<R/W 0x0  delay option ispe */
#define PON_SHIFT_DVSE_ISPD                          19
#define PON_BIT_DVSE_ISPD                            ((u32)0x00000001 << 19)                             /*!<R/W 0x0  delay option enable ispd */
#define PON_SHIFT_DVS_ISPD                           15
#define PON_MASK_DVS_ISPD                            ((u32)0x0000000F << 15)                             /*!<R/W 0x0  delay option ispd */
#define PON_SHIFT_DVSE_ISPC                          14
#define PON_BIT_DVSE_ISPC                            ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable ispc */
#define PON_SHIFT_DVS_ISPC                           10
#define PON_MASK_DVS_ISPC                            ((u32)0x0000000F << 10)                             /*!<R/W 0x0  delay option ispc */
#define PON_SHIFT_DVSE_ISPB                          9
#define PON_BIT_DVSE_ISPB                            ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable ispb */
#define PON_SHIFT_DVS_ISPB                           5
#define PON_MASK_DVS_ISPB                            ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option ispb */
#define PON_SHIFT_DVSE_ISPA                          4
#define PON_BIT_DVSE_ISPA                            ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable ispa */
#define PON_SHIFT_DVS_ISPA                           0
#define PON_MASK_DVS_ISPA                            ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option ispa */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_ISP_CNTRL_1
 * @brief                                            (@ 0X090)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_OSDBRIDGE                     29
#define PON_BIT_DVSE_OSDBRIDGE                       ((u32)0x00000001 << 29)                             /*!<R/W 0x0  delay option enable osdbridge */
#define PON_SHIFT_DVS_OSDBRIDGE                      25
#define PON_MASK_DVS_OSDBRIDGE                       ((u32)0x0000000F << 25)                             /*!<R/W 0x0  delay option osdbridge */
#define PON_SHIFT_DVSE_OSDPAINTER                    24
#define PON_BIT_DVSE_OSDPAINTER                      ((u32)0x00000001 << 24)                             /*!<R/W 0x0  delay option enable osdpainter */
#define PON_SHIFT_DVS_OSDPAINTER                     20
#define PON_MASK_DVS_OSDPAINTER                      ((u32)0x0000000F << 20)                             /*!<R/W 0x0  delay option osdpainter */
#define PON_SHIFT_DVSE_VIDEO_AMBA                    19
#define PON_BIT_DVSE_VIDEO_AMBA                      ((u32)0x00000001 << 19)                             /*!<R/W 0x0  delay option enable video_amba */
#define PON_SHIFT_DVS_VIDEO_AMBA                     15
#define PON_MASK_DVS_VIDEO_AMBA                      ((u32)0x0000000F << 15)                             /*!<R/W 0x0  delay option video_amba */
#define PON_SHIFT_DVSE_ISP_DMA3                      14
#define PON_BIT_DVSE_ISP_DMA3                        ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable isp_dma3 */
#define PON_SHIFT_DVS_ISP_DMA3                       10
#define PON_MASK_DVS_ISP_DMA3                        ((u32)0x0000000F << 10)                             /*!<R/W 0x0  delay option isp_dma3 */
#define PON_SHIFT_DVSE_ISPH                          9
#define PON_BIT_DVSE_ISPH                            ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable isph */
#define PON_SHIFT_DVS_ISPH                           5
#define PON_MASK_DVS_ISPH                            ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option isph */
#define PON_SHIFT_DVSE_ISPG                          4
#define PON_BIT_DVSE_ISPG                            ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable ispg */
#define PON_SHIFT_DVS_ISPG                           0
#define PON_MASK_DVS_ISPG                            ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option ispg */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_ISP_CNTRL_2
 * @brief                                            (@ 0X094)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_MIPI                          4
#define PON_BIT_DVSE_MIPI                            ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable mipi */
#define PON_SHIFT_DVS_MIPI                           0
#define PON_MASK_DVS_MIPI                            ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option mipi */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_COMM_CNTRL
 * @brief                                            (@ 0X098)
 * @{
 *****************************************************************************/
#define PON_SHIFT_NAP_USBOTG                         27
#define PON_BIT_NAP_USBOTG                           ((u32)0x00000001 << 27)                             /*!<R/W 0x0  nap: light sleep usbotg */
#define PON_SHIFT_TMCK_USBOTG                        26
#define PON_BIT_TMCK_USBOTG                          ((u32)0x00000001 << 26)                             /*!<R/W 0x0  internal timing bypass usbotg */
#define PON_SHIFT_DVSE_USBOTG                        25
#define PON_BIT_DVSE_USBOTG                          ((u32)0x00000001 << 25)                             /*!<R/W 0x0  delay option enable usbotg */
#define PON_SHIFT_DVS_USBOTG                         21
#define PON_MASK_DVS_USBOTG                          ((u32)0x0000000F << 21)                             /*!<R/W 0x0  delay option usbotg */
#define PON_SHIFT_NAP_SDMMC_PPBECC                   20
#define PON_BIT_NAP_SDMMC_PPBECC                     ((u32)0x00000001 << 20)                             /*!<R/W 0x0  nap: light sleep sdmmc_ppbecc */
#define PON_SHIFT_TMCK_SDMMC_PPBECC                  19
#define PON_BIT_TMCK_SDMMC_PPBECC                    ((u32)0x00000001 << 19)                             /*!<R/W 0x0  internal timing bypass sdmmc_ppbecc */
#define PON_SHIFT_DVSE_SDMMC_PPBECC                  18
#define PON_BIT_DVSE_SDMMC_PPBECC                    ((u32)0x00000001 << 18)                             /*!<R/W 0x0  delay option enable sdmmc_ppbecc */
#define PON_SHIFT_DVS_SDMMC_PPBECC                   14
#define PON_MASK_DVS_SDMMC_PPBECC                    ((u32)0x0000000F << 14)                             /*!<R/W 0x0  delay option sdmmc_ppbecc */
#define PON_SHIFT_NAP_SDMMC_DMASB0                   13
#define PON_BIT_NAP_SDMMC_DMASB0                     ((u32)0x00000001 << 13)                             /*!<R/W 0x0  nap: light sleep sdmmc_dmasb1 */
#define PON_SHIFT_TMCK_SDMMC_DMASB1                  12
#define PON_BIT_TMCK_SDMMC_DMASB1                    ((u32)0x00000001 << 12)                             /*!<R/W 0x0  internal timing bypass sdmmc_ppbecc */
#define PON_SHIFT_DVSE_SDMMC_DMASB1                  11
#define PON_BIT_DVSE_SDMMC_DMASB1                    ((u32)0x00000001 << 11)                             /*!<R/W 0x0  delay option enable sdmmc_dmasb1 */
#define PON_SHIFT_DVS_SDMMC_DMASB1                   7
#define PON_MASK_DVS_SDMMC_DMASB1                    ((u32)0x0000000F << 7)                              /*!<R/W 0x0  delay option sdmmc_dmasb1 */
#define PON_SHIFT_NAP_SDIO                           6
#define PON_BIT_NAP_SDIO                             ((u32)0x00000001 << 6)                              /*!<R/W 0x0  nap: light sleep sdio */
#define PON_SHIFT_TMCK_SDIO                          5
#define PON_BIT_TMCK_SDIO                            ((u32)0x00000001 << 5)                              /*!<R/W 0x0  internal timing bypass sdio */
#define PON_SHIFT_DVSE_SDIO                          4
#define PON_BIT_DVSE_SDIO                            ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable sdio */
#define PON_SHIFT_DVS_SDIO                           0
#define PON_MASK_DVS_SDIO                            ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option sdio */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_CPU_CNTRL
 * @brief                                            (@ 0X09C)
 * @{
 *****************************************************************************/
#define PON_SHIFT_TMCK_CPU_MEM                       5
#define PON_BIT_TMCK_CPU_MEM                         ((u32)0x00000001 << 5)                              /*!<R/W 0x0  internal timing bypass cpu_dtcm_ram */
#define PON_SHIFT_DVSE_CPU_MEM                       4
#define PON_BIT_DVSE_CPU_MEM                         ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable cpu_dtcm_ram */
#define PON_SHIFT_DVS_CPU_MEM                        0
#define PON_MASK_DVS_CPU_MEM                         ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option cpu_dtcm_ram */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_NN_CNTRL_0
 * @brief                                            (@ 0X0A0)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_NN_CLKCORE_G5                 29
#define PON_BIT_DVSE_NN_CLKCORE_G5                   ((u32)0x00000001 << 29)                             /*!<R/W 0x0  delay option enable nn_clkCore_g5 */
#define PON_SHIFT_DVS_NN_CLKCORE_G5                  25
#define PON_MASK_DVS_NN_CLKCORE_G5                   ((u32)0x0000000F << 25)                             /*!<R/W 0x0  delay option nn_clkCore_g5 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G4                 24
#define PON_BIT_DVSE_NN_CLKCORE_G4                   ((u32)0x00000001 << 24)                             /*!<R/W 0x0  delay option enable nn_clkCore_g4 */
#define PON_SHIFT_DVS_NN_CLKCORE_G4                  20
#define PON_MASK_DVS_NN_CLKCORE_G4                   ((u32)0x0000000F << 20)                             /*!<R/W 0x0  delay option nn_clkCore_g4 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G3                 19
#define PON_BIT_DVSE_NN_CLKCORE_G3                   ((u32)0x00000001 << 19)                             /*!<R/W 0x0  delay option enable nn_clkCore_g3 */
#define PON_SHIFT_DVS_NN_CLKCORE_G3                  15
#define PON_MASK_DVS_NN_CLKCORE_G3                   ((u32)0x0000000F << 15)                             /*!<R/W 0x0  delay option nn_clkCore_g3 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G2                 14
#define PON_BIT_DVSE_NN_CLKCORE_G2                   ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable nn_clkCore_g2 */
#define PON_SHIFT_DVS_NN_CLKCORE_G2                  10
#define PON_MASK_DVS_NN_CLKCORE_G2                   ((u32)0x0000000F << 10)                             /*!<R/W 0x0  delay option nn_clkCore_g2 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G1                 9
#define PON_BIT_DVSE_NN_CLKCORE_G1                   ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable nn_clkCore_g1 */
#define PON_SHIFT_DVS_NN_CLKCORE_G1                  5
#define PON_MASK_DVS_NN_CLKCORE_G1                   ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option nn_clkCore_g1 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G0                 4
#define PON_BIT_DVSE_NN_CLKCORE_G0                   ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable nn_clkCore_g0 */
#define PON_SHIFT_DVS_NN_CLKCORE_G0                  0
#define PON_MASK_DVS_NN_CLKCORE_G0                   ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option nn_clkCore_g0 */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_NN_CNTRL_1
 * @brief                                            (@ 0X0A4)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_NN_CLKCORE_G11                29
#define PON_BIT_DVSE_NN_CLKCORE_G11                  ((u32)0x00000001 << 29)                             /*!<R/W 0x0  delay option enable nn_clkCore_g11 */
#define PON_SHIFT_DVS_NN_CLKCORE_G11                 25
#define PON_MASK_DVS_NN_CLKCORE_G11                  ((u32)0x0000000F << 25)                             /*!<R/W 0x0  delay option nn_clkCore_g11 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G10                24
#define PON_BIT_DVSE_NN_CLKCORE_G10                  ((u32)0x00000001 << 24)                             /*!<R/W 0x0  delay option enable nn_clkCore_g10 */
#define PON_SHIFT_DVS_NN_CLKCORE_G10                 20
#define PON_MASK_DVS_NN_CLKCORE_G10                  ((u32)0x0000000F << 20)                             /*!<R/W 0x0  delay option nn_clkCore_g10 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G9                 19
#define PON_BIT_DVSE_NN_CLKCORE_G9                   ((u32)0x00000001 << 19)                             /*!<R/W 0x0  delay option enable nn_clkCore_g9 */
#define PON_SHIFT_DVS_NN_CLKCORE_G9                  15
#define PON_MASK_DVS_NN_CLKCORE_G9                   ((u32)0x0000000F << 15)                             /*!<R/W 0x0  delay option nn_clkCore_g9 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G8                 14
#define PON_BIT_DVSE_NN_CLKCORE_G8                   ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable nn_clkCore_g8 */
#define PON_SHIFT_DVS_NN_CLKCORE_G8                  10
#define PON_MASK_DVS_NN_CLKCORE_G8                   ((u32)0x0000000F << 10)                             /*!<R/W 0x0  delay option nn_clkCore_g8 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G7                 9
#define PON_BIT_DVSE_NN_CLKCORE_G7                   ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable nn_clkCore_g7 */
#define PON_SHIFT_DVS_NN_CLKCORE_G7                  5
#define PON_MASK_DVS_NN_CLKCORE_G7                   ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option nn_clkCore_g7 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G6                 4
#define PON_BIT_DVSE_NN_CLKCORE_G6                   ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable nn_clkCore_g6 */
#define PON_SHIFT_DVS_NN_CLKCORE_G6                  0
#define PON_MASK_DVS_NN_CLKCORE_G6                   ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option nn_clkCore_g6 */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_NN_CNTRL_2
 * @brief                                            (@ 0X0A8)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_NN_CLKCORE_G17                29
#define PON_BIT_DVSE_NN_CLKCORE_G17                  ((u32)0x00000001 << 29)                             /*!<R/W 0x0  delay option enable nn_clkCore_g17 */
#define PON_SHIFT_DVS_NN_CLKCORE_G17                 25
#define PON_MASK_DVS_NN_CLKCORE_G17                  ((u32)0x0000000F << 25)                             /*!<R/W 0x0  delay option nn_clkCore_g17 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G16                24
#define PON_BIT_DVSE_NN_CLKCORE_G16                  ((u32)0x00000001 << 24)                             /*!<R/W 0x0  delay option enable nn_clkCore_g16 */
#define PON_SHIFT_DVS_NN_CLKCORE_G16                 20
#define PON_MASK_DVS_NN_CLKCORE_G16                  ((u32)0x0000000F << 20)                             /*!<R/W 0x0  delay option nn_clkCore_g16 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G15                19
#define PON_BIT_DVSE_NN_CLKCORE_G15                  ((u32)0x00000001 << 19)                             /*!<R/W 0x0  delay option enable nn_clkCore_g15 */
#define PON_SHIFT_DVS_NN_CLKCORE_G15                 15
#define PON_MASK_DVS_NN_CLKCORE_G15                  ((u32)0x0000000F << 15)                             /*!<R/W 0x0  delay option nn_clkCore_g15 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G14                14
#define PON_BIT_DVSE_NN_CLKCORE_G14                  ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable nn_clkCore_g14 */
#define PON_SHIFT_DVS_NN_CLKCORE_G14                 10
#define PON_MASK_DVS_NN_CLKCORE_G14                  ((u32)0x0000000F << 10)                             /*!<R/W 0x0  delay option nn_clkCore_g14 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G13                9
#define PON_BIT_DVSE_NN_CLKCORE_G13                  ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable nn_clkCore_g13 */
#define PON_SHIFT_DVS_NN_CLKCORE_G13                 5
#define PON_MASK_DVS_NN_CLKCORE_G13                  ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option nn_clkCore_g13 */
#define PON_SHIFT_DVSE_NN_CLKCORE_G12                4
#define PON_BIT_DVSE_NN_CLKCORE_G12                  ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable nn_clkCore_g12 */
#define PON_SHIFT_DVS_NN_CLKCORE_G12                 0
#define PON_MASK_DVS_NN_CLKCORE_G12                  ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option nn_clkCore_g12 */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_NN_CNTRL_3
 * @brief                                            (@ 0X0AC)
 * @{
 *****************************************************************************/
#define PON_SHIFT_SLP_NN                             13
#define PON_BIT_SLP_NN                               ((u32)0x00000001 << 13)                             /*!<R/W 0x0  sleep: NN */
#define PON_SHIFT_RET_NN                             12
#define PON_BIT_RET_NN                               ((u32)0x00000001 << 12)                             /*!<R/W 0x0  ret: retention NN */
#define PON_SHIFT_NAP_NN                             11
#define PON_BIT_NAP_NN                               ((u32)0x00000001 << 11)                             /*!<R/W 0x0  nap: light sleep NN */
#define PON_SHIFT_TMCK_NN                            10
#define PON_BIT_TMCK_NN                              ((u32)0x00000001 << 10)                             /*!<R/W 0x0  internal timing bypass NN */
#define PON_SHIFT_DVSE_NN_CLKSH_DIV2                 9
#define PON_BIT_DVSE_NN_CLKSH_DIV2                   ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable nn_clkSh_div2 */
#define PON_SHIFT_DVS_NN_CLKSH_DIV2                  5
#define PON_MASK_DVS_NN_CLKSH_DIV2                   ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option nn_clkSh_div2 */
#define PON_SHIFT_DVSE_NN_ACLK                       4
#define PON_BIT_DVSE_NN_ACLK                         ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable nn_ACLK */
#define PON_SHIFT_DVS_NN_ACLK                        0
#define PON_MASK_DVS_NN_ACLK                         ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option nn_ACLK */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_VOE_CNTRL_0
 * @brief                                            (@ 0X0B0)
 * @{
 *****************************************************************************/
#define PON_SHIFT_TMCK_VOE                           31
#define PON_BIT_TMCK_VOE                             ((u32)0x00000001 << 31)                             /*!<R/W 0x0  tmck: internal timing bypass VOE */
#define PON_SHIFT_NAP_VOE                            30
#define PON_BIT_NAP_VOE                              ((u32)0x00000001 << 30)                             /*!<R/W 0x0  nap :light sleep VOE */
#define PON_SHIFT_DVSE_VOEMCU_ITCM_ROM               29
#define PON_BIT_DVSE_VOEMCU_ITCM_ROM                 ((u32)0x00000001 << 29)                             /*!<R/W 0x0  delay option enable mbist_voemcu_itcm_rom */
#define PON_SHIFT_DVS_VOEMCU_ITCM_ROM                25
#define PON_MASK_DVS_VOEMCU_ITCM_ROM                 ((u32)0x0000000F << 25)                             /*!<R/W 0x0  delay_option voemcu_itcm_rom */
#define PON_SHIFT_DVSE_VOEMCU_ITCM_RAM               24
#define PON_BIT_DVSE_VOEMCU_ITCM_RAM                 ((u32)0x00000001 << 24)                             /*!<R/W 0x0  delay option enable mbist_voemcu_itcm_ram */
#define PON_SHIFT_DVS_VOEMCU_ITCM_RAM                20
#define PON_MASK_DVS_VOEMCU_ITCM_RAM                 ((u32)0x0000000F << 20)                             /*!<R/W 0x0  delay_option voemcu_itcm_ram */
#define PON_SHIFT_DVSE_VOEMCU_DTCM_ROM               19
#define PON_BIT_DVSE_VOEMCU_DTCM_ROM                 ((u32)0x00000001 << 19)                             /*!<R/W 0x0  delay option enable mbist_voemcu_dtcm_rom */
#define PON_SHIFT_DVS_VOEMCU_DTCM_ROM                15
#define PON_MASK_DVS_VOEMCU_DTCM_ROM                 ((u32)0x0000000F << 15)                             /*!<R/W 0x0  delay_option voemcu_dtcm_rom */
#define PON_SHIFT_DVSE_VOEMCU_DTCM                   14
#define PON_BIT_DVSE_VOEMCU_DTCM                     ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable mbist_voemcu_dtcm */
#define PON_SHIFT_DVS_VOEMCU_DTCM                    10
#define PON_MASK_DVS_VOEMCU_DTCM                     ((u32)0x0000000F << 10)                             /*!<R/W 0x0  delay_option voemcu_dtcm */
#define PON_SHIFT_DVSE_VOE_CPU_ICACHE                9
#define PON_BIT_DVSE_VOE_CPU_ICACHE                  ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable mbist_voe_cpu_icache */
#define PON_SHIFT_DVS_VOE_CPU_ICACHE                 5
#define PON_MASK_DVS_VOE_CPU_ICACHE                  ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay_option voe_cpu_icache */
#define PON_SHIFT_DVSE_VOE_CPU_DCACHE                4
#define PON_BIT_DVSE_VOE_CPU_DCACHE                  ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable mbist_voe_cpu_dcache */
#define PON_SHIFT_DVS_VOE_CPU_DCACHE                 0
#define PON_MASK_DVS_VOE_CPU_DCACHE                  ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay_option voe_cpu_dcache */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_PLATFORM_CNTRL
 * @brief                                            (@ 0X0B4)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_DDRC                          14
#define PON_BIT_DVSE_DDRC                            ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable DDRC */
#define PON_SHIFT_DVS_DDRC                           10
#define PON_MASK_DVS_DDRC                            ((u32)0x0000000F << 10)                             /*!<R/W 0x0  delay option DDRC */
#define PON_SHIFT_DVSE_PLATFORM_ROM                  9
#define PON_BIT_DVSE_PLATFORM_ROM                    ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable PLATFORM_ROM */
#define PON_SHIFT_DVS_PLATFORM_ROM                   5
#define PON_MASK_DVS_PLATFORM_ROM                    ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option PLATFORM_ROM */
#define PON_SHIFT_DVSE_PLATFORM_RAM                  4
#define PON_BIT_DVSE_PLATFORM_RAM                    ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable PLATFORM_RAM */
#define PON_SHIFT_DVS_PLATFORM_RAM                   0
#define PON_MASK_DVS_PLATFORM_RAM                    ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option PLATFORM_RAM */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_ENC_CNTRL_0
 * @brief                                            (@ 0X0B8)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_ENC_GROUP05_1                 29
#define PON_BIT_DVSE_ENC_GROUP05_1                   ((u32)0x00000001 << 29)                             /*!<R/W 0x0  delay option enable mbist_enc_group05_1 */
#define PON_SHIFT_DVS_ENC_GROUP05_1                  25
#define PON_MASK_DVS_ENC_GROUP05_1                   ((u32)0x0000000F << 25)                             /*!<R/W 0x0  delay option mbist_enc_group05_1 */
#define PON_SHIFT_DVSE_ENC_GROUP04                   24
#define PON_BIT_DVSE_ENC_GROUP04                     ((u32)0x00000001 << 24)                             /*!<R/W 0x0  delay option enable mbist_enc_group04 */
#define PON_SHIFT_DVS_ENC_GROUP04                    20
#define PON_MASK_DVS_ENC_GROUP04                     ((u32)0x0000000F << 20)                             /*!<R/W 0x0  delay option mbist_enc_group04 */
#define PON_SHIFT_DVSE_ENC_GROUP03_2                 19
#define PON_BIT_DVSE_ENC_GROUP03_2                   ((u32)0x00000001 << 19)                             /*!<R/W 0x0  delay option enable mbist_enc_group03_2 */
#define PON_SHIFT_DVS_ENC_GROUP03_2                  15
#define PON_MASK_DVS_ENC_GROUP03_2                   ((u32)0x0000000F << 15)                             /*!<R/W 0x0  delay option mbist_enc_group03_2 */
#define PON_SHIFT_DVSE_ENC_GROUP03_1                 14
#define PON_BIT_DVSE_ENC_GROUP03_1                   ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable mbist_enc_group03_1 */
#define PON_SHIFT_DVS_ENC_GROUP03_1                  10
#define PON_MASK_DVS_ENC_GROUP03_1                   ((u32)0x0000000F << 10)                             /*!<R/W 0x0  delay option mbist_enc_group03_1 */
#define PON_SHIFT_DVSE_ENC_GROUP02                   9
#define PON_BIT_DVSE_ENC_GROUP02                     ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable mbist_enc_group02 */
#define PON_SHIFT_DVS_ENC_GROUP02                    5
#define PON_MASK_DVS_ENC_GROUP02                     ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option mbist_enc_group02 */
#define PON_SHIFT_DVSE_ENC_GROUP01                   4
#define PON_BIT_DVSE_ENC_GROUP01                     ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable mbist_enc_group01 */
#define PON_SHIFT_DVS_ENC_GROUP01                    0
#define PON_MASK_DVS_ENC_GROUP01                     ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option mbist_enc_group01 */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_ENC_CNTRL_1
 * @brief                                            (@ 0X0BC)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_ENC_GROUP10_1                 29
#define PON_BIT_DVSE_ENC_GROUP10_1                   ((u32)0x00000001 << 29)                             /*!<R/W 0x0  delay option enable mbist_enc_group10_1 */
#define PON_SHIFT_DVS_ENC_GROUP10_1                  25
#define PON_MASK_DVS_ENC_GROUP10_1                   ((u32)0x0000000F << 25)                             /*!<R/W 0x0  delay option mbist_enc_group10_1 */
#define PON_SHIFT_DVSE_ENC_GROUP09                   24
#define PON_BIT_DVSE_ENC_GROUP09                     ((u32)0x00000001 << 24)                             /*!<R/W 0x0  delay option enable mbist_enc_group09 */
#define PON_SHIFT_DVS_ENC_GROUP09                    20
#define PON_MASK_DVS_ENC_GROUP09                     ((u32)0x0000000F << 20)                             /*!<R/W 0x0  delay option mbist_enc_group09 */
#define PON_SHIFT_DVSE_ENC_GROUP08                   19
#define PON_BIT_DVSE_ENC_GROUP08                     ((u32)0x00000001 << 19)                             /*!<R/W 0x0  delay option enable mbist_enc_group08 */
#define PON_SHIFT_DVS_ENC_GROUP08                    15
#define PON_MASK_DVS_ENC_GROUP08                     ((u32)0x0000000F << 15)                             /*!<R/W 0x0  delay option mbist_enc_group08 */
#define PON_SHIFT_DVSE_ENC_GROUP07                   14
#define PON_BIT_DVSE_ENC_GROUP07                     ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable mbist_enc_group07 */
#define PON_SHIFT_DVS_ENC_GROUP07                    10
#define PON_MASK_DVS_ENC_GROUP07                     ((u32)0x0000000F << 10)                             /*!<R/W 0x0  delay option mbist_enc_group07 */
#define PON_SHIFT_DVSE_ENC_GROUP06                   9
#define PON_BIT_DVSE_ENC_GROUP06                     ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable mbist_enc_group06 */
#define PON_SHIFT_DVS_ENC_GROUP06                    5
#define PON_MASK_DVS_ENC_GROUP06                     ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option mbist_enc_group06 */
#define PON_SHIFT_DVSE_ENC_GROUP05_2                 4
#define PON_BIT_DVSE_ENC_GROUP05_2                   ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable mbist_enc_group05_2 */
#define PON_SHIFT_DVS_ENC_GROUP05_2                  0
#define PON_MASK_DVS_ENC_GROUP05_2                   ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option mbist_enc_group05_2 */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_ENC_CNTRL_2
 * @brief                                            (@ 0X0C0)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_ENC_GROUP13_1                 29
#define PON_BIT_DVSE_ENC_GROUP13_1                   ((u32)0x00000001 << 29)                             /*!<R/W 0x0  delay option enable mbist_enc_group13_1 */
#define PON_SHIFT_DVS_ENC_GROUP13_1                  25
#define PON_MASK_DVS_ENC_GROUP13_1                   ((u32)0x0000000F << 25)                             /*!<R/W 0x0  delay option mbist_enc_group13_1 */
#define PON_SHIFT_DVSE_ENC_GROUP12_2                 24
#define PON_BIT_DVSE_ENC_GROUP12_2                   ((u32)0x00000001 << 24)                             /*!<R/W 0x0  delay option enable mbist_enc_group12_2 */
#define PON_SHIFT_DVS_ENC_GROUP12_2                  20
#define PON_MASK_DVS_ENC_GROUP12_2                   ((u32)0x0000000F << 20)                             /*!<R/W 0x0  delay option mbist_enc_group12_2 */
#define PON_SHIFT_DVSE_ENC_GROUP12_1                 19
#define PON_BIT_DVSE_ENC_GROUP12_1                   ((u32)0x00000001 << 19)                             /*!<R/W 0x0  delay option enable mbist_enc_group12_1 */
#define PON_SHIFT_DVS_ENC_GROUP12_1                  15
#define PON_MASK_DVS_ENC_GROUP12_1                   ((u32)0x0000000F << 15)                             /*!<R/W 0x0  delay option mbist_enc_group12_1 */
#define PON_SHIFT_DVSE_ENC_GROUP11_2                 14
#define PON_BIT_DVSE_ENC_GROUP11_2                   ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable mbist_enc_group11_2 */
#define PON_SHIFT_DVS_ENC_GROUP11_2                  10
#define PON_MASK_DVS_ENC_GROUP11_2                   ((u32)0x0000000F << 10)                             /*!<R/W 0x0  delay option mbist_enc_group11_2 */
#define PON_SHIFT_DVSE_ENC_GROUP11_1                 9
#define PON_BIT_DVSE_ENC_GROUP11_1                   ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable mbist_enc_group11_1 */
#define PON_SHIFT_DVS_ENC_GROUP11_1                  5
#define PON_MASK_DVS_ENC_GROUP11_1                   ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option mbist_enc_group11_1 */
#define PON_SHIFT_DVSE_ENC_GROUP10_2                 4
#define PON_BIT_DVSE_ENC_GROUP10_2                   ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable mbist_enc_group10_2 */
#define PON_SHIFT_DVS_ENC_GROUP10_2                  0
#define PON_MASK_DVS_ENC_GROUP10_2                   ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option mbist_enc_group10_2 */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_ENC_CNTRL_3
 * @brief                                            (@ 0X0C4)
 * @{
 *****************************************************************************/
#define PON_SHIFT_NAP_ENCODER                        11
#define PON_BIT_NAP_ENCODER                          ((u32)0x00000001 << 11)                             /*!<R/W 0x0  nap: light sleep ENCODER */
#define PON_SHIFT_TMCK_ENCODER                       10
#define PON_BIT_TMCK_ENCODER                         ((u32)0x00000001 << 10)                             /*!<R/W 0x0  internal timing bypass ENCODER */
#define PON_SHIFT_DVSE_ENC_GROUP14                   9
#define PON_BIT_DVSE_ENC_GROUP14                     ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable mbist_enc_group14 */
#define PON_SHIFT_DVS_ENC_GROUP14                    5
#define PON_MASK_DVS_ENC_GROUP14                     ((u32)0x0000000F << 5)                              /*!<R/W 0x0  delay option mbist_enc_group14 */
#define PON_SHIFT_DVSE_ENC_GROUP13_2                 4
#define PON_BIT_DVSE_ENC_GROUP13_2                   ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable mbist_enc_group13_2 */
#define PON_SHIFT_DVS_ENC_GROUP13_2                  0
#define PON_MASK_DVS_ENC_GROUP13_2                   ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option mbist_enc_group13_2 */
/** @} */

/**************************************************************************//**
 * @defgroup PON_REG_MEM_RSA
 * @brief                                            (@ 0X0C8)
 * @{
 *****************************************************************************/
#define PON_SHIFT_DVSE_RSA                           4
#define PON_BIT_DVSE_RSA                             ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable mbist_RSA */
#define PON_SHIFT_DVS_RSA                            0
#define PON_MASK_DVS_RSA                             ((u32)0x0000000F << 0)                              /*!<R/W 0x0  delay option mbist_RSA */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_PON
 * @{
 * @brief rtl8735b_PON Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t PON_REG_PON_SYSON_CTRL ;                 /*!<   register,  Address offset: 0x000 */
	__IO uint32_t PON_REG_PON_SYSPLL_CTRL0 ;               /*!<   register,  Address offset: 0x004 */
	__IO uint32_t PON_REG_PON_SYSPLL_CTRL1 ;               /*!<   register,  Address offset: 0x008 */
	__IO uint32_t PON_REG_PON_SYSPLL_CTRL2 ;               /*!<   register,  Address offset: 0x00C */
	__IO uint32_t PON_REG_PON_SYSPLL_CTRL3 ;               /*!<   register,  Address offset: 0x010 */
	__IO uint32_t PON_REG_PON_PERIPLL_CTRL0 ;              /*!<   register,  Address offset: 0x014 */
	__IO uint32_t PON_REG_PON_PERIPLL_CTRL1 ;              /*!<   register,  Address offset: 0x018 */
	__IO uint32_t PON_REG_PON_PERIPLL_CTRL2 ;              /*!<   register,  Address offset: 0x01C */
	__IO uint32_t PON_REG_PON_PERIPLL_CTRL3 ;              /*!<   register,  Address offset: 0x020 */
	__IO uint32_t PON_REG_PON_FUNC_EN_CTRL ;               /*!<   register,  Address offset: 0x024 */
	__IO uint32_t PON_REG_PON_PLL_DBG ;                    /*!<   register,  Address offset: 0x028 */
	__IO uint32_t PON_REG_PON_FUNC_CLK_CTRL ;              /*!<   register,  Address offset: 0x02C */
	__IO uint32_t PON_REG_PON_BT_CTRL ;                    /*!<   register,  Address offset: 0x030 */
	__I  uint32_t PON_REG_UART_INTR_STS ;                  /*!<   register,  Address offset: 0x034 */
	__IO uint32_t PON_REG_WDT_RST_CTRL ;                   /*!<   register,  Address offset: 0x038 */
	__IO uint32_t PON_REG_PON_BUS_CTRL ;                   /*!<   register,  Address offset: 0x03C */
	__IO uint32_t PON_REG_PON_PLL_DIVIDER_CTRL ;           /*!<   register,  Address offset: 0x040 */
	__IO uint32_t PON_REG_SUPER_SEC_EF_CTRL ;              /*!<   register,  Address offset: 0x044 */
	__IO uint32_t PON_REG_BOOT_STATE ;                     /*!<   register,  Address offset: 0x048 */
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	__IO uint32_t PON_RSVD ;                               /*!<   register,  Address offset: 0x04C */
#else
	__IO uint32_t PON_REG_BOOT_STATE1 ;                    /*!<   register,  Address offset: 0x04C */
#endif
	__IO uint32_t PON_REG_PON_GPIOF_0_1_CTRL ;             /*!<   register,  Address offset: 0x050 */
	__IO uint32_t PON_REG_PON_GPIOF_2_3_CTRL ;             /*!<   register,  Address offset: 0x054 */
	__IO uint32_t PON_REG_PON_GPIOF_4_5_CTRL ;             /*!<   register,  Address offset: 0x058 */
	__IO uint32_t PON_REG_PON_GPIOF_6_7_CTRL ;             /*!<   register,  Address offset: 0x05C */
	__IO uint32_t PON_REG_PON_GPIOF_8_9_CTRL ;             /*!<   register,  Address offset: 0x060 */
	__IO uint32_t PON_REG_PON_GPIOF_10_11_CTRL ;           /*!<   register,  Address offset: 0x064 */
	__IO uint32_t PON_REG_PON_GPIOF_12_13_CTRL ;           /*!<   register,  Address offset: 0x068 */
	__IO uint32_t PON_REG_PON_GPIOF_14_15_CTRL ;           /*!<   register,  Address offset: 0x06C */
	__IO uint32_t PON_REG_PON_GPIOF_16_17_CTRL ;           /*!<   register,  Address offset: 0x070 */
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	__O  uint32_t PON_REG_MEM_WLAN_CNTRL_0 ;               /*!<   register,  Address offset: 0x074 */
	__O  uint32_t PON_REG_MEM_WLAN_CNTRL_1 ;               /*!<   register,  Address offset: 0x078 */
#else
	__IO uint32_t PON_REG_RMA_CTRL0 ;                      /*!<   register,  Address offset: 0x074 */
	__IO uint32_t PON_REG_RMA_CTRL1 ;                      /*!<   register,  Address offset: 0x078 */
#endif
	__O  uint32_t PON_REG_MEM_WLAN_CNTRL_2 ;               /*!<   register,  Address offset: 0x07C */
	__O  uint32_t PON_REG_MEM_WLAN_CNTRL_3 ;               /*!<   register,  Address offset: 0x080 */
	__IO uint32_t PON_REG_MEM_BT_CNTRL ;                   /*!<   register,  Address offset: 0x084 */
	__IO uint32_t PON_REG_MEM_GMAC_CNTRL ;                 /*!<   register,  Address offset: 0x088 */
	__IO uint32_t PON_REG_MEM_ISP_CNTRL_0 ;                /*!<   register,  Address offset: 0x08C */
	__IO uint32_t PON_REG_MEM_ISP_CNTRL_1 ;                /*!<   register,  Address offset: 0x090 */
	__IO uint32_t PON_REG_MEM_ISP_CNTRL_2 ;                /*!<   register,  Address offset: 0x094 */
	__IO uint32_t PON_REG_MEM_COMM_CNTRL ;                 /*!<   register,  Address offset: 0x098 */
	__IO uint32_t PON_REG_MEM_CPU_CNTRL ;                  /*!<   register,  Address offset: 0x09C */
	__IO uint32_t PON_REG_MEM_NN_CNTRL_0 ;                 /*!<   register,  Address offset: 0x0A0 */
	__IO uint32_t PON_REG_MEM_NN_CNTRL_1 ;                 /*!<   register,  Address offset: 0x0A4 */
	__IO uint32_t PON_REG_MEM_NN_CNTRL_2 ;                 /*!<   register,  Address offset: 0x0A8 */
	__IO uint32_t PON_REG_MEM_NN_CNTRL_3 ;                 /*!<   register,  Address offset: 0x0AC */
	__IO uint32_t PON_REG_MEM_VOE_CNTRL_0 ;                /*!<   register,  Address offset: 0x0B0 */
	__IO uint32_t PON_REG_MEM_PLATFORM_CNTRL ;             /*!<   register,  Address offset: 0x0B4 */
	__IO uint32_t PON_REG_MEM_ENC_CNTRL_0 ;                /*!<   register,  Address offset: 0x0B8 */
	__IO uint32_t PON_REG_MEM_ENC_CNTRL_1 ;                /*!<   register,  Address offset: 0x0BC */
	__IO uint32_t PON_REG_MEM_ENC_CNTRL_2 ;                /*!<   register,  Address offset: 0x0C0 */
	__IO uint32_t PON_REG_MEM_ENC_CNTRL_3 ;                /*!<   register,  Address offset: 0x0C4 */
	__IO uint32_t PON_REG_MEM_RSA ;                        /*!<   register,          Address offset: 0x0C8 */
} PON_TypeDef;
/** @} */

#endif
