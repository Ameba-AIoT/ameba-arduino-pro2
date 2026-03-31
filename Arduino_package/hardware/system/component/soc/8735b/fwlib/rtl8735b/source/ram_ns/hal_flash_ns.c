/**************************************************************************//**
 * @file     rtl8195bhp_flash.c
 * @brief    Implement HAL flash ROM code functions.
 * @version  1.00
 * @date     2017-08-22
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
#if defined(CONFIG_BUILD_NONSECURE)
#include "cmsis.h"
#include "rtl8735b_spic_type.h"
#include "hal_spic_ns.h"
#include "hal_flash_ns.h"
#include "hal_sys_ctrl_nsc.h"
#include "hal_cache.h"
#include "hal_timer.h"

extern const u32 spic_calibration_pattern[4];

/**

        \addtogroup hal_flash FLASH
        @{
*/


/**
  \brief The data sturcture includes various dummy cycles corresponding to different flash commands for unknown flash type.
*/

static const flash_dummy_cycle_t default_dc = {
	0x0,// dc_read;
	0x8,// dc_dread;
	0x4,// dc_2read;
	0x8,// dc_qread;
	0x4,// dc_4read, for quad io should enable prm mode;2+4
	0x7,// dc_dtr_4read, for quad io dtr should enable prm mode;1+7
	0x4,// dc_qpi_read, for qpi should enable prm mode;2+4
	0x7,// dc_dtr_qpi_read, for qpi dtr should enable prm mode;1+7
	0x0,// dc_read_status;
	0x0,// dc_dtr_4read_status;
};

/**
  \brief The data sturcture includes various dummy cycles corresponding to different flash commands for Winbond flash.
*/

static const flash_dummy_cycle_t winbond_dc = {
	0x0,// dc_read;
	0x8,// dc_dread;
	0x4,// dc_2read;
	0x8,// dc_qread;
	0x4,// dc_4read, for quad io should enable prm mode;2+4
	0x6,// dc_dtr_4read, for quad io dtr should enable prm mode;1+7
	0x4,// dc_qpi_read, for qpi should enable prm mode;2+4
	0x6,// dc_dtr_qpi_read, for qpi dtr should enable prm mode;1+7
	0x0,// dc_read_status;
	0x0,// dc_dtr_4read_status;
};

/**
  \brief The data sturcture includes various dummy cycles corresponding to different flash commands for ESMT flash.
*/

static const flash_dummy_cycle_t esmt_dc = {
	0x0,// dc_read;
	0x8,// dc_dread;
	0x4,// dc_2read;
	0x8,// dc_qread;
	0x4,// dc_4read, for quad io should enable prm mode;2+4
	0x6,// dc_dtr_4read, for quad io dtr should enable prm mode;1+7
	0x4,// dc_qpi_read, for qpi should enable prm mode;2+4
	0x6,// dc_dtr_qpi_read, for qpi dtr should enable prm mode;1+7
	0x0,// dc_read_status;
	0x0,// dc_dtr_4read_status;
};


/**
  \brief The data sturcture includes various dummy cycles corresponding to different flash commands for MXIC flash.
*/

static const flash_dummy_cycle_t mxic_dc = {
	0x0,// dc_read;
	0x8,// dc_dread;
	0x4,// dc_2read;
	0x8,// dc_qread;
	0x4,// dc_4read, for quad io should enable prm mode;2+4
	0x4,// dc_dtr_4read, for quad io dtr should enable prm mode;1+7
	0x4,// dc_qpi_read, for qpi should enable prm mode;2+4
	0x4,// dc_dtr_qpi_read, for qpi dtr should enable prm mode;1+7
	0x0,// dc_read_status;
	0x0,// dc_dtr_4read_status;
};

/**
  \brief The data sturcture includes various dummy cycles corresponding to different flash commands for Micron flash.
*/

static const flash_dummy_cycle_t micron_dc = {
	0x0,// dc_read;
	0x8,// dc_dread;
	0x8,// dc_2read;
	0x8,// dc_qread;
	0x8,// dc_4read, for quad io should enable prm mode;2+4
	0x6,// dc_dtr_4read, for quad io dtr should enable prm mode;1+7
	0x8,// dc_qpi_read, for qpi should enable prm mode;2+4
	0x6,// dc_dtr_qpi_read, for qpi dtr should enable prm mode;1+7
	0x0,// dc_read_status;
	0x0,// dc_dtr_4read_status;
};

/**
  \brief The data sturcture includes various flash commands for unknown flash type.
*/

static const flash_cmd_t default_cmd = {
	0x06, // wren,
	0x04, // wrdi,
	0x05, // rdsr,
	0x01, // wrsr,
	0x35, // rdsr2,
	0x31, // wrsr2,
	0x15, // rdsr3,
	0x11, // wrsr3,
	0xC8, // rear, Read extended address register
	0xC5, // wear, Write extended address register
	0x20, // se,
	0x52, // be_32k,
	0xD8, // be_64k,
	0xC7, // ce,
	0x9F, // rdid,
	0x03, // read,
	0x0B, // fread,
	0x3B, // dread,
	0xBB, // str_2read,
	0xBD, // dtr_2read,
	0x6B, // qread,
	0xEB, // str_4read,
	0xED, // dtr_4read
	0x02, // pp,
	0xB9, // dp,
	0x00, // udp,
	0xAB, // rdp,
	0xFF, // en_spi,
	0x38, // en_qpi,
	0x36, // block_lock,
	0x39, // block_unlock,
	0x7E, // global_lock,
	0x98, // global_unlock,
	0x3D, // read_block_lock,
	0x66, // en_reset,
	0x99, // reset,
	0x5A // read_sfdp,
};

/**
  \brief The data sturcture includes various flash commands for Winbond flash.
*/

static const flash_cmd_t winbond_cmd = {
	0x06, // wren,
	0x04, // wrdi,
	0x05, // rdsr,
	0x01, // wrsr,
	0x35, // rdsr2,
	0x31, // wrsr2,
	0x15, // rdsr3,
	0x11, // wrsr3,
	0xC8, // rear, Read extended address register
	0xC5, // wear, Write extended address register
	0x20, // se,
	0x52, // be_32k,
	0xD8, // be_64k,
	0xC7, // ce,
	0x9F, // rdid,
	0x03, // read,
	0x0B, // fread,
	0x3B, // dread,
	0xBB, // str_2read,
	0xBD, // dtr_2read,
	0x6B, // qread,
	0xEB, // str_4read,
	0xED, // dtr_4read
	0x02, // pp,
	0xB9, // dp,
	0x00, // udp,
	0xAB, // rdp,
	0xFF, // en_spi,
	0x38, // en_qpi,
	0x36, // block_lock,
	0x39, // block_unlock,
	0x7E, // global_lock,
	0x98, // global_unlock,
	0x3D, // read_block_lock,
	0x66, // en_reset,
	0x99, // reset,
	0x00 // read_sfdp,
};

/**
  \brief The data sturcture includes various flash commands for MXIC flash.
*/

static const flash_cmd_t mxic_cmd = {
	0x06, // wren,
	0x04, // wrdi,
	0x05, // rdsr,
	0x01, // wrsr, should follow by address bytes
	0x15, // rdsr2, read configuration register
	0x00, // wrsr2,
	0x00, // rdsr3,
	0x00, // wrsr3,
	0xC8, // rear, Read extended address register
	0xC5, // wear, Write extended address register
	0x20, // se,
	0x52, // be_32k,
	0xD8, // be_64k,
	0xC7, // ce,
	0x9F, // rdid,
	0x03, // read,
	0x0B, // fread,
	0x3B, // dread,
	0xBB, // str_2read,
	0x00, // dtr_2read,
	0x6B, // qread,
	0xEB, // str_4read,
	0xED, // dtr_4read,
	0x02, // pp,
	0xB9, // dp,
	0x00, // udp,
	0xAB, // rdp,
	0xF5, // en_spi,
	0x35, // en_qpi,
	0x00, // block_lock,
	0x00, // block_unlock,
	0x00, // global_lock,
	0x00, // global_unlock,
	0x00, // read_block_lock,
	0x66, // en_reset,
	0x99, // reset,
	0x5A // read_sfdp,
};

/**
  \brief The data sturcture includes various flash commands for Micron flash.
*/

static const flash_cmd_t micron_cmd = {
	0x06, // wren,
	0x04, // wrdi,
	0x05, // rdsr,
	0x01, // wrsr, should follow by address bytes
	0x70, // rdsr2, read flag status register
	0x00, // wrsr2,
	0x00, // rdsr3,
	0x00, // wrsr3,
	0xC8, // rear, Read extended address register
	0xC5, // wear, Write extended address register
	0x20, // se,
	0x52, // be_32k,
	0xD8, // be_64k,
	0xC7, // ce,
	0x9F, // rdid,
	0x03, // read,
	0x0B, // fread,
	0x3B, // dread,
	0xBB, // str_2read,
	0xBD, // dtr_2read,
	0x6B, // qread,
	0xEB, // str_4read,
	0xED, // dtr_4read,
	0x02, // pp,
	0xB9, // dp,
	0x00, // udp,
	0xAB, // rdp,
	0xF5, // en_spi,
	0x35, // en_qpi,
	0x00, // block_lock,
	0x00, // block_unlock,
	0x00, // global_lock,
	0x00, // global_unlock,
	0x00, // read_block_lock,
	0x66, // en_reset,
	0x99, // reset,
	0x5A // read_sfdp,
};

/**
  \brief The data sturcture includes various flash commands for ESMT flash.
*/

static const flash_cmd_t esmt_cmd = {
	0x06, // wren,
	0x04, // wrdi,
	0x05, // rdsr,
	0x01, // wrsr,
	0x09, // rdsr2,
	0xC0, // (wrsr2)wrsr3,
	0x95, // rdsr3,
	0xC1, // (wrsr3)wrsr4,
	0x85, // (rear, Read extended address register)rdsr4
	0x00, // wear, Write extended address register
	0x20, // se,
	0x52, // be_32k,
	0xD8, // be_64k,
	0xC7, // ce,
	0x9F, // rdid,
	0x03, // read,
	0x0B, // fread,
	0x3B, // dread,
	0xBB, // str_2read,
	0xBD, // dtr_2read,
	0x6B, // qread,
	0xEB, // str_4read,
	0xED, // dtr_4read
	0x02, // pp,
	0xB9, // dp,
	0x00, // udp,
	0xAB, // rdp,
	0xFF, // en_spi,
	0x38, // en_qpi,
	0x00, // block_lock,
	0x00, // block_unlock,
	0x00, // global_lock,
	0x00, // global_unlock,
	0x00, // read_block_lock,
	0x66, // en_reset,
	0x99, // reset,
	0x00 // read_sfdp,
};


/// @cond DOXYGEN_ROM_HAL_API

/**

        \addtogroup hal_flash_ns_func FLASH HAL ROM APIs
        \ingroup hal_flash
        \brief ROM APIs implement flash commands.
               The user application(in RAM space) should not call these APIs directly.
               There is another set of Flash HAL APIs in the RAM space is provided for the user application.
        @{
*/


/**
  \brief The stubs functions table to exports Flash HAL functions in ROM.
*/
const hal_flash_func_stubs_t hal_flash_stubs_ns = {
	.hal_flash_read_unique_id = flash_ns_read_unique_id,
	.hal_flash_read_id = flash_ns_read_id,
	.hal_flash_set_write_enable = flash_ns_set_write_enable,
	.hal_flash_set_status = flash_ns_set_status,
	.hal_flash_set_status_no_check = flash_ns_set_status_no_check,
	.hal_flash_set_status_with_addr = flash_ns_set_status_with_addr,
	.hal_flash_set_extended_addr = flash_ns_set_extended_addr,
	.hal_flash_set_write_protect_mode = flash_ns_set_write_protect_mode,
	.hal_flash_get_status = flash_ns_get_status,
	.hal_flash_get_status_with_addr = flash_ns_get_status_with_addr,
	.hal_flash_get_extended_addr = flash_ns_get_extended_addr,
	.hal_flash_wait_ready = flash_ns_wait_ready,
	.hal_flash_chip_erase = flash_ns_chip_erase,
	.hal_flash_64k_block_erase = flash_ns_64k_block_erase,
	.hal_flash_32k_block_erase = flash_ns_32k_block_erase,
	.hal_flash_sector_erase = flash_ns_sector_erase,
	.hal_flash_set_dummy_cycle = flash_ns_set_dummy_cycle,
	.hal_flash_query_sector_protect_state = flash_ns_query_sector_protect_state,
	.hal_flash_protect_sector = flash_ns_protect_sector,
	.hal_flash_unprotect_sector = flash_ns_unprotect_sector,
	.hal_flash_global_lock = flash_ns_global_lock,
	.hal_flash_global_unlock = flash_ns_global_unlock,
	.hal_flash_set_quad_enable = flash_ns_set_quad_enable,
	.hal_flash_unset_quad_enable = flash_ns_unset_quad_enable,
	.hal_flash_enable_qpi = flash_ns_enable_qpi,
	.hal_flash_return_spi = flash_ns_return_spi,
	.hal_flash_return_str = flash_ns_return_str,
	.hal_flash_enter_power_down = flash_ns_enter_power_down,
	.hal_flash_release_from_power_down = flash_ns_release_from_power_down,
	.hal_flash_stream_read = flash_ns_stream_read,
	.hal_flash_stream_write = flash_ns_stream_write,
	.hal_flash_burst_read = flash_ns_burst_read,
	.hal_flash_burst_write = flash_ns_burst_write,
	.hal_flash_page_program = flash_ns_page_program,
	.hal_flash_reset_to_spi = flash_ns_reset_to_spi
};


/** \brief Description of flash_ns_read_unique_id
 *
 *    flash_ns_read_unique_id is used to read unique ID for the flash.
 *    This function is only valid for Winbond Flash.
 *    The ID is unique for each flash sample even if the part number is the name.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param uint8_t *buf:      The buff to store ID.
 *   \param uint8_t *len:      The lenght of ID.
 *
 *   \return void.
 */

void flash_ns_read_unique_id(void *adaptor, uint8_t *buf, uint8_t len)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	u8 i;

	DBG_SPIF_INFO("flash_read_unique_id: (0x%x)\r\n", adaptor);

	/*Load current setting of ctrlr0 register*/
	spic_rtl_disable(spic_dev);

	/*Set chnl num to send read id command*/
	phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;

	/*Expect to receive 8 byte unique ID data*/
	spic_rtl_set_ctrl1(spic_dev, 12);

	spic_ns_rx_cmd(phal_spic_adaptor, 0x4B, 0, 0);

	/*Skip 4 dummy bytes*/
	spic_dev->SPIC_DR_WORD;

	for (i = 0; i < len; i++) {
		buf[i] = HAL_READ8(SPIC_BASE, 0x60);
	}
}

/** \brief Description of flash_ns_read_id
 *
 *    flash_ns_read_id is used to read ID for the flash.
 *    Flash with the same part number has the same flash ID.
 *    ID can be used to identify the type of flash.
 *    The ID information is stored in the flash adaptor.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return hal_status_t.
 */

hal_status_t flash_ns_read_id(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	phal_spic_adaptor->spic_dev = SPIC;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	pflash_cmd_t cmd;
	u32 rd_data;
	u32 reg_value;
	u8 flash_id[3];
	u8 retry_count;

	DBG_SPIF_INFO("flash_read_id: (0x%x)\r\n", adaptor);

	/*Load current setting of ctrlr0 register*/
	reg_value = spic_dev->SPIC_CTRLR0;

	cmd = (pflash_cmd_t)&default_cmd;
	phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&default_dc;

	spic_rtl_disable(spic_dev);

	/*Set chnl num to send read id command*/
	phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;
	reg_value &= ~(SPIC_MASK_CMD_CH | SPIC_MASK_DATA_CH | SPIC_MASK_ADDR_CH);
	spic_dev->SPIC_CTRLR0 = reg_value;

	/*Expect to receive 3 byte ID data*/
	spic_rtl_set_ctrl1(spic_dev, 3);

	for (retry_count = 0; retry_count < 3; retry_count++) {

		/*Send Read ID Command to Flash */
		spic_ns_rx_cmd(phal_spic_adaptor, cmd->rdid, 0, 0);
		//dbg_printf("cmd->rdid = %x\r\n",cmd->rdid);
		rd_data = spic_dev->SPIC_DR_WORD;
		flash_id[0] = rd_data & 0xFF;
		flash_id[1] = (rd_data >> 8) & 0xFF;
		flash_id[2] = (rd_data >> 16) & 0xFF;
		if ((flash_id[0] != 0)
			&& flash_id[0] != 0xFF) {
			switch (flash_id[0]) {
			case 0x20:
				phal_spic_adaptor->flash_type = FLASH_TYPE_MICRON;
				phal_spic_adaptor->cmd = (pflash_cmd_t)&micron_cmd;
				phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&micron_dc;
				break;

			case 0xEF:
				phal_spic_adaptor->flash_type = FLASH_TYPE_WINBOND;
				phal_spic_adaptor->cmd = (pflash_cmd_t)&winbond_cmd;
				phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&winbond_dc;
				break;

			case 0xC2:
				phal_spic_adaptor->flash_type = FLASH_TYPE_MXIC;
				phal_spic_adaptor->cmd = (pflash_cmd_t)&mxic_cmd;
				phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&mxic_dc;
				break;

			case 0x1C:
				phal_spic_adaptor->flash_type = FLASH_TYPE_EON;
				phal_spic_adaptor->cmd = (pflash_cmd_t)&esmt_cmd;
				phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&esmt_dc;
				break;

			case 0xC8:
				if (flash_id[2] >= 0x16) {
					phal_spic_adaptor->flash_type = FLASH_TYPE_GD32;
				} else {
					phal_spic_adaptor->flash_type = FLASH_TYPE_GD;
				}
				phal_spic_adaptor->cmd = (pflash_cmd_t)&default_cmd;
				phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&default_dc;
				break;

			case 0x0B:
				phal_spic_adaptor->flash_type = FLASH_TYPE_XTX;
				phal_spic_adaptor->cmd = (pflash_cmd_t)&default_cmd;
				phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&default_dc;
				break;

			case 0x68:
				phal_spic_adaptor->flash_type = FLASH_TYPE_BOYA;
				phal_spic_adaptor->cmd = (pflash_cmd_t)&default_cmd;
				phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&default_dc;
				break;

			case 0x46:
				phal_spic_adaptor->flash_type = FLASH_TYPE_XMC;
				phal_spic_adaptor->cmd = (pflash_cmd_t)&default_cmd;
				phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&default_dc;
				break;

			case 0x5E:
				phal_spic_adaptor->flash_type = FLASH_TYPE_ZBIT;
				phal_spic_adaptor->cmd = (pflash_cmd_t)&default_cmd;
				phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&default_dc;
				break;

			default:
				phal_spic_adaptor->flash_type = FLASH_TYPE_OTHERS;
				phal_spic_adaptor->cmd = (pflash_cmd_t)&default_cmd;
				phal_spic_adaptor->dummy_cycle = (pflash_dummy_cycle_t)&default_dc;
				break;
			}

			phal_spic_adaptor->flash_id[0] = flash_id[0];
			phal_spic_adaptor->flash_id[1] = flash_id[1];
			phal_spic_adaptor->flash_id[2] = flash_id[2];
			break;
		}

		if (retry_count == 2) {
			DBG_SPIF_ERR("Invalid ID\r\n");
			return HAL_ERR_HW;
		}
	}

	DBG_SPIF_INFO("Flash Type = %d\r\n", phal_spic_adaptor->flash_type);
	DBG_SPIF_INFO("Flash ID = %x\r\n", phal_spic_adaptor->flash_id[0]);
	DBG_SPIF_INFO("Flash ID = %x\r\n", phal_spic_adaptor->flash_id[1]);
	DBG_SPIF_INFO("Flash ID = %x\r\n", phal_spic_adaptor->flash_id[2]);

	return HAL_OK;
}

/** \brief Description of flash_ns_reset_to_spi
 *
 *    flash_ns_reset_to_spi is used to reset flash back to SPI mode.
 *    This function is called when SPIC cannot read correct ID.
 *    It would be two scenarios that ID cannot be read.
 *    First, flash may enter unknown state that SPIC cannot access the flash with the correct IO mode.
 *    Second, flash may be in deep power down state so that commands sent by SPIC cannot be recognized.
 *    This function aims to wake up flash and reset it to default SPI mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_reset_to_spi(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;

	phal_spic_adaptor->spic_dev = SPIC;
	pflash_cmd_t cmd = (pflash_cmd_t)&default_cmd;
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;

	/*Read ID fails with one IO mode, flash may be in deep power down state*/
	spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->rdp, 0, 0);

	phal_spic_adaptor->spic_bit_mode = SpicQpiMode;
	spic_ns_config_user_mode(phal_spic_adaptor);
	spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->rdp, 0, 0);
	hal_delay_us(100);
	spic_ns_tx_cmd_no_check(phal_spic_adaptor, FLASH_CMD_EN_SPI1, 0, 0);
	spic_ns_tx_cmd_no_check(phal_spic_adaptor, FLASH_CMD_EN_SPI2, 0, 0);

	phal_spic_adaptor->spic_bit_mode = SpicOneIOMode;
	spic_ns_config_user_mode(phal_spic_adaptor);

	phal_spic_adaptor->spic_bit_mode = spic_bit_mode;
	DBG_SPIF_WARN("Reset Flash to SPI Mode\r\n");
}

/** \brief Description of flash_ns_set_write_enable
 *
 *    flash_ns_set_write_enable is used to send write enable command.
 *    After the command is sent, SPIC checks if the write enable bit is set or not.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_set_write_enable(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;

	flash_ns_wait_ready(phal_spic_adaptor);

	do {
		spic_ns_tx_cmd(phal_spic_adaptor, cmd->wren, 0, 0);
	} while ((flash_ns_get_status(phal_spic_adaptor, cmd->rdsr) & 0x2) == 0);
}

/** \brief Description of flash_ns_set_status
 *
 *    flash_ns_set_status is used to send write status register command.
 *    Write status register command may not be the same for different status registers or different flash types.
 *    Users can input an instruction and a value according to flash data sheet to set the status register.
 *    The function will check if flash is ready after setting the status register.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:      The instruction of write status register command.
 *   \param u8 data:     The value is going to be set in status register.
 *
 *   \return void.
 */

void flash_ns_set_status(void *adaptor, u8 cmd, u8 data)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd(phal_spic_adaptor, cmd, 1, &data);
}

/** \brief Description of flash_ns_set_status_no_check
 *
 *    flash_ns_set_status_no_check is used to send write status register command.
 *    Write status register command may not be the same for different status registers or different flash types.
 *    Users can input an instruction and a value according to flash data sheet to set the status register.
 *    The function will NOT check if flash is ready after setting the status register.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:      The instruction of write status register command.
 *   \param u8 data:     The value is going to be set in status register.
 *
 *   \return void.
 */

void flash_ns_set_status_no_check(void *adaptor, u8 cmd, u8 data)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd, 1, &data);
}

/** \brief Description of flash_ns_set_status_with_addr
 *
 *    flash_ns_set_status_with_addr is used to send write status register with address command.
 *    Write status register command may not be the same for different status registers or different flash types.
 *    Some write status commands allow to carry one address byte to identify which status register.
 *    Users can input an instruction, an address and a value according to flash data sheet to set the status register.
 *    The function will check if flash is ready after setting the status register.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:      The instruction of write status register command.
 *   \param u8 addr:     The address of write status register command.
 *   \param u8 data:     The value is going to be set in status register.
 *
 *   \return void.
 */

void flash_ns_set_status_with_addr(void *adaptor, u8 cmd, u8 addr, u8 data)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	u8 buff[2];

	buff[0] = addr;
	buff[1] = data;

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd(phal_spic_adaptor, cmd, 2, buff);
}

/** \brief Description of flash_ns_set_extended_addr
 *
 *    flash_ns_set_extended_addr is used to send set extended address command.
 *    Flash access 128 Mbit region at most with three address bytes.
 *    With this command, the value followed by the command presents the fourth address byte.
 *    Flash accesses beyond 128 Mbit region by setting different value of the fourth address byte to switch among different 128 Mbit bank.
 *    Some flashes cannot support this feature, please refer to flash data sheets.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 data:     The fourth address byte.
 *
 *   \return void.
 */

void flash_ns_set_extended_addr(void *adaptor, u8 data)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->wear, 1, &data);
}

/** \brief Description of flash_ns_set_write_protect_mode
 *
 *    flash_ns_set_write_protect_mode is used to send set write protect mode command.
 *    Write protect feature can be either by multiple blocks or by individual block.
 *    Only some of Winbond flashes support this feature.
 *    The block protect control byte is written to one of the status register.
 *    Please refer to flash data sheet for more details
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 mode:     The block protect control parameter.
 *
 *   \return void.
 */

void flash_ns_set_write_protect_mode(void *adaptor, u8 mode)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 value = 0;

	value = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr3);
	value &= ~0x4;
	value |= mode << 2;
	flash_ns_set_status(phal_spic_adaptor, cmd->wrsr3, value);
	DBG_SPIF_INFO("Status Register 3 = %x", flash_ns_get_status(phal_spic_adaptor, cmd->rdsr3));
}

/** \brief Description of flash_ns_get_status
 *
 *    flash_ns_get_status is used to send read status register command.
 *    Each flash may have more than one status registers that can be accessed with different instructions.
 *    Please refer to flash data sheet for more details
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:     The instruction of read status register command.
 *
 *   \return u8: the value of the status register.
 */

u8 flash_ns_get_status(void *adaptor, u8 cmd)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	u8 rd_data;

	/* disable spi_flash user mode */
	spic_rtl_disable(spic_dev);

	/* set ctrlr1; 1 byte data frames */
	spic_rtl_set_ctrl1(spic_dev, 1);

	/* send flash rx command and read the data */
	spic_ns_rx_cmd(phal_spic_adaptor, cmd, 0, 0);

	/* set ctrlr1; 1 byte data frames */
	rd_data = HAL_READ8(SPIC_BASE, 0x60);

	return rd_data;
}

/** \brief Description of flash_ns_get_status_with_addr
 *
 *    flash_ns_get_status_with_addr is used to send read status register command.
 *    Each flash may have more than one status registers that can be accessed with different instructions.
 *    A address byte followed by the instruction is sent to identify which status register.
 *    Please refer to flash data sheet for more details
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:     The instruction of read status register command.
 *   \param u8 addr:    The address byte of read status register command.
 *
 *   \return u8: the value of the status register.
 */

u8 flash_ns_get_status_with_addr(void *adaptor, u8 cmd, u8 addr)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	u32 rd_data;

	/* disable spi_flash user mode */
	spic_rtl_disable(spic_dev);

	/* set ctrlr1; 1 byte data frames */
	spic_rtl_set_ctrl1(spic_dev, 1);

	/* send flash rx command and read the data */
	spic_ns_rx_cmd(phal_spic_adaptor, cmd, 1, &addr);

	rd_data = HAL_READ8(SPIC_BASE, 0x60);

	return rd_data;
}

/** \brief Description of flash_ns_get_extended_addr
 *
 *    flash_ns_get_extended_addr is used to send read extended address register command.
 *    The value of the extended address register presents the fourth byte of the address phase.
 *    Some flashes cannot support this feature, please refer to flash data sheets.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return u8: the value of the extended addr register.
 */

u8 flash_ns_get_extended_addr(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	u32 rd_data;

	/* disable spi_flash user mode */
	spic_rtl_disable(spic_dev);

	/* set ctrlr1; 1 byte data frames */
	spic_rtl_set_ctrl1(spic_dev, 1);

	/* send flash rx command and read the data */
	spic_ns_rx_cmd(phal_spic_adaptor, cmd->rear, 0, 0);

	rd_data = HAL_READ8(SPIC_BASE, 0x60);

	return rd_data;
}

/** \brief Description of flash_ns_wait_ready
 *
 *    flash_ns_wait_ready is used to check the BUSY/WIP bit of the status register.
 *    This function polls the BUSY/WIP of the status register until flash returns to ready state.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_wait_ready(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 flash_type = phal_spic_adaptor->flash_type;

	DBG_SPIF_INFO("flash_ns_wait_ready: (0x%x)\n", adaptor);

	if (flash_type == FLASH_TYPE_MICRON) {
		do {
		} while (!(flash_ns_get_status(adaptor, cmd->rdsr2) & 0x80));
	} else {
		do {
		} while (flash_ns_get_status(adaptor, cmd->rdsr) & 0x1);
	}
}

/** \brief Description of flash_ns_chip_erase
 *
 *    flash_ns_chip_erase is used to send chip erase command.
 *    This function aims to erase whole flash chip.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_chip_erase(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd(phal_spic_adaptor, cmd->ce, 0, 0);
}

/** \brief Description of flash_ns_64k_block_erase
 *
 *    flash_ns_64k_block_erase is used to send 64K block erase command.
 *    This function aims to erase 64K byte blocks.
 *    The address is aligned to 64K byte boundaries.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to be erased.
 *
 *   \return void.
 */

void flash_ns_64k_block_erase(void *adaptor, u32 address)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 addr[4];
	u8 addr_byte_num = phal_spic_adaptor->addr_byte_num;

	if (FourBytesLength == addr_byte_num) {
		addr[3] = address & 0xFF;
		addr[2] = (address >> 8) & 0xFF;
		addr[1] = (address >> 16) & 0xFF;
		addr[0] = (address >> 24) & 0xFF;
	} else {
		addr[2] = address & 0xFF;
		addr[1] = (address >> 8) & 0xFF;
		addr[0] = (address >> 16) & 0xFF;
	}

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd(phal_spic_adaptor, cmd->be_64k, addr_byte_num, addr);
}

/** \brief Description of flash_ns_32k_block_erase
 *
 *    flash_ns_32k_block_erase is used to send 32K block erase command.
 *    This function aims to erase 32K byte blocks.
 *    The address is aligned to 32K byte boundaries.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to be erased.
 *
 *   \return void.
 */

void flash_ns_32k_block_erase(void *adaptor, u32 address)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 addr[4];
	u8 addr_byte_num = phal_spic_adaptor->addr_byte_num;

	if (FourBytesLength == addr_byte_num) {
		addr[3] = address & 0xFF;
		addr[2] = (address >> 8) & 0xFF;
		addr[1] = (address >> 16) & 0xFF;
		addr[0] = (address >> 24) & 0xFF;
	} else {
		addr[2] = address & 0xFF;
		addr[1] = (address >> 8) & 0xFF;
		addr[0] = (address >> 16) & 0xFF;
	}

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd(phal_spic_adaptor, cmd->be_32k, addr_byte_num, addr);
}

/** \brief Description of flash_ns_sector_erase
 *
 *    flash_ns_sector_erase is used to send sector erase command.
 *    This function aims to erase 4K byte sectors.
 *    The address is aligned to 4K byte boundaries.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to be erased.
 *
 *   \return void.
 */

void flash_ns_sector_erase(void *adaptor, u32 address)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 addr[4];
	u8 addr_byte_num = phal_spic_adaptor->addr_byte_num;

	if (FourBytesLength == addr_byte_num) {
		addr[3] = address & 0xFF;
		addr[2] = (address >> 8) & 0xFF;
		addr[1] = (address >> 16) & 0xFF;
		addr[0] = (address >> 24) & 0xFF;
	} else {
		addr[2] = address & 0xFF;
		addr[1] = (address >> 8) & 0xFF;
		addr[0] = (address >> 16) & 0xFF;
	}

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd(phal_spic_adaptor, cmd->se, addr_byte_num, addr);
}

/** \brief Description of flash_ns_query_sector_protect_state
 *
 *    flash_ns_query_sector_protect_state is used to query the sector's write protect status.
 *    This function is only valid for flashes supporting individual block protect or sector protect feature.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to query write protect state.
 *
 *   \return u8: the write protect status.
 */

u8 flash_ns_query_sector_protect_state(void *adaptor, u32 address)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	SPIC_TypeDef *spic_dev = phal_spic_adaptor->spic_dev;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 addr[4];
	u8 addr_byte_num = phal_spic_adaptor->addr_byte_num;
	u8 rd_data = 0;

	if (FourBytesLength == addr_byte_num) {
		addr[3] = address & 0xFF;
		addr[2] = (address >> 8) & 0xFF;
		addr[1] = (address >> 16) & 0xFF;
		addr[0] = (address >> 24) & 0xFF;
		addr_byte_num = 4;
	} else {
		addr[2] = address & 0xFF;
		addr[1] = (address >> 8) & 0xFF;
		addr[0] = (address >> 16) & 0xFF;
	}

	spic_rtl_disable(spic_dev);

	/* set ctrlr1; 1 byte data frames */
	spic_rtl_set_ctrl1(spic_dev, 1);

	/* send flash rx command and read the data */
	spic_ns_rx_cmd(phal_spic_adaptor, cmd->rd_block_lock, addr_byte_num, addr);

	/* set ctrlr1; 1 byte data frames */
	rd_data = HAL_READ8(SPIC_BASE, 0x60);

	return rd_data;
}

/** \brief Description of flash_ns_protect_sector
 *
 *    flash_ns_protect_sector is used to send individual write protect command.
 *    This function is only valid for flashes supporting individual block protect or sector protect feature.
 *    For actual protect regions depending on flash types.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to enable write protect.
 *
 *   \return void.
 */

void flash_ns_protect_sector(void *adaptor, u32 address)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 addr[4];
	u8 addr_byte_num = phal_spic_adaptor->addr_byte_num;

	if (FourBytesLength == addr_byte_num) {
		addr[3] = address & 0xFF;
		addr[2] = (address >> 8) & 0xFF;
		addr[1] = (address >> 16) & 0xFF;
		addr[0] = (address >> 24) & 0xFF;
	} else {
		addr[2] = address & 0xFF;
		addr[1] = (address >> 8) & 0xFF;
		addr[0] = (address >> 16) & 0xFF;
	}

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd(phal_spic_adaptor, cmd->block_lock, addr_byte_num, addr);

}

/** \brief Description of flash_ns_unprotect_sector
 *
 *    flash_ns_unprotect_sector is used to send individual write unprotect command.
 *    This function is only valid for flashes supporting individual block protect or sector protect feature.
 *    For actual protect regions depending on flash types.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to disable write protect.
 *
 *   \return void.
 */

void flash_ns_unprotect_sector(void *adaptor, u32 address)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 addr[4];
	u8 addr_byte_num = phal_spic_adaptor->addr_byte_num;

	if (FourBytesLength == addr_byte_num) {
		addr[3] = address & 0xFF;
		addr[2] = (address >> 8) & 0xFF;
		addr[1] = (address >> 16) & 0xFF;
		addr[0] = (address >> 24) & 0xFF;
	} else {
		addr[2] = address & 0xFF;
		addr[1] = (address >> 8) & 0xFF;
		addr[0] = (address >> 16) & 0xFF;
	}

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd(phal_spic_adaptor, cmd->block_unlock, addr_byte_num, addr);

}

/** \brief Description of flash_ns_global_lock
 *
 *    flash_ns_global_lock is used to send whole chip write protect command.
 *    This function is only valid some of Winbond flash.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_global_lock(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd(phal_spic_adaptor, cmd->global_lock, 0, 0);
}

/** \brief Description of flash_ns_global_unlock
 *
 *    flash_ns_global_unlock is used to send whole chip write unprotect command.
 *    This function is only valid some of Winbond flash.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_global_unlock(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;

	flash_ns_set_write_enable(phal_spic_adaptor);
	spic_ns_tx_cmd(phal_spic_adaptor, cmd->global_unlock, 0, 0);
}

/** \brief Description of flash_ns_set_dummy_cycle
 *
 *    flash_ns_set_dummy_cycle is used to configure flash dummy cycle.
 *    Flash allows users to adjust dummy cycles with various operting frequency under multiple IO modes.
 *    Higher speed requires more dummy cycles.
 *    We take into account the SPIC clock source and performance to derive optimal operating frequnecy of flash.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_set_dummy_cycle(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	u8 dummy_para = 0;
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;
	u8 flash_type = phal_spic_adaptor->flash_type;

	if (FLASH_TYPE_WINBOND == flash_type) {
		if ((spic_bit_mode == SpicQpiMode) || (spic_bit_mode == SpicQpiDtrMode)) {
			dummy_para = 0x20;
			spic_ns_tx_cmd_no_check(phal_spic_adaptor, 0xC0, 1, &dummy_para);
		}
	}
}

/** \brief Description of flash_ns_set_quad_enable
 *
 *    flash_ns_set_quad_enable is used to set quad enable bit of flash.
 *    Some flash types require flash to set quad enable bit before switching to Quad IO mode.
 *    Only Winbond and MXIC supports this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_set_quad_enable(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 flash_type = phal_spic_adaptor->flash_type;
	u8 status_value = 0;

	u8 data[2];

	switch (flash_type) {
	case FLASH_TYPE_WINBOND:
	case FLASH_TYPE_GD32:
	case FLASH_TYPE_BOYA:
	case FLASH_TYPE_XMC:
	case FLASH_TYPE_ZBIT:
		status_value = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr2);
		if ((status_value & 0x2) == 0) {
			flash_ns_set_status(phal_spic_adaptor, cmd->wrsr2, 0x2 | status_value);
		}
		break;

	case FLASH_TYPE_MXIC:
		status_value = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr);
		if ((status_value & 0x40) == 0) {
			flash_ns_set_status(phal_spic_adaptor, cmd->wrsr, 0x40 | status_value);
		}
		break;

	case FLASH_TYPE_GD:
	case FLASH_TYPE_XTX:
		data[1] = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr2);
		if ((data[1] & 0x2) == 0) {
			data[0] = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr);
			data[1] |= 0x2;
			flash_ns_set_write_enable(phal_spic_adaptor);
			spic_ns_tx_cmd(phal_spic_adaptor, cmd->wrsr, 2, data);
		}
		break;

	case FLASH_TYPE_EON:
		break;

	default:
		DBG_SPIF_ERR("Unknown flash type, cannot set QE bit!\n");
	}
}

/** \brief Description of flash_ns_unset_quad_enable
 *
 *    flash_ns_unset_quad_enable is used to clear quad enable bit of flash.
 *    Quad IO bit should be cleaned before switching to other non-Quad IO mode.
 *    Only Winbond and MXIC supports this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_unset_quad_enable(void *adaptor)
{
	/*Keep QE bit even when flash returns to One IO mode*/
#if 0
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 flash_type = phal_spic_adaptor->flash_type;
	u8 status_value = 0;
	u8 data[2];

	switch (flash_type) {
	case FLASH_TYPE_GD32:
	case FLASH_TYPE_BOYA:
	case FLASH_TYPE_XMC:
	case FLASH_TYPE_ZBIT:
		status_value = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr2);
		flash_ns_set_status(phal_spic_adaptor, cmd->wrsr2, ~0x2 & status_value);
		break;

	case FLASH_TYPE_MXIC:
		status_value = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr);
		flash_ns_set_status(phal_spic_adaptor, cmd->wrsr, ~0x40 & status_value);
		break;

	case FLASH_TYPE_GD:
	case FLASH_TYPE_XTX:
		data[0] = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr);
		data[1] = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr2) & (~0x2);
		flash_ns_set_write_enable(phal_spic_adaptor);
		spic_ns_tx_cmd(phal_spic_adaptor, cmd->wrsr, 2, data);
		break;

	case FLASH_TYPE_EON:
	case FLASH_TYPE_MICRON:
	case FLASH_TYPE_WINBOND:
		break;

	default:
		DBG_SPIF_ERR("Unknown flash type, cannot reset QE bit!\n");
	}
#endif
}

/** \brief Description of flash_ns_enable_qpi
 *
 *    flash_ns_enable_qpi is used to switch flash to QPI mode (4-4-4).
 *    Quad enable bit is set before SPIC sends enter QPI mode command.
 *    Only Adesto, Winbond and MXIC supports this function.
 *    Must ensure flash is under SPI mode before CPU enters this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_enable_qpi(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 flash_type = phal_spic_adaptor->flash_type;
	u8 status_value = 0;

	phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;

	switch (flash_type) {
	case FLASH_TYPE_WINBOND:
		status_value = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr2);
		if ((status_value & 0x2) == 0) {
			flash_ns_set_status(phal_spic_adaptor, cmd->wrsr2, 0x2 | status_value);
		}
		spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->en_qpi, 0, 0);
		/*if QPI works, change with check*/
		break;

	case FLASH_TYPE_MXIC:
		status_value = flash_ns_get_status(phal_spic_adaptor, cmd->rdsr);
		if ((status_value & 0x40) == 0) {
			flash_ns_set_status(phal_spic_adaptor, cmd->wrsr, 0x40 | status_value);
		}
		spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->en_qpi, 0, 0);
		/*if QPI works, change with check*/
		break;

	case FLASH_TYPE_EON:
		spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->en_qpi, 0, 0);

	case FLASH_TYPE_MICRON:
		break;

	default:
		DBG_SPIF_ERR("Unknown flash type, cannot switch to QPI mode!\n");
	}

	phal_spic_adaptor->spic_send_cmd_mode = QuadChnl;
	phal_spic_adaptor->cmd_chnl = QuadChnl;
	phal_spic_adaptor->addr_chnl = QuadChnl;
	phal_spic_adaptor->data_chnl = QuadChnl;
	spic_ns_set_chnl_num(phal_spic_adaptor);
	flash_ns_set_dummy_cycle(phal_spic_adaptor);
}

/** \brief Description of flash_ns_return_spi
 *
 *    flash_ns_return_spi is used to switch flash back to SPI mode.
 *    Unlike flash_reset_to_spi function recovering flash back to SPI mode from abnormal state,
 *    this funciton is a bridge to switch between different IO mode when flash is under control.
 *    Every IO mode should call this function to switch back to SPI mode before flash enters the other IO mode.
 *    Only Adesto, Winbond and MXIC support this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_return_spi(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u32 reg_value;
	spic_init_para_t spic_init_data;
	pspic_init_para_t pspic_init_data = &spic_init_data;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	u8 spic_send_cmd_mode = phal_spic_adaptor->spic_send_cmd_mode;
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;
	u8 cpu_type = spic_ns_query_system_clk();

	if (phal_spic_adaptor->spic_init_data[SpicOneIOMode][cpu_type].valid) {
		pspic_init_data = &(phal_spic_adaptor->spic_init_data[SpicOneIOMode][cpu_type]);
	} else {
		spic_ns_load_default_setting(pspic_init_data);
	}

	/*Disable SPIC to set control register*/
	spic_rtl_disable(spic_dev);

	/*Send cmd to switch from QPI to SPI mode, if QPI works, change with check for non-adesto*/
	if (spic_send_cmd_mode == QuadChnl) {
		spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->en_spi, 0, 0);
	}

	phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;
	phal_spic_adaptor->cmd_chnl = SingleChnl;
	phal_spic_adaptor->addr_chnl = SingleChnl;
	phal_spic_adaptor->data_chnl = SingleChnl;
	spic_ns_set_chnl_num(phal_spic_adaptor);
	flash_ns_return_str(phal_spic_adaptor);
	flash_ns_wait_ready(phal_spic_adaptor);

	if ((spic_bit_mode == SpicQuadIOMode)
		|| (spic_bit_mode == SpicQuadIODtrMode)
		|| (spic_bit_mode == SpicQpiMode)
		|| (spic_bit_mode == SpicQpiDtrMode)) {
		flash_ns_unset_quad_enable(phal_spic_adaptor);
	}

	/*Restore back to one IO auto mode*/
	spic_dev->SPIC_VALID_CMD = SPIC_BIT_WR_BLOCKING;

	/*Resotre back to one IO user mode*/
	phal_spic_adaptor->spic_bit_mode = SpicOneIOMode;
	phal_spic_adaptor->read_cmd = cmd->read;
	phal_spic_adaptor->addr_byte_num = ThreeBytesLength;
	reg_value = spic_dev->SPIC_AUTO_LENGTH;
	reg_value &= ~SPIC_MASK_AUTO_ADDR_LENGTH;
	reg_value |= (phal_spic_adaptor->addr_byte_num << SPIC_SHIFT_AUTO_ADDR_LENGTH);
	spic_dev->SPIC_AUTO_LENGTH = reg_value;
	spic_dev->SPIC_ADDR_LENGTH = phal_spic_adaptor->addr_byte_num;

	spic_rtl_set_dummy_cycle(spic_dev, pspic_init_data->rd_dummy_cycle);
	spic_rtl_set_baudr(spic_dev, pspic_init_data->baud_rate);
	spic_ns_set_delay_line(pspic_init_data->delay_line);
}

/** \brief Description of flash_ns_return_str
 *
 *    flash_ns_return_str is used to set SPIC, not flash, to STR mode
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */

void flash_ns_return_str(void *adaptor)
{
	//SYSON_S_TypeDef *syson_s = SYSON_S;
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	u32 reg_ctrl_value;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;

	phal_spic_adaptor->dtr_en = DISABLE;
	reg_ctrl_value = spic_dev->SPIC_CTRLR0;
	reg_ctrl_value &= ~(SPIC_BIT_CMD_DDR_EN | SPIC_BIT_DATA_DDR_EN | SPIC_BIT_ADDR_DDR_EN);
	spic_dev->SPIC_CTRLR0 = reg_ctrl_value;

	/*Disable DTR PHY*/
	//syson_s->SYSON_S_REG_SYS_FLASH_PHY_CTRL0 &= ~SYSON_S_BIT_FLASH_PHY_DQS_DDR_EN;
	hal_sys_spic_ddr_ctrl(DISABLE);
}

/** \brief Description of flash_ns_enter_power_down
 *
 *    flash_ns_enter_power_down is used to send deep power down command.
 *    Flash enters deep power down state after this function.
 *    Any access except few commands is ignored by flash.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return hal_status_t.
 */

hal_status_t flash_ns_enter_power_down(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;

	flash_ns_wait_ready(phal_spic_adaptor);
	spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->dp, 0, 0);

	dcache_invalidate_by_addr((uint32_t *) SPI_FLASH_BASE, 32);
	if (HAL_READ32(SPI_FLASH_BASE, 0x0) == spic_calibration_pattern[0]) {
		DBG_SPIF_ERR("Flash fails to enter power down mode\n");
		return HAL_ERR_HW;
	}

	DBG_SPIF_WARN("Flash enters power down mode\n");
	return HAL_OK;
}

/** \brief Description of flash_ns_release_from_power_down
 *
 *    flash_ns_release_from_power_down is used to send release from deep power down command.
 *    Flash returns from deep power down state after this function.
 *    It can accept any command normally.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return hal_status_t.
 */

hal_status_t flash_ns_release_from_power_down(void *adaptor)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	pflash_cmd_t cmd = (pflash_cmd_t)&default_cmd;

	spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->rdp, 0, 0);
	hal_delay_us(100);

	spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->wren, 0, 0);
	if (flash_ns_get_status(phal_spic_adaptor, cmd->rdsr) & 0x2) {
		spic_ns_tx_cmd_no_check(phal_spic_adaptor, cmd->wrdi, 0, 0);
	} else {
		DBG_SPIF_WARN("Flash may fail to release from power down mode\n");
		return HAL_ERR_HW;
	}

	DBG_SPIF_WARN("Flash releases from power down mode\n");
	return HAL_OK;
}

/** \brief Description of flash_ns_stream_read
 *
 *    flash_ns_stream_read is used to read sequential data with auto mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting read address in flash.
 *   \param u8 *data:      The destination address in memory to store data.
 *
 *   \return void.
 */

void flash_ns_stream_read(void *adaptor, u32 length, u32 addr, u8 *data)
{
	u32 rd_data;
	u32 *tmp;
	u8 *ptr;

	tmp = (u32 *)data;
	while (length >= 4) {
		*tmp = HAL_READ32(SPI_FLASH_BASE, addr);
		addr += 4;
		tmp++;
		length -= 4;
	}

	data = (u8 *)tmp;
	if (length > 0) {
		rd_data = HAL_READ32(SPI_FLASH_BASE, addr);
		ptr = (u8 *)&rd_data;
		while (length > 0) {
			*data = *ptr;
			ptr++;
			data++;
			length--;
		}
	}
}

/** \brief Description of flash_ns_stream_write
 *
 *    flash_ns_stream_write is used to program sequential data with auto mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting program address in flash.
 *   \param u8 *data:      The address of data. Data stored in ram is about to be programmed to the flash.
 *
 *   \return void.
 */

void flash_ns_stream_write(void *adaptor, u32 length, u32 addr, u8 *data)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	u8 offset_to_align;
	u32 i;
	u32 align_addr;
	u32 write_word = 0;
	uint8_t *ptr;

	offset_to_align = addr & 0x3;
	if (offset_to_align) {
		align_addr = addr - offset_to_align;
		write_word = HAL_READ32(SPI_FLASH_BASE, align_addr);
		ptr = (uint8_t *)&write_word + offset_to_align;

		for (i = 0; i < (4 - offset_to_align); i++) {
			*(ptr + i) = *(data + i);
			length--;
			if (length == 0) {
				break;
			}
		}

		data += (4 - offset_to_align);
		HAL_WRITE32(SPI_FLASH_BASE, align_addr, write_word);
		dcache_invalidate_by_addr((uint32_t *) SPI_FLASH_BASE + align_addr, 4);
		flash_ns_wait_ready(phal_spic_adaptor);
	}

	addr = (((addr - 1) >> 2) + 1) << 2;

	if (((u32)data) & 0x3) {
		while (length >= 4) {
			write_word  = ((u32)(*data)) | ((u32)(*(data + 1)) << 8) | ((u32)(*(data + 2)) << 16) | ((u32)(*(data + 3)) << 24);
			HAL_WRITE32(SPI_FLASH_BASE, addr, write_word);
			dcache_invalidate_by_addr((uint32_t *) SPI_FLASH_BASE + addr, 4);
			flash_ns_wait_ready(phal_spic_adaptor);
			data += 4;
			addr += 4;
			length -= 4;
		}
	} else {
		while (length >= 4) {
			HAL_WRITE32(SPI_FLASH_BASE, addr, (u32) * ((u32 *)data));
			dcache_invalidate_by_addr((uint32_t *) SPI_FLASH_BASE + addr, 4);
			flash_ns_wait_ready(phal_spic_adaptor);
			data += 4;
			addr += 4;
			length -= 4;
		}
	}

	if (length > 0) {
		ptr = (uint8_t *)&write_word;
		for (i = 0; i < length; i++) {
			*(ptr + i) = *(data + i);
		}

		HAL_WRITE32(SPI_FLASH_BASE, addr, write_word);
		dcache_invalidate_by_addr((uint32_t *) SPI_FLASH_BASE + addr, 4);
		flash_ns_wait_ready(phal_spic_adaptor);
	}

}

/** \brief Description of flash_ns_burst_read
 *
 *    flash_ns_burst_read is used to read sequential data with user mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting read address in flash.
 *   \param u8 *data:      The destination address in memory to store data.
 *
 *   \return void.
 */

void flash_ns_burst_read(void *adaptor, u32 length, u32 addr, u8 *data)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	u32 rd_data;
	u32 tmp;
	u32 transfer_byte = 0;
	u32 reg_value = 0;
	u8 addr_byte[4];
	u8 *ptr;
	u8 *buf;
	u8 i;
	u8 addr_byte_num;
	u8 ndf_limit = 64;
	u8 read_cmd = phal_spic_adaptor->read_cmd;
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;
	u32 *temp;

	buf = data;
	temp = (u32 *) buf;
	ptr = (u8 *) &rd_data;
	addr_byte_num = phal_spic_adaptor->addr_byte_num;

	spic_rtl_disable(spic_dev);

	spic_dev->SPIC_VALID_CMD &= ~SPIC_BIT_PRM_EN;

	/* Set rx mode */
	reg_value = spic_dev->SPIC_CTRLR0;
	reg_value &= ~SPIC_MASK_TMOD;
	reg_value |= (RxMode << SPIC_SHIFT_TMOD);
	spic_dev->SPIC_CTRLR0 = reg_value;

	/* Set length of address byte */
	spic_dev->SPIC_ADDR_LENGTH = addr_byte_num;

	spic_ns_set_chnl_num(phal_spic_adaptor);

	addr_byte[3] = (addr & 0xFF000000) >> 24;
	addr_byte[2] = (addr & 0xFF0000) >> 16;
	addr_byte[1] = (addr & 0xFF00) >> 8;
	addr_byte[0] = addr & 0xFF;

	if (addr_byte_num == 3) {
		tmp = read_cmd | (addr_byte[2] << 8) | (addr_byte[1] << 16) | (addr_byte[0] << 24);
		spic_dev->SPIC_DR_WORD = tmp;

		if ((SpicQuadIOMode == spic_bit_mode)
			|| (SpicQpiMode == spic_bit_mode)
			|| (SpicQuadIODtrMode == spic_bit_mode)
			|| (SpicQpiDtrMode == spic_bit_mode)) {
			spic_dev->SPIC_ADDR_LENGTH = 0;
			HAL_WRITE8(SPIC_BASE, 0x60, 0);
		}
	} else {
		HAL_WRITE8(SPIC_BASE, 0x60, read_cmd);
		tmp = addr_byte[3] | (addr_byte[2] << 8) | (addr_byte[1] << 16) | (addr_byte[0] << 24);
		spic_dev->SPIC_DR_WORD = tmp;

		if ((SpicQuadIOMode == spic_bit_mode)
			|| (SpicQpiMode == spic_bit_mode)
			|| (SpicQuadIODtrMode == spic_bit_mode)
			|| (SpicQpiDtrMode == spic_bit_mode)) {
			spic_dev->SPIC_ADDR_LENGTH = 4;
			HAL_WRITE8(SPIC_BASE, 0x60, 0);
		}
	}


	if (length <= ndf_limit) {
		spic_rtl_set_ctrl1(spic_dev, length);
	} else {
		spic_rtl_set_ctrl1(spic_dev, ndf_limit);
	}

	/* Enable SPI_FLASH  User Mode to receive data*/
	spic_rtl_enable(spic_dev);

	spic_ns_wait_ready(spic_dev);

	while (length > 0) {
		if (transfer_byte >= ndf_limit) {

			addr += ndf_limit;
			transfer_byte = 0;
			addr_byte[3] = (addr & 0xFF000000) >> 24;
			addr_byte[2] = (addr & 0xFF0000) >> 16;
			addr_byte[1] = (addr & 0xFF00) >> 8;
			addr_byte[0] = addr & 0xFF;

			spic_rtl_disable(spic_dev);

			if (addr_byte_num == 3) {
				tmp = read_cmd | (addr_byte[2] << 8) | (addr_byte[1] << 16) | (addr_byte[0] << 24);
				spic_dev->SPIC_DR_WORD = tmp;
			} else {
				HAL_WRITE8(SPIC_BASE, 0x60, read_cmd);
				tmp = addr_byte[3] | (addr_byte[2] << 8) | (addr_byte[1] << 16) | (addr_byte[0] << 24);
				spic_dev->SPIC_DR_WORD = tmp;
			}

			if ((SpicQuadIOMode == spic_bit_mode)
				|| (SpicQpiMode == spic_bit_mode)
				|| (SpicQuadIODtrMode == spic_bit_mode)
				|| (SpicQpiDtrMode == spic_bit_mode)) {
				HAL_WRITE8(SPIC_BASE, 0x60, 0);
			}

			if (length <= ndf_limit) {
				spic_rtl_set_ctrl1(spic_dev, length);
			} else {
				spic_rtl_set_ctrl1(spic_dev, ndf_limit);
			}

			spic_rtl_enable(spic_dev);
			spic_ns_wait_ready(spic_dev);
		}

		rd_data = spic_dev->SPIC_DR_WORD;
		if (length >= 4) {
			temp = (u32 *) buf;
			*temp = rd_data;
			temp++;
			buf += 4;
			length -= 4;
			transfer_byte += 4;

		} else {
			buf = (u8 *) temp;

			for (i = 0; i < length; i++) {
				*buf = *(ptr + i);
				buf++;
			}

			length = 0;
		}
	}

	/* disable spi_flash user mode */
	spic_rtl_disable(spic_dev);

	spic_dev->SPIC_VALID_CMD |= SPIC_BIT_PRM_EN;

	/* flush fifo */
	spic_ns_flush_fifo(spic_dev);
}

/** \brief Description of flash_ns_burst_write
 *
 *    flash_ns_burst_write is used to program sequential data with user mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting program address in flash.
 *   \param u8 *data:      The address of data. Data stored in ram is about to be programmed to the flash.
 *
 *   \return void.
 */

void flash_ns_burst_write(void *adaptor, u32 length, u32 addr, u8 *data)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	u32 existed_data_size;
	u32 program_size;
	u32 page_size;

	page_size = 256;
	existed_data_size = addr & 0xFF;

	if ((length >= page_size)
		|| ((length + existed_data_size) >= page_size)) {
		program_size = page_size - existed_data_size;
	} else {
		program_size = length;
	}

	while (length > 0) {
		if (existed_data_size) {
			flash_ns_page_program(phal_spic_adaptor, program_size, addr, data);
			addr += program_size;
			data += program_size;
			length -= program_size;
			existed_data_size = 0;
		} else {
			while (length >= page_size) {
				flash_ns_page_program(phal_spic_adaptor, page_size, addr, data);
				addr += page_size;
				data += page_size;
				length -= page_size;
			}

			if (length > 0) {
				flash_ns_page_program(phal_spic_adaptor, length, addr, data);
				break;
			}
		}
	}
}

/** \brief Description of flash_ns_page_program
 *
 *    flash_ns_page_program is used to divide total transfer length into several pages.
 *    Each page program command can program 256 bytes, a page size, at most.
 *    Multiple program commands should be sent if the transfer length is larger than the page size.
 *    Please refer to flash data sheets about page program command for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting program address in flash.
 *   \param u8 *data:      The address of data. Data stored in ram is about to be programmed to the flash.
 *
 *   \return void.
 */

void flash_ns_page_program(void *adaptor, u32 length, u32 addr, u8 *data)
{
	phal_spic_adaptor_t phal_spic_adaptor = (phal_spic_adaptor_t) adaptor;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u32 reg_ctrl_value;
	u32 occu_size;
	u32 program_length;
	u32 page_size;
	u32 tmp;
	u8 addr_byte[4];
	u8 spic_send_cmd_mode;
	u8 cmd_ddr_en;
	u8 addr_ddr_en;
	u8 data_ddr_en;
	u8 addr_byte_num;
	u8 buffer[256];
	u8 *ptr = &buffer[0];
	u8 nop_index = 0;
	u8 nop_delay = 160;

	page_size = 256;
	occu_size = addr & 0xFF;

	if (phal_spic_adaptor->write_delay != 0) {
		nop_delay = phal_spic_adaptor->write_delay;
	}

	if (((u32)data >> 24) == 0x8) {
		flash_ns_stream_read(phal_spic_adaptor, length, (u32)data, buffer);
	}

	addr_byte_num = phal_spic_adaptor->addr_byte_num;
	spic_send_cmd_mode = phal_spic_adaptor->spic_send_cmd_mode;
	program_length = 0;

	/*Load ctrlr0 value to configure*/
	reg_ctrl_value = spic_dev->SPIC_CTRLR0;

	if (phal_spic_adaptor->dtr_en) {
		/*Save current ddr state*/
		cmd_ddr_en = (reg_ctrl_value & SPIC_BIT_CMD_DDR_EN) >> SPIC_SHIFT_CMD_DDR_EN;
		addr_ddr_en = (reg_ctrl_value & SPIC_BIT_ADDR_DDR_EN) >> SPIC_SHIFT_ADDR_DDR_EN;
		data_ddr_en = (reg_ctrl_value & SPIC_BIT_DATA_DDR_EN) >> SPIC_SHIFT_DATA_DDR_EN;

		/*Should program under STR mode*/
		reg_ctrl_value &= ~(SPIC_BIT_CMD_DDR_EN | SPIC_BIT_ADDR_DDR_EN | SPIC_BIT_DATA_DDR_EN);
	}

	if (occu_size) {
		if ((length >= page_size)
			|| ((occu_size + length) >= page_size)) {
			program_length = page_size - occu_size;
		} else {
			program_length = length;
		}
	} else {//program from the beginning of the page
		if (length >= page_size) {
			program_length = page_size;
		} else {
			program_length = length;
		}
	}

	/* Set writen enable bit */
	flash_ns_set_write_enable(phal_spic_adaptor);

	/* Disable spic in user mode */
	spic_rtl_disable(spic_dev);

	spic_dev->SPIC_VALID_CMD &= ~SPIC_BIT_PRM_EN;

	addr_byte[3] = (addr & 0xFF000000) >> 24;
	addr_byte[2] = (addr & 0xFF0000) >> 16;
	addr_byte[1] = (addr & 0xFF00) >> 8;
	addr_byte[0] = addr & 0xFF;

	if (addr_byte_num == 3) {
		tmp = (cmd->pp) | (addr_byte[2] << 8) | (addr_byte[1] << 16) | (addr_byte[0] << 24);
		spic_dev->SPIC_DR_WORD = tmp;
	} else {
		HAL_WRITE8(SPIC_BASE, 0x60, cmd->pp);
		tmp = addr_byte[3] | (addr_byte[2] << 8) | (addr_byte[1] << 16) | (addr_byte[0] << 24);
		spic_dev->SPIC_DR_WORD = tmp;
	}

	/* Set tx mode*/
	reg_ctrl_value &= ~SPIC_MASK_TMOD;
	reg_ctrl_value |= (TxMode << SPIC_SHIFT_TMOD);

	/* Set length of address byte */
	spic_dev->SPIC_ADDR_LENGTH = addr_byte_num;

	/*Program can be executed only with 1-1-1, 4-4-4, 8-8-8 mode*/
	switch (spic_send_cmd_mode) {
	case SingleChnl:
		reg_ctrl_value &= ~(SPIC_MASK_ADDR_CH | SPIC_MASK_DATA_CH | SPIC_MASK_CMD_CH);
		reg_ctrl_value |= ((SingleChnl << SPIC_SHIFT_CMD_CH) | (SingleChnl << SPIC_SHIFT_DATA_CH) | (SingleChnl << SPIC_SHIFT_ADDR_CH));
		break;

	case QuadChnl:
		reg_ctrl_value &= ~(SPIC_MASK_ADDR_CH | SPIC_MASK_DATA_CH | SPIC_MASK_CMD_CH);
		reg_ctrl_value |= ((QuadChnl << SPIC_SHIFT_CMD_CH) | (QuadChnl << SPIC_SHIFT_DATA_CH) | (QuadChnl << SPIC_SHIFT_ADDR_CH));
		break;

	default:
		DBG_SPIF_ERR("Wrong IO Mode to program!\n");
	}

	spic_dev->SPIC_CTRLR0 = reg_ctrl_value;

	/*Set Ctrl2 to enable data split program*/
	spic_dev->SPIC_CTRLR2 |= SPIC_BIT_SEQ_EN;

	if (((u32)data >> 24) == 0x8) {
		data = ptr;
	}

	/* Enable spic in user mode */
	spic_rtl_enable(spic_dev);

	while (program_length >= 4) {
		spic_dev->SPIC_DR_WORD = (u32) * ((u32 *)data);
		program_length -= 4;
		data += 4;

		if (program_length != 0) {
			for (nop_index = 0; nop_index < nop_delay; nop_index++) {
				__NOP();
			}
		}
	}

	while (program_length > 0) {
		HAL_WRITE8(SPIC_BASE, 0x60, (u8)(*data));
		program_length--;
		data++;
	}

	/*Poll SPIC to get ready*/
	spic_ns_wait_ready(spic_dev);

	/*Poll Flash to get ready*/
	flash_ns_wait_ready(phal_spic_adaptor);

	/*Disable spic in user mode*/
	spic_rtl_disable(spic_dev);

	spic_dev->SPIC_CTRLR2 &= ~SPIC_BIT_SEQ_EN;

	spic_dev->SPIC_VALID_CMD |= SPIC_BIT_PRM_EN;

	/* Recover ddr state*/
	if (phal_spic_adaptor->dtr_en) {
		reg_ctrl_value = spic_dev->SPIC_CTRLR0;
		reg_ctrl_value |= (cmd_ddr_en << SPIC_SHIFT_CMD_DDR_EN) | (addr_ddr_en << SPIC_SHIFT_ADDR_DDR_EN) | (data_ddr_en << SPIC_SHIFT_DATA_DDR_EN);
		spic_dev->SPIC_CTRLR0 = reg_ctrl_value;
	}
}
/** *@} */ /* End of group hal_flash_ns_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/** *@} */

#endif
