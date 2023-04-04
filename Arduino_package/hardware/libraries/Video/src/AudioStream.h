#ifndef __AUDIOSTREAM_H__
#define __AUDIOSTREAM_H__

#define CONFIG_NEWAEC 1

#ifdef __cplusplus
extern "C" {
#endif

#include "audio_api.h"
#include "module_audio.h"
#include "avcodec.h"

#ifdef __cplusplus
}
#endif

#include "VideoStream.h"

typedef enum {
    CODEC_AAC = AV_CODEC_ID_MP4A_LATM,
    CODEC_G711_PCMU = AV_CODEC_ID_PCMU,
    CODEC_G711_PCMA = AV_CODEC_ID_PCMA,
} Audio_Codec_T;

class AudioSetting {
    public:
        AudioSetting(uint8_t preset = 0);
        AudioSetting(uint32_t sampleRate, uint8_t channelCount,      uint8_t micType = USE_AUDIO_AMIC);

        uint32_t _sampleRate = 8000;
        audio_params_t _audioParams = {
            .sample_rate    = ASR_8KHZ,
            .word_length    = WL_16BIT,
            .mic_gain       = MIC_0DB,
            .dmic_l_gain    = DMIC_BOOST_0DB,
            .dmic_r_gain    = DMIC_BOOST_0DB,
            .channel        = 1,
            .mix_mode       = 0,
            .use_mic_type   = USE_AUDIO_AMIC,
            .mic_bias       = 0,
            .hpf_set        = 0,
//            .mic_l_eq[0]    = {1, 0x01ca2925, 0x1c000000, 0x02000000, 0x038ea551, 0x1e6600bf}, //USE EQ for HPF 200Hz @ sample rate 8kHz
//            .mic_r_eq[0]    = {1, 0x01ca2925, 0x1c000000, 0x02000000, 0x038ea551, 0x1e6600bf}, //USE EQ for HPF 200Hz @ sample rate 8kHz
//            .spk_l_eq[0]    = {1, 0x01ca2925, 0x1c000000, 0x02000000, 0x038ea551, 0x1e6600bf}, //USE EQ for HPF 200Hz @ sample rate 8kHz
            .ADC_gain       = 0x7F, // 0x00 - 0x7F
            .DAC_gain       = 0x7F, // 0x00 - 0xAF
        };
};

class Audio:public MMFModule {
    public:
        Audio(void);
        ~Audio(void);

        void configAudio(AudioSetting& config);
        void configMicAEC(uint8_t enable, uint8_t level = 5);
        void configMicAGC(uint8_t enable, uint8_t dBFS = 6);
        void configMicNS(uint8_t enable, uint8_t level = 12);
        void configSpkAGC(uint8_t enable, uint8_t dBFS = 6);
        void configSpkNS(uint8_t enable, uint8_t level = 12);
        void begin(void);
        void end(void);

        void setAMicBoost(uint8_t amicBoost);
        void setDMicBoost(uint8_t dmicBoost);
        void setMicGain(uint8_t gain);
        void setSpkGain(uint8_t gain);
        void muteMic(uint8_t mute);
        void muteSpk(uint8_t mute);
        void printInfo(void);

    private:
        audio_params_t* _audioParams = NULL;
        uint8_t _audioStarted = 0;
        RX_cfg_t _rxASPParams = {
            .aec_cfg = {
                .AEC_EN = 0,
                .EchoTailLen = 64,
                .CNGEnable = 1,
                .PPLevel = 6,
                },
            .agc_cfg = {
                .AGC_EN = 0,
                .AGCMode = CT_ALC,
                .ReferenceLvl = 6,
                .RefThreshold = 6,
                .AttackTime = 20,
                .ReleaseTime = 20,
                .Ratio = {50, 50, 50},
                .Threshold = {20, 30, 40},
                .KneeWidth = 0,
                .NoiseFloorAdaptEnable = 1,
                .RMSDetectorEnable = 0,
                },
            .ns_cfg = {
                .NS_EN = 0,
                .NSLevel = 15,
                .HPFEnable = 0,
                }
        };
        TX_cfg_t _txASPParams = {
            .agc_cfg = {
                .AGC_EN = 0,
                .AGCMode = CT_ALC,
                .ReferenceLvl = 6,
                .RefThreshold = 6,
                .AttackTime = 20,
                .ReleaseTime = 20,
                .Ratio = {50, 50, 50},
                .Threshold = {20, 30, 40},
                .KneeWidth = 0,
                .NoiseFloorAdaptEnable = 1,
                .RMSDetectorEnable = 0,
                },
            .ns_cfg = {
                .NS_EN = 0,
                .NSLevel = 15,
                .HPFEnable = 0,
                }
        };

        String micTypeArray[4] = {"USE_AUDIO_AMIC", "USE_AUDIO_LEFT_DMIC", "USE_AUDIO_RIGHT_DMIC", "USE_AUDIO_STEREO_DMIC"};
        String wordLengthArray[2] = {"16 bit", "24 bit"};
};

#endif
