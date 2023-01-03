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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_RTSP_SOURCE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_RTSP_SOURCE_H

#include <vector>
#include "media/common/media_buffer.h"
#include "media/common/media_track.h"

#include "player_core.h"
#include "player_core_source.h"

namespace ameba::media
{

class MessageLooper;
class ReplyMessage;
class MediaBufferBase;
class PacketPool;
class RTSPHandler;

class PlayerCore::RTSPSource : public PlayerCore::Source
{
public:
	RTSPSource(const sptr<Message> &notify, const char *url);

	virtual void PrepareAsync();
	virtual void Start();
	virtual void Stop();

	virtual res_t FeedMoreTSData();

	virtual res_t DequeueDataChunk(MediaBufferBase **data_block);

	virtual res_t GetDuration(int64_t *duration_us);
	virtual res_t Rewind(int64_t rewind_time_us)  override;

	void OnMessage(const sptr<Message> &msg);

protected:
	virtual ~RTSPSource();

	virtual sptr<MetaData> GetFormatMeta();

private:
	enum {
		kMsgDisconnect      = 0x00540202,//'disc',
		kMsgRewind           = 0x00540207,//'rwd',
		kMsgPollBuffering   = 0x00540301,//'poll',
		kMsgSignalEOS       = 0x0054030f,//'eos ',
		kMsgNotify             = 0x00540400,//'noti',
	};

	enum RTSPSourceState {
		RTSP_SOURCE_STATE_DISCONNECTED,
		RTSP_SOURCE_STATE_CONNECTING,
		RTSP_SOURCE_STATE_CONNECTED,
		RTSP_SOURCE_STATE_REWINDING,
	};

	struct TrackInfo {
		sptr<PacketPool> packets_;
		int32_t time_scale_;
		uint32_t rtp_time_;
		int64_t normal_playtime_us_;
		bool ntp_mapping_valid_;
	};

	RString url_;
	uint32_t flags_;
	RTSPSourceState state_;
	res_t final_result_;
	sptr<ReplyMessage> disconnect_reply_id_;
	Mutex buffering_lock_;
	bool buffering_;
	bool at_preparation_stage_;
	bool eos_pending_;

	Mutex buffering_settings_lock_;

	int prepare_mark_ms_;
	// When cached data is above this mark, playback will be resumed if it has been paused
	// due to low cached data.
	int resume_playback_mark_ms_;

	sptr<MessageLooper> looper_;
	sptr<RTSPHandler> handler_;

	std::vector<TrackInfo> tracks_;
	sptr<PacketPool> audio_packet_;

	int32_t rewind_count_;

	int64_t eos_timeout_;

	sptr<ReplyMessage> rewind_reply_id_;

private:
	sptr<PacketPool> GetAudioPackets();

	void OnConnected();
	void OnDisconnected(const sptr<Message> &msg);
	void FinishDisconnectIfPossible();

	void ActRewind(int64_t rewind_time_us);
	void SchedulePollBuffering();
	void CheckBuffering(
		bool *prepared,
		bool *underflow,
		bool *overflow,
		bool *start_server,
		bool *finished);
	void OnPollBuffering();

	bool HaveSufficientDataOnAllTracks();

	void SetEOSTimeout(bool audio, int64_t timeout);
	void SetError(res_t err);
	void StartBufferingIfNecessary();
	bool StopBufferingIfNecessary();
	void FinishRewind(res_t err);

	void PostSourceEOSIfNecessary();
	void SignalSourceEOS(res_t result);
	void OnSignalEOS(const sptr<Message> &msg);

	bool SourceNearEOS(bool audio);
	bool SourceReachedEOS(bool audio);

	DISALLOW_COPY_AND_MOVE(RTSPSource);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_RTSP_SOURCE_H