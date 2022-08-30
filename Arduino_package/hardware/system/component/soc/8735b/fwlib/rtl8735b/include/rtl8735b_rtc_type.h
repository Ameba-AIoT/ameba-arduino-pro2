#ifndef _rtl8735b_RTC_TYPE_H_
#define _rtl8735b_RTC_TYPE_H_

/**************************************************************************//**
 * @defgroup RTC_TYPE_REG_RTC_FEN
 * @brief
 * @{
 *****************************************************************************/
#define BIT_SHIFT_CKDIV_MOD_SEL                      4
#define BIT_CKDIV_MOD_SEL                            ((u32)0x00000001 << 4)                              /*!<R/W 0  0: Normal mode 1024 for 1s; 1: test mode 64 for 1s */
#define BIT_SHIFT_CKDIV_EN                           1
#define BIT_CKDIV_EN                                 ((u32)0x00000001 << 1)                              /*!<R/W 0  1: Enable RTC CLK divider */
#define BIT_SHIFT_RTC_EN                             0
#define BIT_RTC_EN                                   ((u32)0x00000001 << 0)                              /*!<R/W 0  1: Enable RTC  */
/** @} */

/**************************************************************************//**
 * @defgroup RTC_TYPE_REG_RTC_COMP
 * @brief
 * @{
 *****************************************************************************/
#define RTC_SHIFT_TYPE_FUNCTION_EN                   31
#define RTC_BIT_TYPE_FUNCTION_EN                     ((u32)0x00000001 << 31)                             /*!<R/W 0   */
#define RTC_SHIFT_TYPE_ADJUST_DIRECTION              18
#define RTC_BIT_TYPE_ADJUST_DIRECTION                ((u32)0x00000001 << 18)                             /*!<R/W 0  0: plus, 1 mimus */
#define RTC_SHIFT_TYPE_RTC_ADJUST_PERIOD_SEL         0
#define RTC_MASK_TYPE_RTC_ADJUST_PERIOD_SEL          ((u32)0x0003FFFF << 0)                              /*!<R/W 0x00000  unit: s */
/** @} */

/**************************************************************************//**
 * @defgroup RTC_TYPE_REG_RTC_IMR
 * @brief
 * @{
 *****************************************************************************/
#define BIT_SHIFT_RTC_ALRM_IMR                       16
#define BIT_RTC_ALRM_IMR                             ((u32)0x00000001 << 16)                             /*!<R/W 0   */
#define BIT_SHIFT_RTC_ALRM_DOY_IMR                   15
#define BIT_RTC_ALRM_DOY_IMR                         ((u32)0x00000001 << 15)                             /*!<R/W 0   */
#define BIT_SHIFT_RTC_ALRM_YRS_IMR                   14
#define BIT_RTC_ALRM_YRS_IMR                         ((u32)0x00000001 << 14)                             /*!<R/W 0   */
#define BIT_SHIFT_RTC_ALRM_MTH_IMR                   13
#define BIT_RTC_ALRM_MTH_IMR                         ((u32)0x00000001 << 13)                             /*!<R/W 0   */
#define BIT_SHIFT_RTC_ALRM_DOM_IMR                   12
#define BIT_RTC_ALRM_DOM_IMR                         ((u32)0x00000001 << 12)                             /*!<R/W 0   */
#define BIT_SHIFT_RTC_ALRM_DOW_IMR                   11
#define BIT_RTC_ALRM_DOW_IMR                         ((u32)0x00000001 << 11)                             /*!<R/W 0   */
#define BIT_SHIFT_RTC_ALRM_HRS_IMR                   10
#define BIT_RTC_ALRM_HRS_IMR                         ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define BIT_SHIFT_RTC_ALRM_MIN_IMR                   9
#define BIT_RTC_ALRM_MIN_IMR                         ((u32)0x00000001 << 9)                              /*!<R/W 0   */
#define BIT_SHIFT_RTC_ALRM_SEC_IMR                   8
#define BIT_RTC_ALRM_SEC_IMR                         ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define BIT_SHIFT_RTC_CNT_DOY_IMR                    7
#define BIT_RTC_CNT_DOY_IMR                          ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define BIT_SHIFT_RTC_CNT_YRS_IMR                    6
#define BIT_RTC_CNT_YRS_IMR                          ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define BIT_SHIFT_RTC_CNT_MTH_IMR                    5
#define BIT_RTC_CNT_MTH_IMR                          ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define BIT_SHIFT_RTC_CNT_DOM_IMR                    4
#define BIT_RTC_CNT_DOM_IMR                          ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define BIT_SHIFT_RTC_CNT_DOW_IMR                    3
#define BIT_RTC_CNT_DOW_IMR                          ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define BIT_SHIFT_RTC_CNT_HRS_IMR                    2
#define BIT_RTC_CNT_HRS_IMR                          ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define BIT_SHIFT_RTC_CNT_MIN_IMR                    1
#define BIT_RTC_CNT_MIN_IMR                          ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define BIT_SHIFT_RTC_CNT_SEC_IMR                    0
#define BIT_RTC_CNT_SEC_IMR                          ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup RTC_TYPE_REG_RTC_ISR
 * @brief
 * @{
 *****************************************************************************/
#define BIT_SHIFT_RTC_ALRM_ISR                       16
#define BIT_RTC_ALRM_ISR                             ((u32)0x00000001 << 16)                             /*!<R/W 0  Indicate ALL timer value match ALRM value */
#define BIT_SHIFT_RTC_ALRM_DOY_ISR                   15
#define BIT_RTC_ALRM_DOY_ISR                         ((u32)0x00000001 << 15)                             /*!<R/W 0  Indicate DOY timer value match ALRM_DOY */
#define BIT_SHIFT_RTC_ALRM_YRS_ISR                   14
#define BIT_RTC_ALRM_YRS_ISR                         ((u32)0x00000001 << 14)                             /*!<R/W 0  Indicate Year timer value match ALRM_YRS */
#define BIT_SHIFT_RTC_ALRM_MTH_ISR                   13
#define BIT_RTC_ALRM_MTH_ISR                         ((u32)0x00000001 << 13)                             /*!<R/W 0  Indicate MTH timer value match ALRM_MTH */
#define BIT_SHIFT_RTC_ALRM_DOM_ISR                   12
#define BIT_RTC_ALRM_DOM_ISR                         ((u32)0x00000001 << 12)                             /*!<R/W 0  Indicate DOM timer value match ALRM_DOM */
#define BIT_SHIFT_RTC_ALRM_DOW_ISR                   11
#define BIT_RTC_ALRM_DOW_ISR                         ((u32)0x00000001 << 11)                             /*!<R/W 0  Indicate DOW timer value match ALRM_DOW */
#define BIT_SHIFT_RTC_ALRM_HRS_ISR                   10
#define BIT_RTC_ALRM_HRS_ISR                         ((u32)0x00000001 << 10)                             /*!<R/W 0  Indicate Hour timer value match ALRM_HRS */
#define BIT_SHIFT_RTC_ALRM_MIN_ISR                   9
#define BIT_RTC_ALRM_MIN_ISR                         ((u32)0x00000001 << 9)                              /*!<R/W 0  Indicate Minute timer value match ALRM_MIN */
#define BIT_SHIFT_RTC_ALRM_SEC_ISR                   8
#define BIT_RTC_ALRM_SEC_ISR                         ((u32)0x00000001 << 8)                              /*!<R/W 0  Indicate Second timer value match ALRM_SEC */
#define BIT_SHIFT_RTC_CNT_DOY_ISR                    7
#define BIT_RTC_CNT_DOY_ISR                          ((u32)0x00000001 << 7)                              /*!<R/W 0  Indicate increment of the Day-of-year timer */
#define BIT_SHIFT_RTC_CNT_YRS_ISR                    6
#define BIT_RTC_CNT_YRS_ISR                          ((u32)0x00000001 << 6)                              /*!<R/W 0  Indicate increment of the year timer */
#define BIT_SHIFT_RTC_CNT_MTH_ISR                    5
#define BIT_RTC_CNT_MTH_ISR                          ((u32)0x00000001 << 5)                              /*!<R/W 0  Indicate increment of the month timer */
#define BIT_SHIFT_RTC_CNT_DOM_ISR                    4
#define BIT_RTC_CNT_DOM_ISR                          ((u32)0x00000001 << 4)                              /*!<R/W 0  Indicate increment of the day-of-month timer */
#define BIT_SHIFT_RTC_CNT_DOW_ISR                    3
#define BIT_RTC_CNT_DOW_ISR                          ((u32)0x00000001 << 3)                              /*!<R/W 0  Indicate increment of the day-of-week timer */
#define BIT_SHIFT_RTC_CNT_HRS_ISR                    2
#define BIT_RTC_CNT_HRS_ISR                          ((u32)0x00000001 << 2)                              /*!<R/W 0  Indicate increment of the hour timer */
#define BIT_SHIFT_RTC_CNT_MIN_ISR                    1
#define BIT_RTC_CNT_MIN_ISR                          ((u32)0x00000001 << 1)                              /*!<R/W 0  Indicate increment of the minute timer */
#define BIT_SHIFT_RTC_CNT_SEC_ISR                    0
#define BIT_RTC_CNT_SEC_ISR                          ((u32)0x00000001 << 0)                              /*!<R/W 0  Indicate increment of the second timer */
/** @} */

/**************************************************************************//**
 * @defgroup RTC_TYPE_REG_RTC_TIM0
 * @brief
 * @{
 *****************************************************************************/
#define BIT_SHIFT_RTC_DOW                            24
#define BIT_MASK_RTC_DOW                             ((u32)0x00000007 << 24)                             /*!<R/W 000  Day of week value in the range of 0 to 6 */
#define BIT_SHIFT_RTC_HRS                            16
#define BIT_MASK_RTC_HRS                             ((u32)0x0000001F << 16)                             /*!<R/W 00000  Hours value in the range of 0 to 23 */
#define BIT_SHIFT_RTC_MIN                            8
#define BIT_MASK_RTC_MIN                             ((u32)0x0000003F << 8)                              /*!<R/W 000000  Minutes value in the range of 0 to 59 */
#define BIT_SHIFT_RTC_SEC                            0
#define BIT_MASK_RTC_SEC                             ((u32)0x0000003F << 0)                              /*!<R/W 000000  Seconds value in the range of 0 to 59 */
/** @} */

/**************************************************************************//**
 * @defgroup RTC_TYPE_REG_RTC_TIM1
 * @brief
 * @{
 *****************************************************************************/
#define BIT_SHIFT_RTC_YEAR                           16
#define BIT_MASK_RTC_YEAR                            ((u32)0x00000FFF << 16)                             /*!<R/W 0x000  Year value in the range of 0 to 4095. */
#define BIT_SHIFT_RTC_MON                            8
#define BIT_MASK_RTC_MON                             ((u32)0x0000000F << 8)                              /*!<R/W 1  Month value in the range of 1 to 12 */
#define BIT_SHIFT_RTC_DOM                            0
#define BIT_MASK_RTC_DOM                             ((u32)0x0000001F << 0)                              /*!<R/W 1  Day of month value in the range of 1 to 28, 29, 30, or 31 */
/** @} */

/**************************************************************************//**
 * @defgroup RTC_TYPE_REG_RTC_TIM2
 * @brief
 * @{
 *****************************************************************************/
#define BIT_SHIFT_RTC_M4ISCYR                        16
#define BIT_MASK_RTC_M4ISCYR                              ((u32)0x00000001 << 16)                             /*!<R/W 0  Year is quadruple of four, but it is common year */
#define BIT_SHIFT_RTC_DOY                            0
#define BIT_MASK_RTC_DOY                             ((u32)0x000001FF << 0)                              /*!<R/W 1  Day of year, value in the range of 1 to 365 */
/** @} */

/**************************************************************************//**
 * @defgroup RTC_TYPE_REG_RTC_ALRM_CTRL0
 * @brief
 * @{
 *****************************************************************************/
#define BIT_SHIFT_RTC_ALRM_DOW                       24
#define BIT_MASK_RTC_ALRM_DOW                        ((u32)0x00000007 << 24)                             /*!<R/W 0  Day of week value in the range of 0 to 6 */
#define BIT_SHIFT_RTC_ALRM_HRS                       16
#define BIT_MASK_RTC_ALRM_HRS                        ((u32)0x0000001F << 16)                             /*!<R/W 0  Hours value in the range of 0 to 23 */
#define BIT_SHIFT_RTC_ALRM_MIN                       8
#define BIT_MASK_RTC_ALRM_MIN                        ((u32)0x0000003F << 8)                              /*!<R/W 0  Minutes value in the range of 0 to 59 */
#define BIT_SHIFT_RTC_ALRM_SEC                       0
#define BIT_MASK_RTC_ALRM_SEC                        ((u32)0x0000003F << 0)                              /*!<R/W 0  Seconds value in the range of 0 to 59 */
/** @} */

/**************************************************************************//**
 * @defgroup RTC_TYPE_REG_RTC_ALRM_CTRL1
 * @brief
 * @{
 *****************************************************************************/
#define BIT_SHIFT_RTC_ALRM_YEAR                      16
#define BIT_MASK_RTC_ALRM_YEAR                       ((u32)0x00000FFF << 16)                             /*!<R/W 0  Year value in the range of 0 to 4095. */
#define BIT_SHIFT_RTC_ALRM_MON                       8
#define BIT_MASK_RTC_ALRM_MON                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Month value in the range of 1 to 12 */
#define BIT_SHIFT_RTC_ALRM_DOM                       0
#define BIT_MASK_RTC_ALRM_DOM                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Day of month value in the range of 1 to 28, 29, 30, or 31 */
/** @} */

/**************************************************************************//**
 * @defgroup RTC_TYPE_REG_RTC_ALRM_CTRL2
 * @brief
 * @{
 *****************************************************************************/
#define BIT_SHIFT_RTC_ALRM_DOY_EN                    23
#define BIT_MASK_RTC_ALRM_DOY_EN                          ((u32)0x00000001 << 23)                             /*!<R/W 0  Enable DOY timer value match ALRM_DOY */
#define BIT_SHIFT_RTC_ALRM_YRS_EN                    22
#define BIT_MASK_RTC_ALRM_YRS_EN                          ((u32)0x00000001 << 22)                             /*!<R/W 0  Enable Year timer value match ALRM_YRS */
#define BIT_SHIFT_RTC_ALRM_MTH_EN                    21
#define BIT_MASK_RTC_ALRM_MTH_EN                          ((u32)0x00000001 << 21)                             /*!<R/W 0  Enable MTH timer value match ALRM_MTH */
#define BIT_SHIFT_RTC_ALRM_DOM_EN                    20
#define BIT_MASK_RTC_ALRM_DOM_EN                          ((u32)0x00000001 << 20)                             /*!<R/W 0  Enable DOM timer value match ALRM_DOM */
#define BIT_SHIFT_RTC_ALRM_DOW_EN                    19
#define BIT_MASK_RTC_ALRM_DOW_EN                          ((u32)0x00000001 << 19)                             /*!<R/W 0  Enable DOW timer value match ALRM_DOW */
#define BIT_SHIFT_RTC_ALRM_HRS_EN                    18
#define BIT_MASK_RTC_ALRM_HRS_EN                          ((u32)0x00000001 << 18)                             /*!<R/W 0  Enable Hour timer value match ALRM_HRS */
#define BIT_SHIFT_RTC_ALRM_MIN_EN                    17
#define BIT_MASK_RTC_ALRM_MIN_EN                          ((u32)0x00000001 << 17)                             /*!<R/W 0  Enable Minute timer value match ALRM_MIN */
#define BIT_SHIFT_RTC_ALRM_SEC_EN                    16
#define BIT_MASK_RTC_ALRM_SEC_EN                          ((u32)0x00000001 << 16)                             /*!<R/W 0  Enable Second timer value match ALRM_SEC */
#define BIT_SHIFT_RTC_ALRM_DOY                       0
#define BIT_MASK_RTC_ALRM_DOY                        ((u32)0x000001FF << 0)                              /*!<R/W 0  Day of year, value in the range of 1 to 365 */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_RTC_TYPE
 * @{
 * @brief rtl8735b_RTC_TYPE Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t RTC_TYPE_REG_RTC_FEN ;                   /*!<   register,  Address offset: 0x000 */
	__O  uint32_t RTC_TYPE_REG_DUMMY1 ;                    /*!<   register,  Address offset: 0x004 */
	__IO uint32_t RTC_TYPE_REG_RTC_COMP ;                  /*!<   register,  Address offset: 0x008 */
	__IO uint32_t RTC_TYPE_REG_DUMMY2 ;                    /*!<   register,  Address offset: 0x00C */
	__IO uint32_t RTC_TYPE_REG_RTC_IMR ;                   /*!<   register,  Address offset: 0x010 */
	__IO uint32_t RTC_TYPE_REG_RTC_ISR ;                   /*!<   register,  Address offset: 0x014 */
	__IO uint32_t RTC_TYPE_REG_DUMMY3 ;                    /*!<   register,  Address offset: 0x018 */
	__IO uint32_t RTC_TYPE_REG_DUMMY4 ;                    /*!<   register,  Address offset: 0x01C */
	__IO uint32_t RTC_TYPE_REG_RTC_TIM0 ;                  /*!<   register,  Address offset: 0x020 */
	__IO uint32_t RTC_TYPE_REG_RTC_TIM1 ;                  /*!<   register,  Address offset: 0x024 */
	__IO uint32_t RTC_TYPE_REG_RTC_TIM2 ;                  /*!<   register,  Address offset: 0x028 */
	__IO uint32_t RTC_TYPE_REG_DUMMY5 ;                    /*!<   register,  Address offset: 0x02C */
	__IO uint32_t RTC_TYPE_REG_RTC_ALRM_CTRL0 ;            /*!<   register,  Address offset: 0x030 */
	__IO uint32_t RTC_TYPE_REG_RTC_ALRM_CTRL1 ;            /*!<   register,  Address offset: 0x034 */
	__IO uint32_t RTC_TYPE_REG_RTC_ALRM_CTRL2 ;            /*!<   register,          Address offset: 0x038 */
} RTC_TYPE_TypeDef;
/** @} */

#endif
