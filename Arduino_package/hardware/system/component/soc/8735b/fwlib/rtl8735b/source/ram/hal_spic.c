/**************************************************************************//**
 * @file     hal_spic.c
 * @brief    Functions to implement the flash controller operation.
 * @version  1.00
 * @date     2021-11-22
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
#include "section_config.h"
#include "hal_spic.h"
#include "hal_flash.h"
#include "hal_pinmux.h"
#include "hal_irq.h"
#include "hal_gpio.h"
//#include "hal_sys_ctrl.h"
#if !defined(CONFIG_BUILD_NONSECURE)
extern const hal_spic_func_stubs_t hal_spic_stubs;
#else
extern const hal_spic_func_stubs_t hal_spic_stubs_ns;
#define hal_spic_stubs hal_spic_stubs_ns
#endif
/**

        \addtogroup hal_spic Flash Controller
        @{
*/


/**

        \addtogroup hs_hal_spic_ram_func Flash Controller HAL RAM APIs
        \ingroup hs_hal_spic
        \brief The flash controller HAL APIs. Functions become an interface between API functions and ROM codes.
        @{
*/

extern __WEAK void spic_user_select(pspic_user_define_t pspic_user_define);

/** \brief Description of spic_load_default_setting
 *
 *    spic_load_default_setting is used to load default setting for One IO mode at low speed without calibration.
 *    The calibration includes baud rate, delay line and dummy cycles(associated with path delay).
 *
 *   \param pspic_init_para_t pspic_init_data:      The pointer of struct storing calibation settings.
 *
 *   \return void.
 */
void spic_load_default_setting(pspic_init_para_t pspic_init_data)
{
	hal_spic_stubs.spic_load_default_setting(pspic_init_data);
}

/** \brief Description of spic_query_system_clk
 *
 *    spic_query_system_clk is used to query current CPU clock.
 *    Different CPU speed will apply different calibration parameters to optimize the flash controller.
 *
 *   \param void.
 *
 *   \return u8: The macro definition of CPU clock.
 */
u8 spic_query_system_clk(void)
{
	return hal_spic_stubs.spic_query_system_clk();
}

/** \brief Description of spic_clock_ctrl
 *
 *    spic_clock_ctrl is used to enable or disable the flash controller clock and function enable.
 *
 *   \param u8 ctl:      The control parameter.
 *
 *   \return void.
 */
void spic_clock_ctrl(u8 ctl)
{
	hal_spic_stubs.spic_clock_ctrl(ctl);
}

/** \brief Description of spic_init_setting
 *
 *    spic_init_setting is used to initialize the flash controller.
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
hal_status_t spic_init_setting(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode)
{
	return hal_spic_stubs.spic_init_setting(phal_spic_adaptor, spic_bit_mode);
}

/** \brief Description of spic_config_dtr_read
 *
 *    spic_config_dtr_read is used to configurate flash controller so that it can read data correctly with DTR mode .
 *    1-4D-4D, 4D-4D-4D, 8D-8D-8D modes access should call this function first.
 *    x-y-z : x is IO mode of command phase, y is IO mode of address phase, z is IO mode of data phase. D stands for DTR mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
void spic_config_dtr_read(phal_spic_adaptor_t phal_spic_adaptor)
{
	hal_spic_stubs.spic_config_dtr_read(phal_spic_adaptor);
}

/** \brief Description of spic_config_auto_mode
 *
 *    spic_config_auto_mode is used to configurate auto mode of flash controller.
 *    In the meantime, the flash controller sends commands to switch flash to the target IO mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
void spic_config_auto_mode(phal_spic_adaptor_t phal_spic_adaptor)
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
			hal_flash_set_quad_enable(phal_spic_adaptor);
		}
		break;

	case SpicQuadIOMode:            /*Enable 1-4-4*/
		reg_value = spic_dev->SPIC_READ_QUAD_ADDR_DATA;
		reg_value &= ~SPIC_MASK_RD_QUAD_IO_CMD;
		reg_value |= cmd->str_4read;
		spic_dev->SPIC_READ_QUAD_ADDR_DATA = reg_value;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_RD_QUAD_IO;
		hal_flash_set_quad_enable(phal_spic_adaptor);
		break;

	case SpicQuadIODtrMode:         /*Enable 1-4-4 DTR, need to check*/
		reg_value = spic_dev->SPIC_READ_QUAD_ADDR_DATA;
		reg_value &= ~SPIC_MASK_RD_QUAD_IO_CMD;
		reg_value |= cmd->dtr_4read;
		spic_dev->SPIC_READ_QUAD_ADDR_DATA = reg_value;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_RD_QUAD_IO;
		hal_flash_set_quad_enable(phal_spic_adaptor);
		reg_ctrl_value &= ~(SPIC_MASK_ADDR_CH | SPIC_MASK_DATA_CH | SPIC_MASK_CMD_CH);
		reg_ctrl_value |= (SingleChnl << SPIC_SHIFT_CMD_CH) | (QuadChnl << SPIC_SHIFT_ADDR_CH) | (QuadChnl << SPIC_SHIFT_DATA_CH);
		spic_dev->SPIC_CTRLR0 = reg_ctrl_value;
		spic_config_dtr_read(phal_spic_adaptor);
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_CTRLR0_CH;
		break;

	case SpicQpiMode:               /*Enable 4-4-4*/
		reg_value = spic_dev->SPIC_READ_QUAD_ADDR_DATA;
		reg_value &= ~SPIC_MASK_RD_QUAD_IO_CMD;
		reg_value |= cmd->str_4read;
		spic_dev->SPIC_READ_QUAD_ADDR_DATA = reg_value;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_RD_QUAD_IO;
		hal_flash_enable_qpi(phal_spic_adaptor);
		break;

	case SpicQpiDtrMode:            /*Enable 4-4-4 DTR*/
		spic_dev->SPIC_READ_FAST_SINGLE = cmd->dtr_4read;
		spic_dev->SPIC_VALID_CMD |= SPIC_BIT_FRD_SINGLE;
		hal_flash_enable_qpi(phal_spic_adaptor);
		spic_config_dtr_read(phal_spic_adaptor);
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

/** \brief Description of spic_config_user_mode
 *
 *    spic_config_user_mode is used to configurate user mode of flash controller.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
void spic_config_user_mode(phal_spic_adaptor_t phal_spic_adaptor)
{
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;
	u8 baudr = spic_rtl_get_baudr(phal_spic_adaptor->spic_dev);

	hal_spic_stubs.spic_config_user_mode(phal_spic_adaptor);

	if (spic_bit_mode == SpicQpiMode) {
		if (baudr == 1) {
			phal_spic_adaptor->write_delay = 8;//125/100MHz STR with Quad IO program
		} else {
			phal_spic_adaptor->write_delay = 16;//62.5/50MHz STR with Quad IO program
		}
	} else if (spic_bit_mode == SpicQpiDtrMode) {  //62.5MHz DTR with Quad IO program
		phal_spic_adaptor->write_delay = 16;
	} else if (spic_bit_mode == SpicQuadIODtrMode) { //62.5MHz DTR with One IO program
		phal_spic_adaptor->write_delay = 80;
	} else if (spic_bit_mode == SpicOneIOMode) {
		phal_spic_adaptor->write_delay = 160; //Low speed one IO mode
	} else { //STR with One IO program
		if (baudr == 1) {
			phal_spic_adaptor->write_delay = 48;//125/100MHz STR with One IO program
		} else {
			phal_spic_adaptor->write_delay = 80;//62.5/50MHz STR with One IO program
		}
	}
}

/** \brief Description of spic_verify_calibration_para
 *
 *    spic_verify_calibration_para is used to verify calibration pattern for calibration procedure.
 *
 *   \param void.
 *
 *   \return BOOL: _TRUE: data is correct, _FALSE: data is wrong.
 */
BOOL spic_verify_calibration_para(void)
{
	return hal_spic_stubs.spic_verify_calibration_para();
}

/** \brief Description of spic_set_chnl_num
 *
 *    spic_set_chnl_num is used to set channel numbers of command, address and data phases to the control register.
 *    The flash controller should be disabled so that the values can be correctly written.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
void spic_set_chnl_num(phal_spic_adaptor_t phal_spic_adaptor)
{
	hal_spic_stubs.spic_set_chnl_num(phal_spic_adaptor);
}

/** \brief Description of spic_set_delay_line
 *
 *    spic_set_delay_line is used to fine-tune data receive timing with digital PHY.
 *    100 levels of delay line can be used.
 *
 *   \param u8 delay_line:      The level of the delay line, can be 0~99.
 *
 *   \return void.
 */
void spic_set_delay_line(u8 delay_line)
{
	hal_spic_stubs.spic_set_delay_line(delay_line);
}

/** \brief Description of spic_rx_cmd
 *
 *    spic_rx_cmd is an entry function to switch between 8IO or non-8IO rx_cmd functions depending on flash types.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
void spic_rx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
	hal_spic_stubs.spic_rx_cmd(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_tx_cmd_no_check
 *
 *    spic_tx_cmd_no_check is an entry function to switch between 8IO or non-8IO tx_cmd_no_check functions depending on flash types.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
void spic_tx_cmd_no_check(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
	hal_spic_stubs.spic_tx_cmd_no_check(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_tx_cmd
 *
 *    spic_tx_cmd is an entry function to switch between 8IO or non-8IO tx_cmd functions depending on flash types.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
void spic_tx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
	hal_spic_stubs.spic_tx_cmd(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_wait_ready
 *
 *    spic_wait_ready is used to check if the flash controller is ready.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */
void spic_wait_ready(SPIC_TypeDef *spic_dev)
{
	hal_spic_stubs.spic_wait_ready(spic_dev);
}

/** \brief Description of spic_flush_fifo
 *
 *    spic_flush_fifo is used to flush FIFO of the flash controller.
 *
 *   \param SPIC_TypeDef *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */
void spic_flush_fifo(SPIC_TypeDef *spic_dev)
{
	hal_spic_stubs.spic_flush_fifo(spic_dev);
}


/** \brief Description of spic_pinmux_init
 *
 *    spic_pinmux_init is used to select pinmux to operate flash.
 *    The pinmux selection is registered and checked if the relevant pins are occpuied by other devices.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 ctl:      The flash pins control bit.
 *
 *   \return hal_status_t.
 */
hal_status_t spic_pinmux_ctl(phal_spic_adaptor_t phal_spic_adaptor, u8 ctl)
{
	hal_status_t ret = HAL_OK;
	u8 quad_pin_sel = phal_spic_adaptor->quad_pin_sel;

	if (ctl == ENABLE) {
#if CONFIG_FPGA
		hal_pinmux_register(PIN_C0, PID_GPIO);
		hal_pinmux_register(PIN_C2, PID_GPIO);
		hal_pinmux_register(PIN_C4, PID_GPIO);
		hal_pinmux_register(PIN_C5, PID_GPIO);

		if (quad_pin_sel) {
			hal_pinmux_register(PIN_C1, PID_GPIO);
			hal_pinmux_register(PIN_C3, PID_GPIO);
		} else {
			hal_gpio_pull_ctrl((u32)PIN_C1, Pin_PullUp);
			hal_gpio_pull_ctrl((u32)PIN_C3, Pin_PullUp);
		}
#else
		hal_pinmux_register(PIN_C0, PID_FLASH);
		hal_pinmux_register(PIN_C2, PID_FLASH);
		hal_pinmux_register(PIN_C4, PID_FLASH);
		hal_pinmux_register(PIN_C5, PID_FLASH);

		if (quad_pin_sel) {
			hal_pinmux_register(PIN_C1, PID_FLASH);
			hal_pinmux_register(PIN_C3, PID_FLASH);
		} else {
			hal_gpio_pull_ctrl((u32)PIN_C1, Pin_PullUp);
			hal_gpio_pull_ctrl((u32)PIN_C3, Pin_PullUp);
		}
#endif
	} else {
#if CONFIG_FPGA
		hal_pinmux_unregister(PIN_C0, PID_GPIO);
		hal_pinmux_unregister(PIN_C2, PID_GPIO);
		hal_pinmux_unregister(PIN_C4, PID_GPIO);
		hal_pinmux_unregister(PIN_C5, PID_GPIO);

		if (quad_pin_sel) {
			hal_pinmux_unregister(PIN_C1, PID_GPIO);
			hal_pinmux_unregister(PIN_C3, PID_GPIO);
		} else {
			hal_gpio_pull_ctrl((u32)PIN_C1, Pin_PullDefault);
			hal_gpio_pull_ctrl((u32)PIN_C3, Pin_PullDefault);
		}
#else
		hal_pinmux_unregister(PIN_C0, PID_FLASH);
		hal_pinmux_unregister(PIN_C2, PID_FLASH);
		hal_pinmux_unregister(PIN_C4, PID_FLASH);
		hal_pinmux_unregister(PIN_C5, PID_FLASH);

		if (quad_pin_sel) {
			hal_pinmux_unregister(PIN_C1, PID_FLASH);
			hal_pinmux_unregister(PIN_C3, PID_FLASH);
		} else {
			hal_gpio_pull_ctrl((u32)PIN_C1, Pin_PullDefault);
			hal_gpio_pull_ctrl((u32)PIN_C3, Pin_PullDefault);
		}
#endif
	}

	return ret;
}

/** \brief Description of spic_init
 *
 *    spic_init is used to initialize flash controller setting.
 *    Flash can be accessed freely with API functions after this function.
 *    Flash access path delay is calibrated if no available setting is stored in flash before.
 *    After that, the flash controller initializes user mode and auto mode registers for the current IO mode.
 *    At the end of the function, the sequential transfer mode is also calibrated for future use.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 spic_bit_mode:   The flash IO mode.
 *   \param u8 io_pin_sel:      The pinmux selection.
 *
 *   \return hal_status_t.
 */
hal_status_t spic_init(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode, u8 io_pin_sel)
{
	pflash_dummy_cycle_t dummy_cycle;
	SPIC_TypeDef *spic_dev;
	u32 default_dummy_cycle;
	pspic_init_para_t pspic_data;
	u8 cpu_type = spic_query_system_clk();
	u32 reg_value;

	phal_spic_adaptor->flash_pin_sel = io_pin_sel;

	if ((spic_bit_mode == SpicQuadOutputMode)
		|| (spic_bit_mode == SpicQuadIOMode)
		|| (spic_bit_mode == SpicQuadIODtrMode)
		|| (spic_bit_mode == SpicQpiMode)
		|| (spic_bit_mode == SpicQpiDtrMode)) {
		phal_spic_adaptor->quad_pin_sel = ENABLE;
	} else {
		phal_spic_adaptor->quad_pin_sel = DISABLE;
	}

	if (spic_pinmux_ctl(phal_spic_adaptor, ENABLE) == HAL_OK) {
		if (spic_init_setting(phal_spic_adaptor, spic_bit_mode) != HAL_OK) {
			return HAL_ERR_HW;
		}
	} else {
		return HAL_ERR_PARA;
	}

	spic_dev = phal_spic_adaptor->spic_dev;

	/*Disable SPIC interrupt*/
	spic_rtl_disable(spic_dev);

	hal_irq_clear_pending(FlashCtrl_IRQn);
	spic_dev->SPIC_IMR = 0x0;
	spic_rtl_enable(spic_dev);

	hal_flash_support_new_type(phal_spic_adaptor);
	spic_load_calibration_setting(phal_spic_adaptor);

	pspic_data = &phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type];
	dummy_cycle = phal_spic_adaptor->dummy_cycle;
	default_dummy_cycle = *(((u8 *)dummy_cycle) + spic_bit_mode);

	if (pspic_data->valid == 0) {
		spic_config_auto_mode(phal_spic_adaptor);
	}

	/*STR TX do not have to tx calibration*/
	if (spic_calibration(phal_spic_adaptor, default_dummy_cycle) != _TRUE) {
		DBG_SPIF_ERR("spic_init : Calibration Fail, switch back to one bit mode!\r\n");
		hal_flash_return_spi(phal_spic_adaptor);
		spic_dev->SPIC_FBAUDR = (u8)spic_dev->SPIC_BAUDR;
	}

	/*Store pad delay information for auto mode write*/
	spic_rtl_disable(spic_dev);
	reg_value = spic_dev->SPIC_AUTO_LENGTH;
	reg_value &= ~SPIC_MASK_AUTO_DUM_LEN;
	reg_value |= ((pspic_data->rd_dummy_cycle - default_dummy_cycle * (pspic_data->baud_rate) * 2) << SPIC_SHIFT_AUTO_DUM_LEN);
	spic_dev->SPIC_AUTO_LENGTH = reg_value;
	spic_rtl_enable(spic_dev);

	/*Set user relevant parameters according to bit mode*/
	spic_config_user_mode(phal_spic_adaptor);

	return HAL_OK;
}

/** \brief Description of spic_deinit
 *
 *    spic_deinit is used to de-initialize flash controller setting when flash is no longer used.
 *    Pinmux, function enable and clock are disabled in the function.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t spic_deinit(phal_spic_adaptor_t phal_spic_adaptor)
{
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;
	u8 cpu_type = spic_query_system_clk();

	spic_pinmux_ctl(phal_spic_adaptor, DISABLE);

	/*Disable Flash clock*/
	spic_clock_ctrl(DISABLE);

	/*Necessary?*/
	phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type].valid = 0;

	return HAL_OK;
}

hal_status_t spic_deinit_for_xip_img_deinit(phal_spic_adaptor_t phal_spic_adaptor)
{
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;
	u8 cpu_type = spic_query_system_clk();

	spic_pinmux_ctl(phal_spic_adaptor, DISABLE);

	/*Not Disable NOR Flash clock, because Flash SEC setting for XIP rmp & decrypt will be reset*/

	/*Necessary?*/
	phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type].valid = 0;

	return HAL_OK;
}

/** \brief Description of spic_calibration
 *
 *    spic_calibration is used to calibrate the path delay of flash data access path.
 *    It ensures the flash controller can read correct data by inserting few delay.
 *    The level of delays depends on the operating frequency and flash IO mode.
 *    If an optimal available window is found, the setting is stored in flash so that flash controller directly load the setting next time.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash adaptor.
 *
 *   \return BOOL: _TURE: Success, _FALSE: No available window, calibration unsuccessful.
 */
BOOL spic_calibration(phal_spic_adaptor_t phal_spic_adaptor, u32 default_dummy_cycle)
{
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	pspic_init_para_t pspic_init_para;
	valid_windows_t max_wd;
	u32 rd_data = 0;
	u32 auto_len = 0;
	u32 dly_line = 0;
	u32 total_ava_wds = 0;
	u32 tmp_str_pt = 0;
	u32 tmp_end_pt = 0;
	u32 last_pass = 0;
	u8  baudr = 0;
	u8 min_baud_rate = 0;
	u8 max_baud_rate = 0;
	u8 cpu_type = spic_query_system_clk();
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;
	spic_user_define_t spic_user_define;

	spic_user_select(&spic_user_define);
	pspic_init_para = &(phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type]);

	if (pspic_init_para->valid) {
		spic_rtl_disable(spic_dev);
		spic_rtl_set_baudr(spic_dev, pspic_init_para->baud_rate);
		spic_rtl_set_fbaudr(spic_dev, pspic_init_para->baud_rate);
		spic_rtl_set_dummy_cycle(spic_dev, pspic_init_para->rd_dummy_cycle);
		spic_set_delay_line(pspic_init_para->delay_line);
		spic_rtl_enable(spic_dev);

		if (spic_verify_calibration_para() == _TRUE) {
			return _TRUE;
		}
	}

	DBG_SPIF_WARN("Start Flash Calibration\r\n");

	max_wd.auto_length = 0;
	max_wd.baud_rate = 0;
	max_wd.dly_line_ep = 0;
	max_wd.dly_line_sp = 0;

#if CONFIG_FPGA /* FPGA Setting */
	min_baud_rate = 1;
	max_baud_rate = 3;

#else /* PXP & ASIC Setting*/
	/*If SPIC CLK is 300MHz / 200MHz*/
	if ((SpicQuadIODtrMode == spic_bit_mode)
		|| (SpicQpiDtrMode == spic_bit_mode)) {

		/*QPI DTR flash can only operate at 50 / 62.5MHz in at most in DTR mode*/
		min_baud_rate = 2;
		max_baud_rate = 3;
	} else {
		if (spic_user_define.flash_speed == FLASH_SPEED_625MHz) {
			min_baud_rate = MIN_BAUD_RATE + 1;
		} else {
			min_baud_rate = MIN_BAUD_RATE;
		}

		max_baud_rate = MAX_BAUD_RATE;

		/*03 command supports lower speed*/
		if (SpicOneIOMode == spic_bit_mode) {
			min_baud_rate = 0x4;
		}
	}
#endif

	for (baudr = min_baud_rate; baudr <= max_baud_rate; baudr++) {
		spic_rtl_disable(spic_dev);
		spic_rtl_set_baudr(spic_dev, baudr);
		spic_rtl_set_fbaudr(spic_dev, baudr);
		spic_rtl_enable(spic_dev);

		for (auto_len = (default_dummy_cycle * baudr * 2) + 2; auto_len < (default_dummy_cycle * baudr * 2 + MAX_AUTO_LENGTH); auto_len++) {
			spic_rtl_disable(spic_dev);
			spic_rtl_set_dummy_cycle(spic_dev, auto_len);
			spic_rtl_enable(spic_dev);
			tmp_str_pt = MAX_DELAY_LINE;
			tmp_end_pt = 0;
			last_pass = 0;

			for (dly_line = 0; dly_line <= MAX_DELAY_LINE; dly_line++) {
				spic_set_delay_line(dly_line);

				if (spic_verify_calibration_para() == _TRUE) {
					if (last_pass == 0) {
						tmp_str_pt = dly_line;
						total_ava_wds++;
					}

					if (dly_line == MAX_DELAY_LINE) {
						tmp_end_pt = dly_line;

						if (total_ava_wds == 1) {
							max_wd.baud_rate = baudr;
							max_wd.auto_length = auto_len;
							max_wd.dly_line_sp = tmp_str_pt;
							max_wd.dly_line_ep = tmp_end_pt;
						} else {
							DBG_SPIF_WARN("Baud:%x; auto_length:%x; Delay start:%x; Delay end:%x\n", baudr, auto_len, tmp_str_pt, tmp_end_pt);
							if ((tmp_end_pt - tmp_str_pt) > (max_wd.dly_line_ep - max_wd.dly_line_sp)) {
								max_wd.baud_rate = baudr;
								max_wd.auto_length = auto_len;
								max_wd.dly_line_sp = tmp_str_pt;
								max_wd.dly_line_ep = tmp_end_pt;
							}
						}
					}

					last_pass = 1;
				} else {
					if (last_pass == 1) {
						tmp_end_pt = dly_line;

						if (total_ava_wds == 1) {
							max_wd.baud_rate = baudr;
							max_wd.auto_length = auto_len;
							max_wd.dly_line_sp = tmp_str_pt;
							max_wd.dly_line_ep = tmp_end_pt;
						} else {
							DBG_SPIF_WARN("Baud:%x; auto_length:%x; Delay start:%x; Delay end:%x\n", baudr, auto_len, tmp_str_pt, tmp_end_pt);
							if ((tmp_end_pt - tmp_str_pt) > (max_wd.dly_line_ep - max_wd.dly_line_sp)) {
								max_wd.baud_rate = baudr;
								max_wd.auto_length = auto_len;
								max_wd.dly_line_sp = tmp_str_pt;
								max_wd.dly_line_ep = tmp_end_pt;
							}
						}
					}

					last_pass = 0;
				}
			}

			if ((max_wd.dly_line_ep - max_wd.dly_line_sp) == MAX_DELAY_LINE) {
				break;
			}

			DBG_SPIF_WARN("total wds: %d\r\n", total_ava_wds);
			DBG_SPIF_WARN("Current max window, Baud:%x; auto_length:%x; Delay start:%x; Delay end:%x\n", max_wd.baud_rate, max_wd.auto_length, max_wd.dly_line_sp,
						  max_wd.dly_line_ep);
		}

		if (total_ava_wds) {
			DBG_SPIF_WARN("Find the avaiable windows\r\n");
			break;
		}
	}

	if (total_ava_wds == 0) {
		return _FALSE;
	} else {
		DBG_SPIF_WARN("Baud:%x; auto_length:%x; Delay start:%x; Delay end:%x\n", max_wd.baud_rate, max_wd.auto_length, max_wd.dly_line_sp, max_wd.dly_line_ep);

		/* Disable SPI_FLASH User Mode */
		spic_rtl_disable(spic_dev);

		/* Set Baud Rate*/
		spic_rtl_set_baudr(spic_dev, max_wd.baud_rate);
		spic_rtl_set_fbaudr(spic_dev, max_wd.baud_rate);
		pspic_init_para->baud_rate = max_wd.baud_rate;

		/* Set Dummy Cycle*/
		spic_rtl_set_dummy_cycle(spic_dev, max_wd.auto_length);
		pspic_init_para->rd_dummy_cycle = max_wd.auto_length;

		/* Set Delay Line*/
		rd_data = ((max_wd.dly_line_sp + max_wd.dly_line_ep) >> 1);
		spic_set_delay_line(rd_data);
		pspic_init_para->delay_line = rd_data;

		/* Mark as valid*/
		pspic_init_para->valid = 1;

		/* Enable SPI_FLASH User Mode */
		spic_rtl_enable(spic_dev);

		spic_store_calibration_setting(phal_spic_adaptor);

		return _TRUE;
	}
}

/** \brief Description of spic_load_calibration_setting
 *
 *    spic_load_calibration_setting is used to load calibration settings from flash to the adaptor.
 *    Flash controller will try to load available calibration setting so that it does not have to calibrate.
 *    It takes less time to boot up system without flash calibration process.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
void spic_load_calibration_setting(phal_spic_adaptor_t phal_spic_adaptor)
{
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;
	u8 cpu_type = spic_query_system_clk();
	SPIC_TypeDef *spic_dev  = phal_spic_adaptor->spic_dev;
	pspic_init_para_t pspic_data;
	u32 spic_data;
	u32 spic_data_inv;
	u32 data_offset;
	u32 reg_value;

	/*The last 4 byte is used to check the integrity of data*/
	data_offset = cpu_type * 80 + spic_bit_mode * 8;

	phal_spic_adaptor->addr_byte_num = ThreeBytesLength;

	spic_rtl_disable(spic_dev);
	reg_value = spic_dev->SPIC_AUTO_LENGTH;
	reg_value &= ~SPIC_MASK_AUTO_ADDR_LENGTH;
	reg_value |= (phal_spic_adaptor->addr_byte_num << SPIC_SHIFT_AUTO_ADDR_LENGTH);
	spic_dev->SPIC_AUTO_LENGTH = reg_value;
	spic_data = HAL_READ32(SPI_FLASH_BASE, SPIC_DATA_BASE + data_offset);
	spic_data_inv = HAL_READ32(SPI_FLASH_BASE, SPIC_DATA_BASE + data_offset + 4);

	if (spic_data != 0xFFFFFFFF) {
		if (0xFFFFFFFF == (spic_data ^ spic_data_inv)) {
			pspic_data = (pspic_init_para_t)&spic_data;
			spic_rtl_disable(spic_dev);
			spic_rtl_set_baudr(spic_dev, pspic_data->baud_rate);
			spic_rtl_set_fbaudr(spic_dev, pspic_data->baud_rate);
			spic_rtl_set_dummy_cycle(spic_dev, pspic_data->rd_dummy_cycle);
			spic_set_delay_line(pspic_data->delay_line);
			spic_config_auto_mode(phal_spic_adaptor);

			if (spic_verify_calibration_para() == _TRUE) {
				phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type].baud_rate = pspic_data->baud_rate;
				phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type].rd_dummy_cycle = pspic_data->rd_dummy_cycle;
				phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type].delay_line = pspic_data->delay_line;
				phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type].valid = pspic_data->valid;
				DBG_SPIF_WARN("Bit mode %d, Calibration setting loaded from flash. 0x%x\r\n", spic_bit_mode, spic_data);
			} else {
				hal_flash_return_spi(phal_spic_adaptor);
				DBG_SPIF_ERR("Bit mode %d setting cannot work, switch back to one IO mode. 0x%x\n", spic_bit_mode, spic_data);
			}
		} else {
			DBG_SPIF_WARN("spic_load_calibration_setting: Data in Flash(@ 0x%x = 0x%x 0x%x) is Invalid\r\n",
						  (SPIC_DATA_BASE + data_offset), spic_data, spic_data_inv);
		}
	}
}

/** \brief Description of spic_store_calibration_setting
 *
 *    spic_store_calibration_setting is used to store valid calibration setting to flash after calibration process.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
void spic_store_calibration_setting(phal_spic_adaptor_t phal_spic_adaptor)
{
	u8 spic_bit_mode = phal_spic_adaptor->spic_bit_mode;
	u8 cpu_type = spic_query_system_clk();
	pspic_init_para_t pspic_data;
	u32 data_offset;
	u32 spic_data[2];

	data_offset = cpu_type * 80 + spic_bit_mode * 8;

	spic_data[0] = HAL_READ32(SPI_FLASH_BASE, SPIC_DATA_BASE + data_offset);

	if (spic_data[0] == 0xFFFFFFFF) {
		pspic_data = (pspic_init_para_t) &spic_data[0];
		pspic_data->baud_rate = phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type].baud_rate;
		pspic_data->rd_dummy_cycle = phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type].rd_dummy_cycle;
		pspic_data->delay_line = phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type].delay_line;
		pspic_data->valid = phal_spic_adaptor->spic_init_data[spic_bit_mode][cpu_type].valid;
		spic_data[1] = ~spic_data[0];
		hal_flash_page_program(phal_spic_adaptor, 8, (u32)(SPIC_DATA_BASE + data_offset), (u8 *)&spic_data[0]);
		DBG_SPIF_WARN("spic_store_calibration_setting: Wr=%x\r\n", spic_data[0]);
	} else {
		DBG_SPIF_ERR("spic_store_calibration_setting: The flash memory(@0x%x = 0x%x) cannot be programmed, Erase it first!!\r\n",
					 (SPIC_DATA_BASE + data_offset), spic_data[0]);
	}
}
/** *@} */ /* End of group hal_spic_ram_func */

/** *@} */ /* End of group hal_spic */


