#include <Arduino.h>
#include "NNImageClassification.h"
#include "SD_Model.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_vipnn.h"
#include "model_classification.h"
#include "nn_utils/class_name.h"
#include "avcodec.h"
#include "vfs.h"

extern int vipnn_control(void *p, int cmd, int arg);

#ifdef __cplusplus
}
#endif

#define LIMIT(x, lower, upper) \
    if (x < lower) \
        x = lower; \
    else if (x > upper) \
        x = upper;

float NNImageClassification::xscale;
float NNImageClassification::xoffset;
float NNImageClassification::yscale;
float NNImageClassification::yoffset;
uint8_t NNImageClassification::use_roi;

int NNImageClassification::_classID;
float NNImageClassification::_prob;

void (*NNImageClassification::IC_user_CB)(void);

NNImageClassification::NNImageClassification(void)
{
}

NNImageClassification::~NNImageClassification(void)
{
    end();
}

// 1: RGB 0:BW
void NNImageClassification::configInputImageColor(int color)
{
    get_input_image_color(color);
}

void NNImageClassification::configVideo(VideoSetting &config)
{
    roi_nn.img.width = config._w;
    roi_nn.img.height = config._h;
    roi_nn.img.rgb = 0;
    roi_nn.img.roi.xmin = 0;
    roi_nn.img.roi.xmax = config._w;
    roi_nn.img.roi.ymin = 0;
    roi_nn.img.roi.ymax = config._h;
    roi_nn.codec_type = AV_CODEC_ID_RGB888;
}

void NNImageClassification::configRegionOfInterest(int xmin, int xmax, int ymin, int ymax)
{
    roi_nn.img.roi.xmin = xmin;
    roi_nn.img.roi.xmax = xmax;
    roi_nn.img.roi.ymin = ymin;
    roi_nn.img.roi.ymax = ymax;
}

void NNImageClassification::begin(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&vipnn_module);
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] NNImageClassification init failed\n");
        return;
    }
    if ((roi_nn.img.width == 0) || (roi_nn.img.height == 0)) {
        printf("\r\n[ERROR] NNImageClassification video not configured\n");
        return;
    }

    if ((roi_nn.img.roi.xmin != 0) || (roi_nn.img.roi.xmax != roi_nn.img.width) || (roi_nn.img.roi.ymin != 0) || (roi_nn.img.roi.ymax != roi_nn.img.height)) {
        use_roi = 1;
        LIMIT(roi_nn.img.roi.xmin, 0, roi_nn.img.width);
        LIMIT(roi_nn.img.roi.xmax, 0, roi_nn.img.width);
        LIMIT(roi_nn.img.roi.ymin, 0, roi_nn.img.height);
        LIMIT(roi_nn.img.roi.ymax, 0, roi_nn.img.height);

        xscale = (roi_nn.img.roi.xmax - roi_nn.img.roi.xmin) / (float)roi_nn.img.width;
        xoffset = roi_nn.img.roi.xmin / (float)roi_nn.img.width;
        yscale = (roi_nn.img.roi.ymax - roi_nn.img.roi.ymin) / (float)roi_nn.img.height;
        yoffset = roi_nn.img.roi.ymin / (float)roi_nn.img.height;
    } else {
        use_roi = 0;
    }

    if (_nntask != IMAGE_CLASSIFICATION) {
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
        vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&img_classification_from_sd);
    } else {
        vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&img_classification);
    }
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_IN_PARAMS, (int)&roi_nn);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)ICResultCallback);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_RES_SIZE, sizeof(classification_res_t));
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_RES_MAX_CNT, 64);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_APPLY, 0);
}

void NNImageClassification::end(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)NULL);
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] NNImageClassification deinit failed\n");
    }
}

void NNImageClassification::setResultCallback(void (*ic_callback)(void))
{
    IC_user_CB = ic_callback;
}

void NNImageClassification::ICResultCallback(void *p, void *img_param)
{
    (void)img_param;

    if (p == NULL) {
        return;
    }

    vipnn_out_buf_t *out = (vipnn_out_buf_t *)p;
    classification_res_t *result = (classification_res_t *)&out->res[0];

    float *output = (float *)malloc(out->res_cnt * sizeof(float));
    if (output == NULL) {
        printf("\r\n[ERROR] malloc fail\n");
        return;
    }

    // perform softmax() on res[i].prob
    float sum = 0;
    for (int i = 0; i < out->res_cnt; i++) {
        output[i] = exp(result[i].prob);
        sum += output[i];
    }
    for (int i = 0; i < out->res_cnt; i++) {
        output[i] /= sum;
    }

    // find max prob
    float max_prob = 0;
    int max_idx = 0;
    for (int i = 0; i < out->res_cnt; i++) {
        if (output[i] > max_prob) {
            max_prob = output[i];
            max_idx = i;
        }
    }
    free(output);

    _classID = result[max_idx].class_id;
    _prob = max_prob;
    // printf("id:%d prob:%f\r\n", result[max_idx].class_id, max_prob);

    if (IC_user_CB != NULL) {
        IC_user_CB();
    }
}

int NNImageClassification::classID(void)
{
    return _classID;
}

float NNImageClassification::score(void)
{
    return _prob;
}
