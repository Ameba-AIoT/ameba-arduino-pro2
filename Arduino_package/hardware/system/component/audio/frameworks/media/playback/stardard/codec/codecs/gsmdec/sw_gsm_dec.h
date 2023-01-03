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


#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_GSMDEC_SW_GSM_DEC_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_GSMDEC_SW_GSM_DEC_H

#include "media/codec/omx/sw_omx_component.h"

extern "C" {
#include "gsm.h"
}

namespace ameba::media
{

struct SoftGSM : public SwOMXComponent {
	SoftGSM(const char *name,
			const OMX_CALLBACKTYPE *callbacks,
			OMX_PTR app_data,
			OMX_COMPONENTTYPE **component);

protected:
	virtual ~SoftGSM();

	virtual OMX_ERRORTYPE GetParameterInternal(
		OMX_INDEXTYPE index, OMX_PTR params);

	virtual OMX_ERRORTYPE SetParameterInternal(
		OMX_INDEXTYPE index, const OMX_PTR params);

	virtual void OnQueueFilled(OMX_U32 port_index);

	virtual void OnPortFlushCompleted(OMX_U32 port_index);
	virtual void OnReset();

private:
	enum {
		kNumBuffers = 4,
		kMaxNumSamplesPerFrame = 16384,
	};

	bool signalled_error_;
	gsm gsm_;

	void InitPorts();

	static int DecodeGSM(gsm handle, int16_t *out, uint8_t *in, size_t in_size);

	DISALLOW_COPY_AND_MOVE(SoftGSM);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_CODECS_GSMDEC_SW_GSM_DEC_H

