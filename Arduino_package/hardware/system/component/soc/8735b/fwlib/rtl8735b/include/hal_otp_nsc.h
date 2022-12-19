/**************************************************************************//**
 * @file     hal_otp_nsc.h
 * @brief    The header file of hal_flash_nsc.c.
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

#ifndef _HAL_OTP_NSC_H_
#define _HAL_OTP_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */

#ifdef  __cplusplus
extern "C"
{
#endif

#if defined(CONFIG_BUILD_SECURE)
/**

        \addtogroup hs_hal_otp_nsc_api OTP HAL NSC APIs
        \ingroup hal_otp
        \brief The OTP HAL NSC (Non-Secure Callable) APIs. Non-secure domain is allowed to access secure functions through NSC APIs.
        @{
*/
void NS_ENTRY hal_otp_init_nsc(void);
void NS_ENTRY hal_otp_deinit_nsc(void);
void NS_ENTRY hal_otp_ctrl_sel_nsc(uint8_t otp_ctrl_sel);
uint8_t NS_ENTRY hal_otp_ctrl_sel_sts_nsc(void);
void NS_ENTRY hal_otp_pmc_gnt_ctrl_nsc(uint8_t gnt_en);
void NS_ENTRY hal_otp_wr_gnt_ctrl_nsc(uint8_t gnt_en);
void NS_ENTRY hal_otpc_ctrl_nsc(uint8_t otpc_en, uint8_t wclk_en, uint8_t rclk_en);
uint32_t NS_ENTRY hal_otp_pwr_ctrl_nsc(uint8_t pwr_en);
void NS_ENTRY hal_otp_test_mod_cfg_nsc(uint8_t test_mod);
void NS_ENTRY hal_otp_test_row_ctrl_nsc(uint8_t test_row_en);
uint32_t NS_ENTRY hal_otp_chk_err_sts_nsc(void);
void NS_ENTRY hal_otp_dsb_ctrl_nsc(uint8_t dsb_en);
void NS_ENTRY hal_otp_rb_ctrl_nsc(uint8_t rb_en);
void NS_ENTRY hal_otp_cz_ctrl_nsc(uint8_t cz_en);
uint32_t NS_ENTRY hal_otp_chk_cz_sts_nsc(uint32_t key_sel);
uint32_t NS_ENTRY hal_otp_clr_cz_sts_nsc(uint32_t key_sel);
uint32_t NS_ENTRY hal_otp_prct_ctrl_nsc(uint8_t prct_en);
uint32_t NS_ENTRY hal_otp_chk_prct_sts_nsc(uint32_t prct_sel);
uint32_t NS_ENTRY hal_otp_rd_lz_er_addr_nsc(void);
uint32_t NS_ENTRY hal_otp_clr_prct_sts_nsc(uint32_t prct_sel);
uint32_t NS_ENTRY hal_otp_rd_sz_prct_sts_nsc(void);
uint32_t NS_ENTRY hal_otp_clr_sz_prct_sts_nsc(uint32_t sz_prct_sts_sel);
uint32_t NS_ENTRY hal_otp_rd_ssz_prct_sts_nsc(void);
uint32_t NS_ENTRY hal_otp_clr_ssz_prct_sts_nsc(uint32_t ssz_prct_sts_sel);
uint32_t NS_ENTRY hal_otp_szwl_ctrl_nsc(uint32_t sz_wl_en);
uint32_t NS_ENTRY hal_otp_rd_aldn_sts_nsc(uint32_t aldn_sts_sel);
uint32_t NS_ENTRY hal_otp_clr_aldn_sts_nsc(uint32_t aldn_sts_sel);
uint32_t NS_ENTRY hal_otp_rd_al_sts_nsc(uint32_t al_sts_sel);
uint32_t NS_ENTRY hal_otp_clr_al_sts_nsc(uint32_t al_sts_sel);
uint32_t NS_ENTRY hal_otp_al_cfg_nsc(uint32_t al_trg_sel);
uint32_t NS_ENTRY hal_otp_al_ctrl_aon_nsc(uint32_t al_en);
uint32_t NS_ENTRY hal_otp_bust_ctrl_nsc(uint8_t bust_en);
uint32_t NS_ENTRY hal_otp_rd_sub_aon_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t NS_ENTRY hal_otp_rd_aon_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t NS_ENTRY hal_otp_byte_rd_aon_nsc(uint32_t addr);
uint32_t NS_ENTRY hal_otp_wr_sub_aon_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t NS_ENTRY hal_otp_wr_aon_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void NS_ENTRY hal_otp_byte_wr_aon_nsc(uint32_t addr, uint8_t wr_data);
uint32_t NS_ENTRY hal_otp_cmp_aon_nsc(uint32_t addr, uint8_t cmp_data);
uint32_t NS_ENTRY hal_otp_rd_sub_sys_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t NS_ENTRY hal_otp_rd_sys_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t NS_ENTRY hal_otp_byte_rd_sys_nsc(uint32_t addr);
uint32_t NS_ENTRY hal_otp_wr_sub_sys_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t NS_ENTRY hal_otp_wr_sys_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void NS_ENTRY hal_otp_byte_wr_sys_nsc(uint32_t addr, uint8_t wr_data);
uint32_t NS_ENTRY hal_otp_cmp_sys_nsc(uint32_t addr, uint8_t cmp_data);
uint32_t NS_ENTRY hal_otp_al_ctrl_sys_nsc(uint32_t al_en);
uint32_t NS_ENTRY hal_otp_rd_sub_syss_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t NS_ENTRY hal_otp_rd_syss_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t NS_ENTRY hal_otp_byte_rd_syss_nsc(uint32_t addr);
uint32_t NS_ENTRY hal_otp_wr_sub_syss_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t NS_ENTRY hal_otp_wr_syss_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void NS_ENTRY hal_otp_byte_wr_syss_nsc(uint32_t addr, uint8_t wr_data);
uint32_t NS_ENTRY hal_otp_cmp_syss_nsc(uint32_t addr, uint8_t cmp_data);
uint32_t NS_ENTRY hal_otp_al_ctrl_syss_nsc(uint32_t al_en);

uint8_t NS_ENTRY hal_otp_byte_wr_marr_aon_nsc(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
uint8_t NS_ENTRY hal_otp_byte_wr_marr_sys_nsc(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
uint8_t NS_ENTRY hal_otp_byte_wr_marr_syss_nsc(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
void NS_ENTRY hal_otp_set_aon_vol_nsc(uint8_t aon_vol);

uint8_t NS_ENTRY hal_otp_rp_mar_rd_syss_nsc(uint8_t auto_en);
uint8_t NS_ENTRY hal_otp_rp_chk_syss_nsc(void);
uint8_t NS_ENTRY hal_otp_rp_pg_syss_nsc(void);

uint32_t NS_ENTRY hal_otp_sz_key_wr_nsc(uint8_t sz_key_idx, uint8_t *wr_data);
uint32_t NS_ENTRY hal_otp_sz_key_rd_nsc(uint8_t sz_key_idx, uint8_t *rd_data);
uint32_t NS_ENTRY hal_otp_sz_key_lock_nsc(uint8_t sz_key_idx);
uint32_t NS_ENTRY hal_otp_ssz_key_wr_nsc(uint8_t ssz_key_idx, uint8_t *wr_data);
uint32_t NS_ENTRY hal_otp_ssz_key_rd_nsc(uint8_t ssz_key_idx, uint8_t *rd_data);

uint16_t NS_ENTRY hal_adc_rd_inter_r_nsc(void);
int NS_ENTRY hal_user_otp_get_nsc(uint8_t offset, uint8_t len, uint8_t *buf);
int NS_ENTRY hal_user_otp_set_nsc(uint8_t offset, uint8_t len, uint8_t *buf);
int NS_ENTRY hal_otp_sb_key_get_nsc(uint8_t *psec_key, uint8_t key_type);
int NS_ENTRY hal_otp_sb_key_write_nsc(uint8_t *psec_key, uint8_t key_type);
int NS_ENTRY hal_otp_s_jtag_key_write_nsc(u8 *buf, u8 key_num);
int NS_ENTRY hal_otp_ns_jtag_key_write_nsc(u8 *buf, u8 key_num);
int NS_ENTRY hal_otp_crypto_key_get_nsc(uint8_t *pkey, uint8_t key_num);
int NS_ENTRY hal_otp_crypto_key_write_nsc(uint8_t *pkey, uint8_t key_num, uint8_t w_lock_en);
int NS_ENTRY hal_otp_ecdsa_key_get_nsc(uint8_t *pkey, uint8_t key_num);
int NS_ENTRY hal_otp_ecdsa_key_write_nsc(uint8_t *pkey, uint8_t key_num, uint8_t w_lock_en);
int NS_ENTRY hal_otp_ssz_lock_nsc(void);

/** *@} */ /* End of group hal_otp_nsc_api */
#endif // end of "#if defined(CONFIG_BUILD_SECURE)"

#if defined(CONFIG_BUILD_NONSECURE)
void hal_otp_init_nsc(void);
void hal_otp_deinit_nsc(void);
void hal_otp_ctrl_sel_nsc(uint8_t otp_ctrl_sel);
uint8_t hal_otp_ctrl_sel_sts_nsc(void);
void hal_otp_pmc_gnt_ctrl_nsc(uint8_t gnt_en);
void hal_otp_wr_gnt_ctrl_nsc(uint8_t gnt_en);
void hal_otpc_ctrl_nsc(uint8_t otpc_en, uint8_t wclk_en, uint8_t rclk_en);
uint32_t hal_otp_pwr_ctrl_nsc(uint8_t pwr_en);
void hal_otp_test_mod_cfg_nsc(uint8_t test_mod);
void hal_otp_test_row_ctrl_nsc(uint8_t test_row_en);
uint32_t hal_otp_chk_err_sts_nsc(void);
void hal_otp_dsb_ctrl_nsc(uint8_t dsb_en);
void hal_otp_rb_ctrl_nsc(uint8_t rb_en);
void hal_otp_cz_ctrl_nsc(uint8_t cz_en);
uint32_t hal_otp_chk_cz_sts_nsc(uint32_t key_sel);
uint32_t hal_otp_clr_cz_sts_nsc(uint32_t key_sel);
uint32_t hal_otp_prct_ctrl_nsc(uint8_t prct_en);
uint32_t hal_otp_chk_prct_sts_nsc(uint32_t prct_sel);
uint32_t hal_otp_rd_lz_er_addr_nsc(void);
uint32_t hal_otp_clr_prct_sts_nsc(uint32_t prct_sel);
uint32_t hal_otp_rd_sz_prct_sts_nsc(void);
uint32_t hal_otp_clr_sz_prct_sts_nsc(uint32_t sz_prct_sts_sel);
uint32_t hal_otp_rd_ssz_prct_sts_nsc(void);
uint32_t hal_otp_clr_ssz_prct_sts_nsc(uint32_t ssz_prct_sts_sel);
uint32_t hal_otp_szwl_ctrl_nsc(uint32_t sz_wl_en);
uint32_t hal_otp_rd_aldn_sts_nsc(uint32_t aldn_sts_sel);
uint32_t hal_otp_clr_aldn_sts_nsc(uint32_t aldn_sts_sel);
uint32_t hal_otp_rd_al_sts_nsc(uint32_t al_sts_sel);
uint32_t hal_otp_clr_al_sts_nsc(uint32_t al_sts_sel);
uint32_t hal_otp_al_cfg_nsc(uint32_t al_trg_sel);
uint32_t hal_otp_al_ctrl_aon_nsc(uint32_t al_en);
uint32_t hal_otp_bust_ctrl_nsc(uint8_t bust_en);
uint32_t hal_otp_rd_sub_aon_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t hal_otp_rd_aon_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t hal_otp_byte_rd_aon_nsc(uint32_t addr);
uint32_t hal_otp_wr_sub_aon_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t hal_otp_wr_aon_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void hal_otp_byte_wr_aon_nsc(uint32_t addr, uint8_t wr_data);
uint32_t hal_otp_cmp_aon_nsc(uint32_t addr, uint8_t cmp_data);
uint32_t hal_otp_rd_sub_sys_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t hal_otp_rd_sys_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t hal_otp_byte_rd_sys_nsc(uint32_t addr);
uint32_t hal_otp_wr_sub_sys_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t hal_otp_wr_sys_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void hal_otp_byte_wr_sys_nsc(uint32_t addr, uint8_t wr_data);
uint32_t hal_otp_cmp_sys_nsc(uint32_t addr, uint8_t cmp_data);
uint32_t hal_otp_al_ctrl_sys_nsc(uint32_t al_en);
uint32_t hal_otp_rd_sub_syss_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint32_t hal_otp_rd_syss_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *rd_data, uint16_t len);
uint8_t hal_otp_byte_rd_syss_nsc(uint32_t addr);
uint32_t hal_otp_wr_sub_syss_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
uint32_t hal_otp_wr_syss_nsc(uint8_t pwr_cl_en, uint32_t addr, uint8_t *wr_data, uint16_t len);
void hal_otp_byte_wr_syss_nsc(uint32_t addr, uint8_t wr_data);
uint32_t hal_otp_cmp_syss_nsc(uint32_t addr, uint8_t cmp_data);
uint32_t hal_otp_al_ctrl_syss_nsc(uint32_t al_en);

uint8_t hal_otp_byte_wr_marr_aon_nsc(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
uint8_t hal_otp_byte_wr_marr_sys_nsc(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
uint8_t hal_otp_byte_wr_marr_syss_nsc(uint32_t addr, uint8_t wr_data, uint8_t adj_vol);
void hal_otp_set_aon_vol_nsc(uint8_t aon_vol);

uint8_t hal_otp_rp_mar_rd_syss_nsc(uint8_t auto_en);
uint8_t hal_otp_rp_chk_syss_nsc(void);
uint8_t hal_otp_rp_pg_syss_nsc(void);

uint32_t hal_otp_sz_key_wr_nsc(uint8_t sz_key_idx, uint8_t *wr_data);
uint32_t hal_otp_sz_key_rd_nsc(uint8_t sz_key_idx, uint8_t *rd_data);
uint32_t hal_otp_sz_key_lock_nsc(uint8_t sz_key_idx);
uint32_t hal_otp_ssz_key_wr_nsc(uint8_t ssz_key_idx, uint8_t *wr_data);
uint32_t hal_otp_ssz_key_rd_nsc(uint8_t ssz_key_idx, uint8_t *rd_data);

uint16_t hal_adc_rd_inter_r_nsc(void);
int hal_user_otp_get_nsc(uint8_t offset, uint8_t len, uint8_t *buf);
int hal_user_otp_set_nsc(uint8_t offset, uint8_t len, uint8_t *buf);
int hal_otp_sb_key_get_nsc(uint8_t *psec_key, uint8_t key_type);
int hal_otp_sb_key_write_nsc(uint8_t *psec_key, uint8_t key_type);
int hal_otp_s_jtag_key_write_nsc(u8 *buf, u8 key_num);
int hal_otp_ns_jtag_key_write_nsc(u8 *buf, u8 key_num);
int hal_otp_crypto_key_get_nsc(uint8_t *pkey, uint8_t key_num);
int hal_otp_crypto_key_write_nsc(uint8_t *pkey, uint8_t key_num, uint8_t w_lock_en);
int hal_otp_ecdsa_key_get_nsc(uint8_t *pkey, uint8_t key_num);
int hal_otp_ecdsa_key_write_nsc(uint8_t *pkey, uint8_t key_num, uint8_t w_lock_en);
int hal_otp_ssz_lock_nsc(void);

/* Wrapper for NSC functions */
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_otp_init                            hal_otp_init_nsc
#endif
#define hal_otp_deinit                          hal_otp_deinit_nsc
#define hal_otp_ctrl_sel                        hal_otp_ctrl_sel_nsc
#define hal_otp_ctrl_sel_sts                    hal_otp_ctrl_sel_sts_nsc
#define hal_otp_pmc_gnt_ctrl                    hal_otp_pmc_gnt_ctrl_nsc
#define hal_otp_wr_gnt_ctrl                     hal_otp_wr_gnt_ctrl_nsc
#define hal_otpc_ctrl                           hal_otpc_ctrl_nsc
#define hal_otp_pwr_ctrl                        hal_otp_pwr_ctrl_nsc
#define hal_otp_test_mod_cfg                    hal_otp_test_mod_cfg_nsc
#define hal_otp_test_row_ctrl                   hal_otp_test_row_ctrl_nsc
#define hal_otp_chk_err_sts                     hal_otp_chk_err_sts_nsc
#define hal_otp_dsb_ctrl                        hal_otp_dsb_ctrl_nsc
#define hal_otp_rb_ctrl                         hal_otp_rb_ctrl_nsc
#define hal_otp_cz_crtl                         hal_otp_cz_ctrl_nsc
#define hal_otp_chk_cz_sts                      hal_otp_chk_cz_sts_nsc
#define hal_otp_clr_cz_sts                      hal_otp_clr_cz_sts_nsc
#define hal_otp_prct_ctrl                       hal_otp_prct_ctrl_nsc
#define hal_otp_chk_prct_sts                    hal_otp_chk_prct_sts_nsc
#define hal_otp_rd_lz_er_addr                   hal_otp_rd_lz_er_addr_nsc
#define hal_otp_clr_prct_sts                    hal_otp_clr_prct_sts_nsc
#define hal_otp_rd_sz_prct_sts                  hal_otp_rd_sz_prct_sts_nsc
#define hal_otp_clr_sz_prct_sts                 hal_otp_clr_sz_prct_sts_nsc
#define hal_otp_rd_ssz_prct_sts                 hal_otp_rd_ssz_prct_sts_nsc
#define hal_otp_clr_ssz_prct_sts                hal_otp_clr_ssz_prct_sts_nsc
#define hal_otp_szwl_ctrl                       hal_otp_szwl_ctrl_nsc
#define hal_otp_rd_aldn_sts                     hal_otp_rd_aldn_sts_nsc
#define hal_otp_clr_aldn_sts                    hal_otp_clr_aldn_sts_nsc
#define hal_otp_rd_al_sts                       hal_otp_rd_al_sts_nsc
#define hal_otp_clr_al_sts                      hal_otp_clr_al_sts_nsc
#define hal_otp_al_cfg                          hal_otp_al_cfg_nsc
#define hal_otp_al_ctrl_aon                     hal_otp_al_ctrl_aon_nsc
#define hal_otp_bust_ctrl                       hal_otp_bust_ctrl_nsc
#define hal_otp_rd_sub_aon                      hal_otp_rd_sub_aon_nsc
#define hal_otp_rd_aon                          hal_otp_rd_aon_nsc
#define hal_otp_byte_rd_aon                     hal_otp_byte_rd_aon_nsc
#define hal_otp_wr_sub_aon                      hal_otp_wr_sub_aon_nsc
#define hal_otp_wr_aon                          hal_otp_wr_aon_nsc
#define hal_otp_byte_wr_aon                     hal_otp_byte_wr_aon_nsc
#define hal_otp_cmp_aon                         hal_otp_cmp_aon_nsc
#define hal_otp_rd_sub_sys                      hal_otp_rd_sub_sys_nsc
#define hal_otp_rd_sys                          hal_otp_rd_sys_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_otp_byte_rd_sys                     hal_otp_byte_rd_sys_nsc
#endif
#define hal_otp_wr_sub_sys                      hal_otp_wr_sub_sys_nsc
#define hal_otp_wr_sys                          hal_otp_wr_sys_nsc
#define hal_otp_byte_wr_sys                     hal_otp_byte_wr_sys_nsc
#define hal_otp_cmp_sys                         hal_otp_cmp_sys_nsc
#define hal_otp_al_ctrl_sys                     hal_otp_al_ctrl_sys_nsc
#define hal_otp_rd_sub_syss                     hal_otp_rd_sub_syss_nsc
#define hal_otp_rd_syss                         hal_otp_rd_syss_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_otp_byte_rd_syss                    hal_otp_byte_rd_syss_nsc
#endif
#define hal_otp_wr_sub_syss                     hal_otp_wr_sub_syss_nsc
#define hal_otp_wr_syss                         hal_otp_wr_syss_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_otp_byte_wr_syss                    hal_otp_byte_wr_syss_nsc
#endif
#define hal_otp_cmp_syss                        hal_otp_cmp_syss_nsc
#define hal_otp_al_ctrl_syss                    hal_otp_al_ctrl_syss_nsc

#define hal_otp_byte_wr_marr_aon hal_otp_byte_wr_marr_aon_nsc
#define hal_otp_byte_wr_marr_sys hal_otp_byte_wr_marr_sys_nsc
#define hal_otp_byte_wr_marr_syss hal_otp_byte_wr_marr_syss_nsc
#define hal_otp_set_aon_vol hal_otp_set_aon_vol_nsc

#define hal_otp_rp_mar_rd_syss hal_otp_rp_mar_rd_syss_nsc
#define hal_otp_rp_chk_syss hal_otp_rp_chk_syss_nsc
#define hal_otp_rp_pg_syss hal_otp_rp_pg_syss_nsc

#define hal_otp_sz_key_wr hal_otp_sz_key_wr_nsc
#define hal_otp_sz_key_rd hal_otp_sz_key_rd_nsc
#define hal_otp_sz_key_lock hal_otp_sz_key_lock_nsc
#define hal_otp_ssz_key_wr hal_otp_ssz_key_wr_nsc
#define hal_otp_ssz_key_rd hal_otp_ssz_key_rd_nsc

#define hal_adc_rd_inter_r hal_adc_rd_inter_r_nsc
#define hal_user_otp_get hal_user_otp_get_nsc
#define hal_user_otp_set hal_user_otp_set_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_otp_sb_key_get hal_otp_sb_key_get_nsc
#define hal_otp_sb_key_write hal_otp_sb_key_write_nsc
#endif
#define hal_otp_s_jtag_key_write hal_otp_s_jtag_key_write_nsc
#define hal_otp_ns_jtag_key_write hal_otp_ns_jtag_key_write_nsc
#define hal_otp_crypto_key_get hal_otp_crypto_key_get_nsc
#define hal_otp_crypto_key_write hal_otp_crypto_key_write_nsc
#define hal_otp_ecdsa_key_get hal_otp_ecdsa_key_get_nsc
#define hal_otp_ecdsa_key_write hal_otp_ecdsa_key_write_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_otp_ssz_lock hal_otp_ssz_lock_nsc
#endif

#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_OTP_NSC_H_"


