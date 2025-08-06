#ifndef __DEMUXER_H__
#define __DEMUXER_H__

#include "VideoStream.h"

// STREAM TYPE
#define STREAM_AUDIO 0x01
#define STREAM_VIDEO 0x10
#define STREAM_ALL   0x11

// LOOP MODE
#define NO_LOOP 0
#define LOOP    1

#define MEDIA_STREAM_TYPE STREAM_ALL

class Demuxer: public MMFModule {
public:
    Demuxer(void);
    ~Demuxer(void);

    void begin(const char* MP4FileName, uint32_t loopMode, uint32_t startTime = 0);
    void pause();
    void resume();
    void end(void);

private:
};

#endif
