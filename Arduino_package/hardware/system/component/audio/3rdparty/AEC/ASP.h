#ifndef ASP_H
#define ASP_H

#include <stdint.h>

typedef enum {
	SPEEX_AEC,
	WEBRTC_AEC,
	WEBRTC_AECM,
#if defined(CONFIG_PLATFORM_8735B) && (defined(CONFIG_BUILD_CT) && CONFIG_BUILD_CT)
	CT_AEC
#endif
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

#if defined(CONFIG_PLATFORM_8735B) && (defined(CONFIG_BUILD_CT) && CONFIG_BUILD_CT)
typedef struct ct_aec_property {
	//void *ct_aec;
	//void *ct_ns;
	//void *ct_agc;

	int16_t frame_size;
	int32_t sample_freq;
	int32_t echo_tail_length;
	int16_t enable_aec;
	int16_t enable_agc;
	int16_t enable_ns;
	int16_t initialed_rx;
	int16_t initialed_tx_agc;
	int16_t initialed_tx_ns;
} ct_aec_property;
#endif

typedef struct farend_pcm_pack {
	unsigned long time_usec;
	int flag;

	unsigned char *pcm_buf;
	unsigned int length;
} farend_pcm_pack;

#if defined(CONFIG_PLATFORM_8735B) && (defined(CONFIG_BUILD_CT) && CONFIG_BUILD_CT) //consilient AEC only suppored on 8735 now
//Setting for AEC
void AEC_init(int16_t frame_size, int32_t sample_freq, AEC_CORE aec_core,
			  int filter_length, int16_t agc_mode, int16_t targetLevelDbfs, int16_t compression_gain_db, int16_t AGCAttackTime, int16_t AGCReleaseTime, int ns_mode,
			  float snd_amplification);
int AEC_set_level(int level);
int AEC_process(const int16_t *farend, const int16_t *nearend, int16_t *out);
void AEC_destory(void);
void AEC_set_CNG(int16_t set_CNG);
int AEC_set_level(int level);
int NS_set_level_for_AEC(int level);
void set_sndcard_delay_ms_for_AEC(int16_t ms);
void set_agc_config_for_AEC(int16_t targetLevelDbfs, int16_t compressionGaindB, uint8_t limiterEnable);

//Setting for TX AGC
void AGC_init(int32_t sample_freq, int16_t agc_mode, int16_t targetLevelDbfs, int16_t compression_gain_db, int16_t attack_time, int16_t release_time);
void AGC_destory(void);
void AGC_process(int16_t frame_size, int16_t *out);
void set_agc_config_for_TX(int16_t targetLevelDbfs, int16_t compressionGaindB, uint8_t limiterEnable);

//Setting for RX AGC
void AGC2_init(int32_t sample_freq, int16_t agc_mode, int16_t targetLevelDbfs, int16_t compression_gain_db, uint8_t limiter_enable);
void AGC2_destory(void);
void AGC2_process(int16_t frame_size, int16_t *out);

void NS_init(int32_t sample_freq, int16_t ns_mode);
void NS_destory(void);
void NS_process(int16_t frame_size, int16_t *out);
int NS_set_level_for_TX(int level);

void NS2_init(int32_t sample_freq, int16_t ns_mode);
void NS2_destory(void);
void NS2_process(int16_t frame_size, int16_t *out);

//enable AEC, AGC, NS
//AGC and NS => on means it will process AGC and NS
//AEC: 1 normal on, 2 aec will process but output will not use the result, 0 aec not process
void set_module_enable(uint8_t AEC_on, uint8_t AGC_on, uint8_t NS_on);

#else

#define FAREND_PCM_PACK_INITIALIZER {0, 0, 0, 0};
#define FAREND_PCM_PACK_MIN_DIFF_TIME 500000 // usec
extern int PLAYBACK_DELAY;

/**
 *      - agc_mode           : 0 - Unchanged
 *                          : 1 - Adaptive Analog Automatic Gain Control -3dBOv
 *                          : 2 - Adaptive Digital Automatic Gain Control -3dBOv
 *                          : 3 - Fixed Digital Gain 0dB
 *
 *      - ns_mode	: 0: Mild, 1: Medium , 2: Aggressive
**/

void AEC_init(int16_t frame_size, int32_t sample_freq, AEC_CORE aec_core,
			  int filter_length, int16_t agc_mode, int16_t targetLevelDbfs, int16_t compression_gain_db, uint8_t limiter_enable, int ns_mode, float snd_amplification);


int AEC_set_level(int level);
int AEC_process(const int16_t *farend, const int16_t *nearend, int16_t *out);

//for howling suppression
int AEC_process_h(const int16_t *farend, const int16_t *nearend, int16_t *out, int sDelay);
void AEC_destory(void);
int AEC_agc(int16_t *out);
void AEC_set_CNG(int16_t set_CNG);

int speex_aec_playback_for_async(int16_t *farend, float snd_amplification);
#define speex_aec_playback_for_async_default(farend) speex_aec_playback_for_async(farend, 1.0f)

void set_sndcard_delay_ms_for_AEC(int16_t ms);

void set_agc_config_for_AEC(int16_t targetLevelDbfs, int16_t compressionGaindB, uint8_t limiterEnable);
void set_agc_config_for_AEC_h(int16_t targetLevelDbfs, int16_t compressionGaindB, uint8_t limiterEnable);


void AGC_init(int32_t sample_freq, int16_t agc_mode, int16_t targetLevelDbfs, int16_t compression_gain_db, uint8_t limiter_enable);
void AGC_destory(void);
void AGC_process(int16_t frame_size, int16_t *out);

void AGC2_init(int32_t sample_freq, int16_t agc_mode, int16_t targetLevelDbfs, int16_t compression_gain_db, uint8_t limiter_enable);
void AGC2_destory(void);
void AGC2_process(int16_t frame_size, int16_t *out);

void NS_init(int32_t sample_freq, int16_t ns_mode);
void NS_destory(void);
void NS_process(int16_t frame_size, int16_t *out);

void NS2_init(int32_t sample_freq, int16_t ns_mode);
void NS2_destory(void);
void NS2_process(int16_t frame_size, int16_t *out);

void VAD_init(int32_t sample_freq, int16_t vad_mode);
void VAD_destory(void);
int VAD_process(int16_t frame_size, int16_t *out);

//reset the farend buffer of AEC
void AEC_Farend_Reset(void);

//enable use AEC to do howling (if user want to use, it must be set before AEC_init)
void set_howling_enable(uint8_t Howling_process_on);

//enable AEC, AGC, NS
//AGC and NS => on means it will process AGC and NS
//AEC: 1 normal on, 2 aec will process but output will not use the result, 0 aec not process
void set_module_enable(uint8_t AEC_on, uint8_t AGC_on, uint8_t NS_on);
#endif
#endif // ASP_H
