#ifndef ASP_H
#define ASP_H

#include <stdint.h>

typedef enum {
	SPEEX_AEC,
	WEBRTC_AEC,
	WEBRTC_AECM,
} AEC_CORE;

typedef struct farend_pcm_pack {
	unsigned long time_usec;
	int flag;

	unsigned char *pcm_buf;
	unsigned int length;
} farend_pcm_pack;

#if defined(CONFIG_PLATFORM_8735B) && (defined(CONFIG_NEWAEC) && CONFIG_NEWAEC) //consilient AEC only suppored on 8735 now
typedef enum {
	CT_ALC = 0,
	CT_DRC,
	CT_LIMITER,
} CT_AGC_MODE;
//Setting for ASP
typedef struct CTNS_cfg_s {
	int16_t NS_EN;
	int16_t NSLevel;
	int16_t HPFEnable;

	int16_t Reserve1;
	int16_t Reserve2;
} CTNS_cfg_t;

typedef struct CTAGC_cfg_s {
	int16_t AGC_EN;
	CT_AGC_MODE AGCMode;
	int16_t ReferenceLvl;
	int16_t RefThreshold;
	int16_t AttackTime;
	int16_t ReleaseTime;
	int16_t Ratio[3];
	int16_t Threshold[3]; // Threshold1, Threshold2, NoiseGateLvl
	int16_t KneeWidth;
	int16_t NoiseFloorAdaptEnable;
	int16_t RMSDetectorEnable;

	int16_t Reserve1;
} CTAGC_cfg_t;

typedef struct CTAEC_cfg_s {
	int16_t AEC_EN;
	int16_t EchoTailLen;
	int16_t CNGEnable;
	int16_t PPLevel;
	int16_t DTControl;

	int16_t Reserve1;
	int16_t Reserve2;
} CTAEC_cfg_t;

void AEC_init(int16_t frame_size, int32_t sample_freq, CTAEC_cfg_t *RX_AEC, CTAGC_cfg_t *RX_AGC, CTNS_cfg_t *RX_NS, float snd_amplification);
int AEC_set_level(int level, CTAEC_cfg_t *RX_AEC);
int NS_set_level_for_AEC(int level, CTNS_cfg_t *RX_NS);
int AEC_process(const int16_t *farend, const int16_t *nearend, int16_t *out);
void AEC_destory(void);

void NS_init(int32_t sample_freq, CTNS_cfg_t *TX_NS);
int NS_set_level_for_TX(int level, CTNS_cfg_t *TX_NS);
void NS_process(int16_t frame_size, int16_t *out);
void NS_destory(void);

void AGC_init(int32_t sample_freq, CTAGC_cfg_t *TX_AGC);
void AGC_process(int16_t frame_size, int16_t *out);
void AGC_destory(void);
void AEC_set_print(uint8_t flag);
const char *ASP_get_version(void);
void ASP_print_version(void);
#else

/**
 *      - agc_mode           : 0 - Unchanged
 *                          : 1 - Adaptive Analog Automatic Gain Control -3dBOv
 *                          : 2 - Adaptive Digital Automatic Gain Control -3dBOv
 *                          : 3 - Fixed Digital Gain 0dB
 *
 *      - ns_mode	: 0: Mild, 1: Medium , 2: Aggressive
**/
typedef struct WebrtcAEC_cfg_s {
	int16_t AEC_EN;
	//AEC parameters
	AEC_CORE aec_core;
	int FilterLength;
	int16_t AECLevel;
	int16_t CNGEnable;

	//AGC parameters for AEC
	int16_t AGC_EN;
	int16_t AGCMode;
	int16_t TargetLevelDbfs;
	int16_t CompressionGaindB;
	uint8_t LimiterEnable;

	//NS parameters
	int16_t NS_EN;
	int NSLevel;

	int16_t HOWL_EN;
	//AGC parameters for howling
	int16_t HOWL_AGC_EN;
	int16_t HOWL_AGCMode;
	int16_t HOWL_TargetLevelDbfs;
	int16_t HOWL_CompressionGaindB;
	uint8_t HOWL_LimiterEnable;

	//NS parameters for howling
	int16_t HOWL_NS_EN;
	int HOWL_NSLevel;

	int16_t Reserve1;
	int16_t Reserve2;
	int16_t Reserve3;
} WebrtcAEC_cfg_t;

typedef struct WebrtcAGC_cfg_s {
	int16_t AGC_EN;
	int16_t AGCMode;
	int16_t TargetLevelDbfs;
	int16_t CompressionGaindB;
	uint8_t LimiterEnable;

	int16_t Reserve1;
	int16_t Reserve2;
	int16_t Reserve3;
} WebrtcAGC_cfg_t;

typedef struct WebrtcNS_cfg_s {
	int16_t NS_EN;
	int16_t NSLevel;

	int16_t Reserve1;
	int16_t Reserve2;
	int16_t Reserve3;
} WebrtcNS_cfg_t;

typedef struct WebrtcVAD_cfg_s {
	int16_t VAD_EN;
	int16_t VadMode;

	int16_t Reserve1;
	int16_t Reserve2;
	int16_t Reserve3;
} WebrtcVAD_cfg_t;

void AEC_init(int16_t frame_size, int32_t sample_freq, WebrtcAEC_cfg_t *RX_AEC, float snd_amplification);
int AEC_set_level(int AECLevel, WebrtcAEC_cfg_t *RX_AEC);
int AEC_process(const int16_t *farend, const int16_t *nearend, int16_t *out);

//for howling suppression
int AEC_process_h(const int16_t *farend, const int16_t *nearend, int16_t *out, int sDelay);
void AEC_destory(void);

void set_sndcard_delay_ms_for_AEC(int16_t ms, WebrtcAEC_cfg_t *RX_AEC);

void set_agc_config_for_AEC(int16_t TargetLevelDbfs, int16_t CompressionGaindB, uint8_t LimiterEnable, WebrtcAEC_cfg_t *RX_AEC);
void set_agc_config_for_howling(int16_t TargetLevelDbfs, int16_t CompressionGaindB, uint8_t LimiterEnable, WebrtcAEC_cfg_t *RX_AEC);


void AGC_init(int32_t sample_freq, WebrtcAGC_cfg_t *TX_AGC);
void AGC_destory(void);
void AGC_process(int16_t frame_size, int16_t *out);

void AGC2_init(int32_t sample_freq, WebrtcAGC_cfg_t *RX_AGC);
void AGC2_destory(void);
void AGC2_process(int16_t frame_size, int16_t *out);

void NS_init(int32_t sample_freq, WebrtcNS_cfg_t *TX_NS);
void NS_destory(void);
void NS_process(int16_t frame_size, int16_t *out);

void NS2_init(int32_t sample_freq, WebrtcNS_cfg_t *RX_NS);
void NS2_destory(void);
void NS2_process(int16_t frame_size, int16_t *out);

void VAD_init(int32_t sample_freq, WebrtcVAD_cfg_t *RX_VAD);
void VAD_destory(void);
int VAD_process(int16_t frame_size, int16_t *out);

//reset the farend buffer of AEC
void AEC_Farend_Reset(void);

//enable use AEC to do howling (if user want to use, it must be set before AEC_init)
void set_howling_enable(uint8_t Howling_process_on, WebrtcAEC_cfg_t *RX_AEC);

//enable AEC, AGC, NS
//AGC and NS => on means it will process AGC and NS
//AEC: 1 normal on, 2 aec will process but output will not use the result, 0 aec not process
void set_module_enable(uint8_t AEC_on, uint8_t AGC_on, uint8_t NS_on, WebrtcAEC_cfg_t *RX_AEC);
#endif
#endif // ASP_H
