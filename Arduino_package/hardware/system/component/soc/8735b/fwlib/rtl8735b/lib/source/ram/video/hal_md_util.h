#ifndef HAL_MTD_UTIL_H
#define HAL_MTD_UTIL_H

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
//#include "voe.h"
#endif
/**
* @defgroup md2 Motion Detection for RTS3915
* @brief API and Structure for Motion Detection of RTS3915
* @ingroup total
* @{
*/
/**
 * @example example_md2.c
 */
/**
 * @brief Sample region of motion detection 2
 */
struct md2_sample_region {
	uint32_t x; /**< start x */
	uint32_t y; /**< start y */
	uint32_t w; /**< width */
	uint32_t h; /**< height */
	/**
	 * scale of width
	 * pixel sample interval of motion detection in x-direction
	 * senor_image_width = x + w * scale_x
	 */
	uint32_t scale_x;
	/**
	 * scale of height
	 * senor_image_height = y + h * scale_y
	 */
	uint32_t scale_y;
};

/**
 * @brief Bin bits of motion detection 2, data bits of a bin of a pixel sample
 */
enum MD2_BIN_BITS {
	MD2_BIN_BITS_2 = 0, /**< bin bits is 2 */
	MD2_BIN_BITS_4, /**< bin bits is 4 */
	MD2_BIN_BITS_MAX, /**< reserved */
};

/**
 * @brief Bins number of motion detection 2, number of bins of a pixel sample
 */
enum MD2_NR_BINS {
	MD2_NR_BINS_16 = 0, /**< bins number is 16 */
	MD2_NR_BINS_32, /**< bins number is 32 */
	MD2_NR_BINS_MAX, /**< reserved */
};

/**
 * @brief Attribution of motion detection 2
 */
struct md2_attr {
	struct md2_sample_region sample; /**< sample region */
	enum MD2_BIN_BITS bin_bits; /**< bin bits */
	enum MD2_NR_BINS nr_bins; /**< bins number */
	int skip_frames; /**< skip frame count, sample interval of isp frames*/
};

/**
 * @brief Roi(region of interest) map of motion detection 2
 */
struct md2_roi_map {
	const uint32_t width; /**< roi width */
	const uint32_t height; /**< roi height */
	const uint32_t length; /**< roi map buffer length */

	uint8_t *const map; /**< roi map buffer, pixfmt is yonly*/
};

/**
 * @brief Control description for motion detection 2
 * must turn on RTS_MD2_RESULT_FL_ENABLE_CC_FILTER,
 * to make nr_cc_thd&max_ar&min_ar&cc_ratio effective
 */
struct md2_ctrl {
	struct md2_roi_map roi; /**< roi map*/

	/**
	 * sensitivity, 0 ~ 7.
	 * 1 ~ 7 automatic mode, will automatic set nr_cc_thd & back_thd,
	 *  (which means nr_cc_thd & back_thd settings will be ignored).
	 * 0 mannual mode, nr_cc_thd & back_thd is effective.
	 * default value: 6
	 **/
	int sensitivity;

	int train_enable; /**< train enable*/
	uint32_t train_frames; /**< train frames*/
	/**
	 * scene change threshold
	 * if current frame contains more motion pixels, will trigger trainning.
	 * default value: attr->sample.w * attr->sample.h * 0.5
	 */
	uint32_t scene_change_thd;

	/**
	 * background threshold, 0 ~ 15, thd to determind if it's background or foregound.
	 * if sensitivity is 1 ~ 7, back_thd setting is ignored.
	 */
	uint8_t back_thd;
	uint8_t learn_thd; /**< learn threshold, 0 ~ 255, learn_thd/255 is the learn probabilty for each frame*/
	uint8_t forget_thd; /**< forget threshold, 0 ~ 255, learn_thd/255 is the forget probabilty for each frame*/

	/**
	 * minimum pixel number of connect domain
	 * connect domain which cotains less pixels will be filter out.
	 * if sensitivity is 1 ~ 7, nr_cc_thd setting is ignored.
	 */
	uint32_t nr_cc_thd;
	/**
	 * max aspect ratio, compute by cc_w/cc_h, cc ar larger will be filter out.
	 * default value: 1.5
	 */
	float max_ar;
	/**
	 * min aspect ratio, cc ar smaller will be filter out.
	 * default value: 0.05
	 */
	float min_ar;
	/**
	 * connected domain ratio, 0 <= cc_ratio < 1, compute by pixel_count/(cc_w*cc_h), cc_ratio smaller will be filter out.
	 * default value: 0.3
	 */
	float cc_ratio;

	uint32_t RSVD[3];

};

enum MD2_PARAM_SEL {
	MD2_PARAM_ROI = 0, /**< bin bits is 2 */
	MD2_PARAM_SENSITIVITY,
	MD2_PARAM_TRAIN_FRAMES,
	MD2_PARAM_BACK_THD,
	MD2_PARAM_NR_CC_THD,
	MD2_PARAM_LEARN_RATE,
	MD2_PARAM_FORGET_RATE,
	MD2_PARAM_NR_BINS,
	MD2_PARAM_BIN_BITS,
	MD2_PARAM_AR,
	MD2_PARAM_SCENE_THD,
	MD2_PARAM_PP_EN,
};

struct md2_cc {
	uint16_t u; /**< up of connected domain*/
	uint16_t b; /**< bottom of connected domain*/
	uint16_t l; /**< left of connected domain*/
	uint16_t r; /**< right of connected domain*/
	uint32_t pixel_cnt; /**< pixel count of connected domain*/
};

#define MD2_MAX_CC_NUM 20

struct md2_cc_info {
	struct md2_cc cc[MD2_MAX_CC_NUM]; /**< connected domain*/
	uint32_t cc_len; /**< effective connected domain count*/
};

typedef struct {
	unsigned int flags; /**< md2 result flags, control result type*/
	unsigned int motion_cnt; /**< motion count*/
	uint8_t *motion_map; /**< motion map*/
	struct md2_cc_info cc_info; /**< connected domain info*/
} __attribute__((aligned(32))) md2_result_t;


typedef struct {
	struct md2_attr *attr;
	struct md2_ctrl *ctrl;
	int pp_en;
	uint32_t RSVD[5];
} md2_adaptor_t;

#endif	// HAL_MTD_UTIL_H
