#ifndef _MODULE_AUDIO_H
#define _MODULE_AUDIO_H

#include "mmf2_module.h"
#include "mmf2_dbg.h"
#if defined(CONFIG_PLATFORM_8721D)	//amebad 
#include "ameba_soc.h"
#include "rl6548.h"
#else	//amebapro use audio api
#include "audio_api.h"
#endif


#if defined(CONFIG_PLATFORM_8195BHP) || defined(CONFIG_PLATFORM_8735B)
#if defined(CONFIG_PLATFORM_8195BHP)
#include "AEC.h"
#elif defined(CONFIG_PLATFORM_8735B)
#include "ASP.h"
#endif

#define ENABLE_ASP 1        //amebapro/pro2 AEC
#define AUDIO_LOG_LEVEL 2   //set audio default log level, 0: no message, 1: all message, 2: warn, err message, 3: only err message
#define AEC_LOG_EN 1

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

#define CMD_AUDIO_SET_PARAMS            MM_MODULE_CMD(0x00)  // set parameter
#define CMD_AUDIO_SET_PARAMS            MM_MODULE_CMD(0x00)  // set parameter
#define CMD_AUDIO_GET_PARAMS            MM_MODULE_CMD(0x01)  // get parameter
#define CMD_AUDIO_SET_SAMPLERATE        MM_MODULE_CMD(0x02)
#define CMD_AUDIO_SET_WORDLENGTH        MM_MODULE_CMD(0x03)
#define CMD_AUDIO_SET_MICGAIN           MM_MODULE_CMD(0x04)
#define CMD_AUDIO_SET_AES               MM_MODULE_CMD(0x05)
#define CMD_AUDIO_SET_ADC_GAIN          MM_MODULE_CMD(0x06)
#define CMD_AUDIO_SET_DAC_GAIN          MM_MODULE_CMD(0x07)
#if defined(CONFIG_PLATFORM_8195BHP) || defined(CONFIG_PLATFORM_8735B)
#define CMD_AUDIO_SET_RESET             MM_MODULE_CMD(0x08)

#define CMD_AUDIO_SET_AUDIO_STOP        MM_MODULE_CMD(0x0A)
#define CMD_AUDIO_SET_AUDIO_START       MM_MODULE_CMD(0x0B)
#define CMD_AUDIO_SET_TRX               MM_MODULE_CMD(0x0C)
#define CMD_AUDIO_SET_VOL               MM_MODULE_CMD(0x0D)
#if defined(CONFIG_PLATFORM_8735B)
#define CMD_AUDIO_SET_MIC_RECORD_FUN    MM_MODULE_CMD(0x0E)
#endif

#define CMD_AUDIO_SET_NS_ENABLE         MM_MODULE_CMD(0x10)
#define CMD_AUDIO_SET_AEC_ENABLE        MM_MODULE_CMD(0x11)
#define CMD_AUDIO_SET_AGC_ENABLE        MM_MODULE_CMD(0x12)
#define CMD_AUDIO_SET_VAD_ENABLE        MM_MODULE_CMD(0x13)

#define CMD_AUDIO_RUN_NS                MM_MODULE_CMD(0x14)
#define CMD_AUDIO_RUN_AEC               MM_MODULE_CMD(0x15)
#define CMD_AUDIO_RUN_AGC               MM_MODULE_CMD(0x16)
#define CMD_AUDIO_RUN_VAD               MM_MODULE_CMD(0x17)

#define CMD_AUDIO_SET_AEC_LEVEL         MM_MODULE_CMD(0x18)
#define CMD_AUDIO_SET_MIC_ENABLE        MM_MODULE_CMD(0x19)
#define CMD_AUDIO_SET_SPK_ENABLE        MM_MODULE_CMD(0x1A)

#define CMD_AUDIO_GET_FIRST_DATA_TS     MM_MODULE_CMD(0x1B)
#define CMD_AUDIO_GET_FIRST_DUMMY_TS    MM_MODULE_CMD(0x1C)

#define CMD_AUDIO_SET_LEFTMIC_CB        MM_MODULE_CMD(0x1D)
#define CMD_AUDIO_SET_RIGHTMIC_CB       MM_MODULE_CMD(0x1F)

#endif
#define CMD_AUDIO_SET_TIMESTAMP_OFFSET  MM_MODULE_CMD(0x21)
#define CMD_AUDIO_GET_FRAMESIZE_MS      MM_MODULE_CMD(0x22)
#define CMD_AUDIO_SET_MESSAGE_LEVEL     MM_MODULE_CMD(0x23)
#if defined(CONFIG_PLATFORM_8195BHP) || defined(CONFIG_PLATFORM_8735B)
#define CMD_AUDIO_SET_RXASP_PARAM       MM_MODULE_CMD(0x24)
#define CMD_AUDIO_SET_TXASP_PARAM       MM_MODULE_CMD(0x25)
#define CMD_AUDIO_GET_RXASP_PARAM       MM_MODULE_CMD(0x26)
#define CMD_AUDIO_GET_TXASP_PARAM       MM_MODULE_CMD(0x27)
#define CMD_AUDIO_PRINT_ASP_INFO        MM_MODULE_CMD(0x28)
#endif
#define CMD_AUDIO_SET_RX                MM_MODULE_CMD(0x29)
#define CMD_AUDIO_SET_TX                MM_MODULE_CMD(0x2A)

#define CMD_AUDIO_APPLY                 MM_MODULE_CMD(0x30)  // for hardware module

#define USE_DEFAULT_AUDIO_SET			1	//Use the default setting of audio module defined in module_audio.c

#if defined(CONFIG_PLATFORM_8721D)	//amebad
typedef struct {
	GDMA_InitTypeDef       	SpTxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef
	GDMA_InitTypeDef       	SpRxGdmaInitStruct;              //Pointer to GDMA_InitTypeDef
} SP_GDMA_STRUCT, *pSP_GDMA_STRUCT;

typedef struct audio_param_s {
	uint32_t        sample_rate;
	uint32_t        word_length;
	uint32_t        mono_stereo;
	uint32_t        direction;
	uint32_t        enable_aec;     // 0
	uint32_t        mix_mode;       // 0
} audio_params_t;

typedef struct audio_ctx_s {
	void                *parent;

	audio_params_t      params;

	uint8_t             inited_aec;
	uint8_t             inited_ns;
	uint8_t             inited_agc;
	uint8_t             inited_vad;

	uint8_t             run_aec;
	uint8_t             run_ns;
	uint8_t             run_agc;
	uint8_t             run_vad;

	uint8_t             dmic_pin_set;

	uint32_t            sample_rate;
	uint8_t             word_length; // Byte
	// for AEC
	TaskHandle_t        aec_rx_task;
	xSemaphoreHandle    aec_rx_done_sema;

	//for drop frame debug
	uint32_t        timer_1;
	uint32_t        timer_2;
	uint32_t        drop_frame;
	uint32_t        audio_frame;
	uint32_t        drop_frame_total;
	uint32_t        audio_frame_total;
} audio_ctx_t;
#elif defined(CONFIG_PLATFORM_8195BHP) //amebapro
typedef struct audio_param_s {
	audio_sr        sample_rate;	// ASR_8KHZ
	audio_wl        word_length;	// WL_16BIT
	audio_mic_gain  mic_gain;		// MIC_40DB

	int             channel;		// 1
	int             mix_mode;		// 0
	uint8_t         use_mic_type;   // 0: AMIC 1: DMIC

	int             enable_record;

	int             enable_aec;             // 0: off  1: on
	int             enable_ns;              // 0: off, 1: out 2: in 3: in/out
	int             enable_agc;             // 0: off, 1: output agc
	int             enable_vad;             // 0: off  1: input vad
	int             ADC_gain;
	int             DAC_gain;
	//...
} audio_params_t;

typedef struct RX_cfg_s {
	WebrtcAEC_cfg_t aec_cfg;
	WebrtcAGC_cfg_t agc_cfg;
	WebrtcNS_cfg_t  ns_cfg;
	WebrtcVAD_cfg_t vad_cfg;
} RX_cfg_t;

typedef struct TX_cfg_s {
	WebrtcAGC_cfg_t agc_cfg;
	WebrtcNS_cfg_t  ns_cfg;
} TX_cfg_t;

typedef struct audio_ctx_s {
	void            *parent;

	audio_t         *audio;
	audio_params_t  params;

	uint8_t         inited_aec;
	uint8_t         inited_ns;
	uint8_t         inited_agc;
	uint8_t         inited_vad;

	uint8_t         run_aec;
	uint8_t         run_ns;
	uint8_t         run_agc;
	uint8_t         run_vad;

	uint8_t         enable_rxasp;

	uint8_t         dmic_pin_set;

	uint32_t        sample_rate;
	uint8_t         word_length; // Byte

	// for AEC
	TaskHandle_t        aec_rx_task;
	xSemaphoreHandle    aec_rx_done_sema;

	//for drop frame debug
	uint32_t        timer_1;
	uint32_t        timer_2;
	uint32_t        drop_frame;
	uint32_t        audio_frame;
	uint32_t        drop_frame_total;
	uint32_t        audio_frame_total;
	void (*mic_record_file)(void *, void *, void *, void *);

	uint8_t         fcs_avsync_done;

	RX_cfg_t        rxcfg;
	TX_cfg_t        txcfg;
	uint8_t         rx_first_frame;

	uint32_t        audio_timestamp_offset;
} audio_ctx_t;

extern TX_cfg_t default_tx_asp_params;
extern RX_cfg_t default_rx_asp_params;
extern audio_params_t default_audio_params;
#elif defined(CONFIG_PLATFORM_8735B) //amebapro2
typedef struct eq_cof_s {
	uint32_t        eq_enable;
	uint32_t        eq_h0;
	uint32_t        eq_b1;
	uint32_t        eq_b2;
	uint32_t        eq_a1;
	uint32_t        eq_a2;
} eq_cof_t;

typedef struct audio_param_s {
	audio_sr        sample_rate;	// ASR_8KHZ
	audio_wl        word_length;	// WL_16BIT
	audio_mic_gain  mic_gain;       // MIC_40DB
	audio_dmic_gain dmic_l_gain;    // DMIC_BOOST_24DB
	audio_dmic_gain dmic_r_gain;    // DMIC_BOOST_24DB

	int             channel;		// 1
	int             mix_mode;		// 0
	uint8_t         use_mic_type;   // 0: AMIC 1: DMIC
	int             mic_bias; 		// 0:0.9 1:0.86 2:0.75
	int             hpf_set; 		// 0~7
	eq_cof_t        mic_l_eq[5];
	eq_cof_t        mic_r_eq[5];
	eq_cof_t        spk_l_eq[5];
	int             ADC_gain;
	int             DAC_gain;

	int             enable_record;
	uint8_t         fcs_avsync_en;
	uint32_t        fcs_avsync_vtime;
	//...
} audio_params_t;
#if defined(CONFIG_NEWAEC) && CONFIG_NEWAEC //CT AEC library only support on 8735
typedef struct RX_cfg_s {
	CTAEC_cfg_t     aec_cfg;
	CTAGC_cfg_t     agc_cfg;
	CTNS_cfg_t      ns_cfg;
} RX_cfg_t;

typedef struct TX_cfg_s {
	CTAGC_cfg_t     agc_cfg;
	CTNS_cfg_t      ns_cfg;
} TX_cfg_t;
#else
typedef struct RX_cfg_s {
	WebrtcAEC_cfg_t aec_cfg;
	WebrtcAGC_cfg_t agc_cfg;
	WebrtcNS_cfg_t  ns_cfg;
	WebrtcVAD_cfg_t vad_cfg;
} RX_cfg_t;

typedef struct TX_cfg_s {
	WebrtcAGC_cfg_t agc_cfg;
	WebrtcNS_cfg_t  ns_cfg;
} TX_cfg_t;
#endif
typedef struct audio_ctx_s {
	void            *parent;

	audio_t         *audio;
	audio_params_t  params;

	uint8_t         inited_aec;
	uint8_t         inited_ns;
	uint8_t         inited_agc;
	uint8_t         inited_vad;

	uint8_t         run_aec;
	uint8_t         run_ns;
	uint8_t         run_agc;
	uint8_t         run_vad;

	uint8_t         enable_rxasp;

	uint8_t         dmic_pin_set;

	uint32_t        sample_rate;
	uint8_t         word_length; // Byte

	// for AEC
	TaskHandle_t        aec_rx_task;
	xSemaphoreHandle    aec_rx_done_sema;

	//for drop frame debug
	uint32_t        timer_1;
	uint32_t        timer_2;
	uint32_t        drop_frame;
	uint32_t        audio_frame;
	uint32_t        drop_frame_total;
	uint32_t        audio_frame_total;
	void (*mic_record_file)(void *, void *, void *, void *);
	void (*left_mic_cb)(const uint8_t *, int, uint8_t, uint32_t, audio_params_t);
	void (*right_mic_cb)(const uint8_t *, int, uint8_t, uint32_t, audio_params_t);

	uint8_t         fcs_avsync_done;

	RX_cfg_t        rxcfg;
	TX_cfg_t        txcfg;
	uint8_t         rx_first_frame;

	uint32_t        audio_timestamp_offset;
	uint32_t        first_data_frame_ts;
	uint32_t        first_dummy_frame_ts;
} audio_ctx_t;

extern TX_cfg_t default_tx_asp_params;
extern RX_cfg_t default_rx_asp_params;
extern audio_params_t default_audio_params;
#endif
extern mm_module_t audio_module;

#endif
