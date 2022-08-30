#include <Arduino.h>

#include "MP4Recording.h"
#include "mp4_drv.h"

#define DEBUG 0

#if DEBUG
#define CAMDBG(fmt, args...) \
    do {printf("\r\nFunc-[%s]@Line-%d: \r\n" fmt "\r\n", __func__, __LINE__, ## args); } while (0);
#else
#define CAMDBG(fmt, args...)
#endif

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
        CAMDBG("MP4 deinit failed\r\n");
    }
}

/**
  * @brief  Configure MP4 module by setting up MP4 video paramters
  * @param  config : VideoSetting object
  * @retval none
  */
void MP4Recording::configVideo(VideoSetting& config) {
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mp4Init();
    }
    if (_p_mmf_context == NULL) {
        CAMDBG("MP4 Init failed\r\n");
        return;
    }

    mp4Params.width = config._w;
    mp4Params.height = config._h;
    mp4Params.fps = config._fps;
    mp4Params.gop = config._fps;
}

/**
  * @brief  Configure MP4 module by setting up MP4 audio paramters
  * @param  config : AudioSetting object
  * @retval none
  */
void MP4Recording::configAudio(void) {
    // RTSPInit if not previously done so
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mp4Init();
    }
    if (_p_mmf_context == NULL) {
        CAMDBG("MP4 Init failed\r\n");
        return;
    }
}

/**
  * @brief  Start MP4 module recording data to SD card
  * @param  none
  * @retval none
  */
void MP4Recording::begin  (void) {
    if (_p_mmf_context == NULL) {
        CAMDBG("Need MP4 init first\r\n");
        return;
    }
    mp4SetParams(_p_mmf_context->priv, &mp4Params);
    mp4SetLoopMode(_p_mmf_context->priv, loopEnable);
    mp4RecordingStart(_p_mmf_context->priv, &mp4Params);
}

/**
  * @brief  Stop MP4 module recording data to SD card
  * @param  none
  * @retval none
  */
void MP4Recording::end(void) {
    if (_p_mmf_context == NULL) {
        CAMDBG("Need MP4 init first\r\n");
        return;
    }
    mp4RecordingStop(_p_mmf_context->priv);
}

/**
  * @brief  Set filename of recordings saved to SD card
  * @param  filename : pointer to character array containing filename
  * @retval none
  */
void MP4Recording::setRecordingFileName(const char* filename) {
    memset(mp4Params.record_file_name, 0, sizeof(mp4Params.record_file_name));
    strncpy(mp4Params.record_file_name, filename, sizeof(mp4Params.record_file_name));
}

/**
  * @brief  Set filename of recordings saved to SD card
  * @param  filename : String class object containing filename
  * @retval none
  */
void MP4Recording::setRecordingFileName(String filename) {
    setRecordingFileName(filename.c_str());
}

/**
  * @brief  Set maximum recording duration of each file saved to SD card
  * @param  secs : maximum recording duration expressed in seconds
  * @retval none
  */
void MP4Recording::setRecordingDuration(uint32_t secs) {
    mp4Params.record_length = secs;
}

/**
  * @brief  Set total number of recordings saved to SD card, filenames will have a number appended
  * @param  count : total number of recording files
  * @retval none
  */
void MP4Recording::setRecordingFileCount(uint32_t count) {
    mp4Params.record_file_num = count;
}

/**
  * @brief  Enable loop recording, oldest file will be overwritten once total file count is reached
  * @param  enable : integer, 1 to enable, 0 to disable
  * @retval none
  */
void MP4Recording::setLoopRecording(int enable) {
    loopEnable = enable;
}

/**
  * @brief  Select data streams to record, 0 for video and audio, 1 for video only, 2 for audio only
  * @param  type : integer from 0 to 2 inclusive
  * @retval none
  */
void MP4Recording::setRecordingDataType(uint8_t type) {
    if (type <= STORAGE_AUDIO) {
        mp4Params.record_type = type;
    }
}

/**
  * @brief  Get filename of recordings
  * @param  none
  * @retval String class object containing filename
  */
String MP4Recording::getRecordingFileName(void) {
    return String(mp4Params.record_file_name);
}

/**
  * @brief  Get maximum recording duration of each file saved to SD card
  * @param  none
  * @retval maximum recording duration expressed in seconds
  */
uint32_t MP4Recording::getRecordingDuration(void) {
    return (mp4Params.record_length);
}

/**
  * @brief  Set total number of recordings saved to SD card, filenames will have a number appended
  * @param  count : total number of recording files
  * @retval none
  */
uint32_t MP4Recording::getRecordingFileCount(void) {
    return (mp4Params.record_file_num);
}

/**
  * @brief  Select data streams to record, 0 for video and audio, 1 for video only, 2 for audio only
  * @param  type : integer from 0 to 2 inclusive
  * @retval none
  */
uint8_t MP4Recording::getRecordingState(void) {
    if (_p_mmf_context == NULL) {
        CAMDBG("Need MP4 init first\r\n");
        return 0;
    }
    return mp4RecordingState(_p_mmf_context->priv);
}

/**
  * @brief  Print out current configuration of MP4 recording.
  * @param  none
  * @retval none
  */
void MP4Recording::printInfo(void) {
    printf("Recording file name: %s\r\n", getRecordingFileName().c_str());
    printf("Recording duration: %d seconds\r\n", getRecordingDuration());
    printf("File count: %d\r\n", getRecordingFileCount());
    printf("\r\n");
}
