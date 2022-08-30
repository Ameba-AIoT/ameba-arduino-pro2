/**************************************************************************//**
 * @file     hal_audio.h
 * @brief    The HAL API implementation for the Audio device.
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

#ifndef _HAL_AUDIO_H_
#define _HAL_AUDIO_H_
#include "cmsis.h"

#include "rtl8735b_audio.h"


#ifdef  __cplusplus
extern "C"
{
#endif

/**
  * @brief The stubs functions table to exports Audio HAL functions.
  */
extern const hal_audio_func_stubs_t hal_audio_stubs;

void hal_audio_init(hal_audio_adapter_t *paudio_adapter, audio_codec_power_t audio_codec_power);
void hal_audio_deinit(hal_audio_adapter_t *paudio_adapter);
void hal_audio_si_init(hal_audio_adapter_t *paudio_adapter, BOOL en);
u16 hal_audio_si_read(hal_audio_adapter_t *paudio_adapter, u8 address);
HAL_Status hal_audio_si_write(hal_audio_adapter_t *paudio_adapter, u8 address, u16 data);
void hal_audio_ldo_tune(u8 sel);
void hal_audio_dev_ctrl(BOOL en);
void hal_audio_rate(hal_audio_adapter_t *paudio_adapter, audio_sample_rate_t audio_tx_rate, audio_sample_rate_t audio_rx_rate);
void hal_audio_format(hal_audio_adapter_t *paudio_adapter, audio_format_t audio_format);
void hal_audio_length(hal_audio_adapter_t *paudio_adapter, audio_word_len_t audio_tx_word_len, audio_word_len_t audio_rx_word_len);
void hal_audio_sck_inv(hal_audio_adapter_t *paudio_adapter, BOOL sck_inv_en);
void hal_audio_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
void hal_audio_tx_ch(hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch);
void hal_audio_rx_ch(hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch);
void hal_audio_digital_rst(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_daad_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
void hal_audio_adda_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
void hal_audio_asrc(hal_audio_adapter_t *paudio_adapter, BOOL asrc_en);
void hal_audio_dac_mixer(hal_audio_adapter_t *paudio_adapter, BOOL dac_l_mute_en);
void hal_audio_adc_amic_mixer(hal_audio_adapter_t *paudio_adapter, BOOL amic_l_mute_en, BOOL amic_r_mute_en);
void hal_audio_adc_dmic_mixer(hal_audio_adapter_t *paudio_adapter, BOOL dmic_l_mute_en, BOOL dmic_r_mute_en);
void hal_audio_sidetone_mixer(hal_audio_adapter_t *paudio_adapter, BOOL sidetone_l_mute_en);
void hal_audio_dac_clk(hal_audio_adapter_t *paudio_adapter, BOOL dac_l_clk_en);
void hal_audio_adc_clk(hal_audio_adapter_t *paudio_adapter, BOOL adc_l_clk_en, BOOL adc_r_clk_en);
void hal_audio_dmic_clk(hal_audio_adapter_t *paudio_adapter, BOOL dimc_l_clk_en, BOOL dimc_r_clk_en);
void hal_audio_dmic_input_clk(hal_audio_adapter_t *paudio_adapter, audio_dmic_input_clk_t dmic_input_clk);
void hal_audio_dmic_latch(hal_audio_adapter_t *paudio_adapter, audio_dmic_latch_t dmic_l_latch, audio_dmic_latch_t dmic_r_latch);
void hal_audio_dmic_l_gain(hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain);
void hal_audio_dmic_r_gain(hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain);
void hal_audio_dmic_l_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
void hal_audio_dmic_r_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
void hal_audio_amic_l_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
void hal_audio_amic_r_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
void hal_audio_adc_l_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_fc_t audio_hpf_fc);
void hal_audio_adc_r_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_fc_t audio_hpf_fc);
void hal_audio_adc_l_dvol(hal_audio_adapter_t *paudio_adapter, u8 step);
void hal_audio_adc_l_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en);
void hal_audio_adc_r_dvol(hal_audio_adapter_t *paudio_adapter, u8 step);
void hal_audio_adc_r_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en);
void hal_audio_adc_l_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout);
void hal_audio_adc_r_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout);
void hal_audio_adc_l_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time);
u8 hal_audio_adc_l_silence_result(hal_audio_adapter_t *paudio_adapter);
u8 hal_audio_adc_l_silence_status(hal_audio_adapter_t *paudio_adapter);
void hal_audio_adc_r_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time);
u8 hal_audio_adc_r_silence_result(hal_audio_adapter_t *paudio_adapter);
u8 hal_audio_adc_r_silence_status(hal_audio_adapter_t *paudio_adapter);
void hal_audio_dac_dither(hal_audio_adapter_t *paudio_adapter, audio_dac_dither_t dac_l_dither);
void hal_audio_dac_l_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_dac_l_dvol(hal_audio_adapter_t *paudio_adapter, u8 step);
void hal_audio_dac_l_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en);
void hal_audio_dac_l_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_dac_zdet_tout_t adc_zdet_tout);
void hal_audio_dac_l_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time);
u8 hal_audio_dac_l_silence_result(hal_audio_adapter_t *paudio_adapter);
u8 hal_audio_dac_l_silence_status(hal_audio_adapter_t *paudio_adapter);
void hal_audio_l_sidetone_hpf(hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf);
void hal_audio_r_sidetone_hpf(hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf);
void hal_audio_l_sidetone_vol(hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost);
void hal_audio_r_sidetone_vol(hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost);
void hal_audio_ad_da_clk_power(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_dac_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_adc_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_output_power(hal_audio_adapter_t *paudio_adapter, audio_output_mode_t output_mode);
void hal_audio_input_power(hal_audio_adapter_t *paudio_adapter, audio_input_mode_t input_mode);
void hal_audio_hpo_capless_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_hpo_capless_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_hpo_amplifier(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_hpo_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_hpo_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_hpo_mute_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_hpo_op_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_hpo_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en);
void hal_audio_hpo_differential_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_mic_bias(hal_audio_adapter_t *paudio_adapter, BOOL bias_en, audio_bias_voltage_t bias_voltage);
void hal_audio_mic_differential_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_audio_mic_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en);
void hal_audio_line_in_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en);
void hal_audio_mic_boost(hal_audio_adapter_t *paudio_adapter, BOOL left_en, audio_mic_gain_t left_gain);
void hal_audio_vref(hal_audio_adapter_t *paudio_adapter, BOOL vref_en, audio_vref_voltage_t vref_voltage);
void hal_audio_ip_tcon(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_sport_init(hal_audio_adapter_t *paudio_adapter);
void hal_audio_sport_deinit(hal_audio_adapter_t *paudio_adapter);
void hal_audio_sport_tx_params(hal_audio_adapter_t *paudio_adapter, audio_ch_t ch, audio_word_len_t word_len, audio_sample_rate_t audio_sample_rate);
void hal_audio_sport_rx_params(hal_audio_adapter_t *paudio_adapter, audio_ch_t ch, audio_word_len_t word_len, audio_sample_rate_t audio_sample_rate);
void hal_audio_sport_buf(hal_audio_adapter_t *paudio_adapter, hal_audio_dma_params_t dma_params);
void hal_audio_sport_tx_cb_handler(hal_audio_adapter_t *paudio_adapter, audio_sport_irq_cb_t callback, u32 *arg);
void hal_audio_sport_rx_cb_handler(hal_audio_adapter_t *paudio_adapter, audio_sport_irq_cb_t callback, u32 *arg);
int *hal_audio_sport_get_tx_page(hal_audio_adapter_t *paudio_adapter);
void hal_audio_sport_tx_page_send(hal_audio_adapter_t *paudio_adapter, u32 *pbuf);
u32 hal_audio_sport_rx_page_recv(hal_audio_adapter_t *paudio_adapter);
void hal_audio_sport_tx_dma_start(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_sport_rx_dma_start(hal_audio_adapter_t *paudio_adapter, BOOL en);
u32 hal_audio_sport_get_tx_dma_start_sta(hal_audio_adapter_t *paudio_adapter);
u32 hal_audio_sport_get_rx_dma_start_sta(hal_audio_adapter_t *paudio_adapter);
void hal_audio_sport_tx_byte_swap(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_sport_rx_byte_swap(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_sport_tx_start(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_sport_rx_start(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_sport_diff_rate_init(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_input_l_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params);
void hal_audio_input_r_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params);
void hal_audio_output_l_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params);


#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_AUDIO_H_"

