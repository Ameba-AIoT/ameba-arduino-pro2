/**************************************************************************//**
* @file        hal_efuse_nsc.h
* @brief       The HAL Non-secure callable API implementation for the EFUSE
*
* @version     V1.00
* @date        2022-11-15
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



#ifndef _HAL_SYS_CTRL_NSC_H_
#define _HAL_SYS_CTRL_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */
#include "hal_sys_ctrl.h"
#include "hal_power_mode_nsc.h"
#ifdef  __cplusplus
extern "C"
{
#endif

/**
* @addtogroup hal_sys_ctrl_nsc system control NSC
* @{
*/
#if defined(CONFIG_BUILD_SECURE)
void NS_ENTRY hal_sys_peripheral_nsc(uint8_t id, uint8_t en);
void NS_ENTRY hal_sys_set_clk_nsc(uint8_t id, uint8_t sel_val);
uint32_t NS_ENTRY hal_sys_get_clk_nsc(uint8_t id);
void NS_ENTRY hal_sys_set_bus_idau_nsc(uint32_t idau_idx, uint32_t start_addr, uint32_t end_addr);
void NS_ENTRY hal_sdm_32k_enable_nsc(u8 bypass_mode);
u32 NS_ENTRY hal_read_sdm_32k_time_loss_nsc(void);
void NS_ENTRY hal_xtal_divider_enable_nsc(u8 enable);
void NS_ENTRY hal_aon_wdt_enable_nsc(u8 enable, u32 timeout);
void NS_ENTRY hal_osc4m_cal_nsc(void);
void NS_ENTRY hal_sys_bt_uart_mux_nsc(uint8_t sel);
void NS_ENTRY hal_32k_s1_sel_nsc(u8 sel);
void NS_ENTRY hal_xtal_32768_en_nsc(u8 enable);
void NS_ENTRY hal_sys_lxbus_shared_en_nsc(u8 used_id, u8 en);
uint8_t NS_ENTRY hal_sys_get_ld_fw_idx_nsc(void);
void NS_ENTRY hal_sys_get_fw_version_raw_nsc(const uint8_t ld_img_idx, uint8_t *pver_raw_buf);
uint32_t NS_ENTRY hal_sys_get_fw_timest_nsc(const uint8_t ld_img_idx);
uint32_t NS_ENTRY hal_sys_get_ld_fw_img_dev_nor_offset_nsc(void);
hal_status_t NS_ENTRY hal_sys_get_video_img_ld_offset_nsc(void *ctrl_obj_info, const uint8_t ctrl_obj);
void NS_ENTRY hal_sys_get_chip_id_nsc(uint32_t *pchip_id);
uint8_t NS_ENTRY hal_sys_get_rma_state_nsc(void);
void NS_ENTRY hal_sys_set_system_reset_nsc(void);
uint8_t NS_ENTRY hal_sys_get_boot_select_nsc(void);
hal_status_t NS_ENTRY hal_sys_dbg_port_cfg_nsc(dbg_port_mode_t dbg_mode, dbg_port_pin_sel_t pin_sel);
hal_status_t NS_ENTRY hal_sys_dbg_port_en_ctrl_nsc(dbg_port_mode_t dbg_mode, dbg_port_pin_sel_t pin_sel);
void NS_ENTRY hal_sys_sjtag_non_fixed_key_set_nsc(uint8_t set_sjtag_obj, uint8_t *pkey);
uint32_t NS_ENTRY hal_sys_get_video_info_nsc(uint8_t idx);
hal_status_t NS_ENTRY hal_sys_cust_pws_val_ctrl_nsc(uint8_t op, uint16_t *data_buf);
hal_status_t NS_ENTRY hal_sys_adc_vref_setting_nsc(uint8_t set_value);
void NS_ENTRY hal_pll_98p304_ctrl_nsc(u8 en, u8 clk_src);
void NS_ENTRY hal_pll_45p158_ctrl_nsc(u8 en, u8 clk_src);
void NS_ENTRY hal_sys_set_cpu_freq_nsc(uint8_t set_value);
void NS_ENTRY hal_sys_save_dev_adtr(void *p_adatr);
uint8_t NS_ENTRY hal_sys_get_rom_ver_nsc(void);
bool NS_ENTRY hal_sys_spic_boot_finish_nsc(void);
void NS_ENTRY hal_sys_spic_ddr_ctrl_nsc(u8 ctrl);
void NS_ENTRY hal_sys_spic_phy_en_nsc(void);
void NS_ENTRY hal_sys_spic_set_phy_delay_nsc(u8 delay_line);
u8 NS_ENTRY hal_sys_spic_read_phy_delay_nsc(void);
#endif

#if defined(CONFIG_BUILD_NONSECURE)
void hal_sys_peripheral_nsc(uint8_t id, uint8_t en);
void hal_sys_set_clk_nsc(uint8_t id, uint8_t sel_val);
uint32_t hal_sys_get_clk_nsc(uint8_t id);
uint32_t hal_sys_set_bus_idau_nsc(uint32_t idau_idx, uint32_t start_addr, uint32_t end_addr);
void hal_sdm_32k_enable(u8 bypass_mode);
u32 hal_read_sdm_32k_time_loss(void);
void hal_xtal_divider_enable(u8 enable);
void hal_aon_wdt_enable(u8 enable, u32 timeout);
void hal_osc4m_cal(void);
void hal_sys_bt_uart_mux_nsc(uint8_t sel);
void hal_32k_s1_sel(u8 sel);
void hal_sys_lxbus_shared_en_nsc(u8 used_id, u8 en);
uint8_t hal_sys_get_ld_fw_idx_nsc(void);
void hal_sys_get_fw_version_raw_nsc(const uint8_t ld_img_idx, uint8_t *pver_raw_buf);
uint32_t hal_sys_get_fw_timest_nsc(const uint8_t ld_img_idx);
uint32_t hal_sys_get_ld_fw_img_dev_nor_offset_nsc(void);
hal_status_t hal_sys_get_video_img_ld_offset_nsc(void *ctrl_obj_info, const uint8_t ctrl_obj);
void hal_sys_get_chip_id_nsc(uint32_t *pchip_id);
uint8_t hal_sys_get_rma_state_nsc(void);
void hal_sys_set_system_reset_nsc(void);
uint8_t hal_sys_get_boot_select_nsc(void);
hal_status_t hal_sys_dbg_port_cfg_nsc(dbg_port_mode_t dbg_mode, dbg_port_pin_sel_t pin_sel);
hal_status_t hal_sys_dbg_port_en_ctrl_nsc(dbg_port_mode_t dbg_mode, dbg_port_pin_sel_t pin_sel);
void hal_sys_sjtag_non_fixed_key_set_nsc(uint8_t set_sjtag_obj, uint8_t *pkey);
uint32_t hal_sys_get_video_info_nsc(uint8_t idx);
hal_status_t hal_sys_cust_pws_val_ctrl_nsc(uint8_t op, uint16_t *data_buf);
hal_status_t hal_sys_adc_vref_setting_nsc(uint8_t set_value);
void hal_pll_98p304_ctrl_nsc(u8 en, u8 clk_src);
void hal_pll_45p158_ctrl_nsc(u8 en, u8 clk_src);
void hal_sys_set_cpu_freq_nsc(uint8_t set_value);
void hal_sys_save_dev_adtr(void *p_adatr);
uint8_t hal_sys_get_rom_ver_nsc(void);
bool hal_sys_spic_boot_finish_nsc(void);
void hal_sys_spic_ddr_ctrl_nsc(u8 ctrl);
void hal_sys_spic_phy_en_nsc(void);
void hal_sys_spic_set_phy_delay_nsc(u8 delay_line);
u8 hal_sys_spic_read_phy_delay_nsc(void);
void hal_sys_save_dev_adtr_nsc(void *padatr);

#if !defined(ENABLE_SECCALL_PATCH)
#define hal_sys_peripheral_en                 hal_sys_peripheral_nsc
#define hal_sys_set_clk                       hal_sys_set_clk_nsc
#define hal_sys_get_clk                       hal_sys_get_clk_nsc
#endif
#define hal_sys_set_bus_idau                  hal_sys_set_bus_idau_nsc
#define hal_sys_sjtag_non_fixed_key_set       hal_sys_sjtag_non_fixed_key_set_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_sdm_32k_enable                    hal_sdm_32k_enable_nsc
#endif
#define hal_read_sdm_32k_time_loss            hal_read_sdm_32k_time_loss_nsc
#define hal_xtal_divider_enable               hal_xtal_divider_enable_nsc
#define hal_aon_wdt_enable                    hal_aon_wdt_enable_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_osc4m_cal                         hal_osc4m_cal_nsc
#define hal_sys_bt_uart_mux                   hal_sys_bt_uart_mux_nsc
#endif
#define hal_32k_s1_sel                        hal_32k_s1_sel_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_sys_lxbus_shared_en               hal_sys_lxbus_shared_en_nsc
#define hal_sys_get_ld_fw_idx                 hal_sys_get_ld_fw_idx_nsc
#define hal_sys_get_fw_version_raw            hal_sys_get_fw_version_raw_nsc
#define hal_sys_get_fw_timest                 hal_sys_get_fw_timest_nsc
#define hal_sys_get_video_img_ld_offset       hal_sys_get_video_img_ld_offset_nsc
#endif
#define hal_sys_get_ld_fw_img_dev_nor_offset  hal_sys_get_ld_fw_img_dev_nor_offset_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_sys_get_chip_id                   hal_sys_get_chip_id_nsc
#endif
#define hal_sys_get_rma_state                 hal_sys_get_rma_state_nsc
#define hal_sys_set_system_reset              hal_sys_set_system_reset_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_sys_get_boot_select               hal_sys_get_boot_select_nsc
#define hal_sys_dbg_port_cfg                  hal_sys_dbg_port_cfg_nsc
#endif
#define hal_sys_dbg_port_en_ctrl              hal_sys_dbg_port_en_ctrl_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_sys_get_video_info                hal_sys_get_video_info_nsc
#define hal_sys_cust_pws_val_ctrl             hal_sys_cust_pws_val_ctrl_nsc
#endif
#define hal_sys_adc_vref_setting              hal_sys_adc_vref_setting_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_pll_98p304_ctrl                   hal_pll_98p304_ctrl_nsc
#define hal_pll_45p158_ctrl                   hal_pll_45p158_ctrl_nsc
#endif
#define hal_sys_set_cpu_freq                  hal_sys_set_cpu_freq_nsc
#define hal_sys_save_dev_adtr                 hal_sys_save_dev_adtr_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_sys_get_rom_ver                   hal_sys_get_rom_ver_nsc
#define hal_sys_spic_boot_finish              hal_sys_spic_boot_finish_nsc
#define hal_sys_spic_ddr_ctrl                 hal_sys_spic_ddr_ctrl_nsc
#define hal_sys_spic_phy_en                   hal_sys_spic_phy_en_nsc
#define hal_sys_spic_set_phy_delay            hal_sys_spic_set_phy_delay_nsc
#define hal_sys_spic_read_phy_delay           hal_sys_spic_read_phy_delay_nsc
#endif
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

/** @} */ /* End of group hal_sys_ctrl_nsc */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SYS_CTRL_NSC_H_"
