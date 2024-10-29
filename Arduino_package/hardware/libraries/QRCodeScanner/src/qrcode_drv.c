#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <QRCodeScanner_Libraries/zbar/qr_code_scanner.h>
#include "qrcode_drv.h"
#include "module_video.h"
#include "freertos_service.h"
#include "sensor.h"


#define QR_CODE_MAX_SCAN_COUNT 5

#define VIDEO_QCIF 0
#define VIDEO_CIF  1
#define VIDEO_WVGA 2
#define VIDEO_VGA  3
#define VIDEO_D1   4
#define VIDEO_HD   5
#define VIDEO_FHD  6
#define VIDEO_3M   7
#define VIDEO_5M   8
#define VIDEO_2K   9


#define V1_CHANNEL    0
#define V1_RESOLUTION VIDEO_VGA
#define V1_FPS        5
#define V1_GOP        5
#define V1_BPS        2 * 1024 * 1024
#define V1_RCMODE     2    // 1: CBR, 2: VBR

#define VIDEO_TYPE VIDEO_NV12

#if V1_RESOLUTION == VIDEO_VGA
#define V1_WIDTH  640
#define V1_HEIGHT 480
#elif V1_RESOLUTION == VIDEO_HD
#define V1_WIDTH  1280
#define V1_HEIGHT 720
#elif V1_RESOLUTION == VIDEO_FHD
#define V1_WIDTH  1920
#define V1_HEIGHT 1080
#endif

struct yuv_snapshot_context {
    uint8_t snap_flag;
    _sema snapshot_sema;
    uint32_t isp_len;
    uint32_t isp_addr;
    hal_video_adapter_t *v_adp;
};

static void yuv_output_cb(void *param1, void *param2, uint32_t arg)
{
    enc2out_t *enc2out = (enc2out_t *)param1;
    struct yuv_snapshot_context *yuv_ctx = (struct yuv_snapshot_context *)arg;

    if ((enc2out->codec & (CODEC_H264 | CODEC_HEVC | CODEC_JPEG)) != 0) {
        dcache_invalidate_by_addr((uint32_t *)enc2out->enc_addr, enc2out->enc_len);
    } else if ((enc2out->codec & (CODEC_NV12 | CODEC_RGB | CODEC_NV16)) != 0) {
        dcache_invalidate_by_addr((uint32_t *)enc2out->isp_addr, enc2out->enc_len);
        if (yuv_ctx->snap_flag) {
            yuv_ctx->isp_addr = (uint32_t)enc2out->isp_addr;
            rtw_up_sema(&yuv_ctx->snapshot_sema);
            yuv_ctx->snap_flag = 0;
            yuv_ctx->isp_len = enc2out->width * enc2out->height * 3 / 2;
            ;    // enc2out->enc_len;
        } else {
            video_ispbuf_release(enc2out->ch, (uint32_t)enc2out->isp_addr);
        }
    }
}

static video_params_t video_v1_params = {
    .stream_id = V1_CHANNEL,
    .type = VIDEO_TYPE,
    .resolution = V1_RESOLUTION,
    .width = V1_WIDTH,
    .height = V1_HEIGHT,
    .bps = V1_BPS,
    .fps = V1_FPS,
    .gop = V1_GOP,
    .rc_mode = V1_RCMODE,
    .direct_output = 1};

void yuv_snapshot_init(void *ctx)
{
    struct yuv_snapshot_context *yuv_ctx = (struct yuv_snapshot_context *)ctx;
    int iq_addr, sensor_addr;

    int voe_heap_size = video_buf_calc(1, V1_WIDTH, V1_HEIGHT, V1_BPS, 1,
                                       0, 0, 0, 0, 0,
                                       0, 0, 0, 0, 0,
                                       0, 0, 0);

    int sensor_id_value = 0;
    for (int i = 0; i < SENSOR_MAX; i++) {
        if (sen_id[i] == USE_SENSOR) {
            sensor_id_value = i;
            break;
        }
    }
    voe_get_sensor_info(sensor_id_value, &iq_addr, &sensor_addr);

    yuv_ctx->v_adp = video_init(iq_addr, sensor_addr);

    rtw_init_sema(&yuv_ctx->snapshot_sema, 0);
}

void yuv_snapshot_start(void *ctx)
{
    int ret = 0;
    ret = video_open(&video_v1_params, yuv_output_cb, (void *)ctx);
    if (ret < 0) {
        printf("ERR video_open\n");
        while (1) {
            vTaskDelay(100);
        }
    }
}

unsigned char *yuv_snapshot_get(void *ctx)
{
    struct yuv_snapshot_context *yuv_ctx = (struct yuv_snapshot_context *)ctx;
    yuv_ctx->snap_flag = 1;
    video_ctrl(video_v1_params.stream_id, VIDEO_NV12_OUTPUT, 1);
    if (rtw_down_timeout_sema(&yuv_ctx->snapshot_sema, 1000)) {
        return (unsigned char *)yuv_ctx->isp_addr;
    } else {
        printf("Can't get the buffer\r\n");
        return 0;
    }
}

void yuv_snapshot_release(void *ctx)
{
    struct yuv_snapshot_context *yuv_ctx = (struct yuv_snapshot_context *)ctx;
    video_ispbuf_release(video_v1_params.stream_id, (uint32_t)yuv_ctx->isp_addr);
}

void yuv_snapshot_close(void *ctx)
{
    video_close(video_v1_params.stream_id);
}


typedef struct _QR_CODE_SCANNER_CONFIG {
    unsigned int width;
    unsigned int height;
    int x_density;
    int y_density;
    unsigned int scan_count;
} QR_CODE_SCANNER_CONFIG;

QR_CODE_SCANNER_CONFIG qr_code_scanner_config_map[] = {
  //	{640,  480,  2, 2, 0},		// QR_CODE_480P_DENSITY_2
    {640, 480, 1, 1, 0}, // QR_CODE_480P_DENSITY_1
  //	{1280, 720,  2, 2, 0},		// QR_CODE_720P_DENSITY_2
  //	{1280, 720,  1, 1, 0},		// QR_CODE_720P_DENSITY_1
  //	{1920, 1080, 2, 2, 0},		// QR_CODE_1080P_DENSITY_2
  //	{1920, 1080, 1, 1, 0}		// QR_CODE_1080P_DENSITY_1
};

typedef enum {
    //	QR_CODE_480P_DENSITY_2,		// 480P, Density = 2
    //	QR_CODE_480P_DENSITY_1,		// 480P, Density = 1
    //	QR_CODE_720P_DENSITY_2,		// 720P, Density = 2
    //	QR_CODE_720P_DENSITY_1,		// 720P, Density = 1
    //	QR_CODE_1080P_DENSITY_2,	// 1080P, Density = 2
    QR_CODE_1080P_DENSITY_1,    // 1080P, Density = 1
    QR_CODE_CONFIG_MAX_INDEX
} qr_code_scanner_config_index;

char *result_string;
unsigned int result_length;
char *result_string1 = "";
unsigned int result_length1 = 0;

void copyresultstring(void)
{
    result_length1 = result_length;
    result_string1 = result_string;
}

void qr_code_scanner_thread(void *param)
{
    unsigned char *raw_data;
    unsigned int width;
    unsigned int height;
    int x_density;
    int y_density;
    qr_code_scanner_config_index index;
    qr_code_scanner_result qr_code_result;

    vTaskDelay(1000);

    struct yuv_snapshot_context *yuv_ctx = malloc(sizeof(struct yuv_snapshot_context));
    memset(yuv_ctx, 0, sizeof(struct yuv_snapshot_context));

    yuv_snapshot_init(yuv_ctx);

    while (1) {
        yuv_snapshot_start(yuv_ctx);
        video_ctrl(video_v1_params.stream_id, VIDEO_NV12_OUTPUT, 0);
        result_string = (char *)malloc(QR_CODE_MAX_RESULT_LENGTH);
        if (result_string == NULL) {
            printf("%s: result_string malloc fail \r\n", __FUNCTION__);
            break;
        }

        for (int i = 0; i < QR_CODE_CONFIG_MAX_INDEX; i++) {
            qr_code_scanner_config_map[i].scan_count = 0;
        }

        index = 0;
        while (1) {
            width = qr_code_scanner_config_map[index].width;
            height = qr_code_scanner_config_map[index].height;
            x_density = qr_code_scanner_config_map[index].x_density;
            y_density = qr_code_scanner_config_map[index].y_density;
            qr_code_result = QR_CODE_FAIL_UNSPECIFIC_ERROR;
            memset(result_string, 0, QR_CODE_MAX_RESULT_LENGTH);

            raw_data = yuv_snapshot_get(yuv_ctx);
            if (raw_data != NULL) {
                qr_code_result = qr_code_parsing(raw_data, width, height, x_density, y_density, result_string, &result_length);
                yuv_snapshot_release(yuv_ctx);
            }

            if (qr_code_result == QR_CODE_SUCCESS) {
                video_ctrl(video_v1_params.stream_id, VIDEO_NV12_OUTPUT, 0);
                vTaskDelay(1000);
                yuv_snapshot_close(yuv_ctx);
                break;
            } else if (qr_code_result == QR_CODE_FAIL_UNSPECIFIC_ERROR) {
                printf("%s: qr_code_scanner_config_map[%d] for QR_CODE_FAIL_UNSPECIFIC_ERROR \r\n", __FUNCTION__, index);
            } else if (qr_code_result == QR_CODE_FAIL_NO_FINDER_CENTER) {
                printf("%s: qr_code_scanner_config_map[%d] for QR_CODE_FAIL_NO_FINDER_CENTER \r\n", __FUNCTION__, index);
            } else if (qr_code_result == QR_CODE_FAIL_DECODE_ERROR) {
                printf("%s: qr_code_scanner_config_map[%d] for QR_CODE_FAIL_DECODE_ERROR \r\n", __FUNCTION__, index);
            }
        }

        if (qr_code_result == QR_CODE_SUCCESS) {
            printf("%s: qr code scan success \r\n", __FUNCTION__);
            printf("%s: buf = %s \r\n", __FUNCTION__, result_string);
            printf("%s: length = %u \r\n", __FUNCTION__, result_length);


        } else {
            printf("%s: qr code scan fail \r\n", __FUNCTION__);
        }

        copyresultstring();

        if (result_string) {
            free(result_string);
            result_string = NULL;
        }
    }
}

void qr_code_scanning(void)
{
    if (xTaskCreate(qr_code_scanner_thread, ((const char *)"qr_code_scanner_thread"), 1024, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS) {
        printf("\n\r%s xTaskCreate(example_qr_code_scanner_thread) failed", __FUNCTION__);
    }
}
