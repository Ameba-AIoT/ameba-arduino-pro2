#ifndef _RTL8735B_GDMA_TYPE_H_
#define _RTL8735B_GDMA_TYPE_H_

/**************************************************************************//**
 * @defgroup GDMA_RAW_TFR
 * @brief  IntTfr Raw Interrupt Status Register      (@ 0X000)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_RAW_TFR                           0
#define GDMA_MASK_RAW_TFR                            ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_RAW_BLOCK
 * @brief  IntBlock Raw Interrupt Status Register    (@ 0X008)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_RAW_BLOCK                         0
#define GDMA_MASK_RAW_BLOCK                          ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_RAW_SRC_TRAN
 * @brief  IntSrcTran Raw Interrupt Status Register  (@ 0X010)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_RAW_SRC_TRAN                      0
#define GDMA_MASK_RAW_SRC_TRAN                       ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_RAW_DST_TRAN
 * @brief  IntDstTran Raw Interrupt Status Register  (@ 0X018)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_RAW_DST_TRAN                      0
#define GDMA_MASK_RAW_DST_TRAN                       ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_RAW_ERR_LOW
 * @brief  IntErr Raw Interrupt Status Low Register  (@ 0X020)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_RAW_ERR                           0
#define GDMA_MASK_RAW_ERR                            ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_RAW_ERR_UP
 * @brief  IntErr Raw Interrupt Status Up Register   (@ 0X024)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_RAW_SECURE_ERROR                  0
#define GDMA_MASK_RAW_SECURE_ERROR                   ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_STATUS_TFR
 * @brief  IntTfr Interrupt Status Register          (@ 0X028)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_STATUS_TFR                        0
#define GDMA_MASK_STATUS_TFR                         ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_STATUS_BLOCK
 * @brief  IntBlock Interrupt Status Register        (@ 0X030)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_STATUS_BLOCK                      0
#define GDMA_MASK_STATUS_BLOCK                       ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_STATUS_SRC_TRAN
 * @brief  IntSrcTran Interrupt Status Register      (@ 0X038)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_STATUS_SRC_TRAN                   0
#define GDMA_MASK_STATUS_SRC_TRAN                    ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_STATUS_DST_TRAN
 * @brief  IntDstTran Interrupt Status Register      (@ 0X040)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_STATUS_DST_TRAN                   0
#define GDMA_MASK_STATUS_DST_TRAN                    ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_STATUS_ERR_LOW
 * @brief  IntErr Interrupt Status Low Register      (@ 0X048)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_STATUS_ERR                        0
#define GDMA_MASK_STATUS_ERR                         ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_STATUS_ERR_UP
 * @brief  IntErr Interrupt Status Up Register       (@ 0X04C)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_STATUS_SECURE_ERROR               0
#define GDMA_MASK_STATUS_SECURE_ERROR                ((u32)0x0000003F << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_MASK_TFR
 * @brief  IntTfr Interrupt Mask Register            (@ 0X050)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_MASK_TFR_WE                       8
#define GDMA_MASK_MASK_TFR_WE                        ((u32)0x0000003F << 8)                              /*!<W 0   */
#define GDMA_SHIFT_MASK_TFR                          0
#define GDMA_MASK_MASK_TFR                           ((u32)0x0000003F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_MASK_BLOCK
 * @brief  IntBlock Interrupt Mask Register          (@ 0X058)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_MASK_BLOCK_WE                     8
#define GDMA_MASK_MASK_BLOCK_WE                      ((u32)0x0000003F << 8)                              /*!<W 0   */
#define GDMA_SHIFT_MASK_BLOCK                        0
#define GDMA_MASK_MASK_BLOCK                         ((u32)0x0000003F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_MASK_SRC_TRAN
 * @brief  IntSrcTran Interrupt Mask Register        (@ 0X060)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_MASK_SRC_TRAN_WE                  8
#define GDMA_MASK_MASK_SRC_TRAN_WE                   ((u32)0x0000003F << 8)                              /*!<W 0   */
#define GDMA_SHIFT_MASK_SRC_TRAN                     0
#define GDMA_MASK_MASK_SRC_TRAN                      ((u32)0x0000003F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_MASK_DST_TRAN
 * @brief  IntDstTran Interrupt Mask Register        (@ 0X068)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_MASK_DST_TRAN_WE                  8
#define GDMA_MASK_MASK_DST_TRAN_WE                   ((u32)0x0000003F << 8)                              /*!<W 0   */
#define GDMA_SHIFT_MASK_DST_TRAN                     0
#define GDMA_MASK_MASK_DST_TRAN                      ((u32)0x0000003F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_MASK_ERR_LOW
 * @brief  IntErr Interrupt Mask Low Register        (@ 0X070)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_MASK_ERR_WE                       8
#define GDMA_MASK_MASK_ERR_WE                        ((u32)0x0000003F << 8)                              /*!<W 0   */
#define GDMA_SHIFT_MASK_ERR                          0
#define GDMA_MASK_MASK_ERR                           ((u32)0x0000003F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_MASK_ERR_UP
 * @brief  IntErr Interrupt Mask Up Register         (@ 0X074)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_MASK_SECURE_ERROR_WE              8
#define GDMA_MASK_MASK_SECURE_ERROR_WE               ((u32)0x0000003F << 8)                              /*!<W 0   */
#define GDMA_SHIFT_MASK_SECURE_ERROR                 0
#define GDMA_MASK_MASK_SECURE_ERROR                  ((u32)0x0000003F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CLEAR_TFR
 * @brief  IntTfr Interrupt Clear Register           (@ 0X078)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_STATUS_TFR                        0
#define GDMA_MASK_STATUS_TFR                         ((u32)0x0000003F << 0)                              /*!<R/W1C 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CLEAR_BLOCK
 * @brief  IntBlock Interrupt Clear Register         (@ 0X080)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CLEAR_BLOCK                       0
#define GDMA_MASK_CLEAR_BLOCK                        ((u32)0x0000003F << 0)                              /*!<R/W1C 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CLEAR_SRC_TRAN
 * @brief  IntSrcTran Interrupt Clear Register       (@ 0X088)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CLEAR_SRC_TRAN                    0
#define GDMA_MASK_CLEAR_SRC_TRAN                     ((u32)0x0000003F << 0)                              /*!<R/W1C 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CLEAR_DST_TRAN
 * @brief  IntDstTran Interrupt Clear Register       (@ 0X090)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CLEAR_DST_TRAN                    0
#define GDMA_MASK_CLEAR_DST_TRAN                     ((u32)0x0000003F << 0)                              /*!<R/W1C 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CLEAR_ERR_LOW
 * @brief  IntErr Interrupt Clear Low Register       (@ 0X098)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CLEAR_ERR                         0
#define GDMA_MASK_CLEAR_ERR                          ((u32)0x0000003F << 0)                              /*!<R/W1C 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CLEAR_ERR_UP
 * @brief  IntErr Interrupt Clear Up Register        (@ 0X09C)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CLEAR_SECURE_ERROR                0
#define GDMA_MASK_CLEAR_SECURE_ERROR                 ((u32)0x0000003F << 0)                              /*!<R/W1C 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_STATUS_INT
 * @brief  Combined Interrupt Status Register        (@ 0X0A0)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_ERR                               4
#define GDMA_BIT_ERR                                 ((u32)0x00000001 << 4)                              /*!<R 0   */
#define GDMA_SHIFT_DSTT                              3
#define GDMA_BIT_DSTT                                ((u32)0x00000001 << 3)                              /*!<R 0   */
#define GDMA_SHIFT_SRCT                              2
#define GDMA_BIT_SRCT                                ((u32)0x00000001 << 2)                              /*!<R 0   */
#define GDMA_SHIFT_BLOCK                             1
#define GDMA_BIT_BLOCK                               ((u32)0x00000001 << 1)                              /*!<R 0   */
#define GDMA_SHIFT_TFR                               0
#define GDMA_BIT_TFR                                 ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_DMA_CFG_REG
 * @brief  Configuration Register                    (@ 0X0D8)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_DMA_EN                            0
#define GDMA_BIT_DMA_EN                              ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CH_EN_REG
 * @brief  Channel Enable Register                   (@ 0X0E0)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CH_EN_WE                          8
#define GDMA_MASK_CH_EN_WE                           ((u32)0x0000003F << 8)                              /*!<W 0   */
#define GDMA_SHIFT_CH_EN                             0
#define GDMA_MASK_CH_EN                              ((u32)0x0000003F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup GDMA_CH_RESET_REG
 * @brief  Channel Reset Register                    (@ 0X0F8)
 * @{
 *****************************************************************************/
#define GDMA_SHIFT_CH_RESET_EN_WE                    8
#define GDMA_MASK_CH_RESET_EN_WE                     ((u32)0x0000003F << 8)                              /*!<R 0   */
#define GDMA_SHIFT_CH_RESET_EN                       0
#define GDMA_MASK_CH_RESET_EN                        ((u32)0x0000003F << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_GDMA
 * @{
 * @brief rtl8735b_GDMA Register Declaration
 *****************************************************************************/
typedef struct {
	__I  uint32_t GDMA_RAW_TFR ;                           /*!<  IntTfr Raw Interrupt Status Register register,  Address offset: 0x000 */
	__IO uint32_t RSVD0;                                  /*!<  Reserved,  Address offset:0x4 */
	__I  uint32_t GDMA_RAW_BLOCK ;                         /*!<  IntBlock Raw Interrupt Status Register register,  Address offset: 0x008 */
	__IO uint32_t RSVD1;                                  /*!<  Reserved,  Address offset:0xC */
	__I  uint32_t GDMA_RAW_SRC_TRAN ;                      /*!<  IntSrcTran Raw Interrupt Status Register register,  Address offset: 0x010 */
	__IO uint32_t RSVD2;                                  /*!<  Reserved,  Address offset:0x14 */
	__I  uint32_t GDMA_RAW_DST_TRAN ;                      /*!<  IntDstTran Raw Interrupt Status Register register,  Address offset: 0x018 */
	__IO uint32_t RSVD3;                                  /*!<  Reserved,  Address offset:0x1C */
	__I  uint32_t GDMA_RAW_ERR_LOW ;                       /*!<  IntErr Raw Interrupt Status Low Register register,  Address offset: 0x020 */
	__I  uint32_t GDMA_RAW_ERR_UP ;                        /*!<  IntErr Raw Interrupt Status Up Register register,  Address offset: 0x024 */
	__I  uint32_t GDMA_STATUS_TFR ;                        /*!<  IntTfr Interrupt Status Register register,  Address offset: 0x028 */
	__IO uint32_t RSVD4;                                  /*!<  Reserved,  Address offset:0x2C */
	__I  uint32_t GDMA_STATUS_BLOCK ;                      /*!<  IntBlock Interrupt Status Register register,  Address offset: 0x030 */
	__IO uint32_t RSVD5;                                  /*!<  Reserved,  Address offset:0x34 */
	__I  uint32_t GDMA_STATUS_SRC_TRAN ;                   /*!<  IntSrcTran Interrupt Status Register register,  Address offset: 0x038 */
	__IO uint32_t RSVD6;                                  /*!<  Reserved,  Address offset:0x3C */
	__I  uint32_t GDMA_STATUS_DST_TRAN ;                   /*!<  IntDstTran Interrupt Status Register register,  Address offset: 0x040 */
	__IO uint32_t RSVD7;                                  /*!<  Reserved,  Address offset:0x44 */
	__I  uint32_t GDMA_STATUS_ERR_LOW ;                    /*!<  IntErr Interrupt Status Low Register register,  Address offset: 0x048 */
	__I  uint32_t GDMA_STATUS_ERR_UP ;                     /*!<  IntErr Interrupt Status Up Register register,  Address offset: 0x04C */
	__IO uint32_t GDMA_MASK_TFR ;                          /*!<  IntTfr Interrupt Mask Register register,  Address offset: 0x050 */
	__IO uint32_t RSVD8;                                  /*!<  Reserved,  Address offset:0x54 */
	__IO uint32_t GDMA_MASK_BLOCK ;                        /*!<  IntBlock Interrupt Mask Register register,  Address offset: 0x058 */
	__IO uint32_t RSVD9;                                  /*!<  Reserved,  Address offset:0x5C */
	__IO uint32_t GDMA_MASK_SRC_TRAN ;                     /*!<  IntSrcTran Interrupt Mask Register register,  Address offset: 0x060 */
	__IO uint32_t RSVD10;                                 /*!<  Reserved,  Address offset:0x64 */
	__IO uint32_t GDMA_MASK_DST_TRAN ;                     /*!<  IntDstTran Interrupt Mask Register register,  Address offset: 0x068 */
	__IO uint32_t RSVD11;                                 /*!<  Reserved,  Address offset:0x6C */
	__IO uint32_t GDMA_MASK_ERR_LOW ;                      /*!<  IntErr Interrupt Mask Low Register register,  Address offset: 0x070 */
	__IO uint32_t GDMA_MASK_ERR_UP ;                       /*!<  IntErr Interrupt Mask Up Register register,  Address offset: 0x074 */
	__IO uint32_t GDMA_CLEAR_TFR ;                         /*!<  IntTfr Interrupt Clear Register register,  Address offset: 0x078 */
	__IO uint32_t RSVD12;                                 /*!<  Reserved,  Address offset:0x7C */
	__IO uint32_t GDMA_CLEAR_BLOCK ;                       /*!<  IntBlock Interrupt Clear Register register,  Address offset: 0x080 */
	__IO uint32_t RSVD13;                                 /*!<  Reserved,  Address offset:0x84 */
	__IO uint32_t GDMA_CLEAR_SRC_TRAN ;                    /*!<  IntSrcTran Interrupt Clear Register register,  Address offset: 0x088 */
	__IO uint32_t RSVD14;                                 /*!<  Reserved,  Address offset:0x8C */
	__IO uint32_t GDMA_CLEAR_DST_TRAN ;                    /*!<  IntDstTran Interrupt Clear Register register,  Address offset: 0x090 */
	__IO uint32_t RSVD15;                                 /*!<  Reserved,  Address offset:0x94 */
	__IO uint32_t GDMA_CLEAR_ERR_LOW ;                     /*!<  IntErr Interrupt Clear Low Register register,  Address offset: 0x098 */
	__IO uint32_t GDMA_CLEAR_ERR_UP ;                      /*!<  IntErr Interrupt Clear Up Register register,  Address offset: 0x09C */
	__I  uint32_t GDMA_STATUS_INT ;                        /*!<  Combined Interrupt Status Register register,  Address offset: 0x0A0 */
	__IO uint32_t RSVD16[13];                              /*!<  Reserved,  Address offset:0xA4-0xD4 */
	__IO uint32_t GDMA_DMA_CFG_REG ;                       /*!<  Configuration Register register,  Address offset: 0x0D8 */
	__IO uint32_t RSVD17;                                 /*!<  Reserved,  Address offset:0xDC */
	__IO uint32_t GDMA_CH_EN_REG ;                         /*!<  Channel Enable Register register,  Address offset: 0x0E0 */
	__IO uint32_t RSVD18[5];                               /*!<  Reserved,  Address offset:0xE4-0xF4 */
	__IO uint32_t GDMA_CH_RESET_REG ;                      /*!<  Channel Reset Register register,            Address offset: 0x0F8 */
} GDMA_TypeDef;
/** @} */

#endif
