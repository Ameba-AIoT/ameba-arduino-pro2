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


#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_TRACK_SERVER_BUFFER_AGENT_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_TRACK_SERVER_BUFFER_AGENT_H

#include "osal_cxx/errors.h"
#include "audio/audio_time.h"

namespace ameba::audio
{
// ----------------------------------------------------------------------------

class TrackServerBufferAgent
{
public:

	struct Buffer {
		Buffer() : raw(NULL), frame_count(0) { }
		union {
			void       *raw;
			short      *i16;
			int8_t     *i8;
		};
		size_t frame_count;
	};

	virtual ~TrackServerBufferAgent() {}

	static const int64_t kInvalidPTS = 0x7FFFFFFFFFFFFFFFLL;

	virtual res_t GetNextAvailBuffer(Buffer *buffer, int64_t pts = kInvalidPTS) = 0;

	virtual void ReleaseHandledBuffer(Buffer *buffer) = 0;

};

// ----------------------------------------------------------------------------
}; // namespace ameba::audio

#endif // AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_TRACK_SERVER_BUFFER_AGENT_H
