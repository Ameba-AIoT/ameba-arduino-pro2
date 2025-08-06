#ifndef __VIDEOSTREAMOVERLAY_H__
#define __VIDEOSTREAMOVERLAY_H__

#include "VideoStream.h"
#include "canvas.h"

// DEFAULT is previously defined in wiring_constants.h
#ifdef DEFAULT
#undef DEFAULT
#endif

enum rts_osd2_blk_type {
    rts_osd2_type_none = 0,
    rts_osd2_type_date,
    rts_osd2_type_time,
    rts_osd2_type_pict,
    rts_osd2_type_text,
    rts_osd2_type_rect,
    rts_osd2_type_pict_extn,
    rts_osd2_type_text_extn,
    rts_osd2_type_rect_extn,
    rts_osd2_type_temp
};

enum rts_osd_err_code {
    rts_osd_err_success = 0,
    rts_osd_err_fail,
    rts_osd_err_wrong_bitmap_range,
    rts_osd_err_wrong_date,
    rts_osd_err_wrong_time,
    rts_osd_err_malloc_fail,
    rts_osd_err_block_not_available,
    rts_osd_err_stream_not_available,
    rts_osd_err_parameter_null,
    rts_osd_err_reserved
};

#include "hal_osd_util.h"
#include "osd_custom.h"
#include "osd_pict_custom.h"

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int rts_osd_pict_heapsize_cal(int width, int height, enum rts_osd2_blk_fmt osd_format);
extern enum rts_osd_err_code rts_osd_set_frame_size(int chn_id, int frame_w, int frame_h);
extern enum rts_osd_err_code rts_osd_init(int chn_id, int char_resize_w, int char_resize_h, int timezone_s);
extern enum rts_osd_err_code rts_osd_pict_resize(void *pd, void *pixels, int widthSource, int heightSource, int width, int height, enum rts_osd2_blk_fmt osd_format);
extern enum rts_osd_err_code rts_osd_set_info(int osd_type, void *osd_info);
extern void rts_osd_task(void *arg);
extern void osd_remove_info(int chn_id, int block_idx);

#ifdef __cplusplus
}
#endif

#define OSD_COLOR_RED     ARGB(0xff, 0xff, 0x00, 0x00)
#define OSD_COLOR_BLUE    ARGB(0xff, 0x00, 0x00, 0xff)
#define OSD_COLOR_GREEN   ARGB(0xff, 0x00, 0xff, 0x00)
#define OSD_COLOR_CYAN    ARGB(0xff, 0x00, 0xff, 0xff)
#define OSD_COLOR_MAGENTA ARGB(0xff, 0xff, 0x00, 0xff)
#define OSD_COLOR_YELLOW  ARGB(0xff, 0xff, 0xff, 0x00)
#define OSD_COLOR_WHITE   ARGB(0xff, 0xff, 0xff, 0xff)
#define OSD_COLOR_BLACK   ARGB(0xff, 0x00, 0x00, 0x00)
#define OSD_COLOR_GRAY    ARGB(0xff, 0x7f, 0x7f, 0x7f)
#define OSD_COLOR_ORANGE  ARGB(0xff, 0xf3, 0x70, 0x21)

// Each channel supports 6 OSD layers
#define OSDLAYER0 0
#define OSDLAYER1 1
#define OSDLAYER2 2
#define OSDLAYER3 3
#define OSDLAYER4 4
#define OSDLAYER5 5

// OSD only supports Ch 0,1,2
#define MAX_OSD_CH_COUNT 3

class VideoStreamOverlay {
public:
    void configVideo(int ch, VideoSetting &config);
    void configTextSize(int ch, int text_width, int text_height);
    void createBitmap(int ch, int idx = 0);
    void begin(void);
    void end(void);
    void endChannel(int ch);
    int getTextHeight(int ch);
    int getTextWidth(int ch);

    uint32_t color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xff);
    void drawLine(int ch, int xmin, int ymin, int xmax, int ymax, int line_width, uint32_t color, int idx = 0);
    void drawPoint(int ch, int xmin, int ymin, int point_width, uint32_t color, int idx = 0);
    void drawRect(int ch, int xmin, int ymin, int xmax, int ymax, int line_width, uint32_t color, int idx = 0);
    void drawText(int ch, int xmin, int ymin, const char *text_string, uint32_t color, int idx = 0);
    void drawPlus(int ch, int x_center, int y_center, int L, int line_width, uint32_t color, int idx = 0);

    void update(int ch, int idx = 0);
    void update(int ch, int idx, int ready_to_update);

    // OSD draw images/logos
    void begin(VideoSetting &config, int ch, int idx = 0);
    void initOSDBitmapPos(osd_pict_st *bmp_info, int chn_id, uint32_t start_x, uint32_t start_y, uint32_t width, uint32_t height);
    void initOSDBitmapBlk(osd_pict_st *bmp_info, int blk_idx, enum rts_osd2_blk_fmt blk_fmt, uint32_t clr_1bpp);
    void initOSDBitmapBuf(osd_pict_st *bmp_info, uint8_t *buf, uint32_t buf_len);
    int resizeWidth(int pict_width, int pict_scaling_up_factor, int pict_scaling_down_factor);
    int resizeHeight(int pict_height, int pict_scaling_up_factor, int pict_scaling_down_factor);
    unsigned int heapsizeCal(int resize_width, int resize_height, rts_osd2_blk_fmt image_format);
    void drawImage(int ch, unsigned char *osd_array[], osd_pict_st pict_osd_buffer, unsigned int heapsize, void *pict_name, int pict_width, int pict_height, rts_osd2_blk_fmt pict_format, int resize_width, int resize_height, int start_x, int start_y, int pict_blk_idx);
    void displayImage(int ch);

private:
    int ch_enable[3] = {0};
    int character_width[3] = {16, 16, 16};    // Text character size in pixels
    int character_height[3] = {32, 32, 32};
    int ch_width[3] = {0};    // Video channel resolution
    int ch_height[3] = {0};
};

extern VideoStreamOverlay OSD;

#endif
