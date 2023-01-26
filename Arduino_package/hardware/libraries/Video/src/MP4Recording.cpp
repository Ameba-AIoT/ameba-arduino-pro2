#include <Arduino.h>

#include "MP4Recording.h"
#include "mp4_drv.h"

MP4Recording::MP4Recording(void) {
    // Default video parameters
    mp4Params.width = 1920;
    mp4Params.height = 1080;
    mp4Params.fps = 30;
    mp4Params.gop = 30;

    // Default audio parameters
    mp4Params.sample_rate = 8000;
    mp4Params.channel = 1;
    mp4Params.mp4_audio_format = AUDIO_AAC;

    // MP4 recording parameters
    mp4Params.record_length = 60; //seconds
    mp4Params.record_type = STORAGE_ALL;
    mp4Params.record_file_num = 1;
    memset(mp4Params.record_file_name, 0, sizeof(mp4Params.record_file_name));
    strncpy(mp4Params.record_file_name, "AmebaPro_recording", sizeof(mp4Params.record_file_name));
    mp4Params.fatfs_buf_size = 256 * 1024; // 32kb multiple
}

MP4Recording::~MP4Recording(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (mp4Deinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("MP4 deinit failed\r\n");
    }
}

void MP4Recording::configVideo(VideoSetting& config) {
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mp4Init();
    }
    if (_p_mmf_context == NULL) {
        printf("MP4 Init failed\r\n");
        return;
    }

    mp4Params.width = config._w;
    mp4Params.height = config._h;
    mp4Params.fps = config._fps;
    mp4Params.gop = config._fps;
}

void MP4Recording::configAudio(void) {
    // RTSPInit if not previously done so
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mp4Init();
    }
    if (_p_mmf_context == NULL) {
        printf("MP4 Init failed\r\n");
        return;
    }
}

void MP4Recording::begin  (void) {
    if (_p_mmf_context == NULL) {
        printf("Need MP4 init first\r\n");
        return;
    }
    mp4SetParams(_p_mmf_context->priv, &mp4Params);
    mp4SetLoopMode(_p_mmf_context->priv, loopEnable);
    mp4RecordingStart(_p_mmf_context->priv, &mp4Params);
}

void MP4Recording::end(void) {
    if (_p_mmf_context == NULL) {
        printf("Need MP4 init first\r\n");
        return;
    }
    mp4RecordingStop(_p_mmf_context->priv);
}

void MP4Recording::setRecordingFileName(const char* filename) {
    memset(mp4Params.record_file_name, 0, sizeof(mp4Params.record_file_name));
    strncpy(mp4Params.record_file_name, filename, sizeof(mp4Params.record_file_name));
}

void MP4Recording::setRecordingFileName(String filename) {
    setRecordingFileName(filename.c_str());
}

void MP4Recording::setRecordingDuration(uint32_t secs) {
    mp4Params.record_length = secs;
}

void MP4Recording::setRecordingFileCount(uint32_t count) {
    mp4Params.record_file_num = count;
}

void MP4Recording::setLoopRecording(int enable) {
    loopEnable = enable;
}

void MP4Recording::setRecordingDataType(uint8_t type) {
    if (type <= STORAGE_AUDIO) {
        mp4Params.record_type = type;
    }
}

String MP4Recording::getRecordingFileName(void) {
    return String(mp4Params.record_file_name);
}

uint32_t MP4Recording::getRecordingDuration(void) {
    return (mp4Params.record_length);
}

uint32_t MP4Recording::getRecordingFileCount(void) {
    return (mp4Params.record_file_num);
}

uint8_t MP4Recording::getRecordingState(void) {
    if (_p_mmf_context == NULL) {
        printf("Need MP4 init first\r\n");
        return 0;
    }
    return mp4RecordingState(_p_mmf_context->priv);
}

void MP4Recording::printInfo(void) {
    printf("Recording file name: %s\r\n", getRecordingFileName().c_str());
    printf("Recording duration: %d seconds\r\n", getRecordingDuration());
    printf("File count: %d\r\n", getRecordingFileCount());
    printf("\r\n");
}
