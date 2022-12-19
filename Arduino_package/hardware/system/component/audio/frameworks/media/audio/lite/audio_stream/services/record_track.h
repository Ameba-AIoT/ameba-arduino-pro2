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

#ifndef AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_RECORD_TRACK_H
#define AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_RECORD_TRACK_H

#include "osal_cxx/errors.h"
#include "track_base.h"
#include "string.h"
#include "audio/audio_time.h"
#include "hardware/audio/audio_hw_types.h"
#include "track_shared.h"

namespace ameba::audio
{

class RecordThread;
class ResamplerBufferAgent;
class RecordBufferConverter;

// record track
class RecordTrack : public ThreadBase::TrackBase
{
	friend class RecordThread;
public:
	RecordTrack(RecordThread *thread, uint32_t sampleRate, uint32_t format, uint32_t channel_count,
				size_t frame_count);
	virtual             ~RecordTrack();

	virtual res_t       Start();
	virtual void        Stop();
	void        Destroy();
	void        Invalidate();
	void        ClearOverflow()
	{
		over_flow_ = false;
	}
	bool        SetOverflow()
	{
		bool tmp = over_flow_;
		over_flow_ = true;
		return tmp;
	}
	res_t       SetParameters(const char *strs);
private:
	RecordTrack(const RecordTrack &);
	RecordTrack &operator = (const RecordTrack &);

	// TrackServerBufferAgent interface
	virtual res_t       GetNextAvailBuffer(TrackServerBufferAgent::Buffer *buffer,
										   int64_t pts = kInvalidPTS);
	// ReleaseHandledBuffer() not overridden
	bool                                over_flow_;

	TrackServerBufferAgent::Buffer      sink_;

	ResamplerBufferAgent           	   *resampler_buffer_agent_;

	RecordBufferConverter              *record_buffer_converter_;
};

}
#endif // AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_OUTPUT_TRACK_H