/**************************************************************************//**
 * @file     hal_adc.c
 * @brief    This file implements the ADC HAL functions.
 *
 * @version  V1.00
 * @date     2017-01-18
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

#include "cmsis.h"
#include "hal_adc.h"
#include "hal_gdma.h"
#include "hal_pinmux.h"
#include "hal_cache.h"
//#include "hal_timer.h" // commented out unless hal_delay_us/hal_delay_ms is used here
#include "hal_gpio.h" // weide added to support use of hal_gpio_pull_ctrl() function

#include "hal_irq.h"

#include "rtl8735b_syson_type.h"
#include "rtl8735b_syson_s_type.h"

#include "hal_sys_ctrl.h"

#if defined(CONFIG_BUILD_NONSECURE)
#include "hal_sys_ctrl_nsc.h"
#endif

// Removed - Coverity reports that limits.h does not provide needed symbols.
/* #if defined ( __GNUC__ )
#include <limits.h>
#else
#include "__limits.h"
#endif */

#ifdef CONFIG_ADC_EN // weide changed 

uint8_t hp_adc_ch_pin_en_sts;

#if   defined ( __CC_ARM )                                            /* ARM Compiler 4/5 */
extern hal_adc_func_stubs_t Image$$_STUB_ADC$$Base;     // symbol from linker script
#define __rom_stubs_hal_adc Image$$_STUB_ADC$$Base
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)       /* ARM Compiler 6 */
extern hal_adc_func_stubs_t Image$$_STUB_ADC$$Base;     // symbol from linker script
#define __rom_stubs_hal_adc Image$$_STUB_ADC$$Base
#elif defined ( __GNUC__ )
extern hal_adc_func_stubs_t __rom_stubs_hal_adc;     // symbol from linker script
#elif defined ( __ICCARM__ )
extern hal_adc_func_stubs_t __rom_stubs_hal_adc;     // symbol from linker script
#endif

//volatile uint8_t lp_adc_ch_pin_en_sts  = 0;
extern const hal_adc_func_stubs_t hal_adc_stubs;

/** \brief Description of hal_adc_reg_irq
 *
 *    hal_adc_reg_irq is used to register a irq handler

 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \param[in] irq_handler_t handler:                IRQ handler function.
 *   \return void
 */
void hal_adc_reg_irq(hal_adc_adapter_t *phal_adc_adapter, irq_handler_t handler)
{
	hal_adc_stubs.hal_adc_reg_irq(phal_adc_adapter, handler);
}

/** \brief Description of hal_adc_unreg_irq
 *
 *    hal_adc_unreg_irq is used to unregister a irq handler

 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return void
 */
void hal_adc_unreg_irq(hal_adc_adapter_t *phal_adc_adapter)
{
	hal_adc_stubs.hal_adc_unreg_irq(phal_adc_adapter);
}


/**
 * @addtogroup hs_hal_adc ADC
 * @{
 */

/*** Current implementation ONLY in RAM (if ADC were to be fit into ROM in future) ***/

/** \brief Description of hal_adc_vref_control_setting
 *
 *    hal_adc_vref_control_setting is used to configure ADC system registers that controls Vref,
 *    the reference voltage level. A higher Vref will help prevent ADC from clipping at higher
 *    input voltages, e.g. 3.2V - 3.3V (so it can produce meaningful results).
 *
 *    The struct member ref_lvl in init_dat will be updated too.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return hal_status_t:        hal_status_t.
 */

hal_status_t hal_adc_vref_control_setting(hal_adc_adapter_t *phal_adc_adapter, uint8_t set_value)
{

	adc_init_dat_t *padc_init_dat = (adc_init_dat_t *) & (phal_adc_adapter->init_dat);

	switch (set_value) {
	case ADC_VREF_CTRL_0p75_V:
		hal_sys_adc_vref_setting(VREF_SEL_0p75_V);
		// Update vref_sel_lvl in init.dat struct
		padc_init_dat->vref_sel_lvl = 0;
		DBG_ADC_INFO("vref_sel_lvl: %d\r\n", padc_init_dat->vref_sel_lvl);
		break;
	case ADC_VREF_CTRL_0p8_V:
		hal_sys_adc_vref_setting(VREF_SEL_0p8_V);
		// Update vref_sel_lvl in init.dat struct
		padc_init_dat->vref_sel_lvl = 1;
		DBG_ADC_INFO("vref_sel_lvl: %d\r\n", padc_init_dat->vref_sel_lvl);
		break;
	case ADC_VREF_CTRL_0p85_V:
		hal_sys_adc_vref_setting(VREF_SEL_0p85_V);
		// Update vref_sel_lvl in init.dat struct
		padc_init_dat->vref_sel_lvl = 2;
		DBG_ADC_INFO("vref_sel_lvl: %d\r\n", padc_init_dat->vref_sel_lvl);
		break;
	case ADC_VREF_CTRL_0p9_V:
		hal_sys_adc_vref_setting(VREF_SEL_0p9_V);
		// Update vref_sel_lvl in init.dat struct
		padc_init_dat->vref_sel_lvl = 3;
		DBG_ADC_INFO("vref_sel_lvl: %d\r\n", padc_init_dat->vref_sel_lvl);
		break;
	default:
		DBG_ADC_ERR("[ERROR] Invalid ADC VREF setting! - %d\r\n", set_value);
		DBG_ADC_ERR("ADC VREF is UNCHANGED; vref_sel_lvl: %d\r\n", padc_init_dat->vref_sel_lvl);
	}

	return HAL_OK;
}

/**
 * @addtogroup hs_hal_adc ADC
 * @{
 */

/** \brief Description of hal_adc_pin_init
 *
 *    hal_adc_pin_init is used for adc pinmux initialization and register.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_adc_pin_init(hal_adc_adapter_t *phal_adc_adapter)
{
	uint8_t adc_ch_cnt;
	hal_status_t retv;

	for (adc_ch_cnt = 0; adc_ch_cnt < HP_ADC_CH_NO; adc_ch_cnt++) { // weide modified
		if (phal_adc_adapter->plft_dat.pin_en.w & ((uint32_t)0x01 << adc_ch_cnt)) {
			if ((hp_adc_ch_pin_en_sts & ((uint32_t)0x01 << adc_ch_cnt)) == 0) {

				if (adc_ch_cnt < 4) { // first 4 pins - pure ADC
					retv = hal_pinmux_register((hal_adc_stubs.hal_adc_pin_list[adc_ch_cnt]).pin_name, (PID_ADC0 + adc_ch_cnt));

				} else { // last 4 pins - share with comparator

					// GPIO A0 and GPIO A1 pins are default SWD pins with 3.3V pull-up.
					// To use GPIO A0/A1 pins as ADC pins, we need to remove the pin pull-ups and switch pinmux to ADC
					if ((hal_adc_stubs.hal_adc_pin_list[adc_ch_cnt]).pin_name == PIN_A0) {
						hal_pinmux_unregister(PIN_A0, PID_JTAG); // Unregister GPIO_A0 as JTAG/SWD pin
						hal_gpio_pull_ctrl(PIN_A0, 0); // Set GPIO_A0 to High-Z
						DBG_ADC_INFO("GPIO_A0: Unregister JTAG/SWD pinmux, set pull_ctrl = High-Z\r\n");
					}

					if ((hal_adc_stubs.hal_adc_pin_list[adc_ch_cnt]).pin_name == PIN_A1) {
						hal_pinmux_unregister(PIN_A1, PID_JTAG); // Unregister GPIO_A1 as JTAG/SWD pin
						hal_gpio_pull_ctrl(PIN_A1, 0); // Set GPIO_A1 to High-Z
						DBG_ADC_INFO("GPIO_A1: Unregister JTAG/SWD pinmux, set pull_ctrl = High-Z\r\n");
					}

					retv = hal_pinmux_register((hal_adc_stubs.hal_adc_pin_list[adc_ch_cnt]).pin_name, FUNC_COMP_ADC);
				}

				if (retv != HAL_OK) {
					DBG_ADC_ERR("retv post pwr down: %d\r\n", retv);
					return retv;
				}

				hp_adc_ch_pin_en_sts |= ((uint32_t)0x01 << adc_ch_cnt);
			} else {
				DBG_ADC_WARN("ch-%d pin has been enabled.\r\n", adc_ch_cnt);
				DBG_ADC_WARN("adc pin sts: %x\r\n", hp_adc_ch_pin_en_sts);
			}
		}
	}

	return HAL_OK;
}

/** \brief Description of hal_adc_pin_deinit
 *
 *    hal_adc_pin_deinit is used for adc pinmux un-initialization and un-register.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:       Pointer to ADC control adapter.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_adc_pin_deinit(hal_adc_adapter_t *phal_adc_adapter)
{
	uint8_t adc_ch_cnt;
	hal_status_t retv = HAL_OK;

	for (adc_ch_cnt = 0; adc_ch_cnt < HP_ADC_CH_NO; adc_ch_cnt++) {
		if (phal_adc_adapter->plft_dat.pin_en.w & ((uint32_t)0x01 << adc_ch_cnt)) {
			if ((hp_adc_ch_pin_en_sts & ((uint32_t)0x01 << adc_ch_cnt)) != 0) {
				if (adc_ch_cnt < 4) { // first 4 pins - pure ADC
					retv = hal_pinmux_unregister((hal_adc_stubs.hal_adc_pin_list[adc_ch_cnt]).pin_name, (PID_ADC0 + adc_ch_cnt));
				} else { // last 4 pins - share with comparator
					retv = hal_pinmux_unregister((hal_adc_stubs.hal_adc_pin_list[adc_ch_cnt]).pin_name, FUNC_COMP_ADC);

					// Restore GPIO A0 and GPIO A1 pins as SWD pins as they have been switched to be ADC pins during hal_adc_pin_init()
					if ((hal_adc_stubs.hal_adc_pin_list[adc_ch_cnt]).pin_name == PIN_A0) {
						hal_gpio_pull_ctrl(PIN_A0, Pin_PullUp); // Set GPIO_A0 to Pull-Up
						hal_pinmux_register(PIN_A0, PID_JTAG); // Register GPIO_A0 as JTAG/SWD pin
						DBG_ADC_INFO("GPIO_A0: Restore JTAG/SWD pinmux, set pull_ctrl = Pull-Up\r\n");
					}

					if ((hal_adc_stubs.hal_adc_pin_list[adc_ch_cnt]).pin_name == PIN_A1) {
						hal_gpio_pull_ctrl(PIN_A1, Pin_PullUp); // Set GPIO_A1 to Pull-Up
						hal_pinmux_register(PIN_A1, PID_JTAG); // Register GPIO_A1 as JTAG/SWD pin
						DBG_ADC_INFO("GPIO_A1: Restore JTAG/SWD pinmux, set pull_ctrl = Pull-Up\r\n");
					}
				}

				if (retv != HAL_OK) {
					return retv;
				}

				hp_adc_ch_pin_en_sts &= ~((uint32_t)0x01 << adc_ch_cnt);

			} else {
				DBG_ADC_WARN("ch-%d pin is NOT disabled.", adc_ch_cnt);
				DBG_ADC_WARN("since comparator is NOT disabled.");
				DBG_ADC_WARN("adc pin sts: %x\n", hp_adc_ch_pin_en_sts);
			}
		}
	}

	return HAL_OK;
}

/** \brief Description of hal_adc_reinit
 *
 *    hal_adc_reinit is used for adc RE-initialization, thus it excludes pinmux registration and pin power controls.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \return void        Void.
 */
void hal_adc_reinit(hal_adc_adapter_t *phal_adc_adapter)
{

	DBG_ADC_INFO("hal_adc_reinit\r\n");

	*(hal_adc_stubs.phal_adc_irq_adpt) = phal_adc_adapter;

	hal_adc_reg_irq(phal_adc_adapter, (irq_handler_t) hal_adc_stubs.hal_adc_irq_handler);
	hal_irq_set_priority(ADC_IRQn, ADC_IRQPri);

	/* read calibration params */
	if (phal_adc_adapter->use_cali != 0) {
		DBG_ADC_INFO("read cali param\r\n");
		hal_adc_read_cali_param((uint16_t)HP_ADC_GAIN_DENO_ADDR, (uint8_t *)(&(hal_adc_stubs.hal_adc_cali_para->gain_deno)),
								sizeof(hal_adc_stubs.hal_adc_cali_para->gain_deno));
		DBG_ADC_INFO("gain deno: %x\r\n", hal_adc_stubs.hal_adc_cali_para->gain_deno);
		if ((uint16_t)hal_adc_stubs.hal_adc_cali_para->gain_deno == 0xFFFF) {
			DBG_ADC_ERR("Read gain deno failed\r\n");
			DBG_ADC_ERR("Not to use calibration.\r\n");
			phal_adc_adapter->use_cali = 0;
		}
		hal_adc_read_cali_param((uint16_t)HP_ADC_GAIN_MOLE_ADDR, (uint8_t *)(&(hal_adc_stubs.hal_adc_cali_para->gain_mole)),
								sizeof(hal_adc_stubs.hal_adc_cali_para->gain_mole));
		DBG_ADC_INFO("gain mole: %x\r\n", hal_adc_stubs.hal_adc_cali_para->gain_mole);
		if ((uint16_t)hal_adc_stubs.hal_adc_cali_para->gain_mole == 0xFFFF) {
			DBG_ADC_ERR("Read gain mole failed\r\n");
			DBG_ADC_ERR("Not to use calibration.\r\n");
			phal_adc_adapter->use_cali = 0;
		}

		hal_adc_read_cali_param((uint16_t)HP_ADC_OFFSET_DENO_ADDR, (uint8_t *)(&(hal_adc_stubs.hal_adc_cali_para->offset_deno)),
								sizeof(hal_adc_stubs.hal_adc_cali_para->offset_deno));
		DBG_ADC_INFO("offset deno: %x\r\n", hal_adc_stubs.hal_adc_cali_para->offset_deno);
		if ((uint16_t)hal_adc_stubs.hal_adc_cali_para->offset_deno == 0xFFFF) {
			DBG_ADC_ERR("Read offset deno failed\r\n");
			DBG_ADC_ERR("Not to use calibration.\r\n");
			phal_adc_adapter->use_cali = 0;
		}
		hal_adc_read_cali_param((uint32_t)HP_ADC_OFFSET_MOLE_ADDR, (uint8_t *)(&(hal_adc_stubs.hal_adc_cali_para->offset_mole)),
								sizeof(hal_adc_stubs.hal_adc_cali_para->offset_mole));
		DBG_ADC_INFO("offset mole: %x\r\n", hal_adc_stubs.hal_adc_cali_para->offset_mole);
		if ((uint32_t)hal_adc_stubs.hal_adc_cali_para->offset_mole == 0xFFFFFFFF) {
			DBG_ADC_ERR("Read offset mole failed\r\n");
			DBG_ADC_ERR("Not to use calibration.\r\n");
			phal_adc_adapter->use_cali = 0;
		}

		hal_adc_read_cali_param((uint16_t)HP_ADC_INTERNAL_R_ADDR, (uint8_t *)(&(hal_adc_stubs.hal_adc_cali_para->internal_r)),
								sizeof(hal_adc_stubs.hal_adc_cali_para->internal_r));
		DBG_ADC_INFO("ADC internal R mole: %x\n", hal_adc_stubs.hal_adc_cali_para->internal_r);
		if ((uint16_t)hal_adc_stubs.hal_adc_cali_para->internal_r == 0xFFFF) {
			DBG_ADC_ERR("Read ADC internal R failed\r\n");
			DBG_ADC_ERR("Not to use calibration.\r\n");
			phal_adc_adapter->use_cali = 0;
		}
	}

}

/** \brief Description of hal_adc_init
 *
 *    hal_adc_init is used for adc initialization including pinmux control.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_adc_init(hal_adc_adapter_t *phal_adc_adapter)
{
	hal_status_t retv;

	/* Adjust Vref from 0.75V (default) to 0.85V.
	   We can see this as 0.85V is akin to the default value now.*/
	hal_adc_vref_control_setting(phal_adc_adapter, ADC_VREF_CTRL_0p85_V);

	hal_sys_peripheral_en(ADC_SYS, ENABLE);

	/* Pinmux Initialization */
	retv = hal_adc_pin_init(phal_adc_adapter);
	if (retv != HAL_OK) {
		return retv;
	} else {
		return hal_adc_stubs.hal_adc_init(phal_adc_adapter);
	}
}

/** \brief Description of hal_adc_deinit
 *
 *    hal_adc_deinit is used for adc deinitialization including pinmux control.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adapter.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_adc_deinit(hal_adc_adapter_t *phal_adc_adapter)
{
	hal_status_t retv;

	hal_sys_peripheral_en(ADC_SYS, DISABLE);

#if 1 // original code, try temp style for a while
	retv = hal_adc_stubs.hal_adc_deinit(phal_adc_adapter);
	if (retv != HAL_OK) {
		return retv;
	} else {
		retv = hal_adc_pin_deinit(phal_adc_adapter);
		if (retv != HAL_OK) {
			return retv;
		}

	}

	return HAL_OK;
#else

	retv = __rom_stubs_hal_adc.hal_adc_deinit(phal_adc_adapter);
	if (retv != HAL_OK) {
		return retv;
	}

	retv = hal_adc_pin_deinit(phal_adc_adapter);
	if (retv != HAL_OK) {
		return retv;
	}

	return retv;

#endif

}

/** \brief Description of hal_adc_dma_init
 *
 *    hal_adc_dma_init is to initialize DMA module for adc data collection.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] hal_gdma_adaptor_t *padc_gdma_adaptor:            Pointer to GDMA channel control type.
 *
 *   \return hal_status_t:
 */
hal_status_t hal_adc_dma_init(hal_adc_adapter_t *phal_adc_adapter, hal_gdma_adaptor_t *padc_gdma_adaptor)
{
	DBG_ADC_INFO("dma init >>\n");
	if (padc_gdma_adaptor == NULL) {
		return HAL_ERR_PARA;
	}

	phal_adc_adapter->dma_dat.padaptor = padc_gdma_adaptor;
	padc_gdma_adaptor->busy = 0;
	padc_gdma_adaptor->have_chnl = 0;

	/* Allocate DMA channel first */
	if (phal_adc_adapter->dma_dat.ch_sts == ADCDmaChNone) {
		/* alloc a single block channel first */
		if (hal_gdma_chnl_alloc(padc_gdma_adaptor, MultiBlkDis) != HAL_OK) {
			DBG_ADC_ERR("dma channel alloc failed\n");
			return HAL_ERR_HW;
		}
		phal_adc_adapter->dma_dat.ch_sts = ADCDmaChGot;
		phal_adc_adapter->use_dma = ADCEnable;
	}

	if (phal_adc_adapter->dma_dat.ch_sts != ADCDmaChInitialed) {
		padc_gdma_adaptor->gdma_isr_type = (TransferType | ErrType);

		padc_gdma_adaptor->gdma_ctl.int_en = 1;
#ifdef ADC_DMA_PATCH
		padc_gdma_adaptor->gdma_ctl.src_msize   = MsizeOne;
		padc_gdma_adaptor->gdma_ctl.src_tr_width = TrWidthTwoBytes;
		padc_gdma_adaptor->gdma_ctl.dest_msize  = MsizeOne;
		padc_gdma_adaptor->gdma_ctl.dst_tr_width = TrWidthTwoBytes;
#else
		padc_gdma_adaptor->gdma_ctl.src_msize   = MsizeFour;
		padc_gdma_adaptor->gdma_ctl.src_tr_width = TrWidthTwoBytes;
		padc_gdma_adaptor->gdma_ctl.dest_msize  = MsizeFour;
		padc_gdma_adaptor->gdma_ctl.dst_tr_width = TrWidthTwoBytes;
#endif
		padc_gdma_adaptor->gdma_ctl.dinc        = IncType;
		padc_gdma_adaptor->gdma_ctl.sinc        = NoChange;
		padc_gdma_adaptor->gdma_ctl.tt_fc       = TTFCPeriToMem;

		padc_gdma_adaptor->gdma_cfg.src_per    = GDMA_HANDSHAKE_ADC;

		hal_gdma_handshake_init(padc_gdma_adaptor, padc_gdma_adaptor->gdma_cfg.src_per);
		hal_gdma_chnl_init(padc_gdma_adaptor);
		hal_gdma_irq_reg(padc_gdma_adaptor,
						 (irq_handler_t)(hal_adc_stubs.hal_adc_dma_irq_handler), (void *)phal_adc_adapter);
		phal_adc_adapter->dma_dat.ch_sts = ADCDmaChInitialed;

		/* assign default d-cache handling function */
		phal_adc_adapter->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;
		phal_adc_adapter->dcache_clean_invalidate_by_addr = hal_cache_stubs.dcache_clean_invalidate_by_addr;
	}

	DBG_ADC_INFO("dma init <<\n");
	return HAL_OK;
}

/** \brief Description of hal_adc_dma_deinit
 *
 *    hal_adc_dma_deinit is to deinitialize DMA module for adc data collection.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *
 *   \return hal_status_t:
 */
hal_status_t hal_adc_dma_deinit(hal_adc_adapter_t *phal_adc_adapter)
{
	if (phal_adc_adapter->dma_dat.padaptor != NULL) {
		hal_gdma_chnl_free(phal_adc_adapter->dma_dat.padaptor);
	}

	/* remove default d-cache handling function */
	phal_adc_adapter->dcache_invalidate_by_addr = NULL;
	phal_adc_adapter->dcache_clean_invalidate_by_addr = NULL;

	phal_adc_adapter->use_dma = ADCDisable;
	phal_adc_adapter->dma_dat.ch_sts = ADCDmaChNone;
	return HAL_OK;
}

/** \brief Description of hal_adc_read_dma
 *
 *    hal_adc_read_dma is used to read data contiuously by using DMA module.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter
 *   \param[in] uint32_t dat_len:                       ADC conversion data length.
 *   \param[in] uint16_t *dat_buf:                      ADC conversion data pointer.
 *   \param[in] uint8_t trigger_source:                 Inform ADC the trigger source.
 *                                                  1: automatic, 2: timer, 3: comparator,
 *                                                  software trigger is not available when using DMA because
 *                                                  software trigger would occupy CPU resource and application could
 *                                                  not get any performance improvement even using DMA.
 *
 *   \return hal_status_t:
 */
hal_status_t hal_adc_read_dma(hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf,
							  uint8_t trigger_source)
{
	ADC_TypeDef *padc_reg = phal_adc_adapter->init_dat.reg_base;

	volatile uint32_t gdma_idx;
	hal_status_t retv;
	uint8_t adc_dma_multi = 0;

	/* software trigger is not sugguested to use DMA */
	if (trigger_source == ADCSWTrigMod) {
		return HAL_ERR_PARA;
	}

	/* check ADC is in progress or not */
	if (phal_adc_adapter->status != ADCStatusIdle) {
		DBG_ADC_WARN("Hardware in NOT in idle state\n");
		if (phal_adc_adapter->status == ADCStatusCVing) {
			DBG_ADC_WARN("A conversion is in progress\n");
		}

		return HAL_NOT_READY;
	}

	if (dat_len > MAX_DMA_BLOCK_SIZE) {
		if (dat_len <= MAX_DMA_BLOCK_SIZE * MAX_MULTI_BLOCK_NUM) {
			// Need to use multiple block DMA
			if (phal_adc_adapter->dma_dat.padaptor->ch_num < 4) {
				// Current GDMA Channel didn't support multiple block DMA, re-allocate another one
				gdma_idx = phal_adc_adapter->dma_dat.padaptor->gdma_index;  // backup old GDMA index
				hal_gdma_chnl_free(phal_adc_adapter->dma_dat.padaptor);
				retv = hal_gdma_chnl_alloc(phal_adc_adapter->dma_dat.padaptor, MultiBlkEn);
				adc_dma_multi = 1;
				if (retv != HAL_OK) {
					phal_adc_adapter->dma_dat.ch_sts = ADCDmaChNone;
					//phal_adc_adapter->dma_dat.padaptor = NULL;
					DBG_ADC_ERR("hal_uart_dma_recv: Err: re-allocate multiple block DMA channel failed(%d)\r\n", retv);
					return retv;
				} else {
					DBG_ADC_INFO("hal_uart_dma_recv: re-allocate GDMA %u chnl %u\r\n",
								 phal_adc_adapter->dma_dat.padaptor->gdma_index, phal_adc_adapter->dma_dat.padaptor->ch_num);
					hal_gdma_chnl_init(phal_adc_adapter->dma_dat.padaptor);
				}

				// Update GDMA handshake bit and IRQ handler(since may use different GDMA HW)
				if (gdma_idx != phal_adc_adapter->dma_dat.padaptor->gdma_index) {
					// allocated to different GDMA HW, update the handshake bit
					hal_gdma_handshake_init(phal_adc_adapter->dma_dat.padaptor, phal_adc_adapter->dma_dat.padaptor->gdma_cfg.src_per);
					phal_adc_adapter->dma_dat.ch_sts = ADCDmaChInitialed;
				}

				hal_gdma_irq_reg((phal_adc_adapter->dma_dat.padaptor),
								 (irq_handler_t)(hal_adc_stubs.hal_adc_dma_irq_handler), (void *)phal_adc_adapter);
			}

		} else {
			DBG_ADC_ERR("hal_adc_dma: Err: RX Len(%lu) too big\n", dat_len);
			return HAL_ERR_PARA;
		}
	}

	DBG_ADC_INFO("dat_len: %d\n", dat_len);
	phal_adc_adapter->use_dma = ADCEnable;
	phal_adc_adapter->cv_dat_len = dat_len;
	phal_adc_adapter->cv_dat_buf = dat_buf;

	if (phal_adc_adapter->dma_dat.padaptor->gdma_ctl.src_tr_width == TrWidthFourBytes) {
		phal_adc_adapter->cv_dat_len = dat_len * 4;
	} else {
		phal_adc_adapter->cv_dat_len = dat_len * 2;
	}

	phal_adc_adapter->cv_dat_buf = dat_buf;

	phal_adc_adapter->status = ADCStatusCVing;

	phal_adc_adapter->dma_dat.padaptor->ch_sar = (uint32_t) & (padc_reg->ADC_DAT_GLOBAL);
	phal_adc_adapter->dma_dat.padaptor->ch_dar = (uint32_t)phal_adc_adapter->cv_dat_buf;
	phal_adc_adapter->dma_dat.padaptor->gdma_ctl.block_size = dat_len;

	/* deal with d-cache sync. (clean-invalidate) */
	if (is_dcache_enabled()) {
		if (phal_adc_adapter->dcache_clean_invalidate_by_addr != NULL) {
			phal_adc_adapter->dcache_clean_invalidate_by_addr((uint32_t *)phal_adc_adapter->cv_dat_buf, (int32_t)phal_adc_adapter->cv_dat_len);
		} else {
			DBG_ADC_WARN("D-Cache is enabled but clean_invalidate function is NOT available before GDMA starts.\n");
		}
	}

	if (adc_dma_multi) {
		hal_gdma_transfer_start((void *)phal_adc_adapter->dma_dat.padaptor, MultiBlkEn);
	} else {
		hal_gdma_transfer_start((void *)phal_adc_adapter->dma_dat.padaptor, MultiBlkDis);
	}

	hal_adc_reset_list(phal_adc_adapter);
	hal_adc_clear_fifo(phal_adc_adapter);

	padc_reg->ADC_INTR_STS = 0xFFFFFFFF; // clear interrupt status
	padc_reg->ADC_INTR_CTRL |= ADC_BIT_IT_FIFO_OVER_EN | ADC_BIT_IT_ERR_EN;

	padc_reg->ADC_DMA_CON &= ~(ADC_MASK_DMA_CON_LVL);
	padc_reg->ADC_DMA_CON |= (phal_adc_adapter->init_dat.dma_rq_lv) << ADC_SHIFT_DMA_CON_LVL;
	padc_reg->ADC_DMA_CON |= ADC_BIT_DMA_CON_EN;

	padc_reg->ADC_CONF &= ~(ADC_MASK_OP_MOD); // clear any op modes set previously

	if (trigger_source == ADCAutoMod) {
		phal_adc_adapter->init_dat.hw_mode = ADCAutoMod;
		padc_reg->ADC_CONF |= ADCAutoMod << ADC_SHIFT_OP_MOD;
		hal_adc_auto_chsw_ctrl(phal_adc_adapter, ADCEnable);
	} else if (trigger_source == ADCTmTrigMod) {
		phal_adc_adapter->init_dat.hw_mode = ADCTmTrigMod;
		padc_reg->ADC_CONF |= ADCTmTrigMod << ADC_SHIFT_OP_MOD;
	}

	return HAL_OK;
}

/** \brief Description of hal_adc_timeout_chk
 *
 *    hal_adc_timeout_chk is used to check if adc operation is timeout.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:    Pointer to ADC control adapter.
 *   \param[in] uint32_t start_cnt:                     Timer start count.
 *   \return uint8_t:                                   Timeout or not.\n
 *                                                      0: not time-out. 1: time-out.
 */
uint8_t hal_adc_timeout_chk(hal_adc_adapter_t *phal_adc_adapter, uint32_t start_cnt)
{
	return hal_adc_stubs.hal_adc_timeout_chk(phal_adc_adapter, start_cnt);
}

/** \brief Description of hal_adc_sw_cv_trig
 *
 *    hal_adc_sw_cv_trig is used to execute ADC software conversion trigger.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
void hal_adc_sw_cv_trig(hal_adc_adapter_t *phal_adc_adapter)
{
	hal_adc_stubs.hal_adc_sw_cv_trig(phal_adc_adapter);
}

/** \brief Description of hal_adc_pure_init
 *
 *    hal_adc_pure_init is used to initialize ADC module.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:       Pointer to ADC control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_adc_pure_init(hal_adc_adapter_t *phal_adc_adapter)
{
	return hal_adc_stubs.hal_adc_pure_init(phal_adc_adapter);
}

/** \brief Description of hal_adc_pure_deinit
 *
 *    hal_adc_pure_deinit is used to initialize ADC module.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:       Pointer to ADC control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_adc_pure_deinit(hal_adc_adapter_t *phal_adc_adapter)
{
	return hal_adc_stubs.hal_adc_pure_deinit(phal_adc_adapter);
}

/** \brief Description of hal_adc_set_in_type
 *
 *    hal_adc_set_in_type is used to set ADC channel input type.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \param[in] uint8_t input_type:                 Input type.
 *   \return hal_status_t:          return HAL_OK when the given parameters is correct.
 *                                  Only ch0~ch5 are capable of two input type (single-end and differential)
 */
hal_status_t hal_adc_set_in_type(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t input_type)
{
	return hal_adc_stubs.hal_adc_set_in_type(phal_adc_adapter, ch_no, input_type);
}

/** \brief Description of hal_adc_get_in_type
 *
 *    hal_adc_get_in_type is used to set ADC channel input type.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                              ADC channel number.
 *   \return uint8_t:                               channel input type.\n
 *                                                  0: single end, 1: differential.
 */
uint8_t hal_adc_get_in_type(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
	return hal_adc_stubs.hal_adc_get_in_type(phal_adc_adapter, ch_no);
}

/** \brief Description of hal_adc_set_comp_thld
 *
 *    hal_adc_set_comp_thld is used to set ADC channel comparison threshold.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \param[in] uint16_t thld_high:                 Comparison high threshold.
 *   \param[in] uint16_t thld_low:                  Comparison low threshold.
 *   \return hal_status_t
 */
hal_status_t hal_adc_set_comp_thld(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint16_t thld_high, uint16_t thld_low)
{
	return hal_adc_stubs.hal_adc_set_comp_thld(phal_adc_adapter, ch_no, thld_high, thld_low);
}

/** \brief Description of hal_adc_set_comp_rule
 *
 *    hal_adc_set_comp_rule is used to set ADC channel comparison control. When this is set to a particular
 *    criterion, the related comparison status and interrupt would be triggered.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \param[in] uint8_t comp_rule:                  Comparison rule.
 *   \return hal_status_t
 */
hal_status_t hal_adc_set_comp_rule(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t comp_rule)
{
	return hal_adc_stubs.hal_adc_set_comp_rule(phal_adc_adapter, ch_no, comp_rule);
}

/** \brief Description of hal_adc_clear_comp_intr_sts
 *
 *    hal_adc_clear_comp_intr_sts is used to clear adc comparison interrupt status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \return void
 */
void hal_adc_clear_comp_intr_sts(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
	hal_adc_stubs.hal_adc_clear_comp_intr_sts(phal_adc_adapter, ch_no);
}

/** \brief Description of hal_adc_comp_intr_ctrl
 *
 *    hal_adc_comp_intr_ctrl is used to set ADC channel comparison control. When this is set to a particular
 *    criterion, the related comparison status and interrupt would be triggered.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t intr_option:                Interrupt option (source).\n
 *                                              0: cvlist end.          1: cv end.\n
 *                                              2: channel cv end.      3: fifo full.\n
 *                                              4: fifo over.           5: fifo empty.\n
 *                                              6: dat ovw.             7: err.
 *
 *   \param[in] uint8_t intr_enable:                Interrupt enable control.
 *   \return void
 */
void hal_adc_intr_ctrl(hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option, uint8_t intr_enable)
{
	hal_adc_stubs.hal_adc_intr_ctrl(phal_adc_adapter, intr_option, intr_enable);
}

/** \brief Description of hal_adc_clear_intr_sts
 *
 *    hal_adc_clear_intr_sts is used to clear adc interrupt interrupt status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t intr_option:                Interrupt option (source).\n
 *                                              0: cvlist end.          1: cv end.\n
 *                                              2: channel cv end.      3: fifo full.\n
 *                                              4: fifo over.           5: fifo empty.\n
 *                                              6: dat ovw.             7: err.
 *   \return void
 */
void hal_adc_clear_intr_sts(hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option)
{
	hal_adc_stubs.hal_adc_clear_intr_sts(phal_adc_adapter, intr_option);
}

/** \brief Description of hal_adc_set_cvlist
 *
 *    hal_adc_set_cvlist is used to set ADC channel conversion list.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t *cvlist:                    Pointer to a channel conversion list. It should be an array start address.
 *   \param[in] uint8_t cvlist_len:                 Conversion list length.
 *   \return hal_status_t
 */
hal_status_t hal_adc_set_cvlist(hal_adc_adapter_t *phal_adc_adapter, uint8_t *cvlist, uint8_t cvlist_len)
{
	return hal_adc_stubs.hal_adc_set_cvlist(phal_adc_adapter, cvlist, cvlist_len);
}

/** \brief Description of hal_adc_item_to_ch
 *
 *    hal_adc_item_to_ch is used to transfer a list item to channel number.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t item_no:                    Item number in the hardware list register.
 *   \return uint8_t:                           Channel number of the list item.
 */
uint8_t hal_adc_item_to_ch(hal_adc_adapter_t *phal_adc_adapter, uint8_t item_no)
{
	return hal_adc_stubs.hal_adc_item_to_ch(phal_adc_adapter, item_no);
}

/** \brief Description of hal_adc_load_default
 *
 *    hal_adc_load_default is used to load default value for data structure.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return void
 */
void hal_adc_load_default(hal_adc_adapter_t *phal_adc_adapter)
{
	hal_adc_stubs.hal_adc_load_default(phal_adc_adapter);
}


/** \brief Description of hal_adc_single_read
 *
 *    hal_adc_single_read is used for single for particular channel. \n
 *    This function would automatically execute software trigger flow and return the channel data.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adaptor.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \return uint16_t:            ADC sample data.
 */
uint16_t hal_adc_single_read(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
	uint32_t reg_tmp;
	uint32_t count = 0;
	reg_tmp = hal_adc_stubs.hal_adc_single_read(phal_adc_adapter, ch_no);
	while (reg_tmp == 0xFFFF) {
		reg_tmp = hal_adc_stubs.hal_adc_single_read(phal_adc_adapter, ch_no);
		//hal_delay_ms(5);
		count++;
		if (count > 200) {
			DBG_ADC_WARN("Count is: %d\r\n", count); // weide
			break;
		}
	}
	return reg_tmp;
}

/** \brief Description of hal_adc_clear_fifo
 *
 *    hal_adc_clear_fifo is used to clear FIFO to the default state.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
void hal_adc_clear_fifo(hal_adc_adapter_t *phal_adc_adapter)
{
	hal_adc_stubs.hal_adc_clear_fifo(phal_adc_adapter);
}

/** \brief Description of hal_adc_read_ch_dat
 *
 *    hal_adc_read_ch_dat is used to read the channel data directly without any trigger operation.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                          Channel number.
 *   \return uint16_t:                              channel conversion data.\n
 *                                                  If the data is NOT ready or overwritten, a value of 0xFFFF would\n
 *                                                  be returned.
 */

uint16_t hal_adc_read_ch_dat(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t out_raw)
{
	return hal_adc_stubs.hal_adc_read_ch_dat(phal_adc_adapter, ch_no, out_raw);
}

/** \brief Description of hal_adc_read_continuous
 *
 *    hal_adc_read_continuous is used to read the channel data continuously according to cvlist and different
 *                                          trigger source.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter
 *   \param[in] uint32_t dat_len:                       ADC conversion data length.
 *   \param[in] uint16_t *dat_buf:                      ADC conversion data pointer.
 *   \param[in] uint8_t trigger_source:                 Inform ADC the trigger source.
 *                                                  0: software, 1: automatic, 2: timer
 *   \return hal_status_t.
 */
hal_status_t hal_adc_read_continuous(hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf,
									 uint8_t trigger_source)
{
	return hal_adc_stubs.hal_adc_read_continuous(phal_adc_adapter, dat_len, dat_buf, trigger_source);
}

/** \brief Description of hal_adc_cal_gain_deno_rtl8735b
 *
 *    hal_adc_cal_gain_deno_rtl8735b is used to calculate the denominator part of adc gain.
 *
 *   \param[in] int16_t real code 0
 *   \param[in] int16_t real code 1
 *   \return int16_t
 */
int16_t hal_adc_calc_gain_deno(int16_t real_co_0, int16_t real_co_1)
{
	return (int16_t)hal_adc_stubs.hal_adc_calc_gain_deno(real_co_0, real_co_1);
}

/** \brief Description of hal_adc_cal_gain_mole
 *
 *    hal_adc_cal_gain_mole_rtl8735b is used to calculate the molecular part (numerator) of adc gain.
 *
 *   \param[in] int16_t ideal code 0
 *   \param[in] int16_t ideal code 1
 *   \return int16_t
 */
int16_t hal_adc_calc_gain_mole(int16_t ideal_co_0, int16_t ideal_co_1)

{
	return (int16_t)hal_adc_stubs.hal_adc_calc_gain_mole(ideal_co_0, ideal_co_1);
}

/** \brief Description of hal_adc_cal_offet_deno
 *
 *    hal_adc_cal_offet_deno_rtl8735b is used to calculate denominator part of adc offset.
 *
 *   \param[in] int16_t real code 0
 *   \param[in] int16_t real code 1
 *   \return int16_t
 */
int16_t hal_adc_calc_offset_deno(int16_t real_co_0, int16_t real_co_1)
{
	return (int16_t)hal_adc_stubs.hal_adc_calc_offset_deno(real_co_0, real_co_1);
}

/** \brief Description of hal_adc_cal_offset_mole
 *
 *    hal_adc_cal_offset_mole_rtl8735b is used to calculate molecular part (numerator) of adc offset.
 *
 *   \param[in] int16_t ideal code 0
 *   \param[in] int16_t ideal code 1
 *   \param[in] int16_t real code 0
 *   \param[in] int16_t real code 1

 *   \return int32_t
 */
int32_t hal_adc_calc_offset_mole(int16_t ideal_co_0, int16_t ideal_co_1, int16_t real_co_0, int16_t real_co_1)
{
	return (int32_t)hal_adc_stubs.hal_adc_calc_offset_mole(ideal_co_0, ideal_co_1, real_co_0, real_co_1);
}

/** \brief Description of hal_adc_calc_cali_val
 *
 *    hal_adc_calc_cali_val_rtl8735b is used to calculate calibration value
 *
 *   \param[in] uint16_t adc real value
 *   \param[in] hal_adc_cali_para_t *phal_adc_cali_para
 *   \return int32_t
 */
uint32_t hal_adc_calc_cali_val(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para)
{
	return (uint32_t)hal_adc_stubs.hal_adc_calc_cali_val(adc_read_val, phal_adc_cali_para);
}

/** \brief Description of hal_adc_read_cali_param
 *
 *    hal_adc_read_cali_param_rtl8735b is used to read calibration parameters.
 *
 *   \param[in] uint16_t parameters address
 *   \param[in] uint8_t *return data address
 *   \param[in] uint8_t parameter length
 *   \return void
 */
void hal_adc_read_cali_param(uint16_t addr, uint8_t *param_addr, uint8_t param_len)
{
	hal_adc_stubs.hal_adc_read_cali_param(addr, param_addr, param_len);
}

/** \brief Description of hal_adc_write_cali_param
 *
 *    hal_adc_write_cali_param_rtl8735b is used to write calibration parameters.
 *
 *   \param[in] uint16_t parameters address
 *   \param[in] uint8_t *data address
 *   \param[in] uint8_t parameter length
 *   \return void
 */
void hal_adc_write_cali_param(uint16_t addr, uint8_t *param_addr, uint8_t param_len)
{
	hal_adc_stubs.hal_adc_write_cali_param(addr, param_addr, param_len);
}
/** @} */ /* End of group hs_hal_adc */

#endif

