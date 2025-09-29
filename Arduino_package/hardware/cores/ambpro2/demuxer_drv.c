#include "Arduino.h"

#include "demuxer_drv.h"
#include "mmf2_module.h"
#include "module_demuxer.h"

static demuxer_params_t demuxer_params = {
    .start_time = 0,
    .stream_type = 0,
    .loop_mode = 0,    // 0 no loop, 1 loop

    .record_file_name = "",
    .mem_total_size = 0,
    .mem_block_size = 0};

mm_context_t *demuxerInit(void)
{
    return mm_module_open(&demuxer_module);
}

mm_context_t *demuxerDeinit(mm_context_t *p)
{
    return mm_module_close(p);
}

void demuxerOpen(mm_context_t *p, const char *file_name, uint8_t stream_type, uint32_t loop_mode, uint32_t start_time)
{
    demuxer_params.start_time = start_time;
    demuxer_params.stream_type = stream_type;
    demuxer_params.loop_mode = loop_mode;

    // Copy the file name into the structure
    strncpy(demuxer_params.record_file_name, file_name, sizeof(demuxer_params.record_file_name) - 1);
    demuxer_params.record_file_name[sizeof(demuxer_params.record_file_name) - 1] = '\0';

    demuxer_params.mem_total_size = 1 * 1024 * 1024;
    demuxer_params.mem_block_size = 128;

    mm_module_ctrl(p, CMD_DEMUXER_SET_PARAMS, (int)&demuxer_params);
    mm_module_ctrl(p, MM_CMD_SET_QUEUE_LEN, 12);
    mm_module_ctrl(p, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
    mm_module_ctrl(p, CMD_DEMUXER_INIT_MEM_POOL, 0);
    mm_module_ctrl(p, CMD_DEMUXER_OPEN, 0);

    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] DEMUXER OPENED\n");
}

void demuxerStart(mm_context_t *p)
{
    mm_module_ctrl(p, CMD_DEMUXER_STREAM_START, 0);
}

void demuxerPause(mm_context_t *p)
{
    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Set Pause for the MP4\n");
    mm_module_ctrl(p, CMD_DEMUXER_STREAM_PAUSE, 0);
}

void demuxerResume(mm_context_t *p)
{
    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Set RESUME for the MP4\n");
    mm_module_ctrl(p, CMD_DEMUXER_STREAM_RESUME, 0);
}
