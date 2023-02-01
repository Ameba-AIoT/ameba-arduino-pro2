#ifndef __BOX_TYPE_H__
#define __BOX_TYPE_H__

typedef struct box_s {
	float x, y;
	float w, h;
	union {
		float prob;
		float score;
	};
	union {
		float landmarks[10];
		float dummy[10];
	};
	int class_idx;
	int invalid;
} box_t;

#endif /* __BOX_TYPE_H__ */