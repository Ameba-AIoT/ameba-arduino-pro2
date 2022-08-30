#ifndef NNMODEL_INFO_DDR_H_
#define NNMODEL_INFO_DDR_H_

#include "nn_api_config.h"

#if MODEL_SSDM_USED

//Model
extern const unsigned int nnmodel_sm_ro[];

//PPU resize input image resolution
#define NNMODEL_SM_IMG_WIDTH     640
#define NNMODEL_SM_IMG_HEIGHT    360

#define NNMODEL_SM_ADDR_BASE     0x73000000
#define NNMODEL_SM_SIZE          4270192

#define NNMODEL_SM_ADDR_RO       0x73000000
#define NNMODEL_SM_CONTROL       0x00010325
#define NNMODEL_SM_ADDR_ST       0x73410f40

#define NNMODEL_SM_INPUT0        0x733fb2c0
#define NNMODEL_SM_INPUT1        0x733fb300
#define NNMODEL_SM_INPUT2        0x733fb340
#define NNMODEL_SM_INPUT3        0x733fb380
#define NNMODEL_SM_INPUT4        0x733fb3c0
#define NNMODEL_SM_INPUT5        0x733fb400
#define NNMODEL_SM_INPUT6        0x733fb440
#define NNMODEL_SM_INPUT7        0x733fb480
#define NNMODEL_SM_INPUT8        0x733fb4c0
#define NNMODEL_SM_INPUT9        0x733fb500
#define NNMODEL_SM_INPUT10       0x733fb540
#define NNMODEL_SM_INPUT11       0x733fb580
#define NNMODEL_SM_INPUT12       0x733fb5c0

//output0 - location Bounding Boxes
//output1 - confidence scorces
#define NNMODEL_SM_OUTPUT0       0x73e00000
#define NNMODEL_SM_OUTPUT1       0x73e20000

//NN_INPUT0 is RGB
#define NNMODEL_SM_INPUT0_ADDR_R   (0x73000000 + (1065949-6)*4)
#define NNMODEL_SM_INPUT0_ADDR_G   (0x73000000 + (1066223-6)*4)
#define NNMODEL_SM_INPUT0_ADDR_B   (0x73000000 + (1066497-6)*4)

#endif //MODEL_SSDM_USED




#if MODEL_FACE_USED

//VIPLite 1.3.6
extern const unsigned int nnmodel_face_ro[];

//PPU resize input image resolution
#define NNMODEL_FACE_IMG_WIDTH     640
#define NNMODEL_FACE_IMG_HEIGHT    360

//fake use mobilenet to test
#define NNMODEL_FACE_ADDR_BASE     0x73500000
#define NNMODEL_FACE_SIZE          5416256

#define NNMODEL_FACE_ADDR_RO       0x73500000
#define NNMODEL_FACE_CONTROL       0x00010302
#define NNMODEL_FACE_ADDR_ST       0x73a26e00

#define NNMODEL_FACE_INPUT0  0x73a23d40
#define NNMODEL_FACE_INPUT1  0x73a23d80
#define NNMODEL_FACE_INPUT2  0x73a23dc0
#define NNMODEL_FACE_INPUT3  0x73a23e00
#define NNMODEL_FACE_INPUT4  0x73a23e40
#define NNMODEL_FACE_INPUT5  0x73a23e80
#define NNMODEL_FACE_INPUT6  0x73a23ec0
#define NNMODEL_FACE_INPUT7  0x73a23f00
#define NNMODEL_FACE_INPUT8  0x73a23f40
#define NNMODEL_FACE_INPUT9  0x73a23f80
#define NNMODEL_FACE_INPUT10 0x73a23fc0
#define NNMODEL_FACE_INPUT11 0x73a24000
#define NNMODEL_FACE_INPUT12 0x73a24040

//output0 - location Bounding Boxes
//output1 - confidence scorces
#define NNMODEL_FACE_OUTPUT0       0x73e00000
#define NNMODEL_FACE_OUTPUT1       0x73e20000

//NN_INPUT0 is RGB
#define NNMODEL_FACE_INPUT0_ADDR_R   (0x73500000 + (1350541-6)*4)
#define NNMODEL_FACE_INPUT0_ADDR_G   (0x73500000 + (1350815-6)*4)
#define NNMODEL_FACE_INPUT0_ADDR_B   (0x73500000 + (1351089-6)*4)

#endif //MODEL_FACE_USED


#if MODEL_FACERECOG_USED

extern const unsigned int nnmodel_facerecog_ro[];

//crop and resize by c-prog
#define NNMODEL_FR_IMG_WIDTH     112
#define NNMODEL_FR_IMG_HEIGHT    112

#define NNMODEL_FR_ADDR_BASE     0x73000000
#define NNMODEL_FR_SIZE          1016512


#define NNMODEL_FR_ADDR_RO       0x73000000
#define NNMODEL_FR_CONTROL       0x000110a5
#define NNMODEL_FR_ADDR_ST       0x730e9640

#define NNMODEL_FR_INPUT0        0x730e94c0
#define NNMODEL_FR_INPUT1        0x73e20000
#define NNMODEL_FR_INPUT2        0x73e20000
#define NNMODEL_FR_INPUT3        0x73e20000
#define NNMODEL_FR_INPUT4        0x73e20000
#define NNMODEL_FR_INPUT5        0x73e20000
#define NNMODEL_FR_INPUT6        0x73e20000
#define NNMODEL_FR_INPUT7        0x73e20000
#define NNMODEL_FR_INPUT8        0x73e20000
#define NNMODEL_FR_INPUT9        0x73e20000
#define NNMODEL_FR_INPUT10       0x73e20000
#define NNMODEL_FR_INPUT11       0x73e20000
#define NNMODEL_FR_INPUT12       0x73e20000

#define NNMODEL_FR_OUTPUT0       0x73e00000
#define NNMODEL_FR_OUTPUT1       0x73e20000

//NN_INPUT0 is RGB
#define NNMODEL_FR_INPUT0_ADDR_R   (0x73000000 + (239005-6)*4)
#define NNMODEL_FR_INPUT0_ADDR_G   (0x73000000 + (239167-6)*4)
#define NNMODEL_FR_INPUT0_ADDR_B   (0x73000000 + (239329-6)*4)

#endif //MODEL_FACERECOG_USED


#endif //NNMODEL_INFO_DDR_H_
