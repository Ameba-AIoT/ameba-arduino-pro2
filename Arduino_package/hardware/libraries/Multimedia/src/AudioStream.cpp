#include <Arduino.h>
#include "AudioStream.h"
#include "VideoStream.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_audio.h"

#ifdef __cplusplus
}
#endif

AudioSetting::AudioSetting(uint8_t preset)
{
    switch (preset) {
        default:
        case 0: {    // Default quality analog mic
            _sampleRate = 8000;
            _audioParams.sample_rate = ASR_8KHZ;
            _audioParams.channel = 1;
            _audioParams.use_mic_type = USE_AUDIO_AMIC;
            break;
        }
        case 1: {    // Improved quality analog mic
            _sampleRate = 16000;
            _audioParams.sample_rate = ASR_16KHZ;
            _audioParams.channel = 1;
            _audioParams.use_mic_type = USE_AUDIO_AMIC;
            break;
        }
        case 2: {    // Default quality PDM digital mic
            _sampleRate = 8000;
            _audioParams.sample_rate = ASR_8KHZ;
            _audioParams.channel = 1;
            _audioParams.use_mic_type = USE_AUDIO_LEFT_DMIC;
            break;
        }
        case 3: {    // Improved quality PDM digital mic
            _sampleRate = 16000;
            _audioParams.sample_rate = ASR_16KHZ;
            _audioParams.channel = 1;
            _audioParams.use_mic_type = USE_AUDIO_LEFT_DMIC;
            break;
        }
    }
}

AudioSetting::AudioSetting(uint32_t sampleRate, uint8_t channelCount, uint8_t micType)
{
    _sampleRate = sampleRate;
    switch (sampleRate) {
        case 8000: {
            _audioParams.sample_rate = ASR_8KHZ;
            break;
        }
        case 16000: {
            _audioParams.sample_rate = ASR_16KHZ;
            break;
        }
        case 32000: {
            _audioParams.sample_rate = ASR_32KHZ;
            break;
        }
        case 44100: {
            _audioParams.sample_rate = ASR_44p1KHZ;
            break;
        }
        case 48000: {
            _audioParams.sample_rate = ASR_48KHZ;
            break;
        }
            // Disabled due to poor quality when encoded using AAC
            // case 88200: {
            //     _audioParams.sample_rate = ASR_88p2KHZ;
            //     break;
            // }
            // case 96000: {
            //     _audioParams.sample_rate = ASR_96KHZ;
            //     break;
            // }
        default: {
            printf("\r\n[ERROR] Invalid audio sample rate: %ld !\n", sampleRate);
            _sampleRate = 8000;
            _audioParams.sample_rate = ASR_8KHZ;
            break;
        }
    }

    switch (channelCount) {
        case 1: {
            _audioParams.channel = channelCount;
            break;
        }
        case 2:    // Stereo audio is disabled due to poor quality with DMIC
        default: {
            printf("\r\n[ERROR] Invalid audio channel count: %d !\n", channelCount);
            break;
        }
    }

    switch (micType) {
        case USE_AUDIO_AMIC:
        case USE_AUDIO_LEFT_DMIC:
        case USE_AUDIO_RIGHT_DMIC:
        case USE_AUDIO_STEREO_DMIC: {
            _audioParams.use_mic_type = micType;
            break;
        }
        default: {
            printf("\r\n[ERROR] Invalid audio mic type %d !\n", micType);
            break;
        }
    }
}

Audio::Audio(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&audio_module);
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] Audio init failed\n");
        return;
    }
}

Audio::~Audio(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] Audio deinit failed\n");
    }
}

void Audio::configAudio(AudioSetting &config)
{
    _audioParams = &(config._audioParams);
}

void Audio::configMicAEC(uint8_t enable, uint8_t level)
{
    if (level > 17) {
        printf("\r\n[INFO] Acoustic Echo Cancellation limited to maximum level of 17!\n");
        level = 17;
    }
    if (enable) {
        _rxASPParams.aec_cfg.AEC_EN = 1;
    } else {
        _rxASPParams.aec_cfg.AEC_EN = 0;
    }
    _rxASPParams.aec_cfg.PPLevel = level + 1;
}

void Audio::configMicAGC(uint8_t enable, uint8_t dBFS)
{
    if (dBFS > 30) {
        printf("\r\n[INFO] Automatic Gain Control reference level limited from 0 to -30dBFS!\n");
        dBFS = 30;
    }
    if (enable) {
        _rxASPParams.agc_cfg.AGC_EN = 1;
    } else {
        _rxASPParams.agc_cfg.AGC_EN = 0;
    }
    _rxASPParams.agc_cfg.ReferenceLvl = dBFS;
}

void Audio::configMicNS(uint8_t enable, uint8_t level)
{
    if (level > 12) {
        printf("\r\n[INFO] Noise suppression limited to maximum level of 12!\n");
        level = 12;
    }
    if (enable) {
        _rxASPParams.ns_cfg.NS_EN = 1;
    } else {
        _rxASPParams.ns_cfg.NS_EN = 0;
    }
    _rxASPParams.ns_cfg.NSLevel = level + 3;    // NS level valid values range from 3 to 15
}

void Audio::configSpkAGC(uint8_t enable, uint8_t dBFS)
{
    if (dBFS > 30) {
        printf("\r\n[ERROR] Automatic Gain Control reference level limited from 0 to -30dBFS!\n");
        dBFS = 30;
    }
    if (enable) {
        _txASPParams.agc_cfg.AGC_EN = 1;
    } else {
        _txASPParams.agc_cfg.AGC_EN = 0;
    }
    _txASPParams.agc_cfg.ReferenceLvl = dBFS;
}

void Audio::configSpkNS(uint8_t enable, uint8_t level)
{
    if (level > 12) {
        printf("\r\n[ERROR] Noise suppression limited to maximum level of 12!\n");
        level = 12;
    }
    if (enable) {
        _txASPParams.ns_cfg.NS_EN = 1;
    } else {
        _txASPParams.ns_cfg.NS_EN = 0;
    }
    _txASPParams.ns_cfg.NSLevel = level + 3;    // NS level valid values range from 3 to 15
}

void Audio::begin(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    if (_audioParams == NULL) {
        printf("\r\n[ERROR] Invalid AudioSetting configuration!\n");
        return;
    }

    mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_MESSAGE_LEVEL, 0);
    mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_PARAMS, (int)_audioParams);
    mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_RXASP_PARAM, (int)&_rxASPParams);
    mm_module_ctrl(_p_mmf_context, CMD_AUDIO_RUN_AEC, 1);
    mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_TXASP_PARAM, (int)&_txASPParams);
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 6);
    mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
    mm_module_ctrl(_p_mmf_context, CMD_AUDIO_APPLY, 0);
    _audioStarted = 1;
}

void Audio::end(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    _audioStarted = 0;
    mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_TRX, 0);
}

void Audio::setAMicBoost(uint8_t amicBoost)
{
    if (_audioParams == NULL) {
        printf("\r\n[ERROR] Configure AudioSetting first!\n");
        return;
    }
    switch (amicBoost) {
        case MIC_0DB:
        case MIC_20DB:
        case MIC_30DB:
        case MIC_40DB:
            _audioParams->mic_gain = (audio_mic_gain)amicBoost;
            break;
    }

    if (_audioStarted) {
        audio_ctx_t *ctx = (audio_ctx_t *)_p_mmf_context->priv;
        audio_mic_analog_gain(ctx->audio, 1, _audioParams->mic_gain);
        mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_PARAMS, (int)_audioParams);
    }
}

void Audio::setDMicBoost(uint8_t dmicBoost)
{
    if (_audioParams == NULL) {
        printf("\r\n[ERROR] Configure AudioSetting first!\n");
        return;
    }
    switch (dmicBoost) {
        case DMIC_BOOST_0DB:
        case DMIC_BOOST_12DB:
        case DMIC_BOOST_24DB:
        case DMIC_BOOST_36DB:
            _audioParams->dmic_l_gain = (audio_dmic_gain)dmicBoost;
            _audioParams->dmic_r_gain = (audio_dmic_gain)dmicBoost;
            break;
    }

    if (_audioStarted) {
        audio_ctx_t *ctx = (audio_ctx_t *)_p_mmf_context->priv;
        audio_l_dmic_gain(ctx->audio, _audioParams->dmic_l_gain);
        audio_r_dmic_gain(ctx->audio, _audioParams->dmic_r_gain);
        mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_PARAMS, (int)_audioParams);
    }
}

void Audio::setMicGain(uint8_t gain)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    if (gain > 100) {
        gain = 100;
    }
    mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_ADC_GAIN, (0x7F * (gain / 100.0)));
}

void Audio::setSpkGain(uint8_t gain)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    if (gain > 100) {
        gain = 100;
    }
    mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_DAC_GAIN, (0xAF * (gain / 100.0)));
}

void Audio::muteMic(uint8_t mute)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    if (mute) {
        mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_MIC_ENABLE, 0);
    } else {
        mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_MIC_ENABLE, 1);
    }
}

void Audio::muteSpk(uint8_t mute)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    if (mute) {
        mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_SPK_ENABLE, 0);
    } else {
        mm_module_ctrl(_p_mmf_context, CMD_AUDIO_SET_SPK_ENABLE, 1);
    }
}

void Audio::printInfo(void)
{
    uint8_t use_mic_type = _audioParams->use_mic_type;
    uint32_t sample_rate = _audioParams->sample_rate;
    uint32_t word_length = _audioParams->word_length;

    switch (sample_rate) {
        case ASR_8KHZ: {
            sample_rate = 8000;
            break;
        }
        case ASR_16KHZ: {
            sample_rate = 16000;
            break;
        }
        case ASR_32KHZ: {
            sample_rate = 32000;
            break;
        }
        case ASR_44p1KHZ: {
            sample_rate = 44100;
            break;
        }
        case ASR_48KHZ: {
            sample_rate = 48000;
            break;
        }
        case ASR_88p2KHZ: {
            sample_rate = 88200;
            break;
        }
        case ASR_96KHZ: {
            sample_rate = 96000;
            break;
        }
        default: {
            sample_rate = 0;
            break;
        }
    }

    printf("\r\n[INFO] Mic type: %s\n", micTypeArray[use_mic_type].c_str());
    printf("\r\n[INFO] Sample rate: %ld Hz\n", sample_rate);
    printf("\r\n[INFO] Word length: %s\n", wordLengthArray[word_length].c_str());
}
