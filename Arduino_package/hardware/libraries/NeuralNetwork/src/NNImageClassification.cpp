#include <Arduino.h>
#include "NNImageClassification.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_vipnn.h"
#include "model_classification.h"
#include "nn_utils/class_name.h"
#include "avcodec.h"

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

// void (*NNImageClassification::IC_user_CB)(std::vector<ImageClassificationResult>);

NNImageClassification::NNImageClassification(void)
{
}

NNImageClassification::~NNImageClassification(void)
{
    end();
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

    // if (_nntask != IMAGE_CLASSIFICATION && _nntask != DEFAULT_IMGCLASS && _nntask != CUSTOMIZED_IMGCLASS) {
    // printf("\r\n[ERROR] Invalid NN task selected! Please check modelSelect() again\n");
    // while(1) {}
    // }

    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&img_classification);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_IN_PARAMS, (int)&roi_nn);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)ICResultCallback);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_RES_SIZE, sizeof(classification_res_t));
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_RES_MAX_CNT, 1024);
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

void NNImageClassification::ICResultCallback(void *p)
{
    if (p == NULL) {
        return;
    }
    vipnn_out_buf_t *out = (vipnn_out_buf_t *)p;
    classification_res_t *res = (classification_res_t *)&out->res[0];

    for (int i = 0; i < out->res_cnt; i++) {
        printf("%s: class %d, prob: %f\r\n", __func__, res[i].class_id, res[i].prob);
    }
}
