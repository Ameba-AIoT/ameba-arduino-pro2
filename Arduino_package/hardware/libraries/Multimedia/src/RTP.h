#ifndef __RTP_H__
#define __RTP_H__

#include "VideoStream.h"
#include "AudioStream.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmf2_module.h"

#ifdef __cplusplus
}
#endif

// Redefine here since #include "module_rtp.h" causes C/C++ linkage error

#define CMD_RTP_SET_PARAMS      MM_MODULE_CMD(0x00)
#define CMD_RTP_GET_PARAMS      MM_MODULE_CMD(0x01)
#define CMD_RTP_STREAMING       MM_MODULE_CMD(0x02)
#define CMD_RTP_APPLY           MM_MODULE_CMD(0x20)

typedef struct rtp_param_s {
    uint32_t valid_pt;
    uint32_t port;
    uint32_t frame_size;
    uint32_t cache_depth;
} rtp_params_t;

class RTP:public MMFModule {
    public:
        RTP(void);
        ~RTP(void);

        void configPort(uint16_t port);
        void begin(void);
        void end(void);

        uint16_t getPort(void);

    private:
        rtp_params_t _rtpParams = {
            .valid_pt = 0xFFFFFFFF,
            .port = 5004,
            .frame_size = 1500,
            .cache_depth = 6,
        };
};

#endif
