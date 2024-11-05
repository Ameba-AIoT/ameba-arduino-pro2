#ifndef HELIX_MP3_DRV_H
#define HELIX_MP3_DRV_H
#include <stdint.h>
#include <string.h>
#include <stdio.h>
void audio_play_binary_array(uint8_t *srcbuf, uint32_t len);

void initialize_audio(int sample_rate);
void audio_play_pcm(int16_t *buf, uint32_t len);
void audio_rx_complete(uint32_t arg, uint8_t *pbuf);
void audio_tx_complete(uint32_t arg, uint8_t *pbuf);

#endif
