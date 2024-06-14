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

class NNImageClassification: public NNModelSelection {
public:
    NNImageClassification(void);
    ~NNImageClassification(void);

    void configInputImageColor(int color);
    void configVideo(VideoSetting &config);
    void configRegionOfInterest(int xmin, int xmax, int ymin, int ymax);
    void begin(void);
    void end(void);

    void setResultCallback(void (*ic_callback)(void));

    int classID(void);
    float score(void);

private:
    static void ICResultCallback(void *p, void *img_param);
    static void (*IC_user_CB)(void);

    static float xscale;
    static float xoffset;
    static float yscale;
    static float yoffset;
    static uint8_t use_roi;

    static int _classID;
    static float _prob;

    nn_data_param_t roi_nn = {0};
};
#endif
