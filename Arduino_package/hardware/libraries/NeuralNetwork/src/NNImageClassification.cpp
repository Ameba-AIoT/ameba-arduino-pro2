#include <Arduino.h>
#include "NNImageClassification.h"
#include "SD_Model.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"
#include "module_vipnn.h"
#include "model_classification.h"
#include "model_mobilenetv2.h"
#include "nn_utils/class_name.h"
#include "avcodec.h"
#include "vfs.h"
#include "nn_file_op.h"
#include <cJSON.h>

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
int NNImageClassification::_useMetadata;
char *NNImageClassification::model_meta_data = nullptr;

void (*NNImageClassification::IC_user_CB)(std::vector<ImageClassificationResult>);
std::vector<ImageClassificationResult> NNImageClassification::img_class_result_vector;

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
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] NNImageClassification init failed\n");
        return;
    }
    if ((roi_nn.img.width == 0) || (roi_nn.img.height == 0)) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] NNImageClassification video not configured\n");
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
            amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Models loaded using SD Card\n");
        } else {
            while (1) {
                amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Invalid NN task selected! Please check modelSelect() again\n");
                delay(5000);
            }
        }
    }

    if (ARDUINO_LOAD_MODEL == 0x02) {
        vfs_init(NULL);    // init filesystem
        vfs_user_register("sd", VFS_FATFS, VFS_INF_SD);
        switch (_imgclassmodel) {
            case SD_IMGCLASSIFICATION_MOBILENETV2: {
                vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&img_classification_mobilenetv2_from_sd);
                break;
            }
            case SD_IMGCLASSIFICATION: {
                vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&img_classification_from_sd);
                break;
            }
        }
    } else {
        switch (_imgclassmodel) {
            case DEFAULT_IMGCLASS_MOBILENETV2:
            case CUSTOMIZED_IMGCLASS_MOBILENETV2: {
                vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&mobilenetv2);
                break;
            }
            case DEFAULT_IMGCLASS:
            case CUSTOMIZED_IMGCLASS: {
                vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_MODEL, (int)&img_classification);
                break;
            }
        }
    }
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_IN_PARAMS, (int)&roi_nn);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_DISPPOST, (int)ICResultCallback);
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_RES_SIZE, sizeof(classification_res_t));
    vipnn_control(_p_mmf_context->priv, CMD_VIPNN_SET_RES_MAX_CNT, MAX_DETECT_OBJ_NUM);
    if (_useMetadata == 1) {
        int ret = vipnn_control(_p_mmf_context->priv, CMD_VIPNN_APPLY, 0);
        if (ret == 0) {
            model_meta_data = parseModelMetaData(_p_mmf_context);
        }
    } else {
        vipnn_control(_p_mmf_context->priv, CMD_VIPNN_APPLY, 0);
    }
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
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] NNImageClassification deinit failed\n");
    }
}

void NNImageClassification::setResultCallback(void (*ic_callback)(std::vector<ImageClassificationResult>))
{
    IC_user_CB = ic_callback;
}

uint16_t NNImageClassification::getResultCount(void)
{
    uint16_t ic_res_count = img_class_result_vector.size();
    // if (ac_res_count > 6) {
    //     ac_res_count = 6;
    // }
    return ic_res_count;
}

ImageClassificationResult NNImageClassification::getResult(uint16_t index)
{
    if (index >= img_class_result_vector.size()) {
        return ImageClassificationResult();
    }
    return img_class_result_vector[index];
}

std::vector<ImageClassificationResult> NNImageClassification::getResult(void)
{
    return img_class_result_vector;
}

void NNImageClassification::ICResultCallback(void *p, void *img_param)
{
    int i = 0;
    (void)img_param;

    if (p == NULL) {
        return;
    }

    vipnn_out_buf_t *out = (vipnn_out_buf_t *)p;
    classification_res_t *result = (classification_res_t *)&out->res[0];

    img_class_result_vector.clear();
    img_class_result_vector.resize((size_t)out->res_cnt);
    int obj_num = out->res_cnt;

    // amb_ard_printf(ARD_LOG_INF, "[INFO] object num = %d\r\n", obj_num);
    for (i = 0; i < obj_num; i++) {
        //     amb_ard_printf(ARD_LOG_INF, "[INFO] prob: %f, class: %d\n", (float)result[i].prob, (int)result[i].clsid);
        img_class_result_vector[i].result.clsid = (int)result[i].clsid;
        img_class_result_vector[i].result.prob = (float)result[i].prob;
    }

    if (IC_user_CB != NULL) {
        IC_user_CB(img_class_result_vector);
    }
}

char *NNImageClassification::parseModelMetaData(mm_context_t *vipnn_ctx)
{
    char *meta_data = NULL;
    char *nbname = NULL;
    if (ARDUINO_LOAD_MODEL == 0x02) {
        nbname = (char *)img_classification_mobilenetv2_from_sd.nb();
    } else {
        nbname = (char *)mobilenetv2.nb();
    }
    void *mf = nn_f_open(nbname, M_NORMAL);
    if (mf == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] open %s failed\n", nbname);
        return NULL;
    }
    nn_f_seek(mf, 0, SEEK_END);
    int fsize = nn_f_tell(mf);
    int metapos = 0;
    nn_f_seek(mf, MAX_META_DATA_SIZE, SEEK_END);

    // search 'RTKT' in the last MAX_META_DATA_SIZE bytes
    char meta_str[5] = {0};
    for (int i = 0; i < MAX_META_DATA_SIZE; i++) {
        int ret = nn_f_read(mf, meta_str, 4);
        if (ret <= 0) {
            break;
        }
        if (strcmp(meta_str, "RTKT") == 0) {
            metapos = nn_f_tell(mf);
            break;
        }
        nn_f_seek(mf, -3, SEEK_CUR);
    }

    if (metapos != 0) {
        int meta_size = fsize - metapos;
        meta_data = (char *)malloc(meta_size);
        if (meta_data) {
            nn_f_seek(mf, metapos, SEEK_SET);
            nn_f_read(mf, meta_data, meta_size);
            amb_ard_printf(ARD_LOG_INF, "[INFO] meta data:%s\r\n", meta_data);
        } else {
            amb_ard_printf(ARD_LOG_ERR, "[ERROR] malloc meta data fail.\r\n");
        }
    } else {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] meta data of model not found.\r\n");
    }
    nn_f_close(mf);
    return meta_data;
}

char *NNImageClassification::getClassNameFromMeta(char *meta_data, int class_id, int prob)
{
    if (!meta_data) {
        return NULL;
    }
    char *jsonstr = meta_data;
    cJSON *root = cJSON_Parse(jsonstr);
    if (!root) {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] Failed to parse json string\r\n");
        return NULL;
    }
    // parse json array data from class_id
    char *class_name = cJSON_GetArrayItem(root, class_id)->valuestring;
    amb_ard_printf(ARD_LOG_INF, "[INFO] score: %d, class id: %d, class name: %s \r\n", prob, class_id, class_name);
    cJSON_Delete(root);
    return class_name;
}

void NNImageClassification::useModelMetaData(int use_meta_data)
{
    if (use_meta_data == 1) {
        _useMetadata = 1;
    }
}

int ImageClassificationResult::classID(void)
{
    return ((int)(result.clsid));
}

int ImageClassificationResult::score(void)
{
    return ((int)((result.prob) * 100));
}
