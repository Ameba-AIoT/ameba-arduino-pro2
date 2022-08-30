/**************************************************************************//**
 * @file     rtl8735bh_audio.h
 * @brief    The HAL related definition and macros for the AUDIO device.
 *           Includes Registers and data type definition.
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

#ifndef _RTL8735BH_AUDIO_H_
#define _RTL8735BH_AUDIO_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "basic_types.h"
#include "rtl8735b_sport.h"
#include "rtl8735b_si_type.h"
#include "rtl8735b_syson_s_type.h"
#include "rtl8735b.h"
#include "hal_irq.h"
#include "rtl8735b_audio_codec_type.h"

/**
  \brief  Define the audio port ID.
*/
enum  audio_id_e {
	AUDIO_id   =   0x0,
	AUDIO_Max_Id  =   0x1
};
typedef uint8_t audio_id_t;

/**
  \brief Audio Sample Rate.
*/
enum  audio_sample_rate_e {
	AUDIO_SR_8KHZ       =   0x07,
	AUDIO_SR_11p025KHZ  =   0x0d,
	AUDIO_SR_12KHZ      =   0x0b,
	AUDIO_SR_16KHZ      =   0x05,
	AUDIO_SR_24KHZ      =   0x0a,
	AUDIO_SR_22p05KHZ   =   0x0c,
	AUDIO_SR_32KHZ	    = 	0x03,
	AUDIO_SR_44p1KHZ    =   0x08,
	AUDIO_SR_48KHZ	    =	0x00,
	AUDIO_SR_88p2KHZ	=	0x09,
	AUDIO_SR_96KHZ	    =	0x01
};
typedef uint8_t audio_sample_rate_t;

/**
  \brief Audio Format.
*/
enum  audio_format_e {
	AUDIO_FORMAT_I2S          =   0x0,
	AUDIO_FORMAT_LEFT_JUST    =   0x1,
	AUDIO_FORMAT_PCM_MODE_A   =   0x2,
	AUDIO_FORMAT_PCM_MODE_B   =   0x3
};
typedef uint8_t audio_format_t;

/**
  \brief Audio Word Length.
*/
enum  audio_word_len_e {
	AUDIO_WL_16 = 0x0,
	AUDIO_WL_24 = 0x2,
};
typedef uint8_t audio_word_len_t;

/**
  \brief Audio Channel Select.
*/
enum  audio_sel_ch_e {
	AUDIO_L_R = 0x0,
	AUDIO_R_L = 0x1,
	AUDIO_L_L = 0x2,
	AUDIO_R_R = 0x3
};
typedef uint8_t audio_sel_ch_t;

/**
  \brief Audio DMIC Input Clock Select.
*/
enum  audio_dmic_input_clk_e {
	AUDIO_DMIC_5M       = 0x0,
	AUDIO_DMIC_2p5M     = 0x1,  /*!< default */
	AUDIO_DMIC_1p25M    = 0x2,
	AUDIO_DMIC_625K     = 0x3,
	AUDIO_DMIC_312p5K   = 0x4
};
typedef uint8_t audio_dmic_input_clk_t;

/**
  \brief Audio Zero Detection Function Select.
*/
enum  audio_zdet_e {
	AUDIO_IMME_CHAN             = 0x0,
	AUDIO_DETE_AND_IMME_CHAN    = 0x1,
	AUDIO_DETE_AND_INC_DEC_CHAN = 0x2,  /*!< default */
	AUDIO_UN_CHAN               = 0x3
};
typedef uint8_t audio_zdet_t;

/**
  \brief Audio Zero Detection Time Out Select for ADC.
*/
enum  audio_adc_zdet_tout_e {
	AUDIO_ADC_16384_SAMPLES = 0x0,
	AUDIO_ADC_32768_SAMPLES = 0x1,  /*!< default */
	AUDIO_ADC_65536_SAMPLES = 0x2,
	AUDIO_ADC_64_SAMPLES    = 0x3
};
typedef uint8_t audio_adc_zdet_tout_t;

/**
  \brief Audio DMIC Latch Select.
*/
enum  audio_dmic_latch_e {
	AUDIO_DIMC_RISING = 0x0,
	AUDIO_DIMC_FALLING = 0x1
};
typedef uint8_t audio_dmic_latch_t;

/**
  \brief Audio DMIC Boost Select.
*/
enum  audio_dmic_gain_e {
	AUDIO_DMIC_BOOST_0DB = 0x0,
	AUDIO_DMIC_BOOST_12DB = 0x1,
	AUDIO_DMIC_BOOST_24DB = 0x2,
	AUDIO_DMIC_BOOST_36DB = 0x3
};
typedef uint8_t audio_dmic_gain_t;

/**
  \brief Audio Low Pass Filter frequency Select for SRC.
*/
enum  audio_src_freq_e {
	AUDIO_SRC_31p04KHZ = 0x0,
	AUDIO_SRC_46p92KHZ = 0x1,
	AUDIO_SRC_63p06KHZ = 0x2,
	AUDIO_SRC_79p54KHZ = 0x3
};
typedef uint8_t audio_src_freq_t;

/**
  \brief Audio Silence Debounce.
*/
enum  audio_silence_debounce_e {
	AUDIO_SILE_3840_SAMPLES = 0x0,
	AUDIO_SILE_7680_SAMPLES = 0x1,
	AUDIO_SILE_15360_SAMPLES = 0x2,
	AUDIO_SILE_30720_SAMPLES = 0x3, /*!< default */
	AUDIO_SILE_61440_SAMPLES = 0x4,
	AUDIO_SILE_122880_SAMPLES = 0x5,
	AUDIO_SILE_245760_SAMPLES = 0x6
};
typedef uint8_t audio_silence_debounce_t;

/**
  \brief Audio Silence Level.
*/
enum  audio_silence_Level_e {
	AUDIO_SILE_n78DB = 0x0,
	AUDIO_SILE_n84DB = 0x1,
	AUDIO_SILE_n90DB = 0x2,
	AUDIO_SILE_n102DB = 0x3,
	AUDIO_SILE_n108DB = 0x4,
	AUDIO_SILE_n114DB = 0x5,
	AUDIO_SILE_n126DB = 0x6,
	AUDIO_SILE_n132DB = 0x7
};
typedef uint8_t audio_silence_Level_t;

/**
  \brief Audio Dither Select.
*/
enum  audio_dac_dither_e {
	AUDIO_DITHER_DISABLE = 0x0,
	AUDIO_DITHER_LSB = 0x1,
	AUDIO_DITHER_LSB_ADD1 = 0x2,    /*!< default */
	AUDIO_DITHER_LSB_ADD2 = 0x3
};
typedef uint8_t audio_dac_dither_t;

/**
  \brief Audio Zero Detection Time Out Select for DAC.
*/
enum  audio_dac_zdet_tout_e {
	AUDIO_DAC_16384_SAMPLES = 0x0,  /*!< default */
	AUDIO_DAC_32768_SAMPLES = 0x1,
	AUDIO_DAC_65536_SAMPLES = 0x2,
	AUDIO_DAC_256_SAMPLES   = 0x3
};
typedef uint8_t audio_dac_zdet_tout_t;

/**
  \brief Audio Sidetone HPF Cut Off Frequence.
*/
enum  audio_sidetone_hpf_e {
	AUDIO_ST_120HZ = 0x0,
	AUDIO_ST_239HZ = 0x1,
	AUDIO_ST_358HZ = 0x2,
	AUDIO_ST_477HZ = 0x3,
	AUDIO_ST_597HZ = 0x4,
	AUDIO_ST_716HZ = 0x5,
	AUDIO_ST_835HZ = 0x6,
	AUDIO_ST_955HZ = 0x7
};
typedef uint8_t audio_sidetone_hpf_t;

/**
  \brief Audio Sidetone Volume Select .
*/
enum  audio_sidetone_vol_e {
	AUDIO_ST_n46p5DB = 0x0,
	AUDIO_ST_n45DB = 0x1,
	AUDIO_ST_n43p5DB = 0x2,
	AUDIO_ST_n42DB = 0x3,
	AUDIO_ST_n40p5DB = 0x4,
	AUDIO_ST_n39DB = 0x5,
	AUDIO_ST_n37p5DB = 0x6,
	AUDIO_ST_n36DB = 0x7,

	AUDIO_ST_n34p5DB = 0x8,
	AUDIO_ST_n33DB = 0x9,
	AUDIO_ST_n31p5DB = 0xA,
	AUDIO_ST_n30DB = 0xB,
	AUDIO_ST_n28p5DB = 0xC,
	AUDIO_ST_n27DB = 0xD,
	AUDIO_ST_n25p5DB = 0xE,
	AUDIO_ST_n24DB = 0xF,

	AUDIO_ST_n22p5DB = 0x10,
	AUDIO_ST_n21DB = 0x11,
	AUDIO_ST_n19p5DB = 0x12,
	AUDIO_ST_n18DB = 0x13,
	AUDIO_ST_n16p5DB = 0x14,
	AUDIO_ST_n15DB = 0x15,
	AUDIO_ST_n13p5DB = 0x16,
	AUDIO_ST_n12DB = 0x17,

	AUDIO_ST_n10p5DB = 0x18,
	AUDIO_ST_n9DB = 0x19,
	AUDIO_ST_n7p5DB = 0x1A,
	AUDIO_ST_n60DB = 0x1B,
	AUDIO_ST_n4p5DB = 0x1C,
	AUDIO_ST_n3DB = 0x1D,
	AUDIO_ST_n1p5DB = 0x1E,
	AUDIO_ST_00DB = 0x1F
};
typedef uint8_t audio_sidetone_vol_t;

/**
  \brief Audio Sidetone Boost Select .
*/
enum  audio_sidetone_boost_e {
	AUDIO_ST_BOOST_0DB = 0x0,
	AUDIO_ST_BOOST_12DB = 0x1
};
typedef uint8_t audio_sidetone_boost_t;

/**
  \brief Audio Output Mode.
*/
enum  audio_output_mode_e {
	AUDIO_OUTPUT_DISABLE = 0,
	AUDIO_OUTPUT_SINGLE_EDNED = 1,
	AUDIO_OUTPUT_DIFFERENTIAL = 2,
	AUDIO_OUTPUT_CAPLESS = 3
};
typedef uint8_t audio_output_mode_t;

/**
  \brief Audio Input Mode.
*/
enum  audio_input_mode_e {
	AUDIO_INPUT_DISABLE = 0,
	AUDIO_LINE_IN_MODE = 1,
	AUDIO_MIC_DIFFERENTIAL = 2,
	AUDIO_MIC_SINGLE_EDNED = 3,
	AUDIO_LEFT_DMIC = 4,
	AUDIO_RIGHT_DMIC = 5,
	AUDIO_STEREO_DMIC = 6
};
typedef uint8_t audio_input_mode_t;

/**
  \brief Audio Bias Voltage Select.
*/
enum  audio_bias_voltage_e {
	AUDIO_BIAS_0p9_AVDD     = 0x0,  /*!< default */
	AUDIO_BIAS_0p86_AVDD    = 0x1,
	AUDIO_BIAS_0p75_AVDD    = 0x2
};
typedef uint8_t audio_bias_voltage_t;

/**
  \brief Audio Mic Gain Select.
*/
enum  audio_mic_gain_e {
	AUDIO_MIC_0DB     = 0x0,    /*!< default */
	AUDIO_MIC_20DB    = 0x1,
	AUDIO_MIC_30DB    = 0x2,
	AUDIO_MIC_40DB    = 0x3
};
typedef uint8_t audio_mic_gain_t;

/**
  \brief Audio Vref Voltage Select.
*/
enum  audio_vref_voltage_e {
	AUDIO_VREF_0p52_VDD = 0x0,
	AUDIO_VREF_0p51_VDD = 0x1,
	AUDIO_VREF_0p50_VDD = 0x2,  /*!< default */
	AUDIO_VREF_0p49_VDD = 0x3
};
typedef uint8_t audio_vref_voltage_t;

/**
  \brief Audio Channel Number
*/
enum audio_ch_e {
	AUDIO_MONO   = 0x00,
	AUDIO_STEREO = 0x01
};
typedef uint8_t audio_ch_t;

/**
  \brief Audio Codec Power.
*/
enum  audio_codec_power_e {
	AUDIO_POWER_1p8V = 0,
	AUDIO_POWER_2p8V = 1
};
typedef uint8_t audio_codec_power_t;

/**
  \brief Audio HPF Coefficient.
*/
enum  audio_hpf_fc_e {
	AUDIO_HPF_FS_0  = 0x0,  /*!< fc = 5e-3*fs */
	AUDIO_HPF_FS_1  = 0x1,  /*!< fc = 2.5e-3*fs */
	AUDIO_HPF_FS_2  = 0x2,  /*!< fc = 1.25e-3*fs */
	AUDIO_HPF_FS_3  = 0x3,  /*!< fc = 6.25e-4*fs */
	AUDIO_HPF_FS_4  = 0x4,  /*!< fc = 3.125e-4*fs */
	AUDIO_HPF_FS_5  = 0x5,  /*!< fc = 1.5625e-4*fs */
	AUDIO_HPF_FS_6  = 0x6,  /*!< fc = 7.8125-5*fs */
	AUDIO_HPF_FS_7  = 0x7   /*!< fc = 3.90625-5*fs */
};
typedef uint8_t audio_hpf_fc_t;

/**
  \brief EQ band number.
*/
enum  audio_eq_e {
	AUDIO_EQ_0  = 0x0,
	AUDIO_EQ_1  = 0x1,
	AUDIO_EQ_2  = 0x2,
	AUDIO_EQ_3  = 0x3,
	AUDIO_EQ_4  = 0x4
};
typedef uint8_t audio_eq_t;


/**
  \brief  The data structure for an audio port HAL operations.
*/
typedef struct hal_audio_adapter_s {
	SI_Type *si_base_addr;                      /*!< The SI common register base address */
	hal_sport_adapter_t sport_adapter;

} hal_audio_adapter_t, *phal_audio_adapter_t;

/**
  \brief  The sport buffer parameter structure
*/
typedef struct hal_audio_dma_params_s {
	u8      *tx_buf;       /* TX FIFO_0 buffer*/
	u8      *rx_buf;       /* RX FIFO_0 buffer*/
	u32     page_num;       /* Buffer page number*/
	u32     page_size;      /* Buffer page size*/
} hal_audio_dma_params_t, *phal_audio_dma_params_t;

/**
  \brief  The EQ parameter structure
*/
typedef struct hal_eq_params_s {
	u32 h0;
	u32 b1;
	u32 b2;
	u32 a1;
	u32 a2;
} hal_eq_params_t, *phal_eq_params_t;


/**
  \brief  SPORT call back function for the interrupt event.
*/
typedef void (*audio_sport_irq_cb_t)(u32 *arg, u8 *pbuf);

void hal_rtl_audio_init(hal_audio_adapter_t *paudio_adapter, audio_codec_power_t audio_codec_power);
void hal_rtl_audio_deinit(hal_audio_adapter_t *paudio_adapter);
void hal_rtl_audio_si_init(hal_audio_adapter_t *paudio_adapter, BOOL en);
u16 hal_rtl_audio_si_read(hal_audio_adapter_t *paudio_adapter, u8 address);
HAL_Status hal_rtl_audio_si_write(hal_audio_adapter_t *paudio_adapter, u8 address, u16 data);
void hal_rtl_audio_ldo_tune(u8 sel);
void hal_rtl_audio_dev_ctrl(BOOL en);
void hal_rtl_audio_rate(hal_audio_adapter_t *paudio_adapter, audio_sample_rate_t audio_tx_rate, audio_sample_rate_t audio_rx_rate);
void hal_rtl_audio_format(hal_audio_adapter_t *paudio_adapter, audio_format_t audio_format);
void hal_rtl_audio_length(hal_audio_adapter_t *paudio_adapter, audio_word_len_t audio_tx_word_len, audio_word_len_t audio_rx_word_len);
void hal_rtl_audio_sck_inv(hal_audio_adapter_t *paudio_adapter, BOOL sck_inv_en);
void hal_rtl_audio_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
void hal_rtl_audio_tx_ch(hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch);
void hal_rtl_audio_rx_ch(hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch);
void hal_rtl_audio_digital_rst(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_rtl_audio_daad_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
void hal_rtl_audio_adda_loopback(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
void hal_rtl_audio_asrc(hal_audio_adapter_t *paudio_adapter, BOOL asrc_en);
void hal_rtl_audio_dac_mixer(hal_audio_adapter_t *paudio_adapter, BOOL dac_l_mute_en);
void hal_rtl_audio_adc_amic_mixer(hal_audio_adapter_t *paudio_adapter, BOOL amic_l_mute_en, BOOL amic_r_mute_en);
void hal_rtl_audio_adc_dmic_mixer(hal_audio_adapter_t *paudio_adapter, BOOL dmic_l_mute_en, BOOL dmic_r_mute_en);
void hal_rtl_audio_sidetone_mixer(hal_audio_adapter_t *paudio_adapter, BOOL sidetone_l_mute_en);
void hal_rtl_audio_dac_clk(hal_audio_adapter_t *paudio_adapter, BOOL dac_l_clk_en);
void hal_rtl_audio_adc_clk(hal_audio_adapter_t *paudio_adapter, BOOL adc_l_clk_en, BOOL adc_r_clk_en);
void hal_rtl_audio_dmic_clk(hal_audio_adapter_t *paudio_adapter, BOOL dimc_l_clk_en, BOOL dimc_r_clk_en);
void hal_rtl_audio_dmic_input_clk(hal_audio_adapter_t *paudio_adapter, audio_dmic_input_clk_t dmic_input_clk);
void hal_rtl_audio_dmic_latch(hal_audio_adapter_t *paudio_adapter, audio_dmic_latch_t dmic_l_latch, audio_dmic_latch_t dmic_r_latch);
void hal_rtl_audio_dmic_l_gain(hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain);
void hal_rtl_audio_dmic_r_gain(hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain);
void hal_rtl_audio_dmic_l_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
void hal_rtl_audio_dmic_r_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
void hal_rtl_audio_amic_l_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
void hal_rtl_audio_amic_r_src(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
void hal_rtl_audio_adc_l_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_fc_t audio_hpf_fc);
void hal_rtl_audio_adc_r_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_fc_t audio_hpf_fc);
void hal_rtl_audio_adc_l_dvol(hal_audio_adapter_t *paudio_adapter, u8 step);
void hal_rtl_audio_adc_l_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en);
void hal_rtl_audio_adc_r_dvol(hal_audio_adapter_t *paudio_adapter, u8 step);
void hal_rtl_audio_adc_r_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en);
void hal_rtl_audio_adc_l_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout);
void hal_rtl_audio_adc_r_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout);
void hal_rtl_audio_adc_l_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time);
u8 hal_rtl_audio_adc_l_silence_result(hal_audio_adapter_t *paudio_adapter);
u8 hal_rtl_audio_adc_l_silence_status(hal_audio_adapter_t *paudio_adapter);
void hal_rtl_audio_adc_r_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time);
u8 hal_rtl_audio_adc_r_silence_result(hal_audio_adapter_t *paudio_adapter);
u8 hal_rtl_audio_adc_r_silence_status(hal_audio_adapter_t *paudio_adapter);
void hal_rtl_audio_dac_dither(hal_audio_adapter_t *paudio_adapter, audio_dac_dither_t dac_l_dither);
void hal_rtl_audio_dac_l_hpf(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_rtl_audio_dac_l_dvol(hal_audio_adapter_t *paudio_adapter, u8 step);
void hal_rtl_audio_dac_l_dmute(hal_audio_adapter_t *paudio_adapter, BOOL mute_en);
void hal_rtl_audio_dac_l_zdet(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_dac_zdet_tout_t adc_zdet_tout);
void hal_rtl_audio_dac_l_silence(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time);
u8 hal_rtl_audio_dac_l_silence_result(hal_audio_adapter_t *paudio_adapter);
u8 hal_rtl_audio_dac_l_silence_status(hal_audio_adapter_t *paudio_adapter);
void hal_rtl_audio_l_sidetone_hpf(hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf);
void hal_rtl_audio_r_sidetone_hpf(hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf);
void hal_rtl_audio_l_sidetone_vol(hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost);
void hal_rtl_audio_r_sidetone_vol(hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost);
void hal_rtl_audio_ad_da_clk_power(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_rtl_audio_dac_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_adc_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_output_power(hal_audio_adapter_t *paudio_adapter, audio_output_mode_t output_mode);
void hal_rtl_audio_input_power(hal_audio_adapter_t *paudio_adapter, audio_input_mode_t input_mode);
void hal_rtl_audio_hpo_capless_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_hpo_capless_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_hpo_amplifier(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_hpo_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_hpo_power(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_hpo_mute_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_hpo_op_depop(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_hpo_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en);
void hal_rtl_audio_hpo_differential_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_mic_bias(hal_audio_adapter_t *paudio_adapter, BOOL bias_en, audio_bias_voltage_t bias_voltage);
void hal_rtl_audio_mic_differential_mode(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
void hal_rtl_audio_mic_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en);
void hal_rtl_audio_line_in_mute(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en);
void hal_rtl_audio_mic_boost(hal_audio_adapter_t *paudio_adapter, BOOL left_en, audio_mic_gain_t left_gain);
void hal_rtl_audio_vref(hal_audio_adapter_t *paudio_adapter, BOOL vref_en, audio_vref_voltage_t vref_voltage);
void hal_rtl_audio_ip_tcon(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_rtl_audio_sport_init(hal_audio_adapter_t *paudio_adapter);
void hal_rtl_audio_sport_deinit(hal_audio_adapter_t *paudio_adapter);
void hal_rtl_audio_sport_tx_params(hal_audio_adapter_t *paudio_adapter, audio_ch_t ch, audio_word_len_t word_len, audio_sample_rate_t audio_sample_rate);
void hal_rtl_audio_sport_rx_params(hal_audio_adapter_t *paudio_adapter, audio_ch_t ch, audio_word_len_t word_len, audio_sample_rate_t audio_sample_rate);
void hal_rtl_audio_sport_buf(hal_audio_adapter_t *paudio_adapter, hal_audio_dma_params_t dma_params);
void hal_rtl_audio_sport_tx_cb_handler(hal_audio_adapter_t *paudio_adapter, audio_sport_irq_cb_t callback, u32 *arg);
void hal_rtl_audio_sport_rx_cb_handler(hal_audio_adapter_t *paudio_adapter, audio_sport_irq_cb_t callback, u32 *arg);
int *hal_rtl_audio_sport_get_tx_page(hal_audio_adapter_t *paudio_adapter);
void hal_rtl_audio_sport_tx_page_send(hal_audio_adapter_t *paudio_adapter, u32 *pbuf);
u32 hal_rtl_audio_sport_rx_page_recv(hal_audio_adapter_t *paudio_adapter);
void hal_rtl_audio_sport_tx_dma_start(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_rtl_audio_sport_rx_dma_start(hal_audio_adapter_t *paudio_adapter, BOOL en);
u32 hal_rtl_audio_sport_get_tx_dma_start_sta(hal_audio_adapter_t *paudio_adapter);
u32 hal_rtl_audio_sport_get_rx_dma_start_sta(hal_audio_adapter_t *paudio_adapter);
void hal_rtl_audio_sport_tx_byte_swap(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_rtl_audio_sport_rx_byte_swap(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_rtl_audio_sport_tx_start(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_rtl_audio_sport_rx_start(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_rtl_audio_sport_diff_rate_init(hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_rtl_audio_input_l_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params);
void hal_rtl_audio_input_r_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params);
void hal_rtl_audio_output_l_eq(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params);


/**
  \brief  The data structure of the stubs function for the audio HAL functions in ROM
*/
typedef struct hal_audio_func_stubs_s {
	void (*hal_audio_init)(hal_audio_adapter_t *paudio_adapter, audio_codec_power_t audio_codec_power);
	void (*hal_audio_deinit)(hal_audio_adapter_t *paudio_adapter);
	void (*hal_audio_si_init)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	u16(*hal_audio_si_read)(hal_audio_adapter_t *paudio_adapter, u8 address);
	HAL_Status(*hal_audio_si_write)(hal_audio_adapter_t *paudio_adapter, u8 address, u16 data);
	void (*hal_audio_ldo_tune)(u8 sel);
	void (*hal_audio_dev_ctrl)(BOOL en);
	void (*hal_audio_rate)(hal_audio_adapter_t *paudio_adapter, audio_sample_rate_t audio_tx_rate, audio_sample_rate_t audio_rx_rate);
	void (*hal_audio_format)(hal_audio_adapter_t *paudio_adapter, audio_format_t audio_format);
	void (*hal_audio_length)(hal_audio_adapter_t *paudio_adapter, audio_word_len_t audio_tx_word_len, audio_word_len_t audio_rx_word_len);
	void (*hal_audio_sck_inv)(hal_audio_adapter_t *paudio_adapter, BOOL sck_inv_en);
	void (*hal_audio_loopback)(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
	void (*hal_audio_tx_ch)(hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch);
	void (*hal_audio_rx_ch)(hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch);
	void (*hal_audio_digital_rst)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	void (*hal_audio_daad_loopback)(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
	void (*hal_audio_adda_loopback)(hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
	void (*hal_audio_asrc)(hal_audio_adapter_t *paudio_adapter, BOOL asrc_en);
	void (*hal_audio_dac_mixer)(hal_audio_adapter_t *paudio_adapter, BOOL dac_l_mute_en);
	void (*hal_audio_adc_amic_mixer)(hal_audio_adapter_t *paudio_adapter, BOOL amic_l_mute_en, BOOL amic_r_mute_en);
	void (*hal_audio_adc_dmic_mixer)(hal_audio_adapter_t *paudio_adapter, BOOL dmic_l_mute_en, BOOL dmic_r_mute_en);
	void (*hal_audio_sidetone_mixer)(hal_audio_adapter_t *paudio_adapter, BOOL sidetone_l_mute_en);
	void (*hal_audio_dac_clk)(hal_audio_adapter_t *paudio_adapter, BOOL dac_l_clk_en);
	void (*hal_audio_adc_clk)(hal_audio_adapter_t *paudio_adapter, BOOL adc_l_clk_en, BOOL adc_r_clk_en);
	void (*hal_audio_dmic_clk)(hal_audio_adapter_t *paudio_adapter, BOOL dimc_l_clk_en, BOOL dimc_r_clk_en);
	void (*hal_audio_dmic_input_clk)(hal_audio_adapter_t *paudio_adapter, audio_dmic_input_clk_t dmic_input_clk);
	void (*hal_audio_dmic_latch)(hal_audio_adapter_t *paudio_adapter, audio_dmic_latch_t dmic_l_latch, audio_dmic_latch_t dmic_r_latch);
	void (*hal_audio_dmic_l_gain)(hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain);
	void (*hal_audio_dmic_r_gain)(hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain);
	void (*hal_audio_dmic_l_src)(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
	void (*hal_audio_dmic_r_src)(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
	void (*hal_audio_amic_l_src)(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
	void (*hal_audio_amic_r_src)(hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
	void (*hal_audio_adc_l_hpf)(hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_fc_t audio_hpf_fc);
	void (*hal_audio_adc_r_hpf)(hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_fc_t audio_hpf_fc);
	void (*hal_audio_adc_l_dvol)(hal_audio_adapter_t *paudio_adapter, u8 step);
	void (*hal_audio_adc_l_dmute)(hal_audio_adapter_t *paudio_adapter, BOOL mute_en);
	void (*hal_audio_adc_r_dvol)(hal_audio_adapter_t *paudio_adapter, u8 step);
	void (*hal_audio_adc_r_dmute)(hal_audio_adapter_t *paudio_adapter, BOOL mute_en);
	void (*hal_audio_adc_l_zdet)(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout);
	void (*hal_audio_adc_r_zdet)(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout);
	void (*hal_audio_adc_l_silence)(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time);
	u8(*hal_audio_adc_l_silence_result)(hal_audio_adapter_t *paudio_adapter);
	u8(*hal_audio_adc_l_silence_status)(hal_audio_adapter_t *paudio_adapter);
	void (*hal_audio_adc_r_silence)(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time);
	u8(*hal_audio_adc_r_silence_result)(hal_audio_adapter_t *paudio_adapter);
	u8(*hal_audio_adc_r_silence_status)(hal_audio_adapter_t *paudio_adapter);
	void (*hal_audio_dac_dither)(hal_audio_adapter_t *paudio_adapter, audio_dac_dither_t dac_l_dither);
	void (*hal_audio_dac_l_hpf)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	void (*hal_audio_dac_l_dvol)(hal_audio_adapter_t *paudio_adapter, u8 step);
	void (*hal_audio_dac_l_dmute)(hal_audio_adapter_t *paudio_adapter, BOOL mute_en);
	void (*hal_audio_dac_l_zdet)(hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_dac_zdet_tout_t adc_zdet_tout);
	void (*hal_audio_dac_l_silence)(hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_Level_t level, audio_silence_debounce_t debounce_time);
	u8(*hal_audio_dac_l_silence_result)(hal_audio_adapter_t *paudio_adapter);
	u8(*hal_audio_dac_l_silence_status)(hal_audio_adapter_t *paudio_adapter);
	void (*hal_audio_l_sidetone_hpf)(hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf);
	void (*hal_audio_r_sidetone_hpf)(hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf);
	void (*hal_audio_l_sidetone_vol)(hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost);
	void (*hal_audio_r_sidetone_vol)(hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost);
	void (*hal_audio_ad_da_clk_power)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	void (*hal_audio_dac_power)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_adc_power)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_output_power)(hal_audio_adapter_t *paudio_adapter, audio_output_mode_t output_mode);
	void (*hal_audio_input_power)(hal_audio_adapter_t *paudio_adapter, audio_input_mode_t input_mode);
	void (*hal_audio_hpo_capless_mode)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_hpo_capless_depop)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_hpo_amplifier)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_hpo_depop)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_hpo_power)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_hpo_mute_depop)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_hpo_op_depop)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_hpo_mute)(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en);
	void (*hal_audio_hpo_differential_mode)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_mic_bias)(hal_audio_adapter_t *paudio_adapter, BOOL bias_en, audio_bias_voltage_t bias_voltage);
	void (*hal_audio_mic_differential_mode)(hal_audio_adapter_t *paudio_adapter, BOOL left_en);
	void (*hal_audio_mic_mute)(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en);
	void (*hal_audio_line_in_mute)(hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en);
	void (*hal_audio_mic_boost)(hal_audio_adapter_t *paudio_adapter, BOOL left_en, audio_mic_gain_t left_gain);
	void (*hal_audio_vref)(hal_audio_adapter_t *paudio_adapter, BOOL vref_en, audio_vref_voltage_t vref_voltage);
	void (*hal_audio_ip_tcon)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	void (*hal_audio_sport_init)(hal_audio_adapter_t *paudio_adapter);
	void (*hal_audio_sport_deinit)(hal_audio_adapter_t *paudio_adapter);
	void (*hal_audio_sport_tx_params)(hal_audio_adapter_t *paudio_adapter, audio_ch_t ch, audio_word_len_t word_len, audio_sample_rate_t audio_sample_rate);
	void (*hal_audio_sport_rx_params)(hal_audio_adapter_t *paudio_adapter, audio_ch_t ch, audio_word_len_t word_len, audio_sample_rate_t audio_sample_rate);
	void (*hal_audio_sport_buf)(hal_audio_adapter_t *paudio_adapter, hal_audio_dma_params_t dma_params);
	void (*hal_audio_sport_tx_cb_handler)(hal_audio_adapter_t *paudio_adapter, audio_sport_irq_cb_t callback, u32 *arg);
	void (*hal_audio_sport_rx_cb_handler)(hal_audio_adapter_t *paudio_adapter, audio_sport_irq_cb_t callback, u32 *arg);
	int *(*hal_audio_sport_get_tx_page)(hal_audio_adapter_t *paudio_adapter);
	void (*hal_audio_sport_tx_page_send)(hal_audio_adapter_t *paudio_adapter, u32 *pbuf);
	u32(*hal_audio_sport_rx_page_recv)(hal_audio_adapter_t *paudio_adapter);
	void (*hal_audio_sport_tx_dma_start)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	void (*hal_audio_sport_rx_dma_start)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	u32(*hal_audio_sport_get_tx_dma_start_sta)(hal_audio_adapter_t *paudio_adapter);
	u32(*hal_audio_sport_get_rx_dma_start_sta)(hal_audio_adapter_t *paudio_adapter);
	void (*hal_audio_sport_tx_byte_swap)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	void (*hal_audio_sport_rx_byte_swap)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	void (*hal_audio_sport_tx_start)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	void (*hal_audio_sport_rx_start)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	void (*hal_audio_sport_diff_rate_init)(hal_audio_adapter_t *paudio_adapter, BOOL en);
	void (*hal_audio_input_l_eq)(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params);
	void (*hal_audio_input_r_eq)(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params);
	void (*hal_audio_output_l_eq)(hal_audio_adapter_t *paudio_adapter, audio_eq_t audio_eq, BOOL en, hal_eq_params_t *peq_params);
	uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} hal_audio_func_stubs_t;


#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL8735BH_AUDIO_H_

