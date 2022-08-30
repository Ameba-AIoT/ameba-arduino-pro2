#include "nn_model_info.h"

#if MODEL_FACERECOG_USED
extern unsigned char img_face[NNMODEL_FR_NN_WIDTH * NNMODEL_FR_NN_HEIGHT * 3];

extern float face_rec_feature[MAX_DETECT_OBJ_NUM][NNMODEL_FR_FEATURE_NUM];
extern float face_reg_feature[MAX_FRC_OBJ_NUM]   [NNMODEL_FR_FEATURE_NUM];

#endif //MODEL_FACERECOG_USED
