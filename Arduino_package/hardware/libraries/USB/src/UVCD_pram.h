#ifndef __UVCD_PRAM_H__
#define __UVCD_PRAM_H__

#define VIDEO_FHD_WIDTH_UVCD  1920
#define VIDEO_FHD_HEIGHT_UVCD 1080

#define MAX_W VIDEO_FHD_WIDTH_UVCD
#define MAX_H VIDEO_FHD_HEIGHT_UVCD

// Configure for supported format of uvcd
// If only want to support one configuration, you can only enable one of them
#define UVCD_YUY2 1
#define UVCD_NV12 1
#define UVCD_MJPG 1
#define UVCD_H264 1
#define UVCD_H265 1

#endif
