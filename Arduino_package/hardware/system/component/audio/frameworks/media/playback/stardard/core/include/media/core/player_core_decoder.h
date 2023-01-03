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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_DECODER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_DECODER_H
#include <vector>

#include "player_core.h"
#include "player_core_decoder_base.h"

namespace ameba::media
{

class CodecBufferInfo;

class PlayerCore::Decoder : public DecoderBase
{
public:
	Decoder(const sptr<Message> &notify,
			const sptr<Source> &source,
			const sptr<Renderer> &renderer = NULL);

	virtual sptr<Message> GetDecoderInfos() const;

protected:
	virtual ~Decoder();

	virtual void OnMessage(const sptr<Message> &msg);

	virtual void OnConfigure(const sptr<Message> &format);
	virtual void OnSetParameters(const sptr<Message> &params);
	virtual void OnSetRenderer(const sptr<Renderer> &renderer);
	virtual void OnResume(bool need_notify);
	virtual void OnFlush();
	virtual void OnShutdown(bool need_notify);
	virtual bool DoRequestBuffers();

private:
	enum {
		kMsgCodecEvent         = 0x00550403, //'cdcE',
		kMsgRenderBuffer        = 0x00550406, //'rndr',
		kMsgAudioOutputFormatChanged = 0x00550601, //'aofc',
	};

	sptr<Source> source_;
	sptr<Renderer> renderer_;

	sptr<Message> input_format_;
	sptr<Message> output_format_;
	sptr<MediaCodec> codec_;
	sptr<MessageLooper> codec_looper_;

	List<sptr<Message> > pending_input_msges_;

	std::vector<sptr<CodecBufferInfo> > input_buffers_;
	std::vector<sptr<CodecBufferInfo> > output_buffers_;
	std::vector<sptr<RBuffer> > csds_;
	std::vector<sptr<RBuffer> > csds_pending_;
	std::vector<bool> input_buffer_is_dequeued_;
	std::vector<MediaBuffer *> media_buffers_;
	std::vector<size_t> dequeued_input_buffer_ids_;

	int64_t skip_render_until_media_time_us_;
	bool format_change_pending_;
	bool time_change_pending_;

	bool resume_pending_;
	RString component_name_;

	void HandleError(int32_t err);
	bool HandleInputBuffer(size_t index);
	bool HandleOutputBuffer(
		size_t index,
		size_t offset,
		size_t size,
		int64_t time_us,
		int32_t flags);
	void HandleOutputFormatChange(const sptr<Message> &format);

	void ReleaseAndResetMediaBuffers();
	bool IsFreshReply(const sptr<Message> &msg);

	void DoFlush(bool need_notify);
	res_t RequestInputData(sptr<Message> &reply);
	bool OnInputBufferGained(const sptr<Message> &msg);
	void OnRenderBuffer(const sptr<Message> &msg);

	bool SupportsSeamlessFormatChange(const sptr<Message> &to) const;
	bool SupportsSeamlessuint32_tChange(const sptr<Message> &target_format) const;
	void RecordCodecSpecificData(const sptr<Message> &format);
	bool IsDiscontinuityPending() const;
	void FinishHandleDiscontinuity(bool flush_on_time_change);

	void NotifyResumeComplete();

	DISALLOW_COPY_AND_MOVE(Decoder);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_DECODER_H