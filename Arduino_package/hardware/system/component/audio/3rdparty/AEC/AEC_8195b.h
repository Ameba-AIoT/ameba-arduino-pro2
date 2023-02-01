#ifndef AEC_8195B_H
#define AEC_8195B_H

#include <stdint.h>

typedef enum {
	SPEEX_AEC,
	WEBRTC_AEC,
	WEBRTC_AECM
} AEC_CORE;

typedef struct speex_aec_property {
	void *speex_echo_state;
	void *speex_preprocess_state;
	void *speex_preprocess_state_tmp;

	int16_t frame_size;
	int32_t filter_length;
	int32_t sample_freq;
	int32_t *nosie;
} speex_aec_property;

typedef struct webrtc_aec_property {
	void *webrtc_aec;
	void *webrtc_ns;
	void *webrtc_ns2;
	void *webrtc_agc;
	void *webrtc_h_ns;
	void *webrtc_h_ns2;
	void *webrtc_h_agc;

	int16_t frame_size;
	int32_t sample_freq;
	int32_t sndcard_sample_freq;
	int16_t sndcard_delay_ms;
	uint8_t enable_aec;
	uint8_t enable_agc;
	uint8_t enable_ns;
} webrtc_aec_property;

typedef struct webrtc_aecm_property {
	void *webrtc_aec;
	void *webrtc_ns;
	void *webrtc_ns2;
	void *webrtc_agc;
	void *webrtc_h_ns;
	void *webrtc_h_ns2;
	void *webrtc_h_agc;

	int16_t frame_size;
	int32_t sample_freq;
	int32_t sndcard_sample_freq;
	int16_t sndcard_delay_ms;
	uint8_t enable_aec;
	uint8_t enable_agc;
	uint8_t enable_ns;
    uint8_t enable_howling;
	uint8_t enable_agc_h;
	uint8_t enable_ns_h;
} webrtc_aecm_property;

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

void AEC_init(int16_t frame_size, int32_t sample_freq, WebrtcAEC_cfg_t* RX_AEC, float snd_amplification);
int AEC_set_level(int AECLevel, WebrtcAEC_cfg_t* RX_AEC);
int AEC_process(const int16_t *farend, const int16_t *nearend, int16_t *out);

//for howling suppression
int AEC_process_h(const int16_t *farend, const int16_t *nearend, int16_t *out, int sDelay);
void AEC_destory(void);

void set_sndcard_delay_ms_for_AEC(int16_t ms, WebrtcAEC_cfg_t* RX_AEC);

void set_agc_config_for_AEC(int16_t TargetLevelDbfs, int16_t CompressionGaindB, uint8_t LimiterEnable, WebrtcAEC_cfg_t* RX_AEC);
void set_agc_config_for_howling(int16_t TargetLevelDbfs, int16_t CompressionGaindB, uint8_t LimiterEnable, WebrtcAEC_cfg_t* RX_AEC);


void AGC_init(int32_t sample_freq, WebrtcAGC_cfg_t* TX_AGC);
void AGC_destory(void);
void AGC_process(int16_t frame_size, int16_t *out);

void AGC2_init(int32_t sample_freq, WebrtcAGC_cfg_t* RX_AGC);
void AGC2_destory(void);
void AGC2_process(int16_t frame_size, int16_t *out);

void NS_init(int32_t sample_freq, WebrtcNS_cfg_t* TX_NS);
void NS_destory(void);
void NS_process(int16_t frame_size, int16_t *out);

void NS2_init(int32_t sample_freq, WebrtcNS_cfg_t* RX_NS);
void NS2_destory(void);
void NS2_process(int16_t frame_size, int16_t *out);

void VAD_init(int32_t sample_freq, WebrtcVAD_cfg_t* RX_VAD);
void VAD_destory(void);
int VAD_process(int16_t frame_size, int16_t *out);

//reset the farend buffer of AEC
void AEC_Farend_Reset(void);

//enable use AEC to do howling (if user want to use, it must be set before AEC_init)
void set_howling_enable(uint8_t Howling_process_on, WebrtcAEC_cfg_t* RX_AEC);

//enable AEC, AGC, NS
//AGC and NS => on means it will process AGC and NS
//AEC: 1 normal on, 2 aec will process but output will not use the result, 0 aec not process
void set_module_enable(uint8_t AEC_on, uint8_t AGC_on, uint8_t NS_on, WebrtcAEC_cfg_t* RX_AEC);

#endif // AEC_H
