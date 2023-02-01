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
#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_AUDIO_SYSTEM_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_AUDIO_SYSTEM_H

#include "osal_cxx/errors.h"

namespace ameba::audio
{

class AudioSystem
{
public:

	static res_t SetHardwareVolume(float left_volume, float right_volume);
	static res_t GetHardwareVolume(float *left_volume, float *right_volume);
	static res_t SetHardwareMute(bool left_mute, bool right_mute);
	static res_t IsHardwareMuted(bool *left_muted, bool *right_muted);
	static res_t SetCategoryVolume(uint32_t audio_type, float value);
	static float GetCategoryVolume(uint32_t audio_type);
	static res_t SetCategoryMute(uint32_t audio_type, bool mute);
	static bool  IsCategoryMuted(uint32_t audio_type);
};

}

#endif