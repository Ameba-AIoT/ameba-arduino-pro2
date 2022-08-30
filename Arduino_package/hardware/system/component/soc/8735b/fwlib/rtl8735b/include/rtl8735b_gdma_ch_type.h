#ifndef _RTL8735B_GDMA_CH_TYPE_H_
#define _RTL8735B_GDMA_CH_TYPE_H_

/**************************************************************************//**
 * @defgroup GDMA_CH_SAR
 * @brief  Source Address Register for Channel x     (@ 0X000)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CH_SAR                            0
#define GDMA_MASK_CH_SAR                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CH_DAR
 * @brief  Destination Address Register for Channel x (@ 0X008)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CH_DAR                            0
#define GDMA_MASK_CH_DAR                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CH_LLP
 * @brief  Linked List Pointer Register for Channel x (@ 0X010)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CH_LOC                            2
#define GDMA_MASK_CH_LOC                             ((u32)0x3FFFFFFF << 2)                              /*!<R/W 0   */
#define GDMA_SHIFT_CH_LMS                            0
#define GDMA_MASK_CH_LMS                             ((u32)0x00000003 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CH_CTL_LOW
 * @brief  Lower Word of Control Register for Channel x (@ 0X018)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CH_LLP_SRC_EN                     28
#define GDMA_BIT_CH_LLP_SRC_EN                       ((u32)0x00000001 << 28)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_LLP_DST_EN                     27
#define GDMA_BIT_CH_LLP_DST_EN                       ((u32)0x00000001 << 27)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_TT_FC                          20
#define GDMA_MASK_CH_TT_FC                           ((u32)0x00000007 << 20)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_SRC_MSIZE                      14
#define GDMA_MASK_CH_SRC_MSIZE                       ((u32)0x00000007 << 14)                             /*!<R/W 1   */
#define GDMA_SHIFT_CH_DEST_MSIZE                     11
#define GDMA_MASK_CH_DEST_MSIZE                      ((u32)0x00000007 << 11)                             /*!<R/W 1   */
#define GDMA_SHIFT_CH_SINC                           9
#define GDMA_MASK_CH_SINC                            ((u32)0x00000003 << 9)                              /*!<R/W 0   */
#define GDMA_SHIFT_CH_DINC                           7
#define GDMA_MASK_CH_DINC                            ((u32)0x00000003 << 7)                              /*!<R/W 0   */
#define GDMA_SHIFT_CH_SRC_TR_WIDTH                   4
#define GDMA_MASK_CH_SRC_TR_WIDTH                    ((u32)0x00000007 << 4)                              /*!<R/W 0   */
#define GDMA_SHIFT_CH_DST_TR_WIDTH                   1
#define GDMA_MASK_CH_DST_TR_WIDTH                    ((u32)0x00000007 << 1)                              /*!<R/W 0   */
#define GDMA_SHIFT_CH_INT_EN                         0
#define GDMA_BIT_CH_INT_EN                           ((u32)0x00000001 << 0)                              /*!<R/W 1   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CH_CTL_UP
 * @brief  Upper Word of Control Register for Channel x (@ 0X01C)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CH_BLOCK_TS                       0
#define GDMA_MASK_CH_BLOCK_TS                        ((u32)0x00000FFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CH_CFG_LOW
 * @brief  Lower Word of Configuration Register for Channel x (@ 0X040)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CH_RELOAD_DST                     31
#define GDMA_BIT_CH_RELOAD_DST                       ((u32)0x00000001 << 31)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_RELOAD_SRC                     30
#define GDMA_BIT_CH_RELOAD_SRC                       ((u32)0x00000001 << 30)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_MAX_ABRST                      20
#define GDMA_MASK_CH_MAX_ABRST                       ((u32)0x000003FF << 20)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_SRC_HS_POL                     19
#define GDMA_BIT_CH_SRC_HS_POL                       ((u32)0x00000001 << 19)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_DST_HS_POL                     18
#define GDMA_BIT_CH_DST_HS_POL                       ((u32)0x00000001 << 18)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_FIFO_EMPTY                     9
#define GDMA_BIT_CH_FIFO_EMPTY                       ((u32)0x00000001 << 9)                              /*!<R 1   */
#define GDMA_SHIFT_CH_CH_SUSP                        8
#define GDMA_BIT_CH_CH_SUSP                          ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define GDMA_SHIFT_CH_INACTIVE                       0
#define GDMA_BIT_CH_INACTIVE                         ((u32)0x00000001 << 0)                              /*!<R/W 1   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CH_CFG_UP
 * @brief  Upper Word of Configuration Register for Channel x (@ 0X044)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CH_EXTENDED_DEST_PER              16
#define GDMA_BIT_CH_EXTENDED_DEST_PER                ((u32)0x00000001 << 16)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_EXTENDED_SRC_PER               15
#define GDMA_BIT_CH_EXTENDED_SRC_PER                 ((u32)0x00000001 << 15)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_DEST_PER                       11
#define GDMA_MASK_CH_DEST_PER                        ((u32)0x0000000F << 11)                             /*!<R/W 0   */
#define GDMA_SHIFT_CH_SRC_PER                        7
#define GDMA_MASK_CH_SRC_PER                         ((u32)0x0000000F << 7)                              /*!<R/W 0   */
#define GDMA_SHIFT_CH_SECURE_EN                      3
#define GDMA_BIT_CH_SECURE_EN                        ((u32)0x00000001 << 3)                              /*!<R/W 1   */
#define GDMA_SHIFT_CH_FIFO_MODE                      1
#define GDMA_BIT_CH_FIFO_MODE                        ((u32)0x00000001 << 1)                              /*!<R/W 1   */
#define GDMA_SHIFT_CH_FCMODE                         0
#define GDMA_BIT_CH_FCMODE                           ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_GDMA_CH
 * @{
 * @brief rtl8735b_GDMA_CH Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t GDMA_CH_SAR ;                            /*!<  Source Address Register for Channel x register,  Address offset: 0x000 */
	__IO uint32_t RSVD0;                                  /*!<  Reserved,  Address offset:0x4 */
	__IO uint32_t GDMA_CH_DAR ;                            /*!<  Destination Address Register for Channel x register,  Address offset: 0x008 */
	__IO uint32_t RSVD1;                                  /*!<  Reserved,  Address offset:0xC */
	__IO uint32_t GDMA_CH_LLP ;                            /*!<  Linked List Pointer Register for Channel x register,  Address offset: 0x010 */
	__IO uint32_t RSVD2;                                  /*!<  Reserved,  Address offset:0x14 */
	__IO uint32_t GDMA_CH_CTL_LOW ;                        /*!<  Lower Word of Control Register for Channel x register,  Address offset: 0x018 */
	__IO uint32_t GDMA_CH_CTL_UP ;                         /*!<  Upper Word of Control Register for Channel x register,  Address offset: 0x01C */
	__IO uint32_t RSVD3[8];                                /*!<  Reserved,  Address offset:0x20-0x3C */
	__IO uint32_t GDMA_CH_CFG_LOW ;                        /*!<  Lower Word of Configuration Register for Channel x register,  Address offset: 0x040 */
	__IO uint32_t GDMA_CH_CFG_UP ;                         /*!<  Upper Word of Configuration Register for Channel x register,            Address offset: 0x044 */
} GDMA_CH_TypeDef;
/** @} */

#endif
