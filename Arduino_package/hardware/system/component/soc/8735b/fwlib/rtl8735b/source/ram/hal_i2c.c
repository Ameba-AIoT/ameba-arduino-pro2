/**************************************************************************//**
 * @file     hal_i2c.c
 * @brief    This file implements the I2C HAL functions.
 *
 * @version  V1.00
 * @date     2021-05-13
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


#include "hal_i2c.h"

#include "hal_cache.h"
#include "hal_gdma.h"
#ifdef CONFIG_I2C_EN

#if   defined ( __CC_ARM )                                            /* ARM Compiler 4/5 */
extern hal_i2c_func_stubs_t Image$$_STUB_I2C$$Base;     // symbol from linker script
#define __rom_stubs_hal_i2c Image$$_STUB_I2C$$Base
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)       /* ARM Compiler 6 */
extern hal_i2c_func_stubs_t Image$$_STUB_I2C$$Base;     // symbol from linker script
#define __rom_stubs_hal_i2c Image$$_STUB_I2C$$Base
#elif defined ( __GNUC__ )
extern hal_i2c_func_stubs_t __rom_stubs_hal_i2c;     // symbol from linker script
#elif defined ( __ICCARM__ )
extern hal_i2c_func_stubs_t __rom_stubs_hal_i2c;     // symbol from linker script
#endif

gdma_ch_lli_t i2c_tx_gdma_ch_lli[I2C_GDMA_MAX_BLOCK] __ALIGNED(32);
gdma_ch_lli_t i2c_rx_gdma_ch_lli[I2C_GDMA_MAX_BLOCK] __ALIGNED(32);

/**
 * @addtogroup hs_hal_i2c I2C
 * @{
 */

/** \brief Description of hal_i2c_pin_register
 *
 *    hal_i2c_pin_register is used for i2c pinmux initialization and register.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:        Pointer to I2C control adaptor.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_i2c_pin_register(hal_i2c_adapter_t *phal_i2c_adapter)
{
	hal_status_t ret;

	hal_sys_peripheral_en(I2C0_SYS + phal_i2c_adapter->init_dat.index, 1);

	if ((uint8_t)(phal_i2c_adapter->pltf_dat.scl_pin) != (uint8_t)0xFF) {
		ret = hal_pinmux_register(phal_i2c_adapter->pltf_dat.scl_pin, PID_I2C0 + phal_i2c_adapter->init_dat.index);
	}

	if ((uint8_t)(phal_i2c_adapter->pltf_dat.sda_pin) != (uint8_t)0xFF) {
		ret = hal_pinmux_register(phal_i2c_adapter->pltf_dat.sda_pin, PID_I2C0 + phal_i2c_adapter->init_dat.index);
	}

	return ret;
}

/** \brief Description of hal_i2c_pin_unregister
 *
 *    hal_i2c_pin_unregister is used for adc pinmux un-initialization and un-register.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:        Pointer to I2C control adaptor.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_i2c_pin_unregister(hal_i2c_adapter_t *phal_i2c_adapter)
{
	hal_status_t ret;

	hal_sys_peripheral_en(I2C0_SYS + phal_i2c_adapter->init_dat.index, 0);

	if ((uint8_t)(phal_i2c_adapter->pltf_dat.scl_pin) != (uint8_t)0xFF) {
		ret = hal_pinmux_unregister(phal_i2c_adapter->pltf_dat.scl_pin, PID_I2C0 + phal_i2c_adapter->init_dat.index);
	}

	if ((uint8_t)(phal_i2c_adapter->pltf_dat.sda_pin) != (uint8_t)0xFF) {
		ret |= hal_pinmux_unregister(phal_i2c_adapter->pltf_dat.sda_pin, PID_I2C0 + phal_i2c_adapter->init_dat.index);
	}

	return ret;
}

/** \brief Description of hal_i2c_init
 *
 *    hal_i2c_init is to execute i2c init process.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:        Pointer to I2C control adaptor.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_i2c_init(hal_i2c_adapter_t *phal_i2c_adapter, uint32_t scl_pin, uint32_t sda_pin)
{
	hal_status_t retv;

	phal_i2c_adapter->pltf_dat.scl_pin = scl_pin;
	phal_i2c_adapter->pltf_dat.sda_pin = sda_pin;

	/* Pinmux Initialization */
	retv = hal_i2c_pin_register(phal_i2c_adapter);
	if (retv != HAL_OK) {
		return retv;
	} else {
#if IS_CUT_TEST(CONFIG_CHIP_VER)
		hal_rtl_i2c_init_patch(phal_i2c_adapter);
#endif
#ifdef ARDUINO_SDK
		return hal_rtl_i2c_init_arduino_patch(phal_i2c_adapter);
#else
		return __rom_stubs_hal_i2c.hal_i2c_init(phal_i2c_adapter);
#endif
	}
}

/** \brief Description of hal_i2c_deinit
 *
 *    hal_i2c_deinit is to execute i2c deinit process.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:        Pointer to I2C control adaptor.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_i2c_deinit(hal_i2c_adapter_t *phal_i2c_adapter)
{
	hal_status_t retv;
#if IS_AFTER_CUT_E(CONFIG_CHIP_VER)
	retv = __rom_stubs_hal_i2c.hal_i2c_deinit(phal_i2c_adapter);
#else
	retv = hal_rtl_i2c_deinit_patch(phal_i2c_adapter);
#endif
	if (retv != HAL_OK) {
		return retv;
	} else {
		return hal_i2c_pin_unregister(phal_i2c_adapter);
	}
}

/** \brief Description of hal_i2c_timeout_chk
 *
 *    hal_i2c_timeout_chk is used to check if I2C operation is time-out.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter: Pointer to I2C control adapter.
 *   \param[in] uint32_t start_cnt: Start system time count.
 *
 *   \return uint8_t:       Time out result \n\r\t
 *                          0: NOT time-out, 1: Time-out.
 */
uint8_t hal_i2c_timeout_chk(hal_i2c_adapter_t *phal_i2c_adapter, uint32_t start_cnt)
{
	return __rom_stubs_hal_i2c.hal_i2c_timeout_chk(phal_i2c_adapter, start_cnt);
}

/** \brief Description of hal_i2c_chk_mod
 *
 *    hal_i2c_chk_mod is used to check I2C operation mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:           Check mode status. \n\r
 *                              0: Slave mode\n\r
 *                              1: Master mode\n\r
 *                              2: Configuration error.\n\r
 */
uint8_t hal_i2c_chk_mod(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_chk_mod(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_pure_init
 *
 *    hal_i2c_pure_init is used to initialize I2C module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t :      i2c enable status
 */
uint8_t hal_i2c_pure_init(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_pure_init(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_pure_deinit
 *
 *    hal_i2c_pure_deinit is used to deinit I2C module.
 *    It's directly to disable I2C module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t: I2C enable status.
 */
uint8_t hal_i2c_pure_deinit(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_pure_deinit(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_en_ctrl
 *
 *    hal_i2c_en_ctrl is used to enable/disable I2C module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t enable: To enable/disable I2C.\n\r
 *                                  0: Disable.\n\r
 *                                  1: Enable\n\r
 *                                  2: Force Disable
 *   \retrun uint8_t:               I2C enable status.
 */
uint8_t hal_i2c_en_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable)
{
	return __rom_stubs_hal_i2c.hal_i2c_en_ctrl(phal_i2c_adapter, enable);
}

/** \brief Description of hal_i2c_set_clk
 *
 *    hal_i2c_set_clk is used to set I2C clock.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return hal_status_t:      HAL status.
 */
hal_status_t hal_i2c_set_clk(hal_i2c_adapter_t *phal_i2c_adapter)
{
#if IS_CUT_TEST(CONFIG_CHIP_VER)

	return hal_rtl_i2c_set_clk_patch(phal_i2c_adapter);
#else
	return __rom_stubs_hal_i2c.hal_i2c_set_clk(phal_i2c_adapter);
#endif
}

/** \brief Description of hal_i2c_intr_ctrl
 *
 *    hal_i2c_intr_ctrl is used to set/clear interrupt mask bits.\n\r
 *    The given intrmsk bits would be cleared first in this function therefore the related\n\r
 *    interrupt mask is masked.\n\r
 *    If it's to set mask bits, the related interrupt mask would be set therefore the realted\n\r
 *    interrupt mask is unmasked.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter: Pointer to I2C control adapter.
 *   \param[in] uint8_t set_clr: To set or clear interrupt. \n\r
 *                               The interrupt mask register is active low.\n\r
 *                                1: set, which means the related interrupt mask is unmasked.\n\r
 *                                0: clear, which means the related interrupt mask is masked.\n\r
 *   \param[in] uint16_t intr_msk: I2C interrupt mask bit.
 *   \return hal_status_t:      HAL status.
 */
hal_status_t hal_i2c_intr_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t set_clr, uint16_t intr_msk)
{
	return __rom_stubs_hal_i2c.hal_i2c_intr_ctrl(phal_i2c_adapter, set_clr, intr_msk);
}

/** \brief Description of hal_i2c_wr
 *
 *    hal_i2c_wr is used to send I2C data. In master mode, this function could send write command, too.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] const uint8_t *dat_buf:     Data buffer address for I2C write.
 *   \param[in] uint32_t dat_len:           Data length for I2C write.
 *   \param[in] uint8_t ctrl:           To control what I2C would do when data is all sent. (Only for Master Mode)\n\r
 *                                      In slave mode, this part should be always 0.\n\r
 *                                      0: Do nothing. There will not be a STOP condition when all data is sent.\n\r
 *                                      And there will not be any START/RESTART condition in the next transmission ,either.\n\r
 *                                      1: Send STOP after the last data.\n\r
 *                                      2: There will NOT be a STOP condition after the last data sent. But\n\r
 *                                      the next transmision would have a START/RESTART condition sent first.\n\r
 *                                      So setting 2 to this field could influence the following transmission.\n\r
 *   \return hal_status_t:      When the given Ctrl is NOT fit with hardware setting, a value of HAL_STS_ERR_HW\n\r
 *                              will be returned. Otherwise, a value of HAL_STS_OK will be returned.
 */
hal_status_t hal_i2c_wr(hal_i2c_adapter_t *phal_i2c_adapter, const uint8_t *dat_buf, uint32_t dat_len, uint8_t ctrl)
{
	return __rom_stubs_hal_i2c.hal_i2c_wr(phal_i2c_adapter, dat_buf, dat_len, ctrl);
}

/** \brief Description of hal_i2c_mst_send_rdcmd
 *
 *    hal_i2c_mst_send_rdcmd is used to send I2C master read command.
 *    It should only be used for master mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint32_t cmd_len:           Read commnad length for I2C read.
 *   \param[in] uint8_t ctrl:               To control what I2C would do when data is all sent. (Only for Master Mode)\n\r
 *                                      0: Do nothing. There will not be a STOP condition when all data is sent.\n\r
 *                                      And there will not be any START/RESTART condition in the next transmission ,either.\n\r
 *                                      1: Send STOP after the last data.\n\r
 *                                      2: There will NOT be a STOP condition after the last data sent. But\n\r
 *                                      the next transmision would have a START/RESTART condition sent first.\n\r
 *                                      So setting 2 to this field could influence the following transmission.
 *
 *  \return void
 */
void hal_i2c_mst_send_rdcmd(hal_i2c_adapter_t *phal_i2c_adapter, uint32_t cmd_len, uint8_t ctrl)
{
	__rom_stubs_hal_i2c.hal_i2c_mst_send_rdcmd(phal_i2c_adapter, cmd_len, ctrl);
}

/** \brief Description of hal_i2c_dma_ctrl
 *
 *    hal_i2c_dma_ctrl is used to enable/disable I2C DMA function.\n\r
 *    Enable is used to control that this function performs enable or disable operaiton.\n\r
 *    And it would set/clear related register according to the given DMAEnMsk.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t enable:             To enable/disable I2C DMA function.\n\r
 *                                      0: Disable.\n\r
 *                                      1: Enable.
 *   \return uint32_t:         I2C DMA enable status.
 */
uint32_t hal_i2c_dma_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable)
{
	return __rom_stubs_hal_i2c.hal_i2c_dma_ctrl(phal_i2c_adapter, enable);
}

/** \brief Description of hal_i2c_mst_restr_ctrl
 *
 *    hal_i2c_mst_restr_ctrl is used to enable/disable RESTART feature.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t restr_en:               To enable/disable I2C RESTART fearture. Software should enable\n\r
 *                                              this feature before it sets RESTART command in REG_IC_DATA_CMD\n\r
 *                                              register.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_mst_restr_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t restr_en)
{
	return __rom_stubs_hal_i2c.hal_i2c_mst_restr_ctrl(phal_i2c_adapter, restr_en);
}

/** \brief Description of hal_i2c_mst_gc_sb_ctrl
 *
 *    hal_i2c_mst_gc_sb_ctrl is used to enable/disable General Call or START Byte features.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t enable:             To enable/disable I2C General Call or START Byte feature.
 *   \param[in] uint8_t gc_sb:          Select General Call or START Byte feature.\n\r
 *                                      0: General Call\n\r
 *                                      1: START Byte
 *   \return hal_status_t
 */
hal_status_t hal_i2c_mst_gc_sb_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable, uint8_t gc_sb)
{
	return __rom_stubs_hal_i2c.hal_i2c_mst_gc_sb_ctrl(phal_i2c_adapter, enable, gc_sb);
}

/** \brief Description of hal_i2c_slv_no_ack_ctrl
 *
 *    hal_i2c_slv_no_ack_ctrl is used to enable/disable no acknowledge feature in\n\r
 *    slave mode. If SlvNoAck is enabled, I2C would generate NACK after a data byte is \n\r
 *    received in slave mode. If SlvNoAck is disabled, I2C would gernerate ACK/NACK,\n\r
 *    depending on normal criteria.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t no_ack_en:              To enable/disable slave no ack feature.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_slv_no_ack_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t no_ack_en)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_no_ack_ctrl(phal_i2c_adapter, no_ack_en);
}

/** \brief Description of hal_i2c_slv_no_ack_sts
 *
 *    hal_i2c_slv_no_ack_sts is used to get the enable status of slave no ack function.\n\r
 *    If its return value is 0, I2C slave no ack is disabled and could ack to normal transfermation.\n\r
 *    If its return value is 1, I2C slave no ack is enabled and could ONLY send NACK to all
 *    master command or data.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:               slave mode no-ack status.\n\r
 *                                  0: slave no ack disabled. 1: slave no ack enabled.
 */
uint8_t hal_i2c_slv_no_ack_sts(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_no_ack_sts(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_ack_gc_ctrl
 *
 *    hal_i2c_slv_ack_gc_ctrl is used to enable/disable I2C responding General Call \n\r
 *    feature. If it's enabled, I2C could responds to a General Call.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t slv_gc_en:      To enable/disable slave ack General Call feature.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_slv_ack_gc_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t slv_gc_en)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_ack_gc_ctrl(phal_i2c_adapter, slv_gc_en);
}

/** \brief Description of hal_i2c_slv_ack_gc_sts
 *
 *    hal_i2c_slv_ack_gc_sts is used to get the enable status of slave ack General
 *    Call.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:               slave mode adc GC status.\n\r
 *                                  0: Slave does NOT ack GC. 1: Slave could ack GC.
 */
uint8_t hal_i2c_slv_ack_gc_sts(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_ack_gc_sts(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_to_slp
 *
 *    hal_i2c_slv_to_slp is used to set I2C slave into sleep state.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_slv_to_slp(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_to_slp(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_chk_mst_wr
 *
 *    hal_i2c_slv_chk_mst_wr is used to check if there is a master write command for slave addresses of
 *    rtl8195b.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:               0: An master write command for slave address 0 is matched.\n\r
 *                                  1: An master write command for slave address 1 is matched.\n\r
 *                                  0xEF: Error status, disable/deinit process is recommended.\n\r
 *                                  0xFF: No write commnad rtl8195b I2C slave.
 */
uint8_t hal_i2c_slv_chk_mst_wr(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_chk_mst_wr(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_chk_rd_req
 *
 *    hal_i2c_slv_chk_rd_req is used to check if there is a master read command for slave addresses of
 *    rtl8195b.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:       0: An master read command for slave address 0 is matched.\n\r
 *                          1: An master read command for slave address 1 is matched.\n\r
 *                          0xEF: Error status, disable/deinit process is recommended.\n\r
 *                          0xFF: No read commnad rtl8195b I2C slave.
 *
 */
uint8_t hal_i2c_slv_chk_rd_req(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_chk_rd_req(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_pin_init
 *
 *    hal_i2c_pin_init is used to initialize i2c clock and pin.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_pin_init(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_pin_init(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_pin_deinit
 *
 *    hal_i2c_pin_deinit is used to deinitialize i2c clock and pin.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_pin_deinit(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_pin_deinit(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_load_default
 *
 *    hal_i2c_load_default is used to load default setting for i2c module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] uint8_t index:   i2c device index.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_load_default(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t index)
{
	return __rom_stubs_hal_i2c.hal_i2c_load_default(phal_i2c_adapter, index);
}

/** \brief Description of hal_i2c_set_tar
 *
 *    hal_i2c_set_tar is to set target slave address in master mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] uint8_t mst_rw:   This target address is for read or write usage.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_set_tar(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t mst_rw)
{
	return __rom_stubs_hal_i2c.hal_i2c_set_tar(phal_i2c_adapter, mst_rw);
}

/** \brief Description of hal_i2c_send_addr_retry
 *
 *    hal_i2c_send_addr_retry is to send address and the first data byte with fail retry.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_addr_retry(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_send_addr_retry(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_send_poll
 *
 *    hal_i2c_send_poll is to send i2c data by polling (blocking) mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_poll(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_send_poll(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_send_intr
 *
 *    hal_i2c_send_intr is to send i2c data by interrupt mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_intr(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_send_intr(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_recv_addr_retry
 *
 *    hal_i2c_recv_addr_retry is to send slave address and the first read command with retry features.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_addr_retry(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_recv_addr_retry(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_recv_poll
 *
 *    hal_i2c_recv_poll is to receive I2C data by polling (blocking) mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_poll(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_recv_poll(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_recv_intr
 *
 *    hal_i2c_recv_intr is to receive I2C data by interrupt (non-blocking) mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_intr(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_recv_intr(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_set_sar
 *
 *    hal_i2c_set_sar is to set slave own address in slave mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] uint8_t sar_idx:                 SAR index.
 *   \param[in] uint16_t slv_addr:               SAR.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_set_sar(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t sar_idx, uint16_t slv_addr)
{
	return __rom_stubs_hal_i2c.hal_i2c_set_sar(phal_i2c_adapter, sar_idx, slv_addr);
}

/** \brief Description of hal_i2c_slv_recv_poll
 *
 *    hal_i2c_slv_recv_poll is to execute slave receive in polling(blocking) mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t
 */
uint32_t hal_i2c_slv_recv_poll(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_recv_poll(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_recv_intr
 *
 *    hal_i2c_slv_recv_intr is to execute slave receive in interrupt(non-blocking) mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t
 */
uint32_t hal_i2c_slv_recv_intr(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_recv_intr(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_send_poll
 *
 *    hal_i2c_slv_send_poll is to execute slave send transfer by polling mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t
 */
uint32_t hal_i2c_slv_send_poll(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_send_poll(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_send_intr
 *
 *    hal_i2c_slv_send_intr is to execute slave send transfer by interrupt mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t
 */
uint32_t hal_i2c_slv_send_intr(hal_i2c_adapter_t *phal_i2c_adapter)
{
	return __rom_stubs_hal_i2c.hal_i2c_slv_send_intr(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_reg_comm_irq
 *
 *    hal_i2c_reg_comm_irq is to register a common IRQ handler for all I2C.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] irq_handler_t handler:   IRQ handler.
 *   \return void
 */
void hal_i2c_reg_comm_irq(hal_i2c_adapter_t *phal_i2c_adapter, irq_handler_t handler)
{
	int32_t irq_index = I2C0_IRQn + phal_i2c_adapter->init_dat.index;

	hal_irq_disable(irq_index);
	__ISB();

	// Register I2C common IRQ handler
	hal_irq_set_vector(irq_index, (uint32_t)handler);
	hal_irq_clear_pending(irq_index);
	hal_irq_enable(irq_index);
}

/** \brief Description of hal_i2c_reg_irq
 *
 *    hal_i2c_reg_irq is to register a unique IRQ handler for each I2C.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] irq_handler_t handler:   IRQ handler.
 *   \return void
 */
void hal_i2c_reg_irq(hal_i2c_adapter_t *phal_i2c_adapter, irq_handler_t handler)
{
	hal_i2c_group_adapter_t *i2c_gp_adpt = __rom_stubs_hal_i2c.hal_i2c_group_adpt;
	i2c_gp_adpt->adapter[phal_i2c_adapter->init_dat.index] = phal_i2c_adapter;
	i2c_gp_adpt->irq_fun[phal_i2c_adapter->init_dat.index] = handler;
}

/** \brief Description of hal_i2c_unreg_irq
 *
 *    hal_i2c_unreg_irq is to unregister a unique IRQ handler for each I2C.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return void
 */
uint8_t hal_i2c_unreg_irq(hal_i2c_adapter_t *phal_i2c_adapter)
{
	uint8_t i;
	hal_i2c_group_adapter_t *i2c_gp_adpt = __rom_stubs_hal_i2c.hal_i2c_group_adpt;

	i2c_gp_adpt->adapter[phal_i2c_adapter->init_dat.index] = NULL;
	i2c_gp_adpt->irq_fun[phal_i2c_adapter->init_dat.index] = (irq_handler_t)NULL;
	for (i = 0; i < HP_I2C_NO; i++) {
		if (i2c_gp_adpt->irq_fun[phal_i2c_adapter->init_dat.index] != NULL) {
			break;
		}
	}

	if (i == (HP_I2C_NO)) {
		// No any UART port has IRQ handler, so disable the common interrupt
		for (i = 0; i < HP_I2C_NO; i++) {

			hal_irq_disable(I2C0_IRQn + i);
			__ISB();
			hal_irq_set_vector(I2C0_IRQn + i, (uint32_t)NULL);
		}
		return 1;
	}

	return 0;
}

/** \brief Description of hal_i2c_send_dma_init
 *
 *    hal_i2c_send_dma_init is to allocate a GDMA channel and initialize I2C send DMA data structure.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] hal_gdma_adaptor_t *pi2c_gdma_tx_adaptor:   pointer to I2C GDMA TX adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_dma_init(hal_i2c_adapter_t *phal_i2c_adapter, hal_gdma_adaptor_t *pi2c_gdma_tx_adaptor)
{
	if (pi2c_gdma_tx_adaptor == NULL) {
		DBG_I2C_ERR("hal_i2c_send_dma_init: TX DMA adaptor is NULL\n\r");
		return HAL_ERR_PARA;
	}

	/* only i2c0 supports DMA transfer */
	if (phal_i2c_adapter->init_dat.index >= 2) {
		DBG_I2C_ERR("only i2c0/1 supports DMA\n\r");
		return HAL_ERR_PARA;
	}

	/* assign input adaptor to internal struct */
	phal_i2c_adapter->tx_dma_dat.padaptor = pi2c_gdma_tx_adaptor;

	pi2c_gdma_tx_adaptor->busy = 0;
	pi2c_gdma_tx_adaptor->have_chnl = 0;
	/* Allocate DMA channel first */
	if (phal_i2c_adapter->tx_dma_dat.ch_sts == I2CDmaChNone) {
		if (hal_gdma_chnl_alloc(phal_i2c_adapter->tx_dma_dat.padaptor, MultiBlkDis) != HAL_OK) {
			DBG_I2C_ERR("hal_i2c_send_dma_init: TX DMA allocation failed\n\r");
			return HAL_ERR_HW;
		}
		phal_i2c_adapter->tx_dma_dat.ch_sts = I2CDmaChGot;
	}

	if (phal_i2c_adapter->tx_dma_dat.ch_sts != I2CDmaChInitialed) {
		pi2c_gdma_tx_adaptor->gdma_isr_type = (TransferType | ErrType);
		pi2c_gdma_tx_adaptor->gdma_ctl.int_en = 1;
		pi2c_gdma_tx_adaptor->gdma_ctl.src_msize   = MsizeFour;
		pi2c_gdma_tx_adaptor->gdma_ctl.src_tr_width = TrWidthTwoBytes;
		pi2c_gdma_tx_adaptor->gdma_ctl.dest_msize  = MsizeEight;
		pi2c_gdma_tx_adaptor->gdma_ctl.dst_tr_width = TrWidthOneByte;
		pi2c_gdma_tx_adaptor->gdma_ctl.dinc        = NoChange;
		pi2c_gdma_tx_adaptor->gdma_ctl.sinc        = IncType;
		pi2c_gdma_tx_adaptor->gdma_ctl.tt_fc       = TTFCMemToPeri;
		pi2c_gdma_tx_adaptor->gdma_cfg.dest_per    = GDMA_HANDSHAKE_I2C0_TX + phal_i2c_adapter->init_dat.index * 2;
		//padc_gdma_tx_adaptor->dcache_invalidate_by_addr = __rom_stubs_hal_cache.dcache_invalidate_by_addr;
		//padc_gdma_tx_adaptor->dcache_clean_by_addr = __rom_stubs_hal_cache.dcache_clean_by_addr;

		/* For non-multi-block transfer in default */
		pi2c_gdma_tx_adaptor->pgdma_ch_lli         = NULL;
		hal_gdma_handshake_init(pi2c_gdma_tx_adaptor, phal_i2c_adapter->tx_dma_dat.padaptor->gdma_cfg.dest_per);
		hal_gdma_chnl_init(pi2c_gdma_tx_adaptor);
		hal_gdma_irq_reg(pi2c_gdma_tx_adaptor,
						 (irq_handler_t)(__rom_stubs_hal_i2c.hal_i2c_dma_irq_handler), (void *)phal_i2c_adapter);
		phal_i2c_adapter->tx_dma_dat.ch_sts = I2CDmaChInitialed;

		/* assign default d-cache handling function */
#if defined(I2C_CACHE_RAM_VERSION)
		phal_i2c_adapter->dcache_clean_by_addr = dcache_clean_by_addr_ual32;
#else
		phal_i2c_adapter->dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;
#endif
	}

	return HAL_OK;
}

/** \brief Description of hal_i2c_send_dma_deinit
 *
 *    hal_i2c_send_dma_deinit is to free a GDMA channel and de-initialize I2C send DMA data structure.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_dma_deinit(hal_i2c_adapter_t *phal_i2c_adapter)
{
	if (phal_i2c_adapter->tx_dma_dat.padaptor != NULL) {
		hal_gdma_chnl_free((void *)phal_i2c_adapter->tx_dma_dat.padaptor);
	} else {
		return HAL_ERR_PARA;
	}

	/* remove default d-cache handling function */
	phal_i2c_adapter->dcache_clean_by_addr = NULL;
	phal_i2c_adapter->tx_dma_dat.ch_sts = I2CDmaChNone;
	return HAL_OK;
}

/** \brief Description of hal_i2c_send_dma
 *
 *    hal_i2c_send_dma is to execute I2C TX transfer with DMA and the related TX information should be\n\r
 *    given in phal_i2c_adapter->tx_dat.\n\r
 *    hal_i2c_send_dma_init MUST be invoked first before using this function.\n\r
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_dma(hal_i2c_adapter_t *phal_i2c_adapter)
{
	i2c_tx_info_t   *pi2c_tx_info = (i2c_tx_info_t *) & (phal_i2c_adapter->tx_dat);
	I2C_TypeDef *pi2c_reg = (I2C_TypeDef *)phal_i2c_adapter->init_dat.reg_base;
	uint32_t ic_dma_cmd_tmp;

	volatile uint32_t gdma_idx;
	hal_status_t ret;
	uint8_t multi_block_en = MultiBlkDis;

	/* Update data length of DMA mode */
	phal_i2c_adapter->tx_dma_dat.dat_len = pi2c_tx_info->len;

	//change to poll mode , if pi2c_tx_info->len < tx_dma_bound
	if (pi2c_tx_info->len < phal_i2c_adapter->pltf_dat.tx_dma_bound) {
		DBG_I2C_WARN("mst send mode is changed to poll since data is short.\n\r");
		return hal_i2c_send_poll(phal_i2c_adapter);
	} else if (pi2c_tx_info->len > HP_I2C_DMA_MAX_LEN) {
		DBG_I2C_ERR("hal_i2c_send_dma: data length is larger than max DMA length of 65535\n\r");
		return HAL_ERR_PARA;
	}

	/* Update software status and clear i2c interrupt status */
	phal_i2c_adapter->status = I2CStatusTxing;
	READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_TX_ABRT);
	READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_ACT);
	READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_INTR);
	READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_DMA_DONE);

	phal_i2c_adapter->tx_dma_dat.padaptor->ch_sar = (uint32_t)(pi2c_tx_info->buf);
	phal_i2c_adapter->tx_dma_dat.padaptor->ch_dar = (uint32_t)(&(pi2c_reg->I2C_DAT_CMD));
	DBG_I2C_INFO("tx buf: %x\n\r", phal_i2c_adapter->tx_dma_dat.padaptor->ch_sar);
	DBG_I2C_INFO("tx dest: %x\n\r", phal_i2c_adapter->tx_dma_dat.padaptor->ch_dar);

	/* modify for non-alignment case */
	if ((pi2c_tx_info->len & 0x03) != 0) {
		phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.src_tr_width = TrWidthOneByte;
		phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.block_size = pi2c_tx_info->len;
	} else {
		phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.block_size = pi2c_tx_info->len >>
				(phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.src_tr_width);
	}

	/* Check if it needs multi-block channel or not */
	if (phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.block_size > MAX_DMA_BLOCK_SIZE) {
		if (phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.block_size <= MAX_DMA_BLOCK_SIZE * 32) {
			multi_block_en = MultiBlkEn;
			// Need to use multiple block DMA
			if (phal_i2c_adapter->tx_dma_dat.padaptor->ch_num < 4) {
				// Current GDMA Channel didn't support multiple block DMA, re-allocate another one
				DBG_I2C_INFO("hal_i2c_send_dma: re-allocate GDMA chnl to support Multi-Blk transfer\r\n\r");
				gdma_idx = phal_i2c_adapter->tx_dma_dat.padaptor->gdma_index;  // backup old GDMA index
				hal_gdma_chnl_free(phal_i2c_adapter->tx_dma_dat.padaptor);
				ret = hal_gdma_chnl_alloc(phal_i2c_adapter->tx_dma_dat.padaptor, MultiBlkEn);

				if (ret != HAL_OK) {
					phal_i2c_adapter->tx_dma_dat.ch_sts = I2CDmaChNone;
					DBG_I2C_ERR("hal_i2c_send_dma: re-allocate multiple block DMA channel failed(%d)\r\n\r", ret);
					return ret;
				} else {
					DBG_I2C_INFO("hal_i2c_send_dma: re-allocated GDMA %u chnl %u\r\n\r", phal_i2c_adapter->tx_dma_dat.padaptor->gdma_index,
								 phal_i2c_adapter->tx_dma_dat.padaptor->ch_num);
					phal_i2c_adapter->tx_dma_dat.padaptor->pgdma_ch_lli = &i2c_tx_gdma_ch_lli[0];
					hal_gdma_chnl_init(phal_i2c_adapter->tx_dma_dat.padaptor);
				}

				// Update GDMA handshake bit and IRQ handler(since may use different GDMA HW)
				if (gdma_idx != phal_i2c_adapter->tx_dma_dat.padaptor->gdma_index) {
					// allocated to different GDMA HW, update the handshake bit
					hal_gdma_handshake_init(phal_i2c_adapter->tx_dma_dat.padaptor, phal_i2c_adapter->tx_dma_dat.padaptor->gdma_cfg.dest_per);
				}
				hal_gdma_irq_reg((phal_i2c_adapter->tx_dma_dat.padaptor),
								 (irq_handler_t)(__rom_stubs_hal_i2c.hal_i2c_dma_irq_handler), (void *)phal_i2c_adapter);
			}
		} else {
			DBG_I2C_ERR("hal_i2c_send_dma: TX length too long(%lu), it requires too much DMA blks\r\n\r",
						pi2c_tx_info->len);
			return HAL_ERR_PARA;
		}
	}
	hal_i2c_dma_ctrl(phal_i2c_adapter, I2CDisable);
	pi2c_reg->I2C_DMA_TDLR = phal_i2c_adapter->init_dat.tx_dma_rq_lv;
	pi2c_reg->I2C_DMA_MOD = I2CDmaReg;
	pi2c_reg->I2C_DMA_LEN = pi2c_tx_info->len;

	ic_dma_cmd_tmp = pi2c_reg->I2C_DMA_CMD;
	HAL_CLEAR_BIT(ic_dma_cmd_tmp, I2C_BIT_DMA_CMD | I2C_BIT_DMA_STP | I2C_BIT_DMA_RSTRT);

	if (phal_i2c_adapter->mst_spe_func & I2CMasterRestart) {
		HAL_SET_BIT(ic_dma_cmd_tmp, I2C_BIT_DMA_RSTRT);    /* Set RESTART for the next byte */
	} else {
		if (pi2c_tx_info->mst_stop == 1) {
			HAL_SET_BIT(ic_dma_cmd_tmp, I2C_BIT_DMA_STP);
		}
	}

	pi2c_reg->I2C_DMA_CMD = ic_dma_cmd_tmp;
	hal_i2c_dma_ctrl(phal_i2c_adapter, I2CEnable);
	pi2c_reg->I2C_INTR_MSK  = (I2C_BIT_M_TX_ABRT | I2C_BIT_M_TX_OVER);
	HAL_SET_BIT(pi2c_reg->I2C_DMA_CR, I2C_BIT_DMA_TDMAE);

	//dcache_clean_by_addr ((uint32_t *)pi2c_tx_info->buf, (int32_t)pi2c_tx_info->len);
	/* deal with d-cache sync. (clean) */
	if (is_dcache_enabled()) {
		if (phal_i2c_adapter->dcache_clean_by_addr != NULL) {
			phal_i2c_adapter->dcache_clean_by_addr((uint32_t *)pi2c_tx_info->buf, (int32_t)pi2c_tx_info->len);
		} else {
			DBG_I2C_ERR("D-Cache is enabled but clean function is NOT available before tx GDMA starts.\n\r");
		}
	}

	hal_gdma_transfer_start((void *)phal_i2c_adapter->tx_dma_dat.padaptor, multi_block_en);
	return HAL_OK;
}

/** \brief Description of hal_i2c_send
 *
 *    hal_i2c_send is an upper layer I2C send transfer API. It executes the related send(TX) API according \n\r
 *    to the phal_i2c_adapter->op_mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send(hal_i2c_adapter_t *phal_i2c_adapter)
{
	i2c_tx_info_t   *pi2c_tx_info = (i2c_tx_info_t *) & (phal_i2c_adapter->tx_dat);
	hal_status_t retv = HAL_OK;

	if (phal_i2c_adapter->op_mode <= I2CModeDMA) {
		hal_i2c_set_tar(phal_i2c_adapter, I2CWrite);

		if (phal_i2c_adapter->mst_spe_func & I2CAddressRetry) {
			retv = hal_i2c_send_addr_retry(phal_i2c_adapter);

			if (retv != HAL_OK) {
				return (hal_status_t)retv;
			}
		}

		if (pi2c_tx_info->len == 0) {
			phal_i2c_adapter->status = I2CStatusIdle;
			if (phal_i2c_adapter->usr_cb.txc.cb != NULL) {
				phal_i2c_adapter->usr_cb.txc.cb((void *)phal_i2c_adapter->usr_cb.txc.dat);
			}
			return (hal_status_t)retv;
		}

		switch (phal_i2c_adapter->op_mode) {
		case I2CModePoll:
			retv = hal_i2c_send_poll(phal_i2c_adapter);
			break;
		case I2CModeInterrupt:
			retv = hal_i2c_send_intr(phal_i2c_adapter);
			break;
		case I2CModeDMA:
			/* only i2c0 supports DMA transfer */
			if (phal_i2c_adapter->init_dat.index >= 2) {
				DBG_I2C_ERR("only i2c0/1 supports DMA\n\r");
				return HAL_ERR_PARA;
			}
			retv = hal_i2c_send_dma(phal_i2c_adapter);
			break;
		default:
			retv = HAL_ERR_UNKNOWN;
			break;
		}
	}  else {
		retv = HAL_ERR_UNKNOWN;
	}

	return (hal_status_t)retv;
}

/** \brief Description of hal_i2c_recv_dma_init
 *
 *    hal_i2c_recv_dma_init is to allocate DMA channel and initialize I2C DMA data structure.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] hal_gdma_adaptor_t *pi2c_gdma_rx_adaptor:   pointer to I2C GDMA RX adatper.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_dma_init(hal_i2c_adapter_t *phal_i2c_adapter, hal_gdma_adaptor_t *pi2c_gdma_rx_adaptor)
{
	if (pi2c_gdma_rx_adaptor == NULL) {
		DBG_I2C_ERR("hal_i2c_recv_dma_init: TX DMA adaptor is NULL\n\r");
		return HAL_ERR_PARA;
	}

	/* only i2c0 supports DMA transfer */
	if (phal_i2c_adapter->init_dat.index >= 2) {
		DBG_I2C_ERR("only i2c0/1 supports DMA\n\r");
		return HAL_ERR_PARA;
	}

	/* assign input adaptor to internal struct */
	phal_i2c_adapter->rx_dma_dat.padaptor = pi2c_gdma_rx_adaptor;

	pi2c_gdma_rx_adaptor->busy = 0;
	pi2c_gdma_rx_adaptor->have_chnl = 0;

	/* Allocate DMA channel first */
	if (phal_i2c_adapter->rx_dma_dat.ch_sts == I2CDmaChNone) {
		if (phal_i2c_adapter->rx_dma_dat.padaptor == NULL) {
			DBG_I2C_ERR("hal_i2c_recv_dma_init: RX DMA adaptor is NULL\n\r");
			return HAL_ERR_HW;
		}

		if (hal_gdma_chnl_alloc(phal_i2c_adapter->rx_dma_dat.padaptor, MultiBlkDis) != HAL_OK) {
			DBG_I2C_ERR("hal_i2c_recv_dma_init: RX DMA allocation failed\n\r");
			return HAL_ERR_HW;
		}
		phal_i2c_adapter->rx_dma_dat.ch_sts = I2CDmaChGot;
	}

	if (phal_i2c_adapter->rx_dma_dat.ch_sts != I2CDmaChInitialed) {
		pi2c_gdma_rx_adaptor->gdma_isr_type = (TransferType | ErrType);
		pi2c_gdma_rx_adaptor->gdma_ctl.int_en = 1;
		pi2c_gdma_rx_adaptor->gdma_ctl.src_msize   = MsizeEight;
		pi2c_gdma_rx_adaptor->gdma_ctl.src_tr_width = TrWidthOneByte;
		pi2c_gdma_rx_adaptor->gdma_ctl.dest_msize  = MsizeFour;
		pi2c_gdma_rx_adaptor->gdma_ctl.dst_tr_width = TrWidthTwoBytes;
		pi2c_gdma_rx_adaptor->gdma_ctl.dinc        = IncType;
		pi2c_gdma_rx_adaptor->gdma_ctl.sinc        = NoChange;
		pi2c_gdma_rx_adaptor->gdma_ctl.tt_fc       = TTFCPeriToMem;
		//padc_gdma_rx_adaptor->dcache_invalidate_by_addr = __rom_stubs_hal_cache.dcache_invalidate_by_addr;
		//padc_gdma_rx_adaptor->dcache_clean_by_addr = __rom_stubs_hal_cache.dcache_clean_by_addr;

		pi2c_gdma_rx_adaptor->gdma_cfg.src_per    = GDMA_HANDSHAKE_I2C0_RX + phal_i2c_adapter->init_dat.index * 2;
		hal_gdma_handshake_init(pi2c_gdma_rx_adaptor, phal_i2c_adapter->rx_dma_dat.padaptor->gdma_cfg.src_per);
		hal_gdma_chnl_init(pi2c_gdma_rx_adaptor);
		hal_gdma_irq_reg(pi2c_gdma_rx_adaptor,
						 (irq_handler_t)(__rom_stubs_hal_i2c.hal_i2c_dma_irq_handler), (void *)phal_i2c_adapter);
		phal_i2c_adapter->rx_dma_dat.ch_sts = I2CDmaChInitialed;

		/* assign default d-cache handling function */
#if defined(I2C_CACHE_RAM_VERSION)
		phal_i2c_adapter->dcache_invalidate_by_addr = dcache_invalidate_by_addr_ual32;
		phal_i2c_adapter->dcache_clean_invalidate_by_addr = dcache_clean_invalidate_by_addr_ual32;
#else
		phal_i2c_adapter->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;
		phal_i2c_adapter->dcache_clean_invalidate_by_addr = hal_cache_stubs.dcache_clean_invalidate_by_addr;
#endif
	}

	return HAL_OK;
}

/** \brief Description of hal_i2c_recv_dma_deinit
 *
 *    hal_i2c_recv_dma_deinit is to free DMA channel and deinitialize I2C DMA data structure.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_dma_deinit(hal_i2c_adapter_t *phal_i2c_adapter)
{
	if (phal_i2c_adapter->rx_dma_dat.padaptor != NULL) {
		hal_gdma_chnl_free((void *)phal_i2c_adapter->rx_dma_dat.padaptor);
	} else {
		return HAL_ERR_PARA;
	}

	/* remove default d-cache handling function */
	phal_i2c_adapter->dcache_invalidate_by_addr = NULL;
	phal_i2c_adapter->dcache_clean_invalidate_by_addr = NULL;
	phal_i2c_adapter->rx_dma_dat.ch_sts = I2CDmaChNone;
	return HAL_OK;
}

/** \brief Description of hal_i2c_recv_dma
 *
 *    hal_i2c_recv_dma is to execute I2C receive by DMA transfer.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_dma(hal_i2c_adapter_t *phal_i2c_adapter)
{
	i2c_rx_info_t   *pi2c_rx_info = (i2c_rx_info_t *) & (phal_i2c_adapter->rx_dat);
	I2C_TypeDef *pi2c_reg = (I2C_TypeDef *)phal_i2c_adapter->init_dat.reg_base;
	uint32_t ic_dma_cmd_temp;
	volatile uint32_t gdma_idx;
	hal_status_t ret;
	uint8_t multi_block_en = MultiBlkDis;

	if (!(phal_i2c_adapter->mst_spe_func & I2CAddressRetry)) {
		phal_i2c_adapter->rd_cmd_no = pi2c_rx_info->len;
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_TX_ABRT);
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_ACT);
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_INTR);
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_DMA_DONE);
	}

	/* Update data length of DMA mode */
	phal_i2c_adapter->rx_dma_dat.dat_len = pi2c_rx_info->len;

	DBG_I2C_INFO("hal_i2c_recv_dma\n\r");
	DBG_I2C_INFO("Buf: %x, len: %d\n\r", pi2c_rx_info->buf, pi2c_rx_info->len);
	DBG_I2C_INFO("rd cmd no: %d\n\r", phal_i2c_adapter->rd_cmd_no);

	//change to poll mode , if pi2c_rx_info->len < rx_dma_bound
	if (pi2c_rx_info->len < phal_i2c_adapter->pltf_dat.rx_dma_bound) {
		DBG_I2C_WARN("mst recv mode is changed to poll since data is short.\n\r");
		return hal_i2c_recv_poll(phal_i2c_adapter);
	} else if (pi2c_rx_info->len > HP_I2C_DMA_MAX_LEN) {
		DBG_I2C_ERR("hal_i2c_recv_dma: data length is larger than max DMA length of 65535\n\r");
		return HAL_ERR_PARA;
	}

	phal_i2c_adapter->status = I2CStatusRxing;
	phal_i2c_adapter->rx_dma_dat.padaptor->ch_sar = (uint32_t)(&(pi2c_reg->I2C_DAT_CMD));
	phal_i2c_adapter->rx_dma_dat.padaptor->ch_dar = (uint32_t)(pi2c_rx_info->buf);
	phal_i2c_adapter->rx_dma_dat.padaptor->gdma_ctl.block_size = pi2c_rx_info->len >>
			(phal_i2c_adapter->rx_dma_dat.padaptor->gdma_ctl.src_tr_width);
	DBG_I2C_INFO("rx dma block size: %d\n\r", phal_i2c_adapter->rx_dma_dat.padaptor->gdma_ctl.block_size);
	hal_i2c_dma_ctrl(phal_i2c_adapter, I2CDisable);
	pi2c_reg->I2C_DMA_RDLR = phal_i2c_adapter->init_dat.rx_dma_rq_lv;
	pi2c_reg->I2C_DMA_MOD = I2CDmaReg;
	pi2c_reg->I2C_DMA_LEN = phal_i2c_adapter->rd_cmd_no;

	ic_dma_cmd_temp = pi2c_reg->I2C_DMA_CMD;
	HAL_CLEAR_BIT(ic_dma_cmd_temp, I2C_BIT_DMA_STP | I2C_BIT_DMA_RSTRT);
	HAL_SET_BIT(ic_dma_cmd_temp, I2C_BIT_DMA_CMD);

	if (phal_i2c_adapter->mst_spe_func & I2CMasterRestart) {
		HAL_SET_BIT(ic_dma_cmd_temp, I2C_BIT_DMA_RSTRT);    /* Set RESTART for the next byte */
	} else {
		if (pi2c_rx_info->mst_stop == 1) {
			HAL_SET_BIT(ic_dma_cmd_temp, I2C_BIT_DMA_STP);
		}
	}

	pi2c_reg->I2C_DMA_CMD = ic_dma_cmd_temp;
	DBG_I2C_INFO("rx dma cmd: %x\n\r", pi2c_reg->I2C_DMA_CMD);

	if (phal_i2c_adapter->rx_dma_dat.padaptor->gdma_ctl.block_size > MAX_DMA_BLOCK_SIZE) {
		if (phal_i2c_adapter->rx_dma_dat.padaptor->gdma_ctl.block_size <= MAX_DMA_BLOCK_SIZE * 32) {
			multi_block_en = MultiBlkEn;
			DBG_I2C_INFO("dma multi enabled.\n\r");
			// Need to use multiple block DMA
			if (phal_i2c_adapter->rx_dma_dat.padaptor->ch_num < 4) {
				// Current GDMA Channel didn't support multiple block DMA, re-allocate another one
				gdma_idx = phal_i2c_adapter->rx_dma_dat.padaptor->gdma_index;  // backup old GDMA index
				hal_gdma_chnl_free(phal_i2c_adapter->rx_dma_dat.padaptor);
				ret = hal_gdma_chnl_alloc(phal_i2c_adapter->rx_dma_dat.padaptor, MultiBlkEn);

				if (ret != HAL_OK) {
					DBG_I2C_ERR("hal_i2c_recv_dma: re-allocate multiple block DMA channel failed(%d)\r\n\r", ret);
					return ret;
				} else {
					DBG_I2C_INFO("hal_i2c_recv_dma: re-allocated GDMA %u chnl %u\r\n\r", phal_i2c_adapter->rx_dma_dat.padaptor->gdma_index,
								 phal_i2c_adapter->rx_dma_dat.padaptor->ch_num);
					phal_i2c_adapter->rx_dma_dat.padaptor->pgdma_ch_lli = &i2c_rx_gdma_ch_lli[0];
					hal_gdma_chnl_init(phal_i2c_adapter->rx_dma_dat.padaptor);
				}

				// Update GDMA handshake bit and IRQ handler(since may use different GDMA HW)
				if (gdma_idx != phal_i2c_adapter->rx_dma_dat.padaptor->gdma_index) {
					// allocated to different GDMA HW, update the handshake bit
					hal_gdma_handshake_init(phal_i2c_adapter->rx_dma_dat.padaptor, phal_i2c_adapter->rx_dma_dat.padaptor->gdma_cfg.src_per);
				}

				hal_gdma_irq_reg((phal_i2c_adapter->rx_dma_dat.padaptor),
								 (irq_handler_t)(__rom_stubs_hal_i2c.hal_i2c_dma_irq_handler), (void *)phal_i2c_adapter);
			}
		} else {
			DBG_I2C_ERR("hal_i2c_send_dma: TX length too long(%lu), it requires too much DMA blks\r\n\r",
						pi2c_rx_info->len);
			return HAL_ERR_PARA;
		}
	}

	/* deal with d-cache sync. (clean-invalidate) */
	if (is_dcache_enabled()) {
		if (phal_i2c_adapter->dcache_clean_invalidate_by_addr != NULL) {
			phal_i2c_adapter->dcache_clean_invalidate_by_addr((uint32_t *)pi2c_rx_info->buf, (int32_t)pi2c_rx_info->len);
		} else {
			DBG_I2C_ERR("D-Cache is enabled but clean_invalidate function is NOT available before rx GDMA starts.\n\r");
		}
	}

	hal_gdma_transfer_start((void *)phal_i2c_adapter->rx_dma_dat.padaptor, multi_block_en);
	hal_i2c_dma_ctrl(phal_i2c_adapter, I2CEnable);

	pi2c_reg->I2C_INTR_MSK  = (I2C_BIT_M_TX_ABRT | I2C_BIT_M_RX_OVER | I2C_BIT_M_RX_UNDER);
	HAL_SET_BIT(pi2c_reg->I2C_DMA_CR, I2C_BIT_DMA_RDMAE);

	return HAL_OK;
}

/** \brief Description of hal_i2c_receive
 *
 *    hal_i2c_receive is an upper layer I2C receive transfer API. It executes the related receive(RX) API according
 *    to the phal_i2c_adapter->op_mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_receive(hal_i2c_adapter_t *phal_i2c_adapter)
{
	i2c_rx_info_t   *pi2c_rx_info = (i2c_rx_info_t *) & (phal_i2c_adapter->rx_dat);
	hal_status_t retv = HAL_OK;

	if (phal_i2c_adapter->op_mode <= I2CModeDMA) {
		hal_i2c_set_tar(phal_i2c_adapter, 1);

		if (phal_i2c_adapter->mst_spe_func & I2CAddressRetry) {
			retv = hal_i2c_recv_addr_retry(phal_i2c_adapter);

			if (retv != HAL_OK) {
				return (hal_status_t)retv;
			}
		}

		if (pi2c_rx_info->len == 0) {
			phal_i2c_adapter->status = I2CStatusIdle;
			if (phal_i2c_adapter->usr_cb.rxc.cb != NULL) {
				phal_i2c_adapter->usr_cb.rxc.cb((void *)phal_i2c_adapter->usr_cb.rxc.dat);
			}
			return (hal_status_t)retv;
		}

		switch (phal_i2c_adapter->op_mode) {
		case I2CModePoll:
			retv = hal_i2c_recv_poll(phal_i2c_adapter);
			break;
		case I2CModeInterrupt:
			retv = hal_i2c_recv_intr(phal_i2c_adapter);
			break;
		case I2CModeDMA:
			/* only i2c0 supports DMA transfer */
			if (phal_i2c_adapter->init_dat.index >= 2) {
				DBG_I2C_ERR("only i2c0/1 supports DMA\n\r");
				return HAL_ERR_PARA;
			}

			retv = hal_i2c_recv_dma(phal_i2c_adapter);
			break;
		default:
			retv = HAL_ERR_UNKNOWN;
			break;
		}
	} else {
		retv = HAL_ERR_UNKNOWN;
	}

	return (hal_status_t)retv;
}

/** \brief Description of hal_i2c_slv_send_dma
 *
 *    hal_i2c_slv_send_dma is to execute slave send transfer by DMA mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t      received data length in byte.
 */
uint32_t hal_i2c_slv_send_dma(hal_i2c_adapter_t *phal_i2c_adapter)
{
	i2c_tx_info_t   *pi2c_tx_info = (i2c_tx_info_t *) & (phal_i2c_adapter->tx_dat);
	I2C_TypeDef *pi2c_reg = (I2C_TypeDef *)phal_i2c_adapter->init_dat.reg_base;
	uint8_t multi_block_en = MultiBlkDis;
	hal_status_t ret;
	volatile uint32_t gdma_idx;

	DBG_I2C_INFO("hal_i2c_slv_send_dma\n\r");
	DBG_I2C_INFO("Buf: %x, len: %d\n\r", pi2c_tx_info->buf, pi2c_tx_info->len);

	/* Update data length of DMA mode */
	phal_i2c_adapter->tx_dma_dat.dat_len = pi2c_tx_info->len;

	//change to poll mode , if pi2c_tx_info->len < tx_dma_bound
	if (pi2c_tx_info->len < phal_i2c_adapter->pltf_dat.tx_dma_bound) {
		DBG_I2C_WARN("slv send mode is changed to poll since data is short.\n\r");
		return hal_i2c_send_poll(phal_i2c_adapter);
	} else if (pi2c_tx_info->len > HP_I2C_DMA_MAX_LEN) {
		DBG_I2C_ERR("hal_i2c_slv_send_dma: data length is larger than max DMA length of 65535\n\r");
		return HAL_ERR_PARA;
	}

	phal_i2c_adapter->status = I2CStatusTxing;
	phal_i2c_adapter->tx_dma_dat.padaptor->ch_sar = (uint32_t)pi2c_tx_info->buf;
	phal_i2c_adapter->tx_dma_dat.padaptor->ch_dar = (uint32_t) & (pi2c_reg->I2C_DAT_CMD);

	/* modify for non-alignment case */
	if ((pi2c_tx_info->len & 0x03) != 0) {
		phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.src_tr_width = TrWidthOneByte;
		phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.block_size = pi2c_tx_info->len;
	} else {
		phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.block_size = pi2c_tx_info->len >>
				(phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.src_tr_width);
	}

	/* Check if it needs multi-block channel or not */
	if (phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.block_size > MAX_DMA_BLOCK_SIZE) {
		if (phal_i2c_adapter->tx_dma_dat.padaptor->gdma_ctl.block_size <= MAX_DMA_BLOCK_SIZE * 32) {
			multi_block_en = MultiBlkEn;
			// Need to use multiple block DMA
			if (phal_i2c_adapter->tx_dma_dat.padaptor->ch_num < 4) {
				// Current GDMA Channel didn't support multiple block DMA, re-allocate another one
				DBG_I2C_INFO("hal_i2c_send_dma: re-allocate GDMA chnl to support Multi-Blk transfer\r\n\r");
				gdma_idx = phal_i2c_adapter->tx_dma_dat.padaptor->gdma_index;  // backup old GDMA index
				hal_gdma_chnl_free(phal_i2c_adapter->tx_dma_dat.padaptor);
				ret = hal_gdma_chnl_alloc(phal_i2c_adapter->tx_dma_dat.padaptor, MultiBlkEn);

				if (ret != HAL_OK) {
					DBG_I2C_ERR("hal_i2c_send_dma: re-allocate multiple block DMA channel failed(%d)\r\n\r", ret);
					return ret;
				} else {
					DBG_I2C_INFO("hal_i2c_send_dma: re-allocated GDMA %u chnl %u\r\n\r", phal_i2c_adapter->tx_dma_dat.padaptor->gdma_index,
								 phal_i2c_adapter->tx_dma_dat.padaptor->ch_num);
					phal_i2c_adapter->tx_dma_dat.padaptor->pgdma_ch_lli = &i2c_tx_gdma_ch_lli[0];
					hal_gdma_chnl_init(phal_i2c_adapter->tx_dma_dat.padaptor);
				}

				// Update GDMA handshake bit and IRQ handler(since may use different GDMA HW)
				if (gdma_idx != phal_i2c_adapter->tx_dma_dat.padaptor->gdma_index) {
					// allocated to different GDMA HW, update the handshake bit
					hal_gdma_handshake_init(phal_i2c_adapter->tx_dma_dat.padaptor, phal_i2c_adapter->tx_dma_dat.padaptor->gdma_cfg.dest_per);
				}
				hal_gdma_irq_reg((phal_i2c_adapter->tx_dma_dat.padaptor),
								 (irq_handler_t)(__rom_stubs_hal_i2c.hal_i2c_dma_irq_handler), (void *)phal_i2c_adapter);
			}
		} else {
			DBG_I2C_ERR("hal_i2c_send_dma: TX length too long(%lu), it requires too much DMA blks\r\n\r",
						pi2c_tx_info->len);
			return HAL_ERR_PARA;
		}
	}

	pi2c_reg->I2C_DMA_TDLR = phal_i2c_adapter->init_dat.tx_dma_rq_lv;
	pi2c_reg->I2C_DMA_MOD = I2CDmaReg;
	pi2c_reg->I2C_DMA_LEN = pi2c_tx_info->len;
#if defined(TX_ABRT_TEMP_PATCH)
	pi2c_reg->I2C_INTR_MSK  = (I2C_BIT_M_TX_OVER);
#else
	pi2c_reg->I2C_INTR_MSK  = (I2C_BIT_M_TX_ABRT | I2C_BIT_M_TX_OVER);
#endif

	HAL_SET_BIT(pi2c_reg->I2C_DMA_CR, I2C_BIT_DMA_TDMAE);

	//dcache_clean_by_addr ((uint32_t *)pi2c_tx_info->buf, (int32_t)pi2c_tx_info->len);
	/* deal with d-cache sync. (clean) */
	if (is_dcache_enabled()) {
		if (phal_i2c_adapter->dcache_clean_by_addr != NULL) {
			phal_i2c_adapter->dcache_clean_by_addr((uint32_t *)pi2c_tx_info->buf, (int32_t)pi2c_tx_info->len);
		} else {
			DBG_I2C_ERR("D-Cache is enabled but clean function is NOT available before slv tx GDMA starts.\n\r");
		}
	}
	hal_gdma_transfer_start((void *)phal_i2c_adapter->tx_dma_dat.padaptor, multi_block_en);
	return 0;
}

/** \brief Description of hal_i2c_slv_send
 *
 *    hal_i2c_slv_send is to execute slave send upper level API according to phal_i2c_adapter->op_mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_slv_send(hal_i2c_adapter_t *phal_i2c_adapter)
{
	hal_status_t retv = HAL_OK;

	if (hal_i2c_chk_mod(phal_i2c_adapter)) {
		return HAL_ERR_HW;
	}

	phal_i2c_adapter->tx_dma_dat.dat_len = 0;
	switch (phal_i2c_adapter->op_mode) {
	case I2CModePoll:
		retv = hal_i2c_slv_send_poll(phal_i2c_adapter);
		break;
	case I2CModeInterrupt:
		retv = hal_i2c_slv_send_intr(phal_i2c_adapter);
		break;
	case I2CModeDMA:
		/* only i2c0 supports DMA transfer */
		if (phal_i2c_adapter->init_dat.index >= 2) {
			DBG_I2C_ERR("only i2c0/1 supports DMA\n\r");
			return HAL_ERR_PARA;
		}
		retv = hal_i2c_slv_send_dma(phal_i2c_adapter);
		break;
	default:
		retv = HAL_ERR_UNKNOWN;
		break;
	}

	return retv;
}

/** \brief Description of hal_i2c_slv_recv_dma
 *
 *    hal_i2c_slv_recv_dma is to execute slave receive in DMA(non-blocking) mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t
 */
uint32_t hal_i2c_slv_recv_dma(hal_i2c_adapter_t *phal_i2c_adapter)
{
	i2c_rx_info_t   *pi2c_rx_info = (i2c_rx_info_t *) & (phal_i2c_adapter->rx_dat);
	I2C_TypeDef *pi2c_reg = (I2C_TypeDef *)phal_i2c_adapter->init_dat.reg_base;
	volatile uint32_t gdma_idx;
	hal_status_t ret;
	uint8_t multi_block_en = MultiBlkDis;

	DBG_I2C_INFO("hal_i2c_slv_recv_dma\n\r");
	DBG_I2C_INFO("Buf: %x, len: %d\n\r", pi2c_rx_info->buf, pi2c_rx_info->len);

	/* Update data length of DMA mode */
	phal_i2c_adapter->rx_dma_dat.dat_len = pi2c_rx_info->len;

	//change to poll mode , if pi2c_rx_info->len < rx_dma_bound
	if (pi2c_rx_info->len < phal_i2c_adapter->pltf_dat.rx_dma_bound) {
		DBG_I2C_WARN("slv recv mode is changed to poll since data is short.\n\r");
		return hal_i2c_slv_recv_poll(phal_i2c_adapter);
	} else if (pi2c_rx_info->len > HP_I2C_DMA_MAX_LEN) {
		DBG_I2C_ERR("hal_i2c_recv_dma: data length is larger than max DMA length of 65535\n\r");
		return HAL_ERR_PARA;
	}

	phal_i2c_adapter->rx_dma_dat.padaptor->ch_sar = (uint32_t) & (pi2c_reg->I2C_DAT_CMD);
	phal_i2c_adapter->rx_dma_dat.padaptor->ch_dar = (uint32_t)pi2c_rx_info->buf;
	phal_i2c_adapter->rx_dma_dat.padaptor->gdma_ctl.block_size = pi2c_rx_info->len >>
			(phal_i2c_adapter->rx_dma_dat.padaptor->gdma_ctl.src_tr_width);
	phal_i2c_adapter->status = I2CStatusRxing;
	DBG_I2C_INFO("dma block size: %d\n\r", pi2c_rx_info->len);

	pi2c_reg->I2C_DMA_RDLR = phal_i2c_adapter->init_dat.rx_dma_rq_lv;
	pi2c_reg->I2C_DMA_MOD = I2CDmaReg;
	pi2c_reg->I2C_DMA_LEN = pi2c_rx_info->len;

	if (phal_i2c_adapter->rx_dma_dat.padaptor->gdma_ctl.block_size > MAX_DMA_BLOCK_SIZE) {
		if (phal_i2c_adapter->rx_dma_dat.padaptor->gdma_ctl.block_size <= MAX_DMA_BLOCK_SIZE * 32) {
			multi_block_en = MultiBlkEn;
			// Need to use multiple block DMA
			if (phal_i2c_adapter->rx_dma_dat.padaptor->ch_num < 4) {
				// Current GDMA Channel didn't support multiple block DMA, re-allocate another one
				gdma_idx = phal_i2c_adapter->rx_dma_dat.padaptor->gdma_index;  // backup old GDMA index
				hal_gdma_chnl_free(phal_i2c_adapter->rx_dma_dat.padaptor);
				ret = hal_gdma_chnl_alloc(phal_i2c_adapter->rx_dma_dat.padaptor, MultiBlkEn);

				if (ret != HAL_OK) {
					DBG_I2C_ERR("hal_i2c_recv_dma: re-allocate multiple block DMA channel failed(%d)\r\n\r", ret);
					return ret;
				} else {
					DBG_I2C_INFO("hal_i2c_recv_dma: re-allocated GDMA %u chnl %u\r\n\r", phal_i2c_adapter->rx_dma_dat.padaptor->gdma_index,
								 phal_i2c_adapter->rx_dma_dat.padaptor->ch_num);
					phal_i2c_adapter->rx_dma_dat.padaptor->pgdma_ch_lli = &i2c_rx_gdma_ch_lli[0];
					hal_gdma_chnl_init(phal_i2c_adapter->rx_dma_dat.padaptor);
				}

				// Update GDMA handshake bit and IRQ handler(since may use different GDMA HW)
				if (gdma_idx != phal_i2c_adapter->rx_dma_dat.padaptor->gdma_index) {
					// allocated to different GDMA HW, update the handshake bit
					hal_gdma_handshake_init(phal_i2c_adapter->rx_dma_dat.padaptor, phal_i2c_adapter->rx_dma_dat.padaptor->gdma_cfg.src_per);
				}

				hal_gdma_irq_reg((phal_i2c_adapter->rx_dma_dat.padaptor),
								 (irq_handler_t)(__rom_stubs_hal_i2c.hal_i2c_dma_irq_handler), (void *)phal_i2c_adapter);
			}
		} else {
			DBG_I2C_ERR("hal_i2c_send_dma: TX length too long(%lu), it requires too much DMA blks\r\n\r",
						pi2c_rx_info->len);
			return HAL_ERR_PARA;
		}
	}

	/* deal with d-cache sync. (clean-invalidate) */
	if (is_dcache_enabled()) {
		if (phal_i2c_adapter->dcache_clean_invalidate_by_addr != NULL) {
			phal_i2c_adapter->dcache_clean_invalidate_by_addr((uint32_t *)pi2c_rx_info->buf, (int32_t)pi2c_rx_info->len);
		} else {
			DBG_I2C_ERR("D-Cache is enabled but clean_invalidate function is NOT available before slv rx GDMA starts.\n\r");
		}
	}

	hal_gdma_transfer_start((void *)phal_i2c_adapter->rx_dma_dat.padaptor, multi_block_en);

#if defined(TX_ABRT_TEMP_PATCH)
	pi2c_reg->I2C_INTR_MSK  = (I2C_BIT_M_RX_OVER | I2C_BIT_M_RX_UNDER);
#else
	pi2c_reg->I2C_INTR_MSK  = (I2C_BIT_M_TX_ABRT | I2C_BIT_M_RX_OVER | I2C_BIT_M_RX_UNDER);
#endif
	HAL_SET_BIT(pi2c_reg->I2C_DMA_CR, I2C_BIT_DMA_RDMAE);
	return 0;
}

/** \brief Description of hal_i2c_slv_recv
 *
 *    hal_i2c_slv_recv is to execute slave receive upper level API according to phal_i2c_adapter->op_mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_slv_recv(hal_i2c_adapter_t *phal_i2c_adapter)
{
	hal_status_t retv = HAL_OK;

	if (hal_i2c_chk_mod(phal_i2c_adapter)) {
		return HAL_ERR_HW;
	}

	phal_i2c_adapter->rx_dma_dat.dat_len = 0;

	switch (phal_i2c_adapter->op_mode) {
	case I2CModePoll:
		retv = hal_i2c_slv_recv_poll(phal_i2c_adapter);
		break;
	case I2CModeInterrupt:
		retv = hal_i2c_slv_recv_intr(phal_i2c_adapter);
		break;
	case I2CModeDMA:
		/* only i2c0 supports DMA transfer */
		if (phal_i2c_adapter->init_dat.index >= 2) {
			DBG_I2C_ERR("only i2c0/1 supports DMA\n\r");
			return HAL_ERR_PARA;
		}
		retv = hal_i2c_slv_recv_dma(phal_i2c_adapter);
		break;
	default:
		retv = HAL_ERR_UNKNOWN;
		break;
	}

	return retv;
}

#ifdef ARDUINO_SDK
void hal_rtl_i2c_mst_irq_handler_rtl8195bhp_arduino_patch(void *data)
{
	hal_i2c_adapter_t *phal_i2c_adapter = (hal_i2c_adapter_t *)data;
	I2C_TypeDef *pi2c_reg = (I2C_TypeDef *)(phal_i2c_adapter->init_dat.reg_base);
	uint32_t ic_intr_sts_tmp;
	i2c_tx_info_t *pi2c_tx_info = (i2c_tx_info_t *) & (phal_i2c_adapter->tx_dat);
	i2c_rx_info_t *pi2c_rx_info = (i2c_rx_info_t *) & (phal_i2c_adapter->rx_dat);
	uint8_t  wr_ctrl = 0;
	uint32_t tx_abrt_src;

	ic_intr_sts_tmp = pi2c_reg->I2C_INTR_STAT;

	DBG_I2C_INFO("mst irq\n\r");
	DBG_I2C_INFO("intr sts: %x\n\r", ic_intr_sts_tmp);
	if (ic_intr_sts_tmp & I2C_BIT_INTR_RX_UNDER) {
		DBG_I2C_ERR("rx under\n\r");
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_RX_UNDER);
		phal_i2c_adapter->status = I2CStatusError;
		phal_i2c_adapter->err_type = I2CErrorRxUnder;
		if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
			phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
		}
	}

	if (ic_intr_sts_tmp & I2C_BIT_INTR_RX_OVER) {
		DBG_I2C_ERR("rx over\n\r");
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_RX_OVER);
		phal_i2c_adapter->status = I2CStatusError;
		phal_i2c_adapter->err_type = I2CErrorRxOver;
		if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
			phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
		}
	}

	if (ic_intr_sts_tmp & I2C_BIT_INTR_RX_FULL) {
		if ((phal_i2c_adapter->status == I2CStatusRxReady) || (phal_i2c_adapter->status == I2CStatusRxing)) {
			while ((pi2c_reg->I2C_STS & (I2C_BIT_STS_RFNE | I2C_BIT_STS_RFF)) && (pi2c_rx_info->len > 0)) {
				phal_i2c_adapter->status = I2CStatusRxing;
				*(pi2c_rx_info->buf) = pi2c_reg->I2C_DAT_CMD;
				pi2c_rx_info->buf++;
				pi2c_rx_info->len--;
			}

			if (pi2c_rx_info->len == 0) {
				pi2c_reg->I2C_INTR_MSK &= (uint32_t)(~(I2C_BIT_M_TX_ABRT | I2C_BIT_M_TX_EMPTY | I2C_BIT_M_RX_FULL | I2C_BIT_M_RX_OVER
													   | I2C_BIT_M_RX_UNDER));
				if (phal_i2c_adapter->usr_cb.rxc.cb != NULL) {
					phal_i2c_adapter->usr_cb.rxc.cb((void *)phal_i2c_adapter->usr_cb.rxc.dat);
				}

				phal_i2c_adapter->status = I2CStatusIdle;
			}
		} else {
			if (phal_i2c_adapter->usr_cb.rx_full.cb != NULL) {
				phal_i2c_adapter->usr_cb.rx_full.cb((void *)phal_i2c_adapter->usr_cb.rx_full.dat);
			}
		}
	}

	if (ic_intr_sts_tmp & I2C_BIT_INTR_TX_OVER) {
		DBG_I2C_ERR("tx over\n\r");
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_TX_OVER);
		phal_i2c_adapter->status = I2CStatusError;
		phal_i2c_adapter->err_type = I2CErrorTxOver;
		if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
			phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
		}
	}

	if (ic_intr_sts_tmp & I2C_BIT_INTR_TX_EMPTY) {
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_INTR);
		if ((phal_i2c_adapter->status == I2CStatusTxReady) || (phal_i2c_adapter->status == I2CStatusTxing)) {
			//READ_CLEAR_I2C_REG(pi2c_reg, clr_intr);
			if (pi2c_tx_info->len == 0) {
				pi2c_reg->I2C_INTR_MSK &= (uint32_t)(~(I2C_BIT_M_TX_ABRT | I2C_BIT_M_TX_EMPTY | I2C_BIT_M_TX_OVER));
				if (phal_i2c_adapter->usr_cb.txc.cb != NULL) {
					phal_i2c_adapter->usr_cb.txc.cb((void *)phal_i2c_adapter->usr_cb.txc.dat);
				}
				phal_i2c_adapter->status = I2CStatusIdle;
			} else {
				//while ((pi2c_tx_info->len) && (BIT_GET_IC_TFNF(pi2c_reg->status))) {
				while ((pi2c_tx_info->len) && (pi2c_reg->I2C_STS & I2C_BIT_STS_TFNF)) {
					phal_i2c_adapter->status = I2CStatusTxing;
					/* Wrtie data into I2C TX FIFO */
					wr_ctrl = 0;
					if (pi2c_tx_info->len == 1) {
						if (phal_i2c_adapter->mst_spe_func & I2CMasterRestart) {
							wr_ctrl = 2;    /* Set RESTART for the next byte */
						} else {
							if (pi2c_tx_info->mst_stop == 1) {
								wr_ctrl = 1;    /* Set STOP for the last byte */
							}
						}
					}

					hal_i2c_wr(phal_i2c_adapter, pi2c_tx_info->buf, 1, wr_ctrl);
					pi2c_tx_info->buf++;
					pi2c_tx_info->len--;
				}
			}
		} else if ((phal_i2c_adapter->status == I2CStatusRxReady) || (phal_i2c_adapter->status == I2CStatusRxing)) {
			//READ_CLEAR_I2C_REG(pi2c_reg, clr_intr);
			if (phal_i2c_adapter->rd_cmd_no > 0) {
				/* Wrtie cmd into I2C TX FIFO */
				wr_ctrl = 0;
				if (phal_i2c_adapter->rd_cmd_no == 1) {
					if (phal_i2c_adapter->mst_spe_func & I2CMasterRestart) {
						wr_ctrl = 2;    /* Set RESTART for the next byte */
					} else {
						if (pi2c_rx_info->mst_stop == 1) {
							wr_ctrl = 1;    /* Set STOP for the last byte */
						}
					}
					DBG_I2C_INFO("rx, wr_ctrl: %x\n\r", wr_ctrl);
				}


				hal_i2c_mst_send_rdcmd(phal_i2c_adapter, 1, wr_ctrl);
				phal_i2c_adapter->rd_cmd_no--;
			} else if (phal_i2c_adapter->op_mode == I2CModeDMA) {
				HAL_CLEAR_BIT(pi2c_reg->I2C_INTR_MSK, I2C_BIT_M_TX_EMPTY);
			}
		} else {
			if (phal_i2c_adapter->usr_cb.tx_empty.cb != NULL) {
				phal_i2c_adapter->usr_cb.tx_empty.cb((void *)phal_i2c_adapter->usr_cb.tx_empty.dat);
			}
		}


	}

	//if (ic_intr_sts_tmp.b.rd_req) {
	//
	//}

	if (ic_intr_sts_tmp & I2C_BIT_INTR_TX_ABRT) {
		tx_abrt_src = pi2c_reg->I2C_TX_ABRT_SRC;
#ifndef ARDUINO_SDK
		DBG_I2C_ERR("tx abrt src:%08x\n\r", tx_abrt_src);
#endif
		
		if ((phal_i2c_adapter->status == I2CStatusTxReady) || (phal_i2c_adapter->status == I2CStatusTxing)) {
			switch (phal_i2c_adapter->op_mode) {
			case I2CModePoll:
				break;
			case I2CModeInterrupt:
#ifndef ARDUINO_SDK
				DBG_I2C_ERR("terminate tx op. after error\n\r");
				DBG_I2C_ERR("residual len: %d\n\r", phal_i2c_adapter->tx_dat.len);
				DBG_I2C_ERR("last dat: %x\n\r", *(phal_i2c_adapter->tx_dat.buf - 1));
#endif
				pi2c_reg->I2C_INTR_MSK  &= (uint32_t)(~(I2C_BIT_M_TX_ABRT | I2C_BIT_M_TX_EMPTY | I2C_BIT_M_TX_OVER));
				break;
			case I2CModeDMA:
				DBG_I2C_ERR("terminate dma op. after error\n\r");
				DBG_I2C_ERR("dma len:%08x\n\r", pi2c_reg->I2C_DMA_LEN);
				HAL_CLEAR_BIT(pi2c_reg->I2C_DMA_CR, I2C_BIT_DMA_TDMAE);
				hal_gdma_clean_chnl_isr((void *)(phal_i2c_adapter->tx_dma_dat.padaptor));
				hal_gdma_chnl_dis((void *)(phal_i2c_adapter->tx_dma_dat.padaptor));

				pi2c_reg->I2C_INTR_MSK  &= (uint32_t)(~(I2C_BIT_M_TX_ABRT | I2C_BIT_M_TX_OVER));
				phal_i2c_adapter->tx_dma_dat.ch_sts = I2CDmaChGot;
				pi2c_tx_info->buf += pi2c_tx_info->len;
				break;
			default:
				break;
			}
		}

		if ((phal_i2c_adapter->status == I2CStatusRxReady) || (phal_i2c_adapter->status == I2CStatusRxing)) {
			switch (phal_i2c_adapter->op_mode) {
			case I2CModePoll:
				break;
			case I2CModeInterrupt:
				DBG_I2C_ERR("terminate rx op. after error\n\r");
				DBG_I2C_ERR("not received len: %d\n\r", phal_i2c_adapter->rx_dat.len);
				DBG_I2C_ERR("last dat: %x\n\r", *(phal_i2c_adapter->rx_dat.buf - 1));
				pi2c_reg->I2C_INTR_MSK  &= (uint32_t)(~(I2C_BIT_M_TX_ABRT | I2C_BIT_M_TX_EMPTY | I2C_BIT_M_RX_FULL | I2C_BIT_M_RX_OVER |
														I2C_BIT_M_RX_UNDER));
				break;
			case I2CModeDMA:
				DBG_I2C_ERR("terminate dma op. after error\n\r");

				HAL_CLEAR_BIT(pi2c_reg->I2C_DMA_CR, I2C_BIT_DMA_RDMAE);
				hal_gdma_clean_chnl_isr((void *)(phal_i2c_adapter->rx_dma_dat.padaptor));
				hal_gdma_chnl_dis((void *)(phal_i2c_adapter->rx_dma_dat.padaptor));

				pi2c_reg->I2C_INTR_MSK  &= (uint32_t)(~(I2C_BIT_M_TX_ABRT | I2C_BIT_M_RX_OVER | I2C_BIT_M_RX_UNDER));
				phal_i2c_adapter->rx_dma_dat.ch_sts = I2CDmaChGot;
				/* modify read command length, since dma_len register records the dma len */
				phal_i2c_adapter->rd_cmd_no -= pi2c_reg->I2C_DMA_LEN;
				pi2c_rx_info->buf += pi2c_rx_info->len;
				break;
			default:
				break;
			}
		}

		phal_i2c_adapter->status = I2CStatusError;

		phal_i2c_adapter->err_type = I2CErrorTxAbort;
		if (phal_i2c_adapter->usr_cb.err.cb != NULL) {
			phal_i2c_adapter->usr_cb.err.cb((void *)phal_i2c_adapter->usr_cb.err.dat);
		}

		phal_i2c_adapter->status = I2CStatusIdle;
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_TX_ABRT);
		DBG_I2C_INFO("sts:%x\n\r", pi2c_reg->I2C_STS);
		DBG_I2C_INFO("raw:%x\n\r", pi2c_reg->I2C_RAW_INTR_STAT);
	}

	//if (ic_intr_sts_tmp.b.rx_done) {
	//
	//}

	if (ic_intr_sts_tmp & I2C_BIT_INTR_ACT) {
		DBG_I2C_INFO("\n\ractivity\n\r");
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_ACT);
	}

	if (ic_intr_sts_tmp & I2C_BIT_INTR_STRT_DET) {
		DBG_I2C_INFO("\n\rstart det\n\r");
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_STRT_DET);
	}

	if (ic_intr_sts_tmp & I2C_BIT_INTR_STP_DET) {
		DBG_I2C_INFO("\n\rstop det\n\r");
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_STP_DET);
	}

	if (ic_intr_sts_tmp & I2C_BIT_INTR_DMA_I2C_DONE) {
		DBG_I2C_INFO("\n\rdma done\n\r");
		READ_CLEAR_I2C_REG(pi2c_reg, I2C_CLR_DMA_DONE);
	}
//if (ic_intr_sts_tmp.b.gen_call) {
//
//}
}
#endif

/** @} */ /* End of group hs_hal_i2c */
#endif
