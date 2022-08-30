#ifndef _RTL8735B_SYSON_S_TYPE_H_
#define _RTL8735B_SYSON_S_TYPE_H_
#include "platform_conf.h"

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_ISO_CTRL
 * @brief                                            (@ 0X004)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_ISO_I2S2IPLL                   2
#define SYSON_S_BIT_ISO_I2S2IPLL                     ((u32)0x00000001 << 2)                              /*!<R/W 1  1: isolation I2S2PLL to SYSON domain; 0: disable isolation */
#define SYSON_S_SHIFT_ISO_I2S1IPLL                   1
#define SYSON_S_BIT_ISO_I2S1IPLL                     ((u32)0x00000001 << 1)                              /*!<R/W 1  1: isolation I2S1PLL to SYSON domain; 0: disable isolation */
#define SYSON_S_SHIFT_ISO_ISPPLL                     0
#define SYSON_S_BIT_ISO_ISPPLL                       ((u32)0x00000001 << 0)                              /*!<R/W 1  1: isolation ISPPLL to SYSON domain; 0: disable isolation */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_CLK_CTRL
 * @brief                                            (@ 0X008)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_I2S2IPLL_RDY                   2
#define SYSON_S_BIT_I2S2IPLL_RDY                     ((u32)0x00000001 << 2)                              /*!<R 0  1: I2S2 PLL ready */
#define SYSON_S_SHIFT_I2S1IPLL_RDY                   1
#define SYSON_S_BIT_I2S1IPLL_RDY                     ((u32)0x00000001 << 1)                              /*!<R 0  1: I2S1 PLL ready */
#define SYSON_S_SHIFT_ISPPLL_RDY                     0
#define SYSON_S_BIT_ISPPLL_RDY                       ((u32)0x00000001 << 0)                              /*!<R 0  1: ISP PLL ready */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_FUNC_EN
 * @brief                                            (@ 0X00C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_CPU_RST_MASK                   0
#define SYSON_S_BIT_CPU_RST_MASK                     ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Mask "cpu_r0_rst" 0: Reset Peripheral while CPU reset request */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_HS_PLATFORM_PARA
 * @brief                                            (@ 0X010)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_DRAM_ADAP_STATUS               10
#define SYSON_S_BIT_DRAM_ADAP_STATUS                 ((u32)0x00000001 << 10)                             /*!<R 0  dram_adap_idle Note: Tie to 0 in RTL */
#define SYSON_S_SHIFT_LEXRA_TO_AXI_ADAP7_IDLE        9
#define SYSON_S_BIT_LEXRA_TO_AXI_ADAP7_IDLE          ((u32)0x00000001 << 9)                              /*!<R 1  lxm7_idle */
#define SYSON_S_SHIFT_LEXRA_TO_AXI_ADAP6_IDLE        8
#define SYSON_S_BIT_LEXRA_TO_AXI_ADAP6_IDLE          ((u32)0x00000001 << 8)                              /*!<R 1  lxm6_idle */
#define SYSON_S_SHIFT_TM9_DBGRESTARTED_STATUS        3
#define SYSON_S_BIT_TM9_DBGRESTARTED_STATUS          ((u32)0x00000001 << 3)                              /*!<R 1  tm_dbgrestarted_m */
#define SYSON_S_SHIFT_TM9_HALTED_STATUS              2
#define SYSON_S_BIT_TM9_HALTED_STATUS                ((u32)0x00000001 << 2)                              /*!<R 0  tm_halted_m */
#define SYSON_S_SHIFT_TM9_LOCKUP_STATUS              1
#define SYSON_S_BIT_TM9_LOCKUP_STATUS                ((u32)0x00000001 << 1)                              /*!<R 0  tm_lockup_m */
#define SYSON_S_SHIFT_TM9_SLEEP_STATUS               0
#define SYSON_S_BIT_TM9_SLEEP_STATUS                 ((u32)0x00000001 << 0)                              /*!<R 0  tm_sl_sleepsys_r */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_I2S_PLL1_CTRL0
 * @brief                                            (@ 0X014)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_POW_ERC_I2S1                   31
#define SYSON_S_BIT_POW_ERC_I2S1                     ((u32)0x00000001 << 31)                             /*!<R/W 0  erc enable. */
#define SYSON_S_SHIFT_POW_DIV_IN_I2S1                30
#define SYSON_S_BIT_POW_DIV_IN_I2S1                  ((u32)0x00000001 << 30)                             /*!<R/W 0  input divider enable (need pwl signal) 0 -> 1 */
#define SYSON_S_SHIFT_POW_PLL_I2S1                   29
#define SYSON_S_BIT_POW_PLL_I2S1                     ((u32)0x00000001 << 29)                             /*!<R/W 0  (need pwl signal) 0 -> 1 */
#define SYSON_S_SHIFT_REG_CP_BIA_I2S1                26
#define SYSON_S_MASK_REG_CP_BIA_I2S1                 ((u32)0x00000007 << 26)                             /*!<R/W 000  charge pump current selection . Default=10uA CP current select : 000: Icp=10uA, 001: Icp=15uA, 010: Icp=20uA, 011: Icp=25uA; 100: Icp=30uA, 101: Icp=35uA, 110: Icp=40uA, 111: Icp=450uA;  */
#define SYSON_S_SHIFT_DOGENB_I2S1                    25
#define SYSON_S_BIT_DOGENB_I2S1                      ((u32)0x00000001 << 25)                             /*!<R/W 0  0: watch dog on, 1: watch dog off */
#define SYSON_S_SHIFT_REG_PS_I2S1                    22
#define SYSON_S_MASK_REG_PS_I2S1                     ((u32)0x00000007 << 22)                             /*!<R/W 000   */
#define SYSON_S_SHIFT_REG_PSEN_I2S1                  21
#define SYSON_S_BIT_REG_PSEN_I2S1                    ((u32)0x00000001 << 21)                             /*!<R/W 1  phase selector enable */
#define SYSON_S_SHIFT_REG_CP_SET_I2S1                19
#define SYSON_S_MASK_REG_CP_SET_I2S1                 ((u32)0x00000003 << 19)                             /*!<R/W 11  Cp selection. Default=6p 00: Cp=3p, 01: Cp=4p, 10: Cp=5p, 11: Cp=6p */
#define SYSON_S_SHIFT_REG_RS_SET_I2S1                16
#define SYSON_S_MASK_REG_RS_SET_I2S1                 ((u32)0x00000007 << 16)                             /*!<R/W 101  Rs selection. Default=7k 000: Rs=15k, 001: Rs=13k, 010: Rs=11k, 011: Rs=9k, 100: Rs=7k, 101: Rs=5k, 110: Rs=3k, 111: Rs=1k;  */
#define SYSON_S_SHIFT_REG_CS_SEL_I2S1                14
#define SYSON_S_MASK_REG_CS_SEL_I2S1                 ((u32)0x00000003 << 14)                             /*!<R/W 10  Cs selection. Default=60p 00: Cs=40p, 01: Cs=50p, 10: Cs=60p, 11: Cs=70p */
#define SYSON_S_SHIFT_REG_FREF_EDGE_I2S1             13
#define SYSON_S_BIT_REG_FREF_EDGE_I2S1               ((u32)0x00000001 << 13)                             /*!<R/W 1  0:fref, 1:frefb */
#define SYSON_S_SHIFT_REG_CK_EN_I2S1                 12
#define SYSON_S_BIT_REG_CK_EN_I2S1                   ((u32)0x00000001 << 12)                             /*!<R/W 1  output clk enable */
#define SYSON_S_SHIFT_REG_CK_EN_D2_I2S1              11
#define SYSON_S_BIT_REG_CK_EN_D2_I2S1                ((u32)0x00000001 << 11)                             /*!<R/W 1  output clk div 2 enable */
#define SYSON_S_SHIFT_REG_CK_OUT_SEL_I2S1_0          8
#define SYSON_S_MASK_REG_CK_OUT_SEL_I2S1_0           ((u32)0x00000007 << 8)                              /*!<R/W 000  reserved */
#define SYSON_S_SHIFT_REG_XTAL_MANUAL_MODE_I2S1      7
#define SYSON_S_BIT_REG_XTAL_MANUAL_MODE_I2S1        ((u32)0x00000001 << 7)                              /*!<R/W 1  reg_xtal_maunal_mode. Default=0 0: reg_xtal_sel<3:0> is controlled by REG, xtal_div_sel is controlled by mapping table. 1: reg_xtal_sel<3:0>=4'b1111, xtal_div_sel is controlled by reg_xtal_div_sel_maunal<1:0> */
#define SYSON_S_SHIFT_REG_XTAL_DIV_SEL_MANUAL_I2S1   5
#define SYSON_S_MASK_REG_XTAL_DIV_SEL_MANUAL_I2S1    ((u32)0x00000003 << 5)                              /*!<R/W 00  input divider selection in xtal maunal mode. Default=00 00=/1, 10=/2, 11=/4 */
#define SYSON_S_SHIFT_REG_VC_THL_I2S1                3
#define SYSON_S_MASK_REG_VC_THL_I2S1                 ((u32)0x00000003 << 3)                              /*!<R/W 00  VC voltage, Default=00 00: VC=1/4Vdd, 01: VC=1/2Vdd, 10=3/4Vdd, 11: VC=Vdd */
#define SYSON_S_SHIFT_C3_SET_I2S1                    1
#define SYSON_S_MASK_C3_SET_I2S1                     ((u32)0x00000003 << 1)                              /*!<R/W 00  C3 selection. Default=1p 00: 0.5p, 01: 1p, 10: Cs=1.5p, 11: 2p */
#define SYSON_S_SHIFT_R3_SET_I2S1                    0
#define SYSON_S_BIT_R3_SET_I2S1                      ((u32)0x00000001 << 0)                              /*!<R/W 1  Rs selection. Default=1k 0: 0 Ohm, 1: 1k Ohm */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_I2S_PLL1_CTRL1
 * @brief                                            (@ 0X018)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_REG_XTAL_SEL_I2S1              28
#define SYSON_S_MASK_REG_XTAL_SEL_I2S1               ((u32)0x0000000F << 28)                             /*!<R/W 0000  xtal selection, Default=40MHz 0000= 40MHz, 0001= 25MHz, 0010= 13MHz, 0011= 19.2MHz 0100= 20MHz, 0101= 26MHz, 0110= 38.4MHz, 0111= 17.664MHz 1000= 16MHz, 1001= 14.138MHz, 1010= 12MHz, 1011= 52MHz 1100= 48MHz, 1101= 27MHz, 1110= 24MHz, 1111= none  */
#define SYSON_S_SHIFT_REG_FREQ_SEL_I2S1              24
#define SYSON_S_MASK_REG_FREQ_SEL_I2S1               ((u32)0x0000000F << 24)                             /*!<R/W 0000  output clk selection, Default=196.608MHz 0000= 400MHz, 0001=300MHz, 0010= X, 0011= X, 0100= 216MHz, 0101=196.608MHz, 0110=192MHz, 0111= 180.632MHz, 1000= 148.5MHz,1001= X, 1010= X, 1011= X, 1100= X, 1101= X, 1110= X, 1111= 500MHz  */
#define SYSON_S_SHIFT_TBASE_FREQ_I2S1                20
#define SYSON_S_MASK_TBASE_FREQ_I2S1                 ((u32)0x0000000F << 20)                             /*!<R/W 1000   */
#define SYSON_S_SHIFT_STEP_FREQ_I2S1                 16
#define SYSON_S_MASK_STEP_FREQ_I2S1                  ((u32)0x0000000F << 16)                             /*!<R/W 0101  step size selection for switching freq. */
#define SYSON_S_SHIFT_TRIG_FREQ_I2S1                 15
#define SYSON_S_BIT_TRIG_FREQ_I2S1                   ((u32)0x00000001 << 15)                             /*!<R/W 0  freq. step up or step down enable */
#define SYSON_S_SHIFT_BB_DBG_SEL_AFE_SDM_I2S1        11
#define SYSON_S_MASK_BB_DBG_SEL_AFE_SDM_I2S1         ((u32)0x0000000F << 11)                             /*!<R/W 0000   */
#define SYSON_S_SHIFT_DIVN_SDM_I2S1                  5
#define SYSON_S_MASK_DIVN_SDM_I2S1                   ((u32)0x0000003F << 5)                              /*!<R/W 111  393.216M (93.304M/24.576M) 40M: 000111 26M: 001101  */
#define SYSON_S_SHIFT_REG_CK_OUT_SEL_I2S1_1          1
#define SYSON_S_MASK_REG_CK_OUT_SEL_I2S1_1           ((u32)0x0000000F << 1)                              /*!<R/W 1110  output divider selection. Default=1110(/16) 0000=/1, 1000=/2, 1100=/8, 1110=/16, 1111=/32 */
#define SYSON_S_SHIFT_ICP_HALF_I2S1                  0
#define SYSON_S_BIT_ICP_HALF_I2S1                    ((u32)0x00000001 << 0)                              /*!<R/W 1  charge pump current half or not 0: no half 1: half */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_I2S_PLL1_CTRL2
 * @brief                                            (@ 0X01C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_STEP_I2S1                      19
#define SYSON_S_MASK_STEP_I2S1                       ((u32)0x00001FFF << 19)                             /*!<R/W 0000000000000  ssc step size selection. */
#define SYSON_S_SHIFT_TBASE_I2S1                     7
#define SYSON_S_MASK_TBASE_I2S1                      ((u32)0x00000FFF << 7)                              /*!<R/W 000000000000  ssc freq selection */
#define SYSON_S_SHIFT_EN_SSC_I2S1                    6
#define SYSON_S_BIT_EN_SSC_I2S1                      ((u32)0x00000001 << 6)                              /*!<R/W 0  ssc enable. Default=0 */
#define SYSON_S_SHIFT_PLL_I2S1_2                     0
#define SYSON_S_MASK_PLL_I2S1_2                      ((u32)0x0000003F << 0)                              /*!<R/W 000000   */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_I2S_PLL1_CTRL3
 * @brief                                            (@ 0X020)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_F0F_SDM_I2S1                   19
#define SYSON_S_MASK_F0F_SDM_I2S1                    ((u32)0x00001FFF << 19)                             /*!<R/W 1  393.216M (93.304M/24.576M) 40M: 1_0100_1001_0101 26M: 1_1111_1010_1010 */
#define SYSON_S_SHIFT_F0N_SDM_I2S1                   16
#define SYSON_S_MASK_F0N_SDM_I2S1                    ((u32)0x00000007 << 16)                             /*!<R/W 110  393.216M (93.304M/24.576M) 40M: 110 26M: 000 */
#define SYSON_S_SHIFT_ORDER_SDM_I2S1                 15
#define SYSON_S_BIT_ORDER_SDM_I2S1                   ((u32)0x00000001 << 15)                             /*!<R/W 0  SDM order */
#define SYSON_S_SHIFT_PLL_I2S1_3                     0
#define SYSON_S_MASK_PLL_I2S1_3                      ((u32)0x00007FFF << 0)                              /*!<R/W 000000000000000   */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_I2S_PLL2_CTRL0
 * @brief                                            (@ 0X024)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_POW_ERC_I2S2                   31
#define SYSON_S_BIT_POW_ERC_I2S2                     ((u32)0x00000001 << 31)                             /*!<R/W 0  erc enable. */
#define SYSON_S_SHIFT_POW_DIV_IN_I2S2                30
#define SYSON_S_BIT_POW_DIV_IN_I2S2                  ((u32)0x00000001 << 30)                             /*!<R/W 0  input divider enable (need pwl signal) 0 -> 1 */
#define SYSON_S_SHIFT_POW_PLL_I2S2                   29
#define SYSON_S_BIT_POW_PLL_I2S2                     ((u32)0x00000001 << 29)                             /*!<R/W 0  (need pwl signal) 0 -> 1 */
#define SYSON_S_SHIFT_REG_CP_BIA_I2S2                26
#define SYSON_S_MASK_REG_CP_BIA_I2S2                 ((u32)0x00000007 << 26)                             /*!<R/W 000  charge pump current selection . Default=10uA CP current select : 000: Icp=10uA, 001: Icp=15uA, 010: Icp=20uA, 011: Icp=25uA; 100: Icp=30uA, 101: Icp=35uA, 110: Icp=40uA, 111: Icp=450uA;  */
#define SYSON_S_SHIFT_DOGENB_I2S2                    25
#define SYSON_S_BIT_DOGENB_I2S2                      ((u32)0x00000001 << 25)                             /*!<R/W 0  0: watch dog on, 1: watch dog off */
#define SYSON_S_SHIFT_REG_PS_I2S2                    22
#define SYSON_S_MASK_REG_PS_I2S2                     ((u32)0x00000007 << 22)                             /*!<R/W 000   */
#define SYSON_S_SHIFT_REG_PSEN_I2S2                  21
#define SYSON_S_BIT_REG_PSEN_I2S2                    ((u32)0x00000001 << 21)                             /*!<R/W 1  phase selector enable */
#define SYSON_S_SHIFT_REG_CP_SET_I2S2                19
#define SYSON_S_MASK_REG_CP_SET_I2S2                 ((u32)0x00000003 << 19)                             /*!<R/W 11  Cp selection. Default=6p 00: Cp=4p, 01: Cp=5p, 10: Cp=6p, 11: Cp=7p */
#define SYSON_S_SHIFT_REG_RS_SET_I2S2                16
#define SYSON_S_MASK_REG_RS_SET_I2S2                 ((u32)0x00000007 << 16)                             /*!<R/W 101  Rs selection. Default=5k 000: Rs=15k, 001: Rs=13k, 010: Rs=11k, 011: Rs=9k, 100: Rs=7k, 101: Rs=5k, 110: Rs=3k, 111: Rs=1k; 40M = 5k(101), 26M = 5k(101) */
#define SYSON_S_SHIFT_REG_CS_SEL_I2S2                14
#define SYSON_S_MASK_REG_CS_SEL_I2S2                 ((u32)0x00000003 << 14)                             /*!<R/W 10  Cs selection. Default=60p 00: Cs=40p, 01: Cs=50p, 10: Cs=60p, 11: Cs=70p */
#define SYSON_S_SHIFT_REG_FREF_EDGE_I2S2             13
#define SYSON_S_BIT_REG_FREF_EDGE_I2S2               ((u32)0x00000001 << 13)                             /*!<R/W 1  0:fref, 1:frefb */
#define SYSON_S_SHIFT_REG_CK_EN_I2S2                 12
#define SYSON_S_BIT_REG_CK_EN_I2S2                   ((u32)0x00000001 << 12)                             /*!<R/W 1  output clk enable */
#define SYSON_S_SHIFT_REG_CK_EN_D2_I2S2              11
#define SYSON_S_BIT_REG_CK_EN_D2_I2S2                ((u32)0x00000001 << 11)                             /*!<R/W 0  output clk div 2 enable */
#define SYSON_S_SHIFT_REG_CK_OUT_SEL_I2S2_0          8
#define SYSON_S_MASK_REG_CK_OUT_SEL_I2S2_0           ((u32)0x00000007 << 8)                              /*!<R/W 0  reserved */
#define SYSON_S_SHIFT_REG_XTAL_MANUAL_MODE_I2S2      7
#define SYSON_S_BIT_REG_XTAL_MANUAL_MODE_I2S2        ((u32)0x00000001 << 7)                              /*!<R/W 1  reg_xtal_maunal_mode. Default=0 0: reg_xtal_sel<3:0> is controlled by REG, xtal_div_sel is controlled by mapping table. 1: reg_xtal_sel<3:0>=4'b1111, xtal_div_sel is controlled by reg_xtal_div_sel_maunal<1:0> */
#define SYSON_S_SHIFT_REG_XTAL_DIV_SEL_MANUAL_I2S2   5
#define SYSON_S_MASK_REG_XTAL_DIV_SEL_MANUAL_I2S2    ((u32)0x00000003 << 5)                              /*!<R/W 00  input divider selection in xtal maunal mode. Default=00 00=/1, 01=/2, 1X=/4 */
#define SYSON_S_SHIFT_REG_VC_THL_I2S2                3
#define SYSON_S_MASK_REG_VC_THL_I2S2                 ((u32)0x00000003 << 3)                              /*!<R/W 00  VC voltage, Default=00 00: VC=1/4Vdd, 01: VC=1/2Vdd, 10=3/4Vdd, 11: VC=Vdd */
#define SYSON_S_SHIFT_C3_SET_I2S2                    1
#define SYSON_S_MASK_C3_SET_I2S2                     ((u32)0x00000003 << 1)                              /*!<R/W 0  C3 selection. Default=1p 00: 0.5p, 01: 1p, 10: Cs=1.5p, 11: 2p */
#define SYSON_S_SHIFT_R3_SET_I2S2                    0
#define SYSON_S_BIT_R3_SET_I2S2                      ((u32)0x00000001 << 0)                              /*!<R/W 1  Rs selection. Default=1k 0: 0 Ohm, 1: 1k Ohm */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_I2S_PLL2_CTRL1
 * @brief                                            (@ 0X028)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_REG_XTAL_SEL_I2S2              28
#define SYSON_S_MASK_REG_XTAL_SEL_I2S2               ((u32)0x0000000F << 28)                             /*!<R/W 0000  xtal selection, Default=40MHz 0000= 40MHz, 0001= 25MHz, 0010= 13MHz, 0011= 19.2MHz 0100= 20MHz, 0101= 26MHz, 0110= 38.4MHz, 0111= 17.664MHz 1000= 16MHz, 1001= 14.138MHz, 1010= 12MHz, 1011= 52MHz 1100= 48MHz, 1101= 27MHz, 1110= 24MHz, 1111= none  */
#define SYSON_S_SHIFT_REG_FREQ_SEL_I2S2              24
#define SYSON_S_MASK_REG_FREQ_SEL_I2S2               ((u32)0x0000000F << 24)                             /*!<R/W 0  output clk selection, Default=180.632MHz 0000= 400MHz, 0001= X, 0010= X, 0011= X, 0100= 216MHz, 0101=196.608MHz, 0110=192MHz, 0111= 180.632MHz, 1000= 148.5MHz,1001= X, 1010= X, 1011= X, 1100= X, 1101= X, 1110= X, 1111= 500MHz  */
#define SYSON_S_SHIFT_TBASE_FREQ_I2S2                20
#define SYSON_S_MASK_TBASE_FREQ_I2S2                 ((u32)0x0000000F << 20)                             /*!<R/W 1000   */
#define SYSON_S_SHIFT_STEP_FREQ_I2S2                 16
#define SYSON_S_MASK_STEP_FREQ_I2S2                  ((u32)0x0000000F << 16)                             /*!<R/W 0101  step size selection for switching freq. */
#define SYSON_S_SHIFT_TRIG_FREQ_I2S2                 15
#define SYSON_S_BIT_TRIG_FREQ_I2S2                   ((u32)0x00000001 << 15)                             /*!<R/W 0  freq. step up or step down enable */
#define SYSON_S_SHIFT_BB_DBG_SEL_AFE_SDM_I2S2        11
#define SYSON_S_MASK_BB_DBG_SEL_AFE_SDM_I2S2         ((u32)0x0000000F << 11)                             /*!<R/W 0000   */
#define SYSON_S_SHIFT_DIVN_SDM_I2S2                  5
#define SYSON_S_MASK_DIVN_SDM_I2S2                   ((u32)0x0000003F << 5)                              /*!<R/W 111  361.264M (45.158M) 40M: 000111 26M: 001101  */
#define SYSON_S_SHIFT_REG_CK_OUT_SEL_I2S2_1          1
#define SYSON_S_MASK_REG_CK_OUT_SEL_I2S2_1           ((u32)0x0000000F << 1)                              /*!<R/W 1100  output divider selection. Default=1100(/8) 0000=/1, 1000=/2, 1100=/8, 1110=/16, 1111=/32 */
#define SYSON_S_SHIFT_ICP_HALF_I2S2                  0
#define SYSON_S_BIT_ICP_HALF_I2S2                    ((u32)0x00000001 << 0)                              /*!<R/W 1  charge pump current half or not 0: no half 1: half */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_I2S_PLL2_CTRL2
 * @brief                                            (@ 0X02C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_STEP_I2S2                      19
#define SYSON_S_MASK_STEP_I2S2                       ((u32)0x00001FFF << 19)                             /*!<R/W 0000000000000  ssc step size selection. */
#define SYSON_S_SHIFT_TBASE_I2S2                     7
#define SYSON_S_MASK_TBASE_I2S2                      ((u32)0x00000FFF << 7)                              /*!<R/W 000000000000  ssc freq selection */
#define SYSON_S_SHIFT_EN_SSC_I2S2                    6
#define SYSON_S_BIT_EN_SSC_I2S2                      ((u32)0x00000001 << 6)                              /*!<R/W 0  ssc enable. Default=0 */
#define SYSON_S_SHIFT_PLL_I2S2_2                     0
#define SYSON_S_MASK_PLL_I2S2_2                      ((u32)0x0000003F << 0)                              /*!<R/W 000000   */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_I2S_PLL2_CTRL3
 * @brief                                            (@ 0X030)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_F0F_SDM_I2S2                   19
#define SYSON_S_MASK_F0F_SDM_I2S2                    ((u32)0x00001FFF << 19)                             /*!<R/W 1  361.264M (45.158M) 40M: 0_1000_0001_0111 26M: 0_0101_0001_0000  */
#define SYSON_S_SHIFT_F0N_SDM_I2S2                   16
#define SYSON_S_MASK_F0N_SDM_I2S2                    ((u32)0x00000007 << 16)                             /*!<R/W 000  361.264M (45.158M) 40M: 000 26M: 111  */
#define SYSON_S_SHIFT_ORDER_SDM_I2S2                 15
#define SYSON_S_BIT_ORDER_SDM_I2S2                   ((u32)0x00000001 << 15)                             /*!<R/W 0  SDM order */
#define SYSON_S_SHIFT_PLL_I2S2_3                     0
#define SYSON_S_MASK_PLL_I2S2_3                      ((u32)0x00007FFF << 0)                              /*!<R/W 000000000000000   */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_ISP_PLL_CTRL0
 * @brief                                            (@ 0X034)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_POW_ERC_ISP                    31
#define SYSON_S_BIT_POW_ERC_ISP                      ((u32)0x00000001 << 31)                             /*!<R/W 0  erc enable. */
#define SYSON_S_SHIFT_POW_DIV_IN_ISP                 30
#define SYSON_S_BIT_POW_DIV_IN_ISP                   ((u32)0x00000001 << 30)                             /*!<R/W 0  input divider enable (need pwl signal) 0 -> 1 */
#define SYSON_S_SHIFT_POW_PLL_ISP                    29
#define SYSON_S_BIT_POW_PLL_ISP                      ((u32)0x00000001 << 29)                             /*!<R/W 0  (need pwl signal) 0 -> 1 */
#define SYSON_S_SHIFT_REG_CP_BIA_ISP                 26
#define SYSON_S_MASK_REG_CP_BIA_ISP                  ((u32)0x00000007 << 26)                             /*!<R/W 000  charge pump current selection . Default=10uA CP current select : 000: Icp=10uA, 001: Icp=15uA, 010: Icp=20uA, 011: Icp=25uA; 100: Icp=30uA, 101: Icp=35uA, 110: Icp=40uA, 111: Icp=450uA;  */
#define SYSON_S_SHIFT_DOGENB_ISP                     25
#define SYSON_S_BIT_DOGENB_ISP                       ((u32)0x00000001 << 25)                             /*!<R/W 0  0: watch dog on, 1: watch dog off */
#define SYSON_S_SHIFT_REG_PS_ISP                     22
#define SYSON_S_MASK_REG_PS_ISP                      ((u32)0x00000007 << 22)                             /*!<R/W 000   */
#define SYSON_S_SHIFT_REG_PSEN_ISP                   21
#define SYSON_S_BIT_REG_PSEN_ISP                     ((u32)0x00000001 << 21)                             /*!<R/W 1  phase selector enable */
#define SYSON_S_SHIFT_REG_CP_SET_ISP                 19
#define SYSON_S_MASK_REG_CP_SET_ISP                  ((u32)0x00000003 << 19)                             /*!<R/W 11  Cp selection. Default=6p 00: Cp=3p, 01: Cp=4p, 10: Cp=5p, 11: Cp=6p */
#define SYSON_S_SHIFT_REG_RS_SET_ISP                 16
#define SYSON_S_MASK_REG_RS_SET_ISP                  ((u32)0x00000007 << 16)                             /*!<R/W 101  Rs selection. Default=7k 000: Rs=15k, 001: Rs=13k, 010: Rs=11k, 011: Rs=9k, 100: Rs=7k, 101: Rs=5k, 110: Rs=3k, 111: Rs=1k;  */
#define SYSON_S_SHIFT_REG_CS_SEL_ISP                 14
#define SYSON_S_MASK_REG_CS_SEL_ISP                  ((u32)0x00000003 << 14)                             /*!<R/W 10  Cs selection. Default=60p 00: Cs=30p, 01: Cs=40p, 10: Cs=50p, 11: Cs=60p */
#define SYSON_S_SHIFT_REG_FREF_EDGE_ISP              13
#define SYSON_S_BIT_REG_FREF_EDGE_ISP                ((u32)0x00000001 << 13)                             /*!<R/W 1  0:fref, 1:frefb */
#define SYSON_S_SHIFT_REG_CK_EN_ISP                  12
#define SYSON_S_BIT_REG_CK_EN_ISP                    ((u32)0x00000001 << 12)                             /*!<R/W 1  output clk enable */
#define SYSON_S_SHIFT_REG_CK_EN_D2_ISP               11
#define SYSON_S_BIT_REG_CK_EN_D2_ISP                 ((u32)0x00000001 << 11)                             /*!<R/W 0  output clk div 2 enable */
#define SYSON_S_SHIFT_REG_CK_OUT_SEL_ISP0            8
#define SYSON_S_MASK_REG_CK_OUT_SEL_ISP0             ((u32)0x00000007 << 8)                              /*!<R/W 0  reserved */
#define SYSON_S_SHIFT_REG_XTAL_MANUAL_MODE_ISP       7
#define SYSON_S_BIT_REG_XTAL_MANUAL_MODE_ISP         ((u32)0x00000001 << 7)                              /*!<R/W 1  reg_xtal_maunal_mode. Default=0 0: reg_xtal_sel<3:0> is controlled by REG, xtal_div_sel is controlled by mapping table. 1: reg_xtal_sel<3:0>=4'b1111, xtal_div_sel is controlled by reg_xtal_div_sel_maunal<1:0> */
#define SYSON_S_SHIFT_REG_XTAL_DIV_SEL_MANUAL_ISP    5
#define SYSON_S_MASK_REG_XTAL_DIV_SEL_MANUAL_ISP     ((u32)0x00000003 << 5)                              /*!<R/W 00  input divider selection in xtal maunal mode. Default=00 00=/1, 01=/2, 1X=/4 */
#define SYSON_S_SHIFT_REG_VC_THL_ISP                 3
#define SYSON_S_MASK_REG_VC_THL_ISP                  ((u32)0x00000003 << 3)                              /*!<R/W 00  VC voltage, Default=00 00: VC=1/4Vdd, 01: VC=1/2Vdd, 10=3/4Vdd, 11: VC=Vdd */
#define SYSON_S_SHIFT_C3_SET_ISP                     1
#define SYSON_S_MASK_C3_SET_ISP                      ((u32)0x00000003 << 1)                              /*!<R/W 0  C3 selection. Default=1p 00: 0.5p, 01: 1p, 10: Cs=1.5p, 11: 2p */
#define SYSON_S_SHIFT_R3_SET_ISP                     0
#define SYSON_S_BIT_R3_SET_ISP                       ((u32)0x00000001 << 0)                              /*!<R/W 1  Rs selection. Default=1k 0: 0 Ohm, 1: 1k Ohm */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_ISP_PLL_CTRL1
 * @brief                                            (@ 0X038)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_REG_XTAL_SEL_ISP               28
#define SYSON_S_MASK_REG_XTAL_SEL_ISP                ((u32)0x0000000F << 28)                             /*!<R/W 0000  xtal selection, Default=40MHz 0000= 40MHz, 0001= 25MHz, 0010= 13MHz, 0011= 19.2MHz 0100= 20MHz, 0101= 26MHz, 0110= 38.4MHz, 0111= 17.664MHz 1000= 16MHz, 1001= 14.138MHz, 1010= 12MHz, 1011= 52MHz 1100= 48MHz, 1101= 27MHz, 1110= 24MHz, 1111= none  */
#define SYSON_S_SHIFT_REG_FREQ_SEL_ISP               24
#define SYSON_S_MASK_REG_FREQ_SEL_ISP                ((u32)0x0000000F << 24)                             /*!<R/W 0  output clk selection, Default=192MHz 0000= 400MHz, 0001=300MHz, 0010= X, 0011= X, 0100= 216MHz, 0101=196.608MHz, 0110=192MHz, 0111= 180.632MHz, 1000= 148.5MHz,1001= X, 1010= X, 1011= X, 1100= X, 1101= X, 1110= X, 1111= 500MHz  */
#define SYSON_S_SHIFT_TBASE_FREQ_ISP                 20
#define SYSON_S_MASK_TBASE_FREQ_ISP                  ((u32)0x0000000F << 20)                             /*!<R/W 1000   */
#define SYSON_S_SHIFT_STEP_FREQ_ISP                  16
#define SYSON_S_MASK_STEP_FREQ_ISP                   ((u32)0x0000000F << 16)                             /*!<R/W 0101  step size selection for switching freq. */
#define SYSON_S_SHIFT_TRIG_FREQ_ISP                  15
#define SYSON_S_BIT_TRIG_FREQ_ISP                    ((u32)0x00000001 << 15)                             /*!<R/W 0  freq. step up or step down enable */
#define SYSON_S_SHIFT_BB_DBG_SEL_AFE_SDM_ISP         11
#define SYSON_S_MASK_BB_DBG_SEL_AFE_SDM_ISP          ((u32)0x0000000F << 11)                             /*!<R/W 0000   */
#define SYSON_S_SHIFT_DIVN_SDM_ISP                   5
#define SYSON_S_MASK_DIVN_SDM_ISP                    ((u32)0x0000003F << 5)                              /*!<R/W 1111  384M (12M/24M) 40M: 000111 26M: 001100 297M (37.125M/74.25M) 40M: 000101 26M: 001001 432M (27M/54M) 40M: 001000 26M: 001110 */
#define SYSON_S_SHIFT_REG_CK_OUT_SEL_ISP1            1
#define SYSON_S_MASK_REG_CK_OUT_SEL_ISP1             ((u32)0x0000000F << 1)                              /*!<R/W 1110  output divider selection. Default=1110(/16) 0000=/1, 1000=/2, 1100=/8, 1110=/16, 1111=/32 */
#define SYSON_S_SHIFT_ICP_HALF_ISP                   0
#define SYSON_S_BIT_ICP_HALF_ISP                     ((u32)0x00000001 << 0)                              /*!<R/W 1  charge pump current half or not 0: no half 1: half */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_ISP_PLL_CTRL2
 * @brief                                            (@ 0X03C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_STEP_ISP                       19
#define SYSON_S_MASK_STEP_ISP                        ((u32)0x00001FFF << 19)                             /*!<R/W 0000000000000  ssc step size selection. */
#define SYSON_S_SHIFT_TBASE_ISP                      7
#define SYSON_S_MASK_TBASE_ISP                       ((u32)0x00000FFF << 7)                              /*!<R/W 000000000000  ssc freq selection */
#define SYSON_S_SHIFT_EN_SSC_ISP                     6
#define SYSON_S_BIT_EN_SSC_ISP                       ((u32)0x00000001 << 6)                              /*!<R/W 0  ssc enable. Default=0 */
#define SYSON_S_SHIFT_PLL_ISP_2                      0
#define SYSON_S_MASK_PLL_ISP_2                       ((u32)0x0000003F << 0)                              /*!<R/W 000000   */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_ISP_PLL_CTRL3
 * @brief                                            (@ 0X040)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_F0F_SDM_ISP                    19
#define SYSON_S_MASK_F0F_SDM_ISP                     ((u32)0x00001FFF << 19)                             /*!<R/W 1  384M (12M/24M) 40M: 1_1001_1001_1010 26M: 0_0100_1110_1100 297M (37.125M/74.25M) 40M: 0_1100_1100_1101 26M: 0_1100_0100_1111 432M (27M/54M) 40M: 0_1100_1100_1101 26M: 1_1101_1000_1010 */
#define SYSON_S_SHIFT_F0N_SDM_ISP                    16
#define SYSON_S_MASK_F0N_SDM_ISP                     ((u32)0x00000007 << 16)                             /*!<R/W 100  384M (12M/24M) 40M: 100 26M: 110 297M (37.125M/74.25M) 40M: 011 26M: 011 432M (27M/54M) 40M: 110 26M: 100 */
#define SYSON_S_SHIFT_ORDER_SDM_ISP                  15
#define SYSON_S_BIT_ORDER_SDM_ISP                    ((u32)0x00000001 << 15)                             /*!<R/W 0  SDM order */
#define SYSON_S_SHIFT_PLL_ISP_3                      0
#define SYSON_S_MASK_PLL_ISP_3                       ((u32)0x00007FFF << 0)                              /*!<R/W 000000000000000   */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_LDO_SDIO_CTRL
 * @brief                                            (@ 0X044)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_RESERVED1                      16
#define SYSON_S_MASK_RESERVED1                       ((u32)0x0000000F << 16)                             /*!<R/W 0   */
#define SYSON_S_SHIFT_REG_DMY_LDO_L                  14
#define SYSON_S_MASK_REG_DMY_LDO_L                   ((u32)0x00000003 << 14)                             /*!<R/W 00  // [REGU][LDO_SDIO] REG_CTRL // LDO dmy REG */
#define SYSON_S_SHIFT_REG_FORCE_DIODE_L              13
#define SYSON_S_BIT_REG_FORCE_DIODE_L                ((u32)0x00000001 << 13)                             /*!<R/W 0  // [REGU][LDO_SDIO] REG_CTRL // PGATE diode clamp (this is directly force no gating) // (purpose for powerCut mode iOCP) // 0: disable force diode clamp (default) // 1: enable force diode clamp */
#define SYSON_S_SHIFT_REG_BUFFERTYPE_SEL_L           12
#define SYSON_S_BIT_REG_BUFFERTYPE_SEL_L             ((u32)0x00000001 << 12)                             /*!<R/W 0  // [REGU][LDO_SDIO] REG_CTRL // LDO Buffer Type Select // LDO_SDIO should always set PMOS buffer // 0(default): PMOS buffer (for HV 3P3V) // 1: NMOS buffer (for HV 1P8V) */
#define SYSON_S_SHIFT_REG_DMYLOAD_L                  10
#define SYSON_S_MASK_REG_DMYLOAD_L                   ((u32)0x00000003 << 10)                             /*!<R/W 00  // [REGU][LDO_SDIO] REG_CTRL // LDO dmy load ctrl // 00(default): dmy load disable // 01: light dmy load enable (~160kohm) // 10: dmy load enable (~1kohm) // 11: dmy load + light dmy load both enable */
#define SYSON_S_SHIFT_REG_ITAIL_HALF_EN_L            9
#define SYSON_S_BIT_REG_ITAIL_HALF_EN_L              ((u32)0x00000001 << 9)                              /*!<R/W 0  // [REGU][LDO_SDIO] REG_CTRL // LDO iq half ctrl // 0(default): iq normal (for normal mode) // 1: iq half (for standby mode) */
#define SYSON_S_SHIFT_REG_STANDBY_L                  7
#define SYSON_S_MASK_REG_STANDBY_L                   ((u32)0x00000003 << 7)                              /*!<R/W 00  // [REGU][LDO_SDIO] REG_CTRL // LDO standby mode ctrl: // 00 (default): normal mode (iq normal + pwrmos 4x) // 01: debug mode (iq reduce + pwrmos 1x) // 10: debug mode (iq normal + pwrmos 4x) // 11: standby mode (iq reduce + pwrmos 1x) */
#define SYSON_S_SHIFT_EN_DIODE_L                     6
#define SYSON_S_BIT_EN_DIODE_L                       ((u32)0x00000001 << 6)                              /*!<R/W 1  // [REGU][LDO_SDIO] REG_CTRL // PGATE diode clamp (this gating to disable by pd_regu_L) // 0: disable clamp // 1: enable clamp (default) */
#define SYSON_S_SHIFT_VOADJ_L                        2
#define SYSON_S_MASK_VOADJ_L                         ((u32)0x0000000F << 2)                              /*!<R/W 1000  // LDO VOSEL // 0000 1.617 // 0001 1.642 // 0010 1.667 // 0011 1.694 // 0100 1.721 // 0101 1.749 // 0110 1.763 // 0111 1.778 // 1000 1.793 // 1001 1.839 // 1010 1.887 // 1011 1.938 // 1100 1.992 // 1101 2.905 // 1110 2.979 // 1111 3.047 */
#define SYSON_S_SHIFT_PD_REGU_L                      1
#define SYSON_S_BIT_PD_REGU_L                        ((u32)0x00000001 << 1)                              /*!<R/W 1  // [REGU][LDO_SDIO] REG_CTRL // PowerDown CTRL // 0: normal-Mode // 1: power-down Mode (default) */
#define SYSON_S_SHIFT_EN_PC_BT_L                     0
#define SYSON_S_BIT_EN_PC_BT_L                       ((u32)0x00000001 << 0)                              /*!<R/W 0  // [REGU][LDO_SDIO] REG_CTRL // PWRCUT enable // 0: LDO-Mode (default) // 1: PWRCUT-Mode */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_MEM_CTRL
 * @brief                                            (@ 0X048)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_BT_SRAM_MUX                    14
#define SYSON_S_BIT_BT_SRAM_MUX                      ((u32)0x00000001 << 14)                             /*!<R/W 0  SRAM4~8 0: BUS Memory, 1: BT Share Memory */
#define SYSON_S_SHIFT_SRAM8_RET                      13
#define SYSON_S_BIT_SRAM8_RET                        ((u32)0x00000001 << 13)                             /*!<R/W 0  1: SRAM8 Retention Mode */
#define SYSON_S_SHIFT_SRAM7_RET                      12
#define SYSON_S_BIT_SRAM7_RET                        ((u32)0x00000001 << 12)                             /*!<R/W 0  1: SRAM7 Retention Mode */
#define SYSON_S_SHIFT_SRAM6_RET                      11
#define SYSON_S_BIT_SRAM6_RET                        ((u32)0x00000001 << 11)                             /*!<R/W 0  1: SRAM6 Retention Mode */
#define SYSON_S_SHIFT_SRAM5_RET                      10
#define SYSON_S_BIT_SRAM5_RET                        ((u32)0x00000001 << 10)                             /*!<R/W 0  1: SRAM5 Retention Mode */
#define SYSON_S_SHIFT_SRAM4_RET                      9
#define SYSON_S_BIT_SRAM4_RET                        ((u32)0x00000001 << 9)                              /*!<R/W 0  1: SRAM4 Retention Mode */
#define SYSON_S_SHIFT_SRAM3_RET                      8
#define SYSON_S_BIT_SRAM3_RET                        ((u32)0x00000001 << 8)                              /*!<R/W 0  1: SRAM3 Retention Mode */
#define SYSON_S_SHIFT_SRAM2_RET                      7
#define SYSON_S_BIT_SRAM2_RET                        ((u32)0x00000001 << 7)                              /*!<R/W 0  1: SRAM2 Retention Mode */
#define SYSON_S_SHIFT_SRAM8_SD                       6
#define SYSON_S_BIT_SRAM8_SD                         ((u32)0x00000001 << 6)                              /*!<R/W 0  1: Shutdown SRAM8 */
#define SYSON_S_SHIFT_SRAM7_SD                       5
#define SYSON_S_BIT_SRAM7_SD                         ((u32)0x00000001 << 5)                              /*!<R/W 0  1: Shutdown SRAM7 */
#define SYSON_S_SHIFT_SRAM6_SD                       4
#define SYSON_S_BIT_SRAM6_SD                         ((u32)0x00000001 << 4)                              /*!<R/W 0  1: Shutdown SRAM6 */
#define SYSON_S_SHIFT_SRAM5_SD                       3
#define SYSON_S_BIT_SRAM5_SD                         ((u32)0x00000001 << 3)                              /*!<R/W 0  1: Shutdown SRAM5 */
#define SYSON_S_SHIFT_SRAM4_SD                       2
#define SYSON_S_BIT_SRAM4_SD                         ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Shutdown SRAM4 */
#define SYSON_S_SHIFT_SRAM3_SD                       1
#define SYSON_S_BIT_SRAM3_SD                         ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Shutdown SRAM3 */
#define SYSON_S_SHIFT_SRAM2_SD                       0
#define SYSON_S_BIT_SRAM2_SD                         ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Shutdown SRAM2 */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_SCE_EXMEM_CTRL0
 * @brief                                            (@ 0X054)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_RSVD1                          8
#define SYSON_S_MASK_RSVD1                           ((u32)0x00FFFFFF << 8)                              /*!<R/W 0  TBD */
#define SYSON_S_SHIFT_SCE_EXMEM_OP_ADDR              0
#define SYSON_S_MASK_SCE_EXMEM_OP_ADDR               ((u32)0x000000FF << 0)                              /*!<R/W 0  When you want to read or write data from or to SCE register, you need to fill the address to this register at first. Uint: 4 bytes Ex: "REG_SECURE_CTRL[7:0] = 0x2" represent that SCE register is 0x08. */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_SCE_EXMEM_CTRL1
 * @brief                                            (@ 0X058)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SCE_EXMEM_OP_DATA              0
#define SYSON_S_MASK_SCE_EXMEM_OP_DATA               ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  There are two operation in this register. One is reading process and the other is writing process. Reading Process: read data from SCE register according to REG_SCE_CONFIG[7:0]. Writing Process: write data to SCE register according to REG_SCE_CONFIG[7:0]. */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_SCE_FLASH_CTRL0
 * @brief                                            (@ 0X05C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_RSVD2                          8
#define SYSON_S_MASK_RSVD2                           ((u32)0x00FFFFFF << 8)                              /*!<R/W 0  TBD */
#define SYSON_S_SHIFT_SCE_FLASH_OP_ADDR              0
#define SYSON_S_MASK_SCE_FLASH_OP_ADDR               ((u32)0x000000FF << 0)                              /*!<R/W 0  When you want to read or write data from or to SCE register, you need to fill the address to this register at first. Uint: 4 bytes Ex: "REG_SECURE_CTRL[7:0] = 0x2" represent that SCE register is 0x08. */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_SCE_FLASH_CTRL1
 * @brief                                            (@ 0X060)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SCE_FLASH_OP_DATA              0
#define SYSON_S_MASK_SCE_FLASH_OP_DATA               ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  There are two operation in this register. One is reading process and the other is writing process. Reading Process: read data from SCE register according to REG_SCE_CONFIG[7:0]. Writing Process: write data to SCE register according to REG_SCE_CONFIG[7:0]. */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_SEC_EFUSE_CTRL0
 * @brief                                            (@ 0X064)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_RSVD3                          0
#define SYSON_S_MASK_RSVD3                           ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SEC_MASTER_SLAVE_PORT_IP_DIS
 * @brief                                            (@ 0X068)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_RSVD4                          17
#define SYSON_S_MASK_RSVD4                           ((u32)0x00007FFF << 17)                             /*!<R 0  RSVD */
#define SYSON_S_SHIFT_SEC_IP_CONFIG_LOCK_EN          16
#define SYSON_S_BIT_SEC_IP_CONFIG_LOCK_EN            ((u32)0x00000001 << 16)                             /*!<R/W1 Once 0  When this bit is written to '1', this bit cannot be written to '0'. Except the platform reset. 1: REG_SEC_MASTER_SLAVE_PORT_IP_DIS[15:0] can not be accessed. 0: REG_SEC_MASTER_SLAVE_PORT_IP_DIS[15:0] just can be accessed by secure state. */
#define SYSON_S_SHIFT_RSVD5                          14
#define SYSON_S_MASK_RSVD5                           ((u32)0x00000003 << 14)                             /*!<R/W 0  RSVD */
#define SYSON_S_SHIFT_SEC_NAND_FLASH_DIS             13
#define SYSON_S_BIT_SEC_NAND_FLASH_DIS               ((u32)0x00000001 << 13)                             /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for NAND FLASH registers. Master: 1: Disable that NAND FLASH is secure mode. It means that NAND FLASH is Non-secure master. 0: Enable that NAND FLASH is secure mode. (Default) It means that NAND FLASH is Secure master. Slave: 1: NAND FLASH is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access NAND FLASH registers. 0: NAND FLASH is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access NAND FLASH registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_SPORT_DIS                  12
#define SYSON_S_BIT_SEC_SPORT_DIS                    ((u32)0x00000001 << 12)                             /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for SPORT registers. Master: 1: Disable that SPORT is secure mode. It means that SPORT is Non-secure master. 0: Enable that SPORT is secure mode. (Default) It means that SPORT is Secure master. Slave: 1: SPORT is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access SPORT registers. 0: SPORT is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access SPORT registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_ENCODER_DIS                11
#define SYSON_S_BIT_SEC_ENCODER_DIS                  ((u32)0x00000001 << 11)                             /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for Encoder registers. Master: 1: Disable that Encoder is secure mode. It means that Encoder is Non-secure master. 0: Enable that Encoder is secure mode. (Default) It means that Encoder is Secure master. Slave: 1: Encoder is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access Encoder registers. 0: Encoder is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access Encoder registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_ISP_DIS                    10
#define SYSON_S_BIT_SEC_ISP_DIS                      ((u32)0x00000001 << 10)                             /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for ISP registers. Master: 1: Disable that ISP is secure mode. It means that ISP is Non-secure master. 0: Enable that ISP is secure mode. (Default) It means that ISP is Secure master. Slave: 1: ISP is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access ISP registers. 0: ISP is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access ISP registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_I2S_1_DIS                  9
#define SYSON_S_BIT_SEC_I2S_1_DIS                    ((u32)0x00000001 << 9)                              /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for I2S_1 registers. Master: 1: Disable that I2S_1 is secure mode. It means that I2S_1 is Non-secure master. 0: Enable that I2S_1 is secure mode. (Default) It means that I2S_1 is Secure master. Slave: 1: I2S_1 is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access I2S_1 registers. 0: I2S_1 is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access I2S_1 registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_I2S_0_DIS                  8
#define SYSON_S_BIT_SEC_I2S_0_DIS                    ((u32)0x00000001 << 8)                              /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for I2S_0 registers. Master: 1: Disable that I2S_0 is secure mode. It means that I2S_0 is Non-secure master. 0: Enable that I2S_0 is secure mode. (Default) It means that I2S_0 is Secure master. Slave: 1: I2S_0 is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access I2S_0 registers. 0: I2S_0 is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access I2S_0 registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_VOE_DIS                    7
#define SYSON_S_BIT_SEC_VOE_DIS                      ((u32)0x00000001 << 7)                              /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for VOE registers. Master: 1: Disable that VOE is secure mode. It means that VOE is Non-secure master. 0: Enable that VOE is secure mode. (Default) It means that VOE is Secure master. Slave: 1: VOE is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access VOE registers. 0: VOE is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access VOE registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_NN_DIS                     6
#define SYSON_S_BIT_SEC_NN_DIS                       ((u32)0x00000001 << 6)                              /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for NN registers. Master: 1: Disable that NN is secure mode. It means that NN is Non-secure master. 0: Enable that NN is secure mode. (Default) It means that NN is Secure master. Slave: 1: NN is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access NN registers. 0: NN is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access NN registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_OTG_DIS                    5
#define SYSON_S_BIT_SEC_OTG_DIS                      ((u32)0x00000001 << 5)                              /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for OTG registers. Master: 1: Disable that OTG is secure mode. It means that OTG is Non-secure master. 0: Enable that OTG is secure mode. (Default) It means that OTG is Secure master. Slave: 1: OTG is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access OTG registers. 0: OTG is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access OTG registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_MII_DIS                    4
#define SYSON_S_BIT_SEC_MII_DIS                      ((u32)0x00000001 << 4)                              /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for MII registers. Master: 1: Disable that MII is secure mode. It means that MII is Non-secure master. 0: Enable that MII is secure mode. (Default) It means that MII is Secure master. Slave: 1: MII is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access MII registers. 0: MII is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access MII registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_SD_HOST_DIS                3
#define SYSON_S_BIT_SEC_SD_HOST_DIS                  ((u32)0x00000001 << 3)                              /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for SD_HOST registers. Master: 1: Disable that SD_HOST is secure mode. It means that SD_HOST is Non-secure master. 0: Enable that SD_HOST is secure mode. (Default) It means that SD_HOST is Secure master. Slave: 1: SD_HOST is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access SDIO_HOST registers. 0: SD_HOST is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access SD_HOST registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_SDIO_HOST_DIS              2
#define SYSON_S_BIT_SEC_SDIO_HOST_DIS                ((u32)0x00000001 << 2)                              /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for SDIO_HOST registers. Master: 1: Disable that SDIO_HOST is secure mode. It means that SDIO_HOST is Non-secure master. 0: Enable that SDIO_HOST is secure mode. (Default) It means that SDIO_HOST is Secure master. Slave: 1: SDIO_HOST is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access SDIO_HOST registers. 0: SDIO_HOST is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access SDIO_HOST registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
#define SYSON_S_SHIFT_SEC_WLAN_DIS                   1
#define SYSON_S_BIT_SEC_WLAN_DIS                     ((u32)0x00000001 << 1)                              /*!<R/W Once 0  This bit is the control bit of secure filter check and protect signal bit for WLAN registers. Master: 1: Disable that WLAN is secure mode. It means that WLAN is Non-secure master. 0: Enable that WLAN is secure mode. (Default) It means that WLAN is Secure master. Slave: 1: WLAN is Non-secure register. It means that disable secure filter check , so allow Non-secure and Secure masters can access WLAN registers. 0: WLAN is Secure register. (Default) It means that enable secure filter check, so allow only Secure masters can access WLAN registers. Non-secure masters access will be filtered out. This bit is W Once. Re-configure them, unless the platform reset. */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SEC_SLAVE_PORT_IP_DIS
 * @brief                                            (@ 0X06C)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define SYSON_S_SHIFT_RSVD6                          31
#define SYSON_S_BIT_RSVD6                            ((u32)0x00000001 << 31)                             /*!<R 0   */
#else
#define SYSON_S_SHIFT_SEC_BUS_REGU_CTRL_DIS          31
#define SYSON_S_BIT_SEC_BUS_REGU_CTRL_DIS            ((u32)0x00000001 << 31)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for BUS Regulator registers. 1: BUS Regulator is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access BUS Regulator registers. 0: BUS Regulator is Secure register. It means that enable secure filter check, so allow only Secure masters can access BUS Regulator registers. Non-secure masters access will be filtered out. */
#endif
#define SYSON_S_SHIFT_SEC_RSA_CTRL_DIS               30
#define SYSON_S_BIT_SEC_RSA_CTRL_DIS                 ((u32)0x00000001 << 30)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for RSA registers. 1: RSA is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access RSA registers. 0: RSA is Secure register. It means that enable secure filter check, so allow only Secure masters can access RSA registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_DDR_CTRL_DIS               29
#define SYSON_S_BIT_SEC_DDR_CTRL_DIS                 ((u32)0x00000001 << 29)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for DDR related (Ctrler/ PHY Ctrler/ PHY Calib/ Ctrler Func port) registers. 1: DDR related registers is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access DDR related registers. 0: DDR related registers is Secure register. It means that enable secure filter check, so allow only Secure masters can access DDR related registers. Non-secure masters access will be filtered out.  */
#define SYSON_S_SHIFT_SEC_FLASH_CTRL_DIS             28
#define SYSON_S_BIT_SEC_FLASH_CTRL_DIS               ((u32)0x00000001 << 28)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for Flash controller registers. 1: Flash controller is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access Flash controller registers. 0: Flash controller is Secure register. It means that enable secure filter check, so allow only Secure masters can access Flash controller registers. Non-secure masters access will be filtered out.  */
#define SYSON_S_SHIFT_SEC_HS_SPI1_DIS                27
#define SYSON_S_BIT_SEC_HS_SPI1_DIS                  ((u32)0x00000001 << 27)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for HS_SPI1 registers. 1: HS_SPI1 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access HS_SPI1 registers. 0: HS_SPI1 is Secure register. It means that enable secure filter check, so allow only Secure masters can access HS_SPI1 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_HS_SPI0_DIS                26
#define SYSON_S_BIT_SEC_HS_SPI0_DIS                  ((u32)0x00000001 << 26)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for HS_SPI0 registers. 1: HS_SPI0 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access HS_SPI0 registers. 0: HS_SPI0 is Secure register. It means that enable secure filter check, so allow only Secure masters can access HS_SPI0 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_SPI1_DIS                   25
#define SYSON_S_BIT_SEC_SPI1_DIS                     ((u32)0x00000001 << 25)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for SPI1 registers. 1: SPI1 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access SPI1 registers. 0: SPI1 is Secure register. It means that enable secure filter check, so allow only Secure masters can access SPI1 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_SPI0_DIS                   24
#define SYSON_S_BIT_SEC_SPI0_DIS                     ((u32)0x00000001 << 24)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for SPI0 registers. 1: SPI0 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access SPI0 registers. 0: SPI0 is Secure register. It means that enable secure filter check, so allow only Secure masters can access SPI0 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_ED2519_DIS                 23
#define SYSON_S_BIT_SEC_ED2519_DIS                   ((u32)0x00000001 << 23)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for ED25519 registers. 1: ED25519 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access ED25519 registers. 0: ED25519 is Secure register. It means that enable secure filter check, so allow only Secure masters can access ED25519 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_ECDSA_DIS                  22
#define SYSON_S_BIT_SEC_ECDSA_DIS                    ((u32)0x00000001 << 22)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for ECDSA registers. 1: ECDSA is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access ECDSA registers. 0: ECDSA is Secure register. It means that enable secure filter check, so allow only Secure masters can access ECDSA registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_CODEC_DIS                  21
#define SYSON_S_BIT_SEC_CODEC_DIS                    ((u32)0x00000001 << 21)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for CODEC registers. 1: CODEC is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access CODEC registers. 0: CODEC is Secure register. It means that enable secure filter check, so allow only Secure masters can access CODEC registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_SGPIO_DIS                  20
#define SYSON_S_BIT_SEC_SGPIO_DIS                    ((u32)0x00000001 << 20)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for SGPIO registers. 1: SGPIO is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access SGPIO registers. 0: SGPIO is Secure register. It means that enable secure filter check, so allow only Secure masters can access SGPIO registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_PWM_DIS                    19
#define SYSON_S_BIT_SEC_PWM_DIS                      ((u32)0x00000001 << 19)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for PWM registers. 1: PWM is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access PWM registers. 0: PWM is Secure register. It means that enable secure filter check, so allow only Secure masters can access PWM registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_ADC_DIS                    18
#define SYSON_S_BIT_SEC_ADC_DIS                      ((u32)0x00000001 << 18)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for ADC registers. 1: ADC is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access ADC registers. 0: ADC is Secure register. It means that enable secure filter check, so allow only Secure masters can access ADC registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_UART4_DIS                  17
#define SYSON_S_BIT_SEC_UART4_DIS                    ((u32)0x00000001 << 17)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for UART4 registers.(BT UART) 1: UART4 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access UART4 registers. 0: UART4 is Secure register. It means that enable secure filter check, so allow only Secure masters can access UART4 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_UART3_DIS                  16
#define SYSON_S_BIT_SEC_UART3_DIS                    ((u32)0x00000001 << 16)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for UART3 registers. 1: UART3 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access UART3 registers. 0: UART3 is Secure register. It means that enable secure filter check, so allow only Secure masters can access UART3 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_UART2_DIS                  15
#define SYSON_S_BIT_SEC_UART2_DIS                    ((u32)0x00000001 << 15)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for UART2 registers. 1: UART2 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access UART2 registers. 0: UART2 is Secure register. It means that enable secure filter check, so allow only Secure masters can access UART2 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_UART1_DIS                  14
#define SYSON_S_BIT_SEC_UART1_DIS                    ((u32)0x00000001 << 14)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for UART1 registers. 1: UART1 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access UART1 registers. 0: UART1 is Secure register. It means that enable secure filter check, so allow only Secure masters can access UART1 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_UART0_DIS                  13
#define SYSON_S_BIT_SEC_UART0_DIS                    ((u32)0x00000001 << 13)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for UART0 registers. 1: UART0 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access UART0 registers. 0: UART0 is Secure register. It means that enable secure filter check, so allow only Secure masters can access UART0 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_TRNG_DIS                   12
#define SYSON_S_BIT_SEC_TRNG_DIS                     ((u32)0x00000001 << 12)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for TRNG registers. 1: TRNG is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access TRNG registers. 0: TRNG is Secure register. It means that enable secure filter check, so allow only Secure masters can access TRNG registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_I2C3_DIS                   11
#define SYSON_S_BIT_SEC_I2C3_DIS                     ((u32)0x00000001 << 11)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for I2C3 registers. 1: I2C3 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access I2C3 registers. 0: I2C3 is Secure register. It means that enable secure filter check, so allow only Secure masters can access I2C3 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_I2C2_DIS                   10
#define SYSON_S_BIT_SEC_I2C2_DIS                     ((u32)0x00000001 << 10)                             /*!<R/W Once 1  This bit is the control bit of secure filter check for I2C2 registers. 1: I2C2 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access I2C2 registers. 0: I2C2 is Secure register. It means that enable secure filter check, so allow only Secure masters can access I2C2 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_I2C1_DIS                   9
#define SYSON_S_BIT_SEC_I2C1_DIS                     ((u32)0x00000001 << 9)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for I2C1 registers. 1: I2C1 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access I2C1 registers. 0: I2C1 is Secure register. It means that enable secure filter check, so allow only Secure masters can access I2C1 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_I2C0_DIS                   8
#define SYSON_S_BIT_SEC_I2C0_DIS                     ((u32)0x00000001 << 8)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for I2C0 registers. 1: I2C0 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access I2C0 registers. 0: I2C0 is Secure register. It means that enable secure filter check, so allow only Secure masters can access I2C0 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_GTIMER3_DIS                7
#define SYSON_S_BIT_SEC_GTIMER3_DIS                  ((u32)0x00000001 << 7)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for GTIMER3 registers. 1: GTIMER3 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access GTIMER3 registers. 0: GTIMER3 is Secure register. It means that enable secure filter check, so allow only Secure masters can access GTIMER3 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_GTIMER2_DIS                6
#define SYSON_S_BIT_SEC_GTIMER2_DIS                  ((u32)0x00000001 << 6)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for GTIMER2 registers. 1: GTIMER2 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access GTIMER2 registers. 0: GTIMER2 is Secure register. It means that enable secure filter check, so allow only Secure masters can access GTIMER2 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_GTIMER1_DIS                5
#define SYSON_S_BIT_SEC_GTIMER1_DIS                  ((u32)0x00000001 << 5)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for GTIMER1 registers. 1: GTIMER1 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access GTIMER1 registers. 0: GTIMER1 is Secure register. It means that enable secure filter check, so allow only Secure masters can access GTIMER1 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_GTIMER0_DIS                4
#define SYSON_S_BIT_SEC_GTIMER0_DIS                  ((u32)0x00000001 << 4)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for GTIMER0 registers. 1: GTIMER0 is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access GTIMER0 registers. 0: GTIMER0 is Secure register. It means that enable secure filter check, so allow only Secure masters can access GTIMER0 registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_SYSON_GPIO_DIS             3
#define SYSON_S_BIT_SEC_SYSON_GPIO_DIS               ((u32)0x00000001 << 3)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for SYSON_GPIO registers. 1: SYSON_GPIO is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access SYSON_GPIO registers. 0: SYSON_GPIO is Secure register. It means that enable secure filter check, so allow only Secure masters can access SYSON_GPIO registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_PON_GPIO_DIS               2
#define SYSON_S_BIT_SEC_PON_GPIO_DIS                 ((u32)0x00000001 << 2)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for PON_GPIO registers. 1: PON_GPIO is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access PON_GPIO registers. 0: PON_GPIO is Secure register. It means that enable secure filter check, so allow only Secure masters can access PON_GPIO registers. Non-secure masters access will be filtered out. */
#define SYSON_S_SHIFT_SEC_AON_GPIO_DIS               1
#define SYSON_S_BIT_SEC_AON_GPIO_DIS                 ((u32)0x00000001 << 1)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for AON_GPIO registers. 1: AON_GPIO is Non-secure register. (Default) It means that disable secure filter check, so allow Non-secure and Secure masters can access AON_GPIO registers. 0: AON_GPIO is Secure register. It means that enable secure filter check, so allow only Secure masters can access AON_GPIO registers. Non-secure masters access will be filtered out. */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_SEC_CTRL
 * @brief                                            (@ 0X074)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_FLASH_SEC_KEY_RDY_EN           4
#define SYSON_S_BIT_FLASH_SEC_KEY_RDY_EN             ((u32)0x00000001 << 4)                              /*!<R/W 0  Flash SEC key_ready control bit(For Engine reset wait for key_ready pull high, then latch key values)  */
#define SYSON_S_SHIFT_SCE_KEY_SEL                    2
#define SYSON_S_MASK_SCE_KEY_SEL                     ((u32)0x00000003 << 2)                              /*!<R/W 0  2'b0 : Only key 1 load into Flash SEC 2 key regions 2'b1 : Only key 2 load into Flash SEC 2 key regions 2'b2 : key 1 load into Flash SEC key 1 region; key 2 load into Flash SEC key 2 region 2'b3 : key 1 load into Flash SEC key 2 region; key 2 load into Flash SEC key 1 region  */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_RSA_FUNC_CTRL
 * @brief                                            (@ 0X078)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_RSA_EN                         1
#define SYSON_S_BIT_RSA_EN                           ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable RSA */
#define SYSON_S_SHIFT_RSA_CLK_EN                     0
#define SYSON_S_BIT_RSA_CLK_EN                       ((u32)0x00000001 << 0)                              /*!<R/W 0  1: EnableRSA CLK */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_LPDDR1_CTRL
 * @brief                                            (@ 0X080)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_HS_LPDDR1_SPEEDUP              8
#define SYSON_S_BIT_HS_LPDDR1_SPEEDUP                ((u32)0x00000001 << 8)                              /*!<R/W 0  rxi310_speedup_sim */
#define SYSON_S_SHIFT_HS_LPDDR1_CLK_EN               4
#define SYSON_S_BIT_HS_LPDDR1_CLK_EN                 ((u32)0x00000001 << 4)                              /*!<R/W 0  memory control function enable  */
#define SYSON_S_SHIFT_HS_LPDDR1_EN                   0
#define SYSON_S_BIT_HS_LPDDR1_EN                     ((u32)0x00000001 << 0)                              /*!<R/W 0  memory control function enable  */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_DDRPHY_CTRL
 * @brief                                            (@ 0X084)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_DFI_PLL_REF_TEST_MODE          10
#define SYSON_S_BIT_DFI_PLL_REF_TEST_MODE            ((u32)0x00000001 << 10)                             /*!<R/W 0  1:enable */
#define SYSON_S_SHIFT_DFI_PLL_TEST_MODE              9
#define SYSON_S_BIT_DFI_PLL_TEST_MODE                ((u32)0x00000001 << 9)                              /*!<R/W 0  1:enable */
#define SYSON_S_SHIFT_DFI_PLL_TEST_CKE               8
#define SYSON_S_BIT_DFI_PLL_TEST_CKE                 ((u32)0x00000001 << 8)                              /*!<R/W 0  1:enable */
#define SYSON_S_SHIFT_HS_DDRPHY_CRT_CLK_EN           7
#define SYSON_S_BIT_HS_DDRPHY_CRT_CLK_EN             ((u32)0x00000001 << 7)                              /*!<R/W 0  CRT control register clock gating control */
#define SYSON_S_SHIFT_HS_DDRPHY_RBUS_CLK_EN          6
#define SYSON_S_BIT_HS_DDRPHY_RBUS_CLK_EN            ((u32)0x00000001 << 6)                              /*!<R/W 0  Rbus interface clock gating control */
#define SYSON_S_SHIFT_DDRPHY_VCCON                   4
#define SYSON_S_BIT_DDRPHY_VCCON                     ((u32)0x00000001 << 4)                              /*!<R/W 0  1: enable core power */
#define SYSON_S_SHIFT_HS_DDRPHY_PLL_RDY              3
#define SYSON_S_BIT_HS_DDRPHY_PLL_RDY                ((u32)0x00000001 << 3)                              /*!<R 0  PLL ready */
#define SYSON_S_SHIFT_DDRPHY_RBUS_EN                 2
#define SYSON_S_BIT_DDRPHY_RBUS_EN                   ((u32)0x00000001 << 2)                              /*!<R/W 0  1: reset RBUS */
#define SYSON_S_SHIFT_PWDPAD15N                      1
#define SYSON_S_BIT_PWDPAD15N                        ((u32)0x00000001 << 1)                              /*!<R/W 0  0:RESET PAD pull high and CKE PAD pull low (DRAM into seif-refresh mode) */
#define SYSON_S_SHIFT_HS_DDRPHY_CRT_RST              0
#define SYSON_S_BIT_HS_DDRPHY_CRT_RST                ((u32)0x00000001 << 0)                              /*!<R/W 0  CRT active low asynchronous reset */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_FLASH_CTRL
 * @brief                                            (@ 0X08C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_NAND_FLASH_CLK_EN              6
#define SYSON_S_BIT_NAND_FLASH_CLK_EN                ((u32)0x00000001 << 6)                              /*!<R/W 0  1: Enable NAND FLASH CLK */
#define SYSON_S_SHIFT_NAND_FLASH_EN                  5
#define SYSON_S_BIT_NAND_FLASH_EN                    ((u32)0x00000001 << 5)                              /*!<R/W 0  1: Enable NAND FLASH */
#define SYSON_S_SHIFT_HS_FLASH_INIT_OK               4
#define SYSON_S_BIT_HS_FLASH_INIT_OK                 ((u32)0x00000001 << 4)                              /*!<R 0  BOOT_finish  */
#define SYSON_S_SHIFT_SYS_FLASH_SRC_SEL              2
#define SYSON_S_BIT_SYS_FLASH_SRC_SEL                ((u32)0x00000001 << 2)                              /*!<R/W 0  0: 250MHz, 1:200MHz */
#define SYSON_S_SHIFT_NOR_FLASH_CLK_EN               1
#define SYSON_S_BIT_NOR_FLASH_CLK_EN                 ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable NOR FLASH CLK */
#define SYSON_S_SHIFT_NOR_FLASH_EN                   0
#define SYSON_S_BIT_NOR_FLASH_EN                     ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable NOR FLASH */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_FLASH_PHY_CTRL0
 * @brief                                            (@ 0X090)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_FLASH_PHY_CLK_SEL              20
#define SYSON_S_BIT_FLASH_PHY_CLK_SEL                ((u32)0x00000001 << 20)                             /*!<R/W 0  1: SPIC phy use loopback clock through delay chain from PAD as fetch clk. 0: SPIC phy use spic controller clk trhough delay chain as fetch clk */
#define SYSON_S_SHIFT_FLASH_PHY_FETCH_PHASE          16
#define SYSON_S_MASK_FLASH_PHY_FETCH_PHASE           ((u32)0x0000000F << 16)                             /*!<R/W 0  [0]: delay 0.5 spic_clk period to fetch lower lane data [1]: delay 0.5 spic_clk period to fetch upper lane data [2]: delay 0.5 spic_clk period to sync lower lane data to spic [3]: delay 0.5 spic_clk period to sync upper lane data to spic */
#define SYSON_S_SHIFT_FLASH_PHY_MUX_SEL              7
#define SYSON_S_BIT_FLASH_PHY_MUX_SEL                ((u32)0x00000001 << 7)                              /*!<R/W 0  [0]:NOR FLASH [1]: NAND FLASH */
#define SYSON_S_SHIFT_FLASH_PHY_DLY_EN               5
#define SYSON_S_MASK_FLASH_PHY_DLY_EN                ((u32)0x00000003 << 5)                              /*!<R/W 0  [0]: delay lower lane a spic_clk period [1]: delay upper lane a spic_clk period */
#define SYSON_S_SHIFT_FLASH_PHY_DQS_DDR_EN           4
#define SYSON_S_BIT_FLASH_PHY_DQS_DDR_EN             ((u32)0x00000001 << 4)                              /*!<R/W 0  enable DQS to fetch double data rate rx data */
#define SYSON_S_SHIFT_FLASH_PHY_DQS_EN               3
#define SYSON_S_BIT_FLASH_PHY_DQS_EN                 ((u32)0x00000001 << 3)                              /*!<R/W 0  enable DQS to fetch rx data */
#define SYSON_S_SHIFT_FLASH_PHY_MERGE_PHASE_EN       2
#define SYSON_S_BIT_FLASH_PHY_MERGE_PHASE_EN         ((u32)0x00000001 << 2)                              /*!<R/W 0  0: posedge rx data first 1: negedge rx data first */
#define SYSON_S_SHIFT_FLASH_PHY_OUTPUT_PHASE_EN      1
#define SYSON_S_BIT_FLASH_PHY_OUTPUT_PHASE_EN        ((u32)0x00000001 << 1)                              /*!<R/W 0  delay 0.5 spic_clk period of sclk */
#define SYSON_S_SHIFT_FLASH_PHY_EN                   0
#define SYSON_S_BIT_FLASH_PHY_EN                     ((u32)0x00000001 << 0)                              /*!<R/W 0  enble rx data */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_FLASH_PHY_CTRL1
 * @brief                                            (@ 0X094)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_FLASH_PHY_DQSU_DLY_SEL         16
#define SYSON_S_MASK_FLASH_PHY_DQSU_DLY_SEL          ((u32)0x000000FF << 16)                             /*!<R/W 0  select delay level of DQS on the upper lane */
#define SYSON_S_SHIFT_FLASH_PHY_DQSL_DLY_SEL         8
#define SYSON_S_MASK_FLASH_PHY_DQSL_DLY_SEL          ((u32)0x000000FF << 8)                              /*!<R/W 0  select delay level of DQS on the lower lane */
#define SYSON_S_SHIFT_FLASH_PHY_OUTPUT_DLY_SEL       0
#define SYSON_S_MASK_FLASH_PHY_OUTPUT_DLY_SEL        ((u32)0x000000FF << 0)                              /*!<R/W 0  select delay level of sclk delay line  */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_PLATFORM_CTRL0
 * @brief                                            (@ 0X09C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_HS_TRNG_HI_CLK_SEL             27
#define SYSON_S_BIT_HS_TRNG_HI_CLK_SEL               ((u32)0x00000001 << 27)                             /*!<R/W 1  0: XTAL, 1: 40MHz */
#define SYSON_S_SHIFT_HS_TRNG_LOW_CLK_SEL            26
#define SYSON_S_BIT_HS_TRNG_LOW_CLK_SEL              ((u32)0x00000001 << 26)                             /*!<R/W 1  0: 32kHz, 1: 128kHz */
#define SYSON_S_SHIFT_HS_TRNG_CLK_EN                 25
#define SYSON_S_BIT_HS_TRNG_CLK_EN                   ((u32)0x00000001 << 25)                             /*!<R/W 0  1: TRNG clock enable */
#define SYSON_S_SHIFT_HS_TRNG_EN                     24
#define SYSON_S_BIT_HS_TRNG_EN                       ((u32)0x00000001 << 24)                             /*!<R/W 0  1: enable TRNG IP */
#define SYSON_S_SHIFT_HS_IPSEC_CLK_EN                23
#define SYSON_S_BIT_HS_IPSEC_CLK_EN                  ((u32)0x00000001 << 23)                             /*!<R/W 0  1: security engine clock enable */
#define SYSON_S_SHIFT_HS_IPSEC_EN                    22
#define SYSON_S_BIT_HS_IPSEC_EN                      ((u32)0x00000001 << 22)                             /*!<R/W 0  1: enable security engine IP */
#define SYSON_S_SHIFT_HS_ED255_CLK_EN                21
#define SYSON_S_BIT_HS_ED255_CLK_EN                  ((u32)0x00000001 << 21)                             /*!<R/W 0  1: ED25519 clock enable */
#define SYSON_S_SHIFT_HS_ED255_EN                    20
#define SYSON_S_BIT_HS_ED255_EN                      ((u32)0x00000001 << 20)                             /*!<R/W 0  1: enable ED25519 IP */
#define SYSON_S_SHIFT_HS_ECC_CLK_EN                  19
#define SYSON_S_BIT_HS_ECC_CLK_EN                    ((u32)0x00000001 << 19)                             /*!<R/W 0  1: ECC clock enable */
#define SYSON_S_SHIFT_HS_ECC_EN                      18
#define SYSON_S_BIT_HS_ECC_EN                        ((u32)0x00000001 << 18)                             /*!<R/W 0  1: enable ECC IP */
#define SYSON_S_SHIFT_LXBUS_CLK_EN                   17
#define SYSON_S_BIT_LXBUS_CLK_EN                     ((u32)0x00000001 << 17)                             /*!<R/W 0  1: Enable LX bus CLK */
#define SYSON_S_SHIFT_LXBUS_EN                       16
#define SYSON_S_BIT_LXBUS_EN                         ((u32)0x00000001 << 16)                             /*!<R/W 0  1: Enable LX bus */
#define SYSON_S_SHIFT_HS_GDMA1_CLK_ALWS_DIS          13
#define SYSON_S_BIT_HS_GDMA1_CLK_ALWS_DIS            ((u32)0x00000001 << 13)                             /*!<R/W 0  gdma_clk_always_disable */
#define SYSON_S_SHIFT_HS_GDMA1_CLK_ALWS_EN           12
#define SYSON_S_BIT_HS_GDMA1_CLK_ALWS_EN             ((u32)0x00000001 << 12)                             /*!<R/W 0  gdma_clk_always_enable */
#define SYSON_S_SHIFT_HS_GDMA1_CLK_EN                9
#define SYSON_S_BIT_HS_GDMA1_CLK_EN                  ((u32)0x00000001 << 9)                              /*!<R/W 0  1: Enable GDMA1 CLK */
#define SYSON_S_SHIFT_HS_GDMA1_EN                    8
#define SYSON_S_BIT_HS_GDMA1_EN                      ((u32)0x00000001 << 8)                              /*!<R/W 0  1: Enable GDMA1 */
#define SYSON_S_SHIFT_HS_GDMA0_CLK_ALWS_DIS          5
#define SYSON_S_BIT_HS_GDMA0_CLK_ALWS_DIS            ((u32)0x00000001 << 5)                              /*!<R/W 0  gdma_clk_always_disable */
#define SYSON_S_SHIFT_HS_GDMA0_CLK_ALWS_EN           4
#define SYSON_S_BIT_HS_GDMA0_CLK_ALWS_EN             ((u32)0x00000001 << 4)                              /*!<R/W 0  gdma_clk_always_enable */
#define SYSON_S_SHIFT_HS_GDMA0_CLK_EN                1
#define SYSON_S_BIT_HS_GDMA0_CLK_EN                  ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable GDMA0 CLK */
#define SYSON_S_SHIFT_HS_GDMA0_EN                    0
#define SYSON_S_BIT_HS_GDMA0_EN                      ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable GDMA0 */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_FEPHY_CTRL
 * @brief                                            (@ 0X100)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_PHY_AD                         8
#define SYSON_S_MASK_PHY_AD                          ((u32)0x0000001F << 8)                              /*!<R/W 1  phy address */
#define SYSON_S_SHIFT_REF_PORB_DV_CEL_L              7
#define SYSON_S_BIT_REF_PORB_DV_CEL_L                ((u32)0x00000001 << 7)                              /*!<R 0  detecting digital core power lower than ref */
#define SYSON_S_SHIFT_REF_PORB_AV_CEL_L              6
#define SYSON_S_BIT_REF_PORB_AV_CEL_L                ((u32)0x00000001 << 6)                              /*!<R 0  detecting analog core power lower than ref */
#define SYSON_S_SHIFT_REF_AVTH_CEL_H                 4
#define SYSON_S_MASK_REF_AVTH_CEL_H                  ((u32)0x00000003 << 4)                              /*!<R/W 11  analog core power threshold adjust */
#define SYSON_S_SHIFT_REF_AVTH_CEL_L                 2
#define SYSON_S_MASK_REF_AVTH_CEL_L                  ((u32)0x00000003 << 2)                              /*!<R/W 11  analog core power threshold adjust */
#define SYSON_S_SHIFT_REF_PORB_ANA_CELL_L            0
#define SYSON_S_BIT_REF_PORB_ANA_CELL_L              ((u32)0x00000001 << 0)                              /*!<R 0  debug signal */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_TIMER_CTRL
 * @brief                                            (@ 0X104)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_TG3_SRC_SEL                21
#define SYSON_S_MASK_SYS_TG3_SRC_SEL                 ((u32)0x00000003 << 21)                             /*!<R/W 10  00: 32kHz 01: 4MHz 10: 31.25MHz 11: rsvd */
#define SYSON_S_SHIFT_SYS_TG3_INTR_CLK_SEL           20
#define SYSON_S_BIT_SYS_TG3_INTR_CLK_SEL             ((u32)0x00000001 << 20)                             /*!<R/W 0  Select TC1 interrupt clock source, 0: APB clock, 1: timer counter clock (controlled by BIT_TG3_SCLK_SEL[1:0]) */
#define SYSON_S_SHIFT_SYS_TG3_SCLK_EN                19
#define SYSON_S_BIT_SYS_TG3_SCLK_EN                  ((u32)0x00000001 << 19)                             /*!<R/W 0  1: Enable SYS Timer Group3 Sclock */
#define SYSON_S_SHIFT_SYS_TG3_PCLK_EN                18
#define SYSON_S_BIT_SYS_TG3_PCLK_EN                  ((u32)0x00000001 << 18)                             /*!<R/W 0  1: Enable SYS Timer Group3 Pclock */
#define SYSON_S_SHIFT_SYS_TG3_EN                     17
#define SYSON_S_BIT_SYS_TG3_EN                       ((u32)0x00000001 << 17)                             /*!<R/W 0  1: Enable SYS Timer Group3 block */
#define SYSON_S_SHIFT_SYS_TG2_SRC_SEL                12
#define SYSON_S_MASK_SYS_TG2_SRC_SEL                 ((u32)0x00000003 << 12)                             /*!<R/W 10  00: 32kHz 01: 4MHz 10: 31.25MHz 11: rsvd */
#define SYSON_S_SHIFT_SYS_TG2_INTR_CLK_SEL           11
#define SYSON_S_BIT_SYS_TG2_INTR_CLK_SEL             ((u32)0x00000001 << 11)                             /*!<R/W 0  Select TC1 interrupt clock source, 0: APB clock, 1: timer counter clock (controlled by BIT_TG2_SCLK_SEL[1:0]) */
#define SYSON_S_SHIFT_SYS_TG2_SCLK_EN                10
#define SYSON_S_BIT_SYS_TG2_SCLK_EN                  ((u32)0x00000001 << 10)                             /*!<R/W 0  1: Enable SYS Timer Group2 Sclock */
#define SYSON_S_SHIFT_SYS_TG2_PCLK_EN                9
#define SYSON_S_BIT_SYS_TG2_PCLK_EN                  ((u32)0x00000001 << 9)                              /*!<R/W 0  1: Enable SYS Timer Group2 Pclock */
#define SYSON_S_SHIFT_SYS_TG2_EN                     8
#define SYSON_S_BIT_SYS_TG2_EN                       ((u32)0x00000001 << 8)                              /*!<R/W 0  1: Enable SYS Timer Group2 block */
#define SYSON_S_SHIFT_SYS_TG1_SRC_SEL                4
#define SYSON_S_MASK_SYS_TG1_SRC_SEL                 ((u32)0x00000003 << 4)                              /*!<R/W 10  00: 32kHz 01: 4MHz 10: 31.25MHz 11: rsvd */
#define SYSON_S_SHIFT_SYS_TG1_INTR_CLK_SEL           3
#define SYSON_S_BIT_SYS_TG1_INTR_CLK_SEL             ((u32)0x00000001 << 3)                              /*!<R/W 0  select TG1 interrupt clock source, 0: APB clock, 1: timer counter clock (controlled by BIT_TG1_SCLK_SEL[1:0]) */
#define SYSON_S_SHIFT_SYS_TG1_SCLK_EN                2
#define SYSON_S_BIT_SYS_TG1_SCLK_EN                  ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable SYS Timer Group1 Sclock */
#define SYSON_S_SHIFT_SYS_TG1_PCLK_EN                1
#define SYSON_S_BIT_SYS_TG1_PCLK_EN                  ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable SYS Timer Group1 Pclock */
#define SYSON_S_SHIFT_SYS_TG1_EN                     0
#define SYSON_S_BIT_SYS_TG1_EN                       ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable SYS Timer Group1 block */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_ADC_CTRL0
 * @brief                                            (@ 0X108)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_DUMMY_0                        24
#define SYSON_S_MASK_DUMMY_0                         ((u32)0x000000FF << 24)                             /*!<R/W 00000000   */
#define SYSON_S_SHIFT_BYPASSEN                       16
#define SYSON_S_MASK_BYPASSEN                        ((u32)0x000000FF << 16)                             /*!<R/W 00000000  1:1V mode, 0: 3.3V mode */
#define SYSON_S_SHIFT_DUMMY_1                        14
#define SYSON_S_MASK_DUMMY_1                         ((u32)0x00000003 << 14)                             /*!<R/W 00   */
#define SYSON_S_SHIFT_REG_VCM_SEL                    12
#define SYSON_S_MASK_REG_VCM_SEL                     ((u32)0x00000003 << 12)                             /*!<R/W 00  00/01/10/11 0.45/0.4375/0.425/0.4125V */
#define SYSON_S_SHIFT_SEL_LNA                        11
#define SYSON_S_BIT_SEL_LNA                          ((u32)0x00000001 << 11)                             /*!<R/W 1  1: comparator low noise for ALL bit */
#define SYSON_S_SHIFT_SEL_LN                         10
#define SYSON_S_BIT_SEL_LN                           ((u32)0x00000001 << 10)                             /*!<R/W 1  1: comparator low noise for LSB 6bit */
#define SYSON_S_SHIFT_REG_META                       9
#define SYSON_S_BIT_REG_META                         ((u32)0x00000001 << 9)                              /*!<R/W 0  1: enable meta detect */
#define SYSON_S_SHIFT_REG_CMPDEC                     7
#define SYSON_S_MASK_REG_CMPDEC                      ((u32)0x00000003 << 7)                              /*!<R/W 01  meta detect time 00: short */
#define SYSON_S_SHIFT_REG_REV_CLK                    6
#define SYSON_S_BIT_REG_REV_CLK                      ((u32)0x00000001 << 6)                              /*!<R/W 0  1: rever ckdata */
#define SYSON_S_SHIFT_REG_VREF_SEL                   4
#define SYSON_S_MASK_REG_VREF_SEL                    ((u32)0x00000003 << 4)                              /*!<R/W 00  00:0.9V 01:0.95V 10:1V 11:1.05V */
#define SYSON_S_SHIFT_REG_DELAY                      3
#define SYSON_S_BIT_REG_DELAY                        ((u32)0x00000001 << 3)                              /*!<R/W 0  clk delay */
#define SYSON_S_SHIFT_REG_CK                         2
#define SYSON_S_BIT_REG_CK                           ((u32)0x00000001 << 2)                              /*!<R/W 0  1: clk from external */
#define SYSON_S_SHIFT_POW_REF                        1
#define SYSON_S_BIT_POW_REF                          ((u32)0x00000001 << 1)                              /*!<R/W 0  pow adc refgen */
#define SYSON_S_SHIFT_POW                            0
#define SYSON_S_BIT_POW                              ((u32)0x00000001 << 0)                              /*!<R/W 0  pow adc */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_ADC_CTRL1
 * @brief                                            (@ 0X10C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_ADC_CTRL_MSR_SEL           5
#define SYSON_S_BIT_SYS_ADC_CTRL_MSR_SEL             ((u32)0x00000001 << 5)                              /*!<R/W 0  0: HW; 1:SW */
#define SYSON_S_SHIFT_SYS_ADC_INTR_CK_SEL            4
#define SYSON_S_BIT_SYS_ADC_INTR_CK_SEL              ((u32)0x00000001 << 4)                              /*!<R/W 0  0: pclk; 1: sclk */
#define SYSON_S_SHIFT_SYS_ISO_ADC                    3
#define SYSON_S_BIT_SYS_ISO_ADC                      ((u32)0x00000001 << 3)                              /*!<R/W 1  1: isolation ADC analog to digital domain; 0: disable isolation */
#define SYSON_S_SHIFT_SYS_ADC_SCLK_EN                2
#define SYSON_S_BIT_SYS_ADC_SCLK_EN                  ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable SYS ADC Sclock */
#define SYSON_S_SHIFT_SYS_ADC_PCLK_EN                1
#define SYSON_S_BIT_SYS_ADC_PCLK_EN                  ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable SYS ADC Pclock */
#define SYSON_S_SHIFT_SYS_ADC_EN                     0
#define SYSON_S_BIT_SYS_ADC_EN                       ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable SYS ADC block */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_GPIO_CTRL
 * @brief                                            (@ 0X110)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_GPIO_INTR_CLK_SEL          3
#define SYSON_S_BIT_SYS_GPIO_INTR_CLK_SEL            ((u32)0x00000001 << 3)                              /*!<R/W 0  0: APB, 1: debounce clock */
#define SYSON_S_SHIFT_SYS_GPIO_SCLK_EN               2
#define SYSON_S_BIT_SYS_GPIO_SCLK_EN                 ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable SYS GPIO Sclock */
#define SYSON_S_SHIFT_SYS_GPIO_PCLK_EN               1
#define SYSON_S_BIT_SYS_GPIO_PCLK_EN                 ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable SYS GPIO Pclock */
#define SYSON_S_SHIFT_SYS_GPIO_EN                    0
#define SYSON_S_BIT_SYS_GPIO_EN                      ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable SYS GPIO block */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_AUDIO_CTRL
 * @brief                                            (@ 0X114)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_SPORT_CODEC_SEL            20
#define SYSON_S_BIT_SYS_SPORT_CODEC_SEL              ((u32)0x00000001 << 20)                             /*!<R/W 0  Codec Select 0: Internal Codec 1: External Codec */
#define SYSON_S_SHIFT_SYS_CODEC_LDO_TUNE             13
#define SYSON_S_MASK_SYS_CODEC_LDO_TUNE              ((u32)0x0000007F << 13)                             /*!<R/W 1011111   */
#define SYSON_S_SHIFT_SYS_CODEC_LDO_EN               12
#define SYSON_S_BIT_SYS_CODEC_LDO_EN                 ((u32)0x00000001 << 12)                             /*!<R/W 0  LDO power control 0: disable LDO 1: enable LDO */
#define SYSON_S_SHIFT_SYS_CODEC_PORB                 11
#define SYSON_S_BIT_SYS_CODEC_PORB                   ((u32)0x00000001 << 11)                             /*!<R/W 0  0: power down codec */
#define SYSON_S_SHIFT_SYS_CODEC_SCLK_EN              10
#define SYSON_S_BIT_SYS_CODEC_SCLK_EN                ((u32)0x00000001 << 10)                             /*!<R/W 0  1: enable codec Sclock */
#define SYSON_S_SHIFT_SYS_CODEC_EN                   8
#define SYSON_S_BIT_SYS_CODEC_EN                     ((u32)0x00000001 << 8)                              /*!<R/W 0  1: enable codec IP */
#define SYSON_S_SHIFT_SYS_SI_SCLK_EN                 7
#define SYSON_S_BIT_SYS_SI_SCLK_EN                   ((u32)0x00000001 << 7)                              /*!<R/W 0  1: enable si Sclock */
#define SYSON_S_SHIFT_SYS_SI_PCLK_EN                 6
#define SYSON_S_BIT_SYS_SI_PCLK_EN                   ((u32)0x00000001 << 6)                              /*!<R/W 0  1: enable si Pclock */
#define SYSON_S_SHIFT_SYS_SI_EN                      5
#define SYSON_S_BIT_SYS_SI_EN                        ((u32)0x00000001 << 5)                              /*!<R/W 0  1: enable si IP */
#define SYSON_S_SHIFT_SYS_SPORT_SRC_SEL              3
#define SYSON_S_MASK_SYS_SPORT_SRC_SEL               ((u32)0x00000003 << 3)                              /*!<R/W 00  00: 40MHz 01: 98.304kHz 10: 45.158kHz 11: rsvd */
#define SYSON_S_SHIFT_SYS_SPORT_SCLK_EN              2
#define SYSON_S_BIT_SYS_SPORT_SCLK_EN                ((u32)0x00000001 << 2)                              /*!<R/W 0  1: enable sport Sclock */
#define SYSON_S_SHIFT_SYS_SPORT_PCLK_EN              1
#define SYSON_S_BIT_SYS_SPORT_PCLK_EN                ((u32)0x00000001 << 1)                              /*!<R/W 0  1: enable sport Pclock */
#define SYSON_S_SHIFT_SYS_SPORT_EN                   0
#define SYSON_S_BIT_SYS_SPORT_EN                     ((u32)0x00000001 << 0)                              /*!<R/W 0  1: enable sport IP */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_ISP_CTRL
 * @brief                                            (@ 0X118)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_ISP_DBG_SEL                16
#define SYSON_S_MASK_SYS_ISP_DBG_SEL                 ((u32)0x0000003F << 16)                             /*!<R/W 0  select ISP dbg mux */
#define SYSON_S_SHIFT_SYS_VOE_CLK_EN                 13
#define SYSON_S_BIT_SYS_VOE_CLK_EN                   ((u32)0x00000001 << 13)                             /*!<R/W 0  1: Enable VOE CLK */
#define SYSON_S_SHIFT_SYS_VOE_EN                     12
#define SYSON_S_BIT_SYS_VOE_EN                       ((u32)0x00000001 << 12)                             /*!<R/W 0  1: Enable VOE */
#define SYSON_S_SHIFT_SYS_ENCODER_SRC_SEL            10
#define SYSON_S_MASK_SYS_ENCODER_SRC_SEL             ((u32)0x00000003 << 10)                             /*!<R/W 01  00: 166.6MHz 01: 125MHz 10: 100MHz 11: rsvd */
#define SYSON_S_SHIFT_SYS_ENCODER_CLK_EN             9
#define SYSON_S_BIT_SYS_ENCODER_CLK_EN               ((u32)0x00000001 << 9)                              /*!<R/W 0  1: Enable Encoder CLK */
#define SYSON_S_SHIFT_SYS_ENCODER_EN                 8
#define SYSON_S_BIT_SYS_ENCODER_EN                   ((u32)0x00000001 << 8)                              /*!<R/W 0  1: Enable Encoder */
#define SYSON_S_SHIFT_SYS_MIPI_SRC_SEL               5
#define SYSON_S_MASK_SYS_MIPI_SRC_SEL                ((u32)0x00000007 << 5)                              /*!<R/W 000  000: 250MHz 001: 200MHz 010: 166.6MHz 011: 125MHz 100: 100MHz 101: 83.3MHz 110: rsvd 111: rsvd */
#define SYSON_S_SHIFT_SYS_ISP_SRC_SEL                2
#define SYSON_S_MASK_SYS_ISP_SRC_SEL                 ((u32)0x00000007 << 2)                              /*!<R/W 000  000: 200MHz 001: 166.6MHz 010: 125MHz 011: 100MHz 100: 83.3MHz 101: rsvd 110: rsvd 111: rsvd */
#define SYSON_S_SHIFT_SYS_ISP_CLK_EN                 1
#define SYSON_S_BIT_SYS_ISP_CLK_EN                   ((u32)0x00000001 << 1)                              /*!<R/W 0  1. Enable ISP CLK */
#define SYSON_S_SHIFT_SYS_ISP_EN                     0
#define SYSON_S_BIT_SYS_ISP_EN                       ((u32)0x00000001 << 0)                              /*!<R/W 0  1. Enable ISP */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_NN_CTRL
 * @brief                                            (@ 0X11C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_NN_SRC_SEL                 3
#define SYSON_S_MASK_SYS_NN_SRC_SEL                  ((u32)0x00000003 << 3)                              /*!<R/W 0  0: 500MHz 1: 400MHz 2: 250MHz */
#define SYSON_S_SHIFT_SYS_NN_CLK_EN                  1
#define SYSON_S_BIT_SYS_NN_CLK_EN                    ((u32)0x00000001 << 1)                              /*!<R/W 0  1. Enable NN CLK */
#define SYSON_S_SHIFT_SYS_NN_EN                      0
#define SYSON_S_BIT_SYS_NN_EN                        ((u32)0x00000001 << 0)                              /*!<R/W 0  1. Enable NN */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_OTG_CTRL
 * @brief                                            (@ 0X120)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_USBPHY_XTAL_SEL                30
#define SYSON_S_BIT_USBPHY_XTAL_SEL                  ((u32)0x00000001 << 30)                             /*!<R/W 0  0:Analog XTAL, 1:Digital XTAL */
#define SYSON_S_SHIFT_USBPHY_CKREF_SEL               26
#define SYSON_S_MASK_USBPHY_CKREF_SEL                ((u32)0x0000000F << 26)                             /*!<R/W 0  0000: 40MHz 0001: 25MHz 0010: 54MHz 0011: 19.2MHz 0100: 20MHz 0101: 26MHz */
#define SYSON_S_SHIFT_SYS_ISO_USBA_EN                25
#define SYSON_S_BIT_SYS_ISO_USBA_EN                  ((u32)0x00000001 << 25)                             /*!<R/W 1  1: enable usb analogy isolation */
#define SYSON_S_SHIFT_SYS_ISO_USBD_EN                24
#define SYSON_S_BIT_SYS_ISO_USBD_EN                  ((u32)0x00000001 << 24)                             /*!<R/W 1  1: enable usb digital isolation */
#define SYSON_S_SHIFT_USB_IBX2MIPI_EN                22
#define SYSON_S_BIT_USB_IBX2MIPI_EN                  ((u32)0x00000001 << 22)                             /*!<R/W 0  1: Enable IBX to MIPI, DDR and EPHY */
#define SYSON_S_SHIFT_USB_IBX2USB_EN                 21
#define SYSON_S_BIT_USB_IBX2USB_EN                   ((u32)0x00000001 << 21)                             /*!<R/W 0  1: Enable IBX to USB */
#define SYSON_S_SHIFT_USB_PDN33                      20
#define SYSON_S_BIT_USB_PDN33                        ((u32)0x00000001 << 20)                             /*!<R/W 1  1: power up USB */
#define SYSON_S_SHIFT_SYS_UABG_EN                    19
#define SYSON_S_BIT_SYS_UABG_EN                      ((u32)0x00000001 << 19)                             /*!<R/W 0  1. Enable bandgap */
#define SYSON_S_SHIFT_SYS_UAHV_EN                    18
#define SYSON_S_BIT_SYS_UAHV_EN                      ((u32)0x00000001 << 18)                             /*!<R/W 0  1: USB PHY analog 3.3V power cut enable */
#define SYSON_S_SHIFT_SYS_USBD_EN                    16
#define SYSON_S_BIT_SYS_USBD_EN                      ((u32)0x00000001 << 16)                             /*!<R/W 0  1: USB Digital power cut enable (USB PHY analog 1.2V power cut enable) */
#define SYSON_S_SHIFT_SYS_OTG_UTMI_CLK_EN            5
#define SYSON_S_BIT_SYS_OTG_UTMI_CLK_EN              ((u32)0x00000001 << 5)                              /*!<R/W 0  1: OTG utmi enable */
#define SYSON_S_SHIFT_SYS_OTG_CLK_EN                 4
#define SYSON_S_BIT_SYS_OTG_CLK_EN                   ((u32)0x00000001 << 4)                              /*!<R/W 0  1: OTG bus clock enable */
#define SYSON_S_SHIFT_SYS__LPM_PLL_ALIVE             3
#define SYSON_S_BIT_SYS__LPM_PLL_ALIVE               ((u32)0x00000001 << 3)                              /*!<R/W 0  1: Keep utmi clock active during suspend state */
#define SYSON_S_SHIFT_SYS_OTG_RST_MUX                1
#define SYSON_S_BIT_SYS_OTG_RST_MUX                  ((u32)0x00000001 << 1)                              /*!<R/W 0  0: Mask WDOG_RST and "cpu_r0_rst" for OTG */
#define SYSON_S_SHIFT_SYS_OTG_EN                     0
#define SYSON_S_BIT_SYS_OTG_EN                       ((u32)0x00000001 << 0)                              /*!<R/W 0  1: enable OTG IP */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_SDIO_SD_CTRL
 * @brief                                            (@ 0X124)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_SD_CK100_VP1_RDY           26
#define SYSON_S_BIT_SYS_SD_CK100_VP1_RDY             ((u32)0x00000001 << 26)                             /*!<R 0  sdh_clk100m_vp1 clock ready */
#define SYSON_S_SHIFT_SYS_SD_CK100_VP0_RDY           25
#define SYSON_S_BIT_SYS_SD_CK100_VP0_RDY             ((u32)0x00000001 << 25)                             /*!<R 0  sdh_clk100m_vp0 clock ready */
#define SYSON_S_SHIFT_SYS_SD_CK100_RDY               24
#define SYSON_S_BIT_SYS_SD_CK100_RDY                 ((u32)0x00000001 << 24)                             /*!<R 0  sdh_clk100m clock ready */
#define SYSON_S_SHIFT_SD_PLL_BYPASS_MODE             23
#define SYSON_S_BIT_SD_PLL_BYPASS_MODE               ((u32)0x00000001 << 23)                             /*!<R/W 0  0: Use Internal clock, 1: Use tester clock */
#define SYSON_S_SHIFT_SYS_SD_CLK2_PSYSEL             20
#define SYSON_S_MASK_SYS_SD_CLK2_PSYSEL              ((u32)0x00000003 << 20)                             /*!<R/W 0  clk100m_vp1 phase shift selection (shift from clk100m) 2'b00 :shift 0 degree 2'b01 :shift 90 degree 2'b10 :shift 180 degree 2'b11 :shift 270 degree */
#define SYSON_S_SHIFT_SYS_SD_CLK1_PSYSEL             16
#define SYSON_S_MASK_SYS_SD_CLK1_PSYSEL              ((u32)0x00000003 << 16)                             /*!<R/W 0  clk100m_vp0 phase shift selection (shift from clk100m) 2'b00 :shift 0 degree 2'b01 :shift 90 degree 2'b10 :shift 180 degree 2'b11 :shift 270 degree */
#define SYSON_S_SHIFT_SYS_SD_ON_RST_MUX              12
#define SYSON_S_BIT_SYS_SD_ON_RST_MUX                ((u32)0x00000001 << 12)                             /*!<R/W 0  0: Mask WDOG_RST and "cpu_r0_rst" for SD ON */
#define SYSON_S_SHIFT_SYS_SD_SYST_SCLK_EN            11
#define SYSON_S_BIT_SYS_SD_SYST_SCLK_EN              ((u32)0x00000001 << 11)                             /*!<R/W 0  1: Enable SD host SCLK */
#define SYSON_S_SHIFT_SYS_SD_SYST_100M_EN            10
#define SYSON_S_BIT_SYS_SD_SYST_100M_EN              ((u32)0x00000001 << 10)                             /*!<R/W 0  SD 100Mhz clock generator function enable */
#define SYSON_S_SHIFT_SYS_SD_SYST_PCLK_EN            9
#define SYSON_S_BIT_SYS_SD_SYST_PCLK_EN              ((u32)0x00000001 << 9)                              /*!<R/W 0  1: enable SD SYST pclock */
#define SYSON_S_SHIFT_SYS_SDH_EN                     8
#define SYSON_S_BIT_SYS_SDH_EN                       ((u32)0x00000001 << 8)                              /*!<R/W 0  1: enable SD host IP block */
#define SYSON_S_SHIFT_SYS_SDIOD_ON_RST_MUX           4
#define SYSON_S_BIT_SYS_SDIOD_ON_RST_MUX             ((u32)0x00000001 << 4)                              /*!<R/W 0  0: Mask WDOG_RST and "cpu_r0_rst" for SDIO */
#define SYSON_S_SHIFT_SDIO_PLL_BYPASS_MODE           2
#define SYSON_S_BIT_SDIO_PLL_BYPASS_MODE             ((u32)0x00000001 << 2)                              /*!<R/W 0  0: Use Internal clock, 1: Use tester clock */
#define SYSON_S_SHIFT_SYS_SDIO_HOST_CLK_EN           1
#define SYSON_S_BIT_SYS_SDIO_HOST_CLK_EN             ((u32)0x00000001 << 1)                              /*!<R/W 0  1: enable SDIO Host clock */
#define SYSON_S_SHIFT_SYS_SDIOD_HOST_EN              0
#define SYSON_S_BIT_SYS_SDIOD_HOST_EN                ((u32)0x00000001 << 0)                              /*!<R/W 0  1: enable SDIO Host IP block */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_RMII_CTRL
 * @brief                                            (@ 0X128)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_RMII_SCLK_GEN              2
#define SYSON_S_BIT_SYS_RMII_SCLK_GEN                ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable RMII 50MHz */
#define SYSON_S_SHIFT_SYS_RMII_CLK_EN                1
#define SYSON_S_BIT_SYS_RMII_CLK_EN                  ((u32)0x00000001 << 1)                              /*!<R/W 0  1: RMII clock enable */
#define SYSON_S_SHIFT_SYS_RMII_EN                    0
#define SYSON_S_BIT_SYS_RMII_EN                      ((u32)0x00000001 << 0)                              /*!<R/W 0  1: enable RMII IP */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_UART_CTRL
 * @brief                                            (@ 0X12C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_BT_UART_MUX_EN             28
#define SYSON_S_BIT_SYS_BT_UART_MUX_EN               ((u32)0x00000001 << 28)                             /*!<R/W 0  1: BT_UART to internal BT, 0: Pinmux to internal BT */
#define SYSON_S_SHIFT_SYS_BT_UART_SCLK_EN            27
#define SYSON_S_BIT_SYS_BT_UART_SCLK_EN              ((u32)0x00000001 << 27)                             /*!<R/W 0  1: Enable BT_UART SCLK */
#define SYSON_S_SHIFT_SYS_BT_UART_PCLK_EN            26
#define SYSON_S_BIT_SYS_BT_UART_PCLK_EN              ((u32)0x00000001 << 26)                             /*!<R/W 0  1: Enable BT_UART PCLK */
#define SYSON_S_SHIFT_SYS_BT_UART_BD_EN              25
#define SYSON_S_BIT_SYS_BT_UART_BD_EN                ((u32)0x00000001 << 25)                             /*!<R/W 0  1: Enable BT_UART bus domain */
#define SYSON_S_SHIFT_SYS_BT_UART_EN                 24
#define SYSON_S_BIT_SYS_BT_UART_EN                   ((u32)0x00000001 << 24)                             /*!<R/W 0  1: Enable BT_UART  */
#define SYSON_S_SHIFT_SYS_UART3_SCLK_EN              19
#define SYSON_S_BIT_SYS_UART3_SCLK_EN                ((u32)0x00000001 << 19)                             /*!<R/W 0  1: Enable UART3 SCLK */
#define SYSON_S_SHIFT_SYS_UART3_PCLK_EN              18
#define SYSON_S_BIT_SYS_UART3_PCLK_EN                ((u32)0x00000001 << 18)                             /*!<R/W 0  1: Enable UART3 PCLK */
#define SYSON_S_SHIFT_SYS_UART3_BD_EN                17
#define SYSON_S_BIT_SYS_UART3_BD_EN                  ((u32)0x00000001 << 17)                             /*!<R/W 0  1: Enable UART3 bus domain */
#define SYSON_S_SHIFT_SYS_UART3_EN                   16
#define SYSON_S_BIT_SYS_UART3_EN                     ((u32)0x00000001 << 16)                             /*!<R/W 0  1: Enable UART3  */
#define SYSON_S_SHIFT_SYS_UART2_SCLK_EN              11
#define SYSON_S_BIT_SYS_UART2_SCLK_EN                ((u32)0x00000001 << 11)                             /*!<R/W 0  1: Enable UART2 SCLK */
#define SYSON_S_SHIFT_SYS_UART2_PCLK_EN              10
#define SYSON_S_BIT_SYS_UART2_PCLK_EN                ((u32)0x00000001 << 10)                             /*!<R/W 0  1: Enable UART2 PCLK */
#define SYSON_S_SHIFT_SYS_UART2_BD_EN                9
#define SYSON_S_BIT_SYS_UART2_BD_EN                  ((u32)0x00000001 << 9)                              /*!<R/W 0  1: Enable UART2 bus domain */
#define SYSON_S_SHIFT_SYS_UART2_EN                   8
#define SYSON_S_BIT_SYS_UART2_EN                     ((u32)0x00000001 << 8)                              /*!<R/W 0  1: Enable UART2  */
#define SYSON_S_SHIFT_SYS_UART1_SCLK_EN              3
#define SYSON_S_BIT_SYS_UART1_SCLK_EN                ((u32)0x00000001 << 3)                              /*!<R/W 0  1: Enable UART1 SCLK */
#define SYSON_S_SHIFT_SYS_UART1_PCLK_EN              2
#define SYSON_S_BIT_SYS_UART1_PCLK_EN                ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable UART1 PCLK */
#define SYSON_S_SHIFT_SYS_UART1_BD_EN                1
#define SYSON_S_BIT_SYS_UART1_BD_EN                  ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable UART1 bus domain */
#define SYSON_S_SHIFT_SYS_UART1_EN                   0
#define SYSON_S_BIT_SYS_UART1_EN                     ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable UART1  */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_I2C_CTRL
 * @brief                                            (@ 0X130)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_I2C3_SCLK_EN               24
#define SYSON_S_BIT_SYS_I2C3_SCLK_EN                 ((u32)0x00000001 << 24)                             /*!<R/W 0  1: Enable I2C3 SCLK */
#define SYSON_S_SHIFT_SYS_I2C3_PCLK_EN               23
#define SYSON_S_BIT_SYS_I2C3_PCLK_EN                 ((u32)0x00000001 << 23)                             /*!<R/W 0  1: Enable I2C3 PCLK */
#define SYSON_S_SHIFT_SYS_I2C3_EN                    22
#define SYSON_S_BIT_SYS_I2C3_EN                      ((u32)0x00000001 << 22)                             /*!<R/W 0  1: Enable I2C3  */
#define SYSON_S_SHIFT_SYS_I2C2_SCLK_EN               21
#define SYSON_S_BIT_SYS_I2C2_SCLK_EN                 ((u32)0x00000001 << 21)                             /*!<R/W 0  1: Enable I2C2 SCLK */
#define SYSON_S_SHIFT_SYS_I2C2_PCLK_EN               20
#define SYSON_S_BIT_SYS_I2C2_PCLK_EN                 ((u32)0x00000001 << 20)                             /*!<R/W 0  1: Enable I2C2 PCLK */
#define SYSON_S_SHIFT_SYS_I2C2_EN                    19
#define SYSON_S_BIT_SYS_I2C2_EN                      ((u32)0x00000001 << 19)                             /*!<R/W 0  1: Enable I2C2  */
#define SYSON_S_SHIFT_SYS_I2C1_SCLK_EN               18
#define SYSON_S_BIT_SYS_I2C1_SCLK_EN                 ((u32)0x00000001 << 18)                             /*!<R/W 0  1: Enable I2C1 SCLK */
#define SYSON_S_SHIFT_SYS_I2C1_PCLK_EN               17
#define SYSON_S_BIT_SYS_I2C1_PCLK_EN                 ((u32)0x00000001 << 17)                             /*!<R/W 0  1: Enable I2C1 PCLK */
#define SYSON_S_SHIFT_SYS_I2C1_EN                    16
#define SYSON_S_BIT_SYS_I2C1_EN                      ((u32)0x00000001 << 16)                             /*!<R/W 0  1: Enable I2C1  */
#define SYSON_S_SHIFT_SYS_I2C0_SCLK_EN               2
#define SYSON_S_BIT_SYS_I2C0_SCLK_EN                 ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable I2C0 SCLK */
#define SYSON_S_SHIFT_SYS_I2C0_PCLK_EN               1
#define SYSON_S_BIT_SYS_I2C0_PCLK_EN                 ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable I2C0 PCLK */
#define SYSON_S_SHIFT_SYS_I2C0_EN                    0
#define SYSON_S_BIT_SYS_I2C0_EN                      ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable I2C0  */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_SPI_CTRL
 * @brief                                            (@ 0X134)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_HS_SPI1_CLK_EN             7
#define SYSON_S_BIT_SYS_HS_SPI1_CLK_EN               ((u32)0x00000001 << 7)                              /*!<R/W 0  1: Enable HS SPI1 CLK */
#define SYSON_S_SHIFT_SYS_HS_SPI1_EN                 6
#define SYSON_S_BIT_SYS_HS_SPI1_EN                   ((u32)0x00000001 << 6)                              /*!<R/W 0  1: Enable HS SPI1  */
#define SYSON_S_SHIFT_SYS_HS_SPI0_CLK_EN             5
#define SYSON_S_BIT_SYS_HS_SPI0_CLK_EN               ((u32)0x00000001 << 5)                              /*!<R/W 0  1: Enable HS SPI0 CLK */
#define SYSON_S_SHIFT_SYS_HS_SPI0_EN                 4
#define SYSON_S_BIT_SYS_HS_SPI0_EN                   ((u32)0x00000001 << 4)                              /*!<R/W 0  1: Enable HS SPI0  */
#define SYSON_S_SHIFT_SYS_SPI1_CLK_EN                3
#define SYSON_S_BIT_SYS_SPI1_CLK_EN                  ((u32)0x00000001 << 3)                              /*!<R/W 0  1: Enable SPI1 CLK */
#define SYSON_S_SHIFT_SYS_SPI1_EN                    2
#define SYSON_S_BIT_SYS_SPI1_EN                      ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable SPI1  */
#define SYSON_S_SHIFT_SYS_SPI0_CLK_EN                1
#define SYSON_S_BIT_SYS_SPI0_CLK_EN                  ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable SPI0 CLK */
#define SYSON_S_SHIFT_SYS_SPI0_EN                    0
#define SYSON_S_BIT_SYS_SPI0_EN                      ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable SPI0  */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_SYS_I2S_CTRL
 * @brief                                            (@ 0X138)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_SYS_SGPIO0_INT_CLK_SEL         7
#define SYSON_S_BIT_SYS_SGPIO0_INT_CLK_SEL           ((u32)0x00000001 << 7)                              /*!<R/W 0  1: sclk 0: apb0 */
#define SYSON_S_SHIFT_SYS_SGPIO0_SCLK_EN             6
#define SYSON_S_BIT_SYS_SGPIO0_SCLK_EN               ((u32)0x00000001 << 6)                              /*!<R/W 0  1: Enable SGPIO0 SCLK */
#define SYSON_S_SHIFT_SYS_SGPIO0_PCLK_EN             5
#define SYSON_S_BIT_SYS_SGPIO0_PCLK_EN               ((u32)0x00000001 << 5)                              /*!<R/W 0  1: Enable SGPIO0 PCLK */
#define SYSON_S_SHIFT_SYS_SGPIO0_EN                  4
#define SYSON_S_BIT_SYS_SGPIO0_EN                    ((u32)0x00000001 << 4)                              /*!<R/W 0  1: Enable SGPIO0 */
#define SYSON_S_SHIFT_SYS_I2S1_CLK_EN                3
#define SYSON_S_BIT_SYS_I2S1_CLK_EN                  ((u32)0x00000001 << 3)                              /*!<R/W 0  1: Enable I2S1 CLK */
#define SYSON_S_SHIFT_SYS_I2S1_EN                    2
#define SYSON_S_BIT_SYS_I2S1_EN                      ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable I2S1 */
#define SYSON_S_SHIFT_SYS_I2S0_CLK_EN                1
#define SYSON_S_BIT_SYS_I2S0_CLK_EN                  ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable I2S0 CLK */
#define SYSON_S_SHIFT_SYS_I2S0_EN                    0
#define SYSON_S_BIT_SYS_I2S0_EN                      ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable I2S0  */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_OTP_AS_CTRL_S
 * @brief                                            (@ 0X13C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_OTP_MODE_SEL                   30
#define SYSON_S_MASK_OTP_MODE_SEL                    ((u32)0x00000003 << 30)                             /*!<R/W 0  OTP controller Mode (command) selection Program to this field could trigger OTP controller to do related command operation. 2'b00 :Read 2'b10 :Write 2'b01 :Autoload Enable 2'b11 :Compare Secure Data Enable */
#define SYSON_S_SHIFT_OTP_RDY                        29
#define SYSON_S_BIT_OTP_RDY                          ((u32)0x00000001 << 29)                             /*!<R/W1C 0  OTP Operation Ready bit 0: OTP controller has NOT done a requested command. 1: OTP controller has done a requested command. Note : HW set , SW clear Note before any operations, HW/SW should clear ready bit first Note: For autoload operation, this bit is not used for autoload done status. Autoload done status of each zone is shown in 0x40009128[6:4] */
#define SYSON_S_SHIFT_OTP_COMP_RESULT                28
#define SYSON_S_BIT_OTP_COMP_RESULT                  ((u32)0x00000001 << 28)                             /*!<R/W1C 0  compare result 0 : PASS 1 : FAIL Note : HW set , SW clear */
#define SYSON_S_SHIFT_OTP_OP_EN                      27
#define SYSON_S_BIT_OTP_OP_EN                        ((u32)0x00000001 << 27)                             /*!<W1Once 0  OTP controller operation enable control This bit could be set to 1 by software and automatically cleared to 0 by hardware 0: OTP controller does NOT perforam any operations even B_OTP_MODE_SEL is given by a valid value. 1: OTP controller performs corresponding operation according to B_OTP_MODE_SEL, B_OTP_ADDR and B_OTP_DATA */
#define SYSON_S_SHIFT_OTP_ADDR                       16
#define SYSON_S_MASK_OTP_ADDR                        ((u32)0x000007FF << 16)                             /*!<R/W 0  Access Address When SOC in secure state, software using this register could only access the following OTP region: Secure Control, Logical, Customer Data, Secure, Hidden. Super Secure region access depends on Super Secure Lock Control in system register bit (SEC_SUPER_SEC_OTP_LOC, 0x5000_2C20[0]) which comes from OTP secure control region. If this bit is set to 0 (default), this register could access Super Secure region. If this bit is set to 1, this register could NOT access Super Secure region. When SOC in non-secure state, software using this register could access all of the OTP region. */
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define SYSON_S_SHIFT_RSVD7                          9
#define SYSON_S_MASK_RSVD7                           ((u32)0x0000007F << 9)                              /*!<R/W 0x00  Reserved */
#else
#define SYSON_S_SHIFT_RSVD6                          9
#define SYSON_S_MASK_RSVD6                           ((u32)0x0000007F << 9)                              /*!<R/W 0x00  Reserved */
#endif
#define SYSON_S_SHIFT_OTP_AUTO_RDCHK_CTRL            8
#define SYSON_S_BIT_OTP_AUTO_RDCHK_CTRL              ((u32)0x00000001 << 8)                              /*!<R/W 0  Automatic Read Check Control When this bit is set to 1 in OTP write mode, OTP controller would perform a write-read-check process automatically. Read back data would be compared with original write data and the result would be updated in bit28 of this register 0: Disable auto read check mechanism 1: Enable auto read check mechanism */
#define SYSON_S_SHIFT_OTP_DATA                       0
#define SYSON_S_MASK_OTP_DATA                        ((u32)0x000000FF << 0)                              /*!<R/W 0  Access Data [7:0] : Read / Write/Data to be compared */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_OTP_SCAN_TEST_S
 * @brief                                            (@ 0X140)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_AX_EF_CRES_SEL                 31
#define SYSON_S_BIT_AX_EF_CRES_SEL                   ((u32)0x00000001 << 31)                             /*!<R/W 0  1: for debug , 0: for normal */
#define SYSON_S_SHIFT_AX_EF_RSVD                     30
#define SYSON_S_BIT_AX_EF_RSVD                       ((u32)0x00000001 << 30)                             /*!<R/W 0  Reserved */
#define SYSON_S_SHIFT_AX_EF_SCAN_SADR                19
#define SYSON_S_MASK_AX_EF_SCAN_SADR                 ((u32)0x000007FF << 19)                             /*!<R/W 0  EFuse Scan start Address (unit in byte) */
#define SYSON_S_SHIFT_AX_EF_SCAN_EADR                8
#define SYSON_S_MASK_AX_EF_SCAN_EADR                 ((u32)0x000007FF << 8)                              /*!<R/W 0  EFuse Scan End address */
#define SYSON_S_SHIFT_AX_EF_SCAN_TRPT                7
#define SYSON_S_BIT_AX_EF_SCAN_TRPT                  ((u32)0x00000001 << 7)                              /*!<R/W1C 0  Test Scan Report: 1 : Fail, 0 : OK */
#define SYSON_S_SHIFT_AX_EF_SCAN_FTHR                0
#define SYSON_S_MASK_AX_EF_SCAN_FTHR                 ((u32)0x0000007F << 0)                              /*!<R/W 0  Threshold number of bit error If [6:0]=1 and scan check have any cell bit wasn't equal 1b'1(default). It will report Fail. If [6:0]=2, it mean allow one cell bit fail while HW scan was finlish and the [6:0] will write to 0 and then check result([7])  */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_DSS_CPU
 * @brief                                            (@ 0X144)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_READY                          26
#define SYSON_S_BIT_READY                            ((u32)0x00000001 << 26)                             /*!<R 0  Ready strobe to read count_out value */
#define SYSON_S_SHIFT_COUNT_OUT                      6
#define SYSON_S_MASK_COUNT_OUT                       ((u32)0x000FFFFF << 6)                              /*!<R 0  Counter value indicates the speed of selected ring oscillator Cycle time = (count_out*dss_clk period)/ 16384 */
#define SYSON_S_SHIFT_RO_SEL                         3
#define SYSON_S_MASK_RO_SEL                          ((u32)0x00000007 << 3)                              /*!<R/W 0  Ring Oscillator selection 000: select dss_clk (for test mode) 001 : select 1st ring oscillator (RVT NAND) 010 : select 2nd ring oscillator (RVT NOR) 011 : select 3rd ring oscillator (H/LVT NAND) 100 : select 4th ring oscillator (H/LVT NOR) 101 : select mixed-library ring oscillator Others : not used */
#define SYSON_S_SHIFT_WRITE_SEL                      2
#define SYSON_S_BIT_WRITE_SEL                        ((u32)0x00000001 << 2)                              /*!<R/W 0  Wire selection 0 : long wire/delay cell/clock buffer 1 : short wire */
#define SYSON_S_SHIFT_DSS_RST_N                      1
#define SYSON_S_BIT_DSS_RST_N                        ((u32)0x00000001 << 1)                              /*!<R/W 0  Reset signal of Speed-Sensor (low active) */
#define SYSON_S_SHIFT_SPEED_EN                       0
#define SYSON_S_BIT_SPEED_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 0  Speed sensor enable 0: disable 1: enable */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_DSS_ENCODER
 * @brief                                            (@ 0X148)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_READY                          26
#define SYSON_S_BIT_READY                            ((u32)0x00000001 << 26)                             /*!<R 0  Ready strobe to read count_out value */
#define SYSON_S_SHIFT_COUNT_OUT                      6
#define SYSON_S_MASK_COUNT_OUT                       ((u32)0x000FFFFF << 6)                              /*!<R 0  Counter value indicates the speed of selected ring oscillator Cycle time = (count_out*dss_clk period)/ 16384 */
#define SYSON_S_SHIFT_RO_SEL                         3
#define SYSON_S_MASK_RO_SEL                          ((u32)0x00000007 << 3)                              /*!<R/W 0  Ring Oscillator selection 000: select dss_clk (for test mode) 001 : select 1st ring oscillator (RVT NAND) 010 : select 2nd ring oscillator (RVT NOR) 011 : select 3rd ring oscillator (H/LVT NAND) 100 : select 4th ring oscillator (H/LVT NOR) 101 : select mixed-library ring oscillator Others : not used */
#define SYSON_S_SHIFT_WRITE_SEL                      2
#define SYSON_S_BIT_WRITE_SEL                        ((u32)0x00000001 << 2)                              /*!<R/W 0  Wire selection 0 : long wire/delay cell/clock buffer 1 : short wire */
#define SYSON_S_SHIFT_DSS_RST_N                      1
#define SYSON_S_BIT_DSS_RST_N                        ((u32)0x00000001 << 1)                              /*!<R/W 0  Reset signal of Speed-Sensor (low active) */
#define SYSON_S_SHIFT_SPEED_EN                       0
#define SYSON_S_BIT_SPEED_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 0  Speed sensor enable 0: disable 1: enable */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_DSS_WLAN_OFF
 * @brief                                            (@ 0X14C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_READY                          26
#define SYSON_S_BIT_READY                            ((u32)0x00000001 << 26)                             /*!<R 0  Ready strobe to read count_out value */
#define SYSON_S_SHIFT_COUNT_OUT                      6
#define SYSON_S_MASK_COUNT_OUT                       ((u32)0x000FFFFF << 6)                              /*!<R 0  Counter value indicates the speed of selected ring oscillator Cycle time = (count_out*dss_clk period)/ 16384 */
#define SYSON_S_SHIFT_RO_SEL                         3
#define SYSON_S_MASK_RO_SEL                          ((u32)0x00000007 << 3)                              /*!<R/W 0  Ring Oscillator selection 000: select dss_clk (for test mode) 001 : select 1st ring oscillator (RVT NAND) 010 : select 2nd ring oscillator (RVT NOR) 011 : select 3rd ring oscillator (H/LVT NAND) 100 : select 4th ring oscillator (H/LVT NOR) 101 : select mixed-library ring oscillator Others : not used */
#define SYSON_S_SHIFT_WRITE_SEL                      2
#define SYSON_S_BIT_WRITE_SEL                        ((u32)0x00000001 << 2)                              /*!<R/W 0  Wire selection 0 : long wire/delay cell/clock buffer 1 : short wire */
#define SYSON_S_SHIFT_DSS_RST_N                      1
#define SYSON_S_BIT_DSS_RST_N                        ((u32)0x00000001 << 1)                              /*!<R/W 0  Reset signal of Speed-Sensor (low active) */
#define SYSON_S_SHIFT_SPEED_EN                       0
#define SYSON_S_BIT_SPEED_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 0  Speed sensor enable 0: disable 1: enable */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_DSS_SOC
 * @brief                                            (@ 0X150)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_READY                          26
#define SYSON_S_BIT_READY                            ((u32)0x00000001 << 26)                             /*!<R 0  Ready strobe to read count_out value */
#define SYSON_S_SHIFT_COUNT_OUT                      6
#define SYSON_S_MASK_COUNT_OUT                       ((u32)0x000FFFFF << 6)                              /*!<R 0  Counter value indicates the speed of selected ring oscillator Cycle time = (count_out*dss_clk period)/ 16384 */
#define SYSON_S_SHIFT_RO_SEL                         3
#define SYSON_S_MASK_RO_SEL                          ((u32)0x00000007 << 3)                              /*!<R/W 0  Ring Oscillator selection 000: select dss_clk (for test mode) 001 : select 1st ring oscillator (RVT NAND) 010 : select 2nd ring oscillator (RVT NOR) 011 : select 3rd ring oscillator (H/LVT NAND) 100 : select 4th ring oscillator (H/LVT NOR) 101 : select mixed-library ring oscillator Others : not used */
#define SYSON_S_SHIFT_WRITE_SEL                      2
#define SYSON_S_BIT_WRITE_SEL                        ((u32)0x00000001 << 2)                              /*!<R/W 0  Wire selection 0 : long wire/delay cell/clock buffer 1 : short wire */
#define SYSON_S_SHIFT_DSS_RST_N                      1
#define SYSON_S_BIT_DSS_RST_N                        ((u32)0x00000001 << 1)                              /*!<R/W 0  Reset signal of Speed-Sensor (low active) */
#define SYSON_S_SHIFT_SPEED_EN                       0
#define SYSON_S_BIT_SPEED_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 0  Speed sensor enable 0: disable 1: enable */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_DSS_REF1
 * @brief                                            (@ 0X154)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_READY                          26
#define SYSON_S_BIT_READY                            ((u32)0x00000001 << 26)                             /*!<R 0  Ready strobe to read count_out value */
#define SYSON_S_SHIFT_COUNT_OUT                      6
#define SYSON_S_MASK_COUNT_OUT                       ((u32)0x000FFFFF << 6)                              /*!<R 0  Counter value indicates the speed of selected ring oscillator Cycle time = (count_out*dss_clk period)/ 16384 */
#define SYSON_S_SHIFT_RO_SEL                         3
#define SYSON_S_MASK_RO_SEL                          ((u32)0x00000007 << 3)                              /*!<R/W 0  Ring Oscillator selection 000: select dss_clk (for test mode) 001 : select 1st ring oscillator (RVT NAND) 010 : select 2nd ring oscillator (RVT NOR) 011 : select 3rd ring oscillator (H/LVT NAND) 100 : select 4th ring oscillator (H/LVT NOR) 101 : select mixed-library ring oscillator Others : not used */
#define SYSON_S_SHIFT_WRITE_SEL                      2
#define SYSON_S_BIT_WRITE_SEL                        ((u32)0x00000001 << 2)                              /*!<R/W 0  Wire selection 0 : long wire/delay cell/clock buffer 1 : short wire */
#define SYSON_S_SHIFT_DSS_RST_N                      1
#define SYSON_S_BIT_DSS_RST_N                        ((u32)0x00000001 << 1)                              /*!<R/W 0  Reset signal of Speed-Sensor (low active) */
#define SYSON_S_SHIFT_SPEED_EN                       0
#define SYSON_S_BIT_SPEED_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 0  Speed sensor enable 0: disable 1: enable */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_DSS_REF2
 * @brief                                            (@ 0X158)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_READY                          26
#define SYSON_S_BIT_READY                            ((u32)0x00000001 << 26)                             /*!<R 0  Ready strobe to read count_out value */
#define SYSON_S_SHIFT_COUNT_OUT                      6
#define SYSON_S_MASK_COUNT_OUT                       ((u32)0x000FFFFF << 6)                              /*!<R 0  Counter value indicates the speed of selected ring oscillator Cycle time = (count_out*dss_clk period)/ 16384 */
#define SYSON_S_SHIFT_RO_SEL                         3
#define SYSON_S_MASK_RO_SEL                          ((u32)0x00000007 << 3)                              /*!<R/W 0  Ring Oscillator selection 000: select dss_clk (for test mode) 001 : select 1st ring oscillator (RVT NAND) 010 : select 2nd ring oscillator (RVT NOR) 011 : select 3rd ring oscillator (H/LVT NAND) 100 : select 4th ring oscillator (H/LVT NOR) 101 : select mixed-library ring oscillator Others : not used */
#define SYSON_S_SHIFT_WRITE_SEL                      2
#define SYSON_S_BIT_WRITE_SEL                        ((u32)0x00000001 << 2)                              /*!<R/W 0  Wire selection 0 : long wire/delay cell/clock buffer 1 : short wire */
#define SYSON_S_SHIFT_DSS_RST_N                      1
#define SYSON_S_BIT_DSS_RST_N                        ((u32)0x00000001 << 1)                              /*!<R/W 0  Reset signal of Speed-Sensor (low active) */
#define SYSON_S_SHIFT_SPEED_EN                       0
#define SYSON_S_BIT_SPEED_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 0  Speed sensor enable 0: disable 1: enable */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_S_REG_VOL_PROBE
 * @brief                                            (@ 0X15C)
 * @{
 *****************************************************************************/
#define SYSON_S_SHIFT_OE_OTP                         1
#define SYSON_S_BIT_OE_OTP                           ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SYSON_S_SHIFT_OE_AON                         0
#define SYSON_S_BIT_OE_AON                           ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_SYSON_S
 * @{
 * @brief rtl8735b_SYSON_S Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t SYSON_S_REG_SYS_PWR_CTRL ;               /*!<   register,  Address offset: 0x000 */
	__IO uint32_t SYSON_S_REG_SYS_ISO_CTRL ;               /*!<   register,  Address offset: 0x004 */
	__IO uint32_t SYSON_S_REG_SYS_CLK_CTRL ;               /*!<   register,  Address offset: 0x008 */
	__IO uint32_t SYSON_S_REG_SYS_FUNC_EN ;                /*!<   register,  Address offset: 0x00C */
	__IO uint32_t SYSON_S_REG_HS_PLATFORM_PARA ;           /*!<   register,  Address offset: 0x010 */
	__IO uint32_t SYSON_S_REG_I2S_PLL1_CTRL0 ;             /*!<   register,  Address offset: 0x014 */
	__IO uint32_t SYSON_S_REG_I2S_PLL1_CTRL1 ;             /*!<   register,  Address offset: 0x018 */
	__IO uint32_t SYSON_S_REG_I2S_PLL1_CTRL2 ;             /*!<   register,  Address offset: 0x01C */
	__IO uint32_t SYSON_S_REG_I2S_PLL1_CTRL3 ;             /*!<   register,  Address offset: 0x020 */
	__IO uint32_t SYSON_S_REG_I2S_PLL2_CTRL0 ;             /*!<   register,  Address offset: 0x024 */
	__IO uint32_t SYSON_S_REG_I2S_PLL2_CTRL1 ;             /*!<   register,  Address offset: 0x028 */
	__IO uint32_t SYSON_S_REG_I2S_PLL2_CTRL2 ;             /*!<   register,  Address offset: 0x02C */
	__IO uint32_t SYSON_S_REG_I2S_PLL2_CTRL3 ;             /*!<   register,  Address offset: 0x030 */
	__IO uint32_t SYSON_S_REG_ISP_PLL_CTRL0 ;              /*!<   register,  Address offset: 0x034 */
	__IO uint32_t SYSON_S_REG_ISP_PLL_CTRL1 ;              /*!<   register,  Address offset: 0x038 */
	__IO uint32_t SYSON_S_REG_ISP_PLL_CTRL2 ;              /*!<   register,  Address offset: 0x03C */
	__IO uint32_t SYSON_S_REG_ISP_PLL_CTRL3 ;              /*!<   register,  Address offset: 0x040 */
	__IO uint32_t SYSON_S_REG_LDO_SDIO_CTRL ;              /*!<   register,  Address offset: 0x044 */
	__IO uint32_t SYSON_S_REG_SYS_MEM_CTRL ;               /*!<   register,  Address offset: 0x048 */
	__IO uint32_t SYSON_S_REG_RSVD1 ;                      /*!<   register,  Address offset: 0x04C */
	__IO uint32_t SYSON_S_REG_RSVD2 ;                      /*!<   register,  Address offset: 0x050 */
	__IO uint32_t SYSON_S_REG_SYS_SCE_EXMEM_CTRL0 ;        /*!<   register,  Address offset: 0x054 */
	__IO uint32_t SYSON_S_REG_SYS_SCE_EXMEM_CTRL1 ;        /*!<   register,  Address offset: 0x058 */
	__IO uint32_t SYSON_S_REG_SYS_SCE_FLASH_CTRL0 ;        /*!<   register,  Address offset: 0x05C */
	__IO uint32_t SYSON_S_REG_SYS_SCE_FLASH_CTRL1 ;        /*!<   register,  Address offset: 0x060 */
	__IO uint32_t SYSON_S_REG_SYS_SEC_EFUSE_CTRL0 ;        /*!<   register,  Address offset: 0x064 */
	__IO uint32_t SYSON_S_REG_SEC_MASTER_SLAVE_PORT_IP_DIS ;/*!<   register,  Address offset: 0x068 */
	__IO uint32_t SYSON_S_REG_SEC_SLAVE_PORT_IP_DIS ;      /*!<   register,  Address offset: 0x06C */
	__IO uint32_t SYSON_S_REG_RSVD3 ;                      /*!<   register,  Address offset: 0x070 */
	__IO uint32_t SYSON_S_REG_SYS_SEC_CTRL ;               /*!<   register,  Address offset: 0x074 */
	__IO uint32_t SYSON_S_REG_SYS_RSA_FUNC_CTRL ;          /*!<   register,  Address offset: 0x078 */
	__IO uint32_t SYSON_S_REG_RSVD4 ;                      /*!<   register,  Address offset: 0x07C */
	__IO uint32_t SYSON_S_REG_SYS_LPDDR1_CTRL ;            /*!<   register,  Address offset: 0x080 */
	__IO uint32_t SYSON_S_REG_SYS_DDRPHY_CTRL ;            /*!<   register,  Address offset: 0x084 */
	__IO uint32_t SYSON_S_REG_SYS_SHARE_MEM_CTRL ;         /*!<   register,  Address offset: 0x088 */
	__IO uint32_t SYSON_S_REG_SYS_FLASH_CTRL ;             /*!<   register,  Address offset: 0x08C */
	__IO uint32_t SYSON_S_REG_SYS_FLASH_PHY_CTRL0 ;        /*!<   register,  Address offset: 0x090 */
	__IO uint32_t SYSON_S_REG_SYS_FLASH_PHY_CTRL1 ;        /*!<   register,  Address offset: 0x094 */
	__O  uint32_t SYSON_S_RSVD ;                           /*!<   register,  Address offset: 0x098 */
	__IO uint32_t SYSON_S_REG_SYS_PLATFORM_CTRL0 ;         /*!<   register,  Address offset: 0x09C */
	__IO uint32_t RSVD0[24];                               /*!<  Reserved,  Address offset:0xA0-0xFC */
	__IO uint32_t SYSON_S_REG_SYS_FEPHY_CTRL ;             /*!<   register,  Address offset: 0x100 */
	__IO uint32_t SYSON_S_REG_SYS_TIMER_CTRL ;             /*!<   register,  Address offset: 0x104 */
	__IO uint32_t SYSON_S_REG_SYS_ADC_CTRL0 ;              /*!<   register,  Address offset: 0x108 */
	__IO uint32_t SYSON_S_REG_SYS_ADC_CTRL1 ;              /*!<   register,  Address offset: 0x10C */
	__IO uint32_t SYSON_S_REG_GPIO_CTRL ;                  /*!<   register,  Address offset: 0x110 */
	__IO uint32_t SYSON_S_REG_SYS_AUDIO_CTRL ;             /*!<   register,  Address offset: 0x114 */
	__IO uint32_t SYSON_S_REG_SYS_ISP_CTRL ;               /*!<   register,  Address offset: 0x118 */
	__IO uint32_t SYSON_S_REG_SYS_NN_CTRL ;                /*!<   register,  Address offset: 0x11C */
	__IO uint32_t SYSON_S_REG_SYS_OTG_CTRL ;               /*!<   register,  Address offset: 0x120 */
	__IO uint32_t SYSON_S_REG_SYS_SDIO_SD_CTRL ;           /*!<   register,  Address offset: 0x124 */
	__IO uint32_t SYSON_S_REG_SYS_RMII_CTRL ;              /*!<   register,  Address offset: 0x128 */
	__IO uint32_t SYSON_S_REG_SYS_UART_CTRL ;              /*!<   register,  Address offset: 0x12C */
	__IO uint32_t SYSON_S_REG_SYS_I2C_CTRL ;               /*!<   register,  Address offset: 0x130 */
	__IO uint32_t SYSON_S_REG_SYS_SPI_CTRL ;               /*!<   register,  Address offset: 0x134 */
	__IO uint32_t SYSON_S_REG_SYS_I2S_CTRL ;               /*!<   register,  Address offset: 0x138 */
	__IO uint32_t SYSON_S_REG_OTP_AS_CTRL_S ;              /*!<   register,  Address offset: 0x13C */
	__IO uint32_t SYSON_S_REG_OTP_SCAN_TEST_S ;            /*!<   register,  Address offset: 0x140 */
	__IO uint32_t SYSON_S_REG_DSS_CPU ;                    /*!<   register,  Address offset: 0x144 */
	__IO uint32_t SYSON_S_REG_DSS_ENCODER ;                /*!<   register,  Address offset: 0x148 */
	__IO uint32_t SYSON_S_REG_DSS_WLAN_OFF ;               /*!<   register,  Address offset: 0x14C */
	__IO uint32_t SYSON_S_REG_DSS_SOC ;                    /*!<   register,  Address offset: 0x150 */
	__IO uint32_t SYSON_S_REG_DSS_REF1 ;                   /*!<   register,  Address offset: 0x154 */
	__IO uint32_t SYSON_S_REG_DSS_REF2 ;                   /*!<   register,  Address offset: 0x158 */
	__IO uint32_t SYSON_S_REG_VOL_PROBE ;                  /*!<   register,          Address offset: 0x15C */
} SYSON_S_TypeDef;
/** @} */

#endif
