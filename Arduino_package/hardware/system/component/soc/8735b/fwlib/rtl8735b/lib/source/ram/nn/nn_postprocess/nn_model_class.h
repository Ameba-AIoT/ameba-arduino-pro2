#ifndef NNMODEL_CLASS_H_
#define NNMODEL_CLASS_H_

#include "nn_api_config.h"

#if POSTP_SSDM
//SM => SSD mobilenet

static char *CLASSES_21OBJ[21] = {"__background__",
								  "aeroplane", "bicycle", "bird", "boat",
								  "bottle", "bus", "car", "cat", "chair",
								  "cow", "diningtable", "dog", "horse",
								  "motorbike", "person", "pottedplant",
								  "sheep", "sofa", "train", "tvmonitor"
								 };

#endif //POSTP_SSDM




#if POSTP_FACE
static char *CLASSES_FACE[2] = {"__background__",
								"face"
							   };

#endif //POSTP_FACE

#endif //NNMODEL_CLASS_H_
