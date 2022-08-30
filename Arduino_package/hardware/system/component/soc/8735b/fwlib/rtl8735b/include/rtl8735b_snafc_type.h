#ifndef _RTL8735B_SNAFC_TYPE_H_
#define _RTL8735B_SNAFC_TYPE_H_

/**************************************************************************//**
 * @defgroup SNAFC_CFR
 * @brief  SPI NAND Flash Configuration Register (SNAFCFR) (@ 0X000)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_DMYRD                            31
#define SNAFC_BIT_DMYRD                              ((u32)0x00000001 << 31)                             /*!<R/W 0   */
#define SNAFC_SHIFT_NAFC_NF                          28
#define SNAFC_BIT_NAFC_NF                            ((u32)0x00000001 << 28)                             /*!<R 0   */
#define SNAFC_SHIFT_DEBUG_SELECT                     24
#define SNAFC_MASK_DEBUG_SELECT                      ((u32)0x00000007 << 24)                             /*!<R/W 0   */
#define SNAFC_SHIFT_RBO                              22
#define SNAFC_BIT_RBO                                ((u32)0x00000001 << 22)                             /*!<R/W 0   */
#define SNAFC_SHIFT_WBO                              21
#define SNAFC_BIT_WBO                                ((u32)0x00000001 << 21)                             /*!<R/W 0   */
#define SNAFC_SHIFT_DMA_IE                           20
#define SNAFC_BIT_DMA_IE                             ((u32)0x00000001 << 20)                             /*!<R/W 0   */
#define SNAFC_SHIFT_SLV_ENDIAN                       14
#define SNAFC_BIT_SLV_ENDIAN                         ((u32)0x00000001 << 14)                             /*!<R/W 0   */
#define SNAFC_SHIFT_DMA_ENDIAN                       13
#define SNAFC_BIT_DMA_ENDIAN                         ((u32)0x00000001 << 13)                             /*!<R/W 0   */
#define SNAFC_SHIFT_PRECISE                          12
#define SNAFC_BIT_PRECISE                            ((u32)0x00000001 << 12)                             /*!<R/W 0x1   */
#define SNAFC_SHIFT_PIPE_LAT                         8
#define SNAFC_MASK_PIPE_LAT                          ((u32)0x00000003 << 8)                              /*!<R/W 0   */
#define SNAFC_SHIFT_SPI_CLK_DIV                      4
#define SNAFC_MASK_SPI_CLK_DIV                       ((u32)0x00000007 << 4)                              /*!<R/W 0x7   */
#define SNAFC_SHIFT_LBC_BSZ                          0
#define SNAFC_MASK_LBC_BSZ                           ((u32)0x00000003 << 0)                              /*!<R/W 0x3   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_CCR
 * @brief  SPI NAND Flash CS Control Register (SNAFCCR) (@ 0X004)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_CECS                             0
#define SNAFC_BIT_CECS                               ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_WCMR
 * @brief  SPI NAND Flash Write Command Register (SNAFWCMR) (@ 0X008)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_W_IO_WIDTH                       28
#define SNAFC_MASK_W_IO_WIDTH                        ((u32)0x00000003 << 28)                             /*!<R/W 0   */
#define SNAFC_SHIFT_W_LEN                            0
#define SNAFC_MASK_W_LEN                             ((u32)0x00000003 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_RCMR
 * @brief  SPI NAND Flash Read Command Register (SNAFRCMR) (@ 0X00C)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_R_IO_WIDTH                       28
#define SNAFC_MASK_R_IO_WIDTH                        ((u32)0x00000003 << 28)                             /*!<R/W 0   */
#define SNAFC_SHIFT_R_LEN                            0
#define SNAFC_MASK_R_LEN                             ((u32)0x00000003 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_RDR
 * @brief  SPI NAND Flash Read Data Register (SNAFRDR) (@ 0X010)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_RDATA3                           24
#define SNAFC_MASK_RDATA3                            ((u32)0x000000FF << 24)                             /*!<R 0   */
#define SNAFC_SHIFT_RDATA2                           16
#define SNAFC_MASK_RDATA2                            ((u32)0x000000FF << 16)                             /*!<R 0   */
#define SNAFC_SHIFT_RDATA1                           8
#define SNAFC_MASK_RDATA1                            ((u32)0x000000FF << 8)                              /*!<R 0   */
#define SNAFC_SHIFT_RDATA0                           0
#define SNAFC_MASK_RDATA0                            ((u32)0x000000FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_WDR
 * @brief  SPI NAND Flash Write Data Register (SNAFWDR) (@ 0X014)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_WDATA3                           24
#define SNAFC_MASK_WDATA3                            ((u32)0x000000FF << 24)                             /*!<W 0   */
#define SNAFC_SHIFT_WDATA2                           16
#define SNAFC_MASK_WDATA2                            ((u32)0x000000FF << 16)                             /*!<W 0   */
#define SNAFC_SHIFT_WDATA1                           8
#define SNAFC_MASK_WDATA1                            ((u32)0x000000FF << 8)                              /*!<W 0   */
#define SNAFC_SHIFT_WDATA0                           0
#define SNAFC_MASK_WDATA0                            ((u32)0x000000FF << 0)                              /*!<W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_DTR
 * @brief  SPI NAND Flash DMA Trigger Register (SNAFDTR) (@ 0X018)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_DMARWE                           0
#define SNAFC_BIT_DMARWE                             ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_DRSAR
 * @brief  SPI NAND Flash DMA RAM Start Address Register (SNAFCDRSAR) (@ 0X01C)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_ADDR                             0
#define SNAFC_MASK_ADDR                              ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_DIR
 * @brief  SPI NAND Flash DMA Interrupt Register (SNAFDIR) (@ 0X020)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_DMA_IP                           0
#define SNAFC_BIT_DMA_IP                             ((u32)0x00000001 << 0)                              /*!<R/W1C 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_DLR
 * @brief  SPI NAND Flash DMA Length Register (SNAFDLR) (@ 0X024)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_DMA_IO_WIDTH                     28
#define SNAFC_MASK_DMA_IO_WIDTH                      ((u32)0x00000003 << 28)                             /*!<R/W 0   */
#define SNAFC_SHIFT_LEN                              0
#define SNAFC_MASK_LEN                               ((u32)0x0001FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_DCDSR
 * @brief  SPI NAND Flash DMA Current Data Status Register (SNAFDCDSR) (@ 0X028)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_CLENC                            0
#define SNAFC_MASK_CLENC                             ((u32)0x0001FFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SNAFC_SR
 * @brief  SPI NAND Flash Status Register (SNAFSR)   (@ 0X040)
 * @{
 *****************************************************************************/
#define SNAFC_SHIFT_DMARS                            4
#define SNAFC_BIT_DMARS                              ((u32)0x00000001 << 4)                              /*!<R 0   */
#define SNAFC_SHIFT_NFCOS                            3
#define SNAFC_BIT_NFCOS                              ((u32)0x00000001 << 3)                              /*!<R 0   */
#define SNAFC_SHIFT_NFDRS                            2
#define SNAFC_BIT_NFDRS                              ((u32)0x00000001 << 2)                              /*!<R 0   */
#define SNAFC_SHIFT_NFDWS                            1
#define SNAFC_BIT_NFDWS                              ((u32)0x00000001 << 1)                              /*!<R 0   */
#define SNAFC_SHIFT_CS                               0
#define SNAFC_BIT_CS                                 ((u32)0x00000001 << 0)                              /*!<R 1   */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_SNAFC
 * @{
 * @brief rtl8735b_SNAFC Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t SNAFC_CFR ;                              /*!<  SPI NAND Flash Configuration Register (SNAFCFR) register,  Address offset: 0x000 */
	__IO uint32_t SNAFC_CCR ;                              /*!<  SPI NAND Flash CS Control Register (SNAFCCR) register,  Address offset: 0x004 */
	__IO uint32_t SNAFC_WCMR ;                             /*!<  SPI NAND Flash Write Command Register (SNAFWCMR) register,  Address offset: 0x008 */
	__IO uint32_t SNAFC_RCMR ;                             /*!<  SPI NAND Flash Read Command Register (SNAFRCMR) register,  Address offset: 0x00C */
	__I  uint32_t SNAFC_RDR ;                              /*!<  SPI NAND Flash Read Data Register (SNAFRDR) register,  Address offset: 0x010 */
	__O  uint32_t SNAFC_WDR ;                              /*!<  SPI NAND Flash Write Data Register (SNAFWDR) register,  Address offset: 0x014 */
	__IO uint32_t SNAFC_DTR ;                              /*!<  SPI NAND Flash DMA Trigger Register (SNAFDTR) register,  Address offset: 0x018 */
	__IO uint32_t SNAFC_DRSAR ;                            /*!<  SPI NAND Flash DMA RAM Start Address Register (SNAFCDRSAR) register,  Address offset: 0x01C */
	__IO uint32_t SNAFC_DIR ;                              /*!<  SPI NAND Flash DMA Interrupt Register (SNAFDIR) register,  Address offset: 0x020 */
	__IO uint32_t SNAFC_DLR ;                              /*!<  SPI NAND Flash DMA Length Register (SNAFDLR) register,  Address offset: 0x024 */
	__I  uint32_t SNAFC_DCDSR ;                            /*!<  SPI NAND Flash DMA Current Data Status Register (SNAFDCDSR) register,  Address offset: 0x028 */
	__IO uint32_t RSVD0[5];                                /*!<  Reserved,  Address offset:0x2C-0x3C */
	__I  uint32_t SNAFC_SR ;                               /*!<  SPI NAND Flash Status Register (SNAFSR) register,           Address offset: 0x040 */
} SNAFC_TypeDef;
/** @} */

#endif
