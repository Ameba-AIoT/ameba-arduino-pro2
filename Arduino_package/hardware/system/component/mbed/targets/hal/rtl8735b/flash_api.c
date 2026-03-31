/**************************************************************************//**
 * @file     dma_api.c
 * @brief    This file implements the DMA Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-04
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

#include "flash_api.h"
#include "cmsis.h"
#include "hal_spic.h"
#include "hal_flash.h"
#include "hal_flash_ns.h"
#include "hal_spic_ns.h"

extern hal_spic_adaptor_t hal_spic_adaptor;
extern hal_spic_adaptor_t *pglob_spic_adaptor;

/**
  * @brief  Lock resource before flash processing
  * @param  none
  * @retval  none
  * @note  This api can be used to define IC specified operations before flash processing. Please check the project about its implementation.
  */
__weak void flash_resource_lock(void);

/**
  * @brief  Unlock resource after flash processing
  * @param  none
  * @retval  none
  * @note  This api can be used to define IC specified operations after flash processing. Please check the project about its implementation.
  */
__weak void flash_resource_unlock(void);

/**
  * @brief  Init Flash Pinmux
  * @param  obj: address of the flash object
  * @param  spic_pin_sel_t: the pinmux selection of the flash
  * @retval   none
  */
void flash_pinmux_init(flash_t *obj, spic_pin_sel_t pin_sel)
{
#if 0
	phal_spic_adaptor_t phal_spic_adaptor = obj->phal_spic_adaptor;
	phal_spic_adaptor->flash_pin_sel = pin_sel;
	if (pin_sel == SpicPinS0) {
		(phal_spic_adaptor->flash_pin_sel).pin_cs = FLASH_CS_PIN_SEL0;
		(phal_spic_adaptor->flash_pin_sel).pin_clk = FLASH_CLK_PIN_SEL0;
		(phal_spic_adaptor->flash_pin_sel).pin_d0 = FLASH_D0_PIN_SEL0;
		(phal_spic_adaptor->flash_pin_sel).pin_d1 = FLASH_D1_PIN_SEL0;
		(phal_spic_adaptor->flash_pin_sel).pin_d2 = FLASH_D2_PIN_SEL0;
		(phal_spic_adaptor->flash_pin_sel).pin_d3 = FLASH_D3_PIN_SEL0;
	} else {
		(phal_spic_adaptor->flash_pin_sel).pin_cs = FLASH_CS_PIN_SEL1;
		(phal_spic_adaptor->flash_pin_sel).pin_clk = FLASH_CLK_PIN_SEL1;
		(phal_spic_adaptor->flash_pin_sel).pin_d0 = FLASH_D0_PIN_SEL1;
		(phal_spic_adaptor->flash_pin_sel).pin_d1 = FLASH_D1_PIN_SEL1;
		(phal_spic_adaptor->flash_pin_sel).pin_d2 = FLASH_D2_PIN_SEL1;
		(phal_spic_adaptor->flash_pin_sel).pin_d3 = FLASH_D3_PIN_SEL1;
	}

	flash_pin_sel.pin_cs = (phal_spic_adaptor->flash_pin_sel).pin_cs;
	flash_pin_sel.pin_clk = (phal_spic_adaptor->flash_pin_sel).pin_clk;
	flash_pin_sel.pin_d0 = (phal_spic_adaptor->flash_pin_sel).pin_d0;
	flash_pin_sel.pin_d1 = (phal_spic_adaptor->flash_pin_sel).pin_d1;
	flash_pin_sel.pin_d2 = (phal_spic_adaptor->flash_pin_sel).pin_d2;
	flash_pin_sel.pin_d3 = (phal_spic_adaptor->flash_pin_sel).pin_d3;
#endif
}


/**
  * @brief  Init Flash
  * @param  obj: address of the flash object
  * @retval   none
  */
void flash_init(flash_t *obj)
{
	hal_status_t ret;
	if (pglob_spic_adaptor == NULL) {
		ret = spic_init(&hal_spic_adaptor, SPIC_BIT_MODE_SETTING, SpicQuadIOPin);
		if (ret != HAL_OK) {
			DBG_SPIF_ERR("flash_init err(%d)\r\n", ret);
		} else {
			pglob_spic_adaptor = &hal_spic_adaptor;
		}
	}
	obj->phal_spic_adaptor = pglob_spic_adaptor;
}

/**
  * @brief  Get flash ID (command: 0x9F), works in SPI mode only.
  * @param  obj: Flash object define in application software.
  * @param  buf: Pointer to a byte array to save the readback ID.
  * @param  len: Specifies the length of the buf. It should be 3.
  * @retval -1: Fail, len: Succeed.
  */
int flash_read_id(flash_t *obj, uint8_t *buf, uint8_t len)
{
	phal_spic_adaptor_t phal_spic_adaptor;
	u8 index;

	flash_init(obj);
	phal_spic_adaptor = (obj->phal_spic_adaptor);

	if (len < 3) {
		DBG_SPIF_ERR("ID length should be >= 3\n");
	}

	if ((phal_spic_adaptor->flash_id[0] == 0x0)
		|| (phal_spic_adaptor->flash_id[0] == 0xFF)) {
		DBG_SPIF_ERR("Invalide ID\n");
		return -1;
	} else {
		for (index = 0; index < 3; index++) {
			buf[index] = phal_spic_adaptor->flash_id[index];
		}
	}

	return len;
}

/**
  * @brief  This function is only for Winbond flash to get unique ID (command: 0x4B), works in SPI mode.
  * @param  obj: Flash object define in application software.
  * @param  buf: Pointer to a byte array to save the readback unique ID.
  * @param  len: Specifies the length of the buf. It should be 8.
  * @retval -1: Fail, len: Succeed.
  */
int flash_read_unique_id(flash_t *obj, uint8_t *buf, uint8_t len)
{
	phal_spic_adaptor_t phal_spic_adaptor;

	flash_init(obj);
	phal_spic_adaptor = (obj->phal_spic_adaptor);

	if (phal_spic_adaptor->flash_type != FLASH_TYPE_WINBOND) {
		return -1;
	} else {
		flash_resource_lock();
		hal_flash_read_unique_id(phal_spic_adaptor, buf, len);
		flash_resource_unlock();
	}

	return len;
}

/**
  * @brief  Erase flash sector, usually 1 sector = 4K bytes
    Please refer to flash data sheet to confirm the actual sector size.
    The actual address which being erased always aligned with sector size.
  * @param  address: Specifies the starting address to be erased.
  * @retval   none
  */
void flash_erase_sector(flash_t *obj, uint32_t address)
{
	flash_init(obj);

	flash_resource_lock();
	hal_flash_sector_erase((obj->phal_spic_adaptor), address);
	flash_resource_unlock();
}

/**
  * @brief  Erase flash block, usually 1 block = 64K bytes
    Please refer to flash data sheet to confirm the actual block size.
    The actual address which being erased always aligned with block size.
  * @param  address: Specifies the starting address to be erased.
  * @retval   none
  */
void flash_erase_block(flash_t *obj, uint32_t address)
{
	flash_init(obj);

	flash_resource_lock();
	hal_flash_64k_block_erase((obj->phal_spic_adaptor), address);
	flash_resource_unlock();
}


/**
  * @brief  Erase the whole flash chip
  * @param obj: Flash object define in application software.
  * @retval   none
  */
void flash_erase_chip(flash_t *obj)
{
	flash_init(obj);

	flash_resource_lock();
	hal_flash_chip_erase(obj->phal_spic_adaptor);
	flash_resource_unlock();
}

/**
  * @brief  Read a word from specified address
  * @param  obj: Specifies the parameter of flash object.
  * @param  address: Specifies the address to be read.
  * @param  data: Specified the address to save the readback data.
  * @retval   status: Success:1 or Failure: Others.
  */
int  flash_read_word(flash_t *obj, uint32_t address, uint32_t *data)
{
	flash_init(obj);

	dcache_invalidate_by_addr((uint32_t *)(SPI_FLASH_BASE + address), 4);
	hal_flash_stream_read((obj->phal_spic_adaptor), 4, address, (u8 *)data);
	return 1;
}

/**
  * @brief  Write a word to specified address
  * @param  obj: Specifies the parameter of flash object.
  * @param  address: Specifies the address to be programmed.
  * @param  data: Specified the data to be programmed.
  * @retval   status: Success:1 or Failure: Others.
  */
int  flash_write_word(flash_t *obj, uint32_t address, uint32_t data)
{
	flash_init(obj);

	flash_resource_lock();
	hal_flash_burst_write((obj->phal_spic_adaptor), 4, address, (u8 *)&data);
	flash_resource_unlock();
	return 1;
}


/**
  * @brief  Read a stream of data from specified address via auto mode
  * @param  obj: Specifies the parameter of flash object.
  * @param  address: Specifies the address to be read.
  * @param  len: Specifies the length of the data to read.
  * @param  data: Specified the address to save the readback data.
  * @retval   status: Success:1 or Failure: Others.
  */
int  flash_stream_read(flash_t *obj, uint32_t address, uint32_t len, uint8_t *data)
{
	flash_init(obj);

	hal_flash_stream_read((obj->phal_spic_adaptor), len, address, data);
	return 1;
}

/**
  * @brief  Write a stream of data to specified address.
            Write performance is worse than flash_burst_write,
            data length is divided into serveral pieces with each of them is 4 byte,
            SPIC then programs 4 byte data each time until the end of data length,
            it is less possible to be interrupted.
  * @param  obj: Specifies the parameter of flash object.
  * @param  address: Specifies the address to be programmed.
  * @param  len: Specifies the length of the data to write.
  * @param  data: Specified the pointer of the data to be written.
            If the address is in the flash, full address is required, i.e. SPI_FLASH_BASE + Offset
  * @retval   status: Success:1 or Failure: Others.
  */
int  flash_stream_write(flash_t *obj, uint32_t address, uint32_t len, uint8_t *data)
{
	flash_init(obj);

	flash_resource_lock();
	hal_flash_burst_write((obj->phal_spic_adaptor), len, address, data);
	flash_resource_unlock();
	return 1;
}

/**
  * @brief  Read a stream of data from specified address vai user mode
  * @param  obj: Specifies the parameter of flash object.
  * @param  address: Specifies the address to be read.
  * @param  len: Specifies the length of the data to read.
  * @param  data: Specified the address to save the readback data.
  * @retval   status: Success:1 or Failure: Others.
  */
int  flash_burst_read(flash_t *obj, uint32_t address, uint32_t Length, uint8_t *data)
{
	flash_init(obj);

	hal_flash_stream_read((obj->phal_spic_adaptor), Length, address, data);
	return 1;
}

/*
Function Description:
This function performans the same functionality as the function flash_stream_write.
It enhances write performance by reducing overheads.
Users can use either of functions depending on their needs.

* @brief  Write a stream of data to specified address
* @param  obj: Specifies the parameter of flash object.
* @param  address: Specifies the address to be programmed.
* @param  Length: Specifies the length of the data to write.
* @param  data: Specified the pointer of the data to be written.
          If the address is in the flash, full address is required, i.e. SPI_FLASH_BASE + Offset
* @retval   status: Success:1 or Failure: Others.

*/
int flash_burst_write(flash_t *obj, uint32_t address, uint32_t Length, uint8_t *data)
{
	flash_init(obj);

	flash_resource_lock();
	hal_flash_burst_write((obj->phal_spic_adaptor), Length, address, data);
	flash_resource_unlock();
	return 1;
}


/*
Function Description:
This function aims to read the value of the status register 1.
It can be used to check the current status of the flash including protected region, busy state etc.
Please refer to the datatsheet of flash for more details of the content of status register.

* @brief  Read Status register to check flash status
* @param  obj: Specifies the parameter of flash object.
* @retval status: the value of status register.
*/
int flash_get_status(flash_t *obj)
{
	phal_spic_adaptor_t phal_spic_adaptor;
	pflash_cmd_t cmd;
	u8 status = 0;

	flash_init(obj);
	phal_spic_adaptor = (obj->phal_spic_adaptor);
	cmd = phal_spic_adaptor->cmd;

	flash_resource_lock();
	status = hal_flash_get_status(phal_spic_adaptor, cmd->rdsr);
	flash_resource_unlock();

	return status;
}

/*
Function Description:
This function aims to read the value of the status register 2.
It can be used to check the current status of the flash including protected region, busy state etc.
Please refer to the datatsheet of flash for more details of the content of status register.

* @brief  Read Status register 2 to check flash status
* @param  obj: Specifies the parameter of flash object.
* @retval status: the value of status register.
*/
int flash_get_status2(flash_t *obj)
{
	phal_spic_adaptor_t phal_spic_adaptor;
	pflash_cmd_t cmd;
	u8 status = 0;

	flash_init(obj);
	phal_spic_adaptor = (obj->phal_spic_adaptor);
	cmd = phal_spic_adaptor->cmd;

	flash_resource_lock();
	status = hal_flash_get_status(phal_spic_adaptor, cmd->rdsr2);
	flash_resource_unlock();

	return status;
}

/*
Function Description:
This function aims to read the value of the status register 3.
Please refer to the datatsheet of flash for more details of the content of status register.

* @brief  Read Status register to check flash status
* @param  obj: Specifies the parameter of flash object.
* @retval status: the value of status register.
*/
int flash_get_status3(flash_t *obj)
{
	phal_spic_adaptor_t phal_spic_adaptor;
	pflash_cmd_t cmd;
	u8 status = 0;

	flash_init(obj);
	phal_spic_adaptor = (obj->phal_spic_adaptor);
	cmd = phal_spic_adaptor->cmd;

	flash_resource_lock();
	status = hal_flash_get_status(phal_spic_adaptor, cmd->rdsr3);
	flash_resource_unlock();

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
* @param  data: Specifies which bit users like to set
   ex: if users want to set the third bit, data = 0x8.
* @retval   status: Success:1 or Failure: Others.
*/
int flash_set_status(flash_t *obj, uint32_t data)
{
	phal_spic_adaptor_t phal_spic_adaptor;
	pflash_cmd_t cmd;
	u8 status_value = 0;

	flash_init(obj);
	phal_spic_adaptor = (obj->phal_spic_adaptor);
	cmd = phal_spic_adaptor->cmd;

	status_value = flash_get_status2(obj);
	flash_resource_lock();

	if (phal_spic_adaptor->quad_pin_sel) {
		switch (phal_spic_adaptor->flash_type) {
		case FLASH_TYPE_GD:
		case FLASH_TYPE_XTX:
			data = ((status_value << 8) | (data & 0xFF));
			hal_flash_set_write_enable(phal_spic_adaptor);
			spic_tx_cmd(phal_spic_adaptor, cmd->wrsr, 2, (u8 *)&data);
			break;

		case FLASH_TYPE_MXIC:
			hal_flash_set_status(phal_spic_adaptor, cmd->wrsr, (u8)(data | 0x40));
			break;

		default:
			hal_flash_set_status(phal_spic_adaptor, cmd->wrsr, (u8)data);
		}
	} else {
		hal_flash_set_status(phal_spic_adaptor, cmd->wrsr, (u8)data);
	}

	flash_resource_unlock();

	return 1;
}

/*
Function Description:
This function aims to set the value of the status register 2.
It can be used to protect partial flash region.
Please refer to the datatsheet of flash for more details of the content of status register.
The block protected area and the corresponding control bits are provided in the flash datasheet.

* @brief  Set Status register to enable desired operation
* @param  obj: Specifies the parameter of flash object.
* @param  data: Specifies which bit users like to set
   ex: if users want to set the third bit, data = 0x8.
* @retval   status: Success:1 or Failure: Others.
*/
int flash_set_status2(flash_t *obj, uint32_t data)
{
	phal_spic_adaptor_t phal_spic_adaptor;
	pflash_cmd_t cmd;
	u8 status_value = 0;

	flash_init(obj);
	phal_spic_adaptor = (obj->phal_spic_adaptor);
	cmd = phal_spic_adaptor->cmd;

	status_value = flash_get_status(obj) & 0xFF;
	flash_resource_lock();

	if (phal_spic_adaptor->quad_pin_sel) {
		switch (phal_spic_adaptor->flash_type) {
		case FLASH_TYPE_GD:
		case FLASH_TYPE_XTX:
			data = status_value | ((0x2 | data) << 8);
			hal_flash_set_write_enable(phal_spic_adaptor);
			spic_tx_cmd(phal_spic_adaptor, cmd->wrsr, 2, (u8 *)&data);
			break;

		case FLASH_TYPE_MXIC:
			data = (status_value | ((data & 0xFF) << 8));
			hal_flash_set_write_enable(phal_spic_adaptor);
			spic_tx_cmd(phal_spic_adaptor, cmd->wrsr, 2, (u8 *)&data);
			break;

		default:
			data |= 0x2;
			hal_flash_set_status(phal_spic_adaptor, cmd->wrsr2, (u8)data);
		}
	} else {
		switch (phal_spic_adaptor->flash_type) {
		case FLASH_TYPE_GD:
		case FLASH_TYPE_XTX:
		case FLASH_TYPE_MXIC:
			data = status_value | ((data & 0xFF) << 8);
			hal_flash_set_write_enable(phal_spic_adaptor);
			spic_tx_cmd(phal_spic_adaptor, cmd->wrsr, 2, (u8 *)&data);
			break;

		default:
			hal_flash_set_status(phal_spic_adaptor, cmd->wrsr2, (u8)data);
		}
	}

	flash_resource_unlock();
	return 1;
}

/*
Function Description:
This function aims to set the value of the status register 3.
Please refer to the datatsheet of flash for more details of the content of status register.

* @brief  Set Status register to enable desired operation
* @param  obj: Specifies the parameter of flash object.
* @param  data: Specifies which bit users like to set
   ex: if users want to set the third bit, data = 0x8.
* @retval   status: Success:1 or Failure: Others.
*/
int flash_set_status3(flash_t *obj, uint32_t data)
{
	phal_spic_adaptor_t phal_spic_adaptor;
	pflash_cmd_t cmd;

	flash_init(obj);
	phal_spic_adaptor = (obj->phal_spic_adaptor);
	cmd = phal_spic_adaptor->cmd;

	flash_resource_lock();

	if (phal_spic_adaptor->flash_type == FLASH_TYPE_ZBIT) {
		hal_flash_set_status(phal_spic_adaptor, cmd->wrsr3, data | 0x10);
	} else {
		hal_flash_set_status(phal_spic_adaptor, cmd->wrsr3, (u8)data);
	}

	flash_resource_unlock();

	return 1;
}

/*
Function Description:
This function aims to reset the status register, please make sure the operation is appropriate.
* @brief  Set the Status register to 0
* @param  obj: Specifies the parameter of flash object.
* @retval None.
*/
void flash_reset_status(flash_t *obj)
{
	flash_set_status(obj, 0x00);
}

/*
Function Description:
This function aims to get the density of the flash.
* @brief  Get flash density
* @param  obj: Specifies the parameter of flash object.
* @retval None.
*/
void flash_get_size(flash_t *obj)
{
	phal_spic_adaptor_t phal_spic_adaptor;
	u8 size_id;
	u16 size = 0;

	flash_init(obj);
	phal_spic_adaptor = (obj->phal_spic_adaptor);
	size_id = phal_spic_adaptor->flash_id[2];
	size = ((1 << size_id) >> 20) * 8;

	dbg_printf("Flash Size = %d Mbit\r\n", size);
}

/*
Function Description:
This function is only for Micron/Winbond 512Mbit flash to access beyond 128Mbit by switching between four 128 Mbit area.
Please refer to flash datasheet for more information about memory mapping.
* @brief  Set the fourth address byte to switch among different 128Mbit region
* @param  obj: Specifies the parameter of flash object.
* @retval status: Success:1 or Failure: Others.
*/
int flash_set_extend_addr(flash_t *obj, uint32_t data)
{
	flash_init(obj);

	flash_resource_lock();
	hal_flash_set_extended_addr((obj->phal_spic_adaptor), (u8)data);
	flash_resource_unlock();
	return 1;
}

/*
Function Description:
This function returns the status of the extend address register

* @brief  Indicate the fourth address byte
* @param  obj: Specifies the parameter of flash object.
* @retval status: the value of the fourth address byte.

*/
int flash_get_extend_addr(flash_t *obj)
{
	u8 extend_addr_state = 0;
	flash_init(obj);

	flash_resource_lock();
	extend_addr_state = hal_flash_get_extended_addr((obj->phal_spic_adaptor));
	flash_resource_unlock();

	return extend_addr_state;
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
void flash_set_lock_mode(uint32_t mode)
{
	if (pglob_spic_adaptor == NULL) {
		spic_init(&hal_spic_adaptor, SpicQuadIOMode, hal_spic_adaptor.flash_pin_sel);
	}

	flash_resource_lock();
	hal_flash_set_write_protect_mode(pglob_spic_adaptor, mode);
	flash_resource_unlock();
}

/*Lock whole flash chip*/
void flash_global_lock(void)
{
	if (pglob_spic_adaptor == NULL) {
		spic_init(&hal_spic_adaptor, SpicQuadIOMode, hal_spic_adaptor.flash_pin_sel);
	}

	flash_resource_lock();
	hal_flash_global_lock(pglob_spic_adaptor);
	flash_resource_unlock();
}

/*Unlock whole flash chip*/
void flash_global_unlock(void)
{
	if (pglob_spic_adaptor == NULL) {
		spic_init(&hal_spic_adaptor, SpicQuadIOMode, hal_spic_adaptor.flash_pin_sel);
	}

	flash_resource_lock();
	hal_flash_global_unlock(pglob_spic_adaptor);
	flash_resource_unlock();
}

/***********************************************************************************
The following functions are compatile with some of Winbond flash only.
Not all Winbond flash supports these functions,
plase refer to data sheets of the target flashes.
************************************************************************************/

/*Lock individual sector or block region, should refer to the datasheet for more details*/
void flash_individual_lock(uint32_t address)
{
	if (pglob_spic_adaptor == NULL) {
		spic_init(&hal_spic_adaptor, SpicQuadIOMode, hal_spic_adaptor.flash_pin_sel);
	}

	flash_resource_lock();
	hal_flash_protect_sector(pglob_spic_adaptor, address);
	flash_resource_unlock();
}

/*Unlock individual sector or block region, should refer to the datasheet for more details*/
void flash_individual_unlock(uint32_t address)
{
	if (pglob_spic_adaptor == NULL) {
		spic_init(&hal_spic_adaptor, SpicQuadIOMode, hal_spic_adaptor.flash_pin_sel);
	}

	flash_resource_lock();
	hal_flash_unprotect_sector(pglob_spic_adaptor, address);
	flash_resource_unlock();
}

/*
1: the target sector/block is locked
0: the target sector/block is not locked
*/
int flash_read_individual_lock_state(uint32_t address)
{
	if (pglob_spic_adaptor == NULL) {
		spic_init(&hal_spic_adaptor, SpicQuadIOMode, hal_spic_adaptor.flash_pin_sel);
	}

	phal_spic_adaptor_t phal_spic_adaptor;
	u8 flash_type;
	u8 state = 0;

	phal_spic_adaptor = pglob_spic_adaptor;
	flash_type = phal_spic_adaptor->flash_type;

	flash_resource_lock();
	state = hal_flash_query_sector_protect_state(phal_spic_adaptor, address);
	flash_resource_unlock();

	if (FLASH_TYPE_WINBOND == flash_type) {
		if (state & 0x1) {
			DBG_SPIF_WARN("The section is protected\r\n");
		} else {
			DBG_SPIF_WARN("The section is not protected\r\n");
		}
	} else {
		DBG_SPIF_ERR("This flash type does not support this featrue\r\n");
		return 0;
	}

	return 1;
}

/***********************************************************************************
The following functions are compatile with MXIC flash only.
Not all MXIC flash supports these functions,
plase refer to data sheets of the target flashes.
************************************************************************************/

/*
Function Description:
This function sends the command to enter OTP region.
Standard write / command commands can be performed on the OTP region.
* @brief  Enter OTP region
* @param  none
* @retval none.

*/
void flash_mxic_enter_otp(void)
{
	if (pglob_spic_adaptor == NULL) {
		spic_init(&hal_spic_adaptor, SpicQuadIOMode, hal_spic_adaptor.flash_pin_sel);
	}

	spic_tx_cmd_no_check(pglob_spic_adaptor, FLASH_CMD_ENSO, 0, 0);
}

/*
Function Description:
This function sends the command to exit OTP region.
* @brief  Exit OTP region
* @param  none
* @retval none.

*/
void flash_mxic_exit_otp(void)
{
	if (pglob_spic_adaptor == NULL) {
		spic_init(&hal_spic_adaptor, SpicQuadIOMode, hal_spic_adaptor.flash_pin_sel);
	}

	spic_tx_cmd_no_check(pglob_spic_adaptor, FLASH_CMD_EXSO, 0, 0);
}

/*
Function Description:
This function locks the otp region permanently, the data on the OTP region cannot be updated.
* @brief  Lock OTP region
* @param  none
* @retval none.

*/
void flash_mxic_lock_otp(void)
{
	phal_spic_adaptor_t phal_spic_adaptor;

	if (pglob_spic_adaptor == NULL) {
		spic_init(&hal_spic_adaptor, SpicQuadIOMode, hal_spic_adaptor.flash_pin_sel);
	}

	phal_spic_adaptor = pglob_spic_adaptor;

	hal_flash_set_write_enable(phal_spic_adaptor);

	do {
		spic_tx_cmd_no_check(phal_spic_adaptor, FLASH_CMD_WRSCUR, 0, 0);
	} while ((hal_flash_get_status(phal_spic_adaptor, FLASH_CMD_RDSCUR) & 0x2) != 0x2);

	spic_tx_cmd_no_check(phal_spic_adaptor, (phal_spic_adaptor->cmd)->wrdi, 0, 0);
}

