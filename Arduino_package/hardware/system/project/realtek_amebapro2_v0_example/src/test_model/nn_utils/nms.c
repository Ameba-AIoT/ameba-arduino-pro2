//------------------------------------------------------------------------------
// NMS
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdint.h>
#include "nms.h"
#include "iou.h"

static int nms_box_comparator(const void *pa, const void *pb)
{
	box_t *a = *(box_t **)pa;
	box_t *b = *(box_t **)pb;
	float diff = a->prob - b->prob;
	if (diff < 0) {
		return 1;
	} else if (diff > 0) {
		return -1;
	}
	return 0;
}

static int nms_setup_class_box(int class, int total, box_t *pbox, box_t **ppbox)
{
	int class_cnt = 0;
	for (int i = 0; i < total; i++) {
		if (pbox[i].class_idx == class) {
			ppbox[class_cnt] = &pbox[i];
			class_cnt++;
		}
	}
	return class_cnt;
}

static void nms_box(float threshold, box_t **ppbox, int box_cnt, iou_t nms_kind)
{
	qsort(ppbox, box_cnt, sizeof(box_t *), nms_box_comparator);

	box_t *a, *b;
	for (int i = 0; i < box_cnt; i++) {
		a = ppbox[i];
		for (int j = i + 1; j < box_cnt; j++) {
			b = ppbox[j];
			if (iou(a, b, nms_kind) > threshold) {
				b->invalid = 1;
			}
		}
	}
}

void do_nms(int class_num, int total, float threshold, box_t *pbox, box_t **ppbox, iou_t nms_kind)
{
	for (int cls = 0; cls < class_num; cls++) {
		int class_cnt = nms_setup_class_box(cls, total, pbox, ppbox);
		nms_box(threshold, ppbox, class_cnt, nms_kind);
	}
}

