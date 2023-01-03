#ifndef _FACE_ALIGNMENT_H_
#define _FACE_ALIGNMENT_H_

typedef struct lmpos_t_ {
	float x;
	float y;
} lmpos_t;

typedef struct lm_t_ {
	lmpos_t pos[5];
} lm_t;

int face_alignment(lm_t landmark, lm_t ref, uint8_t *psrc, int src_w, int src_h, uint8_t *pdst, int dst_w, int dst_h);

#endif
