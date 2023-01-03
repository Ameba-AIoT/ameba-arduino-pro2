#ifndef __IOU_H__
#define __IOU_H__

#include "box_type.h"

typedef enum {
	IOU,
	DIOU,
} iou_t;

float iou(box_t *a, box_t *b, iou_t iou_type);

#endif /* __IOU_H__ */