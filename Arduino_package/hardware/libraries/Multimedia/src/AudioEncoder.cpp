#include <Arduino.h>
#include "AudioStream.h"
#include "VideoStream.h"
#include "AudioEncoder.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_audio.h"
#include "module_aac.h"
#include "module_g711.h"

#ifdef __cplusplus
}
#endif

AAC::AAC(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&aac_module);
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] AAC init failed\n");
        return;
    }
}

AAC::~AAC(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] AAC deinit failed\n");
    }
}

void AAC::configAudio(AudioSetting& config)
{
    audio_params_t* _audioParams = &(config._audioParams);

    _aacParams.sample_rate = config._sampleRate;
    // switch (_audioParams->word_length) {
    //     default:
    //     case WL_16BIT: {
    //         _aacParams.bit_length = FAAC_INPUT_16BIT;
    //         break;
    //     }
    //     case WL_24BIT: {
    //         _aacParams.bit_length = FAAC_INPUT_24BIT;
    //         break;
    //     }
    // }
    _aacParams.channel = _audioParams->channel;
}

void AAC::begin(void)
{
    mm_module_ctrl(_p_mmf_context, CMD_AAC_SET_PARAMS, (int)&_aacParams);
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 6);
    mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
    mm_module_ctrl(_p_mmf_context, CMD_AAC_INIT_MEM_POOL, 0);
    mm_module_ctrl(_p_mmf_context, CMD_AAC_APPLY, 0);
}

void AAC::end(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    mm_module_ctrl(_p_mmf_context, CMD_AAC_RESET, 0);
}

G711E::G711E(void)
{
}

G711E::~G711E(void)
{
    end();
}

void G711E::configAudio(AudioSetting& config)
{
    audio_params_t* _audioParams = &(config._audioParams);

    if (config._sampleRate > 16000) {
        printf("\r\n[ERROR] Audio sample rate incompatible with G711 codec!\n");
    }
    if (_audioParams->word_length != WL_16BIT) {
        printf("\r\n[ERROR] Audio word length incompatible with G711 codec!\n");
    }
}

void G711E::configCodec(Audio_Codec_T codec)
{
    switch (codec) {
        default:
        case CODEC_G711_PCMU: {
            _g711Params.codec_id = AV_CODEC_ID_PCMU;
            break;
        }
        case CODEC_G711_PCMA: {
            _g711Params.codec_id = AV_CODEC_ID_PCMA;
            break;
        }
    }
}

void G711E::begin(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&g711_module);
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] G711E init failed\n");
        return;
    }
    mm_module_ctrl(_p_mmf_context, CMD_G711_SET_PARAMS, (int)&_g711Params);
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 6);
    mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
    mm_module_ctrl(_p_mmf_context, CMD_G711_APPLY, 0);
}

void G711E::end(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] G711E deinit failed\n");
    }
}
