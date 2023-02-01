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

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_stream_capture_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_stream_capture_H

#include <stdint.h>

#include "audio/audio_time.h"
#include "hardware/audio/audio_hw_manager.h"
#include "hardware/audio/audio_hw_adapter.h"
#include "hardware/audio/audio_hw_capture.h"
#include "osal_cxx/errors.h"

namespace ameba::audio
{
class AudioStreamCapture
{
public:
	AudioStreamCapture(AudioHwAdapter *adapter);
	virtual               ~AudioStreamCapture() { }
	virtual res_t          CreateCapture(const struct AudioHwDeviceDescriptor *desc,
										 const struct AudioHwSampleAttributes *attr);
	void           DestoryCapture();
public:
	AudioHwAdapter        *audio_adapter_;
	AudioHwCapture        *audio_capture_;

private:
	AudioHwAdapter        *HalAdapter() const;

};

} // namespace ameba::audio

#endif // AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_stream_capture_H
