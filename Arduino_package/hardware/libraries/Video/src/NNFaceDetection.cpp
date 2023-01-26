#include <Arduino.h>
#include "NNFaceDetection.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_vipnn.h"
#include "model_scrfd.h"
//#include "roi_delta_qp/roi_delta_qp.h"

extern int vipnn_control(void *p, int cmd, int arg);

#ifdef __cplusplus
}
#endif

#undef min
#undef max
#include <vector>

#define LIMIT(x, lower, upper) if(x<lower) x=lower; else if(x>upper) x=upper;

std::vector<FaceDetectionResult> NNFaceDetection::face_result_vector;
void (*NNFaceDetection::FD_user_CB)(std::vector<FaceDetectionResult>);

NNFaceDetection::NNFaceDetection(void) {
}

NNFaceDetection::~NNFaceDetection(void) {
    end();
}

void NNFaceDetection::configVideo(VideoSetting& config) {
    roi_nn.img.width = config._w;
    roi_nn.img.height = config._h;
    roi_nn.img.rgb = 0;
    roi_nn.img.roi.xmin = 0;
    roi_nn.img.roi.xmax = config._w;
    roi_nn.img.roi.ymin = 0;
    roi_nn.img.roi.ymax = config._h;
}

void NNFaceDetection::configFaceRecogCascadedMode(uint8_t enable) {
    cascaded_mode = enable;
}

void NNFaceDetection::begin(void) {
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&vipnn_module);
    }
    if (_p_mmf_context == NULL) {
        printf("NNFaceDetection init failed\r\n");
        return;
    }
    if((roi_nn.img.width == 0) || (roi_nn.img.height == 0)) {
        printf("NNFaceDetection video not configured\r\n");
        return;
    }

    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&scrfd_fwfs);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_IN_PARAMS, (int)&roi_nn);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)FDResultCallback);
    if (cascaded_mode) {
        mm_module_ctrl(_p_mmf_context, CMD_VIPNN_SET_OUTPUT, 1);
        mm_module_ctrl(_p_mmf_context, MM_CMD_SET_DATAGROUP, MM_GROUP_START);
        mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 1);
        mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
    }
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_APPLY, 0);
}

void NNFaceDetection::end(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)NULL);
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("NNFaceDetection deinit failed\r\n");
    }
}

void NNFaceDetection::setResultCallback(void (*fd_callback)(std::vector<FaceDetectionResult>)) {
    FD_user_CB = fd_callback;
}

uint16_t NNFaceDetection::getResultCount(void) {
    return face_result_vector.size();
}

FaceDetectionResult NNFaceDetection::getResult(uint16_t index) {
    if (index >= face_result_vector.size()) {
        return FaceDetectionResult();
    }
    return face_result_vector[index];
}

std::vector<FaceDetectionResult> NNFaceDetection::getResult(void) {
    return face_result_vector;
}

void NNFaceDetection::FDResultCallback(void *p, void *img_param) {
    (void)img_param;
    if (p == NULL) {
        return;
    }

    facedetect_res_t* result = (facedetect_res_t*)p;

    face_result_vector.clear();
    face_result_vector.resize((size_t)result->obj_num);
    for (int i = 0; i < result->obj_num; i++) {
        memcpy(&(face_result_vector[i].result), &(result->res[i]), sizeof(detobj_t));
        memcpy(&(face_result_vector[i].landmark), &(result->landmark[i]), sizeof(landmark_t));
    }

    if (FD_user_CB != NULL) {
        FD_user_CB(face_result_vector);
    }
}

const char* FaceDetectionResult::name(void) {
    return ("Face");
}

int FaceDetectionResult::score(void) {
    return ((int)(result.score * 100));
}

float FaceDetectionResult::xMin(void) {
    return result.top_x;
}

float FaceDetectionResult::xMax(void) {
    return result.bot_x;
}

float FaceDetectionResult::yMin(void) {
    return result.top_y;
}

float FaceDetectionResult::yMax(void) {
    return result.bot_y;
}

float FaceDetectionResult::xFeature(uint8_t index) {
    if (index >= 5) {
        return 0;
    }
    return landmark.pos[index].x;
}

float FaceDetectionResult::yFeature(uint8_t index) {
    if (index >= 5) {
        return 0;
    }
    return landmark.pos[index].y;
}