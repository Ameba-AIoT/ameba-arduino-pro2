#ifndef _RTL8735B_VNDR_S_TYPE_H_
#define _RTL8735B_VNDR_S_TYPE_H_
#include "platform_conf.h"

/**************************************************************************//**
 * @defgroup VNDR_S_REG_SECURE_WATCH_DOG_TIMER
 * @brief                                            (@ 0X000)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_WDT_TO                          31
#define VNDR_S_BIT_WDT_TO                            ((u32)0x00000001 << 31)                             /*!<R/W1C 0  Watch dog timer timeout. 1 cycle pulse */
#define VNDR_S_SHIFT_WDT_MODE                        30
#define VNDR_S_BIT_WDT_MODE                          ((u32)0x00000001 << 30)                             /*!<R/W 0  1: Reset system, 0: Interrupt CPU */
#define VNDR_S_SHIFT_RSVD1                           29
#define VNDR_S_BIT_RSVD1                             ((u32)0x00000001 << 29)                             /*!<R 0   */
#define VNDR_S_SHIFT_CNT_LIMIT                       25
#define VNDR_S_MASK_CNT_LIMIT                        ((u32)0x0000000F << 25)                             /*!<R/W 0  0: 0x001 1: 0x003 2: 0x007 3: 0x00F 4: 0x01F 5: 0x03F 6: 0x07F 7: 0x0FF 8: 0x1FF 9: 0x3FF 10: 0x7FF 11~15: 0xFFF */
#define VNDR_S_SHIFT_WDT_CLEAR                       24
#define VNDR_S_BIT_WDT_CLEAR                         ((u32)0x00000001 << 24)                             /*!<R/W1P 0  Write 1 to clear timer */
#define VNDR_S_SHIFT_RSVD2                           17
#define VNDR_S_MASK_RSVD2                            ((u32)0x0000007F << 17)                             /*!<R 0   */
#define VNDR_S_SHIFT_WDT_EN_BYTE                     16
#define VNDR_S_BIT_WDT_EN_BYTE                       ((u32)0x00000001 << 16)                             /*!<R/W 0  Set 1 to enable watch dog timer */
#define VNDR_S_SHIFT_VNDR_DIVFACTOR                  0
#define VNDR_S_MASK_VNDR_DIVFACTOR                   ((u32)0x0000FFFF << 0)                              /*!<R/W 1  Dividing factor. Watch dog timer is count with LP 32KHz/(divfactor+1). Minimum dividing factor is 1. */
#define VNDR_S_SHIFT_RSVD3                           0
#define VNDR_S_MASK_RSVD3                            ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_SECURE_LOW_PRI_INT_ISR
 * @brief                                            (@ 0X008)
 * @{
 *****************************************************************************/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define VNDR_S_SHIFT_RSVD4                           1
#define VNDR_S_MASK_RSVD4                            ((u32)0x7FFFFFFF << 1)                              /*!<R 0   */
#define VNDR_S_SHIFT_RXI300_SECURE_BUS_ISR           0
#define VNDR_S_BIT_RXI300_SECURE_BUS_ISR             ((u32)0x00000001 << 0)                              /*!<R/W1C 0   */
#else
#define VNDR_S_SHIFT_RSVD4                           0
#define VNDR_S_MASK_RSVD4                            ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
#endif
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_SECURE_GDMA0_ISR
 * @brief                                            (@ 0X00C)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_RSVD5                           6
#define VNDR_S_MASK_RSVD5                            ((u32)0x03FFFFFF << 6)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA0_CH5_ISR                   5
#define VNDR_S_BIT_GDMA0_CH5_ISR                     ((u32)0x00000001 << 5)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA0_CH4_ISR                   4
#define VNDR_S_BIT_GDMA0_CH4_ISR                     ((u32)0x00000001 << 4)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA0_CH3_ISR                   3
#define VNDR_S_BIT_GDMA0_CH3_ISR                     ((u32)0x00000001 << 3)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA0_CH2_ISR                   2
#define VNDR_S_BIT_GDMA0_CH2_ISR                     ((u32)0x00000001 << 2)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA0_CH1_ISR                   1
#define VNDR_S_BIT_GDMA0_CH1_ISR                     ((u32)0x00000001 << 1)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA0_CH0_ISR                   0
#define VNDR_S_BIT_GDMA0_CH0_ISR                     ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_SECURE_GDMA1_ISR
 * @brief                                            (@ 0X010)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_RSVD6                           6
#define VNDR_S_MASK_RSVD6                            ((u32)0x03FFFFFF << 6)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA1_CH5_ISR                   5
#define VNDR_S_BIT_GDMA1_CH5_ISR                     ((u32)0x00000001 << 5)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA1_CH4_ISR                   4
#define VNDR_S_BIT_GDMA1_CH4_ISR                     ((u32)0x00000001 << 4)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA1_CH3_ISR                   3
#define VNDR_S_BIT_GDMA1_CH3_ISR                     ((u32)0x00000001 << 3)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA1_CH2_ISR                   2
#define VNDR_S_BIT_GDMA1_CH2_ISR                     ((u32)0x00000001 << 2)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA1_CH1_ISR                   1
#define VNDR_S_BIT_GDMA1_CH1_ISR                     ((u32)0x00000001 << 1)                              /*!<R 0   */
#define VNDR_S_SHIFT_GDMA1_CH0_ISR                   0
#define VNDR_S_BIT_GDMA1_CH0_ISR                     ((u32)0x00000001 << 0)                              /*!<R 0   */
#define VNDR_S_SHIFT_RSVD7                           0
#define VNDR_S_MASK_RSVD7                            ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  RSVD */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_OTP_SS_ZONE_COMPARE_CTRL
 * @brief                                            (@ 0X024)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_SS_OTP_CMP_ADDR                 16
#define VNDR_S_MASK_SS_OTP_CMP_ADDR                  ((u32)0x0000FFFF << 16)                             /*!<W 0  PON DFF key compare circuit selected address. Select address of source to be compared. */
#define VNDR_S_SHIFT_SS_OTP_CMP_DATA                 8
#define VNDR_S_MASK_SS_OTP_CMP_DATA                  ((u32)0x000000FF << 8)                              /*!<W 0  PON DFF key compare circuit input data. Compare this data with the selected address data. */
#define VNDR_S_SHIFT_SS_OTP_CMP_EN                   7
#define VNDR_S_BIT_SS_OTP_CMP_EN                     ((u32)0x00000001 << 7)                              /*!<W 0  CMP module wait this signal. Write 1’b1 into this ready bit, to notify CMP module do comparison. CMP module will auto-clear this bit. */
#define VNDR_S_SHIFT_RETRY_MAX_FAIL_LIMIT            4
#define VNDR_S_MASK_RETRY_MAX_FAIL_LIMIT             ((u32)0x00000007 << 4)                              /*!<R/W Once 0x3  When the number of incorrect data entered exceeds the value of this setting "Fail Counter Limiter", lock write operation of this compare circuit, until the platform reset. */
#define VNDR_S_SHIFT_RSVD8                           2
#define VNDR_S_MASK_RSVD8                            ((u32)0x00000003 << 2)                              /*!<R 0  RSVD */
#define VNDR_S_SHIFT_SS_OTP_CMP_STS                  1
#define VNDR_S_BIT_SS_OTP_CMP_STS                    ((u32)0x00000001 << 1)                              /*!<R 0  PON DFF key compare status 1'b1: Data match (Pass) 1'b0: Data mismatch (Fail) (Default) If lock write operation of the compare circuit is enable, then it always return 1'b0 (data mismatch). */
#define VNDR_S_SHIFT_SS_OTP_CMP_SEL                  0
#define VNDR_S_BIT_SS_OTP_CMP_SEL                    ((u32)0x00000001 << 0)                              /*!<R/W 0  PON DFF keys compare circuit select source 1'b0: Select compare source from PON D flip-flops key store (Default)  */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_SECURE_KEY0
 * @brief                                            (@ 0X030)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_SECURE_KEY0           0
#define VNDR_S_MASK_NON_FIXED_SECURE_KEY0            ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  Secure JTAG Key[31:0] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_SECURE_KEY1
 * @brief                                            (@ 0X034)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_SECURE_KEY1           0
#define VNDR_S_MASK_NON_FIXED_SECURE_KEY1            ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  Secure JTAG Key[63:31] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_SECURE_KEY2
 * @brief                                            (@ 0X038)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_SECURE_KEY2           0
#define VNDR_S_MASK_NON_FIXED_SECURE_KEY2            ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  Secure JTAG Key[95:64] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_SECURE_KEY3
 * @brief                                            (@ 0X03C)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_SECURE_KEY3           0
#define VNDR_S_MASK_NON_FIXED_SECURE_KEY3            ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  Secure JTAG Key[127:96] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_SECURE_KEY4
 * @brief                                            (@ 0X040)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_SECURE_KEY4           0
#define VNDR_S_MASK_NON_FIXED_SECURE_KEY4            ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  Secure JTAG Key[159:128] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_SECURE_KEY5
 * @brief                                            (@ 0X044)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_SECURE_KEY5           0
#define VNDR_S_MASK_NON_FIXED_SECURE_KEY5            ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  Secure JTAG Key[191:160] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_SECURE_KEY6
 * @brief                                            (@ 0X048)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_SECURE_KEY6           0
#define VNDR_S_MASK_NON_FIXED_SECURE_KEY6            ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  Secure JTAG Key[223:192] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_SECURE_KEY7
 * @brief                                            (@ 0X04C)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_SECURE_KEY7           0
#define VNDR_S_MASK_NON_FIXED_SECURE_KEY7            ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  Secure JTAG Key[255:224] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_NON_SECURE_KEY0
 * @brief                                            (@ 0X050)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_NON_SECURE_KEY0       0
#define VNDR_S_MASK_NON_FIXED_NON_SECURE_KEY0        ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  NON-Secure JTAG Key[31:0] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_NON_SECURE_KEY1
 * @brief                                            (@ 0X054)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_NON_SECURE_KEY1       0
#define VNDR_S_MASK_NON_FIXED_NON_SECURE_KEY1        ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  NON-Secure JTAG Key[63:31] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_NON_SECURE_KEY2
 * @brief                                            (@ 0X058)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_NON_SECURE_KEY2       0
#define VNDR_S_MASK_NON_FIXED_NON_SECURE_KEY2        ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  NON-Secure JTAG Key[95:64] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_NON_SECURE_KEY3
 * @brief                                            (@ 0X05C)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_NON_SECURE_KEY3       0
#define VNDR_S_MASK_NON_FIXED_NON_SECURE_KEY3        ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  NON-Secure JTAG Key[127:96] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_NON_SECURE_KEY4
 * @brief                                            (@ 0X060)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_NON_SECURE_KEY4       0
#define VNDR_S_MASK_NON_FIXED_NON_SECURE_KEY4        ((u32)0xFFFFFFFF << 0)                              /*!<Wonce 0  NON-Secure JTAG Key[159:128] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_NON_SECURE_KEY5
 * @brief                                            (@ 0X064)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_NON_SECURE_KEY5       0
#define VNDR_S_MASK_NON_FIXED_NON_SECURE_KEY5        ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  NON-Secure JTAG Key[191:160] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_NON_SECURE_KEY6
 * @brief                                            (@ 0X068)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_NON_SECURE_KEY6       0
#define VNDR_S_MASK_NON_FIXED_NON_SECURE_KEY6        ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  NON-Secure JTAG Key[223:192] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_NON_FIXED_NON_SECURE_KEY7
 * @brief                                            (@ 0X06C)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_NON_FIXED_NON_SECURE_KEY7       0
#define VNDR_S_MASK_NON_FIXED_NON_SECURE_KEY7        ((u32)0xFFFFFFFF << 0)                              /*!<WOnce 0  NON-Secure JTAG Key[255:224] This register just can be written once. After that, hardware need disable the writing function. */
/** @} */

/**************************************************************************//**
 * @defgroup VNDR_S_REG_SECURE_JTAG_SWD_CTRL
 * @brief                                            (@ 0X070)
 * @{
 *****************************************************************************/
#define VNDR_S_SHIFT_FW_READY_NONSC                  1
#define VNDR_S_BIT_FW_READY_NONSC                    ((u32)0x00000001 << 1)                              /*!<R/W1 Once 0  In No-Fixed Key Mode and Non-Secure Mode JTAG, Secure JTAG/SWD wait this signal. 0: Secue JTAG/SWD cannot execute the procedure of the unlocking JTAG/SWD. (Default) 1: Secue JTAG/SWD can execute the procedure of the unlocking JTAG/SWD. */
#define VNDR_S_SHIFT_FW_READY_SC                     0
#define VNDR_S_BIT_FW_READY_SC                       ((u32)0x00000001 << 0)                              /*!<R/W1 Once 0  In No-Fixed Key Mode and Secure Mode JTAG, Secure JTAG/SWD wait this signal. 0: Secue JTAG/SWD cannot execute the procedure of the unlocking JTAG/SWD. (Default) 1: Secue JTAG/SWD can execute the procedure of the unlocking JTAG/SWD. */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_VNDR_S
 * @{
 * @brief rtl8735b_VNDR_S Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t VNDR_S_REG_SECURE_WATCH_DOG_TIMER ;      /*!<   register,  Address offset: 0x000 */
	__I  uint32_t VNDR_S_REG_RSVD0 ;                       /*!<   register,  Address offset: 0x004 */
	__I  uint32_t VNDR_S_REG_SECURE_LOW_PRI_INT_ISR ;      /*!<   register,  Address offset: 0x008 */
	__I  uint32_t VNDR_S_REG_SECURE_GDMA0_ISR ;            /*!<   register,  Address offset: 0x00C */
	__I  uint32_t VNDR_S_REG_SECURE_GDMA1_ISR ;            /*!<   register,  Address offset: 0x010 */
	__I  uint32_t VNDR_S_REG_RSVD1 ;                       /*!<   register,  Address offset: 0x014 */
	__I  uint32_t VNDR_S_REG_RSVD2 ;                       /*!<   register,  Address offset: 0x018 */
	__I  uint32_t VNDR_S_REG_RSVD3 ;                       /*!<   register,  Address offset: 0x01C */
	__IO uint32_t VNDR_S_REG_RSVD4 ;                       /*!<   register,  Address offset: 0x020 */
	__IO uint32_t VNDR_S_REG_OTP_SS_ZONE_COMPARE_CTRL ;    /*!<   register,  Address offset: 0x024 */
	__I  uint32_t VNDR_S_REG_RSVD5 ;                       /*!<   register,  Address offset: 0x028 */
	__I  uint32_t VNDR_S_REG_RSVD6 ;                       /*!<   register,  Address offset: 0x02C */
	__O  uint32_t VNDR_S_REG_NON_FIXED_SECURE_KEY0 ;       /*!<   register,  Address offset: 0x030 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_SECURE_KEY1 ;       /*!<   register,  Address offset: 0x034 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_SECURE_KEY2 ;       /*!<   register,  Address offset: 0x038 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_SECURE_KEY3 ;       /*!<   register,  Address offset: 0x03C */
	__O  uint32_t VNDR_S_REG_NON_FIXED_SECURE_KEY4 ;       /*!<   register,  Address offset: 0x040 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_SECURE_KEY5 ;       /*!<   register,  Address offset: 0x044 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_SECURE_KEY6 ;       /*!<   register,  Address offset: 0x048 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_SECURE_KEY7 ;       /*!<   register,  Address offset: 0x04C */
	__O  uint32_t VNDR_S_REG_NON_FIXED_NON_SECURE_KEY0 ;   /*!<   register,  Address offset: 0x050 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_NON_SECURE_KEY1 ;   /*!<   register,  Address offset: 0x054 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_NON_SECURE_KEY2 ;   /*!<   register,  Address offset: 0x058 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_NON_SECURE_KEY3 ;   /*!<   register,  Address offset: 0x05C */
	__O  uint32_t VNDR_S_REG_NON_FIXED_NON_SECURE_KEY4 ;   /*!<   register,  Address offset: 0x060 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_NON_SECURE_KEY5 ;   /*!<   register,  Address offset: 0x064 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_NON_SECURE_KEY6 ;   /*!<   register,  Address offset: 0x068 */
	__O  uint32_t VNDR_S_REG_NON_FIXED_NON_SECURE_KEY7 ;   /*!<   register,  Address offset: 0x06C */
	__IO uint32_t VNDR_S_REG_SECURE_JTAG_SWD_CTRL ;        /*!<   register,          Address offset: 0x070 */
} VNDR_S_TypeDef;
/** @} */

#endif
