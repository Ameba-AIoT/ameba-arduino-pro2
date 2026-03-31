/**************************************************************************//**
 * @file     rtl8195bhp_spic.c
 * @brief    Implement flash controller ROM code functions.
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
#include "hal_spic_ns.h"
#include "hal_flash_ns.h"
#include "hal_sys_ctrl_nsc.h"

/**

        \addtogroup hal_spic Flash Controller
        @{
*/


/**
  \brief The golden pattern to calibrate flash controller data path delay.
*/
const u32 spic_calibration_pattern[4] = {
	0x96969999,
	0xFC66CC3F,
	0x03CC33C0,
	0x6231DCE5
};

/// @cond DOXYGEN_ROM_HAL_API

/**

        \addtogroup hal_spic_ns_func Flash Controller HAL ROM APIs
        \ingroup hal_spic
        \brief Configure SPIC functions to control flash controller and communicate with a flash device.
               The user application(in RAM space) should not call these APIs directly.
               There is another set of Flash Controller HAL APIs in the RAM space is provided for the user application.
        @{
*/

//extern hal_status_t fw_spic_init(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode, u8 io_pin_sel);
//extern hal_status_t fw_spic_deinit(phal_spic_adaptor_t phal_spic_adaptor);

/**
  \brief The stubs functions table to exports flash controller HAL functions in ROM.
*/
const hal_spic_func_stubs_t hal_spic_stubs_ns = {
	.spic_load_default_setting = spic_ns_load_default_setting,
	.spic_query_system_clk = spic_ns_query_system_clk,
	.spic_clock_ctrl = spic_ns_clock_ctrl,
	.spic_init_setting = spic_ns_init_setting,
	.spic_config_dtr_read = spic_ns_config_dtr_read,
	.spic_config_auto_mode = spic_ns_config_auto_mode,
	.spic_config_user_mode = spic_ns_config_user_mode,
	.spic_verify_calibration_para = spic_ns_verify_calibration_para,
	.spic_set_chnl_num = spic_ns_set_chnl_num,
	.spic_set_delay_line = spic_ns_set_delay_line,
	.spic_rx_cmd = spic_ns_rx_cmd,
	.spic_tx_cmd_no_check = spic_ns_tx_cmd_no_check,
	.spic_tx_cmd = spic_ns_tx_cmd,
	.spic_wait_ready = spic_ns_wait_ready,
	.spic_flush_fifo = spic_ns_flush_fifo,
};


/** \brief Description of spic_ns_load_default_setting
 *
 *    spic_ns_load_default_setting is used to load default setting for One IO mode at low speed without calibration.
 *    The calibration includes baud rate, delay line and dummy cycles(associated with path delay).
 *
 *   \param pspic_init_para_t pspic_init_data:      The pointer of struct storing calibation settings.
 *
 *   \return void.
 */

void spic_ns_load_default_setting(pspic_init_para_t pspic_init_data)
{
	pspic_init_data->baud_rate = 5;
	pspic_init_data->delay_line = 0x31;
	pspic_init_data->rd_dummy_cycle = 4;
}


/** \brief Description of spic_ns_query_system_clk
 *
 *    spic_ns_query_system_clk is used to query current CPU clock.
 *    Different CPU speed will apply different calibration parameters to optimize the flash controller.
 *
 *   \param void.
 *
 *   \return u8: The macro definition of CPU clock.
 */

u8 spic_ns_query_system_clk(void)
{
	return 0;
#if 0
	u32 sys_clk = 0;

	sys_clk = hal_syson_query_sys_clk();

	switch (sys_clk) {
	case SYS_CLK_300M:
		return Clk300MHz;
		break;

	case SYS_CLK_200M:
		return Clk200MHz;
		break;

	case SYS_CLK_150M:
		return Clk150MHz;
		break;

	case SYS_CLK_100M:
		return Clk100MHz;
		break;

	case SYS_CLK_4M:
		return Clk4MHz;
		break;

	case SYS_CLK_2M:
		return Clk2MHz;
		break;

	default:
		DBG_SPIF_ERR("Invalid CPU CLK rate\r\n");
		return Clk300MHz;
	}
#endif
}


/** \brief Description of spic_ns_clock_ctrl
 *
 *    spic_ns_clock_ctrl is used to enable or disable the flash controller clock and function enable.
 *
 *   \param u8 ctl:      The control parameter.
 *
 *   \return void.
 */

void spic_ns_clock_ctrl(u8 ctl)
{
	hal_sys_peripheral_en(FLASH_SYS, ctl);
}

/** \brief Description of spic_ns_init_setting
 *
 *    spic_ns_init_setting is used to initialize the flash controller.
 *    The function and clock are enbaled at the first. Some parameters and registers are initialized afte that.
 *    Flash controller is set with One IO mode with low speed to ensure it can operate flash correctly without calibration procedure.
 *    If flash ID cannot be identified, a release from deep power down command is executed to wake the flash.
 *    A return to SPI command is executed followed by the release from deep power down command to ensure flash is under SPI mode.
 *    After these commands, a read ID command is issued to identify the flash type.
 *    For Adesto flash type, we should unlock flash so that the flash can be accessed correctly at the end of the functioin.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 spic_bit_mode:      The target IO mode the flash controller is going to operate.
 *
 *   \return hal_status_t.
 */

hal_status_t spic_ns_init_setting(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode)
{
	SPIC_TypeDef *spic_dev;
	//SYSON_S_TypeDef *syson_s = SYSON_S;
	pspic_init_para_t pspic_init_data = NULL;
	u8 cpu_type = spic_ns_query_system_clk();

	/*Turn ON spic clk*/
	spic_ns_clock_ctrl(ENABLE);

	/*Wait SPIC until ready*/
	while (hal_sys_spic_boot_finish() != SUCCESS);

	/*Enable Spic Rx*/
	//syson_s->SYSON_S_REG_SYS_FLASH_PHY_CTRL0 = SYSON_S_BIT_FLASH_PHY_EN;
	hal_sys_spic_phy_en();

	phal_spic_adaptor->spic_dev = SPIC;
	spic_dev = phal_spic_adaptor->spic_dev;

	phal_spic_adaptor->spic_bit_mode = spic_bit_mode;

	/*Initial Chnl mode*/
	spic_dev->SPIC_CTRLR0 = 0;

	/*Set slave select*/
	spic_dev->SPIC_SER = 1;

	/*Set dma mode*/
	spic_dev->SPIC_DMACR = 0;

	/*Disable Interrupt*/
	spic_dev->SPIC_IMR = 0;

	/*Disable PRM mode to prevent from flash entering this mode unexpectedly*/
	spic_dev->SPIC_READ_QUAD_ADDR_DATA &= ~SPIC_MASK_PRM_VALUE;

	/*Initialize valid command register*/
	spic_dev->SPIC_VALID_CMD = 0x200;

	/*Disable Auto Mode Write*/
	spic_dev->SPIC_WRITE_DUAL_ADDR_DATA = 0;
	spic_dev->SPIC_WRITE_DUAL_DATA = 0;
	spic_dev->SPIC_WRITE_ENABLE = 0;
	spic_dev->SPIC_WRITE_QUAD_ADDR_DATA = 0;
	spic_dev->SPIC_WRITE_QUAD_DATA = 0;
	spic_dev->SPIC_WRITE_SINGLE = 0;

	/*Initial send command mode, default is one IO*/
	phal_spic_adaptor->spic_send_cmd_mode = 0x0;

	/*Inital DTR enable, default is off*/
	phal_spic_adaptor->dtr_en = 0x0;


	pspic_init_data = &(phal_spic_adaptor->spic_init_data[SpicOneIOMode][cpu_type]);

	if (phal_spic_adaptor->spic_init_data[SpicOneIOMode][cpu_type].valid == 0) {
		spic_ns_load_default_setting(pspic_init_data);
	}

	spic_rtl_set_dummy_cycle(spic_dev, pspic_init_data->rd_dummy_cycle);
	spic_rtl_set_baudr(spic_dev, pspic_init_data->baud_rate);
	spic_ns_set_delay_line(pspic_init_data->delay_line);

	/*Read ID under one bit mode*/
	if (phal_spic_adaptor->flash_id[0] == 0x00) {
		if (HAL_OK != flash_ns_read_id(phal_spic_adaptor)) {
			flash_ns_reset_to_spi(phal_spic_adaptor);
			if (HAL_OK != flash_ns_read_id(phal_spic_adaptor)) {
				return HAL_ERR_HW;
			}
		}
	}

	phal_spic_adaptor->write_delay = 0;

	return HAL_OK;
}

/** \brief Description of spic_ns_config_dtr_read
 *
 *    spic_ns_config_dtr_read is used to configurate flash controller so that it can read data correctly with DTR mode .
 *    1-4D-4D, 4D-4D-4D, 8D-8D-8D modes access should call this function first.
 *    x-y-z : x is IO mode of command phase, y is IO mode of address phase, z is IO mode of data phase. D stands for DTR mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */

void spic_ns_config_dtr_read(phal_spic_adaptor_t phal_spic_adaptor)
{
	//SYSON_S_TypeDef *syson_s = SYSON_S;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	u32 reg_value;

	/*Load current setting of ctrlr0 register*/
	reg_value = spic_dev->SPIC_CTRLR0;

	/*Set ctrlr0 value into the ctrlr0 register*/
	reg_value &= ~(SPIC_BIT_CMD_DDR_EN | SPIC_BIT_ADDR_DDR_EN | SPIC_BIT_DATA_DDR_EN);
	reg_value |= (SPIC_BIT_ADDR_DDR_EN | SPIC_BIT_DATA_DDR_EN);
	spic_dev->SPIC_CTRLR0 = reg_value;

	phal_spic_adaptor->dtr_en = ENABLE;

	/*Enable Spic DTR Rx*/
	//syson_s->SYSON_S_REG_SYS_FLASH_PHY_CTRL0 |= SYSON_S_BIT_FLASH_PHY_DQS_DDR_EN;
	hal_sys_spic_ddr_ctrl(ENABLE);
}

/** \brief Description of spic_ns_config_auto_mode
 *
 *    spic_ns_config_auto_mode is used to configurate auto mode of flash controller.
 *    In the meantime, the flash controller sends commands to switch flash to the target IO mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */

void spic_ns_config_auto_mode(phal_spic_adaptor_t phal_spic_adaptor)
{
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u32 reg_value;
	u32 reg_ctrl_value;
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;
	u8 flash_type = phal_spic_adaptor->flash_type;

	reg_ctrl_value = spic_dev->SPIC_CTRLR0;

	/*Set default send cmd channel mode*/
	phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;

	spic_rtl_disable(spic_dev);
	reg_value = SPIC_BIT_PRM_EN | SPIC_BIT_WR_BLOCKING;
	spic_dev->SPIC_VALID_CMD = reg_value;

	switch (spic_bit_mode) {
	case SpicOneIOMode:
		spic_dev->SPIC_READ_FAST_SINGLE = cmd->fread;
		break;

	case SpicDualOutputMode:        /*Enable 1-1-2*/
		spic_dev->SPIC_READ_DUAL_DATA = cmd->dread;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_RD_DUAL_I;
		break;

	case SpicDualIOMode:            /*Enable 1-2-2*/
		spic_dev->SPIC_READ_DUAL_ADDR_DATA = cmd->str_2read;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_RD_DUAL_IO;
		break;

	case SpicQuadOutputMode:        /*Enable 1-1-4*/
		spic_dev->SPIC_READ_QUAD_DATA = cmd->qread;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_RD_QUAD_O;
		if ((flash_type == FLASH_TYPE_WINBOND)
			|| (flash_type == FLASH_TYPE_GD)
			|| (flash_type == FLASH_TYPE_GD32)
			|| (flash_type == FLASH_TYPE_ZBIT)
			|| (flash_type == FLASH_TYPE_XTX)) {
			flash_ns_set_quad_enable(phal_spic_adaptor);
		}
		break;

	case SpicQuadIOMode:            /*Enable 1-4-4*/
		reg_value = spic_dev->SPIC_READ_QUAD_ADDR_DATA;
		reg_value &= ~SPIC_MASK_RD_QUAD_IO_CMD;
		reg_value |= cmd->str_4read;
		spic_dev->SPIC_READ_QUAD_ADDR_DATA = reg_value;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_RD_QUAD_IO;
		flash_ns_set_quad_enable(phal_spic_adaptor);
		break;

	case SpicQuadIODtrMode:         /*Enable 1-4-4 DTR, need to check*/
		reg_value = spic_dev->SPIC_READ_QUAD_ADDR_DATA;
		reg_value &= ~SPIC_MASK_RD_QUAD_IO_CMD;
		reg_value |= cmd->dtr_4read;
		spic_dev->SPIC_READ_QUAD_ADDR_DATA = reg_value;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_RD_QUAD_IO;
		flash_ns_set_quad_enable(phal_spic_adaptor);
		reg_ctrl_value &= ~(SPIC_MASK_ADDR_CH | SPIC_MASK_DATA_CH | SPIC_MASK_CMD_CH);
		reg_ctrl_value |= (SingleChnl << SPIC_SHIFT_CMD_CH) | (QuadChnl << SPIC_SHIFT_ADDR_CH) | (QuadChnl << SPIC_SHIFT_DATA_CH);
		spic_dev->SPIC_CTRLR0 = reg_ctrl_value;
		spic_ns_config_dtr_read(phal_spic_adaptor);
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_CTRLR0_CH;
		break;

	case SpicQpiMode:               /*Enable 4-4-4*/
		reg_value = spic_dev->SPIC_READ_QUAD_ADDR_DATA;
		reg_value &= ~SPIC_MASK_RD_QUAD_IO_CMD;
		reg_value |= cmd->str_4read;
		spic_dev->SPIC_READ_QUAD_ADDR_DATA = reg_value;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_RD_QUAD_IO;
		flash_ns_enable_qpi(phal_spic_adaptor);
		break;

	case SpicQpiDtrMode:            /*Enable 4-4-4 DTR*/
		spic_dev->SPIC_READ_FAST_SINGLE = cmd->dtr_4read;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_FRD_SINGLE;
		flash_ns_enable_qpi(phal_spic_adaptor);
		spic_ns_config_dtr_read(phal_spic_adaptor);
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_CTRLR0_CH;
		break;

	default:
		DBG_SPIF_ERR("spic_config_auto_mode : Invalid Bit Mode\r\n");
	}

	phal_spic_adaptor->addr_byte_num = ThreeBytesLength;

	reg_value = spic_dev->SPIC_AUTO_LENGTH;
	reg_value &= ~SPIC_MASK_AUTO_ADDR_LENGTH;
	reg_value |= (phal_spic_adaptor->addr_byte_num << SPIC_SHIFT_AUTO_ADDR_LENGTH);
	spic_dev->SPIC_AUTO_LENGTH = reg_value;
	spic_rtl_enable(spic_dev);
}

/** \brief Description of spic_ns_config_user_mode
 *
 *    spic_ns_config_user_mode is used to configurate user mode of flash controller.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */

void spic_ns_config_user_mode(phal_spic_adaptor_t phal_spic_adaptor)
{
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	pflash_cmd_t cmd = phal_spic_adaptor->cmd;
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;

	spic_rtl_disable(spic_dev);

	switch (spic_bit_mode) {
	case SpicOneIOMode:
		phal_spic_adaptor->cmd_chnl = SingleChnl;
		phal_spic_adaptor->addr_chnl = SingleChnl;
		phal_spic_adaptor->data_chnl = SingleChnl;
		phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;
		phal_spic_adaptor->read_cmd = cmd->read;
		break;

	case SpicDualOutputMode:
		phal_spic_adaptor->cmd_chnl = SingleChnl;
		phal_spic_adaptor->addr_chnl = SingleChnl;
		phal_spic_adaptor->data_chnl = DualChnl;
		phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;
		phal_spic_adaptor->read_cmd = cmd->dread;
		break;

	case SpicDualIOMode:
		phal_spic_adaptor->cmd_chnl = SingleChnl;
		phal_spic_adaptor->addr_chnl = DualChnl;
		phal_spic_adaptor->data_chnl = DualChnl;
		phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;
		phal_spic_adaptor->read_cmd = cmd->str_2read;
		break;

	case SpicQuadOutputMode:
		phal_spic_adaptor->cmd_chnl = SingleChnl;
		phal_spic_adaptor->addr_chnl = SingleChnl;
		phal_spic_adaptor->data_chnl = QuadChnl;
		phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;
		phal_spic_adaptor->read_cmd = cmd->qread;
		break;

	case SpicQuadIOMode:
		phal_spic_adaptor->cmd_chnl = SingleChnl;
		phal_spic_adaptor->addr_chnl = QuadChnl;
		phal_spic_adaptor->data_chnl = QuadChnl;
		phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;
		phal_spic_adaptor->read_cmd = cmd->str_4read;
		break;

	case SpicQuadIODtrMode:
		phal_spic_adaptor->cmd_chnl = SingleChnl;
		phal_spic_adaptor->addr_chnl = QuadChnl;
		phal_spic_adaptor->data_chnl = QuadChnl;
		phal_spic_adaptor->spic_send_cmd_mode = SingleChnl;
		phal_spic_adaptor->read_cmd = cmd->dtr_4read;
		break;

	case SpicQpiMode:
		phal_spic_adaptor->cmd_chnl = QuadChnl;
		phal_spic_adaptor->addr_chnl = QuadChnl;
		phal_spic_adaptor->data_chnl = QuadChnl;
		phal_spic_adaptor->spic_send_cmd_mode = QuadChnl;
		phal_spic_adaptor->read_cmd = cmd->str_4read;
		break;

	case SpicQpiDtrMode:
		phal_spic_adaptor->cmd_chnl = QuadChnl;
		phal_spic_adaptor->addr_chnl = QuadChnl;
		phal_spic_adaptor->data_chnl = QuadChnl;
		phal_spic_adaptor->spic_send_cmd_mode = QuadChnl;
		phal_spic_adaptor->read_cmd = cmd->dtr_4read;
		break;

	default:
		DBG_SPIF_ERR("spic_config_user_mode : Invalide Bit Mode\r\n");
		break;
	}

	spic_ns_set_chnl_num(phal_spic_adaptor);

	phal_spic_adaptor->addr_byte_num = ThreeBytesLength;

	spic_dev->SPIC_ADDR_LENGTH = phal_spic_adaptor->addr_byte_num;
	spic_rtl_enable(spic_dev);

}

/** \brief Description of spic_verify_calibration_para
 *
 *    spic_verify_calibration_para is used to verify calibration pattern for calibration procedure.
 *
 *   \param void.
 *
 *   \return BOOL: _TRUE: data is correct, _FALSE: data is wrong.
 */

BOOL spic_ns_verify_calibration_para()
{
	u32 rd_data;
	u8  addr_index;

	for (addr_index = 0; addr_index < 4; addr_index++) {
		rd_data = HAL_READ32(SPI_FLASH_BASE, addr_index * 4);
		if (rd_data != spic_calibration_pattern[addr_index]) {
			return _FALSE;
		}
	}

	return _TRUE;
}

/** \brief Description of spic_ns_set_chnl_num
 *
 *    spic_ns_set_chnl_num is used to set channel numbers of command, address and data phases to the control register.
 *    The flash controller should be disabled so that the values can be correctly written.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */

void spic_ns_set_chnl_num(phal_spic_adaptor_t phal_spic_adaptor)
{
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	u32 reg_ctrl_value;

	reg_ctrl_value = spic_dev->SPIC_CTRLR0;
	reg_ctrl_value &= ~(SPIC_MASK_ADDR_CH | SPIC_MASK_DATA_CH | SPIC_MASK_CMD_CH);
	reg_ctrl_value |= (phal_spic_adaptor->cmd_chnl << SPIC_SHIFT_CMD_CH) | (phal_spic_adaptor->addr_chnl << SPIC_SHIFT_ADDR_CH) |
					  (phal_spic_adaptor->data_chnl << SPIC_SHIFT_DATA_CH);
	spic_dev->SPIC_CTRLR0 = reg_ctrl_value;
}

/** \brief Description of spic_ns_set_delay_line
 *
 *    spic_ns_set_delay_line is used to fine-tune data receive timing with digital PHY.
 *    100 levels of delay line can be used.
 *
 *   \param u8 delay_line:      The level of the delay line, can be 0~99.
 *
 *   \return void.
 */

void spic_ns_set_delay_line(u8 delay_line)
{
	//SYSON_S_TypeDef *syson_s = SYSON_S;

	//syson_s->SYSON_S_REG_SYS_FLASH_PHY_CTRL1 = delay_line << SYSON_S_SHIFT_FLASH_PHY_DQSL_DLY_SEL;
	hal_sys_spic_set_phy_delay(delay_line);
}

/** \brief Description of spic_ns_rx_cmd
 *
 *    spic_ns_rx_cmd is used to send commands which return data from flash after command phase and address phase(depends on command) for most of non-8IO flash.
 *    Usually we will use this function when trying to read status registers of flash.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */

void spic_ns_rx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
	//SYSON_S_TypeDef *syson_s = SYSON_S;
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	pflash_dummy_cycle_t dummy_cycle = phal_spic_adaptor->dummy_cycle;
	pspic_init_para_t pspic_init_data = NULL;
	spic_init_para_t tmp_spic_init_data;
	u32 reg_ctrl_value;
	u32 rd_dummy_cycle;
	u32 rx_cmd_dummy_cycle;
	u32 baud_rate;
	u32 delay_line;
	u8 index;
	u8 spic_send_cmd_mode = phal_spic_adaptor->spic_send_cmd_mode;
	u8 cpu_type = spic_ns_query_system_clk();
	u8 cmd_ddr_en = 0;
	u8 addr_ddr_en = 0;
	u8 data_ddr_en = 0;

	DBG_SPIF_INFO("spic_rx_cmd: (0x%x, 0x%x, 0x%x)\n", cmd, data_phase_len, pdata);

	spic_rtl_disable(spic_dev);

	spic_dev->SPIC_VALID_CMD &= ~SPIC_BIT_PRM_EN;

	if (data_phase_len == 4) {
		// Set address phase length
		spic_dev->SPIC_ADDR_LENGTH = FourBytesLength;
	} else {
		// Set address phase length
		spic_dev->SPIC_ADDR_LENGTH = data_phase_len;
	}

	/* Store rd_dummy_cycle */
	rd_dummy_cycle = spic_dev->SPIC_AUTO_LENGTH & SPIC_MASK_RD_DUMMY_LENGTH;

	/* Store baud rate */
	baud_rate = spic_dev->SPIC_BAUDR & SPIC_MASK_SCKDV;

	/* Store delay line */
	//delay_line = (syson_s->SYSON_S_REG_SYS_FLASH_PHY_CTRL1 & SYSON_S_MASK_FLASH_PHY_DQSL_DLY_SEL) >> SYSON_S_SHIFT_FLASH_PHY_DQSL_DLY_SEL;
	delay_line = (u32)hal_sys_spic_read_phy_delay();

	/* Set default setting for rx cmd*/
	pspic_init_data = &tmp_spic_init_data;
	spic_ns_load_default_setting(pspic_init_data);
	rx_cmd_dummy_cycle = pspic_init_data->rd_dummy_cycle;

	/*Load current setting of ctrlr0 register*/
	reg_ctrl_value = spic_dev->SPIC_CTRLR0;

	if (phal_spic_adaptor->dtr_en) {
		/*Save current ddr state*/
		cmd_ddr_en = (reg_ctrl_value & SPIC_BIT_CMD_DDR_EN) >> SPIC_SHIFT_CMD_DDR_EN;
		addr_ddr_en = (reg_ctrl_value & SPIC_BIT_ADDR_DDR_EN) >> SPIC_SHIFT_ADDR_DDR_EN;
		data_ddr_en = (reg_ctrl_value & SPIC_BIT_DATA_DDR_EN) >> SPIC_SHIFT_DATA_DDR_EN;

		/*Should send command under STR mode*/
		reg_ctrl_value &= ~(SPIC_BIT_CMD_DDR_EN | SPIC_BIT_ADDR_DDR_EN | SPIC_BIT_DATA_DDR_EN);

		//syson_s->SYSON_S_REG_SYS_FLASH_PHY_CTRL0 &= ~SYSON_S_BIT_FLASH_PHY_DQS_DDR_EN;
		hal_sys_spic_ddr_ctrl(DISABLE);
	}

	if (spic_send_cmd_mode == SingleChnl) {
		reg_ctrl_value &= ~(SPIC_MASK_CMD_CH | SPIC_MASK_ADDR_CH | SPIC_MASK_DATA_CH);
		reg_ctrl_value |= (SingleChnl << SPIC_SHIFT_CMD_CH) | (SingleChnl << SPIC_SHIFT_ADDR_CH) | (SingleChnl << SPIC_SHIFT_DATA_CH);

		if (phal_spic_adaptor->spic_init_data[SpicOneIOMode][cpu_type].valid) {
			pspic_init_data = &(phal_spic_adaptor->spic_init_data[SpicOneIOMode][cpu_type]);
		}

		rx_cmd_dummy_cycle = pspic_init_data->rd_dummy_cycle;

	} else if (spic_send_cmd_mode == QuadChnl) {
		if (phal_spic_adaptor->spic_init_data[SpicQpiMode][cpu_type].valid) {
			pspic_init_data = &(phal_spic_adaptor->spic_init_data[SpicQpiMode][cpu_type]);
			rx_cmd_dummy_cycle = pspic_init_data->rd_dummy_cycle - (dummy_cycle->dc_4read) * 2 * (pspic_init_data->baud_rate);
		}
	} else {
		DBG_SPIF_ERR("Invalid send cmd mode!, spic_send_cmd_mode = %x\n", spic_send_cmd_mode);
	}

	spic_rtl_set_dummy_cycle(spic_dev, rx_cmd_dummy_cycle);

	spic_rtl_set_baudr(spic_dev, pspic_init_data->baud_rate);

	spic_ns_set_delay_line(pspic_init_data->delay_line);

	/* set ctrlr0: RX_mode */
	reg_ctrl_value &= ~SPIC_MASK_TMOD;
	reg_ctrl_value |= (RxMode << SPIC_SHIFT_TMOD);

	/* Set value to the ctrlr0 register*/
	spic_dev->SPIC_CTRLR0 = reg_ctrl_value;

	/* send cmd to the fifo */
	//spic_dev->dr_byte= cmd;
	HAL_WRITE8(SPIC_BASE, 0x60, cmd);

	for (index = 0; index < data_phase_len; index++) {
		//spic_dev->dr_byte = *((u8 *)(pdata + index));
		HAL_WRITE8(SPIC_BASE, 0x60, *((u8 *)(pdata + index)));
	}

	/* Enable SPI_FLASH  User Mode */
	spic_rtl_enable(spic_dev);

	/* Wait spic busy done */
	spic_ns_wait_ready(spic_dev);

	/* Disable SPI_FLASH  User Mode */
	spic_rtl_disable(spic_dev);

	/* Recover rd_dummy_cycle */
	spic_rtl_set_dummy_cycle(spic_dev, rd_dummy_cycle);

	/* Recover baud rate */
	spic_rtl_set_baudr(spic_dev, baud_rate);

	/* Recover delay line */
	spic_ns_set_delay_line(delay_line);

	/* Recover chnl mode*/
	spic_ns_set_chnl_num(phal_spic_adaptor);

	/* Recover ddr state*/
	if (phal_spic_adaptor->dtr_en) {
		reg_ctrl_value = spic_dev->SPIC_CTRLR0;
		reg_ctrl_value |= (cmd_ddr_en << SPIC_SHIFT_CMD_DDR_EN) | (addr_ddr_en << SPIC_SHIFT_ADDR_DDR_EN) | (data_ddr_en << SPIC_SHIFT_DATA_DDR_EN);
		spic_dev->SPIC_CTRLR0 = reg_ctrl_value;
		//syson_s->SYSON_S_REG_SYS_FLASH_PHY_CTRL0 |= SYSON_S_BIT_FLASH_PHY_DQS_DDR_EN;
		hal_sys_spic_ddr_ctrl(ENABLE);
	}

	spic_dev->SPIC_VALID_CMD |= SPIC_BIT_PRM_EN;
}

/** \brief Description of spic_ns_tx_cmd
 *
 *    spic_ns_tx_cmd is used to send flash commands which do not return values for most of non-8IO flash.
 *    These commands could be erase command or set flash registers.
 *    At the end of the function, the flash status is checked if flash returns to ready state.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */

void spic_ns_tx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	u32 reg_ctrl_value;
	u8 spic_send_cmd_mode = phal_spic_adaptor->spic_send_cmd_mode;
	u8 i;
	u8 cmd_ddr_en = 0;
	u8 addr_ddr_en = 0;
	u8 data_ddr_en = 0;

	DBG_SPIF_INFO("spic_tx_cmd: (0x%x, 0x%x, 0x%x)\n", cmd, data_phase_len, pdata);

	/*Load current setting of ctrlr0 register*/
	reg_ctrl_value = spic_dev->SPIC_CTRLR0;

	// disable spi_flash user mode
	spic_rtl_disable(spic_dev);

	spic_dev->SPIC_VALID_CMD &= ~SPIC_BIT_PRM_EN;

	// Set address phase length
	spic_dev->SPIC_ADDR_LENGTH = data_phase_len;

	if (phal_spic_adaptor->dtr_en) {
		/*Save current ddr state*/
		cmd_ddr_en = (reg_ctrl_value & SPIC_BIT_CMD_DDR_EN) >> SPIC_SHIFT_CMD_DDR_EN;
		addr_ddr_en = (reg_ctrl_value & SPIC_BIT_ADDR_DDR_EN) >> SPIC_SHIFT_ADDR_DDR_EN;
		data_ddr_en = (reg_ctrl_value & SPIC_BIT_DATA_DDR_EN) >> SPIC_SHIFT_DATA_DDR_EN;

		/*Should send command under STR mode*/
		reg_ctrl_value &= ~(SPIC_BIT_CMD_DDR_EN | SPIC_BIT_ADDR_DDR_EN | SPIC_BIT_DATA_DDR_EN);
	}

	if (spic_send_cmd_mode == SingleChnl) {
		reg_ctrl_value &= ~(SPIC_MASK_CMD_CH | SPIC_MASK_ADDR_CH | SPIC_MASK_DATA_CH);
		reg_ctrl_value |= (SingleChnl << SPIC_SHIFT_CMD_CH) | (SingleChnl << SPIC_SHIFT_ADDR_CH) | (SingleChnl << SPIC_SHIFT_DATA_CH);
	}

	DBG_SPIF_INFO("spic_send_cmd_mode = %x\n", spic_send_cmd_mode);


	// set ctrlr0: tx mode
	reg_ctrl_value &= ~SPIC_MASK_TMOD;
	reg_ctrl_value |= (TxMode << SPIC_SHIFT_TMOD);

	// set flash_cmd to fifo
	//spic_dev->dr_byte= cmd;
	HAL_WRITE8(SPIC_BASE, 0x60, cmd);

	/*4 byte address mode*/
	if ((data_phase_len == 0) && (pdata != 0)) {
		data_phase_len = 4;
	}

	//fill addr
	for (i = 0; i < data_phase_len; i++) {
		//spic_dev->dr_byte = *((u8 *)(pdata + i));
		HAL_WRITE8(SPIC_BASE, 0x60, *((u8 *)(pdata + i)));
	}

	/*Set value to the ctrlr0 register*/
	spic_dev->SPIC_CTRLR0 = reg_ctrl_value;

	// enable spi_flash  user mode
	spic_rtl_enable(spic_dev);

	/* Wait spic busy done */
	spic_ns_wait_ready(spic_dev);

	// wait flash to get ready
	flash_ns_wait_ready(phal_spic_adaptor);

	/*Restore to original bit mode*/
	spic_ns_set_chnl_num(phal_spic_adaptor);

	/* Recover ddr state*/
	if (phal_spic_adaptor->dtr_en) {
		reg_ctrl_value = spic_dev->SPIC_CTRLR0;
		reg_ctrl_value |= (cmd_ddr_en << SPIC_SHIFT_CMD_DDR_EN) | (addr_ddr_en << SPIC_SHIFT_ADDR_DDR_EN) | (data_ddr_en << SPIC_SHIFT_DATA_DDR_EN);
		spic_dev->SPIC_CTRLR0 = reg_ctrl_value;
	}

	spic_dev->SPIC_VALID_CMD |= SPIC_BIT_PRM_EN;
}

/** \brief Description of spic_ns_tx_cmd_no_check
 *
 *    spic_ns_tx_cmd_no_check is used to send flash commands which do not return values for most of non-8IO flash.
 *    These commands could be erase command or set flash registers.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */

void spic_ns_tx_cmd_no_check(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	u32 reg_ctrl_value;
	u8 spic_send_cmd_mode = phal_spic_adaptor->spic_send_cmd_mode;
	u8 i;
	u8 cmd_ddr_en = 0;
	u8 addr_ddr_en = 0;
	u8 data_ddr_en = 0;

	DBG_SPIF_INFO("spic_tx_cmd_no_check: (0x%x, 0x%x, 0x%x)\n", cmd, data_phase_len, pdata);

	/*Load current setting of ctrlr0 register*/
	reg_ctrl_value = spic_dev->SPIC_CTRLR0;

	// disable spi_flash user mode
	spic_rtl_disable(spic_dev);

	spic_dev->SPIC_VALID_CMD &= ~SPIC_BIT_PRM_EN;

	// Set address phase length
	spic_dev->SPIC_ADDR_LENGTH = data_phase_len;

	if (phal_spic_adaptor->dtr_en) {
		/*Save current ddr state*/
		cmd_ddr_en = (reg_ctrl_value & SPIC_BIT_CMD_DDR_EN) >> SPIC_SHIFT_CMD_DDR_EN;
		addr_ddr_en = (reg_ctrl_value & SPIC_BIT_ADDR_DDR_EN) >> SPIC_SHIFT_ADDR_DDR_EN;
		data_ddr_en = (reg_ctrl_value & SPIC_BIT_DATA_DDR_EN) >> SPIC_SHIFT_DATA_DDR_EN;

		/*Should send command under STR mode*/
		reg_ctrl_value &= ~(SPIC_BIT_CMD_DDR_EN | SPIC_BIT_ADDR_DDR_EN | SPIC_BIT_DATA_DDR_EN);
	}

	if (spic_send_cmd_mode == SingleChnl) {
		reg_ctrl_value &= ~(SPIC_MASK_CMD_CH | SPIC_MASK_ADDR_CH | SPIC_MASK_DATA_CH);
		reg_ctrl_value |= (SingleChnl << SPIC_SHIFT_CMD_CH) | (SingleChnl << SPIC_SHIFT_ADDR_CH) | (SingleChnl << SPIC_SHIFT_DATA_CH);
	}

	DBG_SPIF_INFO("spic_send_cmd_mode = %x\n", spic_send_cmd_mode);

	// set ctrlr0: tx mode
	reg_ctrl_value &= ~SPIC_MASK_TMOD;
	reg_ctrl_value |= (TxMode << SPIC_SHIFT_TMOD);

	// set flash_cmd to fifo
	//spic_dev->dr_byte= cmd;
	HAL_WRITE8(SPIC_BASE, 0x60, cmd);

	/*4 byte address mode*/
	if ((data_phase_len == 0) && (pdata != 0)) {
		data_phase_len = 4;
	}

	//fill addr
	for (i = 0; i < data_phase_len; i++) {
		//spic_dev->dr_byte = *((u8 *)(pdata + i));
		HAL_WRITE8(SPIC_BASE, 0x60, *((u8 *)(pdata + i)));
	}

	/*Set value to the ctrlr0 register*/
	spic_dev->SPIC_CTRLR0 = reg_ctrl_value;

	// enable spi_flash  user mode
	spic_rtl_enable(spic_dev);

	/* Wait spic busy done */
	spic_ns_wait_ready(spic_dev);

	spic_rtl_disable(spic_dev);

	/* Resotre to original bit mode */
	spic_ns_set_chnl_num(phal_spic_adaptor);

	/* Recover ddr state*/
	if (phal_spic_adaptor->dtr_en) {
		reg_ctrl_value = spic_dev->SPIC_CTRLR0;
		reg_ctrl_value |= (cmd_ddr_en << SPIC_SHIFT_CMD_DDR_EN) | (addr_ddr_en << SPIC_SHIFT_ADDR_DDR_EN) | (data_ddr_en << SPIC_SHIFT_DATA_DDR_EN);
		spic_dev->SPIC_CTRLR0 = reg_ctrl_value;
	}

	spic_dev->SPIC_VALID_CMD |= SPIC_BIT_PRM_EN;
}

/** \brief Description of spic_ns_wait_ready
 *
 *    spic_wait_ready is used to check if the flash controller is ready.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */

void spic_ns_wait_ready(SPIC_TypeDef *spic_dev)
{
	u32 busy_status = 0;

	do {
		busy_status = (spic_dev->SPIC_SR & SPIC_BIT_BUSY) >> SPIC_SHIFT_BUSY;//spic_dev->sr_b.busy;
	} while (busy_status == 1);
}

/** \brief Description of spic_ns_flush_fifo
 *
 *    spic_ns_flush_fifo is used to flush FIFO of the flash controller.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */

void spic_ns_flush_fifo(SPIC_TypeDef *spic_dev)
{
	spic_rtl_disable(spic_dev);
	spic_dev->SPIC_FLUSH_FIFO = 1;
	spic_rtl_enable(spic_dev);
}

/** *@} */ /* End of group hal_spic_ns_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/** *@} */
#endif
