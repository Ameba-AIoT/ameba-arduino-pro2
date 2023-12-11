/**************************************************************************//**
 * @file     fw_img_export.h
 * @brief    Define data format exported after boot.
 * @version  V1.00
 * @date     2022-07-08
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
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
 *
 ******************************************************************************/

#ifndef _FW_IMG_EXPORT_H_
#define _FW_IMG_EXPORT_H_

#include "fw_snand_boot.h"
#include "fw_img_tlv.h"
#include "voe_boot_loader.h"

#ifdef  __cplusplus
extern "C"
{
#endif

enum user_load_fw_idx_e {
	USER_LOAD_FW_FOLLOW_DEFAULT = 0x0,
	USER_LOAD_FW1               = 0x1,
	USER_LOAD_FW2               = 0x2,
};

typedef struct fw_img_pre_boot_fail_sts_s {
	uint8_t img_preld_fail_chk_en;
	uint8_t img_preidx_ld_fail;
	uint8_t kc_preld_fail_bind_img_en;
	uint8_t resv;
} fw_img_pre_boot_fail_sts_t, *pfw_img_pre_boot_fail_sts_t;

typedef struct fw_img_manifest_ld_sel_sts_s {
	uint8_t valid;
	uint8_t resv[3];
	uint32_t timestamp;
	uint8_t version[IMG_MANIFEST_IE_VERSION_SIZE];
} fw_img_manifest_ld_sel_sts_t, *pfw_img_manifest_ld_sel_sts_t;

typedef struct fw_img_user_export_info_type_s {
	fw_img_manifest_ld_sel_sts_t fw1_ld_sel_info;
	fw_img_manifest_ld_sel_sts_t fw2_ld_sel_info;
	fw_img_pre_boot_fail_sts_t pre_boot_fail_sts;
} fw_img_user_export_info_type_t, *pfw_img_user_export_info_type_t;

// Export info of a NAND partition
typedef struct snand_export_part_info {
	u16 blk_cnt;
	snand_addr_t rec0_addr;
	snand_vblk_idx_t vmap[SNAND_VMAP_MAX];
} snand_export_part_info_t;

typedef struct fw_img_tlv_export_info_type_s {
	uint32_t img1_start_offset;                  // the NOR flash offset of FW1 image start
	uint32_t img2_start_offset;                  // the NOR flash offset of FW2 image start
	snand_export_part_info_t img1_nand_addr;     // the NAND flash address of FW1 image start
	snand_export_part_info_t img2_nand_addr;     // the NAND flash address of FW2 image start
	uint32_t img1_version;                       // the FW1 IEs info(version)
	uint32_t img2_version;                       // the FW2 IEs info(version)
	uint32_t img1_timest;                        // the FW1 IEs info(timestamp)
	uint32_t img2_timest;                        // the FW2 IEs info(version)
	uint8_t img1_label_valid;                    // is FW1 label valid (OTA signature valid)
	uint8_t img2_label_valid;                    // is FW2 label valid (OTA signature valid)
	uint8_t img1_valid;                          // is FW1 type_id valid (OTA load object valid)
	uint8_t img2_valid;                          // is FW2 type_id valid (OTA load object valid)
	int img_record_idx;                          // the loaded (to RAM) FW record index of partition table
	uint16_t img_ld_type_id;                     // the loaded (to RAM) FW typed id of partition table
	uint8_t  resv1[2];
	uint32_t resv2[7];
} fw_img_tlv_export_info_type_t, *pfw_img_tlv_export_info_type_t;

typedef struct fw_ld_export_info_type_s {
	uint8_t user_sel_en;
	uint8_t resv[3];
	fw_img_tlv_export_info_type_t fw_sel_ld_info;
	fw_img_user_export_info_type_t fw_user_sel_ld_info;
} fw_ld_export_info_type_t, *pfw_ld_export_info_type_t;

typedef struct voe_ld_export_info_type_s {
	isp_multi_fcs_ld_info_t isp_multi_sensor_ld_info;
	voe_img_ld_info_type_t  voe_img_ld_info;
} voe_ld_export_info_type_t, *pvoe_ld_export_info_type_t;

typedef struct isp_iq_fw_info_s {
	uint16_t type_id;
	uint8_t resv[2];
	uint32_t start_addr;
	uint32_t length;
} isp_iq_fw_info_t;

typedef struct _BL4FW_INFO_T_ {
	struct {
		uint8_t str_sign[BL4FW_STR_SIGN_MAX_SIZE];
		uint32_t resv[4];
	} hdr;
	fw_ld_export_info_type_t data;
} BL4FW_INFO_T;

typedef struct _BL4VOE_INFO_T_ {
	struct {
		uint8_t str_sign[BL4VOE_STR_SIGN_MAX_SIZE];
		uint32_t resv[4];
	} hdr;
	uint8_t data[BL4VOE_INFO_DATA_MAX_SIZE];
} BL4VOE_INFO_T;

typedef struct _BL4VOE_LOAD_INFO_T_ {
	struct {
		uint8_t str_sign[BL4VOE_STR_SIGN_MAX_SIZE];
		uint32_t resv[4];
	} hdr;
	voe_ld_export_info_type_t data;
} BL4VOE_LOAD_INFO_T;

typedef struct _BL4VOE_PERI_INFO_T_ {
	struct {
		uint8_t str_sign[BL4VOE_PERI_STR_SIGN_MAX_SIZE];
		uint32_t resv[4];
	} hdr;
	voe_fcs_peri_info_t data; //32 bytes
	uint8_t resv[BL4VOE_INFO_DATA_MAX_SIZE - sizeof(voe_fcs_peri_info_t)];


} BL4VOE_PERI_INFO_T;


#if defined(ROM_REGION)
extern fw_img_tlv_export_info_type_t kc_image_info;
extern fw_img_tlv_export_info_type_t bl_image_info;
#endif

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _FW_IMG_EXPORT_H_"

