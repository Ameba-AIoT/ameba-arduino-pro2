#ifndef _RTL8735B_RSA_TYPE_H_
#define _RTL8735B_RSA_TYPE_H_

/**************************************************************************//**
 * @defgroup RSA_MODE_CONTROL_FIELD
 * @brief  Mode Control                              (@ 0XF00)
 * @{
 *****************************************************************************/
#define RSA_SHIFT_KEY_SIZE_SEL                       29
#define RSA_MASK_KEY_SIZE_SEL                        ((u32)0x00000007 << 29)                             /*!<R/W 0  0x0: 2048, 0x2: 1024, 0x5: 3072 */
#define RSA_SHIFT_BYTE_SWAP                          28
#define RSA_BIT_BYTE_SWAP                            ((u32)0x00000001 << 28)                             /*!<R/W 0  Byte swapping in a word, 0x0: little, 0x1: big */
#define RSA_SHIFT_ENDIAN                             27
#define RSA_BIT_ENDIAN                               ((u32)0x00000001 << 27)                             /*!<R/W 0  0x0: little, 0x1: big */
/** @} */

/**************************************************************************//**
 * @defgroup RSA_START_AND_INTERRUPT_CONTROL_FIELD
 * @brief  Start_and_interrupt_control               (@ 0XF08)
 * @{
 *****************************************************************************/
#define RSA_SHIFT_INTERRUPT_STATUS_CLEAR             31
#define RSA_BIT_INTERRUPT_STATUS_CLEAR               ((u32)0x00000001 << 31)                             /*!<R/W 0  0x0: no interrupt, 0x1: interrupt active, Write 1 to clear interrupt */
#define RSA_SHIFT_INTERRUPT_ENABLE                   30
#define RSA_BIT_INTERRUPT_ENABLE                     ((u32)0x00000001 << 30)                             /*!<R/W 0  Enable interrupt */
#define RSA_SHIFT_GO                                 0
#define RSA_BIT_GO                                   ((u32)0x00000001 << 0)                              /*!<R/W 0  Write 1 to start engine */
/** @} */

/**************************************************************************//**
 * @defgroup RSA_STATUS_FIELD
 * @brief  Status                                    (@ 0XF0C)
 * @{
 *****************************************************************************/
#define RSA_SHIFT_FINISH                             27
#define RSA_BIT_FINISH                               ((u32)0x00000001 << 27)                             /*!<R 0  RSA finish */
#define RSA_SHIFT_EXP_ERROR                          25
#define RSA_BIT_EXP_ERROR                            ((u32)0x00000001 << 25)                             /*!<R 0  Exponent error (e.g. all zero) */
#define RSA_SHIFT_M_RANGE_ERROR                      24
#define RSA_BIT_M_RANGE_ERROR                        ((u32)0x00000001 << 24)                             /*!<R 0  M > N error */
#define RSA_SHIFT_NPINV_ERROR                        19
#define RSA_BIT_NPINV_ERROR                          ((u32)0x00000001 << 19)                             /*!<R 0  NPINV generate error */
/** @} */

/**************************************************************************//**
 * @defgroup RSA_CLOCK_GATING_CONTROL_FIELD
 * @brief  Clock_gating_control                      (@ 0XF2C)
 * @{
 *****************************************************************************/
#define RSA_SHIFT_CLOCK_GETTING_ENABLE               31
#define RSA_BIT_CLOCK_GETTING_ENABLE                 ((u32)0x00000001 << 31)                             /*!<R/W 0  Enable auto clock gating */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_RSA
 * @{
 * @brief rtl8735b_RSA Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t RSA_MODE_CONTROL_FIELD ;                 /*!<  Mode Control register,  Address offset: 0xF00 */
	__IO uint32_t RSA_RSVD1 ;                              /*!<  rsvd1 register,  Address offset: 0xF04 */
	__IO uint32_t RSA_START_AND_INTERRUPT_CONTROL_FIELD ;  /*!<  Start_and_interrupt_control register,  Address offset: 0xF08 */
	__I  uint32_t RSA_STATUS_FIELD ;                       /*!<  Status register,  Address offset: 0xF0C */
	__IO uint32_t RSA_RSVD2_1 ;                            /*!<  rsvd2_1 register,  Address offset: 0xF10 */
	__IO uint32_t RSA_RSVD2_2 ;                            /*!<  rsvd2_2 register,  Address offset: 0xF14 */
	__IO uint32_t RSA_RSVD2_3 ;                            /*!<  rsvd2_3 register,  Address offset: 0xF18 */
	__IO uint32_t RSA_RSVD2_4 ;                            /*!<  rsvd2_4 register,  Address offset: 0xF1C */
	__IO uint32_t RSA_RSVD2_5 ;                            /*!<  rsvd2_5 register,  Address offset: 0xF20 */
	__IO uint32_t RSA_RSVD2_6 ;                            /*!<  rsvd2_6 register,  Address offset: 0xF24 */
	__IO uint32_t RSA_RSVD2_7 ;                            /*!<  rsvd2_7 register,  Address offset: 0xF28 */
	__IO uint32_t RSA_CLOCK_GATING_CONTROL_FIELD ;         /*!<  Clock_gating_control register,          Address offset: 0xF2C */
} RSA_TypeDef;
/** @} */

#endif
