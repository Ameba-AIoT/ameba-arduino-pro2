#include <Arduino.h>
#include "NNFaceDetectionRecognition.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_vipnn.h"
#include "model_scrfd.h"
#include "model_mobilefacenet.h"
#include "siso_drv.h"
#include "avcodec.h"

extern int vipnn_control(void *p, int cmd, int arg);

#ifdef __cplusplus
}
#endif

#undef min
#undef max
#include <vector>

#define LIMIT(x, lower, upper) if(x<lower) x=lower; else if(x>upper) x=upper;

std::vector<FaceRecognitionResult> NNFaceDetectionRecognition::face_result_vector;
void (*NNFaceDetectionRecognition::FR_user_CB)(std::vector<FaceRecognitionResult>);

NNFaceDetectionRecognition::NNFaceDetectionRecognition(void) {

}

NNFaceDetectionRecognition::~NNFaceDetectionRecognition(void) {
    end();
}

void NNFaceDetectionRecognition::configVideo(VideoSetting& config) {
    roi_nn.img.width = config._w;
    roi_nn.img.height = config._h;
    roi_nn.img.rgb = 0;
    roi_nn.img.roi.xmin = 0;
    roi_nn.img.roi.xmax = config._w;
    roi_nn.img.roi.ymin = 0;
    roi_nn.img.roi.ymax = config._h;
    roi_nn.codec_type =  AV_CODEC_ID_RGB888;
    fr_param.codec_type = AV_CODEC_ID_NN_RAW;
}

void NNFaceDetectionRecognition::begin(void) {
    // Face Detection
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

    if (_nntask != FACE_RECOGNITION) {
        printf("Invalid NN task selected! Please check modelSelect() again.\r\n");
        while(1);
    }
    
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&scrfd_fwfs);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_IN_PARAMS, (int)&roi_nn);
    mm_module_ctrl(_p_mmf_context, CMD_VIPNN_SET_OUTPUT, 1);
    mm_module_ctrl(_p_mmf_context, CMD_VIPNN_SET_RES_SIZE, sizeof(facedetect_res_t));	// result size
    mm_module_ctrl(_p_mmf_context, CMD_VIPNN_SET_RES_MAX_CNT, MAX_DETECT_OBJ_NUM);		// result max count
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_DATAGROUP, MM_GROUP_START);
    mm_module_ctrl(_p_mmf_context, MM_CMD_SET_QUEUE_LEN, 1);
    mm_module_ctrl(_p_mmf_context, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_APPLY, 0);

    // Face Recognition
    if (mbfacenet_ctx == NULL) {
        mbfacenet_ctx = mm_module_open(&vipnn_module);
    }
    if (mbfacenet_ctx == NULL) {
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

    if (mbfacenet_siso_ctx == NULL) {
        mbfacenet_siso_ctx = (void*)sisoCreate();
    }
    if (mbfacenet_siso_ctx == NULL) {
        printf("VIPNN MobileFaceNet SISO init failed\r\n");
        return;
    }

    // VIPNN MobileFaceNet configuration
    vipnn_control(mbfacenet_ctx->priv, CMD_VIPNN_SET_MODEL, (int)&mbfacenet_fwfs);
    vipnn_control(mbfacenet_ctx->priv, CMD_VIPNN_SET_CASCADE, 2);
    vipnn_control(mbfacenet_ctx->priv, CMD_VIPNN_SET_OUTPUT, 1);
    mm_module_ctrl(mbfacenet_ctx, CMD_VIPNN_SET_IN_PARAMS, (int)&fr_param);
    mm_module_ctrl(mbfacenet_ctx, CMD_VIPNN_SET_RES_SIZE, sizeof(face_feature_res_t));	// result size
	mm_module_ctrl(mbfacenet_ctx, CMD_VIPNN_SET_RES_MAX_CNT, MAX_DETECT_OBJ_NUM);		// result max count

    mm_module_ctrl(mbfacenet_ctx, MM_CMD_SET_DATAGROUP, MM_GROUP_END);
    mm_module_ctrl(mbfacenet_ctx, MM_CMD_SET_QUEUE_LEN, 1);
    mm_module_ctrl(mbfacenet_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
    vipnn_control(mbfacenet_ctx->priv, CMD_VIPNN_APPLY, 0);

    // MMFv2 Face Recognition module configuration
    mm_module_ctrl(facerecog_ctx, CMD_FRC_SET_THRES100, 99);  // 99/100 = 0.99 --> set a value to get lowest FP rate
    mm_module_ctrl(facerecog_ctx, CMD_FRC_SET_OSD_DRAW, (int)FRResultCallback);

    // SISO link VIPNN MobileFaceNet to FaceRecognition module
    sisoRegIn(facerecog_siso_ctx, mbfacenet_ctx);
    sisoRegOut(facerecog_siso_ctx, facerecog_ctx);
    sisoStart(facerecog_siso_ctx);

    // SISO link FaceDetection to VIPNN MobileFaceNet
    sisoRegIn(mbfacenet_siso_ctx, _p_mmf_context);
    sisoRegOut(mbfacenet_siso_ctx, mbfacenet_ctx);
    sisoStart(mbfacenet_siso_ctx);
}

void NNFaceDetectionRecognition::end(void) {
    if (facerecog_siso_ctx == NULL) {
        return;
    }
    sisoDestroy(facerecog_siso_ctx);
    facerecog_siso_ctx = NULL;

    if (facerecog_ctx == NULL) {
        return;
    }

    if (mbfacenet_siso_ctx == NULL) {
        return;
    }
    sisoDestroy(mbfacenet_siso_ctx);
    mbfacenet_siso_ctx = NULL;

    if (mbfacenet_siso_ctx == NULL) {
        return;
    }

    if (mm_module_close(facerecog_ctx) == NULL) {
        facerecog_ctx = NULL;
    } else {
        printf("NNFaceRecognition deinit failed\r\n");
    }

    if (mm_module_close(mbfacenet_ctx) == NULL) {
        mbfacenet_ctx = NULL;
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

void NNFaceDetectionRecognition::setResultCallback(void (*fr_callback)(std::vector<FaceRecognitionResult>)) {
    FR_user_CB = fr_callback;
}

uint16_t NNFaceDetectionRecognition::getResultCount(void) {
    uint16_t facerecog_res_count = face_result_vector.size();
    if (facerecog_res_count > 14) {
        facerecog_res_count = 14;
    }
    return facerecog_res_count;
}

FaceRecognitionResult NNFaceDetectionRecognition::getResult(uint16_t index) {
    if (index >= face_result_vector.size()) {
        return FaceRecognitionResult();
    }
    return face_result_vector[index];
}

std::vector<FaceRecognitionResult> NNFaceDetectionRecognition::getResult(void) {
    return face_result_vector;
}

void NNFaceDetectionRecognition::registerFace(String name) {
    registerFace(name.c_str());
}

void NNFaceDetectionRecognition::registerFace(const char* name) {
    if (!facerecog_ctx) {
        return;
    }
    mm_module_ctrl(facerecog_ctx, CMD_FRC_REGISTER_MODE, (int)name);
}

void NNFaceDetectionRecognition::exitRegisterMode(void) {
    if (!facerecog_ctx) {
        return;
    }
    mm_module_ctrl(facerecog_ctx, CMD_FRC_RECOGNITION_MODE, 0);
}

void NNFaceDetectionRecognition::resetRegisteredFace(void) {
    if (!facerecog_ctx) {
        return;
    }
    mm_module_ctrl(facerecog_ctx, CMD_FRC_RESET_FEATURES, 0);
}

void NNFaceDetectionRecognition::backupRegisteredFace(void) {
    if (!facerecog_ctx) {
        return;
    }
    mm_module_ctrl(facerecog_ctx, CMD_FRC_SAVE_FEATURES, 0);
}

void NNFaceDetectionRecognition::restoreRegisteredFace(void) {
    if (!facerecog_ctx) {
        return;
    }
    mm_module_ctrl(facerecog_ctx, CMD_FRC_LOAD_FEATURES, 0);
}

void NNFaceDetectionRecognition::setThreshold(uint8_t threshold) {
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

void NNFaceDetectionRecognition::FRResultCallback(void *p, void *img_param) {
    (void)img_param;
    if (p == NULL) {
        return;
    }

    frc_draw_t* result = (frc_draw_t*)p;

    face_result_vector.clear();
    face_result_vector.resize((size_t)result->obj_cnt);
    for (int i = 0; i < result->obj_cnt; i++) {
        memcpy(&(face_result_vector[i].result), &result->bbox[i], sizeof(frc_bbox_t));
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
    return ((float)result.xmin);
}

float FaceRecognitionResult::xMax(void) {
    return ((float)result.xmax);
}

float FaceRecognitionResult::yMin(void) {
    return ((float)result.ymin);
}

float FaceRecognitionResult::yMax(void) {
   return ((float)result.ymax);
}
