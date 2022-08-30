/**************************************************************************//**
 * @file     rtl8195bhp_spic.h
 * @brief    The header file of rtl8195bhp_spic.c.
 * @version  1.00
 * @date     2017-08-22
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

#ifndef HAL_SPIC_NS_H
#define HAL_SPIC_NS_H

#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */

#ifdef  __cplusplus
extern "C"
{
#endif

#if defined(CONFIG_BUILD_NONSECURE)

/**

        \addtogroup hal_spic Flash Controller
        \ingroup 8735b_hal
        \brief The Flash Controller (SPIC) module of the HS platform.
        @{
*/

/// @cond DOXYGEN_ROM_HAL_API

/**

        \addtogroup hal_spic_ns_func Flash Controller HAL ROM APIs
        @{
*/

void spic_ns_load_default_setting(pspic_init_para_t pspic_init_data);
u8 spic_ns_query_system_clk(void);
void spic_ns_clock_ctrl(u8 ctl);
void spic_ns_pin_ctrl(u8 io_pin_sel, u8 ctl);
hal_status_t spic_ns_init_setting(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode);
void spic_ns_config_dtr_read(phal_spic_adaptor_t phal_spic_adaptor);
void spic_ns_config_auto_mode(phal_spic_adaptor_t phal_spic_adaptor);
void spic_ns_config_user_mode(phal_spic_adaptor_t phal_spic_adaptor);
BOOL spic_ns_verify_calibration_para(void);
void spic_ns_set_chnl_num(phal_spic_adaptor_t phal_spic_adaptor);
void spic_ns_set_delay_line(u8 delay_line);
void spic_ns_rx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_ns_tx_cmd_no_check(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_ns_tx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_ns_wait_ready(SPIC_TypeDef *spic_dev);
void spic_ns_flush_fifo(SPIC_TypeDef *spic_dev);

/** *@} */ /* End of group hal_spic_ns_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */


/** *@} */ /* End of group hal_spic */
#endif
#endif /* RTL8195BHP_SPIC_H */
