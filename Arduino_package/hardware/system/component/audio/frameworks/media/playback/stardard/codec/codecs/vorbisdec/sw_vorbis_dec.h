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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_VORBISDEC_SW_VORBISDEC_DEC_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_VORBISDEC_SW_VORBISDEC_DEC_H

#include "media/codec/omx/sw_omx_component.h"

struct vorbis_dsp_state;
struct vorbis_info;

namespace ameba::media
{

struct SoftVorbis : public SwOMXComponent {
	SoftVorbis(const char *name,
			   const OMX_CALLBACKTYPE *callbacks,
			   OMX_PTR app_data,
			   OMX_COMPONENTTYPE **component);

protected:
	virtual ~SoftVorbis();

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
		kNumBuffers = 4,
		kMaxNumSamplesPerBuffer = 8192 * 2
	};

	size_t input_buffer_count_;

	vorbis_dsp_state *state_;
	vorbis_info *v_info_;

	int64_t anchor_time_us_;
	int64_t num_frames_output_;
	int32_t num_frames_left_on_page_;
	bool saw_input_eos_;
	bool signalled_output_eos_;
	bool signalled_error_;

	enum {
		NONE,
		AWAITING_DISABLED,
		AWAITING_ENABLED
	} output_port_settings_change_;

	void InitPorts();
	res_t InitDecoder();
	bool IsConfigured() const;
	void HandleEOS();

	DISALLOW_COPY_AND_MOVE(SoftVorbis);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_VORBISDEC_SW_VORBISDEC_DEC_H

