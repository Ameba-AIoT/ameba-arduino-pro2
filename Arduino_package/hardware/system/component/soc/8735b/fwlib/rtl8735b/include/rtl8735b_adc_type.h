#ifndef _RTL8735B_ADC_TYPE_H_
#define _RTL8735B_ADC_TYPE_H_

/**************************************************************************//**
 * @defgroup ADC_CONF
 * @brief  ADC Configuration Register                (@ 0X000)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_EN                            9
#define ADC_BIT_EN                              ((u32)0x00000001 << 9)                              /*!<R/W 0  This bit is for ADC enable control. */
#define ADC_SHIFT_CVLIST_LEN                    4
#define ADC_MASK_CVLIST_LEN                     ((u32)0x0000000F << 4)                              /*!<R/W 0  This field defines the number of items in the ADC conversion channel list. 0 is for 1 item in list. 1 is for 2 items in list. */
#define ADC_SHIFT_OP_MOD                        1
#define ADC_MASK_OP_MOD                         ((u32)0x00000007 << 1)                              /*!<R/W 0  These bits selects ADC operation mode. 0: Software Trigger Mode 1: Automatic Mode 2: Timer-Trigger Mode */
#define ADC_SHIFT_REF_IN_SEL                    0
#define ADC_BIT_REF_IN_SEL                      ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit selects ADC reference voltage input. 0: ADC's reference voltage is from internal source. 1: ADC's reference voltage is from external pin. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_IN_TYPE
 * @brief  ADC Input Type Register                   (@ 0X004)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH7_IN_TYPE                   7
#define ADC_BIT_CH7_IN_TYPE                     ((u32)0x00000001 << 7)                              /*!<R/W 0  This bit controls channel 7 input type. If it is set to differential type (value of this bit is 1), channel 6 should also be set to differential type since they are hardware-fixed differential pair. 0: ADC channel 7 is single-end input. 1: ADC channel 7 is differential input which is paired with channel 6. */
#define ADC_SHIFT_CH6_IN_TYPE                   6
#define ADC_BIT_CH6_IN_TYPE                     ((u32)0x00000001 << 6)                              /*!<R/W 0  This bit controls channel 6 input type. If it is set to differential type (value of this bit is 1), channel 7 should also be set to differential type since they are hardware-fixed differential pair. 0: ADC channel 6 is single-end input. 1: ADC channel 6 is differential input which is paired with channel 7. */
#define ADC_SHIFT_CH5_IN_TYPE                   5
#define ADC_BIT_CH5_IN_TYPE                     ((u32)0x00000001 << 5)                              /*!<R/W 0  This bit controls channel 5 input type. If it is set to differential type (value of this bit is 1), channel 4 should also be set to differential type since they are hardware-fixed differential pair. 0: ADC channel 5 is single-end input. 1: ADC channel 5 is differential input which is paired with channel 4. */
#define ADC_SHIFT_CH4_IN_TYPE                   4
#define ADC_BIT_CH4_IN_TYPE                     ((u32)0x00000001 << 4)                              /*!<R/W 0  This bit controls channel 4 input type. If it is set to differential type (value of this bit is 1), channel 5 should also be set to differential type since they are hardware-fixed differential pair. 0: ADC channel 4 is single-end input. 1: ADC channel 4 is differential input which is paired with channel 5. */
#define ADC_SHIFT_CH3_IN_TYPE                   3
#define ADC_BIT_CH3_IN_TYPE                     ((u32)0x00000001 << 3)                              /*!<R/W 0  This bit controls channel 3 input type. If it is set to differential type (value of this bit is 1), channel 2 should also be set to differential type since they are hardware-fixed differential pair. 0: ADC channel 3 is single-end input. 1: ADC channel 3 is differential input which is paired with channel 2. */
#define ADC_SHIFT_CH2_IN_TYPE                   2
#define ADC_BIT_CH2_IN_TYPE                     ((u32)0x00000001 << 2)                              /*!<R/W 0  This bit controls channel 2 input type. If it is set to differential type (value of this bit is 1), channel 3 should also be set to differential type since they are hardware-fixed differential pair. 0: ADC channel 2 is single-end input. 1: ADC channel 2 is differential input which is paired with channel 3. */
#define ADC_SHIFT_CH1_IN_TYPE                   1
#define ADC_BIT_CH1_IN_TYPE                     ((u32)0x00000001 << 1)                              /*!<R/W 0  This bit controls channel 1 input type. If it is set to differential type (value of this bit is 1), channel 0 should also be set to differential type since they are hardware-fixed differential pair. 0: ADC channel 1 is single-end input. 1: ADC channel 1 is differential input which is paired with channel 0. */
#define ADC_SHIFT_CH0_IN_TYPE                   0
#define ADC_BIT_CH0_IN_TYPE                     ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls channel 0 input type. If it is set to differential type (value of this bit is 1), channel 1 should also be set to differential type since they are hardware-fixed differential pair. 0: ADC channel 0 is single-end input. 1: ADC channel 0 is differential input which is paired with channel 1. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_TH_CH0
 * @brief  ADC Channel 0 Comparison Threshold Register (@ 0X008)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH0_TH_H                      16
#define ADC_MASK_CH0_TH_H                       ((u32)0x00000FFF << 16)                             /*!<R/W 0  This field defines the higher threshold of channel 0 for ADC automatic comparison. */
#define ADC_SHIFT_CH0_TH_L                      0
#define ADC_MASK_CH0_TH_L                       ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field defines the lower threshold of channel 0 for ADC automatic comparison. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_TH_CH1
 * @brief  ADC Channel 1 Comparison Threshold Register (@ 0X00C)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH1_TH_H                      16
#define ADC_MASK_CH1_TH_H                       ((u32)0x00000FFF << 16)                             /*!<R/W 0  This field defines the higher threshold of channel 1 for ADC automatic comparison. */
#define ADC_SHIFT_CH1_TH_L                      0
#define ADC_MASK_CH1_TH_L                       ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field defines the lower threshold of channel 1 for ADC automatic comparison. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_TH_CH2
 * @brief  ADC Channel 2 Comparison Threshold Register (@ 0X010)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH2_TH_H                      16
#define ADC_MASK_CH2_TH_H                       ((u32)0x00000FFF << 16)                             /*!<R/W 0  This field defines the higher threshold of channel 2 for ADC automatic comparison. */
#define ADC_SHIFT_CH2_TH_L                      0
#define ADC_MASK_CH2_TH_L                       ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field defines the lower threshold of channel 2 for ADC automatic comparison. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_TH_CH3
 * @brief  ADC Channel 3 Comparison Threshold Register (@ 0X014)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH3_TH_H                      16
#define ADC_MASK_CH3_TH_H                       ((u32)0x00000FFF << 16)                             /*!<R/W 0  This field defines the higher threshold of channel 3 for ADC automatic comparison. */
#define ADC_SHIFT_CH3_TH_L                      0
#define ADC_MASK_CH3_TH_L                       ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field defines the lower threshold of channel 3 for ADC automatic comparison. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_TH_CH4
 * @brief  ADC Channel 4 Comparison Threshold Register (@ 0X018)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH4_TH_H                      16
#define ADC_MASK_CH4_TH_H                       ((u32)0x00000FFF << 16)                             /*!<R/W 0  This field defines the higher threshold of channel 4 for ADC automatic comparison. */
#define ADC_SHIFT_CH4_TH_L                      0
#define ADC_MASK_CH4_TH_L                       ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field defines the lower threshold of channel 4 for ADC automatic comparison. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_TH_CH5
 * @brief  ADC Channel 5 Comparison Threshold Register (@ 0X01C)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH5_TH_H                      16
#define ADC_MASK_CH5_TH_H                       ((u32)0x00000FFF << 16)                             /*!<R/W 0  This field defines the higher threshold of channel 5 for ADC automatic comparison. */
#define ADC_SHIFT_CH5_TH_L                      0
#define ADC_MASK_CH5_TH_L                       ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field defines the lower threshold of channel 5 for ADC automatic comparison. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_TH_CH6
 * @brief  ADC Channel 6 Comparison Threshold Register (@ 0X020)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH6_TH_H                      16
#define ADC_MASK_CH6_TH_H                       ((u32)0x00000FFF << 16)                             /*!<R/W 0  This field defines the higher threshold of channel 6 for ADC automatic comparison. */
#define ADC_SHIFT_CH6_TH_L                      0
#define ADC_MASK_CH6_TH_L                       ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field defines the lower threshold of channel 6 for ADC automatic comparison. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_TH_CH7
 * @brief  ADC Channel 7 Comparison Threshold Register (@ 0X024)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH7_TH_H                      16
#define ADC_MASK_CH7_TH_H                       ((u32)0x00000FFF << 16)                             /*!<R/W 0  This field defines the higher threshold of channel 7 for ADC automatic comparison. */
#define ADC_SHIFT_CH7_TH_L                      0
#define ADC_MASK_CH7_TH_L                       ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field defines the lower threshold of channel 7 for ADC automatic comparison. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_TH_CH8
 * @brief  ADC Channel 8 Comparison Threshold Register (@ 0X028)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH8_TH_H                      16
#define ADC_MASK_CH8_TH_H                       ((u32)0x00000FFF << 16)                             /*!<R/W 0  This field defines the higher threshold of channel 8 for ADC automatic comparison. */
#define ADC_SHIFT_CH8_TH_L                      0
#define ADC_MASK_CH8_TH_L                       ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field defines the lower threshold of channel 8 for ADC automatic comparison. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_CTRL
 * @brief  ADC Comparison Control Register           (@ 0X02C)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH8_COMP_CTRL                 16
#define ADC_MASK_CH8_COMP_CTRL                  ((u32)0x00000003 << 16)                             /*!<R/W 0  This field defines ADC channel comparison criteria which would notify system by interrupt when the criterion matches. Once a criterion matches, ADC should send an interrupt signal to system if the related interrupt mask is unmask. ADC also updates comparison results in REG_ADC_COMP_STS. 0: When Vin < BIT_ADC_COMP_TH_L_CH8, comparison criterion matches. 1: When Vin > BIT_ADC_COMP_TH_H_CH8, comparison criterion matches. 2: When Vin >= BIT_ADC_COMP_TH_L_CH8 and Vin <= BIT_ADC_COMP_TH_H_CH8, comparison criterion matches. 3: When Vin < BIT_ADC_COMP_TH_L_CH8 or Vin > BIT_ADC_COMP_TH_H_CH8,comparison criterion matches. */
#define ADC_SHIFT_CH7_COMP_CTRL                 14
#define ADC_MASK_CH7_COMP_CTRL                  ((u32)0x00000003 << 14)                             /*!<R/W 0  This field defines ADC channel comparison criteria which would notify system by interrupt when the criterion matches. Once a criterion matches, ADC should send an interrupt signal to system if the related interrupt mask is unmask. ADC also updates comparison results in REG_ADC_COMP_STS. 0: When Vin < BIT_ADC_COMP_TH_L_CH7, comparison criterion matches. 1: When Vin > BIT_ADC_COMP_TH_H_CH7, comparison criterion matches. 2: When Vin >= BIT_ADC_COMP_TH_L_CH7 and Vin <= BIT_ADC_COMP_TH_H_CH7, comparison criterion matches. 3: When Vin < BIT_ADC_COMP_TH_L_CH7 or Vin > BIT_ADC_COMP_TH_H_CH7,comparison criterion matches. */
#define ADC_SHIFT_CH6_COMP_CTRL                 12
#define ADC_MASK_CH6_COMP_CTRL                  ((u32)0x00000003 << 12)                             /*!<R/W 0  This field defines ADC channel comparison criteria which would notify system by interrupt when the criterion matches. Once a criterion matches, ADC should send an interrupt signal to system if the related interrupt mask is unmask. ADC also updates comparison results in REG_ADC_COMP_STS. 0: When Vin < BIT_ADC_COMP_TH_L_CH6, comparison criterion matches. 1: When Vin > BIT_ADC_COMP_TH_H_CH6, comparison criterion matches. 2: When Vin >= BIT_ADC_COMP_TH_L_CH6 and Vin <= BIT_ADC_COMP_TH_H_CH6, comparison criterion matches. 3: When Vin < BIT_ADC_COMP_TH_L_CH6 or Vin > BIT_ADC_COMP_TH_H_CH6,comparison criterion matches. */
#define ADC_SHIFT_CH5_COMP_CTRL                 10
#define ADC_MASK_CH5_COMP_CTRL                  ((u32)0x00000003 << 10)                             /*!<R/W 0  This field defines ADC channel comparison criteria which would notify system by interrupt when the criterion matches. Once a criterion matches, ADC should send an interrupt signal to system if the related interrupt mask is unmask. ADC also updates comparison results in REG_ADC_COMP_STS. 0: When Vin < BIT_ADC_COMP_TH_L_CH5, comparison criterion matches. 1: When Vin > BIT_ADC_COMP_TH_H_CH5, comparison criterion matches. 2: When Vin >= BIT_ADC_COMP_TH_L_CH5 and Vin <= BIT_ADC_COMP_TH_H_CH5, comparison criterion matches. 3: When Vin < BIT_ADC_COMP_TH_L_CH5 or Vin > BIT_ADC_COMP_TH_H_CH5,comparison criterion matches. */
#define ADC_SHIFT_CH4_COMP_CTRL                 8
#define ADC_MASK_CH4_COMP_CTRL                  ((u32)0x00000003 << 8)                              /*!<R/W 0  This field defines ADC channel comparison criteria which would notify system by interrupt when the criterion matches. Once a criterion matches, ADC should send an interrupt signal to system if the related interrupt mask is unmask. ADC also updates comparison results in REG_ADC_COMP_STS. 0: When Vin < BIT_ADC_COMP_TH_L_CH4, comparison criterion matches. 1: When Vin > BIT_ADC_COMP_TH_H_CH4, comparison criterion matches. 2: When Vin >= BIT_ADC_COMP_TH_L_CH4 and Vin <= BIT_ADC_COMP_TH_H_CH4, comparison criterion matches. 3: When Vin < BIT_ADC_COMP_TH_L_CH4 or Vin > BIT_ADC_COMP_TH_H_CH4,comparison criterion matches. */
#define ADC_SHIFT_CH3_COMP_CTRL                 6
#define ADC_MASK_CH3_COMP_CTRL                  ((u32)0x00000003 << 6)                              /*!<R/W 0  This field defines ADC channel comparison criteria which would notify system by interrupt when the criterion matches. Once a criterion matches, ADC should send an interrupt signal to system if the related interrupt mask is unmask. ADC also updates comparison results in REG_ADC_COMP_STS. 0: When Vin < BIT_ADC_COMP_TH_L_CH3, comparison criterion matches. 1: When Vin > BIT_ADC_COMP_TH_H_CH3, comparison criterion matches. 2: When Vin >= BIT_ADC_COMP_TH_L_CH3 and Vin <= BIT_ADC_COMP_TH_H_CH3, comparison criterion matches. 3: When Vin < BIT_ADC_COMP_TH_L_CH3 or Vin > BIT_ADC_COMP_TH_H_CH3,comparison criterion matches. */
#define ADC_SHIFT_CH2_COMP_CTRL                 4
#define ADC_MASK_CH2_COMP_CTRL                  ((u32)0x00000003 << 4)                              /*!<R/W 0  This field defines ADC channel comparison criteria which would notify system by interrupt when the criterion matches. Once a criterion matches, ADC should send an interrupt signal to system if the related interrupt mask is unmask. ADC also updates comparison results in REG_ADC_COMP_STS. 0: When Vin < BIT_ADC_COMP_TH_L_CH2, comparison criterion matches. 1: When Vin > BIT_ADC_COMP_TH_H_CH2, comparison criterion matches. 2: When Vin >= BIT_ADC_COMP_TH_L_CH2 and Vin <= BIT_ADC_COMP_TH_H_CH2, comparison criterion matches. 3: When Vin < BIT_ADC_COMP_TH_L_CH2 or Vin > BIT_ADC_COMP_TH_H_CH2,comparison criterion matches. */
#define ADC_SHIFT_CH1_COMP_CTRL                 2
#define ADC_MASK_CH1_COMP_CTRL                  ((u32)0x00000003 << 2)                              /*!<R/W 0  This field defines ADC channel comparison criteria which would notify system by interrupt when the criterion matches. Once a criterion matches, ADC should send an interrupt signal to system if the related interrupt mask is unmask. ADC also updates comparison results in REG_ADC_COMP_STS. 0: When Vin < BIT_ADC_COMP_TH_L_CH1, comparison criterion matches. 1: When Vin > BIT_ADC_COMP_TH_H_CH1, comparison criterion matches. 2: When Vin >= BIT_ADC_COMP_TH_L_CH1 and Vin <= BIT_ADC_COMP_TH_H_CH1, comparison criterion matches. 3: When Vin < BIT_ADC_COMP_TH_L_CH1 or Vin > BIT_ADC_COMP_TH_H_CH1,comparison criterion matches. */
#define ADC_SHIFT_CH0_COMP_CTRL                 0
#define ADC_MASK_CH0_COMP_CTRL                  ((u32)0x00000003 << 0)                              /*!<R/W 0  This field defines ADC channel comparison criteria which would notify system by interrupt when the criterion matches. Once a criterion matches, ADC should send an interrupt signal to system if the related interrupt mask is unmask. ADC also updates comparison results in REG_ADC_COMP_STS. 0: When Vin < BIT_ADC_COMP_TH_L_CH0, comparison criterion matches. 1: When Vin > BIT_ADC_COMP_TH_H_CH0, comparison criterion matches. 2: When Vin >= BIT_ADC_COMP_TH_L_CH0 and Vin <= BIT_ADC_COMP_TH_H_CH0, comparison criterion matches. 3: When Vin < BIT_ADC_COMP_TH_L_CH0 or Vin > BIT_ADC_COMP_TH_H_CH0,comparison criterion matches. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_COMP_STS
 * @brief  ADC Comparison Status Register            (@ 0X030)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CH8_COMP_STS                  16
#define ADC_MASK_CH8_COMP_STS                   ((u32)0x00000003 << 16)                             /*!<R 0  This field reflects comparison result of channel 8 immediately. */
#define ADC_SHIFT_CH7_COMP_STS                  14
#define ADC_MASK_CH7_COMP_STS                   ((u32)0x00000003 << 14)                             /*!<R 0  This field reflects comparison result of channel 7 immediately. */
#define ADC_SHIFT_CH6_COMP_STS                  12
#define ADC_MASK_CH6_COMP_STS                   ((u32)0x00000003 << 12)                             /*!<R 0  This field reflects comparison result of channel 6 immediately. */
#define ADC_SHIFT_CH5_COMP_STS                  10
#define ADC_MASK_CH5_COMP_STS                   ((u32)0x00000003 << 10)                             /*!<R 0  This field reflects comparison result of channel 5 immediately. */
#define ADC_SHIFT_CH4_COMP_STS                  8
#define ADC_MASK_CH4_COMP_STS                   ((u32)0x00000003 << 8)                              /*!<R 0  This field reflects comparison result of channel 4 immediately. */
#define ADC_SHIFT_CH3_COMP_STS                  6
#define ADC_MASK_CH3_COMP_STS                   ((u32)0x00000003 << 6)                              /*!<R 0  This field reflects comparison result of channel 3 immediately. */
#define ADC_SHIFT_CH2_COMP_STS                  4
#define ADC_MASK_CH2_COMP_STS                   ((u32)0x00000003 << 4)                              /*!<R 0  This field reflects comparison result of channel 2 immediately. */
#define ADC_SHIFT_CH1_COMP_STS                  2
#define ADC_MASK_CH1_COMP_STS                   ((u32)0x00000003 << 2)                              /*!<R 0  This field reflects comparison result of channel 1 immediately. */
#define ADC_SHIFT_CH0_COMP_STS                  0
#define ADC_MASK_CH0_COMP_STS                   ((u32)0x00000003 << 0)                              /*!<R 0  This field reflects comparison result of channel 0 immediately. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_CHSW_LIST_0
 * @brief  ADC Channel Swtich List 0 Register        (@ 0X034)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CHSW_7                        28
#define ADC_MASK_CHSW_7                         ((u32)0x0000000F << 28)                             /*!<R/W 0  This field defines the 8th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_6                        24
#define ADC_MASK_CHSW_6                         ((u32)0x0000000F << 24)                             /*!<R/W 0  This field defines the 7th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_5                        20
#define ADC_MASK_CHSW_5                         ((u32)0x0000000F << 20)                             /*!<R/W 0  This field defines the 6th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_4                        16
#define ADC_MASK_CHSW_4                         ((u32)0x0000000F << 16)                             /*!<R/W 0  This field defines the 5th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_3                        12
#define ADC_MASK_CHSW_3                         ((u32)0x0000000F << 12)                             /*!<R/W 0  This field defines the 4th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_2                        8
#define ADC_MASK_CHSW_2                         ((u32)0x0000000F << 8)                              /*!<R/W 0  This field defines the 3rd channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_1                        4
#define ADC_MASK_CHSW_1                         ((u32)0x0000000F << 4)                              /*!<R/W 0  This field defines the 2nd channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_0                        0
#define ADC_MASK_CHSW_0                         ((u32)0x0000000F << 0)                              /*!<R/W 0  This field defines the 1st channel to do a conversion when a conversion event takes place. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_CHSW_LIST_1
 * @brief  ADC Channel Swtich List 1 Register        (@ 0X038)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CHSW_15                       28
#define ADC_MASK_CHSW_15                        ((u32)0x0000000F << 28)                             /*!<R/W 0  This field defines the 16th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_14                       24
#define ADC_MASK_CHSW_14                        ((u32)0x0000000F << 24)                             /*!<R/W 0  This field defines the 15th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_13                       20
#define ADC_MASK_CHSW_13                        ((u32)0x0000000F << 20)                             /*!<R/W 0  This field defines the 14th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_12                       16
#define ADC_MASK_CHSW_12                        ((u32)0x0000000F << 16)                             /*!<R/W 0  This field defines the 13th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_11                       12
#define ADC_MASK_CHSW_11                        ((u32)0x0000000F << 12)                             /*!<R/W 0  This field defines the 12th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_10                       8
#define ADC_MASK_CHSW_10                        ((u32)0x0000000F << 8)                              /*!<R/W 0  This field defines the 11th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_9                        4
#define ADC_MASK_CHSW_9                         ((u32)0x0000000F << 4)                              /*!<R/W 0  This field defines the 10th channel to do a conversion when a conversion event takes place. */
#define ADC_SHIFT_CHSW_8                        0
#define ADC_MASK_CHSW_8                         ((u32)0x0000000F << 0)                              /*!<R/W 0  This field defines the 9th channel to do a conversion when a conversion event takes place. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_RST_LIST
 * @brief  ADC Reset List Register                   (@ 0X03C)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_RST_LIST                      0
#define ADC_BIT_RST_LIST                        ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls to reset the channel switch to default state or not. Once this bit is set, the auto/manual channel switch goes to the first channel as a default state. 0: Do not reset conversion list to default state. 1: Reset conversion list to default state. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_AUTO_CHSW_CTRL
 * @brief  ADC Auto Channel Switch Control Register  (@ 0X040)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_AUTO_CHSW_EN                  0
#define ADC_BIT_AUTO_CHSW_EN                    ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls the automatic channel swtich enabled or disabled. 0: Disable the automatic channel switch. If an automatic channel switch is in progess, writing 0 will terminate the automatic channel switch. 1: Enable the automatic channel switch. When setting this bit, an automatic channel switch starts from the first channel in the channel switch list. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_SW_TRIG
 * @brief  ADC Software Trigger Register             (@ 0X044)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_SW_TRIG                       0
#define ADC_BIT_SW_TRIG                         ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls the ADC module to do a conversion. Every time this bit is set to 1, ADC module would switch to a new channel and do one conversion. Therefore, this bit could be used as a start-convert event which is controlled by software. Every time a conversion is done, software MUST clear this bit manually. 0: Disable the analog module and analog mux. 1: Enable the analog module and analog mux. And then start a new channel conversion. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_LAST_ITEM
 * @brief  ADC Last Item Register                    (@ 0X048)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_LAST_ITEM                     0
#define ADC_MASK_LAST_ITEM                      ((u32)0x0000000F << 0)                              /*!<R 0  This field reflects the last used channel. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_STS
 * @brief  ADC Busy_Ready Status Register            (@ 0X04C)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_STS_EMPTY                     2
#define ADC_BIT_STS_EMPTY                       ((u32)0x00000001 << 2)                              /*!<R 0  This bit directly reflects the FIFO empty status. 0: FIFO is empty. 1: FIFO is NOT empty. */
#define ADC_SHIFT_STS_FULL                      1
#define ADC_BIT_STS_FULL                        ((u32)0x00000001 << 1)                              /*!<R 0  This bit directly reflects the FIFO full status. 0: FIFO is NOT full. 1: FIFO is full. */
#define ADC_SHIFT_STS_BUSY                      0
#define ADC_BIT_STS_BUSY                        ((u32)0x00000001 << 0)                              /*!<R 0  This bit reflects the ADC is busy or not. If the ADC is processing a conversion of a channel, this bit remains 1 which indicates it's busy. Once a conversion is done, this bit becomes 0 which indicates its' ready to do another conversion. 0: The ADC is ready. 1: The ADC is busy. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_INTR_CTRL
 * @brief  ADC Interrupt Control Register            (@ 0X050)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_IT_COMP_CH8_EN                16
#define ADC_BIT_IT_COMP_CH8_EN                  ((u32)0x00000001 << 16)                             /*!<R/W 0  This bit controls the interrupt is enabled or not when channel 8 comparison criterion matches. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_COMP_CH7_EN                15
#define ADC_BIT_IT_COMP_CH7_EN                  ((u32)0x00000001 << 15)                             /*!<R/W 0  This bit controls the interrupt is enabled or not when channel 7 comparison criterion matches. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_COMP_CH6_EN                14
#define ADC_BIT_IT_COMP_CH6_EN                  ((u32)0x00000001 << 14)                             /*!<R/W 0  This bit controls the interrupt is enabled or not when channel 6 comparison criterion matches. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_COMP_CH5_EN                13
#define ADC_BIT_IT_COMP_CH5_EN                  ((u32)0x00000001 << 13)                             /*!<R/W 0  This bit controls the interrupt is enabled or not when channel 5 comparison criterion matches. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_COMP_CH4_EN                12
#define ADC_BIT_IT_COMP_CH4_EN                  ((u32)0x00000001 << 12)                             /*!<R/W 0  This bit controls the interrupt is enabled or not when channel 4 comparison criterion matches. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_COMP_CH3_EN                11
#define ADC_BIT_IT_COMP_CH3_EN                  ((u32)0x00000001 << 11)                             /*!<R/W 0  This bit controls the interrupt is enabled or not when channel 3 comparison criterion matches. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_COMP_CH2_EN                10
#define ADC_BIT_IT_COMP_CH2_EN                  ((u32)0x00000001 << 10)                             /*!<R/W 0  This bit controls the interrupt is enabled or not when channel 2 comparison criterion matches. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_COMP_CH1_EN                9
#define ADC_BIT_IT_COMP_CH1_EN                  ((u32)0x00000001 << 9)                              /*!<R/W 0  This bit controls the interrupt is enabled or not when channel 1 comparison criterion matches. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_COMP_CH0_EN                8
#define ADC_BIT_IT_COMP_CH0_EN                  ((u32)0x00000001 << 8)                              /*!<R/W 0  This bit controls the interrupt is enabled or not when channel 0 comparison criterion matches. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_ERR_EN                     7
#define ADC_BIT_IT_ERR_EN                       ((u32)0x00000001 << 7)                              /*!<R/W 0  This bit controls the interrupt is enabled or not when an error state takes place. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_DAT_OVW_EN                 6
#define ADC_BIT_IT_DAT_OVW_EN                   ((u32)0x00000001 << 6)                              /*!<R/W 0  This bit controls the interrupt is enabled or not when a data overwritten situation takes place. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_FIFO_EMPTY_EN              5
#define ADC_BIT_IT_FIFO_EMPTY_EN                ((u32)0x00000001 << 5)                              /*!<R/W 0  This bit controls the interrupt is enabled or not when a FIFO empty state takes place. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_FIFO_OVER_EN               4
#define ADC_BIT_IT_FIFO_OVER_EN                 ((u32)0x00000001 << 4)                              /*!<R/W 0  This bit controls the interrupt is enabled or not when a FIFO overflow state takes place. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_FIFO_FULL_EN               3
#define ADC_BIT_IT_FIFO_FULL_EN                 ((u32)0x00000001 << 3)                              /*!<R/W 0  This bit controls the interrupt is enabled or not when a FIFO full state takes place. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_CHCV_END_EN                2
#define ADC_BIT_IT_CHCV_END_EN                  ((u32)0x00000001 << 2)                              /*!<R/W 0  This bit controls the interrupt is enbled or not when a particular channel conversion is done. Please refer to REG_ADC_IT_CHNO_CON 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_CV_END_EN                  1
#define ADC_BIT_IT_CV_END_EN                    ((u32)0x00000001 << 1)                              /*!<R/W 0  This bit controls the interrupt is enbled or not every time a conversion is done. No matter ADC module is in what kind of operation mode. Every time a conversion is executed, ADC module would notify system if this bit is set. 0: This interrupt is disabled. 1: This interrupt is enabled. */
#define ADC_SHIFT_IT_CVLIST_END_EN              0
#define ADC_BIT_IT_CVLIST_END_EN                ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls the interrupt is enbled or not when a conversion of the last channel in the list is done. For example, in automatic mode conversions would be executed coninuously. Every time the last channel conversion is done, which means all channel conversions in the list is done, ADC could notify system if this bit is set. 0: This interrupt is disabled. 1: This interrupt is enabled. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_INTR_RAW_STS
 * @brief  ADC Interrupt RAW Status Register         (@ 0X054)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_IT_COMP_CH8_RAW_STS           16
#define ADC_BIT_IT_COMP_CH8_RAW_STS             ((u32)0x00000001 << 16)                             /*!<R 0  This bit is the raw status of channel 8 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH7_RAW_STS           15
#define ADC_BIT_IT_COMP_CH7_RAW_STS             ((u32)0x00000001 << 15)                             /*!<R 0  This bit is the raw status of channel 7 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH6_RAW_STS           14
#define ADC_BIT_IT_COMP_CH6_RAW_STS             ((u32)0x00000001 << 14)                             /*!<R 0  This bit is the raw status of channel 6 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH5_RAW_STS           13
#define ADC_BIT_IT_COMP_CH5_RAW_STS             ((u32)0x00000001 << 13)                             /*!<R 0  This bit is the raw status of channel 5 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH4_RAW_STS           12
#define ADC_BIT_IT_COMP_CH4_RAW_STS             ((u32)0x00000001 << 12)                             /*!<R 0  This bit is the raw status of channel 4 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH3_RAW_STS           11
#define ADC_BIT_IT_COMP_CH3_RAW_STS             ((u32)0x00000001 << 11)                             /*!<R 0  This bit is the raw status of channel 3 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH2_RAW_STS           10
#define ADC_BIT_IT_COMP_CH2_RAW_STS             ((u32)0x00000001 << 10)                             /*!<R 0  This bit is the raw status of channel 2 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH1_RAW_STS           9
#define ADC_BIT_IT_COMP_CH1_RAW_STS             ((u32)0x00000001 << 9)                              /*!<R 0  This bit is the raw status of channel 1 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH0_RAW_STS           8
#define ADC_BIT_IT_COMP_CH0_RAW_STS             ((u32)0x00000001 << 8)                              /*!<R 0  This bit is the raw status of channel 0 comparison interrupt. */
#define ADC_SHIFT_IT_ERR_RAW_STS                7
#define ADC_BIT_IT_ERR_RAW_STS                  ((u32)0x00000001 << 7)                              /*!<R 0  This bit is the raw status of error interrupt. */
#define ADC_SHIFT_IT_DAT_OVW_RAW_STS            6
#define ADC_BIT_IT_DAT_OVW_RAW_STS              ((u32)0x00000001 << 6)                              /*!<R 0  This bit is the raw status of global data register overwritten interrupt. */
#define ADC_SHIFT_IT_FIFO_EMPTY_RAW_STS         5
#define ADC_BIT_IT_FIFO_EMPTY_RAW_STS           ((u32)0x00000001 << 5)                              /*!<R 0  This bit is the raw status of FIFO empty interrupt. */
#define ADC_SHIFT_IT_FIFO_OVER_RAW_STS          4
#define ADC_BIT_IT_FIFO_OVER_RAW_STS            ((u32)0x00000001 << 4)                              /*!<R 0  This bit is the raw status of FIFO overflow interrupt. */
#define ADC_SHIFT_IT_FIFO_FULL_RAW_STS          3
#define ADC_BIT_IT_FIFO_FULL_RAW_STS            ((u32)0x00000001 << 3)                              /*!<R 0  This bit is the raw status of FIFO full interrupt. */
#define ADC_SHIFT_IT_CHCV_END_RAW_STS           2
#define ADC_BIT_IT_CHCV_END_RAW_STS             ((u32)0x00000001 << 2)                              /*!<R 0  This bit is the raw status of particular channel conversion end interrupt. */
#define ADC_SHIFT_IT_CV_END_RAW_STS             1
#define ADC_BIT_IT_CV_END_RAW_STS               ((u32)0x00000001 << 1)                              /*!<R 0  This bit is the raw status of each conversion end interrupt. */
#define ADC_SHIFT_IT_CVLIST_END_RAW_STS         0
#define ADC_BIT_IT_CVLIST_END_RAW_STS           ((u32)0x00000001 << 0)                              /*!<R 0  This bit is the raw status of channel conversion list end interrupt. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_INTR_STS
 * @brief  ADC Interrupt Status Register             (@ 0X058)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_IT_COMP_CH8_STS               16
#define ADC_BIT_IT_COMP_CH8_STS                 ((u32)0x00000001 << 16)                             /*!<R/W1C 0  This bit is the status of channel 8 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH7_STS               15
#define ADC_BIT_IT_COMP_CH7_STS                 ((u32)0x00000001 << 15)                             /*!<R/W1C 0  This bit is the status of channel 7 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH6_STS               14
#define ADC_BIT_IT_COMP_CH6_STS                 ((u32)0x00000001 << 14)                             /*!<R/W1C 0  This bit is the status of channel 6 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH5_STS               13
#define ADC_BIT_IT_COMP_CH5_STS                 ((u32)0x00000001 << 13)                             /*!<R/W1C 0  This bit is the status of channel 5 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH4_STS               12
#define ADC_BIT_IT_COMP_CH4_STS                 ((u32)0x00000001 << 12)                             /*!<R/W1C 0  This bit is the status of channel 4 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH3_STS               11
#define ADC_BIT_IT_COMP_CH3_STS                 ((u32)0x00000001 << 11)                             /*!<R/W1C 0  This bit is the status of channel 3 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH2_STS               10
#define ADC_BIT_IT_COMP_CH2_STS                 ((u32)0x00000001 << 10)                             /*!<R/W1C 0  This bit is the status of channel 2 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH1_STS               9
#define ADC_BIT_IT_COMP_CH1_STS                 ((u32)0x00000001 << 9)                              /*!<R/W1C 0  This bit is the status of channel 1 comparison interrupt. */
#define ADC_SHIFT_IT_COMP_CH0_STS               8
#define ADC_BIT_IT_COMP_CH0_STS                 ((u32)0x00000001 << 8)                              /*!<R/W1C 0  This bit is the status of channel 0 comparison interrupt. */
#define ADC_SHIFT_IT_ERR_STS                    7
#define ADC_BIT_IT_ERR_STS                      ((u32)0x00000001 << 7)                              /*!<R/W1C 0  This bit is the status of error interrupt. */
#define ADC_SHIFT_IT_DAT_OVW_STS                6
#define ADC_BIT_IT_DAT_OVW_STS                  ((u32)0x00000001 << 6)                              /*!<R/W1C 0  This bit is the status of global data register overwritten interrupt. */
#define ADC_SHIFT_IT_FIFO_EMPTY_STS             5
#define ADC_BIT_IT_FIFO_EMPTY_STS               ((u32)0x00000001 << 5)                              /*!<R/W1C 0  This bit is the status of FIFO empty interrupt. */
#define ADC_SHIFT_IT_FIFO_OVER_STS              4
#define ADC_BIT_IT_FIFO_OVER_STS                ((u32)0x00000001 << 4)                              /*!<R/W1C 0  This bit is the status of FIFO overflow interrupt. */
#define ADC_SHIFT_IT_FIFO_FULL_STS              3
#define ADC_BIT_IT_FIFO_FULL_STS                ((u32)0x00000001 << 3)                              /*!<R/W1C 0  This bit is the status of FIFO full interrupt. */
#define ADC_SHIFT_IT_CHCV_END_STS               2
#define ADC_BIT_IT_CHCV_END_STS                 ((u32)0x00000001 << 2)                              /*!<R/W1C 0  This bit is the status of particular channel conversion end interrupt. */
#define ADC_SHIFT_IT_CV_END_STS                 1
#define ADC_BIT_IT_CV_END_STS                   ((u32)0x00000001 << 1)                              /*!<R/W1C 0  This bit is the status of each conversion end interrupt. */
#define ADC_SHIFT_IT_CVLIST_END_STS             0
#define ADC_BIT_IT_CVLIST_END_STS               ((u32)0x00000001 << 0)                              /*!<R/W1C 0  This bit is the status of channel conversion list end interrupt. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_IT_CHNO_CON
 * @brief  ADC Conversion Interrupt Channel Number Configuration Register (@ 0X05C)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_IT_CHNO_CON                   0
#define ADC_MASK_IT_CHNO_CON                    ((u32)0x00000007 << 0)                              /*!<R/W 0  This field defines that ADC module should send interrupt signal to system when a conversion which of channel number is the same as this field. This register is only valid when BIT_ADC_IT_CHCV_END_EN is set. BIT_ADC_IT_CHNO_CON: Channel number. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_FULL_LVL
 * @brief  ADC FIFO Full Level Register              (@ 0X060)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_FULL_LVL                      0
#define ADC_MASK_FULL_LVL                       ((u32)0x0000003F << 0)                              /*!<R/W 0  This field defines the FIFO full entry threshold level and it is used for FIFO full interrupt. It should be set according to ADC FIFO depth. A value of 0 sets the threshold for 1 entry, and a value of 15 sets the threshold for 16 entries. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_TRIG_TIMER_SEL
 * @brief  ADC Trigger Timer Select Register         (@ 0X064)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_TRIG_TIMER_SEL                0
#define ADC_MASK_TRIG_TIMER_SEL                 ((u32)0x00000007 << 0)                              /*!<R/W 0  This three bits defines which timer channel would be used to make ADC module do a conversion. BIT_ADC_EXT_WK_TIMER_SEL is 0: Timer module 0 is used as the comparator external trigger source. 1: Timer module 1 is used as the comparator external trigger source. . . . 7: Timer module 7 is used as the comparator external trigger source. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DAT_GLOBAL
 * @brief  ADC Global Data Register                  (@ 0X068)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DAT_GLOBAL_CH                 23
#define ADC_MASK_DAT_GLOBAL_CH                  ((u32)0x00000007 << 23)                             /*!<R/W 0  This field indicates which channel data is in BIT_ADC_DATA_GLOBAL */
#define ADC_SHIFT_DAT_GLOBAL_RDY                22
#define ADC_BIT_DAT_GLOBAL_RDY                  ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit indicates that a conversion is done. Every time a conversion is done, this bit should be set to 1 and it would be cleared to 0 when a read operation of REG_ADC_DATA_GLOBAL. */
#define ADC_SHIFT_DAT_GLOBAL_OVW                21
#define ADC_BIT_DAT_GLOBAL_OVW                  ((u32)0x00000001 << 21)                             /*!<R/W 0  This bit indicates that there is a data overwritten situation in BIT_ADC_DATA_GLOBAL takes place. A data overwritten situation is that a former conversion data is NOT read before a new conversion is written into data field. 0: There is no data overwritten case. 1: There is a data overwritten case. */
#define ADC_SHIFT_DAT_GLOBAL_DAT                0
#define ADC_MASK_DAT_GLOBAL_DAT                 ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field contains the newest conversion data of a conversion channel in the list. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DAT_CH0
 * @brief  ADC Channel 0 Data Register               (@ 0X06C)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DAT_CH0_RDY                   22
#define ADC_BIT_DAT_CH0_RDY                     ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit indicates that a conversion is done. Every time a conversion is done, this bit should be set to 1 and it would be cleared to 0 when a read operation of dat_ch0. */
#define ADC_SHIFT_DAT_CH0_OVW                   21
#define ADC_BIT_DAT_CH0_OVW                     ((u32)0x00000001 << 21)                             /*!<R/W 0  This bit indicates that there is a data overwritten situation in dat_ch0 takes place. A data overwritten situation is that a former conversion data is NOT read before a new conversion is written into data field. 0: There is no data overwritten case. 1: There is a data overwritten case. */
#define ADC_SHIFT_DAT_CH0_DAT                   0
#define ADC_MASK_DAT_CH0_DAT                    ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field contains the newest conversion data of channel 0. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DAT_CH1
 * @brief  ADC Channel 1 Data Register               (@ 0X070)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DAT_CH1_RDY                   22
#define ADC_BIT_DAT_CH1_RDY                     ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit indicates that a conversion is done. Every time a conversion is done, this bit should be set to 1 and it would be cleared to 0 when a read operation of dat_ch1. */
#define ADC_SHIFT_DAT_CH1_OVW                   21
#define ADC_BIT_DAT_CH1_OVW                     ((u32)0x00000001 << 21)                             /*!<R/W 0  This bit indicates that there is a data overwritten situation in dat_ch1 takes place. A data overwritten situation is that a former conversion data is NOT read before a new conversion is written into data field. 0: There is no data overwritten case. 1: There is a data overwritten case. */
#define ADC_SHIFT_DAT_CH1_DAT                   0
#define ADC_MASK_DAT_CH1_DAT                    ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field contains the newest conversion data of channel 1. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DAT_CH2
 * @brief  ADC Channel 2 Data Register               (@ 0X074)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DAT_CH2_RDY                   22
#define ADC_BIT_DAT_CH2_RDY                     ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit indicates that a conversion is done. Every time a conversion is done, this bit should be set to 1 and it would be cleared to 0 when a read operation of dat_ch2. */
#define ADC_SHIFT_DAT_CH2_OVW                   21
#define ADC_BIT_DAT_CH2_OVW                     ((u32)0x00000001 << 21)                             /*!<R/W 0  This bit indicates that there is a data overwritten situation in dat_ch2 takes place. A data overwritten situation is that a former conversion data is NOT read before a new conversion is written into data field. 0: There is no data overwritten case. 1: There is a data overwritten case. */
#define ADC_SHIFT_DAT_CH2_DAT                   0
#define ADC_MASK_DAT_CH2_DAT                    ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field contains the newest conversion data of channel 2. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DAT_CH3
 * @brief  ADC Channel 3 Data Register               (@ 0X078)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DAT_CH3_RDY                   22
#define ADC_BIT_DAT_CH3_RDY                     ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit indicates that a conversion is done. Every time a conversion is done, this bit should be set to 1 and it would be cleared to 0 when a read operation of dat_ch3. */
#define ADC_SHIFT_DAT_CH3_OVW                   21
#define ADC_BIT_DAT_CH3_OVW                     ((u32)0x00000001 << 21)                             /*!<R/W 0  This bit indicates that there is a data overwritten situation in dat_ch3 takes place. A data overwritten situation is that a former conversion data is NOT read before a new conversion is written into data field. 0: There is no data overwritten case. 1: There is a data overwritten case. */
#define ADC_SHIFT_DAT_CH3_DAT                   0
#define ADC_MASK_DAT_CH3_DAT                    ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field contains the newest conversion data of channel 3. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DAT_CH4
 * @brief  ADC Channel 4 Data Register               (@ 0X07C)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DAT_CH4_RDY                   22
#define ADC_BIT_DAT_CH4_RDY                     ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit indicates that a conversion is done. Every time a conversion is done, this bit should be set to 1 and it would be cleared to 0 when a read operation of dat_ch4. */
#define ADC_SHIFT_DAT_CH4_OVW                   21
#define ADC_BIT_DAT_CH4_OVW                     ((u32)0x00000001 << 21)                             /*!<R/W 0  This bit indicates that there is a data overwritten situation in dat_ch4 takes place. A data overwritten situation is that a former conversion data is NOT read before a new conversion is written into data field. 0: There is no data overwritten case. 1: There is a data overwritten case. */
#define ADC_SHIFT_DAT_CH4_DAT                   0
#define ADC_MASK_DAT_CH4_DAT                    ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field contains the newest conversion data of channel 4. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DAT_CH5
 * @brief  ADC Channel 5 Data Register               (@ 0X080)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DAT_CH5_RDY                   22
#define ADC_BIT_DAT_CH5_RDY                     ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit indicates that a conversion is done. Every time a conversion is done, this bit should be set to 1 and it would be cleared to 0 when a read operation of dat_ch5. */
#define ADC_SHIFT_DAT_CH5_OVW                   21
#define ADC_BIT_DAT_CH5_OVW                     ((u32)0x00000001 << 21)                             /*!<R/W 0  This bit indicates that there is a data overwritten situation in dat_ch5 takes place. A data overwritten situation is that a former conversion data is NOT read before a new conversion is written into data field. 0: There is no data overwritten case. 1: There is a data overwritten case. */
#define ADC_SHIFT_DAT_CH5_DAT                   0
#define ADC_MASK_DAT_CH5_DAT                    ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field contains the newest conversion data of channel 5. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DAT_CH6
 * @brief  ADC Channel 6 Data Register               (@ 0X084)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DAT_CH6_RDY                   22
#define ADC_BIT_DAT_CH6_RDY                     ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit indicates that a conversion is done. Every time a conversion is done, this bit should be set to 1 and it would be cleared to 0 when a read operation of dat_ch6. */
#define ADC_SHIFT_DAT_CH6_OVW                   21
#define ADC_BIT_DAT_CH6_OVW                     ((u32)0x00000001 << 21)                             /*!<R/W 0  This bit indicates that there is a data overwritten situation in dat_ch6 takes place. A data overwritten situation is that a former conversion data is NOT read before a new conversion is written into data field. 0: There is no data overwritten case. 1: There is a data overwritten case. */
#define ADC_SHIFT_DAT_CH6_DAT                   0
#define ADC_MASK_DAT_CH6_DAT                    ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field contains the newest conversion data of channel 6. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DAT_CH7
 * @brief  ADC Channel 7 Data Register               (@ 0X088)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DAT_CH7_RDY                   22
#define ADC_BIT_DAT_CH7_RDY                     ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit indicates that a conversion is done. Every time a conversion is done, this bit should be set to 1 and it would be cleared to 0 when a read operation of dat_ch7. */
#define ADC_SHIFT_DAT_CH7_OVW                   21
#define ADC_BIT_DAT_CH7_OVW                     ((u32)0x00000001 << 21)                             /*!<R/W 0  This bit indicates that there is a data overwritten situation in dat_ch7 takes place. A data overwritten situation is that a former conversion data is NOT read before a new conversion is written into data field. 0: There is no data overwritten case. 1: There is a data overwritten case. */
#define ADC_SHIFT_DAT_CH7_DAT                   0
#define ADC_MASK_DAT_CH7_DAT                    ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field contains the newest conversion data of channel 7. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DAT_CH8
 * @brief  ADC Channel 8 Data Register               (@ 0X08C)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DAT_CH8_RDY                   22
#define ADC_BIT_DAT_CH8_RDY                     ((u32)0x00000001 << 22)                             /*!<R/W 0  This bit indicates that a conversion is done. Every time a conversion is done, this bit should be set to 1 and it would be cleared to 0 when a read operation of dat_ch8. */
#define ADC_SHIFT_DAT_CH8_OVW                   21
#define ADC_BIT_DAT_CH8_OVW                     ((u32)0x00000001 << 21)                             /*!<R/W 0  This bit indicates that there is a data overwritten situation in dat_ch8 takes place. A data overwritten situation is that a former conversion data is NOT read before a new conversion is written into data field. 0: There is no data overwritten case. 1: There is a data overwritten case. */
#define ADC_SHIFT_DAT_CH8_DAT                   0
#define ADC_MASK_DAT_CH8_DAT                    ((u32)0x00000FFF << 0)                              /*!<R/W 0  This field contains the newest conversion data of channel 8. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DMA_CON
 * @brief  ADC DMA Control Register                  (@ 0X090)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_DMA_CON_LVL                   8
#define ADC_MASK_DMA_CON_LVL                    ((u32)0x0000003F << 8)                              /*!<R/W 0  This field defines the FIFO threshold level that ADC module should make a DMA request to DMA module. A value of 0 sets the threshold for 1 entry, and a value of 15 sets the threshold for 16 entries. */
#define ADC_SHIFT_DMA_CON_EN                    0
#define ADC_BIT_DMA_CON_EN                      ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit controls that DMA function of ADC is enabled or not. 0: ADC DMA is disabled. 1: ADC DMA is enabled. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_FLR
 * @brief  ADC FIFO Level Register                   (@ 0X094)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_FLR                           0
#define ADC_MASK_FLR                            ((u32)0x0000007F << 0)                              /*!<R/W 0  This field records the current ADC FIFO entry number. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_CLR_FIFO
 * @brief  ADC Clear FIFO Register                   (@ 0X098)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CLR_FIFO                      0
#define ADC_BIT_CLR_FIFO                        ((u32)0x00000001 << 0)                              /*!<R/W 0  This bit is used to clear FIFO contents and makes it to the default status. Every time this bit is set to 1, FIFO would be cleared to the default status. Software should set this bit to 0 after FIFO is cleared. 0: No effect. 1: Clear FIFO. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_CLK_DIV
 * @brief  ADC Clock Division Register               (@ 0X09C)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_CLK_DIV                       0
#define ADC_MASK_CLK_DIV                        ((u32)0x00000007 << 0)                              /*!<R/W 0  This field defines clock divider level of ADC module. A value of 0 is for clock divided by 5. A value of 1 is for clock divided by 10. A value of 2 is for clock divided by 16. A value of 3 is for clock divided by 32. A value of 4 is for clock divided by 64. */
/** @} */

/**************************************************************************//**
 * @defgroup ADC_DLY_CNT
 * @brief  ADC Delay Count Register                  (@ 0X0A0)
 * @{
 *****************************************************************************/
/* Weide removed the auto-generated bitfields on Jason's advice, as these registers will not be used by customer.*/

/**************************************************************************//**
 * @defgroup ADC_DBG_SEL
 * @brief  ADC Debug Select Register                 (@ 0X0A4)
 * @{
 *****************************************************************************/
/* Weide removed the auto-generated bitfields on Jason's advice, as these registers will not be used by customer.*/


/**************************************************************************//**
 * @defgroup ADC_VREF_SETTLE_TIME
 * @brief  ADC Reference Voltage Settle Time Register (@ 0X0BC)
 * @{
 *****************************************************************************/
#define ADC_SHIFT_VREF_SETTLE_TIME                   0
#define ADC_MASK_VREF_SETTLE_TIME                    ((u32)0x00000003 << 0)                              /*!<R/W 0  This field defines the time required for the reference voltage to settle to ensure stability of ADC operations. By default, it will be 20us. 0: 20 us 1: 40 us 2: 80 us 3: 160 us */
/** @} */


/**************************************************************************//**
 * @defgroup rtl8735b_ADC
 * @{
 * @brief rtl8735b_ADC Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t ADC_CONF ;                          /*!<  ADC Configuration Register register,  Address offset: 0x000 */
	__IO uint32_t ADC_IN_TYPE ;                       /*!<  ADC Input Type Register register,  Address offset: 0x004 */
	__IO uint32_t ADC_COMP_TH_CH0 ;                   /*!<  ADC Channel 0 Comparison Threshold Register register,  Address offset: 0x008 */
	__IO uint32_t ADC_COMP_TH_CH1 ;                   /*!<  ADC Channel 1 Comparison Threshold Register register,  Address offset: 0x00C */
	__IO uint32_t ADC_COMP_TH_CH2 ;                   /*!<  ADC Channel 2 Comparison Threshold Register register,  Address offset: 0x010 */
	__IO uint32_t ADC_COMP_TH_CH3 ;                   /*!<  ADC Channel 3 Comparison Threshold Register register,  Address offset: 0x014 */
	__IO uint32_t ADC_COMP_TH_CH4 ;                   /*!<  ADC Channel 4 Comparison Threshold Register register,  Address offset: 0x018 */
	__IO uint32_t ADC_COMP_TH_CH5 ;                   /*!<  ADC Channel 5 Comparison Threshold Register register,  Address offset: 0x01C */
	__IO uint32_t ADC_COMP_TH_CH6 ;                   /*!<  ADC Channel 6 Comparison Threshold Register register,  Address offset: 0x020 */
	__IO uint32_t ADC_COMP_TH_CH7 ;                   /*!<  ADC Channel 7 Comparison Threshold Register register,  Address offset: 0x024 */
	__IO uint32_t ADC_COMP_TH_CH8 ;                   /*!<  ADC Channel 8 Comparison Threshold Register register,  Address offset: 0x028 */
	__IO uint32_t ADC_COMP_CTRL ;                     /*!<  ADC Comparison Control Register register,  Address offset: 0x02C */
	__I  uint32_t ADC_COMP_STS ;                      /*!<  ADC Comparison Status Register register,  Address offset: 0x030 */
	__IO uint32_t ADC_CHSW_LIST_0 ;                   /*!<  ADC Channel Swtich List 0 Register register,  Address offset: 0x034 */
	__IO uint32_t ADC_CHSW_LIST_1 ;                   /*!<  ADC Channel Swtich List 1 Register register,  Address offset: 0x038 */
	__IO uint32_t ADC_RST_LIST ;                      /*!<  ADC Reset List Register register,  Address offset: 0x03C */
	__IO uint32_t ADC_AUTO_CHSW_CTRL ;                /*!<  ADC Auto Channel Switch Control Register register,  Address offset: 0x040 */
	__IO uint32_t ADC_SW_TRIG ;                       /*!<  ADC Software Trigger Register register,  Address offset: 0x044 */
	__I  uint32_t ADC_LAST_ITEM ;                     /*!<  ADC Last Item Register register,  Address offset: 0x048 */
	__I  uint32_t ADC_STS ;                           /*!<  ADC Busy_Ready Status Register register,  Address offset: 0x04C */
	__IO uint32_t ADC_INTR_CTRL ;                     /*!<  ADC Interrupt Control Register register,  Address offset: 0x050 */
	__I  uint32_t ADC_INTR_RAW_STS ;                  /*!<  ADC Interrupt RAW Status Register register,  Address offset: 0x054 */
	__IO uint32_t ADC_INTR_STS ;                      /*!<  ADC Interrupt Status Register register,  Address offset: 0x058 */
	__IO uint32_t ADC_IT_CHNO_CON ;                   /*!<  ADC Conversion Interrupt Channel Number Configuration Register register,  Address offset: 0x05C */
	__IO uint32_t ADC_FULL_LVL ;                      /*!<  ADC FIFO Full Level Register register,  Address offset: 0x060 */
	__IO uint32_t ADC_TRIG_TIMER_SEL ;                /*!<  ADC Trigger Timer Select Register register,  Address offset: 0x064 */
	__IO uint32_t ADC_DAT_GLOBAL ;                    /*!<  ADC Global Data Register register,  Address offset: 0x068 */
	__IO uint32_t ADC_DAT_CH0 ;                       /*!<  ADC Channel 0 Data Register register,  Address offset: 0x06C */
	__IO uint32_t ADC_DAT_CH1 ;                       /*!<  ADC Channel 1 Data Register register,  Address offset: 0x070 */
	__IO uint32_t ADC_DAT_CH2 ;                       /*!<  ADC Channel 2 Data Register register,  Address offset: 0x074 */
	__IO uint32_t ADC_DAT_CH3 ;                       /*!<  ADC Channel 3 Data Register register,  Address offset: 0x078 */
	__IO uint32_t ADC_DAT_CH4 ;                       /*!<  ADC Channel 4 Data Register register,  Address offset: 0x07C */
	__IO uint32_t ADC_DAT_CH5 ;                       /*!<  ADC Channel 5 Data Register register,  Address offset: 0x080 */
	__IO uint32_t ADC_DAT_CH6 ;                       /*!<  ADC Channel 6 Data Register register,  Address offset: 0x084 */
	__IO uint32_t ADC_DAT_CH7 ;                       /*!<  ADC Channel 7 Data Register register,  Address offset: 0x088 */
	__IO uint32_t ADC_DAT_CH8 ;                       /*!<  ADC Channel 8 Data Register register,  Address offset: 0x08C */
	__IO uint32_t ADC_DMA_CON ;                       /*!<  ADC DMA Control Register register,  Address offset: 0x090 */
	__IO uint32_t ADC_FLR ;                           /*!<  ADC FIFO Level Register register,  Address offset: 0x094 */
	__IO uint32_t ADC_CLR_FIFO ;                      /*!<  ADC Clear FIFO Register register,  Address offset: 0x098 */
	__IO uint32_t ADC_CLK_DIV ;                       /*!<  ADC Clock Division Register register,  Address offset: 0x09C */
	__IO uint32_t ADC_DLY_CNT ; 					  /*!<  ADC Delay Count Register register,  Address offset: 0x0A0 */
	__IO uint32_t ADC_DBG_SEL ; 					  /*!<  ADC Debug Select Register register,  Address offset: 0x0A4 */
	__I  uint32_t ADC_RSVD0 ;						  /*!<  Reserved0 register,  Address offset: 0x0A8 */
	__I  uint32_t ADC_RSVD1 ;						  /*!<  Reserved1 register,  Address offset: 0x0AC */
	__I  uint32_t ADC_RSVD2 ;						  /*!<  Reserved2 register,  Address offset: 0x0B0 */
	__I  uint32_t ADC_RSVD3 ;						  /*!<  Reserved3 register,  Address offset: 0x0B4 */
	__I  uint32_t ADC_RSVD4 ;						  /*!<  Reserved4 register,  Address offset: 0x0B8 */
	__IO uint32_t ADC_VREF_SETTLE_TIME ;			  /*!<  ADC Reference Voltage Settle Time Register register, Address offset: 0x0BC */
} ADC_TypeDef;
/** @} */

#endif
