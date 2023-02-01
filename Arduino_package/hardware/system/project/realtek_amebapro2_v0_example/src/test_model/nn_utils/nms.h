#ifndef __NMS_H__
#define __NMS_H__

#include "box_type.h"
#include "iou.h"

void do_nms(int class_num, int total, float threshold, box_t *pbox, box_t **ppbox, iou_t nms_kind);

#endif /* __NMS_H__ */