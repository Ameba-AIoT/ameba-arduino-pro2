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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_UTILS_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_UTILS_H

#include "media/codec/omx/omx.h"

namespace ameba::media
{

template<class T>
static void InitOMXParams(T *params)
{
	memset(params, 0, sizeof(T));
	params->nSize = sizeof(T);
	params->nVersion.s.nVersionMajor = 1;
	params->nVersion.s.nVersionMinor = 0;
	params->nVersion.s.nRevision = 0;
	params->nVersion.s.nStep = 0;
}

res_t StatusFromOMXError(OMX_ERRORTYPE err);

const char *GetComponentRole(bool is_encoder, const char *mime);
res_t SetComponentRole(const sptr<OMXNode> &omx_node, const char *role);

}  // namespace ameba::media

#endif // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_UTILS_H