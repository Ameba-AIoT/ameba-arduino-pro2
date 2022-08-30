#ifndef _RTL8735B_AON_TYPE_H_
#define _RTL8735B_AON_TYPE_H_
#include "platform_conf.h"

/**************************************************************************//**
 * @defgroup AON_REG_AON_PWR_CTRL
 * @brief                                            (@ 0X000)
 * @{
 *****************************************************************************/
#define AON_SHIFT_WLON_LPC_EN                        3
#define AON_BIT_WLON_LPC_EN                          ((u32)0x00000001 << 3)                              /*!<R/W 0  WLAN on domain large power 0:Disable, 1: Enable */
#define AON_SHIFT_WLON_SPC_EN                        2
#define AON_BIT_WLON_SPC_EN                          ((u32)0x00000001 << 2)                              /*!<R/W 0  WLAN on domain small power 0:Disable, 1: Enable */
#define AON_SHIFT_PON_LPC_EN                         1
#define AON_BIT_PON_LPC_EN                           ((u32)0x00000001 << 1)                              /*!<R/W 0  Peripheral on domain large power 0:Disable, 1: Enable */
#define AON_SHIFT_PON_SPC_EN                         0
#define AON_BIT_PON_SPC_EN                           ((u32)0x00000001 << 0)                              /*!<R/W 0  Peripheral on domain small power 0:Disable, 1: Enable */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_ISO_CTRL
 * @brief                                            (@ 0X004)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SYS_ISO_WLON                       17
#define AON_BIT_SYS_ISO_WLON                         ((u32)0x00000001 << 17)                             /*!<R/W 1  1: isolatino WLON to AON; 0: disable isolation */
#define AON_SHIFT_SYS_ISO_PON                        16
#define AON_BIT_SYS_ISO_PON                          ((u32)0x00000001 << 16)                             /*!<R/W 1  1: isolatino PON to AON; 0: disable isolation */
#define AON_SHIFT_ISO_SYSON_EN                       15
#define AON_BIT_ISO_SYSON_EN                         ((u32)0x00000001 << 15)                             /*!<R/W 1  1: isolation SYSON to AON domain; 0: disable isolation */
#define AON_SHIFT_SYS_ISO_XTAL                       4
#define AON_BIT_SYS_ISO_XTAL                         ((u32)0x00000001 << 4)                              /*!<R/W 1  1: isolatino XTAL to AON; 0: disable isolation */
#define AON_SHIFT_FEPHY_ISO                          2
#define AON_BIT_FEPHY_ISO                            ((u32)0x00000001 << 2)                              /*!<R/W 1  1: Isolation FEPHY digital to analog. */
#define AON_SHIFT_FEPHY_POW_STATE                    1
#define AON_BIT_FEPHY_POW_STATE                      ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable Power state */
#define AON_SHIFT_FEPHY_RSTB_L                       0
#define AON_BIT_FEPHY_RSTB_L                         ((u32)0x00000001 << 0)                              /*!<R/W 0  0: Reset */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_FUNC_CTRL
 * @brief                                            (@ 0X008)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SYS_AMACRO_EN                      31
#define AON_BIT_SYS_AMACRO_EN                        ((u32)0x00000001 << 31)                             /*!<R/W 1  Analog IP PWD_B, REGU hw_pdb_12 */
#define AON_SHIFT_SYS_FEN_SIC_MST                    25
#define AON_BIT_SYS_FEN_SIC_MST                      ((u32)0x00000001 << 25)                             /*!<R/W 0  1: enable SIC to access register by CPU  */
#define AON_SHIFT_SYS_FEN_SIC                        24
#define AON_BIT_SYS_FEN_SIC                          ((u32)0x00000001 << 24)                             /*!<R/W 0  1: enable SIC function enable; 0: reset */
#define AON_SHIFT_SDM_FEN                            7
#define AON_BIT_SDM_FEN                              ((u32)0x00000001 << 7)                              /*!<R/W 0  1:Enable OSC 32K SDM */
#define AON_SHIFT_GPIO_FEN                           6
#define AON_BIT_GPIO_FEN                             ((u32)0x00000001 << 6)                              /*!<R/W 0  1: Enable AON GPIO */
#define AON_SHIFT_COMP_FEN                           5
#define AON_BIT_COMP_FEN                             ((u32)0x00000001 << 5)                              /*!<R/W 0  1: Enable AON Comparator */
#define AON_SHIFT_RTC_INTF_FEN                       3
#define AON_BIT_RTC_INTF_FEN                         ((u32)0x00000001 << 3)                              /*!<R/W 0  RTC Enable (need delay 4ms?) 0: disable RTC , 1: enable RTC  */
#define AON_SHIFT_SYS_PON_FEN                        1
#define AON_BIT_SYS_PON_FEN                          ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable PON */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_CLK_CTRL
 * @brief                                            (@ 0X00C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_REG_CLK_SEL                        31
#define AON_BIT_REG_CLK_SEL                          ((u32)0x00000001 << 31)                             /*!<R/W 0  AON register clock source selection, 0: 100K, 1: 4M */
#define AON_SHIFT_INT_CLK_SEL                        30
#define AON_BIT_INT_CLK_SEL                          ((u32)0x00000001 << 30)                             /*!<R/W 0  Comparator interrupt clock source selection, 0:pclk, 1:sclk */
#define AON_SHIFT_GPIO_INTR_CLK                      7
#define AON_BIT_GPIO_INTR_CLK                        ((u32)0x00000001 << 7)                              /*!<R/W 0  0:pclk, 1:sclk */
#define AON_SHIFT_GPIO_SCLK_EN                       6
#define AON_BIT_GPIO_SCLK_EN                         ((u32)0x00000001 << 6)                              /*!<R/W 0  1:AON GPIO Sclk Enable */
#define AON_SHIFT_GPIO_PCLK_EN                       5
#define AON_BIT_GPIO_PCLK_EN                         ((u32)0x00000001 << 5)                              /*!<R/W 0  1:AON GPIO Pclk Enable */
#define AON_SHIFT_OSC_SDM_CK_EN                      4
#define AON_BIT_OSC_SDM_CK_EN                        ((u32)0x00000001 << 4)                              /*!<R/W 0  1: SDM Pclk enable */
#define AON_SHIFT_RTC_CK_FEN                         3
#define AON_BIT_RTC_CK_FEN                           ((u32)0x00000001 << 3)                              /*!<R/W 1  1: enable RTC clock */
#define AON_SHIFT_SYS_CK_PON_EN                      1
#define AON_BIT_SYS_CK_PON_EN                        ((u32)0x00000001 << 1)                              /*!<R/W 0  1: enable PON register clock */
#define AON_SHIFT_RET_MEM_AUTO_GATE                  0
#define AON_BIT_RET_MEM_AUTO_GATE                    ((u32)0x00000001 << 0)                              /*!<R/W 0  1: disable memory clock gating in mbist wrap */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_LDO_CTRL0
 * @brief                                            (@ 0X010)
 * @{
 *****************************************************************************/
#define AON_SHIFT_LDO_CTRL                           24
#define AON_BIT_LDO_CTRL                             ((u32)0x00000001 << 24)                             /*!<R/W 0  0:The AON_LDO control was come from AON+0x10[7:4] 1:The AON_LDO control was come from AON+0x10[23:20] */
#define AON_SHIFT_LDOH09_V09ADJ_PMC                  20
#define AON_MASK_LDOH09_V09ADJ_PMC                   ((u32)0x0000000F << 20)                             /*!<R/W 0100  AONLDO09 voltage select VREF 0P600V 0P575V 0000: 0.593V 0.568V 0001: 0.708V 0.678V 0010: 0.739V 0.708V 0011: 0.774V 0.742V 0100: 0.812V 0.778V 0101: 0.833V 0.798V 0110: 0.854V 0.819V 0111: 0.877V 0.840V 1000: 0.901V 0.863V 1001: 0.926V 0.888V 1010: 0.953V 0.913V 1011: 0.981V 0.940V 1100: 1.012V 0.969V 1101: 1.044V 1.000V 1110: 1.077V 1.033V 1111: 1.111V 1.067V */
#define AON_SHIFT_BOD_EN                             19
#define AON_BIT_BOD_EN                               ((u32)0x00000001 << 19)                             /*!<R/W 1  Brown-Out-Detect 1 : enable (default) 0 : disable */
#define AON_SHIFT_BOD_VTHSEL                         16
#define AON_MASK_BOD_VTHSEL                          ((u32)0x00000007 << 16)                             /*!<R/W 001  Brown-Out-Detect VTH selection BOD H L 000 0.475 0.450 001 2.426 2.298 010 2.533 2.400 011 2.591 2.455 100 2.651 2.512 101 2.714 2.571 110 2.780 2.634 111 2.850 2.700 INT H L 000 0.520 0.500 001 2.655 2.553 010 2.773 2.667 011 2.836 2.727 100 2.902 2.791 101 2.971 2.857 110 3.044 2.927 111 3.120 3.000 */
#define AON_SHIFT_LDO_CTRL0_DUMMY_0                  12
#define AON_MASK_LDO_CTRL0_DUMMY_0                   ((u32)0x0000000F << 12)                             /*!<R/W 0000  Dummy */
#define AON_SHIFT_CK12M_EN                           11
#define AON_BIT_CK12M_EN                             ((u32)0x00000001 << 11)                             /*!<R/W 1  1: enable 12M ring */
#define AON_SHIFT_CK_SEL                             10
#define AON_BIT_CK_SEL                               ((u32)0x00000001 << 10)                             /*!<R/W 0  1: 12MHz 0:100kHz Choose between 12M and 100K, when selecting 100k, keep 12M enabled. */
#define AON_SHIFT_LDO_CTRL0_DUMMY_1                  9
#define AON_BIT_LDO_CTRL0_DUMMY_1                    ((u32)0x00000001 << 9)                              /*!<R/W 0  Dummy */
#define AON_SHIFT_EN_SLEEP_L                         8
#define AON_BIT_EN_SLEEP_L                           ((u32)0x00000001 << 8)                              /*!<R/W 0  Enable LDO09H sleep mode 0 : disable (default) 1 : enable */
#define AON_SHIFT_LDOH09_V09ADJ_L_3_0                4
#define AON_MASK_LDOH09_V09ADJ_L_3_0                 ((u32)0x0000000F << 4)                              /*!<R/W 1000  AONLDO09 voltage select VREF 0P600V 0P575V 0000: 0.593V 0.568V 0001: 0.708V 0.678V 0010: 0.739V 0.708V 0011: 0.774V 0.742V 0100: 0.812V 0.778V 0101: 0.833V 0.798V 0110: 0.854V 0.819V 0111: 0.877V 0.840V 1000: 0.901V 0.863V 1001: 0.926V 0.888V 1010: 0.953V 0.913V 1011: 0.981V 0.940V 1100: 1.012V 0.969V 1101: 1.044V 1.000V 1110: 1.077V 1.033V 1111: 1.111V 1.067V */
#define AON_SHIFT_DUMMY_REG_ANAPAR_LDO_B3_B2         2
#define AON_MASK_DUMMY_REG_ANAPAR_LDO_B3_B2          ((u32)0x00000003 << 2)                              /*!<R/W 00  // [REGU][AONLDO] dummy */
#define AON_SHIFT_LV_POR_VREF_SEL                    1
#define AON_BIT_LV_POR_VREF_SEL                      ((u32)0x00000001 << 1)                              /*!<R/W 0  LV_POR VREF 0 (default) VREF = 0P600V 1 VREF = 0P450V */
#define AON_SHIFT_AONLDO_VREF_SEL                    0
#define AON_BIT_AONLDO_VREF_SEL                      ((u32)0x00000001 << 0)                              /*!<R/W 0  AONLDO VREF_SEL 0 (default) VREF = 0P600V 1 VREF = 0P575V */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_WLON_LDO_CTRL0
 * @brief                                            (@ 0X014)
 * @{
 *****************************************************************************/
#define AON_SHIFT_RESERVED1                          16
#define AON_MASK_RESERVED1                           ((u32)0x0000000F << 16)                             /*!<R/W 0000  // dummy */
#define AON_SHIFT_REG_DMY_LDO_L                      14
#define AON_MASK_REG_DMY_LDO_L                       ((u32)0x00000003 << 14)                             /*!<R/W 00  // [REGU][LDO] REG_CTRL // LDO extra Power Cut Control <1> : large pwrcut mos, <0> : small pwrcut mos 0 (default): disable pwrcut mos 1 : enable pwrcut mos enable sequence should be first enable small then delay >50us to enable large */
#define AON_SHIFT_REG_FORCE_DIODE_L                  13
#define AON_BIT_REG_FORCE_DIODE_L                    ((u32)0x00000001 << 13)                             /*!<R/W 0  // [REGU][LDO_WLON] REG_CTRL // PGATE diode clamp (this is directly force no gating) // (purpose for powerCut mode iOCP) // 0: disable force diode clamp (default) // 1: enable force diode clamp */
#define AON_SHIFT_REG_BUFFERTYPE_SEL_L               12
#define AON_BIT_REG_BUFFERTYPE_SEL_L                 ((u32)0x00000001 << 12)                             /*!<R/W 1  // [REGU][LDO] REG_CTRL // LDO Buffer Type Select // 0: PMOS buffer (for HV 3P3V) // 1(default): NMOS buffer (for SWR 1P35V) */
#define AON_SHIFT_REG_DMYLOAD_L                      10
#define AON_MASK_REG_DMYLOAD_L                       ((u32)0x00000003 << 10)                             /*!<R/W 00  // [REGU][LDO_WLON] REG_CTRL // LDO dmy load ctrl // 00(default): dmy load disable // 01: light dmy load enable (~160kohm) // 10: dmy load enable (~1kohm) // 11: dmy load + light dmy load both enable */
#define AON_SHIFT_REG_ITAIL_HALF_EN_L                9
#define AON_BIT_REG_ITAIL_HALF_EN_L                  ((u32)0x00000001 << 9)                              /*!<R/W 0  // [REGU][LDO_WLON] REG_CTRL // LDO iq half ctrl // 0(default): iq normal (for normal mode) // 1: iq half (for standby mode) */
#define AON_SHIFT_REG_STANDBY_L                      7
#define AON_MASK_REG_STANDBY_L                       ((u32)0x00000003 << 7)                              /*!<R/W 00  // [REGU][LDO_WLON] REG_CTRL // LDO standby mode ctrl: // 00 (default): normal mode (iq normal + pwrmos 8x) // 01: debug mode (iq reduce + pwrmos 1x) // 10: debug mode (iq normal + pwrmos 8x) // 11: standby mode (iq reduce + pwrmos 1x) */
#define AON_SHIFT_EN_DIODE_L                         6
#define AON_BIT_EN_DIODE_L                           ((u32)0x00000001 << 6)                              /*!<R/W 1  // [REGU][LDO_WLON] REG_CTRL // PGATE diode clamp (this gating to disable by pd_regu_L) // 0: disable clamp // 1: enable clamp (default) */
#define AON_SHIFT_VOADJ_L                            2
#define AON_MASK_VOADJ_L                             ((u32)0x0000000F << 2)                              /*!<R/W 1000  // [REGU][LDO_WLON] REG_CTRL // LDO VOSEL // 0000 0.722 // 0001 0.740 // 0010 0.760 // 0011 0.780 // 0100 0.802 // 0101 0.825 // 0110 0.850 // 0111 0.875 // 1000 0.903 // 1001 0.932 // 1010 0.963 // 1011 0.997 // 1100 1.032 // 1101 1.071 // 1110 1.112 // 1111 1.157 */
#define AON_SHIFT_PD_REGU_L                          1
#define AON_BIT_PD_REGU_L                            ((u32)0x00000001 << 1)                              /*!<R/W 1  // [REGU][LDO_WLON] REG_CTRL // PowerDown CTRL // 0: normal-Mode // 1: power-down Mode (default) */
#define AON_SHIFT_EN_PC_BT_L                         0
#define AON_BIT_EN_PC_BT_L                           ((u32)0x00000001 << 0)                              /*!<R/W 0  // [REGU][LDO_WLON] REG_CTRL // PWRCUT enable // 0: LDO-Mode (default) // 1: PWRCUT-Mode */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_SWR_SRC_CTRL0
 * @brief                                            (@ 0X018)
 * @{
 *****************************************************************************/
#define AON_SHIFT_FORCE_ZCD_BIAS                     31
#define AON_BIT_FORCE_ZCD_BIAS                       ((u32)0x00000001 << 31)                             /*!<R/W 1  //0:ZCD bias on after SS //1:ZCD bias on when ZCD enable */
#define AON_SHIFT_ZCD_SDZ_L_1                        30
#define AON_BIT_ZCD_SDZ_L_1                          ((u32)0x00000001 << 30)                             /*!<R/W 0  //Increase ZCD delay cell */
#define AON_SHIFT_ZCD_SDZ_L_0                        29
#define AON_BIT_ZCD_SDZ_L_0                          ((u32)0x00000001 << 29)                             /*!<R/W 1  //Increase ZCD delay cell */
#define AON_SHIFT_ZCDC_H                             27
#define AON_MASK_ZCDC_H                              ((u32)0x00000003 << 27)                             /*!<R 10  //00:0.1u //01:0.2u(PFM) //10:0.7u (PWM Loading > 50mA) //11:0.8u (PWM Loading <= 50mA) */
#define AON_SHIFT_POW_ZCD_L                          26
#define AON_BIT_POW_ZCD_L                            ((u32)0x00000001 << 26)                             /*!<R/W 1  //Enable ZCD */
#define AON_SHIFT_OCP_L1                             23
#define AON_MASK_OCP_L1                              ((u32)0x00000007 << 23)                             /*!<R 011  //PWM current (A) / PFM Current (A) //000 0.398 0.178 //001 0.486 0.222 //010 0.573 0.266 //011 0.660 0.310 //100 0.747 0.354 //101 0.834 0.398 //110 0.920 0.442 //111 1.008 VIN/10 */
#define AON_SHIFT_POWOCP_L1                          22
#define AON_BIT_POWOCP_L1                            ((u32)0x00000001 << 22)                             /*!<R/W 1  //POWOCP_L1=1 : enable over current protection */
#define AON_SHIFT_SAW_FREQ_L                         18
#define AON_MASK_SAW_FREQ_L                          ((u32)0x0000000F << 18)                             /*!<R/W 1000  0000 458.0k 0001 680.2k 0010 898.9k 0011 1.113M 0100 1.321M 0101 1.522M 0110 1.716M 0111 1.902M 1000 2.087M 1001 2.258M 1010 2.426M 1011 2.582M 1100 2.743M 1101 2.888M 1110 3.035M 1111 3.165M */
#define AON_SHIFT_BYPASS_L                           17
#define AON_BIT_BYPASS_L                             ((u32)0x00000001 << 17)                             /*!<R/W 1  1:bypass SSR latch */
#define AON_SHIFT_FPWM_L1                            16
#define AON_BIT_FPWM_L1                              ((u32)0x00000001 << 16)                             /*!<R/W 1  FPWM_L1 = 1 : force PWM FPWM_L1 = 0 : force PFM */
#define AON_SHIFT_STD_L1                             14
#define AON_MASK_STD_L1                              ((u32)0x00000003 << 14)                             /*!<R/W 01  STD_L1[1:0] time 00 750u 01 1.5m 10 3m 11 12.288m */
#define AON_SHIFT_VOL_L1                             10
#define AON_MASK_VOL_L1                              ((u32)0x0000000F << 10)                             /*!<R/W 1000  // bits SWR / LDO //VREF 0P600V 0P575V 0P500V 0P450V //0000 1.426 1.367 1.189 1.070 //0001 1.455 1.394 1.213 1.091 //0010 1.501 1.438 1.251 1.125 //0011 1.549 1.484 1.291 1.162 //0100 1.583 1.517 1.319 1.187 //0101 1.637 1.569 1.364 1.228 //0110 1.695 1.624 1.412 1.271 //0111 1.736 1.664 1.446 1.302 //1000 1.801 1.726 1.501 1.351 (default) //1001 1.871 1.793 1.559 1.403 //1010 1.921 1.841 1.601 1.441 //1011 2.001 1.918 1.667 1.501 //1100 2.088 2.001 1.740 1.566 //1101 2.150 2.060 1.792 1.613 //1110 2.251 2.157 1.876 1.688 //1111 2.362 2.264 1.968 1.771 */
#define AON_SHIFT_SRC_ENB_LDO_1P8_DIODE              3
#define AON_BIT_SRC_ENB_LDO_1P8_DIODE                ((u32)0x00000001 << 3)                              /*!<R/W 0  [no function] LDOMODE need followed sequence of LDOS->LDO */
#define AON_SHIFT_SRC_POW_LDOS_1P8                   2
#define AON_BIT_SRC_POW_LDOS_1P8                     ((u32)0x00000001 << 2)                              /*!<R/W 0  small LDO enable // default 1'b0 disable */
#define AON_SHIFT_SRC_POW_LDO_1P8                    1
#define AON_BIT_SRC_POW_LDO_1P8                      ((u32)0x00000001 << 1)                              /*!<R/W 0  large LDO enable // default 1'b0 disable */
#define AON_SHIFT_SRC_POW_SW                         0
#define AON_BIT_SRC_POW_SW                           ((u32)0x00000001 << 0)                              /*!<R/W 0  SWR enable // default 1'b0 disable */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_SWR_SRC_CTRL1
 * @brief                                            (@ 0X01C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SRC_SSOVER_L                       30
#define AON_BIT_SRC_SSOVER_L                         ((u32)0x00000001 << 30)                             /*!<R 0  SWR_SRC vout soft-start-over ready signal 1:ready 0:(default) not ready */
#define AON_SHIFT_SP_P_L                             26
#define AON_MASK_SP_P_L                              ((u32)0x0000000F << 26)                             /*!<R/W 0011  PGATE PMOS driving */
#define AON_SHIFT_VO_DISCHG_PWM_H                    25
#define AON_BIT_VO_DISCHG_PWM_H                      ((u32)0x00000001 << 25)                             /*!<R/W 0  1 : dummy load RES 178ohm (~10mA for 1P8V) */
#define AON_SHIFT_MODE_PREDRIVER                     24
#define AON_BIT_MODE_PREDRIVER                       ((u32)0x00000001 << 24)                             /*!<R/W 1  1 : enable 3 level predriver */
#define AON_SHIFT_ADJSLDO_L                          20
#define AON_MASK_ADJSLDO_L                           ((u32)0x0000000F << 20)                             /*!<R/W 0110  bits / voltage (for VREF0p6V) (as for others VREF is in ratio) 4'b0000 1.413 4'b0001 1.451 4'b0010 1.491 4'b0011 1.534 4'b0100 1.579 4'b0101 1.627 4'b0110 1.678 4'b0111 1.732 4'b1000 1.790 4'b1001 1.852 4'b1010 1.918 4'b1011 1.989 4'b1100 2.065 4'b1101 2.148 4'b1110 2.238 4'b1111 2.335 */
#define AON_SHIFT_EN_LDOS_DIODE                      19
#define AON_BIT_EN_LDOS_DIODE                        ((u32)0x00000001 << 19)                             /*!<R/W 1  1 : LDOS diode enable */
#define AON_SHIFT_PWM_FORCE                          18
#define AON_BIT_PWM_FORCE                            ((u32)0x00000001 << 18)                             /*!<R/W 0  0 : bias enabled only at PWM mode 1 : force bias enable before mode tran from PFM to PWM */
#define AON_SHIFT_PFM_PD_RST                         17
#define AON_BIT_PFM_PD_RST                           ((u32)0x00000001 << 17)                             /*!<R/W 1  //1: When leave PFM mode, COT logic is reset */
#define AON_SHIFT_VC_PFM_RSTB                        16
#define AON_BIT_VC_PFM_RSTB                          ((u32)0x00000001 << 16)                             /*!<R/W 0  //When into PFM, VC is, //0: clamped (bit 40 also =1) 1. floating */
#define AON_SHIFT_PFM_IN_SEL                         15
#define AON_BIT_PFM_IN_SEL                           ((u32)0x00000001 << 15)                             /*!<R/W 1  //Power MOS into PFM when PFM CTRL, //0: rising 1: falling */
#define AON_SHIFT_VC_RSTB                            14
#define AON_BIT_VC_RSTB                              ((u32)0x00000001 << 14)                             /*!<R/W 0  //Before SS VC is, 0: pulled low 1: floating */
#define AON_SHIFT_FPWMDELAY                          13
#define AON_BIT_FPWMDELAY                            ((u32)0x00000001 << 13)                             /*!<R/W 0  //1:PFM[=]PWM //PFM/PWM change by using DFF(CKMOD) */
#define AON_SHIFT_ENFPWMDELAY_H                      12
#define AON_BIT_ENFPWMDELAY_H                        ((u32)0x00000001 << 12)                             /*!<R/W 0  //1:PFM=]PWM delay //PWM enable and wait one clock cycle then PFM off */
#define AON_SHIFT_MOS_HALF_L                         11
#define AON_BIT_MOS_HALF_L                           ((u32)0x00000001 << 11)                             /*!<R 0  //1:power mos half */
#define AON_SHIFT_CURRENT_SENSE_MOS                  10
#define AON_BIT_CURRENT_SENSE_MOS                    ((u32)0x00000001 << 10)                             /*!<R/W 0  //1: current sensing MOS for large OC current */
#define AON_SHIFT_PFMCMP_IQ                          9
#define AON_BIT_PFMCMP_IQ                            ((u32)0x00000001 << 9)                              /*!<R/W 1  //PFM comparator bias, //0: 50nA 1:250nA */
#define AON_SHIFT_REG_FORCE_SRC_IMIRROR_EN           8
#define AON_BIT_REG_FORCE_SRC_IMIRROR_EN             ((u32)0x00000001 << 8)                              /*!<R/W 0  // Force SWR_SRC IBIAS Generation circuit enable 1: force enable (need enable this circuit before enable small LDO for SRC, LDO_SDIO, LDO_WLON) 0: non force, IBIAS enable listen to REG_SRC_POW_SW (default) */
#define AON_SHIFT_OFF_END_SEL                        7
#define AON_BIT_OFF_END_SEL                          ((u32)0x00000001 << 7)                              /*!<R/W 1  //COT off time controlled by, //0: ZCD 1: min off time */
#define AON_SHIFT_POW_MINOFF_L                       6
#define AON_BIT_POW_MINOFF_L                         ((u32)0x00000001 << 6)                              /*!<R/W 1  //COT off time controlled by, //0: ZCD 1: min off time */
#define AON_SHIFT_COT_I_L                            4
#define AON_MASK_COT_I_L                             ((u32)0x00000003 << 4)                              /*!<R/W 01  //COT ON Current //00:150nA //01:150nA+100nA //10:150nA+150nA //11:150nA+250nA */
#define AON_SHIFT_VREFPFM_L                          0
#define AON_MASK_VREFPFM_L                           ((u32)0x0000000F << 0)                              /*!<R/W 1010  // SWR/LDO //0000 0.750 //0001 0.800 //0010 0.850 //0011 0.900 //0100 0.950 //0101 1.000 <== step between these two //0110 1.150 <== step between these two //0111 1.200 //1000 1.250 //1001 1.300 //1010 1.350 (default) //1011 1.400 //1100 1.450 //1101 1.500 //1110 1.550 //1111 1.600 */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_SWR_SRC_CTRL2
 * @brief                                            (@ 0X020)
 * @{
 *****************************************************************************/
#define AON_SHIFT_REG_SWR_RSV_CTRL                   16
#define AON_MASK_REG_SWR_RSV_CTRL                    ((u32)0x00000003 << 16)                             /*!<R/W 00  // BG current adjustment // 00 default 23.9n // 01 54.6n // 10 117.8n */
#define AON_SHIFT_REG_SWR_ZCD_CTRL                   14
#define AON_MASK_REG_SWR_ZCD_CTRL                    ((u32)0x00000003 << 14)                             /*!<R/W 10  // SWR ZCD CTRL control <1> 1'b1: extra current add if zcdc is 2'b11, 1'b0 : no extra current (default) <0> 1'b1: force in CCM/DCM boundary mode, 1'b0 : no boundary (default) */
#define AON_SHIFT_REG_PWM_VREF_SEL                   12
#define AON_MASK_REG_PWM_VREF_SEL                    ((u32)0x00000003 << 12)                             /*!<R/W 0  PWM_VREF_SEL 2'b11 0P600V for SWR1P8V (DDR2) 2'b10 0P575V for SWR1P725V (DDR2 trim) 2'b01 0P500V for SWR1P5V (DDR3) 2'b00 0P450V for SWR1P35V (DDR3L) (default) */
#define AON_SHIFT_SN_N_L                             8
#define AON_MASK_SN_N_L                              ((u32)0x0000000F << 8)                              /*!<R/W 1011  NGATE NMOS driving */
#define AON_SHIFT_SP_N_L                             4
#define AON_MASK_SP_N_L                              ((u32)0x0000000F << 4)                              /*!<R/W 1000  NGATE PMOS driving */
#define AON_SHIFT_SN_P_L                             0
#define AON_MASK_SN_P_L                              ((u32)0x0000000F << 0)                              /*!<R/W 0011  PGATE NMOS driving */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_SWR_SRC_CTRL3
 * @brief                                            (@ 0X024)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SDZN_L                             30
#define AON_MASK_SDZN_L                              ((u32)0x00000003 << 30)                             /*!<R/W 01  //Nonoverlap delay cell for NMOS */
#define AON_SHIFT_AUTOZCD_L                          29
#define AON_BIT_AUTOZCD_L                            ((u32)0x00000001 << 29)                             /*!<R/W 0  //0:register 1:10000 */
#define AON_SHIFT_VOFB_SEL                           28
#define AON_BIT_VOFB_SEL                             ((u32)0x00000001 << 28)                             /*!<R/W 0  //0:vo18 //1:LX_SPS */
#define AON_SHIFT_TBOX_L1                            26
#define AON_MASK_TBOX_L1                             ((u32)0x00000003 << 26)                             /*!<R/W 00  //TBOX_L1[1:0] output //00 CKOVER/RAMPOVER //01 // NI/PI //10 CKSS/SSOVER //11 // i/NIOFF_H */
#define AON_SHIFT_ENOCPMUX_L                         25
#define AON_BIT_ENOCPMUX_L                           ((u32)0x00000001 << 25)                             /*!<R/W 1  1:OCP signal control by MUX 0:OCP signal control by I */
#define AON_SHIFT_FORCE_LDOS                         24
#define AON_BIT_FORCE_LDOS                           ((u32)0x00000001 << 24)                             /*!<R/W 0  //1 : LDOS force into Standby Mode //0 : LDOS at normal mode (default) */
#define AON_SHIFT_VO_DISCHG                          23
#define AON_BIT_VO_DISCHG                            ((u32)0x00000001 << 23)                             /*!<R/W 0  //1:VO with 2mA discharge (internal RES ~ 893ohm) */
#define AON_SHIFT_LDO_OC_CLAMP                       22
#define AON_BIT_LDO_OC_CLAMP                         ((u32)0x00000001 << 22)                             /*!<R/W 1  // no function */
#define AON_SHIFT_MINOFF_LIQ                         21
#define AON_BIT_MINOFF_LIQ                           ((u32)0x00000001 << 21)                             /*!<R/W 1  //0:Min. off circuit always on //1:Min. off circuit pulse on */
#define AON_SHIFT_MINON_LIQ                          20
#define AON_BIT_MINON_LIQ                            ((u32)0x00000001 << 20)                             /*!<R/W 1  //0:Min. on circuit always on //1:Min. on circuit pulse on */
#define AON_SHIFT_POW_AUTO_L                         19
#define AON_BIT_POW_AUTO_L                           ((u32)0x00000001 << 19)                             /*!<R/W 0  //1:auto PFM/PWM //0:register control */
#define AON_SHIFT_REG_VC_CLAMP_SEL_L                 18
#define AON_BIT_REG_VC_CLAMP_SEL_L                   ((u32)0x00000001 << 18)                             /*!<R/W 0  // 0(default) : unity gain feedback clamp VC=VREF // 1.orignal clamp(roll back option) */
#define AON_SHIFT_NO_OFFTIME_L                       17
#define AON_BIT_NO_OFFTIME_L                         ((u32)0x00000001 << 17)                             /*!<R/W 0  //0:from min OFF time(PFM COT) //1:always on */
#define AON_SHIFT_EN_ON_END_L                        16
#define AON_BIT_EN_ON_END_L                          ((u32)0x00000001 << 16)                             /*!<R/W 1  //1:EN min OFF time (PFM COT) */
#define AON_SHIFT_ENCOT_L                            15
#define AON_BIT_ENCOT_L                              ((u32)0x00000001 << 15)                             /*!<R/W 1  //1:PFM COT */
#define AON_SHIFT_CLK_SEL                            13
#define AON_MASK_CLK_SEL                             ((u32)0x00000003 << 13)                             /*!<R/W 11  //00:out of phase CKSS //01:out of phase PWM_CTRIL //10:ckout //11:HG */
#define AON_SHIFT_TYPE_L                             12
#define AON_BIT_TYPE_L                               ((u32)0x00000001 << 12)                             /*!<R/W 1  //1:type3 0:type2 */
#define AON_SHIFT_R3_L1                              10
#define AON_MASK_R3_L1                               ((u32)0x00000003 << 10)                             /*!<R/W 10  //00 => 36k //01 => 30k //10 => 24k //11 => 24k */
#define AON_SHIFT_R2_L1                              8
#define AON_MASK_R2_L1                               ((u32)0x00000003 << 8)                              /*!<R/W 10  //00 => 2.5M //01 => 2.0M //10 => 1.5M //11 => 1.0M */
#define AON_SHIFT_R1_L1                              6
#define AON_MASK_R1_L1                               ((u32)0x00000003 << 6)                              /*!<R/W 10  //00 => 900k //01 => 720k //10 => 900k //11 => 1080k */
#define AON_SHIFT_C3_L1                              4
#define AON_MASK_C3_L1                               ((u32)0x00000003 << 4)                              /*!<R/W 10  //00 => 1.59p //01 => 3.2p //10 => 4.76p //11 => 6.34p */
#define AON_SHIFT_C2_L1                              2
#define AON_MASK_C2_L1                               ((u32)0x00000003 << 2)                              /*!<R/W 10  //00 => 13f //01 => 26f //10 => 39f //11 => 41f */
#define AON_SHIFT_C1_L1                              0
#define AON_MASK_C1_L1                               ((u32)0x00000003 << 0)                              /*!<R/W 10  //00 => 1.03p //01 => 2.06p //10 => 3.1p //11 => 4.12p */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_SWR_SRC_CTRL4
 * @brief                                            (@ 0X028)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SRC_DBG                            28
#define AON_MASK_SRC_DBG                             ((u32)0x00000003 << 28)                             /*!<R 00  REG_SRC_ANAPARSW_MAC_OFF[27:26] SRC_DTEST_SWREG_L<1> SRC_DTEST_SWREG_L<0> 2'b00 (1'b1=PWM, 1'b0=PFM) RAMPOVER 2'b01 NI PI 2'b10 CKSS SSOVER 2'b11 i NIOFF_H  */
#define AON_SHIFT_TESTCHIP_DIG_ZCD_CNT_SELECT        13
#define AON_BIT_TESTCHIP_DIG_ZCD_CNT_SELECT          ((u32)0x00000001 << 13)                             /*!<R/W 0  //TOP ZCD counter select //0(default) : reset by 10000 //1 : reset by 11111 */
#define AON_SHIFT_SWR_SRC_CTRL4_DUMMY_0              12
#define AON_BIT_SWR_SRC_CTRL4_DUMMY_0                ((u32)0x00000001 << 12)                             /*!<R/W 0  //Dummy */
#define AON_SHIFT_BG_R1_TUNE2                        11
#define AON_BIT_BG_R1_TUNE2                          ((u32)0x00000001 << 11)                             /*!<R/W 1  // 0(default) : unity gain feedback clamp VC=VREF // 1.orignal clamp(roll back option) */
#define AON_SHIFT_BG_R1_TUNE1                        10
#define AON_BIT_BG_R1_TUNE1                          ((u32)0x00000001 << 10)                             /*!<R/W 0  //LDO feedforward cap //0 : disable //1 : enable (default) */
#define AON_SHIFT_SRC_LDO_BUFFER_DIS_L               9
#define AON_BIT_SRC_LDO_BUFFER_DIS_L                 ((u32)0x00000001 << 9)                              /*!<R/W 0  //LDO buffer //0 : enable (default) //1 : disable */
#define AON_SHIFT_BG_R2_TUNE2                        8
#define AON_BIT_BG_R2_TUNE2                          ((u32)0x00000001 << 8)                              /*!<R/W 1  //LDO_MODE //0 : Normal Mode (default) //1 : Standby Mode */
#define AON_SHIFT_BG_R2_TUNE1                        6
#define AON_MASK_BG_R2_TUNE1                         ((u32)0x00000003 << 6)                              /*!<R/W 00  BG TC tune */
#define AON_SHIFT_NMOS_OFF_L                         5
#define AON_BIT_NMOS_OFF_L                           ((u32)0x00000001 << 5)                              /*!<R/W 0  //0:normal //1:NMOS always off */
#define AON_SHIFT_MUX_PI_L                           4
#define AON_BIT_MUX_PI_L                             ((u32)0x00000001 << 4)                              /*!<R/W 0  //1:PI (original) //0:i */
#define AON_SHIFT_PWM_CTRL_L                         3
#define AON_BIT_PWM_CTRL_L                           ((u32)0x00000001 << 3)                              /*!<R/W 0  //0:internal PWM //1:external PWM */
#define AON_SHIFT_ENSR_L                             2
#define AON_BIT_ENSR_L                               ((u32)0x00000001 << 2)                              /*!<R/W 1  //1:with SSR latch */
#define AON_SHIFT_SDZP_L                             0
#define AON_MASK_SDZP_L                              ((u32)0x00000003 << 0)                              /*!<R/W 01  //Nonoverlap delay cell for PMOS */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_SWR_SRC_OCP
 * @brief                                            (@ 0X02C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SWR_OCP_EN                         31
#define AON_BIT_SWR_OCP_EN                           ((u32)0x00000001 << 31)                             /*!<R/W 1  SRC OCP function enable */
#define AON_SHIFT_SWR_OCP_THD                        16
#define AON_MASK_SWR_OCP_THD                         ((u32)0x00007FFF << 16)                             /*!<R/W 0  SRC OCP threshold */
#define AON_SHIFT_SWR_OCP_WND                        0
#define AON_MASK_SWR_OCP_WND                         ((u32)0x0000FFFF << 0)                              /*!<R/W 0  SRC OCP time windows */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_SWR_ZCD_CTRL
 * @brief                                            (@ 0X030)
 * @{
 *****************************************************************************/
#define AON_SHIFT_ZCD_FORCE_VALUE                    8
#define AON_MASK_ZCD_FORCE_VALUE                     ((u32)0x0000001F << 8)                              /*!<R/W 0  ZCD Force Value */
#define AON_SHIFT_ZCD_FORCE_EN                       7
#define AON_BIT_ZCD_FORCE_EN                         ((u32)0x00000001 << 7)                              /*!<R/W 0  1:Enable ZCD Force */
#define AON_SHIFT_ZCD_VALUE                          1
#define AON_MASK_ZCD_VALUE                           ((u32)0x0000003F << 1)                              /*!<R 0x10  Read zero current detection value */
#define AON_SHIFT_ZCD_EN                             0
#define AON_BIT_ZCD_EN                               ((u32)0x00000001 << 0)                              /*!<R/W 0  1:Enable ZCD Circuit */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_SWR_SRC_LV_CTRL
 * @brief                                            (@ 0X034)
 * @{
 *****************************************************************************/
#define AON_SHIFT_COUNT_READY                        6
#define AON_BIT_COUNT_READY                          ((u32)0x00000001 << 6)                              /*!<R 0  1:PMC Done */
#define AON_SHIFT_UP_EN                              5
#define AON_BIT_UP_EN                                ((u32)0x00000001 << 5)                              /*!<R/W 0  1:Enable PMC to Increase SWR_SRC output Level */
#define AON_SHIFT_DOWN_EN                            4
#define AON_BIT_DOWN_EN                              ((u32)0x00000001 << 4)                              /*!<R/W 0  1:Enable PMC to Decrease SWR_SRC output Level */
#define AON_SHIFT_PFM_LV                             0
#define AON_MASK_PFM_LV                              ((u32)0x0000000F << 0)                              /*!<R/W 2  PFM Output level under LDO WLON at Bypss Mode */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_XTAL32K_CTRL0
 * @brief                                            (@ 0X040)
 * @{
 *****************************************************************************/
#define AON_SHIFT_XTAL32K_GM_3_0                     28
#define AON_MASK_XTAL32K_GM_3_0                      ((u32)0x0000000F << 28)                             /*!<R/W 1111  gm size */
#define AON_SHIFT_XTAL32K_CUR_REP_1_0                26
#define AON_MASK_XTAL32K_CUR_REP_1_0                 ((u32)0x00000003 << 26)                             /*!<R/W 01  replica buffer current */
#define AON_SHIFT_XTAL32K_CUR_GM_3_0                 22
#define AON_MASK_XTAL32K_CUR_GM_3_0                  ((u32)0x0000000F << 22)                             /*!<R/W 0101  awake gm current, 7pXtal: 0100 */
#define AON_SHIFT_XTAL32K_CUR_GM_INI_3_0             18
#define AON_MASK_XTAL32K_CUR_GM_INI_3_0              ((u32)0x0000000F << 18)                             /*!<R/W 1001  initial gm current, 7pXtal: 0100 */
#define AON_SHIFT_XTAL32K_CUR_MAIN_1_0               16
#define AON_MASK_XTAL32K_CUR_MAIN_1_0                ((u32)0x00000003 << 16)                             /*!<R/W 01  xtal main current */
#define AON_SHIFT_POW_XTAL32K                        0
#define AON_BIT_POW_XTAL32K                          ((u32)0x00000001 << 0)                              /*!<R/W 0  xtal 32KHz enable */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_XTAL32K_CTRL1
 * @brief                                            (@ 0X044)
 * @{
 *****************************************************************************/
#define AON_SHIFT_RESERVED2                          23
#define AON_BIT_RESERVED2                            ((u32)0x00000001 << 23)                             /*!<R/W 0  Reserved */
#define AON_SHIFT_XTAL32K_GPIO_SEL                   22
#define AON_BIT_XTAL32K_GPIO_SEL                     ((u32)0x00000001 << 22)                             /*!<R/W 1  0: 32K 1: GPIO Should be efuse control */
#define AON_SHIFT_XTAL32K_SC_XO_EXTRA                21
#define AON_BIT_XTAL32K_SC_XO_EXTRA                  ((u32)0x00000001 << 21)                             /*!<R/W 0  0: w/i 2.8pF cap 1: w/o 2.8pF cap  */
#define AON_SHIFT_XTAL32K_SC_XI_EXTRA                20
#define AON_BIT_XTAL32K_SC_XI_EXTRA                  ((u32)0x00000001 << 20)                             /*!<R/W 0  0: w/i 2.8pF cap 1: w/o 2.8pF cap  */
#define AON_SHIFT_XTAL32K_GM_REP_2_0                 17
#define AON_MASK_XTAL32K_GM_REP_2_0                  ((u32)0x00000007 << 17)                             /*!<R/W 111  repilca size */
#define AON_SHIFT_ENB_XTAL32K_FBRES                  16
#define AON_BIT_ENB_XTAL32K_FBRES                    ((u32)0x00000001 << 16)                             /*!<R/W 0  0: enable feedback resistor */
#define AON_SHIFT_XTAL32K_TOK_1_0                    14
#define AON_MASK_XTAL32K_TOK_1_0                     ((u32)0x00000003 << 14)                             /*!<R/W 11  00: 100ms 01:200ms 10:400ms 11: 800ms */
#define AON_SHIFT_XTAL32K_SC_XO_5_0                  8
#define AON_MASK_XTAL32K_SC_XO_5_0                   ((u32)0x0000003F << 8)                              /*!<R/W 100000  xo cap */
#define AON_SHIFT_XTAL32K_SC_XI_5_0                  2
#define AON_MASK_XTAL32K_SC_XI_5_0                   ((u32)0x0000003F << 2)                              /*!<R/W 100000  xi cap */
#define AON_SHIFT_EN_XTAL32K_CAP_AWAKE               1
#define AON_BIT_EN_XTAL32K_CAP_AWAKE                 ((u32)0x00000001 << 1)                              /*!<R/W 1  internal cap enable as awake */
#define AON_SHIFT_EN_XTAL32K_CAP_INITIAL             0
#define AON_BIT_EN_XTAL32K_CAP_INITIAL               ((u32)0x00000001 << 0)                              /*!<R/W 1  internal cap enable as initial */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_OSC32K_CTRL0
 * @brief                                            (@ 0X048)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_DUMMY_2                            30
#define AON_BIT_DUMMY_2                              ((u32)0x00000001 << 30)                             /*!<R/W 0  RSVD */
#else
#define AON_SHIFT_SWR_SRC_SWITCH                     30
#define AON_BIT_SWR_SRC_SWITCH                       ((u32)0x00000001 << 30)                             /*!<R/W 0  1: Connect to AON+0x1C[3:0] 0: Connect to swr_ctrl for sleep up/down in Low power mode transition */
#endif
#define AON_SHIFT_SEL_LDO_VREF                       29
#define AON_BIT_SEL_LDO_VREF                         ((u32)0x00000001 << 29)                             /*!<R/W 0  0: LDO low valtage setting 1:high voltage */
#define AON_SHIFT_RCAL_5_0                           16
#define AON_MASK_RCAL_5_0                            ((u32)0x0000003F << 16)                             /*!<R/W 100000  osc frequency is highier as RCAL's larger */
#define AON_SHIFT_DUMMY_14_6                         3
#define AON_MASK_DUMMY_14_6                          ((u32)0x000001FF << 3)                              /*!<R/W 0x000  Dummy */
#define AON_SHIFT_DUMMY_1_0                          1
#define AON_MASK_DUMMY_1_0                           ((u32)0x00000003 << 1)                              /*!<R/W 00  // [RF][32KOSC] dummy */
#define AON_SHIFT_POW_OSC32K                         0
#define AON_BIT_POW_OSC32K                           ((u32)0x00000001 << 0)                              /*!<R/W 0  32k osc enable */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_PLATFORM_VER
 * @brief                                            (@ 0X04C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_PLATFORM_VER                       0
#define AON_MASK_PLATFORM_VER                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Platform Version number */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_OSC4M_CTRL
 * @brief                                            (@ 0X050)
 * @{
 *****************************************************************************/
#define AON_SHIFT_C_SEL                              29
#define AON_BIT_C_SEL                                ((u32)0x00000001 << 29)                             /*!<R/W 0   */
#define AON_SHIFT_EN_4MOSC                           28
#define AON_BIT_EN_4MOSC                             ((u32)0x00000001 << 28)                             /*!<R/W 0  [4MOSC] 1'b1 : enable */
#define AON_SHIFT_POW33_LVSFT                        27
#define AON_BIT_POW33_LVSFT                          ((u32)0x00000001 << 27)                             /*!<R/W 0   */
#define AON_SHIFT_IB_BIAS_SEL                        22
#define AON_MASK_IB_BIAS_SEL                         ((u32)0x0000001F << 22)                             /*!<R/W 01111   */
#define AON_SHIFT_VCM_SEL_H                          18
#define AON_MASK_VCM_SEL_H                           ((u32)0x0000000F << 18)                             /*!<R/W 1011   */
#define AON_SHIFT_VCM_SEL_L                          14
#define AON_MASK_VCM_SEL_L                           ((u32)0x0000000F << 14)                             /*!<R/W 1011   */
#define AON_SHIFT_FREQ_R_SEL                         6
#define AON_MASK_FREQ_R_SEL                          ((u32)0x000000FF << 6)                              /*!<R/W 10000000   */
#define AON_SHIFT_POW_4MOSC_YCC                      5
#define AON_BIT_POW_4MOSC_YCC                        ((u32)0x00000001 << 5)                              /*!<R/W 1  REG_POW_4MOSC_YCC */
#define AON_SHIFT_OSC4M_FSET_YCC_3_0                 1
#define AON_MASK_OSC4M_FSET_YCC_3_0                  ((u32)0x0000000F << 1)                              /*!<R/W 1000  osc freq control ,code up freq up */
#define AON_SHIFT_POW_4MOSC                          0
#define AON_BIT_POW_4MOSC                            ((u32)0x00000001 << 0)                              /*!<R/W 0  REG_POW_4MOSC */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SW_DBG0
 * @brief                                            (@ 0X054)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SW_USE0                            0
#define AON_MASK_SW_USE0                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SW_DBG1
 * @brief                                            (@ 0X058)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SW_USE1                            0
#define AON_MASK_SW_USE1                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_XTAL_CLK_CTRL0
 * @brief                                            (@ 0X05C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_XTAL_SC_XO                         21
#define AON_MASK_XTAL_SC_XO                          ((u32)0x0000007F << 21)                             /*!<R/W 1000000  1: reduce cap, 0: increase cap. (160fF per unit) [efuse for BT only ] */
#define AON_SHIFT_XTAL_SC_XI                         14
#define AON_MASK_XTAL_SC_XI                          ((u32)0x0000007F << 14)                             /*!<R/W 1000000  1: reduce cap, 0: increase cap. (160fF per unit) [efuse for BT only ] */
#define AON_SHIFT_XTAL_GMN                           9
#define AON_MASK_XTAL_GMN                            ((u32)0x0000001F << 9)                              /*!<R/W 11111  GMN: 0~31 */
#define AON_SHIFT_XTAL_GMP                           4
#define AON_MASK_XTAL_GMP                            ((u32)0x0000001F << 4)                              /*!<R/W 11111  GMP: 0~31 */
#define AON_SHIFT_XTAL_POR                           3
#define AON_BIT_XTAL_POR                             ((u32)0x00000001 << 3)                              /*!<R/W 0  1: Enable xtal 0.9V */
#define AON_SHIFT_XTAL_HW33_EN                       2
#define AON_BIT_XTAL_HW33_EN                         ((u32)0x00000001 << 2)                              /*!<R/W 0  1: Enable xtal 3.3V */
#define AON_SHIFT_POW_XTAL                           1
#define AON_BIT_POW_XTAL                             ((u32)0x00000001 << 1)                              /*!<R/W 0  0 to 1 Enable xtal  */
#define AON_SHIFT_POW_BG                             0
#define AON_BIT_POW_BG                               ((u32)0x00000001 << 0)                              /*!<R/W 0  Enable BG (BG for xtal and AFE) */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_XTAL_CLK_CTRL1
 * @brief                                            (@ 0X060)
 * @{
 *****************************************************************************/
#define AON_SHIFT_XTAL_LPS_DIVISOR                   29
#define AON_BIT_XTAL_LPS_DIVISOR                     ((u32)0x00000001 << 29)                             /*!<R/W 0  XTAL LPS clock divider 0: XTAL/128(40M), 1: XTAL/64 */
#define AON_SHIFT_XTAL_CKDIGI_SEL                    28
#define AON_BIT_XTAL_CKDIGI_SEL                      ((u32)0x00000001 << 28)                             /*!<R/W 1  1: DIGI CLK from self-bias 0: DIGI CLK from Schmitt */
#define AON_SHIFT_EN_XTAL_LPS_CLK                    27
#define AON_BIT_EN_XTAL_LPS_CLK                      ((u32)0x00000001 << 27)                             /*!<R/W 1  1: enable XTAL LPS clock (312.5kHz enable) */
#define AON_SHIFT_EN_XTAL_SCHMITT                    26
#define AON_BIT_EN_XTAL_SCHMITT                      ((u32)0x00000001 << 26)                             /*!<R/W 1  1: enable XTAL SCHMITT  */
#define AON_SHIFT_XTAL_LDO_VREF                      23
#define AON_MASK_XTAL_LDO_VREF                       ((u32)0x00000007 << 23)                             /*!<R/W 011  111: 1.25V 110: 1.2V 101:1.15V 100:1.1V 011: 1.05V 010: 1V 001: 0.95V 000: 0.9V */
#define AON_SHIFT_XTAL_SEL_TOK                       20
#define AON_MASK_XTAL_SEL_TOK                        ((u32)0x00000007 << 20)                             /*!<R/W 100  For cycles / 40MHz / 26MHz 000: 8 / 200n / 300n 001: 16 / 400n / 600n 010: 32 / 800n / 1.2u 011: 64 / 1.6u / 2.5u 100: 2^14 / 0.4m / 0.6m 101: 2^15 / 0.8m / 1.2m 110: 2^16 / 1.6m / 2.5m 111: 2^17 / 3.2m / 4.9m  */
#define AON_SHIFT_EN_XTAL_DRV_LPS                    19
#define AON_BIT_EN_XTAL_DRV_LPS                      ((u32)0x00000001 << 19)                             /*!<R/W 0  LPS enable clock source control, 1:enable, 0: gated (312.5kHz enable) */
#define AON_SHIFT_EN_XTAL_DRV_DIGI                   18
#define AON_BIT_EN_XTAL_DRV_DIGI                     ((u32)0x00000001 << 18)                             /*!<R/W 0  DIGI enable clock source control, 1:enable, 0: gated  */
#define AON_SHIFT_EN_XTAL_DRV_USB                    17
#define AON_BIT_EN_XTAL_DRV_USB                      ((u32)0x00000001 << 17)                             /*!<R/W 0  USB enable clock source control, 1:enable, 0: gated  */
#define AON_SHIFT_EN_XTAL_DRV_AFE                    16
#define AON_BIT_EN_XTAL_DRV_AFE                      ((u32)0x00000001 << 16)                             /*!<R/W 0  AFE enable clock source control, 1:enable, 0: gated (for WL AFE PLL) */
#define AON_SHIFT_EN_XTAL_DRV_RF2                    15
#define AON_BIT_EN_XTAL_DRV_RF2                      ((u32)0x00000001 << 15)                             /*!<R/W 0  RF2 enable clock source control, 1:enable, 0: gated (for BT) */
#define AON_SHIFT_EN_XTAL_DRV_RF1                    14
#define AON_BIT_EN_XTAL_DRV_RF1                      ((u32)0x00000001 << 14)                             /*!<R/W 0  RF1 enable clock source control, 1:enable, 0: gated (for WL SYN) */
#define AON_SHIFT_XTAL_SC_LPS_RO                     7
#define AON_MASK_XTAL_SC_LPS_RO                      ((u32)0x0000007F << 7)                              /*!<R 0x3f  0: reduce cap, 1: incease cap. (160fF per unit) efuse for BT only Singal from XMD output XTAL_SC_LPS_i<6:0> */
#define AON_SHIFT_XTAL_SC_INIT                       0
#define AON_MASK_XTAL_SC_INIT                        ((u32)0x0000007F << 0)                              /*!<R/W 0000000  0: reduce cap, 1: increase cap. (160fF per unit) efuse for BT only Set to 0 if external Cap is available */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_XTAL_CLK_CTRL2
 * @brief                                            (@ 0X064)
 * @{
 *****************************************************************************/
#define AON_SHIFT_XTAL_LPMODE                        31
#define AON_BIT_XTAL_LPMODE                          ((u32)0x00000001 << 31)                             /*!<R/W 0  1: low power mode enable 22C turn off replica path, RF1 no CLK RF2 sweep to LPS buf  */
#define AON_SHIFT_XTAL_DELAY_DIGI                    30
#define AON_BIT_XTAL_DELAY_DIGI                      ((u32)0x00000001 << 30)                             /*!<R/W 1  1: turn on XI/XO Cfix, single side 8pF */
#define AON_SHIFT_XTAL_DELAY_USB                     29
#define AON_BIT_XTAL_DELAY_USB                       ((u32)0x00000001 << 29)                             /*!<R/W 1  0: short, 1:long */
#define AON_SHIFT_XTAL_DELAY_AFE                     28
#define AON_BIT_XTAL_DELAY_AFE                       ((u32)0x00000001 << 28)                             /*!<R/W 1  0: short, 1:long */
#define AON_SHIFT_XTAL_DRV_DIGI                      26
#define AON_MASK_XTAL_DRV_DIGI                       ((u32)0x00000003 << 26)                             /*!<R/W 11  Driving control of DIGI/LPS clock buffer, 11:large current, 00: small current  */
#define AON_SHIFT_XTAL_DRV_USB                       24
#define AON_MASK_XTAL_DRV_USB                        ((u32)0x00000003 << 24)                             /*!<R/W 11  Driving control of USB clock buffer, 11:large current, 00: small current */
#define AON_SHIFT_XTAL_DRV_AFE                       22
#define AON_MASK_XTAL_DRV_AFE                        ((u32)0x00000003 << 22)                             /*!<R/W 11  Driving control of AFE clock buffer, 11:large current, 00: small current */
#define AON_SHIFT_XTAL_DRV_RF2                       20
#define AON_MASK_XTAL_DRV_RF2                        ((u32)0x00000003 << 20)                             /*!<R/W 11  Driving control of RF2 clock buffer, 11:large current, 00: small current */
#define AON_SHIFT_XTAL_DRV_RF1                       18
#define AON_MASK_XTAL_DRV_RF1                        ((u32)0x00000003 << 18)                             /*!<R/W 11  Driving control of RF1 clock buffer, 11:large current, 00: small current */
#define AON_SHIFT_XTAL_DRV_RF_LATCH                  17
#define AON_BIT_XTAL_DRV_RF_LATCH                    ((u32)0x00000001 << 17)                             /*!<R/W 1  1: latch enable */
#define AON_SHIFT_XTAL_GM_SEP                        16
#define AON_BIT_XTAL_GM_SEP                          ((u32)0x00000001 << 16)                             /*!<R/W 0  0: GMP=GMN */
#define AON_SHIFT_XQSEL_RF_AWAKE                     15
#define AON_BIT_XQSEL_RF_AWAKE                       ((u32)0x00000001 << 15)                             /*!<R/W 1  0: Schmitt trigger, 1:replica INV(for OK0=1) */
#define AON_SHIFT_XQSEL_RF_INITIAL                   14
#define AON_BIT_XQSEL_RF_INITIAL                     ((u32)0x00000001 << 14)                             /*!<R/W 0  0: Schmitt trigger, 1:replica INV(for OK0=0) */
#define AON_SHIFT_XQSEL                              13
#define AON_BIT_XQSEL                                ((u32)0x00000001 << 13)                             /*!<R/W 0  0: Schmitt trigger, 1:replica INV(for AFE) */
#define AON_SHIFT_GATED_XTAL_OK0                     12
#define AON_BIT_GATED_XTAL_OK0                       ((u32)0x00000001 << 12)                             /*!<R/W 0  1:Gated xtal OK0 */
#define AON_SHIFT_EN_XTAL_DRV_IQK_BCN                11
#define AON_BIT_EN_XTAL_DRV_IQK_BCN                  ((u32)0x00000001 << 11)                             /*!<R/W 1  IQKPLL enable clock source control, 1:enable, 0: gate */
#define AON_SHIFT_AAC_MODE                           9
#define AON_MASK_AAC_MODE                            ((u32)0x00000003 << 9)                              /*!<R/W 01  AAC_MODE for LPS 00: all XOXI cap off 01: cap from XTAL_SC_LPS 10: cap from XTAL_SC_INIT 11: cap from XTAL_SC_XI/XO */
#define AON_SHIFT_XTAL_CFIX                          7
#define AON_MASK_XTAL_CFIX                           ((u32)0x00000003 << 7)                              /*!<R/W 11  11: 7.9pF, 10: 4.5pF, 01: 3.4pF, 00: off */
#define AON_SHIFT_XTAL_AAC_OPCUR                     5
#define AON_MASK_XTAL_AAC_OPCUR                      ((u32)0x00000003 << 5)                              /*!<R/W 11  00: 200nA , 200n/step For AAC robust 11 */
#define AON_SHIFT_XTAL_VREF_SEL                      0
#define AON_MASK_XTAL_VREF_SEL                       ((u32)0x0000001F << 0)                              /*!<R/W 11000  Analog AAC VREF, 390mV~700mV, 10mV/step 11000: Vpp 500mV  */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_XTAL_CLK_CTRL3
 * @brief                                            (@ 0X068)
 * @{
 *****************************************************************************/
#define AON_SHIFT_XTAL_SRC_BT                        29
#define AON_MASK_XTAL_SRC_BT                         ((u32)0x00000007 << 29)                             /*!<R/W 000  Dummy(w/o SRC) */
#define AON_SHIFT_XTAL_SRC_RF                        26
#define AON_MASK_XTAL_SRC_RF                         ((u32)0x00000007 << 26)                             /*!<R/W 000  Dummy(w/o SRC) */
#define AON_SHIFT_XTAL_DUMMY                         22
#define AON_MASK_XTAL_DUMMY                          ((u32)0x0000000F << 22)                             /*!<R/W 0000  Dummy control bits  */
#define AON_SHIFT_XTAL_EN_LNBUF                      21
#define AON_BIT_XTAL_EN_LNBUF                        ((u32)0x00000001 << 21)                             /*!<R/W 0  0: separate bias buffer (lower current higher noise) 1: self-bias (higher current lower noise) */
#define AON_SHIFT_XTAL__AAC_TIE_MID                  20
#define AON_BIT_XTAL__AAC_TIE_MID                    ((u32)0x00000001 << 20)                             /*!<R/W 0  XTAL_ AAC_TIE_MID=1 & EN_XTAL_PDCK_VREF=0 & using XTAL_VREF_SEL<4:0> for lock detect */
#define AON_SHIFT_XTAL_AAC_IOFFSET                   18
#define AON_MASK_XTAL_AAC_IOFFSET                    ((u32)0x00000003 << 18)                             /*!<R/W 00  Analog AAC IOFFSET current 00: off, 01:2uA, 10:4uA, 11:6uA */
#define AON_SHIFT_XTAL_AAC_CAP                       16
#define AON_MASK_XTAL_AAC_CAP                        ((u32)0x00000003 << 16)                             /*!<R/W 11  Analog AAC domain pole cap 3pF/step 00: no cap,11: max cap */
#define AON_SHIFT_XTAL_PDSW                          14
#define AON_MASK_XTAL_PDSW                           ((u32)0x00000003 << 14)                             /*!<R/W 01  XTAL analog AAC peak detector source follower size, 00: small 11: large */
#define AON_SHIFT_XTAL_LPS_BUF_VB                    12
#define AON_MASK_XTAL_LPS_BUF_VB                     ((u32)0x00000003 << 12)                             /*!<R/W 00  00: small current, 11: large current */
#define AON_SHIFT_XTAL_PDCK_MANU                     11
#define AON_BIT_XTAL_PDCK_MANU                       ((u32)0x00000001 << 11)                             /*!<R/W 0  1: open analog AAC loop for PDCK manual  */
#define AON_SHIFT_XTAL_PDCK_OK_MANU                  10
#define AON_BIT_XTAL_PDCK_OK_MANU                    ((u32)0x00000001 << 10)                             /*!<R/W 1  1: force PDCK_OK=1 for PDCK manual */
#define AON_SHIFT_EN_XTAL_PDCK_VREF                  9
#define AON_BIT_EN_XTAL_PDCK_VREF                    ((u32)0x00000001 << 9)                              /*!<R/W 1  1: analog AAC VREF from PDCK digital circuit 0: analog AAC VREF from XTAL_VREF_SEL for BT only mode */
#define AON_SHIFT_XTAL_SEL_PWR                       8
#define AON_BIT_XTAL_SEL_PWR                         ((u32)0x00000001 << 8)                              /*!<R/W 0  1: external 0.9V, 0: internal 0.9V (FIB) */
#define AON_SHIFT_XTAL_PK_SEL_OFFSET                 7
#define AON_BIT_XTAL_PK_SEL_OFFSET                   ((u32)0x00000001 << 7)                              /*!<R/W 0  1: XI Vpk-to-Vpk offset to 00: 0.4V 01: 0.5V 10: 0.6V 11: 0.7V */
#define AON_SHIFT_XTAL_MANU_PK_SEL                   5
#define AON_MASK_XTAL_MANU_PK_SEL                    ((u32)0x00000003 << 5)                              /*!<R/W 11  XI Vpk-to-Vpk 00: 0.7V 01: 0.8V 10: 0.9V 11: 1V */
#define AON_SHIFT_XTAL_AACK_PK_MANU                  4
#define AON_BIT_XTAL_AACK_PK_MANU                    ((u32)0x00000001 << 4)                              /*!<R/W 0  1: manual for peak detector peak selection  */
#define AON_SHIFT_EN_XTAL_AAC_PKDET                  3
#define AON_BIT_EN_XTAL_AAC_PKDET                    ((u32)0x00000001 << 3)                              /*!<R/W 0  1: enable xtal aac peak detector */
#define AON_SHIFT_EN_XTAL_AAC_GM                     2
#define AON_BIT_EN_XTAL_AAC_GM                       ((u32)0x00000001 << 2)                              /*!<R/W 0  1: enable xtal aac gm control ,Note: This bit must be able to write by SW */
#define AON_SHIFT_XTAL_LDO_OPVB_SEL                  1
#define AON_BIT_XTAL_LDO_OPVB_SEL                    ((u32)0x00000001 << 1)                              /*!<R/W 0  0: OP bias from IBG, 1: OP bias from Res divider */
#define AON_SHIFT_XTAL_LDO_NC                        0
#define AON_BIT_XTAL_LDO_NC                          ((u32)0x00000001 << 0)                              /*!<R/W 0  1: low current normal mode (22C) 0:high current normal mode (BT could be control this pin) */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_XTAL_CLK_CTRL4
 * @brief                                            (@ 0X06C)
 * @{
 *****************************************************************************/
#define AON_SHIFT__XTAL_MODE_DEC                     15
#define AON_MASK__XTAL_MODE_DEC                      ((u32)0x00000003 << 15)                             /*!<R 10  XTAL Dec Mode */
#define AON_SHIFT_XMD_STATE                          10
#define AON_MASK_XMD_STATE                           ((u32)0x0000001F << 10)                             /*!<R 01011  XMD State */
#define AON_SHIFT_XTAL_SC_LPS                        3
#define AON_MASK_XTAL_SC_LPS                         ((u32)0x0000007F << 3)                              /*!<R/W 0000000  XTAL cap setting @LP 0: reduce cap, 1: increase cap. (160fF per unit) */
#define AON_SHIFT_XTAL_SRC_IQK_BCN                   0
#define AON_MASK_XTAL_SRC_IQK_BCN                    ((u32)0x00000007 << 0)                              /*!<R/W 000  Dummy(w/o SRC) */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_XTAL_CLK_CTRL5
 * @brief                                            (@ 0X070)
 * @{
 *****************************************************************************/
#define AON_SHIFT_XAAC_LPOW                          31
#define AON_BIT_XAAC_LPOW                            ((u32)0x00000001 << 31)                             /*!<R/W 0  AACK low power mode, 1:gating input clk */
#define AON_SHIFT_AAC_MODE_ON                        29
#define AON_MASK_AAC_MODE_ON                         ((u32)0x00000003 << 29)                             /*!<R/W 11  11: XTAL_AACK_PK_SEL=<11>'s XTAL_GM_OUT3 10: XTAL_AACK_PK_SEL=<10>'s XTAL_GM_OUT2 01: XTAL_AACK_PK_SEL=<01>'s XTAL_GM_OUT1 00: XTAL_AACK_PK_SEL=<00>'s XTAL_GM_OUT0 */
#define AON_SHIFT_EN_XTAL_AAC_TRIG                   28
#define AON_BIT_EN_XTAL_AAC_TRIG                     ((u32)0x00000001 << 28)                             /*!<R/W 0  Set by pmc and clr by HW finish calibration */
#define AON_SHIFT_EN_XTAL_AAC                        27
#define AON_BIT_EN_XTAL_AAC                          ((u32)0x00000001 << 27)                             /*!<R/W 0  0:aac off 1:aac power on */
#define AON_SHIFT_EN_XTAL_AAC_DIGI                   26
#define AON_BIT_EN_XTAL_AAC_DIGI                     ((u32)0x00000001 << 26)                             /*!<R/W 0  1:enable aac digital circuit */
#define AON_SHIFT_GM_MANUAL                          21
#define AON_MASK_GM_MANUAL                           ((u32)0x0000001F << 21)                             /*!<R/W 11111  Gm manual at EN_XTAL_AAC_DIGI=0 */
#define AON_SHIFT_GM_STUP                            16
#define AON_MASK_GM_STUP                             ((u32)0x0000001F << 16)                             /*!<R/W 11111  aac gm initial setting */
#define AON_SHIFT_XTAL_CK_SET_2_0                    13
#define AON_MASK_XTAL_CK_SET_2_0                     ((u32)0x00000007 << 13)                             /*!<R/W 011  aac settling cycles (4M CLK) 000: 64us 001: 128us 010: 256us 011: 512us 100: 1024us 101: 2048us 110: 4096us 111: 8192us */
#define AON_SHIFT_GM_INIT                            8
#define AON_MASK_GM_INIT                             ((u32)0x0000001F << 8)                              /*!<R/W 11111  aac gm initial setting  */
#define AON_SHIFT_GM_STEP                            7
#define AON_BIT_GM_STEP                              ((u32)0x00000001 << 7)                              /*!<R/W 0  aac gm searching step. 0:step 1, 1:step 2 */
#define AON_SHIFT_XAAC_GM_OFFSET                     2
#define AON_MASK_XAAC_GM_OFFSET                      ((u32)0x0000001F << 2)                              /*!<R/W 00000  aac calibrated gm result +/- offset */
#define AON_SHIFT_OFFSET_PLUS                        1
#define AON_BIT_OFFSET_PLUS                          ((u32)0x00000001 << 1)                              /*!<R/W 1  0: aac calibrated gm result - offset , 1:aac calibrated gm result + offset  */
#define AON_SHIFT_RESET_N                            0
#define AON_BIT_RESET_N                              ((u32)0x00000001 << 0)                              /*!<R/W 0  AAC digital circuit reset (low to high) */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_XTAL_CLK_CTRL6
 * @brief                                            (@ 0X074)
 * @{
 *****************************************************************************/
#define AON_SHIFT_XTAL_LDO_LPS                       26
#define AON_MASK_XTAL_LDO_LPS                        ((u32)0x00000007 << 26)                             /*!<R/W 010  (after oscillation, into LPS) 111: 1.1V 110: 1.05V 101:1V 100:0.95V 011: 0.9V 010: 0.85V 001: 0.8V 000: 0.75V */
#define AON_SHIFT_XTAL_WAIT_CYC                      20
#define AON_MASK_XTAL_WAIT_CYC                       ((u32)0x0000003F << 20)                             /*!<R/W 000011  Next state wait cycle, 83ns/unit */
#define AON_SHIFT_XTAL_LDO_OK                        17
#define AON_MASK_XTAL_LDO_OK                         ((u32)0x00000007 << 17)                             /*!<R/W 011  (after oscillation) X11: 1.3V X10: 1.2V X01:1.1V X00:0.9V XTAL_LDO_OK<2>: no use  */
#define AON_SHIFT_XTAL_MD_LPOW                       16
#define AON_BIT_XTAL_MD_LPOW                         ((u32)0x00000001 << 16)                             /*!<R/W 0  XTAL mode decoder low power mode 1: gated input clock */
#define AON_SHIFT_XTAL_OV_RATIO                      14
#define AON_MASK_XTAL_OV_RATIO                       ((u32)0x00000003 << 14)                             /*!<R/W 01  overlap unit times (4M ring) 00: 128us 01: 256us 10: 512us 11: 1024us */
#define AON_SHIFT_XTAL_OV_UNIT                       11
#define AON_MASK_XTAL_OV_UNIT                        ((u32)0x00000007 << 11)                             /*!<R/W 011  overlap time settling cycles (4M ring) 000: 2us 001: 4us 010: 8us 011: 16us 100: 32us 101: 64us 110: 128us 111: 256us */
#define AON_SHIFT_XTAL_MODE_MANUAL                   9
#define AON_MASK_XTAL_MODE_MANUAL                    ((u32)0x00000003 << 9)                              /*!<R/W 11  01: LPS mode 10: Normal mode 11: high performance mode */
#define AON_SHIFT_XTAL_MANU_SEL                      8
#define AON_BIT_XTAL_MANU_SEL                        ((u32)0x00000001 << 8)                              /*!<R/W 0  1: enable xtal mode manual */
#define AON_SHIFT_POW_XTAL_LPS                       7
#define AON_BIT_POW_XTAL_LPS                         ((u32)0x00000001 << 7)                              /*!<R/W 0  POW_XTAL_LPS */
#define AON_SHIFT_XTAL_MODE                          6
#define AON_BIT_XTAL_MODE                            ((u32)0x00000001 << 6)                              /*!<R/W 1  xtal mode define: 0: LPS mode 1: high performance mode */
#define AON_SHIFT_XDECODE_RESET_N                    5
#define AON_BIT_XDECODE_RESET_N                      ((u32)0x00000001 << 5)                              /*!<R/W 1  Decoder digital circuit reset (low to high) */
#define AON_SHIFT_PK_END_AR                          3
#define AON_MASK_PK_END_AR                           ((u32)0x00000003 << 3)                              /*!<R/W 11  AAC peak sel end (star>end) */
#define AON_SHIFT_PK_START_AR                        1
#define AON_MASK_PK_START_AR                         ((u32)0x00000003 << 1)                              /*!<R/W 11  AACK peak sel start (star>end) */
#define AON_SHIFT_XAAC_LUT_MANUAL_EN                 0
#define AON_BIT_XAAC_LUT_MANUAL_EN                   ((u32)0x00000001 << 0)                              /*!<R/W 0  1: enable LUT data: GM_MANUAL<4:0> , sel: AAC_MODE<1:0> */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_XTAL_CLK_CTRL7
 * @brief                                            (@ 0X078)
 * @{
 *****************************************************************************/
#define AON_SHIFT_XTAL_LPS_CAP_CTRL                  30
#define AON_BIT_XTAL_LPS_CAP_CTRL                    ((u32)0x00000001 << 30)                             /*!<R/W 1  1:cap step control */
#define AON_SHIFT_XTAL_LPS_CAP_STEP                  28
#define AON_MASK_XTAL_LPS_CAP_STEP                   ((u32)0x00000003 << 28)                             /*!<R/W 10  00:1 step/01:2 step/10:4 step /11:8 step */
#define AON_SHIFT_XTAL_LPS_CAP_CYC                   26
#define AON_MASK_XTAL_LPS_CAP_CYC                    ((u32)0x00000003 << 26)                             /*!<R/W 01  00:8u/01:16u/10:32u/11:64u */
#define AON_SHIFT_XMD_SEL                            24
#define AON_MASK_XMD_SEL                             ((u32)0x00000003 << 24)                             /*!<R/W 10  00:100K/01:500K/10:4M/11:12M */
#define AON_SHIFT_SCAN_MODE_XMD                      23
#define AON_BIT_SCAN_MODE_XMD                        ((u32)0x00000001 << 23)                             /*!<R/W 0  1:scan mode */
#define AON_SHIFT_PDCK_LPOW                          22
#define AON_BIT_PDCK_LPOW                            ((u32)0x00000001 << 22)                             /*!<R/W 0  PDCK low power mode, 1:gating input clk Set to 1 when PDCK finished */
#define AON_SHIFT_XPDCK_VREF_SEL                     17
#define AON_MASK_XPDCK_VREF_SEL                      ((u32)0x0000001F << 17)                             /*!<R/W 00011  PDCK calibrated result +offset For AAC robust +3 */
#define AON_SHIFT_XTAL_PDCK_UNIT                     15
#define AON_MASK_XTAL_PDCK_UNIT                      ((u32)0x00000003 << 15)                             /*!<R/W 01  PDCK settling cycles (4M CLK) 00: 4us 01: 8us 10: 16us 11: 32us */
#define AON_SHIFT_VREF_INIT                          10
#define AON_MASK_VREF_INIT                           ((u32)0x0000001F << 10)                             /*!<R/W 11111  PDCK VREF initial setting */
#define AON_SHIFT_VREF_MANUAL                        5
#define AON_MASK_VREF_MANUAL                         ((u32)0x0000001F << 5)                              /*!<R/W 11111  VREF manual at EN_XTAL_PDCK_DIGI=0 */
#define AON_SHIFT_PDCK_WAIT_CYC                      3
#define AON_MASK_PDCK_WAIT_CYC                       ((u32)0x00000003 << 3)                              /*!<R/W 01  Enable PDCK waiting (4M CLK) 00: 64us 01:128us 10:256us 11:512us */
#define AON_SHIFT_PDCK_SEARCH_MODE                   2
#define AON_BIT_PDCK_SEARCH_MODE                     ((u32)0x00000001 << 2)                              /*!<R/W 0  0: binary search, 1: full search from 31  */
#define AON_SHIFT_EN_XTAL_PDCK_DIGI                  1
#define AON_BIT_EN_XTAL_PDCK_DIGI                    ((u32)0x00000001 << 1)                              /*!<R/W 0  Default set 0 due to POW_XTAL will 1 before do PDCK */
#define AON_SHIFT_PDCK_RESET_N                       0
#define AON_BIT_PDCK_RESET_N                         ((u32)0x00000001 << 0)                              /*!<R/W 0  PDCK digital circuit reset (low to high) */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SRC_CLK_CTRL
 * @brief                                            (@ 0X07C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_LP_CLK_SEL                         26
#define AON_MASK_LP_CLK_SEL                          ((u32)0x00000007 << 26)                             /*!<R/W 000  32K clock source of WLON selection b'000: OSC 32K (32K output of OSC 128K) b'001: OSC 128K with SDM b'011: XTAL (high speed) with divider b'100: XTAL 32K others: rsvd */
#define AON_SHIFT_TIMER_SCLK_SEL                     4
#define AON_BIT_TIMER_SCLK_SEL                       ((u32)0x00000001 << 4)                              /*!<R/W 0  0: AON LP 32K clock source 1: ANACLK 100KHz */
#define AON_SHIFT_COMP_SCLK_SEL                      3
#define AON_BIT_COMP_SCLK_SEL                        ((u32)0x00000001 << 3)                              /*!<R/W 0  0: AON LP 32K clock source 1: OSC 128K/4(without SDM?) */
#define AON_SHIFT_GPIO_SCLK_SEL                      2
#define AON_BIT_GPIO_SCLK_SEL                        ((u32)0x00000001 << 2)                              /*!<R/W 0  0: AON LP 32K clock source 1: OSC 128K/4(without SDM?) */
#define AON_SHIFT_XTAL_DIVIDER_EN                    0
#define AON_BIT_XTAL_DIVIDER_EN                      ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable XTAL divider */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_CLK_STS
 * @brief                                            (@ 0X080)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_ANA4M_CLK_RDY                      3
#define AON_BIT_ANA4M_CLK_RDY                        ((u32)0x00000001 << 3)                              /*!<R 0  OSC4MHz Clock Ready */
#endif
#define AON_SHIFT_REGU_CLK_RDY                       2
#define AON_BIT_REGU_CLK_RDY                         ((u32)0x00000001 << 2)                              /*!<R 1  Regulator Clock 100KHz Clock Ready */
#define AON_SHIFT_32KXTAL_RDY                        1
#define AON_BIT_32KXTAL_RDY                          ((u32)0x00000001 << 1)                              /*!<R 0  32KHz XTALClock Ready */
#define AON_SHIFT_XTAL_RDY                           0
#define AON_BIT_XTAL_RDY                             ((u32)0x00000001 << 0)                              /*!<R 0  High performance XTALClock Ready */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_WAKE_TIMER
 * @brief                                            (@ 0X084)
 * @{
 *****************************************************************************/
#define AON_SHIFT_WAKE_TM_EN                         31
#define AON_BIT_WAKE_TM_EN                           ((u32)0x00000001 << 31)                             /*!<R/W 0  AON wake timer Enable */
#define AON_SHIFT_TIMER_ISR                          30
#define AON_BIT_TIMER_ISR                            ((u32)0x00000001 << 30)                             /*!<R/W1C 0  1: Indicate AON Timer Interrupt Status */
#define AON_SHIFT_WAKE_TM_TC                         0
#define AON_MASK_WAKE_TM_TC                          ((u32)0x3FFFFFFF << 0)                              /*!<R/W 0  AON wake timer counter value */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_PLL_CTRL0
 * @brief                                            (@ 0X088)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SETTLE_TIME_FACTOR                 24
#define AON_MASK_SETTLE_TIME_FACTOR                  ((u32)0x00000003 << 24)                             /*!<R/W 0  0: delay *1, 1:delay *2, 2: delay *4, 3:delay *8 */
#define AON_SHIFT_SW_LDO2PWRCUT                      23
#define AON_BIT_SW_LDO2PWRCUT                        ((u32)0x00000001 << 23)                             /*!<R/W 0  0: LDO 1: power cut */
#define AON_SHIFT_SW_LDO_OUT                         21
#define AON_MASK_SW_LDO_OUT                          ((u32)0x00000003 << 21)                             /*!<R/W 01  00/01/10/11 0.85/0.9/0.95/1 */
#define AON_SHIFT_VPULSE_LDO                         20
#define AON_BIT_VPULSE_LDO                           ((u32)0x00000001 << 20)                             /*!<R/W 1   */
#define AON_SHIFT_POW_LDO09                          19
#define AON_BIT_POW_LDO09                            ((u32)0x00000001 << 19)                             /*!<R/W 0  Power on 13to09 LDO */
#define AON_SHIFT_VSET_1_0                           17
#define AON_MASK_VSET_1_0                            ((u32)0x00000003 << 17)                             /*!<R/W 01   */
#define AON_SHIFT_POW_LDO18                          16
#define AON_BIT_POW_LDO18                            ((u32)0x00000001 << 16)                             /*!<R/W 0  Power on 33to18 LDO */
#define AON_SHIFT_PLL_CTRL0_DUMMY_0                  15
#define AON_BIT_PLL_CTRL0_DUMMY_0                    ((u32)0x00000001 << 15)                             /*!<R/W 0   */
#define AON_SHIFT_PLL_VR1200_TUNE_2_0                12
#define AON_MASK_PLL_VR1200_TUNE_2_0                 ((u32)0x00000007 << 12)                             /*!<R/W 100  Add 40k per step fine tune BG */
#define AON_SHIFT_PLL_CTRL0_DUMMY_1                  11
#define AON_BIT_PLL_CTRL0_DUMMY_1                    ((u32)0x00000001 << 11)                             /*!<R/W 0   */
#define AON_SHIFT_PLL_R2_TUNE_2_0                    8
#define AON_MASK_PLL_R2_TUNE_2_0                     ((u32)0x00000007 << 8)                              /*!<R/W 100  Add 20k per step fine tune BG */
#define AON_SHIFT_PLL_CTRL0_DUMMY_2                  7
#define AON_BIT_PLL_CTRL0_DUMMY_2                    ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define AON_SHIFT_PLL_R1_TUNE_2_0                    4
#define AON_MASK_PLL_R1_TUNE_2_0                     ((u32)0x00000007 << 4)                              /*!<R/W 100  Add 200k per step fine tune BG */
#define AON_SHIFT_PLL_CTRL0_DUMMY_3                  3
#define AON_BIT_PLL_CTRL0_DUMMY_3                    ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define AON_SHIFT_PLL_POW_MBIAS                      2
#define AON_BIT_PLL_POW_MBIAS                        ((u32)0x00000001 << 2)                              /*!<R/W 0  power on mbias */
#define AON_SHIFT_PLL_POW_I                          1
#define AON_BIT_PLL_POW_I                            ((u32)0x00000001 << 1)                              /*!<R/W 0  power on BG current */
#define AON_SHIFT_PLL_POW_BG                         0
#define AON_BIT_PLL_POW_BG                           ((u32)0x00000001 << 0)                              /*!<R/W 0  power on BG */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SD_CTRL0
 * @brief                                            (@ 0X08C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SD_CTRL0_DUMMY_0                   18
#define AON_MASK_SD_CTRL0_DUMMY_0                    ((u32)0x00000003 << 18)                             /*!<R/W 00   */
#define AON_SHIFT_SD_VOS_L                           15
#define AON_MASK_SD_VOS_L                            ((u32)0x00000007 << 15)                             /*!<R/W 011  Offset tunning for comparator */
#define AON_SHIFT_SD_VOS_H                           12
#define AON_MASK_SD_VOS_H                            ((u32)0x00000007 << 12)                             /*!<R/W 011  Offset tunning for comparator */
#define AON_SHIFT_SEL_VREFL                          7
#define AON_MASK_SEL_VREFL                           ((u32)0x0000001F << 7)                              /*!<R/W 00000  vref low voltage 0000:25mV, 25mV/step */
#define AON_SHIFT_SEL_VREFH                          2
#define AON_MASK_SEL_VREFH                           ((u32)0x0000001F << 2)                              /*!<R/W 00000  vref high voltage 0000:25mV, 25mV/step */
#define AON_SHIFT_SD_POSEDGE                         1
#define AON_BIT_SD_POSEDGE                           ((u32)0x00000001 << 1)                              /*!<R/W 1  1: vin>vref output high */
#define AON_SHIFT_POW_SD                             0
#define AON_BIT_POW_SD                               ((u32)0x00000001 << 0)                              /*!<R/W 0  Power on signal detector */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_PAD_CTRL
 * @brief                                            (@ 0X090)
 * @{
 *****************************************************************************/
#define AON_SHIFT_PON_GPIO_WDT_RST_MSK               9
#define AON_BIT_PON_GPIO_WDT_RST_MSK                 ((u32)0x00000001 << 9)                              /*!<R/W 0  1: Mask this bit and then WDOG_RST and CPU_RST can reset PON GPIO block */
#define AON_SHIFT_SYSON_GPIO_WDT_RST_MSK             8
#define AON_BIT_SYSON_GPIO_WDT_RST_MSK               ((u32)0x00000001 << 8)                              /*!<R/W 0  1: Mask this bit and then WDOG_RST and CPU_RST can reset SYSON GPIO block */
#define AON_SHIFT_AON_GPIO_WDT_RST_MSK               7
#define AON_BIT_AON_GPIO_WDT_RST_MSK                 ((u32)0x00000001 << 7)                              /*!<R/W 0  1: Mask this bit and then WDOG_RST and CPU_RST can reset AON GPIO block */
#define AON_SHIFT_SYSON_GPIOS_PWD33                  6
#define AON_BIT_SYSON_GPIOS_PWD33                    ((u32)0x00000001 << 6)                              /*!<R/W 1  1: power down GPIOS */
#define AON_SHIFT_PON_GPIOF_PWD33                    5
#define AON_BIT_PON_GPIOF_PWD33                      ((u32)0x00000001 << 5)                              /*!<R/W 1  1: power down GPIOF */
#define AON_SHIFT_SYSON_GPIOE_PWD33                  4
#define AON_BIT_SYSON_GPIOE_PWD33                    ((u32)0x00000001 << 4)                              /*!<R/W 1  1: power down GPIOE */
#define AON_SHIFT_SYSON_GPIOD_PWD33                  3
#define AON_BIT_SYSON_GPIOD_PWD33                    ((u32)0x00000001 << 3)                              /*!<R/W 1  1: power down GPIOD */
#define AON_SHIFT_SYSON_GPIOC_PWD33                  2
#define AON_BIT_SYSON_GPIOC_PWD33                    ((u32)0x00000001 << 2)                              /*!<R/W 1  1: power down GPIOC */
#define AON_SHIFT_SYSON_GPIOB_PWD33                  1
#define AON_BIT_SYSON_GPIOB_PWD33                    ((u32)0x00000001 << 1)                              /*!<R/W 1  1: power down GPIOB */
#define AON_SHIFT_AON_GPIOA_PWD33                    0
#define AON_BIT_AON_GPIOA_PWD33                      ((u32)0x00000001 << 0)                              /*!<R/W 0  1: power down GPIOA */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_GPIOA_0_1_CTRL
 * @brief                                            (@ 0X094)
 * @{
 *****************************************************************************/
#define AON_SHIFT_AON_GPIO1_SLEW_RATE                28
#define AON_BIT_AON_GPIO1_SLEW_RATE                  ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define AON_SHIFT_AON_GPIO1_DRIVING                  26
#define AON_MASK_AON_GPIO1_DRIVING                   ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define AON_SHIFT_AON_GPIO1_SMT_EN                   25
#define AON_BIT_AON_GPIO1_SMT_EN                     ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable AON GPIO1 Schmitt trigger; 1: enable */
#define AON_SHIFT_AON_GPIO1_PULL_CTRL                22
#define AON_MASK_AON_GPIO1_PULL_CTRL                 ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define AON_SHIFT_AON_GPIO1_PINMUX_SEL               16
#define AON_MASK_AON_GPIO1_PINMUX_SEL                ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: Comparator_ADC 0001: I2C0_SDA 0010: 0011:JTAG_CLK/SWD_CK 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define AON_SHIFT_AON_GPIO0_SLEW_RATE                12
#define AON_BIT_AON_GPIO0_SLEW_RATE                  ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define AON_SHIFT_AON_GPIO0_DRIVING                  10
#define AON_MASK_AON_GPIO0_DRIVING                   ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define AON_SHIFT_AON_GPIO0_SMT_EN                   9
#define AON_BIT_AON_GPIO0_SMT_EN                     ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable AON GPIO0 Schmitt trigger; 1: enable */
#define AON_SHIFT_AON_GPIO0_PULL_CTRL                6
#define AON_MASK_AON_GPIO0_PULL_CTRL                 ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define AON_SHIFT_AON_GPIO0_PINMUX_SEL               0
#define AON_MASK_AON_GPIO0_PINMUX_SEL                ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: Comparator_ADC 0001: I2C0_SCL 0010: 0011: JTAG_TMS/SWD_IO 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_GPIOA_2_3_CTRL
 * @brief                                            (@ 0X098)
 * @{
 *****************************************************************************/
#define AON_SHIFT_AON_GPIO3_SLEW_RATE                28
#define AON_BIT_AON_GPIO3_SLEW_RATE                  ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define AON_SHIFT_AON_GPIO3_DRIVING                  26
#define AON_MASK_AON_GPIO3_DRIVING                   ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define AON_SHIFT_AON_GPIO3_SMT_EN                   25
#define AON_BIT_AON_GPIO3_SMT_EN                     ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable AON GPIO3 Schmitt trigger; 1: enable */
#define AON_SHIFT_AON_GPIO3_PULL_CTRL                22
#define AON_MASK_AON_GPIO3_PULL_CTRL                 ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define AON_SHIFT_AON_GPIO3_PINMUX_SEL               16
#define AON_MASK_AON_GPIO3_PINMUX_SEL                ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000:Comparator_ADC 0001: SIC_SDA 0010: 0011: 0100: 0101: 0110: UART0_IN 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define AON_SHIFT_AON_GPIO2_SLEW_RATE                12
#define AON_BIT_AON_GPIO2_SLEW_RATE                  ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define AON_SHIFT_AON_GPIO2_DRIVING                  10
#define AON_MASK_AON_GPIO2_DRIVING                   ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define AON_SHIFT_AON_GPIO2_SMT_EN                   9
#define AON_BIT_AON_GPIO2_SMT_EN                     ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable AON GPIO2 Schmitt trigger; 1: enable */
#define AON_SHIFT_AON_GPIO2_PULL_CTRL                6
#define AON_MASK_AON_GPIO2_PULL_CTRL                 ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define AON_SHIFT_AON_GPIO2_PINMUX_SEL               0
#define AON_MASK_AON_GPIO2_PINMUX_SEL                ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: Comparator_ADC 0001: SIC_SCL 0010: 0011: 0100: 0101: 0110: UART0_OUT 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_GPIOA_4_5_CTRL
 * @brief                                            (@ 0X09C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_AON_GPIO5_SLEW_RATE                28
#define AON_BIT_AON_GPIO5_SLEW_RATE                  ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define AON_SHIFT_AON_GPIO5_DRIVING                  26
#define AON_MASK_AON_GPIO5_DRIVING                   ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define AON_SHIFT_AON_GPIO5_SMT_EN                   25
#define AON_BIT_AON_GPIO5_SMT_EN                     ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable AON GPIO5 Schmitt trigger; 1: enable */
#define AON_SHIFT_AON_GPIO5_PULL_CTRL                22
#define AON_MASK_AON_GPIO5_PULL_CTRL                 ((u32)0x00000003 << 22)                             /*!<R/W 1  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define AON_SHIFT_AON_GPIO5_PINMUX_SEL               16
#define AON_MASK_AON_GPIO5_PINMUX_SEL                ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000:VP_LOW 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define AON_SHIFT_AON_GPIO4_SLEW_RATE                12
#define AON_BIT_AON_GPIO4_SLEW_RATE                  ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define AON_SHIFT_AON_GPIO4_DRIVING                  10
#define AON_MASK_AON_GPIO4_DRIVING                   ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define AON_SHIFT_AON_GPIO4_SMT_EN                   9
#define AON_BIT_AON_GPIO4_SMT_EN                     ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable AON GPIO4 Schmitt trigger; 1: enable */
#define AON_SHIFT_AON_GPIO4_PULL_CTRL                6
#define AON_MASK_AON_GPIO4_PULL_CTRL                 ((u32)0x00000003 << 6)                              /*!<R/W 1  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define AON_SHIFT_AON_GPIO4_PINMUX_SEL               0
#define AON_MASK_AON_GPIO4_PINMUX_SEL                ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000:VP_HIGH 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_IO1_RSVD
 * @brief                                            (@ 0X0A0)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SW0                                0
#define AON_MASK_SW0                                 ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Reserve for SW DBG */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_IO2_RSVD
 * @brief                                            (@ 0X0A4)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SW1                                0
#define AON_MASK_SW1                                 ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Reserve for SW DBG */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_LSFIF_CMD
 * @brief                                            (@ 0X0A8)
 * @{
 *****************************************************************************/
#define AON_SHIFT_AON_LSFIF_POLL                     31
#define AON_BIT_AON_LSFIF_POLL                       ((u32)0x00000001 << 31)                             /*!<R/W 0  LSF (low speed function) register access polling bit. Set this bit to do LSF register read or write transfer depend on BIT_AON_LSFIF_WR. When transfer done, this bit will be clear by HW */
#define AON_SHIFT_LSF_SEL                            28
#define AON_MASK_LSF_SEL                             ((u32)0x00000007 << 28)                             /*!<R/W 0  000: RTC 001: OSC32K SDM 010: XTAL (high speed) with divider 011: AON Comparator 100: RSVD */
#define AON_SHIFT_AON_LSFIF_WR                       27
#define AON_BIT_AON_LSFIF_WR                         ((u32)0x00000001 << 27)                             /*!<R/W 0  LSF register write transfer indicator.1: LSF register write transfer, 0: LSF register read transfer */
#define AON_SHIFT_AON_LSFIF_WE                       23
#define AON_MASK_AON_LSFIF_WE                        ((u32)0x0000000F << 23)                             /*!<R/W 0  LSF register byte write enable. This field is valid during LSF register write transfer, and is ignored during LSF register read transfer */
#define AON_SHIFT_LSFIF_CMD_DUMMY_0                  16
#define AON_MASK_LSFIF_CMD_DUMMY_0                   ((u32)0x0000007F << 16)                             /*!<R/W 0  Dummy */
#define AON_SHIFT_AON_LSFIF_AD                       0
#define AON_MASK_AON_LSFIF_AD                        ((u32)0x0000FFFF << 0)                              /*!<R/W 0  LSF register access address. BIT_AON_LSFIF_AD[15:8]=8'h00: Indirect register base address */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_LSFIF_RWD
 * @brief                                            (@ 0X0AC)
 * @{
 *****************************************************************************/
#define AON_SHIFT_AON_LSFIF_RWD                      0
#define AON_MASK_AON_LSFIF_RWD                       ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  LSF(low speed function) write */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_TEST_MUX_CTRL
 * @brief                                            (@ 0X0B0)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_TEST3                              25
#define AON_MASK_TEST3                               ((u32)0x0000007F << 25)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_SDIO_HOST_TEST_MUX_EN              24
#define AON_BIT_SDIO_HOST_TEST_MUX_EN                ((u32)0x00000001 << 24)                             /*!<R/W 0  1: enable SDIO HOST test mux */
#define AON_SHIFT_SD_HOST_TEST_MUX_EN                23
#define AON_BIT_SD_HOST_TEST_MUX_EN                  ((u32)0x00000001 << 23)                             /*!<R/W 0  1: enable SD HOST test mux */
#define AON_SHIFT_ETHERNET_TEST_MUX_EN               22
#define AON_BIT_ETHERNET_TEST_MUX_EN                 ((u32)0x00000001 << 22)                             /*!<R/W 0  1: enable Ethernet PHY test mux */
#define AON_SHIFT_AUDIO_TEST_MUX_EN                  21
#define AON_BIT_AUDIO_TEST_MUX_EN                    ((u32)0x00000001 << 21)                             /*!<R/W 0  1: enable AUDIO CODEC test mux */
#define AON_SHIFT_PLL_TEST_MUX_EN                    20
#define AON_BIT_PLL_TEST_MUX_EN                      ((u32)0x00000001 << 20)                             /*!<R/W 0  1: enable PLL test mux */
#define AON_SHIFT_AUX_TEST_MUX_EN                    19
#define AON_BIT_AUX_TEST_MUX_EN                      ((u32)0x00000001 << 19)                             /*!<R/W 0  1: enable AUX test mux */
#define AON_SHIFT_RSVD                               18
#define AON_BIT_RSVD                                 ((u32)0x00000001 << 18)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_WL_BT_RF_TEST_MUX_EN               17
#define AON_BIT_WL_BT_RF_TEST_MUX_EN                 ((u32)0x00000001 << 17)                             /*!<R/W 0  1: enable WLAN BT RF test mux */
#define AON_SHIFT_REGU_TEST_MUX_EN                   16
#define AON_BIT_REGU_TEST_MUX_EN                     ((u32)0x00000001 << 16)                             /*!<R/W 0  1: enable REGU test mux */
#define AON_SHIFT_TEST2                              9
#define AON_MASK_TEST2                               ((u32)0x0000007F << 9)                              /*!<R/W 0  RSVD */
#define AON_SHIFT_MBIST_EN                           8
#define AON_BIT_MBIST_EN                             ((u32)0x00000001 << 8)                              /*!<R/W 0  1: enable MBIST test mux */
#define AON_SHIFT_TEST1                              3
#define AON_MASK_TEST1                               ((u32)0x0000001F << 3)                              /*!<R/W 0  RSVD */
#define AON_SHIFT_SCAN_MOD2_EN                       2
#define AON_BIT_SCAN_MOD2_EN                         ((u32)0x00000001 << 2)                              /*!<R/W 0  1: enable FT2 scan test mux */
#define AON_SHIFT_SCAN_MOD1_EN                       1
#define AON_BIT_SCAN_MOD1_EN                         ((u32)0x00000001 << 1)                              /*!<R/W 0  1: enable FT1 scan test mux */
#define AON_SHIFT_SCAN_MOD0_EN                       0
#define AON_BIT_SCAN_MOD0_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 0  1: enable CP scan test mux */
#else
#define AON_SHIFT_TEST_MOD31_EN                      31
#define AON_BIT_TEST_MOD31_EN                        ((u32)0x00000001 << 31)                             /*!<R/W 0  1: enable test mode 31 mux */
#define AON_SHIFT_TEST_MOD30_EN                      30
#define AON_BIT_TEST_MOD30_EN                        ((u32)0x00000001 << 30)                             /*!<R/W 0  1: enable test mode 30 mux */
#define AON_SHIFT_TEST_MOD29_EN                      29
#define AON_BIT_TEST_MOD29_EN                        ((u32)0x00000001 << 29)                             /*!<R/W 0  1: enable test mode 29 mux */
#define AON_SHIFT_TEST_MOD28_EN                      28
#define AON_BIT_TEST_MOD28_EN                        ((u32)0x00000001 << 28)                             /*!<R/W 0  1: enable test mode 28 mux */
#define AON_SHIFT_TEST_MOD27_EN                      27
#define AON_BIT_TEST_MOD27_EN                        ((u32)0x00000001 << 27)                             /*!<R/W 0  1: enable test mode 27 mux */
#define AON_SHIFT_TEST_MOD26_EN                      26
#define AON_BIT_TEST_MOD26_EN                        ((u32)0x00000001 << 26)                             /*!<R/W 0  1: enable test mode 26 mux */
#define AON_SHIFT_TEST_MOD25_EN                      25
#define AON_BIT_TEST_MOD25_EN                        ((u32)0x00000001 << 25)                             /*!<R/W 0  1: enable test mode 25 mux */
#define AON_SHIFT_SDIO_HOST_TEST_MUX_EN              24
#define AON_BIT_SDIO_HOST_TEST_MUX_EN                ((u32)0x00000001 << 24)                             /*!<R/W 0  1: enable SDIO HOST test mux */
#define AON_SHIFT_SD_HOST_TEST_MUX_EN                23
#define AON_BIT_SD_HOST_TEST_MUX_EN                  ((u32)0x00000001 << 23)                             /*!<R/W 0  1: enable SD HOST test mux */
#define AON_SHIFT_ETHERNET_TEST_MUX_EN               22
#define AON_BIT_ETHERNET_TEST_MUX_EN                 ((u32)0x00000001 << 22)                             /*!<R/W 0  1: enable Ethernet PHY test mux */
#define AON_SHIFT_AUDIO_TEST_MUX_EN                  21
#define AON_BIT_AUDIO_TEST_MUX_EN                    ((u32)0x00000001 << 21)                             /*!<R/W 0  1: enable AUDIO CODEC test mux */
#define AON_SHIFT_PLL_TEST_MUX_EN                    20
#define AON_BIT_PLL_TEST_MUX_EN                      ((u32)0x00000001 << 20)                             /*!<R/W 0  1: enable PLL test mux */
#define AON_SHIFT_AUX_TEST_MUX_EN                    19
#define AON_BIT_AUX_TEST_MUX_EN                      ((u32)0x00000001 << 19)                             /*!<R/W 0  1: enable AUX test mux */
#define AON_SHIFT_RSVD                               18
#define AON_BIT_RSVD                                 ((u32)0x00000001 << 18)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_WL_BT_RF_TEST_MUX_EN               17
#define AON_BIT_WL_BT_RF_TEST_MUX_EN                 ((u32)0x00000001 << 17)                             /*!<R/W 0  1: enable WLAN BT RF test mux */
#define AON_SHIFT_REGU_TEST_MUX_EN                   16
#define AON_BIT_REGU_TEST_MUX_EN                     ((u32)0x00000001 << 16)                             /*!<R/W 0  1: enable REGU test mux */
#define AON_SHIFT_TEST_MOD15_EN                      15
#define AON_BIT_TEST_MOD15_EN                        ((u32)0x00000001 << 15)                             /*!<R/W 0  1: enable test mode 15 mux */
#define AON_SHIFT_TEST_MOD14_EN                      14
#define AON_BIT_TEST_MOD14_EN                        ((u32)0x00000001 << 14)                             /*!<R/W 0  1: enable test mode 14 mux */
#define AON_SHIFT_TEST_MOD13_EN                      13
#define AON_BIT_TEST_MOD13_EN                        ((u32)0x00000001 << 13)                             /*!<R/W 0  1: enable test mode 13 mux */
#define AON_SHIFT_TEST_MOD12_EN                      12
#define AON_BIT_TEST_MOD12_EN                        ((u32)0x00000001 << 12)                             /*!<R/W 0  1: enable test mode 12 mux */
#define AON_SHIFT_TEST_MOD11_EN                      11
#define AON_BIT_TEST_MOD11_EN                        ((u32)0x00000001 << 11)                             /*!<R/W 0  1: enable test mode 11 mux */
#define AON_SHIFT_TEST_MOD10_EN                      10
#define AON_BIT_TEST_MOD10_EN                        ((u32)0x00000001 << 10)                             /*!<R/W 0  1: enable test mode 10 mux */
#define AON_SHIFT_TEST_MOD9_EN                       9
#define AON_BIT_TEST_MOD9_EN                         ((u32)0x00000001 << 9)                              /*!<R/W 0  1: enable test mode 9 mux */
#define AON_SHIFT_TEST_MOD8_EN                       8
#define AON_BIT_TEST_MOD8_EN                         ((u32)0x00000001 << 8)                              /*!<R/W 0  1: enable test mode 8 mux */
#define AON_SHIFT_TEST_MOD7_EN                       7
#define AON_BIT_TEST_MOD7_EN                         ((u32)0x00000001 << 7)                              /*!<R/W 0  1: enable test mode 7 mux */
#define AON_SHIFT_TEST_MOD6_EN                       6
#define AON_BIT_TEST_MOD6_EN                         ((u32)0x00000001 << 6)                              /*!<R/W 0  1: enable test mode 6 mux */
#define AON_SHIFT_SCAN_MOD5_EN                       5
#define AON_BIT_SCAN_MOD5_EN                         ((u32)0x00000001 << 5)                              /*!<R/W 0  1: enable FT3 scan test mux */
#define AON_SHIFT_SCAN_MOD4_EN                       4
#define AON_BIT_SCAN_MOD4_EN                         ((u32)0x00000001 << 4)                              /*!<R/W 0  1: enable FT2 scan test mux */
#define AON_SHIFT_SCAN_MOD3_EN                       3
#define AON_BIT_SCAN_MOD3_EN                         ((u32)0x00000001 << 3)                              /*!<R/W 0  1: enable FT1 scan test mux */
#define AON_SHIFT_SCAN_MOD2_EN                       2
#define AON_BIT_SCAN_MOD2_EN                         ((u32)0x00000001 << 2)                              /*!<R/W 0  1: enable FT0 scan test mux */
#define AON_SHIFT_SCAN_MOD1_EN                       1
#define AON_BIT_SCAN_MOD1_EN                         ((u32)0x00000001 << 1)                              /*!<R/W 0  1: enable CP1 scan test mux */
#define AON_SHIFT_SCAN_MOD0_EN                       0
#define AON_BIT_SCAN_MOD0_EN                         ((u32)0x00000001 << 0)                              /*!<R/W 0  1: enable CP0 scan test mux */
#endif
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_WDT_TIMER
 * @brief                                            (@ 0X0B4)
 * @{
 *****************************************************************************/
#define AON_SHIFT_RSVD1                              17
#define AON_MASK_RSVD1                               ((u32)0x00007FFF << 17)                             /*!<R 0   */
#define AON_SHIFT_CNT                                1
#define AON_MASK_CNT                                 ((u32)0x0000FFFF << 1)                              /*!<R/W 0xFFF  WDT Counter value */
#define AON_SHIFT_WDT_EN_BYTE                        0
#define AON_BIT_WDT_EN_BYTE                          ((u32)0x00000001 << 0)                              /*!<R/W 1  Set 1 to enable watch dog timer */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_TEST_MUX_CTRL1
 * @brief                                            (@ 0X0B8)
 * @{
 *****************************************************************************/
#define AON_SHIFT_TEST                               0
#define AON_MASK_TEST                                ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_ATLOAD_CTRL1
 * @brief                                            (@ 0X0BC)
 * @{
 *****************************************************************************/
#define AON_SHIFT_OTP1                               16
#define AON_MASK_OTP1                                ((u32)0x0000FFFF << 16)                             /*!<R/W 0  For OTP Use */
#define AON_SHIFT_OTP0                               13
#define AON_MASK_OTP0                                ((u32)0x00000007 << 13)                             /*!<R/W 0  For OTP Use */
#define AON_SHIFT_AON_OTP_IND_ACCESS_EN              12
#define AON_BIT_AON_OTP_IND_ACCESS_EN                ((u32)0x00000001 << 12)                             /*!<R/W Once 1  This bit is the control bit for AON OTP indirect access 1: Enable that master(CPU/SIC) can access OTP via AON OTP indirect access. (Default) 0: Disable that master(CPU/SIC) cannot access OTP via AON OTP indirect access. This register just can be written once. After that, hardware need disable the writing function. */
#define AON_SHIFT_JTAG_OTP_KEY_SELECT                10
#define AON_MASK_JTAG_OTP_KEY_SELECT                 ((u32)0x00000003 << 10)                             /*!<R/W Once 11  Secure JTAG OTP Key select. The first bit (Bit 10) determines which Secure Key pair is used. 1: Secure Key 1 (Default) 0: Secure Key 2 The last bit (Bit 11) determines which Non-Secure Key pair is used. 1: Non-Secure Key 1 (Default) 0: Non-Secure Key 2 This register just can be written once. After that, hardware need disable the writing function. */
#define AON_SHIFT_NS_JTAG_SWD_MODE                   8
#define AON_MASK_NS_JTAG_SWD_MODE                    ((u32)0x00000003 << 8)                              /*!<R/W Once 11  3(Default): Enable non-secure world JTAG/SWD 2: RSVD 1: Enable password non-secure world JTAG/SWD 0: disable non-secure world JTAG/SWD This register just can be written once. After that, hardware need disable the writing function. */
#define AON_SHIFT_S_JTAG_SWD_MODE                    6
#define AON_MASK_S_JTAG_SWD_MODE                     ((u32)0x00000003 << 6)                              /*!<R/W Once 11  3(Default): Enable secure world JTAG/SWD 2: RSVD 1: Enable password secure world JTAG/SWD 0: disable secure world JTAG/SWD This register just can be written once. After that, hardware need disable the writing function. */
#define AON_SHIFT_FIXED_JTAG_KEY_EN                  5
#define AON_BIT_FIXED_JTAG_KEY_EN                    ((u32)0x00000001 << 5)                              /*!<R/W Once 1  0: "DAP Protection IP" cannot request "OTP Key Control" to read the OTP key. The key will be stored into register. The length of key: 256 bits. 1: "DAP Protection IP" can request "OTP Key Control" to read the OTP key. The length of key: 256 bits. (Default) This register just can be written once. After that, hardware need disable the writing function. */
#define AON_SHIFT_SIC_SECURE_DIS                     4
#define AON_BIT_SIC_SECURE_DIS                       ((u32)0x00000001 << 4)                              /*!<R/W Once 1  Secure registers can be accessed or not via SIC. 0: Disable that SIC is secure mode. It means that SIC is Non-secure master. 1: Enable that SIC is secure mode. (Default) It means that SIC is Secure master. This register just can be written once. After that, hardware need disable the writing function. */
#define AON_SHIFT_SEC_PON_DIS                        3
#define AON_BIT_SEC_PON_DIS                          ((u32)0x00000001 << 3)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for PON registers. 1: PON is Non-secure register. (Default) It means that disable secure filter check , so allow Non-secure and Secure masters can access PON registers. 0: PON is Secure register. It means that enable secure filter check, so allow only Secure masters can access PON registers. Non-secure masters access will be filtered out. This register just can be written once. After that, hardware need disable the writing function. */
#define AON_SHIFT_SEC_AON_DIS                        2
#define AON_BIT_SEC_AON_DIS                          ((u32)0x00000001 << 2)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for AON registers. 1: AON is Non-secure register. (Default) It means that disable secure filter check , so allow Non-secure and Secure masters can access AON registers. 0: AON is Secure register. It means that enable secure filter check, so allow only Secure masters can access AON registers. Non-secure masters access will be filtered out. This register just can be written once. After that, hardware need disable the writing function. */
#define AON_SHIFT_SECURE_VNDR_CHECK_DIS              1
#define AON_BIT_SECURE_VNDR_CHECK_DIS                ((u32)0x00000001 << 1)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for Vendor secure registers. 1: Disable secure filter check (Default), it means that allow Non-secure masters can access secure Vendor registers, Secure masters as well. 0: Enable secure filter check, it means that allow only Secure masters can access secure Vendor registers. Non-secure masters access will be filtered out. This register just can be written once. After that, hardware need disable the writing function. */
#define AON_SHIFT_SECURE_SYSON_CHECK_DIS             0
#define AON_BIT_SECURE_SYSON_CHECK_DIS               ((u32)0x00000001 << 0)                              /*!<R/W Once 1  This bit is the control bit of secure filter check for SYSON secure registers. 1: Disable secure filter check (Default), it means that allow Non-secure masters can access secure SYSON registers, Secure masters as well. 0: Enable secure filter check, it means that allow only Secure masters can access secure SYSON registers. Non-secure masters access will be filtered out. This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_ATLOAD_CTRL2
 * @brief                                            (@ 0X0C0)
 * @{
 *****************************************************************************/
#define AON_SHIFT_OTP2                               16
#define AON_MASK_OTP2                                ((u32)0x0000FFFF << 16)                             /*!<R/W 0  For OTP Use */
#define AON_SHIFT_EFUSE_ID1                          8
#define AON_MASK_EFUSE_ID1                           ((u32)0x000000FF << 8)                              /*!<R/W 0  Efuse ID byte1, expect ID: 0x87 */
#define AON_SHIFT_EFUSE_ID0                          0
#define AON_MASK_EFUSE_ID0                           ((u32)0x000000FF << 0)                              /*!<R/W 0  Efuse ID byte0, expect ID: 0x35 */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SYS_INFO0
 * @brief                                            (@ 0X0C4)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SYSCFG_BD_PKG_SEL                  31
#define AON_BIT_SYSCFG_BD_PKG_SEL                    ((u32)0x00000001 << 31)                             /*!<R 0  Trapped PKG_ENG_SEL value 0: normal package; 1: engineering mode */
#define AON_SHIFT_CHIP_EN                            30
#define AON_BIT_CHIP_EN                              ((u32)0x00000001 << 30)                             /*!<R 1  CHIP_EN PIN input value */
#define AON_SHIFT_BD_OPT3_                           27
#define AON_BIT_BD_OPT3_                             ((u32)0x00000001 << 27)                             /*!<R 0  Report from bonding option pin */
#define AON_SHIFT_BD_OPT2_                           26
#define AON_BIT_BD_OPT2_                             ((u32)0x00000001 << 26)                             /*!<R 0   */
#define AON_SHIFT_BD_OPT1_                           25
#define AON_BIT_BD_OPT1_                             ((u32)0x00000001 << 25)                             /*!<R 0   */
#define AON_SHIFT_BD_OPT0                            24
#define AON_BIT_BD_OPT0                              ((u32)0x00000001 << 24)                             /*!<R 0   */
#define AON_SHIFT_RSVD2                              17
#define AON_MASK_RSVD2                               ((u32)0x0000007F << 17)                             /*!<R 0   */
#define AON_SHIFT_CHIP_TYPE                          16
#define AON_BIT_CHIP_TYPE                            ((u32)0x00000001 << 16)                             /*!<R 0  1: Test chip; 0:MP */
#define AON_SHIFT_VENDOR_ID                          8
#define AON_MASK_VENDOR_ID                           ((u32)0x0000000F << 8)                              /*!<R 0101  BIT_VENDOR_ID[3:2] : Process 00: TSMC , 01: SMIC, 10: UMC BIT_VENDOR_ID[1] : rsve BIT_VENDOR_ID[0] : 0 : BT do not exist in IC 1 : BT exist in IC */
#define AON_SHIFT_CHIP_VER                           4
#define AON_MASK_CHIP_VER                            ((u32)0x0000000F << 4)                              /*!<R 0  Chip version-8735B 0000: A-cut 0001: B-cut 0010: C-cut 0011: D-cut  */
#define AON_SHIFT_RF_RL_ID                           0
#define AON_MASK_RF_RL_ID                            ((u32)0x0000000F << 0)                              /*!<R 0  Vendor ID defined in RF */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SYS_INFO1
 * @brief                                            (@ 0X0C8)
 * @{
 *****************************************************************************/
#define AON_SHIFT_RSVD3                              28
#define AON_MASK_RSVD3                               ((u32)0x0000000F << 28)                             /*!<R 0   */
#define AON_SHIFT_SYSCFG_TRP_SRCLDO_SEL              27
#define AON_BIT_SYSCFG_TRP_SRCLDO_SEL                ((u32)0x00000001 << 27)                             /*!<R 0  Trapped Selection for SRC 0: SWR mode; 1: LDO mode */
#define AON_SHIFT_SYSCFG_TRP_TEST_MODE_SEL           26
#define AON_BIT_SYSCFG_TRP_TEST_MODE_SEL             ((u32)0x00000001 << 26)                             /*!<R 0  Trapped Selection for Test mode 0: normal mode; 1: test mode  */
#define AON_SHIFT_RSVD4                              25
#define AON_BIT_RSVD4                                ((u32)0x00000001 << 25)                             /*!<R 0   */
#define AON_SHIFT_SYSCFG_TRP_EFUSE_AUTOLOAD_DIS      24
#define AON_BIT_SYSCFG_TRP_EFUSE_AUTOLOAD_DIS        ((u32)0x00000001 << 24)                             /*!<R 0  1: disable efuse autoload 0: enable efuse autoload */
#define AON_SHIFT_RSVD5                              22
#define AON_MASK_RSVD5                               ((u32)0x00000003 << 22)                             /*!<R 0   */
#define AON_SHIFT_SYS_INFO1_DUMMY_0                  21
#define AON_BIT_SYS_INFO1_DUMMY_0                    ((u32)0x00000001 << 21)                             /*!<R 0   */
#define AON_SHIFT_RSVD6                              20
#define AON_BIT_RSVD6                                ((u32)0x00000001 << 20)                             /*!<R 0   */
#define AON_SHIFT_SYS_INFO1_DUMMY_1                  17
#define AON_MASK_SYS_INFO1_DUMMY_1                   ((u32)0x00000007 << 17)                             /*!<R 0   */
#define AON_SHIFT_V09_VLD                            16
#define AON_BIT_V09_VLD                              ((u32)0x00000001 << 16)                             /*!<R 1  0.9V Power Ready, 1: Power Ready */
#define AON_SHIFT_SYS_INFO1_DUMMY_2                  12
#define AON_MASK_SYS_INFO1_DUMMY_2                   ((u32)0x0000000F << 12)                             /*!<R 0   */
#define AON_SHIFT_RSVD7                              11
#define AON_BIT_RSVD7                                ((u32)0x00000001 << 11)                             /*!<R 0   */
#define AON_SHIFT_SYS_128K_RDY                       10
#define AON_BIT_SYS_128K_RDY                         ((u32)0x00000001 << 10)                             /*!<R 0  1: 128K RDY */
#define AON_SHIFT_SYS_SYSPLL_CLK_RDY                 9
#define AON_BIT_SYS_SYSPLL_CLK_RDY                   ((u32)0x00000001 << 9)                              /*!<R 0  SYS PLL Clock Stable, 1: Clock Stable */
#define AON_SHIFT_SYS_XCLK_VLD                       8
#define AON_BIT_SYS_XCLK_VLD                         ((u32)0x00000001 << 8)                              /*!<R 0  Xtal Clock Stable, 1: Clock Stable */
#define AON_SHIFT_SYSCFG_ROM_INFO                    0
#define AON_MASK_SYSCFG_ROM_INFO                     ((u32)0x000000FF << 0)                              /*!<R/W 0  ROM Information */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_OTP_SYSCFG2
 * @brief                                            (@ 0X0CC)
 * @{
 *****************************************************************************/
#define AON_SHIFT_DBG_PORT1_SEL                      28
#define AON_MASK_DBG_PORT1_SEL                       ((u32)0x0000000F << 28)                             /*!<R/W 0  Debug port group 1 data sel 0000 : debug data 3:0 0001 : debug data 7:4 0010 : debug data 11:8 0011 : debug data 15:12 0100 : debug data 19:16 0101 : debug data 23:20 0110 : debug data 27:24 0111 : debug data 31:28 */
#define AON_SHIFT_DBG_PORT0_SEL                      24
#define AON_MASK_DBG_PORT0_SEL                       ((u32)0x0000000F << 24)                             /*!<R/W 0  Debug port group 0 data sel 0000 : debug data 3:0 0001 : debug data 7:4 0010 : debug data 11:8 0011 : debug data 15:12 0100 : debug data 19:16 0101 : debug data 23:20 0110 : debug data 27:24 0111 : debug data 31:28 */
#define AON_SHIFT_DBG_PORT7_EN                       23
#define AON_BIT_DBG_PORT7_EN                         ((u32)0x00000001 << 23)                             /*!<R/W 0  1:Debug port group 7 enable */
#define AON_SHIFT_DBG_PORT6_EN                       22
#define AON_BIT_DBG_PORT6_EN                         ((u32)0x00000001 << 22)                             /*!<R/W 0  1:Debug port group 6 enable */
#define AON_SHIFT_DBG_PORT5_EN                       21
#define AON_BIT_DBG_PORT5_EN                         ((u32)0x00000001 << 21)                             /*!<R/W 0  1:Debug port group 5 enable */
#define AON_SHIFT_DBG_PORT4_EN                       20
#define AON_BIT_DBG_PORT4_EN                         ((u32)0x00000001 << 20)                             /*!<R/W 0  1:Debug port group 4 enable */
#define AON_SHIFT_DBG_PORT3_EN                       19
#define AON_BIT_DBG_PORT3_EN                         ((u32)0x00000001 << 19)                             /*!<R/W 0  1:Debug port group 3 enable */
#define AON_SHIFT_DBG_PORT2_EN                       18
#define AON_BIT_DBG_PORT2_EN                         ((u32)0x00000001 << 18)                             /*!<R/W 0  1:Debug port group 2 enable */
#define AON_SHIFT_DBG_PORT1_EN                       17
#define AON_BIT_DBG_PORT1_EN                         ((u32)0x00000001 << 17)                             /*!<R/W 0  1:Debug port group 1 enable */
#define AON_SHIFT_DBG_PORT0_EN                       16
#define AON_BIT_DBG_PORT0_EN                         ((u32)0x00000001 << 16)                             /*!<R/W 0  1:Debug port group 0 enable */
#define AON_SHIFT_DBG_PORT                           8
#define AON_MASK_DBG_PORT                            ((u32)0x000000FF << 8)                              /*!<R/W 0  Debug port function selection: 8'h00: OTP 8'h01: SIC 8'h02: PMC 8'h03: Comparator 8'h4: HS SDM 8'h5: LS SDM (128K/4) 8'h8: PON UART0 8'h80: SPI_2 (SPI slave) 8'h81: SPI_3 (SPI slave) 8'h82: I2C0 8'h83: I2C1 8'h84: I2C2 8'h85: I2C3 8'h86: UART1 8'h87: UART2 8'h88: UART3 8'h89: SPORT 8'h8A: DDRPHY (High 32bit) 8'h8B: DDRPHY (Low 32bit) 8'h8C: ECDSA 8'h8D: SD Host 8'h8E: ED25519 8'h8F: Digital audio codec 8'h90: MIPI 8'h91: ADC 8'h92: SGPIO 8'h93: I2S0 8'h94: I2S1 8'h95: IPSEC 8'h96: LX arbiter 8'h97: SIC2AHB 8'h98: SDIO Host 8'h99: TRNG 8'h9A: BTTOP 8'h9B: GMAC 8'h9C: USB OTG 8'h9D: FE PHY 8'h9E: ISP 8'h9F: AUX 8'hA0: WLAN BB 8'hA1: WLAN MAC 8'hA2: NN 8'hA3: USB PHY 8'hA4: Nand flash */
#define AON_SHIFT_DBG_PIN_SEL                        4
#define AON_MASK_DBG_PIN_SEL                         ((u32)0x0000000F << 4)                              /*!<R/W 0  Debugger pin sel (TBD) */
#define AON_SHIFT_OTP3                               2
#define AON_MASK_OTP3                                ((u32)0x00000003 << 2)                              /*!<R/W 0  For OTP Use */
#define AON_SHIFT_DBG_SEL                            1
#define AON_BIT_DBG_SEL                              ((u32)0x00000001 << 1)                              /*!<R/W 1  Debugger mode sel (1: JTAG, 0: SWD) */
#define AON_SHIFT_DBG_EN                             0
#define AON_BIT_DBG_EN                               ((u32)0x00000001 << 0)                              /*!<R/W 1  Debugger pin enable(1: enable, 0: disable) */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_OTP_SYSCFG3
 * @brief                                            (@ 0X0D0)
 * @{
 *****************************************************************************/
#define AON_SHIFT_FLASH_PIN_SEL                      28
#define AON_MASK_FLASH_PIN_SEL                       ((u32)0x0000000F << 28)                             /*!<R/W 0  Flash pin sel(TBD) */
#define AON_SHIFT_FLASH_MODE                         24
#define AON_MASK_FLASH_MODE                          ((u32)0x0000000F << 24)                             /*!<R/W 0  Flash IO mode sel(TBD) */
#define AON_SHIFT_DBG_PORT7_SEL                      20
#define AON_MASK_DBG_PORT7_SEL                       ((u32)0x0000000F << 20)                             /*!<R/W 0  Debug port group 7 data sel 0000 : debug data 3:0 0001 : debug data 7:4 0010 : debug data 11:8 0011 : debug data 15:12 0100 : debug data 19:16 0101 : debug data 23:20 0110 : debug data 27:24 0111 : debug data 31:28 */
#define AON_SHIFT_DBG_PORT6_SEL                      16
#define AON_MASK_DBG_PORT6_SEL                       ((u32)0x0000000F << 16)                             /*!<R/W 0  Debug port group 6 data sel 0000 : debug data 3:0 0001 : debug data 7:4 0010 : debug data 11:8 0011 : debug data 15:12 0100 : debug data 19:16 0101 : debug data 23:20 0110 : debug data 27:24 0111 : debug data 31:28 */
#define AON_SHIFT_DBG_PORT5_SEL                      12
#define AON_MASK_DBG_PORT5_SEL                       ((u32)0x0000000F << 12)                             /*!<R/W 0  Debug port group 5 data sel 0000 : debug data 3:0 0001 : debug data 7:4 0010 : debug data 11:8 0011 : debug data 15:12 0100 : debug data 19:16 0101 : debug data 23:20 0110 : debug data 27:24 0111 : debug data 31:28 */
#define AON_SHIFT_DBG_PORT4_SEL                      8
#define AON_MASK_DBG_PORT4_SEL                       ((u32)0x0000000F << 8)                              /*!<R/W 0  Debug port group 4 data sel 0000 : debug data 3:0 0001 : debug data 7:4 0010 : debug data 11:8 0011 : debug data 15:12 0100 : debug data 19:16 0101 : debug data 23:20 0110 : debug data 27:24 0111 : debug data 31:28 */
#define AON_SHIFT_DBG_PORT3_SEL                      4
#define AON_MASK_DBG_PORT3_SEL                       ((u32)0x0000000F << 4)                              /*!<R/W 0  Debug port group 3 data sel 0000 : debug data 3:0 0001 : debug data 7:4 0010 : debug data 11:8 0011 : debug data 15:12 0100 : debug data 19:16 0101 : debug data 23:20 0110 : debug data 27:24 0111 : debug data 31:28 */
#define AON_SHIFT_DBG_PORT2_SEL                      0
#define AON_MASK_DBG_PORT2_SEL                       ((u32)0x0000000F << 0)                              /*!<R/W 0  Debug port group 2 data sel 0000 : debug data 3:0 0001 : debug data 7:4 0010 : debug data 11:8 0011 : debug data 15:12 0100 : debug data 19:16 0101 : debug data 23:20 0110 : debug data 27:24 0111 : debug data 31:28 */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_OTP_SYSCFG4
 * @brief                                            (@ 0X0D4)
 * @{
 *****************************************************************************/
#define AON_SHIFT_LOG_DBG_EN                         31
#define AON_BIT_LOG_DBG_EN                           ((u32)0x00000001 << 31)                             /*!<R/W 0  Log UART message on/off (0: On, 1: off), Use by SW */
#define AON_SHIFT_OTP6                               28
#define AON_MASK_OTP6                                ((u32)0x00000007 << 28)                             /*!<R/W 0  For OTP Use */
#define AON_SHIFT_LOG_TX_PIN_SEL                     26
#define AON_MASK_LOG_TX_PIN_SEL                      ((u32)0x00000003 << 26)                             /*!<R/W 0  Log UART TX pin sel, Use by SW */
#define AON_SHIFT_LOG_RX_PIN_SEL                     24
#define AON_MASK_LOG_RX_PIN_SEL                      ((u32)0x00000003 << 24)                             /*!<R/W 0  Log UART RX pin sel, Use by SW */
#define AON_SHIFT_ROM_UART_BAUD                      20
#define AON_MASK_ROM_UART_BAUD                       ((u32)0x0000000F << 20)                             /*!<R/W 0  ROM UART Baud Rate Sel(TBD), Use by SW */
#define AON_SHIFT_OTP5                               16
#define AON_MASK_OTP5                                ((u32)0x0000000F << 16)                             /*!<R/W 0  For OTP Use */
#define AON_SHIFT_ROM_DBG_EN                         15
#define AON_BIT_ROM_DBG_EN                           ((u32)0x00000001 << 15)                             /*!<R/W 0  ROM UART message on/off (0: On, 1: off), Use by SW */
#define AON_SHIFT_ROM_UART_SEL                       12
#define AON_MASK_ROM_UART_SEL                        ((u32)0x00000007 << 12)                             /*!<R/W 0  ROM UART sel (TBD), Use by SW */
#define AON_SHIFT_ROM_TX_SEL                         10
#define AON_MASK_ROM_TX_SEL                          ((u32)0x00000003 << 10)                             /*!<R/W 0  ROM UART TX pin sel, Use by SW */
#define AON_SHIFT_ROM_RX_SEL                         8
#define AON_MASK_ROM_RX_SEL                          ((u32)0x00000003 << 8)                              /*!<R/W 0  ROM UART RX pin sel, Use by SW */
#define AON_SHIFT_BOOT_SEL                           4
#define AON_MASK_BOOT_SEL                            ((u32)0x0000000F << 4)                              /*!<R/W 0  Boot selection(TBD), Use by SW */
#define AON_SHIFT_OTP4                               0
#define AON_MASK_OTP4                                ((u32)0x0000000F << 0)                              /*!<R/W 0  For OTP Use */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_OTP_SYSCFG5
 * @brief                                            (@ 0X0D8)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_OTP9                               30
#define AON_MASK_OTP9                                ((u32)0x00000003 << 30)                             /*!<R/W 0  For OTP Use */
#else
#define AON_SHIFT_OTP9                               31
#define AON_BIT_OTP9                                 ((u32)0x00000001 << 31)                             /*!<R/W 0  For OTP Use */
#define AON_SHIFT_AACK_EN                            30
#define AON_BIT_AACK_EN                              ((u32)0x00000001 << 30)                             /*!<R/W 0  0:Enable AACK Circuit, 1: Disable AACK Circuit */
#endif
#define AON_SHIFT_PFM_OCP                            27
#define AON_MASK_PFM_OCP                             ((u32)0x00000007 << 27)                             /*!<R/W 011  Mapping to AON+0x18[25:23] once FPWM_L1=0 */
#define AON_SHIFT_PFM_ZCD_H                          25
#define AON_MASK_PFM_ZCD_H                           ((u32)0x00000003 << 25)                             /*!<R/W 01  Mapping to AON+0x18[28:27] once FPWM_L1=0 */
#define AON_SHIFT_PFM_MOS_HALF                       24
#define AON_BIT_PFM_MOS_HALF                         ((u32)0x00000001 << 24)                             /*!<R/W 1  Mapping to AON+0x1C[11] once FPWM_L1=0 */
#define AON_SHIFT_OTP8                               22
#define AON_MASK_OTP8                                ((u32)0x00000003 << 22)                             /*!<R/W 0  For OTP Use */
#define AON_SHIFT_PWM_OCP                            19
#define AON_MASK_PWM_OCP                             ((u32)0x00000007 << 19)                             /*!<R/W 011  Mapping to AON+0x18[25:23] once FPWM_L1=1 */
#define AON_SHIFT_PWM_ZCD_H                          17
#define AON_MASK_PWM_ZCD_H                           ((u32)0x00000003 << 17)                             /*!<R/W 10  Mapping to AON+0x18[28:27] once FPWM_L1=1 */
#define AON_SHIFT_PWM_MOS_HALF                       16
#define AON_BIT_PWM_MOS_HALF                         ((u32)0x00000001 << 16)                             /*!<R/W 0  Mapping to AON+0x1C[11] once FPWM_L1=1 */
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_OTP7                               11
#define AON_MASK_OTP7                                ((u32)0x0000001F << 11)                             /*!<R/W 0  For OTP Use */
#else
#define AON_SHIFT_OTP7                               14
#define AON_MASK_OTP7                                ((u32)0x00000003 << 14)                             /*!<R/W 0  For OTP Use */
#define AON_SHIFT_XTAL_LP_CTRL                       13
#define AON_BIT_XTAL_LP_CTRL                         ((u32)0x00000001 << 13)                             /*!<R/W 0  0:Manual Mode */
#define AON_SHIFT_ISP_CTRL                           12
#define AON_BIT_ISP_CTRL                             ((u32)0x00000001 << 12)                             /*!<R/W Once 1  1:Enable ISP Function  */
#define AON_SHIFT_ENC_CTRL                           11
#define AON_BIT_ENC_CTRL                             ((u32)0x00000001 << 11)                             /*!<R/W Once 1  1:Enable whole video encoder function  */
#endif
#define AON_SHIFT_H265_CTRL                          10
#define AON_BIT_H265_CTRL                            ((u32)0x00000001 << 10)                             /*!<R/W Once 1  1:Enable H265 Function (For SW Control) */
#define AON_SHIFT_NN_CTRL                            9
#define AON_BIT_NN_CTRL                              ((u32)0x00000001 << 9)                              /*!<R/W Once 1  1:Enable NN Function */
#define AON_SHIFT_RM3_DBG_MD_SEL                     8
#define AON_BIT_RM3_DBG_MD_SEL                       ((u32)0x00000001 << 8)                              /*!<R/W 0  Real-M300 SWJ-DP Mode Selection (SW Only) 0:SWD-DP Mode 1:JTAG-DP Mode */
#define AON_SHIFT_RM3_DBG_PIN_EN                     7
#define AON_BIT_RM3_DBG_PIN_EN                       ((u32)0x00000001 << 7)                              /*!<R/W 0  Real-M300 SWJ-DP Pinmux Function Enable (SW Only) 0:SWD/JTAG Pin Disable 1:SWD/JTAG Pin Enable */
#define AON_SHIFT_DBG_CHAIN_EN                       6
#define AON_BIT_DBG_CHAIN_EN                         ((u32)0x00000001 << 6)                              /*!<R/W 0  Real-M500 and Real-M300 JTAG Chain Mode Enable (SW Only) 0:JTAG Chain Mode Disable 1:JTAG Chain Mode Enable */
#define AON_SHIFT_RM5_DBG_MD_SEL                     5
#define AON_BIT_RM5_DBG_MD_SEL                       ((u32)0x00000001 << 5)                              /*!<R/W 0  Real-M500 SWJ-DP Mode Selection (SW Only) 0:SWD-DP Mode 1:JTAG-DP Mode */
#define AON_SHIFT_RM5_DBG_PIN_EN                     4
#define AON_BIT_RM5_DBG_PIN_EN                       ((u32)0x00000001 << 4)                              /*!<R/W 0  Real-M500 SWJ-DP Pinmux Function Enable (SW Only) 0:SWD/JTAG Pin Disable 1:SWD/JTAG Pin Enable */
#define AON_SHIFT_XTAL_SEL                           0
#define AON_MASK_XTAL_SEL                            ((u32)0x0000000F << 0)                              /*!<R/W 0  xtal selection, Default=40MHz 0000= 40MHz, 0001= 25MHz, 0010= 13MHz, 0011= 19.2MHz 0100= 20MHz, 0101= 26MHz, 0110= 38.4MHz, 0111= 17.664MHz 1000= 16MHz, 1001= 14.138MHz, 1010= 12MHz, 1011= 52MHz 1100= 48MHz, 1101= 27MHz, 1110= 24MHz, 1111= none  */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_OTP_SYSCFG6
 * @brief                                            (@ 0X0DC)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SYSCFG6                            0
#define AON_MASK_SYSCFG6                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_OTP_SYSCFG7
 * @brief                                            (@ 0X0E0)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SYSCFG7                            0
#define AON_MASK_SYSCFG7                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_DBG_REG
 * @brief                                            (@ 0X0E4)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SYS_DBG_VALUE                      0
#define AON_MASK_SYS_DBG_VALUE                       ((u32)0xFFFFFFFF << 0)                              /*!<R 0  SYS debug register value */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SYS_CTRL
 * @brief                                            (@ 0X0E8)
 * @{
 *****************************************************************************/
#define AON_SHIFT_CPU_CLK_SEL                        17
#define AON_BIT_CPU_CLK_SEL                          ((u32)0x00000001 << 17)                             /*!<R/W 0  00: 500MHz/300MHz 01: 400MHz */
#define AON_SHIFT_DEBUGER_EN                         8
#define AON_BIT_DEBUGER_EN                           ((u32)0x00000001 << 8)                              /*!<R/W 0  1: swd mux enable */
#define AON_SHIFT_OTP_RW_REG_SEL                     7
#define AON_BIT_OTP_RW_REG_SEL                       ((u32)0x00000001 << 7)                              /*!<R/W 0  OTP Indirect Read/Write Register Selection 0: From AON indirect access register 1: From SYSON/SYSON_S indirect access register */
#define AON_SHIFT_OCP_IMR                            6
#define AON_BIT_OCP_IMR                              ((u32)0x00000001 << 6)                              /*!<R/W 0  1: Enable OCP interrupt */
#define AON_SHIFT_OCP_ISR                            5
#define AON_BIT_OCP_ISR                              ((u32)0x00000001 << 5)                              /*!<R/W1C 0  1: indicate OCP status */
#define AON_SHIFT_AON_TIMER_IMR                      4
#define AON_BIT_AON_TIMER_IMR                        ((u32)0x00000001 << 4)                              /*!<R/W 0  1: Enable AON Timer interrupt */
#define AON_SHIFT_CPU_RET_MODE                       3
#define AON_BIT_CPU_RET_MODE                         ((u32)0x00000001 << 3)                              /*!<R/W 0  1:Enable RET Mode, 0: Disable RET Mode */
#define AON_SHIFT_BOD_INT_IMR                        2
#define AON_BIT_BOD_INT_IMR                          ((u32)0x00000001 << 2)                              /*!<R/W 0  1: indicate BOD Mask; Vin < BOD_VINTL (Ex: Vin<2.791 and then BOD_ISR_STS was high) */
#define AON_SHIFT_GPIOA4_OUTPUT_STATUS               1
#define AON_BIT_GPIOA4_OUTPUT_STATUS                 ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Output High, 0: Output Low */
#define AON_SHIFT_GPIOA4_OUTPUT_EN                   0
#define AON_BIT_GPIOA4_OUTPUT_EN                     ((u32)0x00000001 << 0)                              /*!<R/W 0  1: GPIO Output Enable */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SIC_DBG_CTRL
 * @brief                                            (@ 0X0EC)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SIC_DBG_GP_SEL                     1
#define AON_MASK_SIC_DBG_GP_SEL                      ((u32)0x000000FF << 1)                              /*!<R/W 0x00  Group Sel */
#define AON_SHIFT_SIC_DBG_EN                         0
#define AON_BIT_SIC_DBG_EN                           ((u32)0x00000001 << 0)                              /*!<R/W 0x00  1:Enable */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_OTP_CNT_Z_CTRL
 * @brief                                            (@ 0X0F8)
 * @{
 *****************************************************************************/
#define AON_SHIFT_RSVD8                              19
#define AON_MASK_RSVD8                               ((u32)0x00001FFF << 19)                             /*!<R/W 0x000   */
#define AON_SHIFT_B_OTP_CZ_SS_RSVD_STS               18
#define AON_BIT_B_OTP_CZ_SS_RSVD_STS                 ((u32)0x00000001 << 18)                             /*!<R/W1C 0  SS_RSVD Counting Zero Check Status 0: Counting zero check status of SS_RSVD is passed 1: Counting zero check status of SS_RSVD is failed */
#define AON_SHIFT_B_OTP_CZ_RSIP_K2_STS               17
#define AON_BIT_B_OTP_CZ_RSIP_K2_STS                 ((u32)0x00000001 << 17)                             /*!<R/W1C 0  RSIP_K2 Counting Zero Check Status 0: Counting zero check status of RSIP_K2 is passed 1: Counting zero check status of RSIP_K2 is failed */
#define AON_SHIFT_B_OTP_CZ_RSIP_K1_STS               16
#define AON_BIT_B_OTP_CZ_RSIP_K1_STS                 ((u32)0x00000001 << 16)                             /*!<R/W1C 0  RSIP_K1 Counting Zero Check Status 0: Counting zero check status of RSIP_K1 is passed 1: Counting zero check status of RSIP_K1 is failed */
#define AON_SHIFT_B_OTP_CZ_JTAG_NS2_STS              15
#define AON_BIT_B_OTP_CZ_JTAG_NS2_STS                ((u32)0x00000001 << 15)                             /*!<R/W1C 0  JTAG_NS2 Counting Zero Check Status 0: Counting zero check status of JTAG_NS2 is passed 1: Counting zero check status of JTAG_NS2 is failed */
#define AON_SHIFT_B_OTP_CZ_JTAG_NS1_STS              14
#define AON_BIT_B_OTP_CZ_JTAG_NS1_STS                ((u32)0x00000001 << 14)                             /*!<R/W1C 0  JTAG_NS1 Counting Zero Check Status 0: Counting zero check status of JTAG_NS1 is passed 1: Counting zero check status of JTAG_NS1 is failed */
#define AON_SHIFT_B_OTP_CZ_JTAG_S2_STS               13
#define AON_BIT_B_OTP_CZ_JTAG_S2_STS                 ((u32)0x00000001 << 13)                             /*!<R/W1C 0  JTAG_S2 Counting Zero Check Status 0: Counting zero check status of JTAG_S2 is passed 1: Counting zero check status of JTAG_S2 is failed */
#define AON_SHIFT_B_OTP_CZ_JTAG_S1_STS               12
#define AON_BIT_B_OTP_CZ_JTAG_S1_STS                 ((u32)0x00000001 << 12)                             /*!<R/W1C 0  JTAG_S1 Counting Zero Check Status 0: Counting zero check status of JTAG_S1 is passed 1: Counting zero check status of JTAG_S1 is failed */
#define AON_SHIFT_B_OTP_CZ_HUK_RSVD_STS              11
#define AON_BIT_B_OTP_CZ_HUK_RSVD_STS                ((u32)0x00000001 << 11)                             /*!<R/W1C 0  HUK_RSVD Counting Zero Check Status 0: Counting zero check status of HUK_RSVD is passed 1: Counting zero check status of HUK_RSVD is failed */
#define AON_SHIFT_B_OTP_CZ_HUK_STS                   10
#define AON_BIT_B_OTP_CZ_HUK_STS                     ((u32)0x00000001 << 10)                             /*!<R/W1C 0  HUK Counting Zero Check Status 0: Counting zero check status of HUK is passed 1: Counting zero check status of HUK is failed */
#define AON_SHIFT_RSVD9                              9
#define AON_BIT_RSVD9                                ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define AON_SHIFT_B_OTP_CZ_RSVD2_STS                 8
#define AON_BIT_B_OTP_CZ_RSVD2_STS                   ((u32)0x00000001 << 8)                              /*!<R/W1C 0  RSVD2 Counting Zero Check Status 0: Counting zero check status of RSVD2 is passed 1: Counting zero check status of RSVD2 is failed */
#define AON_SHIFT_B_OTP_CZ_RSVD1_STS                 7
#define AON_BIT_B_OTP_CZ_RSVD1_STS                   ((u32)0x00000001 << 7)                              /*!<R/W1C 0  RSVD1 Counting Zero Check Status 0: Counting zero check status of RSVD1 is passed 1: Counting zero check status of RSVD1 is failed */
#define AON_SHIFT_B_OTP_CZ_ECDSA2_STS                6
#define AON_BIT_B_OTP_CZ_ECDSA2_STS                  ((u32)0x00000001 << 6)                              /*!<R/W1C 0  ECDSA2 Counting Zero Check Status 0: Counting zero check status of ECDSA2 is passed 1: Counting zero check status of ECDSA2 is failed */
#define AON_SHIFT_B_OTP_CZ_ECDSA1_STS                5
#define AON_BIT_B_OTP_CZ_ECDSA1_STS                  ((u32)0x00000001 << 5)                              /*!<R/W1C 0  ECDSA1 Counting Zero Check Status 0: Counting zero check status of ECDSA1 is passed 1: Counting zero check status of ECDSA1 is failed */
#define AON_SHIFT_B_OTP_CZ_IPSEC2_STS                4
#define AON_BIT_B_OTP_CZ_IPSEC2_STS                  ((u32)0x00000001 << 4)                              /*!<R/W1C 0  IPSEC2 Counting Zero Check Status 0: Counting zero check status of IPSEC2 is passed 1: Counting zero check status of IPSEC2 is failed */
#define AON_SHIFT_B_OTP_CZ_IPSEC1_STS                3
#define AON_BIT_B_OTP_CZ_IPSEC1_STS                  ((u32)0x00000001 << 3)                              /*!<R/W1C 0  IPSEC1 Counting Zero Check Status 0: Counting zero check status of IPSEC1 is passed 1: Counting zero check status of IPSEC1 is failed */
#define AON_SHIFT_B_OTP_CZ_ROTPK2_STS                2
#define AON_BIT_B_OTP_CZ_ROTPK2_STS                  ((u32)0x00000001 << 2)                              /*!<R/W1C 0  ROTPK2 Counting Zero Check Status 0: Counting zero check status of ROTPK2 is passed 1: Counting zero check status of ROTPK2 is failed */
#define AON_SHIFT_B_OTP_CZ_ROTPK1_STS                1
#define AON_BIT_B_OTP_CZ_ROTPK1_STS                  ((u32)0x00000001 << 1)                              /*!<R/W1C 0  ROTPK1 Counting Zero Check Status 0: Counting zero check status of ROTPK1 is passed 1: Counting zero check status of ROTPK1 is failed */
#define AON_SHIFT_B_OTP_CNTZ_CTRL                    0
#define AON_BIT_B_OTP_CNTZ_CTRL                      ((u32)0x00000001 << 0)                              /*!<R/W 1  OTP Keys Counting Zero Bit Check Control This bit is used to control conting zero check mechanism is enabled or not. 0: Disable keys counting zero bit check mechanism 1: Enable keys counting zero bit check mechanism */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_PMC_CTRL
 * @brief                                            (@ 0X0FC)
 * @{
 *****************************************************************************/
#define AON_SHIFT_AON_GPIO_WAKE_SEL                  5
#define AON_MASK_AON_GPIO_WAKE_SEL                   ((u32)0x0000000F << 5)                              /*!<R/W 0  0000: GPIOA0~GPIOA3 can wake up system individually 0001: RSVD 0010: RSVD 0011: GPIOA0&GPIOA1=1 and then wake up system. GPIOA2 and GPIOA3 can wake up system individually 0100: RSVD 0101: GPIOA0&GPIOA2=1 and then wake up system. GPIOA1 and GPIOA3 can wake up system individually 0110: GPIOA1&GPIOA2=1 and then wake up system. GPIOA0 and GPIOA3 can wake up system individually 0111: GPIOA0&GPIOA1&GPIOA2=1 and then wake up system. GPIOA0 can wake up system individually 1000: RSVD 1001: GPIOA0&GPIOA3=1 and then wake up system. GPIOA1 and GPIOA2 can wake up system individually 1010: GPIOA1&GPIOA3=1 and then wake up system. GPIOA0 and GPIOA2 can wake up system individually 1011: GPIOA0&GPIOA1&GPIOA3=1 and then wake up system. GPIOA2 can wake up system individually 1100: GPIOA2&GPIOA3=1 and then wake up system. GPIOA0 and GPIOA1 can wake up system individually 1101: GPIOA0&GPIOA2&GPIOA3=1 and then wake up system. GPIOA1 can wake up system individually 1110: GPIOA1&GPIOA2&GPIOA3=1 and then wake up system. GPIOA0 can wake up system individually 1111: GPIOA0&GPIOA1&GPIOA2&GPIOA3=1 and then wake up system  */
#define AON_SHIFT_SYSON_PLL_SWITCH                   3
#define AON_MASK_SYSON_PLL_SWITCH                    ((u32)0x00000003 << 3)                              /*!<R/W 0  00: 500MHz 01: 400MHz 10: 300MHz */
#define AON_SHIFT_SYSON_PM_CMD_SLP                   2
#define AON_BIT_SYSON_PM_CMD_SLP                     ((u32)0x00000001 << 2)                              /*!<R/W 0  1: command SYSON SM to enter sleep state, when PMC finishes the process, this bit will be auto clear to 0 */
#define AON_SHIFT_DSLP_LV_EN                         1
#define AON_BIT_DSLP_LV_EN                           ((u32)0x00000001 << 1)                              /*!<R/W 0  0: LDO_AON output stay 0.9V under deep sleep state 1: LDO_AON output reduce to 0.8V under deep sleep state */
#define AON_SHIFT_SYSON_PM_CMD_DSLP                  0
#define AON_BIT_SYSON_PM_CMD_DSLP                    ((u32)0x00000001 << 0)                              /*!<R/W 0  1: command SYSON SM to enter deep sleep state,when PMC finishes the process, this bit will be auto clear to 0 */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_PMC_OPT
 * @brief                                            (@ 0X100)
 * @{
 *****************************************************************************/
#define AON_SHIFT_DSLP_ANA_4M_EN                     10
#define AON_BIT_DSLP_ANA_4M_EN                       ((u32)0x00000001 << 10)                             /*!<R/W 1  When enter dslp, 1: enable clk; 0: disable If it's selected to disable in DSLP, HW should enable clock the clock automatically when wake event takes place. */
#define AON_SHIFT_DSLP_AON_REG_CLK_EN                9
#define AON_BIT_DSLP_AON_REG_CLK_EN                  ((u32)0x00000001 << 9)                              /*!<R/W 1  When enter dslp, 1: enable clk; 0: gated If it's selected to disable in DSLP, HW should enable clock the clock automatically when wake event takes place. */
#define AON_SHIFT_AON_FSM_DSLP_CLK_SEL               0
#define AON_BIT_AON_FSM_DSLP_CLK_SEL                 ((u32)0x00000001 << 0)                              /*!<R/W 0  FSM clock selection in deep sleep mode 0: ANA_CLK_100K 1: OSC 4MHz */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_BOOT_REASON
 * @brief                                            (@ 0X104)
 * @{
 *****************************************************************************/
#define AON_SHIFT_BOD_ISR_STS                        5
#define AON_BIT_BOD_ISR_STS                          ((u32)0x00000001 << 5)                              /*!<R/W1C 0  1: Indicate BOD interrupt and clear by SW */
#define AON_SHIFT_BOD_STS                            4
#define AON_BIT_BOD_STS                              ((u32)0x00000001 << 4)                              /*!<R/W1C 1  1: Indicate BOD reboot and clear by SW */
#define AON_SHIFT_AON_STANDBY_STS                    3
#define AON_BIT_AON_STANDBY_STS                      ((u32)0x00000001 << 3)                              /*!<R/W 0  Control by SW */
#define AON_SHIFT_AON_DSLP_STS                       2
#define AON_BIT_AON_DSLP_STS                         ((u32)0x00000001 << 2)                              /*!<R/W 0  Control by SW */
#define AON_SHIFT_AON_WATCHDOG_STS                   1
#define AON_BIT_AON_WATCHDOG_STS                     ((u32)0x00000001 << 1)                              /*!<R/W1C 0  1: Indicate AON Watchdog reboot and clear by SW */
#define AON_SHIFT_VNDR_WATCHDOG_STS                  0
#define AON_BIT_VNDR_WATCHDOG_STS                    ((u32)0x00000001 << 0)                              /*!<R/W1C 0  1: Indicate Vendor Watchdog reboot and clear by SW */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_WL_CTRL
 * @brief                                            (@ 0X108)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SYS_WLAFE_POD125                   25
#define AON_BIT_SYS_WLAFE_POD125                     ((u32)0x00000001 << 25)                             /*!<R/W 0  0: power down 125 WLAFE  */
#define AON_SHIFT_SYS_WLAFE_POD33                    24
#define AON_BIT_SYS_WLAFE_POD33                      ((u32)0x00000001 << 24)                             /*!<R/W 0  0: power down 33 WLAFE  */
#define AON_SHIFT_SYS_WLAON_CLK_SEL                  6
#define AON_BIT_SYS_WLAON_CLK_SEL                    ((u32)0x00000001 << 6)                              /*!<R/W 0  1: 100kHz, 0:4MHz */
#define AON_SHIFT_SYS_WLON_CLK_EN                    5
#define AON_BIT_SYS_WLON_CLK_EN                      ((u32)0x00000001 << 5)                              /*!<R/W 0  1: enable WL clock */
#define AON_SHIFT_SYS_WLAXI_CLK_EN                   4
#define AON_BIT_SYS_WLAXI_CLK_EN                     ((u32)0x00000001 << 4)                              /*!<R/W 0  1: enable WL clock */
#define AON_SHIFT_WL_REQ2ACT                         3
#define AON_BIT_WL_REQ2ACT                           ((u32)0x00000001 << 3)                              /*!<R 0  1: WLAN request to active  */
#define AON_SHIFT_WL_RDY2ACT                         2
#define AON_BIT_WL_RDY2ACT                           ((u32)0x00000001 << 2)                              /*!<R/W 0  1: WLAN ready to active */
#define AON_SHIFT_SYS_WLON_EN                        1
#define AON_BIT_SYS_WLON_EN                          ((u32)0x00000001 << 1)                              /*!<R/W 0  1: enable WLON and WL macro block */
#define AON_SHIFT_SYS_WL_AXI_EN                      0
#define AON_BIT_SYS_WL_AXI_EN                        ((u32)0x00000001 << 0)                              /*!<R/W 0  1: enable WL AXI function */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SLP_WAKE_EVENT_MSK0
 * @brief                                            (@ 0X10C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_RSVD10                             16
#define AON_MASK_RSVD10                              ((u32)0x0000FFFF << 16)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_SYSON_WEVT_SGPIO_MSK               15
#define AON_BIT_SYSON_WEVT_SGPIO_MSK                 ((u32)0x00000001 << 15)                             /*!<R/W 0  1: enable SGPIO Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_SYSON_WEVT_ADC_MSK                 14
#define AON_BIT_SYSON_WEVT_ADC_MSK                   ((u32)0x00000001 << 14)                             /*!<R/W 0  1: enable ADC Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_SYSON_WEVT_USB_MSK                 13
#define AON_BIT_SYSON_WEVT_USB_MSK                   ((u32)0x00000001 << 13)                             /*!<R/W 0  1: enable USB Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_AON_WEVT_AON_GPIO3_MSK             12
#define AON_BIT_AON_WEVT_AON_GPIO3_MSK               ((u32)0x00000001 << 12)                             /*!<R/W 0  1: enable AON GPIO3 Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_AON_WEVT_AON_GPIO2_MSK             11
#define AON_BIT_AON_WEVT_AON_GPIO2_MSK               ((u32)0x00000001 << 11)                             /*!<R/W 0  1: enable AON GPIO2 Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_AON_WEVT_AON_GPIO1_MSK             10
#define AON_BIT_AON_WEVT_AON_GPIO1_MSK               ((u32)0x00000001 << 10)                             /*!<R/W 0  1: enable AON GPIO1 Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_AON_WEVT_AON_GPIO0_MSK             9
#define AON_BIT_AON_WEVT_AON_GPIO0_MSK               ((u32)0x00000001 << 9)                              /*!<R/W 0  1: enable AON GPIO0 Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_AON_WEVT_AON_RTC_MSK               8
#define AON_BIT_AON_WEVT_AON_RTC_MSK                 ((u32)0x00000001 << 8)                              /*!<R/W 0  1: enable AON RTC Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_AON_WEVT_AON_COMP_MSK              7
#define AON_BIT_AON_WEVT_AON_COMP_MSK                ((u32)0x00000001 << 7)                              /*!<R/W 0  1: enable AON Comparator Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_AON_WEVT_AON_TIMER_MSK             6
#define AON_BIT_AON_WEVT_AON_TIMER_MSK               ((u32)0x00000001 << 6)                              /*!<R/W 0  1: enable AON Timer Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_PON_WEVT_UART_MSK                  5
#define AON_BIT_PON_WEVT_UART_MSK                    ((u32)0x00000001 << 5)                              /*!<R/W 0  1: enable UART0 Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_RSVD11                             4
#define AON_BIT_RSVD11                               ((u32)0x00000001 << 4)                              /*!<R/W 0  RSVD */
#define AON_SHIFT_PON_WEVT_WLAN_MSK                  3
#define AON_BIT_PON_WEVT_WLAN_MSK                    ((u32)0x00000001 << 3)                              /*!<R/W 0  1: enable WLAN Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_PON_WEVT_PWM_MSK                   2
#define AON_BIT_PON_WEVT_PWM_MSK                     ((u32)0x00000001 << 2)                              /*!<R/W 0  1: enable PWM Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_PON_WEVT_GPIO_MSK                  1
#define AON_BIT_PON_WEVT_GPIO_MSK                    ((u32)0x00000001 << 1)                              /*!<R/W 0  1: enable PON GPIO Wakeup event; 0: disable the event to wakeup system */
#define AON_SHIFT_PON_WEVT_GTIM0_MSK                 0
#define AON_BIT_PON_WEVT_GTIM0_MSK                   ((u32)0x00000001 << 0)                              /*!<R/W 0  1: enable GTIMER0 Wakeup event; 0: disable the event to wakeup system */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SLP_WAKE_EVENT_STATUS0
 * @brief                                            (@ 0X110)
 * @{
 *****************************************************************************/
#define AON_SHIFT_RSVD12                             16
#define AON_MASK_RSVD12                              ((u32)0x0000FFFF << 16)                             /*!<R/W 0  RSVD  */
#define AON_SHIFT_SYSON_WEVT_SGPIO_STS               15
#define AON_BIT_SYSON_WEVT_SGPIO_STS                 ((u32)0x00000001 << 15)                             /*!<R 0  1: Indicate SGPIO Wakeup event */
#define AON_SHIFT_SYSON_WEVT_ADC_STS                 14
#define AON_BIT_SYSON_WEVT_ADC_STS                   ((u32)0x00000001 << 14)                             /*!<R 0  1: Indicate ADC Wakeup event */
#define AON_SHIFT_SYSON_WEVT_USB_STS                 13
#define AON_BIT_SYSON_WEVT_USB_STS                   ((u32)0x00000001 << 13)                             /*!<R 0  1: Indicate USB Wakeup event */
#define AON_SHIFT_AON_WEVT_AON_GPIO3_STS             12
#define AON_BIT_AON_WEVT_AON_GPIO3_STS               ((u32)0x00000001 << 12)                             /*!<R/W1C 0  1: indicate AON GPIO3 Wakeup event;  */
#define AON_SHIFT_AON_WEVT_AON_GPIO2_STS             11
#define AON_BIT_AON_WEVT_AON_GPIO2_STS               ((u32)0x00000001 << 11)                             /*!<R/W1C 0  1: indicate AON GPIO2 Wakeup event;  */
#define AON_SHIFT_AON_WEVT_AON_GPIO1_STS             10
#define AON_BIT_AON_WEVT_AON_GPIO1_STS               ((u32)0x00000001 << 10)                             /*!<R/W1C 0  1: indicate AON GPIO1 Wakeup event;  */
#define AON_SHIFT_AON_WEVT_AON_GPIO0_STS             9
#define AON_BIT_AON_WEVT_AON_GPIO0_STS               ((u32)0x00000001 << 9)                              /*!<R/W1C 0  1: indicate AON GPIO0 Wakeup event; */
#define AON_SHIFT_AON_WEVT_AON_RTC_STS               8
#define AON_BIT_AON_WEVT_AON_RTC_STS                 ((u32)0x00000001 << 8)                              /*!<R 0  1: indicate AON RTC Wakeup event */
#define AON_SHIFT_AON_WEVT_AON_COMP_STS              7
#define AON_BIT_AON_WEVT_AON_COMP_STS                ((u32)0x00000001 << 7)                              /*!<R 0  1: indicate AON Comparator Wakeup event; */
#define AON_SHIFT_AON_WEVT_AON_TIMER_STS             6
#define AON_BIT_AON_WEVT_AON_TIMER_STS               ((u32)0x00000001 << 6)                              /*!<R/W1C 0  1: indicate AON Timer Wakeup event;  */
#define AON_SHIFT_PON_WEVT_UART_STS                  5
#define AON_BIT_PON_WEVT_UART_STS                    ((u32)0x00000001 << 5)                              /*!<R 0  1: indicate UART0 Wakeup event; */
#define AON_SHIFT_RSVD13                             4
#define AON_BIT_RSVD13                               ((u32)0x00000001 << 4)                              /*!<R 0  RSVD  */
#define AON_SHIFT_PON_WEVT_WLAN_STS                  3
#define AON_BIT_PON_WEVT_WLAN_STS                    ((u32)0x00000001 << 3)                              /*!<R 0  1: indicate WLAN Wakeup event;  */
#define AON_SHIFT_PON_WEVT_PWM_STS                   2
#define AON_BIT_PON_WEVT_PWM_STS                     ((u32)0x00000001 << 2)                              /*!<R 0  1: indicate PWM Wakeup event; */
#define AON_SHIFT_PON_WEVT_GPIO_STS                  1
#define AON_BIT_PON_WEVT_GPIO_STS                    ((u32)0x00000001 << 1)                              /*!<R 0  1: indicate PON GPIO Wakeup event;  */
#define AON_SHIFT_PON_WEVT_GTIM0_STS                 0
#define AON_BIT_PON_WEVT_GTIM0_STS                   ((u32)0x00000001 << 0)                              /*!<R 0  1: indicate GTIMER0 Wakeup event;  */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SNF_WAKE_EVENT_MSK0
 * @brief                                            (@ 0X114)
 * @{
 *****************************************************************************/
#define AON_SHIFT_RSVD14                             2
#define AON_MASK_RSVD14                              ((u32)0x3FFFFFFF << 2)                              /*!<R/W 0   */
#define AON_SHIFT_WLAN_IMR_MSK                       1
#define AON_BIT_WLAN_IMR_MSK                         ((u32)0x00000001 << 1)                              /*!<R/W 0  1: enable wlan interrupt; 0: Disable */
#define AON_SHIFT_PON_SNFEVT_WLON_PON_MSK            0
#define AON_BIT_PON_SNFEVT_WLON_PON_MSK              ((u32)0x00000001 << 0)                              /*!<R/W 0  1: enable wlan power on wakeup event interrupt; 0: Disable */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SNF_WAKE_EVENT_STATUS
 * @brief                                            (@ 0X118)
 * @{
 *****************************************************************************/
#define AON_SHIFT_RSVD15                             2
#define AON_MASK_RSVD15                              ((u32)0x3FFFFFFF << 2)                              /*!<R/W 0   */
#define AON_SHIFT_WLAN_ISR                           1
#define AON_BIT_WLAN_ISR                             ((u32)0x00000001 << 1)                              /*!<R/W1C 0  1: indicate wlan power on status */
#define AON_SHIFT_PON_SNFEVT_WLON_PON_STS            0
#define AON_BIT_PON_SNFEVT_WLON_PON_STS              ((u32)0x00000001 << 0)                              /*!<R 0  1: indicate wlan power on wakeup status */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_PWRMGT_OPTION
 * @brief                                            (@ 0X11C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_PON_PMOPT_SNZ_XTAL_NR_EN           19
#define AON_BIT_PON_PMOPT_SNZ_XTAL_NR_EN             ((u32)0x00000001 << 19)                             /*!<R/W 0  1: enable XTAL Normal mode when enter into snooze mode; 1: NR mode, 0: HP mode */
#define AON_SHIFT_PON_PMOPT_SLP_MEM1_PM_EN           17
#define AON_MASK_PON_PMOPT_SLP_MEM1_PM_EN            ((u32)0x00000003 << 17)                             /*!<R/W 0  0: Enable SRAM1 normal mode when enter into power mode 1: Enable SRAM1 RET mode when enter into power mode 2: Enable SRAM1 SD mode when enter into power mode */
#define AON_SHIFT_PON_PMOPT_SLP_MEM0_PM_EN           15
#define AON_MASK_PON_PMOPT_SLP_MEM0_PM_EN            ((u32)0x00000003 << 15)                             /*!<R/W 0  0: Enable SRAM0 normal mode when enter into power mode 1: Enable SRAM0 RET mode when enter into power mode 2: Enable SRAM0 SD mode when enter into power mode */
#define AON_SHIFT_PON_PMOPT_SLP_PERPLL_EN            14
#define AON_BIT_PON_PMOPT_SLP_PERPLL_EN              ((u32)0x00000001 << 14)                             /*!<R/W 0  1: enable Peri PLL when enter into sleep mode; 0: disable PeriPLL */
#define AON_SHIFT_PON_PMOPT_SLP_SYSPLL_EN            13
#define AON_BIT_PON_PMOPT_SLP_SYSPLL_EN              ((u32)0x00000001 << 13)                             /*!<R/W 0  1: enable syspem PLL when enter into sleep mode; 0: disable SYSPLL */
#define AON_SHIFT_PON_PMOPT_SLP_XTAL_EN              12
#define AON_BIT_PON_PMOPT_SLP_XTAL_EN                ((u32)0x00000001 << 12)                             /*!<R/W 0  1: enable XTAL when enter into sleep mode; 0: disable XTAL */
#define AON_SHIFT_PON_PMOPT_SLP_XTAL_LP_EN           11
#define AON_BIT_PON_PMOPT_SLP_XTAL_LP_EN             ((u32)0x00000001 << 11)                             /*!<R/W 0  1: enable XTAL Low Power Mode when enter into sleep mode; 0: disable XTAL */
#define AON_SHIFT_PON_PMOPT_SLP_EN_SOC               10
#define AON_BIT_PON_PMOPT_SLP_EN_SOC                 ((u32)0x00000001 << 10)                             /*!<R/W 0  1: power enable SOC platform when enter into sleep mode; 0: power off SoC domain */
#define AON_SHIFT_PON_PMOPT_SLP_EXT_SWR_EN           9
#define AON_BIT_PON_PMOPT_SLP_EXT_SWR_EN             ((u32)0x00000001 << 9)                              /*!<R/W 0  1: Enable External SWR DCORE 0: Disable External SWR DCORE */
#define AON_SHIFT_PON_PMOPT_SLP_EN_PWM_SRC           7
#define AON_BIT_PON_PMOPT_SLP_EN_PWM_SRC             ((u32)0x00000001 << 7)                              /*!<R/W 0  1: power enable SWR/LDO output heavy loading current mode when enter into sleep mode; 0: disable SWR/LDO output heavy loading mode */
#define AON_SHIFT_PON_PMOPT_SLP_EN_SWR_SRC           6
#define AON_BIT_PON_PMOPT_SLP_EN_SWR_SRC             ((u32)0x00000001 << 6)                              /*!<R/W 0  1: power enable SWR/LDO 1.8V when enter into sleep mode; 0: disable SWR/LDO */
#define AON_SHIFT_PON_PMOPT_SLP_EN_WLON_MODE         4
#define AON_MASK_PON_PMOPT_SLP_EN_WLON_MODE          ((u32)0x00000003 << 4)                              /*!<R/W 0  00: disable LDO_WLON 01: power enable LDO_WLON when enter into sleep mode; 10: enable LDO_WLON Bypass Mode when enter into sleep mode;  */
#define AON_SHIFT_PON_PMOPT_SLP_EN                   1
#define AON_BIT_PON_PMOPT_SLP_EN                     ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable PON Domain when enter into sleep mode; 0: Disable PON Domain */
#define AON_SHIFT_PON_PMOPT_SLP_EN_4M                0
#define AON_BIT_PON_PMOPT_SLP_EN_4M                  ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable OSC 4MHz when enter into sleep mode; 0: Disable OSC 4MHz */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_OTP_CTRL_0
 * @brief                                            (@ 0X120)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_OTP_ENT                            31
#define AON_BIT_OTP_ENT                              ((u32)0x00000001 << 31)                             /*!<R/W 1  OTP IP enable time (OTP SPEC Tcs >10us) For input clock 12MHz 0:24us 1:36us default value : 1 */
#define AON_SHIFT_RSVD16                             28
#define AON_MASK_RSVD16                              ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_RDT                            27
#define AON_BIT_OTP_RDT                              ((u32)0x00000001 << 27)                             /*!<R/W 1  OTP Clock cycle time (OTP SPEC Tcyc >80ns) For input clock 12MHz 0:166.66ns 1:249.9ns default value : 1 */
#define AON_SHIFT_RSVD17                             24
#define AON_MASK_RSVD17                              ((u32)0x00000007 << 24)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_PGTS                           20
#define AON_MASK_OTP_PGTS                            ((u32)0x0000000F << 20)                             /*!<R/W 0011  OTP Program Setup time and Recovery time. In the unit of cycle time. OTP SPEC 5us< Tpps=Tppr <100us For input clock 12MHz 0 : 5us, 1 : 11us, 2 : 17us, 3 : 23us, 4 : 30us, 5 : 36us , 6 : 42us , 7 : 49us 8 : 55us, 9 : 61us , A : 68us , B : 74us C : 80us, D : 87us , E : 93us , F : 100us default value : 3 */
#define AON_SHIFT_OTP_BURST                          19
#define AON_BIT_OTP_BURST                            ((u32)0x00000001 << 19)                             /*!<R/W 0  Efuse Read / Write Burst Mode Enable 0 : Disable 1 : Enable */
#define AON_SHIFT_OTP_TEST_SEL                       16
#define AON_MASK_OTP_TEST_SEL                        ((u32)0x00000007 << 16)                             /*!<R/W 0  OTP Test Mode Selection: 000: User Mode 001: Initial Margin Read Mode 010: Program Margin Read Mode 100: Auto Repair Margin Read Mode (Only in Pro2) 101: Repair Margin Read Mode 110: Repair Check Mode 111: Repair Program Mode Bit18=0:User mode and Test mode Bit18=1: Use Repair mode */
#define AON_SHIFT_OTP_TROW_EN                        15
#define AON_BIT_OTP_TROW_EN                          ((u32)0x00000001 << 15)                             /*!<R/W 0  OTP Test Row Select: 0: Test Row Function Disable 1: Test Row Function Enable */
#define AON_SHIFT_OTP_ERR_FLAG                       14
#define AON_BIT_OTP_ERR_FLAG                         ((u32)0x00000001 << 14)                             /*!<R 0  OTP Error Flag: When OTP read/write and test mode mapping process Error, this flag will be set to 1  */
#define AON_SHIFT_RSVD18                             12
#define AON_MASK_RSVD18                              ((u32)0x00000003 << 12)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_DSB_EN                         11
#define AON_BIT_OTP_DSB_EN                           ((u32)0x00000001 << 11)                             /*!<R/W 0  0: OTP Deep Standby Mode Disable 1 : OTP Deep Standby Mode Enable  */
#define AON_SHIFT_RSVD19                             0
#define AON_MASK_RSVD19                              ((u32)0x000007FF << 0)                              /*!<R/W 0  RSVD */
#else
#define AON_SHIFT_OTP_ENT                            31
#define AON_BIT_OTP_ENT                              ((u32)0x00000001 << 31)                             /*!<R/W 1  OTP IP enable time (OTP SPEC Tcs >10us) For input clock 12MHz 0:24us 1:36us default value : 1 */
#define AON_SHIFT_RSVD16                             28
#define AON_MASK_RSVD16                              ((u32)0x00000007 << 28)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_RDT                            27
#define AON_BIT_OTP_RDT                              ((u32)0x00000001 << 27)                             /*!<R/W 1  OTP Clock cycle time (OTP SPEC Tcyc >80ns) For input clock 12MHz 0:166.66ns 1:249.9ns default value : 1 */
#define AON_SHIFT_RSVD17                             26
#define AON_BIT_RSVD17                               ((u32)0x00000001 << 26)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_TPPS                           24
#define AON_MASK_OTP_TPPS                            ((u32)0x00000003 << 24)                             /*!<R/W 10  OTP Program Setup time and Recovery time. In the unit of cycle time. OTP SPEC 5us< Tpps <20us For input clock 12MHz 0 : 5us, 1 : 10us, 2 : 12.5us, 3 : 20us,  */
#define AON_SHIFT_OTP_PGTS                           20
#define AON_MASK_OTP_PGTS                            ((u32)0x0000000F << 20)                             /*!<R/W 0011  OTP Program Setup time and Recovery time. In the unit of cycle time. OTP SPEC 5us< Tpps=Tppr <100us For input clock 12MHz 0 : 5us, 1 : 11us, 2 : 17us, 3 : 23us, 4 : 30us, 5 : 36us , 6 : 42us , 7 : 49us 8 : 55us, 9 : 61us , A : 68us , B : 74us C : 80us, D : 87us , E : 93us , F : 100us default value : 3 */
#define AON_SHIFT_OTP_BURST                          19
#define AON_BIT_OTP_BURST                            ((u32)0x00000001 << 19)                             /*!<R/W 0  Efuse Read / Write Burst Mode Enable 0 : Disable 1 : Enable */
#define AON_SHIFT_OTP_TEST_SEL                       16
#define AON_MASK_OTP_TEST_SEL                        ((u32)0x00000007 << 16)                             /*!<R/W 0  OTP Test Mode Selection: 000: User Mode 001: Initial Margin Read Mode 010: Program Margin Read Mode 100: Auto Repair Margin Read Mode (Only in Pro2) 101: Repair Margin Read Mode 110: Repair Check Mode 111: Repair Program Mode Bit18=0:User mode and Test mode Bit18=1: Use Repair mode */
#define AON_SHIFT_OTP_TROW_EN                        15
#define AON_BIT_OTP_TROW_EN                          ((u32)0x00000001 << 15)                             /*!<R/W 0  OTP Test Row Select: 0: Test Row Function Disable 1: Test Row Function Enable */
#define AON_SHIFT_OTP_ERR_FLAG                       14
#define AON_BIT_OTP_ERR_FLAG                         ((u32)0x00000001 << 14)                             /*!<R 0  OTP Error Flag: When OTP read/write and test mode mapping process Error, this flag will be set to 1  */
#define AON_SHIFT_OTP_TCOL_EN                        13
#define AON_BIT_OTP_TCOL_EN                          ((u32)0x00000001 << 13)                             /*!<R/W 0  OTP Test Column Select: 0: Test Column Function Disable 1: Test Column Function Enable */
#define AON_SHIFT_OTP_HTEMP_EN                       12
#define AON_BIT_OTP_HTEMP_EN                         ((u32)0x00000001 << 12)                             /*!<R/W 0  OTP High Temperature Test Mode Enable 0: High Temperature Test ModeDisable 1: High Temperature Test Mode Enable */
#define AON_SHIFT_OTP_DSB_EN                         11
#define AON_BIT_OTP_DSB_EN                           ((u32)0x00000001 << 11)                             /*!<R/W 0  0: OTP Deep Standby Mode Disable 1 : OTP Deep Standby Mode Enable  */
#define AON_SHIFT_RSVD18                             0
#define AON_MASK_RSVD18                              ((u32)0x000007FF << 0)                              /*!<R/W 0  RSVD */
#endif
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_OTP_CTRL_1
 * @brief                                            (@ 0X124)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_RSVD20                             28
#define AON_MASK_RSVD20                              ((u32)0x0000000F << 28)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_RSVD21                             20
#define AON_MASK_RSVD21                              ((u32)0x000000FF << 20)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_RSVD22                             19
#define AON_BIT_RSVD22                               ((u32)0x00000001 << 19)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_RSVD23                             16
#define AON_MASK_RSVD23                              ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_RSVD24                             15
#define AON_BIT_RSVD24                               ((u32)0x00000001 << 15)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_RB_CTRL                        14
#define AON_BIT_OTP_RB_CTRL                          ((u32)0x00000001 << 14)                             /*!<R/W 0  OTP Reboot (related to PTRIM) Control After Repair Program Operation 0: Disable reboot poreation after Repair Program 1: Enable reboot poreation after Repair Program */
#define AON_SHIFT_OTP_DLY2SHDN                       12
#define AON_MASK_OTP_DLY2SHDN                        ((u32)0x00000003 << 12)                             /*!<R/W 0  OTP delay time to idle or shutdown state after a requested command done. Consider about level shift between For input clock 12MHz 2'b00: 10us 2'b01: 20us 2'b10: 30us 2'b11: 50us */
#define AON_SHIFT_RSVD25                             6
#define AON_MASK_RSVD25                              ((u32)0x0000003F << 6)                              /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_PGTW                           4
#define AON_MASK_OTP_PGTW                            ((u32)0x00000003 << 4)                              /*!<R/W 1  OTP Program Pulse width Time: (OTP SPEC 10us<Tpw<15us) For Input clock 40Mhz 0 : 10us , 1 : 12.5us, 2 : 15us, 3: 15us, default value : 1 */
#define AON_SHIFT_OTP_VD                             2
#define AON_MASK_OTP_VD                              ((u32)0x00000003 << 2)                              /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_PGITV                          0
#define AON_MASK_OTP_PGITV                           ((u32)0x00000003 << 0)                              /*!<R/W 1  OTP Program Pulse Interval Time : (OTP SPEC 1us<Tpwi<5us) For Input clock 40Mhz 0 : 1us, 1 : 3us, 2 : 5us, 3 : 5us, default value : 1 */
#else
#define AON_SHIFT_RSVD19                             28
#define AON_MASK_RSVD19                              ((u32)0x0000000F << 28)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_RSVD20                             20
#define AON_MASK_RSVD20                              ((u32)0x000000FF << 20)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_RSVD21                             19
#define AON_BIT_RSVD21                               ((u32)0x00000001 << 19)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_RSVD22                             16
#define AON_MASK_RSVD22                              ((u32)0x00000007 << 16)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_RSVD23                             15
#define AON_BIT_RSVD23                               ((u32)0x00000001 << 15)                             /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_RB_CTRL                        14
#define AON_BIT_OTP_RB_CTRL                          ((u32)0x00000001 << 14)                             /*!<R/W 0  OTP Reboot (related to PTRIM) Control After Repair Program Operation 0: Disable reboot poreation after Repair Program 1: Enable reboot poreation after Repair Program */
#define AON_SHIFT_OTP_DLY2SHDN                       12
#define AON_MASK_OTP_DLY2SHDN                        ((u32)0x00000003 << 12)                             /*!<R/W 0  OTP delay time to idle or shutdown state after a requested command done. Consider about level shift between For input clock 12MHz 2'b00: 10us 2'b01: 20us 2'b10: 30us 2'b11: 50us */
#define AON_SHIFT_RSVD24                             6
#define AON_MASK_RSVD24                              ((u32)0x0000003F << 6)                              /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_PGTW                           4
#define AON_MASK_OTP_PGTW                            ((u32)0x00000003 << 4)                              /*!<R/W 1  OTP Program Pulse width Time: (OTP SPEC 10us<Tpw<15us) For Input clock 40Mhz 0 : 10us , 1 : 12.5us, 2 : 15us, 3: 15us, default value : 1 */
#define AON_SHIFT_OTP_VD                             2
#define AON_MASK_OTP_VD                              ((u32)0x00000003 << 2)                              /*!<R/W 0  RSVD */
#define AON_SHIFT_OTP_PGITV                          0
#define AON_MASK_OTP_PGITV                           ((u32)0x00000003 << 0)                              /*!<R/W 1  OTP Program Pulse Interval Time : (OTP SPEC 1us<Tpwi<5us) For Input clock 40Mhz 0 : 1us, 1 : 3us, 2 : 5us, 3 : 5us, default value : 1 */
#endif
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_OTP_AL_CTRL_STS
 * @brief                                            (@ 0X128)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_RSVD26                             14
#define AON_MASK_RSVD26                              ((u32)0x0003FFFF << 14)                             /*!<R/W 0  Reserved */
#define AON_SHIFT_OTP_AL_SYSON_STS                   12
#define AON_MASK_OTP_AL_SYSON_STS                    ((u32)0x00000003 << 12)                             /*!<R/W 00  OTP SYSON Autoload Result Status 00: RSVD 01: Autoload successful 10: RSVD 11: Autoload Failed because of OTP ID check failed */
#define AON_SHIFT_OTP_AL_PON_STS                     10
#define AON_MASK_OTP_AL_PON_STS                      ((u32)0x00000003 << 10)                             /*!<R/W1C 00  OTP PON Autoload Result Status 00: RSVD 01: Autoload successful 10: RSVD 11: Autoload Failed because of OTP ID check failed */
#define AON_SHIFT_OTP_AL_AON_STS                     8
#define AON_MASK_OTP_AL_AON_STS                      ((u32)0x00000003 << 8)                              /*!<R/W1C 00  OTP AON Autoload Result Status 00: RSVD 01: Autoload successful 10: RSVD 11: Autoload Failed because of OTP ID check failed */
#define AON_SHIFT_RSVD27                             7
#define AON_BIT_RSVD27                               ((u32)0x00000001 << 7)                              /*!<R/W 0  Reserved */
#define AON_SHIFT_OTP_ALDN_SYSON_STS                 6
#define AON_BIT_OTP_ALDN_SYSON_STS                   ((u32)0x00000001 << 6)                              /*!<R/W 0  OTP SYSON Autoload Done Status PMC/CPU should clear this bit before enabling autoload process. This bit only represents done status but not autoload resutl 0: SYSON autoload is not done 1: SYSON autoload is done */
#define AON_SHIFT_OTP_ALDN_PON_STS                   5
#define AON_BIT_OTP_ALDN_PON_STS                     ((u32)0x00000001 << 5)                              /*!<R/W1C 0  OTP PON Autoload Done Status PMC/CPU should clear this bit before enabling autoload process. This bit only represents done status but not autoload resutl 0: PON autoload is not done 1: PON autoload is done */
#define AON_SHIFT_OTP_ALDN_AON_STS                   4
#define AON_BIT_OTP_ALDN_AON_STS                     ((u32)0x00000001 << 4)                              /*!<R/W1C 0  OTP AON Autoload Done Status PMC/CPU should clear this bit before enabling autoload process. This bit only represents done status but not autoload resutl 0: AON autoload is not done 1: AON autoload is done */
#define AON_SHIFT_RSVD28                             3
#define AON_BIT_RSVD28                               ((u32)0x00000001 << 3)                              /*!<R/W 0  Reserved */
#define AON_SHIFT_OTP_AL_SYSON_EN                    2
#define AON_BIT_OTP_AL_SYSON_EN                      ((u32)0x00000001 << 2)                              /*!<R/W 0  OTP SYSON Autoload Control If PMC/CPU wants to do this autoload, autoload done status and this bit should be cleared first. After cleared, PMC/CPU could set this bit first and then set mode to Aiutolaod in OTP_AS_CTRL 0: Enable SYSON autoload 1: Enable SYSON autoload */
#define AON_SHIFT_OTP_AL_PON_EN                      1
#define AON_BIT_OTP_AL_PON_EN                        ((u32)0x00000001 << 1)                              /*!<R/W 0  OTP PON Autoload Control If PMC/CPU wants to do this autoload, autoload done status and this bit should be cleared first. After cleared, PMC/CPU could set this bit first and then set mode to Aiutolaod in OTP_AS_CTRL 0: Enable PON autoload 1: Enable PON autoload */
#define AON_SHIFT_OTP_AL_AON_EN                      0
#define AON_BIT_OTP_AL_AON_EN                        ((u32)0x00000001 << 0)                              /*!<R/W 0  OTP AON Autoload Control If PMC/CPU wants to do this autoload, autoload done status and this bit should be cleared first. After cleared, PMC/CPU could set this bit first and then set mode to Aiutolaod in OTP_AS_CTRL 0: Enable AON autoload 1: Enable AON autoload */
#else
#define AON_SHIFT_RSVD25                             14
#define AON_MASK_RSVD25                              ((u32)0x0003FFFF << 14)                             /*!<R/W 0  Reserved */
#define AON_SHIFT_OTP_AL_SYSON_STS                   12
#define AON_MASK_OTP_AL_SYSON_STS                    ((u32)0x00000003 << 12)                             /*!<R/W 00  OTP SYSON Autoload Result Status 00: RSVD 01: Autoload successful 10: RSVD 11: Autoload Failed because of OTP ID check failed */
#define AON_SHIFT_OTP_AL_PON_STS                     10
#define AON_MASK_OTP_AL_PON_STS                      ((u32)0x00000003 << 10)                             /*!<R/W1C 01  OTP PON Autoload Result Status 00: RSVD 01: Autoload successful 10: RSVD 11: Autoload Failed because of OTP ID check failed */
#define AON_SHIFT_OTP_AL_AON_STS                     8
#define AON_MASK_OTP_AL_AON_STS                      ((u32)0x00000003 << 8)                              /*!<R/W1C 01  OTP AON Autoload Result Status 00: RSVD 01: Autoload successful 10: RSVD 11: Autoload Failed because of OTP ID check failed */
#define AON_SHIFT_RSVD26                             7
#define AON_BIT_RSVD26                               ((u32)0x00000001 << 7)                              /*!<R/W 0  Reserved */
#define AON_SHIFT_OTP_ALDN_SYSON_STS                 6
#define AON_BIT_OTP_ALDN_SYSON_STS                   ((u32)0x00000001 << 6)                              /*!<R/W 0  OTP SYSON Autoload Done Status PMC/CPU should clear this bit before enabling autoload process. This bit only represents done status but not autoload resutl 0: SYSON autoload is not done 1: SYSON autoload is done */
#define AON_SHIFT_OTP_ALDN_PON_STS                   5
#define AON_BIT_OTP_ALDN_PON_STS                     ((u32)0x00000001 << 5)                              /*!<R/W1C 0  OTP PON Autoload Done Status PMC/CPU should clear this bit before enabling autoload process. This bit only represents done status but not autoload resutl 0: PON autoload is not done 1: PON autoload is done */
#define AON_SHIFT_OTP_ALDN_AON_STS                   4
#define AON_BIT_OTP_ALDN_AON_STS                     ((u32)0x00000001 << 4)                              /*!<R/W1C 0  OTP AON Autoload Done Status PMC/CPU should clear this bit before enabling autoload process. This bit only represents done status but not autoload resutl 0: AON autoload is not done 1: AON autoload is done */
#define AON_SHIFT_RSVD27                             3
#define AON_BIT_RSVD27                               ((u32)0x00000001 << 3)                              /*!<R/W 0  Reserved */
#define AON_SHIFT_OTP_AL_SYSON_EN                    2
#define AON_BIT_OTP_AL_SYSON_EN                      ((u32)0x00000001 << 2)                              /*!<R/W 0  OTP SYSON Autoload Control If PMC/CPU wants to do this autoload, autoload done status and this bit should be cleared first. After cleared, PMC/CPU could set this bit first and then set mode to Aiutolaod in OTP_AS_CTRL 0: Enable SYSON autoload 1: Enable SYSON autoload */
#define AON_SHIFT_OTP_AL_PON_EN                      1
#define AON_BIT_OTP_AL_PON_EN                        ((u32)0x00000001 << 1)                              /*!<R/W 0  OTP PON Autoload Control If PMC/CPU wants to do this autoload, autoload done status and this bit should be cleared first. After cleared, PMC/CPU could set this bit first and then set mode to Aiutolaod in OTP_AS_CTRL 0: Enable PON autoload 1: Enable PON autoload */
#define AON_SHIFT_OTP_AL_AON_EN                      0
#define AON_BIT_OTP_AL_AON_EN                        ((u32)0x00000001 << 0)                              /*!<R/W 0  OTP AON Autoload Control If PMC/CPU wants to do this autoload, autoload done status and this bit should be cleared first. After cleared, PMC/CPU could set this bit first and then set mode to Aiutolaod in OTP_AS_CTRL 0: Enable AON autoload 1: Enable AON autoload */
#endif
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_OTP_PMC_DBG_CTRL
 * @brief                                            (@ 0X12C)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_RSVD29                             12
#define AON_MASK_RSVD29                              ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Reserve */
#else
#define AON_SHIFT_RSVD28                             12
#define AON_MASK_RSVD28                              ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Reserve */
#endif
#define AON_SHIFT_OTP_DBG_GRP_SEL                    10
#define AON_MASK_OTP_DBG_GRP_SEL                     ((u32)0x00000003 << 10)                             /*!<R/W 0   OTP debug group select */
#define AON_SHIFT_OTP_DBG_EN                         9
#define AON_BIT_OTP_DBG_EN                           ((u32)0x00000001 << 9)                              /*!<R/W 0  OTP debug enable */
#define AON_SHIFT_OPT_PWR_CTRL_GNT                   8
#define AON_BIT_OPT_PWR_CTRL_GNT                     ((u32)0x00000001 << 8)                              /*!<R/W 0  The grant control for OTP power control register (OTP_PWR_CTRL) 1: Enable access to OTP power control register 0: Disable access to OTP power control register */
#define AON_SHIFT_OTP_BURN_GNT                       0
#define AON_MASK_OTP_BURN_GNT                        ((u32)0x000000FF << 0)                              /*!<R/W 0  The Grant Code for OTP Program Operation Need write 0x69 value before any program operation to OTP controller  */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_OTP_PWR_CTRL
 * @brief                                            (@ 0X130)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_RSVD30                             22
#define AON_MASK_RSVD30                              ((u32)0x000003FF << 22)                             /*!<R/W 0  Reserve */
#else
#define AON_SHIFT_RSVD29                             22
#define AON_MASK_RSVD29                              ((u32)0x000003FF << 22)                             /*!<R/W 0  Reserve */
#endif
#define AON_SHIFT_OTP_ISO2SYSON_STS                  21
#define AON_BIT_OTP_ISO2SYSON_STS                    ((u32)0x00000001 << 21)                             /*!<R 1  For status of isolation to SYSON 0: Isolation to SYSON is disabled. 1: Isolation to SYSON is enabled. */
#define AON_SHIFT_OTP_ISO2PON_STS                    20
#define AON_BIT_OTP_ISO2PON_STS                      ((u32)0x00000001 << 20)                             /*!<R 1  For status of isolation to PON 0: Isolation to PON is disabled. 1: Isolation to PON is enabled. */
#define AON_SHIFT_OTP_ISO2AON_STS                    19
#define AON_BIT_OTP_ISO2AON_STS                      ((u32)0x00000001 << 19)                             /*!<R 1  For status of isolation to AON 0: Isolation to AON is disabled. 1: Isolation to AON is enabled. */
#define AON_SHIFT_OTP_PC_BG_STS                      18
#define AON_BIT_OTP_PC_BG_STS                        ((u32)0x00000001 << 18)                             /*!<R 0  Big Power Cut Status 0: Big power cut in disabled state 1: Big power cut in enabled state. */
#define AON_SHIFT_OTP_PC_SL_STS                      17
#define AON_BIT_OTP_PC_SL_STS                        ((u32)0x00000001 << 17)                             /*!<R 0  Small Power Cut Status 0: Small power cut in disabled state 1: Small power cut in enabled state. */
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_RSVD31                             8
#define AON_MASK_RSVD31                              ((u32)0x000001FF << 8)                              /*!<R/W 0  Reserve */
#else
#define AON_SHIFT_RSVD30                             8
#define AON_MASK_RSVD30                              ((u32)0x000001FF << 8)                              /*!<R/W 0  Reserve */
#endif
#define AON_SHIFT_OTP_PGCLK_GT_EN                    7
#define AON_BIT_OTP_PGCLK_GT_EN                      ((u32)0x00000001 << 7)                              /*!<R/W 1  For OTP program clock source gate control. (40MHz) 0: Program clock source is NOT gated. 1: Program clock source is gated. */
#define AON_SHIFT_OTP_RDCLK_GT_EN                    6
#define AON_BIT_OTP_RDCLK_GT_EN                      ((u32)0x00000001 << 6)                              /*!<R/W 0  For OTP read clock source gate control. (12MHz) 0: Read clock source is NOT gated. 1: Read clock source is gated. */
#define AON_SHIFT_OTP_ISO2SYSON_EN                   5
#define AON_BIT_OTP_ISO2SYSON_EN                     ((u32)0x00000001 << 5)                              /*!<R/W 1  For OTP isolation to SYSON control. 0: Isolation to SYSON is disabled. 1: Isolation to SYSON is enabled. */
#define AON_SHIFT_OTP_ISO2PON_EN                     4
#define AON_BIT_OTP_ISO2PON_EN                       ((u32)0x00000001 << 4)                              /*!<R/W 1  For OTP isolation to PON control. 0: Isolation to PON is disabled. 1: Isolation to PON is enabled. */
#define AON_SHIFT_OTP_ISO2AON_EN                     3
#define AON_BIT_OTP_ISO2AON_EN                       ((u32)0x00000001 << 3)                              /*!<R/W 1  For OTP isolation to AON control. 0: Isolation to AON is disabled. 1: Isolation to AON is enabled.  */
#define AON_SHIFT_OTP_PC_BG_EN                       2
#define AON_BIT_OTP_PC_BG_EN                         ((u32)0x00000001 << 2)                              /*!<R/W 0  For Big Power cut control of VDD (0.9V) and VDD2 (3.3V) 0: Big power cut disabled. Therefore power is invalid 1: Big power cut enabled. Therefore power is valid  */
#define AON_SHIFT_OTP_PC_SL_EN                       1
#define AON_BIT_OTP_PC_SL_EN                         ((u32)0x00000001 << 1)                              /*!<R/W 0  For small Power cut control of VDD (0.9V) and VDD2 (3.3V) 0: Small power cut disabled. Therefore power is invalid 1: Small power cut enabled. Therefore power is valid */
#define AON_SHIFT_OTP_CTRLER_FEN                     0
#define AON_BIT_OTP_CTRLER_FEN                       ((u32)0x00000001 << 0)                              /*!<R/W 0  OTP Controller (Loader) Enable. 0: Disable OTP controller 1: Enable OTP controller */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_OTP_AS_CTRL_A
 * @brief                                            (@ 0X134)
 * @{
 *****************************************************************************/
#define AON_SHIFT_OTP_MODE_SEL                       30
#define AON_MASK_OTP_MODE_SEL                        ((u32)0x00000003 << 30)                             /*!<R/W 0  OTP controller Mode (command) selection Program to this field could trigger OTP controller to do related command operation. 2'b00 :Read 2'b10 :Write 2'b01 :Autoload Enable 2'b11 :Compare Secure Data Enable */
#define AON_SHIFT_OTP_RDY                            29
#define AON_BIT_OTP_RDY                              ((u32)0x00000001 << 29)                             /*!<R/W1C 0  OTP Operation Ready bit 0: OTP controller has NOT done a requested command. 1: OTP controller has done a requested command. Note : HW set , SW clear Note before any operations, HW/SW should clear ready bit first Note: For autoload operation, this bit is not used for autoload done status. Autoload done status of each zone is shown in 0x40009128[6:4] */
#define AON_SHIFT_OTP_COMP_RESULT                    28
#define AON_BIT_OTP_COMP_RESULT                      ((u32)0x00000001 << 28)                             /*!<R/W1C 0  compare result 0 : PASS 1 : FAIL Note : HW set , SW clear */
#define AON_SHIFT_OTP_OP_EN                          27
#define AON_BIT_OTP_OP_EN                            ((u32)0x00000001 << 27)                             /*!<W1Once 0  OTP controller operation enable control This bit could be set to 1 by software and automatically cleared to 0 by hardware 0: OTP controller does NOT perforam any operations even B_OTP_MODE_SEL is given by a valid value. 1: OTP controller performs corresponding operation according to B_OTP_MODE_SEL, B_OTP_ADDR and B_OTP_DATA */
#define AON_SHIFT_OTP_ADDR                           16
#define AON_MASK_OTP_ADDR                            ((u32)0x000007FF << 16)                             /*!<R/W 0  Access Address */
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_RSVD32                             9
#define AON_MASK_RSVD32                              ((u32)0x0000007F << 9)                              /*!<R/W 0x00  Reserved */
#else
#define AON_SHIFT_RSVD31                             9
#define AON_MASK_RSVD31                              ((u32)0x0000007F << 9)                              /*!<R/W 0x00  Reserved */
#endif
#define AON_SHIFT_OTP_AUTO_RDCHK_CTRL                8
#define AON_BIT_OTP_AUTO_RDCHK_CTRL                  ((u32)0x00000001 << 8)                              /*!<R/W 0  Automatic Read Check Control When this bit is set to 1 in OTP write mode, OTP controller would perform a write-read-check process automatically. Read back data would be compared with original write data and the result would be updated in bit28 of this register 0: Disable auto read check mechanism 1: Enable auto read check mechanism */
#define AON_SHIFT_OTP_DATA                           0
#define AON_MASK_OTP_DATA                            ((u32)0x000000FF << 0)                              /*!<R/W 0  Access Data [7:0] : Read / Write/Data to be compared */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_OTP_SCAN_TEST_A
 * @brief                                            (@ 0X138)
 * @{
 *****************************************************************************/
#define AON_SHIFT_AX_EF_CRES_SEL                     31
#define AON_BIT_AX_EF_CRES_SEL                       ((u32)0x00000001 << 31)                             /*!<R/W 0  1: for debug , 0: for normal */
#define AON_SHIFT_AX_EF_RSVD                         30
#define AON_BIT_AX_EF_RSVD                           ((u32)0x00000001 << 30)                             /*!<R/W 0  Reserved */
#define AON_SHIFT_AX_EF_SCAN_SADR                    19
#define AON_MASK_AX_EF_SCAN_SADR                     ((u32)0x000007FF << 19)                             /*!<R/W 0  EFuse Scan start Address (unit in byte) */
#define AON_SHIFT_AX_EF_SCAN_EADR                    8
#define AON_MASK_AX_EF_SCAN_EADR                     ((u32)0x000007FF << 8)                              /*!<R/W 0  EFuse Scan End address */
#define AON_SHIFT_AX_EF_SCAN_TRPT                    7
#define AON_BIT_AX_EF_SCAN_TRPT                      ((u32)0x00000001 << 7)                              /*!<R/W1C 0  Test Scan Report: 1 : Fail, 0 : OK */
#define AON_SHIFT_AX_EF_SCAN_FTHR                    0
#define AON_MASK_AX_EF_SCAN_FTHR                     ((u32)0x0000007F << 0)                              /*!<R/W 0  Threshold number of bit error If [6:0]=1 and scan check have any cell bit wasn't equal 1b'1(default). It will report Fail. If [6:0]=2, it mean allow one cell bit fail while HW scan was finlish and the [6:0] will write to 0 and then check result([7])  */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_OTP_PRCT_CTRL
 * @brief                                            (@ 0X13C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_B_OTP_SZ_WL_CTRL                   31
#define AON_BIT_B_OTP_SZ_WL_CTRL                     ((u32)0x00000001 << 31)                             /*!<R/W Once 0  Secure Zone Write Lock Control 0: OTP write lock control is disabed. 1: OTP write lock control is enabled. */
#define AON_SHIFT_B_OTP_SSZ_CRC_STS                  22
#define AON_MASK_B_OTP_SSZ_CRC_STS                   ((u32)0x000001FF << 22)                             /*!<R/W1C 0x000000  Super Secure Zone Entry CRC Status Each bit represents one entry CRC status. 1: CRC check failed 0: CRC check passed Bit22 for HUK Bit23 for HUK reserved 32byte Bit24 for JTAG Secure Key1 Bit25 for JTAG Secure Key2 Bit26 for JTAG non-Secure Key1 Bit27 for JTAG non-Secure Key2 Bit28 for RSIP(SCE) Key1 Bit29 for RSIP(SCE) Key2 Bit30 for Reserved 32byte */
#define AON_SHIFT_B_OTP_SZ_CRC_STS                   13
#define AON_MASK_B_OTP_SZ_CRC_STS                    ((u32)0x000001FF << 13)                             /*!<R/W1C 0  Secure Zone Entry CRC Status Each bit represents one entry CRC status. 1: CRC check failed 0: CRC check passed Bit13 for ROTPK1 Bit14 for RTOPK2 Bit15 for IPSec Cipher Key1 Bit16 for IPSec Cipher Key2 Bit17 for ECDSA Pirvate Key1 Bit18 for ECDSA Pirvate Key2 Bit20-19 for Reserved 64byte Bit21 Reserved */
#define AON_SHIFT_B_OTP_LZ_CRC_ER_ADDR               3
#define AON_MASK_B_OTP_LZ_CRC_ER_ADDR                ((u32)0x000003FF << 3)                              /*!<R 0x000  OTP physical address of the first byte of the first CRC check error entry */
#define AON_SHIFT_B_OTP_LZ_CRC_STS                   2
#define AON_BIT_B_OTP_LZ_CRC_STS                     ((u32)0x00000001 << 2)                              /*!<R/W1C 0  Logical Zone CRC Status 1: CRC check failed 0: CRC check passed  */
#define AON_SHIFT_B_OTP_SC_CRC_STS                   1
#define AON_BIT_B_OTP_SC_CRC_STS                     ((u32)0x00000001 << 1)                              /*!<R/W1C 0  Secure Control Zone CRC Status 1: CRC check failed 0: CRC check passed  */
#define AON_SHIFT_B_OTP_PRCT_CTRL                    0
#define AON_BIT_B_OTP_PRCT_CTRL                      ((u32)0x00000001 << 0)                              /*!<R/W 1  OTP Protect Mechanism Control This bit is used to control CRC check protect mechanism is enabled or not. 0: Disable CRC check report generation 1: Enable CRC check report generation */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SW_BOOT0
 * @brief                                            (@ 0X140)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SW0                                0
#define AON_MASK_SW0                                 ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  SW Control */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_FAST_RESUME
 * @brief                                            (@ 0X144)
 * @{
 *****************************************************************************/
#define AON_SHIFT_AON_FAST_RESUME                    0
#define AON_MASK_AON_FAST_RESUME                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  SW Control */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SW_BOOT1
 * @brief                                            (@ 0X148)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SW1                                0
#define AON_MASK_SW1                                 ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  SW Control */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SW_BOOT2
 * @brief                                            (@ 0X14C)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SW2                                0
#define AON_MASK_SW2                                 ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  SW Control */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SW_BOOT3
 * @brief                                            (@ 0X150)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SW3                                0
#define AON_MASK_SW3                                 ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  SW Control */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_SW_BOOT4
 * @brief                                            (@ 0X154)
 * @{
 *****************************************************************************/
#define AON_SHIFT_SW4                                0
#define AON_MASK_SW4                                 ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  SW Control */
/** @} */

/**************************************************************************//**
 * @defgroup AON_REG_AON_WLMAC_MEM_CNTRL
 * @brief                                            (@ 0X158)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define AON_SHIFT_RSVD33                             22
#define AON_MASK_RSVD33                              ((u32)0x000003FF << 22)                             /*!<R/W 0x0   */
#else
#define AON_SHIFT_RSVD32                             22
#define AON_MASK_RSVD32                              ((u32)0x000003FF << 22)                             /*!<R/W 0x0   */
#endif
#define AON_SHIFT_TMCK_WLMAC                         21
#define AON_BIT_TMCK_WLMAC                           ((u32)0x00000001 << 21)                             /*!<R/W 0x0  internal timing bypass wlan mac mmory cells */
#define AON_SHIFT_DVS_WLMAC                          17
#define AON_MASK_DVS_WLMAC                           ((u32)0x0000000F << 17)                             /*!<R/W 0x0  delay option wlan mac memory cells */
#define AON_SHIFT_DVSE_WLMAC_ROM                     16
#define AON_BIT_DVSE_WLMAC_ROM                       ((u32)0x00000001 << 16)                             /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_AXI_TXDMA               15
#define AON_BIT_DVSE_WLMAC_AXI_TXDMA                 ((u32)0x00000001 << 15)                             /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMCU_IRAM                    14
#define AON_BIT_DVSE_WLMCU_IRAM                      ((u32)0x00000001 << 14)                             /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMCU_ERAM1                   13
#define AON_BIT_DVSE_WLMCU_ERAM1                     ((u32)0x00000001 << 13)                             /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMCU_ERAM0                   12
#define AON_BIT_DVSE_WLMCU_ERAM0                     ((u32)0x00000001 << 12)                             /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMCU_DRAM                    11
#define AON_BIT_DVSE_WLMCU_DRAM                      ((u32)0x00000001 << 11)                             /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_TXRPTBUFFER             10
#define AON_BIT_DVSE_WLMAC_TXRPTBUFFER               ((u32)0x00000001 << 10)                             /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_RXPKTBUFFER             9
#define AON_BIT_DVSE_WLMAC_RXPKTBUFFER               ((u32)0x00000001 << 9)                              /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_TXPKTBUFFER1            8
#define AON_BIT_DVSE_WLMAC_TXPKTBUFFER1              ((u32)0x00000001 << 8)                              /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_TXPKTBUFFER0            7
#define AON_BIT_DVSE_WLMAC_TXPKTBUFFER0              ((u32)0x00000001 << 7)                              /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_TXLLT                   6
#define AON_BIT_DVSE_WLMAC_TXLLT                     ((u32)0x00000001 << 6)                              /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_MACTX_FIFO              5
#define AON_BIT_DVSE_WLMAC_MACTX_FIFO                ((u32)0x00000001 << 5)                              /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_MACRX_FIFO              4
#define AON_BIT_DVSE_WLMAC_MACRX_FIFO                ((u32)0x00000001 << 4)                              /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_TKIPRC4                 3
#define AON_BIT_DVSE_WLMAC_TKIPRC4                   ((u32)0x00000001 << 3)                              /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_PSF                     2
#define AON_BIT_DVSE_WLMAC_PSF                       ((u32)0x00000001 << 2)                              /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_RXBACAM                 1
#define AON_BIT_DVSE_WLMAC_RXBACAM                   ((u32)0x00000001 << 1)                              /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
#define AON_SHIFT_DVSE_WLMAC_KEYSRCH                 0
#define AON_BIT_DVSE_WLMAC_KEYSRCH                   ((u32)0x00000001 << 0)                              /*!<R/W 0x0  delay option enable wlan mac memory cells 1 bit for each wlmac bist group */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_AON
 * @{
 * @brief rtl8735b_AON Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t AON_REG_AON_PWR_CTRL ;                   /*!<   register,  Address offset: 0x000 */
	__IO uint32_t AON_REG_AON_ISO_CTRL ;                   /*!<   register,  Address offset: 0x004 */
	__IO uint32_t AON_REG_AON_FUNC_CTRL ;                  /*!<   register,  Address offset: 0x008 */
	__IO uint32_t AON_REG_AON_CLK_CTRL ;                   /*!<   register,  Address offset: 0x00C */
	__IO uint32_t AON_REG_AON_LDO_CTRL0 ;                  /*!<   register,  Address offset: 0x010 */
	__IO uint32_t AON_REG_WLON_LDO_CTRL0 ;                 /*!<   register,  Address offset: 0x014 */
	__IO uint32_t AON_REG_SWR_SRC_CTRL0 ;                  /*!<   register,  Address offset: 0x018 */
	__IO uint32_t AON_REG_SWR_SRC_CTRL1 ;                  /*!<   register,  Address offset: 0x01C */
	__IO uint32_t AON_REG_SWR_SRC_CTRL2 ;                  /*!<   register,  Address offset: 0x020 */
	__IO uint32_t AON_REG_SWR_SRC_CTRL3 ;                  /*!<   register,  Address offset: 0x024 */
	__IO uint32_t AON_REG_SWR_SRC_CTRL4 ;                  /*!<   register,  Address offset: 0x028 */
	__IO uint32_t AON_REG_SWR_SRC_OCP ;                    /*!<   register,  Address offset: 0x02C */
	__IO uint32_t AON_REG_SWR_ZCD_CTRL ;                   /*!<   register,  Address offset: 0x030 */
	__IO uint32_t AON_REG_SWR_SRC_LV_CTRL ;                /*!<   register,  Address offset: 0x034 */
	__IO uint32_t AON_REG_SWR_CORE_CTRL3 ;                 /*!<   register,  Address offset: 0x038 */
	__IO uint32_t AON_REG_SWR_CORE_CTRL4 ;                 /*!<   register,  Address offset: 0x03C */
	__IO uint32_t AON_REG_AON_XTAL32K_CTRL0 ;              /*!<   register,  Address offset: 0x040 */
	__IO uint32_t AON_REG_AON_XTAL32K_CTRL1 ;              /*!<   register,  Address offset: 0x044 */
	__IO uint32_t AON_REG_AON_OSC32K_CTRL0 ;               /*!<   register,  Address offset: 0x048 */
	__IO uint32_t AON_REG_AON_PLATFORM_VER ;               /*!<   register,  Address offset: 0x04C */
	__IO uint32_t AON_REG_AON_OSC4M_CTRL ;                 /*!<   register,  Address offset: 0x050 */
	__IO uint32_t AON_REG_AON_SW_DBG0 ;                    /*!<   register,  Address offset: 0x054 */
	__IO uint32_t AON_REG_AON_SW_DBG1 ;                    /*!<   register,  Address offset: 0x058 */
	__IO uint32_t AON_REG_AON_XTAL_CLK_CTRL0 ;             /*!<   register,  Address offset: 0x05C */
	__IO uint32_t AON_REG_AON_XTAL_CLK_CTRL1 ;             /*!<   register,  Address offset: 0x060 */
	__IO uint32_t AON_REG_AON_XTAL_CLK_CTRL2 ;             /*!<   register,  Address offset: 0x064 */
	__IO uint32_t AON_REG_AON_XTAL_CLK_CTRL3 ;             /*!<   register,  Address offset: 0x068 */
	__IO uint32_t AON_REG_AON_XTAL_CLK_CTRL4 ;             /*!<   register,  Address offset: 0x06C */
	__IO uint32_t AON_REG_AON_XTAL_CLK_CTRL5 ;             /*!<   register,  Address offset: 0x070 */
	__IO uint32_t AON_REG_AON_XTAL_CLK_CTRL6 ;             /*!<   register,  Address offset: 0x074 */
	__IO uint32_t AON_REG_AON_XTAL_CLK_CTRL7 ;             /*!<   register,  Address offset: 0x078 */
	__IO uint32_t AON_REG_AON_SRC_CLK_CTRL ;               /*!<   register,  Address offset: 0x07C */
	__I  uint32_t AON_REG_AON_CLK_STS ;                    /*!<   register,  Address offset: 0x080 */
	__IO uint32_t AON_REG_AON_WAKE_TIMER ;                 /*!<   register,  Address offset: 0x084 */
	__IO uint32_t AON_REG_AON_PLL_CTRL0 ;                  /*!<   register,  Address offset: 0x088 */
	__IO uint32_t AON_REG_AON_SD_CTRL0 ;                   /*!<   register,  Address offset: 0x08C */
	__IO uint32_t AON_REG_AON_PAD_CTRL ;                   /*!<   register,  Address offset: 0x090 */
	__IO uint32_t AON_REG_AON_GPIOA_0_1_CTRL ;             /*!<   register,  Address offset: 0x094 */
	__IO uint32_t AON_REG_AON_GPIOA_2_3_CTRL ;             /*!<   register,  Address offset: 0x098 */
	__IO uint32_t AON_REG_AON_GPIOA_4_5_CTRL ;             /*!<   register,  Address offset: 0x09C */
	__IO uint32_t AON_REG_AON_IO1_RSVD ;                   /*!<   register,  Address offset: 0x0A0 */
	__IO uint32_t AON_REG_AON_IO2_RSVD ;                   /*!<   register,  Address offset: 0x0A4 */
	__IO uint32_t AON_REG_AON_LSFIF_CMD ;                  /*!<   register,  Address offset: 0x0A8 */
	__IO uint32_t AON_REG_AON_LSFIF_RWD ;                  /*!<   register,  Address offset: 0x0AC */
	__IO uint32_t AON_REG_AON_TEST_MUX_CTRL ;              /*!<   register,  Address offset: 0x0B0 */
	__IO uint32_t AON_REG_AON_WDT_TIMER ;                  /*!<   register,  Address offset: 0x0B4 */
	__IO uint32_t AON_REG_AON_TEST_MUX_CTRL1 ;             /*!<   register,  Address offset: 0x0B8 */
	__IO uint32_t AON_REG_AON_ATLOAD_CTRL1 ;               /*!<   register,  Address offset: 0x0BC */
	__IO uint32_t AON_REG_AON_ATLOAD_CTRL2 ;               /*!<   register,  Address offset: 0x0C0 */
	__I  uint32_t AON_REG_AON_SYS_INFO0 ;                  /*!<   register,  Address offset: 0x0C4 */
	__IO uint32_t AON_REG_AON_SYS_INFO1 ;                  /*!<   register,  Address offset: 0x0C8 */
	__IO uint32_t AON_REG_AON_OTP_SYSCFG2 ;                /*!<   register,  Address offset: 0x0CC */
	__IO uint32_t AON_REG_AON_OTP_SYSCFG3 ;                /*!<   register,  Address offset: 0x0D0 */
	__IO uint32_t AON_REG_AON_OTP_SYSCFG4 ;                /*!<   register,  Address offset: 0x0D4 */
	__IO uint32_t AON_REG_AON_OTP_SYSCFG5 ;                /*!<   register,  Address offset: 0x0D8 */
	__IO uint32_t AON_REG_AON_OTP_SYSCFG6 ;                /*!<   register,  Address offset: 0x0DC */
	__IO uint32_t AON_REG_AON_OTP_SYSCFG7 ;                /*!<   register,  Address offset: 0x0E0 */
	__I  uint32_t AON_REG_AON_DBG_REG ;                    /*!<   register,  Address offset: 0x0E4 */
	__IO uint32_t AON_REG_AON_SYS_CTRL ;                   /*!<   register,  Address offset: 0x0E8 */
	__IO uint32_t AON_REG_AON_SIC_DBG_CTRL ;               /*!<   register,  Address offset: 0x0EC */
	__I  uint32_t AON_REG_AON_GPIO1_WAKE_CTRL ;            /*!<   register,  Address offset: 0x0F0 */
	__I  uint32_t AON_REG_AON_GPIO2_WAKE_CTRL ;            /*!<   register,  Address offset: 0x0F4 */
	__IO uint32_t AON_REG_AON_OTP_CNT_Z_CTRL ;             /*!<   register,  Address offset: 0x0F8 */
	__IO uint32_t AON_REG_AON_PMC_CTRL ;                   /*!<   register,  Address offset: 0x0FC */
	__IO uint32_t AON_REG_AON_PMC_OPT ;                    /*!<   register,  Address offset: 0x100 */
	__IO uint32_t AON_REG_AON_BOOT_REASON ;                /*!<   register,  Address offset: 0x104 */
	__IO uint32_t AON_REG_AON_WL_CTRL ;                    /*!<   register,  Address offset: 0x108 */
	__IO uint32_t AON_REG_AON_SLP_WAKE_EVENT_MSK0 ;        /*!<   register,  Address offset: 0x10C */
	__IO uint32_t AON_REG_AON_SLP_WAKE_EVENT_STATUS0 ;     /*!<   register,  Address offset: 0x110 */
	__IO uint32_t AON_REG_AON_SNF_WAKE_EVENT_MSK0 ;        /*!<   register,  Address offset: 0x114 */
	__IO uint32_t AON_REG_AON_SNF_WAKE_EVENT_STATUS ;      /*!<   register,  Address offset: 0x118 */
	__IO uint32_t AON_REG_AON_PWRMGT_OPTION ;              /*!<   register,  Address offset: 0x11C */
	__IO uint32_t AON_REG_OTP_CTRL_0 ;                     /*!<   register,  Address offset: 0x120 */
	__IO uint32_t AON_REG_OTP_CTRL_1 ;                     /*!<   register,  Address offset: 0x124 */
	__IO uint32_t AON_REG_OTP_AL_CTRL_STS ;                /*!<   register,  Address offset: 0x128 */
	__IO uint32_t AON_REG_OTP_PMC_DBG_CTRL ;               /*!<   register,  Address offset: 0x12C */
	__IO uint32_t AON_REG_OTP_PWR_CTRL ;                   /*!<   register,  Address offset: 0x130 */
	__IO uint32_t AON_REG_OTP_AS_CTRL_A ;                  /*!<   register,  Address offset: 0x134 */
	__IO uint32_t AON_REG_OTP_SCAN_TEST_A ;                /*!<   register,  Address offset: 0x138 */
	__IO uint32_t AON_REG_OTP_PRCT_CTRL ;                  /*!<   register,  Address offset: 0x13C */
	__IO uint32_t AON_REG_AON_SW_BOOT0 ;                   /*!<   register,  Address offset: 0x140 */
	__IO uint32_t AON_REG_AON_FAST_RESUME ;                /*!<   register,  Address offset: 0x144 */
	__IO uint32_t AON_REG_AON_SW_BOOT1 ;                   /*!<   register,  Address offset: 0x148 */
	__IO uint32_t AON_REG_AON_SW_BOOT2 ;                   /*!<   register,  Address offset: 0x14C */
	__IO uint32_t AON_REG_AON_SW_BOOT3 ;                   /*!<   register,  Address offset: 0x150 */
	__IO uint32_t AON_REG_AON_SW_BOOT4 ;                   /*!<   register,  Address offset: 0x154 */
	__IO uint32_t AON_REG_AON_WLMAC_MEM_CNTRL ;            /*!<   register,          Address offset: 0x158 */
} AON_TypeDef;
/** @} */

#endif
