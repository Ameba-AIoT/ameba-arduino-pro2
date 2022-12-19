/**************************************************************************//**
 * @file     hal_flash_boot.h
 * @brief    This file implements the entry functions of the Flash Booting
 *           API ROM functions.
 *
 * @version  V1.00
 * @date     2022-07-29
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

#ifndef _HAL_FLASH_BOOT_H_
#define _HAL_FLASH_BOOT_H_
#include "cmsis.h"
#include "fw_img.h"
#include "fw_img_tlv.h"
#include "fw_img_export.h"
#include "hal_sys_ctrl.h"

#ifdef  __cplusplus
extern "C"
{
#endif

extern const hal_flash_boot_stubs_t hal_flash_boot_stubs;     // symbol from linker script
extern const hal_flash_boot_tlv_stubs_t hal_flash_boot_tlv_stubs;

#if !defined(CONFIG_BUILD_NONSECURE)
__STATIC_INLINE
void *boot_get_partition_tbl(void)
{
	return hal_flash_boot_stubs.ppartition_tbl;
}

__STATIC_INLINE
void *boot_get_fw1_key_tbl(void)
{
	return hal_flash_boot_stubs.get_fw1_key_tbl();
}

__STATIC_INLINE
void *boot_get_fw2_key_tbl(void)
{
	return hal_flash_boot_stubs.get_fw2_key_tbl();
}

__STATIC_INLINE
void boot_clear_partition_tbl(void)
{
	hal_flash_boot_stubs.clear_export_partition_tbl();
}

__STATIC_INLINE
void boot_loader_erase(uint32_t code_start, uint32_t code_size, uint32_t img2_entry)
{
	hal_flash_boot_stubs.erase_boot_loader(code_start, code_size, img2_entry);
}


__STATIC_INLINE
void *get_fw_img_info_tbl(void)
{
	return hal_flash_boot_stubs.fw_img_info_tbl_query();
}

__STATIC_INLINE
int32_t fw_img_update_over_uart(hal_uart_adapter_t *potu_uart, uint32_t flash_sel, uint32_t flash_offset)
{
	return hal_flash_boot_stubs.otu_fw_download(potu_uart, flash_sel, flash_offset);
}

__STATIC_INLINE
void *boot_get_tlv_partition_tbl(void)
{
	return hal_flash_boot_tlv_stubs.ppartition_tbl;
}

__STATIC_INLINE
void *boot_get_key_certi(void)
{
	return hal_flash_boot_tlv_stubs.pkeycerti;
}

__STATIC_INLINE
void *boot_get_enc_sec_info(void)
{
	return hal_flash_boot_tlv_stubs.penc_sec_info;
}

__STATIC_INLINE
void *boot_get_isp_iq_fcs_ld_sts(void)
{
	uint8_t v_main = 0;
	v_main = hal_sys_get_rom_ver();
	if (IS_AFTER_CUT_C(v_main)) {
		return hal_flash_boot_tlv_stubs.pisp_iq_ld_sts;
	} else {
		return NULL;
	}
}

__STATIC_INLINE
void boot_clear_partition_tbl_info(void)
{
	hal_flash_boot_tlv_stubs.clear_export_partition_tbl_info();
}

__STATIC_INLINE
void boot_clear_keycerti_info(void)
{
	hal_flash_boot_tlv_stubs.clear_export_sb_keycerti_info();
}

__STATIC_INLINE
void boot_clear_sec_info(void)
{
	uint8_t v_main = 0;
	v_main = hal_sys_get_rom_ver();
	if (IS_AFTER_CUT_B(v_main)) {
		hal_flash_boot_tlv_stubs.clear_export_enc_sec_info();
	}
}

__STATIC_INLINE
int boot_verify_manif_f(const uint8_t *img_offset, const uint8_t info_type, sec_boot_info_t *p_sb_info)
{
	return (hal_flash_boot_tlv_stubs.verify_manif_f(img_offset, info_type, p_sb_info));
}

__STATIC_INLINE
void boot_load_img_hdr_f(const uint8_t *img_offset, fw_img_hdr_t *img_hdr_buf, const uint8_t sel_img_load)
{
	uint8_t *ptr = (uint8_t *)img_offset;
	fw_img_hdr_t *pimg_hdr = img_hdr_buf;
	// set img hdr data
	BOOT_RAM_SAFE_LOAD_DEVICE_TO_MEM((void *)pimg_hdr, (void *)ptr, sizeof(fw_img_hdr_t), FW_IMG_HDR_MAX_SIZE);
	return;
}

__STATIC_INLINE
uint8_t boot_sec_search_available_idx(uint8_t *p_sts, const uint8_t cfg_max_size)
{
	return (hal_flash_boot_tlv_stubs.search_available_idx(p_sts, cfg_max_size));
}

__STATIC_INLINE
int boot_sec_xip_pending_cfg_add_rmp(hal_sec_region_cfg_t *psb_sec_cfg_pending, img_region_lookup_t *pimg_rmp_lkp_tbl,
									 uint32_t phy_addr, uint32_t remap_addr, uint32_t remap_sz)
{
	return (hal_flash_boot_tlv_stubs.xip_pending_cfg_add_rmp(psb_sec_cfg_pending, pimg_rmp_lkp_tbl, phy_addr, remap_addr, remap_sz));
}

__STATIC_INLINE
int boot_sec_xip_pending_process_rmp(hal_sec_region_cfg_t *psb_sec_cfg_pending, sec_boot_info_t *p_sb_info)
{
	return (hal_flash_boot_tlv_stubs.xip_pending_process_rmp(psb_sec_cfg_pending, p_sb_info));
}

__STATIC_INLINE
int boot_sec_xip_disable_rmp_config(hal_sec_region_cfg_t *psb_sec_cfg_pending, uint8_t region_sel)
{
	return (hal_flash_boot_tlv_stubs.xip_disable_rmp_config(psb_sec_cfg_pending, region_sel));
}

__STATIC_INLINE
int boot_sec_xip_pending_cfg_add_dec_key(hal_sec_region_cfg_t *psb_sec_cfg_pending, const uint8_t key_id)
{
	return (hal_flash_boot_tlv_stubs.xip_pending_cfg_add_dec_key(psb_sec_cfg_pending, key_id));
}

__STATIC_INLINE
int boot_sec_xip_pending_cfg_add_dec(hal_sec_region_cfg_t *psb_sec_cfg_pending, img_region_lookup_t *pimg_dec_lkp_tbl,
									 uint8_t cipher_sel, uint32_t dec_base, uint32_t dec_sz,
									 uint32_t iv_ptn_low, uint32_t iv_ptn_high,
									 uint32_t tag_base_addr, uint32_t tag_flh_addr, uint32_t total_hdr_size)
{
	return (hal_flash_boot_tlv_stubs.xip_pending_cfg_add_dec(psb_sec_cfg_pending, pimg_dec_lkp_tbl, cipher_sel, dec_base, dec_sz,
			iv_ptn_low, iv_ptn_high,
			tag_base_addr, tag_flh_addr, total_hdr_size));
}

__STATIC_INLINE
int boot_sec_xip_pending_process_dec(hal_sec_region_cfg_t *psb_sec_cfg_pending, sec_boot_info_t *p_sb_info)
{
	return (hal_flash_boot_tlv_stubs.xip_pending_process_dec(psb_sec_cfg_pending, p_sb_info));
}

__STATIC_INLINE
int boot_sec_xip_disable_dec_config(hal_sec_region_cfg_t *psb_sec_cfg_pending, uint8_t region_sel)
{
	return (hal_flash_boot_tlv_stubs.xip_disable_dec_config(psb_sec_cfg_pending, region_sel));
}

__STATIC_INLINE
int boot_img_rmp_and_dec_lkp_tbl_insert(img_region_lookup_t *plkp_tbl, uint8_t tbl_size, uint8_t is_xip, uint8_t *tbl_cnt)
{
	return (hal_flash_boot_tlv_stubs.img_rmp_and_dec_lkp_tbl_insert(plkp_tbl, tbl_size, is_xip, tbl_cnt));
}

__STATIC_INLINE
void boot_img_rmp_and_dec_lkp_tbl_remove(img_region_lookup_t *plkp_tbl, uint8_t *tbl_cnt)
{
	return (hal_flash_boot_tlv_stubs.img_rmp_and_dec_lkp_tbl_remove(plkp_tbl, tbl_cnt));
}

__STATIC_INLINE
int boot_img_get_ld_sel_info_from_ie(const uint8_t img_obj, const uint8_t *ptr, img_manifest_ld_sel_t *pld_sel_info)
{
	return (hal_flash_boot_tlv_stubs.img_get_ld_sel_info_from_ie(img_obj, ptr, pld_sel_info));
}

__STATIC_INLINE
uint32_t boot_get_ld_version(const uint8_t img_obj, uint8_t *p_img_version)
{
	return (hal_flash_boot_tlv_stubs.get_ld_version(img_obj, p_img_version));
}

__STATIC_INLINE
uint32_t boot_get_ld_timst(uint8_t *p_img_timest)
{
	return (hal_flash_boot_tlv_stubs.get_ld_timst(p_img_timest));
}

__STATIC_INLINE
void boot_set_fw_img_rollback_check_en_ctrl(uint8_t en)
{
	uint8_t v_main = 0;
	v_main = hal_sys_get_rom_ver();
	if (IS_AFTER_CUT_C(v_main)) {
		hal_flash_boot_tlv_stubs.set_fw_img_rollback_check_en_ctrl(en);
	}
}

__STATIC_INLINE
int boot_img_get_ld_sel_idx(const uint8_t img_obj, img_manifest_ld_sel_t *pld_sel_info1, img_manifest_ld_sel_t *pld_sel_info2, uint8_t img1_idx,
							uint8_t img2_idx)
{
	return (hal_flash_boot_tlv_stubs.img_get_ld_sel_idx(img_obj, pld_sel_info1, pld_sel_info2, img1_idx, img2_idx));
}

__STATIC_INLINE
uint32_t boot_img_get_update_sel_idx(const uint8_t img_obj, img_manifest_ld_sel_t *pld_sel_info1, img_manifest_ld_sel_t *pld_sel_info2, uint8_t img1_idx,
									 uint8_t img2_idx)
{
	return (hal_flash_boot_tlv_stubs.img_get_update_sel_idx(img_obj, pld_sel_info1, pld_sel_info2, img1_idx, img2_idx));
}

__STATIC_INLINE
int boot_img_sel_op_idx(void *p_tbl_info, const uint8_t img_obj, const uint8_t img_sel_op)
{
	return (hal_flash_boot_tlv_stubs.img_sel_op_idx(p_tbl_info, img_obj, img_sel_op));
}

__STATIC_INLINE
void boot_img_set_fw_img_load_info(fw_img_tlv_export_info_type_t *p_set_fw_img_info)
{
	uint8_t v_main = 0;
	v_main = hal_sys_get_rom_ver();
	if (IS_AFTER_CUT_C(v_main)) {
		hal_flash_boot_tlv_stubs.set_fw_img_load_info(p_set_fw_img_info);
	}
}

__STATIC_INLINE
void boot_img_record_fw_ld_info(const uint8_t img_obj, void *pimg_info_export, void *img1_addr, void *img2_addr, img_manifest_ld_sel_t *pld_sel_info)
{
	uint8_t v_main = 0;
	v_main = hal_sys_get_rom_ver();
	if (IS_AFTER_CUT_C(v_main)) {
		hal_flash_boot_tlv_stubs.record_fw_ld_info(img_obj, pimg_info_export, img1_addr, img2_addr, pld_sel_info);
	}
}

__STATIC_INLINE
void boot_flash_sec_crypto_gen_iv(uint32_t flash_addr, uint32_t cahce_line_size, Flash_SEC_IV_Data_t *p_sec_iv, uint32_t iv_len)
{
	hal_flash_boot_tlv_stubs.flash_sec_crypto_gen_iv(flash_addr, cahce_line_size, p_sec_iv, iv_len);
}

__STATIC_INLINE
void boot_flash_sec_crypto_xor_data(unsigned char *buf1, unsigned char *buf2, uint32_t len, unsigned char *result)
{
	hal_flash_boot_tlv_stubs.flash_sec_crypto_xor_data(buf1, buf2, len, result);
}

#endif  // end of "#if !defined(CONFIG_BUILD_NONSECURE)"

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_FLASH_BOOT_H_"

