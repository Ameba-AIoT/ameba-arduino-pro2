/**************************************************************************//**
 * @file     hal_otp.h
 * @brief    The HAL related definition and macros for the OTP device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2020-03-10
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2020 Realtek Corporation. All rights reserved.
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

#ifndef _HAL_OTP_H_
#define _HAL_OTP_H_

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

void hal_otp_init(void);
void hal_otp_deinit(void);
void hal_otp_ctrl_sel(uint8_t otp_ctrl_sel);
uint8_t hal_otp_ctrl_sel_sts(void);
void hal_otp_pmc_gnt_ctrl(uint8_t gnt_en);
void hal_otp_wr_gnt_ctrl(uint8_t gnt_en);
void hal_otpc_ctrl(uint8_t otpc_en, uint8_t wclk_en, uint8_t rclk_en);
uint32_t hal_otp_pwr_ctrl(uint8_t pwr_en);
void hal_otp_test_mod_cfg(uint8_t test_mod);
void hal_otp_test_row_ctrl(uint8_t test_row_en);
uint32_t hal_otp_chk_err_sts(void);
void hal_otp_dsb_ctrl(uint8_t dsb_en);
void hal_otp_rb_ctrl(uint8_t rb_en);
void hal_otp_cz_ctrl(uint8_t cz_en);
uint32_t hal_otp_chk_cz_sts(uint32_t key_sel);
uint32_t hal_otp_clr_cz_sts(uint32_t key_sel);
uint32_t hal_otp_prct_ctrl(uint8_t prct_en);
uint32_t hal_otp_chk_prct_sts(uint32_t prct_sel);
uint32_t hal_otp_rd_lz_er_addr(void);
uint32_t hal_otp_clr_prct_sts(uint32_t prct_sel);
uint32_t hal_otp_rd_sz_prct_sts(void);
uint32_t hal_otp_clr_sz_prct_sts(uint32_t sz_prct_sts_sel);
uint32_t hal_otp_rd_ssz_prct_sts(void);
uint32_t hal_otp_clr_ssz_prct_sts(uint32_t ssz_prct_sts_sel);
uint32_t hal_otp_szwl_ctrl(uint32_t sz_wl_en);
uint32_t hal_otp_rd_aldn_sts(uint32_t aldn_sts_sel);
uint32_t hal_otp_clr_aldn_sts(uint32_t aldn_sts_sel);
uint32_t hal_otp_rd_al_sts(uint32_t al_sts_sel);
uint32_t hal_otp_clr_al_sts(uint32_t al_sts_sel);
uint32_t hal_otp_al_cfg(uint32_t al_trg_sel);
uint32_t hal_otp_al_ctrl_aon(uint32_t al_en);
uint32_t hal_otp_bust_ctrl(uint8_t bust_en);
uint32_t hal_otp_rd_sub_aon(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t hal_otp_rd_aon(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t hal_otp_byte_rd_aon(uint32_t addr);
uint32_t hal_otp_wr_sub_aon(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t hal_otp_wr_aon(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void hal_otp_byte_wr_aon(uint32_t addr, uint8_t wr_data);
uint32_t hal_otp_cmp_aon(uint32_t addr, uint8_t cmp_data);
uint32_t hal_otp_rd_sub_sys(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t hal_otp_rd_sys(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t hal_otp_byte_rd_sys(uint32_t addr);
uint32_t hal_otp_wr_sub_sys(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t hal_otp_wr_sys(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void hal_otp_byte_wr_sys(uint32_t addr, uint8_t wr_data);
uint32_t hal_otp_cmp_sys(uint32_t addr, uint8_t cmp_data);
uint32_t hal_otp_al_ctrl_sys(uint32_t al_en);
uint32_t hal_otp_rd_sub_syss(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t hal_otp_rd_syss(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t hal_otp_byte_rd_syss(uint32_t addr);
uint32_t hal_otp_wr_sub_syss(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t hal_otp_wr_syss(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void hal_otp_byte_wr_syss(uint32_t addr, uint8_t wr_data);
uint32_t hal_otp_cmp_syss(uint32_t addr, uint8_t cmp_data);
uint32_t hal_otp_al_ctrl_syss(uint32_t al_en);

uint8_t hal_otp_byte_wr_marr_aon(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
uint8_t hal_otp_byte_wr_marr_sys(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
uint8_t hal_otp_byte_wr_marr_syss(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
void hal_otp_set_aon_vol(uint8_t aon_vol);

uint8_t hal_otp_rp_mar_rd_syss(uint8_t auto_en);
uint8_t hal_otp_rp_chk_syss(void);
uint8_t hal_otp_rp_pg_syss(void);

uint32_t hal_otp_sz_key_wr(uint8_t sz_key_idx, uint8_t *wr_data);
uint32_t hal_otp_sz_key_rd(uint8_t sz_key_idx, uint8_t *rd_data);
uint32_t hal_otp_sz_key_lock(uint8_t sz_key_idx);
uint32_t hal_otp_ssz_key_wr(uint8_t ssz_key_idx, uint8_t *wr_data);
uint32_t hal_otp_ssz_key_rd(uint8_t ssz_key_idx, uint8_t *rd_data);

uint16_t hal_adc_rd_inter_r(void);
int hal_user_otp_get(uint8_t offset, uint8_t len, uint8_t *buf);
int hal_user_otp_set(uint8_t offset, uint8_t len, uint8_t *buf);
int hal_otp_sb_key_get(uint8_t *psec_key, uint8_t key_type);
int hal_otp_sb_key_write(uint8_t *psec_key, uint8_t key_type);
int hal_otp_s_jtag_key_write(u8 *buf, u8 key_num);
int hal_otp_ns_jtag_key_write(u8 *buf, u8 key_num);
int hal_otp_crypto_key_get(uint8_t *pkey, uint8_t key_num);
int hal_otp_crypto_key_write(uint8_t *pkey, uint8_t key_num, uint8_t w_lock_en);
int hal_otp_ecdsa_key_get(uint8_t *pkey, uint8_t key_num);
int hal_otp_ecdsa_key_write(uint8_t *pkey, uint8_t key_num, uint8_t w_lock_en);
int hal_otp_ssz_lock(void);
uint32_t hal_otp_get_pc_dly(void);



extern uint8_t efuse_otp_init_flag;

#define OTP_ADJ_VOL_DEFAULT             0x04

enum otp_sb_key_idx_e {
	SB_OTP_HIGH_VAL_ROTPK_HSH1          =   0x11,
	SB_OTP_HIGH_VAL_ROTPK_HSH2          =   0x12,
	SB_OTP_HIGH_VAL_ROTPK_HSH_RMA       =   0x1F,

	SB_OTP_HIGH_VAL_HUK1                =   0x21,
	SB_OTP_HIGH_VAL_HUK2                =   0x22,
	SB_OTP_HIGH_VAL_HUK_RMA             =   0x2F,

	SB_OTP_HIGH_VAL_SEC_KEY1            =   0x31,
	SB_OTP_HIGH_VAL_SEC_KEY2            =   0x32,
	SB_OTP_HIGH_VAL_SEC_KEY_RMA         =   0x3F,
};

#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL_8735B_OTP_H_



