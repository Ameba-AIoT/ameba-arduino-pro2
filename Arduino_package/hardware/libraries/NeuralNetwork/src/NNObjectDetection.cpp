#include <Arduino.h>
#include "NNObjectDetection.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_vipnn.h"
#include "model_yolo.h"
#include "nn_utils/class_name.h"
#include "avcodec.h"

extern int vipnn_control(void *p, int cmd, int arg);

#ifdef __cplusplus
}
#endif

#undef min
#undef max
#include <vector>

#define LIMIT(x, lower, upper) if(x<lower) x=lower; else if(x>upper) x=upper;

std::vector<ObjectDetectionResult> NNObjectDetection::object_result_vector;
float NNObjectDetection::xscale;
float NNObjectDetection::xoffset;
float NNObjectDetection::yscale;
float NNObjectDetection::yoffset;
uint8_t NNObjectDetection::use_roi;

void (*NNObjectDetection::OD_user_CB)(std::vector<ObjectDetectionResult>);

NNObjectDetection::NNObjectDetection(void) {
}

NNObjectDetection::~NNObjectDetection(void) {
    end();
}

void NNObjectDetection::configVideo(VideoSetting& config) {
    roi_nn.img.width = config._w;
    roi_nn.img.height = config._h;
    roi_nn.img.rgb = 0;
    roi_nn.img.roi.xmin = 0;
    roi_nn.img.roi.xmax = config._w;
    roi_nn.img.roi.ymin = 0;
    roi_nn.img.roi.ymax = config._h;
    roi_nn.codec_type =  AV_CODEC_ID_RGB888;
}

void NNObjectDetection::configRegionOfInterest(int xmin, int xmax, int ymin, int ymax) {
    roi_nn.img.roi.xmin = xmin;
    roi_nn.img.roi.xmax = xmax;
    roi_nn.img.roi.ymin = ymin;
    roi_nn.img.roi.ymax = ymax;
}

void NNObjectDetection::configThreshold(float confidence_threshold, float nms_threshold) {
    od_confidence_thresh = confidence_threshold;
    od_nms_thresh = nms_threshold;
}

void NNObjectDetection::begin(void) {
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&vipnn_module);
    }
    if (_p_mmf_context == NULL) {
        printf("NNObjectDetection init failed\r\n");
        return;
    }
    if((roi_nn.img.width == 0) || (roi_nn.img.height == 0)) {
        printf("ERROR: NNFaceDetection video not configured\r\n");
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

    if (_nntask != OBJECT_DETECTION) {
        printf("Invalid NN task selected! Please check modelSelect() again.\r\n");
        while(1) {}
    }

    switch (_yolomodel) {
        case DEFAULT_YOLOV3TINY: 
        case CUSTOMIZED_YOLOV3TINY: {
            vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&yolov3_tiny);
            //printf("YOLOV3 running...\r\n");
            break;
        }
        case DEFAULT_YOLOV4TINY:
        case CUSTOMIZED_YOLOV4TINY: {
            vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&yolov4_tiny);
            //printf("YOLOV4 running...\r\n");
            break;
        }
        case DEFAULT_YOLOV7TINY :
        case CUSTOMIZED_YOLOV7TINY: {
            vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&yolov7_tiny);
            //printf("YOLOV7 running...\r\n");
            break;
        }
    }

    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_IN_PARAMS, (int)&roi_nn);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)ODResultCallback);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_CONFIDENCE_THRES, (int)&od_confidence_thresh);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_NMS_THRES, (int)&od_nms_thresh);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_RES_SIZE, sizeof(objdetect_res_t));	// result size
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_RES_MAX_CNT, MAX_DETECT_OBJ_NUM);		// result max count
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_APPLY, 0);
}

void NNObjectDetection::end(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)NULL);
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("NNObjectDetection deinit failed\r\n");
    }
}

void NNObjectDetection::setResultCallback(void (*od_callback)(std::vector<ObjectDetectionResult>)) {
    OD_user_CB = od_callback;
}

uint16_t NNObjectDetection::getResultCount(void) {
    uint16_t od_res_count = object_result_vector.size();
    if (od_res_count > 14) {
        od_res_count = 14;
    }
    return od_res_count;
}

ObjectDetectionResult NNObjectDetection::getResult(uint16_t index) {
    if (index >= object_result_vector.size()) {
        return ObjectDetectionResult();
    }
    return object_result_vector[index];
}

std::vector<ObjectDetectionResult> NNObjectDetection::getResult(void) {
    return object_result_vector;
}

void NNObjectDetection::ODResultCallback(void *p, void *img_param) {
    (void)img_param;
    if (p == NULL) {
        return;
    }
    vipnn_out_buf_t *out = (vipnn_out_buf_t *)p;
    objdetect_res_t* result = (objdetect_res_t*)&out->res[0];

    object_result_vector.clear();
    object_result_vector.resize((size_t)out->res_cnt);
    for (int i = 0; i < out->res_cnt; i++) {
        if (use_roi) {
            // Scale result box back to original frame size
            object_result_vector[i].result.classes = result[i].res.classes;
            object_result_vector[i].result.score = result[i].res.score;
            object_result_vector[i].result.top_x = result[i].res.top_x * xscale + xoffset;
            object_result_vector[i].result.bot_x = result[i].res.bot_x * xscale + xoffset;
            object_result_vector[i].result.top_y = result[i].res.top_y * yscale + yoffset;
            object_result_vector[i].result.bot_y = result[i].res.bot_y * yscale + yoffset;

            LIMIT(object_result_vector[i].result.top_x, 0.00, 1.00);
            LIMIT(object_result_vector[i].result.bot_x, 0.00, 1.00);
            LIMIT(object_result_vector[i].result.top_y, 0.00, 1.00);
            LIMIT(object_result_vector[i].result.bot_y, 0.00, 1.00);
        } else {
            memcpy(&(object_result_vector[i].result), &(result[i].res), sizeof(detobj_t));
        }
    }

    if (OD_user_CB != NULL) {
        OD_user_CB(object_result_vector);
    }
}

int ObjectDetectionResult::type(void) {
    return ((int)(result.classes));
}

const char* ObjectDetectionResult::name(void) {
    return coco_name_get_by_id((int)result.classes);
}

int ObjectDetectionResult::score(void) {
    return ((int)(result.score * 100));
}

float ObjectDetectionResult::xMin(void) {
    return result.top_x;
}

float ObjectDetectionResult::xMax(void) {
    return result.bot_x;
}

float ObjectDetectionResult::yMin(void) {
    return result.top_y;
}

float ObjectDetectionResult::yMax(void) {
    return result.bot_y;
}
