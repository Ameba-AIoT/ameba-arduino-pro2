#ifndef _RTL8735B_TG_TYPE_H_
#define _RTL8735B_TG_TYPE_H_

/**************************************************************************//**
 * @defgroup TG_ISTS
 * @brief  Timer Group interrupt status register     (@ 0X000)
 * @{
 *****************************************************************************/
#define TG_SHIFT_ISTS                                0
#define TG_MASK_ISTS                                 ((u32)0x000000FF << 0)                              /*!<R 0  Each bit indicates the interrupt pending status of corresponding timer: 0: the specifiied timer has no interrupt pending 1: the specifiied timer has pending interrupt */
/** @} */

/**************************************************************************//**
 * @defgroup TG_RAW_ISTS
 * @brief  Timer Group raw interrupt status register (@ 0X004)
 * @{
 *****************************************************************************/
#define TG_SHIFT_RISTS                               0
#define TG_MASK_RISTS                                ((u32)0x000000FF << 0)                              /*!<R 0  Each bit indicates the interrupt pending status of corresponding timer: 0: the specifiied timer has no interrupt pending 1: the specifiied timer has pending interrupt (pre-masing) */
/** @} */

/**************************************************************************//**
 * @defgroup TG_TSEL
 * @brief  Timer Group indirect read control register (@ 0X008)
 * @{
 *****************************************************************************/
#define TG_SHIFT_POLL                                7
#define TG_BIT_POLL                                  ((u32)0x00000001 << 7)                              /*!<R/W 0  Set this bit to enable indirect read current value of timer selected by tsel. This bit is cleared by HW while finishing read and indicate REG_TIMER_TC is ready */
#define TG_SHIFT_SYNC_MODE                           4
#define TG_BIT_SYNC_MODE                             ((u32)0x00000001 << 4)                              /*!<R/W 0  Sync mode between Timer clock and APB clock 0: Freq. of APB clock >> Freq. of Timer clock (about 10 times) 1: others */
#define TG_SHIFT_TSEL                                0
#define TG_MASK_TSEL                                 ((u32)0x00000007 << 0)                              /*!<R/W 0  The timer index in a timer group, to select the timer for indirect read. */
/** @} */

/**************************************************************************//**
 * @defgroup TG_TC
 * @brief  Timer Group indirect read timer counter register (@ 0X00C)
 * @{
 *****************************************************************************/
#define TG_SHIFT_TIMER_TC                            0
#define TG_MASK_TIMER_TC                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  Current counter value of the specifiied timer by register tg_tsel. */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_TG
 * @{
 * @brief rtl8735b_TG Register Declaration
 *****************************************************************************/
typedef struct {
	__I  uint32_t TG_ISTS ;                                /*!<  Timer Group interrupt status register,  Address offset: 0x000 */
	__I  uint32_t TG_RAW_ISTS ;                            /*!<  Timer Group raw interrupt status register,  Address offset: 0x004 */
	__IO uint32_t TG_TSEL ;                                /*!<  Timer Group indirect read control register,  Address offset: 0x008 */
	__I  uint32_t TG_TC ;                                  /*!<  Timer Group indirect read timer counter register,           Address offset: 0x00C */
} TG_TypeDef;
/** @} */

#endif
