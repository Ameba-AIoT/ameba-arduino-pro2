#include "mp4_drv.h"
#include "mmf2_module.h"
#include "module_mp4.h"
#include "mp4_muxer.h"

// MP4 module init
mm_context_t *mp4Init(void)
{
    return mm_module_open(&mp4_module);
}

// M4 module deinit
mm_context_t *mp4Deinit(mm_context_t *p)
{
    return mm_module_close(p);
}

// Set MP4 module parameters
int mp4SetParams(void *p, mp4_params_t *params)
{
    return mp4_control(p, CMD_MP4_SET_PARAMS, (int)params);
}

// Enable MP4 module loop recording mode
int mp4SetLoopMode(void *p, int enable)
{
    if (enable) {
        return mp4_control(p, CMD_MP4_LOOP_MODE, 1);
    } else {
        return mp4_control(p, CMD_MP4_LOOP_MODE, 0);
    }
}

// Start MP4 module recording
int mp4RecordingStart(void *p, mp4_params_t *params)
{
    return mp4_control(p, CMD_MP4_START, params->record_file_num);
}

// Stop MP4 module recording
int mp4RecordingStop(void *p)
{
    return mp4_control(p, CMD_MP4_STOP, (int)NULL);
}

// Check MP4 module recording state
uint8_t mp4RecordingState(void *p)
{
    uint8_t state;
    mp4_control(p, CMD_MP4_GET_STATUS, (int)(&state));
    return state;
}
