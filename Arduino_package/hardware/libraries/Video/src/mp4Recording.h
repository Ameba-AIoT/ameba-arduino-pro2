#ifndef __MP4_RECORDING_H__
#define __MP4_RECORDING_H__

#include "mmf2_module.h"
#include "mp4_muxer.h"

#include "video.h"
#include "audio.h"

class MP4Recording:public MMFModule {
    public:
        MP4Recording(void);
        ~MP4Recording(void);

        void configVideo(VideoSetting& config);
        void configAudio(void);
        void begin(void);
        void end(void);

        void setRecordingFileName(const char* filename);
        void setRecordingFileName(String filename);
        void setRecordingDuration(uint32_t secs);
        void setRecordingFileCount(uint32_t count);
        void setLoopRecording(int enable);
        void setRecordingDataType(uint8_t type);

        String getRecordingFileName();
        uint32_t getRecordingDuration();
        uint32_t getRecordingFileCount();
        uint8_t getRecordingState(void);

         void printInfo(void);

    private:
        int loopEnable = 0;
        mp4_params_t mp4Params;
};

#endif
