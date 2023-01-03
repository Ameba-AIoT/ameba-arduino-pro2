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

/*
 * The Opus specification is part of IETF RFC 6716:
 * http://tools.ietf.org/html/rfc6716
 */

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_OPUSDEC_SW_OPUS_DEC_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_OPUSDEC_SW_OPUS_DEC_H

#include "media/codec/omx/sw_omx_component.h"

struct OpusMSDecoder;

namespace ameba::media
{

struct OpusHeader {
	int channels;
	int skip_samples;
	int channel_mapping;
	int num_streams;
	int num_coupled;
	int16_t gain_db;
	uint8_t stream_map[8];
};

struct SoftOpus : public SwOMXComponent {
	SoftOpus(const char *name,
			 const OMX_CALLBACKTYPE *callbacks,
			 OMX_PTR app_data,
			 OMX_COMPONENTTYPE **component);

protected:
	virtual ~SoftOpus();

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
		kMaxNumSamplesPerBuffer = 960 * 6
	};

	size_t input_buffer_count;

	OpusMSDecoder *decoder_;
	OpusHeader *header_;

	int64_t codec_delay;
	int64_t seek_pre_roll;
	int64_t samples_to_discard;
	int64_t anchor_time_us;
	int64_t num_samples_output_;
	bool have_eos_;

	enum {
		NONE,
		AWAITING_DISABLED,
		AWAITING_ENABLED
	} output_port_settings_change_;

	void InitPorts();
	res_t InitDecoder();
	bool IsConfigured() const;
	void HandleEOS();

	DISALLOW_COPY_AND_MOVE(SoftOpus);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_OPUSDEC_SW_OPUS_DEC_H
