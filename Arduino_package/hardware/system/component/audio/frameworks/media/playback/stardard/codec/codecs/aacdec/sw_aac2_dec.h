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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_AACDEC_SW_AAC2_DEC_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_AACDEC_SW_AAC2_DEC_H

#include <vector>

#include "media/codec/omx/sw_omx_component.h"

#include "aacdecoder_lib.h"
#include "drc_pres_mode_wrap.h"

namespace ameba::media
{

class SwAAC2Dec : public SwOMXComponent
{
public:
	SwAAC2Dec(const char *name,
			  const OMX_CALLBACKTYPE *callbacks,
			  OMX_PTR appData,
			  OMX_COMPONENTTYPE **component);

protected:
	virtual ~SwAAC2Dec();

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
		kNumDelayBlocksMax      = 8,
	};

	HANDLE_AACDECODER aac_decoder_;
	CStreamInfo *stream_info_;
	bool is_adts_;
	bool is_first_;
	size_t input_buffer_count_;
	size_t output_buffer_count_;
	bool signalled_error_;
	OMX_BUFFERHEADERTYPE *last_in_header_;
	std::vector<int32_t> buffer_sizes_;
	std::vector<int32_t> decoded_sizes_;
	std::vector<int64_t> buffer_timestamps_;

	CDrcPresModeWrapper drc_wrap_;

	enum {
		NONE,
		AWAITING_DISABLED,
		AWAITING_ENABLED
	} output_port_settings_change_;

	void InitPorts();
	res_t InitDecoder();
	bool IsConfigured() const;
	void DrainDecoder();

//      delay compensation
	bool end_of_input_;
	bool end_of_output_;
	int32_t output_delay_compensated_;
	int32_t output_delay_ring_buffer_Size;
	short *output_delay_ring_buffer_;
	int32_t output_delay_ring_buffer_WritePos;
	int32_t output_delay_ring_buffer_ReadPos;
	int32_t output_delay_ring_buffer_Filled;
	INT_PCM *decoder_out_buffer_;
	bool OutputDelayRingBufferPutSamples(INT_PCM *samples, int32_t num_samples);
	int32_t OutputDelayRingBufferGetSamples(INT_PCM *samples, int32_t num_samples);
	int32_t OutputDelayRingBufferSamplesAvailable();
	int32_t OutputDelayRingBufferSpaceLeft();


	// disable copy ctor
	SwAAC2Dec(const SwAAC2Dec &);
	SwAAC2Dec &operator=(const SwAAC2Dec &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_AACDEC_SW_AAC2_DEC_H