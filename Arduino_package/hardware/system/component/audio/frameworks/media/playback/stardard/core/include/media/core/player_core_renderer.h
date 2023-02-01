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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_RENDERER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_RENDERER_H

#include "player_core.h"

namespace ameba::media
{

class AudioRenderSink;
class CodecBufferInfo;

class PlayerCore::Renderer : public MessageHandler
{
public:
	Renderer(const sptr<AudioRenderSink> &sink, const sptr<Message> &notify);

	void QueueBuffer(const sptr<CodecBufferInfo> &buffer, const sptr<Message> &notify_consumed);

	void QueueEOS(res_t final_result);

	void Flush(bool need_notify);
	void Pause();
	void Resume();
	res_t GetCurrentTime(int64_t *media_us);
	res_t SetVolume(float left, float right);
	void SetSpeed(float speed, float pitch);

	// re-open audio sink after all pending audio buffers played.
	void Changeuint32_t(const sptr<Message> &format, bool is_streaming, const sptr<Message> &notify);

	enum {
		kMsgEOS                      = 0x0056030f, //'eos ',
		kMsgFlushComplete            = 0x00560209, //'fluC',
		kMsgAudioSinkTearDown            = 0x0056040e, //'adTD',
	};

	enum AudioSinkTearDownReason {
		kReasonError = 0,   // Could restart
		kReasonTimeout,
		kReasonNonOffload,  // Restart only with non-offload.
	};

protected:
	virtual ~Renderer();

	virtual void OnMessage(const sptr<Message> &msg);

private:
	enum {
		kMsgFlush               = 0x00560204, //'flus',
		kMsgPause               = 0x00560205, //'paus',
		kMsgResume              = 0x00560206, //'resm',

		kMsgDrainAudioQueue     = 0x00560501, //'draA',
		kMsgQueueBuffer         = 0x00560500, //'queB',
		kMsgQueueEOS            = 0x0056050f, //'qEOS',

		kMsgChangeuint32_t   = 0x00560601, //'chgA',
	};

	// if mBuffer != nullptr, it's a buffer containing real data.
	// else if notify_consumed == nullptr, it's EOS.
	// else it's a tag for re-opening audio sink in different format.
	struct BufferChunck {
		sptr<CodecBufferInfo> codec_buffer_;
		sptr<Message> meta_;
		sptr<Message> notify_consumed_;
		size_t offset_;
		res_t final_result_;
		int32_t buffer_order_;
	};

	sptr<AudioRenderSink> audio_render_sink_;
	sptr<Message> notify_;
	Mutex lock_;
	List<BufferChunck> audio_chuncks_;

	uint32_t num_frames_written_;

	bool drain_audio_pending_;
	int32_t audio_chuncks_count_;
	int32_t audio_drain_count_;
	int32_t audio_eos_count_;

	int64_t audio_anchor_time_media_us_;
	int64_t audio_time_media_us_;

	bool notify_complete_audio_;

	// modified on only renderer's thread.
	bool paused_;
	int64_t pause_drain_audio_allowed_us_; // time when we can drain/deliver audio in pause mode.

	bool audio_torn_down_;

	struct PcmInfo {
		uint32_t channel_mask_;
		uint32_t audio_format_;
		int32_t num_channels_;
		int32_t sample_rate_;
	};
	PcmInfo current_pcm_info_;
	static const PcmInfo AUDIO_PCMINFO_INITIALIZER;

	int32_t buffers_queued_sum_;
	int32_t last_audio_buffer_drained_;

	bool OnDrainAudioQueue();
	int64_t GetPendingAudioPlayoutDurationUs();
	void DrainAudioQueue(int64_t delay_us = 0);

	void OnQueueBuffer(const sptr<Message> &msg);
	void OnQueueEOS(const sptr<Message> &msg);
	void OnFlush(const sptr<Message> &msg);
	void OnPause();
	void OnResume();
	int32_t GetChuncksCount();
	int32_t GetDrainCount();
	void OnAudioTearDown(AudioSinkTearDownReason reason);
	res_t OnOpenAudioRenderSink(
		const sptr<Message> &format,
		bool is_streaming);
	void OnCloseAudioRenderSink();
	void OnChangeuint32_t(const sptr<Message> &meta, const sptr<Message> &notify);

	void NotifyEOS(res_t final_result, int64_t delay_us = 0);
	void NotifyEOS_l(res_t final_result, int64_t delay_us = 0);
	void NotifyFlushComplete();
	void NotifyAudioTearDown(AudioSinkTearDownReason reason);

	void FlushChuncks(List<BufferChunck> *queue);
	bool DropBufferIfStale(const sptr<Message> &msg);

	int64_t GetDurationUsIfPlayedAtSampleRate(uint32_t num_frames);

	DISALLOW_COPY_AND_MOVE(Renderer);
};

} // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_RENDERER_H