/**
*****************************************************************************************
*     Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
* @file     audio_codec_wrapper.h
* @brief    Source file for audio codec wrapper interface.
* @details  api function.
* @author   sherman
* @date     2021-06-10
* @version  v1.0
* *************************************************************************************
*/
#ifndef _AUDIO_CODEC_WRAPPER_H_
#define _AUDIO_CODEC_WRAPPER_H_

#include "osdep_service.h"

struct codec_buffer {
	struct list_head          list;
	int16_t                   *pbuffer;
	uint8_t                   size;
};

struct audio_param {
	unsigned int              channels;
	unsigned int              rate;
	unsigned int              bits; 
};

/** @brief application priv obj struct*/
struct audio_codec_entity_priv {
	struct list_head          list;
	bool                      active_flag;
	uint8_t                   type;
	int                       stream_in_num;     //!< indicate application enqueue data/command num.
	bool                      (*init)(void);
	bool                      (*deinit)(void);
	bool                      (*audio_handle_media_data_packet)(uint8_t *packet, uint16_t size, uint32_t *pframe_size, uint8_t *pframe_num, bool *psbc_header_flag, struct audio_param *paudio_param);
	bool                      (*coding_func)(void);
	bool                      (*decoding_func)(uint8_t *data, uint8_t size, struct codec_buffer *decode_buffer, uint32_t *ppcm_size);
	struct codec_buffer      *(*get_decode_buffer)(void);
	void                      (*free_decode_buffer)(struct codec_buffer *buffer);
	struct codec_buffer      *(*get_encode_buffer)(void);
	void                      (*free_encode_buffer)(struct codec_buffer *buffer);
	int                       (*decoder_num_samples_per_frame)(void);
	int                       (*decoder_num_channels)(void);
	int                       (*decoder_sample_rate)(void);
};

/** @brief typedef struct audio_application_entity_priv */
typedef struct audio_codec_entity_priv AUDIO_CODEC_ENTITY, *PAUDIO_CODEC_ENTITY;

/**
 * @brief get decode buffer from specific application memory management
 *
 * @param[in] pentity: codec entity poniter
 * @param[in] type: indicate application
 * @return buffer: point to buffer , NULL: allocate fail
 */
struct codec_buffer *audio_get_decode_buffer(PAUDIO_CODEC_ENTITY pentity, uint8_t type);

/**
 * @brief memory free decode buffer
 *
 * @param[in] pentity: codec entity poniter
 * @param[in] type: indicate application
 * @param[in] buffer: indicate the allocate memory
 * @param[in] reason: decide whether invoking AUDIO_DECODE_DEC
 * @return true: free success , false: free fail
 */
bool audio_free_decode_buffer(PAUDIO_CODEC_ENTITY pentity, uint8_t type, struct codec_buffer *buffer, int8_t reason);

/**
 * @brief get encode buffer from specific application memory management
 *
 * @param[in] pentity: codec entity poniter
 * @param[in] type: indicate application
 * @return buffer: point to buffer , NULL: allocate fail
 */
struct codec_buffer *audio_get_encode_buffer(PAUDIO_CODEC_ENTITY pentity, uint8_t type);

/**
 * @brief memory free encode buffer
 *
 * @param[in] pentity: codec entity poniter
 * @param[in] type: indicate application
 * @param[in] buffer: indicate the allocate memory
 * @return true: free success , false: free fail
 */
bool audio_free_encode_buffer(PAUDIO_CODEC_ENTITY pentity, uint8_t type, struct codec_buffer *buffer);

/**
 * @brief param 
 *
 * @param[in] pentity: codec entity poniter
 * @param[in] type: indicate application
 * @param[in] pdecode_buffer: indicate the allocate memory
 * @param[in] data: poniter to the data buffer
 * @param[in] size: indicate data size
 * @return true: free success , false: free fail
 */
int8_t audio_decode_process_data(PAUDIO_CODEC_ENTITY pentity, uint8_t type, struct codec_buffer *pdecode_buffer, uint8_t *data, uint32_t size, uint32_t *ppcm_size);

/**
 * @brief param media packet
 *
 * @param[in] pentity: codec entity poniter
 * @param[in] type: indicate application
 * @param[in] packet: poniter to the data buffer
 * @param[in] size: indicate data size
 * @param[in] pframe_size: pointer to the frame size value
 * @param[in] pframe_num: pointer to the frame num value
 * @return true: free success , false: free fail
 */
bool audio_handle_media_data_packet(PAUDIO_CODEC_ENTITY pentity, uint8_t type, uint8_t *packet, uint16_t size, uint32_t *pframe_size, uint8_t *pframe_num, bool *psbc_header_flag, struct audio_param *paudio_param);

/**
 * @brief get decoder num samples per frame media packet
 *
 * @param[in] pentity: codec entity poniter
 * @return 0xFF: fail others: number samplers
 */
int codec_decoder_num_samples_per_frame(PAUDIO_CODEC_ENTITY pentity);

/**
 * @brief get decoder channel numbers
 *
 * @param[in] pentity: codec entity poniter
 * @return 0xFF: fail others: number samplers
 */
int codec_decoder_num_channels(PAUDIO_CODEC_ENTITY pentity);

/**
 * @brief get decoder sample rate
 *
 * @param[in] pentity: codec entity poniter
 * @return 0xFF: fail others: number samplers
 */
int codec_decoder_sample_rate(PAUDIO_CODEC_ENTITY pentity);

#endif // _AUDIO_CODEC_WRAPPER_H_