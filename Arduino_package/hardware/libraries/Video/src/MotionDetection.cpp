#include <Arduino.h>
#include "MotionDetection.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "md_drv.h"

#ifdef __cplusplus
}
#endif

MotionDetection::MotionDetection(uint8_t row, uint8_t col) {
    md_param.image_width = 0;
    md_param.image_height = 0;
    md_param.md_row = 0;
    md_param.md_col = 0;
    configResolution(row, col);
}

MotionDetection::~MotionDetection(void) {
    end();
}

void MotionDetection::configResolution(uint8_t row, uint8_t col) {
    if (row > MD_MAX_ROW) row = MD_MAX_ROW;
    if (col > MD_MAX_COL) col = MD_MAX_COL;
    if (row == 0) row = 1;
    if (col == 0) col = 1;

    md_param.md_row = row;
    md_param.md_col = col;
}

void MotionDetection::configVideo(VideoSetting& config) {
    md_param.image_width = config._w;
    md_param.image_height = config._h;
}

void MotionDetection::begin(void) {
    if (_p_mmf_context == NULL) {
        _p_mmf_context = MDInit();
    }
    if (_p_mmf_context == NULL) {
        printf("MD init failed\r\n");
        return;
    }

    setMDParams(_p_mmf_context->priv, &md_param);
//    setMDThreshold(_p_mmf_context->priv, &md_thr);
    setMDDisppost(_p_mmf_context->priv, md_ResultCB);
}

void MotionDetection::end(void) {
    if (_p_mmf_context == NULL) {
        return;
    }
    setMDDisppost(_p_mmf_context->priv, NULL);
    if (MDDeinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("MD deinit failed\r\n");
    }
}

void MotionDetection::setTriggerBlockCount(uint16_t count) {
    if (_p_mmf_context == NULL) {
        return;
    }
    setMDTrigBlock(_p_mmf_context->priv, count);
}

void MotionDetection::setDetectionMask(char* mask) {
    if (_p_mmf_context == NULL) {
        return;
    }
    setMDMask(_p_mmf_context->priv, mask);
}

char* MotionDetection::getResult(void) {
    getMDResult(_p_mmf_context->priv, md_result);
    return md_result;
}

void MotionDetection::setResultCallback(void (*md_callback)(char*)) {
    md_ResultCB = md_callback;
    if (_p_mmf_context == NULL) {
        return;
    }
    setMDDisppost(_p_mmf_context->priv, md_ResultCB);
}

uint8_t MotionDetection::rows(void) {
    return md_param.md_row;
}

uint8_t MotionDetection::cols(void) {
    return md_param.md_col;
}