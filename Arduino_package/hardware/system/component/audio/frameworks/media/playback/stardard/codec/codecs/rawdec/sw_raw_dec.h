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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_RAWDEC_SW_RAW_DEC_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_RAWDEC_SW_RAW_DEC_H

#include "media/codec/omx/sw_omx_component.h"

namespace ameba::media
{

class SwRawDec : public SwOMXComponent
{
public:
	SwRawDec(const char *name,
			 const OMX_CALLBACKTYPE *callbacks,
			 OMX_PTR appData,
			 OMX_COMPONENTTYPE **component);

protected:
	virtual ~SwRawDec();

	virtual OMX_ERRORTYPE GetParameterInternal(
		OMX_INDEXTYPE index, OMX_PTR params);

	virtual OMX_ERRORTYPE SetParameterInternal(
		OMX_INDEXTYPE index, const OMX_PTR params);

	virtual void OnQueueFilled(OMX_U32 port_idx);

private:
	enum {
		kNumBuffers = 2
	};

	bool signalled_error_;

	int32_t channel_count_;
	int32_t sample_rate_;
	int32_t numerical_data_;
	int32_t bits_per_sample_;

	void InitPorts();
	res_t InitDecoder();

	// disable copy ctor
	SwRawDec(const SwRawDec &);
	SwRawDec &operator=(const SwRawDec &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_RAWDEC_SW_RAW_DEC_H