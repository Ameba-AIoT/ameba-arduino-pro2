#ifndef MI48_ENCODER_H
#define MI48_ENCODER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void *mi48_stream_open(uint16_t width, uint16_t height, uint8_t fps, uint8_t channel, uint32_t bps, uint32_t type, uint32_t resolution, uint32_t ext_fmt);
int mi48_stream_encode(uint8_t *nv12);

#ifdef __cplusplus
}
#endif
#endif
