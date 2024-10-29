#ifndef ASP_H
#define ASP_H

#include <stdint.h>

#define TX_CURRENT_STATUS_MASK  (0x01 << 0)
#define RX_CURRENT_STATUS_MASK  (0x01 << 1)
#define TX_LASTFRAME_STATUS_MASK  (0x01 << 2)
#define RX_LASTFRAME_STATUS_MASK  (0x01 << 3)

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

#if (defined(CONFIG_NEWAEC) && CONFIG_NEWAEC)
typedef enum {
	CT_ALC = 0,
	CT_LIMITER,
} CT_AGC_MODE;

typedef enum {
	ADAPTATION = 1,
	SIREN_TONE = 16,
} CT_AEC_MODE;
//Setting for ASP
typedef struct CTNS_cfg_s {
	int16_t NS_EN;
	int16_t NSLevel;
	int16_t HPFEnable;
	int16_t QuickConvergenceEnable; //QuickConvergenceEnable = 1 => NSGainSlowConvergenceEnable = 0

	int16_t Reserve1;
} CTNS_cfg_t;

typedef struct CTAGC_cfg_s {
	int16_t AGC_EN;
	CT_AGC_MODE AGCMode;
	int16_t ReferenceLvl;
	int16_t RatioFormat;    // Ratio format: 0 => integer, range 1~50, 1 => 8.8 fix point, range 26~50*256 (mapping 26/256~50)
	int16_t AttackTime;
	int16_t ReleaseTime;
	int16_t Ratio[3];
	int16_t Threshold[3];   // Threshold1, Threshold2, NoiseGateLvl
	int16_t KneeWidth;
	int16_t NoiseFloorAdaptEnable;
	int16_t RMSDetectorEnable;
	int16_t MaxGainLimit;
} CTAGC_cfg_t;

typedef struct CTAEC_cfg_s {
	int16_t AEC_EN;
	int16_t EchoTailLen;
	int16_t CNGEnable;
	int16_t PPLevel;
	int16_t DTControl;
	int16_t ConvergenceTime;

	int16_t Reserve1;
} CTAEC_cfg_t;

typedef struct CTBF_cfg_s {
	int16_t BF_EN;
	int16_t DOAEnable;
	int16_t MM; //no of mics
	int16_t mic_spacing;
	int16_t mic_array_type;

	int16_t Reserve1;
	int16_t Reserve2;
	int16_t Reserve3;
} CTBF_cfg_t;

typedef struct VQE_SND_STATE_s {
	int16_t DoA;              //in degrees
	int16_t ERLE;             //in dB
	int16_t SinLvldB;         //in dBFs
	int16_t SoutLvldB;        //indBFs after AGC (if AGC is enabled)
	int16_t DTState;          //0 = single talk  or 1 = doulble talk
	int16_t HCDetectState;    //1 = detected, 0 = not detected
	uint8_t AECRun;
	uint8_t AGCRun;
	uint8_t NSRun;
	uint8_t BFRun;

	uint8_t Reserve1;
	uint8_t Reserve2;
	uint8_t Reserve3;
	uint8_t Reserve4;
} VQE_SND_STATE_t;

typedef struct VQE_RCV_STATE_s {
	int16_t RinLvldB;
	int16_t RoutLvldB;
	int16_t HCDetectState;    //1 = detected, 0 = not detected
	uint8_t AGCRun;
	uint8_t NSRun;

	uint8_t Reserve1;
	uint8_t Reserve2;
	uint8_t Reserve3;
	uint8_t Reserve4;
} VQE_RCV_STATE_t;

// VQE SND api is the new api for stereo and mono mic channel
//*************************//
void VQE_SND_init(int16_t frame_size, int32_t sample_freq, CTAEC_cfg_t *RX_AEC, CTAGC_cfg_t *RX_AGC, CTNS_cfg_t *RX_NS, CTBF_cfg_t *RX_BF, void *RX_reserve0,
				  void *RX_reserve1, float snd_amplification, int16_t mic_num);
int VQE_SND_process(const int16_t *farend, const int16_t *mic1, const int16_t *mic2, int16_t *out);
void VQE_SND_destroy(void);
//*************************//
// AEC api is the old api for mono mic channel only
//*************************//
void AEC_init(int16_t frame_size, int32_t sample_freq, CTAEC_cfg_t *RX_AEC, CTAGC_cfg_t *RX_AGC, CTNS_cfg_t *RX_NS, float snd_amplification);
int AEC_process(const int16_t *farend, const int16_t *nearend, int16_t *out);
void AEC_destory(void);
//*************************//
int VQE_SND_set_AEC_level(int level, CTAEC_cfg_t *RX_AEC);
int VQE_SND_set_NS_level(int level, CTNS_cfg_t *RX_NS);
void VQE_SND_set_AGC_runtime_en(uint8_t enable);
void VQE_SND_set_AEC_runtime_en(uint8_t enable);
void VQE_SND_set_AEC_cancelmode(uint8_t mode);
void VQE_SND_set_AEC_convergencetime(int16_t convergencetime, CTAEC_cfg_t *RX_AEC);
uint8_t VQE_SND_get_AEC_cancelmode(void);

void VQE_RCV_NS_init(int32_t sample_freq, CTNS_cfg_t *TX_NS);
int VQE_RCV_set_NS_level(int level, CTNS_cfg_t *TX_NS);
void VQE_RCV_NS_process(int16_t frame_size, int16_t *out);
void VQE_RCV_NS_destroy(void);

void VQE_RCV_AGC_init(int32_t sample_freq, CTAGC_cfg_t *TX_AGC);
void VQE_RCV_set_AGC_runtime_en(uint8_t enable);
void VQE_RCV_AGC_process(int16_t frame_size, int16_t *out);
void VQE_RCV_AGC_destroy(void);

void VQE_set_print(uint8_t flag);
const char *VQE_get_ASP_version(void);
void VQE_print_ASP_version(void);
void VQE_SND_get_status(VQE_SND_STATE_t *snd_state);
void VQE_RCV_get_status(VQE_RCV_STATE_t *rcv_state);

#define ASP_get_version     VQE_get_ASP_version
#define ASP_print_version   VQE_print_ASP_version
#define SND_process         VQE_SND_process
#define RCV_AGC_process     VQE_RCV_AGC_process
#define RCV_NS_process      VQE_RCV_NS_process
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

void Webrtc_SND_init(int16_t frame_size, int32_t sample_freq, WebrtcAEC_cfg_t *RX_AEC, float snd_amplification);
int Webrtc_SND_set_AEC_level(int AECLevel, WebrtcAEC_cfg_t *RX_AEC);
int Webrtc_SND_process(const int16_t *farend, const int16_t *nearend, int16_t *out);

//for howling suppression
int Webrtc_SND_process_h(const int16_t *farend, const int16_t *nearend, int16_t *out, int sDelay);
void Webrtc_SND_destroy(void);

void Webrtc_SND_set_aec_sndcard_delay_ms(int16_t ms, WebrtcAEC_cfg_t *RX_AEC);

void Webrtc_SND_set_agc_config(int16_t TargetLevelDbfs, int16_t CompressionGaindB, uint8_t LimiterEnable, WebrtcAEC_cfg_t *RX_AEC);
void Webrtc_SND_set_agc_config_for_howling(int16_t TargetLevelDbfs, int16_t CompressionGaindB, uint8_t LimiterEnable, WebrtcAEC_cfg_t *RX_AEC);


void Webrtc_RCV_AGC_init(int32_t sample_freq, WebrtcAGC_cfg_t *TX_AGC);
void Webrtc_RCV_AGC_destroy(void);
void Webrtc_RCV_AGC_process(int16_t frame_size, int16_t *out);

void Webrtc_SND_AGC_init(int32_t sample_freq, WebrtcAGC_cfg_t *RX_AGC);
void Webrtc_SND_AGC_destroy(void);
void Webrtc_SND_AGC_process(int16_t frame_size, int16_t *out);

void Webrtc_RCV_NS_init(int32_t sample_freq, WebrtcNS_cfg_t *TX_NS);
void Webrtc_RCV_NS_destroy(void);
void Webrtc_RCV_NS_process(int16_t frame_size, int16_t *out);

void Webrtc_SND_NS_init(int32_t sample_freq, WebrtcNS_cfg_t *RX_NS);
void Webrtc_SND_NS_destroy(void);
void Webrtc_SND_NS_process(int16_t frame_size, int16_t *out);

void Webrtc_SND_VAD_init(int32_t sample_freq, WebrtcVAD_cfg_t *RX_VAD);
void Webrtc_SND_VAD_destroy(void);
int Webrtc_SND_VAD_process(int16_t frame_size, int16_t *out);

//reset the farend buffer of AEC
void Webrtc_SND_reset_aec_farend(void);

//enable use AEC to do howling (if user want to use, it must be set before AEC_init)
void Webrtc_SND_set_howling_enable(uint8_t Howling_process_on, WebrtcAEC_cfg_t *RX_AEC);

//enable AEC, AGC, NS
//AGC and NS => on means it will process AGC and NS
//AEC: 1 normal on, 2 aec will process but output will not use the result, 0 aec not process
void Webrtc_SND_set_module_enable(uint8_t AEC_on, uint8_t AGC_on, uint8_t NS_on, WebrtcAEC_cfg_t *RX_AEC);

const char *Webrtc_get_ASP_version(void);
void Webrtc_print_ASP_version(void);

#define ASP_get_version     Webrtc_get_ASP_version
#define ASP_print_version   Webrtc_print_ASP_version
#define SND_process         Webrtc_SND_process
#define SND_VAD_process     Webrtc_SND_VAD_process
#define SND_AGC_process     Webrtc_SND_AGC_process
#define SND_NS_process      Webrtc_SND_NS_process
#define RCV_AGC_process     Webrtc_RCV_AGC_process
#define RCV_NS_process      Webrtc_RCV_NS_process
#endif
#endif // ASP_H
