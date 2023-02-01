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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_SW_OMX_COMPONENT_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_SW_OMX_COMPONENT_H

#include <stdio.h>
#include <vector>

#include "osal_c/osal_compat.h"
#include "osal_cxx/refptr.h"
#include "osal_cxx/threads.h"

#include "media/utils/message_handler_wrapper.h"

#include <OMX_Component.h>

namespace ameba::media
{

class MessageLooper;

class SwOMXComponent : public RefPtr
{
public:
	SwOMXComponent(
		const char *name,
		const OMX_CALLBACKTYPE *callbacks,
		OMX_PTR appData,
		OMX_COMPONENTTYPE **component);

	virtual ~SwOMXComponent();

	virtual void PrepareForDestruction();

	const char *Name() const;

	void OnMessage(const sptr<Message> &msg);

protected:
	struct BufferInfo {
		OMX_BUFFERHEADERTYPE *header_;
		bool owned_;
	};

	struct PortInfo {
		OMX_PARAM_PORTDEFINITIONTYPE def_;
		std::vector<BufferInfo> buffers_;
		List<BufferInfo *> queue_;

		enum {
			NONE,
			DISABLING,
			ENABLING,
		} status_;
	};

	enum {
		kStoreMetaDataExtensionIndex = OMX_IndexVendorStartUnused + 1,
		kPrepareForAdaptivePlaybackIndex,
	};

	void Notify(
		OMX_EVENTTYPE event,
		OMX_U32 data1, OMX_U32 data2, OMX_PTR data);

	void NotifyEmptyBufferDone(OMX_BUFFERHEADERTYPE *header);
	void NotifyFillBufferDone(OMX_BUFFERHEADERTYPE *header);

	void AddPort(const OMX_PARAM_PORTDEFINITIONTYPE &def);

	virtual OMX_ERRORTYPE GetParameterInternal(
		OMX_INDEXTYPE index, OMX_PTR params);

	virtual OMX_ERRORTYPE SetParameterInternal(
		OMX_INDEXTYPE index, const OMX_PTR params);

	virtual void OnQueueFilled(OMX_U32 port_idx);
	List<BufferInfo *> &GetPortQueue(OMX_U32 port_idx);

	virtual void OnPortFlushCompleted(OMX_U32 port_idx);
	virtual void OnPortEnableCompleted(OMX_U32 port_idx, bool enabled);
	virtual void OnReset();

	PortInfo *EditPortInfo(OMX_U32 port_idx);

private:
	enum {
		kMsgSendCommand,
		kMsgEmptyThisBuffer,
		kMsgFillBuffer,
	};

	RString name_;
	const OMX_CALLBACKTYPE *callbacks_;
	OMX_COMPONENTTYPE *component_;

	sptr<MessageLooper> looper_;
	sptr<MessageHandlerWrapper<SwOMXComponent> > handler_;

	Mutex lock_;

	OMX_STATETYPE state_;
	OMX_STATETYPE target_state_;

	std::vector<PortInfo> ports_;

	bool CheckSetParameterPermission(OMX_INDEXTYPE index, const OMX_PTR params) const;

	virtual OMX_ERRORTYPE SendCommand(OMX_COMMANDTYPE cmd, OMX_U32 param, OMX_PTR data);

	virtual OMX_ERRORTYPE GetParameter(OMX_INDEXTYPE index, OMX_PTR params);

	virtual OMX_ERRORTYPE SetParameter(OMX_INDEXTYPE index, const OMX_PTR params);

	virtual OMX_ERRORTYPE GetConfig(OMX_INDEXTYPE index, OMX_PTR params);

	virtual OMX_ERRORTYPE SetConfig(OMX_INDEXTYPE index, const OMX_PTR params);

	virtual OMX_ERRORTYPE GetExtensionIndex(const char *name, OMX_INDEXTYPE *index);

	virtual OMX_ERRORTYPE UseBuffer(
		OMX_BUFFERHEADERTYPE **buffer,
		OMX_U32 port_idx,
		OMX_PTR app_private,
		OMX_U32 size,
		OMX_U8 *ptr);

	virtual OMX_ERRORTYPE AllocateBuffer(
		OMX_BUFFERHEADERTYPE **buffer,
		OMX_U32 port_idx,
		OMX_PTR app_private,
		OMX_U32 size);

	virtual OMX_ERRORTYPE FreeBuffer(
		OMX_U32 port_idx,
		OMX_BUFFERHEADERTYPE *buffer);

	virtual OMX_ERRORTYPE EmptyThisBuffer(
		OMX_BUFFERHEADERTYPE *buffer);

	virtual OMX_ERRORTYPE FillThisBuffer(
		OMX_BUFFERHEADERTYPE *buffer);

	virtual OMX_ERRORTYPE GetOMXState(OMX_STATETYPE *state);

	void OnSendCommand(OMX_COMMANDTYPE cmd, OMX_U32 param);
	void OnChangeState(OMX_STATETYPE state);
	void OnPortEnable(OMX_U32 port_idx, bool enable);
	void OnPortFlush(OMX_U32 port_idx, bool notify_flush_complete);

	void CheckStateTransition();

	/////////////////////////////////////////////////////////
	static OMX_ERRORTYPE OmxSendCommand(
		OMX_HANDLETYPE component,
		OMX_COMMANDTYPE cmd,
		OMX_U32 param,
		OMX_PTR data);

	static OMX_ERRORTYPE OmxGetParameter(
		OMX_HANDLETYPE component,
		OMX_INDEXTYPE index,
		OMX_PTR params);

	static OMX_ERRORTYPE OmxSetParameter(
		OMX_HANDLETYPE component,
		OMX_INDEXTYPE index,
		OMX_PTR params);

	static OMX_ERRORTYPE OmxGetConfig(
		OMX_HANDLETYPE component,
		OMX_INDEXTYPE index,
		OMX_PTR params);

	static OMX_ERRORTYPE OmxSetConfig(
		OMX_HANDLETYPE component,
		OMX_INDEXTYPE index,
		OMX_PTR params);

	static OMX_ERRORTYPE OmxGetExtensionIndex(
		OMX_HANDLETYPE component,
		OMX_STRING name,
		OMX_INDEXTYPE *index);

	static OMX_ERRORTYPE OmxUseBuffer(
		OMX_HANDLETYPE component,
		OMX_BUFFERHEADERTYPE **buffer,
		OMX_U32 port_idx,
		OMX_PTR app_private,
		OMX_U32 size,
		OMX_U8 *ptr);

	static OMX_ERRORTYPE OmxAllocateBuffer(
		OMX_HANDLETYPE component,
		OMX_BUFFERHEADERTYPE **buffer,
		OMX_U32 port_idx,
		OMX_PTR app_private,
		OMX_U32 size);

	static OMX_ERRORTYPE OmxFreeBuffer(
		OMX_HANDLETYPE component,
		OMX_U32 port_idx,
		OMX_BUFFERHEADERTYPE *buffer);

	static OMX_ERRORTYPE OmxEmptyThisBuffer(
		OMX_HANDLETYPE component,
		OMX_BUFFERHEADERTYPE *buffer);

	static OMX_ERRORTYPE OmxFillThisBuffer(
		OMX_HANDLETYPE component,
		OMX_BUFFERHEADERTYPE *buffer);

	static OMX_ERRORTYPE OmxGetState(
		OMX_HANDLETYPE component,
		OMX_STATETYPE *state);

	// disable copy ctor
	SwOMXComponent(const SwOMXComponent &);
	SwOMXComponent &operator=(const SwOMXComponent &);
};

template<typename T>
bool CheckOMXParamValidation(T *a)
{
	static_assert(offsetof(typeof(*a), nSize) == 0, "nSize not at offset 0");
	static_assert(std::is_same < decltype(a->nSize), OMX_U32 >::value, "nSize has wrong type");
	static_assert(offsetof(typeof(*a), nVersion) == 4, "nVersion not at offset 4");
	static_assert(std::is_same < decltype(a->nVersion), OMX_VERSIONTYPE >::value,
				  "nVersion has wrong type");

	if (a->nSize < sizeof(*a)) {
		RTLOGE("Invalid OMX param: need %d, got %u", (int)sizeof(*a), (unsigned int)a->nSize);
		return false;
	}
	return true;
}

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_SW_OMX_COMPONENT_H
