/**************************************************************************//**
 * @file     bootloader.h
 * @brief    Declare functions for boot loader.
 *
 * @version  V1.00
 * @date     2022-09-28
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

#ifndef _BOOT_LOADER_H_
#define _BOOT_LOADER_H_
#if defined(CONFIG_BUILD_BOOT) && (CONFIG_BUILD_BOOT == 1)

#include "fw_img_tlv.h"
#include "fw_img_export.h"
#include "hal_crypto.h"
#include "voe_boot_loader.h"
#include "rtl8735b_voe_status.h"
#include "memory.h"

#define RAM_FUN_TABLE_VALID_DRAM_START_ADDR    (0x70000000)
#define RAM_FUN_TABLE_VALID_DRAM_END_ADDR      (0x80000000)

#define TEMP_DECRYPT_BUF_SIZE       (384)       // al least > sizeof(fw_sub_image_type_t) + sizeof(fm_image_header_t) + sizeof(raw_image_hdr_t)

enum voe_flash_load_sel {
	NOR_LOAD_MEMCPY             = 0x0,
	SNAND_LOAD_SIM_MEMCPY       = 0x10,
	SNAND_LOAD_SIM_DEC          = 0x11
};

typedef struct snand_decrypt_info {
	BOOL valid;
	const sec_boot_info_t *sb_info;
} snand_decrypt_info_t;

typedef struct snand_decryp_ivptn_s {
	uint8_t data[EACH_IV_DATA_SIZE * 2];
} snand_decryp_ivptn_t;

typedef struct snand_img_data_addr_s {
	hal_snand_part_adpt_t *p_img_part_adpt;
	uint32_t *p_cur_offset;
	uint32_t *p_real_addr;
	uint32_t resv;
} snand_img_data_addr_t;

typedef struct video_img_ld_sts_s {
	uint8_t isp_enc;
	uint8_t voe_enc;
	uint8_t resv1[2];
	uint32_t isp_iq_img_addr;
	uint32_t fw_img_addr;
	uint32_t resv2;
} video_img_ld_sts_t;

// NOR Flash Boot
typedef int (*img_hsh_init_f_t)(const uint8_t *key, const uint32_t key_len);
typedef int (*img_hsh_update_f_t)(const uint8_t *msg, const uint32_t msg_len);
typedef int (*img_hsh_final_f_t)(uint8_t *digest);
typedef void (*flash_cpy_t)(void *, const void *, size_t);

extern boot_init_flags_t boot_init_flags;
extern sec_boot_info_t sb_ram_info;
extern uint8_t sb_digest_buf[IMG_HASH_CHK_DIGEST_MAX_SIZE];
extern hal_flash_sec_adapter_t sec_adtr;
extern hal_xip_sce_cfg_t xip_sce_cfg_pending __ALIGNED(32);
extern hal_sec_region_cfg_t sb_ram_sec_cfg_pending __ALIGNED(32);
extern uint8_t sec_digest_buf[2][20];
extern uint32_t fw1_xip_img_phy_offset; // simu
extern uint8_t tmp_img_hdr[FW_IMG_HDR_MAX_SIZE];
extern uint8_t tmp_sect_hdr[FW_IMG_HDR_MAX_SIZE];
extern uint8_t aes_gcm_tagfor_4k[512];
extern uint8_t aes_iv_info[2][4];
extern sb_crypto_enc_info_t crypto_enc_info;
extern uint8_t aes_key_info[SB_SEC_KEY_SIZE];
extern uint8_t mani_data[MANIFEST_IEDATA_SIZE];
extern fw_ld_export_info_type_t fw_ld_export_info;
extern int __voe_code_start__[];            // VOE DDR address
extern voe_ld_export_info_type_t voe_ld_export_info;
extern voe_fcs_peri_info_t voe_fcs_peri_info;
extern video_img_ld_sts_t video_img_ld_info;
extern uint8_t voe_fcs_para_raw[BOOT_LD_FCS_PARA_IMG_MAX_SIZE];
extern snand_decrypt_info_t ispiq_img_dec_info;

int fw_load_img_sect_f(const uint8_t *img_offset, fw_img_hdr_t *pfw_hdr, sec_boot_info_t *p_sb_info);
int sb_ram_img_vrf_op(const uint8_t sbl_cfg, sec_boot_info_t *p_sb_info, const uint8_t info_type);
uint8_t sb_ram_sect_ld_hash_prechk_valid_f(sec_boot_info_t *p_sb_info);
int sb_ram_sect_ld_hash_chk_f(uint8_t *p_msg, uint32_t msglen, uint8_t *p_img_digest_chk, sec_boot_info_t *p_sb_info);
int sec_ram_cfg_f_init(hal_sec_region_cfg_t *psb_sec_cfg_pending);
int flash_sec_crypto_ram_init(uint8_t sec_mode, uint8_t *pIv_info, uint32_t iv_len, uint8_t key_idx, uint32_t key_len);
int flash_sec_crypto_ram_decrypt(uint32_t flash_addr, uint8_t *pMsg, uint32_t msglen, uint8_t *pResult, uint8_t *pflh_Tag);
uint8_t sb_ram_sect_ld_hash_prechk_valid_f(sec_boot_info_t *p_sb_info);
uint8_t chk_img_type_id_invalid(const uint16_t type_id);
int sec_ram_key_register_key_stg(sec_boot_info_t *p_sb_info);
int confirm_manif_label_f(const uint8_t *ptr);
void record_fw_ld_info(const uint8_t img_obj, fw_img_tlv_export_info_type_t *pfw_img_info, void *fw1_addr, void *fw2_addr, img_manifest_ld_sel_t *pld_sel_info);
int verify_fw_manif_f(const uint8_t *img_offset, const uint8_t info_type, sec_boot_info_t *p_sb_info);
int multi_sensor_info_load(const uint8_t *img_offset, isp_multi_fcs_ld_info_t *p_isp_sensor_ld_info, flash_cpy_t load_op_f);
void dump_mutli_sensor_info(isp_multi_fcs_ld_info_t *p_isp_sensor_ld_info, flash_cpy_t load_op_f);
int32_t chk_manifest_lbl(unsigned char *lbl_name);
int boot_img_get_ld_select_idx(const uint8_t img_obj, img_manifest_ld_sel_t *pld_sel_info1, img_manifest_ld_sel_t *pld_sel_info2, uint8_t img1_idx,
							   uint8_t img2_idx);
int boot_img_anti_rollback(const uint8_t img_obj, const int ld_img_idx);
void boot_record_fw_ld_info(const uint8_t img_obj, fw_img_tlv_export_info_type_t *pfw_img_info, void *fw1_addr, void *fw2_addr,
							img_manifest_ld_sel_t *pld_sel_info);
void bl_load_ispiq_img_core(fw_img_hdr_t *pfw_hdr, uint8_t *pFw_data);
void bl_get_ispiq_imgsz_manif_ie_f(const uint8_t *ptr, uint32_t *p_imgsz);
void img_part_rd_export_info_load(const uint8_t export_obj, void *part_record, void *p_setinfo);
void img_data_export_info_load(const uint8_t export_obj, const uint32_t img_manif_addr, flash_cpy_t load_op_f);
void img_load_fail_set_rollback(void *pfw_load_info);
int ram_vrf_dest_sect_load(void *device_ctrl_adptr, void *data_addr, sect_hdr_t *psect_hdr, uint8_t *pimg_load_dest, uint32_t img_load_size,
						   sec_boot_info_t *p_sb_info);
int chk_load_fw_idx(const uint8_t boot_sel, void *pfw_img_partrd, uint8_t *pld_fw_idx_user);
int ram_vrf_img_from_device_load(void *device_ctrl_adptr, void *p_part_record, void *p_img_data,
								 sec_boot_info_t *p_sb_info, const uint8_t sbl_cfg);
int ram_vrf_isp_img_from_device_load(void *device_ctrl_adptr, void *p_part_record, void *p_img_data, sec_boot_info_t *p_sb_info);
int sb_ram_preld_img_manifest_data(const uint8_t *ptr, sec_boot_info_t *p_sb_info, void *p_sb_data, const uint8_t info_type);
int verify_manif_4imgpayld_ram_f(const uint8_t *img_offset, const uint8_t info_type, sec_boot_info_t *p_sb_info, void *p_ld_info);
uint8_t chk_ram_sect_type_id_invalid(const uint16_t type_id);

// NAND Flash Boot
int sb_snand_hash_update(img_hsh_update_f_t img_hsh_update_f, uint32_t msglen, uint8_t *p_msg, uint8_t is_flash_dat);
hal_status_t snand_fw_img_memcpy(void *dst, const void *src, u32 size);
hal_status_t snand_iq_img_memcpy(void *dst, const void *src, u32 size);
s32 snand_voe_img_decrypt(void *const _dst, const void *_src, u32 size);
s32 snand_ispiq_img_decrypt(void *const dest, const void *src, u32 size);
s32 snand_load_cipher_sect_data(hal_snand_part_adpt_t *part_adpt,
								sect_hdr_t *sect_hdr, const u32 offset,
								sec_boot_info_t *sb_info);

__STATIC_FORCEINLINE
void ie_safe_load(void *dst, const void *src, const uint32_t size, const uint32_t max_size)
{
	BOOT_RAM_SAFE_LOAD_DEVICE_TO_MEM(dst, src, size, max_size);
}

#endif  // end of CONFIG_BUILD_BOOT
#endif  // end of "#define _BOOT_LOADER_H_"
