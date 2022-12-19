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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_BUFFER_TUNNEL_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_BUFFER_TUNNEL_H

#include <memory>
#include <vector>

#include "media/codec/omxil/OMX_Types.h"
#include "media/codec/codec_base.h"
#include "media/codec/omx/omx.h"

namespace ameba::media
{

class CodecBufferInfo;

/**
 * BufferTunnelBase implementation
 */
class CodecBufferTunnel : public BufferTunnelBase
{
public:
	struct BufferChannelElem {
		sptr<CodecBufferInfo> mBuffer;
		OMX::buffer_id buffer_id_;
	};

	class BufferInfo
	{
	public:
		BufferInfo(
			const sptr<CodecBufferInfo> &buffer,
			OMX::buffer_id buffer_id);

		//BufferInfo() = delete;

		// Buffer facing MediaCodec and its clients.
		const sptr<CodecBufferInfo> client_buffer_;
		// Buffer facing CodecBase.
		const sptr<CodecBufferInfo> codec_buffer_;
		// OMX buffer ID.
		const OMX::buffer_id buffer_id_;
	};

	CodecBufferTunnel(
		const sptr<Message> &input_buffer_filled, const sptr<Message> &output_buffer_drained);
	virtual ~CodecBufferTunnel();

	// BufferTunnelBase interface
	virtual res_t EnqueueInputBuffer(const sptr<CodecBufferInfo> &buffer) override;
	virtual res_t DiscardBuffer(const sptr<CodecBufferInfo> &buffer) override;
	virtual void GetInputBufferArray(std::vector<sptr<CodecBufferInfo>> *array) override;
	virtual void GetOutputBufferArray(std::vector<sptr<CodecBufferInfo>> *array) override;
	// Methods below are interface for Codec to use.

	/**
	 * Set input buffer array.
	 *
	 * @param array     Newly allocated buffers. Empty if buffers are
	 *                  deallocated.
	 */
	void SetInputBufferElems(const std::vector<BufferChannelElem> &elems);

	/**
	 * Set output buffer array.
	 *
	 * @param array     Newly allocated buffers. Empty if buffers are
	 *                  deallocated.
	 */
	void SetOutputBufferElems(const std::vector<BufferChannelElem> &elems);

	/**
	 * Request MediaCodec to fill the specified input buffer.
	 *
	 * @param id  ID of the buffer, assigned by underlying component.
	 */
	void FillThisBuffer(OMX::buffer_id id);

	/**
	 * Request MediaCodec to drain the specified output buffer.
	 *
	 * @param id  ID of the buffer, assigned by underlying component.
	 * @param omx_flags  flags associated with this buffer (e.g. EOS).
	 */
	void DrainBuffer(OMX::buffer_id id, OMX_U32 omx_flags);

private:
	const sptr<Message> input_buffer_filled_;
	const sptr<Message> output_buffer_drained_;

	Mutex output_buffer_lock_;
	Mutex input_buffer_lock_;

	// These should only be accessed via std::atomic_* functions.
	//
	// Note on thread safety: since the vector and BufferInfo are const, it's
	// safe to read them at any thread once the shared_ptr object is atomically
	// obtained. Inside BufferInfo, buffer_id_ and mSharedEncryptedBuffer are
	// immutable objects. We write internal states of mClient/CodecBuffer when
	// the caller has given up the reference, so that access is also safe.
	std::shared_ptr<const std::vector<BufferInfo>> input_buffers_;
	std::shared_ptr<const std::vector<BufferInfo>> output_buffers_;
};


}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_CODEC_BUFFER_TUNNEL_H
