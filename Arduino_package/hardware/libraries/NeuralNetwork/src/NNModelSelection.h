#ifndef __NNMODELSELECTION_H__
#define __NNMODELSELECTION_H__

#include "VideoStream.h"

#define NA_MODEL                 0x00
#define DEFAULT_YOLOV3TINY       0x01
#define DEFAULT_YOLOV4TINY       0x02
#define DEFAULT_YOLOV7TINY       0x03
#define DEFAULT_SCRFD            0x04
#define DEFAULT_MOBILEFACENET    0x05
#define CUSTOMIZED_YOLOV3TINY    0x11
#define CUSTOMIZED_YOLOV4TINY    0x12
#define CUSTOMIZED_YOLOV7TINY    0x13
#define CUSTOMIZED_SCRFD         0x14
#define CUSTOMIZED_MOBILEFACENET 0x15

#define OBJECT_DETECTION         0x21
#define FACE_DETECTION           0x22
#define FACE_RECOGNITION         0x23

class NNModelSelection:public MMFModule {
    public:
        void modelSelect(unsigned char nntask);
        void modelSelect(unsigned char nntask, unsigned char objdetmodel, unsigned char facedetmodel, unsigned char facerecogmodel);

    protected:
        unsigned char _yolomodel;
        unsigned char _scrfdmodel;
        unsigned char _mfnmodel;
        unsigned char _nntask;
};
#endif
