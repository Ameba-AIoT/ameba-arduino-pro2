#include <Arduino.h>

#include "MP4Recording.h"
#include "mp4_drv.h"

MP4Recording::MP4Recording(void)
{
    // Default video parameters
    mp4Params.width = 1920;
    mp4Params.height = 1080;
    mp4Params.fps = 30;
    mp4Params.gop = 30;

    // Default audio parameters
    mp4Params.sample_rate = 8000;
    mp4Params.channel = 1;
    mp4Params.mp4_audio_format = AUDIO_AAC;
    mp4Params.mp4_audio_duration = 20;    // Required for G711 audio

    // MP4 recording parameters
    mp4Params.record_length = 60;    // seconds
    mp4Params.record_type = STORAGE_ALL;
    mp4Params.record_file_num = 1;
    memset(mp4Params.record_file_name, 0, sizeof(mp4Params.record_file_name));
    strncpy(mp4Params.record_file_name, "AmebaPro_recording", sizeof(mp4Params.record_file_name));
    mp4Params.fatfs_buf_size = 256 * 1024;    // 32kb multiple
}

MP4Recording::~MP4Recording(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (mp4Deinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] MP4 deinit failed\n");
    }
}

void MP4Recording::configVideo(VideoSetting& config)
{
    if (config._encoder == VIDEO_JPEG) {
        printf("\r\n[ERROR] MP4 Recording does not support MJPEG format.\n");
        return;
    }
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mp4Init();
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] MP4 Init failed\n");
        return;
    }

    mp4Params.width = config._w;
    mp4Params.height = config._h;
    mp4Params.fps = config._fps;
    mp4Params.gop = config._fps;
}

void MP4Recording::configAudio(AudioSetting& config, Audio_Codec_T codec)
{
    if ((codec == CODEC_G711_PCMU) || (codec == CODEC_G711_PCMA)) {
        printf("\r\n[ERROR] MP4 Recording only accepts AAC codec\n");
        // Unable to only record G711 audio without video, 23/3/2023
        return;
    }
    if (_p_mmf_context == NULL) {
        _p_mmf_context = mp4Init();
    }
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] MP4 Init failed\n");
        return;
    }

    mp4Params.sample_rate = config._sampleRate;
    mp4Params.channel = config._audioParams.channel;
    mp4Params.mp4_audio_format = AUDIO_AAC;
}

void MP4Recording::begin(void)
{
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] Need MP4 init first\n");
        return;
    }
    mp4SetParams(_p_mmf_context->priv, &mp4Params);
    mp4SetLoopMode(_p_mmf_context->priv, loopEnable);
    mp4RecordingStart(_p_mmf_context->priv, &mp4Params);
}

void MP4Recording::end(void)
{
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] Need MP4 init first\n");
        return;
    }
    mp4RecordingStop(_p_mmf_context->priv);
}

void MP4Recording::setRecordingFileName(const char* filename)
{
    memset(mp4Params.record_file_name, 0, sizeof(mp4Params.record_file_name));
    strncpy(mp4Params.record_file_name, filename, sizeof(mp4Params.record_file_name));
}

void MP4Recording::setRecordingFileName(String filename)
{
    setRecordingFileName(filename.c_str());
}

void MP4Recording::setRecordingDuration(uint32_t secs)
{
    mp4Params.record_length = secs;
}

void MP4Recording::setRecordingFileCount(uint32_t count)
{
    mp4Params.record_file_num = count;
}

void MP4Recording::setLoopRecording(int enable)
{
    loopEnable = enable;
}

void MP4Recording::setRecordingDataType(uint8_t type)
{
    if (type <= STORAGE_AUDIO) {
        mp4Params.record_type = type;
    }
}

String MP4Recording::getRecordingFileName(void)
{
    return String(mp4Params.record_file_name);
}

uint32_t MP4Recording::getRecordingDuration(void)
{
    return (mp4Params.record_length);
}

uint32_t MP4Recording::getRecordingFileCount(void)
{
    return (mp4Params.record_file_num);
}

uint8_t MP4Recording::getRecordingState(void)
{
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] Need MP4 init first\n");
        return 0;
    }
    return mp4RecordingState(_p_mmf_context->priv);
}

void MP4Recording::printInfo(void)
{
    printf("\r\n[INFO] Recording file name: %s\n", getRecordingFileName().c_str());
    printf("\r\n[INFO] Recording duration: %ld seconds\n", getRecordingDuration());
    printf("\r\n[INFO] File count: %ld\n", getRecordingFileCount());
}
