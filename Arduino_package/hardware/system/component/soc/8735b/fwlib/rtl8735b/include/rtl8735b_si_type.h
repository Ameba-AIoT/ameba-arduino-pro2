#ifndef _RTL8735B_SI_TYPE_H_
#define _RTL8735B_SI_TYPE_H_

/**************************************************************************//**
 * @defgroup SI_CTRL
 * @brief  SI Control Register                       (@ 0X000)
 * @{
 *****************************************************************************/
#define SI_SHIFT_DATA                                16
#define SI_MASK_DATA                                 ((u32)0x0000FFFF << 16)                             /*!<R/W 0  For si write, the data is written to the codec register. For si read, the data is read out the codec register. */
#define SI_SHIFT_ADDRESS                             8
#define SI_MASK_ADDRESS                              ((u32)0x000000FF << 8)                              /*!<R/W 0  Set the 8 bit address of audio codec. */
#define SI_SHIFT_DISABLE                             7
#define SI_BIT_DISABLE                               ((u32)0x00000001 << 7)                              /*!<R/W 0  0: Si is enabled. 1: Si is disabled. */
#define SI_SHIFT_READ_START                          4
#define SI_BIT_READ_START                            ((u32)0x00000001 << 4)                              /*!<R/W 0  Read value form codec 0: This bit will be cleared when reading is done. 1: Start to perform SI read to audio codec. */
#define SI_SHIFT_WR_START                            0
#define SI_BIT_WR_START                              ((u32)0x00000001 << 0)                              /*!<R/W 0  Write value to codec. 0: This bit will be cleared when wriring is done. 1: Start to perform SI write to audio codec. */
/** @} */

/**************************************************************************//**
 * @defgroup SI_CLK_CTRL
 * @brief  SI Clock Control Register                 (@ 0X004)
 * @{
 *****************************************************************************/
#define SI_SHIFT_REG_DK_EN                           0
#define SI_BIT_REG_DK_EN                             ((u32)0x00000001 << 0)                              /*!<R/W 1  To save power, reset this bit to gate CLK when the registers are already programmed. 0: Turn off the clock. 1: Turn off the clock of the register bank of audio codec. */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_SI
 * @{
 * @brief rtl8735b_SI Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t SI_CTRL ;                                /*!<  SI Control Register register,  Address offset: 0x000 */
	__IO uint32_t SI_CLK_CTRL ;                            /*!<  SI Clock Control Register register,			Address offset: 0x004 */
} SI_TypeDef;
/** @} */

#endif
