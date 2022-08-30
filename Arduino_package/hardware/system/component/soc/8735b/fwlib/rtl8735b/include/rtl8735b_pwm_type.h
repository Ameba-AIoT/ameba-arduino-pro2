#ifndef _RTL8735B_PWM_TYPE_2_H_
#define _RTL8735B_PWM_TYPE_2_H_

/**************************************************************************//**
 * @defgroup PWM_CTRL
 * @brief  PWM Control Register                      (@ 0X000)
 * @{
 *****************************************************************************/
#define PWM_SHIFT_CTRL_SET                           31
#define PWM_BIT_CTRL_SET                             ((u32)0x00000001 << 31)                             /*!<R/W 0  SW can change setting only at ctrl_set = 0, and set ctrl_set = 1 after changing PWM Ctrl. HW will clear ctrl_set bit after changing PWM Ctrl. PS. If this PWM is disabled (PWMx_EN=0), the HW will not clear this bit. PS. if this bit is asserted and the duty auto adjustment is enabled, when the PWM is enabled the HW will updates its duty at the 1st PWM period and then start the duty adjustment at 2nd PWM period. */
#define PWM_SHIFT_PAUSE                              30
#define PWM_BIT_PAUSE                                ((u32)0x00000001 << 30)                             /*!<R/W 0  The paus control: 0: Normal running 1: To pause the PWM out at current PWM period end. Since the PWM output is not stopped immediately, the software can poll the BIT_PERI_PWMx_RUNSTS to know the PWM out is still running or is paused. */
#define PWM_SHIFT_RUN_STS                            29
#define PWM_BIT_RUN_STS                              ((u32)0x00000001 << 29)                             /*!<R 0  The PWM output running status: 0: PWM output is paused 1: the PWM output is running. */
#define PWM_SHIFT_PERIOD_IE                          28
#define PWM_BIT_PERIOD_IE                            ((u32)0x00000001 << 28)                             /*!<R/W 0  This bit control the PWM period end interrupt enable (1) or disable (0). When the PWM period end interrupt is enabled, the PWM HW will assert the interrupt on every PWM period end time. This interrupt status can be read from pwm_int_status. */
#define PWM_SHIFT_CUR_DUTY                           16
#define PWM_MASK_CUR_DUTY                            ((u32)0x00000FFF << 16)                             /*!<R 0  The current duty size which is adjusted by the duty auto-adjustment HW. The SW can read this field to know the current duty size. However, the latest duty size may not be sync to this field on time or the value may transition while the SW is reading this field. So use in-direct read method to read the duty size is more save and is suggested. */
#define PWM_SHIFT_CLK_SEL                            12
#define PWM_MASK_CLK_SEL                             ((u32)0x0000000F << 12)                             /*!<R/W 0  The tick source selection, G-timer 0 ~ 7 or SClk: 0: GTIMER 0 1: GTIMER 1 ... 7: GTIMER 7 8: sclk */
#define PWM_SHIFT_DUTY                               0
#define PWM_MASK_DUTY                                ((u32)0x00000FFF << 0)                              /*!<R/W 0  The on-duty duration of PWM pulse. The time unit is configured by the GTIMER which is specified by clk_sel field. It can be written at any time, but HW will apply the changing at PWM enable time or at the end of PWM period. */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_TIMING_CTRL
 * @brief  PWM Timing Control Register               (@ 0X004)
 * @{
 *****************************************************************************/
#define PWM_SHIFT_DUTY_START                         16
#define PWM_MASK_DUTY_START                          ((u32)0x00000FFF << 16)                             /*!<R/W 0  The start of ON duration of PWM pulse in the period. The time unit is the same as PWM period. It can be written at any time, but HW change setting only at PWM enable and the end of period. */
#define PWM_SHIFT_PERIOD                             0
#define PWM_MASK_PERIOD                              ((u32)0x00000FFF << 0)                              /*!<R/W 0  The period of PWM pulse. The time unit is configured by the GTIMER which is specified by the clk_sel field. It can be written at any time, but the HW will apply the changing at PWM enable time or at the end of PWM period. */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_AUTO_ADJ_CTRL
 * @brief  PWM Duty Auto Adjustment Control Register (@ 0X008)
 * @{
 *****************************************************************************/
#define PWM_SHIFT_ADJ_EN                             31
#define PWM_BIT_ADJ_EN                               ((u32)0x00000001 << 31)                             /*!<R/W 0  This bit is used to enable the Duty Ato Adjustment. 0: Disable 1: Enable PS. If this bit is 1, the duty of the auto adjustment will override the duty setting in the pwm_ctrl register.  */
#define PWM_SHIFT_ADJ_DIR                            30
#define PWM_BIT_ADJ_DIR                              ((u32)0x00000001 << 30)                             /*!<R/W 0  This bit is used to set the Duty Ato Adjustment direction. 0: Decrease Duty 1: Increase Duty */
#define PWM_SHIFT_ADJ_LOOP_EN                        29
#define PWM_BIT_ADJ_LOOP_EN                          ((u32)0x00000001 << 29)                             /*!<R/W 0  This bit is used to enable the Duty Auto Adjustment Loop mode. 0: Disable 1: Enable If the Loop Mode is enabled, reverse the Duty Auto Adjustment direction when the adjusted Duty reach the Up Limit or the Down Limit. */
#define PWM_SHIFT_DUTY_UP_LIM_IE                     28
#define PWM_BIT_DUTY_UP_LIM_IE                       ((u32)0x00000001 << 28)                             /*!<R/W 0  This bit is used to enable the Interrupt of the Duty Auto Adjustment. 0: Disable 1: Enable If the Interrupt is enabled, issue an interrupt when the Adjusted Duty reach the Up Limit. */
#define PWM_SHIFT_DUTY_DN_LIM_IE                     27
#define PWM_BIT_DUTY_DN_LIM_IE                       ((u32)0x00000001 << 27)                             /*!<R/W 0  This bit is used to enable the Interrupt of the Duty Auto Adjustment. 0: Disable 1: Enable If the Interrupt is enabled, issue an interrupt when the Adjusted Duty reach the Down Limit. */
#define PWM_SHIFT_DUTY_INC_STEP                      12
#define PWM_MASK_DUTY_INC_STEP                       ((u32)0x000003FF << 12)                             /*!<R/W 0  The Duty Increasing Step size of the Duty Auto Adjustment */
#define PWM_SHIFT_DUTY_DEC_STEP                      0
#define PWM_MASK_DUTY_DEC_STEP                       ((u32)0x000003FF << 0)                              /*!<R/W 0  The Duty Decreasing Step size of the Duty Auto Adjustment. */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_AUTO_ADJ_LIMIT
 * @brief  PWM Duty Auto Adjustment Limit Register   (@ 0X00C)
 * @{
 *****************************************************************************/
#define PWM_SHIFT_DUTY_ADJ_UP_LIM                    16
#define PWM_MASK_DUTY_ADJ_UP_LIM                     ((u32)0x00000FFF << 16)                             /*!<R/W 0  The up limit of the duty period for the duty ratio auto adjustment */
#define PWM_SHIFT_DUTY_ADJ_DN_LIM                    0
#define PWM_MASK_DUTY_ADJ_DN_LIM                     ((u32)0x00000FFF << 0)                              /*!<R/W 0  The down limit (in ticks) of the duty period for the duty ratio auto adjustment */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_AUTO_ADJ_CYCLE
 * @brief  PWM Duty Auto Adjustment Cycle Count Register (@ 0X010)
 * @{
 *****************************************************************************/
#define PWM_SHIFT_ADJ_CYCLES                         0
#define PWM_MASK_ADJ_CYCLES                          ((u32)0x00000FFF << 0)                              /*!<R/W 0  The Cycle Count of the Duty Auto Adjustment. The Duty size will be increased/decreased with a step size every Cycle Count of PWM period */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_OUT_DMA
 * @brief  PWMx Output DMA Mode Register             (@ 0X014)
 * @{
 *****************************************************************************/
#define PWM_SHIFT_DMA_MODE                           2
#define PWM_BIT_DMA_MODE                             ((u32)0x00000001 << 2)                              /*!<R/W 0  1 : Enable, 0: Disable DMA Mode. */
#define PWM_SHIFT_CHG_PERIOD                         1
#define PWM_BIT_CHG_PERIOD                           ((u32)0x00000001 << 1)                              /*!<R/W 0  1: this parameter defines to update PWM period register for each period-end interrupt. 0: no update. */
#define PWM_SHIFT_CHG_DUTY                           0
#define PWM_BIT_CHG_DUTY                             ((u32)0x00000001 << 0)                              /*!<R/W 0  1: this parameter defines to update PWM duty register for each period-end interrupt. 0: no update. */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_DMA_BUFF
 * @brief  BIT_DMA_BUFF                              (@ 0X018)
 * @{
 *****************************************************************************/
#define PWM_SHIFT_BUFF                               0
#define PWM_MASK_BUFF                                ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Data register for DMA mode. */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_PWM
 * @{
 * @brief rtl8735b_PWM Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t PWM_CTRL ;                               /*!<  PWM Control Register register,  Address offset: 0x000 */
	__IO uint32_t PWM_TIMING_CTRL ;                        /*!<  PWM Timing Control Register register,  Address offset: 0x004 */
	__IO uint32_t PWM_AUTO_ADJ_CTRL ;                      /*!<  PWM Duty Auto Adjustment Control Register register,  Address offset: 0x008 */
	__IO uint32_t PWM_AUTO_ADJ_LIMIT ;                     /*!<  PWM Duty Auto Adjustment Limit Register register,  Address offset: 0x00C */
	__IO uint32_t PWM_AUTO_ADJ_CYCLE ;                     /*!<  PWM Duty Auto Adjustment Cycle Count Register register,  Address offset: 0x010 */
	__IO uint32_t PWM_OUT_DMA ;                            /*!<  PWMx Output DMA Mode Register register,  Address offset: 0x014 */
	__IO uint32_t PWM_DMA_BUFF ;                           /*!<  BIT_DMA_BUFF register,          Address offset: 0x018 */
} PWM_TypeDef;
/** @} */

#endif
