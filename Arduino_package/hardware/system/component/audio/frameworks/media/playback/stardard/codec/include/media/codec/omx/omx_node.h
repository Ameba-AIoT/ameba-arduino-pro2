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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_NODE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_NODE_H

#include <atomic>
#include <vector>
#include <map>

#include "osal_cxx/refptr.h"
#include "osal_cxx/mutex.h"
#include "media/codec/omx/omx.h"

namespace ameba::media
{

class OMXObserver;
class OMXBuffer;

class OMXNode : public RefPtr
{
public:
	OMXNode(OMX *owner, const sptr<OMXObserver> &observer, const char *name);

	~OMXNode();

	void SetOMXHandle(OMX_HANDLETYPE handle);

	OMX_HANDLETYPE GetOMXHandle();
	sptr<OMXObserver> GetOMXObserver();

	res_t DeleteOMXNode();

	res_t SendCommand(OMX_COMMANDTYPE cmd, OMX_S32 param);
	res_t GetParameter(OMX_INDEXTYPE index, void *params, size_t size);

	res_t SetParameter(
		OMX_INDEXTYPE index, const void *params, size_t size);

	res_t GetConfig(OMX_INDEXTYPE index, void *params, size_t size);
	res_t SetConfig(OMX_INDEXTYPE index, const void *params, size_t size);

	res_t UseBuffer(OMX_U32 port_idx, const OMXBuffer &omx_buffer, OMX::buffer_id *buffer);

	res_t FreeBuffer(OMX_U32 port_idx, OMX::buffer_id buffer);

	res_t FillThisBuffer(OMX::buffer_id buffer, const OMXBuffer &omx_buffer);

	res_t EmptyBuffer(OMX::buffer_id buffer, const OMXBuffer &omx_buffer,
					  OMX_U32 flags, OMX_TICKS timestamp);

	res_t GetExtensionIndex(const char *parameter_name, OMX_INDEXTYPE *index);

	// handles messages and removes them from the list
	void OnMessages(std::list<omx_message> &messages);
	void OnEvent(OMX_EVENTTYPE event, OMX_U32 arg1, OMX_U32 arg2);

	static OMX_CALLBACKTYPE kCallbacks;

private:
	class EventBatcherThread;
	class EventBatcher;

	static OMX_ERRORTYPE OnEvent(
		OMX_IN OMX_HANDLETYPE hComponent,
		OMX_IN OMX_PTR pAppData,
		OMX_IN OMX_EVENTTYPE eEvent,
		OMX_IN OMX_U32 nData1,
		OMX_IN OMX_U32 nData2,
		OMX_IN OMX_PTR pEventData);

	static OMX_ERRORTYPE OnEmptyBufferDone(
		OMX_IN OMX_HANDLETYPE hComponent,
		OMX_IN OMX_PTR pAppData,
		OMX_IN OMX_BUFFERHEADERTYPE *pBuffer);

	static OMX_ERRORTYPE OnFillBufferDone(
		OMX_IN OMX_HANDLETYPE hComponent,
		OMX_IN OMX_PTR pAppData,
		OMX_IN OMX_BUFFERHEADERTYPE *pBuffer);

	// Handles |msg|, and may modify it. Returns true iff completely handled it and
	// |msg| does not need to be sent to the event listener.
	bool HandleMessage(omx_message &msg);

	void AddActiveBuffer(OMX_U32 port_idx, OMX::buffer_id id);
	void RemoveActiveBuffer(OMX_U32 port_idx, OMX::buffer_id id);
	void DeleteActiveBuffers();

	// For buffer id management
	OMX::buffer_id CreateBufferID(OMX_BUFFERHEADERTYPE *buffer_header);
	OMX_BUFFERHEADERTYPE *GetBufferHeader(OMX::buffer_id buffer, OMX_U32 port_idx);
	OMX::buffer_id GetBufferID(OMX_BUFFERHEADERTYPE *buffer_header);
	void InvalidateBufferID(OMX::buffer_id buffer);

	Mutex lock_;
	OMX *omx_;
	OMX_HANDLETYPE handle_;
	sptr<OMXObserver> observer_;
	sptr<EventBatcher> event_batcher_;
	Mutex dying_lock_;
	std::atomic_bool dying_;

	struct ActiveBuffer {
		OMX_U32 port_idx_;
		OMX::buffer_id id_;
	};
	std::vector<ActiveBuffer> active_buffers_;
	// for buffer ptr to buffer id translation
	Mutex buffer_id_Lock_;
	uint32_t buffer_id_count_;
	std::map<OMX::buffer_id, OMX_BUFFERHEADERTYPE *> buffer_id_to_buffer_header_;
	std::map<OMX_BUFFERHEADERTYPE *, OMX::buffer_id> buffer_header_to_buffer_id_;

	char *name_;
	int debug_;
	size_t port_buffers_num_[2];  // modified under lock_, read outside for debug

	OMXNode(const OMXNode &);
	OMXNode &operator=(const OMXNode &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_NODE_H
