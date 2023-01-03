/*
 * Copyright (c) 2022 Realtek, LLC.
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


#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_AMRDEC_SW_AMR_DEC_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_AMRDEC_SW_AMR_DEC_H

#include "media/codec/omx/sw_omx_component.h"

namespace ameba::media
{

struct SoftAMR : public SwOMXComponent {
	SoftAMR(const char *name,
			const OMX_CALLBACKTYPE *callbacks,
			OMX_PTR app_data,
			OMX_COMPONENTTYPE **component);

protected:
	virtual ~SoftAMR();

	virtual OMX_ERRORTYPE GetParameterInternal(
		OMX_INDEXTYPE index, OMX_PTR params);

	virtual OMX_ERRORTYPE SetParameterInternal(
		OMX_INDEXTYPE index, const OMX_PTR params);

	virtual void OnQueueFilled(OMX_U32 port_index);
	virtual void OnPortFlushCompleted(OMX_U32 port_index);
	virtual void OnPortEnableCompleted(OMX_U32 port_index, bool enabled);
	virtual void OnReset();

private:
	enum {
		kNumBuffers             = 4,
		kSampleRateNB           = 8000,
		kSampleRateWB           = 16000,
		kNumSamplesPerFrameNB   = 160,
		kNumSamplesPerFrameWB   = 320,
	};

	enum {
		MODE_NARROW,
		MODE_WIDE

	} mode_;

	void *state_;
	void *decoder_buf_;
	int16_t *decoder_cookie_;

	size_t input_buffer_count_;
	int64_t anchor_time_us_;
	int64_t num_samples_output_;

	bool signalled_error_;

	enum {
		NONE,
		AWAITING_DISABLED,
		AWAITING_ENABLED
	} output_port_settings_change_;

	int16_t input_sample_buffer_[477];

	void InitPorts();
	res_t InitDecoder();
	bool IsConfigured() const;

	DISALLOW_COPY_AND_MOVE(SoftAMR);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_AMRDEC_SW_AMR_DEC_H

