#include <Arduino.h>
#include "NNObjectDetectionImage.h"
#include "SD_Model.h"
#include "3rdparty/stb_image.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "model_yolo.h"
#include "siso_drv.h"

extern int vipnn_control(void *p, int cmd, int arg);

#ifdef __cplusplus
}
#endif

mm_context_t *NNObjectDetectionImage::fileloader_ctx = NULL;
mm_context_t *NNObjectDetectionImage::filesaver_ctx = NULL;
mm_context_t *NNObjectDetectionImage::vipnn_ctx = NULL;
mm_siso_t *NNObjectDetectionImage::siso_fileloader_vipnn = NULL;
mm_siso_t *NNObjectDetectionImage::siso_vipnn_filesaver = NULL;
char NNObjectDetectionImage::coco_name[80][20] = {"person", "bicycle", "car", "motorbike", "aeroplane", "bus", "train", "truck", "boat", "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard", "tennis racket", "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair", "sofa", "pottedplant", "bed", "diningtable", "toilet", "tvmonitor", "laptop", "mouse", "remote", "keyboard", "cell phone", "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush"};
fileloader_params_t NNObjectDetectionImage::test_image_params = {.codec_id = AV_CODEC_ID_JPEG}; /* Fix me (AV_CODEC_ID_BMP or AV_CODEC_ID_JPEG) */
nn_data_param_t NNObjectDetectionImage::roi_tester = {
    .img = {
            .width = TEST_IMAGE_WIDTH,
            .height = TEST_IMAGE_HEIGHT,
            .roi = {
            .xmin = 0,
            .ymin = 0,
            .xmax = TEST_IMAGE_WIDTH,
            .ymax = TEST_IMAGE_HEIGHT,
        }},
    .codec_type = AV_CODEC_ID_RGB888
};

int NNObjectDetectionImage::saver_count = 0;

NNObjectDetectionImage::NNObjectDetectionImage(void)
{
}

NNObjectDetectionImage::~NNObjectDetectionImage(void)
{
}

void NNObjectDetectionImage::begin(char *filelist_name)
{
    // init virtual file system
    vfs_init(NULL);
    if (vfs_user_register("sd", VFS_FATFS, VFS_INF_SD) != 0) {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] fail to register SD vfs\r\n");
        return;
    }

    // get test file num on list
    amb_ard_printf(ARD_LOG_INF, "[INFO] Getting data set image number in list......\r\n");
    uint32_t t0 = xTaskGetTickCount();
    int file_count = get_line_num_in_sdfile((char *)filelist_name);
    if (file_count < 0) {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] fail to get line numbers\r\n");
        return;
    }
    amb_ard_printf(ARD_LOG_INF, "[INFO] The file has %d lines, it take %ld ms\r\n", file_count, xTaskGetTickCount() - t0);

    // file loader
    fileloader_ctx = mm_module_open(&fileloader_module);
    if (fileloader_ctx) {
        mm_module_ctrl(fileloader_ctx, CMD_FILELOADER_SET_PARAMS, (int)&test_image_params);
        mm_module_ctrl(fileloader_ctx, CMD_FILELOADER_SET_READ_MODE, (int)FILELIST_MODE);
        mm_module_ctrl(fileloader_ctx, CMD_FILELOADER_SET_FILELIST_NAME, (int)filelist_name);
        mm_module_ctrl(fileloader_ctx, CMD_FILELOADER_SET_FILE_NUM, (int)file_count);
        mm_module_ctrl(fileloader_ctx, CMD_FILELOADER_SET_DECODE_PROCESS, (int)ImageDecodeToRGB888planar_ConvertInPlace);
        mm_module_ctrl(fileloader_ctx, MM_CMD_SET_QUEUE_LEN, 1);    // set to 1 when using NN file tester
        mm_module_ctrl(fileloader_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(fileloader_ctx, CMD_FILELOADER_APPLY, 0);
    } else {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] fileloader open fail\n\r");
        goto mmf2_example_file_vipnn_tester_fail;
    }
    amb_ard_printf(ARD_LOG_INF, "[INFO] fileloader opened\n\r");

    // VIPNN
    vipnn_ctx = mm_module_open(&vipnn_module);
    if (vipnn_ctx) {
        if (_nntask != OBJECT_DETECTION) {
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
            switch (_yolomodel) {
                case SD_YOLOV3TINY: {
                    mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_MODEL, (int)&yolov3_tiny_from_sd);
                    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] YOLOV3 running...\n");
                    break;
                }
                case SD_YOLOV4TINY: {
                    mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_MODEL, (int)&yolov4_tiny_from_sd);
                    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] YOLOV4 running...\n");
                    break;
                }
                case SD_YOLOV7TINY: {
                    mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_MODEL, (int)&yolov7_tiny_from_sd);
                    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] YOLOV7 running...\n");
                    break;
                }
            }
        } else {
            switch (_yolomodel) {
                case DEFAULT_YOLOV3TINY:
                case CUSTOMIZED_YOLOV3TINY: {
                    mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_MODEL, (int)&yolov3_tiny);
                    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] YOLOV3 running...\n");
                    break;
                }
                case DEFAULT_YOLOV4TINY:
                case CUSTOMIZED_YOLOV4TINY: {
                    mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_MODEL, (int)&yolov4_tiny);
                    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] YOLOV4 running...\n");
                    break;
                }
                case DEFAULT_YOLOV7TINY:
                case CUSTOMIZED_YOLOV7TINY: {
                    mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_MODEL, (int)&yolov7_tiny);
                    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] YOLOV7 running...\n");
                    break;
                }
            }
        }

        mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_IN_PARAMS, (int)&roi_tester);
        mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_RES_SIZE, sizeof(objdetect_res_t));    // result size
        mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_RES_MAX_CNT, MAX_DETECT_OBJ_NUM);      // result max count
        mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_CONFIDENCE_THRES, (int)&nn_confidence_thresh);
        mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_NMS_THRES, (int)&nn_nms_thresh);
        mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_OUTPUT, 1);    // enable module output
        mm_module_ctrl(vipnn_ctx, MM_CMD_SET_QUEUE_LEN, 1);    // set to 1 when using NN file tester
        mm_module_ctrl(vipnn_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(vipnn_ctx, CMD_VIPNN_APPLY, 0);
    } else {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] VIPNN open fail\n\r");
        goto mmf2_example_file_vipnn_tester_fail;
    }
    amb_ard_printf(ARD_LOG_INF, "[INFO] VIPNN opened\n\r");

    // file saver
    filesaver_ctx = mm_module_open(&filesaver_module);
    if (filesaver_ctx) {
        mm_module_ctrl(filesaver_ctx, CMD_FILESAVER_SET_TYPE_HANDLER, (int)nn_save_handler_for_evaluate);
        mm_module_ctrl(filesaver_ctx, CMD_FILESAVER_APPLY, 0);
    } else {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] filesaver open fail\n\r");
        goto mmf2_example_file_vipnn_tester_fail;
    }
    amb_ard_printf(ARD_LOG_INF, "[INFO] filesaver opened\n\r");

    //--------------Link---------------------------

    if (siso_fileloader_vipnn == NULL) {
        siso_fileloader_vipnn = siso_create();
    }

    if (siso_fileloader_vipnn) {
        sisoRegIn(siso_fileloader_vipnn, fileloader_ctx);
        sisoRegOut(siso_fileloader_vipnn, vipnn_ctx);
        sisoSetStackSizeDefined((void *)siso_fileloader_vipnn, 128);
        sisoStart(siso_fileloader_vipnn);
    } else {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] siso_fileloader_vipnn open fail\n\r");
        goto mmf2_example_file_vipnn_tester_fail;
    }
    amb_ard_printf(ARD_LOG_INF, "[INFO] siso_fileloader_vipnn started\n\r");

    if (siso_vipnn_filesaver == NULL) {
        siso_vipnn_filesaver = siso_create();
    }

    if (siso_vipnn_filesaver) {
        sisoRegIn(siso_vipnn_filesaver, vipnn_ctx);
        sisoRegOut(siso_vipnn_filesaver, filesaver_ctx);
        sisoSetStackSizeDefined((void *)siso_vipnn_filesaver, 128);
        sisoStart(siso_vipnn_filesaver);
    } else {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] siso_vipnn_filesaver open fail\n\r");
        goto mmf2_example_file_vipnn_tester_fail;
    }
    amb_ard_printf(ARD_LOG_INF, "[INFO] siso_vipnn_filesaver started\n\r");

    return;

mmf2_example_file_vipnn_tester_fail:

    return;
}

void NNObjectDetectionImage::set_nn_roi(int w, int h)
{
    roi_tester.img.width = w;
    roi_tester.img.height = h;
    roi_tester.img.roi.xmax = w;
    roi_tester.img.roi.ymax = h;
    mm_module_ctrl(vipnn_ctx, CMD_VIPNN_SET_IN_PARAMS, (int)&roi_tester);
}

int NNObjectDetectionImage::ImageDecodeToRGB888planar_ConvertInPlace(void *pbuffer, void *pbuffer_size)
{
    uint8_t *pImageBuf = (uint8_t *)pbuffer;
    uint32_t *pImageSize = (uint32_t *)pbuffer_size;

    int w, h, c;
    int channels = 3;
    uint8_t *im_data = stbi_load_from_memory(pImageBuf, *pImageSize, &w, &h, &c, channels);
    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] image data size: w:%d, h:%d, c:%d\r\n", w, h, c);

    if (c != 1 && c != 3) {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] error: it's not an image file\r\n");
        return -1;
    }

    /* set nn roi according to image size */
    set_nn_roi(w, h);

    /* rgb packed to rgb planar */
    int data_size = w * h * c;
    uint8_t *rgb_planar_buf = (uint8_t *)malloc(data_size);
    for (int k = 0; k < c; k++) {
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                int dst_i = i + w * j + w * h * k;
                int src_i = k + c * i + c * w * j;
                rgb_planar_buf[dst_i] = im_data[src_i];
            }
        }
    }
    memcpy(pImageBuf, rgb_planar_buf, data_size);
    *pImageSize = (uint32_t)data_size;

    free(rgb_planar_buf);
    stbi_image_free(im_data);

    return 0;
}

char *NNObjectDetectionImage::nn_get_json_format(void *p, int frame_id, char *file_name)
{

    vipnn_out_buf_t *out = (vipnn_out_buf_t *)p;

    objdetect_res_t *od_res = (objdetect_res_t *)&out->res[0];

    /**** cJSON ****/
    cJSON_Hooks memoryHook;
    memoryHook.malloc_fn = malloc;
    memoryHook.free_fn = free;
    cJSON_InitHooks(&memoryHook);

    cJSON *nn_obj_JSObject = NULL;
    cJSON *nnJSArray = NULL, *nn_coor_JSArray = NULL;
    char *nn_json_string = NULL;

    nnJSArray = cJSON_CreateArray();

    int im_w = roi_tester.img.width;
    int im_h = roi_tester.img.height;

    amb_ard_printf(ARD_LOG_INF, "[INFO] object num = %d\r\n", out->res_cnt);
    if (out->res_cnt > 0) {
        for (int i = 0; i < out->res_cnt; i++) {

            int top_x = (int)(od_res[i].result[2] * im_w) < 0 ? 0 : (int)(od_res[i].result[2] * im_w);
            int top_y = (int)(od_res[i].result[3] * im_h) < 0 ? 0 : (int)(od_res[i].result[3] * im_h);
            int bottom_x = (int)(od_res[i].result[4] * im_w) > im_w ? im_w : (int)(od_res[i].result[4] * im_w);
            int bottom_y = (int)(od_res[i].result[5] * im_h) > im_h ? im_h : (int)(od_res[i].result[5] * im_h);
            int class_id = (int)(od_res[i].result[0]);
            float probability = od_res[i].result[1];

            int w = bottom_x - top_x;
            int h = bottom_y - top_y;

            cJSON_AddItemToArray(nnJSArray, nn_obj_JSObject = cJSON_CreateObject());

            cJSON_AddItemToObject(nn_obj_JSObject, "image_id", cJSON_CreateNumber(frame_id));
            cJSON_AddItemToObject(nn_obj_JSObject, "category_id", cJSON_CreateNumber(class_id));
            cJSON_AddItemToObject(nn_obj_JSObject, "bbox", nn_coor_JSArray = cJSON_CreateArray());
            cJSON_AddItemToObject(nn_obj_JSObject, "score", cJSON_CreateNumber(probability));
            cJSON_AddItemToArray(nn_coor_JSArray, cJSON_CreateNumber(top_x));
            cJSON_AddItemToArray(nn_coor_JSArray, cJSON_CreateNumber(top_y));
            cJSON_AddItemToArray(nn_coor_JSArray, cJSON_CreateNumber(w));
            cJSON_AddItemToArray(nn_coor_JSArray, cJSON_CreateNumber(h));
        }
    }

    nn_json_string = cJSON_Print(nnJSArray);
    cJSON_Delete(nnJSArray);


    return nn_json_string;
}

// char *str1 = "coco_val2017_pro2/image-0001.jpg";  --> return 1
// char *str2 = "coco_val2017_pro2/000000425131.jpg";  --> return 425131
int NNObjectDetectionImage::get_id_in_filename(char *str)
{
    int pos_slash = strrchr(str, '/') - str;
    int pos_dash = strrchr(str, '-') - str;
    int start_pos = pos_dash > pos_slash ? pos_dash + 1 : pos_slash + 1;

    int pos_dot = strrchr(str, '.') - str;
    int len = pos_dot - start_pos;

    char image_id[32];
    memset(&image_id[0], 0x00, sizeof(image_id));
    strncpy(image_id, &str[start_pos], len);

    amb_ard_printf(ARD_LOG_INF, "[INFO] image_id = %s\n", image_id);

    return (int)strtol(image_id, NULL, 10);
}

// char *str1 = "coco_val2017_pro2/000000425131.jpg";  --> return "coco_val2017_pro2/000000425131"
char *NNObjectDetectionImage::strip_filename_extention(char *filename)
{
    char *end = filename + strlen(filename);

    while (end > filename && *end != '.') {
        --end;
    }

    if (end > filename) {
        *end = '\0';
    }
    return filename;
}

void NNObjectDetectionImage::nn_save_handler_for_evaluate(char *file_name, uint32_t data_addr, uint32_t data_size)
{
    delay(100);
    vipnn_out_buf_t *out = (vipnn_out_buf_t *)data_addr;

    objdetect_res_t *od_res = (objdetect_res_t *)&out->res[0];

    char nn_fn[128];
    memset(&nn_fn[0], 0x00, sizeof(nn_fn));

    int image_id = get_id_in_filename(file_name);

    /* save yolo json result */
    snprintf(nn_fn, sizeof(nn_fn), "%s.json", strip_filename_extention(file_name));
    char *json_format_out = nn_get_json_format((void *)out, image_id, nn_fn);
    // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] json_format_out: %s\r\n", json_format_out);
    sd_save_file(nn_fn, json_format_out, strlen(json_format_out));

    // print object detected
    if (out->res_cnt > 0) {
        for (int i = 0; i < out->res_cnt; i++) {
            float probability = od_res[i].result[1];
            int class_id = (int)(od_res[i].result[0]);
            amb_ard_printf(ARD_LOG_INF, "[INFO] Image: %s, OBJECT IDENTIFIED: %s, with a probability of: %.3f\n\r", file_name, coco_name[class_id], probability);
        }
    }

    saver_count++;
}

int NNObjectDetectionImage::sd_save_file(char *file_name, char *data_buf, int data_buf_size)
{
    char fn[128];
    snprintf(fn, sizeof(fn), "%s%s", "sd:/", file_name);

    FILE *fp;
    fp = fopen(fn, "wb+");
    if (fp == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] fail to open file.\r\n");
        return -1;
    }
    fwrite(data_buf, data_buf_size, 1, fp);
    fclose(fp);

    amb_ard_printf(ARD_LOG_INF, "[INFO] save file to %s\r\n", fn);

    return 0;
}

int NNObjectDetectionImage::get_line_num_in_sdfile(char *file_name)
{
    char line[128];
    memset(line, 0, sizeof(line));
    char file_path[64];
    memset(file_path, 0, sizeof(file_path));
    snprintf(file_path, sizeof(file_path), "%s%s", "sd:/", file_name);
    int count = 0;
    if (access(file_path, F_OK) != 0) {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] file list not exists\r\n");
        return -1;
    }
    FILE *f = fopen(file_path, "r");
    while (fgets(line, sizeof(line), f)) {
        count++;
        // amb_ard_printf(ARD_LOG_INF, "[INFO][line %d] %s\r\n", count, line);
        memset(line, 0, sizeof(line));
    }
    fclose(f);

    return count;
}
