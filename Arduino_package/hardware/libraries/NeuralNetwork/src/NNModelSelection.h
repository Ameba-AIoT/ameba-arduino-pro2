#ifndef __NNMODELSELECTION_H__
#define __NNMODELSELECTION_H__

#include "VideoStream.h"

#define NA_MODEL              0x00
#define DEFAULT_YOLOV3TINY    0x01
#define DEFAULT_YOLOV4TINY    0x02
#define DEFAULT_YOLOV7TINY    0x03
#define DEFAULT_SCRFD         0x04
#define DEFAULT_MOBILEFACENET 0x05
#define DEFAULT_YAMNET        0x06
#define DEFAULT_IMGCLASS      0x07

#define CUSTOMIZED_YOLOV3TINY    0x11
#define CUSTOMIZED_YOLOV4TINY    0x12
#define CUSTOMIZED_YOLOV7TINY    0x13
#define CUSTOMIZED_SCRFD         0x14
#define CUSTOMIZED_MOBILEFACENET 0x15
#define CUSTOMIZED_YAMNET        0x16
#define CUSTOMIZED_IMGCLASS      0x17

#define OBJECT_DETECTION     0x21
#define FACE_DETECTION       0x22
#define FACE_RECOGNITION     0x23
#define AUDIO_CLASSIFICATION 0x24
#define IMAGE_CLASSIFICATION 0x25

class NNModelSelection: public MMFModule {
public:
    void modelSelect(unsigned char nntask);
    void modelSelect(unsigned char nntask, unsigned char objdetmodel, unsigned char facedetmodel, unsigned char facerecogmodel, unsigned char audclassmodel);
    void modelSelect(unsigned char nntask, unsigned char objdetmodel, unsigned char facedetmodel, unsigned char facerecogmodel);
    void modelSelect(unsigned char nntask, unsigned char objdetmodel, unsigned char facedetmodel, unsigned char facerecogmodel, unsigned char audclassmodel, unsigned char imgclassmodel);

protected:
    unsigned char _yolomodel;
    unsigned char _scrfdmodel;
    unsigned char _mfnmodel;
    unsigned char _yamnetmodel;
    unsigned char _imgclassmodel;
    unsigned char _nntask;
};
#endif
