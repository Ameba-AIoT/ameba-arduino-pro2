#ifndef HAL_OSD_UTIL_H
#define HAL_OSD_UTIL_H

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif

#include "hal_osd_avdef.h"
#include "hal_osd_code.h"

#ifndef RTS_L_BYTE
#define RTS_L_BYTE(a)       ((a) & 0xff)
#endif
#ifndef RTS_H_BYTE
#define RTS_H_BYTE(a)       (((a) >> 8) & 0xff)
#endif
#ifndef RTS_L_WORD
#define RTS_L_WORD(a)       ((a) & 0xffff)
#endif
#ifndef RTS_H_WORD
#define RTS_H_WORD(a)       (((a) >> 16) & 0xffff)
#endif


#ifndef RTS_MAKE_WORD
#define RTS_MAKE_WORD(a, b) ((a) | ((b) << 8))
#endif
#ifndef RTS_MAKE_DWORD
#define RTS_MAKE_DWORD(a, b, c, d)  \
    ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#endif

#ifndef RTS_MAKE_WORD_BE
#define RTS_MAKE_WORD_BE(a, b)  ((b) | ((a) << 8))
#endif
#ifndef RTS_MAKE_DWORD_BE
#define RTS_MAKE_DWORD_BE(a, b, c, d)   \
    ((d) | ((c) << 8) | ((b) << 16) | ((a) << 24))
#endif

#ifndef RTS_SPLIT_WORD
#define RTS_SPLIT_WORD(array, value)    \
	do {\
		array[0] = (value) & 0xff;\
		array[1] = ((value) >> 8) & 0xff;\
	} while (0)
#endif
#ifndef RTS_SPLIT_DWORD
#define RTS_SPLIT_DWORD(array, value)   \
	do {\
		array[0] = (value) & 0xff;\
		array[1] = ((value) >> 8) & 0xff;\
		array[2] = ((value) >> 16) & 0xff;\
		array[3] = ((value) >> 24) & 0xff;\
	} while (0)
#endif

#ifndef RTS_SET_BIT
#define RTS_SET_BIT(v, i)   ((v) | (1<<(i)))
#endif
#ifndef RTS_CLEAR_BIT
#define RTS_CLEAR_BIT(v, i) ((v) & (~(1<<(i))))
#endif
#ifndef RTS_CHECK_BIT
#define RTS_CHECK_BIT(v, i) (((v)>>(i)) & 1)
#endif

#ifndef RTS_DIV_ROUND_UP
#define RTS_DIV_ROUND_UP(n, d)	(((n) + (d) - 1) / (d))
#endif

#ifndef RTS_DIV_ROUND_OFF
#define RTS_DIV_ROUND_OFF(n, d)	(((n) * 2 + (d)) / ((d) * 2))
#endif

#define OSD_MAX_CHNS		2

// fixed. don't change these value
#define OSD_PIC0_BLK_IDX	0
#define OSD_PIC1_BLK_IDX	1
#define OSD_PIC2_BLK_IDX	2
#define OSD_TEXT_BLK_IDX	3
#define OSD_DATE_BLK_IDX	4
#define OSD_TIME_BLK_IDX	5

#define OSD_TEXT_STR_MAX	32

#define RTS_OSD2_BLK_MAX_NUMBER		96
#define RTS_MAX_STM_COUNT		5

enum osd_char_type {
	char_type_single = 0,
	char_type_double = 1,
	char_type_picture = 2
};

enum rts_pix_fmt_e {
	RTS_PIX_FMT_UNDEFINED = 0,
	RTS_PIX_FMT_NV12 = 0x1,	/*YUV 420 semiplanar*/
	RTS_PIX_FMT_NV16,	/*YUV 422 semiplanar*/
	RTS_PIX_FMT_YUYV,
	RTS_PIX_FMT_YUV420M,	/*YUV 420 planar*/
	RTS_PIX_FMT_YVYU,

	RTS_PIX_FMT_1BPP = 0x100,
	RTS_PIX_FMT_GRAY_2,
	RTS_PIX_FMT_GRAY_4,
	RTS_PIX_FMT_GRAY_8,

	RTS_PIX_FMT_RGB888 = 0x200,
	RTS_PIX_FMT_ARGB8888,
	RTS_PIX_FMT_ARGB1555,

	RTS_PIX_FMT_RGBA1111 = 0x240,
	RTS_PIX_FMT_RGBA2222,
	RTS_PIX_FMT_RGBA5551,
	RTS_PIX_FMT_RGBA4444,
	RTS_PIX_FMT_RGBA8888,

	RTS_PIX_FMT_MJPEG = 0x300,
	RTS_PIX_FMT_H264,
	RTS_PIX_FMT_H265,
};

enum rts_osd2_blk_fmt {
	RTS_OSD2_BLK_FMT_1BPP = RTS_PIX_FMT_1BPP, /**< 1bpp format */
	RTS_OSD2_BLK_FMT_RGBA1111 = RTS_PIX_FMT_RGBA1111, /**< rgba1111 format */
	RTS_OSD2_BLK_FMT_RGBA2222 = RTS_PIX_FMT_RGBA2222, /**< rgba2222 format */
	RTS_OSD2_BLK_FMT_RGBA5551 = RTS_PIX_FMT_RGBA5551, /**< rgba5551 format */
	RTS_OSD2_BLK_FMT_RGBA4444 = RTS_PIX_FMT_RGBA4444, /**< rgba4444 format */
	RTS_OSD2_BLK_FMT_RGBA8888 = RTS_PIX_FMT_RGBA8888 /**< rgba8888 format */
};

enum rts_osd_time_fmt {
	osd_time_fmt_no = 0,	/*not show time*/
	osd_time_fmt_24,    //	hh:mm:ss	14:32:58
	osd_time_fmt_12,    //	hh:mm:ss	02:32:58
	osd_time_fmt_12_1,  //	Phh:mm:ss	P02:32:58
	osd_time_fmt_12_2,  //	PMhh:mm:ss	PM02:32:58
	osd_time_fmt_12_3,  //	PM~hh:mm:ss	PM~02:32:58
	osd_time_fmt_12_4,  //	hh:mm:ssPM	02:32:58PM
	osd_time_fmt_12_5,  //	hh:mm:ss~PM	02:32:58~PM
	osd_time_fmt_12_6,  //	hh:mm:ss~~PM	02:32:58~~PM
	osd_time_fmt_12_7,  //	hh:mm:ss~~~PM	02:32:58~~~PM
	osd_time_fmt_reserved
};

enum rts_osd_date_fmt {
	osd_date_fmt_no = 0,	/*not show date*/
	osd_date_fmt_0,		/*dd/MM/yyyy, eg. 26/05/2015*/
	osd_date_fmt_1,		/*dd/MM/yy, eg. 26/05/15*/
	osd_date_fmt_2,		/*d/M/yy, eg. 26/5/15*/
	osd_date_fmt_3,		/*M/d/yyyy, eg. 5/26/2015*/
	osd_date_fmt_4,		/*M/d/yy, eg. 5/26/15*/
	osd_date_fmt_5,		/*MM/dd/yy, eg. 05/26/15*/
	osd_date_fmt_6,		/*MM/dd/yyyy, eg. 05/26/2015*/
	osd_date_fmt_7,		/*yyyy/M/d, eg. 2015/5/26*/
	osd_date_fmt_8,		/*yyyy-M-d, eg. 2015-5-26*/
	osd_date_fmt_9,		/*yyyy-MM-dd, eg. 2015-05-26*/
	osd_date_fmt_10,	/*yyyy/MM/dd, eg. 2015/05/26*/
	osd_date_fmt_11,	/*yy-MM-dd, eg. 15-05-26*/
	osd_date_fmt_12,	/*yy/M/d, eg. 15/5/26*/
	osd_date_fmt_13,	/*yy-M-d, eg. 15-5-26*/
	osd_date_fmt_14,	/*yy/MM/dd, eg. 15/05/26*/
	osd_date_fmt_15,	/*yyyy.mm.dd, eg. 2015.05.26*/
	osd_date_fmt_16,	/*dd.mm.yyyy, eg. 26.05.2015*/
	osd_date_fmt_17,	/*mm.dd.yyyy, eg. 05.26.2015*/
	osd_date_fmt_18,	/*mm-dd-yyyy, eg. 05-26-2015*/
	osd_date_fmt_19,	/*dd-mm-yyyy, eg. 26-05-2015*/
	osd_date_fmt_20,	/*dd-mm-yyyy www, eg. 26-05-2015 Tue*/
	osd_date_fmt_21,	/*dd/mm/yyyy www, eg. 26/05/2015 Tue*/
	osd_date_fmt_22,	/*dd.mm.yyyy www, eg. 26.05.2015 Tue*/
	osd_date_fmt_reserved
};

typedef enum {
	OSD_FONT_ENG_CHI	= 0,
	OSD_FONT_ENG		= 1,
	OSD_FONT_SMALL_ENG	= 2,
} fontlib_e;

struct osd2_font_lib_header_t {
	uint16_t header_length;
	enum osd_char_type char_type;
	uint16_t char_width;
	uint16_t char_height;
	uint16_t width_bytes;
	enum {
		font_song = 0,
	} font_type;
	uint8_t font_size;
	enum {
		coding_utf8 = 0,
		coding_gbk = 1
	} coding_fmt;
	uint8_t char_num;
	uint8_t char_rotation;
	uint8_t reserved[2];
};

struct rts_osd2_font_lib_t {
	uint32_t lib_addr;

	struct osd2_font_lib_header_t header;
	uint16_t mapping_length;
	uint8_t *mapping_info;

	uint16_t start;
	uint16_t size;

	uint32_t lattice_size;

	int load;
	int inuse;
};

struct rts_osd_char_t {
	enum osd_char_type char_type;
	unsigned char char_value[4];
};

struct rts_osd_text_t {
	struct rts_osd_char_t *content;
	unsigned int count;
};

struct rts_osd_datetime_t {
	enum rts_osd_time_fmt time_fmt;
	uint8_t time_blkidx;
	int time_pos;
	enum rts_osd_date_fmt date_fmt;
	uint8_t date_blkidx;
	int date_pos;
};

struct rts_osd_rect_t {
	uint16_t start_x;
	uint16_t start_y;
	uint16_t end_x;
	uint16_t end_y;
};

typedef struct {
	int blk_idx;

	struct rts_video_osd2_attr *attr;
	enum rts_osd2_blk_fmt blk_fmt;
	uint32_t start_x;
	uint32_t start_y;
	uint32_t end_x;
	uint32_t end_y;
	uint32_t color_1bpp;

	uint8_t *buf;
	uint32_t len;

	int flick_enable;
	uint32_t show_time;
	uint32_t hide_time;
	uint8_t RSVD[12];
} rt_osd2_info_st;

typedef struct {
	BOOL	show;
	int		chn_id;
	__attribute__((aligned(32))) rt_osd2_info_st osd2;
} osd_pict_st;

typedef struct RS_BITMAP_S {
	uint32_t pixel_fmt;
	uint32_t u32Width;
	uint32_t u32Height;
	uint32_t u32BfrSize; //data buffer size
	uint32_t u32Length;  //actual len in data buffer
	void *pData;
} BITMAP_S;

typedef struct {
	void *font_lib_addr;

	uint8_t block_alpha;    //0~15
	uint32_t ch_color;
	uint8_t bg_enable;
	uint32_t bg_color;

	uint8_t h_gap : 4,
			v_gap : 4;

	uint8_t osd_char_w;
	uint8_t osd_char_h;

	enum rts_osd_time_fmt time_fmt;
	enum rts_osd_date_fmt date_fmt;
} rt_font_st;

typedef struct {
	BOOL	show;
	int		chn_id;
	__attribute__((aligned(32)))  rt_osd2_info_st osd2;
	//
	char		str[OSD_TEXT_STR_MAX];
	rt_font_st	font;
	rt_rotate_t	rotate;
} osd_text_st;

struct rts_video_coordinate {
	int32_t x; /**< x-axis value */
	int32_t y; /**< y-axis value */
};

/**
 * @brief Resolution description
 */
struct rts_video_size {
	uint32_t width; /**< width */
	uint32_t height; /**< height */
};

/**
 * @brief Rectangle description
 */
struct rts_video_rect {
	union {
		struct {
			struct rts_video_coordinate start; /**< coordinate of the starting point */
			struct rts_video_coordinate end; /**< coordinate of the ending point */
		}; /**< rectangle in coordinate format */
		struct {
			int32_t left; /**< rectangle left value */
			int32_t top; /**< rectangle top value */
			int32_t right; /**< rectangle right value */
			int32_t bottom; /**< rectangle bottom value */
		}; /**< rectangle in other format */
	}; /**< union of rectangle discription in two formats */
};

//osd2 func use 3903 arch
/**
 * @brief detail OSD block information
 */
struct rts_video_osd2_block {
	struct rts_video_rect rect; /**< rectangle */

	struct {
		enum rts_osd2_blk_fmt pixel_fmt;
		void *pdata; /**< picture data */
		uint32_t length; /**< picture data length */
		uint32_t pure_color; /**< set pure color rgb */
	} picture; /**< picture configure*/

	struct {
		int flick_enable; /**< enable flick */
		uint32_t show_time; /**< show time for flik */
		uint32_t hide_time; /**< hide tim efor flick */
	} flick; /**< flick configure*/

	uint8_t enable; /**< enable show block */
	//disable internal buffer, user should take care buffer management by themself
	//uint32_t fixed_buf_len;
	uint32_t reserved[4];
};

/**
 * @brief OSD attribute
 */
struct rts_video_osd2_attr {
	const int number; /**< OSD block number */
	struct rts_video_osd2_block *blocks;

	unsigned int single_font_addr;
	unsigned int double_font_addr;
	uint8_t osd_char_w;
	uint8_t osd_char_h;

	uint32_t reserved[4];
};
#define OSD_COLOR_TABLE_R_NUM_MAX 32
#define OSD_COLOR_TABLE_G_NUM_MAX 32
#define OSD_COLOR_TABLE_B_NUM_MAX 32
#define OSD_COLOR_TABLE_A_NUM_MAX 16
typedef struct {

	int fmt;

	BOOL b_update_all;

	uint8_t ch_id;

	uint8_t r_idx;
	uint8_t g_idx;
	uint8_t b_idx;
	uint8_t a_idx;

	uint8_t r_val;
	uint8_t g_val;
	uint8_t b_val;
	uint8_t a_val;

	uint8_t r_val_full[OSD_COLOR_TABLE_R_NUM_MAX];
	uint8_t g_val_full[OSD_COLOR_TABLE_G_NUM_MAX];
	uint8_t b_val_full[OSD_COLOR_TABLE_B_NUM_MAX];
	uint8_t a_val_full[OSD_COLOR_TABLE_A_NUM_MAX];

	uint8_t RSVD[2];

} rt_osd2_color_table_st;

#endif	// OSD_UTIL_H
