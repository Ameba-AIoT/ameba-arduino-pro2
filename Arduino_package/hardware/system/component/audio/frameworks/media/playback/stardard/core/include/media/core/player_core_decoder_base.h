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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_DECODER_BASE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_DECODER_BASE_H

#include "media/utils/message_handler.h"

#include "player_core.h"

namespace ameba::media
{

class MediaCodec;

class PlayerCore::DecoderBase : public MessageHandler
{
public:
	explicit DecoderBase(const sptr<Message> &notify);

	void Configure(const sptr<Message> &format);
	void Init();
	void SetParameters(const sptr<Message> &params);

	// Synchronous call to ensure decoder will not request or send out data.
	void Pause();

	void SetRenderer(const sptr<Renderer> &renderer);

	void Flush();
	void Resume(bool need_notify);
	void StartShutdown();

	virtual sptr<Message> GetDecoderInfos() const
	{
		return infos_;
	}

	enum {
		kMsgShutdownCompleted   = 0x00550208, //'shDC',
		kMsgFlushCompleted      = 0x00550209, //'flsC',
		kMsgResumeCompleted     = 0x00550206, //'resC',
		kMsgInputDiscontinuity  = 0x00550306, //'inDi',
		kMsgEOS                 = 0x0055030f, //'eos ',
		kMsgError               = 0x0055060f, //'err ',
	};

protected:
	virtual ~DecoderBase();

	void StopLooper();

	virtual void OnMessage(const sptr<Message> &msg);

	virtual void OnConfigure(const sptr<Message> &format) = 0;
	virtual void OnSetParameters(const sptr<Message> &params) = 0;
	virtual void OnSetRenderer(const sptr<Renderer> &renderer) = 0;
	virtual void OnResume(bool need_notify) = 0;
	virtual void OnFlush() = 0;
	virtual void OnShutdown(bool need_notify) = 0;

	void OnRequestInputBuffers();
	virtual bool DoRequestBuffers() = 0;
	virtual void HandleError(int32_t err);

	sptr<Message> notify_;
	int32_t buffer_count_;
	bool paused_;
	sptr<Message> infos_;

private:
	enum {
		kMsgConfigure           = 0x00550101, //'conf',
		kMsgSetParameters       = 0x00550102, //'setP',
		kWhatSetRenderer         = 0x00550103, //'setR',
		kMsgShutdown            = 0x00550202, //'shuD',
		kMsgFlush               = 0x00550204, //'flus',
		kMsgPause               = 0x00550205, //'paus',
		kWhatRequestInputBuffers = 0x00550301, //'reqB',
	};

	sptr<MessageLooper> decoder_looper_;
	bool request_input_buffers_pending_;

	DISALLOW_COPY_AND_MOVE(DecoderBase);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_DECODER_BASE_H