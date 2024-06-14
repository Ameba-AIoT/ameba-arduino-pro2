#include <Arduino.h>
#include "AudioStream.h"
#include "VideoStream.h"
#include "AudioDecoder.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_audio.h"
#include "module_aad.h"
#include "module_g711.h"

#ifdef __cplusplus
}
#endif

AAD::AAD(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&aad_module);
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] AAD init failed\n");
        return;
    }
}

AAD::~AAD(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] AAD deinit failed\n");
    }
}

void AAD::configAudio(AudioSetting& config)
{
    audio_params_t* _audioParams = &(config._audioParams);

    _aadParams.sample_rate = config._sampleRate;
    _aadParams.channel = _audioParams->channel;
}

void AAD::begin(void)
{
    mm_module_ctrl(_p_mmf_context, CMD_AAD_SET_PARAMS, (int)&_aadParams);
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 6);
    mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
    mm_module_ctrl(_p_mmf_context, CMD_AAD_APPLY, 0);
}

void AAD::end(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    mm_module_ctrl(_p_mmf_context, CMD_AAD_RESET, 0);
}

G711D::G711D(void)
{
}

G711D::~G711D(void)
{
    end();
}

void G711D::configAudio(AudioSetting& config)
{
    audio_params_t* _audioParams = &(config._audioParams);

    if (config._sampleRate > 16000) {
        printf("\r\n[ERROR] Audio sample rate incompatible with G711 codec!\n");
    }
    if (_audioParams->word_length != WL_16BIT) {
        printf("\r\n[ERROR] Audio word length incompatible with G711 codec!\n");
    }
}

void G711D::configCodec(Audio_Codec_T codec)
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

void G711D::begin(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&g711_module);
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] G711D init failed\n");
        return;
    }
    mm_module_ctrl(_p_mmf_context, CMD_G711_SET_PARAMS, (int)&_g711Params);
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 6);
    mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
    mm_module_ctrl(_p_mmf_context, CMD_G711_APPLY, 0);
}

void G711D::end(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] G711D deinit failed\n");
    }
}
