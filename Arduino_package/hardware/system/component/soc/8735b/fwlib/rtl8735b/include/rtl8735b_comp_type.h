#ifndef _RTL8735B_COMP_TYPE_H_
#define _RTL8735B_COMP_TYPE_H_

/**************************************************************************//**
 * @defgroup COMP_REF_CH0
 * @brief  Comparator Channel 0 Reference Volatage Register (@ 0X000)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_COMP_REF_SEL                      31
#define COMP_BIT_COMP_REF_SEL                        ((u32)0x00000001 << 31)                             /*!<R/W 0  0:Comparator, 1: SEL_VREFL[4:0] and SEL_VREFH[4:0] */
#define COMP_SHIFT_REF1                              16
#define COMP_MASK_REF1                               ((u32)0x0000003F << 16)                             /*!<R/W 0x00  This bit controls the comparator channel 0 internal reference voltage 1. Vref1 is equal to (the value of BIT_COMP_REF1+1) * 0.1V. Therefore, when BIT_COMP_REF1 is 5, Vref1 is 0.6V. When BIT_COMP_REF1 is 30, Vref1 is 3.1V. 0x00: Vref1 is 0.1V. 0x01: Vref1 is 0.2V. 0x02: Vref1 is 0.3V . . . */
#define COMP_SHIFT_REF0                              0
#define COMP_MASK_REF0                               ((u32)0x0000003F << 0)                              /*!<R/W 0x00  This bit controls the comparator channel 0 internal reference voltage 0. Vref0 is equal to (the value of BIT_COMP_REF0+1) * 0.1V. Therefore, when BIT_COMP_REF0 is 5, Vref0 is 0.6V. When BIT_COMP_REF0 is 30, Vref0 is 3.1V. 0x00: Vref0 is 0.1V. 0x01: Vref0 is 0.2V. 0x02: Vref0 is 0.3V . . . */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_REF_CH1
 * @brief  Comparator Channel 1 Reference Volatage Register (@ 0X004)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_REF1                              16
#define COMP_MASK_REF1                               ((u32)0x0000003F << 16)                             /*!<R/W 0x00  This bit controls the comparator channel 0 internal reference voltage 1. Vref1 is equal to (the value of BIT_COMP_REF1+1) * 0.1V. Therefore, when BIT_COMP_REF1 is 5, Vref1 is 0.6V. When BIT_COMP_REF1 is 30, Vref1 is 3.1V. 0x00: Vref1 is 0.1V. 0x01: Vref1 is 0.2V. 0x02: Vref1 is 0.3V . . . */
#define COMP_SHIFT_REF0                              0
#define COMP_MASK_REF0                               ((u32)0x0000003F << 0)                              /*!<R/W 0x00  This bit controls the comparator channel 0 internal reference voltage 0. Vref0 is equal to (the value of BIT_COMP_REF0+1) * 0.1V. Therefore, when BIT_COMP_REF0 is 5, Vref0 is 0.6V. When BIT_COMP_REF0 is 30, Vref0 is 3.1V. 0x00: Vref0 is 0.1V. 0x01: Vref0 is 0.2V. 0x02: Vref0 is 0.3V . . . */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_REF_CH2
 * @brief  Comparator Channel 2 Reference Volatage Register (@ 0X008)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_REF1                              16
#define COMP_MASK_REF1                               ((u32)0x0000003F << 16)                             /*!<R/W 0x00  This bit controls the comparator channel 0 internal reference voltage 1. Vref1 is equal to (the value of BIT_COMP_REF1+1) * 0.1V. Therefore, when BIT_COMP_REF1 is 5, Vref1 is 0.6V. When BIT_COMP_REF1 is 30, Vref1 is 3.1V. 0x00: Vref1 is 0.1V. 0x01: Vref1 is 0.2V. 0x02: Vref1 is 0.3V . . . */
#define COMP_SHIFT_REF0                              0
#define COMP_MASK_REF0                               ((u32)0x0000003F << 0)                              /*!<R/W 0x00  This bit controls the comparator channel 0 internal reference voltage 0. Vref0 is equal to (the value of BIT_COMP_REF0+1) * 0.1V. Therefore, when BIT_COMP_REF0 is 5, Vref0 is 0.6V. When BIT_COMP_REF0 is 30, Vref0 is 3.1V. 0x00: Vref0 is 0.1V. 0x01: Vref0 is 0.2V. 0x02: Vref0 is 0.3V . . . */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_REF_CH3
 * @brief  Comparator Channel 3 Reference Volatage Register (@ 0X00C)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_REF1                              16
#define COMP_MASK_REF1                               ((u32)0x0000003F << 16)                             /*!<R/W 0x00  This bit controls the comparator channel 0 internal reference voltage 1. Vref1 is equal to (the value of BIT_COMP_REF1+1) * 0.1V. Therefore, when BIT_COMP_REF1 is 5, Vref1 is 0.6V. When BIT_COMP_REF1 is 30, Vref1 is 3.1V. 0x00: Vref1 is 0.1V. 0x01: Vref1 is 0.2V. 0x02: Vref1 is 0.3V . . . */
#define COMP_SHIFT_REF0                              0
#define COMP_MASK_REF0                               ((u32)0x0000003F << 0)                              /*!<R/W 0x00  This bit controls the comparator channel 0 internal reference voltage 0. Vref0 is equal to (the value of BIT_COMP_REF0+1) * 0.1V. Therefore, when BIT_COMP_REF0 is 5, Vref0 is 0.6V. When BIT_COMP_REF0 is 30, Vref0 is 3.1V. 0x00: Vref0 is 0.1V. 0x01: Vref0 is 0.2V. 0x02: Vref0 is 0.3V . . . */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_INTR_CTRL
 * @brief  Comparator Interrupt Control Register     (@ 0X010)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_WK_SYS_CTRL_3                     26
#define COMP_MASK_WK_SYS_CTRL_3                      ((u32)0x00000003 << 26)                             /*!<R/W 0  This bit defines the criterion of when comparator channel 3 should interrupts (wake up) system. The comparator should send wakeup signal only when BIT_COMP_WK_SYS_EN is 1, if the criterion matches. 0: When Vin < Vref0, the comparator interrupts (wake up) system. 1: When Vin > Vref1, the Comparator interrupts (wake up) system. 2: When Vin > Vref0 and Vin < Vref1, the Comparator interrupts (wake up) system. 3: When Vin < Vref0 or Vin > Vref1, the Comparator interrupts (wake up) system. */
#define COMP_SHIFT_WK_SYS_EN_3                       25
#define COMP_BIT_WK_SYS_EN_3                         ((u32)0x00000001 << 25)                             /*!<R/W 0  This bit controls whether the comparator channel 3 sends interrupt (wake up) signal or not when the criterion of BIT_COMP_WK_SYS_CTRL matches. 0: Disable comparator interrupt (wake up) system. 1: Enable comparator interrupt (wake up) system. */
#define COMP_SHIFT_WK_SYS_CTRL_2                     23
#define COMP_MASK_WK_SYS_CTRL_2                      ((u32)0x00000003 << 23)                             /*!<R/W 0  This bit defines the criterion of when comparator channel 2 should interrupt (wake up) system. The comparator should send wakeup signal only when BIT_COMP_WK_SYS_EN is 1, if the criterion matches. 0: When Vin < Vref0, the comparator interrupts (wake up) system. 1: When Vin >= Vref1, the Comparator interrupts (wake up) system. 2: When Vin > Vref0 and Vin < Vref1, the Comparator interrupts (wake up) system. 3: When Vin < Vref0 or Vin > Vref1, the Comparator interrupts (wake up) system. */
#define COMP_SHIFT_WK_SYS_EN_2                       22
#define COMP_BIT_WK_SYS_EN_2                         ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit controls whether the comparator channel 2 sends interrupt (wake up) signal or not when the criterion of BIT_COMP_WK_SYS_CTRL matches. 0: Disable comparator interrupt (wake up) system. 1: Enable comparator interrupt (wake up) system. */
#define COMP_SHIFT_WK_SYS_CTRL_1                     20
#define COMP_MASK_WK_SYS_CTRL_1                      ((u32)0x00000003 << 20)                             /*!<R/W 0  This bit defines the criterion of when comparator channel 1 should interrupt (wake up) system. The comparator should send wakeup signal only when BIT_COMP_WK_SYS_EN is 1, if the criterion matches. 0: When Vin < Vref0, the comparator interrupt (wake up) system. 1: When Vin > Vref1, the Comparator interrupt (wake up) system. 2: When Vin > Vref0 and Vin < Vref1, the Comparator interrupts (wake up) system. 3: When Vin < Vref0 or Vin > Vref1, the Comparator interrupts (wake up) system. */
#define COMP_SHIFT_WK_SYS_EN_1                       19
#define COMP_BIT_WK_SYS_EN_1                         ((u32)0x00000001 << 19)                             /*!<R/W 0  This bit controls whether the comparator channel 1 sends interrupt (wake up) signal or not when the criterion of BIT_COMP_WK_SYS_CTRL matches. 0: Disable comparator interrupt (wake up) system. 1: Enable comparator interrupt (wake up) system. */
#define COMP_SHIFT_WK_SYS_CTRL_0                     17
#define COMP_MASK_WK_SYS_CTRL_0                      ((u32)0x00000003 << 17)                             /*!<R/W 0  This bit defines the criterion of when comparator channel 0 should interrupt (wake up) system. The comparator should send wakeup signal only when BIT_COMP_WK_SYS_EN is 1, if the criterion matches. 0: When Vin < Vref0, the comparator interrupts (wake up) system. 1: When Vin > Vref1, the Comparator interrupts (wake up) system. 2: When Vin > Vref0 and Vin < Vref1, the Comparator interrupts (wake up) system. 3: When Vin < Vref0 or Vin > Vref1, the Comparator interrupts (wake up) system. */
#define COMP_SHIFT_WK_SYS_EN_0                       16
#define COMP_BIT_WK_SYS_EN_0                         ((u32)0x00000001 << 16)                             /*!<R/W 0  This bit controls whether the comparator channel 0 sends wakeup signal or not when the criterion of BIT_COMP_WK_SYS_CTRL matches. 0: Disable comparator interrupt (wake up) system. 1: Enable comparator interrupt (wake up) system. */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_INTR_STS
 * @brief  Comparator Interrupt Status Register      (@ 0X014)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_WK_SYS_STS_3                      25
#define COMP_BIT_WK_SYS_STS_3                        ((u32)0x00000001 << 25)                             /*!<R/W1C 0  This bit reflects if channle 3 of comparator module sent a interrupt (wake-up) signal to system or not. 0: Channel 3 did NOT send an interrupt (wake-up) signal to System. 1: Channel 3 has sent an interrupt (wake-up) signal to System. */
#define COMP_SHIFT_WK_SYS_STS_2                      22
#define COMP_BIT_WK_SYS_STS_2                        ((u32)0x00000001 << 22)                             /*!<R/W1C 0  This bit reflects if channle 2 of comparator module sent a interrupt (wake-up) signal to system or not. 0: Channel 2 did NOT send an interrupt (wake-up) signal to System. 1: Channel 2 has sent an interrupt (wake-up) signal to System. */
#define COMP_SHIFT_WK_SYS_STS_1                      19
#define COMP_BIT_WK_SYS_STS_1                        ((u32)0x00000001 << 19)                             /*!<R/W1C 0  This bit reflects if channle 1 of comparator module sent a interrupt (wake-up) signal to system or not. 0: Channel 1 did NOT send an interrupt (wake-up) signal to System. 1: Channel 1 has sent an interrupt (wake-up) signal to System. */
#define COMP_SHIFT_WK_SYS_STS_0                      16
#define COMP_BIT_WK_SYS_STS_0                        ((u32)0x00000001 << 16)                             /*!<R/W1C 0  This bit reflects if channle 0 of comparator module sent a interrupt (wake-up) signal to system or not. 0: Channel 0 did NOT send an interrupt (wake-up) signal to System. 1: Channel 0 has sent an interrupt (wake-up) signal to System. */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_INTR_RAW_STS
 * @brief  Comparator Interrupt RAW Status Register  (@ 0X018)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_WK_SYS_STS_3                      25
#define COMP_BIT_WK_SYS_STS_3                        ((u32)0x00000001 << 25)                             /*!<R 0  This bit reflects if channle 3 of comparator module sent a interrupt (wake-up) signal to system or not. 0: Channel 3 did NOT send an interrupt (wake-up) signal to System. 1: Channel 3 has sent an interrupt (wake-up) signal to System. */
#define COMP_SHIFT_WK_SYS_STS_2                      22
#define COMP_BIT_WK_SYS_STS_2                        ((u32)0x00000001 << 22)                             /*!<R 0  This bit reflects if channle 2 of comparator module sent a interrupt (wake-up) signal to system or not. 0: Channel 2 did NOT send an interrupt (wake-up) signal to System. 1: Channel 2 has sent an interrupt (wake-up) signal to System. */
#define COMP_SHIFT_WK_SYS_STS_1                      19
#define COMP_BIT_WK_SYS_STS_1                        ((u32)0x00000001 << 19)                             /*!<R 0  This bit reflects if channle 1 of comparator module sent a interrupt (wake-up) signal to system or not. 0: Channel 1 did NOT send an interrupt (wake-up) signal to System. 1: Channel 1 has sent an interrupt (wake-up) signal to System. */
#define COMP_SHIFT_WK_SYS_STS_0                      16
#define COMP_BIT_WK_SYS_STS_0                        ((u32)0x00000001 << 16)                             /*!<R 0  This bit reflects if channle 0 of comparator module sent a interrupt (wake-up) signal to system or not. 0: Channel 0 did NOT send an interrupt (wake-up) signal to System. 1: Channel 0 has sent an interrupt (wake-up) signal to System. */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_ITEMSW_LIST
 * @brief  Comparator Item Switch List Register      (@ 0X01C)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_ITEMSW_3                          12
#define COMP_MASK_ITEMSW_3                           ((u32)0x0000000F << 12)                             /*!<R/W 0  These bits defines which comparator Channel start comparison at the 4th item to do */
#define COMP_SHIFT_ITEMSW_2                          8
#define COMP_MASK_ITEMSW_2                           ((u32)0x0000000F << 8)                              /*!<R/W 0  These bits defines which comparator Channel start comparison at the 3rd item to do */
#define COMP_SHIFT_ITEMSW_1                          4
#define COMP_MASK_ITEMSW_1                           ((u32)0x0000000F << 4)                              /*!<R/W 0  These bits defines which comparator Channel start comparison at the 2nd item to do */
#define COMP_SHIFT_ITEMSW_0                          0
#define COMP_MASK_ITEMSW_0                           ((u32)0x0000000F << 0)                              /*!<R/W 0  These bits defines which comparator Channel start comparison at the 1st item to do */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_LAST_ITEM
 * @brief  Comparator Last Item Register             (@ 0X020)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_LAST_ITEM                         0
#define COMP_MASK_LAST_ITEM                          ((u32)0x00000003 << 0)                              /*!<R 0  These bits reflects the last used item. The last_item will be round robin from itemsw_0 to itemsw_3 */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_BUSY
 * @brief  Comparator Busy Status Register           (@ 0X024)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_BUSY                              0
#define COMP_BIT_BUSY                                ((u32)0x00000001 << 0)                              /*!<R 0  This bit reflects the comparator is busy or not. If the comparator is processing a comparison of a channel, this bit remains 1 which indicates it's busy. Once a comparison is done, this bit becomes 0 which indicates its' ready to do another comparison. 0: The comparator is ready. 1: The comparator is busy. */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_CH_STS
 * @brief  Comparator Channel Status Register        (@ 0X028)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_CH_STS_3                          6
#define COMP_MASK_CH_STS_3                           ((u32)0x00000003 << 6)                              /*!<R 0  This bit reflects the channel 3 comparison result. 0: When Vin < Vref0, the bits should be set to 0. 1: When Vin >= Vref1, the bits should be set to 1. 2:When Vin > Vref0 and Vin < Vref1, the bits should be set to 2. */
#define COMP_SHIFT_CH_STS_2                          4
#define COMP_MASK_CH_STS_2                           ((u32)0x00000003 << 4)                              /*!<R 0  This bit reflects the channel 2 comparison result. 0: When Vin < Vref0, the bits should be set to 0. 1: When Vin >= Vref1, the bits should be set to 1. 2:When Vin > Vref0 and Vin < Vref1, the bits should be set to 2. */
#define COMP_SHIFT_CH_STS_1                          2
#define COMP_MASK_CH_STS_1                           ((u32)0x00000003 << 2)                              /*!<R 0  This bit reflects the channel 1 comparison result. 0: When Vin < Vref0, the bits should be set to 0. 1: When Vin >= Vref1, the bits should be set to 1. 2:When Vin > Vref0 and Vin < Vref1, the bits should be set to 2. */
#define COMP_SHIFT_CH_STS_0                          0
#define COMP_MASK_CH_STS_0                           ((u32)0x00000003 << 0)                              /*!<R 0  This bit reflects the channel 0 comparison result. 0: When Vin < Vref0, the bits should be set to 0. 1: When Vin >= Vref1, the bits should be set to 1. 2:When Vin > Vref0 and Vin < Vref1, the bits should be set to 2. */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_AUTO_SHUT
 * @brief  Comparator Auto Shutdown Register         (@ 0X02C)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_AUTO_SHUT                         0
#define COMP_BIT_AUTO_SHUT                           ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls the comparator to disable the analog module and mux automatically or not after the analog conversion is done. 0: The analog module and mux will NOT be disabled.The comparator module is always enabled. 1: The analog module and mux will be disabled automatically after the analog conversion is done. */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_WK_TIMER
 * @brief  Comparator Wake Timer Control Reigster    (@ 0X030)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_WK_TIMER                          0
#define COMP_BIT_WK_TIMER                            ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls the external trigger source of general timer enabled or not. If it is enabled, the comparator would execute compare process when the timer event sends to comparator module. 0: Disable external timer trigger 1: Enable external timer trigger */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_WK_TIMER_SEL
 * @brief  Comparator Wake Timer Select Reigster     (@ 0X034)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_WK_TIMER_SEL                      0
#define COMP_MASK_WK_TIMER_SEL                       ((u32)0x00000007 << 0)                              /*!<R/W 0  This three bits defines which timer channel would be used to wake up the comparator. BIT_COMP_EXT_WK_TIMER_SEL is 0: Timer module 0 is used as the comparator external trigger source. 1: Timer module 1 is used as the comparator external trigger source. . . . 7: Timer module 7 is used as the comparator external trigger source. */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_RST_LIST
 * @brief  Comparator Rest List Register             (@ 0X038)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_RST_LIST                          0
#define COMP_BIT_RST_LIST                            ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls to reset the item switch to default state or not. Once this bit is set, the auto/manual channel switch goes to the first item as a default state. This control bit will trigger from 0 to 1 0: Do not reset conversion list to default state. 1: Force last_ittem to itemsw_0. */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_AUTO_SW_EN
 * @brief  Comparator Auto Channel Switch Enable Reigster (@ 0X03C)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_AUTO_SW_EN                        0
#define COMP_BIT_AUTO_SW_EN                          ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls the automatic channel swtich enabled or disabled. If it's disabled, comparator could be run in software or timer trigger mode. 0: Disable the automatic channel switch. 1: Enable the automatic channel switch.  */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_ENABLE
 * @brief  Comparator Enable Control Register        (@ 0X040)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_COMP_DBG_EN                       2
#define COMP_BIT_COMP_DBG_EN                         ((u32)0x00000001 << 2)                              /*!<R/W 0  1:enable debug */
#define COMP_SHIFT_TRIG_EN                           1
#define COMP_BIT_TRIG_EN                             ((u32)0x00000001 << 1)                              /*!<R/W 0  This bit is a mulitple trigger control source. For software trigger (when comparator auto channel switch register (offset: 0x3C) is NOT set and wake timer control is NOT set), this bit is used to be a software trigger source. Each time this bit is set to 1 from 0, it drives comparator to do a channel comparison. For auto trigger, this bit is used to drive comparator to start the auto channel switch operation. */
#define COMP_SHIFT_ENABLE                            0
#define COMP_BIT_ENABLE                              ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit is for comparator enable control. */
/** @} */

/**************************************************************************//**
 * @defgroup COMP_WK_SHUT_CNT
 * @brief  Comparator Shutdown Counter Register      (@ 0X044)
 * @{
 *****************************************************************************/
#define COMP_SHIFT_POWON_CNT                         24
#define COMP_MASK_POWON_CNT                          ((u32)0x000000FF << 24)                             /*!<R/W 0x64  It is time delay between comparator trigger to read and LPSD[0] */
#define COMP_SHIFT_DATA_VALID_CNT                    16
#define COMP_MASK_DATA_VALID_CNT                     ((u32)0x000000FF << 16)                             /*!<R/W 0x6E  Data valid counter after turn on REG0X_LPSD[0] */
#define COMP_SHIFT_CHSW_CNT                          8
#define COMP_MASK_CHSW_CNT                           ((u32)0x000000FF << 8)                              /*!<R/W 0x3C  TBD */
#define COMP_SHIFT_WK_SHUT_CNT                       0
#define COMP_MASK_WK_SHUT_CNT                        ((u32)0x000000FF << 0)                              /*!<R/W 0x96  This eight bits defines how long to disable comparator analog module when an external trigger event is sent to the comparator. The count must include the comparator response time to get a correct compare result. */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_COMP
 * @{
 * @brief rtl8735b_COMP Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t COMP_REF_CH0 ;                           /*!<  Comparator Channel 0 Reference Volatage Register register,  Address offset: 0x000 */
	__IO uint32_t COMP_REF_CH1 ;                           /*!<  Comparator Channel 1 Reference Volatage Register register,  Address offset: 0x004 */
	__IO uint32_t COMP_REF_CH2 ;                           /*!<  Comparator Channel 2 Reference Volatage Register register,  Address offset: 0x008 */
	__IO uint32_t COMP_REF_CH3 ;                           /*!<  Comparator Channel 3 Reference Volatage Register register,  Address offset: 0x00C */
	__IO uint32_t COMP_INTR_CTRL ;                         /*!<  Comparator Interrupt Control Register register,  Address offset: 0x010 */
	__IO uint32_t COMP_INTR_STS ;                          /*!<  Comparator Interrupt Status Register register,  Address offset: 0x014 */
	__I  uint32_t COMP_INTR_RAW_STS ;                      /*!<  Comparator Interrupt RAW Status Register register,  Address offset: 0x018 */
	__IO uint32_t COMP_ITEMSW_LIST ;                       /*!<  Comparator Item Switch List Register register,  Address offset: 0x01C */
	__I  uint32_t COMP_LAST_ITEM ;                         /*!<  Comparator Last Item Register register,  Address offset: 0x020 */
	__I  uint32_t COMP_BUSY ;                              /*!<  Comparator Busy Status Register register,  Address offset: 0x024 */
	__I  uint32_t COMP_CH_STS ;                            /*!<  Comparator Channel Status Register register,  Address offset: 0x028 */
	__IO uint32_t COMP_AUTO_SHUT ;                         /*!<  Comparator Auto Shutdown Register register,  Address offset: 0x02C */
	__IO uint32_t COMP_WK_TIMER ;                          /*!<  Comparator Wake Timer Control Reigster register,  Address offset: 0x030 */
	__IO uint32_t COMP_WK_TIMER_SEL ;                      /*!<  Comparator Wake Timer Select Reigster register,  Address offset: 0x034 */
	__IO uint32_t COMP_RST_LIST ;                          /*!<  Comparator Rest List Register register,  Address offset: 0x038 */
	__IO uint32_t COMP_AUTO_SW_EN ;                        /*!<  Comparator Auto Channel Switch Enable Reigster register,  Address offset: 0x03C */
	__IO uint32_t COMP_ENABLE ;                            /*!<  Comparator Enable Control Register register,  Address offset: 0x040 */
	__IO uint32_t COMP_WK_SHUT_CNT ;                       /*!<  Comparator Shutdown Counter Register register,          Address offset: 0x044 */
} COMP_TypeDef;
/** @} */

#endif
