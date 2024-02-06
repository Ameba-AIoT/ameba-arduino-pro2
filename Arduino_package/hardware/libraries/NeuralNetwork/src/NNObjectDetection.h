#ifndef __NN_OBJECTDETECTION_H__
#define __NN_OBJECTDETECTION_H__

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

#define MAX_OBJ_DET 14

class ObjectDetectionResult {
    friend class NNObjectDetection;
public:
    int type(void);
    const char *name(void);
    int score(void);
    float xMin(void);
    float xMax(void);
    float yMin(void);
    float yMax(void);

private:
    detobj_t result = {0};
};

class NNObjectDetection: public NNModelSelection {
public:
    NNObjectDetection(void);
    ~NNObjectDetection(void);

    void configVideo(VideoSetting &config);
    void configRegionOfInterest(int xmin, int xmax, int ymin, int ymax);
    void configThreshold(float confidence_threshold, float nms_threshold);
    void begin(void);
    void end(void);

    void setResultCallback(void (*od_callback)(std::vector<ObjectDetectionResult>));
    uint16_t getResultCount(void);
    ObjectDetectionResult getResult(uint16_t index);
    std::vector<ObjectDetectionResult> getResult(void);

private:
    static void ODResultCallback(void *p, void *img_param);

    static std::vector<ObjectDetectionResult> object_result_vector;
    static void (*OD_user_CB)(std::vector<ObjectDetectionResult>);

    static float xscale;
    static float xoffset;
    static float yscale;
    static float yoffset;
    static uint8_t use_roi;

    nn_data_param_t roi_nn = {0};
    float od_confidence_thresh = 0.5;
    float od_nms_thresh = 0.3;
};
#endif
