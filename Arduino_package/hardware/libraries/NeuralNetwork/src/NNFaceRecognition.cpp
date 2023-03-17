#include <Arduino.h>
#include "NNFaceRecognition.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_vipnn.h"
#include "module_facerecog.h"
#include "model_mobilefacenet.h"
#include "siso_drv.h"

extern int vipnn_control(void *p, int cmd, int arg);

#ifdef __cplusplus
}
#endif

#undef min
#undef max
#include <vector>

#define LIMIT(x, lower, upper) if(x<lower) x=lower; else if(x>upper) x=upper;

std::vector<FaceRecognitionResult> NNFaceRecognition::face_result_vector;
void (*NNFaceRecognition::FR_user_CB)(std::vector<FaceRecognitionResult>);

NNFaceRecognition::NNFaceRecognition(void) {

}

NNFaceRecognition::~NNFaceRecognition(void) {
    end();
}

void NNFaceRecognition::begin(void) {
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&vipnn_module);
    }
    if (_p_mmf_context == NULL) {
        printf("NNFaceRecognition init failed\r\n");
        return;
    }
    if (facerecog_ctx == NULL) {
        facerecog_ctx = mm_module_open(&facerecog_module);
    }
    if (facerecog_ctx == NULL) {
        printf("FaceRecognition module init failed\r\n");
        return;
    }
    if (facerecog_siso_ctx == NULL) {
        facerecog_siso_ctx = (void*)sisoCreate();
    }
    if (facerecog_siso_ctx == NULL) {
        printf("FaceRecognition SISO init failed\r\n");
        return;
    }

    // VIPNN MobileFaceNet configuration
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&mbfacenet_fwfs);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_CASCADE, 2);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_OUTPUT, 1);
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_DATAGROUP, MM_GROUP_END);
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 1);
    mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_APPLY, 0);

    // MMFv2 Face Recognition module configuration
    mm_module_ctrl(facerecog_ctx, CMD_FRC_SET_THRES100, 99);  // 99/100 = 0.99 --> set a value to get lowest FP rate
    mm_module_ctrl(facerecog_ctx, CMD_FRC_SET_OSD_DRAW, (int)FRResultCallback);

    // SISO link VIPNN to FaceRecognition module
    sisoRegIn(facerecog_siso_ctx, _p_mmf_context);
    sisoRegOut(facerecog_siso_ctx, facerecog_ctx);
    sisoStart(facerecog_siso_ctx);
}

void NNFaceRecognition::end(void) {
    if (facerecog_siso_ctx == NULL) {
        return;
    }
    sisoDestroy(facerecog_siso_ctx);
    facerecog_siso_ctx = NULL;

    if (facerecog_ctx == NULL) {
        return;
    }
    if (mm_module_close(facerecog_ctx) == NULL) {
        facerecog_ctx = NULL;
    } else {
        printf("NNFaceRecognition deinit failed\r\n");
    }

    if (_p_mmf_context == NULL) {
        return;
    }
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("NNFaceRecognition deinit failed\r\n");
    }
}

void NNFaceRecognition::setResultCallback(void (*fr_callback)(std::vector<FaceRecognitionResult>)) {
    FR_user_CB = fr_callback;
}

uint16_t NNFaceRecognition::getResultCount(void) {
    return face_result_vector.size();
}

FaceRecognitionResult NNFaceRecognition::getResult(uint16_t index) {
    if (index >= face_result_vector.size()) {
        return FaceRecognitionResult();
    }
    return face_result_vector[index];
}

std::vector<FaceRecognitionResult> NNFaceRecognition::getResult(void) {
    return face_result_vector;
}

void NNFaceRecognition::registerFace(String name) {
    registerFace(name.c_str());
}

void NNFaceRecognition::registerFace(const char* name) {
    if (!facerecog_ctx) {
        return;
    }
    mm_module_ctrl(facerecog_ctx, CMD_FRC_REGISTER_MODE, (int)name);
}

void NNFaceRecognition::exitRegisterMode(void) {
    if (!facerecog_ctx) {
        return;
    }
    mm_module_ctrl(facerecog_ctx, CMD_FRC_RECOGNITION_MODE, 0);
}

void NNFaceRecognition::resetRegisteredFace(void) {
    if (!facerecog_ctx) {
        return;
    }
    mm_module_ctrl(facerecog_ctx, CMD_FRC_RESET_FEATURES, 0);
}

void NNFaceRecognition::backupRegisteredFace(void) {
    if (!facerecog_ctx) {
        return;
    }
    mm_module_ctrl(facerecog_ctx, CMD_FRC_SAVE_FEATURES, 0);
}

void NNFaceRecognition::restoreRegisteredFace(void) {
    if (!facerecog_ctx) {
        return;
    }
    mm_module_ctrl(facerecog_ctx, CMD_FRC_LOAD_FEATURES, 0);
}

void NNFaceRecognition::setThreshold(uint8_t threshold) {
    if (!facerecog_ctx) {
        return;
    }

    if (threshold > 100) {
        threshold = 100;
    }
    // Face detection default is 0 = same face. Invert value to be same as object detection
    threshold = 100 - threshold;
    mm_module_ctrl(facerecog_ctx, CMD_FRC_SET_THRES100, threshold);
}

void NNFaceRecognition::FRResultCallback(void *p, void *img_param) {
    (void)img_param;
    if (p == NULL) {
        return;
    }

    frc_draw_t* result = (frc_draw_t*)p;

    face_result_vector.clear();
    face_result_vector.resize((size_t)result->obj_cnt);
    for (int i = 0; i < result->obj_cnt; i++) {
        memcpy(&(face_result_vector[i].result), result->img_param[i], sizeof(nn_data_param_t));
        strcpy(face_result_vector[i].result_name, result->obj_name[i]);
    }

    if (FR_user_CB != NULL) {
        FR_user_CB(face_result_vector);
    }
}

const char* FaceRecognitionResult::name(void) {
    return result_name;
}

float FaceRecognitionResult::xMin(void) {
    return ((float)result.img.roi.xmin/(float)result.img.width);
}

float FaceRecognitionResult::xMax(void) {
    return ((float)result.img.roi.xmax/(float)result.img.width);
}

float FaceRecognitionResult::yMin(void) {
    return ((float)result.img.roi.ymin/(float)result.img.height);
}

float FaceRecognitionResult::yMax(void) {
    return ((float)result.img.roi.ymax/(float)result.img.height);
}
