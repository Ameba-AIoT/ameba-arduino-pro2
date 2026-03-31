
/**************************************************************************//**
 * @file     snand_api.c
 * @brief    This file implements the SNAND (Serial NAND) Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2021-09-15
 *
 * @note
 *
 ******************************************************************************
 * @attention
 *
 * Copyright(c) 2007 - 2022 Realtek Corporation. All rights reserved.
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
 ******************************************************************************
 */
#include <string.h> /* memset(), memcmp(), memcpy() */
#include "snand_api.h"
#include "cmsis.h"
#include "hal_snand.h"
#include "hal_cache.h" /**< dcache_invalidate_by_addr(addr, dsize), dcache_clean_by_addr(addr, dsize) */
#define DCACHE_WB_BY_ADDR(addr,sz)      do {dcache_clean_by_addr(addr,sz);} while(0)
#define DCACHE_INV_BY_ADDR(addr,sz)     do {dcache_invalidate_by_addr(addr,sz);} while(0)
extern hal_snafc_adaptor_t *pglob_snafc_adaptor;
#define EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW (0)
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
rtkNandInfo_t mSnandApiNandInfo;
nand_chip_param_T *mSnandChipParam = NULL;
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
/* ======================================== */
/* For S-NAND Bad-Block Management (BBM)    */
/* ======================================== */
#define MAGIC_PATTERN_LEN (4)
#define SNAND_BBM_MEMCMP_MATCH (0)
#define BBM_MAGIC_OFFSET (1) /* 1*sizeof(bb_m) = 8 byte */
#define V2R_MAGIC_OFFSET (4) /* 4*sizeof(v2r) = 8 byte */
/*
 id: spi nand flash id
 // isLastPage: 0 // (unknown) deprecated
 id_len: spi nand flash id len
 pagesize: S-NAND's main area size (bytes)
 oobsize: S-NAND's spare area size (bytes)
 num_chunk_per_block: page-per-block
 num_block: block-per-die (flash vendor MAY packed multi-die into 1 flash device)
 maxclk
 pipe_lat
 support_dio
 support_qio
 enable_dieon_ecc
*/
static nand_chip_param_T nand_chip_id[] = {
	/* MXIC MX35LF1GE4AB */
	{
		.id = MXIC_RDID_MX35LF1GE4AB,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 2,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 1,
		.maxclk = 104000000,
		.pipe_lat = 0,
		.support_dio = FALSE,
		.support_qio = FALSE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = FALSE,
		.enable_dieon_ecc = TRUE,
	},
	/* MXIC MX35LF2GE4AB */
	{
		.id = MXIC_RDID_MX35LF2GE4AB,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 2,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 2048,
		.dienum = 1,
		.maxclk = 104000000,
		.pipe_lat = 0,
		.support_dio = FALSE,
		.support_qio = FALSE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = FALSE,
		.enable_dieon_ecc = TRUE,
	},
	/* Winbond W25N512GV */
	{
		.id = WINBOND_RDID_W25N512GV,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 3,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 512,
		.dienum = 1,
		.maxclk = 133000000,
		.pipe_lat = 1,
		.support_dio = TRUE,
		.support_qio = TRUE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = TRUE,
		.enable_dieon_ecc = FALSE,
	},
	/* Winbond W25N01GV */
	{
		.id = WINBOND_RDID_W25N01GV,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 3,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 1,
		.maxclk = 104000000,
		.pipe_lat = 1,
		.support_dio = TRUE,
		.support_qio = TRUE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = TRUE,
		.enable_dieon_ecc = FALSE,
	},
	/* Winbond W25M02GV*/
	{
		.id = WINBOND_RDID_W25M02GV,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 3,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 2,
		.maxclk = 104000000,
		.pipe_lat = 1,
		.support_dio = TRUE,
		.support_qio = TRUE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = TRUE,
		.enable_dieon_ecc = FALSE,
	},
	/* GigaDevice GD5F1GQ4U */
	{
		.id = GD_RDID_GD5F1GQ4U,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 2,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 1,
		.maxclk = 120000000,
		.pipe_lat = 0,
		.support_dio = TRUE,
		.support_qio = TRUE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = TRUE,
		.enable_dieon_ecc = FALSE,
	},
	/* GigaDevice GD5F1GQ4A */
	{
		.id = GD_RDID_GD5F1GQ4A,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 2,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 1,
		.maxclk = 104000000,
		.pipe_lat = 0,
		.support_dio = TRUE,
		.support_qio = TRUE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = TRUE,
		.enable_dieon_ecc = FALSE,
	},
	/* GigaDevice GD5F1GQ4xFxxH */
	{
		.id = GD_RDID_GD5F1GQ4xFxxH,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 3,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 1,
		.maxclk = 120000000,
		.pipe_lat = 0,
		.support_dio = TRUE,
		.support_qio = TRUE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = TRUE,
		.enable_dieon_ecc = FALSE,
	},
	/* GigaDevice GD5F1GQ5xExxH */
	{
		.id = GD_RDID_GD5F1GQ5xExxH,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 2,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 1,
		.maxclk = 133000000,
		.pipe_lat = 0,
		.support_dio = TRUE,
		.support_qio = TRUE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = TRUE,
		.enable_dieon_ecc = FALSE,
	},
	/* Kiaxio (Toshiba) TC58CVG0S3HxAIx */
	{
		.id = TOSHIBA_RDID_TC58CVG0S3HxAIx,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 2,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 1,
		.maxclk = 104000000,
		.pipe_lat = 0,
		.support_dio = FALSE,
		.support_qio = FALSE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = FALSE,
		.enable_dieon_ecc = TRUE,
	},
	/* Kiaxio (Toshiba) TC58CVG0S3HRAIJ */
	{
		.id = TOSHIBA_RDID_TC58CVG0S3HRAIJ,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 3,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 1,
		.maxclk = 133000000,
		.pipe_lat = 0,
		.support_dio = FALSE,
		.support_qio = FALSE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = FALSE,
		.enable_dieon_ecc = TRUE,
	},
	/* Kiaxio (Toshiba) TC58CVG1S3HRAIJ */
	{
		.id = TOSHIBA_RDID_TC58CVG1S3HRAIJ,
		//.isLastPage = 0,
		.id_len = 3,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 2048,
		.dienum = 1,
		.maxclk = 133000000,
		.pipe_lat = 0,
		.support_dio = FALSE,
		.support_qio = FALSE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = FALSE,
		.enable_dieon_ecc = TRUE,
	},
	/* Micron MT29F1G01AAADD */
	{
		.id = MICRON_RDID_MT29F1G01AAADD,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 2,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 1,
		.maxclk = 50000000,
		.pipe_lat = 0,
		.support_dio = TRUE,
		.support_qio = TRUE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = TRUE,
		.enable_dieon_ecc = TRUE,
	},
	/* Micron MT29F1G01ABAFDxx */
	{
		.id = MICRON_RDID_MT29F1G01ABAFD,
		//.isLastPage = 0, /* Deprecated in AmebaPro2 */
		.id_len = 2,
		.pagesize = 0x800,
		.oobsize = 64,
		.num_chunk_per_block = 64,
		.num_block = 1024,
		.dienum = 1,
		.maxclk = 133000000,
		.pipe_lat = 0,
		.support_dio = TRUE,
		.support_qio = TRUE,
		.support_read_cache_2 = TRUE,
		.support_read_cache_4 = TRUE,
		.support_programme_cache_4 = TRUE,
		.enable_dieon_ecc = TRUE,
	},
};
uint32_t mSnandBbmLastGoodBlkIdx; /* =0; */
uint32_t mSnandBbmLastRbaBlkIdx; /* =0; */
struct mtd_info mSnandBbm_mtdInfo = {
	.type = 0,
	.flags = 0,
	.size = 132 * 1024 * 1024, /* 1 plane = 1024 BLK = 132 MBs */
	.erasesize = 132 * 1024, /* 1 Block = 0x840 * 64 (pages) = 132 KBs */
	.writesize = 2048, /* 2048 */
	.writebufsize = 2112, /* .writesize + .oobsize = 2048+64 */
	.oobsize = 0x40, // 64 bytes
	.oobavail = TRUE,
	.erasesize_shift = 17,
	.writesize_shift = 11,
	.erasesize_mask = 17,
	.writesize_mask = 11,
	.bitflip_threshold = 10,
};
/**************************************************************************
 *                           D E F I N I T I O N S
 **************************************************************************/
/* _rtkNandInfo_dump */
static uint32_t
_rtkNandInfo_dump(
	rtkNandInfo_t *rtkNandInfo
)
{
	dbg_printf("rtkNandInfo_t at addr=0x%08x (sz=0x%x)\r\n", rtkNandInfo, sizeof(rtkNandInfo_t));
	if (!rtkNandInfo) {
		return FAIL;
	}
	/* ----- */
	dbg_printf("  0x%08x = totalsize\r\n", rtkNandInfo->totalsize);
	dbg_printf("  0x%08x = erasesize\r\n", rtkNandInfo->erasesize);
	dbg_printf("  0x%08x = writesize\r\n", rtkNandInfo->writesize);
	dbg_printf("  0x%08x, 0x%08x = (pBuf, writebufsize)\r\n", rtkNandInfo->pBuf, rtkNandInfo->writebufsize);
	/* ----- */
	dbg_printf("  %d = RBA_PERCENT\r\n", rtkNandInfo->RBA_PERCENT);
	dbg_printf("  0x%08x = RBA_CNT\r\n", rtkNandInfo->RBA_CNT);
	dbg_printf("  0x%08x = RBA_OFFSET\r\n", rtkNandInfo->RBA_OFFSET);
	/* ----- */
	dbg_printf("  0x%08x, 0x%08x = (pBBM, nBBMBufSz)\r\n", rtkNandInfo->pBBM, rtkNandInfo->nBBMBufSz);
	dbg_printf("  0x%08x, 0x%08x = (pV2R, nV2RBufSz)\r\n", rtkNandInfo->pV2R, rtkNandInfo->nV2RBufSz);
	return SUCCESS;
} /* _rtkNandInfo_dump */
/**
 snand_bbm_init
 @brief Inital S-NAND BBM relate configuration before calling other snand_bbm APIs.
 @param[in] rtkNandInfo RTK NAND info, S-NAND Flash dependent configuration for SNAND BBM functions.
 @return SUCCESS
 @return FAIL
 */
uint32_t
snand_bbm_init(
	rtkNandInfo_t *rtkNandInfo
)
{
	uint32_t totalBlkCnt = 0;
	if (!rtkNandInfo) {
		dbg_printf("ERR: NULL pointer to rtkNandInfo_t.\r\n");
		return FAIL;
	}
	if ((!rtkNandInfo->writesize) || (!rtkNandInfo->erasesize) || (!rtkNandInfo->totalsize)) {
		dbg_printf("ERR: Access size information of MTD device are 0.\r\n");
		return FAIL;
	}
	if (((rtkNandInfo->writesize) > (rtkNandInfo->erasesize)) ||
		((rtkNandInfo->erasesize) > (rtkNandInfo->totalsize)) ||
		((rtkNandInfo->writesize) > (rtkNandInfo->totalsize))) {
		dbg_printf("ERR: Access size for MTD device are INCORRECT.\r\n");
		return FAIL;
	}
	if (!rtkNandInfo->pBuf) {
		dbg_printf("ERR: NULL pointer to temp buffer.\r\n");
		return FAIL;
	}
	if (!rtkNandInfo->writebufsize) {
		dbg_printf("ERR: temp buffer size is 0.\r\n");
		return FAIL;
	}
	if (!rtkNandInfo->RBA_PERCENT) {
		dbg_printf("ERR: RBA_PERCENT is 0.\r\n");
		return FAIL;
	}
#if 1 /* (optional) protection */
	totalBlkCnt = (rtkNandInfo->totalsize) / (rtkNandInfo->erasesize);
	if (rtkNandInfo->RBA_CNT != ((totalBlkCnt * rtkNandInfo->RBA_PERCENT) / 100)) {
		dbg_printf("ERR: RBA_CNT incorrect.\r\n");
		return FAIL;
	}
	if (rtkNandInfo->RBA_OFFSET != (totalBlkCnt - rtkNandInfo->RBA_CNT)) {
		dbg_printf("ERR: RBA_OFFSET incorrect.\r\n");
		return FAIL;
	}
#endif /* (optional) protection */
	if ((!rtkNandInfo->pBBM) || (!rtkNandInfo->pV2R)) {
		return FAIL;
	}
	if (rtkNandInfo->nBBMBufSz < sizeof(BB_t)) {
		return FAIL;
	}
	if (rtkNandInfo->nV2RBufSz < sizeof(BB_v2r)) {
		return FAIL;
	}
#if 1 /* (optional) protection */
	/* Force BBMBufSz ALIGN to struct BB_t */
	if (rtkNandInfo->nBBMBufSz % sizeof(BB_t)) {
		return FAIL;
	}
	/* Force BBMBufSz ALIGN to struct BB_t */
	if (rtkNandInfo->nV2RBufSz % sizeof(BB_v2r)) {
		return FAIL;
	}
#endif /* (optional) protection */
	rtkNandInfo->magicStr[0] = 'R';
	rtkNandInfo->magicStr[1] = 'T';
	rtkNandInfo->magicStr[2] = 'K';
	rtkNandInfo->magicStr[3] = 'N';
	return SUCCESS;
} /* snand_bbm_init */
/* _snand_bbm_dump_short */
static uint32_t
_snand_bbm_dump_short(
	uint32_t *pBufStart,
	uint32_t bufSzB
)
{
	uint16_t *pBuf = NULL;
	uint32_t tLoopIdx = 0;
	uint32_t tLoopCnt = 1;
	if (pBufStart == NULL) {
		return FAIL;
	}
	if (bufSzB < 2) {
		return FAIL;
	}
	pBuf = (uint16_t *) pBufStart;
	tLoopCnt = bufSzB / sizeof(uint16_t);
	for (tLoopIdx = 0; tLoopIdx < tLoopCnt; tLoopIdx++, pBuf++) {
		/* prefix for each LINE (16 bytes) */
		if (0 == tLoopIdx % (16 / sizeof(uint16_t))) {
			dbg_printf("[%04d]:", (tLoopIdx / (16 / sizeof(uint16_t))));
		}
		dbg_printf("0x%04x", *pBuf);
		/* skip post-fix if its last UNIT */
		if (tLoopIdx + 1 == tLoopCnt) {
			break;
		}
		/* post-fix for each UNIT */
		if (3 == tLoopIdx % (16 / sizeof(uint16_t))) {
			dbg_printf("-");
		} else if (7 == tLoopIdx % (16 / sizeof(uint16_t))) {
			dbg_printf("\r\n");
		} else {
			dbg_printf(" ");
		}
	}
	dbg_printf("\r\n");
	return SUCCESS;
} /* _snand_bbm_dump_short */
/**
 snand_bbm_dump
 @brief Dump V2R_T and BBM_T data structure.
 @param[in] rtkNandInfo RTK NAND info
 @param[in] opt option; 1 for V2R_T only; 2 for BBM_T only; 3 for both V2R_T and BBM_T.
 @return SUCCESS
 */
uint32_t
snand_bbm_dump(
	rtkNandInfo_t *rtkNandInfo,
	uint32_t opt
)
{
	if (!rtkNandInfo) {
		return FAIL;
	}
	if (SNAND_BBM_MEMCMP_MATCH != memcmp(rtkNandInfo->magicStr, "RTKN", MAGIC_PATTERN_LEN)) {
		return FAIL;
	}
	if (opt & (1 << 0)) {
		dbg_printf("Virtual-to-Real (V2R) mapping\r\n");
		_snand_bbm_dump_short((uint32_t *) rtkNandInfo->pV2R, rtkNandInfo->nV2RBufSz);
		dbg_printf("\r\n");
	}
	if (opt & (1 << 1)) {
		dbg_printf("BBM Table\r\n");
		_snand_bbm_dump_short((uint32_t *) rtkNandInfo->pBBM, rtkNandInfo->nBBMBufSz);
		dbg_printf("\r\n");
	}
	return SUCCESS;
} /* snand_bbm_dump */
/**
 snand_bbm_create
 @brief Create V2R_T data structure for mapping VIRTUAL ADDRESS to PHYSICAL ADDRESS; and create BBM_T data structure for mapping BAD block to (pre-reserved) GOOD block.
 @param[in] rtkNandInfo RTK NAND info
 @return SUCCESS
 @return FAIL
*/
uint32_t
snand_bbm_create(
	rtkNandInfo_t *rtkNandInfo
)
{
	uint32_t curBlkIdx;
	//uint32_t dummyIdx;
	uint32_t dummyIdx2;
	uint32_t ppb = -1UL; /**< pagePerBlock */
	if (!rtkNandInfo) {
		return FAIL;
	}
	if (SNAND_BBM_MEMCMP_MATCH != memcmp(rtkNandInfo->magicStr, "RTKN", MAGIC_PATTERN_LEN)) {
		return FAIL;
	}
	if (rtkNandInfo->writesize) {
		ppb = rtkNandInfo->erasesize / rtkNandInfo->writesize;
	} else {
		ppb = 0x40; /* default */
	}
	memset(rtkNandInfo->pBBM, 0xff, rtkNandInfo->nBBMBufSz);
	memset(rtkNandInfo->pV2R, 0xff, rtkNandInfo->nV2RBufSz);
#if 0
	dbg_printf("%s Ln %d.\r\n", __FILE__, __LINE__); /*PhilipDebug*/
#endif
	/* MAGIC_PATTERN (8 bytes) for BBM */
	rtkNandInfo->pBBM[0].BB_die = 0x4242;       /* "BB" */
	rtkNandInfo->pBBM[0].bad_block = 0x544d;    /* "MT" */
	rtkNandInfo->pBBM[0].RB_die = 0x6262;       /* "bb" */
	rtkNandInfo->pBBM[0].remap_block = 0x746d;  /* "mt" */
	/* MAGIC_PATTERN (8 bytes) for V2R */
	rtkNandInfo->pV2R[0].block_r = 0x3256;  /* "V2" */
	rtkNandInfo->pV2R[1].block_r = 0x5452;  /* "RT" */
	rtkNandInfo->pV2R[2].block_r = 0x3276;  /* "v2" */
	rtkNandInfo->pV2R[3].block_r = 0x7472;  /* "rt" */
	mSnandBbmLastGoodBlkIdx = V2R_MAGIC_OFFSET;
	for (curBlkIdx = 0; curBlkIdx < (rtkNandInfo->RBA_OFFSET); curBlkIdx++) {
		hal_snand_pio_read(pglob_snafc_adaptor, rtkNandInfo->pBuf, rtkNandInfo->writebufsize, (curBlkIdx * ppb));
		if (rtkNandInfo->pBuf[rtkNandInfo->writesize] == 0xFF) {
			/*good block*/
			rtkNandInfo->pV2R[mSnandBbmLastGoodBlkIdx].block_r = curBlkIdx;
			mSnandBbmLastGoodBlkIdx++;
		} else {
			/*bad block*/
			for (dummyIdx2 = mSnandBbmLastRbaBlkIdx; dummyIdx2 < rtkNandInfo->RBA_CNT; dummyIdx2++) {
				/* Reserve [0] for MAGIC_PATTERN, and keep BBM info from [1] to [RBA_OFFSET] */
				if (dummyIdx2 < BBM_MAGIC_OFFSET) {
					continue;
				}
				if (rtkNandInfo->pBBM[dummyIdx2].bad_block == 0xFFFF) {
					rtkNandInfo->pBBM[dummyIdx2].BB_die = 0x0550;
					rtkNandInfo->pBBM[dummyIdx2].bad_block = curBlkIdx;
					rtkNandInfo->pBBM[dummyIdx2].RB_die = 0x0AA0;
					rtkNandInfo->pBBM[dummyIdx2].remap_block = mSnandBbmLastRbaBlkIdx + (rtkNandInfo->RBA_OFFSET); /*offset*/
					mSnandBbmLastRbaBlkIdx++;
					break;
				}
			}
		}
	}
	return SUCCESS;
} /* snand_bbm_create */
/**
 snand_bbm_load
 @brief Load S-NAND BBM data struct (BBM_T and V2R_T) from flash memory device to normal memory
 @param[in] rtkNandInfo RTK NAND info
 @return SUCCESS
 @return FAIL
*/
uint32_t
snand_bbm_load(
	rtkNandInfo_t *rtkNandInfo
)
{
	uint32_t tmpIdx = 0;
	uint32_t blkIdx = 0;
	//uint32_t bbmtValid = FALSE;
	//uint32_t v2rtValid = FALSE;
	uint32_t ppb = -1UL; /**< pagePerBlock */
	dbg_printf("%s %s Ln %d.\r\n", __FILE__, __func__, __LINE__);
	if (!rtkNandInfo) {
		return FAIL;
	}
	if (SNAND_BBM_MEMCMP_MATCH != memcmp(rtkNandInfo->magicStr, "RTKN", MAGIC_PATTERN_LEN)) {
		return FAIL;
	}
	if (rtkNandInfo->writesize) {
		ppb = rtkNandInfo->erasesize / rtkNandInfo->writesize;
	} else {
		ppb = 0x40; /* default */
	}
	blkIdx = BBMT_BACKUP_BLOCK_IDX;
	for (tmpIdx = 0; tmpIdx < BBMT_BACKUP_COPY; tmpIdx++) {
		/*
		dbg_printf("load BBM from specified blkPageAddr_BBM (0x%x) to rtkNandInfo->pBuf (0x%x)(sz=0x%x).\r\n",\
		((blkIdx + tmpIdx) * 0x40), \
		rtkNandInfo->pBuf, rtkNandInfo->writebufsize);
		*/
		hal_snand_pio_read(pglob_snafc_adaptor, rtkNandInfo->pBuf, rtkNandInfo->writebufsize, ((blkIdx + tmpIdx)*ppb));
#if 1 /*PhilipHack*/
		//dbg_printf("[ToDo] check BBM magic signature. If FAIL, run snand_bbm_create() flow\r\n");
		if (1) {
			memcpy(rtkNandInfo->pBBM, rtkNandInfo->pBuf, rtkNandInfo->nBBMBufSz); /*HACK: assume nBBMBufSz<writebufsize (pageSize) */
			break;
		}
#else /* ToDo: Normal flow*/
		/* ToDo: Normal flow*/
#endif
		blkIdx++;
	}
	//bbmtValid = TRUE;
	blkIdx = V2RT_BACKUP_BLOCK_IDX;
	for (tmpIdx = 0; tmpIdx < V2RT_BACKUP_COPY; tmpIdx++) {
		/*
		dbg_printf("load V2R from specified blkPageAddr_V2R (0x%x) to rtkNandInfo->pBuf (0x%x)(sz=0x%x).\r\n",\
		((blkIdx + tmpIdx) * 0x40), \
		rtkNandInfo->pBuf, rtkNandInfo->writebufsize);
		*/
		hal_snand_pio_read(pglob_snafc_adaptor, rtkNandInfo->pBuf, rtkNandInfo->writebufsize, ((blkIdx + tmpIdx)*ppb));
#if 1 /*PhilipHack*/
		//dbg_printf("[ToDo] check V2R magic signature. If FAIL, run snand_bbm_create() flow\r\n");
		//dbg_printf("[ToDo] check BBM magic signature. If FAIL, run snand_bbm_create() flow\r\n");
		if (1) {
			memcpy(rtkNandInfo->pV2R, rtkNandInfo->pBuf, rtkNandInfo->nV2RBufSz); /*HACK: assume nV2RBufSz<writebufsize (pageSize) */
			break;
		}
#else /* ToDo: Normal flow*/
		/* ToDo: Normal flow*/
#endif
		blkIdx++;
	}
	//v2rtValid = TRUE;
	dbg_printf("[ToDo] else, BBM and V2R are available\r\n");
	return SUCCESS;
} /* snand_bbm_load */
/**
 snand_bbm_store
 @brief Store S-NAND BBM data struct (BBM_T and V2R_T) from normal memory to flash memory device.
 @param[in] rtkNandInfo RTK NAND info
 @return SUCCESS
 @return FAIL
*/
uint32_t
snand_bbm_store(
	rtkNandInfo_t *rtkNandInfo
)
{
	uint32_t tmpIdx = 0;
	uint32_t blkIdx = 0;
	//uint32_t bbmtSaved = FALSE;
	//uint32_t v2rtSaved = FALSE;
	uint32_t ppb = -1UL; /**< pagePerBlock */
	dbg_printf("%s %s Ln %d.\r\n", __FILE__, __func__, __LINE__);
	if (!rtkNandInfo) {
		return FAIL;
	}
	if (SNAND_BBM_MEMCMP_MATCH != memcmp(rtkNandInfo->magicStr, "RTKN", MAGIC_PATTERN_LEN)) {
		return FAIL;
	}
	if (rtkNandInfo->writesize) {
		ppb = rtkNandInfo->erasesize / rtkNandInfo->writesize;
	} else {
		ppb = 0x40; /* default */
	}
	blkIdx = BBMT_BACKUP_BLOCK_IDX;
	for (tmpIdx = 0; tmpIdx < BBMT_BACKUP_COPY; tmpIdx++) {
		//dbg_printf("blockErase for specified blkPageAddr_BBM (0x%x).\r\n", ((blkIdx+tmpIdx)*ppb) );
		hal_snand_block_erase(pglob_snafc_adaptor, ((blkIdx + tmpIdx)*ppb));
		/*
		dbg_printf("pageWrite BBM info from rtkNandInfo->pBBM (0x%x)(sz=0x%x) into specified blkPageAddr_BBM (0x%x).\r\n",\
		rtkNandInfo->pBBM, rtkNandInfo->writebufsize, \
		((blkIdx + tmpIdx)*ppb));
		*/
		hal_snand_pio_write(pglob_snafc_adaptor, rtkNandInfo->pBBM, rtkNandInfo->writebufsize, ((blkIdx + tmpIdx)*ppb));
#if 1 /*PhilipHack*/
		if (1) {
			break; /* test 1 copy at the first */
		}
#else /* ToDo: Normal flow*/
		/* ToDo: Normal flow*/
#endif
		blkIdx++;
	}
	//bbmtSaved = TRUE;
	blkIdx = V2RT_BACKUP_BLOCK_IDX;
	for (tmpIdx = 0; tmpIdx < V2RT_BACKUP_COPY; tmpIdx++) {
		//dbg_printf("blockErase for specified blkPageAddr_V2R (0x%x).\r\n", ((blkIdx+tmpIdx)*ppb) );
		hal_snand_block_erase(pglob_snafc_adaptor, ((blkIdx + tmpIdx)*ppb));
		/*
		dbg_printf("pageWrite V2R info from rtkNandInfo->pV2R (0x%x)(sz=0x%x) into specified blkPageAddr_V2R (0x%x).\r\n",\
		rtkNandInfo->pV2R, rtkNandInfo->writebufsize, \
		(blkIdx * 0x40));
		*/
		hal_snand_pio_write(pglob_snafc_adaptor, rtkNandInfo->pV2R, rtkNandInfo->writebufsize, ((blkIdx + tmpIdx)*ppb));
#if 1 /*PhilipHack*/
		if (1) {
			break; /* test 1 copy at the first */
		}
#else /* ToDo: Normal flow*/
		/* ToDo: Normal flow*/
#endif
		blkIdx++;
	}
	//v2rtSaved = TRUE;
	dbg_printf("[ToDo] If no error, BBM and V2R are stored in S-NAND flash\r\n");
	return SUCCESS;
} /* snand_bbm_store */
/**
 snand_bbm_isBadBlock
 @brief Check specific flash block in BBM data structure is BAD or GOOD.
 @param[in] blkPageIdx S-NAND's blkPageIdx (page addr, not include column addr)
 @retval 0: SNAND_BBM_GOOD_BLK
 @retval 1: SNAND_BBM_BAD_BLK
 @retval 2: SNAND_BBM_RSVD_BLK
 @retval 3: SNAND_BBM_UNKNOWN_BLK
*/
uint32_t
snand_bbm_isBadBlock(
	rtkNandInfo_t *rtkNandInfo,
	uint32_t blkPageIdx
)
{
	uint32_t blkIdx = 0;
	uint32_t pagePerBlk = 0;
	uint32_t totalBlkCnt = 0;
	uint32_t tmpIdx = 0;
	if ((!rtkNandInfo) || (SNAND_BBM_MEMCMP_MATCH != memcmp(rtkNandInfo->magicStr, "RTKN", MAGIC_PATTERN_LEN))) {
		return SNAND_BBM_UNKNOWN_BLK;
	}
	// blkIdx = blkPageIdx/DEF_SNAND_PAGE_PER_BLOCK;
	pagePerBlk = (rtkNandInfo->erasesize / rtkNandInfo->writesize);
	blkIdx = blkPageIdx / pagePerBlk;
	// if (blkIdx > MAX_BLK_CNT)
	totalBlkCnt = (rtkNandInfo->totalsize / rtkNandInfo->erasesize);
	if (blkIdx > totalBlkCnt) {
		return SNAND_BBM_UNKNOWN_BLK;
	}
	if (blkIdx > rtkNandInfo->RBA_OFFSET) {
		return SNAND_BBM_RSVD_BLK;
	}
	for (tmpIdx = BBM_MAGIC_OFFSET; tmpIdx < rtkNandInfo->RBA_CNT; tmpIdx++) {
		if (rtkNandInfo->pBBM[tmpIdx].bad_block == 0xFFFF) {
			return SNAND_BBM_GOOD_BLK;
		}
		if (rtkNandInfo->pBBM[tmpIdx].bad_block == blkIdx) {
			return SNAND_BBM_BAD_BLK;
		}
	}
	return SNAND_BBM_BAD_BLK;
} /* snand_bbm_isBadBlock */
/**
 snand_bbm_markBad
 @brief Mark specific flash block in BBM data structure as BAD block.
 @param[in] blkPageIdx S-NAND's blkPageIdx (page addr, not include column addr)
 @retval 2: SNAND_BBM_BAD_BLK (already BAD before mark)
 @retval 3: SNAND_BBM_UNKNOWN_BLK
 @return SUCCESS
 @return FAIL
*/
uint32_t
snand_bbm_markBad(
	rtkNandInfo_t *rtkNandInfo,
	uint32_t blkPageIdx
)
{
	uint32_t blkIdx = 0;
	uint32_t tmpIdx = 0;
	uint32_t pagePerBlk = 0; /* ppb */
	uint32_t retVal = FAIL;
	retVal = snand_bbm_isBadBlock(rtkNandInfo, blkPageIdx);
	if (retVal == SNAND_BBM_UNKNOWN_BLK) {
		return SNAND_BBM_UNKNOWN_BLK;
	}
	if (retVal == SNAND_BBM_BAD_BLK) {
		return SNAND_BBM_BAD_BLK;
	}
	if ((!rtkNandInfo) || (SNAND_BBM_MEMCMP_MATCH != memcmp(rtkNandInfo->magicStr, "RTKN", MAGIC_PATTERN_LEN))) {
		return SNAND_BBM_UNKNOWN_BLK;
	}
	pagePerBlk = (rtkNandInfo->erasesize / rtkNandInfo->writesize);
	/*
	  If reach here, mark USED BAD.
	  1. Assign remap_block for BBM
	  2. Mark related entry in V2R table as BAD.
	*/
	blkIdx = blkPageIdx / pagePerBlk;
	for (tmpIdx = BBM_MAGIC_OFFSET; tmpIdx < rtkNandInfo->RBA_CNT; tmpIdx++) {
		if (rtkNandInfo->pBBM[tmpIdx].bad_block == 0xFFFF) {
			/* AVAILABLE "block" in RBA to replace */
			rtkNandInfo->pBBM[tmpIdx].BB_die = 0x0550;
			rtkNandInfo->pBBM[tmpIdx].bad_block = blkIdx;
			rtkNandInfo->pBBM[tmpIdx].RB_die = 0x0AA0;
			rtkNandInfo->pBBM[tmpIdx].remap_block = mSnandBbmLastRbaBlkIdx + (rtkNandInfo->RBA_OFFSET); /*offset*/
			mSnandBbmLastRbaBlkIdx++;
			retVal = SUCCESS;
			break;
		}
	}
	if (tmpIdx == rtkNandInfo->RBA_CNT) {
		return FAIL; /* Not available block in RBA to replace*/
	}
	for (tmpIdx = V2R_MAGIC_OFFSET; tmpIdx < rtkNandInfo->RBA_OFFSET; tmpIdx++) {
		if (rtkNandInfo->pV2R[tmpIdx].block_r == blkIdx) {
			rtkNandInfo->pV2R[tmpIdx].block_r = BBM_USD_BAD_TAG; /*0xFFFE*/
			return SUCCESS;
		}
	}
	return SNAND_BBM_UNKNOWN_BLK;
} /* snand_bbm_markBad */
/**
 snand_bbm_translate
 @brief Translate specific flash blkPageAddr from VIRTUAL ADDRESS to PHYSICAL ADDRESS according to V2R_T and BBM_T data structure.
 @param[in] rtkNandInfo RTK NAND info
 @param[in] blkPageIdx S-NAND's blkPageIdx (page addr, not include column addr)
 @retval 2: SNAND_BBM_BAD_BLK (already BAD before mark)
 @retval 3: SNAND_BBM_UNKNOWN_BLK
 @return the blkPageAddr after translate
*/
uint32_t
snand_bbm_translate(
	rtkNandInfo_t *rtkNandInfo,
	uint32_t blkPageIdx
)
{
	uint32_t blkIdx = 0;
	uint32_t pageIdx = 0;
	uint32_t tmpIdx = 0;
	uint32_t pagePerBlk = 0; /* ppb */
	uint32_t retVal = FAIL;
	tmpIdx = snand_bbm_isBadBlock(rtkNandInfo, blkPageIdx);
	if (tmpIdx == SNAND_BBM_UNKNOWN_BLK) {
		return SNAND_BBM_UNKWNON_TAG;
	}
	if ((!rtkNandInfo) || (SNAND_BBM_MEMCMP_MATCH != memcmp(rtkNandInfo->magicStr, "RTKN", MAGIC_PATTERN_LEN))) {
		return SNAND_BBM_UNKNOWN_BLK;
	}
	pagePerBlk = (rtkNandInfo->erasesize / rtkNandInfo->writesize);
	/*
	  If reach here, start translate.
	  1. lookup blkIdx for BBM.bad_block. If found, use BBM.remap_block as blkIdx to translate to real blkPageIdx.
	  2. lookup blkIdx for V2R.block_r. If found, use V2R.block_ras blkIdx to translate to real blkPageIdx.
	  3. If NOT found, return SNAND_BBM_UNKWNON_TAG.
	*/
	blkIdx = blkPageIdx / pagePerBlk;
	pageIdx = blkPageIdx % pagePerBlk;
	for (tmpIdx = BBM_MAGIC_OFFSET; tmpIdx < rtkNandInfo->RBA_CNT; tmpIdx++) {
		if (rtkNandInfo->pBBM[tmpIdx].bad_block == 0xFFFF) {
			break;
		}
		if (rtkNandInfo->pBBM[tmpIdx].bad_block == blkIdx) {
			blkIdx = rtkNandInfo->pBBM[tmpIdx].remap_block;
			retVal = (blkIdx * pagePerBlk) + pageIdx;
			return retVal;
		}
	}
	for (tmpIdx = V2R_MAGIC_OFFSET; tmpIdx < rtkNandInfo->RBA_OFFSET; tmpIdx++) {
		if (rtkNandInfo->pV2R[tmpIdx].block_r == blkIdx) {
			retVal = (blkIdx * pagePerBlk) + pageIdx;
			return retVal;
		}
	}
	return SNAND_BBM_UNKWNON_TAG;
} /* snand_bbm_translate */
/* ======================================== */
/* For access S-NAND flash device           */
/* ======================================== */
/**
 0: READ page data via 1-bit mode
 1: READ page data via 4-bit mode (default)
 */
#define SUPPORT_QUAD_BIT_MODE_R (1)
/**
 0: WRITE page data via 1-bit mode
 1: WRITE page data via 4-bit mode (default)
 */
#define SUPPORT_QUAD_BIT_MODE_W (1)
/**
 0: Access page data via PIO mode
 1: Access page data via DMA mode (default)
 */
#define DEFAULT_DATA_ACCESS_VIA_DMA (1)
hal_snafc_adaptor_t mMBedAmebaPro2SnafcAdaptor = {
	.irq_handle = { .irq_fun = NULL, .data = NULL, .irq_num = 0, .priority = 0, },
	.initVal[SNAFC_SPEED_SEL_0].l = 0x00001043, /* Est. sck=12.50 MHz, with pipe_lat=0 (0..3) */
	.initVal[SNAFC_SPEED_SEL_1].l = 0x00001023, /* Est. sck=20.83 MHz, with pipe_lat=0 (0..3) */
	.initVal[SNAFC_SPEED_SEL_2].l = 0x00001013, /* Est. sck=31.25 MHz, with pipe_lat=0 (0..3) */
	.initVal[SNAFC_SPEED_SEL_3].l = 0x00001103, /* Est. sck=62.50 MHz, with pipe_lat=1 (0..3) */
	.clkSel = SNAFC_SPEED_SEL_3,
	.pinmuxSel = SnafcPinmuxCfg_0,
	.maxCtrlRdyCnt = 0x1000 /*VRFY_SNAFC_CTRLR_RDY_CNT*/,
	.maxDmaRdyCnt = 0x10000 /*VRFY_SNAFC_DMA_RDY_CNT*/,
	.maxWaitOipCnt = 0x4000 /*VRFY_SNAND_OIP_TIMEOUT_CNT*/,
	.dma_en = 1,
	.col_addr = 0,
	.funcWaitSnandReady = NULL,
	.funcBlockProtectNone = NULL,
	.funcBlockProtectAll = NULL,
	.funcEnQuadSpiMode = NULL,
	.funcDisQuadSpiMode = NULL,
	.funcChkEccSts = NULL,
	.funcChkPgmSts = NULL,
	.snand_cmd_info.w_cmd_cycle = (1),
	.snand_cmd_info.w_cmd = SNAND_PROGRAM_LOAD_OP,
	.snand_cmd_info.w_addr_cycle = (3),
	.snand_cmd_info.w_addr_io = SNAFC_SIO_WIDTH,
	.snand_cmd_info.w_data_io = SNAFC_SIO_WIDTH,
	.snand_cmd_info.r_cmd_cycle = (1),
	.snand_cmd_info.r_cmd = SNAND_NORMAL_READ_OP,
	.snand_cmd_info.r_addr_cycle = (3),
	.snand_cmd_info.r_addr_io = SNAFC_SIO_WIDTH,
	.snand_cmd_info.r_data_io = SNAFC_SIO_WIDTH,
};
/* Default BUS setting for WRITE */
#define SNAND_API_DEF_W_CMD_CYCLE (3)
#define SNAND_API_DEF_W_CMD_IOWIDTH (SNAFC_SIO_WIDTH)
#if SUPPORT_QUAD_BIT_MODE_W
#define SNAND_API_DEF_W_CMD_OP (SNAND_PROGRAM_LOAD_X4_OP) /*@@ sa enum snandBusOpCmd_e in rtl8735b_snand.h */
#define SNAND_API_DEF_W_DAT_IOWIDTH (SNAFC_QIO_WIDTH)     /*@@ sa enum snandBusOpCmd_e in rtl8735b_snand.h */
#else /* !SUPPORT_QUAD_BIT_MODE_W, using 1-bit mode as default */
#define SNAND_API_DEF_W_CMD_OP (SNAND_PROGRAM_LOAD_OP)    /*@@ sa enum snandBusOpCmd_e in rtl8735b_snand.h */
#define SNAND_API_DEF_W_DAT_IOWIDTH (SNAFC_SIO_WIDTH)     /*@@ sa enum snandBusOpCmd_e in rtl8735b_snand.h */
#endif
/* Default BUS setting for READ */
#define SNAND_API_DEF_R_CMD_CYCLE (3)
#define SNAND_API_DEF_R_CMD_IOWIDTH (SNAFC_SIO_WIDTH)
#if SUPPORT_QUAD_BIT_MODE_R
#define SNAND_API_DEF_R_CMD_OP (SNAND_FAST_READ_X4_OP)    /*@@ sa enum snandBusOpCmd_e in rtl8735b_snand.h */
#define SNAND_API_DEF_R_DAT_IOWIDTH (SNAFC_QIO_WIDTH)     /*@@ sa enum snafcBusWidth_e in rtl8735b_snand.h */
#else /* !SUPPORT_QUAD_BIT_MODE_W, using 1-bit mode as default */
#define SNAND_API_DEF_R_CMD_OP (SNAND_NORMAL_READ_OP)     /*@@ sa enum snandBusOpCmd_e in rtl8735b_snand.h */
#define SNAND_API_DEF_R_DAT_IOWIDTH (SNAFC_SIO_WIDTH)     /*@@ sa enum snafcBusWidth_e in rtl8735b_snand.h */
#endif
snand_bus_cfg_t mMBedAmebaPro2SnafcCmd = {
	.w_cmd_cycle = 1,
	.w_cmd = SNAND_API_DEF_W_CMD_OP,
	.w_addr_cycle = SNAND_API_DEF_W_CMD_CYCLE,
	.w_addr_io = SNAND_API_DEF_W_CMD_IOWIDTH,
	.w_data_io = SNAND_API_DEF_W_DAT_IOWIDTH,
	.r_cmd_cycle = 1,
	.r_cmd = SNAND_API_DEF_R_CMD_OP,
	.r_addr_cycle = SNAND_API_DEF_R_CMD_CYCLE,
	.r_addr_io = SNAND_API_DEF_R_CMD_IOWIDTH,
	.r_data_io = SNAND_API_DEF_R_DAT_IOWIDTH,
};
/**
  * @brief  Lock resource before flash processing
  * @param  none
  * @retval  none
  * @note  This api can be used to define IC specified operations before flash processing. Please check the project about its implementation.
  */
__weak void snand_resource_lock(void);
/**
  * @brief  Unlock resource after flash processing
  * @param  none
  * @retval  none
  * @note  This api can be used to define IC specified operations after flash processing. Please check the project about its implementation.
  */
__weak void snand_resource_unlock(void);
/**
  * @brief  Init Flash Pinmux
  * @param  obj: address of the flash object
  * @param  snafcPinmuxSel_t: the pinmux selection of the flash
  * @retval   none
  */
void snand_pinmux_init(snand_t *obj, snafcPinmuxSel_t pin_sel)
{
}
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
/**
 matching_for_spi_rdid
 @param[in] rdid S-NAND flash device ID returned by S-NAND flash device READID
 @retval NULL: NOT FOUND (No previous definition for specified ID)
 @return pointer to struct nand_chip_param_T
*/
static nand_chip_param_T *
matching_for_spi_rdid(
	uint32_t rdid
)
{
	uint32_t tmpIdx = 0;
	uint32_t tmpRdId = 0;
	if (!nand_chip_id) {
		/* (GLOBAL VARIABLE) NOT FOUND */
		return NULL;
	}
	for (tmpIdx = 0; tmpIdx < (sizeof(nand_chip_id) / sizeof(nand_chip_param_T)); tmpIdx++) {
		if (nand_chip_id[tmpIdx].id_len == 2) {
			tmpRdId = (rdid & 0xFFFF);
		} else if (nand_chip_id[tmpIdx].id_len == 3) {
			tmpRdId = (rdid & 0xFFFFFF);
		} else if (nand_chip_id[tmpIdx].id_len == 4) {
			tmpRdId = (rdid & 0xFFFFFFFF);
		} else {
			return NULL;
		}
		if (nand_chip_id[tmpIdx].id == tmpRdId) {
			return &nand_chip_id[tmpIdx];
		}
	}
	return NULL;
} /* matching_for_spi_rdid */
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
/**
  * @brief  De-Init S-NAND Flash
  * @param  obj: address of the flash object
  * @retval   none
  */
void snand_deinit(snand_t *obj)
{
	hal_snafc_adaptor_t *ptPro2SnafcAdator = &mMBedAmebaPro2SnafcAdaptor;
	hal_snand_deinit(ptPro2SnafcAdator);
	pglob_snafc_adaptor = NULL;
	obj->psnand_adapter = NULL;
}
/**
  * @brief  Init S-NAND Flash
  * @param  obj: address of the flash object
  * @retval   none
  */
void snand_init(snand_t *obj)
{
	if (pglob_snafc_adaptor == NULL) {
		hal_snafc_adaptor_t *ptPro2SnafcAdator;
		uint32_t tDevId;
#if 0 /* DEBUG only */
		uint32_t tCmd, tRetVal, tData;
#endif
		ptPro2SnafcAdator = &mMBedAmebaPro2SnafcAdaptor;
		memcpy((void *) & (ptPro2SnafcAdator->snand_cmd_info), (void *) &mMBedAmebaPro2SnafcCmd, sizeof(snand_bus_cfg_t));
		hal_snand_init(ptPro2SnafcAdator);
		tDevId = hal_snand_read_id(ptPro2SnafcAdator);
#if 0 /* DEBUG only */
		tCmd = 0xa0;
		tRetVal = hal_snand_get_status(ptPro2SnafcAdator, tCmd);
		dbg_printf("getf 0x%02x return 0x%x.\r\n", tCmd, tRetVal);
		tCmd = 0xb0;
		tRetVal = hal_snand_get_status(ptPro2SnafcAdator, tCmd);
		dbg_printf("getf 0x%02x return 0x%x.\r\n", tCmd, tRetVal);
		tCmd = 0xc0;
		tRetVal = hal_snand_get_status(ptPro2SnafcAdator, tCmd);
		dbg_printf("getf 0x%02x return 0x%x.\r\n", tCmd, tRetVal);
#endif
		if (tDevId == 0) {
			DBG_SNAND_ERR("snand_init err (DevId=0)\r\n");
		} else {
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
			uint32_t pageBufSzB;
			uint32_t spareBufSzB;
			uint32_t pagesPerBlk;
			uint32_t totalBlkCnt;
			uint32_t rbaPercentage = DEF_RESERVED_BLOCK_AREA_PERCENTAGE;
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
			pglob_snafc_adaptor = ptPro2SnafcAdator;
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
			mSnandChipParam = matching_for_spi_rdid(tDevId);
			if (!mSnandChipParam) {
				dbg_printf("NOT FOUND for SNAND RDID 0x%x. Using Default value.\r\n", tDevId);
				pageBufSzB = DEF_PAGE_SIZE;
				spareBufSzB = DEF_SPARE_SIZE;
				pagesPerBlk = DEF_SNAND_PAGE_PER_BLOCK;
				totalBlkCnt = DEF_TOTAL_BLK_CNT;
			} else {
				pageBufSzB = mSnandChipParam->pagesize;
				spareBufSzB = mSnandChipParam->oobsize;
				pagesPerBlk = mSnandChipParam->num_chunk_per_block;
				totalBlkCnt = (mSnandChipParam->num_block * mSnandChipParam->dienum);
			}
			mSnandApiNandInfo.writesize = (pageBufSzB); /* pageSize (Bytes) */
			mSnandApiNandInfo.erasesize = (mSnandApiNandInfo.writesize) * pagesPerBlk; /* blockSize (Bytes) */
			mSnandApiNandInfo.totalsize = (mSnandApiNandInfo.erasesize) * totalBlkCnt; /* flashDevSize (Bytes) */
			mSnandApiNandInfo.writebufsize = (pageBufSzB + spareBufSzB); /* write buffer size, the same as pageSize for most of S-NAND flash device */
			if (mSnandApiNandInfo.pBuf) {
				free(mSnandApiNandInfo.pBuf);
				mSnandApiNandInfo.pBuf = NULL;
			}
			mSnandApiNandInfo.pBuf = malloc(mSnandApiNandInfo.writebufsize);
			if (!mSnandApiNandInfo.pBuf) {
				tRetVal = FAIL;
				dbg_printf("Error: %s Ln %d. malloc(0x%x) return NULL.\r\n", __FILE__, __LINE__, mSnandApiNandInfo.writebufsize);
				goto _snand_api_bbm_init_release;
			}
			mSnandApiNandInfo.RBA_PERCENT = DEF_RESERVED_BLOCK_AREA_PERCENTAGE; /* It means, reserved 5% of totalBlkCnt as Reserved Block Area (RBA) */
			mSnandApiNandInfo.RBA_CNT = totalBlkCnt * (mSnandApiNandInfo.RBA_PERCENT) / 100; /* RBA block cout. */
			mSnandApiNandInfo.RBA_OFFSET = totalBlkCnt - (mSnandApiNandInfo.RBA_CNT); /* Start block index for RBA. (RBA located in the end of flash device) */
			if (mSnandApiNandInfo.pBBM) {
				free(mSnandApiNandInfo.pBBM);
				mSnandApiNandInfo.pBBM = NULL;
			}
			mSnandApiNandInfo.nBBMBufSz = sizeof(BB_t) * (mSnandApiNandInfo.RBA_CNT + 1); /*Put MAGIC_PATTERN in array[0] */
			mSnandApiNandInfo.pBBM = malloc(mSnandApiNandInfo.nBBMBufSz);
			if (!mSnandApiNandInfo.pBBM) {
				tRetVal = FAIL;
				dbg_printf("Error: %s Ln %d. malloc(0x%x) return NULL.\r\n", __FILE__, __LINE__, mSnandApiNandInfo.nBBMBufSz);
				goto _snand_api_bbm_init_release;
			}
			if (mSnandApiNandInfo.pV2R) {
				free(mSnandApiNandInfo.pV2R);
				mSnandApiNandInfo.pV2R = NULL;
			}
			mSnandApiNandInfo.nV2RBufSz = sizeof(BB_v2r) * (totalBlkCnt - mSnandApiNandInfo.RBA_CNT + 1); /*Put MAGIC_PATTERN in array[0] */
			mSnandApiNandInfo.pV2R = malloc(mSnandApiNandInfo.nV2RBufSz);
			if (!mSnandApiNandInfo.pV2R) {
				tRetVal = FAIL;
				dbg_printf("Error: %s Ln %d. malloc(0x%x) return NULL.\r\n", __FILE__, __LINE__, mSnandApiNandInfo.nV2RBufSz);
				goto _snand_api_bbm_init_release;
			}
			tRetVal = snand_bbm_init(&mSnandApiNandInfo);
			if (tRetVal != SUCCESS) {
				tRetVal = FAIL;
				dbg_printf("Error: %s Ln %d. bbm_init(struct rtkNandInfo_s*) FAIL.\r\n", __FILE__, __LINE__);
				rtkNandInfo_dump(&mSnandApiNandInfo);
				goto _snand_api_bbm_init_release;
			}
			if (tRetVal != SUCCESS) {
_snand_api_bbm_init_release:
				if (mSnandApiNandInfo.pBBM) {
					free(mSnandApiNandInfo.pBBM);
					mSnandApiNandInfo.pBBM = NULL;
				}
				if (mSnandApiNandInfo.pV2R) {
					free(mSnandApiNandInfo.pV2R);
					mSnandApiNandInfo.pV2R = NULL;
				}
				if (mSnandApiNandInfo.pBuf) {
					free(mSnandApiNandInfo.pBuf);
					mSnandApiNandInfo.pBuf = NULL;
				}
			}
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
		}
	}
	obj->psnand_adapter = pglob_snafc_adaptor;
}
/**
  * @brief  Get flash ID (command: 0x9F), works in SPI mode only.
  * @param  obj: Flash object define in application software.
  * @param  buf: Pointer to a byte array to save the readback ID.
  * @param  len: Specifies the length of the buf. It should be 3.
  * @retval -1: Fail, len: Succeed.
  */
int snand_read_id(snand_t *obj, uint8_t *buf, uint8_t len)
{
	hal_snafc_adaptor_t *ptPro2SnafcAdator;
	u8 index;
	snand_init(obj);
	ptPro2SnafcAdator = (obj->psnand_adapter);
	if (len < 3) {
		DBG_SNAND_ERR("ID length should be >= 3\r\n");
	}
	if ((ptPro2SnafcAdator->devId[0] == 0x0)
		|| (ptPro2SnafcAdator->devId[0] == 0xFF)) {
		DBG_SNAND_ERR("Invalide ID\r\n");
		return -1;
	} else {
		for (index = 0; index < 3; index++) {
			buf[index] = ptPro2SnafcAdator->devId[index];
		}
	}
	return len;
}
/**
  * @brief  Erase flash block, usually 1 block = 64K bytes
    Please refer to flash data sheet to confirm the actual block size.
    The actual address which being erased always aligned with block size.
  * @param  address: Specifies the starting address to be erased.
  * @retval SUCCESS, FAIL
  */
int snand_erase_block(snand_t *obj, uint32_t address)
{
	uint32_t tRetVal = FAIL;
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
	uint32_t tVirtualAddr = address;
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
	snand_init(obj);
	snand_resource_lock();
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
	tRetVal = snand_bbm_translate(&mSnandApiNandInfo, tVirtualAddr /* blkPageIdx */);
	if (tRetVal == SNAND_BBM_UNKWNON_TAG) {
		snand_resource_unlock();
		tRetVal = FAIL;
		return tRetVal;
	}
	address = tRetVal; /* translate the blkPageIdx from virtual address (VA) to phyiscal address (PA) */
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
	hal_snand_block_erase((obj->psnand_adapter), address);
	tRetVal = hal_snand_get_status(NULL, 0xc0);
	if (tRetVal & (1 << 2) /*E_FAIL*/) {
		DBG_SNAND_ERR("%s: E_FAIL (0x%x) for block erase 0x%x.\r\n", __FUNCTION__, tRetVal, address);
		tRetVal = FAIL;
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
		snand_bbm_markBad(&mSnandApiNandInfo, tVirtualAddr /* blkPageIdx */);
		snand_bbm_store(&mSnandApiNandInfo);
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
	} else {
		tRetVal = SUCCESS;
	}
	snand_resource_unlock();
	return tRetVal;
}
/**
  * @brief  Read a stream of data from specified address vai user mode
  * @param  obj: Specifies the parameter of flash object.
  * @param  address: Specifies the address to be read.
  * @param  len: Specifies the length of the data to read.
  * @param  data: Specified the address to save the readback data.
  * @retval   SUCCESS, FAIL
  */
int  snand_page_read(snand_t *obj, uint32_t address, uint32_t Length, uint8_t *data)
{
	uint32_t tRetVal = FAIL;
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
	uint32_t tVirtualAddr = address;
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
	snand_init(obj);
	snand_resource_lock();
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
	tRetVal = snand_bbm_translate(&mSnandApiNandInfo, tVirtualAddr /* blkPageIdx */);
	if (tRetVal == SNAND_BBM_UNKWNON_TAG) {
		snand_resource_unlock();
		tRetVal = FAIL;
		return tRetVal;
	}
	address = tRetVal; /* translate the blkPageIdx from virtual address (VA) to phyiscal address (PA) */
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
#if DEFAULT_DATA_ACCESS_VIA_DMA
	DCACHE_WB_BY_ADDR((uint32_t *)(data), Length);
	hal_snand_dma_read((obj->psnand_adapter), data, Length, address);
	DCACHE_INV_BY_ADDR((uint32_t *)(data), Length);
#else
	hal_snand_pio_read((obj->psnand_adapter), data, Length, address);
#endif
	tRetVal = hal_snand_get_status(NULL, 0xc0);
	if ((0x20 /*CANNOT FIX*/ == (tRetVal & 0x30)) ||
		(0x30 /*RSVD*/ == (tRetVal & 0x30))) {
		DBG_SNAND_ERR("%s: ECC error (0x%x) for page read 0x%x.\r\n", __FUNCTION__, tRetVal, address);
		tRetVal = FAIL;
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
		snand_bbm_markBad(&mSnandApiNandInfo, tVirtualAddr /* blkPageIdx */);
		snand_bbm_store(&mSnandApiNandInfo);
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
	} else {
		tRetVal = SUCCESS;
	}
	snand_resource_unlock();
	return tRetVal;
}
/*
Function Description:
This function performans the same functionality as the function snand_stream_write.
It enhances write performance by reducing overheads.
Users can use either of functions depending on their needs.
* @brief  Write a stream of data to specified address
* @param  obj: Specifies the parameter of flash object.
* @param  address: Specifies the address to be programmed.
* @param  Length: Specifies the length of the data to write.
* @param  data: Specified the pointer of the data to be written.
          If the address is in the flash, full address is required, i.e. SPI_FLASH_BASE + Offset
* @retval SUCCESS, FAIL
*/
int snand_page_write(snand_t *obj, uint32_t address, uint32_t Length, uint8_t *data)
{
	uint32_t tRetVal = FAIL;
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
	uint32_t tVirtualAddr = address;
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
	snand_init(obj);
	snand_resource_lock();
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
	tRetVal = snand_bbm_translate(&mSnandApiNandInfo, tVirtualAddr /* blkPageIdx */);
	if (tRetVal == SNAND_BBM_UNKWNON_TAG) {
		snand_resource_unlock();
		tRetVal = FAIL;
		return tRetVal;
	}
	address = tRetVal; /* translate the blkPageIdx from virtual address (VA) to phyiscal address (PA) */
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
#if DEFAULT_DATA_ACCESS_VIA_DMA
	DCACHE_WB_BY_ADDR((uint32_t *)(data), Length);
	hal_snand_dma_write((obj->psnand_adapter), data, Length, address);
#else
	hal_snand_pio_write((obj->psnand_adapter), data, Length, address);
#endif
	tRetVal = hal_snand_get_status(NULL, 0xc0);
	if (tRetVal & (1 << 3) /*P_FAIL*/) {
		DBG_SNAND_ERR("%s: P_FAIL (0x%x) for page write 0x%x.\r\n", __FUNCTION__, tRetVal, address);
		tRetVal = FAIL;
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
		snand_bbm_markBad(&mSnandApiNandInfo, tVirtualAddr /* blkPageIdx */);
		snand_bbm_store(&mSnandApiNandInfo);
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
	} else {
		tRetVal = SUCCESS;
	}
	snand_resource_unlock();
	return tRetVal;
}
/*
Function Description:
This function aims to read the value of the status register 1.
It can be used to check the current status of the flash including protected region, busy state etc.
Please refer to the datatsheet of flash for more details of the content of status register.
* @brief  Read Status register to check flash status
* @param  obj: Specifies the parameter of flash object.
* @param  offset: Specifies which register offset users like to access
* @retval status: the value of status register.
*/
int snand_get_feature(snand_t *obj, uint32_t offset)
{
	hal_snafc_adaptor_t *ptPro2SnafcAdator;
	u8 status = 0;
	snand_init(obj);
	ptPro2SnafcAdator = (obj->psnand_adapter);
	snand_resource_lock();
	status = hal_snand_get_status(ptPro2SnafcAdator, offset);
	snand_resource_unlock();
	return status;
}
/*
Function Description:
This function aims to set the value of the status register 1.
It can be used to protect partial flash region.
Please refer to the datatsheet of flash for more details of the content of status register.
The block protected area and the corresponding control bits are provided in the flash datasheet.
* @brief  Set Status register to enable desired operation
* @param  obj: Specifies the parameter of flash object.
* @param  offset: Specifies which register offset users like to access
* @param  data: Specifies which bit users like to set
   ex: if users want to set the third bit, data = 0x8.
* @retval SUCCESS, FAIL
*/
int snand_set_feature(snand_t *obj, uint32_t offset, uint32_t data)
{
	hal_snafc_adaptor_t *ptPro2SnafcAdator;
	snand_init(obj);
	ptPro2SnafcAdator = (obj->psnand_adapter);
	snand_resource_lock();
	hal_snand_set_status(ptPro2SnafcAdator, offset, (u8)data);
	snand_resource_unlock();
	return SUCCESS;
}
/*
Function Description:
This function aims to get the density of the flash.
* @brief  Get flash density (unit: Byte)
* @param  obj: Specifies the parameter of flash object.
* @retval flash size (unit: Byte)
*/
uint32_t snand_get_size(snand_t *obj)
{
	uint32_t size = 0;
	snand_init(obj);
#if 0 /* FIXME */
	hal_snafc_adaptor_t *ptPro2SnafcAdator;
	uint32_t size_id;
	ptPro2SnafcAdator = (obj->psnand_adapter);
	size_id = ptPro2SnafcAdator->flash_id[2];
	size = ((1 << size_id) >> 20) * 8;
#else /* Hack */
	size = 1024; /* Hard-code test */
#endif
	dbg_printf("Flash Size = %d Mbit\r\n", size);
	return size;
}
/*
 Using this API to faster SPI_CLK
*/
void snand_clk_faster(void)
{
	hal_snafc_adaptor_t *ptPro2SnafcAdator;
	ptPro2SnafcAdator = &mMBedAmebaPro2SnafcAdaptor;
	if (ptPro2SnafcAdator->clkSel < SNAFC_SPEED_SEL_3) {
		ptPro2SnafcAdator->clkSel++;
		snand_resource_lock();
		if (pglob_snafc_adaptor != NULL) {
			hal_snand_deinit(ptPro2SnafcAdator);
			hal_snand_init(ptPro2SnafcAdator); /* Restart with faster clkSel */
		} else {
			hal_snand_init(ptPro2SnafcAdator); /* Init with faster clkSel */
			pglob_snafc_adaptor = ptPro2SnafcAdator;
		}
		snand_resource_unlock();
	}
}
/*
 Using this API to slower SPI_CLK
*/
void snand_clk_slower(void)
{
	hal_snafc_adaptor_t *ptPro2SnafcAdator;
	ptPro2SnafcAdator = &mMBedAmebaPro2SnafcAdaptor;
	if ((ptPro2SnafcAdator->clkSel <= SNAFC_SPEED_SEL_3) && (ptPro2SnafcAdator->clkSel > SNAFC_SPEED_SEL_0)) {
		ptPro2SnafcAdator->clkSel--;
		snand_resource_lock();
		if (pglob_snafc_adaptor != NULL) {
			hal_snand_deinit(ptPro2SnafcAdator);
			hal_snand_init(ptPro2SnafcAdator); /* Restart with slower clkSel */
		} else {
			hal_snand_init(ptPro2SnafcAdator); /* Init with slower clkSel */
			pglob_snafc_adaptor = ptPro2SnafcAdator;
		}
		snand_resource_unlock();
	}
}
/***********************************************************************************
The following functions are flash dependent setting.
Plase refer to data sheets of the target flash.
************************************************************************************/
#define SNAND_QUAD_ENABLE_FLAG (1<<0)
/*
 Using set_feature OPCMD to ask S-NAND device goes into QUAD-bit mode
 And, change SNAFC's CMD from SIO (SNAND_PROGRAM_LOAD_OP, and SNAND_NORMAL_READ_OP) to QIO (SNAND_PROGRAM_LOAD_X4_OP, and SNAND_FAST_READ_X4_OP)
*/
void snand_set_quad_bit_mode(void)
{
	uint32_t tVal;
	hal_snafc_adaptor_t *ptPro2SnafcAdator;
	ptPro2SnafcAdator = &mMBedAmebaPro2SnafcAdaptor;
	if (pglob_snafc_adaptor == NULL) {
		snand_resource_lock();
		hal_snand_init(ptPro2SnafcAdator);
		pglob_snafc_adaptor = ptPro2SnafcAdator;
		snand_resource_unlock();
	}
	snand_resource_lock();
	tVal = hal_snand_get_status(ptPro2SnafcAdator, 0xB0);
	if ((tVal & SNAND_QUAD_ENABLE_FLAG) != SNAND_QUAD_ENABLE_FLAG) {
		tVal |= SNAND_QUAD_ENABLE_FLAG;
		hal_snand_set_status(pglob_snafc_adaptor, 0xB0, tVal);
		ptPro2SnafcAdator->snand_cmd_info.w_cmd = SNAND_PROGRAM_LOAD_X4_OP;
		ptPro2SnafcAdator->snand_cmd_info.w_data_io = SNAFC_QIO_WIDTH;
		ptPro2SnafcAdator->snand_cmd_info.r_cmd = SNAND_FAST_READ_X4_OP;
		ptPro2SnafcAdator->snand_cmd_info.r_data_io = SNAFC_QIO_WIDTH;
	}
	snand_resource_unlock();
}
/*
 Change SNAFC's CMD from QIO (SNAND_PROGRAM_LOAD_X4_OP, and SNAND_FAST_READ_X4_OP) to SIO (SNAND_PROGRAM_LOAD_OP, and SNAND_NORMAL_READ_OP).
 (Keep flash device's feature setting as previous)
*/
void snand_unset_quad_bit_mode(void)
{
	hal_snafc_adaptor_t *ptPro2SnafcAdator;
	ptPro2SnafcAdator = &mMBedAmebaPro2SnafcAdaptor;
	if (pglob_snafc_adaptor == NULL) {
		snand_resource_lock();
		hal_snand_init(ptPro2SnafcAdator);
		pglob_snafc_adaptor = ptPro2SnafcAdator;
		snand_resource_unlock();
	}
	snand_resource_lock();
	ptPro2SnafcAdator->snand_cmd_info.w_cmd = SNAND_PROGRAM_LOAD_OP;
	ptPro2SnafcAdator->snand_cmd_info.w_data_io = SNAFC_SIO_WIDTH;
	ptPro2SnafcAdator->snand_cmd_info.r_cmd = SNAND_NORMAL_READ_OP;
	ptPro2SnafcAdator->snand_cmd_info.r_data_io = SNAFC_SIO_WIDTH;
	snand_resource_unlock();
}
/***********************************************************************************
The following functions are compatile with Winbond flash only.
But not all Winbond flash supports these functions,
plase refer to data sheets of the target flashes.
************************************************************************************/
/*
0: Set status register 1 to enble write protect feature
1: Enable individual sector / block protect feature
*/
void snand_set_lock_mode(uint32_t mode)
{
	if (pglob_snafc_adaptor == NULL) {
		hal_snafc_adaptor_t *ptPro2SnafcAdator;
		ptPro2SnafcAdator = &mMBedAmebaPro2SnafcAdaptor;
		hal_snand_init(ptPro2SnafcAdator);
		pglob_snafc_adaptor = ptPro2SnafcAdator;
	}
	snand_resource_lock();
	hal_snand_set_status(pglob_snafc_adaptor, 0xA0, mode);
	snand_resource_unlock();
}
/*Lock whole flash chip*/
void snand_global_lock(void)
{
	if (pglob_snafc_adaptor == NULL) {
		hal_snafc_adaptor_t *ptPro2SnafcAdator;
		ptPro2SnafcAdator = &mMBedAmebaPro2SnafcAdaptor;
		hal_snand_init(ptPro2SnafcAdator);
		pglob_snafc_adaptor = ptPro2SnafcAdator;
	}
	snand_resource_lock();
	hal_snand_set_status(pglob_snafc_adaptor, 0xA0, 0x38);
	snand_resource_unlock();
}
/*Unlock whole flash chip*/
void snand_global_unlock(void)
{
	if (pglob_snafc_adaptor == NULL) {
		hal_snafc_adaptor_t *ptPro2SnafcAdator;
		ptPro2SnafcAdator = &mMBedAmebaPro2SnafcAdaptor;
		hal_snand_init(ptPro2SnafcAdator);
		pglob_snafc_adaptor = ptPro2SnafcAdator;
	}
	snand_resource_lock();
	hal_snand_set_status(pglob_snafc_adaptor, 0xA0, 0x00);
	snand_resource_unlock();
}
/**
  * @brief  Using Winbond's CONTINUE PAGE READ mode to read data
  * @param  obj: Specifies the parameter of flash object.
  * @param  address: Specifies the page address to be read. (Suggest as start page of each block)
  * @param  len: Specifies the length of the data to read. (Suggest as (pageSize*pageCount) of whole block)
  * @param  data: Specified the address to save the readback data.
  * @retval   SUCCESS, FAIL
  */
int  snand_winbond_cont_read(snand_t *obj, uint32_t address, uint32_t Length, uint8_t *data)
{
	uint32_t tRetVal = FAIL;
#define WINBOND_BUF_MODE_EN (1<<3)
	uint32_t tSR2_BUF0, tSR2_BUF1;
#define EN_TIME_MEASURE (0)
#if EN_TIME_MEASURE
	uint32_t time1, time2;
#endif
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
	uint32_t tVirtualAddr = address;
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
	snand_init(obj);
	snand_resource_lock();
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
	tRetVal = snand_bbm_translate(&mSnandApiNandInfo, tVirtualAddr /* blkPageIdx */);
	if (tRetVal == SNAND_BBM_UNKWNON_TAG) {
		snand_resource_unlock();
		tRetVal = FAIL;
		return tRetVal;
	}
	address = tRetVal; /* translate the blkPageIdx from virtual address (VA) to phyiscal address (PA) */
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
	tRetVal = hal_snand_get_status(pglob_snafc_adaptor, 0xB0);
	tSR2_BUF1 = tRetVal; // W25N01GVxxxG default BUF=1
	tSR2_BUF0 = tSR2_BUF1 & ~(WINBOND_BUF_MODE_EN);
	hal_snand_set_status(pglob_snafc_adaptor, 0xB0, tSR2_BUF0); // Set BUF=0 (Enter CONTINUE READ mode)
	DCACHE_WB_BY_ADDR((uint32_t *)(data), Length);
#if EN_TIME_MEASURE
	time1 = hal_read_curtime_us();
#endif
	tRetVal = hal_snand_dma_cont_read((obj->psnand_adapter), data, Length, address);
#if EN_TIME_MEASURE
	time2 = hal_read_curtime_us();
	dbg_printf(" takes %d usec. (%d - %d)\r\n", (time2 - time1), time2, time1);
#endif
	DCACHE_INV_BY_ADDR((uint32_t *)(data), Length);
	tRetVal = hal_snand_get_status(NULL, 0xc0);
	if ((0x20 /*CANNOT FIX*/ == (tRetVal & 0x30)) ||
		(0x30 /*RSVD*/ == (tRetVal & 0x30))) {
		DBG_SNAND_ERR("%s: ECC error (0x%x) for page read 0x%x.\r\n", __FUNCTION__, tRetVal, address);
		tRetVal = FAIL;
#if EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW
		snand_bbm_markBad(&mSnandApiNandInfo, tVirtualAddr /* blkPageIdx */);
		snand_bbm_store(&mSnandApiNandInfo);
#endif /* EMBED_BAD_BLOCK_LOOKUP_AND_TRANSLATE_IN_API_FLOW */
	} else {
		tRetVal = SUCCESS;
	}
	hal_snand_set_status(pglob_snafc_adaptor, 0xB0, tSR2_BUF1); // Set BUF=1 (Exit CONTINUE READ mode)(Normal page read mode)
	snand_resource_unlock();
	return tRetVal;
}
