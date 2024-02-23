#ifndef __NN_IMAGECLASSIFICATION_H__
#define __NN_IMAGECLASSIFICATION_H__

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

#define MAX_OBJ_DET 7

class ImageClassificationResult {
    friend class NNImageClassification;
public:


private:
};

class NNImageClassification: public NNModelSelection {
public:
    NNImageClassification(void);
    ~NNImageClassification(void);

    void configVideo(VideoSetting &config);
    void configRegionOfInterest(int xmin, int xmax, int ymin, int ymax);
    void begin(void);
    void end(void);

private:
    static void ICResultCallback(void *p);

    // static void (*IC_user_CB)(std::vector<ImageClassificationResult>);

    static float xscale;
    static float xoffset;
    static float yscale;
    static float yoffset;
    static uint8_t use_roi;

    nn_data_param_t roi_nn = {0};
};
#endif
