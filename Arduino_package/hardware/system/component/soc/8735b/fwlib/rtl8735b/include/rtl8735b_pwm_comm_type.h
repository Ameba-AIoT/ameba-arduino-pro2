#ifndef _RTL8735B_PWM_COMM_TYPE_2_H_
#define _RTL8735B_PWM_COMM_TYPE_2_H_

/**************************************************************************//**
 * @defgroup PWM_COMM_ENABLE_STATUS
 * @brief  PWM enable status Register                (@ 0X000)
 * @{
 *****************************************************************************/
#define PWM_COMM_SHIFT_PWM_EN_STS                    0
#define PWM_COMM_MASK_PWM_EN_STS                     ((u32)0x00000FFF << 0)                              /*!<R 0  Each bit indicates the enabling status of corresponding PWM: 0: the specific PWM is Disabled 1: the specific PWM is Enabled */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_COMM_ENABLE_CTRL
 * @brief  PWM enable Register                       (@ 0X004)
 * @{
 *****************************************************************************/
#define PWM_COMM_SHIFT_PWM_EN                        0
#define PWM_COMM_MASK_PWM_EN                         ((u32)0x00000FFF << 0)                              /*!<R/W 0  Each bit is used to enablel the corresponding PWM function: When wrote 0: No operation 1: the specific PWM is enabled and the specific bit of REG_PWM_EN_STS is ONE. */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_COMM_DISABLE_CTRL
 * @brief  PWM disable Register                      (@ 0X008)
 * @{
 *****************************************************************************/
#define PWM_COMM_SHIFT_PWM_DIS                       0
#define PWM_COMM_MASK_PWM_DIS                        ((u32)0x00000FFF << 0)                              /*!<R/W 0  Each bit is used to disable the corresponding PW6M function: When wrote 0: No operation 1: the conrtolled PWM is disabled and the specific bit of REG_PWM_EN_STS is ZERO. */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_COMM_INT_STATUS
 * @brief  PWM Interrupt Status Register             (@ 0X00C)
 * @{
 *****************************************************************************/
#define PWM_COMM_SHIFT_PERIOD_END                    24
#define PWM_COMM_MASK_PERIOD_END                     ((u32)0x000000FF << 24)                             /*!<R/W1C 0  This bits are used to indicate the interrupt pending status for PWM 0 ~7 period end. Write 1 clear. Bit 24 for PWM0, bit 25 for PWM1, ...bit31 for PWM7. */
#define PWM_COMM_SHIFT_DUTY_ADJ_UP_LIM               16
#define PWM_COMM_MASK_DUTY_ADJ_UP_LIM                ((u32)0x000000FF << 16)                             /*!<R/W1C 0  To indicate the interrupt pending status for PWM 0 ~ 7 duty auto-adjustment reaches the up-limit. Write 1 clear. Bit 16 for PWM0, bit 17 for PWM1, ...bit23 for PWM7. */
#define PWM_COMM_SHIFT_DUTY_ADJ_DN_LIM               0
#define PWM_COMM_MASK_DUTY_ADJ_DN_LIM                ((u32)0x000000FF << 0)                              /*!<R/W1C 0  To indicate the interrupt pending status for PWM 0 ~ 7 duty auto-adjustment reaches the down-limit. Write 1 clear. Bit 0 for PWM0, bit 1 for PWM1, ...bit7 for PWM7. */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_COMM_INT_STATUS1
 * @brief  PWM Interrupt Status1 Register            (@ 0X010)
 * @{
 *****************************************************************************/
#define PWM_COMM_SHIFT_PERIOD_END1                   24
#define PWM_COMM_MASK_PERIOD_END1                    ((u32)0x0000000F << 24)                             /*!<R/W1C 0  This bits are used to indicate the interrupt pending status for PWM 8 ~B period end. Write 1 clear. Bit 24 for PWM8, bit 25 for PWM1, ...bit27 for PWMB. */
#define PWM_COMM_SHIFT_DUTY_ADJ_UP_LIM1              16
#define PWM_COMM_MASK_DUTY_ADJ_UP_LIM1               ((u32)0x0000000F << 16)                             /*!<R/W1C 0  To indicate the interrupt pending status for PWM 8 ~ B duty auto-adjustment reaches the up-limit. Write 1 clear. Bit 16 for PWM8, bit 17 for PWM9, ...bit19 for PWMB. */
#define PWM_COMM_SHIFT_DUTY_ADJ_DN_LIM1              0
#define PWM_COMM_MASK_DUTY_ADJ_DN_LIM1               ((u32)0x0000000F << 0)                              /*!<R/W1C 0  To indicate the interrupt pending status for PWM 8 ~ B duty auto-adjustment reaches the down-limit. Write 1 clear. Bit 0 for PWM8, bit 1 for PWM9, ...bit3 for PWMB. */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_COMM_INDREAD_IDX
 * @brief  PWM Index of Indirect Read Register       (@ 0X014)
 * @{
 *****************************************************************************/
#define PWM_COMM_SHIFT_POOL                          7
#define PWM_COMM_BIT_POOL                            ((u32)0x00000001 << 7)                              /*!<R/W 0  Set this bit to enable indirect read current value of timer selected by BIT_PWM_INDREAD_IDX. This bit is cleared by HW when reading is finished and indicates REG_PERI_PWM_INDREAD_DUTY is ready. */
#define PWM_COMM_SHIFT_SYNC_MODE                     4
#define PWM_COMM_BIT_SYNC_MODE                       ((u32)0x00000001 << 4)                              /*!<R/W 0  Register sync mode selection for PWM clock and APB clock 0: Freq. of APB clock >> Freq. of PWM clock (about 10 times) 1: Freq. of PWM clock >= Freq. of APB clock */
#define PWM_COMM_SHIFT_PWM_SEL                       0
#define PWM_COMM_MASK_PWM_SEL                        ((u32)0x0000000F << 0)                              /*!<R/W 0  This field is used to assign the PWM index (0 ~ 7) for the auto adjusted duty size indirect reading. */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_COMM_INDREAD_DUTY
 * @brief  PWM Auto Adjusted Duty Indirect Read Register (@ 0X018)
 * @{
 *****************************************************************************/
#define PWM_COMM_SHIFT_PWM_DUTY                      0
#define PWM_COMM_MASK_PWM_DUTY                       ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field is used to read the auto adjusted duty size of the PWM which is assigned by the pwm_sel. The SW should assign the PWM to read by write the pwm_sel and then read this field to get the current duty size of the specified PWM. */
/** @} */

/**************************************************************************//**
 * @defgroup PWM_COMM_COMPLEMENTARY
 * @brief  PWM Complementary Register                (@ 0X01C)
 * @{
 *****************************************************************************/
#define PWM_COMM_SHIFT_PWM_DB                        6
#define PWM_COMM_MASK_PWM_DB                         ((u32)0x00FFFFFF << 6)                              /*!<R/W 0  To indicate the amount of delay. Delay time = (1/Sclk)*PWMX_Y_DB. Bit 6~9 for PWM0_1_DB, bit 10~13 for PWM2_3_DB.. Bit 26~29 for PWMA_B_DB */
#define PWM_COMM_SHIFT_PWM_COMP_EN                   0
#define PWM_COMM_MASK_PWM_COMP_EN                    ((u32)0x0000003F << 0)                              /*!<R/W 0  Enable/Disable PWM Complementary mode. Bit 0 for PWM0_1, bit 1 for PWM2_3..bit 5 for PWMA_B */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_PWM_COMM
 * @{
 * @brief rtl8735b_PWM_COMM Register Declaration
 *****************************************************************************/
typedef struct {
	__I  uint32_t PWM_COMM_ENABLE_STATUS ;                 /*!<  PWM enable status Register register,  Address offset: 0x000 */
	__IO uint32_t PWM_COMM_ENABLE_CTRL ;                   /*!<  PWM enable Register register,  Address offset: 0x004 */
	__IO uint32_t PWM_COMM_DISABLE_CTRL ;                  /*!<  PWM disable Register register,  Address offset: 0x008 */
	__IO uint32_t PWM_COMM_INT_STATUS ;                    /*!<  PWM Interrupt Status Register register,  Address offset: 0x00C */
	__IO uint32_t PWM_COMM_INT_STATUS1 ;                   /*!<  PWM Interrupt Status1 Register register,  Address offset: 0x010 */
	__IO uint32_t PWM_COMM_INDREAD_IDX ;                   /*!<  PWM Index of Indirect Read Register register,  Address offset: 0x014 */
	__IO uint32_t PWM_COMM_INDREAD_DUTY ;                  /*!<  PWM Auto Adjusted Duty Indirect Read Register register,  Address offset: 0x018 */
	__IO uint32_t PWM_COMM_COMPLEMENTARY ;                 /*!<  PWM Complementary Register register,            Address offset: 0x01C */
} PWM_COMM_TypeDef;
/** @} */

#endif
