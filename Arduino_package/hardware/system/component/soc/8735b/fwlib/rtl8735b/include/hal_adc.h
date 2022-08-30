/**************************************************************************//**
 * @file     hal_adc.h
 * @brief    The HAL API implementation for the ADC device.
 * @version  V1.00
 * @date     2016-12-14
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

#ifndef _HAL_ADC_H_
#define _HAL_ADC_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

extern const hal_adc_func_stubs_t hal_adc_stubs;

enum VREF_FOR_HAL_ADC_CTRL_e {
	ADC_VREF_CTRL_0p75_V	= 0x0,
	ADC_VREF_CTRL_0p8_V		= 0x1,
	ADC_VREF_CTRL_0p85_V	= 0x2,
	ADC_VREF_CTRL_0p9_V		= 0x3,
};

/**
 * @addtogroup hs_hal_adc ADC
 * @ingroup 8195bh_hal
 * @{
 * @brief The ADC HAL module of the LS platform.
 */


__STATIC_INLINE void hal_adc_set_mod(hal_adc_adapter_t *phal_adc_adapter, uint8_t mod)
{
	// Trying to catch not init error
	/*if (phal_adc_adapter == NULL) {
	    DBG_ADC_ERR ("hal_rtl_adc_sw_cv_trig: ADC is not initialized\r\n");
	    dbg_printf ("hal_rtl_adc_sw_cv_trig: ADC is not initialized\r\n");
	    return HAL_NOT_READY;
	} */

	(phal_adc_adapter->init_dat.reg_base)->ADC_CONF &= ~(ADC_MASK_OP_MOD); // Clear operating mode (i.e. set to software trigger (default))
	(phal_adc_adapter->init_dat.reg_base)->ADC_CONF |= (mod << ADC_SHIFT_OP_MOD);
}

/** \brief Description of hal_adc_auto_chsw_ctrl
 *
 *    hal_adc_auto_chsw_ctrl is used to enable/disable auto mode.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t auto_enable:                enable/ disable auto chsw.
 *   \return void
 */
__STATIC_INLINE void hal_adc_auto_chsw_ctrl(hal_adc_adapter_t *phal_adc_adapter, uint8_t auto_enable)
{
	if (auto_enable) {
		(phal_adc_adapter->init_dat.reg_base)->ADC_AUTO_CHSW_CTRL |= ADC_BIT_AUTO_CHSW_EN;
	} else {
		(phal_adc_adapter->init_dat.reg_base)->ADC_AUTO_CHSW_CTRL &= ~(ADC_BIT_AUTO_CHSW_EN);
	}
}

/** \brief Description of hal_adc_get_last_item
 *
 *    hal_adc_get_last_item is used to read the last cvlist item number which\n
 *    the last conversion is executed.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \return uint32_t:            item number in cvlist
 */
__STATIC_INLINE uint32_t hal_adc_get_last_item(hal_adc_adapter_t *phal_adc_adapter)
{
	return (uint32_t)(phal_adc_adapter->init_dat.reg_base)->ADC_LAST_ITEM;
}

/** \brief Description of hal_adc_get_empty_sts
 *
 *    hal_adc_get_empty_sts is used to read adc empty status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint32_t:                              0: not empty; 1: empty
 */
__STATIC_INLINE uint32_t hal_adc_get_empty_sts(hal_adc_adapter_t *phal_adc_adapter)
{
	if (((phal_adc_adapter->init_dat.reg_base)->ADC_STS & (ADC_BIT_STS_EMPTY)) >> ADC_SHIFT_STS_EMPTY) {
		return (uint32_t)1;
	} else {
		return (uint32_t)0;
	}
}

/** \brief Description of hal_adc_get_fifo_no
 *
 *    hal_adc_get_fifo_no is used to read adc fifo entry number.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint32_t:                              fifo entry number
 */
__STATIC_INLINE uint32_t hal_adc_get_fifo_no(hal_adc_adapter_t *phal_adc_adapter)
{
	return (uint32_t)((phal_adc_adapter->init_dat.reg_base)->ADC_FLR);
}

/** \brief Description of hal_adc_set_full_level
 *
 *    hal_adc_set_full_level is used to set adc fifo full level.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint8_t full_lvl:                       Full level.
 *   \return void
 */
__STATIC_INLINE void hal_adc_set_full_level(hal_adc_adapter_t *phal_adc_adapter, uint8_t full_lvl)
{
	if ((full_lvl == 0) || (full_lvl > HP_ADC_FIFO_LEN)) {
		DBG_ADC_ERR("Given full level is larger than HW supported.\r\n");
	}

	(phal_adc_adapter->init_dat.reg_base)->ADC_FULL_LVL = (full_lvl - 1); // assign value to reg straight because only one set of bits is available in the reg
}

/** \brief Description of hal_adc_get_full_level
 *
 *    hal_adc_get_full_level is used to get adc fifo full level.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint8_t:       ADC full level.
 */
__STATIC_INLINE uint8_t hal_adc_get_full_level(hal_adc_adapter_t *phal_adc_adapter)
{
	return (uint8_t)(((phal_adc_adapter->init_dat.reg_base)->ADC_FULL_LVL) + 1);
}

/** \brief Description of hal_adc_set_in_tape_all
 *
 *    hal_adc_set_in_tape_all is used to set channel input type register directly.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint32_t in_type_mask:                  Mask to ADC input type register.
 *   \return void
 */
__STATIC_INLINE void hal_adc_set_in_type_all(hal_adc_adapter_t *phal_adc_adapter, uint32_t in_type_mask)
{
	// Weide: This is a special function; used only in the test code verify_adc.c
	(phal_adc_adapter->init_dat.reg_base)->ADC_IN_TYPE = in_type_mask;
}

/** \brief Description of hal_adc_set_trig_timer
 *
 *    hal_adc_set_trig_timer is used to set timer module number for adc conversion trigger source.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint8_t timer_number:                   Timer number for ADC timer trigger source.
 *   \return void
 */
__STATIC_INLINE void hal_adc_set_trig_timer(hal_adc_adapter_t *phal_adc_adapter, uint8_t timer_number)
{
	phal_adc_adapter->init_dat.trig_timer = timer_number;
	(phal_adc_adapter->init_dat.reg_base)->ADC_TRIG_TIMER_SEL = timer_number;
}

/** \brief Description of hal_adc_set_cv_intr_ch
 *
 *    hal_adc_set_cv_intr_ch is used to set channel number for channel conversion interrrupt.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                          Channel number.
 *   \return void
 */
__STATIC_INLINE void hal_adc_set_cv_intr_ch(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
	(phal_adc_adapter->init_dat.reg_base)->ADC_IT_CHNO_CON = ch_no;
}

/** \brief Description of hal_adc_get_cv_intr_ch
 *
 *    hal_adc_get_cv_intr_ch is used to get channel number for channel conversion interrrupt.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint8_t:                       ADC channel number.
 */
__STATIC_INLINE uint8_t hal_adc_get_cv_intr_ch(hal_adc_adapter_t *phal_adc_adapter)
{
	return (uint8_t)((phal_adc_adapter->init_dat.reg_base)->ADC_IT_CHNO_CON);
}

/** \brief Description of hal_adc_clear_all_intr
 *
 *    hal_adc_clear_all_intr is used to clear all pending interrupt status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
__STATIC_INLINE void hal_adc_clear_all_intr(hal_adc_adapter_t *phal_adc_adapter)
{
	(phal_adc_adapter->init_dat.reg_base)->ADC_INTR_STS |= 0xFFFFFFFF;
}

/** \brief Description of hal_adc_reset_list
 *
 *    hal_adc_reset_list is used to reset cvlist to the default state.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
__STATIC_INLINE void hal_adc_reset_list(hal_adc_adapter_t *phal_adc_adapter)
{
	(phal_adc_adapter->init_dat.reg_base)->ADC_RST_LIST |= ADC_BIT_RST_LIST;
	(phal_adc_adapter->init_dat.reg_base)->ADC_RST_LIST &= ~(ADC_BIT_RST_LIST);
}

uint32_t hal_adc_calc_cali_val(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para); // declare protoype before its use


/** \brief Description of hal_adc_read_fifo
 *
 *    hal_adc_read_fifo is used to read the fifo register(global) without any trigger operations.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint16_t:                              channel conversion data.
 */
__STATIC_INLINE uint16_t hal_adc_read_fifo(hal_adc_adapter_t *phal_adc_adapter, uint8_t out_raw)
{
	return (uint16_t)(hal_adc_stubs.hal_adc_read_fifo(phal_adc_adapter, out_raw));
}

__STATIC_INLINE uint32_t hal_adc_read_fifo_w_sts(hal_adc_adapter_t *phal_adc_adapter)
{
	// Weide unsure - commenting out first

	uint32_t global_data_tmp;
	uint32_t global_data_post_cali;
	global_data_tmp = (phal_adc_adapter->init_dat.reg_base)->ADC_DAT_GLOBAL;

	if (phal_adc_adapter->use_cali) {
		global_data_post_cali = hal_adc_calc_cali_val((uint16_t)(global_data_tmp & ADC_MASK_DAT_GLOBAL_DAT),
								(hal_adc_cali_para_t *) & (hal_adc_stubs.hal_adc_cali_para));
	}

	global_data_tmp |= (global_data_post_cali << ADC_SHIFT_DAT_GLOBAL_DAT);

	return (uint32_t)global_data_tmp;

	/*#endif*/
}

uint8_t hal_adc_timeout_chk(hal_adc_adapter_t *phal_adc_adapter, uint32_t start_cnt);
void hal_adc_sw_cv_trig(hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pure_init(hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pure_deinit(hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_set_in_type(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t input_type);
uint8_t hal_adc_get_in_type(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
hal_status_t hal_adc_set_comp_thld(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint16_t thld_high, uint16_t thld_low);
hal_status_t hal_adc_set_comp_rule(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t comp_rule);
void hal_adc_clear_comp_intr_sts(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
void hal_adc_intr_ctrl(hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option, uint8_t intr_enable);
void hal_adc_clear_intr_sts(hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option);
hal_status_t hal_adc_set_cvlist(hal_adc_adapter_t *phal_adc_adapter, uint8_t *cvlist, uint8_t cvlist_len);
uint8_t hal_adc_item_to_ch(hal_adc_adapter_t *phal_adc_adapter, uint8_t item_no);
void hal_adc_load_default(hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pin_init(hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pin_deinit(hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_init(hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_deinit(hal_adc_adapter_t *phal_adc_adapter);
uint16_t hal_adc_single_read(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
void hal_adc_clear_fifo(hal_adc_adapter_t *phal_adc_adapter);
uint16_t hal_adc_read_ch_dat(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t out_raw);
hal_status_t hal_adc_read_continuous(hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf,
									 uint8_t trigger_source);
hal_status_t hal_adc_dma_init(hal_adc_adapter_t *phal_adc_adapter, hal_gdma_adaptor_t *padc_gdma_adaptor);
hal_status_t hal_adc_dma_deinit(hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_read_dma(hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf, uint8_t trigger_source);

int16_t hal_adc_calc_gain_deno(int16_t real_co_0, int16_t real_co_1);
int16_t hal_adc_calc_gain_mole(int16_t ideal_co_0, int16_t ideal_co_1);
int16_t hal_adc_calc_offset_deno(int16_t real_co_0, int16_t real_co_1);
int32_t hal_adc_calc_offset_mole(int16_t ideal_co_0, int16_t ideal_co_1, int16_t real_co_0, int16_t real_co_1);
//uint32_t hal_adc_calc_cali_val(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para);
void hal_adc_read_cali_param(uint16_t addr, uint8_t *param_addr, uint8_t param_len);
void hal_adc_write_cali_param(uint16_t addr, uint8_t *param_addr, uint8_t param_len);
uint16_t hal_adc_single_read_rtl8195bhp_patch(hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
void hal_adc_reinit(hal_adc_adapter_t *phal_adc_adapter);
/** @} */ /* End of group ls_hal_adc */

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_ADC_H_"
