/**************************************************************************//**
 * @file      rtl8735b_vdr_s_type.h
 * @brief
 * @version   V1.00
 * @date      2018-6-12 12:5:43
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef _RTL8710C_VENDOR_VDR_S_TYPE_H_
#define _RTL8710C_VENDOR_VDR_S_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_VDR_S_REG_TYPE

/**
 * @addtogroup hs_hal_vdr_s_reg VDR_S Register Type.
 * @ingroup hs_hal_vendor
 * @{
 */

/**
  \brief Union type to access vdr_s_sec_low_pri_int_mode (@ 0x00000000).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000000) Secure Low Priority Interrupt Trigger Mode Control
                                                                  Register                                                   */

	struct {
		__IOM uint32_t sec_low_pri_int0_mode : 1; /*!< [0..0] Each bit control corresponding interrupt mode. 1: Rising
                                                   edge trigger 0: High level active                                         */
	} b;                                        /*!< bit fields for vdr_s_sec_low_pri_int_mode */
} vdr_s_sec_low_pri_int_mode_t, *pvdr_s_sec_low_pri_int_mode_t;

/**
  \brief Union type to access vdr_s_sec_low_pri_int_imr (@ 0x00000004).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000004) Secure Low Priority Interrupt Mask Register                */

	struct {
		__IOM uint32_t rxi300_int_imr : 1;        /*!< [0..0] 1: Enable 0: Disable                                               */
	} b;                                        /*!< bit fields for vdr_s_sec_low_pri_int_imr */
} vdr_s_sec_low_pri_int_imr_t, *pvdr_s_sec_low_pri_int_imr_t;

/**
  \brief Union type to access vdr_s_secure_low_pri_int_isr (@ 0x00000008).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000008) Secure Low Priority Interrupt Pending Status
                                                                  Register                                                   */

	struct {
		__IOM uint32_t rxi300_secure_bus_isr : 1; /*!< [0..0] RXI300 secure bus interrupt pending status. Wite 1 clear.          */
	} b;                                        /*!< bit fields for vdr_s_secure_low_pri_int_isr */
} vdr_s_secure_low_pri_int_isr_t, *pvdr_s_secure_low_pri_int_isr_t;

/**
  \brief Union type to access vdr_s_secure_gdma0_isr (@ 0x0000000C).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000010) Secure GDMA Interrupt Pending Status Register              */

	struct {
		__IM  uint32_t gdma0_ch0_isr : 1;         /*!< [0..0] Secure GDMA 0 channel 0 interrupt pending status                     */
		__IM  uint32_t gdma0_ch1_isr : 1;         /*!< [1..1] Secure GDMA 0 channel 1 interrupt pending status                     */
		__IM  uint32_t gdma0_ch2_isr : 1;         /*!< [2..2] Secure GDMA 0 channel 2 interrupt pending status                     */
		__IM  uint32_t gdma0_ch3_isr : 1;         /*!< [3..3] Secure GDMA 0 channel 3 interrupt pending status                     */
		__IM  uint32_t gdma0_ch4_isr : 1;         /*!< [4..4] Secure GDMA 0 channel 4 interrupt pending status                     */
		__IM  uint32_t gdma0_ch5_isr : 1;         /*!< [5..5] Secure GDMA 0 channel 5 interrupt pending status                     */
	} b;                                        /*!< bit fields for vdr_s_secure_gdma0_isr */
} vdr_s_gdma0_isr_t, *pvdr_s_gdma0_isr_t;

/**
  \brief Union type to access vdr_s_secure_gdma0_isr (@ 0x00000010).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000010) Secure GDMA Interrupt Pending Status Register              */

	struct {
		__IM  uint32_t gdma1_ch0_isr : 1;         /*!< [0..0] Secure GDMA 1 channel 0 interrupt pending status                     */
		__IM  uint32_t gdma1_ch1_isr : 1;         /*!< [1..1] Secure GDMA 1 channel 1 interrupt pending status                     */
		__IM  uint32_t gdma1_ch2_isr : 1;         /*!< [2..2] Secure GDMA 1 channel 2 interrupt pending status                     */
		__IM  uint32_t gdma1_ch3_isr : 1;         /*!< [3..3] Secure GDMA 1 channel 3 interrupt pending status                     */
		__IM  uint32_t gdma1_ch4_isr : 1;         /*!< [4..4] Secure GDMA 1 channel 4 interrupt pending status                     */
		__IM  uint32_t gdma1_ch5_isr : 1;         /*!< [5..5] Secure GDMA 1 channel 5 interrupt pending status                     */
	} b;                                        /*!< bit fields for vdr_s_secure_gdma0_isr */
} vdr_s_gdma1_isr_t, *pvdr_s_gdma1_isr_t;


/**
  \brief Union type to access vdr_s_super_sec_ef_ctrl (@ 0x00000020).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000020) Super Secure eFuse Control Register                        */

	struct {
		__OM  uint32_t sec_super_sec_ef_lock : 1; /*!< [0..0] When this bit is written to '1', this bit can not be
                                                   written to '0'. Beside the high speed platform is reset.
                                                   1: Super secure zone can not be accessed. 0: Super secure
                                                   zone just can be accessed by secure state. (AXI_PORT[1]
                                                   = 0)                                                                      */
	} b;                                        /*!< bit fields for vdr_s_super_sec_ef_ctrl */
} vdr_s_super_sec_ef_ctrl_t, *pvdr_s_super_sec_ef_ctrl_t;

/**
  \brief Union type to access vdr_s_non_fixed_secure_key0 (@ 0x00000030).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000030) Non-Fixed Secure Key Register0                             */

	struct {
		__OM  uint32_t non_fixed_secure_key : 32; /*!< [31..0] Secure JTAG Key This register just can be written once.
                                                   After that, hardware need disable the writing function                    */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_secure_key0 */
} vdr_s_non_fixed_secure_key0_t, *pvdr_s_non_fixed_secure_key0_t;

/**
  \brief Union type to access vdr_s_non_fixed_secure_key1 (@ 0x00000034).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000034) Non-Fixed Secure Key Register1                             */

	struct {
		__OM  uint32_t non_fixed_secure_key : 32; /*!< [31..0] Secure JTAG Key This register just can be written once.
                                                   After that, hardware need disable the writing function                    */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_secure_key1 */
} vdr_s_non_fixed_secure_key1_t, *pvdr_s_non_fixed_secure_key1_t;

/**
  \brief Union type to access vdr_s_non_fixed_secure_key2 (@ 0x00000038).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000038) Non-Fixed Secure Key Register2                             */

	struct {
		__OM  uint32_t non_fixed_secure_key : 32; /*!< [31..0] Secure JTAG Key This register just can be written once.
                                                   After that, hardware need disable the writing function                    */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_secure_key2 */
} vdr_s_non_fixed_secure_key2_t, *pvdr_s_non_fixed_secure_key2_t;

/**
  \brief Union type to access vdr_s_non_fixed_secure_key3 (@ 0x0000003C).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x0000003C) Non-Fixed Secure Key Register3                             */

	struct {
		__OM  uint32_t non_fixed_secure_key : 32; /*!< [31..0] Secure JTAG Key This register just can be written once.
                                                   After that, hardware need disable the writing function                    */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_secure_key3 */
} vdr_s_non_fixed_secure_key3_t, *pvdr_s_non_fixed_secure_key3_t;

/**
  \brief Union type to access vdr_s_non_fixed_secure_key4 (@ 0x00000040).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000040) Non-Fixed Secure Key Register4                             */

	struct {
		__OM  uint32_t non_fixed_secure_key : 32; /*!< [31..0] Secure JTAG Key This register just can be written once.
                                                   After that, hardware need disable the writing function                    */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_secure_key4 */
} vdr_s_non_fixed_secure_key4_t, *pvdr_s_non_fixed_secure_key4_t;

/**
  \brief Union type to access vdr_s_non_fixed_secure_key5 (@ 0x00000044).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000044) Non-Fixed Secure Key Register5                             */

	struct {
		__OM  uint32_t non_fixed_secure_key : 32; /*!< [31..0] Secure JTAG Key This register just can be written once.
                                                   After that, hardware need disable the writing function                    */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_secure_key5 */
} vdr_s_non_fixed_secure_key5_t, *pvdr_s_non_fixed_secure_key5_t;

/**
  \brief Union type to access vdr_s_non_fixed_secure_key6 (@ 0x00000048).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000048) Non-Fixed Secure Key Register6                             */

	struct {
		__OM  uint32_t non_fixed_secure_key : 32; /*!< [31..0] Secure JTAG Key This register just can be written once.
                                                   After that, hardware need disable the writing function                    */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_secure_key6 */
} vdr_s_non_fixed_secure_key6_t, *pvdr_s_non_fixed_secure_key6_t;

/**
  \brief Union type to access vdr_s_non_fixed_secure_key7 (@ 0x0000004C).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x0000004C) Non-Fixed Secure Key Register7                             */

	struct {
		__OM  uint32_t non_fixed_secure_key : 32; /*!< [31..0] Secure JTAG Key This register just can be written once.
                                                   After that, hardware need disable the writing function                    */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_secure_key7 */
} vdr_s_non_fixed_secure_key7_t, *pvdr_s_non_fixed_secure_key7_t;

/**
  \brief Union type to access vdr_s_non_fixed_non_secure_key0 (@ 0x00000050).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000050) Non-Fixed Non-Secure Key Register0                         */

	struct {
		__OM  uint32_t non_fixed_non_secure_key : 32;/*!< [31..0] Non-Secure JTAG Key This register just can be written
                                                   once. After that, hardware need disable the writing function              */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_non_secure_key0 */
} vdr_s_non_fixed_non_secure_key0_t, *pvdr_s_non_fixed_non_secure_key0_t;

/**
  \brief Union type to access vdr_s_non_fixed_non_secure_key1 (@ 0x00000054).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000054) Non-Fixed Non-Secure Key Register1                         */

	struct {
		__OM  uint32_t non_fixed_non_secure_key : 32;/*!< [31..0] Non-Secure JTAG Key This register just can be written
                                                   once. After that, hardware need disable the writing function              */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_non_secure_key1 */
} vdr_s_non_fixed_non_secure_key1_t, *pvdr_s_non_fixed_non_secure_key1_t;

/**
  \brief Union type to access vdr_s_non_fixed_non_secure_key2 (@ 0x00000058).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000058) Non-Fixed Non-Secure Key Register2                         */

	struct {
		__OM  uint32_t non_fixed_non_secure_key : 32;/*!< [31..0] Non-Secure JTAG Key This register just can be written
                                                   once. After that, hardware need disable the writing function              */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_non_secure_key2 */
} vdr_s_non_fixed_non_secure_key2_t, *pvdr_s_non_fixed_non_secure_key2_t;

/**
  \brief Union type to access vdr_s_non_fixed_non_secure_key3 (@ 0x0000005C).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x0000005C) Non-Fixed Non-Secure Key Register3                         */

	struct {
		__OM  uint32_t non_fixed_non_secure_key : 32;/*!< [31..0] Non-Secure JTAG Key This register just can be written
                                                   once. After that, hardware need disable the writing function              */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_non_secure_key3 */
} vdr_s_non_fixed_non_secure_key3_t, *pvdr_s_non_fixed_non_secure_key3_t;

/**
  \brief Union type to access vdr_s_non_fixed_non_secure_key4 (@ 0x00000060).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000060) Non-Fixed Non-Secure Key Register4                         */

	struct {
		__OM  uint32_t non_fixed_non_secure_key : 32;/*!< [31..0] Non-Secure JTAG Key This register just can be written
                                                   once. After that, hardware need disable the writing function              */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_non_secure_key4 */
} vdr_s_non_fixed_non_secure_key4_t, *pvdr_s_non_fixed_non_secure_key4_t;

/**
  \brief Union type to access vdr_s_non_fixed_non_secure_key5 (@ 0x00000064).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000064) Non-Fixed Non-Secure Key Register5                         */

	struct {
		__OM  uint32_t non_fixed_non_secure_key : 32;/*!< [31..0] Non-Secure JTAG Key This register just can be written
                                                   once. After that, hardware need disable the writing function              */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_non_secure_key5 */
} vdr_s_non_fixed_non_secure_key5_t, *pvdr_s_non_fixed_non_secure_key5_t;

/**
  \brief Union type to access vdr_s_non_fixed_non_secure_key6 (@ 0x00000068).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x00000068) Non-Fixed Non-Secure Key Register6                         */

	struct {
		__OM  uint32_t non_fixed_non_secure_key : 32;/*!< [31..0] Non-Secure JTAG Key This register just can be written
                                                   once. After that, hardware need disable the writing function              */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_non_secure_key6 */
} vdr_s_non_fixed_non_secure_key6_t, *pvdr_s_non_fixed_non_secure_key6_t;

/**
  \brief Union type to access vdr_s_non_fixed_non_secure_key7 (@ 0x0000006C).
*/
typedef union {
	__OM  uint32_t w;                           /*!< (@ 0x0000006C) Non-Fixed Non-Secure Key Register7                         */

	struct {
		__OM  uint32_t non_fixed_non_secure_key : 32;/*!< [31..0] Non-Secure JTAG Key This register just can be written
                                                   once. After that, hardware need disable the writing function              */
	} b;                                        /*!< bit fields for vdr_s_non_fixed_non_secure_key7 */
} vdr_s_non_fixed_non_secure_key7_t, *pvdr_s_non_fixed_non_secure_key7_t;

/**
  \brief Union type to access vdr_s_secure_jtag_swd_ctrl (@ 0x00000070).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000070) Secure JTAG SWD Control Register                           */

	struct {
		__IOM uint32_t fw_ready_sc : 1;           /*!< [0..0] In Non-Fixed Key Mode, Secure JTAG/SWD wait this signal.
                                                   0: Secue JTAG/SWD cannot execute the procedure of the unlocking
                                                   JTAG/SWD. 1: Secue JTAG/SWD can execute the procedure of
                                                   the unlocking JTAG/SWD. This register just can be written
                                                   once. After that, hardware need disable the writing function              */
		__IOM uint32_t fw_ready_nonsc : 1;        /*!< [1..1] In Non-Fixed Key Mode, Non-Secure JTAG/SWD wait this
                                                   signal. 0: Secue JTAG/SWD cannot execute the procedure
                                                   of the unlocking JTAG/SWD. 1: Secue JTAG/SWD can execute
                                                   the procedure of the unlocking JTAG/SWD. This register
                                                   just can be written once. After that, hardware need disable
                                                   the writing function                                                      */
	} b;                                        /*!< bit fields for vdr_s_secure_jtag_swd_ctrl */
} vdr_s_secure_jtag_swd_ctrl_t, *pvdr_s_secure_jtag_swd_ctrl_t;

/** @} */ /* End of group hal_vdr_s_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_VDR_S_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8710C_VENDOR_VDR_S_TYPE_H_

