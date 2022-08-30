#ifndef _RTL8735B_SSI_TYPE_H_
#define _RTL8735B_SSI_TYPE_H_

/**************************************************************************//**
 * @defgroup SSI_CTRLR0
 * @brief  SSI Control Register 0                    (@ 0X000)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_SS_T                               31
#define SSI_BIT_SS_T                                 ((u32)0x00000001 << 31)                             /*!<R/W 0   */
#define SSI_SHIFT_RX_SHIFT_SWAP                      24
#define SSI_BIT_RX_BIT_SWAP                          ((u32)0x00000001 << 24)                             /*!<R/W 0   */
#define SSI_SHIFT_RX_BYTE_SWAP                       23
#define SSI_BIT_RX_BYTE_SWAP                         ((u32)0x00000001 << 23)                             /*!<R/W 0   */
#define SSI_SHIFT_TX_SHIFT_SWAP                      22
#define SSI_BIT_TX_BIT_SWAP                          ((u32)0x00000001 << 22)                             /*!<R/W 0   */
#define SSI_SHIFT_TX_BYTE_SWAP                       21
#define SSI_BIT_TX_BYTE_SWAP                         ((u32)0x00000001 << 21)                             /*!<R/W 0   */
#define SSI_SHIFT_CFS                                12
#define SSI_MASK_CFS                                 ((u32)0x0000000F << 12)                             /*!<R/W 0   */
#define SSI_SHIFT_SLV_OE                             10
#define SSI_BIT_SLV_OE                               ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define SSI_SHIFT_TMOD                               8
#define SSI_MASK_TMOD                                ((u32)0x00000003 << 8)                              /*!<R/W 0   */
#define SSI_SHIFT_SCPOL                              7
#define SSI_BIT_SCPOL                                ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define SSI_SHIFT_SCPH                               6
#define SSI_BIT_SCPH                                 ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define SSI_SHIFT_FRF                                4
#define SSI_MASK_FRF                                 ((u32)0x00000003 << 4)                              /*!<R/W 0   */
#define SSI_SHIFT_DFS                                0
#define SSI_MASK_DFS                                 ((u32)0x0000000F << 0)                              /*!<R/W 0x7   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_CTRLR1
 * @brief  SSI Control Register 1                    (@ 0X004)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_NDF                                0
#define SSI_MASK_NDF                                 ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_SSIENR
 * @brief  SSI Enable Register                       (@ 0X008)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_EN                                 0
#define SSI_BIT_EN                                   ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_MWCR
 * @brief  Microwire Control Register                (@ 0X00C)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_MHS                                2
#define SSI_BIT_MHS                                  ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define SSI_SHIFT_MDD                                1
#define SSI_BIT_MDD                                  ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SSI_SHIFT_MWMOD                              0
#define SSI_BIT_MWMOD                                ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_SER
 * @brief  Slave Enable Register                     (@ 0X010)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_SER                                0
#define SSI_MASK_SER                                 ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_BAUDR
 * @brief  Baud Rate Select Register                 (@ 0X014)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_SCKDV                              0
#define SSI_MASK_SCKDV                               ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_TXFTLR
 * @brief  Transmit FIFO Threshold Level             (@ 0X018)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_TFT                                0
#define SSI_MASK_TFT                                 ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_RXFTLR
 * @brief  Receive FIFO Threshold Level              (@ 0X01C)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_RFT                                0
#define SSI_MASK_RFT                                 ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_TXFLR
 * @brief  Transmit FIFO Level Register              (@ 0X020)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_TXTFL                              0
#define SSI_MASK_TXTFL                               ((u32)0x000000FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_RXFLR
 * @brief  Receive FIFO Level Register               (@ 0X024)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_RXTFL                              0
#define SSI_MASK_RXTFL                               ((u32)0x000000FF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_SR
 * @brief  Status Register                           (@ 0X028)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_TXE                                5
#define SSI_BIT_TXE                                  ((u32)0x00000001 << 5)                              /*!<R 0   */
#define SSI_SHIFT_RFF                                4
#define SSI_BIT_RFF                                  ((u32)0x00000001 << 4)                              /*!<R 0   */
#define SSI_SHIFT_RFNE                               3
#define SSI_BIT_RFNE                                 ((u32)0x00000001 << 3)                              /*!<R 0   */
#define SSI_SHIFT_TFE                                2
#define SSI_BIT_TFE                                  ((u32)0x00000001 << 2)                              /*!<R 1   */
#define SSI_SHIFT_TFNF                               1
#define SSI_BIT_TFNF                                 ((u32)0x00000001 << 1)                              /*!<R 1   */
#define SSI_SHIFT_BUSY                               0
#define SSI_BIT_BUSY                                 ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_IMR
 * @brief  Interrupt Mask Register                   (@ 0X02C)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_SSRIM                              7
#define SSI_BIT_SSRIM                                ((u32)0x00000001 << 7)                              /*!<R/W 1   */
#define SSI_SHIFT_TXUIM                              6
#define SSI_BIT_TXUIM                                ((u32)0x00000001 << 6)                              /*!<R/W 1   */
#define SSI_SHIFT_MSTIM                              5
#define SSI_BIT_MSTIM                                ((u32)0x00000001 << 5)                              /*!<R/W 1   */
#define SSI_SHIFT_RXFIM                              4
#define SSI_BIT_RXFIM                                ((u32)0x00000001 << 4)                              /*!<R/W 1   */
#define SSI_SHIFT_RXOIM                              3
#define SSI_BIT_RXOIM                                ((u32)0x00000001 << 3)                              /*!<R/W 1   */
#define SSI_SHIFT_RXUIM                              2
#define SSI_BIT_RXUIM                                ((u32)0x00000001 << 2)                              /*!<R/W 1   */
#define SSI_SHIFT_TXOIM                              1
#define SSI_BIT_TXOIM                                ((u32)0x00000001 << 1)                              /*!<R/W 1   */
#define SSI_SHIFT_TXEIM                              0
#define SSI_BIT_TXEIM                                ((u32)0x00000001 << 0)                              /*!<R/W 1   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_IMR_SLV
 * @brief  Interrupt Mask of RTK-SPI Slave Register  (@ 0X02C)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_SSRIM                              7
#define SSI_BIT_SSRIM                                ((u32)0x00000001 << 7)                              /*!<R/W 1   */
#define SSI_SHIFT_TXUIM                              6
#define SSI_BIT_TXUIM                                ((u32)0x00000001 << 6)                              /*!<R/W 1   */
#define SSI_SHIFT_FAEIM                              5
#define SSI_BIT_FAEIM                                ((u32)0x00000001 << 5)                              /*!<R/W 1   */
#define SSI_SHIFT_RXFIM                              4
#define SSI_BIT_RXFIM                                ((u32)0x00000001 << 4)                              /*!<R/W 1   */
#define SSI_SHIFT_RXOIM                              3
#define SSI_BIT_RXOIM                                ((u32)0x00000001 << 3)                              /*!<R/W 1   */
#define SSI_SHIFT_RXUIM                              2
#define SSI_BIT_RXUIM                                ((u32)0x00000001 << 2)                              /*!<R/W 1   */
#define SSI_SHIFT_TXOIM                              1
#define SSI_BIT_TXOIM                                ((u32)0x00000001 << 1)                              /*!<R/W 1   */
#define SSI_SHIFT_TXEIM                              0
#define SSI_BIT_TXEIM                                ((u32)0x00000001 << 0)                              /*!<R/W 1   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_ISR
 * @brief  Interrupt Status Register                 (@ 0X030)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_SSRIS                              7
#define SSI_BIT_SSRIS                                ((u32)0x00000001 << 7)                              /*!<R 0   */
#define SSI_SHIFT_TXUIS                              6
#define SSI_BIT_TXUIS                                ((u32)0x00000001 << 6)                              /*!<R 0   */
#define SSI_SHIFT_MSTIS                              5
#define SSI_BIT_MSTIS                                ((u32)0x00000001 << 5)                              /*!<R 0   */
#define SSI_SHIFT_RXFIS                              4
#define SSI_BIT_RXFIS                                ((u32)0x00000001 << 4)                              /*!<R 0   */
#define SSI_SHIFT_RXOIS                              3
#define SSI_BIT_RXOIS                                ((u32)0x00000001 << 3)                              /*!<R 0   */
#define SSI_SHIFT_RXUIS                              2
#define SSI_BIT_RXUIS                                ((u32)0x00000001 << 2)                              /*!<R 0   */
#define SSI_SHIFT_TXOIS                              1
#define SSI_BIT_TXOIS                                ((u32)0x00000001 << 1)                              /*!<R 0   */
#define SSI_SHIFT_TXEIS                              0
#define SSI_BIT_TXEIS                                ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_ISR_SLV
 * @brief  Interrupt Status Register                 (@ 0X030)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_SSRIS                              7
#define SSI_BIT_SSRIS                                ((u32)0x00000001 << 7)                              /*!<R 0   */
#define SSI_SHIFT_TXUIS                              6
#define SSI_BIT_TXUIS                                ((u32)0x00000001 << 6)                              /*!<R 0   */
#define SSI_SHIFT_FAEIS                              5
#define SSI_BIT_FAEIS                                ((u32)0x00000001 << 5)                              /*!<R 0   */
#define SSI_SHIFT_RXFIS                              4
#define SSI_BIT_RXFIS                                ((u32)0x00000001 << 4)                              /*!<R 0   */
#define SSI_SHIFT_RXOIS                              3
#define SSI_BIT_RXOIS                                ((u32)0x00000001 << 3)                              /*!<R 0   */
#define SSI_SHIFT_RXUIS                              2
#define SSI_BIT_RXUIS                                ((u32)0x00000001 << 2)                              /*!<R 0   */
#define SSI_SHIFT_TXOIS                              1
#define SSI_BIT_TXOIS                                ((u32)0x00000001 << 1)                              /*!<R 0   */
#define SSI_SHIFT_TXEIS                              0
#define SSI_BIT_TXEIS                                ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_RISR
 * @brief  Raw Interrupt Status Register             (@ 0X034)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_SSRIR                              7
#define SSI_BIT_SSRIR                                ((u32)0x00000001 << 7)                              /*!<R 0   */
#define SSI_SHIFT_TXUIR                              6
#define SSI_BIT_TXUIR                                ((u32)0x00000001 << 6)                              /*!<R 0   */
#define SSI_SHIFT_MSTIR                              5
#define SSI_BIT_MSTIR                                ((u32)0x00000001 << 5)                              /*!<R 0   */
#define SSI_SHIFT_RXFIR                              4
#define SSI_BIT_RXFIR                                ((u32)0x00000001 << 4)                              /*!<R 0   */
#define SSI_SHIFT_RXOIR                              3
#define SSI_BIT_RXOIR                                ((u32)0x00000001 << 3)                              /*!<R 0   */
#define SSI_SHIFT_RXUIR                              2
#define SSI_BIT_RXUIR                                ((u32)0x00000001 << 2)                              /*!<R 0   */
#define SSI_SHIFT_TXOIR                              1
#define SSI_BIT_TXOIR                                ((u32)0x00000001 << 1)                              /*!<R 0   */
#define SSI_SHIFT_TXEIR                              0
#define SSI_BIT_TXEIR                                ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_RISR_SLV
 * @brief  Raw Interrupt Status Register             (@ 0X034)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_SSRIR                              7
#define SSI_BIT_SSRIR                                ((u32)0x00000001 << 7)                              /*!<R 0   */
#define SSI_SHIFT_TXUIR                              6
#define SSI_BIT_TXUIR                                ((u32)0x00000001 << 6)                              /*!<R 0   */
#define SSI_SHIFT_FAEIR                              5
#define SSI_BIT_FAEIR                                ((u32)0x00000001 << 5)                              /*!<R 0   */
#define SSI_SHIFT_RXFIR                              4
#define SSI_BIT_RXFIR                                ((u32)0x00000001 << 4)                              /*!<R 0   */
#define SSI_SHIFT_RXOIR                              3
#define SSI_BIT_RXOIR                                ((u32)0x00000001 << 3)                              /*!<R 0   */
#define SSI_SHIFT_RXUIR                              2
#define SSI_BIT_RXUIR                                ((u32)0x00000001 << 2)                              /*!<R 0   */
#define SSI_SHIFT_TXOIR                              1
#define SSI_BIT_TXOIR                                ((u32)0x00000001 << 1)                              /*!<R 0   */
#define SSI_SHIFT_TXEIR                              0
#define SSI_BIT_TXEIR                                ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_TXOICR
 * @brief  Transmit FIFO Overflow Interrupt Clear Register (@ 0X038)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_TXOICR                             0
#define SSI_BIT_TXOICR                               ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_RXOICR
 * @brief  Receive FIFO Overflow Interrupt Clear Register (@ 0X03C)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_RXOICR                             0
#define SSI_BIT_RXOICR                               ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_RXUICR
 * @brief  Receive FIFO Underflow Interrupt Clear Register (@ 0X040)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_RXUICR                             0
#define SSI_BIT_RXUICR                               ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_MSTICR
 * @brief  Multi-Master Interrupt Clear Register     (@ 0X044)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_MSTICR                             0
#define SSI_BIT_MSTICR                               ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_FAEICR
 * @brief  Frame Alignment Interrupt Clear Register  (@ 0X044)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_FAEICR                             0
#define SSI_BIT_FAEICR                               ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_ICR
 * @brief  Interrupt Clear Register                  (@ 0X048)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_ICR                                0
#define SSI_BIT_ICR                                  ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_DMACR
 * @brief  DMA Control Register                      (@ 0X04C)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_TDMAE                              1
#define SSI_BIT_TDMAE                                ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define SSI_SHIFT_RDMAE                              0
#define SSI_BIT_RDMAE                                ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_DMATDLR
 * @brief  DMA Transmit Data Level Register          (@ 0X050)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_DMATDL                             0
#define SSI_MASK_DMATDL                              ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_DMARDLR
 * @brief  DMA Receive Data Level Register           (@ 0X054)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_DMARDL                             7
#define SSI_BIT_DMARDL                               ((u32)0x00000001 << 7)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_TXUICR
 * @brief  Transmit FIFO Underflow Interrupt Clear Register (@ 0X058)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_TXUICR                             0
#define SSI_BIT_TXUICR                               ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_SSRICR
 * @brief  SS_N Rising Edge Detect Interrupt Clear Register (@ 0X05C)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_SSIICR                             0
#define SSI_BIT_SSIICR                               ((u32)0x00000001 << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_DR
 * @brief  Data Register                             (@ 0X060)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_DR                                 0
#define SSI_MASK_DR                                  ((u32)0x0000FFFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup SSI_RX_SAMPLE_DLY
 * @brief  Rx Sample Delay Register                  (@ 0X0F0)
 * @{
 *****************************************************************************/
#define SSI_SHIFT_RSD                                0
#define SSI_MASK_RSD                                 ((u32)0x000000FF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_SSI
 * @{
 * @brief rtl8735b_SSI Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t SSI_CTRLR0 ;                             /*!<  SSI Control Register 0 register,  Address offset: 0x000 */
	__IO uint32_t SSI_CTRLR1 ;                             /*!<  SSI Control Register 1 register,  Address offset: 0x004 */
	__IO uint32_t SSI_SSIENR ;                             /*!<  SSI Enable Register register,  Address offset: 0x008 */
	__IO uint32_t SSI_MWCR ;                               /*!<  Microwire Control Register register,  Address offset: 0x00C */
	__IO uint32_t SSI_SER ;                                /*!<  Slave Enable Register register,  Address offset: 0x010 */
	__IO uint32_t SSI_BAUDR ;                              /*!<  Baud Rate Select Register register,  Address offset: 0x014 */
	__IO uint32_t SSI_TXFTLR ;                             /*!<  Transmit FIFO Threshold Level register,  Address offset: 0x018 */
	__IO uint32_t SSI_RXFTLR ;                             /*!<  Receive FIFO Threshold Level register,  Address offset: 0x01C */
	__IO uint32_t SSI_TXFLR ;                              /*!<  Transmit FIFO Level Register register,  Address offset: 0x020 */
	__I  uint32_t SSI_RXFLR ;                              /*!<  Receive FIFO Level Register register,  Address offset: 0x024 */
	__I  uint32_t SSI_SR ;                                 /*!<  Status Register register,  Address offset: 0x028 */
	union {
		__IO uint32_t SSI_IMR ;                                /*!<  Interrupt Mask Register register,  Address offset: 0x02C */
		__IO uint32_t SSI_IMR_SLV ;                            /*!<  Interrupt Mask of RTK-SPI Slave Register register,  Address offset: 0x02C */
	};
	union {
		__I  uint32_t SSI_ISR ;                                /*!<  Interrupt Status Register register,  Address offset: 0x030 */
		__I  uint32_t SSI_ISR_SLV ;                            /*!<  Interrupt Status Register register,  Address offset: 0x030 */
	};
	union {
		__I  uint32_t SSI_RISR ;                               /*!<  Raw Interrupt Status Register register,  Address offset: 0x034 */
		__I  uint32_t SSI_RISR_SLV ;                           /*!<  Raw Interrupt Status Register register,  Address offset: 0x034 */
	};
	__I  uint32_t SSI_TXOICR ;                             /*!<  Transmit FIFO Overflow Interrupt Clear Register register,  Address offset: 0x038 */
	__I  uint32_t SSI_RXOICR ;                             /*!<  Receive FIFO Overflow Interrupt Clear Register register,  Address offset: 0x03C */
	__I  uint32_t SSI_RXUICR ;                             /*!<  Receive FIFO Underflow Interrupt Clear Register register,  Address offset: 0x040 */
	union {
		__I  uint32_t SSI_MSTICR ;                             /*!<  Multi-Master Interrupt Clear Register register,  Address offset: 0x044 */
		__I  uint32_t SSI_FAEICR ;                             /*!<  Frame Alignment Interrupt Clear Register register,  Address offset: 0x044 */
	};
	__I  uint32_t SSI_ICR ;                                /*!<  Interrupt Clear Register register,  Address offset: 0x048 */
	__IO uint32_t SSI_DMACR ;                              /*!<  DMA Control Register register,  Address offset: 0x04C */
	__IO uint32_t SSI_DMATDLR ;                            /*!<  DMA Transmit Data Level Register register,  Address offset: 0x050 */
	__IO uint32_t SSI_DMARDLR ;                            /*!<  DMA Receive Data Level Register register,  Address offset: 0x054 */
	__I  uint32_t SSI_TXUICR ;                             /*!<  Transmit FIFO Underflow Interrupt Clear Register register,  Address offset: 0x058 */
	__I  uint32_t SSI_SSRICR ;                             /*!<  SS_N Rising Edge Detect Interrupt Clear Register register,  Address offset: 0x05C */
	__IO uint32_t SSI_DR ;                                 /*!<  Data Register register,  Address offset: 0x060 */
	__IO uint32_t RSVD0[35];                               /*!<  Reserved,  Address offset:0x64-0xEC */
	__IO uint32_t SSI_RX_SAMPLE_DLY ;                      /*!<  Rx Sample Delay Register register,         Address offset: 0x0F0 */
} SSI_TypeDef;
/** @} */

#endif
