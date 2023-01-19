#ifndef __MOTIONDETECTION_H__
#define __MOTIONDETECTION_H__

#include "md_api.h"
#include "VideoStream.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "osd_render.h"

#ifdef __cplusplus
}
#endif

class MotionDetection:public MMFModule {
    public:
        MotionDetection(uint8_t row = 16, uint8_t col = 16);
        ~MotionDetection(void);

        void configResolution(uint8_t row = 16, uint8_t col = 16);
        void configVideo(VideoSetting& config);
        void begin(void);
        void end(void);
        void setTriggerBlockCount(uint16_t count);
        void setDetectionMask(char * mask);

        char* getResult(void);
        void setResultCallback(void (*md_callback)(char*));
        uint8_t rows(void);
        uint8_t cols(void);

    private:
//        static void mdPostProcess(void *md_result);
        md_param_t md_param = {0};
        motion_detect_threshold_t md_thr = {2,3};
        char md_result[MD_MAX_COL * MD_MAX_ROW] = {0};
        void (*md_ResultCB)(char*) = NULL;
};

#endif
