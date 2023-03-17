#ifndef _ROI_DELTA_QP_H_
#define _ROI_DELTA_QP_H_

/*
 * This function should work with VOE1.3.4.0 and later version
 */

typedef enum {
	ROI_DELTA_QP_START,
	ROI_DELTA_QP_STOP
} roi_delta_qp_status_t;

typedef struct roi_delta_qp_ctx_s {
	int ch_use[4];
	int video_wh[4][2];
	roi_delta_qp_status_t status;
} roi_delta_qp_ctx_t;

/*
 * delta QP range: -31 ~ 31
 * the smaller delta QP, the better video roi quality
 */
#define ROI_DELTA_QP_MAX      (31)
#define ROI_DELTA_QP_MIN      (-31)
#define ROI_DELTA_QP_DEFAULT  (-20)

void roi_delta_qp_init(int ch, int width, int height);
void roi_delta_qp_deinit(void);
void roi_delta_qp_start(void);
void roi_delta_qp_stop(void);
void roi_delta_qp_reset_qptable(void);
void roi_delta_qp_set_param(int ch, int rect_xmin, int rect_ymin, int rect_w, int rect_h, int delta_qp);

#endif /* _ROI_DELTA_QP_H_ */