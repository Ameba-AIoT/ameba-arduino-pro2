#ifndef __RTSP_H__
#define __RTSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rtsp_drv.h"
#include "avcodec.h"

#ifdef __cplusplus
}
#endif

#include "video.h"

class RTSPClass   {

    public:
        RTSPClass(void);
        ~RTSPClass(void);

        void init(CameraSetting& obj);
        void open(void);
        void close(void);
        void deinit(void);
        mm_context_t *getIO(void);
        int enableAudio(void);
        int getPort(void);

    private:
        mm_context_t *rtspData;
};

#endif
