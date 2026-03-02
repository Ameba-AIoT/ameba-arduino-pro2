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

#define MAX_META_DATA_SIZE (1024)

class ImageClassificationResult {
    friend class NNImageClassification;
public:
    int classID(void);
    int score(void);

private:
    classification_res_t result = {0};
};

class NNImageClassification: public NNModelSelection {
public:
    NNImageClassification(void);
    ~NNImageClassification(void);

    void configInputImageColor(int color);
    void configVideo(VideoSetting &config);
    void configRegionOfInterest(int xmin, int xmax, int ymin, int ymax);
    void begin(void);
    void end(void);

    char *getClassNameFromMeta(char *meta_data, int class_id, int prob);
    char *parseModelMetaData(mm_context_t *vipnn_ctx);
    void useModelMetaData(int use_meta_data);

    void setResultCallback(void (*ic_callback)(std::vector<ImageClassificationResult>));
    uint16_t getResultCount(void);
    ImageClassificationResult getResult(uint16_t index);
    std::vector<ImageClassificationResult> getResult(void);
    static char *model_meta_data;    // declaration only

private:
    static void ICResultCallback(void *p, void *img_param);
    static std::vector<ImageClassificationResult> img_class_result_vector;
    static void (*IC_user_CB)(std::vector<ImageClassificationResult>);

    static float xscale;
    static float xoffset;
    static float yscale;
    static float yoffset;
    static uint8_t use_roi;
    static int _useMetadata;

    nn_data_param_t roi_nn = {0};
};
#endif
