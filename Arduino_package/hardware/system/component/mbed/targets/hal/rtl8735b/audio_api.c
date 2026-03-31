/**************************************************************************//**
 * @file     audio_api.c
 * @brief    This file implements the AUDIO Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-03
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
#include "objects.h"
#include "audio_api.h"
#include "hal_audio.h"

static audio_t *audio_obj;
void audio_init(audio_t *obj, audio_output_mode output_mode, audio_input_mode input_mode, audio_power_sel power_sel)
{
	if (obj->audio_initialized == 0) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_init(paudio_adapter, power_sel);
		hal_audio_sport_init(paudio_adapter);

		hal_audio_output_power(paudio_adapter, output_mode);
		hal_audio_input_power(paudio_adapter, input_mode);

		hal_audio_adc_l_dvol(paudio_adapter, DVOL_ADC_0DB);
		hal_audio_adc_r_dvol(paudio_adapter, DVOL_ADC_0DB);
		hal_audio_adc_l_dmute(paudio_adapter, DISABLE);
		obj->adc_l_dmute_en = DISABLE;
		hal_audio_adc_r_dmute(paudio_adapter, DISABLE);
		obj->adc_r_dmute_en = DISABLE;

		hal_audio_dac_dither(paudio_adapter, AUDIO_DITHER_DISABLE);
		hal_audio_dac_l_dvol(paudio_adapter, DVOL_DAC_0DB);
		hal_audio_dac_l_dmute(paudio_adapter, DISABLE);
		obj->dac_l_dmute_en = DISABLE;
		hal_audio_dac_l_zdet(paudio_adapter, AUDIO_DETE_AND_INC_DEC_CHAN, AUDIO_DAC_16384_SAMPLES);
		hal_audio_sidetone_mixer(paudio_adapter, ENABLE);

		hal_audio_format(paudio_adapter, AUDIO_FORMAT_I2S);
		hal_audio_sck_inv(paudio_adapter, DISABLE);
		hal_audio_loopback(paudio_adapter, DISABLE); //DISABLE, ENABLE
		hal_audio_tx_ch(paudio_adapter, AUDIO_L_R);
		if (input_mode == RIGHT_DMIC) {
			hal_audio_rx_ch(paudio_adapter, AUDIO_R_L);
		} else {
			hal_audio_rx_ch(paudio_adapter, AUDIO_L_R);
		}

		hal_audio_digital_rst(paudio_adapter, DISABLE);
		obj->audio_initialized = 1;
		audio_obj = obj;
	}

}

void audio_deinit(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		u32 temp_tx, temp_rx;

		temp_tx = hal_audio_sport_get_tx_dma_start_sta(paudio_adapter);
		temp_rx = hal_audio_sport_get_rx_dma_start_sta(paudio_adapter);

		if (temp_tx == 0x01) {
			hal_audio_sport_tx_dma_start(paudio_adapter, DISABLE);
		}

		if (temp_rx == 0x01) {
			hal_audio_sport_rx_dma_start(paudio_adapter, DISABLE);
		}

		audio_clean_error_cnt(obj);
		hal_audio_output_power(paudio_adapter, AUDIO_OUTPUT_DISABLE);
		hal_audio_input_power(paudio_adapter, AUDIO_INPUT_DISABLE);
		hal_audio_digital_rst(paudio_adapter, ENABLE);
		hal_audio_deinit(paudio_adapter);

		hal_audio_sport_deinit(paudio_adapter);
		obj->audio_initialized = 0;
		audio_obj = NULL;
	}
}

void audio_dac_clk(audio_t *obj, BOOL dac_clk_en)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		hal_audio_dac_clk(paudio_adapter, dac_clk_en);
	}
}

void audio_adc_clk(audio_t *obj, BOOL adc_l_clk_en, BOOL adc_r_clk_en)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		hal_audio_adc_clk(paudio_adapter, adc_l_clk_en, adc_r_clk_en);
	}
}

void audio_set_param(audio_t *obj, audio_sr sample_rate, audio_wl word_length)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_rate(paudio_adapter, sample_rate, sample_rate);
		hal_audio_length(paudio_adapter, word_length, word_length);
		hal_audio_sport_tx_params(paudio_adapter, AUDIO_MONO, word_length, sample_rate); // AUDIO_STEREO,AUDIO_MONO
		hal_audio_sport_rx_params(paudio_adapter, AUDIO_MONO, word_length, sample_rate); // AUDIO_STEREO,AUDIO_MONO

		if (word_length == WL_24BIT) {
			hal_audio_sport_tx_byte_swap(paudio_adapter, 1);
			hal_audio_sport_rx_byte_swap(paudio_adapter, 1);
		} else {
			hal_audio_sport_tx_byte_swap(paudio_adapter, 0);
			hal_audio_sport_rx_byte_swap(paudio_adapter, 0);
		}
	}
}

void audio_set_dma_buffer(audio_t *obj, u8 *tx_buf, u8 *rx_buf, u32 page_size, audio_page_num page_num)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		hal_audio_dma_params_t dma_params;

		dma_params.page_num = page_num;
		dma_params.page_size = page_size;
		dma_params.tx_buf = tx_buf;
		dma_params.rx_buf = rx_buf;
		hal_audio_sport_buf(paudio_adapter, dma_params);
	}
}

void audio_tx_irq_handler(audio_t *obj, audio_irq_handler tx_handler, u32 *arg)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_sport_tx_cb_handler(paudio_adapter, (audio_sport_irq_cb_t)tx_handler, arg);
	}
}

void audio_rx_irq_handler(audio_t *obj, audio_irq_handler rx_handler, u32 *arg)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_sport_rx_cb_handler(paudio_adapter, (audio_sport_irq_cb_t)rx_handler, arg);
	}
}

void audio_err_irq_handler(audio_t *obj, audio_irq_handler err_handler, u32 *arg)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &(obj->audio_adapter);
		hal_sport_adapter_t *psport_adapter = &(paudio_adapter->sport_adapter);

		hal_sport_dma_err_cb_handler(psport_adapter, (audio_sport_irq_cb_t)err_handler, arg);
	}
}

u8 *audio_get_tx_page_adr(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		return (u8 *)hal_audio_sport_get_tx_page(paudio_adapter);
	} else {
		return NULL;
	}
}

void audio_set_tx_page(audio_t *obj, u8 *pbuf)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_sport_tx_page_send(paudio_adapter, (u32 *)pbuf);
	}
}

void audio_set_rx_page(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_sport_rx_page_recv(paudio_adapter);
	}
}

void audio_tx_start(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		audio_clean_error_cnt(obj);
		hal_audio_sport_tx_dma_start(paudio_adapter, ENABLE);
	}
}

void audio_rx_start(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		audio_clean_error_cnt(obj);
		hal_audio_sport_rx_dma_start(paudio_adapter, ENABLE);
	}
}

void audio_trx_start(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		audio_clean_error_cnt(obj);
		hal_audio_sport_rx_dma_start(paudio_adapter, ENABLE);
		hal_audio_sport_tx_dma_start(paudio_adapter, ENABLE);
	}
}

void audio_tx_stop(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_sport_tx_dma_start(paudio_adapter, DISABLE);
	}
}

void audio_rx_stop(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_sport_rx_dma_start(paudio_adapter, DISABLE);
	}
}

void audio_trx_stop(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		audio_clean_error_cnt(obj);
		hal_audio_sport_tx_dma_start(paudio_adapter, DISABLE);
		hal_audio_sport_rx_dma_start(paudio_adapter, DISABLE);
	}
}

u8 audio_get_tx_error_cnt(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		return (paudio_adapter->sport_adapter.dma_err_sta & 0x01);
	} else {
		return 0;
	}
}

u8 audio_get_rx_error_cnt(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		return ((paudio_adapter->sport_adapter.dma_err_sta & 0x04) >> 2);
	} else {
		return 0;
	}
}

void audio_clean_error_cnt(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		paudio_adapter->sport_adapter.dma_err_sta = paudio_adapter->sport_adapter.dma_err_sta & ~(0x05);
	}
}

void audio_sport_loopback(audio_t *obj, BOOL en)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_rtl_sport_set_loopback(&paudio_adapter->sport_adapter, en);
	}
}

void audio_mic_analog_mute(audio_t *obj, BOOL en)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_mic_mute(paudio_adapter, en);
	}
}

void audio_line_in_analog_mute(audio_t *obj, BOOL en)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_line_in_mute(paudio_adapter, en);
	}
}

void audio_mic_analog_gain(audio_t *obj, BOOL en, audio_mic_gain mic_gain)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_mic_boost(paudio_adapter, en, mic_gain);
	}
}

void audio_hpo_amplifier(audio_t *obj, BOOL en)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_hpo_amplifier(paudio_adapter, en);
	}
}

void audio_adc_digital_vol(audio_t *obj, u8 step)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		if (step > 0x7F) {
			DBG_AUDIO_ERR(" The adc step exceeds the maximum value 0x7F. \r\n");
		} else {
			hal_audio_adc_l_dvol(paudio_adapter, step);
			hal_audio_adc_r_dvol(paudio_adapter, step);
		}
	}
}

void audio_adc_digital_mute(audio_t *obj, BOOL mute_en)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_adc_l_dmute(paudio_adapter, mute_en);
		obj->adc_l_dmute_en = mute_en;
		hal_audio_adc_r_dmute(paudio_adapter, mute_en);
		obj->adc_r_dmute_en = mute_en;
	}
}

void audio_headphone_analog_mute(audio_t *obj, BOOL en)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_hpo_mute(paudio_adapter, en);
	}
}

void audio_dac_digital_vol(audio_t *obj, u8 step)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		if (step > DVOL_DAC_0DB) {
			DBG_AUDIO_ERR(" The dac step exceeds the maximum value 0xAF. \r\n");
		} else {
			hal_audio_dac_l_dvol(paudio_adapter, step);
		}
	}
}

void audio_dac_digital_mute(audio_t *obj, BOOL mute_en)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_dac_l_dmute(paudio_adapter, mute_en);
		obj->dac_l_dmute_en = mute_en;
	}
}

void audio_vref_voltage_ctrl(audio_t *obj, audio_vref_voltage voltage)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_vref(paudio_adapter, ENABLE, voltage);
	}
}

void audio_sidetone_init(audio_t *obj)
{
#if 0
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_sidetone_mixer(paudio_adapter, DISABLE, DISABLE);
		hal_audio_sidetone_source(paudio_adapter, AUDIO_ST_ADC_L);
		hal_audio_sidetone_clk(paudio_adapter, ENABLE);
	}
#endif
}

void audio_sidetone_deinit(audio_t *obj)
{
#if 0
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_sidetone_mixer(paudio_adapter, ENABLE, ENABLE);
		hal_audio_sidetone_clk(paudio_adapter, DISABLE);
	}
#endif
}

void audio_sidetone_vol(audio_t *obj, audio_sidetone_boost_t sidetone_boost, u8 step)
{
#if 0
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		if (step > SIDETONE_0DB) {
			DBG_AUDIO_ERR(" The sidetone step exceeds the maximum value 0x1F. \r\n");
		} else {
			hal_audio_sidetone_vol(paudio_adapter, step, sidetone_boost);
		}
	}
#endif
}

void audio_sidetone_hpf_ctrl(audio_t *obj, BOOL en, audio_sidetone_hpf sidetone_hpf)
{
#if 0
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_sidetone_hpf(paudio_adapter, en, sidetone_hpf);
	}
#endif
}

void audio_mic_bias_ctrl(audio_t *obj, BOOL en, audio_bias_voltage voltage)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_mic_bias(paudio_adapter, en, voltage);
	}
}

void audio_adda_loopback(audio_t *obj, BOOL en)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_adda_loopback(paudio_adapter, en);
	}
}

static uint32_t dmic_data_set;
static uint32_t dmic_clk_set;
void audio_dmic_pinmux(audio_t *obj, PinName dmic_clk, PinName dmic_data)
{
	HAL_Status ret;
	u8 pin_mux_err = 0;

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	uint32_t dmic_s0[3] = {PE_4, PE_0, PE_2};
#else
	uint32_t dmic_s0[3] = {PD_18, PD_14, PD_16};
#endif

	if (dmic_data == dmic_s0[0]) {
		ret = hal_pinmux_register(dmic_s0[0], PID_DMIC);
		if (ret != HAL_OK) {
			DBG_AUDIO_ERR("audio_dmic_pinmux : dmic data pin is conflict. \r\n");
			pin_mux_err |= 1;
		} else {
			dmic_data_set = dmic_s0[0];
		}
	} else {
		DBG_AUDIO_ERR("audio_dmic_pinmux : dmic data pin is invalid. \r\n");
		pin_mux_err |= 1;
	}

	if (dmic_clk == dmic_s0[1]) {
		ret = hal_pinmux_register(dmic_s0[1], PID_DMIC);
		if (ret != HAL_OK) {
			DBG_AUDIO_ERR("audio_dmic_pinmux : dmic clk pin is conflict. \r\n");
			pin_mux_err |= 1;
		} else {
			dmic_clk_set = dmic_s0[1];
		}
	} else if (dmic_clk == dmic_s0[2]) {
		ret = hal_pinmux_register(dmic_s0[2], PID_DMIC);
		if (ret != HAL_OK) {
			DBG_AUDIO_ERR("audio_dmic_pinmux : dmic clk pin is conflict. \r\n");
			pin_mux_err |= 1;
		} else {
			dmic_clk_set = dmic_s0[2];
		}
	} else {
		DBG_AUDIO_ERR("audio_dmic_pinmux : dmic data pin is invalid. \r\n");
		pin_mux_err |= 1;
	}

	if (pin_mux_err == 1) {
		DBG_AUDIO_ERR("audio_dmic_pinmux : DMIC pins is invalid. \r\n");
	}

}

void audio_dmic_depinmux(audio_t *obj, PinName dmic_clk, PinName dmic_data)
{
	HAL_Status ret;
	u8 pin_mux_err = 0;

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	uint32_t dmic_s0[3] = {PE_4, PE_0, PE_2};
#else
	uint32_t dmic_s0[3] = {PD_18, PD_14, PD_16};
#endif
	if (dmic_data == dmic_s0[0]) {
		ret = hal_pinmux_unregister(dmic_s0[0], PID_DMIC);
		if (ret != HAL_OK) {
			DBG_AUDIO_ERR("audio_dmic_pinmux : dmic data pin is conflict. \r\n");
			pin_mux_err |= 1;
		} else {
			dmic_data_set = 0;
		}
	} else {
		DBG_AUDIO_ERR("audio_dmic_pinmux : dmic data pin is invalid. \r\n");
		pin_mux_err |= 1;
	}

	if (dmic_clk == dmic_s0[1]) {
		ret = hal_pinmux_unregister(dmic_s0[1], PID_DMIC);
		if (ret != HAL_OK) {
			DBG_AUDIO_ERR("audio_dmic_pinmux : dmic clk pin is conflict. \r\n");
			pin_mux_err |= 1;
		} else {
			dmic_clk = 0;
		}
	} else if (dmic_clk == dmic_s0[2]) {
		ret = hal_pinmux_unregister(dmic_s0[2], PID_DMIC);
		if (ret != HAL_OK) {
			DBG_AUDIO_ERR("audio_dmic_pinmux : dmic clk pin is conflict. \r\n");
			pin_mux_err |= 1;
		} else {
			dmic_clk = 0;
		}
	} else {
		DBG_AUDIO_ERR("audio_dmic_pinmux : dmic data pin is invalid. \r\n");
		pin_mux_err |= 1;
	}

	if (pin_mux_err == 1) {
		DBG_AUDIO_ERR("audio_dmic_pinmux : DMIC pins is invalid. \r\n");
	}

}

static void audio_dmic_poweroffcheck(void)
{
	HAL_Status ret;
	u8 pin_mux_err = 0;

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	uint32_t dmic_s0[3] = {PE_4, PE_0, PE_2};
#else
	uint32_t dmic_s0[3] = {PD_18, PD_14, PD_16};
#endif
	if (dmic_data_set != 0) {
		if (dmic_data_set == dmic_s0[0]) {
			ret = hal_pinmux_unregister(dmic_s0[0], PID_DMIC);
			if (ret != HAL_OK) {
				DBG_AUDIO_ERR("audio_dmic_pinmux : dmic data pin is conflict. \r\n");
				pin_mux_err |= 1;
			} else {
				dmic_data_set = 0;
			}
		} else {
			DBG_AUDIO_ERR("audio_dmic_pinmux : dmic data pin is invalid. \r\n");
			pin_mux_err |= 1;
		}
	}

	if (dmic_clk_set != 0) {
		if (dmic_clk_set == dmic_s0[1]) {
			ret = hal_pinmux_unregister(dmic_s0[1], PID_DMIC);
			if (ret != HAL_OK) {
				DBG_AUDIO_ERR("audio_dmic_pinmux : dmic clk pin is conflict. \r\n");
				pin_mux_err |= 1;
			} else {
				dmic_clk_set = 0;
			}
		} else if (dmic_clk_set == dmic_s0[2]) {
			ret = hal_pinmux_unregister(dmic_s0[2], PID_DMIC);
			if (ret != HAL_OK) {
				DBG_AUDIO_ERR("audio_dmic_pinmux : dmic clk pin is conflict. \r\n");
				pin_mux_err |= 1;
			} else {
				dmic_clk_set = 0;
			}
		} else {
			DBG_AUDIO_ERR("audio_dmic_pinmux : dmic data pin is invalid. \r\n");
			pin_mux_err |= 1;
		}
	}

	if (pin_mux_err == 1) {
		DBG_AUDIO_ERR("audio_dmic_pinmux : DMIC pins is invalid. \r\n");
	}

}

void audio_l_dmic_gain(audio_t *obj, audio_dmic_gain dmic_gain)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_dmic_l_gain(paudio_adapter, dmic_gain);
	}
}

void audio_r_dmic_gain(audio_t *obj, audio_dmic_gain dmic_gain)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_dmic_r_gain(paudio_adapter, dmic_gain);
	}
}

void audio_set_diff_tx_rx_param(audio_t *obj, audio_diff_para_t *pdiff_para)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_sport_diff_rate_init(paudio_adapter, pdiff_para->diff_en);
		hal_audio_rate(paudio_adapter, pdiff_para->tx_sr, pdiff_para->rx_sr);
		hal_audio_length(paudio_adapter, pdiff_para->tx_wl, pdiff_para->rx_wl);
		hal_audio_sport_tx_params(paudio_adapter, pdiff_para->tx_ch, pdiff_para->tx_wl, pdiff_para->tx_sr);
		hal_audio_sport_rx_params(paudio_adapter, pdiff_para->rx_ch, pdiff_para->rx_wl, pdiff_para->rx_sr);

		if (pdiff_para->tx_wl == WL_24BIT) {
			hal_audio_sport_tx_byte_swap(paudio_adapter, 1);
		} else {
			hal_audio_sport_tx_byte_swap(paudio_adapter, 0);
		}

		if (pdiff_para->rx_wl == WL_24BIT) {
			hal_audio_sport_rx_byte_swap(paudio_adapter, 1);
		} else {
			hal_audio_sport_rx_byte_swap(paudio_adapter, 0);
		}
	}
}

void audio_adc_l_hpf(audio_t *obj, BOOL en, audio_hpf_fc hpf_fc)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		hal_audio_adc_l_hpf(paudio_adapter, en, hpf_fc);
	}
}

void audio_adc_r_hpf(audio_t *obj, BOOL en, audio_hpf_fc hpf_fc)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		hal_audio_adc_r_hpf(paudio_adapter, en, hpf_fc);
	}
}

void audio_input_l_eq(audio_t *obj, audio_eq eq, BOOL en, u32 h0, u32 b1, u32 b2, u32 a1, u32 a2)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		hal_eq_params_t eq_params;

		eq_params.h0 = h0;
		eq_params.b1 = b1;
		eq_params.b2 = b2;
		eq_params.a1 = a1;
		eq_params.a2 = a2;

		hal_audio_input_l_eq(paudio_adapter, eq, en, &eq_params);
	}
}

void audio_input_r_eq(audio_t *obj, audio_eq eq, BOOL en, u32 h0, u32 b1, u32 b2, u32 a1, u32 a2)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		hal_eq_params_t eq_params;

		eq_params.h0 = h0;
		eq_params.b1 = b1;
		eq_params.b2 = b2;
		eq_params.a1 = a1;
		eq_params.a2 = a2;

		hal_audio_input_r_eq(paudio_adapter, eq, en, &eq_params);
	}
}

void audio_output_l_eq(audio_t *obj, audio_eq eq, BOOL en, u32 h0, u32 b1, u32 b2, u32 a1, u32 a2)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		hal_eq_params_t eq_params;

		eq_params.h0 = h0;
		eq_params.b1 = b1;
		eq_params.b2 = b2;
		eq_params.a1 = a1;
		eq_params.a2 = a2;

		hal_audio_output_l_eq(paudio_adapter, eq, en, &eq_params);
	}
}

void audio_set_param_adv(audio_t *obj, audio_sr sample_rate, audio_wl word_length, audio_ch tx_ch, audio_ch rx_ch)
{
	if (obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

		hal_audio_rate(paudio_adapter, sample_rate, sample_rate);
		hal_audio_length(paudio_adapter, word_length, word_length);
		hal_audio_sport_tx_params(paudio_adapter, tx_ch, word_length, sample_rate); // AUDIO_STEREO,AUDIO_MONO
		hal_audio_sport_rx_params(paudio_adapter, rx_ch, word_length, sample_rate); // AUDIO_STEREO,AUDIO_MONO

		if (word_length == WL_24BIT) {
			hal_audio_sport_tx_byte_swap(paudio_adapter, 1);
			hal_audio_sport_rx_byte_swap(paudio_adapter, 1);
		} else {
			hal_audio_sport_tx_byte_swap(paudio_adapter, 0);
			hal_audio_sport_rx_byte_swap(paudio_adapter, 0);
		}
	}
}

uint32_t audio_get_tx_start_status(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		u32 temp_tx;
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		temp_tx = hal_audio_sport_get_tx_dma_start_sta(paudio_adapter);

		if (temp_tx == 0x01) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

uint32_t audio_get_rx_start_status(audio_t *obj)
{
	if (obj->audio_initialized == 1) {
		u32 temp_rx;
		hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
		temp_rx = hal_audio_sport_get_rx_dma_start_sta(paudio_adapter);

		if (temp_rx == 0x01) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

void audio_poweroff(void)
{
	if (audio_obj && audio_obj->audio_initialized == 1) {
		hal_audio_adapter_t *paudio_adapter = &audio_obj->audio_adapter;
		u32 temp_tx, temp_rx;

		temp_tx = hal_audio_sport_get_tx_dma_start_sta(paudio_adapter);
		temp_rx = hal_audio_sport_get_rx_dma_start_sta(paudio_adapter);

		if (temp_tx == 0x01) {
			hal_audio_sport_tx_dma_start(paudio_adapter, DISABLE);
		}

		if (temp_rx == 0x01) {
			hal_audio_sport_rx_dma_start(paudio_adapter, DISABLE);
		}

		audio_clean_error_cnt(audio_obj);
		hal_audio_output_power(paudio_adapter, AUDIO_OUTPUT_DISABLE);
		hal_audio_input_power(paudio_adapter, AUDIO_INPUT_DISABLE);
		hal_audio_digital_rst(paudio_adapter, ENABLE);
		hal_audio_deinit(paudio_adapter);

		hal_audio_sport_deinit(paudio_adapter);
		audio_obj->audio_initialized = 0;
		audio_obj = NULL;
	}
	audio_dmic_poweroffcheck();
}