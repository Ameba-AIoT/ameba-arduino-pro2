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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_BASE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_BASE_H

#include <list>
#include <memory>

#include <stdint.h>

#include "media/utils/message_handler.h"
#include "media/common/media_errors.h"

namespace ameba::media
{

class BufferTunnelBase;
class CodecBufferInfo;

class CodecBase : public MessageHandler
{
public:
	/**
	 * This interface defines events firing from CodecBase back to MediaCodec.
	 * All methods must not block.
	 */
	class CodecCallback
	{
	public:
		virtual ~CodecCallback() = default;

		/**
		 * Notify MediaCodec for seeing an output EOS.
		 *
		 * @param err the underlying cause of the EOS. If the value is neither
		 *            OK nor ERROR_END_OF_STREAM, the EOS is declared
		 *            prematurely for that error.
		 */
		virtual void OnEos(res_t err) = 0;
		/**
		 * Notify MediaCodec that start operation is complete.
		 */
		virtual void OnStartCompleted() = 0;
		/**
		 * Notify MediaCodec that stop operation is complete.
		 */
		virtual void OnStopCompleted() = 0;
		/**
		 * Notify MediaCodec that release operation is complete.
		 */
		virtual void OnReleaseCompleted() = 0;
		/**
		 * Notify MediaCodec that flush operation is complete.
		 */
		virtual void OnFlushCompleted() = 0;
		/**
		 * Notify MediaCodec that an error is occurred.
		 *
		 * @param err         an error code for the occurred error.
		 * @param codec_action  an action code for severity of the error.
		 */
		virtual void OnError(res_t err, enum CodecAction codec_action) = 0;
		/**
		 * Notify MediaCodec that the underlying component is allocated.
		 *
		 * @param comp_name the unique name of the component specified in
		 *                      MediaCodecList.
		 */
		virtual void OnComponentAllocated(const char *comp_name) = 0;
		/**
		 * Notify MediaCodec that the underlying component is configured.
		 *
		 * @param input_format   an input format at configure time.
		 * @param output_format  an output format at configure time.
		 */
		virtual void OnComponentConfigured(
			const sptr<Message> &input_format, const sptr<Message> &output_format) = 0;

		/**
		 * Notify MediaCodec that output buffers are changed.
		 */
		virtual void OnOutputBuffersChanged() = 0;
	};

	/**
	 * This interface defines events firing from BufferTunnelBase back to MediaCodec.
	 * All methods must not block.
	 */
	class BufferCallback
	{
	public:
		virtual ~BufferCallback() = default;

		/**
		 * Notify MediaCodec that an input buffer is available with given index.
		 * When BufferTunnelBase::GetInputBufferArray() is not called,
		 * BufferTunnelBase may report different buffers with the same index if
		 * MediaCodec already queued/discarded the buffer. After calling
		 * BufferTunnelBase::GetInputBufferArray(), the buffer and index match the
		 * returned array.
		 */
		virtual void OnInputBufferAvailable(
			size_t index, const sptr<CodecBufferInfo> &buffer) = 0;
		/**
		 * Notify MediaCodec that an output buffer is available with given index.
		 * When BufferTunnelBase::GetOutputBufferArray() is not called,
		 * BufferTunnelBase may report different buffers with the same index if
		 * MediaCodec already queued/discarded the buffer. After calling
		 * BufferTunnelBase::GetOutputBufferArray(), the buffer and index match the
		 * returned array.
		 */
		virtual void OnOutputBufferAvailable(
			size_t index, const sptr<CodecBufferInfo> &buffer) = 0;
	};

	enum {
		kMaxCodecBufferSize = 8192 * 4096 * 4,
	};

	inline void SetCallback(std::unique_ptr<CodecCallback> &&callback)
	{
		callback_ = std::move(callback);
	}

	virtual std::shared_ptr<BufferTunnelBase> GetBufferTunnel() = 0;

	virtual void AllocateComponent(const sptr<Message> &msg) = 0;
	virtual void ConfigureComponent(const sptr<Message> &msg) = 0;
	virtual void Start() = 0;
	virtual void StartShutdown(bool reserve_component = false) = 0;

	// require an explicit message handler
	virtual void OnMessage(const sptr<Message> &msg) = 0;

	virtual void Flush() = 0;
	virtual void Resume() = 0;

protected:
	CodecBase() = default;
	virtual ~CodecBase() = default;

	std::unique_ptr<CodecCallback> callback_;

private:
	DISALLOW_COPY_AND_MOVE(CodecBase);
};

/**
 * A channel between MediaCodec and CodecBase object which manages buffer
 * passing. Only MediaCodec is expected to call these methods, and
 * underlying CodecBase implementation should define its own interface
 * separately for itself.
 *
 * Concurrency assumptions:
 *
 * 1) Clients may access the object at multiple threads concurrently.
 * 2) All methods do not call underlying CodecBase object while holding a lock.
 * 3) Code inside critical section executes within 1ms.
 */
class BufferTunnelBase
{
public:
	virtual ~BufferTunnelBase() = default;

	inline void SetCallback(std::unique_ptr<CodecBase::BufferCallback> &&callback)
	{
		callback_ = std::move(callback);
	}

	/**
	 * Queue an input buffer into the buffer channel.
	 *
	 * @return    OK if successful;
	 *            -ENOENT if the buffer is not known (TODO: this should be
	 *            handled gracefully in the future, here and below).
	 */
	virtual res_t EnqueueInputBuffer(const sptr<CodecBufferInfo> &buffer) = 0;

	/**
	 * Discard a buffer to the underlying CodecBase object.
	 *
	 * TODO: remove once this operation can be handled by just clearing the
	 * reference.
	 *
	 * @return    OK if successful;
	 *            -ENOENT if the buffer is not known.
	 */
	virtual res_t DiscardBuffer(const sptr<CodecBufferInfo> &buffer) = 0;

	virtual void GetInputBufferArray(std::vector<sptr<CodecBufferInfo>> *array) = 0;
	virtual void GetOutputBufferArray(std::vector<sptr<CodecBufferInfo>> *array) = 0;

protected:
	std::unique_ptr<CodecBase::BufferCallback> callback_;
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_BASE_H
