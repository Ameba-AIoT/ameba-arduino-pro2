#ifndef _RTL8735B_GPIO_TYPE_H_
#define _RTL8735B_GPIO_TYPE_H_

/**************************************************************************//**
 * @defgroup GPIO_IT_STS
 * @brief  GPIO interrupt type status Register       (@ 0X000)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_IT_STS                            0
#define GPIO_MASK_IT_STS                             ((u32)0x0000FFFF << 0)                              /*!<R 0  For each bit : 0: the specific GPIO pin is configured to edge sensitive interrupt mode 1: the specific GPIO pin is configured to levle sensitive interrupt mode. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_EI_EN
 * @brief  GPIO edge sensitive interrupt mode enable (@ 0X004)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_EI_EN                             0
#define GPIO_MASK_EI_EN                              ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO pin is configured to edge sensitive interrupt mode and also cause the corresponging bit of REG_GPIO_IT_STS to be read as 0. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_LI_EN
 * @brief  GPIO level sensitive interrupt mode enable (@ 0X008)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_LI_EN                             0
#define GPIO_MASK_LI_EN                              ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO pin is configured as level sensitive interrupt mode and also cause the corresponging bit of REG_GPIO_IT_STS to be read as 1. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_IP_STS
 * @brief  GPIO interrupt polarity status            (@ 0X00C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_IP_STS15                          30
#define GPIO_MASK_IP_STS15                           ((u32)0x00000003 << 30)                             /*!<R 0  The interrupt polarity status of GPIO15 */
#define GPIO_SHIFT_IP_STS14                          28
#define GPIO_MASK_IP_STS14                           ((u32)0x00000003 << 28)                             /*!<R 0  The interrupt polarity status of GPIO14 */
#define GPIO_SHIFT_IP_STS13                          26
#define GPIO_MASK_IP_STS13                           ((u32)0x00000003 << 26)                             /*!<R 0  The interrupt polarity status of GPIO13 */
#define GPIO_SHIFT_IP_STS12                          24
#define GPIO_MASK_IP_STS12                           ((u32)0x00000003 << 24)                             /*!<R 0  The interrupt polarity status of GPIO12 */
#define GPIO_SHIFT_IP_STS11                          22
#define GPIO_MASK_IP_STS11                           ((u32)0x00000003 << 22)                             /*!<R 0  The interrupt polarity status of GPIO11 */
#define GPIO_SHIFT_IP_STS10                          20
#define GPIO_MASK_IP_STS10                           ((u32)0x00000003 << 20)                             /*!<R 0  The interrupt polarity status of GPIO10 */
#define GPIO_SHIFT_IP_STS9                           18
#define GPIO_MASK_IP_STS9                            ((u32)0x00000003 << 18)                             /*!<R 0  The interrupt polarity status of GPIO9 */
#define GPIO_SHIFT_IP_STS8                           16
#define GPIO_MASK_IP_STS8                            ((u32)0x00000003 << 16)                             /*!<R 0  The interrupt polarity status of GPIO8 */
#define GPIO_SHIFT_IP_STS7                           14
#define GPIO_MASK_IP_STS7                            ((u32)0x00000003 << 14)                             /*!<R 0  The interrupt polarity status of GPIO7 */
#define GPIO_SHIFT_IP_STS6                           12
#define GPIO_MASK_IP_STS6                            ((u32)0x00000003 << 12)                             /*!<R 0  The interrupt polarity status of GPIO6 */
#define GPIO_SHIFT_IP_STS5                           10
#define GPIO_MASK_IP_STS5                            ((u32)0x00000003 << 10)                             /*!<R 0  The interrupt polarity status of GPIO5 */
#define GPIO_SHIFT_IP_STS4                           8
#define GPIO_MASK_IP_STS4                            ((u32)0x00000003 << 8)                              /*!<R 0  The interrupt polarity status of GPIO4 */
#define GPIO_SHIFT_IP_STS3                           6
#define GPIO_MASK_IP_STS3                            ((u32)0x00000003 << 6)                              /*!<R 0  The interrupt polarity status of GPIO3 */
#define GPIO_SHIFT_IP_STS2                           4
#define GPIO_MASK_IP_STS2                            ((u32)0x00000003 << 4)                              /*!<R 0  The interrupt polarity status of GPIO2 */
#define GPIO_SHIFT_IP_STS1                           2
#define GPIO_MASK_IP_STS1                            ((u32)0x00000003 << 2)                              /*!<R 0  The interrupt polarity status of GPIO1 */
#define GPIO_SHIFT_IP_STS0                           0
#define GPIO_MASK_IP_STS0                            ((u32)0x00000003 << 0)                              /*!<R 0  The interrupt polarity status of GPIO0 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_IR_EN
 * @brief  GPIO interrupt rising-edge enable         (@ 0X014)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_IR_EN                             0
#define GPIO_MASK_IR_EN                              ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation; 1: the conrtolled GPIO pin is configured to rising-edge interrupt mode or high-level mode (depends on REG_GPIO_IT_STS) and also cause the corresponding bits of REG_GPIO_IP_STS to be read as 00b. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_IF_EN
 * @brief  GPIO interrupt falling-edge enable        (@ 0X018)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_IF_EN                             0
#define GPIO_MASK_IF_EN                              ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation; 1: the conrtolled GPIO pin is configured to falling-edge interrupt mode or low-level interrupt mode (depends on REG_GPIO_IT_STS) and cause the corresponding bits of REG_GPIO_IP_STS to be read as 01b. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_ID_EN
 * @brief  GPIO interrupt dual-edge enable           (@ 0X01C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ID_EN                             0
#define GPIO_MASK_ID_EN                              ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation; 1: the conrtolled GPIO pin is configured to dual-edge interrupt mode and also cause the corresponding bits of REG_GPIO_IP_STS to be read as 10b. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_IE_STS
 * @brief  GPIO interrupt enable status              (@ 0X020)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_IE_STS                            0
#define GPIO_MASK_IE_STS                             ((u32)0x0000FFFF << 0)                              /*!<R 0  For each bit: 0: the interrupt of the specific GPIO pin is disabled 1: the interrupt of the specific GPIO pin is enabled */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT_EN
 * @brief  GPIO interrupt enable                     (@ 0X024)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_EN                            0
#define GPIO_MASK_INT_EN                             ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: to enable the specific GPIO INT and also cause the specified bit of REG_GPIO_IE_STS to be read as ONE. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT_DIS
 * @brief  GPIO interrupt disable                    (@ 0X028)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_DIS                           0
#define GPIO_MASK_INT_DIS                            ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: to disable the specified the GPIO INT and also cause the specified bit of REG_GPIO_IE_STS to be read as ZERO. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT_RAW_STS
 * @brief  GPIO RAW interrupt status                 (@ 0X02C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_RAW_STS                       0
#define GPIO_MASK_INT_RAW_STS                        ((u32)0x0000FFFF << 0)                              /*!<R 0  For each bit: 0: the specified GPIO pin has no pending interrupt 1: the specified GPIO pin's interrupt is pending (permasking) */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT_STS
 * @brief  GPIO interrupt status                     (@ 0X030)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_STS                           0
#define GPIO_MASK_INT_STS                            ((u32)0x0000FFFF << 0)                              /*!<R 0  For each bit: 0: the specified GPIO pin has no pending interrupt 1: the specified GPIO pin's interrupt is pending */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT_CLR
 * @brief  GPIO interrupt status clear               (@ 0X034)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_CLR                           0
#define GPIO_MASK_INT_CLR                            ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit writting: 0: No operation; 1: Clear edge type pending interrupt of the conrtolled GPIO pin and clear the specified bits of REG_GPIO_INT_STS as ZERO */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT_FUNC_EN_STS
 * @brief  GPIO interrupt function enable status     (@ 0X038)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_EN_STS                        0
#define GPIO_MASK_INT_EN_STS                         ((u32)0x0000FFFF << 0)                              /*!<R 0  For each bit: 0: the specified GPIO INT is Disable 1: the specified GPIO INT is Enable */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT_FUNC_EN
 * @brief  GPIO interrupt function enable            (@ 0X03C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_EN                            0
#define GPIO_MASK_INT_EN                             ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the specified GPIO INT is enabled and also cause the specified bit of REG_GPIO_INT_FUNC_EN_STS to be read as ONE. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT_FUNC_DIS
 * @brief  GPIO interrupt function disable           (@ 0X040)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_DIS                           0
#define GPIO_MASK_INT_DIS                            ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the specified GPIO INT is disabled and also cause the specified bit of REG_GPIO_INT_FUNC_EN_STS to be read as ZERO. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT0_SEL
 * @brief  GPIO INT0 selection                       (@ 0X050)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT0 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT0 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT0 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT1_SEL
 * @brief  GPIO INT1 selection                       (@ 0X054)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT1 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT1 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT1 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT2_SEL
 * @brief  GPIO INT2 selection                       (@ 0X058)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT2 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT2 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT2 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT3_SEL
 * @brief  GPIO INT3 selection                       (@ 0X05C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT3 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT3 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT3 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT4_SEL
 * @brief  GPIO INT4 selection                       (@ 0X060)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT4 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT4 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT4 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT5_SEL
 * @brief  GPIO INT5 selection                       (@ 0X064)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT5 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT5 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT5 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT6_SEL
 * @brief  GPIO INT6 selection                       (@ 0X068)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT6 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT6 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT6 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT7_SEL
 * @brief  GPIO INT7 selection                       (@ 0X06C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT7 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT7 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT7 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT8_SEL
 * @brief  GPIO INT8 selection                       (@ 0X070)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT8 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT8 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT8 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT9_SEL
 * @brief  GPIO INT9 selection                       (@ 0X074)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT9 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT9 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT9 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT10_SEL
 * @brief  GPIO INT10 selection                      (@ 0X078)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT10 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT10 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT10 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT11_SEL
 * @brief  GPIO INT11 selection                      (@ 0X07C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT11 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT11 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT11 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT12_SEL
 * @brief  GPIO INT12 selection                      (@ 0X080)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT12 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT12 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT12 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT13_SEL
 * @brief  GPIO INT13 selection                      (@ 0X084)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT13 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT13 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT13 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT14_SEL
 * @brief  GPIO INT14 selection                      (@ 0X088)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT14 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT14 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT14 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_INT15_SEL
 * @brief  GPIO INT15 selection                      (@ 0X08C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_INT_SUR_SEL                       15
#define GPIO_BIT_INT_SUR_SEL                         ((u32)0x00000001 << 15)                             /*!<R/W 0  0: Useing pin input signal as interrupt signal source 1: Using debounce output signal as interrupt signal source */
#define GPIO_SHIFT_INT_DEB_SEL                       8
#define GPIO_MASK_INT_DEB_SEL                        ((u32)0x0000000F << 8)                              /*!<R/W 0  Debounce Output signal selection for GPIO INT15 */
#define GPIO_SHIFT_INT_GP_SEL                        5
#define GPIO_MASK_INT_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for GPIO INT15 */
#define GPIO_SHIFT_INT_MER_SEL                       0
#define GPIO_MASK_INT_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for GPIO INT15 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB_STS
 * @brief  GPIO port debounce status                 (@ 0X0F0)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_STS                           0
#define GPIO_MASK_DEB_STS                            ((u32)0x0000FFFF << 0)                              /*!<R 0  For each bit: 0: the specific GPIO debounce pin is DISABLE debounce 1: the specific GPIO debounce pin is ENABLE debounce */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB_EN
 * @brief  GPIO debounce pin enable                  (@ 0X0F4)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_EN                            0
#define GPIO_MASK_DEB_EN                             ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO de-bouncing pin is enabled and also cause the specified bit of REG_GPIO_DEB_STS to be read as ONE. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB_DIS
 * @brief  GPIO debounce pin disable                 (@ 0X0F8)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_DIS                           0
#define GPIO_MASK_DEB_DIS                            ((u32)0x0000FFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO de-bouncing pin is disabled and also cause the specified bit of REG_GPIO_DEB_STS to be read as ZERO. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB_DP_STS
 * @brief  GPIO debounce data pin status             (@ 0X0FC)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_DP_STS                        0
#define GPIO_MASK_DEB_DP_STS                         ((u32)0x0000FFFF << 0)                              /*!<R 0  For each bit reading: read the signal level of the specified pin after de-bounce */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB0_SEL
 * @brief  GPIO debounce0 selection                  (@ 0X100)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce0 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce0 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB1_SEL
 * @brief  GPIO debounce1 selection                  (@ 0X104)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce1 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce1 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB2_SEL
 * @brief  GPIO debounce2 selection                  (@ 0X108)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce2 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce2 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB3_SEL
 * @brief  GPIO debounce3 selection                  (@ 0X10C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce3 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce3 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB4_SEL
 * @brief  GPIO debounce4 selection                  (@ 0X110)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce4 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce4 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB5_SEL
 * @brief  GPIO debounce5 selection                  (@ 0X114)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce5 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce5 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB6_SEL
 * @brief  GPIO debounce6 selection                  (@ 0X118)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce6 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce6 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB7_SEL
 * @brief  GPIO debounce7 selection                  (@ 0X11C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce7 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce7 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB8_SEL
 * @brief  GPIO debounce8 selection                  (@ 0X120)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce8 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce8 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB9_SEL
 * @brief  GPIO debounce9 selection                  (@ 0X124)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce9 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce9 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB10_SEL
 * @brief  GPIO debounce10 selection                 (@ 0X128)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce10 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce10 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB11_SEL
 * @brief  GPIO debounce11 selection                 (@ 0X12C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce11 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce11 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB12_SEL
 * @brief  GPIO debounce12 selection                 (@ 0X130)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce12 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce12 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB13_SEL
 * @brief  GPIO debounce13 selection                 (@ 0X134)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce13 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce13 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB14_SEL
 * @brief  GPIO debounce14 selection                 (@ 0X138)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce14 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce14 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_DEB15_SEL
 * @brief  GPIO debounce15 selection                 (@ 0X13C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DEB_CYC                           8
#define GPIO_MASK_DEB_CYC                            ((u32)0x00003FFF << 8)                              /*!<R/W 0  The GPIO signal will be filtered by the number of debounce cycles given in this field. */
#define GPIO_SHIFT_DEB_GP_SEL                        5
#define GPIO_MASK_DEB_GP_SEL                         ((u32)0x00000003 << 5)                              /*!<R/W 0  GPIO port selection for debounce15 */
#define GPIO_SHIFT_DEB_MER_SEL                       0
#define GPIO_MASK_DEB_MER_SEL                        ((u32)0x0000001F << 0)                              /*!<R/W 0  Pin selection of specified port for debounce15 */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_A_DMD_STS
 * @brief  GPIO port A data mode direction status    (@ 0X200)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DMD_STS                           0
#define GPIO_MASK_DMD_STS                            ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit: 0: the specific GPIO pin is configured to INPUT data mode 1: the specific GPIO pin is configured to OUTPUT data mode */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_A_IDM_EN
 * @brief  GPIO port A input data mode enable        (@ 0X204)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_IDM_EN                            0
#define GPIO_MASK_IDM_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: the configuration of the conrtolled GPIO pin is unchanged; 1: the conrtolled GPIO pin is configured to input data mode and also cause the specified bit of REG_PORT_A_DMD_STS to be read as zero. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_A_ODM_EN
 * @brief  GPIO port A output data mode enable       (@ 0X208)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODM_EN                            0
#define GPIO_MASK_ODM_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: the configuration of conrtolled GPIO pin is unchanged; 1: the conrtolled GPIO pin is configured as output data mode and also cause the specified bit of REG_PORT_A_DMD_STS to be read as one */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_A_OD_STS
 * @brief  GPIO port A output data status            (@ 0X20C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_OD_STS                            0
#define GPIO_MASK_OD_STS                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit: 0: the specified GPIO pin is configured as output low 1: the specified GPIO pin is configured as output high , if the specific GPIO pin is output data mode. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_A_ODL_EN
 * @brief  GPIO port A output data low enable        (@ 0X210)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODL_EN                            0
#define GPIO_MASK_ODL_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO pin is configured as output low and also cause the specified bit of REG_PORT_A_OD_STS is zero. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_A_ODH_EN
 * @brief  GPIO port A output data high enable       (@ 0X214)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODH_EN                            0
#define GPIO_MASK_ODH_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO pin is configured as output high and also cause the specified bit of REG_PORT_A_OD_STS is one. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_A_ODT_EN
 * @brief  GPIO port A output data toggle enable     (@ 0X218)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODT_EN                            0
#define GPIO_MASK_ODT_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: Toggle output of the conrtolled GPIO pin and the specified bit of REG_PORT_A_OD_STS also will be toggled. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_A_DP_STS
 * @brief  GPIO port A data pin status               (@ 0X21C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DP_STS                            0
#define GPIO_MASK_DP_STS                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit reading: If the direction of the specified bit is input then read the signal level of the input pin. If the direction of the specified bit is output then reads the output data register for port A. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_B_DMD_STS
 * @brief  GPIO port B data mode direction status    (@ 0X240)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DMD_STS                           0
#define GPIO_MASK_DMD_STS                            ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit: 0: the specific GPIO pin is configured to INPUT data mode 1: the specific GPIO pin is configured to OUTPUT data mode */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_B_IDM_EN
 * @brief  GPIO port B input data mode enable        (@ 0X244)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_IDM_EN                            0
#define GPIO_MASK_IDM_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: the configuration of the conrtolled GPIO pin is unchanged; 1: the conrtolled GPIO pin is configured to input data mode and also cause the specified bit of REG_PORT_B_DMD_STS to be read as zero. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_B_ODM_EN
 * @brief  GPIO port B output data mode enable       (@ 0X248)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODM_EN                            0
#define GPIO_MASK_ODM_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: the configuration of the conrtolled GPIO pin is unchanged; 1: the conrtolled GPIO pin is configured as output data mode and also cause the specified bit of REG_PORT_B_DMD_STS to be read as one */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_B_OD_STS
 * @brief  GPIO port B output data status            (@ 0X24C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_OD_STS                            0
#define GPIO_MASK_OD_STS                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit: 0: the specified GPIO pin is configured as output low 1: the specified GPIO pin is configured as output high , if the specific GPIO pin is output data mode. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_B_ODL_EN
 * @brief  GPIO port B output data low enable        (@ 0X250)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODL_EN                            0
#define GPIO_MASK_ODL_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO pin is configured as output low and also cause the specified bit of REG_PORT_B_OD_STS is zero. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_B_ODH_EN
 * @brief  GPIO port B output data high enable       (@ 0X254)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODH_EN                            0
#define GPIO_MASK_ODH_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO pin is configured as output high and also cause the specified bit of REG_PORT_B_OD_STS is one. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_B_ODT_EN
 * @brief  GPIO port B output data toggle enable     (@ 0X258)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODT_EN                            0
#define GPIO_MASK_ODT_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: Toggle output of the conrtolled GPIO pin and the specified bit of REG_PORT_B_OD_STS also will be toggled. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_B_DP_STS
 * @brief  GPIO port B data pin status               (@ 0X25C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DP_STS                            0
#define GPIO_MASK_DP_STS                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit reading: If the direction of the specified bit is input then read the signal level of the input pin. If the direction of the specified bit is output then reads the output data register for port B. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_C_DMD_STS
 * @brief  GPIO port C data mode direction status    (@ 0X280)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DMD_STS                           0
#define GPIO_MASK_DMD_STS                            ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit: 0: the specific GPIO pin is configured to INPUT data mode 1: the specific GPIO pin is configured to OUTPUT data mode */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_C_IDM_EN
 * @brief  GPIO port C input data mode enable        (@ 0X284)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_IDM_EN                            0
#define GPIO_MASK_IDM_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: the configuration of the conrtolled GPIO pin is unchanged; 1: the conrtolled GPIO pin is configured to input data mode and also cause the specified bit of REG_PORT_C_DMD_STS to be read as zero. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_C_ODM_EN
 * @brief  GPIO port C output data mode enable       (@ 0X288)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODM_EN                            0
#define GPIO_MASK_ODM_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: the configuration of the conrtolled GPIO pin is unchanged; 1: the conrtolled GPIO pin is configured as output data mode and also cause the specified bit of REG_PORT_C_DMD_STS to be read as one */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_C_OD_STS
 * @brief  GPIO port C output data status            (@ 0X28C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_OD_STS                            0
#define GPIO_MASK_OD_STS                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit: 0: the specified GPIO pin is configured as output low 1: the specified GPIO pin is configured as output high , if the specific GPIO pin is output data mode. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_C_ODL_EN
 * @brief  GPIO port C output data low enable        (@ 0X290)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODL_EN                            0
#define GPIO_MASK_ODL_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO pin is configured as output low and also cause the specified bit of REG_PORT_C_OD_STS is zero. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_C_ODH_EN
 * @brief  GPIO port C output data high enable       (@ 0X294)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODH_EN                            0
#define GPIO_MASK_ODH_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO pin is configured as output high and also cause the specified bit of REG_PORT_C_OD_STS is one. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_C_ODT_EN
 * @brief  GPIO port C output data toggle enable     (@ 0X298)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODT_EN                            0
#define GPIO_MASK_ODT_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: Toggle output of the conrtolled GPIO pin and the specified bit of REG_PORT_C_OD_STS also will be toggled. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_C_DP_STS
 * @brief  GPIO port C data pin status               (@ 0X29C)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DP_STS                            0
#define GPIO_MASK_DP_STS                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit reading: If the direction of the specified bit is input then read the signal level of the input pin. If the direction of the specified bit is output then reads the output data register for port C. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_D_DMD_STS
 * @brief  GPIO port D data mode direction status    (@ 0X2C0)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DMD_STS                           0
#define GPIO_MASK_DMD_STS                            ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit: 0: the specific GPIO pin is configured to INPUT data mode 1: the specific GPIO pin is configured to OUTPUT data mode */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_D_IDM_EN
 * @brief  GPIO port D input data mode enable        (@ 0X2C4)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_IDM_EN                            0
#define GPIO_MASK_IDM_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: the configuration of the conrtolled GPIO pin is unchanged; 1: the conrtolled GPIO pin is configured to input data mode and also cause the specified bit of REG_PORT_D_DMD_STS to be read as zero. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_D_ODM_EN
 * @brief  GPIO port D output data mode enable       (@ 0X2C8)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODM_EN                            0
#define GPIO_MASK_ODM_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: the configuration of the conrtolled GPIO pin is unchanged; 1: the conrtolled GPIO pin is configured as output data mode and also cause the specified bit of REG_PORT_D_DMD_STS to be read as one */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_D_OD_STS
 * @brief  GPIO port D output data status            (@ 0X2CC)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_OD_STS                            0
#define GPIO_MASK_OD_STS                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit: 0: the specified GPIO pin is configured as output low 1: the specified GPIO pin is configured as output high , if the specific GPIO pin is output data mode. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_D_ODL_EN
 * @brief  GPIO port D output data low enable        (@ 0X2D0)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODL_EN                            0
#define GPIO_MASK_ODL_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO pin is configured as output low and also cause the specified bit of REG_PORT_D_OD_STS is zero. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_D_ODH_EN
 * @brief  GPIO port D output data high enable       (@ 0X2D4)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODH_EN                            0
#define GPIO_MASK_ODH_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: the conrtolled GPIO pin is configured as output high and also cause the specified bit of REG_PORT_D_OD_STS is one. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_D_ODT_EN
 * @brief  GPIO port D output data toggle enable     (@ 0X2D8)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_ODT_EN                            0
#define GPIO_MASK_ODT_EN                             ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  For each bit write: 0: No operation 1: Toggle output of the conrtolled GPIO pin and the specified bit of REG_PORT_D_OD_STS also will be toggled. */
/** @} */

/**************************************************************************//**
 * @defgroup GPIO_PORT_D_DP_STS
 * @brief  GPIO port D data pin status               (@ 0X2DC)
 * @{
 *****************************************************************************/
#define GPIO_SHIFT_DP_STS                            0
#define GPIO_MASK_DP_STS                             ((u32)0xFFFFFFFF << 0)                              /*!<R 0  For each bit reading: If the direction of the specified bit is input then read the signal level of the input pin. If the direction of the specified bit is output then reads the output data register for port D. */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_GPIO
 * @{
 * @brief rtl8735b_GPIO Register Declaration
 *****************************************************************************/
typedef struct {
	__I  uint32_t GPIO_IT_STS ;                            /*!<  GPIO interrupt type status Register register,  Address offset: 0x000 */
	__IO uint32_t GPIO_EI_EN ;                             /*!<  GPIO edge sensitive interrupt mode enable register,  Address offset: 0x004 */
	__IO uint32_t GPIO_LI_EN ;                             /*!<  GPIO level sensitive interrupt mode enable register,  Address offset: 0x008 */
	__I  uint32_t GPIO_IP_STS ;                            /*!<  GPIO interrupt polarity status register,  Address offset: 0x00C */
	__IO uint32_t RSVD0;                                  /*!<  Reserved,  Address offset:0x10 */
	__IO uint32_t GPIO_IR_EN ;                             /*!<  GPIO interrupt rising-edge enable register,  Address offset: 0x014 */
	__IO uint32_t GPIO_IF_EN ;                             /*!<  GPIO interrupt falling-edge enable register,  Address offset: 0x018 */
	__IO uint32_t GPIO_ID_EN ;                             /*!<  GPIO interrupt dual-edge enable register,  Address offset: 0x01C */
	__I  uint32_t GPIO_IE_STS ;                            /*!<  GPIO interrupt enable status register,  Address offset: 0x020 */
	__IO uint32_t GPIO_INT_EN ;                            /*!<  GPIO interrupt enable register,  Address offset: 0x024 */
	__IO uint32_t GPIO_INT_DIS ;                           /*!<  GPIO interrupt disable register,  Address offset: 0x028 */
	__I  uint32_t GPIO_INT_RAW_STS ;                       /*!<  GPIO RAW interrupt status register,  Address offset: 0x02C */
	__I  uint32_t GPIO_INT_STS ;                           /*!<  GPIO interrupt status register,  Address offset: 0x030 */
	__IO uint32_t GPIO_INT_CLR ;                           /*!<  GPIO interrupt status clear register,  Address offset: 0x034 */
	__I  uint32_t GPIO_INT_FUNC_EN_STS ;                   /*!<  GPIO interrupt function enable status register,  Address offset: 0x038 */
	__IO uint32_t GPIO_INT_FUNC_EN ;                       /*!<  GPIO interrupt function enable register,  Address offset: 0x03C */
	__IO uint32_t GPIO_INT_FUNC_DIS ;                      /*!<  GPIO interrupt function disable register,  Address offset: 0x040 */
	__IO uint32_t RSVD1[3];                                /*!<  Reserved,  Address offset:0x44-0x4C */
	__IO uint32_t GPIO_INT0_SEL ;                          /*!<  GPIO INT0 selection register,  Address offset: 0x050 */
	__IO uint32_t GPIO_INT1_SEL ;                          /*!<  GPIO INT1 selection register,  Address offset: 0x054 */
	__IO uint32_t GPIO_INT2_SEL ;                          /*!<  GPIO INT2 selection register,  Address offset: 0x058 */
	__IO uint32_t GPIO_INT3_SEL ;                          /*!<  GPIO INT3 selection register,  Address offset: 0x05C */
	__IO uint32_t GPIO_INT4_SEL ;                          /*!<  GPIO INT4 selection register,  Address offset: 0x060 */
	__IO uint32_t GPIO_INT5_SEL ;                          /*!<  GPIO INT5 selection register,  Address offset: 0x064 */
	__IO uint32_t GPIO_INT6_SEL ;                          /*!<  GPIO INT6 selection register,  Address offset: 0x068 */
	__IO uint32_t GPIO_INT7_SEL ;                          /*!<  GPIO INT7 selection register,  Address offset: 0x06C */
	__IO uint32_t GPIO_INT8_SEL ;                          /*!<  GPIO INT8 selection register,  Address offset: 0x070 */
	__IO uint32_t GPIO_INT9_SEL ;                          /*!<  GPIO INT9 selection register,  Address offset: 0x074 */
	__IO uint32_t GPIO_INT10_SEL ;                         /*!<  GPIO INT10 selection register,  Address offset: 0x078 */
	__IO uint32_t GPIO_INT11_SEL ;                         /*!<  GPIO INT11 selection register,  Address offset: 0x07C */
	__IO uint32_t GPIO_INT12_SEL ;                         /*!<  GPIO INT12 selection register,  Address offset: 0x080 */
	__IO uint32_t GPIO_INT13_SEL ;                         /*!<  GPIO INT13 selection register,  Address offset: 0x084 */
	__IO uint32_t GPIO_INT14_SEL ;                         /*!<  GPIO INT14 selection register,  Address offset: 0x088 */
	__IO uint32_t GPIO_INT15_SEL ;                         /*!<  GPIO INT15 selection register,  Address offset: 0x08C */
	__IO uint32_t RSVD2[24];                               /*!<  Reserved,  Address offset:0x90-0xEC */
	__I  uint32_t GPIO_DEB_STS ;                           /*!<  GPIO port debounce status register,  Address offset: 0x0F0 */
	__IO uint32_t GPIO_DEB_EN ;                            /*!<  GPIO debounce pin enable register,  Address offset: 0x0F4 */
	__IO uint32_t GPIO_DEB_DIS ;                           /*!<  GPIO debounce pin disable register,  Address offset: 0x0F8 */
	__I  uint32_t GPIO_DEB_DP_STS ;                        /*!<  GPIO debounce data pin status register,  Address offset: 0x0FC */
	__IO uint32_t GPIO_DEB0_SEL ;                          /*!<  GPIO debounce0 selection register,  Address offset: 0x100 */
	__IO uint32_t GPIO_DEB1_SEL ;                          /*!<  GPIO debounce1 selection register,  Address offset: 0x104 */
	__IO uint32_t GPIO_DEB2_SEL ;                          /*!<  GPIO debounce2 selection register,  Address offset: 0x108 */
	__IO uint32_t GPIO_DEB3_SEL ;                          /*!<  GPIO debounce3 selection register,  Address offset: 0x10C */
	__IO uint32_t GPIO_DEB4_SEL ;                          /*!<  GPIO debounce4 selection register,  Address offset: 0x110 */
	__IO uint32_t GPIO_DEB5_SEL ;                          /*!<  GPIO debounce5 selection register,  Address offset: 0x114 */
	__IO uint32_t GPIO_DEB6_SEL ;                          /*!<  GPIO debounce6 selection register,  Address offset: 0x118 */
	__IO uint32_t GPIO_DEB7_SEL ;                          /*!<  GPIO debounce7 selection register,  Address offset: 0x11C */
	__IO uint32_t GPIO_DEB8_SEL ;                          /*!<  GPIO debounce8 selection register,  Address offset: 0x120 */
	__IO uint32_t GPIO_DEB9_SEL ;                          /*!<  GPIO debounce9 selection register,  Address offset: 0x124 */
	__IO uint32_t GPIO_DEB10_SEL ;                         /*!<  GPIO debounce10 selection register,  Address offset: 0x128 */
	__IO uint32_t GPIO_DEB11_SEL ;                         /*!<  GPIO debounce11 selection register,  Address offset: 0x12C */
	__IO uint32_t GPIO_DEB12_SEL ;                         /*!<  GPIO debounce12 selection register,  Address offset: 0x130 */
	__IO uint32_t GPIO_DEB13_SEL ;                         /*!<  GPIO debounce13 selection register,  Address offset: 0x134 */
	__IO uint32_t GPIO_DEB14_SEL ;                         /*!<  GPIO debounce14 selection register,  Address offset: 0x138 */
	__IO uint32_t GPIO_DEB15_SEL ;                         /*!<  GPIO debounce15 selection register,  Address offset: 0x13C */
	__IO uint32_t RSVD3[48];                               /*!<  Reserved,  Address offset:0x140-0x1FC */
	__I  uint32_t GPIO_PORT_A_DMD_STS ;                    /*!<  GPIO port A data mode direction status register,  Address offset: 0x200 */
	__IO uint32_t GPIO_PORT_A_IDM_EN ;                     /*!<  GPIO port A input data mode enable register,  Address offset: 0x204 */
	__IO uint32_t GPIO_PORT_A_ODM_EN ;                     /*!<  GPIO port A output data mode enable register,  Address offset: 0x208 */
	__I  uint32_t GPIO_PORT_A_OD_STS ;                     /*!<  GPIO port A output data status register,  Address offset: 0x20C */
	__IO uint32_t GPIO_PORT_A_ODL_EN ;                     /*!<  GPIO port A output data low enable register,  Address offset: 0x210 */
	__IO uint32_t GPIO_PORT_A_ODH_EN ;                     /*!<  GPIO port A output data high enable register,  Address offset: 0x214 */
	__IO uint32_t GPIO_PORT_A_ODT_EN ;                     /*!<  GPIO port A output data toggle enable register,  Address offset: 0x218 */
	__I  uint32_t GPIO_PORT_A_DP_STS ;                     /*!<  GPIO port A data pin status register,  Address offset: 0x21C */
	__IO uint32_t RSVD4[8];                                /*!<  Reserved,  Address offset:0x220-0x23C */
	__I  uint32_t GPIO_PORT_B_DMD_STS ;                    /*!<  GPIO port B data mode direction status register,  Address offset: 0x240 */
	__IO uint32_t GPIO_PORT_B_IDM_EN ;                     /*!<  GPIO port B input data mode enable register,  Address offset: 0x244 */
	__IO uint32_t GPIO_PORT_B_ODM_EN ;                     /*!<  GPIO port B output data mode enable register,  Address offset: 0x248 */
	__I  uint32_t GPIO_PORT_B_OD_STS ;                     /*!<  GPIO port B output data status register,  Address offset: 0x24C */
	__IO uint32_t GPIO_PORT_B_ODL_EN ;                     /*!<  GPIO port B output data low enable register,  Address offset: 0x250 */
	__IO uint32_t GPIO_PORT_B_ODH_EN ;                     /*!<  GPIO port B output data high enable register,  Address offset: 0x254 */
	__IO uint32_t GPIO_PORT_B_ODT_EN ;                     /*!<  GPIO port B output data toggle enable register,  Address offset: 0x258 */
	__I  uint32_t GPIO_PORT_B_DP_STS ;                     /*!<  GPIO port B data pin status register,  Address offset: 0x25C */
	__IO uint32_t RSVD5[8];                                /*!<  Reserved,  Address offset:0x260-0x27C */
	__I  uint32_t GPIO_PORT_C_DMD_STS ;                    /*!<  GPIO port C data mode direction status register,  Address offset: 0x280 */
	__IO uint32_t GPIO_PORT_C_IDM_EN ;                     /*!<  GPIO port C input data mode enable register,  Address offset: 0x284 */
	__IO uint32_t GPIO_PORT_C_ODM_EN ;                     /*!<  GPIO port C output data mode enable register,  Address offset: 0x288 */
	__I  uint32_t GPIO_PORT_C_OD_STS ;                     /*!<  GPIO port C output data status register,  Address offset: 0x28C */
	__IO uint32_t GPIO_PORT_C_ODL_EN ;                     /*!<  GPIO port C output data low enable register,  Address offset: 0x290 */
	__IO uint32_t GPIO_PORT_C_ODH_EN ;                     /*!<  GPIO port C output data high enable register,  Address offset: 0x294 */
	__IO uint32_t GPIO_PORT_C_ODT_EN ;                     /*!<  GPIO port C output data toggle enable register,  Address offset: 0x298 */
	__I  uint32_t GPIO_PORT_C_DP_STS ;                     /*!<  GPIO port C data pin status register,  Address offset: 0x29C */
	__IO uint32_t RSVD6[8];                                /*!<  Reserved,  Address offset:0x2A0-0x2BC */
	__I  uint32_t GPIO_PORT_D_DMD_STS ;                    /*!<  GPIO port D data mode direction status register,  Address offset: 0x2C0 */
	__IO uint32_t GPIO_PORT_D_IDM_EN ;                     /*!<  GPIO port D input data mode enable register,  Address offset: 0x2C4 */
	__IO uint32_t GPIO_PORT_D_ODM_EN ;                     /*!<  GPIO port D output data mode enable register,  Address offset: 0x2C8 */
	__I  uint32_t GPIO_PORT_D_OD_STS ;                     /*!<  GPIO port D output data status register,  Address offset: 0x2CC */
	__IO uint32_t GPIO_PORT_D_ODL_EN ;                     /*!<  GPIO port D output data low enable register,  Address offset: 0x2D0 */
	__IO uint32_t GPIO_PORT_D_ODH_EN ;                     /*!<  GPIO port D output data high enable register,  Address offset: 0x2D4 */
	__IO uint32_t GPIO_PORT_D_ODT_EN ;                     /*!<  GPIO port D output data toggle enable register,  Address offset: 0x2D8 */
	__I  uint32_t GPIO_PORT_D_DP_STS ;                     /*!<  GPIO port D data pin status register,           Address offset: 0x2DC */
} GPIO_TypeDef;
/** @} */

#endif
