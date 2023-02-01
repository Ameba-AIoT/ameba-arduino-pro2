/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
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
#ifndef __RTL8195B_EFUSE_H__
#define __RTL8195B_EFUSE_H__

//============================================================
// structure and define
//============================================================
// Efuse MAP
#define HWSET_MAX_SIZE_8195B            HWSET_MAX_SIZE_512
#define EFUSE_OOB_PROTECT_BYTES 		(176 + 48) // reserved area 0x100 ~ 0x1AF = 176, wlan hidden area : 0x1B0 ~ 0x1FF = 80
#define EFUSE_MAP_LEN_8195B             512 /*!< logical map len in byte */
#define EFUSE_MAX_SECTION_8195B			(EFUSE_MAP_LEN_8195B >> 3) /*!< logical map len in section */
//#define PGPKT_DATA_SIZE				8 /*!< logical map section len */
/*  physical EFUSE len */
#define EFUSE_REAL_CONTENT_LEN_8195B    512
#define AVAILABLE_EFUSE_ADDR(addr) 		(addr < EFUSE_REAL_CONTENT_LEN_8195B)

#define EFUSE_CTRL_SETTING				0x37F00000
#define L25EOUTVOLTAGE					7

#define FLASH_SECTOR_SIZE				0x1000

#define FLASH_CAL_DATA_SIZE				0x1000
#define FLASH_CAL_DATA_BASE				0x2000
#define FLASH_CAL_DATA_ADDR(_offset)	(FLASH_CAL_DATA_BASE + _offset)

#define FLASH_DPK_DATA_SIZE				0x1000
#define FLASH_DPK_DATA_BASE				0x3000
#define FLASH_DPK_DATA_ADDR(_offset)	(FLASH_DPK_DATA_BASE + _offset)

//============================================================
// function prototype
//============================================================
void Hal_ReadEFuse(PADAPTER padapter, u8 efuseType, u16 addr, u16 cnts, u8 *data, u8 bPseudoTest);
void Hal_GetEfuseDefinition(PADAPTER padapter, u8 efuseType, u8 type, void *pOut, u8 bPseudoTest);
u16 Hal_EfuseGetCurrentSize(PADAPTER pAdapter, u8 efuseType, u8 bPseudoTest);
s32 Hal_EfusePgPacketWrite(PADAPTER	padapter, u8 offset, u8 word_en, u8 *pData, u8 bPseudoTest);
u8 Hal_EfuseWordEnableDataWrite(PADAPTER padapter, u16 efuse_addr, u8 word_en, u8 *data, u8 bPseudoTest);

#endif

