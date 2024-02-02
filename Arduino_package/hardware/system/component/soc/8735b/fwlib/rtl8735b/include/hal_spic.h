/**************************************************************************//**
 * @file     hal_spic.h
 * @brief    The header file of hal_spic.c
 * @version  1.00
 * @date     2022-10-19
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

#ifndef _HAL_SPIC_H_
#define _HAL_SPIC_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#define HIGH_SPEED_FLASH FLASH_SPEED_625MHz //62.5MHz: FLASH_SPEED_625MHz, 100MHz: FLASH_SPEED_100MHz, 125MHz: FLASH_SPEED_125MHz

#define SPIC_BIT_MODE_SETTING SpicQuadIOMode  // Default for ram code using is qpi mode

/**

        \addtogroup hs_hal_spic Flash Controller
        @{
*/
#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define SPIC_DATA_BASE 0x1000       //!< Define address offset to store calibration setting
#else
#define SPIC_DATA_BASE 0x3000       //!< Define address offset to store calibration setting, because 0x1000 by other info, so move it to other place
#endif

/**

        \addtogroup hs_hal_spic_ram_func Flash Controller HAL RAM APIs
        @{
*/


void spic_load_default_setting(pspic_init_para_t pspic_init_data);
u8 spic_query_system_clk(void);
void spic_clock_ctrl(u8 ctl);
hal_status_t spic_init_setting(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode);
void spic_load_calibration_setting(phal_spic_adaptor_t phal_spic_adaptor);
void spic_store_calibration_setting(phal_spic_adaptor_t phal_spic_adaptor);
void spic_config_dtr_read(phal_spic_adaptor_t phal_spic_adaptor);
void spic_config_auto_mode(phal_spic_adaptor_t phal_spic_adaptor);
void spic_config_user_mode(phal_spic_adaptor_t phal_spic_adaptor);
BOOL spic_verify_calibration_para(void);
void spic_set_chnl_num(phal_spic_adaptor_t phal_spic_adaptor);
void spic_set_delay_line(u8 delay_line);
void spic_rx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_no_check(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_wait_ready(SPIC_TypeDef *spic_dev);
void spic_flush_fifo(SPIC_TypeDef *spic_dev);
hal_status_t spic_pinmux_ctl(phal_spic_adaptor_t phal_spic_adaptor, u8 ctl);
hal_status_t spic_init(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode, u8 io_pin_sel);
hal_status_t spic_deinit(phal_spic_adaptor_t phal_spic_adaptor);
hal_status_t spic_deinit_for_xip_img_deinit(phal_spic_adaptor_t phal_spic_adaptor);
BOOL spic_calibration(phal_spic_adaptor_t phal_spic_adaptor, u32 default_dummy_cycle);

/** *@} */ /* End of group hal_spic_ram_func */

/** *@} */ /* End of group hal_spic */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SPIC_H_"


