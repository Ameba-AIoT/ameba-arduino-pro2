/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
* @file     a2dp_sbc_codec_entity.h
* @brief    Source file for application service.
* @details  main function.
* @author   sherman
* @date     2021-06-10
* @version  v1.0
* *************************************************************************************
*/
#ifndef _A2DP_SBC_CODEC_ENTITY_H_
#define _A2DP_SBC_CODEC_ENTITY_H_

#include "osdep_service.h"
#include "oi_status.h"
#include "oi_codec_sbc.h"
#include "audio_codec_wrapper.h"

#define RTK_A2DP_SINK 0x01

#define SBC_MAX_CHANNELS 2
#define SBC_MAX_BANDS 8
#define SBC_MAX_BLOCKS 16
#define SBC_FS 120          /* SBC Frame Size */
#define SBC_N 512           /* 32ms - Window Length for pattern matching */
#define SBC_M 64            /* 4ms - Template for matching */
#define SBC_LHIST (SBC_N+SBC_FS-1)  /* Length of history buffer required */
#define SBC_RT 36           /* SBC Reconvergence Time (samples) */
#define SBC_OLAL 16         /* OverLap-Add Length (samples) */
#define mSBC_SYNCWORD 0xad
#define SBC_SYNCWORD 0x9c
#define DECODER_DATA_SIZE (SBC_MAX_CHANNELS*SBC_MAX_BLOCKS*SBC_MAX_BANDS * 4 + SBC_CODEC_MIN_FILTER_BUFFERS*SBC_MAX_BANDS*SBC_MAX_CHANNELS * 2)

typedef enum {
	SBC_MODE_STANDARD = 0,
	SBC_MODE_mSBC
} sbc_mode_t;

/* PLC State Information */
typedef struct sbc_plc_state {
	int16_t hist[SBC_LHIST + SBC_FS + SBC_RT + SBC_OLAL];
	int16_t bestlag;
	int     nbf;

	// summary of processed good and bad frames
	int good_frames_nr;
	int bad_frames_nr;
	int frame_count;
	int max_consecutive_bad_frames_nr;
} sbc_plc_state_t;

typedef struct {
	void *context;
	// private
	void *decoder_state;
	sbc_plc_state_t plc_state;
	sbc_mode_t mode;

	// summary of processed good, bad and zero frames
	int good_frames_nr;
	int bad_frames_nr;
	int zero_frames_nr;
} sbc_decoder_state_t;

typedef struct {
	OI_UINT32 bytes_in_frame_buffer;
	OI_CODEC_SBC_DECODER_CONTEXT decoder_context;
	int16_t   *ppcm_plc_data;
	int16_t   *ppcm_data;
	uint32_t  pcm_bytes;
	OI_UINT32 decoder_data[(DECODER_DATA_SIZE + 3) / 4];
	int       first_good_frame_found;
	int       h2_sequence_nr;
	uint16_t  msbc_bad_bytes;
} bludroid_decoder_state_t;

struct sbc_pcm_data {
	struct list_head list;
	int16_t pcm_data[SBC_MAX_CHANNELS * SBC_MAX_BANDS * SBC_MAX_BLOCKS];
};

typedef struct {
	uint8_t fragmentation;
	uint8_t starting_packet; // of fragmented SBC frame
	uint8_t last_packet;     // of fragmented SBC frame
	uint8_t num_frames;
} avdtp_sbc_codec_header_t;

typedef struct {
	uint8_t syncword;
	uint8_t sampling_frequency: 2;
	uint8_t blocks: 2;
	uint8_t channel_mode: 2;
	uint8_t allocation_method: 1;
	uint8_t subbands: 1;
	uint8_t bitpool;
	uint8_t crc_check;
	// If (channel_mode==JOINT_STEREO)
	// {
	// for (sb=0;sb<nrof_subbands-1;sb++)
	// {
	// join[sb] 1 UiMsbf
	// }
	// RFA 1 UiMsbf
	// }
} sbc_frame_header_t;

bool rtk_audio_sbc_register(uint8_t type, PAUDIO_CODEC_ENTITY p_entity);

#endif /* _A2DP_SBC_CODEC_ENTITY_H_ */