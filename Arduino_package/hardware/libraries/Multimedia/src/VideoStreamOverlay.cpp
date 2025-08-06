#include <Arduino.h>
#include "VideoStreamOverlay.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "osd_render.h"

#ifdef __cplusplus
}
#endif

VideoStreamOverlay OSD;

void VideoStreamOverlay::configVideo(int ch, VideoSetting &config)
{
    ch_enable[ch] = 1;
    ch_width[ch] = config._w;
    ch_height[ch] = config._h;

    // printf("\r\n[INFO] ch_enable %d  %d  %d\n", ch_enable[0], ch_enable[1], ch_enable[2]);
    // printf("\r\n[INFO] character_width %d  %d  %d\n", character_width[0], character_width[1], character_width[2]);
    // printf("\r\n[INFO] character_height %d  %d  %d\n", character_height[0], character_height[1], character_height[2]);
    // printf("\r\n[INFO] ch_width %d  %d  %d\n", ch_width[0], ch_width[1], ch_width[2]);
    // printf("\r\n[INFO] ch_height %d  %d  %d\n", ch_height[0], ch_height[1], ch_height[2]);
}

void VideoStreamOverlay::configTextSize(int ch, int text_width, int text_height)
{
    character_width[ch] = text_width;
    character_height[ch] = text_height;
}

void VideoStreamOverlay::createBitmap(int ch, int idx)
{
    canvas_create_bitmap(ch, idx, RTS_OSD2_BLK_FMT_RGBA2222);
}

void VideoStreamOverlay::begin(void)
{
    osd_render_dev_init(ch_enable, character_width, character_height);
    osd_render_task_start(ch_enable, ch_width, ch_height);
}

void VideoStreamOverlay::end(void)
{
    osd_render_dev_deinit_all();
    osd_render_task_stop();
}

void VideoStreamOverlay::endChannel(int ch)
{
    ch_enable[ch] = 0;
    osd_render_dev_deinit(ch);

    for (int i = 0; i < OSD_OBJ_MAX_CH; i++) {
        if (ch_enable[ch]) {
            break;
        }
        end();    // Check for active channels, if no channels active, stop task
    }
}

int VideoStreamOverlay::getTextHeight(int ch)
{
    return character_height[ch];
}

int VideoStreamOverlay::getTextWidth(int ch)
{
    return character_width[ch];
}

uint32_t VideoStreamOverlay::color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    return (ARGB(alpha, red, green, blue));
}

void VideoStreamOverlay::drawLine(int ch, int xmin, int ymin, int xmax, int ymax, int line_width, uint32_t color, int idx)
{
    canvas_set_line(ch, idx, xmin, ymin, xmax, ymax, line_width, color);
}

void VideoStreamOverlay::drawPoint(int ch, int xmin, int ymin, int point_width, uint32_t color, int idx)
{
    canvas_set_point(ch, idx, xmin, ymin, point_width, color);
}

void VideoStreamOverlay::drawRect(int ch, int xmin, int ymin, int xmax, int ymax, int line_width, uint32_t color, int idx)
{
    canvas_set_rect(ch, idx, xmin, ymin, xmax, ymax, line_width, color);
}

void VideoStreamOverlay::drawText(int ch, int xmin, int ymin, const char *text_string, uint32_t color, int idx)
{
    canvas_set_text(ch, idx, xmin, ymin, (char *)text_string, color);
}

void VideoStreamOverlay::drawPlus(int ch, int x_center, int y_center, int L, int line_width, uint32_t color, int idx)
{
    int h_xmin = x_center - L;
    int h_ymin = y_center;
    int h_xmax = x_center + L;
    int h_ymax = y_center;
    drawLine(ch, h_xmin, h_ymin, h_xmax, h_ymax, line_width, color, idx);    // horizontal line

    int v_xmin = x_center;
    int v_ymin = y_center - L;
    int v_xmax = x_center;
    int v_ymax = y_center + L;
    drawLine(ch, v_xmin, v_ymin, v_xmax, v_ymax, line_width, color, idx);    // vertical line
}

void VideoStreamOverlay::update(int ch, int idx)
{
    canvas_update(ch, idx, 1);
}

void VideoStreamOverlay::update(int ch, int idx, int ready_to_update)
{
    canvas_update(ch, idx, ready_to_update);
}

// OSD draw images/logos
const int ach_id[RTS_MAX_STM_COUNT] = {0, 1, 2, 3, 4};

void VideoStreamOverlay::initOSDBitmapPos(osd_pict_st *bmp_info, int chn_id, uint32_t start_x, uint32_t start_y, uint32_t width, uint32_t height)
{
    bmp_info->chn_id = chn_id;
    bmp_info->osd2.start_x = start_x;
    bmp_info->osd2.start_y = start_y;
    bmp_info->osd2.end_x = bmp_info->osd2.start_x + width;
    bmp_info->osd2.end_y = bmp_info->osd2.start_y + height;
}

void VideoStreamOverlay::initOSDBitmapBlk(osd_pict_st *bmp_info, int blk_idx, enum rts_osd2_blk_fmt blk_fmt, uint32_t clr_1bpp)
{
    bmp_info->osd2.blk_idx = blk_idx;
    bmp_info->osd2.blk_fmt = blk_fmt;
    bmp_info->osd2.color_1bpp = clr_1bpp;    // 0xAABBGGRR
}

void VideoStreamOverlay::initOSDBitmapBuf(osd_pict_st *bmp_info, uint8_t *buf, uint32_t buf_len)
{
    bmp_info->osd2.buf = buf;
    bmp_info->osd2.len = buf_len;
}

void VideoStreamOverlay::begin(VideoSetting &config, int ch, int idx)
{
    rts_osd_set_frame_size(ch, config._w, config._h);
    rts_osd_init(ch, 28, 56, (int)8.0f * 3600);
}

int VideoStreamOverlay::resizeWidth(int pict_width, int pict_scaling_up_factor, int pict_scaling_down_factor)
{
    int resize_w = pict_width * pict_scaling_up_factor / pict_scaling_down_factor;

    return resize_w;
}

int VideoStreamOverlay::resizeHeight(int pict_height, int pict_scaling_up_factor, int pict_scaling_down_factor)
{
    int resize_h = pict_height * pict_scaling_up_factor / pict_scaling_down_factor;

    return resize_h;
}

unsigned int VideoStreamOverlay::heapsizeCal(int resize_width, int resize_height, rts_osd2_blk_fmt image_format)
{
    int resize_s = rts_osd_pict_heapsize_cal(resize_width, resize_height, image_format);

    return resize_s;
}

void VideoStreamOverlay::drawImage(int ch, unsigned char *osd_array[], osd_pict_st pict_osd_buffer, unsigned int heapsize, void *pict_name, int pict_width, int pict_height, rts_osd2_blk_fmt pict_format, int resize_width, int resize_height, int start_x, int start_y, int pict_blk_idx)
{
    if (osd_array[ch]) {
        free(osd_array[ch]);
    }

    printf("[osd] Heap available:%d\r\n", xPortGetFreeHeapSize());
    resize_width = (resize_width + 1) & (~1);      // 2 alignment
    resize_height = (resize_height + 1) & (~1);    // 2 alignment
    osd_array[ch] = (unsigned char *)malloc(heapsize);
    rts_osd_pict_resize(osd_array[ch], pict_name, pict_width, pict_height, resize_width, resize_height, pict_format);

    initOSDBitmapPos(&pict_osd_buffer, ch, start_x, start_y, resize_width, resize_height);
    initOSDBitmapBlk(&pict_osd_buffer, pict_blk_idx, pict_format, 0);
    initOSDBitmapBuf(&pict_osd_buffer, osd_array[ch], heapsize);

    rts_osd_set_info(rts_osd2_type_pict_extn, &pict_osd_buffer);
    printf("[osd] Heap available:%d\r\n", xPortGetFreeHeapSize());
}

void VideoStreamOverlay::displayImage(int ch)
{
    if (xTaskCreate(rts_osd_task, "OSD", 10 * 1024, (void *)(ach_id + ch), tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        printf("\n\r%s xTaskCreate failed", __FUNCTION__);
    }
}
