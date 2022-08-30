#ifndef _RTL8735B_AUDIO_CODEC_TYPE_H_
#define _RTL8735B_AUDIO_CODEC_TYPE_H_

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_00H
 * @brief  index_00h                                 (@ 0X000)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_HPO_CLPDPL                 15
#define AUDIO_CODEC_BIT_HPO_CLPDPL                   ((u32)0x00000001 << 15)                             /*!<R/W 0  Headphone left channel capless positive depop mode control (0: no depop, 1: depop) */
#define AUDIO_CODEC_SHIFT_HPO_CLNDPL                 13
#define AUDIO_CODEC_BIT_HPO_CLNDPL                   ((u32)0x00000001 << 13)                             /*!<R/W 0  Headphone left channel capless negative depop mode control (0: no depop, 1: depop) */
#define AUDIO_CODEC_SHIFT_HPO_CLL                    12
#define AUDIO_CODEC_BIT_HPO_CLL                      ((u32)0x00000001 << 12)                             /*!<R/W 0  Headphone left channel capless mode control (0: non-capless, 1: capless) */
#define AUDIO_CODEC_SHIFT_DTSDM_POW_L                10
#define AUDIO_CODEC_BIT_DTSDM_POW_L                  ((u32)0x00000001 << 10)                             /*!<R/W 0  Left channel ADC power on control: 0: power down 1: power on */
#define AUDIO_CODEC_SHIFT_DTSDM_CKXEN                9
#define AUDIO_CODEC_BIT_DTSDM_CKXEN                  ((u32)0x00000001 << 9)                              /*!<R/W 1  ADC integrater 1 OP chopper enable: 0 : disable 1 : enable (default) */
#define AUDIO_CODEC_SHIFT_DPRAMP_POW                 8
#define AUDIO_CODEC_BIT_DPRAMP_POW                   ((u32)0x00000001 << 8)                              /*!<R/W 0  DPRAMP power down control (0: power down, 1: power on) */
#define AUDIO_CODEC_SHIFT_DPRAMP_ENRAMP              7
#define AUDIO_CODEC_BIT_DPRAMP_ENRAMP                ((u32)0x00000001 << 7)                              /*!<R/W 0  DPRAMP enable ramp control (0: disable, 1: enable) */
#define AUDIO_CODEC_SHIFT_DPRAMP_CSEL                5
#define AUDIO_CODEC_MASK_DPRAMP_CSEL                 ((u32)0x00000003 << 5)                              /*!<R/W 11  Depop C size selection (00: 1x, 01: 2x, 10: 3x, 11: 4x) */
#define AUDIO_CODEC_SHIFT_DAC_L_POW                  3
#define AUDIO_CODEC_BIT_DAC_L_POW                    ((u32)0x00000001 << 3)                              /*!<R/W 0  DAC left channel power down control (0: power down, 1: power on) */
#define AUDIO_CODEC_SHIFT_DAC_CKXSEL                 2
#define AUDIO_CODEC_BIT_DAC_CKXSEL                   ((u32)0x00000001 << 2)                              /*!<R/W 0  DAC chopper clock selection (0: ckx2/4, 1: ckx2/8) */
#define AUDIO_CODEC_SHIFT_DAC_CKXEN                  1
#define AUDIO_CODEC_BIT_DAC_CKXEN                    ((u32)0x00000001 << 1)                              /*!<R/W 1  DAC chopper clock enable control (0: disable, 1: enable) */
#define AUDIO_CODEC_SHIFT_DAC_ADDACK_POW             0
#define AUDIO_CODEC_BIT_DAC_ADDACK_POW               ((u32)0x00000001 << 0)                              /*!<R/W 0  AD/DA clock power down control (0: power down, 1: power on) */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_01H
 * @brief  index_01h                                 (@ 0X002)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_HPO_OPPDPL                 15
#define AUDIO_CODEC_BIT_HPO_OPPDPL                   ((u32)0x00000001 << 15)                             /*!<R/W 0  Headphone left channel op positive depop mode control (0: no depop, 1: depop) */
#define AUDIO_CODEC_SHIFT_HPO_OPNDPL                 13
#define AUDIO_CODEC_BIT_HPO_OPNDPL                   ((u32)0x00000001 << 13)                             /*!<R/W 0  Headphone left channel op negative depop mode control (0: no depop, 1: depop) */
#define AUDIO_CODEC_SHIFT_HPO_MDPL                   11
#define AUDIO_CODEC_BIT_HPO_MDPL                     ((u32)0x00000001 << 11)                             /*!<R/W 0  Headphone left channel mute depop mode control (0: no depop, 1: depop) */
#define AUDIO_CODEC_SHIFT_HPO_L_POW                  10
#define AUDIO_CODEC_BIT_HPO_L_POW                    ((u32)0x00000001 << 10)                             /*!<R/W 0  Headphone left channel power down control (0: power down, 1: power on) */
#define AUDIO_CODEC_SHIFT_HPO_ENDPL                  8
#define AUDIO_CODEC_BIT_HPO_ENDPL                    ((u32)0x00000001 << 8)                              /*!<R/W 1  Headphone left channel enable depop control (0: disable, 1: enable) */
#define AUDIO_CODEC_SHIFT_HPO_ENAL                   6
#define AUDIO_CODEC_BIT_HPO_ENAL                     ((u32)0x00000001 << 6)                              /*!<R/W 1  Headphone left channel enable amplifier control (0: disable, 1: enable) */
#define AUDIO_CODEC_SHIFT_HPO_DPRSELL                2
#define AUDIO_CODEC_MASK_HPO_DPRSELL                 ((u32)0x00000003 << 2)                              /*!<R/W 11  Headphone left channel depop R size selection (00: 1x, 01: 2x, 10: 3x, 11: 4x) */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_02H
 * @brief  index_02h                                 (@ 0X004)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_VREF_POW                   15
#define AUDIO_CODEC_BIT_VREF_POW                     ((u32)0x00000001 << 15)                             /*!<R/W 0  VREF power control 0: power down 1: power on */
#define AUDIO_CODEC_SHIFT_MICBST_ENDFL               13
#define AUDIO_CODEC_BIT_MICBST_ENDFL                 ((u32)0x00000001 << 13)                             /*!<R/W 0  MICBST left channel enable differential 0:single to differential 1:differential to differential */
#define AUDIO_CODEC_SHIFT_MICBIAS_VSET               11
#define AUDIO_CODEC_MASK_MICBIAS_VSET                ((u32)0x00000003 << 11)                             /*!<R/W 0  MICBIAS select output voltage level 00:0.9*AVDD 01:0.86*AVDD (for AVDD=1.8v) 10:0.75*AVDD 11:reserved */
#define AUDIO_CODEC_SHIFT_MICBIAS_POW                10
#define AUDIO_CODEC_BIT_MICBIAS_POW                  ((u32)0x00000001 << 10)                             /*!<R/W 0  MICBIAS power control 0:power down 1:power on */
#define AUDIO_CODEC_SHIFT_MICBIAS_ENCHX              9
#define AUDIO_CODEC_BIT_MICBIAS_ENCHX                ((u32)0x00000001 << 9)                              /*!<R/W 1  MICBIAS enable chopper clock 0:disable 1:enable */
#define AUDIO_CODEC_SHIFT_MBIAS_POW                  8
#define AUDIO_CODEC_BIT_MBIAS_POW                    ((u32)0x00000001 << 8)                              /*!<R/W 0  MBIAS power control 0: power down 1: power on */
#define AUDIO_CODEC_SHIFT_HPO_SEL                    6
#define AUDIO_CODEC_BIT_HPO_SEL                      ((u32)0x00000001 << 6)                              /*!<R/W 1  Headphone left channel single-end mode control (0: differential, 1: single-end) */
#define AUDIO_CODEC_SHIFT_HPO_ML                     0
#define AUDIO_CODEC_MASK_HPO_ML                      ((u32)0x00000003 << 0)                              /*!<R/W 11  Headphone left channel mute control (0: un-mute, 1: mute), <0>: DAC, <1>: Analog in */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_03H
 * @brief  index_03h                                 (@ 0X006)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_HPO_GSELL                  12
#define AUDIO_CODEC_MASK_HPO_GSELL                   ((u32)0x00000003 << 12)                             /*!<R/W 0  invalid */
#define AUDIO_CODEC_SHIFT_VREF_VREFSEL               10
#define AUDIO_CODEC_MASK_VREF_VREFSEL                ((u32)0x00000003 << 10)                             /*!<R/W 10  VREF voltage selection 00: 0.52*VDD 01: 0.51*VDD 10: 0.50*VDD (default) 11: 0.49*VDD */
#define AUDIO_CODEC_SHIFT_MICBST_POW                 9
#define AUDIO_CODEC_BIT_MICBST_POW                   ((u32)0x00000001 << 9)                              /*!<R/W 0  MICBST power control pow<0>: right channel pow<1>: left channel 0:power down 1:power on */
#define AUDIO_CODEC_SHIFT_MICBST_MUTE_L              4
#define AUDIO_CODEC_MASK_MICBST_MUTE_L               ((u32)0x00000003 << 4)                              /*!<R/W 11  MICBST mute control mute<0>: mic in mute<1>: line in 0:unmute 1:mute */
#define AUDIO_CODEC_SHIFT_MICBST_GSELL               0
#define AUDIO_CODEC_MASK_MICBST_GSELL                ((u32)0x00000003 << 0)                              /*!<R/W 0  MICBST left channel gain select 00: 0dB 01:20dB 10:30dB 11:40dB */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_04H
 * @brief  index_04h                                 (@ 0X008)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_MICBIAS_POWSHDT            14
#define AUDIO_CODEC_BIT_MICBIAS_POWSHDT              ((u32)0x00000001 << 14)                             /*!<R/W 0  MICMIAS OCP power control 0: disable OCP 1: enable OCP */
#define AUDIO_CODEC_SHIFT_MICBIAS_OCSEL              12
#define AUDIO_CODEC_MASK_MICBIAS_OCSEL               ((u32)0x00000003 << 12)                             /*!<R/W 1  OCP current selection 00: 2.5mA 01: 5mA 10: 7.5mA 11: 10mA */
#define AUDIO_CODEC_SHIFT_MICBIAS_COUNT              8
#define AUDIO_CODEC_MASK_MICBIAS_COUNT               ((u32)0x0000000F << 8)                              /*!<R/W 1  when OCP happen disable time @312.5kHz 0000: 819.2us 0001: 1638.4us 0010: 3276.8us 0011: 6553.6us */
#define AUDIO_CODEC_SHIFT_REG_HPO_BIAS               6
#define AUDIO_CODEC_MASK_REG_HPO_BIAS                ((u32)0x00000003 << 6)                              /*!<R/W 0  HPO driving current control */
#define AUDIO_CODEC_SHIFT_DEBUG_BUS_SEL              0
#define AUDIO_CODEC_MASK_DEBUG_BUS_SEL               ((u32)0x0000001F << 0)                              /*!<R/W 0  2'b00: debug_bus_a; 2'b01: debug_bus_b; 2'b10: debug_bus_c; 2'b11: debug_bus_d; */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_0AH
 * @brief  index_0ah                                 (@ 0X014)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_LPF_RD               0
#define AUDIO_CODEC_MASK_ADC_L_LPF_RD                ((u32)0x0000FFFF << 0)                              /*!<R 0   LCH adc lpf out valus: format S(16,15) */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_0BH
 * @brief  index_0bh                                 (@ 0X016)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_LPF_RD               0
#define AUDIO_CODEC_MASK_ADC_R_LPF_RD                ((u32)0x0000FFFF << 0)                              /*!<R 0   RCH adc lpf out valus: format S(16,23) */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_0CH
 * @brief  index_0ch                                 (@ 0X018)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_CKX_MICBIAS_EN             4
#define AUDIO_CODEC_BIT_CKX_MICBIAS_EN               ((u32)0x00000001 << 4)                              /*!<R/W 0  1'b1: enable ckx_micbias to be 312.5KHz */
#define AUDIO_CODEC_SHIFT_BB_CK_DEPOP_EN             3
#define AUDIO_CODEC_BIT_BB_CK_DEPOP_EN               ((u32)0x00000001 << 3)                              /*!<R/W 0  1'b1: enable ck_depop  */
#define AUDIO_CODEC_SHIFT_MICBIAS_OC                 2
#define AUDIO_CODEC_BIT_MICBIAS_OC                   ((u32)0x00000001 << 2)                              /*!<R 0  the status flag of MICBIAS over-current protection */
#define AUDIO_CODEC_SHIFT_SEL_BB_CK_DEPOP            0
#define AUDIO_CODEC_MASK_SEL_BB_CK_DEPOP             ((u32)0x00000003 << 0)                              /*!<R/W 1  2'b00: ck_depop=40MHz/1024, 2'b01: ck_depop=40MHz/2048 2'b10: ck_depop=40MHz/4096, 2'b11: ck_depop=40MHz/8192 */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_0DH
 * @brief  index_0dh                                 (@ 0X01A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ST_L_DS_EN                 6
#define AUDIO_CODEC_BIT_ST_L_DS_EN                   ((u32)0x00000001 << 6)                              /*!<R/W 0  sidetone L path clock enable after EQ : 0:disable 1:enable */
#define AUDIO_CODEC_SHIFT_ST_L_DS_MUTE_EN            5
#define AUDIO_CODEC_BIT_ST_L_DS_MUTE_EN              ((u32)0x00000001 << 5)                              /*!<R/W 1  sidetone L path mute enable after EQ : 0:disable 1:enable */
#define AUDIO_CODEC_SHIFT_SIDETON_L_IN_SEL           0
#define AUDIO_CODEC_MASK_SIDETON_L_IN_SEL            ((u32)0x00000003 << 0)                              /*!<R/W 0  sideton_l_in_sel[0] 1'b0 source from uplink channel L; 1'b1 source from uplink channel R */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_0EH
 * @brief  index_0eh                                 (@ 0X01C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_SIDETONE_L_ZDET_FUNC       14
#define AUDIO_CODEC_MASK_SIDETONE_L_ZDET_FUNC        ((u32)0x00000003 << 14)                             /*!<R/W 0  2'b0:immediate change 2'b01: zero detection enable 2'b10: zero detection step change */
#define AUDIO_CODEC_SHIFT_SIDETONE_L_ZDET_TOUT       12
#define AUDIO_CODEC_MASK_SIDETONE_L_ZDET_TOUT        ((u32)0x00000003 << 12)                             /*!<R/W 0  After EQ(samples =fs ): 2'b00: 1024*16 samples 2'b01: 1024*32 samples 2'b10: 1024*64 samples 2'b11: 256 samples  */
#define AUDIO_CODEC_SHIFT_SIDETONE_L_BOOST_SEL       11
#define AUDIO_CODEC_BIT_SIDETONE_L_BOOST_SEL         ((u32)0x00000001 << 11)                             /*!<R/W 0  sidetone boost select 1'b1 : +12.04dB 1'b0 : + 0dB  */
#define AUDIO_CODEC_SHIFT_SIDETONE_L_VOL_SEL         4
#define AUDIO_CODEC_MASK_SIDETONE_L_VOL_SEL          ((u32)0x0000007F << 4)                              /*!<R/W 0  sidetone volume select ~0.375db/step 7'h7f : 0B ~ 7'h00 : -47.625db  */
#define AUDIO_CODEC_SHIFT_SIDETONE_L_HPF_FC_SEL      1
#define AUDIO_CODEC_MASK_SIDETONE_L_HPF_FC_SEL       ((u32)0x00000007 << 1)                              /*!<R/W 0  sidetone HPF cut-off frequency select (-6dB) 3'b000 : fc = 2.925e-3*fs, 3'b001 : fc = 1.4625e-3*fs 3'b010 : fc = 7.3125e-4*fs, 3'b011 : fc = 3.65625e-4*fs 3'b100 : fc = 1.828e-4*fs, 3'b101 : fc = 9.14e-5*fs 3'b110 : fc = 4.57e-5*fs, 3'b111 : fc = 2.285e-5*fs */
#define AUDIO_CODEC_SHIFT_SIDETONE_L_HPF_EN          0
#define AUDIO_CODEC_BIT_SIDETONE_L_HPF_EN            ((u32)0x00000001 << 0)                              /*!<R/W 0  sidetone processing enable control for 1'b1 : enable sidetone HPF processing 1'b0 : disable sidetone HPF processing  */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_0FH
 * @brief  index_0fh                                 (@ 0X01E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_SIDETONE_R_ZDET_FUNC       14
#define AUDIO_CODEC_MASK_SIDETONE_R_ZDET_FUNC        ((u32)0x00000003 << 14)                             /*!<R/W 0   2'b0:immediate change 2'b01: zero detection enable 2'b10: zero detection step change */
#define AUDIO_CODEC_SHIFT_SIDETONE_R_ZDET_TOUT       12
#define AUDIO_CODEC_MASK_SIDETONE_R_ZDET_TOUT        ((u32)0x00000003 << 12)                             /*!<R/W 0  After EQ(samples =fs ): 2'b00: 1024*16 samples 2'b01: 1024*32 samples 2'b10: 1024*64 samples 2'b11: 256 samples  */
#define AUDIO_CODEC_SHIFT_SIDETONE_R_BOOST_SEL       11
#define AUDIO_CODEC_BIT_SIDETONE_R_BOOST_SEL         ((u32)0x00000001 << 11)                             /*!<R/W 0  sidetone boost select 1'b1 : +12dB 1'b0 : + 0dB  */
#define AUDIO_CODEC_SHIFT_SIDETONE_R_VOL_SEL         4
#define AUDIO_CODEC_MASK_SIDETONE_R_VOL_SEL          ((u32)0x0000007F << 4)                              /*!<R/W 0  sidetone volume select ~0.375db/step 7'h7f : 0B ~ 7'h00 : -47.625db  */
#define AUDIO_CODEC_SHIFT_SIDETONE_R_HPF_FC_SEL      1
#define AUDIO_CODEC_MASK_SIDETONE_R_HPF_FC_SEL       ((u32)0x00000007 << 1)                              /*!<R/W 0  sidetone HPF cut-off frequency select (-6dB) 3'b000 : fc = 2.925e-3*fs, 3'b001 : fc = 1.4625e-3*fs 3'b010 : fc = 7.3125e-4*fs, 3'b011 : fc = 3.65625e-4*fs 3'b100 : fc = 1.828e-4*fs, 3'b101 : fc = 9.14e-5*fs 3'b110 : fc = 4.57e-5*fs, 3'b111 : fc = 2.285e-5*fs */
#define AUDIO_CODEC_SHIFT_SIDETONE_R_HPF_EN          0
#define AUDIO_CODEC_BIT_SIDETONE_R_HPF_EN            ((u32)0x00000001 << 0)                              /*!<R/W 0  sidetone processing enable control 1'b1 : enable sidetone HPF processing 1'b0 : disable sidetone HPF processing  */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_10H
 * @brief  index_10h                                 (@ 0X020)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_I2S_DATA_LEN_SEL_RX        14
#define AUDIO_CODEC_MASK_I2S_DATA_LEN_SEL_RX         ((u32)0x00000003 << 14)                             /*!<R/W 0  2'b00: 16 bits; 2'b10: 24 bits; 2'b11: 8 bits; */
#define AUDIO_CODEC_SHIFT_I2S_SAME_LRC               13
#define AUDIO_CODEC_BIT_I2S_SAME_LRC                 ((u32)0x00000001 << 13)                             /*!<R/W 0  1'b1: DA/AD both use lrc_tx 1'b0: separate DA/AD lrc for different sample rate */
#define AUDIO_CODEC_SHIFT_STEREO_I2S_SELF_LPBK_EN    12
#define AUDIO_CODEC_BIT_STEREO_I2S_SELF_LPBK_EN      ((u32)0x00000001 << 12)                             /*!<R/W 0  1'b1: internal loopback mode is enabled */
#define AUDIO_CODEC_SHIFT_SEL_I2S_TX_CH              10
#define AUDIO_CODEC_MASK_SEL_I2S_TX_CH               ((u32)0x00000003 << 10)                             /*!<R/W 0  2'b00: L/R; 2'b01: R/L; 2'b10: L/L; 2'b11: R/R @ DAC path */
#define AUDIO_CODEC_SHIFT_SEL_I2S_RX_CH              8
#define AUDIO_CODEC_MASK_SEL_I2S_RX_CH               ((u32)0x00000003 << 8)                              /*!<R/W 0  2'b00: L/R; 2'b01: R/L; 2'b10: L/L; 2'b11: R/R @ ADC path */
#define AUDIO_CODEC_SHIFT_I2S_RST_N_REG              7
#define AUDIO_CODEC_BIT_I2S_RST_N_REG                ((u32)0x00000001 << 7)                              /*!<R/W 0  1'b1: rst_n to audio digital IP is de-asserted; 1'b0: rst_n to audio digital IP is asserted */
#define AUDIO_CODEC_SHIFT_INV_I2S_SCLK               6
#define AUDIO_CODEC_BIT_INV_I2S_SCLK                 ((u32)0x00000001 << 6)                              /*!<R/W 0  1'b1: I2S/PCM bit clock is inverted */
#define AUDIO_CODEC_SHIFT_I2S_DATA_LEN_SEL_TX        4
#define AUDIO_CODEC_MASK_I2S_DATA_LEN_SEL_TX         ((u32)0x00000003 << 4)                              /*!<R/W 0  2'b00: 16 bits; 2'b10: 24 bits; 2'b11: 8 bits; */
#define AUDIO_CODEC_SHIFT_I2S_DATA_FORMAT_SEL_RX     2
#define AUDIO_CODEC_MASK_I2S_DATA_FORMAT_SEL_RX      ((u32)0x00000003 << 2)                              /*!<R/W 0  2b00: I2S; 2'b01: Left Justified; 2'b10: PCM mode A; 2'b11: PCM mode B;  */
#define AUDIO_CODEC_SHIFT_I2S_DATA_FORMAT_SEL_TX     0
#define AUDIO_CODEC_MASK_I2S_DATA_FORMAT_SEL_TX      ((u32)0x00000003 << 0)                              /*!<R/W 0  2b00: I2S; 2'b01: Left Justified; 2'b10: PCM mode A; 2'b11: PCM mode B;  */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_11H
 * @brief  index_11h                                 (@ 0X022)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_AD_DCHPF_EN          14
#define AUDIO_CODEC_BIT_ADC_L_AD_DCHPF_EN            ((u32)0x00000001 << 14)                             /*!<R/W 1  High pass filter enable control (filter DC): 0: disable 1: enable */
#define AUDIO_CODEC_SHIFT_ADC_L_DMIC_MIX_MUTE        13
#define AUDIO_CODEC_BIT_ADC_L_DMIC_MIX_MUTE          ((u32)0x00000001 << 13)                             /*!<R/W 1  DMIC input path mute control Left Channel: 0: Un-Mute 1: Mute */
#define AUDIO_CODEC_SHIFT_ADC_L_AD_MIX_MUTE          12
#define AUDIO_CODEC_BIT_ADC_L_AD_MIX_MUTE            ((u32)0x00000001 << 12)                             /*!<R/W 1  analog ADC input path mute control Left Channel: 0: Un-Mute 1: Mute */
#define AUDIO_CODEC_SHIFT_ADC_L_AD_LPF1ST_FC_SEL     10
#define AUDIO_CODEC_MASK_ADC_L_AD_LPF1ST_FC_SEL      ((u32)0x00000003 << 10)                             /*!<R/W 0  ADC SRC 1st LPF fc: 00b:31.04khz, 01b:46.92khz, 10b:63.06khz, 11b:79.45khz */
#define AUDIO_CODEC_SHIFT_ADC_L_AD_LPF1ST_EN         9
#define AUDIO_CODEC_BIT_ADC_L_AD_LPF1ST_EN           ((u32)0x00000001 << 9)                              /*!<R/W 1  ADC SRC 1st LPF control: 0: disable 1: enable  */
#define AUDIO_CODEC_SHIFT_ADC_L_AD_LPF2ND_EN         8
#define AUDIO_CODEC_BIT_ADC_L_AD_LPF2ND_EN           ((u32)0x00000001 << 8)                              /*!<R/W 1  ADC SRC 2nd LPF control: 0: disable 1: enable  */
#define AUDIO_CODEC_SHIFT_ADC_L_DMIC_LPF1ST_FC_SEL   5
#define AUDIO_CODEC_MASK_ADC_L_DMIC_LPF1ST_FC_SEL    ((u32)0x00000003 << 5)                              /*!<R/W 0  DMIC SRC 1st LPF fc: 00b:31.04khz, 01b:46.92khz, 10b:63.06khz, 11b:79.45khz */
#define AUDIO_CODEC_SHIFT_ADC_L_DMIC_LPF1ST_EN       4
#define AUDIO_CODEC_BIT_ADC_L_DMIC_LPF1ST_EN         ((u32)0x00000001 << 4)                              /*!<R/W 1  DMIC SRC 1st LPF control: 0: disable 1: enable  */
#define AUDIO_CODEC_SHIFT_ADC_L_DMIC_LPF2ND_EN       3
#define AUDIO_CODEC_BIT_ADC_L_DMIC_LPF2ND_EN         ((u32)0x00000001 << 3)                              /*!<R/W 1  DMIC SRC 2nd LPF control: 0: disable 1: enable  */
#define AUDIO_CODEC_SHIFT_ADC_L_DMIC_SRC_SEL         0
#define AUDIO_CODEC_MASK_ADC_L_DMIC_SRC_SEL          ((u32)0x00000003 << 0)                              /*!<R/W 0  DMIC Data source selection: 2'b00: MIC 1 rising 2'b01: MIC 1 falling 2'b10: MIC 1 rising 2'b11: MIC 1 falling */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_12H
 * @brief  index_12h                                 (@ 0X024)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_AD_SRC_SEL           13
#define AUDIO_CODEC_MASK_ADC_L_AD_SRC_SEL            ((u32)0x00000003 << 13)                             /*!<R/W 0  ADC Data source selection: 2'b00: ADC1 2'b01: ADC 2 2'b10: ADC 3 2'b11: ADC1 */
#define AUDIO_CODEC_SHIFT_ADC_L_AD_ZDET_TOUT         11
#define AUDIO_CODEC_MASK_ADC_L_AD_ZDET_TOUT          ((u32)0x00000003 << 11)                             /*!<R/W 1  ADC zero detection time out select: 2'b00 : 1024*16 samples 2'b01 : 1024*32 samples 2'b10 : 1024*64 samples 2'b11 : 64 samples */
#define AUDIO_CODEC_SHIFT_ADC_L_AD_ZDET_FUNC         9
#define AUDIO_CODEC_MASK_ADC_L_AD_ZDET_FUNC          ((u32)0x00000003 << 9)                              /*!<R/W 1  ADC zero detection function select: 2'b00 : immediate change 2'b01 : zero detection & immediate change 2'b10 : zero detection & step change 2'b11 : unchange */
#define AUDIO_CODEC_SHIFT_ADC_L_AD_MUTE              8
#define AUDIO_CODEC_BIT_ADC_L_AD_MUTE                ((u32)0x00000001 << 8)                              /*!<R/W 0  Digital Mute From ADC Left Channel Digital Mixer: 0: Un-Mute 1: Mute */
#define AUDIO_CODEC_SHIFT_ADC_L_DMIC_BOOST_GAIN      6
#define AUDIO_CODEC_MASK_ADC_L_DMIC_BOOST_GAIN       ((u32)0x00000003 << 6)                              /*!<R/W 0  DMIC boost gain control: 0:0dB 1:12dB 2:24dB 3:36dB */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_13H
 * @brief  index_13h                                 (@ 0X026)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_DCHPF_FC_SEL         13
#define AUDIO_CODEC_MASK_ADC_L_DCHPF_FC_SEL          ((u32)0x00000007 << 13)                             /*!<R/W 0x5  -6db cut off freq: 3'b000 : fc = 2.925e-3*fs, 3'b001 : fc = 1.4625e-3*fs 3'b010 : fc = 7.3125e-4*fs, 3'b011 : fc = 3.65625e-4*fs 3'b100 : fc = 1.828e-4*fs, 3'b101 : fc = 9.14e-5*fs 3'b110 : fc = 4.57e-5*fs, 3'b111 : fc = 2.285e-5*fs */
#define AUDIO_CODEC_SHIFT_ADC_L_AD_GAIN              6
#define AUDIO_CODEC_MASK_ADC_L_AD_GAIN               ((u32)0x0000007F << 6)                              /*!<R/W 0x2F  ADC digital volume -17.625dB~+30dB in 0.375 dB step (7'h00:-17.625dB, xxx, 7'h2f:0dB, 7'h30:0.375dB, xxx , 7'h7f:30dB) */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_14H
 * @brief  index_14h                                 (@ 0X028)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_AD_DCHPF_EN          14
#define AUDIO_CODEC_BIT_ADC_R_AD_DCHPF_EN            ((u32)0x00000001 << 14)                             /*!<R/W 1  High pass filter enable control (filter DC): 0: disable 1: enable */
#define AUDIO_CODEC_SHIFT_ADC_R_DMIC_MIX_MUTE        13
#define AUDIO_CODEC_BIT_ADC_R_DMIC_MIX_MUTE          ((u32)0x00000001 << 13)                             /*!<R/W 1  DMIC input path mute control Left Channel: 0: Un-Mute 1: Mute */
#define AUDIO_CODEC_SHIFT_ADC_R_AD_MIX_MUTE          12
#define AUDIO_CODEC_BIT_ADC_R_AD_MIX_MUTE            ((u32)0x00000001 << 12)                             /*!<R/W 1  analog ADC input path mute control Left Channel: 0: Un-Mute 1: Mute */
#define AUDIO_CODEC_SHIFT_ADC_R_AD_LPF1ST_FC_SEL     10
#define AUDIO_CODEC_MASK_ADC_R_AD_LPF1ST_FC_SEL      ((u32)0x00000003 << 10)                             /*!<R/W 0  ADC SRC 1st LPF fc: 00b:31.04khz, 01b:46.92khz, 10b:63.06khz, 11b:79.45khz */
#define AUDIO_CODEC_SHIFT_ADC_R_AD_LPF1ST_EN         9
#define AUDIO_CODEC_BIT_ADC_R_AD_LPF1ST_EN           ((u32)0x00000001 << 9)                              /*!<R/W 1  ADC SRC 1st LPF control: 0: disable 1: enable  */
#define AUDIO_CODEC_SHIFT_ADC_R_AD_LPF2ND_EN         8
#define AUDIO_CODEC_BIT_ADC_R_AD_LPF2ND_EN           ((u32)0x00000001 << 8)                              /*!<R/W 1  ADC SRC 2nd LPF control: 0: disable 1: enable  */
#define AUDIO_CODEC_SHIFT_ADC_R_DMIC_LPF1ST_FC_SEL   5
#define AUDIO_CODEC_MASK_ADC_R_DMIC_LPF1ST_FC_SEL    ((u32)0x00000003 << 5)                              /*!<R/W 0  DMIC SRC 1st LPF fc: 00b:31.04khz, 01b:46.92khz, 10b:63.06khz, 11b:79.45khz */
#define AUDIO_CODEC_SHIFT_ADC_R_DMIC_LPF1ST_EN       4
#define AUDIO_CODEC_BIT_ADC_R_DMIC_LPF1ST_EN         ((u32)0x00000001 << 4)                              /*!<R/W 1  DMIC SRC 1st LPF control: 0: disable 1: enable  */
#define AUDIO_CODEC_SHIFT_ADC_R_DMIC_LPF2ND_EN       3
#define AUDIO_CODEC_BIT_ADC_R_DMIC_LPF2ND_EN         ((u32)0x00000001 << 3)                              /*!<R/W 1  DMIC SRC 2nd LPF control: 0: disable 1: enable  */
#define AUDIO_CODEC_SHIFT_ADC_R_DMIC_SRC_SEL         0
#define AUDIO_CODEC_MASK_ADC_R_DMIC_SRC_SEL          ((u32)0x00000003 << 0)                              /*!<R/W 1  DMIC Data source selection: 2'b00: MIC 1 rising 2'b01: MIC 1 falling 2'b10: MIC 2 rising 2'b11: MIC 2 falling */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_15H
 * @brief  index_15h                                 (@ 0X02A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_AD_SRC_SEL           13
#define AUDIO_CODEC_MASK_ADC_R_AD_SRC_SEL            ((u32)0x00000003 << 13)                             /*!<R/W 1  ADC Data source selection: 2'b00: ADC1 2'b01: ADC 2 2'b10: ADC 3 2'b11: ADC1 */
#define AUDIO_CODEC_SHIFT_ADC_R_AD_ZDET_TOUT         11
#define AUDIO_CODEC_MASK_ADC_R_AD_ZDET_TOUT          ((u32)0x00000003 << 11)                             /*!<R/W 1  ADC zero detection time out select: 2'b00 : 1024*16 samples 2'b01 : 1024*32 samples 2'b10 : 1024*64 samples 2'b11 : 64 samples */
#define AUDIO_CODEC_SHIFT_ADC_R_AD_ZDET_FUNC         9
#define AUDIO_CODEC_MASK_ADC_R_AD_ZDET_FUNC          ((u32)0x00000003 << 9)                              /*!<R/W 1  ADC zero detection function select: 2'b00 : immediate change 2'b01 : zero detection & immediate change 2'b10 : unchange 2'b11 : unchange */
#define AUDIO_CODEC_SHIFT_ADC_R_AD_MUTE              8
#define AUDIO_CODEC_BIT_ADC_R_AD_MUTE                ((u32)0x00000001 << 8)                              /*!<R/W 0  Digital mute from ADC right cheannel digital mixer, 0:un-mute, 1:mute */
#define AUDIO_CODEC_SHIFT_ADC_R_DMIC_BOOST_GAIN      6
#define AUDIO_CODEC_MASK_ADC_R_DMIC_BOOST_GAIN       ((u32)0x00000003 << 6)                              /*!<R/W 0  DMIC boost gain control: 00'b : 0dB 01'b: 12dB 10'b : 24dB 11'b: 36dB */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_16H
 * @brief  index_16h                                 (@ 0X02C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_DCHPF_FC_SEL         13
#define AUDIO_CODEC_MASK_ADC_R_DCHPF_FC_SEL          ((u32)0x00000007 << 13)                             /*!<R/W 0x5  -3db cut off freq: 3'd0:0.01 * fs 3'd1:5e-3 * fs 3'd2:2.5e-3 *fs 3'd3:1.25e-3 *fs 3'd4: 6.25e-4 *fs 3'd5:3.125e-4*fs 3'd6: 1.5625e-4 *fs 3'd7:7.8125-5*fs */
#define AUDIO_CODEC_SHIFT_ADC_R_AD_GAIN              6
#define AUDIO_CODEC_MASK_ADC_R_AD_GAIN               ((u32)0x0000007F << 6)                              /*!<R/W 0x2F  ADC digital volume -17.625dB~+30dB in 0.375 dB step (7'h00:-17.625dB, xxx, 7'h2f:0dB, 7'h30:0.375dB, xxx , 7'h7f:30dB) */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_17H
 * @brief  index_17h                                 (@ 0X02E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADDA_SAME_FS_EN            15
#define AUDIO_CODEC_BIT_ADDA_SAME_FS_EN              ((u32)0x00000001 << 15)                             /*!<R/W 0  1'b1 : AD/DA use same sample rate (adc_sample_rate and asrc_rx is useless ) */
#define AUDIO_CODEC_SHIFT_ASRC_FTK_LOOP_GAIN_SEL_TX  13
#define AUDIO_CODEC_MASK_ASRC_FTK_LOOP_GAIN_SEL_TX   ((u32)0x00000003 << 13)                             /*!<R/W 0x3  set loop gain: 2'b00 :2^-8 2'b01:2^-14 2'b10:2^-18 2'b11:2^-20  */
#define AUDIO_CODEC_SHIFT_ASRC_RATE_SEL_RX           12
#define AUDIO_CODEC_BIT_ASRC_RATE_SEL_RX             ((u32)0x00000001 << 12)                             /*!<R/W 0  (1) If ASRC is enabled,adc_sample_rate @0x17[7:4] become useless. (2)If asrc_rate_sel=1'h0 (ASRC output rate @48KHz), I2S word clock rate can be 2KHz ~ 60KHz (3) If asrc_rate_sel=1'h1 (ASRC output rate @96KHz), I2S word clock rate can be 4KHz ~ 120KHz */
#define AUDIO_CODEC_SHIFT_ASRC_RATE_SEL_TX           11
#define AUDIO_CODEC_BIT_ASRC_RATE_SEL_TX             ((u32)0x00000001 << 11)                             /*!<R/W 0  (1) If ASRC is enabled, dac_sample_rate @0x17[3:0] become useless. (2)If asrc_rate_sel=1'h0 (ASRC output rate @48KHz), I2S word clock rate can be 2KHz ~ 60KHz (3) If asrc_rate_sel=1'h1 (ASRC output rate @96KHz), I2S word clock rate can be 4KHz ~ 120KHz */
#define AUDIO_CODEC_SHIFT_DMIC1_CLK_SEL              8
#define AUDIO_CODEC_MASK_DMIC1_CLK_SEL               ((u32)0x00000007 << 8)                              /*!<R/W 1  set clock of digital microphone: 3'b000: 5MHz, 3'b001: 2.5MHz, 3'b010: 1.25MHz, 3'b011: 625kHz, 3'b100: 312.5kHz */
#define AUDIO_CODEC_SHIFT_ADC_SAMPLE_RATE            4
#define AUDIO_CODEC_MASK_ADC_SAMPLE_RATE             ((u32)0x0000000F << 4)                              /*!<R/W 0  set ADC sample rate: 4'h0: 48K, 4'h1: 96K, 4'h2: reserved, 4'h3: 32K 4'h4: reserved, 4'h5: 16K, 4'h6: reserved, 4'h7: 8K 4'h8: 44.1K, 4'h9: 88.2K, 4'hA~4'hF:reserved */
#define AUDIO_CODEC_SHIFT_DAC_SAMPLE_RATE            0
#define AUDIO_CODEC_MASK_DAC_SAMPLE_RATE             ((u32)0x0000000F << 0)                              /*!<R/W 0  set DAC sample rate: 4'h0: 48K, 4'h1: 96K, 4'h2: reserved, 4'h3: 32K 4'h4: reserved, 4'h5: 16K, 4'h6: reserved, 4'h7: 8K 4'h8: 44.1K, 4'h9: 88.2K, 4'hA~4'hF:reserved */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_18H
 * @brief  index_18h                                 (@ 0X030)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DMIC_CLK_EN                15
#define AUDIO_CODEC_BIT_DMIC_CLK_EN                  ((u32)0x00000001 << 15)                             /*!<R/W 0  set digital MIC clock: 1'b0 : turn off clock 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_DMIC_R_EN                  14
#define AUDIO_CODEC_BIT_DMIC_R_EN                    ((u32)0x00000001 << 14)                             /*!<R/W 0  set ADC filter right channel digital MIC pathclock: 1'b0 : turn off clock and reset 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_DMIC_L_EN                  13
#define AUDIO_CODEC_BIT_DMIC_L_EN                    ((u32)0x00000001 << 13)                             /*!<R/W 0  set ADC filter left channel digital MIC path clock: 1'b0 : turn off clock and reset 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_AD_ANA_R_EN                12
#define AUDIO_CODEC_BIT_AD_ANA_R_EN                  ((u32)0x00000001 << 12)                             /*!<R/W 0  set ADC filter right channel analog ADC pathclock: 1'b0 : turn off clock and reset 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_AD_ANA_L_EN                11
#define AUDIO_CODEC_BIT_AD_ANA_L_EN                  ((u32)0x00000001 << 11)                             /*!<R/W 0  set ADC filter left channel analog ADC path clock: 1'b0 : turn off clock and reset 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_AD_ANA_CLK_EN              10
#define AUDIO_CODEC_BIT_AD_ANA_CLK_EN                ((u32)0x00000001 << 10)                             /*!<R/W 0  set ADC analog clock: 1'b0 : turn off clock 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_AD_FIFO_EN                 9
#define AUDIO_CODEC_BIT_AD_FIFO_EN                   ((u32)0x00000001 << 9)                              /*!<R/W 0  set ADC fifo clock: 1'b0 : turn off clock and reset 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_AD_R_EN                    8
#define AUDIO_CODEC_BIT_AD_R_EN                      ((u32)0x00000001 << 8)                              /*!<R/W 0  set ADC filter right channel clock: 1'b0 : turn off clock and reset 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_AD_L_EN                    7
#define AUDIO_CODEC_BIT_AD_L_EN                      ((u32)0x00000001 << 7)                              /*!<R/W 0  set ADC filter left channel clock: 1'b0 : turn off clock and reset 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_DA_FIFO_EN                 5
#define AUDIO_CODEC_BIT_DA_FIFO_EN                   ((u32)0x00000001 << 5)                              /*!<R/W 0  set DAC fifo clock: 1'b0 : turn off clock and reset 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_DA_ANA_CLK_EN              4
#define AUDIO_CODEC_BIT_DA_ANA_CLK_EN                ((u32)0x00000001 << 4)                              /*!<R/W 0  set DAC analog clock: 1'b0 : turn off clock 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_MOD_L_EN                   2
#define AUDIO_CODEC_BIT_MOD_L_EN                     ((u32)0x00000001 << 2)                              /*!<R/W 0  set DAC modulation left channel clock: 1'b0 : turn off clock and reset 1'b1: turn on clock  */
#define AUDIO_CODEC_SHIFT_DA_L_EN                    0
#define AUDIO_CODEC_BIT_DA_L_EN                      ((u32)0x00000001 << 0)                              /*!<R/W 0  set DAC filter left channel clock: 1'b0 : turn off clock and reset 1'b1: turn on clock  */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_19H
 * @brief  index_19h                                 (@ 0X032)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ASRC_FTK_SDM_INI_TX        0
#define AUDIO_CODEC_MASK_ASRC_FTK_SDM_INI_TX         ((u32)0x0000FFFF << 0)                              /*!<R/W 0  set initial value of tracked frequency */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_1AH
 * @brief  index_1ah                                 (@ 0X034)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ASRC_FTK_SDM_INI_RX        0
#define AUDIO_CODEC_MASK_ASRC_FTK_SDM_INI_RX         ((u32)0x0000FFFF << 0)                              /*!<R/W 0  set initial value of tracked frequency */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_1BH
 * @brief  index_1bh                                 (@ 0X036)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ASRC_FTK_LOOP_GAIN_SEL_RX  14
#define AUDIO_CODEC_MASK_ASRC_FTK_LOOP_GAIN_SEL_RX   ((u32)0x00000003 << 14)                             /*!<R/W 0x3  set loop gain: 2'b00 :2^-8 2'b01:2^-14 2'b10:2^-18 2'b11:2^-20  */
#define AUDIO_CODEC_SHIFT_AD_ANA_CLK_SEL             13
#define AUDIO_CODEC_BIT_AD_ANA_CLK_SEL               ((u32)0x00000001 << 13)                             /*!<R/W 0  set clk_ad_ana phase ( reference clk_da_ana): 1'b0 : inphase 1'b1: inverse phase  */
#define AUDIO_CODEC_SHIFT_DA_ANA_CLK_SEL             12
#define AUDIO_CODEC_BIT_DA_ANA_CLK_SEL               ((u32)0x00000001 << 12)                             /*!<R/W 0  set clk_da_ana phase : 1'b0 : inphase 1'b1: inverse phase  */
#define AUDIO_CODEC_SHIFT_ADC_LATCH_PHASE            7
#define AUDIO_CODEC_BIT_ADC_LATCH_PHASE              ((u32)0x00000001 << 7)                              /*!<R/W 0  set latch adc data phase : 1'b0 : inphase 1'b1: inverse phase  */
#define AUDIO_CODEC_SHIFT_ASRC_RX_EN                 4
#define AUDIO_CODEC_BIT_ASRC_RX_EN                   ((u32)0x00000001 << 4)                              /*!<R/W 0  set asynchronous sample rate conversion: 1'b0: disable 1'b1:enable */
#define AUDIO_CODEC_SHIFT_ASRC_TX_EN                 3
#define AUDIO_CODEC_BIT_ASRC_TX_EN                   ((u32)0x00000001 << 3)                              /*!<R/W 0  set asynchronous sample rate conversion: 1'b0: disable 1'b1:enable */
#define AUDIO_CODEC_SHIFT_ASRC_AUTO_ADJUST_RX        2
#define AUDIO_CODEC_BIT_ASRC_AUTO_ADJUST_RX          ((u32)0x00000001 << 2)                              /*!<R/W 1  set HW auto adjust loop gain: 1'b0 : disable 1'b1: enable */
#define AUDIO_CODEC_SHIFT_ASRC_AUTO_ADJUST_TX        1
#define AUDIO_CODEC_BIT_ASRC_AUTO_ADJUST_TX          ((u32)0x00000001 << 1)                              /*!<R/W 1  set HW auto adjust loop gain: 1'b0 : disable 1'b1: enable */
#define AUDIO_CODEC_SHIFT_AUDIO_IP_TCON_EN           0
#define AUDIO_CODEC_BIT_AUDIO_IP_TCON_EN             ((u32)0x00000001 << 0)                              /*!<R/W 0  set audio ip tcon: 1'b0 : disable and reset 1'b1: enable */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_2BH
 * @brief  index_2bh                                 (@ 0X056)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_H0_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_H0_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 1st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_2CH
 * @brief  index_2ch                                 (@ 0X058)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_H0_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_H0_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  DAC Lch EQ 1st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_2DH
 * @brief  index_2dh                                 (@ 0X05A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B1_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B1_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 1st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_2EH
 * @brief  index_2eh                                 (@ 0X05C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B1_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B1_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 1st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_2FH
 * @brief  index_2fh                                 (@ 0X05E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B2_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B2_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 1st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_30H
 * @brief  index_30h                                 (@ 0X060)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B2_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B2_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 1st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_31H
 * @brief  index_31h                                 (@ 0X062)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A1_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A1_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 1st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_32H
 * @brief  index_32h                                 (@ 0X064)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A1_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A1_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 1st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_33H
 * @brief  index_33h                                 (@ 0X066)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A2_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A2_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 1st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_34H
 * @brief  index_34h                                 (@ 0X068)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_EN_1          13
#define AUDIO_CODEC_BIT_DAC_L_BIQUAD_EN_1            ((u32)0x00000001 << 13)                             /*!<R/W 0  DAC Lch 1st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A2_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A2_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 1st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_35H
 * @brief  index_35h                                 (@ 0X06A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_H0_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_H0_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 2st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_36H
 * @brief  index_36h                                 (@ 0X06C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_H0_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_H0_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  DAC Lch EQ 2st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_37H
 * @brief  index_37h                                 (@ 0X06E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B1_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B1_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 2st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_38H
 * @brief  index_38h                                 (@ 0X070)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B1_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B1_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 2st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_39H
 * @brief  index_39h                                 (@ 0X072)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B2_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B2_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 2st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_3AH
 * @brief  index_3ah                                 (@ 0X074)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B2_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B2_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 2st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_3BH
 * @brief  index_3bh                                 (@ 0X076)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A1_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A1_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 2st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_3CH
 * @brief  index_3ch                                 (@ 0X078)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A1_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A1_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 2st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_3DH
 * @brief  index_3dh                                 (@ 0X07A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A2_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A2_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 2st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_3EH
 * @brief  index_3eh                                 (@ 0X07C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_EN_2          13
#define AUDIO_CODEC_BIT_DAC_L_BIQUAD_EN_2            ((u32)0x00000001 << 13)                             /*!<R/W 0  DAC Lch 2st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A2_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A2_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 2st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_3FH
 * @brief  index_3fh                                 (@ 0X07E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_H0_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_H0_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 3st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_40H
 * @brief  index_40h                                 (@ 0X080)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_H0_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_H0_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  DAC Lch EQ 3st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_41H
 * @brief  index_41h                                 (@ 0X082)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B1_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B1_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 3st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_42H
 * @brief  index_42h                                 (@ 0X084)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B1_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B1_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 3st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_43H
 * @brief  index_43h                                 (@ 0X086)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B2_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B2_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 3st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_44H
 * @brief  index_44h                                 (@ 0X088)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B2_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B2_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 3st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_45H
 * @brief  index_45h                                 (@ 0X08A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A1_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A1_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 3st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_46H
 * @brief  index_46h                                 (@ 0X08C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A1_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A1_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 3st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_47H
 * @brief  index_47h                                 (@ 0X08E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A2_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A2_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 3st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_48H
 * @brief  index_48h                                 (@ 0X090)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_EN_3          13
#define AUDIO_CODEC_BIT_DAC_L_BIQUAD_EN_3            ((u32)0x00000001 << 13)                             /*!<R/W 0  DAC Lch 3st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A2_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A2_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 3st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_49H
 * @brief  index_49h                                 (@ 0X092)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_H0_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_H0_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 4st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_4AH
 * @brief  index_4ah                                 (@ 0X094)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_H0_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_H0_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  DAC Lch EQ 4st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_4BH
 * @brief  index_4bh                                 (@ 0X096)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B1_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B1_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 4st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_4CH
 * @brief  index_4ch                                 (@ 0X098)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B1_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B1_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 4st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_4DH
 * @brief  index_4dh                                 (@ 0X09A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B2_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B2_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 4st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_4EH
 * @brief  index_4eh                                 (@ 0X09C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B2_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B2_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 4st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_4FH
 * @brief  index_4fh                                 (@ 0X09E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A1_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A1_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 4st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_50H
 * @brief  index_50h                                 (@ 0X0A0)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A1_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A1_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 4st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_51H
 * @brief  index_51h                                 (@ 0X0A2)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A2_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A2_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 4st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_52H
 * @brief  index_52h                                 (@ 0X0A4)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_EN_4          13
#define AUDIO_CODEC_BIT_DAC_L_BIQUAD_EN_4            ((u32)0x00000001 << 13)                             /*!<R/W 0  DAC Lch 4st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A2_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A2_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 4st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_53H
 * @brief  index_53h                                 (@ 0X0A6)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_H0_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_H0_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 5st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_54H
 * @brief  index_54h                                 (@ 0X0A8)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_H0_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_H0_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  DAC Lch EQ 5st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_55H
 * @brief  index_55h                                 (@ 0X0AA)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B1_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B1_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 5st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_56H
 * @brief  index_56h                                 (@ 0X0AC)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B1_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B1_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 5st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_57H
 * @brief  index_57h                                 (@ 0X0AE)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B2_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B2_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 5st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_58H
 * @brief  index_58h                                 (@ 0X0B0)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_B2_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_B2_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 5st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_59H
 * @brief  index_59h                                 (@ 0X0B2)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A1_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A1_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 5st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_5AH
 * @brief  index_5ah                                 (@ 0X0B4)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A1_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A1_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 5st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_5BH
 * @brief  index_5bh                                 (@ 0X0B6)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A2_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A2_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  DAC Lch EQ 5st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_5CH
 * @brief  index_5ch                                 (@ 0X0B8)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_EN_5          13
#define AUDIO_CODEC_BIT_DAC_L_BIQUAD_EN_5            ((u32)0x00000001 << 13)                             /*!<R/W 0  DAC Lch 5st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_DAC_L_BIQUAD_A2_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_DAC_L_BIQUAD_A2_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  DAC Lch EQ 5st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_91H
 * @brief  index_91h                                 (@ 0X122)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 1st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_92H
 * @brief  index_92h                                 (@ 0X124)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  ADC Lch EQ 1st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_93H
 * @brief  index_93h                                 (@ 0X126)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B1_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B1_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 1st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_94H
 * @brief  index_94h                                 (@ 0X128)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B1_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B1_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 1st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_95H
 * @brief  index_95h                                 (@ 0X12A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B2_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B2_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 1st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_96H
 * @brief  index_96h                                 (@ 0X12C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B2_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B2_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 1st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_97H
 * @brief  index_97h                                 (@ 0X12E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A1_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A1_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 1st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_98H
 * @brief  index_98h                                 (@ 0X130)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A1_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A1_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 1st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_99H
 * @brief  index_99h                                 (@ 0X132)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A2_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A2_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 1st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_9AH
 * @brief  index_9ah                                 (@ 0X134)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_EN_1          13
#define AUDIO_CODEC_BIT_ADC_L_BIQUAD_EN_1            ((u32)0x00000001 << 13)                             /*!<R/W 0  ADC Lch 1st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A2_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A2_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 1st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_9BH
 * @brief  index_9bh                                 (@ 0X136)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 2st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_9CH
 * @brief  index_9ch                                 (@ 0X138)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  ADC Lch EQ 2st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_9DH
 * @brief  index_9dh                                 (@ 0X13A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B1_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B1_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 2st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_9EH
 * @brief  index_9eh                                 (@ 0X13C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B1_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B1_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 2st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_9FH
 * @brief  index_9fh                                 (@ 0X13E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B2_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B2_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 2st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_A0H
 * @brief  index_a0h                                 (@ 0X140)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B2_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B2_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 2st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_A1H
 * @brief  index_a1h                                 (@ 0X142)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A1_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A1_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 2st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_A2H
 * @brief  index_a2h                                 (@ 0X144)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A1_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A1_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 2st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_A3H
 * @brief  index_a3h                                 (@ 0X146)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A2_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A2_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 2st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_A4H
 * @brief  index_a4h                                 (@ 0X148)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_EN_2          13
#define AUDIO_CODEC_BIT_ADC_L_BIQUAD_EN_2            ((u32)0x00000001 << 13)                             /*!<R/W 0  ADC Lch 2st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A2_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A2_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 2st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_A5H
 * @brief  index_a5h                                 (@ 0X14A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 3st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_A6H
 * @brief  index_a6h                                 (@ 0X14C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  ADC Lch EQ 3st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_A7H
 * @brief  index_a7h                                 (@ 0X14E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B1_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B1_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 3st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_A8H
 * @brief  index_a8h                                 (@ 0X150)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B1_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B1_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 3st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_A9H
 * @brief  index_a9h                                 (@ 0X152)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B2_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B2_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 3st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_AAH
 * @brief  index_aah                                 (@ 0X154)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B2_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B2_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 3st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_ABH
 * @brief  index_abh                                 (@ 0X156)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A1_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A1_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 3st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_ACH
 * @brief  index_ach                                 (@ 0X158)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A1_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A1_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 3st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_ADH
 * @brief  index_adh                                 (@ 0X15A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A2_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A2_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 3st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_AEH
 * @brief  index_aeh                                 (@ 0X15C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_EN_3          13
#define AUDIO_CODEC_BIT_ADC_L_BIQUAD_EN_3            ((u32)0x00000001 << 13)                             /*!<R/W 0  ADC Lch 3st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A2_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A2_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 3st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_AFH
 * @brief  index_afh                                 (@ 0X15E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 4st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_B0H
 * @brief  index_b0h                                 (@ 0X160)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  ADC Lch EQ 4st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_B1H
 * @brief  index_b1h                                 (@ 0X162)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B1_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B1_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 4st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_B2H
 * @brief  index_b2h                                 (@ 0X164)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B1_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B1_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 4st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_B3H
 * @brief  index_b3h                                 (@ 0X166)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B2_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B2_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 4st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_B4H
 * @brief  index_b4h                                 (@ 0X168)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B2_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B2_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 4st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_B5H
 * @brief  index_b5h                                 (@ 0X16A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A1_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A1_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 4st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_B6H
 * @brief  index_b6h                                 (@ 0X16C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A1_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A1_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 4st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_B7H
 * @brief  index_b7h                                 (@ 0X16E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A2_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A2_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 4st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_B8H
 * @brief  index_b8h                                 (@ 0X170)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_EN_4          13
#define AUDIO_CODEC_BIT_ADC_L_BIQUAD_EN_4            ((u32)0x00000001 << 13)                             /*!<R/W 0  ADC Lch 4st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A2_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A2_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 4st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_B9H
 * @brief  index_b9h                                 (@ 0X172)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 5st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_BAH
 * @brief  index_bah                                 (@ 0X174)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_H0_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_H0_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  ADC Lch EQ 5st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_BBH
 * @brief  index_bbh                                 (@ 0X176)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B1_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B1_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 5st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_BCH
 * @brief  index_bch                                 (@ 0X178)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B1_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B1_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 5st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_BDH
 * @brief  index_bdh                                 (@ 0X17A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B2_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B2_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 5st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_BEH
 * @brief  index_beh                                 (@ 0X17C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_B2_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_B2_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 5st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_BFH
 * @brief  index_bfh                                 (@ 0X17E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A1_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A1_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 5st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_C0H
 * @brief  index_c0h                                 (@ 0X180)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A1_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A1_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 5st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_C1H
 * @brief  index_c1h                                 (@ 0X182)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A2_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A2_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Lch EQ 5st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_C2H
 * @brief  index_c2h                                 (@ 0X184)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_EN_5          13
#define AUDIO_CODEC_BIT_ADC_L_BIQUAD_EN_5            ((u32)0x00000001 << 13)                             /*!<R/W 0  ADC Lch 5st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_ADC_L_BIQUAD_A2_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_L_BIQUAD_A2_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Lch EQ 5st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_C4H
 * @brief  index_c4h                                 (@ 0X188)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_H0_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_H0_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 1st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_C5H
 * @brief  index_c5h                                 (@ 0X18A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_H0_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_H0_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  ADC Rch EQ 1st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_C6H
 * @brief  index_c6h                                 (@ 0X18C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B1_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B1_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 1st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_C7H
 * @brief  index_c7h                                 (@ 0X18E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B1_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B1_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 1st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_C8H
 * @brief  index_c8h                                 (@ 0X190)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B2_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B2_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 1st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_C9H
 * @brief  index_c9h                                 (@ 0X192)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B2_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B2_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 1st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_CAH
 * @brief  index_cah                                 (@ 0X194)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A1_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A1_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 1st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_CBH
 * @brief  index_cbh                                 (@ 0X196)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A1_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A1_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 1st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_CCH
 * @brief  index_cch                                 (@ 0X198)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A2_1_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A2_1_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 1st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_CDH
 * @brief  index_cdh                                 (@ 0X19A)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_EN_1          13
#define AUDIO_CODEC_BIT_ADC_R_BIQUAD_EN_1            ((u32)0x00000001 << 13)                             /*!<R/W 0  ADC Rch 1st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A2_1_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A2_1_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 1st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_CEH
 * @brief  index_ceh                                 (@ 0X19C)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_H0_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_H0_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 2st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_CFH
 * @brief  index_cfh                                 (@ 0X19E)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_H0_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_H0_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  ADC Rch EQ 2st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_D0H
 * @brief  index_d0h                                 (@ 0X1A0)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B1_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B1_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 2st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_D1H
 * @brief  index_d1h                                 (@ 0X1A2)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B1_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B1_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 2st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_D2H
 * @brief  index_d2h                                 (@ 0X1A4)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B2_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B2_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 2st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_D3H
 * @brief  index_d3h                                 (@ 0X1A6)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B2_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B2_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 2st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_D4H
 * @brief  index_d4h                                 (@ 0X1A8)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A1_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A1_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 2st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_D5H
 * @brief  index_d5h                                 (@ 0X1AA)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A1_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A1_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 2st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_D6H
 * @brief  index_d6h                                 (@ 0X1AC)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A2_2_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A2_2_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 2st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_D7H
 * @brief  index_d7h                                 (@ 0X1AE)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_EN_2          13
#define AUDIO_CODEC_BIT_ADC_R_BIQUAD_EN_2            ((u32)0x00000001 << 13)                             /*!<R/W 0  ADC Rch 2st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A2_2_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A2_2_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 2st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_D8H
 * @brief  index_d8h                                 (@ 0X1B0)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_H0_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_H0_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 3st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_D9H
 * @brief  index_d9h                                 (@ 0X1B2)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_H0_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_H0_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  ADC Rch EQ 3st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_DAH
 * @brief  index_dah                                 (@ 0X1B4)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B1_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B1_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 3st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_DBH
 * @brief  index_dbh                                 (@ 0X1B6)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B1_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B1_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 3st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_DCH
 * @brief  index_dch                                 (@ 0X1B8)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B2_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B2_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 3st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_DDH
 * @brief  index_ddh                                 (@ 0X1BA)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B2_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B2_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 3st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_DEH
 * @brief  index_deh                                 (@ 0X1BC)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A1_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A1_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 3st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_DFH
 * @brief  index_dfh                                 (@ 0X1BE)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A1_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A1_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 3st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_E0H
 * @brief  index_e0h                                 (@ 0X1C0)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A2_3_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A2_3_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 3st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_E1H
 * @brief  index_e1h                                 (@ 0X1C2)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_EN_3          13
#define AUDIO_CODEC_BIT_ADC_R_BIQUAD_EN_3            ((u32)0x00000001 << 13)                             /*!<R/W 0  ADC Rch 3st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A2_3_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A2_3_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 3st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_E2H
 * @brief  index_e2h                                 (@ 0X1C4)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_H0_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_H0_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 4st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_E3H
 * @brief  index_e3h                                 (@ 0X1C6)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_H0_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_H0_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  ADC Rch EQ 4st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_E4H
 * @brief  index_e4h                                 (@ 0X1C8)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B1_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B1_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 4st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_E5H
 * @brief  index_e5h                                 (@ 0X1CA)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B1_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B1_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 4st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_E6H
 * @brief  index_e6h                                 (@ 0X1CC)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B2_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B2_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 4st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_E7H
 * @brief  index_e7h                                 (@ 0X1CE)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B2_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B2_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 4st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_E8H
 * @brief  index_e8h                                 (@ 0X1D0)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A1_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A1_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 4st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_E9H
 * @brief  index_E9h                                 (@ 0X1D2)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A1_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A1_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 4st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_EAH
 * @brief  index_eah                                 (@ 0X1D4)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A2_4_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A2_4_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 4st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_EBH
 * @brief  index_ebh                                 (@ 0X1D6)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_EN_4          13
#define AUDIO_CODEC_BIT_ADC_R_BIQUAD_EN_4            ((u32)0x00000001 << 13)                             /*!<R/W 0  ADC Rch 4st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A2_4_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A2_4_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 4st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_ECH
 * @brief  index_ech                                 (@ 0X1D8)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_H0_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_H0_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 5st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_EDH
 * @brief  index_edh                                 (@ 0X1DA)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_H0_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_H0_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0x200  ADC Rch EQ 5st-band coef. h0 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_EEH
 * @brief  index_eeh                                 (@ 0X1DC)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B1_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B1_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 5st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_EFH
 * @brief  index_efh                                 (@ 0X1DE)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B1_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B1_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 5st-band coef. b1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_F0H
 * @brief  index_f0h                                 (@ 0X1E0)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B2_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B2_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 5st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_F1H
 * @brief  index_f1h                                 (@ 0X1E2)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_B2_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_B2_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 5st-band coef. b2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_F2H
 * @brief  index_f2h                                 (@ 0X1E4)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A1_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A1_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 5st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_F3H
 * @brief  index_f3h                                 (@ 0X1E6)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A1_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A1_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 5st-band coef. a1 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_F4H
 * @brief  index_f4h                                 (@ 0X1E8)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A2_5_BIT15TO0 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A2_5_BIT15TO0  ((u32)0x0000FFFF << 0)                              /*!<R/W 0  ADC Rch EQ 5st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_F5H
 * @brief  index_f5h                                 (@ 0X1EA)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_EN_5          13
#define AUDIO_CODEC_BIT_ADC_R_BIQUAD_EN_5            ((u32)0x00000001 << 13)                             /*!<R/W 0  ADC Rch 5st-band EQ biquad control 1'b0: Disable 1'b1: Enable */
#define AUDIO_CODEC_SHIFT_ADC_R_BIQUAD_A2_5_BIT28TO16 0
#define AUDIO_CODEC_MASK_ADC_R_BIQUAD_A2_5_BIT28TO16 ((u32)0x00001FFF << 0)                              /*!<R/W 0  ADC Rch EQ 5st-band coef. a2 2's complement in 4.25 format, i.e. the range is from -8~7.99. */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_F6H
 * @brief  index_f6h                                 (@ 0X1EC)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_SILENECE_DET_MONO_STATUS 11
#define AUDIO_CODEC_BIT_DAC_L_SILENECE_DET_MONO_STATUS ((u32)0x00000001 << 11)                             /*!<R 0  ongoing status of dac_l_silence detection 1'b0: dac_l_silence detection is resting (clk is gating) 1'b1: dac_l_silence detection is working  */
#define AUDIO_CODEC_SHIFT_DAC_L_SILENCE_DET_MONO_O   10
#define AUDIO_CODEC_BIT_DAC_L_SILENCE_DET_MONO_O     ((u32)0x00000001 << 10)                             /*!<R 1  dac_l_silence data status (result of silence detection) 1'b0: not dac_l_silence data ; 1'b1: dac_l_silence is detected  */
#define AUDIO_CODEC_SHIFT_DAC_L_SILENCE_MONO_DEBOUNCE_SEL 7
#define AUDIO_CODEC_MASK_DAC_L_SILENCE_MONO_DEBOUNCE_SEL ((u32)0x00000007 << 7)                              /*!<R/W 0x3  dac_l_silence data detection debounce control 3'b000: debounce 80ms at sample rate 48k 3'b001: debounce 160ms at sample rate 48k 3'b010: debounce 320ms at sample rate 48k 3'b011: debounce 640ms at sample rate 48k 3'b100: debounce 1.28 s at sample rate 48k 3'b101: debounce 2.56 s at sample rate 48k 3'b110: debounce 5.12 s at sample rate 48k 3'b111: debounce 0.16ms at sample rate 48k (test mode) */
#define AUDIO_CODEC_SHIFT_DAC_L_SILENCE_MONO_LEVEL_SEL 4
#define AUDIO_CODEC_MASK_DAC_L_SILENCE_MONO_LEVEL_SEL ((u32)0x00000007 << 4)                              /*!<R/W 1  dac_l_silence data detection threshold register control 3'b000: -78 db ; 3'b001: -84 db ; 3'b010: -90 db ; 3'b011: -102db 3'b100: -108db ; 3'b101: -114db ; 3'b110: -126db ; 3'b111: -132db */
#define AUDIO_CODEC_SHIFT_DAC_L_SILENCE_DET_MONO_EN  0
#define AUDIO_CODEC_BIT_DAC_L_SILENCE_DET_MONO_EN    ((u32)0x00000001 << 0)                              /*!<R/W 0  dac_l_silence data detection enable contorl 1'b0: diable dac_l_silence data detection 1'b1: enable dac_l_silence data detection */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_F8H
 * @brief  index_f8h                                 (@ 0X1F0)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_L_SILENECE_DET_MONO_STATUS 11
#define AUDIO_CODEC_BIT_ADC_L_SILENECE_DET_MONO_STATUS ((u32)0x00000001 << 11)                             /*!<R 0  status of adc_l_silence detection 1'b0: adc_l_silence detection is resting (clk is gating) 1'b1: adc_l_silence detection is working  */
#define AUDIO_CODEC_SHIFT_ADC_L_SILENCE_DET_MONO_O   10
#define AUDIO_CODEC_BIT_ADC_L_SILENCE_DET_MONO_O     ((u32)0x00000001 << 10)                             /*!<R 1  adc_l_silence data status 1'b0: not adc_l_silence data ; 1'b1: adc_l_silence is detected  */
#define AUDIO_CODEC_SHIFT_ADC_L_SILENCE_MONO_DEBOUNCE_SEL 7
#define AUDIO_CODEC_MASK_ADC_L_SILENCE_MONO_DEBOUNCE_SEL ((u32)0x00000007 << 7)                              /*!<R/W 0x3  adc_l_silence data detection debounce control 3'b000: debounce 80ms at sample rate 48k 3'b001: debounce 160ms at sample rate 48k 3'b010: debounce 320ms at sample rate 48k 3'b011: debounce 640ms at sample rate 48k 3'b100: debounce 1.28 s at sample rate 48k 3'b101: debounce 2.56 s at sample rate 48k 3'b110: debounce 5.12 s at sample rate 48k 3'b111: debounce 0.16ms at sample rate 48k (test mode) */
#define AUDIO_CODEC_SHIFT_ADC_L_SILENCE_MONO_LEVEL_SEL 4
#define AUDIO_CODEC_MASK_ADC_L_SILENCE_MONO_LEVEL_SEL ((u32)0x00000007 << 4)                              /*!<R/W 1  adc_l_silence data detection threshold register control 3'b000: -78 db ; 3'b001: -84 db ; 3'b010: -90 db ; 3'b011: -102db 3'b100: -108db ; 3'b101: -114db ; 3'b110: -126db ; 3'b111: -132db */
#define AUDIO_CODEC_SHIFT_ADC_L_SILENCE_DET_MONO_EN  0
#define AUDIO_CODEC_BIT_ADC_L_SILENCE_DET_MONO_EN    ((u32)0x00000001 << 0)                              /*!<R/W 0  adc_l_silence data detection enable contorl 1'b0: diable adc_l_silence data detection 1'b1: enable adc_l_silence data detection */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_F9H
 * @brief  index_f9h                                 (@ 0X1F2)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADC_R_SILENECE_DET_MONO_STATUS 11
#define AUDIO_CODEC_BIT_ADC_R_SILENECE_DET_MONO_STATUS ((u32)0x00000001 << 11)                             /*!<R 0  status of adc_r_silence detection 1'b0: adc_r_silence detection is resting (clk is gating) 1'b1: adc_r_silence detection is working  */
#define AUDIO_CODEC_SHIFT_ADC_R_SILENCE_DET_MONO_O   10
#define AUDIO_CODEC_BIT_ADC_R_SILENCE_DET_MONO_O     ((u32)0x00000001 << 10)                             /*!<R 1  adc_r_silence data status 1'b0: not adc_r_silence data ; 1'b1: adc_r_silence is detected  */
#define AUDIO_CODEC_SHIFT_ADC_R_SILENCE_MONO_DEBOUNCE_SEL 7
#define AUDIO_CODEC_MASK_ADC_R_SILENCE_MONO_DEBOUNCE_SEL ((u32)0x00000007 << 7)                              /*!<R/W 0x3  adc_r_silence data detection debounce control 3'b000: debounce 80ms at sample rate 48k 3'b001: debounce 160ms at sample rate 48k 3'b010: debounce 320ms at sample rate 48k 3'b011: debounce 640ms at sample rate 48k 3'b100: debounce 1.28 s at sample rate 48k 3'b101: debounce 2.56 s at sample rate 48k 3'b110: debounce 5.12 s at sample rate 48k 3'b111: debounce 0.16ms at sample rate 48k (test mode) */
#define AUDIO_CODEC_SHIFT_ADC_R_SILENCE_MONO_LEVEL_SEL 4
#define AUDIO_CODEC_MASK_ADC_R_SILENCE_MONO_LEVEL_SEL ((u32)0x00000007 << 4)                              /*!<R/W 1  adc_r_silence data detection threshold register control 3'b000: -78 db ; 3'b001: -84 db ; 3'b010: -90 db ; 3'b011: -102db 3'b100: -108db ; 3'b101: -114db ; 3'b110: -126db ; 3'b111: -132db */
#define AUDIO_CODEC_SHIFT_ADC_R_SILENCE_DET_MONO_EN  0
#define AUDIO_CODEC_BIT_ADC_R_SILENCE_DET_MONO_EN    ((u32)0x00000001 << 0)                              /*!<R/W 0  adc_r_silence data detection enable contorl 1'b0: diable adc_r_silence data detection 1'b1: enable adc_r_silence data detection */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_FAH
 * @brief  index_fah                                 (@ 0X1F4)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_DA_ZDET_TOUT         13
#define AUDIO_CODEC_MASK_DAC_L_DA_ZDET_TOUT          ((u32)0x00000003 << 13)                             /*!<R/W 0  mon DAC Lch Zero detection time out mode control 2'b00: 1024*16 samples 2'b01: 1024*32 samples 2'b10: 1024*64 samples 2'b11: 256 samples  */
#define AUDIO_CODEC_SHIFT_DAC_L_DA_ZDET_FUNC         11
#define AUDIO_CODEC_MASK_DAC_L_DA_ZDET_FUNC          ((u32)0x00000003 << 11)                             /*!<R/W 0x3  mon DAC Lch Zero detection function mode control 2'b00: Immediate change 2'b01: Zero detection and immediate change 2'b10: Zero detection and increase/decrease change 2'b11: N/A  */
#define AUDIO_CODEC_SHIFT_DAC_L_DA_DITHER_SEL        9
#define AUDIO_CODEC_MASK_DAC_L_DA_DITHER_SEL         ((u32)0x00000003 << 9)                              /*!<R/W 0x2  mon DAC Lch dither select 2'b00: disable 2'b01: LSB 2'b10: LSB+1 2'b11: LSB+2  */
#define AUDIO_CODEC_SHIFT_DAC_L_DAHPF_EN             8
#define AUDIO_CODEC_BIT_DAC_L_DAHPF_EN               ((u32)0x00000001 << 8)                              /*!<R/W 1  mon DAC Lch Narrow-band 1st HPF enable control 1'b0: Disable 1'b1: Enable  */
#define AUDIO_CODEC_SHIFT_DAC_L_DA_GAIN              0
#define AUDIO_CODEC_MASK_DAC_L_DA_GAIN               ((u32)0x000000FF << 0)                              /*!<R/W 0xFF  mon DAC Lch dvol gain control (0.375dB/step) 8'hAF: 0dB 8'h00: -65.625dB  */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_FBH
 * @brief  index_fbh                                 (@ 0X1F6)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_SDM_EF_EN            6
#define AUDIO_CODEC_BIT_DAC_L_SDM_EF_EN              ((u32)0x00000001 << 6)                              /*!<R/W 0  DAC Lch 2rd SDM enable 1'b0: off 1'b1: on */
#define AUDIO_CODEC_SHIFT_DAC_L_DMIX_MUTE_128FS_TONE_COMPENSATION 4
#define AUDIO_CODEC_BIT_DAC_L_DMIX_MUTE_128FS_TONE_COMPENSATION ((u32)0x00000001 << 4)                              /*!<R/W 1  mon DAC Lch 128fs-domain mixer a DC from dac_l_tone_compensation_offset 1'b0: off 1'b1: on */
#define AUDIO_CODEC_SHIFT_DAC_L_DMIX_MUTE_128FS_SIDETONE 3
#define AUDIO_CODEC_BIT_DAC_L_DMIX_MUTE_128FS_SIDETONE ((u32)0x00000001 << 3)                              /*!<R/W 1  mon DAC Lch 128fs-domain mixer sidetone path mute enable 1'b0: unmute 1'b1: mute  */
#define AUDIO_CODEC_SHIFT_DAC_L_DMIX_MUTE_128FS_DA   2
#define AUDIO_CODEC_BIT_DAC_L_DMIX_MUTE_128FS_DA     ((u32)0x00000001 << 2)                              /*!<R/W 0  mon DAC Lch 128fs-domain mixer da path mute enable 1'b0: unmute 1'b1: mute  */
#define AUDIO_CODEC_SHIFT_DAAD_LPBK_EN               1
#define AUDIO_CODEC_BIT_DAAD_LPBK_EN                 ((u32)0x00000001 << 1)                              /*!<R/W 0  Digital DAC & ADC loop back control 1'b0: Disable 1'b1: Enable  */
#define AUDIO_CODEC_SHIFT_DAC_L_DA_MUTE              0
#define AUDIO_CODEC_BIT_DAC_L_DA_MUTE                ((u32)0x00000001 << 0)                              /*!<R/W 0  mon DAC Lch dvol mute enable 1'b0: unmute 1'b1: mute  */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_FDH
 * @brief  index_fdh                                 (@ 0X1FA)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_ADDA_LPBK_EN               1
#define AUDIO_CODEC_BIT_ADDA_LPBK_EN                 ((u32)0x00000001 << 1)                              /*!<R/W 0  Digital ADC to DAC loop back control 1'b0: Disable 1'b1: Enable  */
/** @} */

/**************************************************************************//**
 * @defgroup AUDIO_CODEC_INDEX_FEH
 * @brief  index_feh                                 (@ 0X1FC)
 * @{
 *****************************************************************************/
#define AUDIO_CODEC_SHIFT_DAC_L_TONE_COMPENSATION_OFFSET0
#define AUDIO_CODEC_MASK_DAC_L_TONE_COMPENSATION_OFFSET ((u32)0x0000FFFF << 0)                              /*!<R/W 0  mon DAC Lch 128fs-domain mixe a DC compensation for spur issue 2's complemet */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_AUDIO_CODEC
 * @{
 * @brief rtl8735b_AUDIO_CODEC Register Declaration
 *****************************************************************************/
typedef struct {
	__IO uint32_t AUDIO_CODEC_INDEX_00H ;                  /*!<  index_00h register,  Address offset: 0x000 */
	__IO uint32_t AUDIO_CODEC_INDEX_01H ;                  /*!<  index_01h register,  Address offset: 0x002 */
	__IO uint32_t AUDIO_CODEC_INDEX_02H ;                  /*!<  index_02h register,  Address offset: 0x004 */
	__IO uint32_t AUDIO_CODEC_INDEX_03H ;                  /*!<  index_03h register,  Address offset: 0x006 */
	__IO uint32_t AUDIO_CODEC_INDEX_04H ;                  /*!<  index_04h register,  Address offset: 0x008 */
	__IO uint32_t AUDIO_CODEC_INDEX_05H ;                  /*!<  index_05h register,  Address offset: 0x00A */
	__IO uint32_t AUDIO_CODEC_INDEX_06H ;                  /*!<  index_06h register,  Address offset: 0x00C */
	__IO uint32_t AUDIO_CODEC_INDEX_07H ;                  /*!<  index_07h register,  Address offset: 0x00E */
	__IO uint32_t AUDIO_CODEC_INDEX_08H ;                  /*!<  index_08h register,  Address offset: 0x010 */
	__IO uint32_t AUDIO_CODEC_INDEX_09H ;                  /*!<  index_09h register,  Address offset: 0x012 */
	__I  uint32_t AUDIO_CODEC_INDEX_0AH ;                  /*!<  index_0ah register,  Address offset: 0x014 */
	__I  uint32_t AUDIO_CODEC_INDEX_0BH ;                  /*!<  index_0bh register,  Address offset: 0x016 */
	__IO uint32_t AUDIO_CODEC_INDEX_0CH ;                  /*!<  index_0ch register,  Address offset: 0x018 */
	__IO uint32_t AUDIO_CODEC_INDEX_0DH ;                  /*!<  index_0dh register,  Address offset: 0x01A */
	__IO uint32_t AUDIO_CODEC_INDEX_0EH ;                  /*!<  index_0eh register,  Address offset: 0x01C */
	__IO uint32_t AUDIO_CODEC_INDEX_0FH ;                  /*!<  index_0fh register,  Address offset: 0x01E */
	__IO uint32_t AUDIO_CODEC_INDEX_10H ;                  /*!<  index_10h register,  Address offset: 0x020 */
	__IO uint32_t AUDIO_CODEC_INDEX_11H ;                  /*!<  index_11h register,  Address offset: 0x022 */
	__IO uint32_t AUDIO_CODEC_INDEX_12H ;                  /*!<  index_12h register,  Address offset: 0x024 */
	__IO uint32_t AUDIO_CODEC_INDEX_13H ;                  /*!<  index_13h register,  Address offset: 0x026 */
	__IO uint32_t AUDIO_CODEC_INDEX_14H ;                  /*!<  index_14h register,  Address offset: 0x028 */
	__IO uint32_t AUDIO_CODEC_INDEX_15H ;                  /*!<  index_15h register,  Address offset: 0x02A */
	__IO uint32_t AUDIO_CODEC_INDEX_16H ;                  /*!<  index_16h register,  Address offset: 0x02C */
	__IO uint32_t AUDIO_CODEC_INDEX_17H ;                  /*!<  index_17h register,  Address offset: 0x02E */
	__IO uint32_t AUDIO_CODEC_INDEX_18H ;                  /*!<  index_18h register,  Address offset: 0x030 */
	__IO uint32_t AUDIO_CODEC_INDEX_19H ;                  /*!<  index_19h register,  Address offset: 0x032 */
	__IO uint32_t AUDIO_CODEC_INDEX_1AH ;                  /*!<  index_1ah register,  Address offset: 0x034 */
	__IO uint32_t AUDIO_CODEC_INDEX_1BH ;                  /*!<  index_1bh register,  Address offset: 0x036 */
	__I  uint32_t AUDIO_CODEC_INDEX_1CH ;                  /*!<  index_1ch register,  Address offset: 0x038 */
	__I  uint32_t AUDIO_CODEC_INDEX_1DH ;                  /*!<  index_1dh register,  Address offset: 0x03A */
	__I  uint32_t AUDIO_CODEC_INDEX_1EH ;                  /*!<  index_1eh register,  Address offset: 0x03C */
	__I  uint32_t AUDIO_CODEC_INDEX_1FH ;                  /*!<  index_1fh register,  Address offset: 0x03E */
	__I  uint32_t AUDIO_CODEC_INDEX_20H ;                  /*!<  index_20h register,  Address offset: 0x040 */
	__I  uint32_t AUDIO_CODEC_INDEX_21H ;                  /*!<  index_21h register,  Address offset: 0x042 */
	__I  uint32_t AUDIO_CODEC_INDEX_22H ;                  /*!<  index_22h register,  Address offset: 0x044 */
	__I  uint32_t AUDIO_CODEC_INDEX_23H ;                  /*!<  index_23h register,  Address offset: 0x046 */
	__I  uint32_t AUDIO_CODEC_INDEX_24H ;                  /*!<  index_24h register,  Address offset: 0x048 */
	__I  uint32_t AUDIO_CODEC_INDEX_25H ;                  /*!<  index_25h register,  Address offset: 0x04A */
	__I  uint32_t AUDIO_CODEC_INDEX_26H ;                  /*!<  index_26h register,  Address offset: 0x04C */
	__I  uint32_t AUDIO_CODEC_INDEX_27H ;                  /*!<  index_27h register,  Address offset: 0x04E */
	__I  uint32_t AUDIO_CODEC_INDEX_28H ;                  /*!<  index_28h register,  Address offset: 0x050 */
	__I  uint32_t AUDIO_CODEC_INDEX_29H ;                  /*!<  index_29h register,  Address offset: 0x052 */
	__I  uint32_t AUDIO_CODEC_INDEX_2AH ;                  /*!<  index_2ah register,  Address offset: 0x054 */
	__IO uint32_t AUDIO_CODEC_INDEX_2BH ;                  /*!<  index_2bh register,  Address offset: 0x056 */
	__IO uint32_t AUDIO_CODEC_INDEX_2CH ;                  /*!<  index_2ch register,  Address offset: 0x058 */
	__IO uint32_t AUDIO_CODEC_INDEX_2DH ;                  /*!<  index_2dh register,  Address offset: 0x05A */
	__IO uint32_t AUDIO_CODEC_INDEX_2EH ;                  /*!<  index_2eh register,  Address offset: 0x05C */
	__IO uint32_t AUDIO_CODEC_INDEX_2FH ;                  /*!<  index_2fh register,  Address offset: 0x05E */
	__IO uint32_t AUDIO_CODEC_INDEX_30H ;                  /*!<  index_30h register,  Address offset: 0x060 */
	__IO uint32_t AUDIO_CODEC_INDEX_31H ;                  /*!<  index_31h register,  Address offset: 0x062 */
	__IO uint32_t AUDIO_CODEC_INDEX_32H ;                  /*!<  index_32h register,  Address offset: 0x064 */
	__IO uint32_t AUDIO_CODEC_INDEX_33H ;                  /*!<  index_33h register,  Address offset: 0x066 */
	__IO uint32_t AUDIO_CODEC_INDEX_34H ;                  /*!<  index_34h register,  Address offset: 0x068 */
	__IO uint32_t AUDIO_CODEC_INDEX_35H ;                  /*!<  index_35h register,  Address offset: 0x06A */
	__IO uint32_t AUDIO_CODEC_INDEX_36H ;                  /*!<  index_36h register,  Address offset: 0x06C */
	__IO uint32_t AUDIO_CODEC_INDEX_37H ;                  /*!<  index_37h register,  Address offset: 0x06E */
	__IO uint32_t AUDIO_CODEC_INDEX_38H ;                  /*!<  index_38h register,  Address offset: 0x070 */
	__IO uint32_t AUDIO_CODEC_INDEX_39H ;                  /*!<  index_39h register,  Address offset: 0x072 */
	__IO uint32_t AUDIO_CODEC_INDEX_3AH ;                  /*!<  index_3ah register,  Address offset: 0x074 */
	__IO uint32_t AUDIO_CODEC_INDEX_3BH ;                  /*!<  index_3bh register,  Address offset: 0x076 */
	__IO uint32_t AUDIO_CODEC_INDEX_3CH ;                  /*!<  index_3ch register,  Address offset: 0x078 */
	__IO uint32_t AUDIO_CODEC_INDEX_3DH ;                  /*!<  index_3dh register,  Address offset: 0x07A */
	__IO uint32_t AUDIO_CODEC_INDEX_3EH ;                  /*!<  index_3eh register,  Address offset: 0x07C */
	__IO uint32_t AUDIO_CODEC_INDEX_3FH ;                  /*!<  index_3fh register,  Address offset: 0x07E */
	__IO uint32_t AUDIO_CODEC_INDEX_40H ;                  /*!<  index_40h register,  Address offset: 0x080 */
	__IO uint32_t AUDIO_CODEC_INDEX_41H ;                  /*!<  index_41h register,  Address offset: 0x082 */
	__IO uint32_t AUDIO_CODEC_INDEX_42H ;                  /*!<  index_42h register,  Address offset: 0x084 */
	__IO uint32_t AUDIO_CODEC_INDEX_43H ;                  /*!<  index_43h register,  Address offset: 0x086 */
	__IO uint32_t AUDIO_CODEC_INDEX_44H ;                  /*!<  index_44h register,  Address offset: 0x088 */
	__IO uint32_t AUDIO_CODEC_INDEX_45H ;                  /*!<  index_45h register,  Address offset: 0x08A */
	__IO uint32_t AUDIO_CODEC_INDEX_46H ;                  /*!<  index_46h register,  Address offset: 0x08C */
	__IO uint32_t AUDIO_CODEC_INDEX_47H ;                  /*!<  index_47h register,  Address offset: 0x08E */
	__IO uint32_t AUDIO_CODEC_INDEX_48H ;                  /*!<  index_48h register,  Address offset: 0x090 */
	__IO uint32_t AUDIO_CODEC_INDEX_49H ;                  /*!<  index_49h register,  Address offset: 0x092 */
	__IO uint32_t AUDIO_CODEC_INDEX_4AH ;                  /*!<  index_4ah register,  Address offset: 0x094 */
	__IO uint32_t AUDIO_CODEC_INDEX_4BH ;                  /*!<  index_4bh register,  Address offset: 0x096 */
	__IO uint32_t AUDIO_CODEC_INDEX_4CH ;                  /*!<  index_4ch register,  Address offset: 0x098 */
	__IO uint32_t AUDIO_CODEC_INDEX_4DH ;                  /*!<  index_4dh register,  Address offset: 0x09A */
	__IO uint32_t AUDIO_CODEC_INDEX_4EH ;                  /*!<  index_4eh register,  Address offset: 0x09C */
	__IO uint32_t AUDIO_CODEC_INDEX_4FH ;                  /*!<  index_4fh register,  Address offset: 0x09E */
	__IO uint32_t AUDIO_CODEC_INDEX_50H ;                  /*!<  index_50h register,  Address offset: 0x0A0 */
	__IO uint32_t AUDIO_CODEC_INDEX_51H ;                  /*!<  index_51h register,  Address offset: 0x0A2 */
	__IO uint32_t AUDIO_CODEC_INDEX_52H ;                  /*!<  index_52h register,  Address offset: 0x0A4 */
	__IO uint32_t AUDIO_CODEC_INDEX_53H ;                  /*!<  index_53h register,  Address offset: 0x0A6 */
	__IO uint32_t AUDIO_CODEC_INDEX_54H ;                  /*!<  index_54h register,  Address offset: 0x0A8 */
	__IO uint32_t AUDIO_CODEC_INDEX_55H ;                  /*!<  index_55h register,  Address offset: 0x0AA */
	__IO uint32_t AUDIO_CODEC_INDEX_56H ;                  /*!<  index_56h register,  Address offset: 0x0AC */
	__IO uint32_t AUDIO_CODEC_INDEX_57H ;                  /*!<  index_57h register,  Address offset: 0x0AE */
	__IO uint32_t AUDIO_CODEC_INDEX_58H ;                  /*!<  index_58h register,  Address offset: 0x0B0 */
	__IO uint32_t AUDIO_CODEC_INDEX_59H ;                  /*!<  index_59h register,  Address offset: 0x0B2 */
	__IO uint32_t AUDIO_CODEC_INDEX_5AH ;                  /*!<  index_5ah register,  Address offset: 0x0B4 */
	__IO uint32_t AUDIO_CODEC_INDEX_5BH ;                  /*!<  index_5bh register,  Address offset: 0x0B6 */
	__IO uint32_t AUDIO_CODEC_INDEX_5CH ;                  /*!<  index_5ch register,  Address offset: 0x0B8 */
	__I  uint32_t AUDIO_CODEC_INDEX_5DH ;                  /*!<  index_5dh register,  Address offset: 0x0BA */
	__I  uint32_t AUDIO_CODEC_INDEX_5EH ;                  /*!<  index_5eh register,  Address offset: 0x0BC */
	__I  uint32_t AUDIO_CODEC_INDEX_5FH ;                  /*!<  index_5fh register,  Address offset: 0x0BE */
	__I  uint32_t AUDIO_CODEC_INDEX_60H ;                  /*!<  index_60h register,  Address offset: 0x0C0 */
	__I  uint32_t AUDIO_CODEC_INDEX_61H ;                  /*!<  index_61h register,  Address offset: 0x0C2 */
	__I  uint32_t AUDIO_CODEC_INDEX_62H ;                  /*!<  index_62h register,  Address offset: 0x0C4 */
	__I  uint32_t AUDIO_CODEC_INDEX_63H ;                  /*!<  index_63h register,  Address offset: 0x0C6 */
	__I  uint32_t AUDIO_CODEC_INDEX_64H ;                  /*!<  index_64h register,  Address offset: 0x0C8 */
	__IO uint32_t AUDIO_CODEC_INDEX_65H ;                  /*!<  index_65h register,  Address offset: 0x0CA */
	__IO uint32_t AUDIO_CODEC_INDEX_66H ;                  /*!<  index_66h register,  Address offset: 0x0CC */
	__IO uint32_t AUDIO_CODEC_INDEX_67H ;                  /*!<  index_67h register,  Address offset: 0x0CE */
	__IO uint32_t AUDIO_CODEC_INDEX_68H ;                  /*!<  index_68h register,  Address offset: 0x0D0 */
	__IO uint32_t AUDIO_CODEC_INDEX_69H ;                  /*!<  index_69h register,  Address offset: 0x0D2 */
	__IO uint32_t AUDIO_CODEC_INDEX_6AH ;                  /*!<  index_6ah register,  Address offset: 0x0D4 */
	__IO uint32_t AUDIO_CODEC_INDEX_6BH ;                  /*!<  index_6bh register,  Address offset: 0x0D6 */
	__IO uint32_t AUDIO_CODEC_INDEX_6CH ;                  /*!<  index_6ch register,  Address offset: 0x0D8 */
	__IO uint32_t AUDIO_CODEC_INDEX_6DH ;                  /*!<  index_6dh register,  Address offset: 0x0DA */
	__IO uint32_t AUDIO_CODEC_INDEX_6EH ;                  /*!<  index_6eh register,  Address offset: 0x0DC */
	__IO uint32_t AUDIO_CODEC_INDEX_6FH ;                  /*!<  index_6fh register,  Address offset: 0x0DE */
	__IO uint32_t AUDIO_CODEC_INDEX_70H ;                  /*!<  index_70h register,  Address offset: 0x0E0 */
	__IO uint32_t AUDIO_CODEC_INDEX_71H ;                  /*!<  index_71h register,  Address offset: 0x0E2 */
	__IO uint32_t AUDIO_CODEC_INDEX_72H ;                  /*!<  index_72h register,  Address offset: 0x0E4 */
	__IO uint32_t AUDIO_CODEC_INDEX_73H ;                  /*!<  index_73h register,  Address offset: 0x0E6 */
	__IO uint32_t AUDIO_CODEC_INDEX_74H ;                  /*!<  index_74h register,  Address offset: 0x0E8 */
	__IO uint32_t AUDIO_CODEC_INDEX_75H ;                  /*!<  index_75h register,  Address offset: 0x0EA */
	__IO uint32_t AUDIO_CODEC_INDEX_76H ;                  /*!<  index_76h register,  Address offset: 0x0EC */
	__IO uint32_t AUDIO_CODEC_INDEX_77H ;                  /*!<  index_77h register,  Address offset: 0x0EE */
	__IO uint32_t AUDIO_CODEC_INDEX_78H ;                  /*!<  index_78h register,  Address offset: 0x0F0 */
	__IO uint32_t AUDIO_CODEC_INDEX_79H ;                  /*!<  index_79h register,  Address offset: 0x0F2 */
	__IO uint32_t AUDIO_CODEC_INDEX_7AH ;                  /*!<  index_7ah register,  Address offset: 0x0F4 */
	__IO uint32_t AUDIO_CODEC_INDEX_7BH ;                  /*!<  index_7bh register,  Address offset: 0x0F6 */
	__IO uint32_t AUDIO_CODEC_INDEX_7CH ;                  /*!<  index_7ch register,  Address offset: 0x0F8 */
	__IO uint32_t AUDIO_CODEC_INDEX_7DH ;                  /*!<  index_7dh register,  Address offset: 0x0FA */
	__IO uint32_t AUDIO_CODEC_INDEX_7EH ;                  /*!<  index_7eh register,  Address offset: 0x0FC */
	__IO uint32_t AUDIO_CODEC_INDEX_7FH ;                  /*!<  index_7fh register,  Address offset: 0x0FE */
	__IO uint32_t AUDIO_CODEC_INDEX_80H ;                  /*!<  index_80h register,  Address offset: 0x100 */
	__IO uint32_t AUDIO_CODEC_INDEX_81H ;                  /*!<  index_81h register,  Address offset: 0x102 */
	__IO uint32_t AUDIO_CODEC_INDEX_82H ;                  /*!<  index_82h register,  Address offset: 0x104 */
	__IO uint32_t AUDIO_CODEC_INDEX_83H ;                  /*!<  index_83h register,  Address offset: 0x106 */
	__IO uint32_t AUDIO_CODEC_INDEX_84H ;                  /*!<  index_84h register,  Address offset: 0x108 */
	__IO uint32_t AUDIO_CODEC_INDEX_85H ;                  /*!<  index_85h register,  Address offset: 0x10A */
	__IO uint32_t AUDIO_CODEC_INDEX_86H ;                  /*!<  index_86h register,  Address offset: 0x10C */
	__IO uint32_t AUDIO_CODEC_INDEX_87H ;                  /*!<  index_87h register,  Address offset: 0x10E */
	__IO uint32_t AUDIO_CODEC_INDEX_88H ;                  /*!<  index_88h register,  Address offset: 0x110 */
	__IO uint32_t AUDIO_CODEC_INDEX_89H ;                  /*!<  index_89h register,  Address offset: 0x112 */
	__IO uint32_t AUDIO_CODEC_INDEX_8AH ;                  /*!<  index_8ah register,  Address offset: 0x114 */
	__IO uint32_t AUDIO_CODEC_INDEX_8BH ;                  /*!<  index_8bh register,  Address offset: 0x116 */
	__IO uint32_t AUDIO_CODEC_INDEX_8CH ;                  /*!<  index_8ch register,  Address offset: 0x118 */
	__IO uint32_t AUDIO_CODEC_INDEX_8DH ;                  /*!<  index_8dh register,  Address offset: 0x11A */
	__IO uint32_t AUDIO_CODEC_INDEX_8EH ;                  /*!<  index_8eh register,  Address offset: 0x11C */
	__IO uint32_t AUDIO_CODEC_INDEX_8FH ;                  /*!<  index_8fh register,  Address offset: 0x11E */
	__IO uint32_t AUDIO_CODEC_INDEX_90H ;                  /*!<  index_90h register,  Address offset: 0x120 */
	__IO uint32_t AUDIO_CODEC_INDEX_91H ;                  /*!<  index_91h register,  Address offset: 0x122 */
	__IO uint32_t AUDIO_CODEC_INDEX_92H ;                  /*!<  index_92h register,  Address offset: 0x124 */
	__IO uint32_t AUDIO_CODEC_INDEX_93H ;                  /*!<  index_93h register,  Address offset: 0x126 */
	__IO uint32_t AUDIO_CODEC_INDEX_94H ;                  /*!<  index_94h register,  Address offset: 0x128 */
	__IO uint32_t AUDIO_CODEC_INDEX_95H ;                  /*!<  index_95h register,  Address offset: 0x12A */
	__IO uint32_t AUDIO_CODEC_INDEX_96H ;                  /*!<  index_96h register,  Address offset: 0x12C */
	__IO uint32_t AUDIO_CODEC_INDEX_97H ;                  /*!<  index_97h register,  Address offset: 0x12E */
	__IO uint32_t AUDIO_CODEC_INDEX_98H ;                  /*!<  index_98h register,  Address offset: 0x130 */
	__IO uint32_t AUDIO_CODEC_INDEX_99H ;                  /*!<  index_99h register,  Address offset: 0x132 */
	__IO uint32_t AUDIO_CODEC_INDEX_9AH ;                  /*!<  index_9ah register,  Address offset: 0x134 */
	__IO uint32_t AUDIO_CODEC_INDEX_9BH ;                  /*!<  index_9bh register,  Address offset: 0x136 */
	__IO uint32_t AUDIO_CODEC_INDEX_9CH ;                  /*!<  index_9ch register,  Address offset: 0x138 */
	__IO uint32_t AUDIO_CODEC_INDEX_9DH ;                  /*!<  index_9dh register,  Address offset: 0x13A */
	__IO uint32_t AUDIO_CODEC_INDEX_9EH ;                  /*!<  index_9eh register,  Address offset: 0x13C */
	__IO uint32_t AUDIO_CODEC_INDEX_9FH ;                  /*!<  index_9fh register,  Address offset: 0x13E */
	__IO uint32_t AUDIO_CODEC_INDEX_A0H ;                  /*!<  index_a0h register,  Address offset: 0x140 */
	__IO uint32_t AUDIO_CODEC_INDEX_A1H ;                  /*!<  index_a1h register,  Address offset: 0x142 */
	__IO uint32_t AUDIO_CODEC_INDEX_A2H ;                  /*!<  index_a2h register,  Address offset: 0x144 */
	__IO uint32_t AUDIO_CODEC_INDEX_A3H ;                  /*!<  index_a3h register,  Address offset: 0x146 */
	__IO uint32_t AUDIO_CODEC_INDEX_A4H ;                  /*!<  index_a4h register,  Address offset: 0x148 */
	__IO uint32_t AUDIO_CODEC_INDEX_A5H ;                  /*!<  index_a5h register,  Address offset: 0x14A */
	__IO uint32_t AUDIO_CODEC_INDEX_A6H ;                  /*!<  index_a6h register,  Address offset: 0x14C */
	__IO uint32_t AUDIO_CODEC_INDEX_A7H ;                  /*!<  index_a7h register,  Address offset: 0x14E */
	__IO uint32_t AUDIO_CODEC_INDEX_A8H ;                  /*!<  index_a8h register,  Address offset: 0x150 */
	__IO uint32_t AUDIO_CODEC_INDEX_A9H ;                  /*!<  index_a9h register,  Address offset: 0x152 */
	__IO uint32_t AUDIO_CODEC_INDEX_AAH ;                  /*!<  index_aah register,  Address offset: 0x154 */
	__IO uint32_t AUDIO_CODEC_INDEX_ABH ;                  /*!<  index_abh register,  Address offset: 0x156 */
	__IO uint32_t AUDIO_CODEC_INDEX_ACH ;                  /*!<  index_ach register,  Address offset: 0x158 */
	__IO uint32_t AUDIO_CODEC_INDEX_ADH ;                  /*!<  index_adh register,  Address offset: 0x15A */
	__IO uint32_t AUDIO_CODEC_INDEX_AEH ;                  /*!<  index_aeh register,  Address offset: 0x15C */
	__IO uint32_t AUDIO_CODEC_INDEX_AFH ;                  /*!<  index_afh register,  Address offset: 0x15E */
	__IO uint32_t AUDIO_CODEC_INDEX_B0H ;                  /*!<  index_b0h register,  Address offset: 0x160 */
	__IO uint32_t AUDIO_CODEC_INDEX_B1H ;                  /*!<  index_b1h register,  Address offset: 0x162 */
	__IO uint32_t AUDIO_CODEC_INDEX_B2H ;                  /*!<  index_b2h register,  Address offset: 0x164 */
	__IO uint32_t AUDIO_CODEC_INDEX_B3H ;                  /*!<  index_b3h register,  Address offset: 0x166 */
	__IO uint32_t AUDIO_CODEC_INDEX_B4H ;                  /*!<  index_b4h register,  Address offset: 0x168 */
	__IO uint32_t AUDIO_CODEC_INDEX_B5H ;                  /*!<  index_b5h register,  Address offset: 0x16A */
	__IO uint32_t AUDIO_CODEC_INDEX_B6H ;                  /*!<  index_b6h register,  Address offset: 0x16C */
	__IO uint32_t AUDIO_CODEC_INDEX_B7H ;                  /*!<  index_b7h register,  Address offset: 0x16E */
	__IO uint32_t AUDIO_CODEC_INDEX_B8H ;                  /*!<  index_b8h register,  Address offset: 0x170 */
	__IO uint32_t AUDIO_CODEC_INDEX_B9H ;                  /*!<  index_b9h register,  Address offset: 0x172 */
	__IO uint32_t AUDIO_CODEC_INDEX_BAH ;                  /*!<  index_bah register,  Address offset: 0x174 */
	__IO uint32_t AUDIO_CODEC_INDEX_BBH ;                  /*!<  index_bbh register,  Address offset: 0x176 */
	__IO uint32_t AUDIO_CODEC_INDEX_BCH ;                  /*!<  index_bch register,  Address offset: 0x178 */
	__IO uint32_t AUDIO_CODEC_INDEX_BDH ;                  /*!<  index_bdh register,  Address offset: 0x17A */
	__IO uint32_t AUDIO_CODEC_INDEX_BEH ;                  /*!<  index_beh register,  Address offset: 0x17C */
	__IO uint32_t AUDIO_CODEC_INDEX_BFH ;                  /*!<  index_bfh register,  Address offset: 0x17E */
	__IO uint32_t AUDIO_CODEC_INDEX_C0H ;                  /*!<  index_c0h register,  Address offset: 0x180 */
	__IO uint32_t AUDIO_CODEC_INDEX_C1H ;                  /*!<  index_c1h register,  Address offset: 0x182 */
	__IO uint32_t AUDIO_CODEC_INDEX_C2H ;                  /*!<  index_c2h register,  Address offset: 0x184 */
	__IO uint32_t AUDIO_CODEC_INDEX_C3H ;                  /*!<  index_c3h register,  Address offset: 0x186 */
	__IO uint32_t AUDIO_CODEC_INDEX_C4H ;                  /*!<  index_c4h register,  Address offset: 0x188 */
	__IO uint32_t AUDIO_CODEC_INDEX_C5H ;                  /*!<  index_c5h register,  Address offset: 0x18A */
	__IO uint32_t AUDIO_CODEC_INDEX_C6H ;                  /*!<  index_c6h register,  Address offset: 0x18C */
	__IO uint32_t AUDIO_CODEC_INDEX_C7H ;                  /*!<  index_c7h register,  Address offset: 0x18E */
	__IO uint32_t AUDIO_CODEC_INDEX_C8H ;                  /*!<  index_c8h register,  Address offset: 0x190 */
	__IO uint32_t AUDIO_CODEC_INDEX_C9H ;                  /*!<  index_c9h register,  Address offset: 0x192 */
	__IO uint32_t AUDIO_CODEC_INDEX_CAH ;                  /*!<  index_cah register,  Address offset: 0x194 */
	__IO uint32_t AUDIO_CODEC_INDEX_CBH ;                  /*!<  index_cbh register,  Address offset: 0x196 */
	__IO uint32_t AUDIO_CODEC_INDEX_CCH ;                  /*!<  index_cch register,  Address offset: 0x198 */
	__IO uint32_t AUDIO_CODEC_INDEX_CDH ;                  /*!<  index_cdh register,  Address offset: 0x19A */
	__IO uint32_t AUDIO_CODEC_INDEX_CEH ;                  /*!<  index_ceh register,  Address offset: 0x19C */
	__IO uint32_t AUDIO_CODEC_INDEX_CFH ;                  /*!<  index_cfh register,  Address offset: 0x19E */
	__IO uint32_t AUDIO_CODEC_INDEX_D0H ;                  /*!<  index_d0h register,  Address offset: 0x1A0 */
	__IO uint32_t AUDIO_CODEC_INDEX_D1H ;                  /*!<  index_d1h register,  Address offset: 0x1A2 */
	__IO uint32_t AUDIO_CODEC_INDEX_D2H ;                  /*!<  index_d2h register,  Address offset: 0x1A4 */
	__IO uint32_t AUDIO_CODEC_INDEX_D3H ;                  /*!<  index_d3h register,  Address offset: 0x1A6 */
	__IO uint32_t AUDIO_CODEC_INDEX_D4H ;                  /*!<  index_d4h register,  Address offset: 0x1A8 */
	__IO uint32_t AUDIO_CODEC_INDEX_D5H ;                  /*!<  index_d5h register,  Address offset: 0x1AA */
	__IO uint32_t AUDIO_CODEC_INDEX_D6H ;                  /*!<  index_d6h register,  Address offset: 0x1AC */
	__IO uint32_t AUDIO_CODEC_INDEX_D7H ;                  /*!<  index_d7h register,  Address offset: 0x1AE */
	__IO uint32_t AUDIO_CODEC_INDEX_D8H ;                  /*!<  index_d8h register,  Address offset: 0x1B0 */
	__IO uint32_t AUDIO_CODEC_INDEX_D9H ;                  /*!<  index_d9h register,  Address offset: 0x1B2 */
	__IO uint32_t AUDIO_CODEC_INDEX_DAH ;                  /*!<  index_dah register,  Address offset: 0x1B4 */
	__IO uint32_t AUDIO_CODEC_INDEX_DBH ;                  /*!<  index_dbh register,  Address offset: 0x1B6 */
	__IO uint32_t AUDIO_CODEC_INDEX_DCH ;                  /*!<  index_dch register,  Address offset: 0x1B8 */
	__IO uint32_t AUDIO_CODEC_INDEX_DDH ;                  /*!<  index_ddh register,  Address offset: 0x1BA */
	__IO uint32_t AUDIO_CODEC_INDEX_DEH ;                  /*!<  index_deh register,  Address offset: 0x1BC */
	__IO uint32_t AUDIO_CODEC_INDEX_DFH ;                  /*!<  index_dfh register,  Address offset: 0x1BE */
	__IO uint32_t AUDIO_CODEC_INDEX_E0H ;                  /*!<  index_e0h register,  Address offset: 0x1C0 */
	__IO uint32_t AUDIO_CODEC_INDEX_E1H ;                  /*!<  index_e1h register,  Address offset: 0x1C2 */
	__IO uint32_t AUDIO_CODEC_INDEX_E2H ;                  /*!<  index_e2h register,  Address offset: 0x1C4 */
	__IO uint32_t AUDIO_CODEC_INDEX_E3H ;                  /*!<  index_e3h register,  Address offset: 0x1C6 */
	__IO uint32_t AUDIO_CODEC_INDEX_E4H ;                  /*!<  index_e4h register,  Address offset: 0x1C8 */
	__IO uint32_t AUDIO_CODEC_INDEX_E5H ;                  /*!<  index_e5h register,  Address offset: 0x1CA */
	__IO uint32_t AUDIO_CODEC_INDEX_E6H ;                  /*!<  index_e6h register,  Address offset: 0x1CC */
	__IO uint32_t AUDIO_CODEC_INDEX_E7H ;                  /*!<  index_e7h register,  Address offset: 0x1CE */
	__IO uint32_t AUDIO_CODEC_INDEX_E8H ;                  /*!<  index_e8h register,  Address offset: 0x1D0 */
	__IO uint32_t AUDIO_CODEC_INDEX_E9H ;                  /*!<  index_E9h register,  Address offset: 0x1D2 */
	__IO uint32_t AUDIO_CODEC_INDEX_EAH ;                  /*!<  index_eah register,  Address offset: 0x1D4 */
	__IO uint32_t AUDIO_CODEC_INDEX_EBH ;                  /*!<  index_ebh register,  Address offset: 0x1D6 */
	__IO uint32_t AUDIO_CODEC_INDEX_ECH ;                  /*!<  index_ech register,  Address offset: 0x1D8 */
	__IO uint32_t AUDIO_CODEC_INDEX_EDH ;                  /*!<  index_edh register,  Address offset: 0x1DA */
	__IO uint32_t AUDIO_CODEC_INDEX_EEH ;                  /*!<  index_eeh register,  Address offset: 0x1DC */
	__IO uint32_t AUDIO_CODEC_INDEX_EFH ;                  /*!<  index_efh register,  Address offset: 0x1DE */
	__IO uint32_t AUDIO_CODEC_INDEX_F0H ;                  /*!<  index_f0h register,  Address offset: 0x1E0 */
	__IO uint32_t AUDIO_CODEC_INDEX_F1H ;                  /*!<  index_f1h register,  Address offset: 0x1E2 */
	__IO uint32_t AUDIO_CODEC_INDEX_F2H ;                  /*!<  index_f2h register,  Address offset: 0x1E4 */
	__IO uint32_t AUDIO_CODEC_INDEX_F3H ;                  /*!<  index_f3h register,  Address offset: 0x1E6 */
	__IO uint32_t AUDIO_CODEC_INDEX_F4H ;                  /*!<  index_f4h register,  Address offset: 0x1E8 */
	__IO uint32_t AUDIO_CODEC_INDEX_F5H ;                  /*!<  index_f5h register,  Address offset: 0x1EA */
	__IO uint32_t AUDIO_CODEC_INDEX_F6H ;                  /*!<  index_f6h register,  Address offset: 0x1EC */
	__IO uint32_t AUDIO_CODEC_INDEX_F7H ;                  /*!<  index_f7h register,  Address offset: 0x1EE */
	__IO uint32_t AUDIO_CODEC_INDEX_F8H ;                  /*!<  index_f8h register,  Address offset: 0x1F0 */
	__IO uint32_t AUDIO_CODEC_INDEX_F9H ;                  /*!<  index_f9h register,  Address offset: 0x1F2 */
	__IO uint32_t AUDIO_CODEC_INDEX_FAH ;                  /*!<  index_fah register,  Address offset: 0x1F4 */
	__IO uint32_t AUDIO_CODEC_INDEX_FBH ;                  /*!<  index_fbh register,  Address offset: 0x1F6 */
	__I  uint32_t AUDIO_CODEC_INDEX_FCH ;                  /*!<  index_fch register,  Address offset: 0x1F8 */
	__IO uint32_t AUDIO_CODEC_INDEX_FDH ;                  /*!<  index_fdh register,  Address offset: 0x1FA */
	__IO uint32_t AUDIO_CODEC_INDEX_FEH ;                  /*!<  index_feh register,			Address offset: 0x1FC */
} AUDIO_CODEC_TypeDef;
/** @} */

#endif
