// brief:
//  - define audio/video/image basic or standard(eg: wav_header) types
//    used for entire project scale.
//
#ifndef HAL_OSD_AVDEF_H__
#define HAL_OSD_AVDEF_H__
#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif

#define rt_av_fourcc(a, b, c, d)	((u32)(a) | ((u32)(b) << 8) | ((u32)(c)<<16) | ((u32)((d) & 0x7f)<<24))

#define YUV_TO_RGB(y, u, v, r, g, b)	\
do { \
	r = (298*(y-16) + 409*(v-128) + 128) >> 8; \
	g = (298*(y-16) - 100*(u-128) - 208*(v-128) + 128) >> 8; \
	b = (298*(y-16) + 516*(u-128) + 128) >> 8; \
	r = (r > 255) ? 255 : ((r < 0) ? 0 : r); \
	g = (g > 255) ? 255 : ((g < 0) ? 0 : g); \
	b = (b > 255) ? 255 : ((b < 0) ? 0 : b); \
} while (0)

#define RGB_TO_YUV(r, g, b, y, u, v)	\
do { \
	y =  ((66*r + 129*g +  25*b + 128) >> 8) +  16; \
	u = ((-38*r -  74*g + 112*b + 128) >> 8) + 128; \
	v = ((112*r -  94*g -  18*b + 128) >> 8) + 128; \
	y = (y > 236) ? 236 : ((y < 16) ? 16 : y); \
	u = (u > 240) ? 240 : ((u < 16) ? 16 : u); \
	v = (v > 240) ? 240 : ((v < 16) ? 16 : v); \
} while (0)

typedef union {
	struct {
		unsigned char b;
		unsigned char g;
		unsigned char r;
	} rgb;
	unsigned int color;
} rt_color;

#define RT_COLOR(_r, _g, _b)	((_b)<<16|(_g)<<8|(_r))

#define RGB_Black		RT_COLOR(0,     0,   0)
#define RGB_White		RT_COLOR(255, 255, 255)
#define RGB_Red			RT_COLOR(255,   0,   0)
#define RGB_Lime		RT_COLOR(0,   255,   0)
#define RGB_Blue		RT_COLOR(0,     0, 255)
#define RGB_Yellow		RT_COLOR(255, 255,   0)
#define RGB_Cyan		RT_COLOR(0,   255, 255)
#define RGB_Magenta		RT_COLOR(255,   0, 255)
#define RGB_Silver		RT_COLOR(192, 192, 192)
#define RGB_Gray		RT_COLOR(128, 128, 128)
#define RGB_Maroon		RT_COLOR(128,   0,   0)
#define RGB_Olive		RT_COLOR(128, 128,   0)
#define RGB_Green		RT_COLOR(0,   128,   0)
#define RGB_Purple		RT_COLOR(128,   0, 128)
#define RGB_Teal		RT_COLOR(0,   128, 128)
#define RGB_Navy		RT_COLOR(0,     0, 128)
#define RGB_Brown		RT_COLOR(165,  42,  42)
#define RGB_Tomato		RT_COLOR(255,  99,  71)
#define RGB_Orange		RT_COLOR(255, 165,   0)
#define RGB_Gold		RT_COLOR(255, 215,   0)
#define RGB_Aqua		RT_COLOR(0,   255, 255)
#define RGB_Violet		RT_COLOR(238, 130, 238)
#define RGB_Orchid		RT_COLOR(218, 112, 214)
#define RGB_Pink		RT_COLOR(255, 192, 203)
#define RGB_Wheat		RT_COLOR(245, 222, 179)
#define RGB_Chocolate	RT_COLOR(210, 105,  30)
#define RGB_Lavender	RT_COLOR(230, 230, 250)
#define RGB_Ivory		RT_COLOR(255, 255, 240)
#define RGB_Azure		RT_COLOR(240, 255, 255)
#define RGB_Snow		RT_COLOR(255, 250, 250)

// ----------------------------------------------------------------------------
int rt_calc_frm_size(u8 fmt, int width, int height);

// resolution from predefined string, ex: vga -> (640, 480)
// if str is invalid string, then w & h will set to 0.
//
void rt_res_from_str(char *str, int *w, int *h);

// bit0: degree/90
// bit4: 0 Right & 1 Left
typedef enum {
	RT_ROTATE_0		= 0x00,
	RT_ROTATE_90R	= 0x01,
	RT_ROTATE_180R	= 0x02,
	RT_ROTATE_270R	= 0x03,
	RT_ROTATE_90L	= 0x11,
	RT_ROTATE_180L	= 0x12,
	RT_ROTATE_270L	= 0x13,
} rt_rotate_t;

// ref: http://soundfile.sapp.org/doc/WaveFormat/
// 44 Bytes
typedef struct {
	char	ChunkID[4];
	long	ChunkSize;
	char	Format[4];
	char	Subchunk1ID[4];
	long	Subchunk1Size;
	short	AudioFormat;
	short	NumChannels;
	long	SampleRate;
	long	ByteRate;
	short	BlockAlign;
	short	BitsPerSample;
	char	Subchunk2ID[4];
	long	Subchunk2Size;
} wav_header_st;

// AudioFormat field values
#define WAV_PCM			1
#define WAV_ALAW		6
#define WAV_ULAW		7

// av domain: use bit7
#define RT_AV_VIDEO		0x00
#define RT_AV_AUDIO		0x80

#define	rt_av_is_video(f)	(((f) & 0x80) == 0)
#define rt_av_is_audio(f)	(((f) & 0x80) == 1)

// NOTE: rt_av_fmt_t will sync with the following table.
//
// (ref: RTS3903_ISP_Software_Specification_V0.11.pdf)
// value    rts_camera_soc_drv.h
// -----------------------------------------------------
// 0x01     RTSCAM_SOC_FORMAT_TYPE_YUV420_SEMIPLANAR
// 0x02     RTSCAM_SOC_FORMAT_TYPE_YUV422_SEMIPLANAR
// 0x03
// 0x04     RTSCAM_SOC_FORMAT_TYPE_MJPG
//
// ref: rtsaudio.h
enum enum_rts_audio_type_id {
	RTS_AUDIO_TYPE_ID_MP3 = 1,
	RTS_AUDIO_TYPE_ID_ULAW,
	RTS_AUDIO_TYPE_ID_ALAW,
	RTS_AUDIO_TYPE_ID_PCM,
	RTS_AUDIO_TYPE_ID_G726,
	RTS_AUDIO_TYPE_ID_AMRNB,
	RTS_AUDIO_TYPE_ID_AAC,
	RTS_AUDIO_TYPE_ID_SBC,
	RTS_AUDIO_TYPE_ID_OPUS,
	RTS_AUDIO_TYPE_ID_WAV,		// our added.
};
//
typedef enum {
	RT_AV_NONE		= 0x00,
	RT_AV_DONTCARE	= 0xFF,
	//
	RT_V_YUV420_SEMIPLANAR	= 0x01,
	RT_V_YUV422_SEMIPLANAR	= 0x02,
	RT_V_BAYER	= 0x03,
	RT_V_MJPG	= 0x04,
	RT_V_H264	= 0x05,
	//
	RT_A_MP3	= RT_AV_AUDIO | RTS_AUDIO_TYPE_ID_MP3,
	RT_A_ULAW	= RT_AV_AUDIO | RTS_AUDIO_TYPE_ID_ULAW,
	RT_A_ALAW	= RT_AV_AUDIO | RTS_AUDIO_TYPE_ID_ALAW,
	RT_A_PCM	= RT_AV_AUDIO | RTS_AUDIO_TYPE_ID_PCM,
	RT_A_G726	= RT_AV_AUDIO | RTS_AUDIO_TYPE_ID_G726,
	RT_A_AMRNB	= RT_AV_AUDIO | RTS_AUDIO_TYPE_ID_AMRNB,
	RT_A_AAC	= RT_AV_AUDIO | RTS_AUDIO_TYPE_ID_AAC,
	RT_A_SBC	= RT_AV_AUDIO | RTS_AUDIO_TYPE_ID_SBC,
	RT_A_OPUS	= RT_AV_AUDIO | RTS_AUDIO_TYPE_ID_OPUS,
	RT_A_WAV	= RT_AV_AUDIO | RTS_AUDIO_TYPE_ID_WAV,
} rt_av_fmt_t;

// brief: get format from file path (file extension)
rt_av_fmt_t rt_av_fmt_from_path(char *abs_path);
char *rt_av_fmt_str(rt_av_fmt_t f);

// if not audio, then return 0
// else, return enum_rts_audio_type_id value.
#define rt_av_fmt_to_audio_type_id(f)	(((f) > 0x80) ? ((f) - 0x80) : 0)

#endif	// HAL_OSD_AVDEF_H__
