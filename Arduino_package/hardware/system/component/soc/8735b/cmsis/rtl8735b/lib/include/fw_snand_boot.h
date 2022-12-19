/**************************************************************************//**
 * @file     fw_snand_boot.h
 * @brief    Declare the booting from nand flash.
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

#ifndef _FW_SNAND_BOOT_H_
#define _FW_SNAND_BOOT_H_

#include "cmsis.h"
#include "rtl8735b_ramstart.h"
#include "fw_img_tlv.h"
#include "static_assert.h"

/* Util macro */
#define SIZE_ALIGN_TO(size, align)  ((size) % (align) > 0 ? (((size) / (align)) + 1) * (align) : (size))

/* End of util */

#define NAND_PAGE_MAX_LEN           (2 * 0x840)

#define NAND_TMP_DATA_MAX_LEN       0x1000

#define IMG_HDR_MAX                 256
#define SECT_HDR_MAX                256

/// Fixed ctrl info start blk
#define NAND_CTRL_INFO_START_BLK    0
/// Fixed ctrl info backup count
#define NAND_CTRL_INFO_DUP_CNT      8
/// Max count of virtual block map
#define SNAND_VMAP_MAX              48
/// SNAND start block for debug
#define DBG_SNAND_START_BLK         0

#define SNAND_PAR_RECORD_MAG_NUM    0xFF35FF87
#define SNAND_CTRL_INFO_MAG_NUM     0xFF35FF87

#define NAND_SPARE_TYPE_IDX         4

#define SNAND_INVAL_PAR_TBL_IDX     ((u8)0xFF)

#define SNAND_ADDR_INIT(PAGE, COL)  { .page = PAGE, .col = COL}
#define SNAND_ADDR_BLK_INIT(BLK, COL)  { .page = (BLK) * NAND_PAGE_PER_BLK, .col = COL}

#define SNAND_ADDR_SET(addr_ptr, PAGE, COL) {(addr_ptr)->page = PAGE; (addr_ptr)->col = COL; }
#define SNAND_ADDR_BLK_SET(addr_ptr, BLK, COL) \
    {(addr_ptr)->page = (BLK) * NAND_PAGE_PER_BLK; \
     (addr_ptr)->col = COL; }

/// NAND flash page data size in byte
#define NAND_PAGE_LEN               ((const u32)NAND_CTRL_INFO.page_size)
/// NAND flash page spare size in byte
#define NAND_SPARE_LEN              ((const u32)NAND_CTRL_INFO.spare_size)
/// NAND flash page count per block
#define NAND_PAGE_PER_BLK           ((const u32)NAND_CTRL_INFO.page_per_blk)
/// Total block count in flash
#define NAND_BLK_CNT                ((const u32)NAND_CTRL_INFO.blk_cnt)
/// NAND flash block size in byte
#define NAND_BLK_LEN                (NAND_PAGE2ADDR(NAND_PAGE_PER_BLK))
/// Get offset of address inside page
#define NAND_PAGE_OFST(addr)        ((addr) & NAND_CTRL_INFO.page_mask)
/// Get offset of page inside block
#define NAND_BLK_OFST(page_addr)    (((u32)page_addr) & NAND_CTRL_INFO.blk_mask)
/// Convert page to block
#define NAND_PAGE2BLK(page_addr)    ((page_addr) >> NAND_CTRL_INFO.page2blk_shift)
/// Convert address to page
#define NAND_ADDR2PAGE(addr)        ((addr) >> NAND_CTRL_INFO.addr2page_shift)
/// Convert page to address
#define NAND_PAGE2ADDR(page_addr)   (((u32)page_addr) << NAND_CTRL_INFO.addr2page_shift)
/// Convert block to page
#define NAND_BLK2PAGE(blk_idx)      (((u32)blk_idx) << NAND_CTRL_INFO.page2blk_shift)
/// Base address of simulated snand address
#define NAND_SIM_ADDR_BASE          SPI_FLASH_BASE
/// Convert page & col to simulated address, do not directly access the address
#define NAND_SIM_ADDR(addr_ptr)    ((void *)(NAND_PAGE2ADDR((addr_ptr)->page) + (addr_ptr)->col + NAND_SIM_ADDR_BASE))

#define CEILING_NBYTE(SIZE, N)      (SIZE + ((SIZE % N)  ? (N - (SIZE % N)) : 0))

// Slots to store virtual maps
// Usually just use DEFAULT. Only use EXTEND when concurrent vmap is needed
enum snand_glb_vmap_slot {
	SNAND_GLB_VMAP_SLOT_DEFAULT = 0,
	SNAND_GLB_VMAP_SLOT_EXTEND = 1,

	SNAND_GLB_VMAP_TOTAL_SLOTS = 2,
};

typedef u8 snand_glb_vmap_slot_t;
typedef u16 snand_vblk_idx_t;

typedef struct snand_raw_ctrl_info {
	u32 blk_cnt;
	u32 page_per_blk;
	u32 page_size;
	u32 spare_size;
	u32 vendor_info[2];
	u32 bbt_start;
	u32 bbt_dup_cnt;
	u32 par_tbl_start;
	u32 par_tbl_dup_cnt;
	u16 vrf_alg;            // verify image algorithm selection
	u16 rsvd1;
	u32 rsvd2;
	u32 magic_num;
	u32 rsvd3[11];
} snand_raw_ctrl_info_t;

STATIC_ASSERT(sizeof(snand_raw_ctrl_info_t) == 32 * 3, struct_not_align);

typedef struct snand_ctrl_info {
	u32 blk_cnt;
	u32 page_per_blk;
	u32 page_size;
	u32 spare_size;
	u32 page_mask;
	u32 blk_mask;
	u8 page2blk_shift;
	u8 addr2page_shift;
	u8 cache_rsvd[6];
	// cache line size
	snand_raw_ctrl_info_t raw;
	// Following data is not present in < C cut
	u32 ctrl_info_blk_idx;
	u32 part_tbl_blk_idx;
	u32 rsvd2[14];
} snand_ctrl_info_t;

STATIC_ASSERT((offsetof(snand_ctrl_info_t, cache_rsvd) + sizeof(((snand_ctrl_info_t *)NULL)->cache_rsvd)) == 32, struct_not_align);
STATIC_ASSERT(sizeof(snand_ctrl_info_t) == 32 * 6, struct_not_align);


// NAND Flash Physical Address
typedef struct snand_addr {
	u32 page;
	u16 col;
} snand_addr_t;

STATIC_ASSERT(sizeof(snand_addr_t) == 8, addr_sz);

// NAND Flash virtual map info
typedef struct snand_vmap {
	// For map_size > SNAND_VMAP_MAX, need rotation
	u16 map_size;
	u16 cur_rec_idx;
	snand_addr_t vmap0_addr;

	// virtual physical block mapping
	snand_vblk_idx_t map[SNAND_VMAP_MAX];
} snand_vmap_t;

// NAND Flash Address with virtual map (virtual address)
typedef struct snand_vaddr {
	u32 page;
	u16 col;
	snand_vmap_t *vmap;
} snand_vaddr_t;

typedef struct snand_spare0_meta {
	u8 bad_blk_tag;
	u8 type_id;
	u16 crc16;
} snand_spare0_meta_t;

STATIC_ASSERT(sizeof(snand_spare0_meta_t) == 4, spare0_sz);

// Partition record raw format on Flash
typedef struct snand_part_record {
	u32 magic_num;
	u16 type_id;
	u16 blk_cnt;
	u16 serno;

	u8 rsvd2[22];
	snand_vblk_idx_t vblk[SNAND_VMAP_MAX];
} snand_part_record_t;

STATIC_ASSERT(sizeof(snand_part_record_t) == (32 * 4), rec_sz);

// Partition Table Info on RAM
typedef struct snand_part_entry {
	u16 type_id;
	u16 blk_cnt;
	snand_addr_t vmap_addr;
	u32 rsvd[6];
} snand_part_entry_t;

STATIC_ASSERT(sizeof(snand_part_entry_t) == 36, entry_sz);

// Partition Table on RAM
typedef struct snand_partition_tbl {
	part_fst_info_t mfst;
	snand_part_entry_t entrys[PARTITION_RECORD_MAX];
} snand_partition_tbl_t;

// Partition record group info (combine multiple records into a partition)
typedef struct snand_rec_grp {
	BOOL valid;
	u16 type_id;
	u16 blk_cnt;
	u16 rec_cnt;
	snand_addr_t vmap0_addr;
} snand_rec_grp_t;

// Stubs for NAND Flash Boot
typedef struct hal_snand_boot_stubs {
	u8 *rom_snand_boot;
	snand_ctrl_info_t *ctrl_info;
	snand_partition_tbl_t *part_tbl;
	hal_status_t (*snand_memcpy_update)(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_addr_t *snand_addr, u32 size);
	hal_status_t (*snand_memcpy)(hal_snafc_adaptor_t *snafc_adpt, void *dest, const snand_addr_t *snand_addr, u32 size);
	void (*snand_offset)(snand_addr_t *snand_addr, u32 offset);
	hal_status_t (*snand_vmemcpy_update)(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_vaddr_t *snand_addr, u32 size);
	hal_status_t (*snand_vmemcpy)(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_vaddr_t *snand_addr, u32 size);
	void (*snand_voffset)(snand_vaddr_t *snand_addr, u32 offset);
	s32(*snand_img_sel)(snand_partition_tbl_t *part_tbl, const u8 img_obj, const u8 img_sel_op);
	u32 rsvd[38];
} hal_snand_boot_stubs_t;

typedef struct snand_sect_cipher_info_s {
	snand_vaddr_t *cur_addr;
	snand_vaddr_t *pgcm_tag_addr;
	uint32_t dec_base;
	uint32_t resv;
} snand_sect_cipher_info_t, *psnand_sect_cipher_info_t;

STATIC_ASSERT(sizeof(hal_snand_boot_stubs_t) == (48 * 4), stub_sz_changed);

extern const hal_snand_boot_stubs_t hal_snand_boot_stubs;

#if defined(ROM_REGION)

#define NAND_CTRL_INFO              rom_snand_ctrl_info
extern snand_ctrl_info_t rom_snand_ctrl_info;
extern u8 rom_snand_boot;
extern snand_partition_tbl_t snand_part_tbl;
extern u8 snand_page_buf[NAND_PAGE_MAX_LEN]; // must > 4K to store manifest
extern u8 mfst_buf[sizeof(img_manifest_t)];
extern snand_vaddr_t sim_memcpy_start_addr;
extern hal_snafc_adaptor_t boot_snafc_adpt;

hal_status_t fw_spic_pinmux_ctl(phal_spic_adaptor_t, flash_pin_sel_t *, u8);
hal_status_t fw_snafc_deinit(hal_snafc_adaptor_t *pSnafcAdaptor);
s32 snand_flash_boot(PRAM_FUNCTION_START_TABLE *pram_start_func);
void init_ctrl_info(snand_ctrl_info_t *info);

s32 snand_vaddr_init(hal_snafc_adaptor_t *adpt, snand_vaddr_t *addr,
					 const snand_part_entry_t *entry, snand_glb_vmap_slot_t slot);
hal_status_t snand_memcpy(hal_snafc_adaptor_t *snafc_adpt, void *dest, const snand_addr_t *snand_addr, u32 size);
hal_status_t snand_memcpy_update(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_addr_t *snand_addr, u32 size);
void snand_offset(snand_addr_t *snand_addr, u32 offset);
hal_status_t snand_vmemcpy_update(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_vaddr_t *snand_addr, u32 size);
hal_status_t snand_vmemcpy(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_vaddr_t *snand_addr, u32 size);
void snand_voffset(snand_vaddr_t *snand_addr, u32 offset);
hal_status_t snand_sim_memcpy(void *dst, const void *src, u32 size);
s32 sb_snand_hash_update(hal_crypto_adapter_t *crypto_adtr, uint32_t msglen, uint32_t auth_type, uint8_t *p_msg, uint8_t is_flash_dat);
s32 snand_img_sel(snand_partition_tbl_t *part_tbl, const u8 img_obj, const u8 img_sel_op);
hal_status_t fw_snafc_init_core(hal_snafc_adaptor_t *snafc_adpt, u8 spic_bit_mode, u8 io_pin_sel, u8 do_protect);
s32 snand_load_ctrl_info(hal_crypto_adapter_t *crypto_adpt);
s32 snand_load_cipher_data(sect_hdr_t *sect_hdr, snand_vaddr_t *cur_addr,
						   snand_vaddr_t *gcm_tag_addr, sec_boot_info_t *sb_info, const u32 dec_base);

__STATIC_FORCEINLINE
hal_status_t fw_snafc_init_wr(hal_snafc_adaptor_t *snafc_adpt, u8 spic_bit_mode, u8 io_pin_sel)
{
	// Write Proect disable
	return fw_snafc_init_core(snafc_adpt, spic_bit_mode, io_pin_sel, DISABLE);
}

__STATIC_FORCEINLINE
hal_status_t fw_snafc_init(hal_snafc_adaptor_t *snafc_adpt, u8 spic_bit_mode, u8 io_pin_sel)
{
	return fw_snafc_init_core(snafc_adpt, spic_bit_mode, io_pin_sel, ENABLE);
}

__STATIC_FORCEINLINE void snand_vaddr_clone(snand_vaddr_t *dest, const snand_vaddr_t *src)
{
	_memcpy(dest, src, sizeof(snand_vaddr_t));
}

#elif defined(CONFIG_BUILD_BOOT) && (CONFIG_BUILD_BOOT == 1) // Boot loader only

#define NAND_CTRL_INFO              snand_ctrl_info
extern snand_ctrl_info_t            snand_ctrl_info;
//#define NAND_CTRL_INFO              (*hal_snand_boot_stubs.ctrl_info)

extern hal_snafc_adaptor_t boot_snafc_adpt;
extern u8 snand_page_buf[NAND_PAGE_MAX_LEN];
extern u8 mfst_buf[NAND_PAGE_MAX_LEN];
extern snand_partition_tbl_t snand_part_tbl;

s32 snand_boot_loader(PRAM_FUNCTION_START_TABLE *ram_start_func);

#if 0
__STATIC_FORCEINLINE hal_status_t snand_memcpy(hal_snafc_adaptor_t *snafc_adpt, void *dest, const snand_addr_t *snand_addr, u32 size)
{
	return hal_snand_boot_stubs.snand_memcpy(snafc_adpt, dest, snand_addr, size);
}

__STATIC_FORCEINLINE hal_status_t snand_memcpy_update(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_addr_t *snand_addr, u32 size)
{
	return hal_snand_boot_stubs.snand_memcpy_update(snafc_adpt, dest, snand_addr, size);
}
__STATIC_FORCEINLINE hal_status_t snand_vmemcpy_update(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_vaddr_t *snand_addr, u32 size)
{
	return hal_snand_boot_stubs.snand_vmemcpy_update(snafc_adpt, dest, snand_addr, size);
}

__STATIC_FORCEINLINE hal_status_t snand_vmemcpy(hal_snafc_adaptor_t *snafc_adpt, void *dest, const snand_vaddr_t *snand_addr, u32 size)
{
	return hal_snand_boot_stubs.snand_vmemcpy(snafc_adpt, dest, snand_addr, size);
}

__STATIC_FORCEINLINE hal_status_t snand_offset(snand_addr_t *snand_addr, u32 offset)
{
	return hal_snand_boot_stubs.snand_offset(snand_addr, offset);
}

__STATIC_FORCEINLINE hal_status_t snand_voffset(snand_vaddr_t *snand_addr, u32 offset)
{
	return hal_snand_boot_stubs.snand_voffset(snand_addr, offset);
}
#else
hal_status_t snand_memcpy(hal_snafc_adaptor_t *snafc_adpt, void *dest, const snand_addr_t *snand_addr, u32 size);
hal_status_t snand_memcpy_update(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_addr_t *snand_addr, u32 size);
hal_status_t snand_vmemcpy_update(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_vaddr_t *snand_addr, u32 size);
hal_status_t snand_vmemcpy(hal_snafc_adaptor_t *snafc_adpt, void *dest, snand_vaddr_t *snand_addr, u32 size);
void snand_offset(snand_addr_t *snand_addr, u32 offset);
void snand_voffset(snand_vaddr_t *snand_addr, u32 offset);
#endif

s32 boot_snand_reparse(void);
s32 snand_img_sel(snand_partition_tbl_t *part_tbl, const u8 img_obj, const u8 img_sel_op);

#else // MAIN

#define NAND_CTRL_INFO              snand_ctrl_info
extern snand_ctrl_info_t            snand_ctrl_info;

#endif // end of CONFIG_BUILD_BOOT

#endif  // end of "#define _FW_SNAND_BOOT_H_"
