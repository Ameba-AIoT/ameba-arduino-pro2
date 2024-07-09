#include <Arduino.h>
#include "NNAudioClassification.h"
#include "SD_Model.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_audio.h"
#include "module_vipnn.h"
#include "model_yamnet.h"
#include "avcodec.h"
#include "vfs.h"

extern int vipnn_control(void *p, int cmd, int arg);

#ifdef __cplusplus
}
#endif

#undef min
#undef max
#include <vector>

void (*NNAudioClassification::AC_user_CB)(std::vector<AudioClassificationResult>);
std::vector<AudioClassificationResult> NNAudioClassification::audio_result_vector;

NNAudioClassification::NNAudioClassification(void)
{
}

NNAudioClassification::~NNAudioClassification(void)
{
    end();
}

void NNAudioClassification::configAudio(AudioSetting &config, uint16_t bitDepth)
{
    audio_nn_params.aud.bit_pre_sample = bitDepth;                // bit per sample
    audio_nn_params.aud.channel = config._audioParams.channel;    // channel count
    audio_nn_params.aud.sample_rate = config._audioParams.sample_rate;
    audio_nn_params.codec_type = AV_CODEC_ID_PCM_RAW;
}

void NNAudioClassification::begin(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&vipnn_module);
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] NNAudioClassification init failed\n");
        return;
    }

    if (_nntask != AUDIO_CLASSIFICATION) {
        if (ARDUINO_LOAD_MODEL == 0x02) {
            printf("\r\n[INFO] Models loaded using SD Card\n");
        } else {
            while (1) {
                printf("\r\n[ERROR] Invalid NN task selected! Please check modelSelect() again\n");
                delay(5000);
            }
        }
    }

    if (ARDUINO_LOAD_MODEL == 0x02) {
        vfs_init(NULL);    // init filesystem
        vfs_user_register("sd", VFS_FATFS, VFS_INF_SD);
        vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&yamnet_from_sd);
    } else {
        vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&yamnet);
    }
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_IN_PARAMS, (int)&audio_nn_params);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)ACResultCallback);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_APPLY, 0);
}

void NNAudioClassification::end(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] NNAudioClassification deinit failed\n");
    }
}

void NNAudioClassification::setResultCallback(void (*ac_callback)(std::vector<AudioClassificationResult>))
{
    AC_user_CB = ac_callback;
}

uint16_t NNAudioClassification::getResultCount(void)
{
    uint16_t ac_res_count = audio_result_vector.size();
    // if (ac_res_count > 6) {
    //     ac_res_count = 6;
    // }
    return ac_res_count;
}

AudioClassificationResult NNAudioClassification::getResult(uint16_t index)
{
    if (index >= audio_result_vector.size()) {
        return AudioClassificationResult();
    }
    return audio_result_vector[index];
}

std::vector<AudioClassificationResult> NNAudioClassification::getResult(void)
{
    return audio_result_vector;
}

void NNAudioClassification::ACResultCallback(void *p, void *img_param)
{
    int i = 0;
    (void)img_param;

    if (p == NULL) {
        return;
    }

    vipnn_out_buf_t *out = (vipnn_out_buf_t *)p;
    yamnet_res_t *result = (yamnet_res_t *)&out->res[0];

    audio_result_vector.clear();
    audio_result_vector.resize((size_t)out->res_cnt);
    for (i = 0; i < out->res_cnt; i++) {
        audio_result_vector[i].result.clsid = (int)result[i].clsid;
        audio_result_vector[i].result.prob = (float)result[i].prob;
    }

    if (AC_user_CB != NULL) {
        AC_user_CB(audio_result_vector);
    }
}

int AudioClassificationResult::classID(void)
{
    return ((int)(result.clsid));
}

int AudioClassificationResult::score(void)
{
    return ((int)((result.prob) * 100));
}
