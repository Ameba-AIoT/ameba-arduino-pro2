#ifndef NNMODEL_CONF_H_
#define NNMODEL_CONF_H_

//ifdef NNIRQ_USED_SKIP => NN H/W interrupt not used
//#define NNIRQ_USED_SKIP


#define POSTP_SSDM_USED       0
#define POSTP_FACE_USED       0
#define POSTP_HUMAN_USED      0

#define MODEL_SSDM_USED       0
#define MODEL_FACE_USED       1
#define MODEL_HUMAN_USED      0
#define MODEL_FACERECOG_USED  1


#define POSTP_SSDM       (MODEL_SSDM_USED | POSTP_SSDM_USED)
#define POSTP_FACE       (MODEL_FACE_USED | POSTP_FACE_USED)
#define POSTP_FACERECOG  (MODEL_FACERECOG_USED             )

typedef enum {
	MOBILENETSSD_20OBJ = 0,
	MODEL_HUMAN,
	MODEL_FACE,
	MODEL_FACERECOG,
} NNMODEL_TYPE_t;

#endif //NNMODEL_CONF_H_
