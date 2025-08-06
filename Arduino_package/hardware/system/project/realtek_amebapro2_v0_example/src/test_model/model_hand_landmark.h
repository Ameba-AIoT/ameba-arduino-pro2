#ifndef MODEL_HAND_LANDMARK_H
#define MODEL_HAND_LANDMARK_H
#include "module_vipnn.h"
extern nnmodel_t hand_landmark_fwfs;

enum {
	HANDEDNESS_LEFT = 0,
	HANDEDNESS_RIGHT = 1,
	HANDEDNESS_NOTSURE = 2,
	HANDEDNESS_NOTFOUND = 3,
};

#endif
