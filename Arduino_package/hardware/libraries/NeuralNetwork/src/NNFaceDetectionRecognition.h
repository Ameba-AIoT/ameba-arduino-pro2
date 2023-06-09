#ifndef __NN_FACEDETECTIONRECOGNITION_H__
#define __NN_FACEDETECTIONRECOGNITION_H__

#include "VideoStream.h"
#include "NNModelSelection.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "module_vipnn.h"
#include "module_facerecog.h"

#ifdef __cplusplus
}
#endif

#undef min
#undef max
#include <vector>

class FaceRecognitionResult {
    friend class NNFaceDetectionRecognition;

    public:
        const char* name(void);
        float xMin(void);
        float xMax(void);
        float yMin(void);
        float yMax(void);

    private:
        char result_name[32] = {0};
        frc_bbox_t result = {0};
};

class NNFaceDetectionRecognition:public NNModelSelection {
    public:
        NNFaceDetectionRecognition(void);
        ~NNFaceDetectionRecognition(void);

        void configVideo(VideoSetting& config);
        void begin(void);
        void end(void);

        void registerFace(String name);
        void registerFace(const char* name);
        void exitRegisterMode(void);
        void resetRegisteredFace(void);
        void backupRegisteredFace(void);
        void restoreRegisteredFace(void);
        void setThreshold(uint8_t threshold);

        void setResultCallback(void (*fr_callback)(std::vector<FaceRecognitionResult>));
        uint16_t getResultCount(void);
        FaceRecognitionResult getResult(uint16_t index);
        std::vector<FaceRecognitionResult> getResult(void);

    private:
        static void FRResultCallback(void *p, void *img_param);

        static std::vector<FaceRecognitionResult> face_result_vector;
        static void (*FR_user_CB)(std::vector<FaceRecognitionResult>);

        mm_context_t* facerecog_ctx = NULL;
        mm_context_t* mbfacenet_ctx = NULL;
        void* facerecog_siso_ctx = NULL;
        void* mbfacenet_siso_ctx = NULL;
        nn_data_param_t roi_nn = {0};
        nn_data_param_t fr_param = {0};
};

#endif
