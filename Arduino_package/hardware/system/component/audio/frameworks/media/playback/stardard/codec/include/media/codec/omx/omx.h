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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_H

#include <list>
#include <map>

#include "osal_cxx/errors.h"
#include "osal_cxx/refptr.h"
#include "osal_cxx/mutex.h"

#include "media/codec/omxil/OMX_Core.h"

namespace ameba::media
{

class OMXNode;
class OMXObserver;
struct omx_message;

class OMX : public RefPtr
{
public:
	typedef uint32_t buffer_id;

	OMX();
	virtual ~OMX();

	virtual res_t CreateOMXNode(
		const char *name, const sptr<OMXObserver> &observer,
		sptr<OMXNode> *omx_node);

	res_t DeleteOMXNode(sptr<OMXNode> const &omx_node);

private:
	Mutex lock_;

	std::map<wptr<OMXObserver>, sptr<OMXNode>> nodes_;
	std::map<OMXNode *, wptr<OMXObserver>> node_observer_map_;
};

struct omx_message {
	enum {
		EVENT,
		EMPTY_BUFFER_DONE,
		FILL_BUFFER_DONE,
		FRAME_RENDERED,
	} type;

	union {
		// if type == EVENT
		struct {
			OMX_EVENTTYPE event;
			OMX_U32 data1;
			OMX_U32 data2;
			OMX_U32 data3;
			OMX_U32 data4;
		} event_data;

		// if type == EMPTY_BUFFER_DONE
		struct {
			OMX::buffer_id buffer;
		} buffer_data;

		// if type == FILL_BUFFER_DONE
		struct {
			OMX::buffer_id buffer;
			OMX_U32 range_offset;
			OMX_U32 range_length;
			OMX_U32 flags;
			OMX_TICKS timestamp;
		} extended_buffer_data;

		// if type == FRAME_RENDERED
		struct {
			OMX_TICKS timestamp;
			OMX_S64 nano_time;
		} render_data;
	} u;
};

class OMXObserver : public RefPtr
{
public:
	// Handle (list of) messages.
	virtual void OnMessages(const std::list<omx_message> &messages) = 0;
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_H