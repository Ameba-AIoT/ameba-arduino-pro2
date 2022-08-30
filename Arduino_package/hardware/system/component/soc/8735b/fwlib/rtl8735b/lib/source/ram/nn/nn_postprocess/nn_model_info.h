#ifndef NNMODEL_INFO_H_
#define NNMODEL_INFO_H_

#include "nn_api_config.h"

#define MAX_DETECT_OBJ_NUM     20
#define MAX_FRC_OBJ_NUM        20

#if POSTP_SSDM
//======== Begin : MOBILENETSSD_20OBJ ========
//SM => SSD mobilenet


#define NNMODEL_SM_NN_WIDTH           300
#define NNMODEL_SM_NN_HEIGHT          300

// model input is Planer -- mobilenet_ssd_uint8
// RGB planar
#define NNMODEL_SM_CHANREVERSE       1

/************************************************************
Post processing of Output Tensors
************************************************************
Output 0
Dim Count:                                                 2
Size of Dim[0]:                                         7668
Size of Dim[1]:                                            1
Data Format:                         NBG_BUFFER_FORMAT_UINT8
Data Type:                            NBG_BUFFER_TYPE_TENSOR
Quantization Format:   NBG_BUFFER_QUANTIZE_AFFINE_ASYMMETRIC
Fixed Point Pos:                                         -45
TF Scale:                                           0.124952
TF Zeropoint:                                            169
Memory Size (bytes):                                    7680
************************************************************
Output 1
Dim Count:                                                 2
Size of Dim[0]:                                        40257
Size of Dim[1]:                                            1
Data Format:                          NBG_BUFFER_FORMAT_FP16
Data Type:                            NBG_BUFFER_TYPE_TENSOR
Quantization Format:                NBG_BUFFER_QUANTIZE_NONE
Fixed Point Pos:                                           0
TF Scale:                                           1.000000
TF Zeropoint:                                              0
Memory Size (bytes):                                   80576
************************************************************/
#define NNMODEL_SM_POST_CLASS_NUM      21
#define NNMODEL_SM_POST_LOCA_NUM       1917
#define NNMODEL_SM_POST_LOCA_SCALE     0.124952
#define NNMODEL_SM_POST_LOCA_ZEROPOINT 169
#define NNMODEL_SM_POST_CONF_NUM       40257

//======== End   : MOBILENETSSD_20OBJ ========
#endif //POSTP_SSDM




#if POSTP_FACE
//======== Begin : MODEL_FACE ========

#define NNMODEL_FACE_NN_WIDTH           300
#define NNMODEL_FACE_NN_HEIGHT          300

// RGB planar
#define NNMODEL_FACE_CHANREVERSE       0

/********************************************************************************
Output Table
********************************************************************************
Output 0
Dim Count:                                                                     4
Size of Dim[0]:                                                                4
Size of Dim[1]:                                                                1
Size of Dim[2]:                                                             1917
Size of Dim[3]:                                                                1
Data Format:                                             NBG_BUFFER_FORMAT_UINT8
Data Type:                                                NBG_BUFFER_TYPE_TENSOR
Quantization Format:                       NBG_BUFFER_QUANTIZE_AFFINE_ASYMMETRIC
Fixed Point Pos:                                                             118
TF Scale:                                                               0.056639
TF Zeropoint:                                                                192
Memory Size (bytes):                                                        7680
output name:                                                         uid_3_out_0
********************************************************************************
Output 1
Dim Count:                                                                     3
Size of Dim[0]:                                                                2
Size of Dim[1]:                                                             1917
Size of Dim[2]:                                                                1
Data Format:                                             NBG_BUFFER_FORMAT_UINT8
Data Type:                                                NBG_BUFFER_TYPE_TENSOR
Quantization Format:                       NBG_BUFFER_QUANTIZE_AFFINE_ASYMMETRIC
Fixed Point Pos:                                                              35
TF Scale:                                                               0.108771
TF Zeropoint:                                                                126
Memory Size (bytes):                                                        3840
output name:                                                         uid_4_out_0
********************************************************************************/
#define NNMODEL_FACE_CLASS_NUM      2

#define NNMODEL_FACE_LOCA_NUM       1917
#define NNMODEL_FACE_LOCA_SCALE     0.056639
#define NNMODEL_FACE_LOCA_ZEROPOINT 192

#define NNMODEL_FACE_CONF_NUM       3834
#define NNMODEL_FACE_CONF_SCALE     0.108771
#define NNMODEL_FACE_CONF_ZEROPOINT 126



//======== End : MODEL_FACE ========
#endif //POSTP_FACE

#if POSTP_FACERECOG
#define NNMODEL_FR_NN_WIDTH     112
#define NNMODEL_FR_NN_HEIGHT    112

#define NNMODEL_FR_CHANREVERSE       1
/********************************************************************************
Output Table
********************************************************************************
Output 0
Dim Count:                                                                     2
Size of Dim[0]:                                                              128
Size of Dim[1]:                                                                1
Data Format:                                             NBG_BUFFER_FORMAT_UINT8
Data Type:                                                NBG_BUFFER_TYPE_TENSOR
Quantization Format:                       NBG_BUFFER_QUANTIZE_AFFINE_ASYMMETRIC
Fixed Point Pos:                                                            -126
TF Scale:                                                               0.015558
TF Zeropoint:                                                                129
Memory Size (bytes):                                                         128
output name:                                                         uid_2_out_0
********************************************************************************/
#define NNMODEL_FR_FEATURE_NUM       128
#define NNMODEL_FR_FEATURE_SCALE     0.015558
#define NNMODEL_FR_FEATURE_ZEROPOINT 129
//======== End : MODEL_FACE ========
#endif //POSTP_FACERECOG



//--- Used to declare post_porcessing memory array -----
#if   POSTP_SSDM
#define MAX_CLASS_NUM 21
#elif POSTP_FACE
#define MAX_CLASS_NUM 2
#elif MODEL_HUMAN_USED
#define MAX_CLASS_NUM 2
#else
#define MAX_CLASS_NUM 2
#endif

#define MAX_LOCA_NUM  1917


#endif //NNMODEL_INFO_H_
