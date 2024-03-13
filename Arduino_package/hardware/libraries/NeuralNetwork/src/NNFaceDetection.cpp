#include <Arduino.h>
#include "NNFaceDetection.h"
#include "SD_Model.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_vipnn.h"
#include "model_scrfd.h"
#include "avcodec.h"
#include "vfs.h"
// #include "roi_delta_qp/roi_delta_qp.h"

extern int vipnn_control(void *p, int cmd, int arg);

#ifdef __cplusplus
}
#endif


#undef min
#undef max
#include <vector>

#define LIMIT(x, lower, upper) \
    if (x < lower) \
        x = lower; \
    else if (x > upper) \
        x = upper;

std::vector<FaceDetectionResult> NNFaceDetection::face_result_vector;
void (*NNFaceDetection::FD_user_CB)(std::vector<FaceDetectionResult>);

NNFaceDetection::NNFaceDetection(void)
{
}

NNFaceDetection::~NNFaceDetection(void)
{
    end();
}

void NNFaceDetection::configVideo(VideoSetting &config)
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

void NNFaceDetection::begin(void)
{
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mm_module_open(&vipnn_module);
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] NNFaceDetection init failed\n");
        return;
    }
    if ((roi_nn.img.width == 0) || (roi_nn.img.height == 0)) {
        printf("\r\n[ERROR] NNFaceDetection video not configured\n");
        return;
    }

    if (_nntask != FACE_DETECTION) {
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
        vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&scrfd_fwfs_from_sd);
    } else {
        vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&scrfd_fwfs);
    }
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_IN_PARAMS, (int)&roi_nn);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_RES_SIZE, sizeof(facedetect_res_t));
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_RES_MAX_CNT, MAX_DETECT_OBJ_NUM);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)FDResultCallback);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_APPLY, 0);
}

void NNFaceDetection::end(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)NULL);
    if (mm_module_close(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] NNFaceDetection deinit failed\n");
    }
}

void NNFaceDetection::setResultCallback(void (*fd_callback)(std::vector<FaceDetectionResult>))
{
    FD_user_CB = fd_callback;
}

uint16_t NNFaceDetection::getResultCount(void)
{
    uint16_t facedet_res_count = face_result_vector.size();

    if (facedet_res_count > MAX_FACE_DET) {
        facedet_res_count = MAX_FACE_DET;
    }

    return facedet_res_count;
}

FaceDetectionResult NNFaceDetection::getResult(uint16_t index)
{
    if (index >= face_result_vector.size()) {
        return FaceDetectionResult();
    }
    return face_result_vector[index];
}

std::vector<FaceDetectionResult> NNFaceDetection::getResult(void)
{
    return face_result_vector;
}

void NNFaceDetection::FDResultCallback(void *p, void *img_param)
{
    (void)img_param;
    if (p == NULL) {
        return;
    }
    vipnn_out_buf_t *out = (vipnn_out_buf_t *)p;
    facedetect_res_t *result = (facedetect_res_t *)&out->res[0];

    face_result_vector.clear();
    face_result_vector.resize((size_t)out->res_cnt);
    for (int i = 0; i < out->res_cnt; i++) {
        memcpy(&(face_result_vector[i].result), &(result[i].res), sizeof(detobj_t));
        memcpy(&(face_result_vector[i].landmark), &(result[i].landmark), sizeof(landmark_t));
    }

    if (FD_user_CB != NULL) {
        FD_user_CB(face_result_vector);
    }
}

const char *FaceDetectionResult::name(void)
{
    return ("Face");
}

int FaceDetectionResult::score(void)
{
    return ((int)(result.score * 100));
}

float FaceDetectionResult::xMin(void)
{
    return result.top_x;
}

float FaceDetectionResult::xMax(void)
{
    return result.bot_x;
}

float FaceDetectionResult::yMin(void)
{
    return result.top_y;
}

float FaceDetectionResult::yMax(void)
{
    return result.bot_y;
}

float FaceDetectionResult::xFeature(uint8_t index)
{
    if (index >= 5) {
        return 0;
    }
    return landmark.pos[index].x;
}

float FaceDetectionResult::yFeature(uint8_t index)
{
    if (index >= 5) {
        return 0;
    }
    return landmark.pos[index].y;
}
