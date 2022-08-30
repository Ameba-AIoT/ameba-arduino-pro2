/**************************************************************************//**
 * @file      rtl8710c_vdr_type.h
 * @brief
 * @version   V1.00
 * @date      2018-12-13 15:8:15
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

#ifndef _RTL8710C_VENDOR_VDR_TYPE_H_
#define _RTL8710C_VENDOR_VDR_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_VDR_REG_TYPE

/**
 * @addtogroup hal_vdr_reg VDR Register Type.
 * @ingroup hs_hal_vendor
 * @{
 */

/**
  \brief Union type to access vdr_watch_dog_timer (@ 0x00000000).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000000) Watch Dog Timer Control Register                           */

	struct {
		__IOM uint32_t vndr_divfactor : 16;       /*!< [15..0] Dividing factor. Watch dog timer is count with 64KHz/(divfactor+1).
                                                   Minimum dividing factor is 1.                                             */
		__IOM uint32_t wdt_en_byte : 8;           /*!< [23..16] Set 0xA5 to enable watch dog timer                               */
		__OM  uint32_t wdt_clear  : 1;            /*!< [24..24] Write 1 to clear timer                                           */
		__IOM uint32_t cnt_limit  : 4;            /*!< [28..25] 0: 0x001 1: 0x003 2: 0x007 3: 0x00F 4: 0x01F 5: 0x03F
                                                   6: 0x07F 7: 0x0FF 8: 0x1FF 9: 0x3FF 10: 0x7FF 11~15: 0xFFF                */
		__IM  uint32_t            : 1;
		__IOM uint32_t wdt_mode   : 1;            /*!< [30..30] 1: Reset system, 0: Interrupt CPU                                */
		__IOM uint32_t wdt_to     : 1;            /*!< [31..31] Watch dog timer timeout. 1 cycle pulse, Write 1 to
                                                   clear.                                                                    */
	} b;                                        /*!< bit fields for vdr_watch_dog_timer */
} vdr_watch_dog_timer_t, *pvdr_watch_dog_timer_t;

/**
  \brief Union type to access vdr_low_pri_int_mode (@ 0x00000004).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000004) Low Priority Interrupt Trigger Mode Control Register       */

	struct {
		__IOM uint32_t low_pri_int0_mode : 1;     /*!< [0..0] Each bit control corresponding interrupt mode. 1: Rising
                                                   edge trigger 0: High level active                                         */
		__IOM uint32_t low_pri_int1_mode : 1;     /*!< [1..1] Each bit control corresponding interrupt mode. 1: Rising
                                                   edge trigger 0: High level active                                         */
		__IOM uint32_t low_pri_int2_mode : 1;     /*!< [2..2] Each bit control corresponding interrupt mode. 1: Rising
                                                   edge trigger 0: High level active                                         */
		__IOM uint32_t low_pri_int13_mode : 1;    /*!< [3..3] Each bit control corresponding interrupt mode. 1: Rising
                                                   edge trigger 0: High level active                                         */
		__IOM uint32_t low_pri_int4_mode : 1;     /*!< [4..4] Each bit control corresponding interrupt mode. 1: Rising
                                                   edge trigger 0: High level active                                         */
	} b;                                        /*!< bit fields for vdr_low_pri_int_mode */
} vdr_low_pri_int_mode_t, *pvdr_low_pri_int_mode_t;

/**
  \brief Union type to access vdr_low_pri_int_imr (@ 0x00000008).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000008) Low Priority Interrupt Mask Register                       */

	struct {
		__IOM uint32_t rxi_300_en : 1;            /*!< [0..0] Each bit enable corresponding interrupt. 1: Enable 0:
                                                   Disable                                                                   */
		__IOM uint32_t spic_int_en : 1;           /*!< [1..1] Each bit enable corresponding interrupt. 1: Enable 0:
                                                   Disable                                                                   */
		__IOM uint32_t psrm_cal_fail_int_en : 1;  /*!< [2..2] Each bit enable corresponding interrupt. 1: Enable 0:
                                                   Disable                                                                   */
		__IOM uint32_t psrm_time_out_int_en : 1;  /*!< [3..3] Each bit enable corresponding interrupt. 1: Enable 0:
                                                   Disable                                                                   */
		__IOM uint32_t scorebord_int_en : 1;      /*!< [4..4] Each bit enable corresponding interrupt. 1: Enable 0:
                                                   Disable                                                                   */
	} b;                                        /*!< bit fields for vdr_low_pri_int_imr */
} vdr_low_pri_int_imr_t, *pvdr_low_pri_int_imr_t;

/**
  \brief Union type to access vdr_low_pri_int_isr (@ 0x0000000C).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x0000000C) Low Priority Interrupt Pending Status Register             */

	struct {
		__IOM uint32_t rxi_300_int : 1;           /*!< [0..0] RXI300 bus interrupt status. Write 1 clear.                        */
		__IOM uint32_t spic_int   : 1;            /*!< [1..1] SPIC interrupt status, Write 1 clear.                              */
		__IOM uint32_t psrm_cal_fail_int : 1;     /*!< [2..2] PSRAM calibration fail interrupt status. Write 1 clear.            */
		__IOM uint32_t psrm_time_out_int : 1;     /*!< [3..3] PSRAM calibration timeout interrupt status. Write 1 clear.         */
		__IM  uint32_t scoreboard_int : 1;        /*!< [4..4] Scoreboard interrupt status                                        */
	} b;                                        /*!< bit fields for vdr_low_pri_int_isr */
} vdr_low_pri_int_isr_t, *pvdr_low_pri_int_isr_t;

/**
  \brief Union type to access vdr_anack_ctrl (@ 0x0000001C).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x0000001C) ANA Clock Control Register                                 */

	struct {
		__IOM uint32_t anack_rpt  : 16;           /*!< [15..0] The calculation value of ANA clock where the reference
                                                   clock is 40MHz.                                                           */
		__IM  uint32_t            : 8;
		__IOM uint32_t anack_sel  : 2;            /*!< [25..24] 00: Calculation of 4M for 32 cycles (for debug use)
                                                   01: Calculation of 128K for 8 cycles 10: Rsvd 11: Rsvd                    */
		__IM  uint32_t            : 5;
		__IOM uint32_t anack_cmd  : 1;            /*!< [31..31] 1: Enable ANACK calculation and indicate busy when
                                                   the calculation process is on-going. 0: Calculation is
                                                   done. Set as 0 by HW when calibration is done.                            */
	} b;                                        /*!< bit fields for vdr_anack_ctrl */
} vdr_anack_ctrl_t, *pvdr_anack_ctrl_t;

/**
  \brief Union type to access vdr_data_fifo_swap_ctrl (@ 0x00000020).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000020) FIFO Data Swap Control Register                            */

	struct {
		__IOM uint32_t i2c0_tx_bit_swap_en : 1;   /*!< [0..0] I2C TX bits swap enable                                            */
		__IOM uint32_t i2c0_rx_bit_swap_en : 1;   /*!< [1..1] I2C RX bits swap enable                                            */
	} b;                                        /*!< bit fields for vdr_data_fifo_swap_ctrl */
} vdr_data_fifo_swap_ctrl_t, *pvdr_data_fifo_swap_ctrl_t;

/**
  \brief Union type to access vdr_gdma0_isr (@ 0x00000030).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000030) GDMA Interrupt Status Register                             */

	struct {
		__IM  uint32_t gdma0_ch0_isr : 1;         /*!< [0..0] Non-Secure GDMA 0 channel 0 interrupt pending status                     */
		__IM  uint32_t gdma0_ch1_isr : 1;         /*!< [1..1] Non-Secure GDMA 0 channel 1 interrupt pending status                     */
		__IM  uint32_t gdma0_ch2_isr : 1;         /*!< [2..2] Non-Secure GDMA 0 channel 2 interrupt pending status                     */
		__IM  uint32_t gdma0_ch3_isr : 1;         /*!< [3..3] Non-Secure GDMA 0 channel 3 interrupt pending status                     */
		__IM  uint32_t gdma0_ch4_isr : 1;         /*!< [4..4] Non-Secure GDMA 0 channel 4 interrupt pending status                     */
		__IM  uint32_t gdma0_ch5_isr : 1;         /*!< [5..5] Non-Secure GDMA 0 channel 5 interrupt pending status                     */
	} b;                                        /*!< bit fields for vdr_gdma0_isr */
} vdr_gdma0_isr_t, *pvdr_gdma0_isr_t;

/**
  \brief Union type to access vdr_gdma1_isr (@ 0x00000034).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000034) GDMA Interrupt Status Register                             */

	struct {
		__IM  uint32_t gdma1_ch0_isr : 1;         /*!< [0..0] Non-Secure GDMA 1 channel 0 interrupt pending status                     */
		__IM  uint32_t gdma1_ch1_isr : 1;         /*!< [1..1] Non-Secure GDMA 1 channel 1 interrupt pending status                     */
		__IM  uint32_t gdma1_ch2_isr : 1;         /*!< [2..2] Non-Secure GDMA 1 channel 2 interrupt pending status                     */
		__IM  uint32_t gdma1_ch3_isr : 1;         /*!< [3..3] Non-Secure GDMA 1 channel 3 interrupt pending status                     */
		__IM  uint32_t gdma1_ch4_isr : 1;         /*!< [4..4] Non-Secure GDMA 1 channel 4 interrupt pending status                     */
		__IM  uint32_t gdma1_ch5_isr : 1;         /*!< [5..5] Non-Secure GDMA 1 channel 5 interrupt pending status                     */
	} b;                                        /*!< bit fields for vdr_gdma0_isr */
} vdr_gdma1_isr_t, *pvdr_gdma1_isr_t;

/**
  \brief Union type to access vdr_wl_isr (@ 0x00000038).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000038) WLAN Interrupt Pending Status Register                     */

	struct {
		__IM  uint32_t wlan_page0_int : 1;        /*!< [0..0] Wlan Page0 Interrupt pending status.                               */
		__IM  uint32_t ahb_local_int : 1;         /*!< [1..1] WL page3 interrupt pending status                                  */
	} b;                                        /*!< bit fields for vdr_wl_isr */
} vdr_wl_isr_t, *pvdr_wl_isr_t;

/**
  \brief Union type to access vdr_mbist_ctrl (@ 0x00000040).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000040) MBIST Control Register                                     */

	struct {
		__IOM uint32_t mbist_clk_en : 1;          /*!< [0..0] bit mbist clock enable.                                            */
		__IOM uint32_t mbist_rstn : 1;            /*!< [1..1] mbist enable for each mbist group                                  */
		__IOM uint32_t mbist_msel : 2;            /*!< [3..2] mbist mode select, 2'b01, 2'b11---> nrml mode enalbe,
                                                   2'b10, 2'b11 -->drf mode enable                                           */
		__IOM uint32_t mbist_resume : 1;          /*!< [4..4] resume mbist drf test                                              */
		__IOM uint32_t mbist_dyn_rden : 1;        /*!< [5..5] dynamic vdd enable                                                 */
		__IOM uint32_t mbist_resume_ps : 1;       /*!< [6..6] resume mbist ps test                                               */
		__IM  uint32_t            : 1;
		__IOM uint32_t mbist_rom_rpt_sel0 : 3;    /*!< [10..8] select mbist rom report result                                    */
	} b;                                        /*!< bit fields for vdr_mbist_ctrl */
} vdr_mbist_ctrl_t, *pvdr_mbist_ctrl_t;

/**
  \brief Union type to access vdr_mbist_func_en_ctrl (@ 0x00000044).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000044) MBIST Function Enable Control Register                     */

	struct {
		__IOM uint32_t mbist_fen_cpu_bt : 1;      /*!< [0..0] enable mbist for BT CPU                                            */
		__IOM uint32_t mbist_fen_128x12x4 : 1;    /*!< [1..1] enable mbist for 128x12x4                                          */
		__IOM uint32_t mbist_fen_512x16_bt : 1;   /*!< [2..2] enable mbist for 512x16 BT                                         */
		__IOM uint32_t mbist_fen_128x16_bt : 1;   /*!< [3..3] enable mbist for 128x16 BT                                         */
		__IOM uint32_t mbist_fen_288x32_bt : 1;   /*!< [4..4] enable mbist for 288x32 BT                                         */
		__IOM uint32_t mbist_fen_03 : 1;          /*!< [5..5] enable mbist 3                                                     */
		__IOM uint32_t mbist_fen_06 : 1;          /*!< [6..6] enable mbist 6                                                     */
		__IOM uint32_t mbist_fen_07 : 1;          /*!< [7..7] enable mbist for mbist_07, mbist_09                                */
		__IM  uint32_t            : 1;
		__IOM uint32_t mbist_fen_11 : 1;          /*!< [9..9] enable mbist for mbist_11, mbist_12                                */
		__IM  uint32_t            : 1;
		__IOM uint32_t mbist_fen_13 : 1;          /*!< [11..11] enable mbist for mbist_13, mbist_18, mbist_19                    */
		__IOM uint32_t mbist_fen_17 : 1;          /*!< [12..12] enable mbist 17                                                  */
		__IM  uint32_t            : 2;
		__IOM uint32_t mbist_fen_rx2_icache : 1;  /*!< [15..15] enable mbist for RX to I-Cache                                   */
		__IOM uint32_t mbist_fen_rx2_dcache : 1;  /*!< [16..16] enable mbist for RX to D-cache                                   */
		__IOM uint32_t mbist_fen_rx2_dtcm : 1;    /*!< [17..17] enable mbist for RX to DTCM                                      */
		__IOM uint32_t mbist_fen_wmac_e0_dc : 1;  /*!< [18..18] enable mbist for wmac_e0 DC                                      */
		__IOM uint32_t mbist_fen_wmac_e1_dc : 1;  /*!< [19..19] enable mbist for wmac_e1 DC                                      */
		__IOM uint32_t mbist_fen_wpon_e0_dc : 1;  /*!< [20..20] enable mbist for wpon_e0_dc                                      */
		__IOM uint32_t mbist_fen_wpon_e1_dc : 1;  /*!< [21..21] enable mbist for wpon_e1_dc                                      */
		__IOM uint32_t mbist_fen_sdio : 1;        /*!< [22..22] enable mbist for SDIO                                            */
		__IOM uint32_t mbiist_fen_share : 1;      /*!< [23..23] enable mbist for share                                           */
		__IOM uint32_t mbist_fen_rom32kx32 : 1;   /*!< [24..24] enable mbist for 32K x 32                                        */
		__IOM uint32_t mbist_fen_rx2_itcm : 1;    /*!< [25..25] enable mbist for rx to ITCM                                      */
		__IOM uint32_t mbist_fen_wmac_e2_dc : 1;  /*!< [26..26] enable mbist for wmac_e2_dc                                      */
	} b;                                        /*!< bit fields for vdr_mbist_func_en_ctrl */
} vdr_mbist_func_en_ctrl_t, *pvdr_mbist_func_en_ctrl_t;

/**
  \brief Union type to access vdr_mbist_sta (@ 0x00000048).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000048) MBIST Status Register                                      */

	struct {
		__IM  uint32_t mbist_drf_fail : 1;        /*!< [0..0] mbist test status :drf_fail                                        */
		__IM  uint32_t mbist_drf_done : 1;        /*!< [1..1] mbist test status: drf_done                                        */
		__IM  uint32_t mbist_nrml_fail : 1;       /*!< [2..2] mbist test status : normal failed                                  */
		__IM  uint32_t mbist_nrml_done : 1;       /*!< [3..3] mbist test status: normal done                                     */
		__IM  uint32_t mbist_start_pause : 1;     /*!< [4..4] mbist test status :start/pause                                     */
	} b;                                        /*!< bit fields for vdr_mbist_sta */
} vdr_mbist_sta_t, *pvdr_mbist_sta_t;

/**
  \brief Union type to access vdr_mbist_done (@ 0x0000004C).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x0000004C) MBIST Done Output Register                                 */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] mbist_done                                                        */
	} b;                                        /*!< bit fields for vdr_mbist_done */
} vdr_mbist_done_t, *pvdr_mbist_done_t;

/**
  \brief Union type to access vdr_mbist_fail_nrml0 (@ 0x00000050).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000050) MBIST Fail Normal Output Register0                         */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] mbist_fail_nrml0                                                  */
	} b;                                        /*!< bit fields for vdr_mbist_fail_nrml0 */
} vdr_mbist_fail_nrml0_t, *pvdr_mbist_fail_nrml0_t;

/**
  \brief Union type to access vdr_mbist_fail_nrml1 (@ 0x00000054).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000054) MBIST Fail Normal Output Register1                         */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] mbist_fail_nrml1                                                  */
	} b;                                        /*!< bit fields for vdr_mbist_fail_nrml1 */
} vdr_mbist_fail_nrml1_t, *pvdr_mbist_fail_nrml1_t;

/**
  \brief Union type to access vdr_mbist_fail_nrml2 (@ 0x00000058).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000058) MBIST Fail Normal Output Register2                         */

	struct {
		__IM  uint32_t dara       : 32;           /*!< [31..0] mbist_fail_nrml2                                                  */
	} b;                                        /*!< bit fields for vdr_mbist_fail_nrml2 */
} vdr_mbist_fail_nrml2_t, *pvdr_mbist_fail_nrml2_t;

/**
  \brief Union type to access vdr_mbist_fail_drf0 (@ 0x0000005C).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x0000005C) MBIST Fail DRF Output Register0                            */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] mbist_fail_drf0                                                   */
	} b;                                        /*!< bit fields for vdr_mbist_fail_drf0 */
} vdr_mbist_fail_drf0_t, *pvdr_mbist_fail_drf0_t;

/**
  \brief Union type to access vdr_mbist_fail_drf1 (@ 0x00000060).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000060) MBIST Fail DRF Output Register1                            */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] mbist_fail_drf1                                                   */
	} b;                                        /*!< bit fields for vdr_mbist_fail_drf1 */
} vdr_mbist_fail_drf1_t, *pvdr_mbist_fail_drf1_t;

/**
  \brief Union type to access vdr_mbist_fail_drf2 (@ 0x00000064).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000064) MBIST Fail DRF Output Register2                            */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] mbist_fail_drf2                                                   */
	} b;                                        /*!< bit fields for vdr_mbist_fail_drf2 */
} vdr_mbist_fail_drf2_t, *pvdr_mbist_fail_drf2_t;

/**
  \brief Union type to access vdr_mbist_start_pause0 (@ 0x00000068).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000068) MBIST Start Pause Output Register0                         */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] mbist_start_pause0                                                */
	} b;                                        /*!< bit fields for vdr_mbist_start_pause0 */
} vdr_mbist_start_pause0_t, *pvdr_mbist_start_pause0_t;

/**
  \brief Union type to access vdr_mbist_start_pause1 (@ 0x0000006C).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x0000006C) MBIST Start Pause Output Register1                         */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] mbist_start_pause1                                                */
	} b;                                        /*!< bit fields for vdr_mbist_start_pause1 */
} vdr_mbist_start_pause1_t, *pvdr_mbist_start_pause1_t;

/**
  \brief Union type to access vdr_mbist_start_pause2 (@ 0x00000070).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000070) MBIST Start Pause Output Register2                         */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] mbist_start_pause2                                                */
	} b;                                        /*!< bit fields for vdr_mbist_start_pause2 */
} vdr_mbist_start_pause2_t, *pvdr_mbist_start_pause2_t;

/**
  \brief Union type to access vdr_mbist_rom_misr_dout_l (@ 0x00000078).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x00000078) MBIST ROM MISR Data Output Low Register                    */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] rom_misr_dout[31:0] of memory misr                                */
	} b;                                        /*!< bit fields for vdr_mbist_rom_misr_dout_l */
} vdr_mbist_rom_misr_dout_l_t, *pvdr_mbist_rom_misr_dout_l_t;

/**
  \brief Union type to access vdr_mbist_rom_misr_dout_h (@ 0x0000007C).
*/
typedef union {
	__IOM uint32_t w;                           /*!< (@ 0x0000007C) MBIST ROM MISR Data Output High Register                   */

	struct {
		__IM  uint32_t data       : 32;           /*!< [31..0] rom_misr_dout[63:32] of memory misr                               */
	} b;                                        /*!< bit fields for vdr_mbist_rom_misr_dout_h */
} vdr_mbist_rom_misr_dout_h_t, *pvdr_mbist_rom_misr_dout_h_t;

/** @} */ /* End of group hal_vdr_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_VDR_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8710C_VENDOR_VDR_TYPE_H_

