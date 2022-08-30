#include "nn_api.h"
#include "nn_model_info.h"

typedef struct _BBoxRect {
	float xmin;
	float ymin;
	float xmax;
	float ymax;
	int label;
} BBoxRect;


#ifndef USEORGMEM
extern float bboxes[MAX_LOCA_NUM * 4];
extern BBoxRect class_bbox_rects[MAX_LOCA_NUM];
extern float class_bbox_scores[MAX_LOCA_NUM];
extern int picked[MAX_LOCA_NUM];
extern BBoxRect *all_class_bbox_rects[MAX_CLASS_NUM];
extern float *all_class_bbox_scores[MAX_CLASS_NUM];


extern BBoxRect bbox_rects[MAX_LOCA_NUM];
extern float bbox_scores[MAX_LOCA_NUM];
extern float all_class_bbox_scores_all[MAX_LOCA_NUM * MAX_CLASS_NUM];
extern BBoxRect all_class_bbox_rects_all[MAX_LOCA_NUM * MAX_CLASS_NUM];
#endif


