#ifndef _HAL_FRC_H_
#define _HAL_FRC_H_

#include "nn_api.h"
#include "nn_model_info.h"

#if MODEL_FACERECOG_USED

typedef struct FRC_INFO_S {
	struct cvRect_S      bbox;
	unsigned int         reg_index;
	float                score;
} FRC_INFO_S;

int nn_face_register(
	//-- input --
	struct MODEL_INFO_S *model_info_face,
	struct MODEL_INFO_S *model_info_frc,
	unsigned char       *frame_in,
	unsigned int         frame_in_width,
	unsigned int         frame_in_height,
	struct cvRect_S     *ROIRect,
	//-- buffer --
	struct FRC_INFO_S   *frc_info,
	float                face_feature[][NNMODEL_FR_FEATURE_NUM],
	//-- output --
	unsigned int         *reg_feature_num,
	float                reg_feature[][NNMODEL_FR_FEATURE_NUM]
);

int nn_face_recog(
	//-- input --
	struct MODEL_INFO_S *model_info_face,
	struct MODEL_INFO_S *model_info_frc,
	unsigned char       *frame_in,
	unsigned int         frame_in_width,
	unsigned int         frame_in_height,
	struct cvRect_S     *ROIRect,
	//--output--
	struct FRC_INFO_S   *frc_info,
	unsigned int         *face_feature_num,
	//--buffer--
	float                face_feature[][NNMODEL_FR_FEATURE_NUM],
	//--input--
	unsigned int         reg_feature_num,
	float                reg_feature [][NNMODEL_FR_FEATURE_NUM]
);

#endif //MODEL_FACERECOG_USED

#endif //_HAL_FRC_H_
