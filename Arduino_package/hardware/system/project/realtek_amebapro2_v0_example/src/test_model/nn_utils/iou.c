//------------------------------------------------------------------------------
// IOU
//------------------------------------------------------------------------------
#include <math.h>
#include <stdint.h>
#include "iou.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

static float overlap(float x1, float w1, float x2, float w2)
{
	float l1 = x1;
	float l2 = x2;
	float left = max(l1, l2);
	float r1 = x1 + w1;
	float r2 = x2 + w2;
	float right = min(r1, r2);
	return right - left;
}

static float box_intersection(box_t *a, box_t *b)
{
	float w = overlap(a->x, a->w, b->x, b->w);
	float h = overlap(a->y, a->h, b->y, b->h);
	if (w < 0 || h < 0) {
		return 0;
	}
	float area = w * h;
	return area;
}

static float box_union(box_t *a, box_t *b)
{
	float i = box_intersection(a, b);
	float u = a->w * a->h + b->w * b->h - i;
	return u;
}

static float box_iou(box_t *a, box_t *b)
{
	return box_intersection(a, b) / box_union(a, b);
}

// return a smallest box contain a and b
static box_t box_box(box_t *a, box_t *b)
{
	box_t c;
	float c_topx = min(a->x, b->x);
	float c_topy = min(a->y, b->y);
	float c_botx = max(a->x + a->w, b->x + b->w);
	float c_boty = max(a->y + a->h, b->y + b->h);
	c.x = c_topx;
	c.y = c_topy;
	c.w = c_botx - c_topx;
	c.h = c_boty - c_topy;
	return c;
}

static float box_diou(box_t *a, box_t *b)
{
	float a_cx = a->x + (a->w / 2);
	float a_cy = a->y + (a->h / 2);
	float b_cx = b->x + (b->w / 2);
	float b_cy = b->y + (b->h / 2);
	box_t ab = box_box(a, b);
	float c = ab.w * ab.w + ab.h * ab.h;
	float d = (a_cx - b_cx) * (a_cx - b_cx) + (a_cy - b_cy) * (a_cy - b_cy);
	float u = pow(d / c, 0.6);
	return box_iou(a, b) - u;
}

float iou(box_t *a, box_t *b, iou_t iou_type)
{
	switch (iou_type) {
	case IOU:
		return box_iou(a, b);
	case DIOU:
		return box_diou(a, b);
	}
	return 0.0;
}
