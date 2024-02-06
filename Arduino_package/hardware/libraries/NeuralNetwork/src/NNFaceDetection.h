#ifndef __NN_FACEDETECTION_H__
#define __NN_FACEDETECTION_H__

#include "VideoStream.h"
#include "NNModelSelection.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "module_vipnn.h"

#ifdef __cplusplus
}
#endif

#undef min
#undef max
#include <vector>

#define MAX_FACE_DET 10

class FaceDetectionResult {
    friend class NNFaceDetection;

public:
    const char *name(void);
    int score(void);
    float xMin(void);
    float xMax(void);
    float yMin(void);
    float yMax(void);
    float xFeature(uint8_t index);
    float yFeature(uint8_t index);

private:
    detobj_t result = {0};
    landmark_t landmark = {0};
};

class NNFaceDetection: public NNModelSelection {
public:
    NNFaceDetection(void);
    ~NNFaceDetection(void);

    void configVideo(VideoSetting &config);
    void begin(void);
    void end(void);

    void setResultCallback(void (*fd_callback)(std::vector<FaceDetectionResult>));
    uint16_t getResultCount(void);
    FaceDetectionResult getResult(uint16_t index);
    std::vector<FaceDetectionResult> getResult(void);

private:
    static void FDResultCallback(void *p, void *img_param);

    static std::vector<FaceDetectionResult> face_result_vector;
    static void (*FD_user_CB)(std::vector<FaceDetectionResult>);

    nn_data_param_t roi_nn = {0};
};

#endif
