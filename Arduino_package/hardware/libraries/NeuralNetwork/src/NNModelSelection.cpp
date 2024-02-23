#include <Arduino.h>
#include "NNModelSelection.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "nn_file_op.h"
#ifdef __cplusplus
}
#endif

extern void nn_load_model_src_sel(uint32_t);

void NNModelSelection::modelSelect(unsigned char nntask)
{
    nn_load_model_src_sel(ARDUINO_LOAD_MODEL);
    switch (nntask) {
        case OBJECT_DETECTION: {
            _nntask = OBJECT_DETECTION;
            _yolomodel = DEFAULT_YOLOV4TINY;
            _scrfdmodel = NA_MODEL;
            _mfnmodel = NA_MODEL;
            _yamnetmodel = NA_MODEL;
            break;
        }
        case FACE_DETECTION: {
            _nntask = FACE_DETECTION;
            _yolomodel = NA_MODEL;
            _scrfdmodel = DEFAULT_SCRFD;
            _mfnmodel = NA_MODEL;
            _yamnetmodel = NA_MODEL;
            break;
        }
        case FACE_RECOGNITION: {
            _nntask = FACE_RECOGNITION;
            _yolomodel = NA_MODEL;
            _mfnmodel = DEFAULT_MOBILEFACENET;
            _scrfdmodel = DEFAULT_SCRFD;
            _yamnetmodel = NA_MODEL;
            break;
        }
        case AUDIO_CLASSIFICATION: {
            _nntask = AUDIO_CLASSIFICATION;
            _yolomodel = NA_MODEL;
            _mfnmodel = NA_MODEL;
            _scrfdmodel = NA_MODEL;
            _yamnetmodel = DEFAULT_YAMNET;
            break;
        }
        case IMAGE_CLASSIFICATION: {
            _nntask = IMAGE_CLASSIFICATION;
            _yolomodel = NA_MODEL;
            _mfnmodel = NA_MODEL;
            _scrfdmodel = NA_MODEL;
            _yamnetmodel = NA_MODEL;
            _imgclassmodel = DEFAULT_IMGCLASS;
            break;
        }
    }
}

void NNModelSelection::modelSelect(unsigned char nntask, unsigned char objdetmodel, unsigned char facedetmodel, unsigned char facerecogmodel, unsigned char audclassmodel, unsigned char imgclassmodel)
{
    nn_load_model_src_sel(ARDUINO_LOAD_MODEL);
    switch (nntask) {
        case OBJECT_DETECTION: {
            _nntask = OBJECT_DETECTION;
            break;
        }
        case FACE_DETECTION: {
            _nntask = FACE_DETECTION;
            break;
        }
        case FACE_RECOGNITION: {
            _nntask = FACE_RECOGNITION;
            break;
        }
        case AUDIO_CLASSIFICATION: {
            _nntask = AUDIO_CLASSIFICATION;
            break;
        }
        case IMAGE_CLASSIFICATION: {
            _nntask = IMAGE_CLASSIFICATION;
            break;
        }
    }

    // YOLO
    switch (objdetmodel) {
        case DEFAULT_YOLOV3TINY: {
            _yolomodel = DEFAULT_YOLOV3TINY;
            break;
        }
        case DEFAULT_YOLOV4TINY: {
            _yolomodel = DEFAULT_YOLOV4TINY;
            break;
        }
        case DEFAULT_YOLOV7TINY: {
            _yolomodel = DEFAULT_YOLOV7TINY;
            break;
        }
        case CUSTOMIZED_YOLOV3TINY: {
            _yolomodel = CUSTOMIZED_YOLOV3TINY;
            break;
        }
        case CUSTOMIZED_YOLOV4TINY: {
            _yolomodel = CUSTOMIZED_YOLOV4TINY;
            break;
        }
        case CUSTOMIZED_YOLOV7TINY: {
            _yolomodel = CUSTOMIZED_YOLOV7TINY;
            break;
        }
        case NA_MODEL: {
            _yolomodel = NA_MODEL;
            break;
        }
        default:
            _yolomodel = NA_MODEL;
    }

    // SCRFD
    switch (facedetmodel) {
        case DEFAULT_SCRFD: {
            _scrfdmodel = DEFAULT_SCRFD;
            break;
        }
        case CUSTOMIZED_SCRFD: {
            _scrfdmodel = CUSTOMIZED_SCRFD;
            break;
        }
        case NA_MODEL: {
            _scrfdmodel = NA_MODEL;
            break;
        }
        default:
            _scrfdmodel = NA_MODEL;
    }

    // MOBILEFACENET
    switch (facerecogmodel) {
        case DEFAULT_MOBILEFACENET: {
            _mfnmodel = DEFAULT_MOBILEFACENET;
            break;
        }
        case CUSTOMIZED_MOBILEFACENET: {
            _mfnmodel = CUSTOMIZED_MOBILEFACENET;
            break;
        }
        case NA_MODEL: {
            _mfnmodel = NA_MODEL;
            break;
        }
        default:
            _mfnmodel = NA_MODEL;
    }

    // Audio Classification
    switch (audclassmodel) {
        case DEFAULT_YAMNET: {
            _yamnetmodel = DEFAULT_YAMNET;
            break;
        }
        case CUSTOMIZED_YAMNET: {
            _yamnetmodel = CUSTOMIZED_YAMNET;
            break;
        }
        case NA_MODEL: {
            _yamnetmodel = NA_MODEL;
            break;
        }
        default:
            _yamnetmodel = NA_MODEL;
    }

    // Image Classification
    switch (imgclassmodel) {
        case DEFAULT_IMGCLASS: {
            _imgclassmodel = DEFAULT_IMGCLASS;
            break;
        }
        case CUSTOMIZED_YAMNET: {
            _imgclassmodel = CUSTOMIZED_IMGCLASS;
            break;
        }
        case NA_MODEL: {
            _imgclassmodel = NA_MODEL;
            break;
        }
        default:
            _imgclassmodel = NA_MODEL;
    }
}


void NNModelSelection::modelSelect(unsigned char nntask, unsigned char objdetmodel, unsigned char facedetmodel, unsigned char facerecogmodel, unsigned char audclassmodel)
{
    nn_load_model_src_sel(ARDUINO_LOAD_MODEL);
    switch (nntask) {
        case OBJECT_DETECTION: {
            _nntask = OBJECT_DETECTION;
            break;
        }
        case FACE_DETECTION: {
            _nntask = FACE_DETECTION;
            break;
        }
        case FACE_RECOGNITION: {
            _nntask = FACE_RECOGNITION;
            break;
        }
        case AUDIO_CLASSIFICATION: {
            _nntask = AUDIO_CLASSIFICATION;
            break;
        }
    }

    // YOLO
    switch (objdetmodel) {
        case DEFAULT_YOLOV3TINY: {
            _yolomodel = DEFAULT_YOLOV3TINY;
            break;
        }
        case DEFAULT_YOLOV4TINY: {
            _yolomodel = DEFAULT_YOLOV4TINY;
            break;
        }
        case DEFAULT_YOLOV7TINY: {
            _yolomodel = DEFAULT_YOLOV7TINY;
            break;
        }
        case CUSTOMIZED_YOLOV3TINY: {
            _yolomodel = CUSTOMIZED_YOLOV3TINY;
            break;
        }
        case CUSTOMIZED_YOLOV4TINY: {
            _yolomodel = CUSTOMIZED_YOLOV4TINY;
            break;
        }
        case CUSTOMIZED_YOLOV7TINY: {
            _yolomodel = CUSTOMIZED_YOLOV7TINY;
            break;
        }
        case NA_MODEL: {
            _yolomodel = NA_MODEL;
            break;
        }
        default:
            _yolomodel = NA_MODEL;
    }

    // SCRFD
    switch (facedetmodel) {
        case DEFAULT_SCRFD: {
            _scrfdmodel = DEFAULT_SCRFD;
            break;
        }
        case CUSTOMIZED_SCRFD: {
            _scrfdmodel = CUSTOMIZED_SCRFD;
            break;
        }
        case NA_MODEL: {
            _scrfdmodel = NA_MODEL;
            break;
        }
        default:
            _scrfdmodel = NA_MODEL;
    }

    // MOBILEFACENET
    switch (facerecogmodel) {
        case DEFAULT_MOBILEFACENET: {
            _mfnmodel = DEFAULT_MOBILEFACENET;
            break;
        }
        case CUSTOMIZED_MOBILEFACENET: {
            _mfnmodel = CUSTOMIZED_MOBILEFACENET;
            break;
        }
        case NA_MODEL: {
            _mfnmodel = NA_MODEL;
            break;
        }
        default:
            _mfnmodel = NA_MODEL;
    }

    // Audio Classification
    switch (audclassmodel) {
        case DEFAULT_YAMNET: {
            _yamnetmodel = DEFAULT_YAMNET;
            break;
        }
        case CUSTOMIZED_YAMNET: {
            _yamnetmodel = CUSTOMIZED_YAMNET;
            break;
        }
        case NA_MODEL: {
            _yamnetmodel = NA_MODEL;
            break;
        }
        default:
            _yamnetmodel = NA_MODEL;
    }
}

void NNModelSelection::modelSelect(unsigned char nntask, unsigned char objdetmodel, unsigned char facedetmodel, unsigned char facerecogmodel)
{
    nn_load_model_src_sel(ARDUINO_LOAD_MODEL);
    switch (nntask) {
        case OBJECT_DETECTION: {
            _nntask = OBJECT_DETECTION;
            break;
        }
        case FACE_DETECTION: {
            _nntask = FACE_DETECTION;
            break;
        }
        case FACE_RECOGNITION: {
            _nntask = FACE_RECOGNITION;
            break;
        }
        case AUDIO_CLASSIFICATION: {
            _nntask = AUDIO_CLASSIFICATION;
            break;
        }
    }

    // YOLO
    switch (objdetmodel) {
        case DEFAULT_YOLOV3TINY: {
            _yolomodel = DEFAULT_YOLOV3TINY;
            break;
        }
        case DEFAULT_YOLOV4TINY: {
            _yolomodel = DEFAULT_YOLOV4TINY;
            break;
        }
        case DEFAULT_YOLOV7TINY: {
            _yolomodel = DEFAULT_YOLOV7TINY;
            break;
        }
        case CUSTOMIZED_YOLOV3TINY: {
            _yolomodel = CUSTOMIZED_YOLOV3TINY;
            break;
        }
        case CUSTOMIZED_YOLOV4TINY: {
            _yolomodel = CUSTOMIZED_YOLOV4TINY;
            break;
        }
        case CUSTOMIZED_YOLOV7TINY: {
            _yolomodel = CUSTOMIZED_YOLOV7TINY;
            break;
        }
        case NA_MODEL: {
            _yolomodel = NA_MODEL;
            break;
        }
        default:
            _yolomodel = NA_MODEL;
    }

    // SCRFD
    switch (facedetmodel) {
        case DEFAULT_SCRFD: {
            _scrfdmodel = DEFAULT_SCRFD;
            break;
        }
        case CUSTOMIZED_SCRFD: {
            _scrfdmodel = CUSTOMIZED_SCRFD;
            break;
        }
        case NA_MODEL: {
            _scrfdmodel = NA_MODEL;
            break;
        }
        default:
            _scrfdmodel = NA_MODEL;
    }

    // MOBILEFACENET
    switch (facerecogmodel) {
        case DEFAULT_MOBILEFACENET: {
            _mfnmodel = DEFAULT_MOBILEFACENET;
            break;
        }
        case CUSTOMIZED_MOBILEFACENET: {
            _mfnmodel = CUSTOMIZED_MOBILEFACENET;
            break;
        }
        case NA_MODEL: {
            _mfnmodel = NA_MODEL;
            break;
        }
        default:
            _mfnmodel = NA_MODEL;
    }
}
