#ifndef _MODULE_AUDIO_H
#define _MODULE_AUDIO_H

#include "mmf2_module.h"
#if defined(CONFIG_PLATFORM_8721D)	//amebad 
#include "ameba_soc.h"
#include "rl6548.h"
#else	//amebapro use audio api
#include "audio_api.h"
#endif


#if defined(CONFIG_PLATFORM_8195BHP) || defined(CONFIG_PLATFORM_8735B)
#define ENABLE_ASP 1    //amebapro/pro2 AEC
#define AUDIO_DEBUG_SHOW 1

#define CONFIG_MMF_AUDIO_DEBUG 0
#define CONFIG_MMF_AUDIO_ATAF 1


typedef enum {
	USE_AUDIO_AMIC = 0,
	USE_AUDIO_LEFT_DMIC = 1,
	USE_AUDIO_RIGHT_DMIC = 2,
	USE_AUDIO_STEREO_DMIC = 3,
} audio_mic_type;

#else

#define ENABLE_SPEEX_AEC 0

#endif

#define CMD_AUDIO_SET_PARAMS     		MM_MODULE_CMD(0x00)  // set parameter
#define CMD_AUDIO_GET_PARAMS     		MM_MODULE_CMD(0x01)  // get parameter
#define CMD_AUDIO_SET_SAMPLERATE		MM_MODULE_CMD(0x02)
#define CMD_AUDIO_SET_WORDLENGTH		MM_MODULE_CMD(0x03)
#define CMD_AUDIO_SET_MICGAIN			MM_MODULE_CMD(0x04)
#define CMD_AUDIO_SET_AES			MM_MODULE_CMD(0x05)
#define CMD_AUDIO_SET_ADC_GAIN          	MM_MODULE_CMD(0x06)
#define CMD_AUDIO_SET_DAC_GAIN          	MM_MODULE_CMD(0x07)
#if defined(CONFIG_PLATFORM_8195BHP) || defined(CONFIG_PLATFORM_8735B)
#define CMD_AUDIO_SET_RESET             	MM_MODULE_CMD(0x08)

#define CMD_AUDIO_SET_AUDIO_STOP        	MM_MODULE_CMD(0x0A)
#define CMD_AUDIO_SET_AUDIO_START       	MM_MODULE_CMD(0x0B)
#define CMD_AUDIO_SET_TRX			MM_MODULE_CMD(0x0C)
#define CMD_AUDIO_SET_VOL			MM_MODULE_CMD(0x0D)
#if defined(CONFIG_PLATFORM_8735B)
#define CMD_AUDIO_SET_MIC_RECORD_FUN		MM_MODULE_CMD(0x0E)
#endif

#define CMD_AUDIO_SET_NS_ENABLE			MM_MODULE_CMD(0x10)
#define CMD_AUDIO_SET_AEC_ENABLE		MM_MODULE_CMD(0x11)
#define CMD_AUDIO_SET_AGC_ENABLE		MM_MODULE_CMD(0x12)
#define CMD_AUDIO_SET_VAD_ENABLE		MM_MODULE_CMD(0x13)

#define CMD_AUDIO_RUN_NS			MM_MODULE_CMD(0x14)
#define CMD_AUDIO_RUN_AEC			MM_MODULE_CMD(0x15)
#define CMD_AUDIO_RUN_AGC			MM_MODULE_CMD(0x16)
#define CMD_AUDIO_RUN_VAD			MM_MODULE_CMD(0x17)

#define CMD_AUDIO_SET_AEC_LEVEL			MM_MODULE_CMD(0x18)
#define CMD_AUDIO_SET_MIC_ENABLE		MM_MODULE_CMD(0x19)
#define CMD_AUDIO_SET_SPK_ENABLE		MM_MODULE_CMD(0x20)

#endif
#define CMD_AUDIO_APPLY				MM_MODULE_CMD(0x21)  // for hardware module

#define USE_DEFAULT_AUDIO_SET			1	//Use the default setting of audio module defined in module_audio.c

#if defined(CONFIG_PLATFORM_8735B)
typedef struct eq_cof_s {
	uint32_t eq_enable;
	uint32_t eq_h0;
	uint32_t eq_b1;
	uint32_t eq_b2;
	uint32_t eq_a1;
	uint32_t eq_a2;
} eq_cof_t;
#endif

#if defined(CONFIG_PLATFORM_8721D)	//amebad
typedef struct {
	GDMA_InitTypeDef       	SpTxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef
	GDMA_InitTypeDef       	SpRxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef
} SP_GDMA_STRUCT, *pSP_GDMA_STRUCT;

typedef struct audio_param_s {
	uint32_t sample_rate;
	uint32_t word_length;
	uint32_t mono_stereo;
	uint32_t direction;
	uint32_t enable_aec;		// 0
	uint32_t mix_mode;		// 0
} audio_params_t;
#else	//amebapro and amebapro2
typedef struct audio_param_s {
	audio_sr        sample_rate;	// ASR_8KHZ
	audio_wl        word_length;	// WL_16BIT
	audio_mic_gain  mic_gain;		// MIC_40DB
	audio_dmic_gain dmic_l_gain;    // DMIC_BOOST_24DB
	audio_dmic_gain dmic_r_gain;    // DMIC_BOOST_24DB

	int				channel;		// 1
	int				enable_aec;		// 0: off  1: on
	int				enable_ns;		// 0: off, 1: out 2: in 3: in/out
	int				enable_agc;		// 0: off, 1: output agc
	int				enable_vad;		// 0: off  1: input vad
	int				mix_mode;		// 0
	uint8_t				use_mic_type;   	// 0: AMIC 1: DMIC

#if defined(CONFIG_PLATFORM_8735B) //TODO: test on other platform
	int			enable_record;
	int 			NS_level;
	int 			NS_level_SPK;
	int 			ADC_gain;
	int 			DAC_gain;
	int16_t 		AEC_CNG_EN;			// enable comfortable noise or not
	int 			AEC_sdelay_ms;			// 0 ~ 500
	int 			AEC_level;			// 0 ~ 4
	int 			AGC_mode;			// 0: Unchanged, 1: kAgcModeAdaptiveAnalog, 2: kAgcModeAdaptiveDigital, 3: kAgcModeFixedDigital
	int 			AGC_targetLevelDbfs;		// target output level of AGC 0~31 (set 5 means output compressed to -5dBFS)
	int 			AGC_compression_gain_db;	// 0~60
	int				AGC_AttackTime ;	//800-2000msec
	int				AGC_ReleaseTime ;   //800-2000msec
	int 			AGC_limiter_enable;		// enable limiter (means the boost will be limit in target level)
	int 			AGC_mode_SPK;			// 0: Unchanged, 1: kAgcModeAdaptiveAnalog, 2: kAgcModeAdaptiveDigital, 3: kAgcModeFixedDigital
	int 			AGC_targetLevelDbfs_SPK;	// target output level of AGC 0~31 (set 5 means output compressed to -5dBFS)
	int 			AGC_compression_gain_db_SPK;	// 0~60
	int 			AGC_limiter_enable_SPK;		// enable limiter (means the boost will be limit in target level)
	int				AGC_AttackTime_SPK;	//800-2000msec
	int				AGC_ReleaseTime_SPK;   //800-2000msec
	int 			mic_bias; 			// 0:0.9 1:0.86 2:0.75
	int 			hpf_set; 			// 0~7
	eq_cof_t        	mic_l_eq[5];
	eq_cof_t        	mic_r_eq[5];
	eq_cof_t        	spk_l_eq[5];
#endif
	//...
} audio_params_t;
#endif

typedef struct audio_ctx_s {
	void             *parent;
#if !defined(CONFIG_PLATFORM_8721D)	//amebapro
	audio_t          *audio;
#endif

	audio_params_t    params;

	uint8_t			inited_aec;
	uint8_t			inited_ns;
	uint8_t			inited_agc;
	uint8_t			inited_vad;

	uint8_t			run_aec;
	uint8_t			run_ns;
	uint8_t			run_agc;
	uint8_t			run_vad;

	uint8_t			dmic_pin_set;

	uint32_t		sample_rate;
	uint8_t			word_length; // Byte
	// for AEC
	TaskHandle_t		aec_rx_task;
	xSemaphoreHandle	aec_rx_done_sema;

	//for drop frame debug
	uint32_t		timer_1;
	uint32_t		timer_2;
	uint32_t		drop_frame;
	uint32_t		audio_frame;
	uint32_t		drop_frame_total;
	uint32_t		audio_frame_total;
#if defined(CONFIG_PLATFORM_8735B)
	void (*mic_record_file)(void *, void *, void *, void *);
#endif
} audio_ctx_t;

extern audio_params_t default_audio_params;

extern mm_module_t audio_module;
#endif
