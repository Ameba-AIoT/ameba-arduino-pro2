#ifndef __RTSP_H__
#define __RTSP_H__

#include "VideoStream.h"
#include "AudioStream.h"

class RTSP: public MMFModule {
public:
    RTSP(void);
    ~RTSP(void);

    void configVideo(VideoSetting& config);
    void configAudio(AudioSetting& config, Audio_Codec_T codec);
    void begin(void);
    void end(void);

    int getPort(void);
    void printInfo(void);

private:
};

#endif
