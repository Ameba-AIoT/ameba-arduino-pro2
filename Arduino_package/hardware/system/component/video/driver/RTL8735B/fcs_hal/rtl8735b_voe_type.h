#ifndef _RTL8735B_VOE_TYPE_H_
#define _RTL8735B_VOE_TYPE_H_

/**************************************************************************//**
 * @defgroup VOE_REG_VOE_SYSTEM_CTRL
 * @brief  N/A                                       (@ 0X00)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD1                              3
#define VOE_MASK_RSVD1                               ((u32)0x1FFFFFFF << 3)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_KM_RESET_DIS                       2
#define VOE_BIT_KM_RESET_DIS                         ((u32)0x00000001 << 2)                              /*!<R/W 0  0': Disable KM; '1': Enable KM */
#define VOE_SHIFT_VOE_RESET_DIS                      1
#define VOE_BIT_VOE_RESET_DIS                        ((u32)0x00000001 << 1)                              /*!<R/W 1  0': Disable VOE function; '1': Enable VOE function */
#define VOE_SHIFT_CLOCK_GATING_DIS                   0
#define VOE_BIT_CLOCK_GATING_DIS                     ((u32)0x00000001 << 0)                              /*!<R/W 1  0': Disable VOE clock; '1': Enable VOE clock */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_FW_BASE_ADDRESS
 * @brief  N/A                                       (@ 0X04)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_KM_FW_BASE_ADDR                    0
#define VOE_MASK_KM_FW_BASE_ADDR                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  When KM boots, rom code should read this register to get the location of ram code. Then, it also should read 'REG_KM_FW_LEN' and copy the fw into memory of VOE. */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_FW_LEN
 * @brief  N/A                                       (@ 0X08)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_KM_FW_LEN                          0
#define VOE_MASK_KM_FW_LEN                           ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Same ad 'REG_KM_FW_BASE_ADDRESS' */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_SEND_MESSAGE_EXTERNAL_CTRL
 * @brief  N/A                                       (@ 0X0C)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_INVALID_AP_QUEUE                   31
#define VOE_BIT_INVALID_AP_QUEUE                     ((u32)0x00000001 << 31)                             /*!<r/wonce 0  0': Default value '1': Trigger interrupt to KM. */
#define VOE_SHIFT_RSVD2                              30
#define VOE_BIT_RSVD2                                ((u32)0x00000001 << 30)                             /*!<-- 0  RSVD */
#define VOE_SHIFT_MESSAGE                            0
#define VOE_MASK_MESSAGE                             ((u32)0x3FFFFFFF << 0)                              /*!<R/W 0  Message from AP */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_READ_MESSAGE_EXTERNAL_CTRL
 * @brief  N/A                                       (@ 0X10)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_INVALID_VOE_QUEUE                  31
#define VOE_BIT_INVALID_VOE_QUEUE                    ((u32)0x00000001 << 31)                             /*!<r/w 0  0': Default value; When this bit is written to '0', FSM should clean the bit 0x108[31] 'REG_SEND_MESSAGE_KM_CTRL'. And FSM also should clean 0x108[29:0] '1': Trigger interrupt to the external CPU */
#define VOE_SHIFT_RSVD3                              30
#define VOE_BIT_RSVD3                                ((u32)0x00000001 << 30)                             /*!<-- 0  RSVD */
#define VOE_SHIFT_MESSAGE                            0
#define VOE_MASK_MESSAGE                             ((u32)0x3FFFFFFF << 0)                              /*!<R 0  Message from VOE and thie field equal to 0x108[29:0] 'REG_SEND_MESSAGE_KM_CTRL' */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_INTERRUPT_STATUS_OF_EXTERNAL_CPU
 * @brief  N/A                                       (@ 0X14)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD4                              24
#define VOE_MASK_RSVD4                               ((u32)0x000000FF << 24)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD5                              25
#define VOE_BIT_RSVD5                                ((u32)0x00000001 << 25)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD6                              24
#define VOE_BIT_RSVD6                                ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD7                              18
#define VOE_MASK_RSVD7                               ((u32)0x0000003F << 18)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD8                              17
#define VOE_BIT_RSVD8                                ((u32)0x00000001 << 17)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD9                              16
#define VOE_BIT_RSVD9                                ((u32)0x00000001 << 16)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD10                             9
#define VOE_MASK_RSVD10                              ((u32)0x0000007F << 9)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ERAC_FINISH                        8
#define VOE_BIT_ERAC_FINISH                          ((u32)0x00000001 << 8)                              /*!<R/W1C 0  ERAC finsh write/read */
#define VOE_SHIFT_RSVD11                             1
#define VOE_MASK_RSVD11                              ((u32)0x0000007F << 1)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_KM_MESSAGE_ISR_STATUS              0
#define VOE_BIT_KM_MESSAGE_ISR_STATUS                ((u32)0x00000001 << 0)                              /*!<R/W1C 0  0': default '1': When KM set 0x108[31] REG_SEND_MESSAGE_KM_CTRL, FSM will set this bit to '1'. And this bit will be clear with writing '1'. */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_INTERRUPT_MASK_OF_EXTERNAL_CPU
 * @brief  N/A                                       (@ 0X18)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD12                             26
#define VOE_MASK_RSVD12                              ((u32)0x0000003F << 26)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD13                             25
#define VOE_BIT_RSVD13                               ((u32)0x00000001 << 25)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD14                             24
#define VOE_BIT_RSVD14                               ((u32)0x00000001 << 24)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD15                             18
#define VOE_MASK_RSVD15                              ((u32)0x0000003F << 18)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD16                             17
#define VOE_BIT_RSVD16                               ((u32)0x00000001 << 17)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD17                             16
#define VOE_BIT_RSVD17                               ((u32)0x00000001 << 16)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD18                             9
#define VOE_MASK_RSVD18                              ((u32)0x0000007F << 9)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ERAC_AP_FINISH_EN                  8
#define VOE_BIT_ERAC_AP_FINISH_EN                    ((u32)0x00000001 << 8)                              /*!<R/W 0  ERAC finsh write/read */
#define VOE_SHIFT_RSVD19                             1
#define VOE_MASK_RSVD19                              ((u32)0x0000007F << 1)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_KM_MESSAGE_ISR_EN                  0
#define VOE_BIT_KM_MESSAGE_ISR_EN                    ((u32)0x00000001 << 0)                              /*!<R/W 0  0': Default; disable interrupt '1': Enable the interrupt where KM set 0x108[31] REG_SEND_MESSAGE_KM_CTRL. */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_VOE_ARB_PRIORITY_CTRL0
 * @brief  N/A                                       (@ 0X100)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD20                             16
#define VOE_MASK_RSVD20                              ((u32)0x0000FFFF << 16)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_ARB_WR_PRIOR                       0
#define VOE_MASK_ARB_WR_PRIOR                        ((u32)0x0000FFFF << 0)                              /*!<R/W h8421  AXI aribter write priority.should be set to exclusive number of '8, 4, 2, 1' */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_VOE_ARB_PRIORITY_CTRL1
 * @brief  N/A                                       (@ 0X104)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD21                             16
#define VOE_MASK_RSVD21                              ((u32)0x0000FFFF << 16)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_ARB_RD_PRIOR                       0
#define VOE_MASK_ARB_RD_PRIOR                        ((u32)0x0000FFFF << 0)                              /*!<R/W h8421  AXI ariber read priority should be set to exclusive number of '8, 4, 2, 1' */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_SEND_MESSAGE_KM_CTRL
 * @brief  N/A                                       (@ 0X108)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_INVALID_AP_QUEUE                   31
#define VOE_BIT_INVALID_AP_QUEUE                     ((u32)0x00000001 << 31)                             /*!<r/wonce 0  0': Default value '1': Trigger interrupt to the external CPU. */
#define VOE_SHIFT_RSVD22                             30
#define VOE_BIT_RSVD22                               ((u32)0x00000001 << 30)                             /*!<-- 0  RSVD */
#define VOE_SHIFT_MESSAGE                            0
#define VOE_MASK_MESSAGE                             ((u32)0x3FFFFFFF << 0)                              /*!<R/W 0  Message from KM */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_READ_MESSAGE_KM_CTRL
 * @brief  N/A                                       (@ 0X10C)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_INVALID_VOE_QUEUE                  31
#define VOE_BIT_INVALID_VOE_QUEUE                    ((u32)0x00000001 << 31)                             /*!<r/w 0  0': Default value; When this bit is written to '0', FSM should clean the bit 0x0C[31] 'REG_SEND_MESSAGE_EXTERNAL_CTRL'. And FSM also should clean 0x0C[29:0] '1': Trigger interrupt to the external CPU */
#define VOE_SHIFT_RSVD23                             30
#define VOE_BIT_RSVD23                               ((u32)0x00000001 << 30)                             /*!<-- 0  RSVD */
#define VOE_SHIFT_MESSAGE                            0
#define VOE_MASK_MESSAGE                             ((u32)0x3FFFFFFF << 0)                              /*!<R 0  Message from the external cpu and thie field equal to 0x0C[29:0] 'REG_SEND_MESSAGE_EXTERNAL_CTRL' */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_INTERRUPT_STATUS_OF_KM
 * @brief  N/A                                       (@ 0X110)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD24                             27
#define VOE_MASK_RSVD24                              ((u32)0x0000001F << 27)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_SCRYPTO_ISR_STATUS                 26
#define VOE_BIT_SCRYPTO_ISR_STATUS                   ((u32)0x00000001 << 26)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from SCrypto */
#define VOE_SHIFT_I2C2_ISR_STATUS                    25
#define VOE_BIT_I2C2_ISR_STATUS                      ((u32)0x00000001 << 25)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from I2C2 */
#define VOE_SHIFT_NN_ISR_STATUS                      24
#define VOE_BIT_NN_ISR_STATUS                        ((u32)0x00000001 << 24)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from NN */
#define VOE_SHIFT_GDMA1_ISR_STATUS                   23
#define VOE_BIT_GDMA1_ISR_STATUS                     ((u32)0x00000001 << 23)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from GDMA1 */
#define VOE_SHIFT_GDMA0_G0_ISR_STATUS                22
#define VOE_BIT_GDMA0_G0_ISR_STATUS                  ((u32)0x00000001 << 22)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from GDMA0 */
#define VOE_SHIFT_I2C3_ISR_STATUS                    21
#define VOE_BIT_I2C3_ISR_STATUS                      ((u32)0x00000001 << 21)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from I2C3 */
#define VOE_SHIFT_UART0_ISR_STATUS                   20
#define VOE_BIT_UART0_ISR_STATUS                     ((u32)0x00000001 << 20)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from UART0 */
#define VOE_SHIFT_ADC_ISR_STATUS                     19
#define VOE_BIT_ADC_ISR_STATUS                       ((u32)0x00000001 << 19)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from ADC */
#define VOE_SHIFT_PWM_ISR_STATUS                     18
#define VOE_BIT_PWM_ISR_STATUS                       ((u32)0x00000001 << 18)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from PWM */
#define VOE_SHIFT_GPIO_ISR_STATUS                    17
#define VOE_BIT_GPIO_ISR_STATUS                      ((u32)0x00000001 << 17)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from GPIO */
#define VOE_SHIFT_TIMER_G0_ISR_STATUS                16
#define VOE_BIT_TIMER_G0_ISR_STATUS                  ((u32)0x00000001 << 16)                             /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from TimerGroup0 */
#define VOE_SHIFT_RSVD25                             9
#define VOE_MASK_RSVD25                              ((u32)0x0000007F << 9)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ERAC_KM_FINISH                     8
#define VOE_BIT_ERAC_KM_FINISH                       ((u32)0x00000001 << 8)                              /*!<R/W1C 0  ERAC to KM , indicate erac finish. Asserted when ERAC finish wr/rd data to/from encoder/ISP */
#define VOE_SHIFT_RSVD26                             7
#define VOE_BIT_RSVD26                               ((u32)0x00000001 << 7)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD27                             6
#define VOE_BIT_RSVD27                               ((u32)0x00000001 << 6)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD28                             5
#define VOE_BIT_RSVD28                               ((u32)0x00000001 << 5)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ISP_ISR_STATUS                     4
#define VOE_BIT_ISP_ISR_STATUS                       ((u32)0x00000001 << 4)                              /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from ISP */
#define VOE_SHIFT_RSVD29                             3
#define VOE_BIT_RSVD29                               ((u32)0x00000001 << 3)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ENCODER_ISR_STATUS                 2
#define VOE_BIT_ENCODER_ISR_STATUS                   ((u32)0x00000001 << 2)                              /*!<R/W1C 0  0': Default; there is no active interrupt '1': There is a active interrupt from encoder */
#define VOE_SHIFT_RSVD30                             1
#define VOE_BIT_RSVD30                               ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_AP_MESSAGE_ISR_STATUS              0
#define VOE_BIT_AP_MESSAGE_ISR_STATUS                ((u32)0x00000001 << 0)                              /*!<R/W1C 0  0': Default; there is no active interrupt '1': When the external cpu set 0x0C[31] REG_SEND_MESSAGE_EXTERNAL_CTRL, FSM will set this bit to '1'. And this bit will be clear to '0' with writing '1'. */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_INTERRUPT_MASK_OF_KM
 * @brief  N/A                                       (@ 0X114)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD31                             27
#define VOE_MASK_RSVD31                              ((u32)0x0000001F << 27)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_SCRYPTO_ISR_EN                     26
#define VOE_BIT_SCRYPTO_ISR_EN                       ((u32)0x00000001 << 26)                             /*!<R/W 0  0': Default; disable SCrypto interrupt '1': Enable SCrypto interrupt */
#define VOE_SHIFT_I2C2_ISR_EN                        25
#define VOE_BIT_I2C2_ISR_EN                          ((u32)0x00000001 << 25)                             /*!<R/W 0  0': Default; disable I2C2 interrupt '1': Enable I2C2 interrupt */
#define VOE_SHIFT_NN_ISR_EN                          24
#define VOE_BIT_NN_ISR_EN                            ((u32)0x00000001 << 24)                             /*!<R/W 0  0': Default; disable NN interrupt '1': Enable NN interrupt */
#define VOE_SHIFT_GDMA1_ISR_EN                       23
#define VOE_BIT_GDMA1_ISR_EN                         ((u32)0x00000001 << 23)                             /*!<R/W 0  0': Default; disable GDMA1 interrupt '1': Enable GDMA1 interrupt */
#define VOE_SHIFT_GDMA0_G0_ISR_EN                    22
#define VOE_BIT_GDMA0_G0_ISR_EN                      ((u32)0x00000001 << 22)                             /*!<R/W 0  0': Default; disable GDMA0 interrupt '1': Enable GDMA0 interrupt */
#define VOE_SHIFT_I2C3_ISR_EN                        21
#define VOE_BIT_I2C3_ISR_EN                          ((u32)0x00000001 << 21)                             /*!<R/W 0  0': Default; disable I2C3 interrupt '1': Enable I2C3 interrupt */
#define VOE_SHIFT_UART0_ISR_EN                       20
#define VOE_BIT_UART0_ISR_EN                         ((u32)0x00000001 << 20)                             /*!<R/W 0  0': Default; disable UART0 interrupt '1': Enable UART0 interrupt */
#define VOE_SHIFT_ADC_ISR_EN                         19
#define VOE_BIT_ADC_ISR_EN                           ((u32)0x00000001 << 19)                             /*!<R/W 0  0': Default; disable ADC interrupt '1': Enable ADC interrupt */
#define VOE_SHIFT_PWM_ISR_EN                         18
#define VOE_BIT_PWM_ISR_EN                           ((u32)0x00000001 << 18)                             /*!<R/W 0  0': Default; disable PWM interrupt '1': Enable PWM interrupt */
#define VOE_SHIFT_GPIO_ISR_EN                        17
#define VOE_BIT_GPIO_ISR_EN                          ((u32)0x00000001 << 17)                             /*!<R/W 0  0': Default; disable GPIO interrupt '1': Enable GPIO interrupt */
#define VOE_SHIFT_TIMER_G3_ISR_EN                    16
#define VOE_BIT_TIMER_G3_ISR_EN                      ((u32)0x00000001 << 16)                             /*!<R/W 0  0': Default; disable TimerGroup0 interrupt '1': Enable TimerGroup0 interrupt */
#define VOE_SHIFT_RSVD32                             9
#define VOE_MASK_RSVD32                              ((u32)0x0000007F << 9)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ERAC_KM_ISR_EN                     8
#define VOE_BIT_ERAC_KM_ISR_EN                       ((u32)0x00000001 << 8)                              /*!<R/W 0  erac to km , erac finish interrupt */
#define VOE_SHIFT_RSVD33                             7
#define VOE_BIT_RSVD33                               ((u32)0x00000001 << 7)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD34                             6
#define VOE_BIT_RSVD34                               ((u32)0x00000001 << 6)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_RSVD35                             5
#define VOE_BIT_RSVD35                               ((u32)0x00000001 << 5)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ISP_ISR_EN                         4
#define VOE_BIT_ISP_ISR_EN                           ((u32)0x00000001 << 4)                              /*!<R/W 0  0': Default; disable ISP interrupt '1': Enable ISP interrupt */
#define VOE_SHIFT_RSVD36                             3
#define VOE_BIT_RSVD36                               ((u32)0x00000001 << 3)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ENCODER_ISR_EN                     2
#define VOE_BIT_ENCODER_ISR_EN                       ((u32)0x00000001 << 2)                              /*!<R/W 0  0': Default; disable encoder interrupt '1': Enable encoder interrupt */
#define VOE_SHIFT_RSVD37                             1
#define VOE_BIT_RSVD37                               ((u32)0x00000001 << 1)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_AP_MESSAGE_ISR_EN                  0
#define VOE_BIT_AP_MESSAGE_ISR_EN                    ((u32)0x00000001 << 0)                              /*!<R/W 0  0': Default; disable interrupt '1': Enable the interrupt where KM set 0x0C[31] REG_SEND_MESSAGE_EXTERNAL_CTRL. */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_MBIST_REG
 * @brief  N/A                                       (@ 0X118)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD38                             21
#define VOE_MASK_RSVD38                              ((u32)0x000007FF << 21)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_MEM_CONFIG                         16
#define VOE_MASK_MEM_CONFIG                          ((u32)0x0000001F << 16)                             /*!<R/W 0  {rtsel[1:0],wtsel[1:0],sram_pd} */
#define VOE_SHIFT_RSVD39                             13
#define VOE_MASK_RSVD39                              ((u32)0x00000007 << 13)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_MBIST_OUTPUTS                      8
#define VOE_MASK_MBIST_OUTPUTS                       ((u32)0x0000001F << 8)                              /*!<R 0  mbist result,{drf_bist_fail, bist_fail, drf_bist_done, drf_start_pause, bist_done} */
#define VOE_SHIFT_RSVD40                             5
#define VOE_MASK_RSVD40                              ((u32)0x00000007 << 5)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_MBIST_INPUTS                       0
#define VOE_MASK_MBIST_INPUTS                        ((u32)0x0000000F << 0)                              /*!<R/W 0  {drf_test_resume, drf_bist_mode, bist_mode, bist_rstn} */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_DBGEN
 * @brief  N/A                                       (@ 0X11C)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD41                             18
#define VOE_MASK_RSVD41                              ((u32)0x00003FFF << 18)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_SYST_CLK_EN                        17
#define VOE_BIT_SYST_CLK_EN                          ((u32)0x00000001 << 17)                             /*!<R/W 0  Systick clock enable: Systick would count if systick is enabled and syst_clk_en is 1'b1 at rising edge of cpu clock (sysclk_f) */
#define VOE_SHIFT_RETENTION_MODE                     16
#define VOE_BIT_RETENTION_MODE                       ((u32)0x00000001 << 16)                             /*!<R/W 0  After reset, KM/TM processor hardware automatically clears internal instruction and data caches by writing 0's to those cache memories. This input pin provides an alternative to keep cache contents when reset. That is, if the retention_mode input pin is tied to 1, the processor hardware will not clear caches after reset, so that cache contents will be retained. On the other hand, when tied to 0, the processor clear cache automatically. */
#define VOE_SHIFT_RSVD42                             14
#define VOE_MASK_RSVD42                              ((u32)0x00000003 << 14)                             /*!<RW 0  RSVD */
#define VOE_SHIFT_SL_SLEEPSYS_R                      13
#define VOE_BIT_SL_SLEEPSYS_R                        ((u32)0x00000001 << 13)                             /*!<R 0  Core is sleeping */
#define VOE_SHIFT_SYSRESET_REQ                       12
#define VOE_BIT_SYSRESET_REQ                         ((u32)0x00000001 << 12)                             /*!<R 0  KM system warm reset request */
#define VOE_SHIFT_RSVD43                             9
#define VOE_MASK_RSVD43                              ((u32)0x00000007 << 9)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_LOCKUP_M                           8
#define VOE_BIT_LOCKUP_M                             ((u32)0x00000001 << 8)                              /*!<R 0  Indicate whether KM CPU is locked or not */
#define VOE_SHIFT_HALTED_M                           7
#define VOE_BIT_HALTED_M                             ((u32)0x00000001 << 7)                              /*!<R 0  Indicate whether KM CPU is in debug mode (halting mode) or not */
#define VOE_SHIFT_DBGRESTARTED_M                     6
#define VOE_BIT_DBGRESTARTED_M                       ((u32)0x00000001 << 6)                              /*!<R 0  Indicate whether KM CPU is returning to normal mode from debug mode */
#define VOE_SHIFT_KM_DBGEN                           0
#define VOE_MASK_KM_DBGEN                            ((u32)0x0000003F << 0)                              /*!<R/W 0x0F  KM configuration register */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_INITVTOR_S
 * @brief  N/A                                       (@ 0X120)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_KM_INITVTOR_S                      0
#define VOE_MASK_KM_INITVTOR_S                       ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  KM configuration register */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_INITVTOR_NS
 * @brief  N/A                                       (@ 0X124)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_KM_INITVTOR_NS                     0
#define VOE_MASK_KM_INITVTOR_NS                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  KM configuration register */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_INIT
 * @brief  N/A                                       (@ 0X128)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD44                             6
#define VOE_MASK_RSVD44                              ((u32)0x03FFFFFF << 6)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_INITD2ITCM_S                       5
#define VOE_BIT_INITD2ITCM_S                         ((u32)0x00000001 << 5)                              /*!<R/W 1  Initial value of D2ITCM in ACTLR */
#define VOE_SHIFT_INITI2DTCM_S                       4
#define VOE_BIT_INITI2DTCM_S                         ((u32)0x00000001 << 4)                              /*!<R/W 1  Initial value of I2DTCM in ACTLR */
#define VOE_SHIFT_INITDTCMEN1_S                      3
#define VOE_BIT_INITDTCMEN1_S                        ((u32)0x00000001 << 3)                              /*!<R/W 1  Initial value of EN in DTCMCR1 */
#define VOE_SHIFT_INITDTCMEN0_S                      2
#define VOE_BIT_INITDTCMEN0_S                        ((u32)0x00000001 << 2)                              /*!<R/W 1  Initial value of EN in DTCMCR0 */
#define VOE_SHIFT_INITITCMEN1_S                      1
#define VOE_BIT_INITITCMEN1_S                        ((u32)0x00000001 << 1)                              /*!<R/W 1  Initial value of EN in ITCMCR1 */
#define VOE_SHIFT_INITITCMEN0_S                      0
#define VOE_BIT_INITITCMEN0_S                        ((u32)0x00000001 << 0)                              /*!<R/W 1  Initial value of EN in ITCMCR0 */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_TMODE
 * @brief  N/A                                       (@ 0X12C)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD45                             1
#define VOE_MASK_RSVD45                              ((u32)0x7FFFFFFF << 1)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_KM_TMODE                           0
#define VOE_BIT_KM_TMODE                             ((u32)0x00000001 << 0)                              /*!<R/W 0  KM bist mode */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_CFG_CPU_NUM
 * @brief  N/A                                       (@ 0X130)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD46                             10
#define VOE_MASK_RSVD46                              ((u32)0x003FFFFF << 10)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_KM_CFG_CPU_NUM                     0
#define VOE_MASK_KM_CFG_CPU_NUM                      ((u32)0x000003FF << 0)                              /*!<R/W 0  KM configuration register */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_MBIST_REG_FBCU_0
 * @brief  N/A                                       (@ 0X134)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD47                             21
#define VOE_MASK_RSVD47                              ((u32)0x000007FF << 21)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_MEM_CONFIG_FBCU                    16
#define VOE_MASK_MEM_CONFIG_FBCU                     ((u32)0x0000001F << 16)                             /*!<R/W 110  {rtsel[0],tsel[1:0],turbo,sram_pd} */
#define VOE_SHIFT_RSVD48                             13
#define VOE_MASK_RSVD48                              ((u32)0x00000007 << 13)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_MBIST_OUTPUTS_FBCU_0               8
#define VOE_MASK_MBIST_OUTPUTS_FBCU_0                ((u32)0x0000001F << 8)                              /*!<R 0  mbist result,{drf_bist_fail, bist_fail, drf_bist_done, drf_start_pause, bist_done} */
#define VOE_SHIFT_RSVD49                             3
#define VOE_MASK_RSVD49                              ((u32)0x0000001F << 3)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_MBIST_INPUTS_FBCU_0                0
#define VOE_MASK_MBIST_INPUTS_FBCU_0                 ((u32)0x00000007 << 0)                              /*!<R/W 0  {drf_test_resume, drf_bist_mode, bist_mode} */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_MBIST_REG_FBCU_1
 * @brief  N/A                                       (@ 0X138)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD50                             13
#define VOE_MASK_RSVD50                              ((u32)0x0007FFFF << 13)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_MBIST_OUTPUTS_FBCU_1               8
#define VOE_MASK_MBIST_OUTPUTS_FBCU_1                ((u32)0x0000001F << 8)                              /*!<R 0  mbist result,{drf_bist_fail, bist_fail, drf_bist_done, drf_start_pause, bist_done} */
#define VOE_SHIFT_RSVD51                             3
#define VOE_MASK_RSVD51                              ((u32)0x0000001F << 3)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_MBIST_INPUTS_FBCU_1                0
#define VOE_MASK_MBIST_INPUTS_FBCU_1                 ((u32)0x00000007 << 0)                              /*!<R/W 0  {drf_test_resume, drf_bist_mode, bist_mode} */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_ADDRESS_REMAP_CTRL
 * @brief  N/A                                       (@ 0X13C)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD52                             1
#define VOE_MASK_RSVD52                              ((u32)0x7FFFFFFF << 1)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_KM_REMAP_EN                        0
#define VOE_BIT_KM_REMAP_EN                          ((u32)0x00000001 << 0)                              /*!<R/W 0  0': Default; disable remap function '1': Enable remap function */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_ITCM_REMAP_BASE
 * @brief  N/A                                       (@ 0X140)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_KM_ITCM_REMAP_ADDRESS              0
#define VOE_MASK_KM_ITCM_REMAP_ADDRESS               ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  When 0x13C[0] equals to '1' and the address bit [29] KM sent equals to '0', decoder should execute the process that address bits [27:0] plus this register. Then hw should send this address to bus . */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_KM_DTCM_REMAP_BASE
 * @brief  N/A                                       (@ 0X144)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_KM_DTCM_REMAP_ADDRESS              0
#define VOE_MASK_KM_DTCM_REMAP_ADDRESS               ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  When 0x13C[0] equals to '1' and the address bit [29] KM sent equals to '1', decoder should execute the process that address bits [27:0] plus this register. Then hw should send this address to bus . */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_MBIST_KM_ROM
 * @brief  N/A                                       (@ 0X148)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD53                             9
#define VOE_MASK_RSVD53                              ((u32)0x007FFFFF << 9)                              /*!< 0  RSVD */
#define VOE_SHIFT_ROM_BIST_DONE                      8
#define VOE_BIT_ROM_BIST_DONE                        ((u32)0x00000001 << 8)                              /*!<R 0   */
#define VOE_SHIFT_ROM_RM_0                           4
#define VOE_MASK_ROM_RM_0                            ((u32)0x0000000F << 4)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ROM_LS_0                           3
#define VOE_BIT_ROM_LS_0                             ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define VOE_SHIFT_ROM_RME_0                          2
#define VOE_BIT_ROM_RME_0                            ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define VOE_SHIFT_ROM_BIST_MODE                      1
#define VOE_BIT_ROM_BIST_MODE                        ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define VOE_SHIFT_ROM_BIST_RSTN                      0
#define VOE_BIT_ROM_BIST_RSTN                        ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_MBIST_ROM_MISR_DOUT_H
 * @brief  N/A                                       (@ 0X14C)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_MBIST_ROM_MISR_DOUT                0
#define VOE_MASK_MBIST_ROM_MISR_DOUT                 ((u32)0xFFFFFFFF << 0)                              /*!<R 0  misr_dout[63:32]; ITCM ROM */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_MBIST_ROM_MISR_DOUT_L
 * @brief  N/A                                       (@ 0X150)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_MBIST_ROM_MISR_DOUT                0
#define VOE_MASK_MBIST_ROM_MISR_DOUT                 ((u32)0xFFFFFFFF << 0)                              /*!<R 0  misr_dout[31:0]; ITCM_ROM */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_MBIST_KM_RAM_WR
 * @brief  N/A                                       (@ 0X154)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD54                             10
#define VOE_MASK_RSVD54                              ((u32)0x003FFFFF << 10)                             /*!< 0  RSVD */
#define VOE_SHIFT_ITCM_DRF_TEST_RESUME               9
#define VOE_BIT_ITCM_DRF_TEST_RESUME                 ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define VOE_SHIFT_ITCM_PD_0                          8
#define VOE_BIT_ITCM_PD_0                            ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define VOE_SHIFT_ITCM_DRF_BIST_MODE                 7
#define VOE_BIT_ITCM_DRF_BIST_MODE                   ((u32)0x00000001 << 7)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ITCM_BIST_MODE                     6
#define VOE_BIT_ITCM_BIST_MODE                       ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define VOE_SHIFT_ITCM_BIST_RSTN                     5
#define VOE_BIT_ITCM_BIST_RSTN                       ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define VOE_SHIFT_DTCM_DRF_TEST_RESUME               4
#define VOE_BIT_DTCM_DRF_TEST_RESUME                 ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define VOE_SHIFT_DTCM_PD_0                          3
#define VOE_BIT_DTCM_PD_0                            ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define VOE_SHIFT_DTCM_DRF_BIST_MODE                 2
#define VOE_BIT_DTCM_DRF_BIST_MODE                   ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define VOE_SHIFT_DTCM_BIST_MODE                     1
#define VOE_BIT_DTCM_BIST_MODE                       ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define VOE_SHIFT_DTCM_BIST_RSTN                     0
#define VOE_BIT_DTCM_BIST_RSTN                       ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_MBIST_KM_RAM_RD
 * @brief  N/A                                       (@ 0X158)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD55                             10
#define VOE_MASK_RSVD55                              ((u32)0x003FFFFF << 10)                             /*!<R 0   */
#define VOE_SHIFT_ITCM_DRF_START_PAUSE               9
#define VOE_BIT_ITCM_DRF_START_PAUSE                 ((u32)0x00000001 << 9)                              /*!<R 0   */
#define VOE_SHIFT_ITCM_DRF_BIST_FAIL                 8
#define VOE_BIT_ITCM_DRF_BIST_FAIL                   ((u32)0x00000001 << 8)                              /*!<R 0   */
#define VOE_SHIFT_ITCM_BIST_FAIL                     7
#define VOE_BIT_ITCM_BIST_FAIL                       ((u32)0x00000001 << 7)                              /*!<R 0   */
#define VOE_SHIFT_ITCM_DRF_BIST_DONE                 6
#define VOE_BIT_ITCM_DRF_BIST_DONE                   ((u32)0x00000001 << 6)                              /*!<R 0   */
#define VOE_SHIFT_ITCM_BIST_DONE                     5
#define VOE_BIT_ITCM_BIST_DONE                       ((u32)0x00000001 << 5)                              /*!<R 0   */
#define VOE_SHIFT_DTCM_DRF_START_PAUSE               4
#define VOE_BIT_DTCM_DRF_START_PAUSE                 ((u32)0x00000001 << 4)                              /*!<R 0   */
#define VOE_SHIFT_DTCM_DRF_BIST_FAIL                 3
#define VOE_BIT_DTCM_DRF_BIST_FAIL                   ((u32)0x00000001 << 3)                              /*!<R 0   */
#define VOE_SHIFT_DTCM_BIST_FAIL                     2
#define VOE_BIT_DTCM_BIST_FAIL                       ((u32)0x00000001 << 2)                              /*!<R 0   */
#define VOE_SHIFT_DTCM_DRF_BIST_DONE                 1
#define VOE_BIT_DTCM_DRF_BIST_DONE                   ((u32)0x00000001 << 1)                              /*!<R 0   */
#define VOE_SHIFT_DTCM_BIST_DONE                     0
#define VOE_BIT_DTCM_BIST_DONE                       ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_MBIST_DTCM_ROM_MISR_DOUT_H
 * @brief  N/A                                       (@ 0X15C)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_MBIST_DTCM_ROM_MISR_DOUT           0
#define VOE_MASK_MBIST_DTCM_ROM_MISR_DOUT            ((u32)0xFFFFFFFF << 0)                              /*!<R 0  DTCM ROM */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_MBIST_DTCM_ROM_MISR_DOUT_L
 * @brief  N/A                                       (@ 0X160)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_MBIST_DTCM_ROM_MISR_DOUT           0
#define VOE_MASK_MBIST_DTCM_ROM_MISR_DOUT            ((u32)0xFFFFFFFF << 0)                              /*!<R 0  DTCM ROM */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_PC_VALUE
 * @brief  N/A                                       (@ 0X164)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_PC_VALUE                           0
#define VOE_MASK_PC_VALUE                            ((u32)0xFFFFFFFF << 0)                              /*!<R 0  KM pc value */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_RETIRED_INSTRUCTION_ADDR_0
 * @brief  N/A                                       (@ 0X168)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RETIRED_INSTRUCTION_ADDR_0         0
#define VOE_MASK_RETIRED_INSTRUCTION_ADDR_0          ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_RETIRED_INSTRUCTION_ADDR_1
 * @brief  N/A                                       (@ 0X16C)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RETIRED_INSTRUCTION_ADDR_1         0
#define VOE_MASK_RETIRED_INSTRUCTION_ADDR_1          ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_VOE_WATCHDOG_CTRL
 * @brief  N/A                                       (@ 0X170)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_WDT_TO                             31
#define VOE_BIT_WDT_TO                               ((u32)0x00000001 << 31)                             /*!<R/W1C 0  Watch dog timer timeout. 1 cycle pulse */
#define VOE_SHIFT_WDT_MODE                           30
#define VOE_BIT_WDT_MODE                             ((u32)0x00000001 << 30)                             /*!<R/W 0  0: Interrupt CPU when WDT timer counter is overflow. 1: Reset system when WDT timer counter is overflow. */
#define VOE_SHIFT_RSVD56                             29
#define VOE_BIT_RSVD56                               ((u32)0x00000001 << 29)                             /*!<R 0   */
#define VOE_SHIFT_CNT_LIMIT                          25
#define VOE_MASK_CNT_LIMIT                           ((u32)0x0000000F << 25)                             /*!<R/W 0  0: 0x001 1: 0x003 2: 0x007 3: 0x00F 4: 0x01F 5: 0x03F 6: 0x07F 7: 0x0FF 8: 0x1FF 9: 0x3FF 10: 0x7FF 11~15: 0xFFF Watchdog Count= (0x00000001 << (CNT_LIMIT + 1)) - 1 */
#define VOE_SHIFT_WDT_CLEAR                          24
#define VOE_BIT_WDT_CLEAR                            ((u32)0x00000001 << 24)                             /*!<W1C 0  Write 1 to clear timer */
#define VOE_SHIFT_RSVD57                             17
#define VOE_MASK_RSVD57                              ((u32)0x0000007F << 17)                             /*!<R 0   */
#define VOE_SHIFT_WDT_EN_BYTE                        16
#define VOE_BIT_WDT_EN_BYTE                          ((u32)0x00000001 << 16)                             /*!<R/W 0  Set 1 to enable watch dog timer */
#define VOE_SHIFT_VNDR_DIVFACTOR                     0
#define VOE_MASK_VNDR_DIVFACTOR                      ((u32)0x0000FFFF << 0)                              /*!<R/W 1  Dividing factor. Watch dog timer is count with 32KHz/(divfactor+1). Minimum dividing factor is 1. */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_ERAC_CTRL
 * @brief  N/A                                       (@ 0X200)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD58                             3
#define VOE_MASK_RSVD58                              ((u32)0x1FFFFFFF << 3)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ERAC_RST_DIS                       2
#define VOE_BIT_ERAC_RST_DIS                         ((u32)0x00000001 << 2)                              /*!<R/W 0  0: disable erac, 1: enable erac.(keep stable when ERAC_RD_EN/ERAC_WR_EN asserted) */
#define VOE_SHIFT_ERAC_RD_EN                         1
#define VOE_BIT_ERAC_RD_EN                           ((u32)0x00000001 << 1)                              /*!<R/W 0  Auto reset to 0 when erac read/write finished. BIT_ERAC_RD_EN and BIT_ERAC_WR_EN can not be asserted at the same time */
#define VOE_SHIFT_ERAC_WR_EN                         0
#define VOE_BIT_ERAC_WR_EN                           ((u32)0x00000001 << 0)                              /*!<R/W 0  Auto reset to 0 when erac read/write finished. BIT_ERAC_RD_EN and BIT_ERAC_WR_EN can not be asserted at the same time */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_ERAC_NUM_WR
 * @brief  N/A                                       (@ 0X204)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD59                             9
#define VOE_MASK_RSVD59                              ((u32)0x007FFFFF << 9)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ERAC_NUM_WR                        0
#define VOE_MASK_ERAC_NUM_WR                         ((u32)0x000001FF << 0)                              /*!<R/W 0  gives number of external memory to be written. Range: 1-512 (keep stable when BIT_ERAC_RD_EN/BIT_ERAC_WR_EN asserted) */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_ERAC_SMBA_OA_WR
 * @brief  N/A                                       (@ 0X208)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD60                             13
#define VOE_MASK_RSVD60                              ((u32)0x0007FFFF << 13)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_ERAC_SMBA_OA_WR                    0
#define VOE_MASK_ERAC_SMBA_OA_WR                     ((u32)0x00001FFF << 0)                              /*!<R/W 0  address of the table stored the address of the registers to be written. (keep stable when BIT_ERAC_RD_EN/BIT_ERAC_WR_EN asserted) */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_ERAC_SMBA_WR
 * @brief  N/A                                       (@ 0X20C)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD61                             13
#define VOE_MASK_RSVD61                              ((u32)0x0007FFFF << 13)                             /*!<R/W 0  RSVD */
#define VOE_SHIFT_ERAC_SMBA_WR                       0
#define VOE_MASK_ERAC_SMBA_WR                        ((u32)0x00001FFF << 0)                              /*!<R/W 0  address offset of the data to be write in shared memory (keep stable when BIT_ERAC_RD_EN/BIT_ERAC_WR_EN asserted) */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_ERAC_ERBA_WR
 * @brief  N/A                                       (@ 0X210)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_ERAC_ERBA_WR                       0
#define VOE_MASK_ERAC_ERBA_WR                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  address offset of the data to be wirte in external mem (keep stable when BIT_ERAC_RD_EN/BIT_ERAC_WR_EN asserted) */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_ERAC_NUM_RD
 * @brief  N/A                                       (@ 0X214)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD62                             9
#define VOE_MASK_RSVD62                              ((u32)0x007FFFFF << 9)                              /*!<R/W 0  RSVD */
#define VOE_SHIFT_ERAC_NUM_RD                        0
#define VOE_MASK_ERAC_NUM_RD                         ((u32)0x000001FF << 0)                              /*!<R/W 0  gives number of external memory to be read. Range: 1-512 (keep stable when BIT_ERAC_RD_EN/BIT_ERAC_WR_EN asserted) */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_ERAC_SMBA_OA_RD
 * @brief  N/A                                       (@ 0X218)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD63                             13
#define VOE_MASK_RSVD63                              ((u32)0x0007FFFF << 13)                             /*!<R/W 0  TBD */
#define VOE_SHIFT_ERAC_SMBA_OA_RD                    0
#define VOE_MASK_ERAC_SMBA_OA_RD                     ((u32)0x00001FFF << 0)                              /*!<R/W 0  address of the table stored the address of the registers to be read (keep stable when BIT_ERAC_RD_EN/BIT_ERAC_WR_EN asserted) */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_ERAC_SMBA_RD
 * @brief  N/A                                       (@ 0X21C)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_RSVD64                             13
#define VOE_MASK_RSVD64                              ((u32)0x0007FFFF << 13)                             /*!<R/W 0  TBD */
#define VOE_SHIFT_ERAC_SMBA_RD                       0
#define VOE_MASK_ERAC_SMBA_RD                        ((u32)0x00001FFF << 0)                              /*!<R/W 0  address offset of the data to be read in shared memory (keep stable when BIT_ERAC_RD_EN/BIT_ERAC_WR_EN asserted) */
/** @} */

/**************************************************************************//**
 * @defgroup VOE_REG_ERAC_ERBA_RD
 * @brief  N/A                                       (@ 0X220)
 * @{
 *****************************************************************************/
#define VOE_SHIFT_ERAC_ERBA_RD                       0
#define VOE_MASK_ERAC_ERBA_RD                        ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  address offset of the data to be read in external mem (keep stable when BIT_ERAC_RD_EN/BIT_ERAC_WR_EN asserted) */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_VOE
 * @{
 * @brief rtl8735b_VOE Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t VOE_REG_VOE_SYSTEM_CTRL ;                /*!<  N/A register,  Address offset: 0x00 */
	__IO uint32_t VOE_REG_KM_FW_BASE_ADDRESS ;             /*!<  N/A register,  Address offset: 0x04 */
	__IO uint32_t VOE_REG_KM_FW_LEN ;                      /*!<  N/A register,  Address offset: 0x08 */
	__IO uint32_t VOE_REG_SEND_MESSAGE_EXTERNAL_CTRL ;     /*!<  N/A register,  Address offset: 0x0C */
	__IO uint32_t VOE_REG_READ_MESSAGE_EXTERNAL_CTRL ;     /*!<  N/A register,  Address offset: 0x10 */
	__IO uint32_t VOE_REG_INTERRUPT_STATUS_OF_EXTERNAL_CPU ;/*!<  N/A register,  Address offset: 0x14 */
	__IO uint32_t VOE_REG_INTERRUPT_MASK_OF_EXTERNAL_CPU ; /*!<  N/A register,  Address offset: 0x18 */
	__IO uint32_t VOE_RSVD ;                               /*!<  N/A register,  Address offset: 0x1C */
	__IO uint32_t RSVD0[56];                               /*!<  Reserved,  Address offset:0x20-0xFC */
	__IO uint32_t VOE_REG_VOE_ARB_PRIORITY_CTRL0 ;         /*!<  N/A register,  Address offset: 0x100 */
	__IO uint32_t VOE_REG_VOE_ARB_PRIORITY_CTRL1 ;         /*!<  N/A register,  Address offset: 0x104 */
	__IO uint32_t VOE_REG_SEND_MESSAGE_KM_CTRL ;           /*!<  N/A register,  Address offset: 0x108 */
	__IO uint32_t VOE_REG_READ_MESSAGE_KM_CTRL ;           /*!<  N/A register,  Address offset: 0x10C */
	__IO uint32_t VOE_REG_INTERRUPT_STATUS_OF_KM ;         /*!<  N/A register,  Address offset: 0x110 */
	__IO uint32_t VOE_REG_INTERRUPT_MASK_OF_KM ;           /*!<  N/A register,  Address offset: 0x114 */
	__IO uint32_t VOE_REG_MBIST_REG ;                      /*!<  N/A register,  Address offset: 0x118 */
	__IO uint32_t VOE_REG_KM_DBGEN ;                       /*!<  N/A register,  Address offset: 0x11C */
	__IO uint32_t VOE_REG_KM_INITVTOR_S ;                  /*!<  N/A register,  Address offset: 0x120 */
	__IO uint32_t VOE_REG_KM_INITVTOR_NS ;                 /*!<  N/A register,  Address offset: 0x124 */
	__IO uint32_t VOE_REG_KM_INIT ;                        /*!<  N/A register,  Address offset: 0x128 */
	__IO uint32_t VOE_REG_KM_TMODE ;                       /*!<  N/A register,  Address offset: 0x12C */
	__IO uint32_t VOE_REG_KM_CFG_CPU_NUM ;                 /*!<  N/A register,  Address offset: 0x130 */
	__IO uint32_t VOE_REG_MBIST_REG_FBCU_0 ;               /*!<  N/A register,  Address offset: 0x134 */
	__IO uint32_t VOE_REG_MBIST_REG_FBCU_1 ;               /*!<  N/A register,  Address offset: 0x138 */
	__IO uint32_t VOE_REG_KM_ADDRESS_REMAP_CTRL ;          /*!<  N/A register,  Address offset: 0x13C */
	__IO uint32_t VOE_REG_KM_ITCM_REMAP_BASE ;             /*!<  N/A register,  Address offset: 0x140 */
	__IO uint32_t VOE_REG_KM_DTCM_REMAP_BASE ;             /*!<  N/A register,  Address offset: 0x144 */
	__IO uint32_t VOE_REG_MBIST_KM_ROM ;                   /*!<  N/A register,  Address offset: 0x148 */
	__I  uint32_t VOE_REG_MBIST_ROM_MISR_DOUT_H ;          /*!<  N/A register,  Address offset: 0x14C */
	__I  uint32_t VOE_REG_MBIST_ROM_MISR_DOUT_L ;          /*!<  N/A register,  Address offset: 0x150 */
	__IO uint32_t VOE_REG_MBIST_KM_RAM_WR ;                /*!<  N/A register,  Address offset: 0x154 */
	__I  uint32_t VOE_REG_MBIST_KM_RAM_RD ;                /*!<  N/A register,  Address offset: 0x158 */
	__I  uint32_t VOE_REG_MBIST_DTCM_ROM_MISR_DOUT_H ;     /*!<  N/A register,  Address offset: 0x15C */
	__I  uint32_t VOE_REG_MBIST_DTCM_ROM_MISR_DOUT_L ;     /*!<  N/A register,  Address offset: 0x160 */
	__I  uint32_t VOE_REG_PC_VALUE ;                       /*!<  N/A register,  Address offset: 0x164 */
	__I  uint32_t VOE_REG_RETIRED_INSTRUCTION_ADDR_0 ;     /*!<  N/A register,  Address offset: 0x168 */
	__I  uint32_t VOE_REG_RETIRED_INSTRUCTION_ADDR_1 ;     /*!<  N/A register,  Address offset: 0x16C */
	__IO uint32_t VOE_REG_VOE_WATCHDOG_CTRL ;              /*!<  N/A register,  Address offset: 0x170 */
	__IO uint32_t RSVD1[35];                               /*!<  Reserved,  Address offset:0x174-0x1FC */
	__IO uint32_t VOE_REG_ERAC_CTRL ;                      /*!<  N/A register,  Address offset: 0x200 */
	__IO uint32_t VOE_REG_ERAC_NUM_WR ;                    /*!<  N/A register,  Address offset: 0x204 */
	__IO uint32_t VOE_REG_ERAC_SMBA_OA_WR ;                /*!<  N/A register,  Address offset: 0x208 */
	__IO uint32_t VOE_REG_ERAC_SMBA_WR ;                   /*!<  N/A register,  Address offset: 0x20C */
	__IO uint32_t VOE_REG_ERAC_ERBA_WR ;                   /*!<  N/A register,  Address offset: 0x210 */
	__IO uint32_t VOE_REG_ERAC_NUM_RD ;                    /*!<  N/A register,  Address offset: 0x214 */
	__IO uint32_t VOE_REG_ERAC_SMBA_OA_RD ;                /*!<  N/A register,  Address offset: 0x218 */
	__IO uint32_t VOE_REG_ERAC_SMBA_RD ;                   /*!<  N/A register,  Address offset: 0x21C */
	__IO uint32_t VOE_REG_ERAC_ERBA_RD ;                   /*!<  N/A register,			Address offset: 0x220 */
} VOE_TypeDef;
/** @} */

#endif
