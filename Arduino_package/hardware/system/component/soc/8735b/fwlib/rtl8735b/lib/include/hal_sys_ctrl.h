/**************************************************************************//**
* @file        hal_sys_ctrl.h
* @brief       The HAL API implementation for the System control
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



#ifndef _HAL_SYS_CTRL_H_
#define _HAL_SYS_CTRL_H_
#include "cmsis.h"
#include "rtl8735b_sys_ctrl.h"
#include "fw_img_tlv.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#define FW_IMG_MANIFEST_VERSION_MAX_SIZE                (32)
#define VIDEO_IMGS_INVALID_OFFSET                       (0xFEFEFEFE)

typedef enum {
	SYS_CUST_PWS_VAL_SET = 1,
	SYS_CUST_PWS_VAL_GET = 2
} SYS_CUST_PWS_VAL_CTRL_t;

typedef enum {
	BT_UART_MUX_EXTERNAL = 0,
	BT_UART_MUX_INTERNAL = 1
} BT_UART_MUX_SELECT_t;

typedef enum {
	VIDEO_ISP_SENSOR_SET0               = 0x1,
	VIDEO_ISP_SENSOR_SET1               = 0x2,
	VIDEO_ISP_SENSOR_SET2               = 0x3,
	VIDEO_ISP_SENSOR_SET3               = 0x4,
	VIDEO_ISP_SENSOR_SET4               = 0x5,
	VIDEO_ISP_SENSOR_SET5               = 0x6,
	VIDEO_ISP_SENSOR_SET6               = 0x7,
	VIDEO_ISP_SENSOR_SET7               = 0x8,
	VIDEO_ISP_SENSOR_SET8               = 0x9,
	VIDEO_ISP_SENSOR_SET9               = 0xA
} VIDEO_ISPIQ_IMG_GET_SENSOR_SET_CTRL_t;

typedef enum {
	VIDEO_ISP_SENSOR_IQ                 = 0x1,
	VIDEO_ISP_SENSOR_DATA               = 0x2,
} VIDEO_ISPIQ_IMG_GET_SENSOR_MEMBER_CTRL_t;

typedef enum {
	VIDEO_ISP_SET0_IQ_OFFSET            = ((VIDEO_ISP_SENSOR_SET0 << 4) | VIDEO_ISP_SENSOR_IQ),
	VIDEO_ISP_SET0_SENSOR_OFFSET        = ((VIDEO_ISP_SENSOR_SET0 << 4) | VIDEO_ISP_SENSOR_DATA),
	VIDEO_ISP_SET1_IQ_OFFSET            = ((VIDEO_ISP_SENSOR_SET1 << 4) | VIDEO_ISP_SENSOR_IQ),
	VIDEO_ISP_SET1_SENSOR_OFFSET        = ((VIDEO_ISP_SENSOR_SET1 << 4) | VIDEO_ISP_SENSOR_DATA),
	VIDEO_ISP_SET2_IQ_OFFSET            = ((VIDEO_ISP_SENSOR_SET2 << 4) | VIDEO_ISP_SENSOR_IQ),
	VIDEO_ISP_SET2_SENSOR_OFFSET        = ((VIDEO_ISP_SENSOR_SET2 << 4) | VIDEO_ISP_SENSOR_DATA),
	VIDEO_ISP_SET3_IQ_OFFSET            = ((VIDEO_ISP_SENSOR_SET3 << 4) | VIDEO_ISP_SENSOR_IQ),
	VIDEO_ISP_SET3_SENSOR_OFFSET        = ((VIDEO_ISP_SENSOR_SET3 << 4) | VIDEO_ISP_SENSOR_DATA),
	VIDEO_ISP_SET4_IQ_OFFSET            = ((VIDEO_ISP_SENSOR_SET4 << 4) | VIDEO_ISP_SENSOR_IQ),
	VIDEO_ISP_SET4_SENSOR_OFFSET        = ((VIDEO_ISP_SENSOR_SET4 << 4) | VIDEO_ISP_SENSOR_DATA),
	VIDEO_ISP_SET5_IQ_OFFSET            = ((VIDEO_ISP_SENSOR_SET5 << 4) | VIDEO_ISP_SENSOR_IQ),
	VIDEO_ISP_SET5_SENSOR_OFFSET        = ((VIDEO_ISP_SENSOR_SET5 << 4) | VIDEO_ISP_SENSOR_DATA),
	VIDEO_ISP_SET6_IQ_OFFSET            = ((VIDEO_ISP_SENSOR_SET6 << 4) | VIDEO_ISP_SENSOR_IQ),
	VIDEO_ISP_SET6_SENSOR_OFFSET        = ((VIDEO_ISP_SENSOR_SET6 << 4) | VIDEO_ISP_SENSOR_DATA),
	VIDEO_ISP_SET7_IQ_OFFSET            = ((VIDEO_ISP_SENSOR_SET7 << 4) | VIDEO_ISP_SENSOR_IQ),
	VIDEO_ISP_SET7_SENSOR_OFFSET        = ((VIDEO_ISP_SENSOR_SET7 << 4) | VIDEO_ISP_SENSOR_DATA),
	VIDEO_ISP_SET8_IQ_OFFSET            = ((VIDEO_ISP_SENSOR_SET8 << 4) | VIDEO_ISP_SENSOR_IQ),
	VIDEO_ISP_SET8_SENSOR_OFFSET        = ((VIDEO_ISP_SENSOR_SET8 << 4) | VIDEO_ISP_SENSOR_DATA),
	VIDEO_ISP_SET9_IQ_OFFSET            = ((VIDEO_ISP_SENSOR_SET9 << 4) | VIDEO_ISP_SENSOR_IQ),
	VIDEO_ISP_SET9_SENSOR_OFFSET        = ((VIDEO_ISP_SENSOR_SET9 << 4) | VIDEO_ISP_SENSOR_DATA),
	VIDEO_VOE_OFFSET                    = 0xF0,
} VIDEO_IMG_GET_OBJ_CTRL_t;

typedef struct video_reld_img_ctrl_info_s {
	uint8_t fwin;
	uint8_t enc_en;
	uint8_t resv[2];
	uint32_t data_start_offset;     // ref img manifest start
} video_reld_img_ctrl_info_t;

enum dbg_port_mode_e {
	DBG_PORT_OFF            = 0,    ///< debug port off
	SWD_MODE                = 1,    ///< debugger use SWD mode
	JTAG_MODE               = 2,    ///< debugger use JTAG mode
	DBG_PORT_USE_DEFAULT    = 3,    ///< debugger use same as rom code select
};
typedef uint8_t     dbg_port_mode_t;

enum dbg_port_pin_sel_e {
	TMS_IO_S0_CLK_S0   = 0,
	TMS_IO_S1_CLK_S0   = 1,
	TMS_IO_S0_CLK_S1   = 2,
	TMS_IO_S1_CLK_S1   = 3,
	TMS_IO_DF_CLK_DF   = 4,         ///< debugger use pins same as rom code select
};
typedef uint8_t     dbg_port_pin_sel_t;

enum {
	FW_IMG_IDX_UNKNOWN     =   0x0,
	FW_IMG_IDX1            =   0x1,
	FW_IMG_IDX2            =   0x2
};

enum ADC_VREF_SEL_e {
	VREF_SEL_0p75_V = 0x0,
	VREF_SEL_0p8_V  = 0x1,
	VREF_SEL_0p85_V = 0x2,
	VREF_SEL_0p9_V  = 0x3,
};

typedef uint8_t ADC_VREF_SEL_t;

/**
* @addtogroup N/A
* @{
*/

void hal_sys_get_chip_id(uint32_t *pchip_id);
void hal_sys_peripheral_en(uint8_t id, uint8_t en);
void hal_sys_lxbus_shared_en(uint8_t used_id, uint8_t en);
void hal_sys_set_clk(uint8_t id, uint8_t sel_val);
uint32_t hal_sys_get_clk(uint8_t id);
void hal_sys_set_system_reset(void);
hal_status_t hal_sys_dbg_port_cfg(dbg_port_mode_t dbg_mode, dbg_port_pin_sel_t pin_sel);
hal_status_t hal_sys_dbg_port_en_ctrl(dbg_port_mode_t dbg_mode, dbg_port_pin_sel_t pin_sel);
uint8_t hal_sys_get_boot_select(void);

void hal_sys_set_bus_idau(uint32_t idau_idx, uint32_t start_addr, uint32_t end_addr);

uint32_t hal_sys_boot_info_get_val(uint8_t info_idx);
void hal_sys_boot_info_assign_val(uint8_t info_idx, uint32_t info_v);
void hal_sys_boot_footpath_init(uint8_t info_idx);
void hal_sys_boot_footpath_store(uint8_t info_idx, uint8_t fp_v);
void hal_sys_boot_footpath_clear(uint8_t info_idx, uint8_t fp_v);
uint8_t hal_sys_get_rma_state(void);
void hal_sys_sjtag_fixed_key_enable(void);
void hal_sys_sjtag_non_fixed_key_set(uint8_t set_sjtag_obj, uint8_t *pkey);
uint32_t hal_sys_get_video_info(uint8_t idx);
uint8_t hal_sys_get_rom_ver(void);
uint8_t hal_sys_get_img_ld_idx_core(const uint8_t img_obj, void *pimf_ld_info);
uint8_t hal_sys_get_ld_fw_idx(void);
void hal_sys_get_fw_version_raw(const uint8_t ld_img_idx, uint8_t *pver_raw_buf);
uint32_t hal_sys_get_fw_timest(const uint8_t ld_img_idx);
uint32_t hal_sys_get_ld_fw_img_dev_nor_offset(void);
hal_status_t hal_sys_get_video_img_ld_offset(void *ctrl_obj_info, const uint8_t ctrl_obj);
uint8_t hal_sys_get_ld_img_idx(const uint8_t img_obj);

void hal_sdm_32k_enable(u8 bypass_mode);
u32 hal_read_sdm_32k_time_loss(void);
void hal_xtal_divider_enable(u8 enable);
void hal_aon_wdt_enable(u8 enable, u32 timeout);
void hal_osc4m_cal(void);
void hal_pll_98p304_ctrl(u8 en, u8 clk_src);
void hal_pll_45p158_ctrl(u8 en, u8 clk_src);
void hal_32k_s1_sel(u8 sel);
void hal_xtal_32768_en(u8 enable);

void hal_sys_high_val_protect_init_hook(hv_prot_trng_init_func_t trng_init_f, hv_prot_trng_deinit_func_t trng_deinit_f,
										hv_prot_trng_ld_def_setting_func_t trng_ld_def_set_f, hv_prot_trng_get_rand_func_t trng_get_rand_f,
										hv_prot_trng_set_clk_func_t trng_set_clk_f, hv_prot_trng_swrst_en_func_t trng_swrst_enf_f);
void hal_sys_high_val_protect_init(void);
void hal_sys_high_val_protect_init_flow(void);
void hal_sys_high_val_protect_deinit(void);
void hal_sys_high_val_protect_ld(const uint32_t otp_addr, uint8_t *p_otp_v, const uint32_t ld_size);
void hal_sys_high_val_mem_protect_ld(void *s1, const void *s2, size_t ld_size);
void hal_sys_high_val_protect_ld_delay(uint8_t delay_unit_sel);
uint8_t hal_sys_check_high_val_protect_init(void);
int hal_sys_flash_sec_aes_gcm_tag_cmp(const void *a, const void *b, size_t size);
int hal_sys_high_val_protect_cmp(const void *a, const void *b, size_t size);
hal_status_t hal_sys_adc_vref_setting(uint8_t set_value);
void hal_sys_set_sw_boot_rom_trap_op(uint8_t op_idx, uint8_t ctrl_status);
void hal_sys_set_sw_boot_rom_pg_trap_op(void);
void hal_sys_save_dev_adtr(void *p_adatr);
hal_spic_adaptor_t *hal_sys_get_spic_adtr(void);
void hal_sys_get_pre_boot_fail_sts(const uint8_t img_obj, void *pboot_fail_sts);
hal_snafc_adaptor_t *hal_sys_get_snafc_adtr(void);
uint8_t hal_sys_check_kc_bind_img(uint8_t img_obj);
void hal_sys_clear_kc_bind_img(void);
bool hal_sys_spic_boot_finish(void);
void hal_sys_spic_ddr_ctrl(u8 ctrl);
void hal_sys_spic_phy_en(void);
void hal_sys_spic_set_phy_delay(u8 delay_line);
u8 hal_sys_spic_read_phy_delay(void);
uint8_t hal_sys_get_atld_cfg(const uint8_t op);
void hal_sys_get_img_vrf_digest(const uint8_t op_img, void *pld_buf);
void hal_sys_get_cust_derived_uid(void *pld_buf);

#define RAM_FOOTPH_INIT(idx)                hal_sys_boot_footpath_init(idx)
#define RAM_FOOTPH_STORE(idx,fp_v)          hal_sys_boot_footpath_store(idx,fp_v)
#define RAM_FOOTPH_CLR(idx,fp_v)            hal_sys_boot_footpath_clear(idx,fp_v)
#define RAM_FOOTPH_GET(idx)                 hal_sys_boot_info_get_val(idx)

// Patch functions
void hal_rtl_sys_peripheral_en_patch(uint8_t id, uint8_t en);
void hal_rtl_sys_set_clk_patch(uint8_t id, uint8_t sel_val);
uint32_t hal_rtl_sys_get_clk_patch(uint8_t id);
void hal_sys_set_cpu_freq(uint8_t set_value);

/** @} */ /* End of group hs_hal_efuse */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SYS_CTRL_H_"


