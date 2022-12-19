/**************************************************************************//**
 * @file     fw_img_tlv.h
 * @brief    This file defines the image tlv(type-length-value) format for boot flow and some secure info type
 *           for secure boot.
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

#ifndef _FW_IMG_TLV_H_
#define _FW_IMG_TLV_H_

#include "otp_boot_cfg.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/*
   Boot Fail/Error number
*/

/* Normal boot ROM */
#define _ERRNO_BOOT_UNKNOWN_BOOT_MODE                                   (0x10)
#define _ERRNO_BOOT_INVALID_RAM_IMG_SIGN_OR_START_FUNC_ADDR             (0x11)
#define _ERRNO_BOOT_INVALID_RAM_START_FUNC_ADDR                         (0x12)
#define _ERRNO_BOOT_IMG_SEL_IDX_FAIL                                    (0x13)
#define _ERRNO_BOOT_SEL_IMG_INVALID_TO_LOAD                             (0x14)
#define _ERRNO_BOOT_SEL_IMG_WRONG_TYPE_ID                               (0x15)
#define _ERRNO_BOOT_NULL_POINTER                                        (0x16)
#define _ERRNO_BOOT_MSGLEN_IS_NULL                                      (0x17)
#define _ERRNO_BOOT_INVALID_MANI_LABEL                                  (0x18)
#define _ERRNO_BOOT_INVALID_MANI_IE_TOTAL_SIZE                          (0x19)
#define _ERRNO_BOOT_MANI_UNPT_AREA_CRC_VRF_FAIL                         (0x1A)
#define _ERRNO_BOOT_GET_WRONG_TYPE_ID_FAIL                              (0x1B)
#define _ERRNO_BOOT_SET_SJTAG_NFIXED_INVALID_SJTAG_OBJ                  (0x1C)
#define _ERRNO_BOOT_SET_SJTAG_NFIXED_KSKN_CNTENT_NULL                   (0x1D)
#define _ERRNO_BOOT_UNSUPPORT_VRF_ALG                                   (0x1E)
#define _ERRNO_BOOT_UNSUPPORT_CTRL_OBJ                                  (0x1F)
#define _ERRNO_BOOT_INVALID_VERSION_ANTI_ROLBK                          (0x20)
#define _ERRNO_BOOT_ADDR_OUT_OF_RANGE                                   (0x21)


/* Secure boot */
#define _ERRNO_BOOT_SB_IMG_PBK_HASH_VRF_FAIL                            (0x30)
#define _ERRNO_BOOT_SB_HKDF_SECURE_INIT_FAIL                            (0x31)
#define _ERRNO_BOOT_SB_HKDF_EXTRACT_SEC_ALL_FAIL                        (0x32)
#define _ERRNO_BOOT_SB_HKDF_EXPAND_SEC_ALL_FAIL                         (0x33)
#define _ERRNO_BOOT_SB_IMG_HASH_INIT_FAIL                               (0x34)
#define _ERRNO_BOOT_SB_IMG_HASH_UPDATE_FAIL                             (0x35)
#define _ERRNO_BOOT_SB_IMG_HASH_FINAL_FAIL                              (0x36)
#define _ERRNO_BOOT_SB_IMG_HASH_CORE_F_FAIL                             (0x37)
#define _ERRNO_BOOT_SB_INVALID_ENC_RMP_BASE_ADDR                        (0x38)
#define _ERRNO_BOOT_SB_NO_AVAILABLE_SEC_RMP_CFG_RGN                     (0x39)
#define _ERRNO_BOOT_SB_NO_AVAILABLE_SEC_RMP_CFG_IDX                     (0x3A)
#define _ERRNO_BOOT_SB_SET_SEC_RMP_FAIL                                 (0x3B)
#define _ERRNO_BOOT_SB_SEC_ENC_RECORD_INFO_FAIL                         (0x3C)
#define _ERRNO_BOOT_SB_BOOT_IMG_NON_SUPPORT_XIP_IMG_LOAD                (0x3D)
#define _ERRNO_BOOT_SB_SET_SEC_AES_GCM_MULTIPLE_FAIL                    (0x3E)
#define _ERRNO_BOOT_SB_CAL_TAG_BASE_FAIL                                (0x3F)
#define _ERRNO_BOOT_SB_NO_AVAILABLE_SEC_DEC_CFG_RGN                     (0x40)
#define _ERRNO_BOOT_SB_NO_AVAILABLE_SEC_DEC_CFG_IDX                     (0x41)
#define _ERRNO_BOOT_SB_SET_SEC_DEFAULT_DEC_INIT_FAIL                    (0x42)
#define _ERRNO_BOOT_SB_SET_SEC_DEC_RGN_INIT_FAIL                        (0x43)
#define _ERRNO_BOOT_SB_SET_SEC_DEC_CIPHER_ALG_UNKNOWN                   (0x44)
#define _ERRNO_BOOT_SB_SET_SEC_DEC_RGN_ENABLE_FAIL                      (0x45)
#define _ERRNO_BOOT_SB_IMG_SECT_LD_HASH_CHK_FAIL                        (0x46)
#define _ERRNO_BOOT_SB_CRYPTO_INIT_FAIL                                 (0x47)
#define _ERRNO_BOOT_SB_NOT_ALLOW_IMG_LOAD_AFTER_XIP_IMG_SET             (0x48)
#define _ERRNO_BOOT_SB_GCM_TAG_CMP_FAIL                                 (0x49)
#define _ERRNO_BOOT_SB_FLASH_SEC_CRYPTO_GET_SK_CFG_FAIL                 (0x4A)
#define _ERRNO_BOOT_SB_FLASH_SEC_CRYPTO_AES_GCM_TAG_NOT_MATCH           (0x4B)
#define _ERRNO_BOOT_SB_FLASH_SEC_CRYPTO_AES_INVALID_IVLEN               (0x4C)
#define _ERRNO_BOOT_SB_FLASH_SEC_CRYPTO_AES_INVALID_KEYLEN              (0x4D)
#define _ERRNO_BOOT_SB_FLASH_SEC_CRYPTO_AES_INVALID_CACHE_LINE_SIZE     (0x4E)
#define _ERRNO_BOOT_SB_PBK_SIGN_VRF_FAIL                                (0x4F)

/* Secure boot error extended */
#define _ERRNO_BOOT_SB_CRYPTO_AES_GCM_SK_INIT_FAIL                      (0x80)
#define _ERRNO_BOOT_SB_CRYPTO_AES_GCM_DEC_FAIL                          (0x81)
#define _ERRNO_BOOT_SB_CRYPTO_AES_ECB_SK_INIT_FAIL                      (0x82)
#define _ERRNO_BOOT_SB_CRYPTO_AES_CTR_ENC_BLK_FAIL                      (0x83)
#define _ERRNO_BOOT_SB_CRYPTO_AES_ECB_DEC_FAIL                          (0x84)

/* UART Boot */
#define _ERRNO_BOOT_UART_BOOT_FW_DOWNLOAD_SIZE_NULL                     (0x50)

/* NAND Boot */
#define _ERRNO_BOOT_NAND_BOOT_NONSUPPORT_NTLV_FORMAT                    (0x60)
#define _ERRNO_BOOT_SNAFC_INIT_FAIL                                     (0x61)
#define _ERRNO_BOOT_SNAFC_DEINIT_FAIL                                   (0x62)
#define _ERRNO_BOOT_SNAFC_MEMCPY_FAIL                                   (0x63)
#define _ERRNO_BOOT_SNAFC_OFFSET_FAIL                                   (0x64)
#define _ERRNO_BOOT_NAND_NO_VALID_CTRL_BLK                              (0x65)
#define _ERRNO_BOOT_NAND_INVALID_CTRL                                   (0x66)
#define _ERRNO_BOOT_NAND_NO_VALID_PART_BLK                              (0x67)
#define _ERRNO_BOOT_NAND_NO_VALID_ISP_IDX                               (0x68)
#define _ERRNO_BOOT_NAND_NO_VALID_BL_IDX                                (0x69)
#define _ERRNO_BOOT_NAND_BLK_OVERFLOW                                   (0x64)
#define _ERRNO_BOOT_NAND_GLB_VMAP_SLOT                                  (0x65)

#define _ERRNO_BOOT_NAND_NO_SUPPORT_TB                                  (0x70)

#define _ERRNO_BOOT_MSG_SIZE_OUT_OF_RANGE                               (0xA0)
#define _ERRNO_BOOT_INVALID_STR_SIGN_VAL                                (0xA1)
#define _ERRNO_BOOT_IDX_OUT_OF_RANGE                                    (0xA2)
#define _ERRNO_BOOT_DEV_CTRL_INIT_FAIL                                  (0xA3)
#define _ERRNO_BOOT_FCS_DATA_HEADER_FAIL                                (0xA4)


#define BOOT_LD_FAIL_IMG_TYPE_ERR_STS_SHIFT                             (24)
#define BOOT_LD_FAIL_IMG_TYPE_ERR_STS_MASK                              (0xFF << BOOT_LD_FAIL_IMG_TYPE_ERR_STS_SHIFT)
#define BOOT_LD_FAIL_FLOW_CHK_ERR_STS_SHIFT                             (8)
#define BOOT_LD_FAIL_FLOW_CHK_ERR_STS_MASK                              (0xFFFF)
#define BOOT_LD_FAIL_KC_REG_ERR_STS_SHIFT                               (16)
#define BOOT_LD_FAIL_KC_REG_ERR_STS_MASK                                (0x3 << BOOT_LD_FAIL_KC_REG_ERR_STS_SHIFT)
#define BOOT_LD_FAIL_KC1_REG_ERR_STS_EN_SHIFT                           (16)
#define BOOT_LD_FAIL_KC1_REG_ERR_STS_EN                                 (0x1 << BOOT_LD_FAIL_KC1_REG_ERR_STS_EN_SHIFT)
#define BOOT_LD_FAIL_KC2_REG_ERR_STS_EN_SHIFT                           (17)
#define BOOT_LD_FAIL_KC2_REG_ERR_STS_EN                                 (0x1 << BOOT_LD_FAIL_KC2_REG_ERR_STS_EN_SHIFT)
#define BOOT_LD_FAIL_BL_REG_ERR_STS_SHIFT                               (18)
#define BOOT_LD_FAIL_BL_REG_ERR_STS_MASK                                (0x3 << BOOT_LD_FAIL_BL_REG_ERR_STS_SHIFT)
#define BOOT_LD_FAIL_BL1_REG_ERR_STS_EN_SHIFT                           (18)
#define BOOT_LD_FAIL_BL1_REG_ERR_STS_EN                                 (0x1 << BOOT_LD_FAIL_BL1_REG_ERR_STS_EN_SHIFT)
#define BOOT_LD_FAIL_BL2_REG_ERR_STS_EN_SHIFT                           (19)
#define BOOT_LD_FAIL_BL2_REG_ERR_STS_EN                                 (0x1 << BOOT_LD_FAIL_BL2_REG_ERR_STS_EN_SHIFT)
#define BOOT_LD_FAIL_FW_REG_ERR_STS_SHIFT                               (20)
#define BOOT_LD_FAIL_FW_REG_ERR_STS_MASK                                (0x3 << BOOT_LD_FAIL_FW_REG_ERR_STS_SHIFT)
#define BOOT_LD_FAIL_FW1_REG_ERR_STS_EN_SHIFT                           (20)
#define BOOT_LD_FAIL_FW1_REG_ERR_STS_EN                                 (0x1 << BOOT_LD_FAIL_FW1_REG_ERR_STS_EN_SHIFT)
#define BOOT_LD_FAIL_FW2_REG_ERR_STS_EN_SHIFT                           (21)
#define BOOT_LD_FAIL_FW2_REG_ERR_STS_EN                                 (0x1 << BOOT_LD_FAIL_FW2_REG_ERR_STS_EN_SHIFT)
#define BOOT_LD_FAIL_KC_REG_ERR_LD_CHK_EN_SHIFT                         (24)
#define BOOT_LD_FAIL_KC_REG_ERR_LD_CHK_EN                               (0x1 << BOOT_LD_FAIL_KC_REG_ERR_LD_CHK_EN_SHIFT)
#define BOOT_LD_FAIL_BL_REG_ERR_LD_CHK_EN_SHIFT                         (25)
#define BOOT_LD_FAIL_BL_REG_ERR_LD_CHK_EN                               (0x1 << BOOT_LD_FAIL_BL_REG_ERR_LD_CHK_EN_SHIFT)
#define BOOT_LD_FAIL_FW_REG_ERR_LD_CHK_EN_SHIFT                         (26)
#define BOOT_LD_FAIL_FW_REG_ERR_LD_CHK_EN                               (0x1 << BOOT_LD_FAIL_FW_REG_ERR_LD_CHK_EN_SHIFT)
#define BOOT_LD_KEY_CERTI_UPDATE_REG_BIND_BL_EN_SHIFT                   (28)
#define BOOT_LD_KEY_CERTI_UPDATE_REG_BIND_BL_EN                         (0x1 << BOOT_LD_KEY_CERTI_UPDATE_REG_BIND_BL_EN_SHIFT)
#define BOOT_LD_KEY_CERTI_UPDATE_REG_BIND_FW_EN_SHIFT                   (29)
#define BOOT_LD_KEY_CERTI_UPDATE_REG_BIND_FW_EN                         (0x1 << BOOT_LD_KEY_CERTI_UPDATE_REG_BIND_FW_EN_SHIFT)

#define BOOT_LOAD_FAIL_SET_STS_FOR_IMG(boot_ret, load_fail_img_type) \
        (((boot_ret & BOOT_LD_FAIL_FLOW_CHK_ERR_STS_MASK) << BOOT_LD_FAIL_FLOW_CHK_ERR_STS_SHIFT) | \
        (load_fail_img_type << BOOT_LD_FAIL_IMG_TYPE_ERR_STS_SHIFT))

// Byte
#define EACH_IV_DATA_SIZE           (4)

#define AES_GCM_IV_DATA_SIZE        (12)
#define AES_BLOCK_SIZE              (16)

#define AES_GCM_TAG_SIZE_RATIO      (CACHE_LINE_SIZE_32_BYTE / AES_GCM_TAG_SIZE_4_BYTE)

#define BOOT_DEVICE_NOR_FLSH_START_ADDR     (uint32_t)(0x08000000)
#define BOOT_DEVICE_NOR_FLSH_LIMIT_ADDR     (uint32_t)(0x10000000)
#define RAM_FUN_TABLE_VALID_ITCM_START_ADDR    (0x00010000)
#define RAM_FUN_TABLE_VALID_ITCM_END_ADDR      (0x00030000)
#define RAM_FUN_TABLE_VALID_DTCM_START_ADDR    (0x20000000)
#define RAM_FUN_TABLE_VALID_DTCM_END_ADDR      (0x20004000)
#define RAM_FUN_TABLE_VALID_START_ADDR         (0x20100000)
#define RAM_FUN_TABLE_VALID_END_ADDR           (0x20180000)

// NOR FLASH REGION CHECK
#define CHK_BOOT_DEVICE_NOR_FLSH_REGION_VALID(flash_addr, p_valid) \
    do { \
        if ((flash_addr >= BOOT_DEVICE_NOR_FLSH_START_ADDR) && (flash_addr < BOOT_DEVICE_NOR_FLSH_LIMIT_ADDR)) { \
            *(uint8_t *)(p_valid) = ENABLE; \
        } else { \
            *(uint8_t *)(p_valid) = DISABLE; \
        } \
    } while(0)

// BOOT LOAD DESTINATION REGION CHECK
#define CHK_BOOT_LOAD_DEST_REGION_VALID(base_addr, end_addr, dest_addr, load_size, p_valid) \
    do { \
        if (((dest_addr >= base_addr) && (dest_addr < end_addr)) && \
            (((dest_addr+load_size) >= base_addr) && ((dest_addr+load_size) < end_addr))) { \
            *(uint8_t *)(p_valid) = ENABLE; \
        } else { \
            *(uint8_t *)(p_valid) = DISABLE; \
        } \
    } while(0)

#if defined(ROM_REGION)
// Boot ROM Device Safe Load
#define BOOT_ROM_SAFE_LOAD_DEVICE_TO_MEM(dst, src, size, max_size) \
    do { \
        if (size > max_size) { \
            _memcpy(dst, src, max_size); \
        } else { \
            _memcpy(dst, src, size); \
        } \
    } while(0)
#else
// Boot RAM Device Safe Load
#define BOOT_RAM_SAFE_LOAD_DEVICE_TO_MEM(dst, src, size, max_size) \
    do { \
        if (size > max_size) { \
            memcpy(dst, src, max_size); \
        } else { \
            memcpy(dst, src, size); \
        } \
    } while(0)
#endif

// IMG SELECT CORE FUNC
#define IMG_SELECT_LATEST_LOAD_CORE(img1_ver, img2_ver, img1_timst, img2_timst, img1_idx, img2_idx, img_ld_idx) \
    do { \
        if (img2_ver > img1_ver) { \
            img_ld_idx = img2_idx; \
        } else if (img2_ver < img1_ver) { \
            img_ld_idx = img1_idx; \
        } else { \
            if (img2_timst >= img1_timst) { \
                img_ld_idx = img2_idx; \
            } else { \
                img_ld_idx = img1_idx; \
            } \
        } \
    } while(0)

#define IMG_SELECT_OLDEST_LOAD_CORE(img1_ver, img2_ver, img1_timst, img2_timst, img1_idx, img2_idx, img_ld_idx) \
    do { \
        if (img2_ver > img1_ver) { \
            img_ld_idx = img1_idx; \
        } else if (img2_ver < img1_ver) { \
            img_ld_idx = img2_idx; \
        } else { \
            if (img2_timst >= img1_timst) { \
                img_ld_idx = img1_idx; \
            } else { \
                img_ld_idx = img2_idx; \
            } \
        } \
    } while(0)

enum {
	CACHE_LINE_SIZE_16_BYTE  = FLASH_SEC_CACHE_16,
	CACHE_LINE_SIZE_32_BYTE  = FLASH_SEC_CACHE_32,
	CACHE_LINE_SIZE_64_BYTE  = FLASH_SEC_CACHE_64,
	CACHE_LINE_SIZE_128_BYTE = FLASH_SEC_CACHE_128

};

enum {
	AES_GCM_TAG_SIZE_4_BYTE = FLASH_SEC_TAG_4,
	AES_GCM_TAG_SIZE_8_BYTE = FLASH_SEC_TAG_8,
	AES_GCM_TAG_SIZE_16_BYTE = FLASH_SEC_TAG_16
};

enum {
	CIPHER_AES_KEY_256_BITS = FLASH_SEC_KEY_256
};

// enum only for arg input
enum {
	CIPHER_AES_256_CTR      = 0,
	CIPHER_AES_256_GCM      = 1,
	CIPHER_AES_256_ECB_MIX  = 2,
};

typedef struct Flash_SEC_IV_Data_s {
	uint8_t iv_high[EACH_IV_DATA_SIZE];
	uint8_t iv_low[EACH_IV_DATA_SIZE];
	uint8_t iv_flash_addr[EACH_IV_DATA_SIZE];
	uint8_t iv_f_addr_cnt[EACH_IV_DATA_SIZE];

} Flash_SEC_IV_Data_t;


typedef struct Flash_SEC_IV_s {
	uint32_t iv_size;
	Flash_SEC_IV_Data_t iv_data __attribute__((aligned(32)));
} Flash_SEC_IV_t;

typedef struct Flash_SEC_KEY_Data_s {
	uint8_t ex_key[32];
	uint8_t ex_mix_ecb_key[32];

} Flash_SEC_KEY_Data_t;

typedef struct Flash_SEC_KEY_s {
	uint8_t key_idx;
	uint8_t resv[3];
	uint32_t key_size;
	Flash_SEC_KEY_Data_t key_data __attribute__((aligned(32)));

} Flash_SEC_KEY_t;

typedef struct Flash_SEC_CTRL_s {
	uint8_t sec_cipher_mode;
	uint8_t cache_line_size;

} Flash_SEC_CTRL_t;

typedef struct Flash_SEC_CRYPTO_DEC_INFO_s {
	uint32_t flash_addr;
	uint32_t key_size;
	uint8_t cache_line_size;
	uint8_t sk_idx;
} Flash_SEC_CRYPTO_DEC_INFO_t;


/*
   IMG TLV Format define
*/
#define IMG_VRF_PBK_MAX_SIZE                        (384)
#define IMG_VRF_SIGNDATA_MAX_SIZE                   (384)
#define IMG_HASH_CHK_DIGEST_MAX_SIZE                (64)
// 4K bytes-aligned offset from Manifest start to IMG HDR start
// FIXME use IMG_HDR_START_ALIGN_SIZE
#define IMG_HDR_START_OFFSET                        (((sizeof(img_manifest_t) >> IMG_HDR_START_ALIGN_SHIFT) + 1) << IMG_HDR_START_ALIGN_SHIFT)
#define IMG_HDR_START_ALIGN_SHIFT                   (12)
#define IMG_HDR_START_ALIGN_SIZE                    (0x1 << IMG_HDR_START_ALIGN_SHIFT)
#define IMG_HDR_START_ALIGN_MASK                    (IMG_HDR_START_ALIGN_SIZE - 0x1)
#define SB_PBK_HASH_SIZE                            (32)
#define SB_HUK_SIZE                                 (32)
#define SB_HKDF_KEY_SALT_SIZE                       (32)
#define SB_HKDF_KEY_NONCE_SIZE                      (32)
#define SB_HKDF_HMAC_SHA256_SIZE                    (32)
#define SB_CRYPTO_MAX_MSG_LENGTH                    (65536)
#define SB_SEC_KEY_SIZE                             (32)
#define SB_SEC_INIT_ADDR                            (0xFFFFFFFF)

#define MAX_CERTI_TBL_RECORD                        (2)
#define KEYCERTI_TBL_HDR_RESV_SIZE                  (12)
#define KEYCERTI_TBL_RECRD_RESV_SIZE                (5)
#define KEYCERTI_HDR_SIZE                           (16)
#define KEYCERTI_ROTPKDATA_SIZE                     (IMG_VRF_PBK_MAX_SIZE)
#define KEYCERTI_SIGNDATA_SIZE                      (IMG_VRF_SIGNDATA_MAX_SIZE)
#define MAX_KEYCERTI_HSH_TBL_RECORD                 (12)
#define KEYCERTI_PKHASH_SIZE                        (32)
#define KEYCERTI_SJTAG_KEY_SALT_SIZE                (32)
#define KEYCERTI_SJTAG_KEY_NONCE_SIZE               (32)
#define SB_SJTAG_KEY_SIZE                           (32)

#define KEYCERTI_RESV1_SIZE                         (13)
#define KEYCERTI_RESV2_SIZE                         (12)
#define KEYCERTI_RESV3_SIZE                         (15)
#define KEYCERTI_HSH_TBL_RESV_SIZE                  (6)
#define KEYCERTI_TYPEID_SIZE                        (2)
#define KEYCERTI_VERSION_SIZE                       (2)
#define KEYCERTI_TIMST_SIZE                         (8)


#define MANIFEST_HDR_SIZE                           (32)
//#define MANIFEST_HDR_RESERV1_SIZE                   (4)
#define MANIFEST_HDR_RESERV2_SIZE                   (16)
#define MANIFEST_IEDATA_SIZE                        (704)
#define MANIFEST_SIGNDATA_SIZE                      (IMG_VRF_SIGNDATA_MAX_SIZE)
#define MANIFEST_TOTAL_SIZE                         (MANIFEST_HDR_SIZE+MANIFEST_IEDATA_SIZE+MANIFEST_SIGNDATA_SIZE)
#define MAX_SEC_ENC_RECORD                          (8)
#define MANIFEST_MAX_LABEL_SIZE                     (8)
#define MANIFEST_IE_TBL_MAX_NUM                     (88)
#define MANIFEST_IE_ID_MAX_NUM                      (22)
#define MANIFEST_IE_ALIGNED_SIZE                    (4)
#define MANIFEST_IE_RESERV_SIZE                     (32)
#define MANIFEST_UNIE_START_ALIGN_SHIFT             (11)
#define MANIFEST_UNIE_START_ALIGN_SIZE              (0x1 << MANIFEST_UNIE_START_ALIGN_SHIFT) // 2KB
#define MANIFEST_UNIE_AREA_SIZE                     (0x1 << MANIFEST_UNIE_START_ALIGN_SHIFT) // 2KB
#define MANIFEST_UNIE_CHK_SIZE                      (4)
#define MANIFEST_UNIE_RSVD_TYPEID                   (0xFF)
#define IMG_MANIFEST_IE_TYPEID_SIZE                 (2)
#define IMG_MANIFEST_IE_VERSION_SIZE                (32)
#define IMG_MANIFEST_IE_TIMEST_SIZE                 (8)
#define IMG_MANIFEST_LD_SEL_MAX_IE_CNT              (3)

#define PARTITION_TABLE_ID_MAX_NUM                  (12)
#define PARTITION_RECORD_MAX                        (12)
#define PARTITION_TBL_FST_SIZE                      (32)
#define PARTITION_TBL_RECORD_SIZE                   (32*PARTITION_RECORD_MAX)
#define PARTITION_TBL_USER_DATA_SIZE                (256)
#define PARTITION_TBL_FST_RESV1_SIZE                (8)
#define PARTITION_TBL_FST_RESV2_SIZE                (8)
#define PARTITION_TBL_RECORD_RESV1_SIZE             (5)
#define PARTITION_TBL_RECORD_RESV2_SIZE             (16)

#define FW_IMG_HDR_MAX_SIZE                         (256)

#define FW_JTAG_KEY_SIZE                            (32)
#define FW_HDR_RESV1_SIZE                           (4)
#define FW_HDR_RESV2_SIZE                           (3)
#define FW_HDR_RESV3_SIZE                           (4)
#define FW_HDR_RESV4_SIZE                           (4)
#define FW_HDR_RESV5_SIZE                           (4)
#define FW_HDR_RESV6_SIZE                           (16)
#define FW_HDR_RESV7_SIZE                           (16)
#define FW_HDR_NXTOFFSET_NULL                       (0xFFFFFFFF)
#define FW_LD_VALID_IMG_TYPE_ID_MAX_SIZE            (10)

#define SECT_HDR_RESV2_SIZE                         (4)
#define SECT_HDR_RESV3_SIZE                         (4)
#define SECT_HDR_RESV4_SIZE                         (4)
#define SECT_HDR_RESV5_SIZE                         (16)
#define SECT_HDR_RESV6_SIZE                         (16)
#define SECT_HDR_NXTOFFSET_NULL                     (0xFFFFFFFF)
#define SECT_HDR_LD_VRF_HASH_MAX_SIZE               (64)
#define SECT_LD_VALID_TYPE_ID_MAX_SIZE              (7)

#define MULTI_SENSOR_SET_INVALID_PTN1               (0xFFFFFFFF)
#define MULTI_SENSOR_SET_INVALID_PTN2               (0xFEFEFEFE)


//#define BL_SECT_SECLEN                              (50319)

enum {
	LD_IMF_FT_TLV    =   0x0,
	LD_IMF_FT_NTLV   =   0x1,
};

enum {
	IMG_SEL_LD       =   0x0,
	IMG_SEL_UPDATE   =   0x1,
};

enum {
	LD_SEL_IMG_FW           =   0x0,
	LD_SEL_IMG_BOOT         =   0x1,
	LD_SEL_IMG_KEYCERTI     =   0x2,
	LD_SEL_IMG_PTBL         =   0x3,
};

enum {
	OTA_UPDATE_IMG_FW       =   0x0,
	OTA_UPDATE_IMG_BOOT     =   0x1,
	OTA_UPDATE_IMG_KEYCERTI =   0x2,
};

enum {
	OTA_UPDATE_IMG_NO_SPECI_IDX =   0x0,
	OTA_UPDATE_IMG_SPECI_IDX1   =   0x1,
	OTA_UPDATE_IMG_SPECI_IDX2   =   0x2,
};

enum {
	IMG_LD_FAIL_KC      =   0xE1,
	IMG_LD_FAIL_PT      =   0xE2,
	IMG_LD_FAIL_BL      =   0xE3,
	IMG_LD_FAIL_FW      =   0xE4,
	IMG_LD_FAIL_ISP     =   0xE5
};

typedef enum {
	FW_PT_INI_VAL_ID       = 0xF8E0,
	FW_PT_KEY_CER_TBL_ID   = 0xF1C1,
	FW_PT_KEY_CER1_ID      = 0xE9C2,
	FW_PT_KEY_CER2_ID      = 0xE1C3,
	FW_PT_PT_ID            = 0xD9C4,
	FW_PT_BL_PRI_ID        = 0xD1C5,
	FW_PT_BL_SEC_ID        = 0xC9C6,
	FW_PT_FW1_ID           = 0xC1C7,
	FW_PT_FW2_ID           = 0xB9C8,
	FW_PT_ISP_IQ_ID        = 0x89CE,
	FW_PT_NN_MDL_ID        = 0x81CF,
	FW_PT_NAND_CTRL_ID     = 0x79D0,
	FW_PT_NAND_BBT_ID      = 0x71D1,
	FW_PT_FCS_PARA_ID      = 0x69D2,
	FW_PT_RESV_ID          = 0x01DF,
} PART_TYPE_ID_T;

typedef enum {
	IE_PK_ID        = 0x01,
	IE_VERSION_ID   = 0x02,
	IE_IMGSZ_ID     = 0x03,
	IE_TYPEID_ID    = 0x04,
	IE_ENCALG_ID    = 0x05,
	IE_ENCKN_ID     = 0x06,
	IE_ENCKS_ID     = 0x07,
	IE_ENCIV_ID     = 0x08,
	IE_HSHALG_ID    = 0x09,
	IE_HSHKN_ID     = 0x0A,
	IE_HSHKS_ID     = 0x0B,
	IE_HASH_ID      = 0x0C,
	IE_TIMST_ID     = 0x0D,
	IE_VID_ID       = 0x0E,
	IE_PID_ID       = 0x0F,
	IE_IMGLST_ID    = 0x10,
	IE_DEP_ID       = 0x11,
	IE_RMATKN_ID    = 0x12,
	IE_BATLV_ID     = 0x13,
	IE_ACPW_ID      = 0x14,
	IE_IERESV_ID    = 0x15,
	IE_NAN_ID       = 0xFF,
} IE_ID_T;

typedef enum {
	SENSOR_ID        = 0x01
} ISP_UNPT_IE_ID_T;


#define    IE_TLV_TYPE_ID_SIZE     (1)
#define    IE_TLV_SIZE_SIZE        (3)
#define    IE_TLV_TL_TOTAL_SIZE    (4)

#define    ISP_UNPT_IE_SENSOR_ID_MAX_SIZE           (1)

enum {
	IE_DATA_PADDING_ONEBYTE =   0x1,
	IE_DATA_PADDING_TWOBYTE =   0x2,
	IE_DATA_PADDING_THRBYTE =   0x3,
};

enum {
	IMG_PARSE_BL =   0x1,
	IMG_PARSE_FW =   0x2
};

enum {
	IMG_LOAD_BL     =   0x1,
	IMG_LOAD_FW     =   0x2,
	IMG_LOAD_ISP_IQ =   0x3
};

enum {
	INFO_INVALID =   0x0,
	INFO_VALID   =   0x1
};

enum {
	IMG_SIGN_VRF_ALG_NONE          =   0x0,
	IMG_SIGN_VRF_ALG_HMAC_SHA256   =   0x1,
	IMG_SIGN_VRF_ALG_EDDSA_ED25519 =   0x2,
	IMG_SIGN_VRF_ALG_ECDSA256      =   0x3,
	IMG_SIGN_VRF_ALG_RSA2048       =   0x4,
	IMG_SIGN_VRF_ALG_RSA3072       =   0x5,
};

enum {
	IMG_HSH_CHK_ALG_NONE           =   0x0,
	IMG_HSH_CHK_ALG_SHA256         =   0x1,
	IMG_HSH_CHK_ALG_HMAC_SHA256    =   0x2
};

enum {
	IMG_SEC_ENC_ALG_NONE           =   0xFF,
	IMG_SEC_ENC_ALG_AES256_GCM     =   0x1,
	IMG_SEC_ENC_ALG_AES256_CTR     =   0x2,
	IMG_SEC_ENC_ALG_AES256_ECB_MIX =   0x3,
};

enum {
	MANIFEST_HSH_QUICK_CHK_INVALID_PTN0 = 0x0,
	MANIFEST_HSH_QUICK_CHK_INVALID_PTN1 = 0xFF0,
};

enum {
	KEY_CERTI_SJTAG_NFIX_QUICK_CHK_INVALID_PTN0 = 0x0,
	KEY_CERTI_SJTAG_NFIX_QUICK_CHK_INVALID_PTN1 = 0xFF0,
};

typedef enum {
	FW_IMG_INI_VAL_ID       = 0xF8E0,
	FW_IMG_KEY_CER_ID       = 0xF2A1,
	FW_IMG_PT_ID            = 0xEAA2,
	FW_IMG_BL_ID            = 0xE2A3,
	FW_IMG_FWHS_S_ID        = 0xDAA4,
	FW_IMG_FWHS_NS_ID       = 0xD2A5,
	FW_IMG_ISP_ID           = 0xCAA6,
	FW_IMG_VOE_ID           = 0xC2A7,
	FW_IMG_WLAN_ID          = 0xBAA8,
	FW_IMG_XIP_ID           = 0xB2A9,
	FW_IMG_CPFW_ID          = 0xAAAA,
	FW_IMG_WOWLN_ID         = 0xA2AB,
	FW_IMG_CINIT_ID         = 0x9AAC,
	FW_IMG_FWUPD_ID         = 0x92AD,
	FW_IMG_RESV_ID          = 0x02BF,
	FW_IMG_NOTSET_ID        = 0xFFFF,

} FW_IMG_TYPE_ID_T;

typedef enum {
	FW_SIMG_INI_VAL_ID      = 0xF8E0,
	FW_SIMG_DTCM_ID         = 0xF381,
	FW_SIMG_ITCM_ID         = 0xEB82,
	FW_SIMG_SRAM_ID         = 0xE383,
	FW_SIMG_PSRAM_ID        = 0xDB84,
	FW_SIMG_LPDDR_ID        = 0xD385,
	FW_SIMG_DDR_ID          = 0xCB86,
	FW_SIMG_XIP_ID          = 0xC387,
	FW_SIMG_RESV_ID         = 0x039F,

} FW_SECT_TYPE_ID_T;

typedef struct certi_tbl_record_s {
	uint32_t start_addr;
	uint32_t length;
	uint16_t type_id;
	uint8_t  resv[5];
	uint8_t  valid;
} certi_tbl_record_t, *pcerti_tbl_record_t;

typedef struct certi_tbl_s {
	uint8_t certi1_idx;
	uint8_t certi2_idx;
	uint8_t resv[2];
	certi_tbl_record_t  key_cer_tbl_rec[MAX_CERTI_TBL_RECORD];
} certi_tbl_t, *pcerti_tbl_t;

typedef struct img_keycerti_tbl_s {
	uint16_t type_id;
	uint16_t vrf_al;
	uint8_t  resv[12];
	certi_tbl_record_t  key_cer_tbl_rec[MAX_CERTI_TBL_RECORD];
} img_keycerti_tbl_t, *pimg_keycerti_tbl_t;

typedef struct key_certi_rotpk_s {
	uint8_t data[KEYCERTI_ROTPKDATA_SIZE];
} key_certi_rotpk_t, *pkey_certi_rotpk_t;

typedef struct key_certi_hsh_tbl_s {
	uint16_t type_id;
	uint8_t  resv[6];
} key_certi_hsh_tbl_t, *pkey_certi_hsh_tbl_t;

typedef struct key_certi_pkhsh_s {
	uint8_t data[KEYCERTI_PKHASH_SIZE];
} key_certi_pkhsh_t, *pkey_certi_pkhsh_t;

typedef struct key_certi_sign_s {
	uint8_t data[KEYCERTI_SIGNDATA_SIZE];
} key_certi_sign_t, *pkey_certi_sign_t;

typedef struct s_jtag_sec_nonfixed_key_s {
	uint8_t kn[KEYCERTI_SJTAG_KEY_NONCE_SIZE];
	uint8_t ks[KEYCERTI_SJTAG_KEY_SALT_SIZE];
} s_jtag_sec_nonfixed_key_t, *ps_jtag_sec_nonfixed_key_t;

typedef struct s_jtag_nsec_nonfixed_key_s {
	uint8_t kn[KEYCERTI_SJTAG_KEY_NONCE_SIZE];
	uint8_t ks[KEYCERTI_SJTAG_KEY_SALT_SIZE];
} s_jtag_nsec_nonfixed_key_t, *ps_jtag_nsec_nonfixed_key_t;

typedef struct img_keycerti_s {
	uint8_t  rotpk_hsh_idx;
	uint8_t  huk_idx;
	uint8_t  sec_key_idx;
	uint8_t  resv1[13];
	key_certi_rotpk_t   rotpk;
	uint16_t type_id;
	uint16_t key_version;
	uint8_t  timest[8];
	uint32_t imgsz;
	uint32_t s_jtag_ctrl;
	uint8_t  resv2[12];
	s_jtag_sec_nonfixed_key_t jtag_s_nonfixed_key_info;
	s_jtag_nsec_nonfixed_key_t jtag_ns_nonfixed_key_info;
	uint8_t  key_hash_rec_num;
	uint8_t  resv3[15];
	key_certi_hsh_tbl_t key_hsh_tbl[MAX_KEYCERTI_HSH_TBL_RECORD];
	key_certi_pkhsh_t   key_pkhsh[MAX_KEYCERTI_HSH_TBL_RECORD];
	key_certi_sign_t    signature;
} img_keycerti_t, *pimg_keycerti_t;

typedef struct ie_tlv_const_tbl_s {
	IE_ID_T   ie_id;
	char      *ie_name;
	uint32_t  max_size;
} ie_tlv_const_tbl_t, *pie_tlv_const_tbl_t;

typedef struct part_type_id_tbl_s {
	PART_TYPE_ID_T   id;
	char             *name;
} part_type_id_tbl_t, *ppart_type_id_tbl_t;


typedef struct manif_ie_tlv_s {
	uint8_t  id;
	uint8_t  resv[3];
	uint32_t size;
	uint8_t *p_val;
} manif_ie_tlv_t, *pmanif_ie_tlv_t;

typedef struct manif_ie_tlv_tbl_s {
	manif_ie_tlv_t tbl_info[MANIFEST_IE_TBL_MAX_NUM];
} manif_ie_tlv_tbl_t, *pmanif_ie_tlv_tbl_t;

typedef struct manif_hdr_s {
	uint8_t  lbl[MANIFEST_MAX_LABEL_SIZE];
	uint16_t size;
	uint16_t vrf_al;
	uint32_t enc_rmp_base_addr;
	uint8_t resv2[MANIFEST_HDR_RESERV2_SIZE];
} manif_hdr_t, *pmanif_hdr_t;

typedef struct manif_sec_enc_record_s {
	uint8_t enc_en;
	uint8_t encalg_sel;
	uint8_t add_ref;
	uint8_t xip_en;

	uint8_t resv2[4];
	uint8_t tag_size_sel;
	uint8_t resv3[3];
	uint32_t tag_base_addr;
	uint32_t iv_ptn_low;
	uint32_t iv_ptn_high;
	uint32_t base_addr;
	uint32_t end_addr;
} manif_sec_enc_record_t, *pmanif_sec_enc_record_t;

typedef struct manif_ie_data_s {
	uint8_t data[MANIFEST_IEDATA_SIZE];
} manif_ie_data_t, *pmanif_ie_data_t;

typedef struct manif_sign_s {
	uint8_t data[MANIFEST_SIGNDATA_SIZE];
} manif_sign_t, *pmanif_sign_t;

typedef struct img_manifest_s {
	manif_hdr_t             hdr;
	manif_sec_enc_record_t  sec_enc_record[MAX_SEC_ENC_RECORD];
	manif_ie_data_t         ie_data;
	manif_sign_t            signature;
} img_manifest_t, *pimg_manifest_t;

typedef struct img_manifest_ld_sel_s {
	uint16_t type_id;
	uint8_t  version[IMG_MANIFEST_IE_VERSION_SIZE];
	uint8_t  timest[IMG_MANIFEST_IE_TIMEST_SIZE];
} img_manifest_ld_sel_t, *pimg_manifest_ld_sel_t;

typedef struct gpio_pwr_on_trap_pin_s {
	uint16_t pin: 5;            /*!< bit: 4...0 the GPIO pin number */
	uint16_t port: 3;           /*!< bit: 7...6 the  GPIO port number */
	uint16_t io_lev: 1;         /*!< bit:  8 the IO level to trigger the trap */
	uint16_t reserved: 6;       /*!< bit: 14...9 reserved */
	uint16_t valid: 1;          /*!< bit:  15 is this trap valid */
} gpio_pwr_on_trap_pin_t;

typedef struct part_fst_info_s {
	uint8_t rec_num;
	uint8_t bl_p_idx;
	uint8_t bl_s_idx;
	uint8_t fw1_idx;
	uint8_t fw2_idx;
	uint8_t iq_idx;
	uint8_t nn_m_idx;
	uint8_t mp_idx;
	uint8_t keycert1_idx;   // For NAND Flash boot
	uint8_t keycert2_idx;   // For NAND Flash boot
	uint8_t fcs_para_idx;
	uint8_t resv1[5];

	gpio_pwr_on_trap_pin_t ota_trap;
	gpio_pwr_on_trap_pin_t mp_trap;
	uint32_t udl;
	uint8_t resv2[8];
} part_fst_info_t, *ppart_fst_info_t;

typedef struct part_record_t_s {
	uint32_t start_addr;        /*!< The start address of the image partition, it should be 4K-bytes aligned */
	uint32_t length;            /*!< The size of the image partition, it should be times of 4K-bytes */
	uint16_t type_id;           /*!< The image type of the partition */
	uint8_t  resv1[5];          /*!< reserved */
	uint8_t  valid;
	uint8_t  resv2[16];         /*!< reserved */
} part_record_t, *ppart_record_t;

typedef struct partition_tbl_s {
	part_fst_info_t     fst;
	part_record_t       partition_record[PARTITION_RECORD_MAX];
} partition_tbl_t, *ppartition_tbl_t;

typedef struct part_user_data_s {
	uint8_t data[PARTITION_TBL_USER_DATA_SIZE];
} part_user_data_t, *ppart_user_data_t;

typedef struct partition_tbl_user_s {
	partition_tbl_t     tbl_info;
	part_user_data_t    user_data;
} partition_tbl_user_t, *ppartition_tbl_user_t;

typedef struct img_partition_tbl_s {
	img_manifest_t      manifest;
	partition_tbl_t     tbl_info;
	part_user_data_t    user_data;
} img_partition_tbl_t, *pimg_partition_tbl_t;

typedef struct fw_img_jtag_key_s {
	uint8_t s_jtag_s_key[FW_JTAG_KEY_SIZE];
	uint8_t s_jtag_ns_key[FW_JTAG_KEY_SIZE];
} fw_img_jtag_key_t, *pfw_img_jtag_key_t;

typedef struct fw_img_hdr_s {
	uint32_t imglen;
	uint32_t nxtoffset;
	uint16_t type_id;
	uint16_t nxt_type_id;
	uint8_t  s_jtag_ctrl;
	uint8_t  resv2[3];
	uint8_t  resv3[4];
	uint8_t  resv4[4];
	uint32_t str_tbl;
	uint8_t  resv5[4];
	fw_img_jtag_key_t   jtag_key;
	uint8_t  resv6[16];
	uint8_t  resv7[16];
} fw_img_hdr_t, *pfw_img_hdr_t;

typedef struct img_fw_img_s {
	img_manifest_t      manifest;
	fw_img_hdr_t        fw_img_hdr;
} img_fw_img_t, *pfw_img_t;

typedef struct sec_ctrl_s {
	uint32_t ctrl_val;
} sec_ctrl_t, *psec_ctrl_t;

typedef struct ld_vrf_hash_s {
	uint8_t data[SECT_HDR_LD_VRF_HASH_MAX_SIZE];
} ld_vrf_hash_t, *pld_vrf_hash_t;

typedef struct sect_hdr_s {
	uint32_t    seclen;
	uint32_t    nxtoffset;
	uint16_t    type_id;
	uint16_t    resv1;
	sec_ctrl_t  sec_ctrl;
	uint8_t     resv2[4];
	uint32_t    dest;
	uint8_t     resv3[4];
	uint8_t     resv4[4];
	ld_vrf_hash_t  ld_vrf_hash;
	uint8_t     resv5[16];
	uint8_t     resv6[16];
} sect_hdr_t, *psect_hdr_t;

typedef struct img_pkhsh_info_s {
	key_certi_hsh_tbl_t key_hsh_tbl;
	key_certi_pkhsh_t   key_pkhsh;
} img_pkhsh_info_t, *pimg_pkhsh_info_t;

typedef struct sec_boot_keycerti_s {
	uint8_t  rotpk_hsh_idx;
	uint8_t  huk_idx;
	uint8_t  sec_key_idx;
	uint8_t  resv1[13];
	uint8_t  rotpk_hsh_data[SB_PBK_HASH_SIZE];
	uint32_t s_jtag_ctrl;
	uint8_t  resv2[12];
	s_jtag_sec_nonfixed_key_t jtag_s_nonfixed_key_info;
	s_jtag_nsec_nonfixed_key_t jtag_ns_nonfixed_key_info;
	uint8_t  key_hash_rec_num;
	uint8_t  resv3[15];
	img_pkhsh_info_t img_pkhsh_info[MAX_KEYCERTI_HSH_TBL_RECORD];
} sec_boot_keycerti_t, *psec_boot_keycerti_t;

typedef struct tb_img_sign_vrf_info_s {
	uint8_t vrf_alg;
	uint8_t resv1[3];

	uint8_t *p_pbk;
	uint8_t *p_sign;
	uint8_t *p_msg;
	uint32_t msglen;
	uint32_t resv2[3];
} tb_img_sign_vrf_info_t, *ptb_img_sign_vrf_info_t;

typedef struct tb_img_hash_chk_info_s {
	uint8_t hash_alg;
	uint8_t resv1[3];

	uint8_t *p_key_huk;
	uint8_t *p_key_salt;
	uint8_t *p_key_nonce;
	uint8_t *p_msg;
	uint8_t *p_digest;
	uint32_t msglen;
	uint32_t resv2;
} tb_img_hash_chk_info_t, *ptb_img_hash_chk_info_t;

typedef struct sb_sec_enc_info_s {
	uint32_t enc_rmp_base_addr;
	uint8_t *p_msg;
	uint8_t enc_sts;
	uint8_t resv[3];
	//uint32_t msglen;
	manif_sec_enc_record_t sec_enc_record[MAX_SEC_ENC_RECORD];
} sb_sec_enc_info_t, *psb_sec_enc_info_t;

typedef struct sb_crypto_enc_info_s {
	uint8_t encalg_sel;
	uint8_t sk_idx;
	uint8_t resv1[2];
	uint8_t *p_ivptn;
	uint8_t *p_key;
	uint32_t key_len;
	uint32_t iv_len;
	uint32_t base_offset;
	uint32_t dec_base;
	uint32_t dec_size;
	uint32_t tag_base;
} sb_crypto_enc_info_t, *psb_crypto_enc_info_t;

/**
  \brief  The data structure for a SEC remap configuration of a XIP memory block.
*/
typedef struct hal_sec_rmp_region_cfg_s {
	uint8_t is_used;
	uint8_t resv[3];
	uint32_t phy_addr;      // The image physical address (flash image offset)
	uint32_t remap_addr;    // The re-mapping address (image virtual address)
	uint32_t remap_size;    // re-mapping size
} hal_sec_rmp_region_cfg_t, *phal_sec_rmp_region_cfg_t;

/**
  \brief  The data structure for a SEC decrypt configuration of a XIP memory block.
*/
typedef struct hal_sec_dec_region_cfg_s {
	uint8_t is_used;
	uint8_t cipher_sel;
	uint8_t resv[2];
	uint32_t iv_ptn_low;
	uint32_t iv_ptn_high;
	uint32_t dec_base;      // The image decrypt address (flash address)
	uint32_t dec_size;      // decrypt size
	uint32_t tag_base_addr; // aes-gcm flash tag_base_addr
	uint32_t tag_flh_addr;  // aes-gcm flash tag located addr
	uint32_t hdr_total_size;// IMG header total size
} hal_sec_dec_region_cfg_t, *phal_sec_dec_region_cfg_t;

#define MAX_PENDING_SEC_RMP_REGION_CFG          (4)
#define MAX_PENDING_SEC_DEC_REGION_CFG          (8)
#define IMG_REGION_LOOKUP_TBL_MAX_SIZE          (10)
#define RGN_IDX_INITVAL                         (0xFF)

typedef struct img_region_lookup_s {
	uint8_t  is_xip;
	uint8_t  rng_idx;
} img_region_lookup_t, *pimg_region_lookup_t;

typedef struct hal_sec_region_cfg_f_s {
	hal_status_t (*enable_remap_region)(uint8_t rmp_region_sel,
										uint32_t va_base, uint32_t pa_base, uint32_t region_size);
	hal_status_t (*disable_rmp_region)(uint8_t rmp_region_sel);
	hal_status_t (*default_decrypt_init)(const uint8_t key_sel);
	hal_status_t (*decrypt_region_init)(const uint32_t iv_low_ptn, const uint32_t iv_high_ptn, uint8_t dec_region_sel);
	hal_status_t (*decrypt_region_enable)(const uint8_t cipher_sel,
										  uint32_t dec_base, uint32_t dec_size, uint32_t tag_base);
	hal_status_t (*disable_dec_region)(uint8_t dec_region_sel);
	void (*aes_disable)(void);
	uint32_t (*set_word_from_byte_bigen)(const unsigned char *s_value);
	hal_status_t (*default_calculate_tag_base)(uint32_t flash_addr, uint32_t region_size,
			uint32_t tag_region_addr, uint32_t *tag_base,
			uint32_t *tag_region_size);
	uint32_t resv[3];
} hal_sec_region_cfg_f_t, *phal_sec_region_cfg_f_t;

/**
  \brief  The data structure for pending SEC configuration job.
*/
typedef struct hal_sec_region_cfg_s {
	uint8_t key_set;
	uint8_t key_id;
	uint8_t rmp_not_set_sts;
	uint8_t dec_not_set_sts;

	uint8_t rmp_cfg_cnt;    // the configured memory block count
	uint8_t dec_cfg_cnt;    // the configured memory block count
	uint8_t rmp_sts;
	uint8_t dec_sts;

	hal_sec_rmp_region_cfg_t sec_rmp_region_cfg[MAX_PENDING_SEC_RMP_REGION_CFG];
	hal_sec_dec_region_cfg_t sec_dec_region_cfg[MAX_PENDING_SEC_DEC_REGION_CFG];
	hal_sec_region_cfg_f_t sec_cfg_f;
} hal_sec_region_cfg_t, *phal_sec_region_cfg_t;

typedef struct sec_boot_info_s {
	uint32_t sb_level;
	sec_boot_keycerti_t *psb_keycerti;
	sb_sec_enc_info_t *pimg_sec_enc_info;
	hal_sec_region_cfg_t *psec_region_ctrl;
	tb_img_sign_vrf_info_t img_sign_vrf_info;
	tb_img_hash_chk_info_t img_hash_chk_info;
	sb_crypto_enc_info_t *pimg_crypto_enc_info;
	uint32_t resv[3];
} sec_boot_info_t, *psec_boot_info_t;

typedef enum {
	KEY_CERTI_INFO    = 0x1,
	PT_TBL_INFO       = 0x2,
	BL_INFO           = 0x3,
	FW_IMG_INFO       = 0x4,
	FW_ISP_INFO       = 0x5,
	FW_VOE_INFO       = 0x6,
	FW_ISP_IQ_INFO    = 0x7,

} IMG_INFO_T;

enum {
	IMG_IDX_UNKNOWN     =   0x0,
	IMG_IDX1            =   0x1,
	IMG_IDX2            =   0x2
};

enum {
	SB_HIGH_VAL_RTOPK_HSH       =   0x1,
	SB_HIGH_VAL_HUK             =   0x2,
	SB_HIGH_VAL_SEC_KEY         =   0x3,
	SB_HIGH_VAL_SJTAG_S_KEY     =   0x4,
	SB_HIGH_VAL_SJTAG_NS_KEY    =   0x5
};

enum {
	SB_HIGH_VAL_IDX1      =   0x1,
	SB_HIGH_VAL_IDX2      =   0x2,
	SB_HIGH_VAL_RMA_IDX   =   0x3
};

enum {
	ROTPK_IDX1      =   0x1,
	ROTPK_IDX2      =   0x2,
	ROTPK_RMA_IDX   =   0x3
};

enum {
	HUK_IDX1        =   0x1,
	HUK_IDX2        =   0x2,
	HUK_RMA_IDX     =   0x3
};

enum {
	SEC_KEY_IDX1    =   0x1,
	SEC_KEY_IDX2    =   0x2,
	SEC_KEY_RMA_IDX =   0x3
};

enum {
	RMA_INFO_ROTPK_HSH    =   0x0,
	RMA_INFO_HUK          =   0x1,
	RMA_INFO_SEC_KEY      =   0x2
};

enum {
	TOP_SEC_KEY1_LD_SEC_KEY_ALL  =   0x0,
	TOP_SEC_KEY2_LD_SEC_KEY_ALL  =   0x1,
	TOP_SEC_KEY_LD_SEC_KEY_MATCH =   0x2,
	TOP_SEC_KEY_LD_SEC_KEY_CROSS =   0x3
};

enum {
	FCS_LD_ISP_IQ_FAIL_MAIN_TYPE             = 0x1,
	FCS_LD_ISP_IQ_FAIL_SUB_TYPE              = 0x2
};

enum {
	FCS_LD_ISP_IQ_FAIL_INIT_VAL              = 0x0,
	FCS_LD_ISP_IQ_FAIL_MAIN_VRF_FAIL         = 0xC0,
	FCS_LD_ISP_IQ_FAIL_MAIN_TMR_INIT_FAIL    = 0xC1,
	FCS_LD_ISP_IQ_FAIL_MAIN_PROCESS_FAIL     = 0xC2,
	FCS_LD_ISP_IQ_FAIL_MAIN_NAND_CTRL_FAIL   = 0xC3,
};

typedef struct part_tbl_info_s {

#if 0
	// not sure members
	uint16_t mani_size;
	uint16_t vrf_al;
	manif_ie_tlv_t *ie_cache_tbl;
	uint8_t *ie_raw_data;
	manif_sign_t *manif_sign;
#endif
	partition_tbl_t *part_tbl_raw_data;

} part_tbl_info_t, *ppart_tbl_info_t;

typedef struct boot_load_img_cur_info_s {
	uint8_t sbl_cfg;
	uint8_t resv1[3];
	uint8_t *pIMG_data;
	uint32_t resv2[2];
} boot_load_img_cur_info_t, *pboot_load_img_cur_info_t;

typedef union {
	__IOM uint8_t byte;
	struct {
		__IOM uint8_t kc1_ld_fail_en       : 1;       /*!< [0..0] Key certificate1 load fail enable */
		__IOM uint8_t kc2_ld_fail_en       : 1;       /*!< [1..1] Key certificate2 load fail enable */
		__IOM uint8_t bl1_ld_fail_en       : 1;       /*!< [2..2] Boot loader1 load fail enable */
		__IOM uint8_t bl2_ld_fail_en       : 1;       /*!< [3..3] Boot loader2 load fail enable */
		__IOM uint8_t fw1_ld_fail_en       : 1;       /*!< [4..4] FW1 load fail enable */
		__IOM uint8_t fw2_ld_fail_en       : 1;       /*!< [5..5] FW2 load fail enable */
		__IM  uint8_t : 2;
	} bit;
} img_ld_fail_en_t, *pimg_ld_fail_en_t;

typedef union {
	__IOM uint8_t byte;
	struct {
		__IOM uint8_t kc_ld_fail_chk       : 1;       /*!< [0..0] Key certificate load fail check (1'b0: Enable/ 1'b1: disable) */
		__IOM uint8_t bl_ld_fail_chk       : 1;       /*!< [1..1] Boot loader load fail check (1'b0: Enable/ 1'b1: disable) */
		__IOM uint8_t fw_ld_fail_chk       : 1;       /*!< [2..2] FW load fail check (1'b0: Enable/ 1'b1: disable) */
		__IM  uint8_t : 1;
		__IOM uint8_t kc_ota_bind_bl       : 1;       /*!< [4..4] Key certificate ota bind with boot loader (1'b0: Enable/ 1'b1: disable) */
		__IOM uint8_t kc_ota_bind_fw       : 1;       /*!< [5..5] Key certificate ota bind with FW (1'b0: Enable/ 1'b1: disable) */
		__IM  uint8_t : 2;
	} bit;
} img_ld_misc_ctrl_t, *pimg_ld_misc_ctrl_t;

typedef union {
	__IOM uint16_t boot_load_fail_sts;

	struct {
		img_ld_fail_en_t   img_ld_fail;               /*!< [0..7] img load fail enable status */
		img_ld_misc_ctrl_t img_ld_misc_ctrl;          /*!< [8..15] img load misc control */
	} byte;
} boot_ld_reg_sts_t, *pboot_ld_reg_sts_t;

typedef struct fcs_ld_isp_iq_fail_s {
	int fail_main;
	int fail_sub;
} fcs_ld_isp_iq_fail_t, *pfcs_ld_isp_iq_fail_t;

typedef struct hal_flash_boot_tlv_stubs_s {
	void *ppartition_tbl;
	void *pkeycerti;
	uint8_t *fast_boot;
	void (*clear_export_partition_tbl_info)(void);
	void (*clear_export_sb_keycerti_info)(void);
	void (*erase_boot_loader)(uint32_t code_start, uint32_t code_size, uint32_t img2_entry);
	int32_t (*otu_fw_download)(hal_uart_adapter_t *potu_uart, uint32_t flash_sel, uint32_t flash_offset);
	int (*verify_manif_f)(const uint8_t *img_offset, const uint8_t info_type, sec_boot_info_t *p_sb_info);
	void (*load_img_hdr_f)(const uint8_t *img_offset, fw_img_hdr_t *img_hdr_buf, const uint8_t sel_img_load);
	uint8_t (*search_available_idx)(uint8_t *p_sts, const uint8_t cfg_max_size);
	int (*xip_pending_cfg_add_rmp)(hal_sec_region_cfg_t *psb_sec_cfg_pending, img_region_lookup_t *pimg_rmp_lkp_tbl,
								   uint32_t phy_addr, uint32_t remap_addr, uint32_t remap_sz);
	int (*xip_pending_process_rmp)(hal_sec_region_cfg_t *psb_sec_cfg_pending, sec_boot_info_t *p_sb_info);
	int (*xip_disable_rmp_config)(hal_sec_region_cfg_t *psb_sec_cfg_pending, uint8_t region_sel);

	int (*xip_pending_cfg_add_dec_key)(hal_sec_region_cfg_t *psb_sec_cfg_pending, const uint8_t key_id);
	int (*xip_pending_cfg_add_dec)(hal_sec_region_cfg_t *psb_sec_cfg_pending, img_region_lookup_t *pimg_dec_lkp_tbl,
								   uint8_t cipher_sel, uint32_t dec_base, uint32_t dec_sz,
								   uint32_t iv_ptn_low, uint32_t iv_ptn_high,
								   uint32_t tag_base_addr, uint32_t tag_flh_addr, uint32_t total_hdr_size);
	int (*xip_pending_process_dec)(hal_sec_region_cfg_t *psb_sec_cfg_pending, sec_boot_info_t *p_sb_info);
	int (*xip_disable_dec_config)(hal_sec_region_cfg_t *psb_sec_cfg_pending, uint8_t region_sel);
	int (*img_rmp_and_dec_lkp_tbl_insert)(img_region_lookup_t *plkp_tbl, uint8_t tbl_size, uint8_t is_xip, uint8_t *tbl_cnt);
	void (*img_rmp_and_dec_lkp_tbl_remove)(img_region_lookup_t *plkp_tbl, uint8_t *tbl_cnt);
	int (*img_get_ld_sel_info_from_ie)(const uint8_t img_obj, const uint8_t *ptr, img_manifest_ld_sel_t *pld_sel_info);
	uint32_t (*get_ld_version)(const uint8_t img_obj, uint8_t *p_img_version);
	uint32_t (*get_ld_timst)(uint8_t *p_img_timest);
	int (*img_get_ld_sel_idx)(const uint8_t img_obj, img_manifest_ld_sel_t *pld_sel_info1, img_manifest_ld_sel_t *pld_sel_info2, uint8_t img1_idx,
							  uint8_t img2_idx);
	int (*img_get_update_sel_idx)(const uint8_t img_obj, img_manifest_ld_sel_t *pld_sel_info1, img_manifest_ld_sel_t *pld_sel_info2, uint8_t img1_idx,
								  uint8_t img2_idx);
	int (*img_sel_op_idx)(void *p_tbl_info, const uint8_t img_obj, const uint8_t img_sel_op);
	void *penc_sec_info;
	void (*clear_export_enc_sec_info)(void);
	void (*flash_sec_crypto_gen_iv)(uint32_t flash_addr, uint32_t cahce_line_size, Flash_SEC_IV_Data_t *p_sec_iv, uint32_t iv_len);
	void (*flash_sec_crypto_xor_data)(unsigned char *buf1, unsigned char *buf2, uint32_t len, unsigned char *result);
	void (*set_fw_img_load_info)(void *p_set_fw_img_info);
	void *(*get_img_load_info)(const uint8_t img_obj);
	void (*set_fw_img_rollback_check_en_ctrl)(uint8_t en);
	void (*record_fw_ld_info)(const uint8_t img_obj, void *pimg_info_export, void *img1_addr, void *img2_addr, img_manifest_ld_sel_t *pld_sel_info);
	void *pisp_iq_ld_sts;
	uint32_t reserved[6];  // reserved space for next ROM code version function table extending.
} hal_flash_boot_tlv_stubs_t;

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _FW_IMG_TLV_H_"
