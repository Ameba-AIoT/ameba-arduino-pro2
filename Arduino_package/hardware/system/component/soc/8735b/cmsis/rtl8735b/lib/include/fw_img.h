/**************************************************************************//**
 * @file     fw_img.h
 * @brief    Define the FW image format.
 * @version  V1.00
 * @date     2021-06-06
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#ifndef _FW_IMG_H_
#define _FW_IMG_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#define PRIV_KEY_SIZE               32
#define AES_KEY_SIZE                32
#define HASH_KEY_SIZE               32
#define PUBLIC_KEY_SIZE             32
#define AES_IV_LEN                  16
#define HASH_RESULT_SIZE            32

#define FW_PART_MAGIC_NUM           (0x55AA55AA)
#define FW_PART_REC_SIGN            (0x5A)
#define MAX_PARTITION_RECORD        (8)

#define PARTITION_TBL_ENC_SIZE      (1024*4)
#define BOOT_IMG_ENC_BLK_SIZE       (1024*16)
//#define BOOT_IMG_ENC_BLK_SIZE       (1024*256)

#define LS_IMG_DMA_BLK_SIZE         (32*127)
#define UART_BOOT_LS_IMG_DMA_BLK_SIZE   (1024+32)

// Hash length cannot over 16K ?
#define BOOT_IMG_HASH_BLK_SIZE      (1024*16)

#define FW_IMG_HASH_BLK_SIZE        (1024*16)
#define FW_IMG_ENC_BLK_SIZE         (1024*16)

#define PARTITION_TBL_USER_DATA_SIZE       (256)

#define FLASH_CAL_PATTER_SIZE       32
#define OTA_SIGNATURE_SIZE          32
#define MAX_PUBLIC_KEY_NUM          (6)

#define IMG_LINK_LIST_END           (0xFFFFFFFF)
#define XIP_REMAP_UP_LIMIT          (0x9C000000)

#define HEADER_SIGN_SIZE            (4)

/* define the Image partition type in the Partition Record */
enum FW_PartitionType_e {
	FW_PT_PT                = 0,    // Partition Table
	FW_PT_Boot              = 1,    // FW image for Boot or Initial
	FW_PT_SysData           = 2,    // System Data
	FW_PT_Cal               = 3,    // Calibration Data
	FW_PT_User              = 4,    // User defined partition type
	FW_PT_FW1               = 5,    // FW1 Image
	FW_PT_FW2               = 6,    // FW2 Image
	FW_PT_VAR               = 7,    // VAR defined partition type
	FW_PT_MP                = 8,    // FW image for MP
	FW_PT_RDP               = 9,    // FW image for RDP

	FW_PT_Reserv            = 10    // Reserved type
};

/* define the FW Image type in the Image Header */
enum FW_PImageType_e {
	FW_IMG_PT              = 0x00, // FW image for Partition Table
	FW_IMG_BOOT            = 0x01, // FW image for Boot Image
	FW_IMG_FWHS_S          = 0x02, // FW image for HS Secure Image
	FW_IMG_FWHS_NS         = 0x03, // FW image for HS Non-Secure Image
//    FW_IMG_FWLS            = 0x04, // FW image for LS Image
//    FW_IMG_ISP             = 0x05, // FW image for Image processor
	FW_IMG_VOE             = 0x06, // FW image for Video Offload Engine
	FW_IMG_WLAN            = 0x07, // FW image for WLan processor
	FW_IMG_XIP             = 0x08, // FW image for execution on Flash
	FW_IMG_CPFW            = 0x09, // CoProcessor FW image

	FW_IMG_RESV            = 0x3F  // FW image reservation
};

/* define the FW Image type in the Section Header */
enum FW_SImageType_e {
	FW_SIMG_DTCM            = 0x80, // FW image for DTCM
	FW_SIMG_ITCM            = 0x81, // FW image for ITCM
	FW_SIMG_SRAM            = 0x82, // FW image for SRAM
	FW_SIMG_PSRAM           = 0x83, // FW image for External PSRAM
	FW_SIMG_LPDDR           = 0x84, // FW image for External LPDDR RAM
	FW_SIMG_XIP             = 0x85  // FW image for XIP
};

/* define the Image1 AES key export option */
enum FW_KeyExportOption_e {
	KEY_EXPORT_LATEST       = 0x01, // Export the AES key for the latest FW
	KEY_EXPORT_BOTH         = 0x02  // Export the AES key for both FW1 & FW2
};

/* define the hash algorithm option */
enum FW_HashAlgorithm_e {
	HASH_MD5                = 0x00,
	HASH_SHA256             = 0x01
};

/* define the encryption algorithm option */
enum FW_EncryptAlgorithm_e {
	ENC_AES_ECB             = 0x00,
	ENC_AES_CBC             = 0x01
};

/* define the encryption algorithm option */
enum user_key_id_e {
	S_JTAG_KEY              = 0,
	NS_JTAG_KEY             = 1
};

typedef struct image_load_log_s {
	uint32_t img_sz;    // image size
	uint32_t start_addr;    // the image start address (destination address to load the image)
} image_load_log_t, *pimage_load_log_t;

typedef struct public_key_type_s {
	uint8_t key[PUBLIC_KEY_SIZE];
} public_key_type_t, *ppublic_key_type_t;

typedef struct aes_key_type_s {
	uint8_t key[AES_KEY_SIZE];
} aes_key_type_t, *paes_key_type_t;

// the structure type for Curve25519 key generate log
typedef struct share_key_gen_log_s {
	uint8_t pub_key[AES_KEY_SIZE];      // Public key input
	uint8_t share_key[AES_KEY_SIZE];    // the generated share key output
} share_key_gen_log_t, *pshare_key_gen_log_t;

typedef union {
	uint8_t w;                    /*!< byte fields for user_key_val_t */

	struct {
		uint8_t key1_valid: 1;      /*!< bit: 0 user key1 valid */
		uint8_t key2_valid: 1;      /*!< bit: 1 user key2 valid */
	} b;                                        /*!< bit fields for user_key_val_t */
} user_key_val_t, *puser_key_val_t;

typedef struct fm_image_header_s {
	uint32_t image_len;             // Offset 0x00: the length of this image, not inclues this image header
	uint32_t nxt_img_offset;        /* Offset 0x04: the offset to next image header (header to header), 0xFFFFFFFF for no next image
                                       For next partition, this offset should aligned to 4096, for next FW image
                                       this offset should aligned to 1024 */
	uint8_t img_type;               // Offset 0x08: The image type: partition type or secure image type
	union {
		uint8_t enc_ctrl;           // Offset 0x09: FST/image is encrypted(1) or is plain text(0), ignored when eFuse Secure Lock = 1, for image header
		uint8_t sce_en;             // Offset 0x09: enable the ERAM image encryption by the SCE, for section header
	};

	union {
		uint8_t key_idx;            // Offset 0x0a : the key index for the image decryption
		uint8_t xip_pg_sz;          // Offset 0x0a : the XIP page size selection: 0/1/2: 16K/32K/64K
	};

	union {
		uint8_t xip_bk_sz;          // Offset 0x0b : the XIP block size selection: 0/1/2/3: 32B/64B/128B/256B
		user_key_val_t user_key_val;  // Offset 0x0b : the user key valid, user key data is in offset 0x20 ~ 0x5F
	};

	uint8_t reserved1[4];           // Offset 0x0c : reserved
	union {
		uint8_t validation_patt[8];   // Offset 0x10: the validation pattern of this image, it must match with the signature in the FST, for section header
		struct {                    // offset 0x10: for image header
			char sign[4];           // Offset 0x10: the pre-fixed signature, "RTK#"
			uint32_t serial_no;     // Offset 0x14: the serial number of image, biger is newer
		} signature;
	};
	uint8_t sce_key_valid;          // Offset 0x18 : bit[0] indicates the SCE key & IV is valid or not. For section header only
	uint8_t reserved2[7];           // Offset 0x19 : reserved

	union {
		uint32_t reserved3[16];     // Offset 0x20 : reserved, for image header

		struct {
			uint8_t key_data[2][32];  // Offset 0x20 : user key1 data, Offset 0x40 : user key2 data
		} user_key_data;

		struct {                    // Offset 0x20 : for section header
			uint8_t key[16];        // Offset 0x20 : XIP/Ext_RAM image decryption key, for section header
			uint8_t iv[16];         // Offset 0x30 : XIP/Ext_RAM image decryption IV, for section header
			uint32_t reserved[8];   // Offset 0x40: reserved
		} sce_key_pair;
	};
} fm_image_header_t, *pfm_image_header_t;

/* define the structure for the GPIO pin power on trap */
typedef struct gpio_pin_pwr_on_trap_s {
	uint16_t pin: 5;      /*!< bit: 4...0 the GPIO pin number */
	uint16_t port: 3;      /*!< bit: 7...6 the  GPIO port number */
	uint16_t io_lev: 1;           /*!< bit:  8 the IO level to trigger the trap */
	uint16_t reserved: 6;       /*!< bit: 14...9 reserved */
	uint16_t valid: 1;      /*!< bit:  15 is this trap valid */
} gpio_pin_pwr_on_trap_t;

/* define the FW image information in the partition table */
typedef struct fw_part_info_s {
	uint8_t lfc_state_write;  /*!< life-cycle state update */
	uint8_t lfc_state_override;  /*!< life-cycle state eFuse setting over-ride */
	uint8_t efuse_wr_voltage;   /*!< LDO voltage for Life-cycle eFuse writting */
	uint8_t reserve0;
	uint8_t rec_num;   /*!< The record number in the partition table */
	uint8_t fw1_idx;   /*!< the record index for the FW1 partition */
	uint8_t fw2_idx;   /*!< the record index for the FW2 partition */
	uint8_t var_idx;   /*!< the record index for the VAR FW image partition */
	uint8_t mp_idx;   /*!< the record index for the MP FW image partition */
	uint8_t reserve1;
	gpio_pin_pwr_on_trap_t ota_trap;    /*!< to load and run the OTA FW image by this GPIO trap */
	gpio_pin_pwr_on_trap_t mp_trap;    /*!< to load and run the MP FW image by this GPIO trap */
	uint8_t reserve2;
	uint8_t key_exp_op;     /*!< the image1 AES key export option */
	uint32_t user_dat_len;  /*!< the length of user data those append after the partition records */
	uint8_t reserve3[12];
} fw_part_info_t, *pfw_part_info_t;

/* define the FW image information in the partition table */
typedef struct fw_part_record_s {
	uint32_t start_addr;    /*!< The start address of the image partition, it should be 4096 aligned */
	uint32_t len;    /*!< The size of the image partition, it should be times of 4096 */
	uint8_t pt_type;    /*!< the image type of the partition */
	uint8_t dbg_skip;    /*!< does skip the loading of this partition for debugging */
	uint8_t resv0;      /*!< reserved */
	uint8_t name[4];    /*!< the Name string of this partition */
	uint8_t sign;       /*!< the signature of the partition record */
	uint8_t hkey_valid; /*!< bit[0] to indicates the hask_key is valid or not */
	uint8_t resv1[15];  /*!< reserved */
	uint8_t hash_key[HASH_KEY_SIZE];  /*!<the hash key for the FW image ceritification */
} fw_part_record_t, *pfw_part_record_t;

/* define the FW secure table of a partition */
typedef struct fw_fst_s {
	uint16_t enc_option;        /*!< offset 0x00: Encryption algorithm selection, 0: ECB, 1: CBC */
	uint16_t hash_option;       /*!< offset 0x02: Hash algorithm selection, 0: MD5, 1: SHA256 */
	uint32_t cipher_size;       /*!< offset 0x04: if not the whole partition are encrypted, this field indicates the partition size of the chpher text */
	uint8_t  validate[8];       /*!< offset 0x08: the pattern to validate the decrypted image */
	uint32_t reserve1;          /*!< offset 0x10: reserved */
	union {                     /*!< offset 0x14: option flags */
		uint8_t option;
		struct {
			uint8_t enc_en: 1;  /*!< is the section_header/image encrypted */
			uint8_t hash_en: 1; /*!< is the image is hashed */
			uint8_t : 6;        /*!< reserved */
		} option_b;
	};
	uint8_t aes_key_valid;      /*!< offset 0x15: indicates the AES key & IV is valid or not */
	uint8_t reserve2[10];       /*!< offset 0x16: reserved */
	uint8_t aes_key[AES_KEY_SIZE];    /*!< offset 0x20: the AES key for the image decryption, if this key is invalid(all 0xFF), then use the origional AES key */
	uint8_t aes_iv[AES_IV_LEN]; /*!< offset 0x40: the IV for the AES-CBC encryption */
	uint8_t reserve3[16];       /*!< offset 0x50: reserved */
} fw_fst_t, *pfw_fst_t;

typedef struct image_partition_s {
	fm_image_header_t plain_header;
	uint8_t pub_key[32];
	fw_fst_t fst;
	fm_image_header_t secure_header;
} image_partition_t, *pimage_partition_t;

typedef struct decrypted_partition_info_s {
	uint8_t *pdec_key;  // the key for decryption
	fw_fst_t *pfst;     // point to the decrypted FST buffer
	fm_image_header_t *psecure_header;  // point to decrypted secure header
} decrypted_partition_info_t, *pdecrypted_partition_info_t;

typedef struct partition_table_s {
	fm_image_header_t header;       // header of partition table
	fw_part_info_t image_info;
	fw_part_record_t partition_record[MAX_PARTITION_RECORD];
	uint8_t user_data[PARTITION_TBL_USER_DATA_SIZE];
	uint8_t hash[HASH_RESULT_SIZE];
} partition_table_t, *ppartition_table_t;

typedef struct raw_image_hdr_s {
	uint32_t img_sz;    // image size
	uint32_t start_addr;    // the image start address (destination address to load the image)
	uint32_t ram_start_tbl;    // the RAM start function table
	uint32_t reserved0;
	uint32_t reserved1[4];
} raw_image_hdr_t, *praw_image_hdr_t;

/* Basic contruct of a Sub-Image */
typedef struct fw_sub_image_type_s {
	fm_image_header_t img_header;
	fw_fst_t fst;
} fw_sub_image_type_t, *pfw_sub_image_type_t;

/* header of a section of a Sub-Image */
typedef struct fw_image_section_type_s {
	fm_image_header_t sec_header;
	raw_image_hdr_t img_raw_header;
} fw_image_section_type_t, *pfw_image_section_type_t;

typedef struct fw_image_type_s {
	uint8_t ota_signature[OTA_SIGNATURE_SIZE];
	public_key_type_t pub_key[MAX_PUBLIC_KEY_NUM];
	fw_sub_image_type_t sub_img;
} fw_image_type_t, *pfw_image_type_t;

typedef struct fw_img_export_info_type_s {
	uint32_t img1_start_offset; // the Image1 offset of FW1 image start
	uint32_t fw1_start_offset;  // the flash offset of FW1 image start
	uint32_t fw2_start_offset;  // the flash offset of FW2 image start
	uint32_t fw1_sn;  // the FW1 SN
	uint32_t fw2_sn;  // the FW2 SN
	uint8_t fw1_valid;  // is FW1 valid (OTA signature valid)
	uint8_t fw2_valid;  // is FW2 valid (OTA signature valid)
	uint8_t loaded_fw_idx;      // the loaded (to RAM) FW index
	uint8_t reserv1;
} fw_img_export_info_type_t, *pfw_img_export_info_type_t;

typedef struct hal_sce_key_pair_s {
	uint8_t key[16];      // Key for XIP decryption
	uint8_t iv[16];       // IV for XIP decryption
} hal_sce_key_pair_t, *phal_sce_key_pair_t;

/**
  \brief  The data structure for a SCE configuration of a XIP memory block.
*/
typedef struct hal_xip_page_cfg_s {
	uint8_t is_used;
	uint8_t is_remap;
	uint8_t is_encrypted;
	uint8_t key_id;
	uint32_t phy_addr;      // The image physical address (flash image offset)
	uint32_t remap_addr;    // The re-mapping address (image virtual address)
	uint32_t remap_size;    // re-mapping size
	uint32_t hdr_total_size;// xip sub-image header total size
	uint32_t tag_base_addr; // aes-gcm flash tag_base_addr, tmp work around, pro2 flash sec remap & decrypt are independent
	uint32_t tag_flh_addr;  // aes-gcm flash tag located addr, tmp work around, pro2 flash sec remap & decrypt are independent
} hal_xip_page_cfg_t, *phal_xip_page_cfg_t;

#define MAX_PENDING_XIP_PAGE_CFG        4
/**
  \brief  The data structure for pending SCE configuration job.
*/
typedef struct hal_xip_sce_cfg_s {
	uint8_t cfg_cnt;        // the configured memory block count
	uint8_t xip_pg_sz;      // SCE page size selection
	uint8_t xip_bk_sz;      // SCE blcok size selection
	uint8_t flash_io_mode;
	uint8_t flash_pin_sel;
	uint8_t key_enc;        // is key encrypted
	char sign[9];        // signature
	uint8_t reserved[1];    // pad bytes to make structure size is 16*N
	hal_sce_key_pair_t xip_key[2];
	hal_xip_page_cfg_t xip_page_cfg[MAX_PENDING_XIP_PAGE_CFG];
} hal_xip_sce_cfg_t, *phal_xip_sce_cfg_t;

/**
  \brief  The data structure for a SCE configuration of a PSRAM/LPDDR memory block.
*/
typedef struct hal_ddr_sect_cfg_s {
	uint8_t is_used;
	uint8_t key_id;
	uint8_t reserv[2];      // padding bytes
	uint32_t start_addr;    // The image start address
	uint32_t img_size;      // The image size
} hal_ddr_sect_cfg_t, *phal_ddr_sect_cfg_t;

#define MAX_DDR_SECT_CFG        8
/**
  \brief  The data structure for PSRAM/LPDDR SCE configuration.
*/
typedef struct hal_ddr_sce_cfg_s {
	uint8_t mem_type;   // memory type, PSRAM or LPDDR
	uint8_t cfg_cnt;        // the configured memory block count
	uint8_t pg_sz;      // SCE page size selection
	uint8_t bk_sz;      // SCE blcok size selection
	uint8_t key_enc;    // is key encrypted
	char sign[9];        // signature
	uint8_t reserved[2];   // pad bytes to make structure size is 16*N
	hal_sce_key_pair_t key[2];
	hal_ddr_sect_cfg_t sect_cfg[MAX_DDR_SECT_CFG];
} hal_ddr_sce_cfg_t, *phal_ddr_sce_cfg_t;

/**
  \brief  The structure to store the data buffer address for boot loader.
*/
typedef struct hal_img1_tmp_buf_s {
	hal_crypto_adapter_t *pcrypto_engine;
	uint8_t *paes_iv;
	uint8_t *paes_key;
	uint8_t *phash_key;
	uint8_t *pexport_hash_priv_key;
	uint8_t *jtag_key_data[2];
	uint8_t jtag_key_valid;
} hal_img1_tmp_buf_t, *phal_img1_tmp_buf_t;


// ----------------------
/**
    FIXME: PRO2_WKARD for fixing broken build
    1: mark broken build reference as comment
    0: original
 */
#define PRO2_WKARD (1)
// ----------------------

/**
  \brief  The data structure of the stubs function for the flash booting functions in ROM
*/
typedef struct hal_flash_boot_stubs_s {
	void *ppartition_tbl;
	void *(*get_fw1_key_tbl)(void);
	void *(*get_fw2_key_tbl)(void);
	void (*clear_export_partition_tbl)(void);
	void (*erase_boot_loader)(uint32_t code_start, uint32_t code_size, uint32_t img2_entry);
	void *(*fw_img_info_tbl_query)(void);
	int32_t (*otu_fw_download)(hal_uart_adapter_t *potu_uart, uint32_t flash_sel, uint32_t flash_offset);
	uint8_t *fast_boot;

#if !defined(PRO2_WKARD) || (PRO2_WKARD==0) /* FIXME: PRO2_WKARD for fixing broken build */
	const flash_pin_sel_t *boot_flash_pin_sel;
#endif /* FIXME: PRO2_WKARD for fixing broken build */

	uint8_t *pexport_hash_priv_key;

	uint32_t reserved[4];  // reserved space for next ROM code version function table extending.
} hal_flash_boot_stubs_t;


#if 0
/**
  \brief  The data buffer for crypto operation of fast boot image2 checking
*/
typedef struct hal_fast_boot_crypto_buf_s {
	uint8_t ss_priv_key[PRIV_KEY_SIZE];
	uint8_t hash_priv_key_enced[PRIV_KEY_SIZE];
	uint8_t temp_hash_out_buf[HASH_RESULT_SIZE];
	uint8_t hash_key[HASH_KEY_SIZE];
	uint8_t aes_iv[AES_IV_LEN];
	hal_crypto_adapter_t crypto_engine;
} hal_fast_boot_crypto_buf_t;
#endif
#define START_TBL_HASH_CHK_MIN_SIZE         76

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _FW_IMG_H_"

