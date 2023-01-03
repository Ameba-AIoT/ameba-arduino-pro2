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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_H

#include <atomic>

#include "media/utils/message_handler.h"
#include "player_driver.h"

namespace ameba::media
{

class Message;
class MetaData;
class DataSource;
class AudioRenderSink;
class PlayerDriver;

class PlayerCore : public MessageHandler
{
public:
	explicit PlayerCore();

	void Init(PlayerDriver *driver);

	void SetSourceAsync(const char *url);
	void SetSourceAsync(const sptr<DataSource> &source);

	void PrepareAsync();
	void Start();
	void Pause();
	void ResetAsync();
	void RewindAsync(int64_t rewind_time_us, bool need_notify = false);
	res_t SetVolume(float left, float right);
	res_t SetSpeed(float speed, float pitch);

	void SetAudioRenderSink(const sptr<AudioRenderSink> &sink);
	res_t GetCurrentTime(int64_t *media_us);

protected:
	virtual ~PlayerCore();

	virtual void OnMessage(const sptr<Message> &msg);

public:
	class Source;

private:
	class Decoder;
	class DecoderBase;
	class GenericSource;
	class RTSPSource;
	class Renderer;
	class Action;
	class RewindAction;
	class ResumeDecoderAction;
	class FlushDecoderAction;
	class DummyAction;

	enum {
		kMsgSetSource                 = 0x00510101, //'stS',
		kMsgPrepare                    = 0x00510102, //'prep',
		kMsgScanSources             = 0x00510103, //'scan',
		kMsgSetAudioRenderSink  = 0x00510104, //'audS',
		//kWhatMoreDataQueued             = 'more',
		//kWhatConfigPlayback             = 'cfPB',
		//kWhatConfigSync                 = 'cfSy',
		//kWhatGetPlaybackSettings        = 'gPbS',
		//kWhatGetSyncSettings            = 'gSyS',
		kMsgStart                          = 0x00510201, //'strt',
		kMsgReset                       = 0x00510202, //'rset',
		kMsgPause                       = 0x00510205, //'paus',
		kMsgResume                      = 0x00510206, //'rsme',
		kMsgRewind                       = 0x00510207, //'rwd',

		kMsgSourceEvent             = 0x00510401, //'srcN',
		kMsgRendererEvent          = 0x00510404, //'renN',
		kMsgSinkEvent                = 0x00510405, //'audN',
		//kWhatClosedCaptionNotify        = 'capN',
		//kWhatPollDuration               = 'polD',
		//kWhatGetTrackInfo               = 'gTrI',
		//kWhatGetSelectedTrack           = 'gSel',
		//kWhatSelectTrack                = 'selT',
		//kWhatGetBufferingSettings       = 'gBus',
		//kWhatSetBufferingSettings       = 'sBuS',
		//kMsgPrepareDrm                 = 'pDrm',
		//kMsgReleaseDrm                 = 'rDrm',
		//kWhatMediaClockNotify           = 'mckN',
		kMsgSetSpeed                 = 0x00510406,
		kMsgSetVolume                 = 0x00510407,
	};

	PlayerDriver *driver_;
	Mutex source_lock_;
	sptr<Source> source_;

	sptr<DecoderBase> audio_decoder_;
	int32_t audio_decoder_count_;
	Mutex decoder_lock_;

	sptr<Renderer> renderer_;
	sptr<MessageLooper> renderer_looper_;
	int32_t renderer_count_;

	sptr<AudioRenderSink> audio_sink_;

	int64_t previous_rewind_time_us_;

	List<sptr<Action> > pending_actions_;

	bool eos_;

	bool scan_sources_pending_;
	int32_t scan_sources_count_;

	enum FlushStatus {
		NONE,
		STATE_FLUSHING_DECODER,
		STATE_FLUSHING_DECODER_SHUTDOWN,
		SHUTTING_DOWN_DECODER,
		STATE_FLUSHED,
		SHUT_DOWN,
	};

	enum FlushAction {
		FLUSH_ACTION_NONE,
		FLUSH_ACTION_FLUSH,
		FLUSH_ACTION_SHUTDOWN,
	};

	// Status of flush responses from the decoder and renderer.
	bool flush_complete_[2]; //0-render; 1- decoder
	FlushStatus audio_flush_status_;

	// Status of flush responses from the decoder and renderer.
	bool resume_pending_;

	bool started_;
	bool prepared_;
	bool resetting_;
	bool source_started_;

	// Pause state
	// two cases may cause pause
	// 1. request by client
	// 2. pause for internal buffering
	bool paused_;
	bool paused_by_client_;
	bool paused_for_buffering_;

	typedef enum {
		SOURCE_TYPE_NONE,
		SOURCE_TYPE_HTTP_LIVE,
		SOURCE_TYPE_RTSP,
		SOURCE_TYPE_GENERIC_URL,
		SOURCE_TYPE_GENERIC_FD,
		SOURCE_TYPE_MEDIA,
		SOURCE_TYPE_STREAM,
	} SOURCE_TYPE;

	std::atomic<SOURCE_TYPE> source_type_;

	res_t CreateDecoder(sptr<DecoderBase> *decoder);

	void OnStart(int64_t start_time_us = -1);
	void OnResume();
	void OnPause();

	void HandleFlushComplete(bool is_decoder);
	void FinishFlushIfPossible();

	void FinishResume();
	void ActResumeDecoders(bool need_notify);
	void ActRewind(int64_t rewind_time_us);
	void ActDecoderFlush(FlushAction action);
	void FlushDecoder(bool shut_down);
	void ActReset();
	void ActPendingActions();

	void postScanSources();

	void NotifyRewindComplete();

	void OnSourceNotify(const sptr<Message> &msg);

	void OnSetSpeed(float speed, float pitch);

	void OnSetVolume(float left, float right);

	DISALLOW_COPY_AND_MOVE(PlayerCore);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_H
