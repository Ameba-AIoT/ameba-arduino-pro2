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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_MP3DEC_SW_MP3_DEC_H_
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_MP3DEC_SW_MP3_DEC_H_

#include "utils/nocopyable.h"
#include "media/codec/omx/sw_omx_component.h"

struct tPVMP3DecoderExternal;

namespace ameba::media
{

class SoftMP3 : public SwOMXComponent
{
public:
	SoftMP3(const char *name,
			const OMX_CALLBACKTYPE *callbacks,
			OMX_PTR appData,
			OMX_COMPONENTTYPE **component);

protected:
	virtual ~SoftMP3();

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
		kNumBuffers = 2,
		kOutputBufferSize = 4608 * 2,
		kPVMP3DecoderDelay = 529 // frames
	};

	tPVMP3DecoderExternal *config_;
	void *decoder_buf_;
	int64_t anchor_time_us_;
	int64_t num_frames_output_;

	int32_t num_channels_;
	int32_t sampling_rate_;

	bool is_first_;
	bool signalled_error_;
	bool saw_input_eos_;
	bool signalled_output_eos_;

	enum {
		NONE,
		AWAITING_DISABLED,
		AWAITING_ENABLED
	} output_port_settings_change_;

	void InitPorts();
	void InitDecoder();
	void *MemsetSafe(OMX_BUFFERHEADERTYPE *out_header, int c, size_t len);

	DISALLOW_COPY_AND_MOVE(SoftMP3);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_MP3DEC_SW_MP3_DEC_H_


