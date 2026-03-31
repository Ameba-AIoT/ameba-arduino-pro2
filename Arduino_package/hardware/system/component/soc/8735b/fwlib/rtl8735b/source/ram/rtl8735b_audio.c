/**************************************************************************//**
 * @file     rtl8735b_audio.c
 * @brief    This file implements the AUDIO HAL functions in ROM.
 *
 * @version  V1.00
 * @date     2016-07-20
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
#include "rtl8735b_audio.h"
#include "hal_sys_ctrl.h"
#include "hal_sys_ctrl_nsc.h"
#include "hal_timer.h"

#if !defined(CONFIG_BUILD_NONSECURE)

#undef SI_REG_BASE
#define SI_REG_BASE (SI_S_BASE)

#else

#undef SI_REG_BASE
#define SI_REG_BASE (SI_BASE)

#endif


/**
  * @brief The stubs functions table to exports audio HAL functions in ROM.
  */
const hal_audio_func_stubs_t hal_audio_stubs = {
	.hal_audio_init = hal_rtl_audio_init,
	.hal_audio_deinit = hal_rtl_audio_deinit,
	.hal_audio_si_init = hal_rtl_audio_si_init,
	.hal_audio_si_read = hal_rtl_audio_si_read,
	.hal_audio_si_write = hal_rtl_audio_si_write,
	.hal_audio_ldo_tune = hal_rtl_audio_ldo_tune,
	.hal_audio_dev_ctrl = hal_rtl_audio_dev_ctrl,
	.hal_audio_rate = hal_rtl_audio_rate,
	.hal_audio_format = hal_rtl_audio_format,
	.hal_audio_length = hal_rtl_audio_length,
	.hal_audio_sck_inv = hal_rtl_audio_sck_inv,
	.hal_audio_loopback = hal_rtl_audio_loopback,
	.hal_audio_tx_ch = hal_rtl_audio_tx_ch,
	.hal_audio_rx_ch = hal_rtl_audio_rx_ch,
	.hal_audio_digital_rst = hal_rtl_audio_digital_rst,
	.hal_audio_daad_loopback = hal_rtl_audio_daad_loopback,
	.hal_audio_adda_loopback = hal_rtl_audio_adda_loopback,
	.hal_audio_asrc = hal_rtl_audio_asrc,
	.hal_audio_dac_mixer = hal_rtl_audio_dac_mixer,
	.hal_audio_adc_amic_mixer = hal_rtl_audio_adc_amic_mixer,
	.hal_audio_adc_dmic_mixer = hal_rtl_audio_adc_dmic_mixer,
	.hal_audio_sidetone_mixer = hal_rtl_audio_sidetone_mixer,
	.hal_audio_dac_clk = hal_rtl_audio_dac_clk,
	.hal_audio_adc_clk = hal_rtl_audio_adc_clk,
	.hal_audio_dmic_clk = hal_rtl_audio_dmic_clk,
	.hal_audio_dmic_input_clk = hal_rtl_audio_dmic_input_clk,
	.hal_audio_dmic_latch = hal_rtl_audio_dmic_latch,
	.hal_audio_dmic_l_gain = hal_rtl_audio_dmic_l_gain,
	.hal_audio_dmic_r_gain = hal_rtl_audio_dmic_r_gain,
	.hal_audio_dmic_l_src = hal_rtl_audio_dmic_l_src,
	.hal_audio_dmic_r_src = hal_rtl_audio_dmic_r_src,
	.hal_audio_amic_l_src = hal_rtl_audio_amic_l_src,
	.hal_audio_amic_r_src = hal_rtl_audio_amic_r_src,
	.hal_audio_adc_l_hpf = hal_rtl_audio_adc_l_hpf,
	.hal_audio_adc_r_hpf = hal_rtl_audio_adc_r_hpf,
	.hal_audio_adc_l_dvol = hal_rtl_audio_adc_l_dvol,
	.hal_audio_adc_l_dmute = hal_rtl_audio_adc_l_dmute,
	.hal_audio_adc_r_dvol = hal_rtl_audio_adc_r_dvol,
	.hal_audio_adc_r_dmute = hal_rtl_audio_adc_r_dmute,
	.hal_audio_adc_l_zdet = hal_rtl_audio_adc_l_zdet,
	.hal_audio_adc_r_zdet = hal_rtl_audio_adc_r_zdet,
	.hal_audio_adc_l_silence = hal_rtl_audio_adc_l_silence,
	.hal_audio_adc_l_silence_result = hal_rtl_audio_adc_l_silence_result,
	.hal_audio_adc_l_silence_status = hal_rtl_audio_adc_l_silence_status,
	.hal_audio_adc_r_silence = hal_rtl_audio_adc_r_silence,
	.hal_audio_adc_r_silence_result = hal_rtl_audio_adc_r_silence_result,
	.hal_audio_adc_r_silence_status = hal_rtl_audio_adc_r_silence_status,
	.hal_audio_dac_dither = hal_rtl_audio_dac_dither,
	.hal_audio_dac_l_hpf = hal_rtl_audio_dac_l_hpf,
	.hal_audio_dac_l_dvol = hal_rtl_audio_dac_l_dvol,
	.hal_audio_dac_l_dmute = hal_rtl_audio_dac_l_dmute,
	.hal_audio_dac_l_zdet = hal_rtl_audio_dac_l_zdet,
	.hal_audio_dac_l_silence = hal_rtl_audio_dac_l_silence,
	.hal_audio_dac_l_silence_result = hal_rtl_audio_dac_l_silence_result,
	.hal_audio_dac_l_silence_status = hal_rtl_audio_dac_l_silence_status,
	.hal_audio_l_sidetone_hpf = hal_rtl_audio_l_sidetone_hpf,
	.hal_audio_r_sidetone_hpf = hal_rtl_audio_r_sidetone_hpf,
	.hal_audio_l_sidetone_vol = hal_rtl_audio_l_sidetone_vol,
	.hal_audio_r_sidetone_vol = hal_rtl_audio_r_sidetone_vol,
	.hal_audio_ad_da_clk_power = hal_rtl_audio_ad_da_clk_power,
	.hal_audio_dac_power = hal_rtl_audio_dac_power,
	.hal_audio_adc_power = hal_rtl_audio_adc_power,
	.hal_audio_output_power = hal_rtl_audio_output_power,
	.hal_audio_input_power = hal_rtl_audio_input_power,
	.hal_audio_hpo_capless_mode = hal_rtl_audio_hpo_capless_mode,
	.hal_audio_hpo_capless_depop = hal_rtl_audio_hpo_capless_depop,
	.hal_audio_hpo_amplifier = hal_rtl_audio_hpo_amplifier,
	.hal_audio_hpo_depop = hal_rtl_audio_hpo_depop,
	.hal_audio_hpo_power = hal_rtl_audio_hpo_power,
	.hal_audio_hpo_mute_depop = hal_rtl_audio_hpo_mute_depop,
	.hal_audio_hpo_op_depop = hal_rtl_audio_hpo_op_depop,
	.hal_audio_hpo_mute = hal_rtl_audio_hpo_mute,
	.hal_audio_hpo_differential_mode = hal_rtl_audio_hpo_differential_mode,
	.hal_audio_mic_bias = hal_rtl_audio_mic_bias,
	.hal_audio_mic_differential_mode = hal_rtl_audio_mic_differential_mode,
	.hal_audio_mic_mute = hal_rtl_audio_mic_mute,
	.hal_audio_line_in_mute = hal_rtl_audio_line_in_mute,
	.hal_audio_mic_boost = hal_rtl_audio_mic_boost,
	.hal_audio_vref = hal_rtl_audio_vref,
	.hal_audio_ip_tcon = hal_rtl_audio_ip_tcon,
	.hal_audio_sport_init = hal_rtl_audio_sport_init,
	.hal_audio_sport_deinit = hal_rtl_audio_sport_deinit,
	.hal_audio_sport_tx_params = hal_rtl_audio_sport_tx_params,
	.hal_audio_sport_rx_params = hal_rtl_audio_sport_rx_params,
	.hal_audio_sport_buf = hal_rtl_audio_sport_buf,
	.hal_audio_sport_tx_cb_handler = hal_rtl_audio_sport_tx_cb_handler,
	.hal_audio_sport_rx_cb_handler = hal_rtl_audio_sport_rx_cb_handler,
	.hal_audio_sport_get_tx_page   = hal_rtl_audio_sport_get_tx_page,
	.hal_audio_sport_tx_page_send  = hal_rtl_audio_sport_tx_page_send,
	.hal_audio_sport_rx_page_recv  = hal_rtl_audio_sport_rx_page_recv,
	.hal_audio_sport_tx_dma_start  = hal_rtl_audio_sport_tx_dma_start,
	.hal_audio_sport_rx_dma_start  = hal_rtl_audio_sport_rx_dma_start,
	.hal_audio_sport_get_tx_dma_start_sta  = hal_rtl_audio_sport_get_tx_dma_start_sta,
	.hal_audio_sport_get_rx_dma_start_sta  = hal_rtl_audio_sport_get_rx_dma_start_sta,
	.hal_audio_sport_tx_byte_swap  = hal_rtl_audio_sport_tx_byte_swap,
	.hal_audio_sport_rx_byte_swap  = hal_rtl_audio_sport_rx_byte_swap,
	.hal_audio_sport_tx_start  = hal_rtl_audio_sport_tx_start,
	.hal_audio_sport_rx_start  = hal_rtl_audio_sport_rx_start,
	.hal_audio_sport_diff_rate_init = hal_rtl_audio_sport_diff_rate_init,
	.hal_audio_input_l_eq = hal_rtl_audio_input_l_eq,
	.hal_audio_input_r_eq = hal_rtl_audio_input_r_eq,
	.hal_audio_output_l_eq = hal_rtl_audio_output_l_eq,
};

/**
 *  @brief Initialize the AUDIO hardware and turn on the AUDIO.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_codec_power Select audio codec LDO power. 0: 1.8V, 1: 2.8V.
 *
 *  @returns void
 */
void hal_rtl_audio_init(hal_audio_adapter_t *paudio_adapter, audio_codec_power_t audio_codec_power)
{
	u16 audio_codec_index_02h;

	paudio_adapter->si_base_addr = (SI_Type *)SI_REG_BASE;

	hal_sys_peripheral_en(SI_SYS, ENABLE);

	//Use internal audio codec
	hal_sys_peripheral_en(AUDIO_CODEC_EXTE_EN, DISABLE);

	//Init Audio Codec enable and clock
	hal_rtl_audio_dev_ctrl(ENABLE);

	//Init Audio Porb
	hal_sys_peripheral_en(AUDIO_CODEC_PORB_EN, ENABLE);

	//Init SI (Serial Interface)
	hal_rtl_audio_si_init(paudio_adapter, ENABLE);

	//MBIAS POW
	audio_codec_index_02h = hal_rtl_audio_si_read(paudio_adapter, 0x02);
	audio_codec_index_02h |= AUDIO_CODEC_BIT_MBIAS_POW;
	hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);

	//LDO POW
	hal_delay_us(2);
	hal_rtl_audio_ldo_tune(audio_codec_power);
	hal_sys_peripheral_en(AUDIO_CODEC_LDO_EN, ENABLE);

	//Audio Codec En
	hal_rtl_audio_ip_tcon(paudio_adapter, ENABLE);

}

/**
 *  @brief De-initialize of the AUDIO hardware and turn off the AUDIO.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_rtl_audio_deinit(hal_audio_adapter_t *paudio_adapter)
{
	//Deinit LDO POW
	hal_sys_peripheral_en(AUDIO_CODEC_LDO_EN, DISABLE);

	//Deinit SI (Serial Interface)
	hal_sys_peripheral_en(SI_SYS, DISABLE);

	//Deinit Audio Porb
	hal_sys_peripheral_en(AUDIO_CODEC_PORB_EN, DISABLE);

	//Deinit Audio
	hal_rtl_audio_dev_ctrl(DISABLE);
}

/**
 *  @brief Control the communication interface of the audio codec for reading or writing the register.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_si_init(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	SI_TypeDef *psi_reg = (SI_TypeDef *)paudio_adapter->si_base_addr;
	u32 temp_reg;

	temp_reg = psi_reg->SI_CLK_CTRL;

	temp_reg &= ~(SI_BIT_REG_DK_EN);

	temp_reg |= (en << SI_SHIFT_REG_DK_EN);

	psi_reg->SI_CLK_CTRL = temp_reg;
}

/**
 *  @brief Read the register of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] address  The register address.
 *
 *  @returns The register value.
 */
u16 hal_rtl_audio_si_read(hal_audio_adapter_t *paudio_adapter, u8 address)
{
	SI_TypeDef *psi_reg = (SI_TypeDef *)paudio_adapter->si_base_addr;
	u32 temp_reg;

	if ((psi_reg->SI_CTRL & SI_BIT_READ_START) == SI_BIT_READ_START) {
		DBG_AUDIO_WARN("hal_rtl_audio_si_read: before still in reading \r\n");
	}

	temp_reg = psi_reg->SI_CTRL;
	temp_reg &= ~(SI_MASK_ADDRESS);
	temp_reg |= ((address << SI_SHIFT_ADDRESS) | SI_BIT_READ_START);
	psi_reg->SI_CTRL = temp_reg;

	while (1) {
		if ((psi_reg->SI_CTRL & SI_BIT_READ_START) == 0) {
			break;
		}
	}

	return ((psi_reg->SI_CTRL & SI_MASK_DATA) >> SI_SHIFT_DATA);
}

/**
 *  @brief Write the register of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] address  The register address.
 *  @param[in] data  The register value to be written.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_rtl_audio_si_write(hal_audio_adapter_t *paudio_adapter, u8 address, u16 data)
{
	SI_TypeDef *psi_reg = (SI_TypeDef *)paudio_adapter->si_base_addr;
	u16 si_read_data;
	u32 temp_reg;

	if ((psi_reg->SI_CTRL & SI_BIT_WR_START) == SI_BIT_WR_START) {
		DBG_AUDIO_WARN("hal_audio_si_write: before still in writing \r\n");
		return HAL_BUSY;
	}

	temp_reg = psi_reg->SI_CTRL;
	temp_reg &= ~(SI_MASK_ADDRESS | SI_MASK_DATA);
	temp_reg |= ((address << SI_SHIFT_ADDRESS) | (data << SI_SHIFT_DATA) | SI_BIT_WR_START);
	psi_reg->SI_CTRL = temp_reg;

	while (1) {
		if ((psi_reg->SI_CTRL & SI_BIT_WR_START) == 0) {
			break;
		}
	}

#if 1
	si_read_data = hal_rtl_audio_si_read(paudio_adapter, address);
	DBG_AUDIO_INFO("0x%2x: 0x%4x \r\n", address, si_read_data);
#endif

	return HAL_OK;
}

/**
 *  @brief Select audio codec LDO power.
 *  @details Select audio codec LDO power 1.8V or 2.8V.
 *  @param[in]   sel  Select codec LDO power.
 *                 - 0 = LDO power 1.8V.
 *                 - 1 = LDO power 2.8V.
 *  @return      void
 *
 */
void hal_rtl_audio_ldo_tune(u8 sel)
{
	u8 power_tune;

	if (sel == 0) {
		power_tune = 0x5F;
	} else {
		power_tune = 0x20;
	}

	hal_sys_set_clk(AUDIO_CODEC_LDO_TUNE, power_tune);
}

/**
 *  @brief Audio codec device enable control.
 *  @details Enable or disable the audio codec device function, clock and pins.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.
 *  @return      void
 *
 */
void hal_rtl_audio_dev_ctrl(BOOL en)
{
	if (en) {
		hal_sys_peripheral_en(AUDIO_CODEC_SCLK_EN, ENABLE);
		hal_sys_peripheral_en(AUDIO_CODEC_EN, ENABLE);
	} else {
		hal_sys_peripheral_en(AUDIO_CODEC_EN, DISABLE);
		hal_sys_peripheral_en(AUDIO_CODEC_SCLK_EN, DISABLE);
	}
}

/**
 *  @brief Set the sample rate of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_sample_rate  Sample rate.
 *
 *  @returns void
 */
void hal_rtl_audio_rate(hal_audio_adapter_t *paudio_adapter, audio_sample_rate_t audio_tx_rate, audio_sample_rate_t audio_rx_rate)
{
	u16 audio_codec_index_17h;

	audio_codec_index_17h = hal_rtl_audio_si_read(paudio_adapter, 0x17);

	audio_codec_index_17h &= ~(AUDIO_CODEC_MASK_DAC_SAMPLE_RATE | AUDIO_CODEC_MASK_ADC_SAMPLE_RATE);
	audio_codec_index_17h |= (audio_tx_rate << AUDIO_CODEC_SHIFT_DAC_SAMPLE_RATE);
	audio_codec_index_17h |= (audio_rx_rate << AUDIO_CODEC_SHIFT_ADC_SAMPLE_RATE);

	hal_rtl_audio_si_write(paudio_adapter, 0x17, audio_codec_index_17h);
}

/**
 *  @brief Set the format of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_format  Select the interface format.
 *
 *  @returns void
 */
void hal_rtl_audio_format(hal_audio_adapter_t *paudio_adapter, audio_format_t audio_format)
{
	u16 audio_codec_index_10h;

	audio_codec_index_10h = hal_rtl_audio_si_read(paudio_adapter, 0x10);

	audio_codec_index_10h &= ~(AUDIO_CODEC_MASK_I2S_DATA_FORMAT_SEL_TX | AUDIO_CODEC_MASK_I2S_DATA_FORMAT_SEL_RX);
	audio_codec_index_10h |= (audio_format << AUDIO_CODEC_SHIFT_I2S_DATA_FORMAT_SEL_TX);
	audio_codec_index_10h |= (audio_format << AUDIO_CODEC_SHIFT_I2S_DATA_FORMAT_SEL_RX);

	hal_rtl_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h);
}

/**
 *  @brief Set the data length of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_word_len  The data length.
 *
 *  @returns void
 */
void hal_rtl_audio_length(hal_audio_adapter_t *paudio_adapter, audio_word_len_t audio_tx_word_len, audio_word_len_t audio_rx_word_len)
{
	u16 audio_codec_index_10h;

	audio_codec_index_10h = hal_rtl_audio_si_read(paudio_adapter, 0x10);

	audio_codec_index_10h &= ~(AUDIO_CODEC_MASK_I2S_DATA_LEN_SEL_TX | AUDIO_CODEC_MASK_I2S_DATA_LEN_SEL_RX);
	audio_codec_index_10h |= (audio_tx_word_len << AUDIO_CODEC_SHIFT_I2S_DATA_LEN_SEL_TX);
	audio_codec_index_10h |= (audio_rx_word_len << AUDIO_CODEC_SHIFT_I2S_DATA_LEN_SEL_RX);

	hal_rtl_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h);
}

/**
 *  @brief Invert the SCK of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sck_inv_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_sck_inv(hal_audio_adapter_t *paudio_adapter, BOOL sck_inv_en)
{
	u16 audio_codec_index_10h;

	audio_codec_index_10h = hal_rtl_audio_si_read(paudio_adapter, 0x10);

	audio_codec_index_10h &= ~(AUDIO_CODEC_BIT_INV_I2S_SCLK);
	audio_codec_index_10h |= (sck_inv_en << AUDIO_CODEC_SHIFT_INV_I2S_SCLK);

	hal_rtl_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h);
}

/**
 *  @brief Control the interface loopback mode of the audio codec. This direction is tx to rx.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sck_inv_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en)
{
	u16 audio_codec_index_10h;

	audio_codec_index_10h = hal_rtl_audio_si_read(paudio_adapter, 0x10);

	audio_codec_index_10h &= ~(AUDIO_CODEC_BIT_STEREO_I2S_SELF_LPBK_EN);
	audio_codec_index_10h |= (loopback_en << AUDIO_CODEC_SHIFT_STEREO_I2S_SELF_LPBK_EN);

	hal_rtl_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h);
}

/**
 *  @brief Control the tx data format of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_sel_ch  Set the relation between the data and channel.
 *                      -00: L/R.
 *                      -01: R/L.
 *                      -10: L/L.
 *                      -11: R/R.
 *
 *  @returns void
 */
void hal_rtl_audio_tx_ch(hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch)
{
	u16 audio_codec_index_10h;

	audio_codec_index_10h = hal_rtl_audio_si_read(paudio_adapter, 0x10);

	audio_codec_index_10h &= ~(AUDIO_CODEC_MASK_SEL_I2S_TX_CH);
	audio_codec_index_10h |= (audio_sel_ch << AUDIO_CODEC_SHIFT_SEL_I2S_TX_CH);

	hal_rtl_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h);
}

/**
 *  @brief Control the rx data format of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_sel_ch  Set the relation between the data and channel.
 *                      -00: L/R.
 *                      -01: R/L.
 *                      -10: L/L.
 *                      -11: R/R.
 *
 *  @returns void
 */
void hal_rtl_audio_rx_ch(hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch)
{
	u16 audio_codec_index_10h;

	audio_codec_index_10h = hal_rtl_audio_si_read(paudio_adapter, 0x10);

	audio_codec_index_10h &= ~(AUDIO_CODEC_MASK_SEL_I2S_RX_CH);
	audio_codec_index_10h |= (audio_sel_ch << AUDIO_CODEC_SHIFT_SEL_I2S_RX_CH);

	hal_rtl_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h);
}

/**
 *  @brief Reset the the digital IP of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_digital_rst(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	u16 audio_codec_index_10h;
	u8 rst_dis_en = 0;

	if (en == 0) {
		rst_dis_en = 1;
	}

	audio_codec_index_10h = hal_rtl_audio_si_read(paudio_adapter, 0x10);

	audio_codec_index_10h &= ~(AUDIO_CODEC_BIT_I2S_RST_N_REG);
	audio_codec_index_10h |= (rst_dis_en << AUDIO_CODEC_SHIFT_I2S_RST_N_REG);

	hal_rtl_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h);
}

/**
 *  @brief Control the DAC & ADC loopback. This direction is tx to rx.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] loopback_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_daad_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en)
{
	u16 audio_codec_index_fbh;

	audio_codec_index_fbh = hal_rtl_audio_si_read(paudio_adapter, 0xfb);

	audio_codec_index_fbh &= ~(AUDIO_CODEC_BIT_DAAD_LPBK_EN);
	audio_codec_index_fbh |= (loopback_en << AUDIO_CODEC_SHIFT_DAAD_LPBK_EN);

	hal_rtl_audio_si_write(paudio_adapter, 0xfb, audio_codec_index_fbh);
}

/**
 *  @brief Control the DAC & ADC loopback. This direction is rx to tx.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] loopback_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_adda_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en)
{
	u16 audio_codec_index_fdh;

	audio_codec_index_fdh = hal_rtl_audio_si_read(paudio_adapter, 0xfd);

	audio_codec_index_fdh &= ~(AUDIO_CODEC_BIT_ADDA_LPBK_EN);
	audio_codec_index_fdh |= (loopback_en << AUDIO_CODEC_SHIFT_ADDA_LPBK_EN);

	hal_rtl_audio_si_write(paudio_adapter, 0xfd, audio_codec_index_fdh);
}

/**
 *  @brief Control the ASRC of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] asrc_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_asrc(hal_audio_adapter_t *paudio_adapter, BOOL asrc_en)
{
	u16 audio_codec_index_1bh;

	audio_codec_index_1bh = hal_rtl_audio_si_read(paudio_adapter, 0x1b);

	audio_codec_index_1bh &= ~(AUDIO_CODEC_BIT_ASRC_TX_EN | AUDIO_CODEC_BIT_ASRC_RX_EN);
	audio_codec_index_1bh |= (asrc_en << AUDIO_CODEC_SHIFT_ASRC_TX_EN);
	audio_codec_index_1bh |= (asrc_en << AUDIO_CODEC_SHIFT_ASRC_RX_EN);

	hal_rtl_audio_si_write(paudio_adapter, 0x1b, audio_codec_index_1bh);
}

/**
 *  @brief Control the mute mixer of DAC.
 *         Only support the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dac_l_mute_en  Mute control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_dac_mixer(hal_audio_adapter_t *paudio_adapter, BOOL dac_l_mute_en)
{
	u16 audio_codec_index_fbh;

	audio_codec_index_fbh = hal_rtl_audio_si_read(paudio_adapter, 0xfb);

	audio_codec_index_fbh &= ~(AUDIO_CODEC_BIT_DAC_L_DMIX_MUTE_128FS_DA);
	audio_codec_index_fbh |= (dac_l_mute_en << AUDIO_CODEC_SHIFT_DAC_L_DMIX_MUTE_128FS_DA);

	hal_rtl_audio_si_write(paudio_adapter, 0xfb, audio_codec_index_fbh);
}

/**
 *  @brief Control the mute mixer of amic.
 *         Only support the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] amic_l_mute_en  Mute control: 0 is disable, 1 is enable.
 *  @param[in] amic_r_mute_en  Mute control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_amic_mixer(hal_audio_adapter_t *paudio_adapter, BOOL amic_l_mute_en, BOOL amic_r_mute_en)
{
	u16 audio_codec_index_11h;
	u16 audio_codec_index_14h;

	audio_codec_index_11h = hal_rtl_audio_si_read(paudio_adapter, 0x11);
	audio_codec_index_14h = hal_rtl_audio_si_read(paudio_adapter, 0x14);

	audio_codec_index_11h &= ~(AUDIO_CODEC_BIT_ADC_L_AD_MIX_MUTE);
	audio_codec_index_11h |= (amic_l_mute_en << AUDIO_CODEC_SHIFT_ADC_L_AD_MIX_MUTE);

	audio_codec_index_14h &= ~(AUDIO_CODEC_BIT_ADC_R_AD_MIX_MUTE);
	audio_codec_index_14h |= (amic_r_mute_en << AUDIO_CODEC_SHIFT_ADC_R_AD_MIX_MUTE);

	hal_rtl_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h);
	hal_rtl_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h);
}

/**
 *  @brief Control the mute mixer of dmic.
 *         Only support the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_l_mute_en  Mute control: 0 is disable, 1 is enable.
 *  @param[in] dmic_r_mute_en  Mute control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_dmic_mixer(hal_audio_adapter_t *paudio_adapter, BOOL dmic_l_mute_en, BOOL dmic_r_mute_en)
{
	u16 audio_codec_index_11h;
	u16 audio_codec_index_14h;

	audio_codec_index_11h = hal_rtl_audio_si_read(paudio_adapter, 0x11);
	audio_codec_index_14h = hal_rtl_audio_si_read(paudio_adapter, 0x14);

	audio_codec_index_11h &= ~(AUDIO_CODEC_BIT_ADC_L_DMIC_MIX_MUTE);
	audio_codec_index_11h |= (dmic_l_mute_en << AUDIO_CODEC_SHIFT_ADC_L_DMIC_MIX_MUTE);

	audio_codec_index_14h &= ~(AUDIO_CODEC_BIT_ADC_R_DMIC_MIX_MUTE);
	audio_codec_index_14h |= (dmic_r_mute_en << AUDIO_CODEC_SHIFT_ADC_R_DMIC_MIX_MUTE);

	hal_rtl_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h);
	hal_rtl_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h);
}

/**
 *  @brief Control the sidetone mixer.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sidetone_l_mute_en  Mute control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_sidetone_mixer(hal_audio_adapter_t *paudio_adapter, BOOL sidetone_l_mute_en)
{
	u16 audio_codec_index_fbh;

	audio_codec_index_fbh = hal_rtl_audio_si_read(paudio_adapter, 0xfb);

	audio_codec_index_fbh &= ~(AUDIO_CODEC_BIT_DAC_L_DMIX_MUTE_128FS_SIDETONE);
	audio_codec_index_fbh |= (sidetone_l_mute_en << AUDIO_CODEC_SHIFT_DAC_L_DMIX_MUTE_128FS_SIDETONE);

	hal_rtl_audio_si_write(paudio_adapter, 0xfb, audio_codec_index_fbh);
}

/**
 *  @brief Control the DAC clock.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dac_l_clk_en  Control the left channel clock: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_dac_clk(hal_audio_adapter_t *paudio_adapter, BOOL dac_l_clk_en)
{
	u16 audio_codec_index_18h;

	audio_codec_index_18h = hal_rtl_audio_si_read(paudio_adapter, 0x18);

	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_DA_L_EN);
	audio_codec_index_18h |= (dac_l_clk_en << AUDIO_CODEC_SHIFT_DA_L_EN);
	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_MOD_L_EN);
	audio_codec_index_18h |= (dac_l_clk_en << AUDIO_CODEC_SHIFT_MOD_L_EN);

	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_DA_ANA_CLK_EN | AUDIO_CODEC_BIT_DA_FIFO_EN);

	if (dac_l_clk_en == 1) {
		audio_codec_index_18h |= (AUDIO_CODEC_BIT_DA_ANA_CLK_EN | AUDIO_CODEC_BIT_DA_FIFO_EN);
	}

	hal_rtl_audio_si_write(paudio_adapter, 0x18, audio_codec_index_18h);
}

/**
 *  @brief Control the ADC clock.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] adc_l_clk_en  Control the left channel clock: 0 is disable, 1 is enable.
 *  @param[in] adc_r_clk_en  Control the right channel clock: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_clk(hal_audio_adapter_t *paudio_adapter, BOOL adc_l_clk_en, BOOL adc_r_clk_en)
{
	u16 audio_codec_index_18h;

	audio_codec_index_18h = hal_rtl_audio_si_read(paudio_adapter, 0x18);

	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_AD_L_EN);
	audio_codec_index_18h |= (adc_l_clk_en << AUDIO_CODEC_SHIFT_AD_L_EN);
	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_AD_R_EN);
	audio_codec_index_18h |= (adc_r_clk_en << AUDIO_CODEC_SHIFT_AD_R_EN);

	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_AD_ANA_L_EN);
	audio_codec_index_18h |= (adc_l_clk_en << AUDIO_CODEC_SHIFT_AD_ANA_L_EN);
	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_AD_ANA_R_EN);
	audio_codec_index_18h |= (adc_r_clk_en << AUDIO_CODEC_SHIFT_AD_ANA_R_EN);

	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_AD_FIFO_EN);
	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_AD_ANA_CLK_EN);

	if ((adc_l_clk_en == 1) || (adc_r_clk_en == 1)) {
		audio_codec_index_18h |= AUDIO_CODEC_BIT_AD_FIFO_EN;
		audio_codec_index_18h |= AUDIO_CODEC_BIT_AD_ANA_CLK_EN;
	}

	hal_rtl_audio_si_write(paudio_adapter, 0x18, audio_codec_index_18h);
}

/**
 *  @brief Control the D-MIC clock.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dimc_l_clk_en  Control the left channel clock: 0 is disable, 1 is enable.
 *  @param[in] dimc_r_clk_en  Control the right channel clock: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_dmic_clk(hal_audio_adapter_t *paudio_adapter, BOOL dimc_l_clk_en, BOOL dimc_r_clk_en)
{
	u16 audio_codec_index_18h;

	audio_codec_index_18h = hal_rtl_audio_si_read(paudio_adapter, 0x18);

	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_AD_L_EN);
	audio_codec_index_18h |= (dimc_l_clk_en << AUDIO_CODEC_SHIFT_AD_L_EN);
	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_AD_R_EN);
	audio_codec_index_18h |= (dimc_r_clk_en << AUDIO_CODEC_SHIFT_AD_R_EN);

	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_DMIC_L_EN);
	audio_codec_index_18h |= (dimc_l_clk_en << AUDIO_CODEC_SHIFT_DMIC_L_EN);
	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_DMIC_R_EN);
	audio_codec_index_18h |= (dimc_r_clk_en << AUDIO_CODEC_SHIFT_DMIC_R_EN);

	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_AD_FIFO_EN);
	audio_codec_index_18h &= ~(AUDIO_CODEC_BIT_DMIC_CLK_EN);

	if ((dimc_l_clk_en == 1) || (dimc_r_clk_en == 1)) {
		audio_codec_index_18h |= AUDIO_CODEC_BIT_AD_FIFO_EN;
		audio_codec_index_18h |= AUDIO_CODEC_BIT_DMIC_CLK_EN;
	}

	hal_rtl_audio_si_write(paudio_adapter, 0x18, audio_codec_index_18h);
}

/**
 *  @brief Select the input clock of D-MIC.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_input_clk  The D-MIC clock.
 *                      -0: 5MHz.
 *                      -1: 2.5MHz.
 *                      -2: 1.25MHz.
 *                      -3: 625KHz.
 *                      -4: 312.5KHz.
 *
 *  @returns void
 */
void hal_rtl_audio_dmic_input_clk(hal_audio_adapter_t *paudio_adapter, audio_dmic_input_clk_t dmic_input_clk)
{
	u16 audio_codec_index_17h;

	audio_codec_index_17h = hal_rtl_audio_si_read(paudio_adapter, 0x17);

	audio_codec_index_17h &= ~(AUDIO_CODEC_MASK_DMIC1_CLK_SEL);
	audio_codec_index_17h |= (dmic_input_clk << AUDIO_CODEC_SHIFT_DMIC1_CLK_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x17, audio_codec_index_17h);
}

/**
 *  @brief Control the D-MIC latch.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_l_latch  Control the D-MIC latch of the left channel.
 *  @param[in] dmic_r_latch  Control the D-MIC latch of the right channel.
 *
 *  @returns void
 */
void hal_rtl_audio_dmic_latch(hal_audio_adapter_t *paudio_adapter, audio_dmic_latch_t dmic_l_latch, audio_dmic_latch_t dmic_r_latch)
{
	u16 audio_codec_index_11h;
	u16 audio_codec_index_14h;

	audio_codec_index_11h = hal_rtl_audio_si_read(paudio_adapter, 0x11);
	audio_codec_index_14h = hal_rtl_audio_si_read(paudio_adapter, 0x14);

	audio_codec_index_11h &= ~(AUDIO_CODEC_MASK_ADC_L_DMIC_SRC_SEL);
	audio_codec_index_11h |= (dmic_l_latch << AUDIO_CODEC_SHIFT_ADC_L_DMIC_SRC_SEL);
	audio_codec_index_14h &= ~(AUDIO_CODEC_MASK_ADC_R_DMIC_SRC_SEL);
	audio_codec_index_14h |= (dmic_r_latch << AUDIO_CODEC_SHIFT_ADC_R_DMIC_SRC_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h);
	hal_rtl_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h);
}

/**
 *  @brief Control the D-MIC gain of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_boost  Set the D-MIC boost.
 *
 *  @returns void
 */
void hal_rtl_audio_dmic_l_gain(hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain)
{
	u16 audio_codec_index_12h;

	audio_codec_index_12h = hal_rtl_audio_si_read(paudio_adapter, 0x12);

	audio_codec_index_12h &= ~(AUDIO_CODEC_MASK_ADC_L_DMIC_BOOST_GAIN);
	audio_codec_index_12h |= (dmic_gain << AUDIO_CODEC_SHIFT_ADC_L_DMIC_BOOST_GAIN);

	hal_rtl_audio_si_write(paudio_adapter, 0x12, audio_codec_index_12h);
}

/**
 *  @brief Control the D-MIC gain of the right channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_boost  Set the D-MIC boost.
 *
 *  @returns void
 */
void hal_rtl_audio_dmic_r_gain(hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain)
{
	u16 audio_codec_index_15h;

	audio_codec_index_15h = hal_rtl_audio_si_read(paudio_adapter, 0x15);

	audio_codec_index_15h &= ~(AUDIO_CODEC_MASK_ADC_R_DMIC_BOOST_GAIN);
	audio_codec_index_15h |= (dmic_gain << AUDIO_CODEC_SHIFT_ADC_R_DMIC_BOOST_GAIN);

	hal_rtl_audio_si_write(paudio_adapter, 0x15, audio_codec_index_15h);
}

/**
 *  @brief Control the D-MIC SRC filter of the left channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lp_1st_en  Control the 1nd LPF: 0 is disable, 1 is enable.
 *  @param[in] lp_2st_en  Control the 2nd LPF: 0 is disable, 1 is enable.
 *  @param[in] src_freq  Set the 1st LPF fc.
 *
 *  @returns void
 */
void hal_rtl_audio_dmic_l_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
	u16 audio_codec_index_11h;

	audio_codec_index_11h = hal_rtl_audio_si_read(paudio_adapter, 0x11);

	audio_codec_index_11h &= ~(AUDIO_CODEC_BIT_ADC_L_DMIC_LPF1ST_EN);
	audio_codec_index_11h |= (lp_1st_en << AUDIO_CODEC_SHIFT_ADC_L_DMIC_LPF1ST_EN);
	audio_codec_index_11h &= ~(AUDIO_CODEC_BIT_ADC_L_DMIC_LPF2ND_EN);
	audio_codec_index_11h |= (lp_2st_en << AUDIO_CODEC_SHIFT_ADC_L_DMIC_LPF2ND_EN);
	audio_codec_index_11h &= ~(AUDIO_CODEC_MASK_ADC_L_DMIC_LPF1ST_FC_SEL);
	audio_codec_index_11h |= (src_freq << AUDIO_CODEC_SHIFT_ADC_L_DMIC_LPF1ST_FC_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h);
}

/**
 *  @brief Control the D-MIC SRC filter of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lp_1st_en  Control the 1nd LPF: 0 is disable, 1 is enable.
 *  @param[in] lp_2st_en  Control the 2nd LPF: 0 is disable, 1 is enable.
 *  @param[in] src_freq  Set the 1st LPF fc.
 *
 *  @returns void
 */
void hal_rtl_audio_dmic_r_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
	u16 audio_codec_index_14h;

	audio_codec_index_14h = hal_rtl_audio_si_read(paudio_adapter, 0x14);

	audio_codec_index_14h &= ~(AUDIO_CODEC_BIT_ADC_R_DMIC_LPF1ST_EN);
	audio_codec_index_14h |= (lp_1st_en << AUDIO_CODEC_SHIFT_ADC_R_DMIC_LPF1ST_EN);
	audio_codec_index_14h &= ~(AUDIO_CODEC_BIT_ADC_R_DMIC_LPF2ND_EN);
	audio_codec_index_14h |= (lp_2st_en << AUDIO_CODEC_SHIFT_ADC_R_DMIC_LPF2ND_EN);
	audio_codec_index_14h &= ~(AUDIO_CODEC_MASK_ADC_R_DMIC_LPF1ST_FC_SEL);
	audio_codec_index_14h |= (src_freq << AUDIO_CODEC_SHIFT_ADC_R_DMIC_LPF1ST_FC_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h);
}

/**
 *  @brief Control the A-MIC SRC filter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lp_1st_en  Control the 1nd LPF: 0 is disable, 1 is enable.
 *  @param[in] lp_2st_en  Control the 2nd LPF: 0 is disable, 1 is enable.
 *  @param[in] src_freq  Set the 1st LPF fc.
 *
 *  @returns void
 */
void hal_rtl_audio_amic_l_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
	u16 audio_codec_index_11h;

	audio_codec_index_11h = hal_rtl_audio_si_read(paudio_adapter, 0x11);

	audio_codec_index_11h &= ~(AUDIO_CODEC_BIT_ADC_L_AD_LPF1ST_EN);
	audio_codec_index_11h |= (lp_1st_en << AUDIO_CODEC_SHIFT_ADC_L_AD_LPF1ST_EN);
	audio_codec_index_11h &= ~(AUDIO_CODEC_BIT_ADC_L_AD_LPF2ND_EN);
	audio_codec_index_11h |= (lp_2st_en << AUDIO_CODEC_SHIFT_ADC_L_AD_LPF2ND_EN);
	audio_codec_index_11h &= ~(AUDIO_CODEC_MASK_ADC_L_AD_LPF1ST_FC_SEL);
	audio_codec_index_11h |= (src_freq << AUDIO_CODEC_SHIFT_ADC_L_AD_LPF1ST_FC_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h);
}

/**
 *  @brief Control the A-MIC SRC filter of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lp_1st_en  Control the 1nd LPF: 0 is disable, 1 is enable.
 *  @param[in] lp_2st_en  Control the 2nd LPF: 0 is disable, 1 is enable.
 *  @param[in] src_freq  Set the 1st LPF fc.
 *
 *  @returns void
 */
void hal_rtl_audio_amic_r_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
	u16 audio_codec_index_14h;

	audio_codec_index_14h = hal_rtl_audio_si_read(paudio_adapter, 0x14);

	audio_codec_index_14h &= ~(AUDIO_CODEC_BIT_ADC_R_AD_LPF1ST_EN);
	audio_codec_index_14h |= (lp_1st_en << AUDIO_CODEC_SHIFT_ADC_R_AD_LPF1ST_EN);
	audio_codec_index_14h &= ~(AUDIO_CODEC_BIT_ADC_R_AD_LPF2ND_EN);
	audio_codec_index_14h |= (lp_2st_en << AUDIO_CODEC_SHIFT_ADC_R_AD_LPF2ND_EN);
	audio_codec_index_14h &= ~(AUDIO_CODEC_MASK_ADC_R_AD_LPF1ST_FC_SEL);
	audio_codec_index_14h |= (src_freq << AUDIO_CODEC_SHIFT_ADC_R_AD_LPF1ST_FC_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h);
}

/**
 *  @brief Control the ADC high pass filter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Control the HPF: 0 is disable, 1 is enable.
 *  @param[in] audio_hpf_fc Set the cutoff frequency.
 *                      -0:  The cutoff frequency is 0.005*fs.
 *                      -1:  The cutoff frequency is 0.0025*fs.
 *                      -2:  The cutoff frequency is 0.00125*fs.
 *                      -3:  The cutoff frequency is 0.000625*fs.
 *                      -4:  The cutoff frequency is 0.0003125*fs.
 *                      -5:  The cutoff frequency is 0.00015625*fs.
 *                      -6:  The cutoff frequency is 0.000078125*fs.
 *                      -7:  The cutoff frequency is 0.0000390625*fs.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_l_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_fc_t audio_hpf_fc)
{
	u16 audio_codec_index_11h;
	u16 audio_codec_index_13h;

	audio_codec_index_11h = hal_rtl_audio_si_read(paudio_adapter, 0x11);
	audio_codec_index_11h &= ~(AUDIO_CODEC_BIT_ADC_L_AD_DCHPF_EN);
	hal_rtl_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h);

	if (en == ENABLE) {
		audio_codec_index_13h = hal_rtl_audio_si_read(paudio_adapter, 0x13);
		audio_codec_index_13h &= ~(AUDIO_CODEC_MASK_ADC_L_DCHPF_FC_SEL);
		audio_codec_index_13h |= (audio_hpf_fc << AUDIO_CODEC_SHIFT_ADC_L_DCHPF_FC_SEL);
		hal_rtl_audio_si_write(paudio_adapter, 0x13, audio_codec_index_13h);

		audio_codec_index_11h = hal_rtl_audio_si_read(paudio_adapter, 0x11);
		audio_codec_index_11h |= (0x01 << AUDIO_CODEC_SHIFT_ADC_L_AD_DCHPF_EN);
		hal_rtl_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h);
	}
}

/**
 *  @brief Control the ADC high pass filter of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Control the HPF: 0 is disable, 1 is enable.
 *  @param[in] audio_hpf_fc Set the cutoff frequency.
 *                      -0:  The cutoff frequency is 0.005*fs.
 *                      -1:  The cutoff frequency is 0.0025*fs.
 *                      -2:  The cutoff frequency is 0.00125*fs.
 *                      -3:  The cutoff frequency is 0.000625*fs.
 *                      -4:  The cutoff frequency is 0.0003125*fs.
 *                      -5:  The cutoff frequency is 0.00015625*fs.
 *                      -6:  The cutoff frequency is 0.000078125*fs.
 *                      -7:  The cutoff frequency is 0.0000390625*fs.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_r_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_fc_t audio_hpf_fc)
{
	u16 audio_codec_index_14h;
	u16 audio_codec_index_16h;

	audio_codec_index_14h = hal_rtl_audio_si_read(paudio_adapter, 0x14);
	audio_codec_index_14h &= ~(AUDIO_CODEC_BIT_ADC_R_AD_DCHPF_EN);
	hal_rtl_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h);

	if (en == ENABLE) {
		audio_codec_index_16h = hal_rtl_audio_si_read(paudio_adapter, 0x16);
		audio_codec_index_16h &= ~(AUDIO_CODEC_MASK_ADC_R_DCHPF_FC_SEL);
		audio_codec_index_16h |= (audio_hpf_fc << AUDIO_CODEC_SHIFT_ADC_R_DCHPF_FC_SEL);
		hal_rtl_audio_si_write(paudio_adapter, 0x16, audio_codec_index_16h);

		audio_codec_index_14h = hal_rtl_audio_si_read(paudio_adapter, 0x14);
		audio_codec_index_14h |= (0x01 << AUDIO_CODEC_SHIFT_ADC_R_AD_DCHPF_EN);
		hal_rtl_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h);
	}
}

/**
 *  @brief Control the ADC digital volume of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] step  The digital volume. Every Step is 0.375dB.
 *         The value 0x7F is 30dB.
 *         The value 0x2F is 0dB.
 *         The value 0x00 is -17.625dB.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_l_dvol(hal_audio_adapter_t *paudio_adapter, u8 step)
{
	u16 audio_codec_index_13h;

	audio_codec_index_13h = hal_rtl_audio_si_read(paudio_adapter, 0x13);

	audio_codec_index_13h &= ~(AUDIO_CODEC_MASK_ADC_L_AD_GAIN);
	audio_codec_index_13h |= (step << AUDIO_CODEC_SHIFT_ADC_L_AD_GAIN);

	hal_rtl_audio_si_write(paudio_adapter, 0x13, audio_codec_index_13h);
}

/**
 *  @brief Control the ADC digital mute of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] mute_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_l_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en)
{
	u16 audio_codec_index_12h;

	audio_codec_index_12h = hal_rtl_audio_si_read(paudio_adapter, 0x12);

	audio_codec_index_12h &= ~(AUDIO_CODEC_BIT_ADC_L_AD_MUTE);
	audio_codec_index_12h |= (mute_en << AUDIO_CODEC_SHIFT_ADC_L_AD_MUTE);

	hal_rtl_audio_si_write(paudio_adapter, 0x12, audio_codec_index_12h);
}

/**
 *  @brief Control the ADC digital volume of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] step  The digital volume. Every Step is 0.375dB.
 *         The value 0x7F is 30dB.
 *         The value 0x2F is 0dB.
 *         The value 0x00 is -17.625dB.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_r_dvol(hal_audio_adapter_t *paudio_adapter, u8 step)
{
	u16 audio_codec_index_16h;

	audio_codec_index_16h = hal_rtl_audio_si_read(paudio_adapter, 0x16);

	audio_codec_index_16h &= ~(AUDIO_CODEC_MASK_ADC_R_AD_GAIN);
	audio_codec_index_16h |= (step << AUDIO_CODEC_SHIFT_ADC_R_AD_GAIN);

	hal_rtl_audio_si_write(paudio_adapter, 0x16, audio_codec_index_16h);
}

/**
 *  @brief Control the ADC digital mute of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] mute_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_r_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en)
{
	u16 audio_codec_index_15h;

	audio_codec_index_15h = hal_rtl_audio_si_read(paudio_adapter, 0x15);

	audio_codec_index_15h &= ~(AUDIO_CODEC_BIT_ADC_R_AD_MUTE);
	audio_codec_index_15h |= (mute_en << AUDIO_CODEC_SHIFT_ADC_R_AD_MUTE);

	hal_rtl_audio_si_write(paudio_adapter, 0x15, audio_codec_index_15h);
}

/**
 *  @brief Control the ADC zero detection function of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] zdet  The detection control.
 *  @param[in] audio_adc_zdet_tout_t  Set the detection timeout.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_l_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout)
{
	u16 audio_codec_index_12h;

	audio_codec_index_12h = hal_rtl_audio_si_read(paudio_adapter, 0x12);

	audio_codec_index_12h &= ~(AUDIO_CODEC_MASK_ADC_L_AD_ZDET_FUNC);
	audio_codec_index_12h |= (zdet << AUDIO_CODEC_SHIFT_ADC_L_AD_ZDET_FUNC);
	audio_codec_index_12h &= ~(AUDIO_CODEC_MASK_ADC_L_AD_ZDET_TOUT);
	audio_codec_index_12h |= (adc_zdet_tout << AUDIO_CODEC_SHIFT_ADC_L_AD_ZDET_TOUT);

	hal_rtl_audio_si_write(paudio_adapter, 0x12, audio_codec_index_12h);
}

/**
 *  @brief Control the ADC zero detection function of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] zdet  The detection control.
 *  @param[in] audio_adc_zdet_tout_t  Set the detection timeout.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_r_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout)
{
	u16 audio_codec_index_15h;

	audio_codec_index_15h = hal_rtl_audio_si_read(paudio_adapter, 0x15);

	audio_codec_index_15h &= ~(AUDIO_CODEC_MASK_ADC_R_AD_ZDET_FUNC);
	audio_codec_index_15h |= (zdet << AUDIO_CODEC_SHIFT_ADC_R_AD_ZDET_FUNC);
	audio_codec_index_15h &= ~(AUDIO_CODEC_MASK_ADC_R_AD_ZDET_TOUT);
	audio_codec_index_15h |= (adc_zdet_tout << AUDIO_CODEC_SHIFT_ADC_R_AD_ZDET_TOUT);

	hal_rtl_audio_si_write(paudio_adapter, 0x15, audio_codec_index_15h);
}

/**
 *  @brief Control the ADC silence detection function of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] silence_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] detect_sel  The detection control.
 *  @param[in] debounce_time  Set the detection timeout.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_l_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time)
{
	u16 audio_codec_index_f8h;

	audio_codec_index_f8h = hal_rtl_audio_si_read(paudio_adapter, 0xf8);

	audio_codec_index_f8h &= ~(AUDIO_CODEC_BIT_ADC_L_SILENCE_DET_MONO_EN);
	audio_codec_index_f8h |= (silence_en << AUDIO_CODEC_SHIFT_ADC_L_SILENCE_DET_MONO_EN);
	audio_codec_index_f8h &= ~(AUDIO_CODEC_MASK_ADC_L_SILENCE_MONO_LEVEL_SEL);
	audio_codec_index_f8h |= (level << AUDIO_CODEC_SHIFT_ADC_L_SILENCE_MONO_LEVEL_SEL);
	audio_codec_index_f8h &= ~(AUDIO_CODEC_MASK_ADC_L_SILENCE_MONO_DEBOUNCE_SEL);
	audio_codec_index_f8h |= (debounce_time << AUDIO_CODEC_SHIFT_ADC_L_SILENCE_MONO_DEBOUNCE_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0xf8, audio_codec_index_f8h);
}

/**
 *  @brief Get the ADC silence detection result of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The silence is not detected.
 *  @return     1:  The silence is detected.
 */
u8 hal_rtl_audio_adc_l_silence_result(hal_audio_adapter_t *paudio_adapter)
{
	u16 audio_codec_index_f8h;
	u8 result;

	audio_codec_index_f8h = hal_rtl_audio_si_read(paudio_adapter, 0xf8);

	result = (audio_codec_index_f8h & AUDIO_CODEC_BIT_ADC_L_SILENCE_DET_MONO_O) >> AUDIO_CODEC_SHIFT_ADC_L_SILENCE_DET_MONO_O;

	return result;
}

/**
 *  @brief Get the ADC silence detection status of the right channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The detection is resting.
 *  @return     1:  The detection is working.
 */
u8 hal_rtl_audio_adc_l_silence_status(hal_audio_adapter_t *paudio_adapter)
{
	u16 audio_codec_index_f8h;
	u8 result;

	audio_codec_index_f8h = hal_rtl_audio_si_read(paudio_adapter, 0xf8);

	result = (audio_codec_index_f8h & AUDIO_CODEC_BIT_ADC_L_SILENECE_DET_MONO_STATUS) >> AUDIO_CODEC_SHIFT_ADC_L_SILENECE_DET_MONO_STATUS;

	return result;
}

/**
 *  @brief Control the ADC silence detection function of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] silence_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] detect_sel  The detection control.
 *  @param[in] debounce_time  Set the detection timeout.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_r_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time)
{
	u16 audio_codec_index_f9h;

	audio_codec_index_f9h = hal_rtl_audio_si_read(paudio_adapter, 0xf9);

	audio_codec_index_f9h &= ~(AUDIO_CODEC_BIT_ADC_R_SILENCE_DET_MONO_EN);
	audio_codec_index_f9h |= (silence_en << AUDIO_CODEC_SHIFT_ADC_R_SILENCE_DET_MONO_EN);
	audio_codec_index_f9h &= ~(AUDIO_CODEC_MASK_ADC_R_SILENCE_MONO_LEVEL_SEL);
	audio_codec_index_f9h |= (level << AUDIO_CODEC_SHIFT_ADC_R_SILENCE_MONO_LEVEL_SEL);
	audio_codec_index_f9h &= ~(AUDIO_CODEC_MASK_ADC_R_SILENCE_MONO_DEBOUNCE_SEL);
	audio_codec_index_f9h |= (debounce_time << AUDIO_CODEC_SHIFT_ADC_R_SILENCE_MONO_DEBOUNCE_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0xf9, audio_codec_index_f9h);
}

/**
 *  @brief Get the ADC silence detection result of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The silence is not detected.
 *  @return     1:  The silence is detected.
 */
u8 hal_rtl_audio_adc_r_silence_result(hal_audio_adapter_t *paudio_adapter)
{
	u16 audio_codec_index_f9h;
	u8 result;

	audio_codec_index_f9h = hal_rtl_audio_si_read(paudio_adapter, 0xf9);

	result = (audio_codec_index_f9h & AUDIO_CODEC_BIT_ADC_R_SILENCE_DET_MONO_O) >> AUDIO_CODEC_SHIFT_ADC_R_SILENCE_DET_MONO_O;

	return result;
}

/**
 *  @brief Get the ADC silence detection status of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The detection is resting.
 *  @return     1:  The detection is working.
 */
u8 hal_rtl_audio_adc_r_silence_status(hal_audio_adapter_t *paudio_adapter)
{
	u16 audio_codec_index_f9h;
	u8 result;

	audio_codec_index_f9h = hal_rtl_audio_si_read(paudio_adapter, 0xf9);

	result = (audio_codec_index_f9h & AUDIO_CODEC_BIT_ADC_R_SILENECE_DET_MONO_STATUS) >> AUDIO_CODEC_SHIFT_ADC_R_SILENECE_DET_MONO_STATUS;

	return result;
}

/**
 *  @brief Control the DAC dither.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dac_l_dither Control the dither of the left channel.
 *                      -0: Disable.
 *                      -1: LSB.
 *                      -2: LSB + 1.
 *                      -3: LSB + 2.
 *  @param[in] dac_r_dither Control the dither of the right channel.  This function is not supported.
 *                      -0: Disable.
 *                      -1: LSB.
 *                      -2: LSB + 1.
 *                      -3: LSB + 2.
 *
 *  @returns void
 */
void hal_rtl_audio_dac_dither(hal_audio_adapter_t *paudio_adapter, audio_dac_dither_t dac_l_dither)
{
	u16 audio_codec_index_fah;

	audio_codec_index_fah = hal_rtl_audio_si_read(paudio_adapter, 0xfa);

	audio_codec_index_fah &= ~(AUDIO_CODEC_MASK_DAC_L_DA_DITHER_SEL);
	audio_codec_index_fah |= (dac_l_dither << AUDIO_CODEC_SHIFT_DAC_L_DA_DITHER_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0xfa, audio_codec_index_fah);
}

/**
 *  @brief Control the DAC high pass filter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Control the HPF: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_dac_l_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	u16 audio_codec_index_fah;

	audio_codec_index_fah = hal_rtl_audio_si_read(paudio_adapter, 0xfa);

	audio_codec_index_fah &= ~(AUDIO_CODEC_BIT_DAC_L_DAHPF_EN);
	audio_codec_index_fah |= (en << AUDIO_CODEC_SHIFT_DAC_L_DAHPF_EN);

	hal_rtl_audio_si_write(paudio_adapter, 0xfa, audio_codec_index_fah);
}

/**
 *  @brief Control the DAC digital volume of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] step  The digital volume. Every Step is 0.375dB.
 *         The value 0xAF is 0dB.
 *         The value 0x00 is -65.625dB.
 *
 *  @returns void
 */

void hal_rtl_audio_dac_l_dvol(hal_audio_adapter_t *paudio_adapter, u8 step)

{
	u16 audio_codec_index_fah;

	audio_codec_index_fah = hal_rtl_audio_si_read(paudio_adapter, 0xfa);

	audio_codec_index_fah &= ~(AUDIO_CODEC_MASK_DAC_L_DA_GAIN);
	audio_codec_index_fah |= (step << AUDIO_CODEC_SHIFT_DAC_L_DA_GAIN);

	hal_rtl_audio_si_write(paudio_adapter, 0xfa, audio_codec_index_fah);
}

/**
 *  @brief Control the DAC digital mute of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] mute_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_dac_l_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en)
{
	u16 audio_codec_index_fbh;

	audio_codec_index_fbh = hal_rtl_audio_si_read(paudio_adapter, 0xfb);

	audio_codec_index_fbh &= ~(AUDIO_CODEC_BIT_DAC_L_DA_MUTE);
	audio_codec_index_fbh |= (mute_en << AUDIO_CODEC_SHIFT_DAC_L_DA_MUTE);

	hal_rtl_audio_si_write(paudio_adapter, 0xfb, audio_codec_index_fbh);
}

/**
 *  @brief Control the DAC zero detection function of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] zdet  The detection control.
 *  @param[in] audio_adc_zdet_tout_t  Set the detection timeout.
 *
 *  @returns void
 */
void hal_rtl_audio_dac_l_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_dac_zdet_tout_t adc_zdet_tout)
{
	u16 audio_codec_index_fah;

	audio_codec_index_fah = hal_rtl_audio_si_read(paudio_adapter, 0xfa);

	audio_codec_index_fah &= ~(AUDIO_CODEC_MASK_DAC_L_DA_ZDET_FUNC);
	audio_codec_index_fah |= (zdet << AUDIO_CODEC_SHIFT_DAC_L_DA_ZDET_FUNC);

	audio_codec_index_fah &= ~(AUDIO_CODEC_MASK_DAC_L_DA_ZDET_TOUT);
	audio_codec_index_fah |= (adc_zdet_tout << AUDIO_CODEC_SHIFT_DAC_L_DA_ZDET_TOUT);

	hal_rtl_audio_si_write(paudio_adapter, 0xfa, audio_codec_index_fah);
}

/**
 *  @brief Control the DAC silence detection function of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] silence_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] debounce_time  Set the detection timeout.
 *
 *  @returns void
 */
void hal_rtl_audio_dac_l_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time)
{
	u16 audio_codec_index_f6h;

	audio_codec_index_f6h = hal_rtl_audio_si_read(paudio_adapter, 0xf6);

	audio_codec_index_f6h &= ~(AUDIO_CODEC_BIT_DAC_L_SILENCE_DET_MONO_EN);
	audio_codec_index_f6h |= (silence_en << AUDIO_CODEC_SHIFT_DAC_L_SILENCE_DET_MONO_EN);

	audio_codec_index_f6h &= ~(AUDIO_CODEC_MASK_DAC_L_SILENCE_MONO_LEVEL_SEL);
	audio_codec_index_f6h |= (level << AUDIO_CODEC_SHIFT_DAC_L_SILENCE_MONO_LEVEL_SEL);

	audio_codec_index_f6h &= ~(AUDIO_CODEC_MASK_DAC_L_SILENCE_MONO_DEBOUNCE_SEL);
	audio_codec_index_f6h |= (debounce_time << AUDIO_CODEC_SHIFT_DAC_L_SILENCE_MONO_DEBOUNCE_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0xf6, audio_codec_index_f6h);
}

/**
 *  @brief Get the DAC silence detection result of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The silence is not detected.
 *  @return     1:  The silence is detected.
 */
u8 hal_rtl_audio_dac_l_silence_result(hal_audio_adapter_t *paudio_adapter)
{
	u16 audio_codec_index_f6h;
	u8 result;

	audio_codec_index_f6h = hal_rtl_audio_si_read(paudio_adapter, 0xf6);

	result = (audio_codec_index_f6h & AUDIO_CODEC_BIT_DAC_L_SILENCE_DET_MONO_O) >> AUDIO_CODEC_SHIFT_DAC_L_SILENCE_DET_MONO_O;

	return result;
}

/**
 *  @brief Get the DAC silence detection status of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The detection is resting.
 *  @return     1:  The detection is working.
 */
u8 hal_rtl_audio_dac_l_silence_status(hal_audio_adapter_t *paudio_adapter)
{
	u16 audio_codec_index_f6h;
	u8 result;

	audio_codec_index_f6h = hal_rtl_audio_si_read(paudio_adapter, 0xf6);

	result = (audio_codec_index_f6h & AUDIO_CODEC_BIT_DAC_L_SILENECE_DET_MONO_STATUS) >> AUDIO_CODEC_SHIFT_DAC_L_SILENECE_DET_MONO_STATUS;

	return result;
}

/**
 *  @brief Control the sidetone high pass filter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] hpf_en  Enable Narrow-band 1st HPF : 0 is disable, 1 is enable.
 *  @param[in] sidetone_hpf  Select the sidetone HPF cut-off frequency.
 *
 *  @returns void
 */
void hal_rtl_audio_l_sidetone_hpf(hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf)
{
	u16 audio_codec_index_0eh;

	audio_codec_index_0eh = hal_rtl_audio_si_read(paudio_adapter, 0x0e);

	audio_codec_index_0eh &= ~(AUDIO_CODEC_BIT_SIDETONE_L_HPF_EN);
	audio_codec_index_0eh |= (hpf_en << AUDIO_CODEC_SHIFT_SIDETONE_L_HPF_EN);

	audio_codec_index_0eh &= ~(AUDIO_CODEC_MASK_SIDETONE_L_HPF_FC_SEL);
	audio_codec_index_0eh |= (sidetone_hpf << AUDIO_CODEC_SHIFT_SIDETONE_L_HPF_FC_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x0e, audio_codec_index_0eh);
}

/**
 *  @brief Control the sidetone high pass filter of the right channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] hpf_en  Enable Narrow-band 1st HPF : 0 is disable, 1 is enable.
 *  @param[in] sidetone_hpf  Select the sidetone HPF cut-off frequency.
 *
 *  @returns void
 */
void hal_rtl_audio_r_sidetone_hpf(hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf)
{
	u16 audio_codec_index_0fh;

	audio_codec_index_0fh = hal_rtl_audio_si_read(paudio_adapter, 0x0f);

	audio_codec_index_0fh &= ~(AUDIO_CODEC_BIT_SIDETONE_R_HPF_EN);
	audio_codec_index_0fh |= (hpf_en << AUDIO_CODEC_SHIFT_SIDETONE_R_HPF_EN);

	audio_codec_index_0fh &= ~(AUDIO_CODEC_MASK_SIDETONE_R_HPF_FC_SEL);
	audio_codec_index_0fh |= (sidetone_hpf << AUDIO_CODEC_SHIFT_SIDETONE_R_HPF_FC_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x0f, audio_codec_index_0fh);
}

/**
 *  @brief Control the sidetone volume of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sidetone_vol  Select the sidetone volume.
 *  @param[in] sidetone_boost  Select the sidetone boost.
 *
 *  @returns void
 */
void hal_rtl_audio_l_sidetone_vol(hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost)
{
	u16 audio_codec_index_0eh;

	audio_codec_index_0eh = hal_rtl_audio_si_read(paudio_adapter, 0x0e);

	audio_codec_index_0eh &= ~(AUDIO_CODEC_MASK_SIDETONE_L_VOL_SEL);
	audio_codec_index_0eh |= (sidetone_vol << AUDIO_CODEC_SHIFT_SIDETONE_L_VOL_SEL);

	audio_codec_index_0eh &= ~(AUDIO_CODEC_BIT_SIDETONE_L_BOOST_SEL);
	audio_codec_index_0eh |= (sidetone_boost << AUDIO_CODEC_SHIFT_SIDETONE_L_BOOST_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x0e, audio_codec_index_0eh);
}

/**
 *  @brief Control the sidetone volume of the right channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sidetone_vol  Select the sidetone volume.
 *  @param[in] sidetone_boost  Select the sidetone boost.
 *
 *  @returns void
 */
void hal_rtl_audio_r_sidetone_vol(hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost)
{
	u16 audio_codec_index_0fh;

	audio_codec_index_0fh = hal_rtl_audio_si_read(paudio_adapter, 0x0f);

	audio_codec_index_0fh &= ~(AUDIO_CODEC_MASK_SIDETONE_R_VOL_SEL);
	audio_codec_index_0fh |= (sidetone_vol << AUDIO_CODEC_SHIFT_SIDETONE_R_VOL_SEL);

	audio_codec_index_0fh &= ~(AUDIO_CODEC_BIT_SIDETONE_R_BOOST_SEL);
	audio_codec_index_0fh |= (sidetone_boost << AUDIO_CODEC_SHIFT_SIDETONE_R_BOOST_SEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x0f, audio_codec_index_0fh);
}

/**
 *  @brief Control the power of the ADC and DAC clock.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_ad_da_clk_power(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	u16 audio_codec_index_00h;

	audio_codec_index_00h = hal_rtl_audio_si_read(paudio_adapter, 0x00);

	audio_codec_index_00h &= ~(AUDIO_CODEC_BIT_DAC_ADDACK_POW);
	audio_codec_index_00h |= (en << AUDIO_CODEC_SHIFT_DAC_ADDACK_POW);

	hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
}

/**
 *  @brief Control the DAC power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_dac_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_00h;

	audio_codec_index_00h = hal_rtl_audio_si_read(paudio_adapter, 0x00);

	audio_codec_index_00h &= ~(AUDIO_CODEC_BIT_DAC_L_POW);
	audio_codec_index_00h |= (left_en << AUDIO_CODEC_SHIFT_DAC_L_POW);

	hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
}

/**
 *  @brief Control the ADC power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_rtl_audio_adc_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_00h;

	audio_codec_index_00h = hal_rtl_audio_si_read(paudio_adapter, 0x00);

	audio_codec_index_00h &= ~(AUDIO_CODEC_BIT_DTSDM_POW_L);
	audio_codec_index_00h |= (left_en << AUDIO_CODEC_SHIFT_DTSDM_POW_L);

	hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
}

/**
 *  @brief Control the output power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_output_mode_t Select the output mode.
 *
 *  @returns void
 */
void hal_rtl_audio_output_power(hal_audio_adapter_t *paudio_adapter, audio_output_mode_t output_mode)
{
	u16 audio_codec_index_00h;
	u16 audio_codec_index_01h;
	u16 audio_codec_index_02h;
	//audio_codec_index_03h_t audio_codec_index_03h;
	u16 audio_codec_index_0ch;
	u16 input_index_00h;
	u16 input_index_02h;

	input_index_00h = hal_rtl_audio_si_read(paudio_adapter, 0x00) & 0x0c00;
	input_index_02h = hal_rtl_audio_si_read(paudio_adapter, 0x02) & 0x7e00;

	if (output_mode == AUDIO_OUTPUT_SINGLE_EDNED) {

		DBG_AUDIO_INFO(" hal_audio_output_power, AUDIO_OUTPUT_SINGLE_EDNED\r\n");

		//Step0:
		//audio_codec_index_03h.w = 0x08f0;
		//hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);

		//Step1:
		audio_codec_index_00h = (0x031b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_01h = 0x07fc;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
		audio_codec_index_02h = (0x81ea | input_index_02h);
		hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);
		audio_codec_index_0ch = 0x0010;
		hal_rtl_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch);

		//Step2:
		audio_codec_index_01h = 0x9ffc;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
		audio_codec_index_02h = (0x81fa | input_index_02h);
		hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);

		//Step3:
		audio_codec_index_00h = (0x039b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_0ch = 0x0018;
		hal_rtl_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch);

		//Step4:
		//hal_delay_ms(300);

		//Step5:
		audio_codec_index_00h = (0x021b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_01h = 0x04fc;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
		audio_codec_index_02h = (0x81ea | input_index_02h);
		hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);
		audio_codec_index_0ch = 0x0010;
		hal_rtl_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch);

	} else if (output_mode == AUDIO_OUTPUT_DIFFERENTIAL) {

		DBG_AUDIO_INFO(" hal_audio_output_power, AUDIO_OUTPUT_DIFFERENTIAL\r\n");

		//Step0:
		//audio_codec_index_03h.w = 0x08f0;
		//hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);

		//Step1:
		audio_codec_index_00h = (0x031b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_01h = 0x07fc;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
		audio_codec_index_02h = (0x812a | input_index_02h);
		hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);
		audio_codec_index_0ch = 0x0010;
		hal_rtl_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch);

		//Step2:
		audio_codec_index_01h = 0x9ffc;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
		audio_codec_index_02h = (0x813a | input_index_02h);
		hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);

		//Step3:
		audio_codec_index_00h = (0x039b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_0ch = 0x0018;
		hal_rtl_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch);

		//Step4:
		hal_delay_ms(50);

		//Step5:
		audio_codec_index_00h = (0x031b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_01h = 0x67fc;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
		audio_codec_index_02h = (0x812a | input_index_02h);
		hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);

		//Step6:
		audio_codec_index_00h = (0x039b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);

		//Step7:
		hal_delay_ms(5);

		//Step8:
		audio_codec_index_01h = 0x04fc;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);

		//Step9:
		audio_codec_index_00h = (0x021b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_0ch = 0x0010;
		hal_rtl_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch);

	} else if (output_mode == AUDIO_OUTPUT_CAPLESS) {

		DBG_AUDIO_INFO(" hal_audio_output_power, AUDIO_OUTPUT_CAPLESS\r\n");

		//Step0:
		//audio_codec_index_03h.w = 0x08f0;
		//hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);

		//Step1:
		audio_codec_index_00h = (0x131b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_01h = 0x07fe;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
		audio_codec_index_02h = (0x81ea | input_index_02h);
		hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);
		audio_codec_index_0ch = 0x0010;
		hal_rtl_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch);

		//Step2:
		audio_codec_index_00h = (0x731b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);

		//Step3:
		audio_codec_index_00h = (0x739b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_0ch = 0x0018;
		hal_rtl_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch);

		//Step4:
		hal_delay_ms(50);

		//Step5:
		audio_codec_index_00h = (0x731b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);

		//Step6:
		audio_codec_index_00h = (0x931b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_01h = 0x1fff;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);

		//Step7:
		audio_codec_index_00h = (0x939b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);

		//Step8:
		hal_delay_ms(5);

		//Step9:
		audio_codec_index_01h = 0x04fe;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);

		//Step10:
		audio_codec_index_00h = (0x121b | input_index_00h);
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);

	} else if (output_mode == AUDIO_OUTPUT_DISABLE) {

		DBG_AUDIO_INFO(" hal_audio_output_power, AUDIO_OUTPUT_DISABLE\r\n");

		audio_codec_index_00h = hal_rtl_audio_si_read(paudio_adapter, 0x00);
		//audio_codec_index_01h = hal_rtl_audio_si_read(paudio_adapter, 0x01);
		audio_codec_index_02h = hal_rtl_audio_si_read(paudio_adapter, 0x02);

		audio_codec_index_00h = audio_codec_index_00h & 0x0FFF;
		hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
		audio_codec_index_01h = 0x0000;
		hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
		audio_codec_index_02h = audio_codec_index_02h & 0xFF00;
		hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);

		hal_delay_ms(3);
	}

	if (output_mode != AUDIO_OUTPUT_DISABLE) {
		hal_rtl_audio_dac_clk(paudio_adapter, ENABLE);
		hal_rtl_audio_dac_mixer(paudio_adapter, DISABLE);
	} else {
		hal_rtl_audio_dac_clk(paudio_adapter, DISABLE);
		hal_rtl_audio_dac_mixer(paudio_adapter, ENABLE);
	}

}

/**
 *  @brief Control the input power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_input_mode_t Select the input mode.
 *
 *  @returns void
 */
void hal_rtl_audio_input_power(hal_audio_adapter_t *paudio_adapter, audio_input_mode_t input_mode)
{
	u16 audio_codec_index_02h;
	u16 audio_codec_index_03h;

	if ((input_mode == AUDIO_MIC_DIFFERENTIAL) || (input_mode == AUDIO_MIC_SINGLE_EDNED)) {

		//MICBAS POW
		hal_delay_us(1);
		audio_codec_index_02h = hal_rtl_audio_si_read(paudio_adapter, 0x02);
		audio_codec_index_02h |= AUDIO_CODEC_BIT_MICBIAS_ENCHX;
		audio_codec_index_02h |= AUDIO_CODEC_BIT_MICBIAS_POW;
		hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);

		//MICBST POW
		hal_delay_us(2);
		audio_codec_index_03h = hal_rtl_audio_si_read(paudio_adapter, 0x03);
		audio_codec_index_03h |= AUDIO_CODEC_BIT_MICBST_POW;
		hal_rtl_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h);

		if (input_mode == AUDIO_MIC_DIFFERENTIAL) {
			DBG_AUDIO_INFO(" hal_rtl_audio_input_power, AUDIO_MIC_DIFFERENTIAL\r\n");
			hal_rtl_audio_mic_differential_mode(paudio_adapter, ENABLE);
		} else {
			DBG_AUDIO_INFO(" hal_rtl_audio_input_power, AUDIO_MIC_SINGLE_EDNED\r\n");
			hal_rtl_audio_mic_differential_mode(paudio_adapter, DISABLE);
		}

		hal_rtl_audio_adc_power(paudio_adapter, ENABLE);
		hal_rtl_audio_mic_boost(paudio_adapter, ENABLE, AUDIO_MIC_0DB);
		hal_rtl_audio_adc_clk(paudio_adapter, ENABLE, ENABLE);
		hal_rtl_audio_adc_amic_mixer(paudio_adapter, DISABLE, DISABLE);

		hal_rtl_audio_line_in_mute(paudio_adapter, ENABLE);
		hal_rtl_audio_mic_mute(paudio_adapter, DISABLE);

		hal_rtl_audio_mic_bias(paudio_adapter, ENABLE, AUDIO_BIAS_0p9_AVDD);
	} else if (input_mode == AUDIO_LINE_IN_MODE) {

		DBG_AUDIO_INFO(" hal_rtl_audio_input_power, AUDIO_LINE_IN_MODE\r\n");

		//MICBAS POW
		hal_delay_us(1);
		audio_codec_index_02h = hal_rtl_audio_si_read(paudio_adapter, 0x02);
		audio_codec_index_02h |= AUDIO_CODEC_BIT_MICBIAS_ENCHX;
		audio_codec_index_02h &= ~(AUDIO_CODEC_BIT_MICBIAS_POW);
		hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);

		//MICBST POW
		hal_delay_us(2);
		audio_codec_index_03h = hal_rtl_audio_si_read(paudio_adapter, 0x03);
		audio_codec_index_03h &= ~(AUDIO_CODEC_BIT_MICBST_POW);
		hal_rtl_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h);

		hal_rtl_audio_adc_power(paudio_adapter, ENABLE);
		hal_rtl_audio_mic_boost(paudio_adapter, ENABLE, AUDIO_MIC_0DB);
		hal_rtl_audio_adc_clk(paudio_adapter, ENABLE, ENABLE);
		hal_rtl_audio_adc_amic_mixer(paudio_adapter, DISABLE, DISABLE);

		hal_rtl_audio_mic_mute(paudio_adapter, ENABLE);
		hal_rtl_audio_line_in_mute(paudio_adapter, DISABLE);
	} else if (input_mode == AUDIO_LEFT_DMIC) {
		DBG_AUDIO_INFO(" hal_rtl_audio_input_power, AUDIO_LEFT_DMIC\r\n");
		hal_rtl_audio_dmic_latch(paudio_adapter, AUDIO_DIMC_RISING, AUDIO_DIMC_FALLING);
		hal_rtl_audio_dmic_l_src(paudio_adapter, ENABLE, ENABLE, AUDIO_SRC_31p04KHZ);
		hal_rtl_audio_dmic_l_gain(paudio_adapter, AUDIO_DMIC_BOOST_0DB);
		hal_rtl_audio_dmic_input_clk(paudio_adapter, AUDIO_DMIC_2p5M);
		hal_rtl_audio_dmic_clk(paudio_adapter, ENABLE, DISABLE);
		hal_rtl_audio_adc_dmic_mixer(paudio_adapter, DISABLE, ENABLE);
	} else if (input_mode == AUDIO_RIGHT_DMIC) {
		DBG_AUDIO_INFO(" hal_rtl_audio_input_power, AUDIO_LEFT_DMIC\r\n");
		hal_rtl_audio_dmic_latch(paudio_adapter, AUDIO_DIMC_RISING, AUDIO_DIMC_FALLING);
		hal_rtl_audio_dmic_r_src(paudio_adapter, ENABLE, ENABLE, AUDIO_SRC_31p04KHZ);
		hal_rtl_audio_dmic_r_gain(paudio_adapter, AUDIO_DMIC_BOOST_0DB);
		hal_rtl_audio_dmic_input_clk(paudio_adapter, AUDIO_DMIC_2p5M);
		hal_rtl_audio_dmic_clk(paudio_adapter, DISABLE, ENABLE);
		hal_rtl_audio_adc_dmic_mixer(paudio_adapter, ENABLE, DISABLE);
	} else if (input_mode == AUDIO_STEREO_DMIC) {
		DBG_AUDIO_INFO(" hal_rtl_audio_input_power, AUDIO_LEFT_DMIC\r\n");
		hal_rtl_audio_dmic_latch(paudio_adapter, AUDIO_DIMC_RISING, AUDIO_DIMC_FALLING);
		hal_rtl_audio_dmic_l_src(paudio_adapter, ENABLE, ENABLE, AUDIO_SRC_31p04KHZ);
		hal_rtl_audio_dmic_l_gain(paudio_adapter, AUDIO_DMIC_BOOST_0DB);
		hal_rtl_audio_dmic_r_src(paudio_adapter, ENABLE, ENABLE, AUDIO_SRC_31p04KHZ);
		hal_rtl_audio_dmic_r_gain(paudio_adapter, AUDIO_DMIC_BOOST_0DB);
		hal_rtl_audio_dmic_input_clk(paudio_adapter, AUDIO_DMIC_2p5M);
		hal_rtl_audio_dmic_clk(paudio_adapter, ENABLE, ENABLE);
		hal_rtl_audio_adc_dmic_mixer(paudio_adapter, DISABLE, DISABLE);
	} else if (input_mode == AUDIO_INPUT_DISABLE) {
		DBG_AUDIO_INFO(" hal_rtl_audio_input_power, AUDIO_INPUT_DISABLE\r\n");
		hal_rtl_audio_mic_mute(paudio_adapter, ENABLE);
		hal_rtl_audio_line_in_mute(paudio_adapter, ENABLE);
		hal_rtl_audio_adc_amic_mixer(paudio_adapter, ENABLE, ENABLE);
		hal_rtl_audio_adc_clk(paudio_adapter, DISABLE, DISABLE);
		hal_rtl_audio_mic_boost(paudio_adapter, DISABLE, AUDIO_MIC_0DB);
		hal_rtl_audio_adc_power(paudio_adapter, DISABLE);

		hal_rtl_audio_adc_dmic_mixer(paudio_adapter, ENABLE, ENABLE);
		hal_rtl_audio_dmic_l_src(paudio_adapter, DISABLE, DISABLE, AUDIO_SRC_31p04KHZ);
		hal_rtl_audio_dmic_l_src(paudio_adapter, DISABLE, DISABLE, AUDIO_SRC_31p04KHZ);
		hal_rtl_audio_dmic_clk(paudio_adapter, DISABLE, DISABLE);
	}

}

/**
 *  @brief Control the capless mode of the headphone.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_hpo_capless_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_00h;

	audio_codec_index_00h = hal_rtl_audio_si_read(paudio_adapter, 0x00);

	audio_codec_index_00h &= ~(AUDIO_CODEC_BIT_HPO_CLL);
	audio_codec_index_00h |= (left_en << AUDIO_CODEC_SHIFT_HPO_CLL);

	hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
}

/**
 *  @brief Control the depop of the headphone in the capless mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is no depop, 1 is depop.
 *
 *  @returns void
 */
void hal_rtl_audio_hpo_capless_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_00h;

	audio_codec_index_00h = hal_rtl_audio_si_read(paudio_adapter, 0x00);

	audio_codec_index_00h &= ~(AUDIO_CODEC_BIT_HPO_CLNDPL | AUDIO_CODEC_BIT_HPO_CLPDPL);
	audio_codec_index_00h |= (left_en << AUDIO_CODEC_SHIFT_HPO_CLNDPL);
	audio_codec_index_00h |= (left_en << AUDIO_CODEC_SHIFT_HPO_CLPDPL);

	hal_rtl_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h);
}

/**
 *  @brief Control the amplifier of the headphone.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_hpo_amplifier(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_01h;

	audio_codec_index_01h = hal_rtl_audio_si_read(paudio_adapter, 0x01);

	audio_codec_index_01h &= ~(AUDIO_CODEC_BIT_HPO_ENAL);
	audio_codec_index_01h |= (left_en << AUDIO_CODEC_SHIFT_HPO_ENAL);

	hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
}

/**
 *  @brief Control the depop mode of the headphone.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_hpo_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_01h;

	audio_codec_index_01h = hal_rtl_audio_si_read(paudio_adapter, 0x01);

	audio_codec_index_01h &= ~(AUDIO_CODEC_BIT_HPO_ENDPL);
	audio_codec_index_01h |= (left_en << AUDIO_CODEC_SHIFT_HPO_ENDPL);

	hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
}

/**
 *  @brief Control the headphone power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_hpo_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_01h;

	audio_codec_index_01h = hal_rtl_audio_si_read(paudio_adapter, 0x01);

	audio_codec_index_01h &= ~(AUDIO_CODEC_BIT_HPO_L_POW);
	audio_codec_index_01h |= (left_en << AUDIO_CODEC_SHIFT_HPO_L_POW);

	hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
}

/**
 *  @brief Control the depop of the headphone mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is no depop, 1 is depop.
 *
 *  @returns void
 */
void hal_rtl_audio_hpo_mute_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_01h;

	audio_codec_index_01h = hal_rtl_audio_si_read(paudio_adapter, 0x01);

	audio_codec_index_01h &= ~(AUDIO_CODEC_BIT_HPO_MDPL);
	audio_codec_index_01h |= (left_en << AUDIO_CODEC_SHIFT_HPO_MDPL);

	hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
}

/**
 *  @brief Control the depop of the headphone op.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is no depop, 1 is depop.
 *
 *  @returns void
 */
void hal_rtl_audio_hpo_op_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_01h;

	audio_codec_index_01h = hal_rtl_audio_si_read(paudio_adapter, 0x01);

	audio_codec_index_01h &= ~(AUDIO_CODEC_BIT_HPO_OPNDPL | AUDIO_CODEC_BIT_HPO_OPPDPL);
	audio_codec_index_01h |= (left_en << AUDIO_CODEC_SHIFT_HPO_OPNDPL);
	audio_codec_index_01h |= (left_en << AUDIO_CODEC_SHIFT_HPO_OPPDPL);

	hal_rtl_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h);
}

/**
 *  @brief Control the headphone mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_mute_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_hpo_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en)
{
	u16 audio_codec_index_02h;

	audio_codec_index_02h = hal_rtl_audio_si_read(paudio_adapter, 0x02);

	audio_codec_index_02h &= ~(AUDIO_CODEC_MASK_HPO_ML);

	if (left_mute_en == 1) {
		audio_codec_index_02h |= (0x3 << AUDIO_CODEC_SHIFT_HPO_ML);
	} else {
		audio_codec_index_02h |= (0x2 << AUDIO_CODEC_SHIFT_HPO_ML);
	}

	hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);
}

/**
 *  @brief Control the headphone differential mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_hpo_differential_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_02h;

	audio_codec_index_02h = hal_rtl_audio_si_read(paudio_adapter, 0x02);

	if (left_en == 1) {
		audio_codec_index_02h &= ~(AUDIO_CODEC_BIT_HPO_SEL);
	} else {
		audio_codec_index_02h |= AUDIO_CODEC_BIT_HPO_SEL;
	}

	hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);
}

/**
 *  @brief Control the mic bias.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] bias_en Enable control: 0 is disable, 1 is enable.
 *  @param[in] bias_voltage Select the bias voltage.
 *                      -00: 0.9AVDD. (default)
 *                      -01: 0.86AVDD.
 *                      -10: 0.75AVDD.
 *                      -11: reserved.
 *
 *  @returns void
 */
void hal_rtl_audio_mic_bias(hal_audio_adapter_t *paudio_adapter, BOOL bias_en, audio_bias_voltage_t bias_voltage)
{
	u16 audio_codec_index_02h;

	audio_codec_index_02h = hal_rtl_audio_si_read(paudio_adapter, 0x02);

	audio_codec_index_02h &= ~(AUDIO_CODEC_BIT_MICBIAS_POW);
	audio_codec_index_02h |= (bias_en << AUDIO_CODEC_SHIFT_MICBIAS_POW);

	audio_codec_index_02h &= ~(AUDIO_CODEC_MASK_MICBIAS_VSET);
	audio_codec_index_02h |= (bias_voltage << AUDIO_CODEC_SHIFT_MICBIAS_VSET);

	hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);
}

/**
 *  @brief Control the mic differential mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_mic_differential_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	u16 audio_codec_index_02h;

	audio_codec_index_02h = hal_rtl_audio_si_read(paudio_adapter, 0x02);

	audio_codec_index_02h &= ~(AUDIO_CODEC_BIT_MICBST_ENDFL);
	audio_codec_index_02h |= (left_en << AUDIO_CODEC_SHIFT_MICBST_ENDFL);

	hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);
}

/**
 *  @brief Control the mic mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_mute_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_mic_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en)
{
	u16 audio_codec_index_03h;

	audio_codec_index_03h = hal_rtl_audio_si_read(paudio_adapter, 0x03);

	audio_codec_index_03h &= ~(0x1 << AUDIO_CODEC_SHIFT_MICBST_MUTE_L);

	if (left_mute_en == 1) {
		audio_codec_index_03h |= (0x1 << AUDIO_CODEC_SHIFT_MICBST_MUTE_L);
	}

	hal_rtl_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h);
}

/**
 *  @brief Control the line-in mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_mute_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_audio_line_in_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en)
{
	u16 audio_codec_index_03h;

	audio_codec_index_03h = hal_rtl_audio_si_read(paudio_adapter, 0x03);

	audio_codec_index_03h &= ~(0x2 << AUDIO_CODEC_SHIFT_MICBST_MUTE_L);

	if (left_mute_en == 1) {
		audio_codec_index_03h |= (0x2 << AUDIO_CODEC_SHIFT_MICBST_MUTE_L);
	}

	hal_rtl_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h);
}

/**
 *  @brief Control the mic power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] left_gain Select the left channel gain.
 *                      -00: 0dB. (default)
 *                      -01: 20dB.
 *                      -10: 30dB.
 *                      -11: 40dB.
 *
 *  @returns void
 */
void hal_rtl_audio_mic_boost(hal_audio_adapter_t *paudio_adapter, BOOL left_en, audio_mic_gain_t left_gain)
{
	u16 audio_codec_index_03h;

	audio_codec_index_03h = hal_rtl_audio_si_read(paudio_adapter, 0x03);

	audio_codec_index_03h &= ~(AUDIO_CODEC_BIT_MICBST_POW);
	audio_codec_index_03h |= (left_en << AUDIO_CODEC_SHIFT_MICBST_POW);

	audio_codec_index_03h &= ~(AUDIO_CODEC_MASK_MICBST_GSELL);
	audio_codec_index_03h |= (left_gain << AUDIO_CODEC_SHIFT_MICBST_GSELL);

	hal_rtl_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h);
}

/**
 *  @brief Control the vref voltage.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] vref_en Enable control: 0 is disable, 1 is enable.
 *  @param[in] vref_voltage Select the bias voltage.
 *                      -00: 0.52VDD.
 *                      -01: 0.51VDD.
 *                      -10: 0.50VDD. (default)
 *                      -11: 0.49VDD.
 *
 *  @returns void
 */
void hal_rtl_audio_vref(hal_audio_adapter_t *paudio_adapter, BOOL vref_en, audio_vref_voltage_t vref_voltage)
{
	u16 audio_codec_index_02h;
	u16 audio_codec_index_03h;

	audio_codec_index_02h = hal_rtl_audio_si_read(paudio_adapter, 0x02);
	audio_codec_index_03h = hal_rtl_audio_si_read(paudio_adapter, 0x03);

	audio_codec_index_02h &= ~(AUDIO_CODEC_BIT_VREF_POW);
	audio_codec_index_02h |= (vref_en << AUDIO_CODEC_SHIFT_VREF_POW);

	audio_codec_index_03h &= ~(AUDIO_CODEC_MASK_VREF_VREFSEL);
	audio_codec_index_03h |= (vref_voltage << AUDIO_CODEC_SHIFT_VREF_VREFSEL);

	hal_rtl_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h);
	hal_rtl_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h);
}

/**
 *  @brief Control audio ip tcon
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_audio_ip_tcon(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	u16 audio_codec_index_1bh;

	audio_codec_index_1bh = hal_rtl_audio_si_read(paudio_adapter, 0x1b);

	audio_codec_index_1bh &= ~(AUDIO_CODEC_BIT_AUDIO_IP_TCON_EN);
	audio_codec_index_1bh |= (en << AUDIO_CODEC_SHIFT_AUDIO_IP_TCON_EN);

	hal_rtl_audio_si_write(paudio_adapter, 0x1b, audio_codec_index_1bh);
}

/**
 *  @brief Initialize the sport and  DMA of the audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_init(hal_audio_adapter_t *paudio_adapter)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	//Reset
	hal_rtl_sport_init(psport_adapter);
	hal_rtl_sport_reset_tx_fifo(psport_adapter);
	hal_rtl_sport_reset_rx_fifo(psport_adapter);
	hal_rtl_sport_dma_reset(psport_adapter);
	hal_rtl_sport_clean_tx_page_own(psport_adapter);
	hal_rtl_sport_clean_rx_page_own(psport_adapter);

	//Init setting
	hal_rtl_sport_set_master(psport_adapter, SPORT_MASTER_MODE);
	hal_rtl_sport_set_loopback(psport_adapter, DISABLE); //ENABLE, DISABLE
	hal_rtl_sport_mode(psport_adapter, SPORT_DMA_MODE);
	hal_rtl_sport_tx_ch(psport_adapter, SPORT_L_R);
	hal_rtl_sport_rx_ch(psport_adapter, SPORT_L_R);
	hal_rtl_sport_format(psport_adapter, SPORT_I2S);
	hal_rtl_sport_rx_same_format(psport_adapter, ENABLE);
	hal_rtl_sport_rx_format(psport_adapter, SPORT_I2S);

	hal_rtl_sport_tx_data_dir(psport_adapter, SPORT_MSB_FIRST, SPORT_MSB_FIRST);
	hal_rtl_sport_rx_data_dir(psport_adapter, SPORT_MSB_FIRST, SPORT_MSB_FIRST);
	hal_rtl_sport_tx_lr_swap(psport_adapter, DISABLE, DISABLE);
	hal_rtl_sport_rx_lr_swap(psport_adapter, DISABLE, DISABLE);

	hal_rtl_sport_tx_byte_swap(psport_adapter, DISABLE, DISABLE);
	hal_rtl_sport_rx_byte_swap(psport_adapter, DISABLE, DISABLE);
	hal_rtl_sport_bclk_inverse(psport_adapter, DISABLE);

	hal_rtl_sport_set_mclk(psport_adapter, SPORT_SRC_DIV_1, ENABLE);

	hal_rtl_sport_rx_same_mono_stereo(psport_adapter, DISABLE);

	//IRQ
	hal_rtl_sport_tx_fifo_th(psport_adapter, 16);
	hal_rtl_sport_rx_fifo_th(psport_adapter, 16);
	hal_rtl_sport_autoload_dma_burst(psport_adapter);

	//Enable SPORT TX and RX
	hal_rtl_sport_rx_start(psport_adapter, ENABLE);
	hal_rtl_sport_tx_start(psport_adapter, ENABLE);

}

/**
 *  @brief De-initialize of the audio SPORT hardware and turn off the audio SPORT.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_deinit(hal_audio_adapter_t *paudio_adapter)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_deinit(psport_adapter);
}

/**
 *  @brief Set the tx SPORT parameter of the audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] ch The audio channel.
 *  @param[in] word_len The audio word length.
 *  @param[in] audio_sample_rate  Sample rate.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_tx_params(hal_audio_adapter_t *paudio_adapter, audio_ch_t ch, audio_word_len_t word_len, audio_sample_rate_t audio_sample_rate)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;
	hal_sport_tx_params_t tx_params;
	sport_cl_t cl_t;
	sport_dl_t dl_t;

	tx_params.sport_tx_ch = ch;

	cl_t = SPORT_CL_32BIT;
	dl_t = SPORT_DL_16BIT;

	if (word_len == AUDIO_WL_24) {
		dl_t = SPORT_DL_24BIT;
	}

	tx_params.sport_tx_cl = cl_t;
	tx_params.sport_tx0_dl = dl_t;
	tx_params.sport_tx1_dl = dl_t;
	tx_params.sport_tx_rate = audio_sample_rate;
	hal_rtl_sport_tx_params(psport_adapter, &tx_params);
}

/**
 *  @brief Set the rx SPORT parameter of the audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] ch The audio channel.
 *  @param[in] word_len The audio word length.
 *  @param[in] audio_sample_rate  Sample rate.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_rx_params(hal_audio_adapter_t *paudio_adapter, audio_ch_t ch, audio_word_len_t word_len, audio_sample_rate_t audio_sample_rate)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;
	hal_sport_rx_params_t rx_params;
	sport_cl_t cl_t;
	sport_dl_t dl_t;

	rx_params.sport_rx_ch = ch;

	cl_t = SPORT_CL_32BIT;
	dl_t = SPORT_DL_16BIT;

	if (word_len == AUDIO_WL_24) {
		dl_t = SPORT_DL_24BIT;
	}

	rx_params.sport_rx_cl = cl_t;
	rx_params.sport_rx0_dl = dl_t;
	rx_params.sport_rx1_dl = dl_t;
	rx_params.sport_rx_rate = audio_sample_rate;
	hal_rtl_sport_rx_params(psport_adapter, &rx_params);
}

/**
 *  @brief Initialize the buffer of the audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dma_params The AUDIO adapter. Set tx0_buf pointer, rx0_buf pointer, page_num and page_size.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_buf(hal_audio_adapter_t *paudio_adapter, hal_audio_dma_params_t dma_params)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;
	hal_sport_buf_params_t buf_params;
	hal_sport_page_intr_t page_intr;

	page_intr.sport_p0ok = 0;
	page_intr.sport_p1ok = 0;
	page_intr.sport_p2ok = 0;
	page_intr.sport_p3ok = 0;
	page_intr.sport_p0unava = 0;
	page_intr.sport_p1unava = 0;
	page_intr.sport_p2unava = 0;
	page_intr.sport_p3unava = 0;
	page_intr.sport_p0err = 0;
	page_intr.sport_p1err = 0;
	page_intr.sport_p2err = 0;
	page_intr.sport_p3err = 0;
	page_intr.sport_fifo_err = 0;
	hal_rtl_sport_set_dma_intr(psport_adapter, SPORT_TX1, &page_intr);
	hal_rtl_sport_set_dma_intr(psport_adapter, SPORT_RX1, &page_intr);

	buf_params.tx0_buf = (u8 *)dma_params.tx_buf;
	buf_params.rx0_buf = (u8 *)dma_params.rx_buf;
	buf_params.tx1_buf = (u8 *)NULL;
	buf_params.rx1_buf = (u8 *)NULL;
	if ((dma_params.page_num < 5) && (dma_params.page_num > 1)) {
		buf_params.page_num = dma_params.page_num;

		if (dma_params.page_num == 4) {
			page_intr.sport_p0ok = 1;
			page_intr.sport_p1ok = 1;
			page_intr.sport_p2ok = 1;
			page_intr.sport_p3ok = 1;
			page_intr.sport_p0unava = 1;
			page_intr.sport_p1unava = 1;
			page_intr.sport_p2unava = 1;
			page_intr.sport_p3unava = 1;
			page_intr.sport_p0err = 1;
			page_intr.sport_p1err = 1;
			page_intr.sport_p2err = 1;
			page_intr.sport_p3err = 1;
		} else if (dma_params.page_num == 3) {
			page_intr.sport_p0ok = 1;
			page_intr.sport_p1ok = 1;
			page_intr.sport_p2ok = 1;
			page_intr.sport_p0unava = 1;
			page_intr.sport_p1unava = 1;
			page_intr.sport_p2unava = 1;
			page_intr.sport_p0err = 1;
			page_intr.sport_p1err = 1;
			page_intr.sport_p2err = 1;
		} else if (dma_params.page_num == 2) {
			page_intr.sport_p0ok = 1;
			page_intr.sport_p1ok = 1;
			page_intr.sport_p0unava = 1;
			page_intr.sport_p1unava = 1;
			page_intr.sport_p0err = 1;
			page_intr.sport_p1err = 1;
		}

		page_intr.sport_fifo_err = 1;
		hal_rtl_sport_set_dma_intr(psport_adapter, SPORT_TX0, &page_intr);
		hal_rtl_sport_set_dma_intr(psport_adapter, SPORT_RX0, &page_intr);
		buf_params.page_size = dma_params.page_size;
		hal_rtl_sport_dma_buffer(psport_adapter, &buf_params);
	} else {
		DBG_AUDIO_ERR(" hal_rtl_audio_dma_params, dma_params.page_num is invalid\r\n");
	}

}

/**
 *  @brief Register the audio SPORT TX IRQ callback function and argument.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_rtl_audio_sport_tx_cb_handler(hal_audio_adapter_t *paudio_adapter, audio_sport_irq_cb_t callback, u32 *arg)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_tx0_dma_cb_handler(psport_adapter, (sport_irq_user_cb_t)callback, arg);
}

/**
 *  @brief Register the audio SPORT RX IRQ callback function and argument.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_rtl_audio_sport_rx_cb_handler(hal_audio_adapter_t *paudio_adapter, audio_sport_irq_cb_t callback, u32 *arg)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_rx0_dma_cb_handler(psport_adapter, (sport_irq_user_cb_t)callback, arg);
}

/**
 *  @brief Get the current tx0 page address.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns The address of current tx0 page or NULL.
 */
int *hal_rtl_audio_sport_get_tx_page(hal_audio_adapter_t *paudio_adapter)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	return hal_rtl_sport_get_tx0_page(psport_adapter);
}

/**
 *  @brief Sets current tx page own by audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] pbuf  Set tx buffer adderss.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_tx_page_send(hal_audio_adapter_t *paudio_adapter, u32 *pbuf)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_tx0_page_send(psport_adapter, pbuf);
}

/**
 *  @brief Sets current rx page own by audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
u32 hal_rtl_audio_sport_rx_page_recv(hal_audio_adapter_t *paudio_adapter)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	return hal_rtl_sport_rx0_page_recv(psport_adapter);
}

/**
 *  @brief Start the audio tx DMA.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_tx_dma_start(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_tx_dma_start(psport_adapter, en);
}

/**
 *  @brief Start the audio rx DMA.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_rx_dma_start(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_rx_dma_start(psport_adapter, en);
}

/**
 *  @brief Get the audio tx DMA status.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
u32 hal_rtl_audio_sport_get_tx_dma_start_sta(hal_audio_adapter_t *paudio_adapter)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	return hal_rtl_sport_get_tx_dma_start_sta(psport_adapter);
}

/**
 *  @brief Get the audio rx DMA status.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
u32 hal_rtl_audio_sport_get_rx_dma_start_sta(hal_audio_adapter_t *paudio_adapter)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	return hal_rtl_sport_get_rx_dma_start_sta(psport_adapter);
}

/**
 *  @brief Swap the byte of tx data.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_tx_byte_swap(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_tx_byte_swap(psport_adapter, en, 0);
}

/**
 *  @brief Swap the byte of tx data.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_rx_byte_swap(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_rx_byte_swap(psport_adapter, en, 0);
}

/**
 *  @brief Start the audio tx SPORT.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_tx_start(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_tx_start(psport_adapter, en);
}

/**
 *  @brief Start the audio rx SPORT.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_rx_start(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_rx_start(psport_adapter, en);
}

/**
 *  @brief Init the tx and rx different rate.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_audio_sport_diff_rate_init(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_sport_adapter_t *psport_adapter = &paudio_adapter->sport_adapter;

	hal_rtl_sport_format(psport_adapter, SPORT_I2S);
	hal_rtl_sport_rx_format(psport_adapter, SPORT_I2S);

	if (en == ENABLE) {
		hal_rtl_sport_fixed_bclk(psport_adapter, ENABLE, SPORT_BCLK_1D4);
		hal_rtl_sport_rx_same_format(psport_adapter, DISABLE);
		hal_rtl_sport_rx_same_fs(psport_adapter, DISABLE);

	} else {
		hal_rtl_sport_fixed_bclk(psport_adapter, DISABLE, SPORT_BCLK_1D4);
		hal_rtl_sport_rx_same_format(psport_adapter, ENABLE);
		hal_rtl_sport_rx_same_fs(psport_adapter, ENABLE);
	}
}

/**
 *  @brief Set EQ register
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] start_adr start address.
 *  @param[in] data value.
 *
 *  @returns void
 */
void hal_rtl_set_eq_reg(hal_audio_adapter_t *paudio_adapter, u32 start_adr, u32 data)
{
	u16 audio_codec_index_l;
	u16 audio_codec_index_h;

	audio_codec_index_l = hal_rtl_audio_si_read(paudio_adapter, start_adr);
	audio_codec_index_l &= ~(AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_1_BIT15TO0);
	audio_codec_index_l |= ((data & 0xFFFF) << AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_1_BIT15TO0);
	hal_rtl_audio_si_write(paudio_adapter, start_adr, audio_codec_index_l);

	audio_codec_index_h = hal_rtl_audio_si_read(paudio_adapter, (start_adr + 1));
	audio_codec_index_h &= ~(AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_1_BIT28TO16);
	audio_codec_index_h |= (((data >> 16) & 0x1FFF) << AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_1_BIT28TO16);
	hal_rtl_audio_si_write(paudio_adapter, (start_adr + 1), audio_codec_index_h);

}

/**
 *  @brief Set EQ parameter
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Enable or Disable.
 *  @param[in] first_gp_adr First group address.
 *  @param[in] peq_params EQ parameter.
 *
 *  @returns void
 */
void hal_rtl_set_eq_para(hal_audio_adapter_t *paudio_adapter, BOOL en, u32 first_gp_adr, hal_eq_params_t *peq_params)
{
	u16 audio_codec_index_en;

	//disable the EQ before setting
	audio_codec_index_en = hal_rtl_audio_si_read(paudio_adapter, (first_gp_adr + 9));
	audio_codec_index_en &= ~(AUDIO_CODEC_BIT_ADC_L_BIQUAD_EN_1);
	hal_rtl_audio_si_write(paudio_adapter, (first_gp_adr + 9), audio_codec_index_en);

	//h0
	hal_rtl_set_eq_reg(paudio_adapter, first_gp_adr, peq_params->h0);
	//b1
	hal_rtl_set_eq_reg(paudio_adapter, (first_gp_adr + 2), peq_params->b1);
	//b2
	hal_rtl_set_eq_reg(paudio_adapter, (first_gp_adr + 4), peq_params->b2);
	//a1
	hal_rtl_set_eq_reg(paudio_adapter, (first_gp_adr + 6), peq_params->a1);
	//a2
	hal_rtl_set_eq_reg(paudio_adapter, (first_gp_adr + 8), peq_params->a2);

	audio_codec_index_en = hal_rtl_audio_si_read(paudio_adapter, (first_gp_adr + 9));
	audio_codec_index_en &= ~(AUDIO_CODEC_BIT_ADC_L_BIQUAD_EN_1);
	hal_rtl_audio_si_write(paudio_adapter, (first_gp_adr + 9), audio_codec_index_en);

	if (en == ENABLE) {
		audio_codec_index_en = hal_rtl_audio_si_read(paudio_adapter, (first_gp_adr + 9));
		audio_codec_index_en |= (1 << AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_EN_1);
		hal_rtl_audio_si_write(paudio_adapter, (first_gp_adr + 9), audio_codec_index_en);
	}

}

/**
 *  @brief Set input 5-band equalizers for the left channel
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_eq Select the EQ number.
 *  @param[in] en Enable or Disable.
 *  @param[in] peq_params EQ parameter.
 *
 *  @returns void
 */
void hal_rtl_audio_input_l_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params)
{
	u16 audio_codec_index_en;

	if (audio_eq == AUDIO_EQ_0) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0x91, peq_params);
	} else if (audio_eq == AUDIO_EQ_1) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0x9B, peq_params);
	} else if (audio_eq == AUDIO_EQ_2) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0xA5, peq_params);
	} else if (audio_eq == AUDIO_EQ_3) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0xAF, peq_params);
	} else if (audio_eq == AUDIO_EQ_4) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0xB9, peq_params);
	}
}

/**
 *  @brief Set input 5-band equalizers for the right channel
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_eq Select the EQ number.
 *  @param[in] en Enable or Disable.
 *  @param[in] peq_params EQ parameter.
 *
 *  @returns void
 */
void hal_rtl_audio_input_r_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params)
{
	u16 audio_codec_index_en;

	if (audio_eq == AUDIO_EQ_0) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0xC4, peq_params);
	} else if (audio_eq == AUDIO_EQ_1) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0xCE, peq_params);
	} else if (audio_eq == AUDIO_EQ_2) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0xD8, peq_params);
	} else if (audio_eq == AUDIO_EQ_3) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0xE2, peq_params);
	} else if (audio_eq == AUDIO_EQ_4) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0xEC, peq_params);
	}
}

/**
 *  @brief Set output 5-band equalizers for the left channel
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_eq Select the EQ number.
 *  @param[in] en Enable or Disable.
 *  @param[in] peq_params EQ parameter.
 *
 *  @returns void
 */
void hal_rtl_audio_output_l_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params)
{
	u16 audio_codec_index_en;

	if (audio_eq == AUDIO_EQ_0) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0x2B, peq_params);
	} else if (audio_eq == AUDIO_EQ_1) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0x35, peq_params);
	} else if (audio_eq == AUDIO_EQ_2) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0x3F, peq_params);
	} else if (audio_eq == AUDIO_EQ_3) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0x49, peq_params);
	} else if (audio_eq == AUDIO_EQ_4) {
		hal_rtl_set_eq_para(paudio_adapter, en, 0x53, peq_params);
	}
}

