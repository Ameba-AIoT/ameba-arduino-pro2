#ifndef __VIDEOSTREAMOVERLAY_H__
#define __VIDEOSTREAMOVERLAY_H__

#include "VideoStream.h"
#include "canvas.h"

#define OSD_COLOR_RED       ARGB(0xff,0xff,0x00,0x00)
#define OSD_COLOR_BLUE      ARGB(0xff,0x00,0x00,0xff)
#define OSD_COLOR_GREEN     ARGB(0xff,0x00,0xff,0x00)
#define OSD_COLOR_CYAN      ARGB(0xff,0x00,0xff,0xff)
#define OSD_COLOR_MAGENTA   ARGB(0xff,0xff,0x00,0xff)
#define OSD_COLOR_YELLOW    ARGB(0xff,0xff,0xff,0x00)
#define OSD_COLOR_WHITE     ARGB(0xff,0xff,0xff,0xff)
#define OSD_COLOR_BLACK     ARGB(0xff,0x00,0x00,0x00)
#define OSD_COLOR_GRAY      ARGB(0xff,0x7f,0x7f,0x7f)
#define OSD_COLOR_ORANGE    ARGB(0xff,0xf3,0x70,0x21)

class VideoStreamOverlay {
    public:
        void configVideo(int ch, VideoSetting& config);
        void configTextSize(int ch, int text_width, int text_height);
        void begin(void);
        void end(void);
        void endChannel(int ch);

        uint32_t color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xff);
        void drawPoint(int ch, int idx, int xmin, int ymin, int point_width, uint32_t color);
        void drawRect(int ch, int idx, int xmin, int ymin, int xmax, int ymax, int line_width, uint32_t color);
        void drawText(int ch, int idx, int xmin, int ymin, char *text_string, uint32_t color);
        void clearAll(int ch, int idx);
        void update(int ch, int idx);

    private:
        int ch_enable[3]={0};
        int character_width[3] = {16, 16, 16};     // Text character size in pixels
        int character_height[3] = {32, 32, 32};
        int ch_width[3] = {0};          // Video channel resolution
        int ch_height[3] = {0};
};

extern VideoStreamOverlay OSD;

#endif