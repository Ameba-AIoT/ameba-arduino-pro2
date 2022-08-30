

/**************************************************************************//**
 * @defgroup I2S_CTRL
 * @brief  I2S Control Register                      (@ 0X000)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_SW_RSTN                            31
#define I2S_BIT_SW_RSTN                              ((u32)0x00000001 << 31)                             /*!<R/W 0   */
#define I2S_SHIFT_WL                                 29
#define I2S_MASK_WL                                  ((u32)0x00000003 << 29)                             /*!<R/W 0   */
#define I2S_SHIFT_SLAVE_MODE                         28
#define I2S_BIT_SLAVE_MODE                           ((u32)0x00000001 << 28)                             /*!<R/W 0   */
#define I2S_SHIFT_MUTE                               27
#define I2S_BIT_MUTE                                 ((u32)0x00000001 << 27)                             /*!<R/W 0   */
#define I2S_SHIFT_BURST_SIZE                         18
#define I2S_MASK_BURST_SIZE                          ((u32)0x0000001F << 18)                             /*!<R/W 0xf   */
#define I2S_SHIFT_DEBUG_SWITCH                       15
#define I2S_MASK_DEBUG_SWITCH                        ((u32)0x00000003 << 15)                             /*!<R/W 0   */
#define I2S_SHIFT_BYTE_SWAP                          12
#define I2S_BIT_BYTE_SWAP                            ((u32)0x00000001 << 12)                             /*!<R/W 0   */
#define I2S_SHIFT_SCK_SWAP                           11
#define I2S_BIT_SCK_SWAP                             ((u32)0x00000001 << 11)                             /*!<R/W 0   */
#define I2S_SHIFT_LR_SWAP                            10
#define I2S_BIT_LR_SWAP                              ((u32)0x00000001 << 10)                             /*!<R/W 0   */
#define I2S_SHIFT_FORMAT                             8
#define I2S_MASK_FORMAT                              ((u32)0x00000003 << 8)                              /*!<R/W 0   */
#define I2S_SHIFT_LOOP_BACK                          7
#define I2S_BIT_LOOP_BACK                            ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define I2S_SHIFT_EDGE_SW                            5
#define I2S_BIT_EDGE_SW                              ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define I2S_SHIFT_AUDIO_MONO                         3
#define I2S_MASK_AUDIO_MONO                          ((u32)0x00000003 << 3)                              /*!<R/W 0   */
#define I2S_SHIFT_TX_ACT                             1
#define I2S_MASK_TX_ACT                              ((u32)0x00000003 << 1)                              /*!<R/W 0   */
#define I2S_SHIFT_IIS_EN                             0
#define I2S_BIT_IIS_EN                               ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_PAGE_PTR_TX
 * @brief  TX Page pointer Register                  (@ 0X004)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_PAGE_PTR_TX                        2
#define I2S_MASK_PAGE_PTR_TX                         ((u32)0x3FFFFFFF << 2)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_PAGE_PTR_RX
 * @brief  RX Page pointer Register                  (@ 0X008)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_PAGE_PTR_RX                        2
#define I2S_MASK_PAGE_PTR_RX                         ((u32)0x3FFFFFFF << 2)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_PAGE_SIZE_RATE
 * @brief  Page Size and Sample Rate Register        (@ 0X00C)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_CLK_SWITCH                         18
#define I2S_BIT_CLK_SWITCH                           ((u32)0x00000001 << 18)                             /*!<R/W 0   */
#define I2S_SHIFT_SR                                 14
#define I2S_MASK_SR                                  ((u32)0x0000000F << 14)                             /*!<R/W 0x5   */
#define I2S_SHIFT_PAGE_NUM                           12
#define I2S_MASK_PAGE_NUM                            ((u32)0x00000003 << 12)                             /*!<R/W 0   */
#define I2S_SHIFT_PAGE_SIZE                          0
#define I2S_MASK_PAGE_SIZE                           ((u32)0x00000FFF << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_TX_ISR_EN
 * @brief  TX Interrupt Enable Register              (@ 0X010)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_FIFO_EMPTY_IE_TX                   8
#define I2S_BIT_FIFO_EMPTY_IE_TX                     ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE3UNAVA_IE_TX                   7
#define I2S_BIT_PAGE3UNAVA_IE_TX                     ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE2UNAVA_IE_TX                   6
#define I2S_BIT_PAGE2UNAVA_IE_TX                     ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE1UNAVA_IE_TX                   5
#define I2S_BIT_PAGE1UNAVA_IE_TX                     ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE0UNAVA_IE_TX                   4
#define I2S_BIT_PAGE0UNAVA_IE_TX                     ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define I2S_SHIFT_P3OKIE_TX                          3
#define I2S_BIT_P3OKIE_TX                            ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define I2S_SHIFT_P2OKIE_TX                          2
#define I2S_BIT_P2OKIE_TX                            ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define I2S_SHIFT_P1OKIE_TX                          1
#define I2S_BIT_P1OKIE_TX                            ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define I2S_SHIFT_P0OKIE_TX                          0
#define I2S_BIT_P0OKIE_TX                            ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_TX_ISR_STATUS
 * @brief  TX Interrupt Status Register              (@ 0X014)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_FIFO_EMPTY_IP_TX                   8
#define I2S_BIT_FIFO_EMPTY_IP_TX                     ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE3UNAVA_IP_TX                   7
#define I2S_BIT_PAGE3UNAVA_IP_TX                     ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE2UNAVA_IP_TX                   6
#define I2S_BIT_PAGE2UNAVA_IP_TX                     ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE1UNAVA_IP_TX                   5
#define I2S_BIT_PAGE1UNAVA_IP_TX                     ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE0UNAVA_IP_TX                   4
#define I2S_BIT_PAGE0UNAVA_IP_TX                     ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define I2S_SHIFT_P3OKIP_TX                          3
#define I2S_BIT_P3OKIP_TX                            ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define I2S_SHIFT_P2OKIP_TX                          2
#define I2S_BIT_P2OKIP_TX                            ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define I2S_SHIFT_P1OKIP_TX                          1
#define I2S_BIT_P1OKIP_TX                            ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define I2S_SHIFT_P0OKIP_TX                          0
#define I2S_BIT_P0OKIP_TX                            ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_RX_ISR_EN
 * @brief  RX Interrupt Enable Register              (@ 0X018)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_FIFO_FULL_IE_RX                    8
#define I2S_BIT_FIFO_FULL_IE_RX                      ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE3UNAVA_IE_RX                   7
#define I2S_BIT_PAGE3UNAVA_IE_RX                     ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE2UNAVA_IE_RX                   6
#define I2S_BIT_PAGE2UNAVA_IE_RX                     ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE1UNAVA_IE_RX                   5
#define I2S_BIT_PAGE1UNAVA_IE_RX                     ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE0UNAVA_IE_RX                   4
#define I2S_BIT_PAGE0UNAVA_IE_RX                     ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define I2S_SHIFT_P3OKIE_RX                          3
#define I2S_BIT_P3OKIE_RX                            ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define I2S_SHIFT_P2OKIE_RX                          2
#define I2S_BIT_P2OKIE_RX                            ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define I2S_SHIFT_P1OKIE_RX                          1
#define I2S_BIT_P1OKIE_RX                            ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define I2S_SHIFT_P0OKIE_RX                          0
#define I2S_BIT_P0OKIE_RX                            ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_RX_ISR_STATUS
 * @brief  RX Interrupt Status Register              (@ 0X01C)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_FIFO_FULL_IP_RX                    8
#define I2S_BIT_FIFO_FULL_IP_RX                      ((u32)0x00000001 << 8)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE3UNAVA_IP_RX                   7
#define I2S_BIT_PAGE3UNAVA_IP_RX                     ((u32)0x00000001 << 7)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE2UNAVA_IP_RX                   6
#define I2S_BIT_PAGE2UNAVA_IP_RX                     ((u32)0x00000001 << 6)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE1UNAVA_IP_RX                   5
#define I2S_BIT_PAGE1UNAVA_IP_RX                     ((u32)0x00000001 << 5)                              /*!<R/W 0   */
#define I2S_SHIFT_PAGE0UNAVA_IP_RX                   4
#define I2S_BIT_PAGE0UNAVA_IP_RX                     ((u32)0x00000001 << 4)                              /*!<R/W 0   */
#define I2S_SHIFT_P3OKIP_RX                          3
#define I2S_BIT_P3OKIP_RX                            ((u32)0x00000001 << 3)                              /*!<R/W 0   */
#define I2S_SHIFT_P2OKIP_RX                          2
#define I2S_BIT_P2OKIP_RX                            ((u32)0x00000001 << 2)                              /*!<R/W 0   */
#define I2S_SHIFT_P1OKIP_RX                          1
#define I2S_BIT_P1OKIP_RX                            ((u32)0x00000001 << 1)                              /*!<R/W 0   */
#define I2S_SHIFT_P0OKIP_RX                          0
#define I2S_BIT_P0OKIP_RX                            ((u32)0x00000001 << 0)                              /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_TX_PAGE0_OWN
 * @brief  TX Page0 Own Bit Register                 (@ 0X020)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_P0OWN_TX                           31
#define I2S_BIT_P0OWN_TX                             ((u32)0x00000001 << 31)                             /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_TX_PAGE1_OWN
 * @brief  TX Page1 Own Bit Register                 (@ 0X024)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_P1OWN_TX                           31
#define I2S_BIT_P1OWN_TX                             ((u32)0x00000001 << 31)                             /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_TX_PAGE2_OWN
 * @brief  TX Page2 Own Bit Register                 (@ 0X028)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_P2OWN_TX                           31
#define I2S_BIT_P2OWN_TX                             ((u32)0x00000001 << 31)                             /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_TX_PAGE3_OWN
 * @brief  TX Page3 Own Bit Register                 (@ 0X02C)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_P3OWN_TX                           31
#define I2S_BIT_P3OWN_TX                             ((u32)0x00000001 << 31)                             /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_RX_PAGE0_OWN
 * @brief  RX Page0 Own Bit Register                 (@ 0X030)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_P0OWN_RX                           31
#define I2S_BIT_P0OWN_RX                             ((u32)0x00000001 << 31)                             /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_RX_PAGE1_OWN
 * @brief  RX Page1 Own Bit Register                 (@ 0X034)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_P1OWN_RX                           31
#define I2S_BIT_P1OWN_RX                             ((u32)0x00000001 << 31)                             /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_RX_PAGE2_OWN
 * @brief  RX Page2 Own Bit Register                 (@ 0X038)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_P2OWN_RX                           31
#define I2S_BIT_P2OWN_RX                             ((u32)0x00000001 << 31)                             /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_RX_PAGE3_OWN
 * @brief  RX Page3 Own Bit Register                 (@ 0X03C)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_P3OWN_RX                           31
#define I2S_BIT_P3OWN_RX                             ((u32)0x00000001 << 31)                             /*!<R/W 0   */
/** @} */

/**************************************************************************//**
 * @defgroup I2S_VERSION_ID
 * @brief  Version id                                (@ 0X040)
 * @{
 *****************************************************************************/
#define I2S_SHIFT_VERSION_ID                         0
#define I2S_MASK_VERSION_ID                          ((u32)0xFFFFFFFF << 0)                              /*!<R 0   */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_I2S
 * @{
 * @brief rtl8735b_I2S Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t I2S_CTRL ;                               /*!<  I2S Control Register register,  Address offset: 0x000 */
	__IO uint32_t I2S_PAGE_PTR_TX ;                        /*!<  TX Page pointer Register register,  Address offset: 0x004 */
	__IO uint32_t I2S_PAGE_PTR_RX ;                        /*!<  RX Page pointer Register register,  Address offset: 0x008 */
	__IO uint32_t I2S_PAGE_SIZE_RATE ;                     /*!<  Page Size and Sample Rate Register register,  Address offset: 0x00C */
	__IO uint32_t I2S_TX_ISR_EN ;                          /*!<  TX Interrupt Enable Register register,  Address offset: 0x010 */
	__IO uint32_t I2S_TX_ISR_STATUS ;                      /*!<  TX Interrupt Status Register register,  Address offset: 0x014 */
	__IO uint32_t I2S_RX_ISR_EN ;                          /*!<  RX Interrupt Enable Register register,  Address offset: 0x018 */
	__IO uint32_t I2S_RX_ISR_STATUS ;                      /*!<  RX Interrupt Status Register register,  Address offset: 0x01C */
	__IO uint32_t I2S_TX_PAGE0_OWN ;                       /*!<  TX Page0 Own Bit Register register,  Address offset: 0x020 */
	__IO uint32_t I2S_TX_PAGE1_OWN ;                       /*!<  TX Page1 Own Bit Register register,  Address offset: 0x024 */
	__IO uint32_t I2S_TX_PAGE2_OWN ;                       /*!<  TX Page2 Own Bit Register register,  Address offset: 0x028 */
	__IO uint32_t I2S_TX_PAGE3_OWN ;                       /*!<  TX Page3 Own Bit Register register,  Address offset: 0x02C */
	__IO uint32_t I2S_RX_PAGE0_OWN ;                       /*!<  RX Page0 Own Bit Register register,  Address offset: 0x030 */
	__IO uint32_t I2S_RX_PAGE1_OWN ;                       /*!<  RX Page1 Own Bit Register register,  Address offset: 0x034 */
	__IO uint32_t I2S_RX_PAGE2_OWN ;                       /*!<  RX Page2 Own Bit Register register,  Address offset: 0x038 */
	__IO uint32_t I2S_RX_PAGE3_OWN ;                       /*!<  RX Page3 Own Bit Register register,  Address offset: 0x03C */
	__I  uint32_t I2S_VERSION_ID ;                         /*!<  Version id register,            Address offset: 0x040 */
} I2S_TypeDef;
/** @} */


