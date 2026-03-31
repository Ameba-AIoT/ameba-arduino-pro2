/**************************************************************************//**
 * @file     hal_audio.c
 * @brief    This AUDIO HAL API functions.
 *
 * @version  V1.00
 * @date     2016-09-19
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

#include "hal_cache.h"
//#include "hal_pinmux.h"
#include "hal_audio.h"

#if CONFIG_AUDIO_EN

/**
 * @addtogroup hs_hal_audio AUDIO
 * @{
 */

/**
 *  @brief Initialize the AUDIO hardware and turn on the AUDIO.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_codec_power Select audio codec LDO power. 0: 1.8V, 1: 2.8V.
 *
 *  @returns void
 */
void hal_audio_init(hal_audio_adapter_t *paudio_adapter, audio_codec_power_t audio_codec_power)
{
	hal_audio_stubs.hal_audio_init(paudio_adapter, audio_codec_power);
}

/**
 *  @brief De-initialize of the AUDIO hardware and turn off the AUDIO.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_audio_deinit(hal_audio_adapter_t *paudio_adapter)
{
	hal_audio_stubs.hal_audio_deinit(paudio_adapter);
}

/**
 *  @brief Control the communication interface of the audio codec for reading or writing the register.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_si_init(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_si_init(paudio_adapter, en);
}

/**
 *  @brief Read the register of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] address  The register address.
 *
 *  @returns The register value.
 */
u16 hal_audio_si_read(hal_audio_adapter_t *paudio_adapter, u8 address)
{
	return hal_audio_stubs.hal_audio_si_read(paudio_adapter, address);
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
HAL_Status hal_audio_si_write(hal_audio_adapter_t *paudio_adapter, u8 address, u16 data)
{
	return hal_audio_stubs.hal_audio_si_write(paudio_adapter, address, data);
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
void hal_audio_ldo_tune(u8 sel)
{
	hal_audio_stubs.hal_audio_ldo_tune(sel);
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
void hal_audio_dev_ctrl(BOOL en)
{
	hal_audio_stubs.hal_audio_dev_ctrl(en);
}

/**
 *  @brief Set the sample rate of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_sample_rate  Sample rate.
 *
 *  @returns void
 */
void hal_audio_rate(hal_audio_adapter_t *paudio_adapter, audio_sample_rate_t audio_tx_rate, audio_sample_rate_t audio_rx_rate)
{
	hal_audio_stubs.hal_audio_rate(paudio_adapter, audio_tx_rate, audio_rx_rate);
}

/**
 *  @brief Set the format of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_format  Select the interface format.
 *
 *  @returns void
 */
void hal_audio_format(hal_audio_adapter_t *paudio_adapter, audio_format_t audio_format)
{
	hal_audio_stubs.hal_audio_format(paudio_adapter, audio_format);
}

/**
 *  @brief Set the data length of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_word_len  The data length.
 *
 *  @returns void
 */
void hal_audio_length(hal_audio_adapter_t *paudio_adapter, audio_word_len_t audio_tx_word_len, audio_word_len_t audio_rx_word_len)
{
	hal_audio_stubs.hal_audio_length(paudio_adapter, audio_tx_word_len, audio_rx_word_len);
}

/**
 *  @brief Invert the SCK of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sck_inv_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_sck_inv(hal_audio_adapter_t *paudio_adapter, BOOL sck_inv_en)
{
	hal_audio_stubs.hal_audio_sck_inv(paudio_adapter, sck_inv_en);
}

/**
 *  @brief Control the interface loopback mode of the audio codec. This direction is tx to rx.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sck_inv_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en)
{
	hal_audio_stubs.hal_audio_loopback(paudio_adapter, loopback_en);
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
void hal_audio_tx_ch(hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch)
{
	hal_audio_stubs.hal_audio_tx_ch(paudio_adapter, audio_sel_ch);
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
void hal_audio_rx_ch(hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch)
{
	hal_audio_stubs.hal_audio_rx_ch(paudio_adapter, audio_sel_ch);
}

/**
 *  @brief Reset the the digital IP of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_digital_rst(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_digital_rst(paudio_adapter, en);
}

/**
 *  @brief Control the DAC & ADC loopback. This direction is tx to rx.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] loopback_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_daad_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en)
{
	hal_audio_stubs.hal_audio_daad_loopback(paudio_adapter, loopback_en);
}

/**
 *  @brief Control the DAC & ADC loopback. This direction is rx to tx.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] loopback_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adda_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en)
{
	hal_audio_stubs.hal_audio_adda_loopback(paudio_adapter, loopback_en);
}

/**
 *  @brief Control the ASRC of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] asrc_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_asrc(hal_audio_adapter_t *paudio_adapter, BOOL asrc_en)
{
	hal_audio_stubs.hal_audio_asrc(paudio_adapter, asrc_en);
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
void hal_audio_dac_mixer(hal_audio_adapter_t *paudio_adapter, BOOL dac_l_mute_en)
{
	hal_audio_stubs.hal_audio_dac_mixer(paudio_adapter, dac_l_mute_en);
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
void hal_audio_adc_amic_mixer(hal_audio_adapter_t *paudio_adapter, BOOL amic_l_mute_en, BOOL amic_r_mute_en)
{
	hal_audio_stubs.hal_audio_adc_amic_mixer(paudio_adapter, amic_l_mute_en, amic_r_mute_en);
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
void hal_audio_adc_dmic_mixer(hal_audio_adapter_t *paudio_adapter, BOOL dmic_l_mute_en, BOOL dmic_r_mute_en)
{
	hal_audio_stubs.hal_audio_adc_dmic_mixer(paudio_adapter, dmic_l_mute_en, dmic_r_mute_en);
}

/**
 *  @brief Control the sidetone mixer.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sidetone_l_mute_en  Mute control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_sidetone_mixer(hal_audio_adapter_t *paudio_adapter, BOOL sidetone_l_mute_en)
{
	hal_audio_stubs.hal_audio_sidetone_mixer(paudio_adapter, sidetone_l_mute_en);
}

/**
 *  @brief Control the DAC clock.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dac_l_clk_en  Control the left channel clock: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dac_clk(hal_audio_adapter_t *paudio_adapter, BOOL dac_l_clk_en)
{
	hal_audio_stubs.hal_audio_dac_clk(paudio_adapter, dac_l_clk_en);
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
void hal_audio_adc_clk(hal_audio_adapter_t *paudio_adapter, BOOL adc_l_clk_en, BOOL adc_r_clk_en)
{
	hal_audio_stubs.hal_audio_adc_clk(paudio_adapter, adc_l_clk_en, adc_r_clk_en);
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
void hal_audio_dmic_clk(hal_audio_adapter_t *paudio_adapter, BOOL dimc_l_clk_en, BOOL dimc_r_clk_en)
{
	hal_audio_stubs.hal_audio_dmic_clk(paudio_adapter, dimc_l_clk_en, dimc_r_clk_en);
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
void hal_audio_dmic_input_clk(hal_audio_adapter_t *paudio_adapter, audio_dmic_input_clk_t dmic_input_clk)
{
	hal_audio_stubs.hal_audio_dmic_input_clk(paudio_adapter, dmic_input_clk);
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
void hal_audio_dmic_latch(hal_audio_adapter_t *paudio_adapter, audio_dmic_latch_t dmic_l_latch, audio_dmic_latch_t dmic_r_latch)
{
	hal_audio_stubs.hal_audio_dmic_latch(paudio_adapter, dmic_l_latch, dmic_r_latch);
}

/**
 *  @brief Control the D-MIC gain of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_boost  Set the D-MIC boost.
 *
 *  @returns void
 */
void hal_audio_dmic_l_gain(hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain)
{
	hal_audio_stubs.hal_audio_dmic_l_gain(paudio_adapter, dmic_gain);
}

/**
 *  @brief Control the D-MIC gain of the right channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_boost  Set the D-MIC boost.
 *
 *  @returns void
 */
void hal_audio_dmic_r_gain(hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain)
{
	hal_audio_stubs.hal_audio_dmic_r_gain(paudio_adapter, dmic_gain);
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
void hal_audio_dmic_l_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
	hal_audio_stubs.hal_audio_dmic_l_src(paudio_adapter, lp_1st_en, lp_2st_en, src_freq);
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
void hal_audio_dmic_r_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
	hal_audio_stubs.hal_audio_dmic_r_src(paudio_adapter, lp_1st_en, lp_2st_en, src_freq);
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
void hal_audio_amic_l_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
	hal_audio_stubs.hal_audio_amic_l_src(paudio_adapter, lp_1st_en, lp_2st_en, src_freq);
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
void hal_audio_amic_r_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
	hal_audio_stubs.hal_audio_amic_r_src(paudio_adapter, lp_1st_en, lp_2st_en, src_freq);
}

/**
 *  @brief Control the ADC high pass filter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Control the HPF: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adc_l_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_fc_t audio_hpf_fc)
{
	hal_audio_stubs.hal_audio_adc_l_hpf(paudio_adapter, en, audio_hpf_fc);
}

/**
 *  @brief Control the ADC high pass filter of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Control the HPF: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adc_r_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_fc_t audio_hpf_fc)
{
	hal_audio_stubs.hal_audio_adc_r_hpf(paudio_adapter, en, audio_hpf_fc);
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
void hal_audio_adc_l_dvol(hal_audio_adapter_t *paudio_adapter, u8 step)
{
	hal_audio_stubs.hal_audio_adc_l_dvol(paudio_adapter, step);
}

/**
 *  @brief Control the ADC digital mute of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] mute_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adc_l_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en)
{
	hal_audio_stubs.hal_audio_adc_l_dmute(paudio_adapter, mute_en);
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
void hal_audio_adc_r_dvol(hal_audio_adapter_t *paudio_adapter, u8 step)
{
	hal_audio_stubs.hal_audio_adc_r_dvol(paudio_adapter, step);
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
void hal_audio_adc_r_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en)
{
	hal_audio_stubs.hal_audio_adc_r_dmute(paudio_adapter, mute_en);
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
void hal_audio_adc_l_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout)
{
	hal_audio_stubs.hal_audio_adc_l_zdet(paudio_adapter, zdet, adc_zdet_tout);
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
void hal_audio_adc_r_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout)
{
	hal_audio_stubs.hal_audio_adc_r_zdet(paudio_adapter, zdet, adc_zdet_tout);
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
void hal_audio_adc_l_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time)
{
	hal_audio_stubs.hal_audio_adc_l_silence(paudio_adapter, silence_en, level, debounce_time);
}

/**
 *  @brief Get the ADC silence detection result of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The silence is not detected.
 *  @return     1:  The silence is detected.
 */
u8 hal_audio_adc_l_silence_result(hal_audio_adapter_t *paudio_adapter)
{
	return hal_audio_stubs.hal_audio_adc_l_silence_result(paudio_adapter);
}

/**
 *  @brief Get the ADC silence detection status of the right channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The detection is resting.
 *  @return     1:  The detection is working.
 */
u8 hal_audio_adc_l_silence_status(hal_audio_adapter_t *paudio_adapter)
{
	return hal_audio_stubs.hal_audio_adc_l_silence_status(paudio_adapter);
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
void hal_audio_adc_r_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time)
{
	hal_audio_stubs.hal_audio_adc_r_silence(paudio_adapter, silence_en, level, debounce_time);
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
u8 hal_audio_adc_r_silence_result(hal_audio_adapter_t *paudio_adapter)
{
	return hal_audio_stubs.hal_audio_adc_r_silence_result(paudio_adapter);
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
u8 hal_audio_adc_r_silence_status(hal_audio_adapter_t *paudio_adapter)
{
	return hal_audio_stubs.hal_audio_adc_r_silence_status(paudio_adapter);
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
void hal_audio_dac_dither(hal_audio_adapter_t *paudio_adapter, audio_dac_dither_t dac_l_dither)
{
	hal_audio_stubs.hal_audio_dac_dither(paudio_adapter, dac_l_dither);
}

/**
 *  @brief Control the DAC high pass filter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Control the HPF: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dac_l_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_dac_l_hpf(paudio_adapter, en);
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

void hal_audio_dac_l_dvol(hal_audio_adapter_t *paudio_adapter, u8 step)

{
	hal_audio_stubs.hal_audio_dac_l_dvol(paudio_adapter, step);
}

/**
 *  @brief Control the DAC digital mute of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] mute_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dac_l_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en)
{
	hal_audio_stubs.hal_audio_dac_l_dmute(paudio_adapter, mute_en);
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
void hal_audio_dac_l_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_dac_zdet_tout_t adc_zdet_tout)
{
	hal_audio_stubs.hal_audio_dac_l_zdet(paudio_adapter, zdet, adc_zdet_tout);
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
void hal_audio_dac_l_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time)
{
	hal_audio_stubs.hal_audio_dac_l_silence(paudio_adapter, silence_en, level, debounce_time);
}

/**
 *  @brief Get the DAC silence detection result of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The silence is not detected.
 *  @return     1:  The silence is detected.
 */
u8 hal_audio_dac_l_silence_result(hal_audio_adapter_t *paudio_adapter)
{
	return hal_audio_stubs.hal_audio_dac_l_silence_result(paudio_adapter);
}

/**
 *  @brief Get the DAC silence detection status of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The detection is resting.
 *  @return     1:  The detection is working.
 */
u8 hal_audio_dac_l_silence_status(hal_audio_adapter_t *paudio_adapter)
{
	return hal_audio_stubs.hal_audio_dac_l_silence_status(paudio_adapter);
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
void hal_audio_l_sidetone_hpf(hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf)
{
	hal_audio_stubs.hal_audio_l_sidetone_hpf(paudio_adapter, hpf_en, sidetone_hpf);
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
void hal_audio_r_sidetone_hpf(hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf)
{
	hal_audio_stubs.hal_audio_r_sidetone_hpf(paudio_adapter, hpf_en, sidetone_hpf);
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
void hal_audio_l_sidetone_vol(hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost)
{
	hal_audio_stubs.hal_audio_l_sidetone_vol(paudio_adapter, sidetone_vol, sidetone_boost);
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
void hal_audio_r_sidetone_vol(hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost)
{
	hal_audio_stubs.hal_audio_r_sidetone_vol(paudio_adapter, sidetone_vol, sidetone_boost);
}

/**
 *  @brief Control the power of the ADC and DAC clock.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_ad_da_clk_power(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_ad_da_clk_power(paudio_adapter, en);
}

/**
 *  @brief Control the DAC power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dac_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_dac_power(paudio_adapter, left_en);
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
void hal_audio_adc_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_adc_power(paudio_adapter, left_en);
}

/**
 *  @brief Control the output power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_output_mode_t Select the output mode.
 *
 *  @returns void
 */
void hal_audio_output_power(hal_audio_adapter_t *paudio_adapter, audio_output_mode_t output_mode)
{
	hal_audio_stubs.hal_audio_output_power(paudio_adapter, output_mode);
}

/**
 *  @brief Control the input power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_input_mode_t Select the input mode.
 *
 *  @returns void
 */
void hal_audio_input_power(hal_audio_adapter_t *paudio_adapter, audio_input_mode_t input_mode)
{
	hal_audio_stubs.hal_audio_input_power(paudio_adapter, input_mode);
}

/**
 *  @brief Control the capless mode of the headphone.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_hpo_capless_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_hpo_capless_mode(paudio_adapter, left_en);
}

/**
 *  @brief Control the depop of the headphone in the capless mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is no depop, 1 is depop.
 *
 *  @returns void
 */
void hal_audio_hpo_capless_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_hpo_capless_depop(paudio_adapter, left_en);
}

/**
 *  @brief Control the amplifier of the headphone.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_hpo_amplifier(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_hpo_amplifier(paudio_adapter, left_en);
}

/**
 *  @brief Control the depop mode of the headphone.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_hpo_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_hpo_depop(paudio_adapter, left_en);
}

/**
 *  @brief Control the headphone power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_hpo_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_hpo_power(paudio_adapter, left_en);
}

/**
 *  @brief Control the depop of the headphone mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is no depop, 1 is depop.
 *
 *  @returns void
 */
void hal_audio_hpo_mute_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_hpo_mute_depop(paudio_adapter, left_en);
}

/**
 *  @brief Control the depop of the headphone op.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is no depop, 1 is depop.
 *
 *  @returns void
 */
void hal_audio_hpo_op_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_hpo_op_depop(paudio_adapter, left_en);
}

/**
 *  @brief Control the headphone mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_mute_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_hpo_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en)
{
	hal_audio_stubs.hal_audio_hpo_mute(paudio_adapter, left_mute_en);
}

/**
 *  @brief Control the headphone differential mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_hpo_differential_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_hpo_differential_mode(paudio_adapter, left_en);
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
void hal_audio_mic_bias(hal_audio_adapter_t *paudio_adapter, BOOL bias_en, audio_bias_voltage_t bias_voltage)
{
	hal_audio_stubs.hal_audio_mic_bias(paudio_adapter, bias_en, bias_voltage);
}

/**
 *  @brief Control the mic differential mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_mic_differential_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en)
{
	hal_audio_stubs.hal_audio_mic_differential_mode(paudio_adapter, left_en);
}

/**
 *  @brief Control the mic mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_mute_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_mic_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en)
{
	hal_audio_stubs.hal_audio_mic_mute(paudio_adapter, left_mute_en);
}

/**
 *  @brief Control the line-in mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_mute_en The left channel control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_line_in_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en)
{
	hal_audio_stubs.hal_audio_line_in_mute(paudio_adapter, left_mute_en);
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
void hal_audio_mic_boost(hal_audio_adapter_t *paudio_adapter, BOOL left_en, audio_mic_gain_t left_gain)
{
	hal_audio_stubs.hal_audio_mic_boost(paudio_adapter, left_en, left_gain);
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
void hal_audio_vref(hal_audio_adapter_t *paudio_adapter, BOOL vref_en, audio_vref_voltage_t vref_voltage)
{
	hal_audio_stubs.hal_audio_vref(paudio_adapter, vref_en, vref_voltage);
}

/**
 *  @brief Control audio ip tcon
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_audio_ip_tcon(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_ip_tcon(paudio_adapter, en);
}

/**
 *  @brief Initialize the sport and  DMA of the audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_audio_sport_init(hal_audio_adapter_t *paudio_adapter)
{
	hal_audio_stubs.hal_audio_sport_init(paudio_adapter);
}

/**
 *  @brief De-initialize of the audio SPORT hardware and turn off the audio SPORT.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_audio_sport_deinit(hal_audio_adapter_t *paudio_adapter)
{
	hal_audio_stubs.hal_audio_sport_deinit(paudio_adapter);
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
void hal_audio_sport_tx_params(hal_audio_adapter_t *paudio_adapter, audio_ch_t ch, audio_word_len_t word_len, audio_sample_rate_t audio_sample_rate)
{
	hal_audio_stubs.hal_audio_sport_tx_params(paudio_adapter, ch, word_len, audio_sample_rate);
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
void hal_audio_sport_rx_params(hal_audio_adapter_t *paudio_adapter, audio_ch_t ch, audio_word_len_t word_len, audio_sample_rate_t audio_sample_rate)
{
	hal_audio_stubs.hal_audio_sport_rx_params(paudio_adapter, ch, word_len, audio_sample_rate);
}

/**
 *  @brief Initialize the buffer of the audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dma_params The AUDIO adapter. Set tx0_buf pointer, rx0_buf pointer, page_num and page_size.
 *
 *  @returns void
 */
void hal_audio_sport_buf(hal_audio_adapter_t *paudio_adapter, hal_audio_dma_params_t dma_params)
{
	hal_audio_stubs.hal_audio_sport_buf(paudio_adapter, dma_params);
}

/**
 *  @brief Register the audio SPORT TX IRQ callback function and argument.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_audio_sport_tx_cb_handler(hal_audio_adapter_t *paudio_adapter, audio_sport_irq_cb_t callback, u32 *arg)
{
	hal_audio_stubs.hal_audio_sport_tx_cb_handler(paudio_adapter, callback, arg);
}

/**
 *  @brief Register the audio SPORT RX IRQ callback function and argument.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_audio_sport_rx_cb_handler(hal_audio_adapter_t *paudio_adapter, audio_sport_irq_cb_t callback, u32 *arg)
{
	hal_audio_stubs.hal_audio_sport_rx_cb_handler(paudio_adapter, callback, arg);
}

/**
 *  @brief Get the current tx0 page address.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns The address of current tx0 page or NULL.
 */
int *hal_audio_sport_get_tx_page(hal_audio_adapter_t *paudio_adapter)
{
	return hal_audio_stubs.hal_audio_sport_get_tx_page(paudio_adapter);
}

/**
 *  @brief Sets current tx page own by audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] pbuf  Set tx buffer adderss.
 *
 *  @returns void
 */
void hal_audio_sport_tx_page_send(hal_audio_adapter_t *paudio_adapter, u32 *pbuf)
{
	hal_audio_stubs.hal_audio_sport_tx_page_send(paudio_adapter, pbuf);
}

/**
 *  @brief Sets current rx page own by audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
u32 hal_audio_sport_rx_page_recv(hal_audio_adapter_t *paudio_adapter)
{
	return hal_audio_stubs.hal_audio_sport_rx_page_recv(paudio_adapter);
}

/**
 *  @brief Start the audio tx DMA.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_audio_sport_tx_dma_start(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_sport_tx_dma_start(paudio_adapter, en);
}

/**
 *  @brief Start the audio rx DMA.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_audio_sport_rx_dma_start(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_sport_rx_dma_start(paudio_adapter, en);
}

/**
 *  @brief Get the audio tx DMA status.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
u32 hal_audio_sport_get_tx_dma_start_sta(hal_audio_adapter_t *paudio_adapter)
{
	return hal_audio_stubs.hal_audio_sport_get_tx_dma_start_sta(paudio_adapter);
}

/**
 *  @brief Get the audio rx DMA status.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
u32 hal_audio_sport_get_rx_dma_start_sta(hal_audio_adapter_t *paudio_adapter)
{
	return hal_audio_stubs.hal_audio_sport_get_rx_dma_start_sta(paudio_adapter);
}

/**
 *  @brief Swap the byte of tx data.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_audio_sport_tx_byte_swap(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_sport_tx_byte_swap(paudio_adapter, en);
}

/**
 *  @brief Swap the byte of rx data.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_audio_sport_rx_byte_swap(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_sport_rx_byte_swap(paudio_adapter, en);
}

/**
 *  @brief Start the audio tx SPORT.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_audio_sport_tx_start(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_sport_tx_start(paudio_adapter, en);
}

/**
 *  @brief Start the audio rx SPORT.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_audio_sport_rx_start(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_sport_rx_start(paudio_adapter, en);
}

/**
 *  @brief Init the tx and rx different rate.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_audio_sport_diff_rate_init(hal_audio_adapter_t *paudio_adapter, BOOL en)
{
	hal_audio_stubs.hal_audio_sport_diff_rate_init(paudio_adapter, en);
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
void hal_audio_input_l_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params)
{
	hal_audio_stubs.hal_audio_input_l_eq(paudio_adapter, audio_eq, en, peq_params);
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
void hal_audio_input_r_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params)
{
	hal_audio_stubs.hal_audio_input_r_eq(paudio_adapter, audio_eq, en, peq_params);
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
void hal_audio_output_l_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params)
{
	hal_audio_stubs.hal_audio_output_l_eq(paudio_adapter, audio_eq, en, peq_params);
}


/** @} */ /* End of group hs_hal_audio */


#endif

