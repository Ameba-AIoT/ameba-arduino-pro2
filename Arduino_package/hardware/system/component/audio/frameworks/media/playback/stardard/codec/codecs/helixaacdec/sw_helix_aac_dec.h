/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_AACDEC_SW_HELIX_AAC_DEC_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_AACDEC_SW_HELIX_AAC_DEC_H

#include "media/codec/omx/sw_omx_component.h"
#include "aacdec.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BUFFUER_MAX                1024

namespace ameba::media
{

class SwHelixAACDec : public SwOMXComponent
{
public:
	SwHelixAACDec(const char *name,
				  const OMX_CALLBACKTYPE *callbacks,
				  OMX_PTR appData,
				  OMX_COMPONENTTYPE **component);

protected:
	virtual ~SwHelixAACDec();

	virtual OMX_ERRORTYPE GetParameterInternal(
		OMX_INDEXTYPE index, OMX_PTR params);

	virtual OMX_ERRORTYPE SetParameterInternal(
		OMX_INDEXTYPE index, const OMX_PTR params);

	virtual void OnQueueFilled(OMX_U32 port_idx);
	virtual void OnPortFlushCompleted(OMX_U32 port_idx);
	virtual void OnPortEnableCompleted(OMX_U32 port_idx, bool enabled);
	virtual void OnReset();

private:
	enum {
		kNumInputBuffers        = 2,
		kNumOutputBuffers       = 2,
		kNumDelayBlocksMax      = 2,
	};

	HAACDecoder	aac_decoder_;
	AACFrameInfo frame_info_;
	bool has_stream_info_;
	bool is_adts_;
	uint8_t *read_ptr_;
	int32_t bytes_left_;
	uint8_t read_buf_[BUFFUER_MAX] __attribute__((aligned(4)));
	bool is_first_;
	std::vector<int64_t> buffer_timestamps_;
	mutable Mutex lock_;
	bool end_of_input_;
	bool end_of_output_;
	bool signal_err_;

	void InitPorts();
	res_t InitDecoder();
	bool IsConfigured() const;
	void DrainDecoder();

	enum {
		NONE,
		AWAITING_DISABLED,
		AWAITING_ENABLED
	} output_port_settings_change_;

	int32_t input_delay_ring_buffer_size_;
	uint8_t *input_delay_ring_buffer_;
	int32_t input_delay_ring_buffer_write_pos_;
	int32_t input_delay_ring_buffer_read_pos_;
	int32_t input_delay_ring_buffer_filled_;
	bool InputDelayRingBufferPutSamples(uint8_t *samples, int32_t num_samples);
	int32_t InputDelayRingBufferGetSamples(uint8_t *samples, int32_t num_samples);
	int32_t InputDelayRingBufferSamplesAvailable();
	int32_t InputDelayRingBufferSpaceLeft();
	void InputDelayRingBufferSamplesBack(int32_t num_samples);
	// disable copy ctor
	SwHelixAACDec(const SwHelixAACDec &);
	SwHelixAACDec &operator=(const SwHelixAACDec &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_AACDEC_SW_HELIX_AAC_DEC_H

