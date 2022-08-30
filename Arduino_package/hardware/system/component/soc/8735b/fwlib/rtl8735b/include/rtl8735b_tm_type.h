#ifndef _RTL8735B_TM_TYPE_H_
#define _RTL8735B_TM_TYPE_H_

/**************************************************************************//**
 * @defgroup TM_LC
 * @brief  Timer load count register                 (@ 0X000)
 * @{
 *****************************************************************************/
#define TM_SHIFT_LC                                  0
#define TM_MASK_LC                                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  The counter value to be loaded into the timer counter when timer is enabled or reset. Min = 0, when prescaler register > 0; otherwise Min = 1. */
/** @} */

/**************************************************************************//**
 * @defgroup TM_TC
 * @brief  Timer current counter register            (@ 0X004)
 * @{
 *****************************************************************************/
#define TM_SHIFT_TC                                  0
#define TM_MASK_TC                                   ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Current counter value. */
/** @} */

/**************************************************************************//**
 * @defgroup TM_PC
 * @brief  Timer prescaler counter register          (@ 0X008)
 * @{
 *****************************************************************************/
#define TM_SHIFT_PC                                  0
#define TM_MASK_PC                                   ((u32)0x000003FF << 0)                              /*!<R/W 0  Pre-scaler counter will be increased every clock after timer is enabled. When the prescaler counter is equal to PR, the next clock increments (decrements) the TC and clears the PC. */
/** @} */

/**************************************************************************//**
 * @defgroup TM_PR
 * @brief  Timer prescaler register                  (@ 0X00C)
 * @{
 *****************************************************************************/
#define TM_SHIFT_PR                                  0
#define TM_MASK_PR                                   ((u32)0x000003FF << 0)                              /*!<R/W 0  When the PC is equal to this value, the next clock increments (decrements) the TC and clears the PC. */
/** @} */

/**************************************************************************//**
 * @defgroup TM_CTRL
 * @brief  Timer control register                    (@ 0X010)
 * @{
 *****************************************************************************/
#define TM_SHIFT_CNT_MOD                             3
#define TM_BIT_CNT_MOD                               ((u32)0x00000001 << 3)                              /*!<R/W 0  Timer counting mode: 0: Up-counter 1: Down-counter */
#define TM_SHIFT_IMR                                 2
#define TM_BIT_IMR                                   ((u32)0x00000001 << 2)                              /*!<R/W 0  Timer Interrupt mask: 0: disable interrupt 1: enable interrupt */
#define TM_SHIFT_MOD                                 1
#define TM_BIT_MOD                                   ((u32)0x00000001 << 1)                              /*!<R/W 0  Timer operation mode: 0: timer mode (periodical mode); it reloads LC to TC and repeat the process according to the setting when the timeout event occurred. 1: counter mode (one-shot mode); only one time process. */
#define TM_SHIFT_EN                                  0
#define TM_BIT_EN                                    ((u32)0x00000001 << 0)                              /*!<R/W 0  Timer enable control: 0: Disable 1: Enable */
/** @} */

/**************************************************************************//**
 * @defgroup TM_ISR
 * @brief  Timer0 interrupt status register          (@ 0X014)
 * @{
 *****************************************************************************/
#define TM_SHIFT_MATCH_EV3                           4
#define TM_BIT_MATCH_EV3                             ((u32)0x00000001 << 4)                              /*!<R/W1C 0  Counter value match event3 interrupt. */
#define TM_SHIFT_MATCH_EV2                           3
#define TM_BIT_MATCH_EV2                             ((u32)0x00000001 << 3)                              /*!<R/W1C 0  Counter value match event2 interrupt. */
#define TM_SHIFT_MATCH_EV1                           2
#define TM_BIT_MATCH_EV1                             ((u32)0x00000001 << 2)                              /*!<R/W1C 0  Counter value match event1 interrupt. */
#define TM_SHIFT_MATCH_EV0                           1
#define TM_BIT_MATCH_EV0                             ((u32)0x00000001 << 1)                              /*!<R/W1C 0  Counter value match event0 interrupt. */
#define TM_SHIFT_TIMEOUT                             0
#define TM_BIT_TIMEOUT                               ((u32)0x00000001 << 0)                              /*!<R/W1C 0  Timeout interrupt */
/** @} */

/**************************************************************************//**
 * @defgroup TM_MECTRL
 * @brief  Timer match event control register        (@ 0X01C)
 * @{
 *****************************************************************************/
#define TM_SHIFT_ME3_EN                              3
#define TM_BIT_ME3_EN                                ((u32)0x00000001 << 3)                              /*!<R/W 0  Counter value match event3 enable control: 0: Disable 1: Enable */
#define TM_SHIFT_ME2_EN                              2
#define TM_BIT_ME2_EN                                ((u32)0x00000001 << 2)                              /*!<R/W 0  Counter value match event2 enable control: 0: Disable 1: Enable */
#define TM_SHIFT_ME1_EN                              1
#define TM_BIT_ME1_EN                                ((u32)0x00000001 << 1)                              /*!<R/W 0  Counter value match event1 enable control: 0: Disable 1: Enable */
#define TM_SHIFT_ME0_EN                              0
#define TM_BIT_ME0_EN                                ((u32)0x00000001 << 0)                              /*!<R/W 0  Counter value match event0 enable control: 0: Disable 1: Enable */
/** @} */

/**************************************************************************//**
 * @defgroup TM_ME0
 * @brief  Timer match event0 counter register       (@ 0X020)
 * @{
 *****************************************************************************/
#define TM_SHIFT_ME0                                 0
#define TM_MASK_ME0                                  ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Timer counter value for metch event0. */
/** @} */

/**************************************************************************//**
 * @defgroup TM_ME1
 * @brief  Timer match event1 counter register       (@ 0X024)
 * @{
 *****************************************************************************/
#define TM_SHIFT_ME1                                 0
#define TM_MASK_ME1                                  ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Timer counter value for metch event1. */
/** @} */

/**************************************************************************//**
 * @defgroup TM_ME2
 * @brief  Timer match event2 counter register       (@ 0X028)
 * @{
 *****************************************************************************/
#define TM_SHIFT_ME2                                 0
#define TM_MASK_ME2                                  ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Timer counter value for metch event2. */
/** @} */

/**************************************************************************//**
 * @defgroup TM_ME3
 * @brief  Timer match event3 counter register       (@ 0X02C)
 * @{
 *****************************************************************************/
#define TM_SHIFT_ME3                                 0
#define TM_MASK_ME3                                  ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  Timer counter value for metch event3. */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_TM
 * @{
 * @brief rtl8735b_TM Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t TM_LC ;                                  /*!<  Timer load count register,  Address offset: 0x000 */
	__IO uint32_t TM_TC ;                                  /*!<  Timer current counter register,  Address offset: 0x004 */
	__IO uint32_t TM_PC ;                                  /*!<  Timer prescaler counter register,  Address offset: 0x008 */
	__IO uint32_t TM_PR ;                                  /*!<  Timer prescaler register,  Address offset: 0x00C */
	__IO uint32_t TM_CTRL ;                                /*!<  Timer control register,  Address offset: 0x010 */
	__IO uint32_t TM_ISR ;                                 /*!<  Timer0 interrupt status register,  Address offset: 0x014 */
	__IO uint32_t RSVD0;                                  /*!<  Reserved,  Address offset:0x18 */
	__IO uint32_t TM_MECTRL ;                              /*!<  Timer match event control register,  Address offset: 0x01C */
	__IO uint32_t TM_ME0 ;                                 /*!<  Timer match event0 counter register,  Address offset: 0x020 */
	__IO uint32_t TM_ME1 ;                                 /*!<  Timer match event1 counter register,  Address offset: 0x024 */
	__IO uint32_t TM_ME2 ;                                 /*!<  Timer match event2 counter register,  Address offset: 0x028 */
	__IO uint32_t TM_ME3 ;                                 /*!<  Timer match event3 counter register,            Address offset: 0x02C */
} TM_TypeDef;
/** @} */

#endif
