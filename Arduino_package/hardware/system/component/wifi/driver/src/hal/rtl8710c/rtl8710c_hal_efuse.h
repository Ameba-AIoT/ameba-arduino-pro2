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
#ifndef __RTL8710C_EFUSE_H__
#define __RTL8710C_EFUSE_H__

//============================================================
// structure and define
//============================================================

/* logical eFUSE map */
#define EFUSE_MAP_LEN_8710C             512 /*!< logical map size in byte */
#define EFUSE_MAX_SECTION_8710C			(EFUSE_MAP_LEN_8710C >> 3) /*!< logical map len in section */
//#define PGPKT_DATA_SIZE				8 /*!< logical map section len */

/*  physical eFUSE map */
#define HWSET_MAX_SIZE_8710C            HWSET_MAX_SIZE_512 /*!<actual size of 8710c eFUSE>*/
#define EFUSE_OOB_PROTECT_BYTES 		(0x200 - 0xD0) /*!<0xD0~0x1FF is reserved for physical map use, and can not be r/w for logical map use>*/
#define EFUSE_REAL_CONTENT_LEN_8710C    HWSET_MAX_SIZE_8710C /*!<actual size of physical map>*/
#define AVAILABLE_EFUSE_ADDR(addr) 		(addr < (EFUSE_REAL_CONTENT_LEN_8710C - EFUSE_OOB_PROTECT_BYTES)) /*!<actual size reserved for logical map use>*/

//#define EFUSE_CTRL_SETTING			(uint32_t)(0x33000000)
#define L25EOUTVOLTAGE					LDO_OUT_DEFAULT_VOLT

#define FLASH_CAL_DATA_BASE				0x2000
#define FLASH_CAL_DATA_ADDR(_offset)	(FLASH_CAL_DATA_BASE + _offset)
#define FLASH_SECTOR_SIZE				0x1000

//============================================================
// function prototype
//============================================================
void Hal_ReadEFuse(PADAPTER padapter, u8 efuseType, u16 addr, u16 cnts, u8 *data, u8 bPseudoTest);
void Hal_GetEfuseDefinition(PADAPTER padapter, u8 efuseType, u8 type, void *pOut, u8 bPseudoTest);
u16 Hal_EfuseGetCurrentSize(PADAPTER pAdapter, u8 efuseType, u8 bPseudoTest);
s32 Hal_EfusePgPacketWrite(PADAPTER	padapter, u8 offset, u8 word_en, u8 *pData, u8 bPseudoTest);
u8 Hal_EfuseWordEnableDataWrite(PADAPTER padapter, u16 efuse_addr, u8 word_en, u8 *data, u8 bPseudoTest);
bool Hal_BT_Is_Supported(_adapter *adapter);

#endif

