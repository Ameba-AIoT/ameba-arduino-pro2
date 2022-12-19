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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_MEDIA_CODEC_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_MEDIA_CODEC_H

#include <memory>
#include <vector>

#include "media/utils/message_handler.h"

namespace ameba::media
{

class RBuffer;
class Message;
class ReplyMessage;
class RString;
class CodecBase;
class CodecBufferInfo;
class BufferTunnelBase;

class MediaCodec : public MessageHandler
{
public:
	enum BufferFlags {
		BUFFERFLAG_CODECCONFIG = 1,
		BUFFERFLAG_EOS = 4,
	};

	enum Events {
		EVENT_INPUT_PORT_AVAILABLE = 1,
		EVENT_OUTPUT_PORT_AVAILABLE = 2,
		EVENT_ERROR = 3,
		EVENT_OUTPUT_FORMAT_CHANGED = 4,
	};

	static sptr<MediaCodec> CreateCodec(const sptr<MessageLooper> &looper, const RString &type);

	res_t Configure(const sptr<Message> &format, uint32_t flags);

	res_t SetCallback(const sptr<Message> &callback);

	res_t Start();

	// Returns to a state in which the component remains allocated but
	// unconfigured.
	res_t Stop();

	// Resets the codec to the STATE_INITIALIZED state.  Can be called after an error
	// has occured to make the codec usable.
	res_t Reset();

	// Client MUST call release before releasing final reference to this
	// object.
	res_t Release();

	res_t Flush();

	res_t EnqueueInputBuffer(
		size_t index,
		size_t offset,
		size_t size,
		int64_t pts,
		uint32_t flags);

	res_t ReleaseOutputBuffer(size_t index);

	res_t GetOutputFormat(sptr<Message> *format) const;
	res_t GetInputFormat(sptr<Message> *format) const;

	// for player_core_decoder
	res_t GetOutputBuffer(size_t index, sptr<CodecBufferInfo> *buffer);
	res_t GetInputBuffer(size_t index, sptr<CodecBufferInfo> *buffer);

	// for codec wrapper
	res_t GetOutputBuffers(std::vector<sptr<CodecBufferInfo>> *buffers) const;
	res_t GetInputBuffers(std::vector<sptr<CodecBufferInfo>> *buffers) const;
	res_t DequeueInputBuffer(size_t *index, int64_t timeout_us);
	res_t DequeueOutputBuffer(
		size_t *index,
		size_t *offset,
		size_t *size,
		int64_t *pts,
		uint32_t *flags,
		int64_t timeout_us);

	res_t GetCodecName(RString *name) const;

protected:
	virtual ~MediaCodec();
	virtual void OnMessage(const sptr<Message> &msg);

private:
	enum State {
		STATE_UNINITIALIZED,
		STATE_INITIALIZING,
		STATE_INITIALIZED,
		STATE_CONFIGURING,
		STATE_CONFIGURED,
		STATE_STARTING,
		STATE_STARTED,
		STATE_FLUSHING,
		STATE_FLUSHED,
		STATE_STOPPING,
		STATE_RELEASING,
	};
	std::string GetStateStr(State state);

	enum {
		kPortInput         = 0,
		kPortOutput        = 1,
	};

	enum {
		kMsgInit                               = 0x310100,//'init',
		kMsgConfigure                      = 0x310101,//'conf',
		kMsgSetParameters              = 0x310102,//'setP',
		kMsgSetCallback                   = 0x310103,//'setC',

		kMsgStart                             = 0x310201,//'strt',
		kMsgStop                              = 0x310202,//'stop',
		kMsgRelease                         = 0x310203,//'rele',
		kMsgFlush                             = 0x310204,//'flus',

		kMsgDequeueInputBuffer      = 0x310300,//'deqI',
		kMsgEnqueueInputBuffer      = 0x310301,//'queI',
		kMsgDequeueInputOvertime  = 0x310303,//'dITO',
		kMsgDequeueOutputBuffer    = 0x310310,//'deqO',
		kMsgReleaseOutputBuffer     = 0x310311,//'relO',
		kMsgDequeueOutputOvertime = 0x310313, //'dOTO',
		kMsgGetBuffers                     = 0x310320,//'getB',

		kMsgCodecEvent                    = 0x310400,//'codc',

		kMsgGetOutputFormat           = 0x310600,//'getO',
		kMsgGetInputFormat             = 0x310601,//'getI',
	};

	enum {
		kFlagOutputFormatChanged        = 1 << 1,
		kFlagOutputBuffersChanged       = 1 << 2,
		kFlagCodecError                = 1 << 3,
		kFlagDequeueInputPending        = 1 << 4,
		kFlagDequeueOutputPending       = 1 << 5,
		kFlagPlayerDied          = 1 << 6,
		kFlagIsAsyncMode                    = 1 << 7,
		kFlagIsComponentAllocated       = 1 << 8,
	};

	struct BufferInfo {
		sptr<CodecBufferInfo> data_;
		bool mOwnedByClient;
	};

	MediaCodec(const sptr<MessageLooper> &looper);

	static res_t PostAndAwaitResponse(
		const sptr<Message> &msg, sptr<Message> *response);

	void PostReplyWithError(const sptr<ReplyMessage> &reply_id, int32_t err);

	res_t Init(const RString &name);

	void SetState(State newState);
	void ReleaseBuffersToCodec();
	void ReleaseBuffersToCodec(int32_t port_idx);
	size_t UpdateBuffers(int32_t port_idx, const sptr<Message> &msg);
	void GetCodecSpecificData(const sptr<Message> &format); //codec specific data
	res_t EnqueueCodecSpecificData(size_t bufferIndex);
	res_t OnEnqueueInputBuffer(const sptr<Message> &msg);
	res_t OnReleaseOutputBuffer(const sptr<Message> &msg);
	ssize_t DequeueBufferAtPort(int32_t port_idx);

	res_t GetBufferAndFormat(
		size_t port_idx, size_t index,
		sptr<CodecBufferInfo> *buffer, sptr<Message> *format);

	void OnError(res_t err, int32_t codec_action, const char *detail = NULL);

	void OnInputBufferAvailable();
	void OnOutputBufferAvailable();
	void OnOutputFormatChanged();

	// for codec wrapper
	bool OnDequeueInputBuffer(const sptr<ReplyMessage> &reply_id);
	bool OnDequeueOutputBuffer(const sptr<ReplyMessage> &reply_id);

	bool IsActing() const;

	void ReturnBuffersToCodec(bool is_reclaim);
	void ReturnBuffersToCodecOnPort(int32_t port_index, bool is_reclaim);

	/* called to get the last codec error when the sticky flag is set.
	 * if no such codec error is found, returns UNKNOWN_ERROR.
	 */
	inline res_t GetCodecError() const
	{
		return codec_error_ != 0 ? codec_error_ : (res_t)UNKNOWN_ERROR;
	}

	inline void SetCodecError(res_t err)
	{
		flags_ |= kFlagCodecError;
		codec_error_ = err;
	}

	State state_;
	sptr<MessageLooper> looper_;
	sptr<CodecBase> codec_;
	RString component_name_;
	sptr<ReplyMessage> reply_id_;
	uint32_t flags_;
	res_t codec_error_;

	int32_t dequeue_input_timeout_count_;
	sptr<ReplyMessage> dequeue_input_reply_id_;

	int32_t dequeue_output_timeout_count_;
	sptr<ReplyMessage> dequeue_output_reply_id_;

	sptr<Message> output_format_;
	sptr<Message> input_format_;
	sptr<Message> callback_;

	List<sptr<RBuffer> > codec_specific_data_;
	bool have_pending_input_buffers_;

	std::shared_ptr<BufferTunnelBase> buffer_tunnel_;

	RString init_name_;

	// Used only to synchronize asynchronous GetBufferAndFormat
	// across all the other (synchronous) buffer state change
	// operations, such as de/queueIn/OutputBuffer, start and
	// stop/flush/reset/release.
	Mutex buffer_lock_;
	List<size_t> avail_port_buffers_[2];
	std::vector<BufferInfo> port_buffers_[2];

	DISALLOW_COPY_AND_MOVE(MediaCodec);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_MEDIA_CODEC_H
