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

class RTSPClass {
    public:
        RTSPClass(void);
        ~RTSPClass(void);

        void init(void);
        void open(void);
        void close(void);
        void deInit(void);
        mm_context_t *getIO(void);

        int ch_idx = 0;

        uint32_t video_type = AVMEDIA_TYPE_VIDEO;
        uint32_t fps = 30;
        uint32_t bps = 2*1024*1024;
        uint32_t VC = AV_CODEC_ID_H264;
        
        
    private:
        mm_context_t *rtspData;
        

};



#endif



