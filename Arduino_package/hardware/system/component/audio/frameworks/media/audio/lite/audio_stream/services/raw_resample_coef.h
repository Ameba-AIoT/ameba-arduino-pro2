/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from PanKore
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_RAW_RESAMPLE_COEF_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_RAW_RESAMPLE_COEF_H

#include <stdint.h>

using namespace ameba::audio;

#ifdef __cplusplus
extern "C" {
#endif

const   int32_t *readResamplerCoefficients(bool upSample);
int32_t  readResampleFirNumCoeff();
int32_t  readResampleFirLerpIntBits();

#ifdef __cplusplus
}
#endif

#endif
