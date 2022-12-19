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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_RTSP_MY_HANDLER_H_

#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_RTSP_MY_HANDLER_H_

//#define LOG_NDEBUG 0

#include <vector>
#include "packet_source.h"
#include "rtp_connection.h"
#include "rtsp_connection.h"
#include "session_description.h"

#include <ctype.h>

#include "media/utils/rbuffer.h"
#include "media/utils/rdebug.h"
#include "media/utils/message.h"
#include "media/common/media_defs.h"
#include "media/common/media_buffer.h"
#include "media/common/meta_data.h"
#include "media/common/packet_pool.h"
#include "utils/nocopyable.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

#if LOG_NDEBUG
#define UNUSED_UNLESS_VERBOSE(x) (void)(x)
#else
#define UNUSED_UNLESS_VERBOSE(x)
#endif

#undef LOG_TAG
#define LOG_TAG "RtspHandler"


// If no access units are received within 5 secs, assume that the rtp
// stream has ended and signal end of stream.
static int64_t kDataChunkTimeoutUs = 10000000ll;

// If no access units arrive for the first 10 secs after starting the
// stream, assume none ever will and signal EOS or switch transports.
static int64_t kStartupTimeoutUs = 10000000ll;

static int64_t kDefaultKeepAliveTimeoutUs = 60000000ll;

static int64_t kPauseDelayUs = 3000000ll;

// The allowed maximum number of stale access units at the beginning of
// a new sequence.
static int32_t kMaxAllowedStaleDataChunks = 20;

namespace ameba::media
{

extern RString MakeUserAgent()  ;

static bool GetAttribute(const char *s, const char *key, RString *value)
{
	value->Clear();

	size_t key_len = strlen(key);

	for (;;) {
		while (isspace(*s)) {
			++s;
		}

		const char *colon_pos = strchr(s, ';');

		size_t len =
			(colon_pos == NULL) ? strlen(s) : colon_pos - s;

		if (len >= key_len + 1 && s[key_len] == '=' && !strncmp(s, key, key_len)) {
			value->SetTo(&s[key_len + 1], len - key_len - 1);
			return true;
		}

		if (colon_pos == NULL) {
			return false;
		}

		s = colon_pos + 1;
	}
}

class RTSPHandler : public MessageHandler
{
public:
	enum {
		kMsgConnected                  = 0x00130201,//'conn',
		kMsgDisconnected               = 0x00130202,//'disc',
		kMsgRewindPaused                 = 0x00130207,//'spau',
		kMsgRewindDone                   = 0x00130208,//'sdon',
		kMsgRewindDiscontinuity          = 0x00130209,//'seeD',

		kMsgDataChunk                 = 0x00130301,//'accU',
		kMsgEOS                        = 0x0013030f,//'eos!',

		kMsgNormalPlayTimeMapping      = 0x00130600,//'nptM',
	};

	RTSPHandler(
		const char *url,
		const sptr<Message> &notify)
		: notify_(notify),
		  net_looper_(new MessageLooper),
		  rtsp_connection_(new RTSPConnection()),
		  rtp_connection_(new RTPConnection),
		  original_session_url_(url),
		  session_url_(url),
		  setup_done_(false),
		  rewind_pending_(false),
		  first_data_chunk_(true),
		  all_tracks_have_time_(false),
		  ntp_anchor_us_(-1),
		  media_anchor_us_(-1),
		  last_media_time_us_(0),
		  num_data_chunks_received_(0),
		  check_pending_(false),
		  check_count_(0),
		  check_timeout_count_(0),
		  try_tcp_interleaving_(false),
		  try_fake_rtcp_(false),
		  received_first_rtcp_packet_(false),
		  received_first_rtp_packet_(false),
		  rewindable_(true),
		  keep_alive_timeout_us_(kDefaultKeepAliveTimeoutUs),
		  keep_alive_count_(0),
		  pausing_(false),
		  pause_count_(0),
		  play_response_parsed_(false)
	{
		net_looper_->SetName("rtsp net");
		net_looper_->Start(false /* runOnCallingThread */, PRIORITY_HIGHEST);

		// Strip any authentication info from the session url, we don't
		// want to transmit user/pass in cleartext.
		RString host, path, user, pass;
		unsigned port;
		CHECK(RTSPConnection::ParseURL(
				  session_url_.Str(), &host, &port, &path, &user, &pass));

		if (user.Size() > 0) {
			session_url_.Clear();
			session_url_.Append("rtsp://");
			session_url_.Append(host);
			session_url_.Append(":");
			session_url_.Append(RStringPrintf("%u", port));
			session_url_.Append(path);

			RTLOGE("rewritten session url: '%s'", session_url_.Str());
		}

		session_host_ = host;
	}

	void Connect()
	{
		GetStrongLooper()->RegisterHandler(rtsp_connection_);
		(1 ? net_looper_ : GetStrongLooper())->RegisterHandler(rtp_connection_);

		sptr<Message> notify = new Message('biny', this);
		rtsp_connection_->ObserveBinaryData(notify);

		sptr<Message> reply = new Message(kMsgConnected, this);
		//connect to the server , and reply result to myhandler
		rtsp_connection_->Connect(original_session_url_.Str(), reply);
	}

	RString GetControlURL()
	{
		RString session_level_control_url;
		if (session_description_->FindAttribute(
				0,
				"a=control",
				&session_level_control_url)) {
			if (session_level_control_url.Compare("*") == 0) {
				return base_url_;
			} else {
				RString control_url;
				CHECK(MakeURL(
						  base_url_.Str(),
						  session_level_control_url.Str(),
						  &control_url));
				return control_url;
			}
		} else {
			return session_url_;
		}
	}

	void Disconnect()
	{
		(new Message('abor', this))->Post();
	}

	void Rewind(int64_t time_us)
	{
		sptr<Message> msg = new Message('rwd', this);
		msg->SetInt64("time", time_us);
		pause_count_++;
		msg->Post();
	}

	void ContinueRewindAfterPause(int64_t time_us)
	{
		sptr<Message> msg = new Message('see1', this);
		msg->SetInt64("time", time_us);
		msg->Post();
	}

	bool IsRewindable() const
	{
		return rewindable_;
	}

	void Pause()
	{
		sptr<Message> msg = new Message('paus', this);
		pause_count_++;
		msg->SetInt32("pausecheck", pause_count_);
		msg->Post();
	}

	void Resume()
	{
		sptr<Message> msg = new Message('resu', this);
		pause_count_++;
		msg->Post();
	}

	static void AddRR(const sptr<RBuffer> &buf)
	{
		uint8_t *ptr = buf->Data() + buf->Size();
		ptr[0] = 0x80 | 0;
		ptr[1] = 201;  // RR
		ptr[2] = 0;
		ptr[3] = 1;
		ptr[4] = 0xde;  // SSRC
		ptr[5] = 0xad;
		ptr[6] = 0xbe;
		ptr[7] = 0xef;

		buf->SetRange(0, buf->Size() + 8);
	}

	static void AddSDES(int s, const sptr<RBuffer> &buffer)
	{
		struct sockaddr_in addr;
		socklen_t addr_size = sizeof(addr);
		if (getsockname(s, (sockaddr *)&addr, &addr_size) != 0) {
			inet_aton("0.0.0.0", &(addr.sin_addr));
		}

		uint8_t *data = buffer->Data() + buffer->Size();
		data[0] = 0x80 | 1;
		data[1] = 202;  // SDES
		data[4] = 0xde;  // SSRC
		data[5] = 0xad;
		data[6] = 0xbe;
		data[7] = 0xef;

		size_t offset = 8;

		data[offset++] = 1;  // CNAME

		RString c_name = "ameba_rtsp@";
		c_name.Append(inet_ntoa(addr.sin_addr));
		data[offset++] = c_name.Size();

		memcpy(&data[offset], c_name.Str(), c_name.Size());
		offset += c_name.Size();

		data[offset++] = 6;  // TOOL

		RString tool = MakeUserAgent();

		data[offset++] = tool.Size();

		memcpy(&data[offset], tool.Str(), tool.Size());
		offset += tool.Size();

		data[offset++] = 0;

		if ((offset % 4) > 0) {
			size_t count = 4 - (offset % 4);
			switch (count) {
			case 3:
				data[offset++] = 0;
				goto case_2;

			case 2:
case_2:
				data[offset++] = 0;
				goto case_1;

			case 1:
case_1:
				data[offset++] = 0;
			}
		}

		size_t num_words = (offset / 4) - 1;
		data[2] = num_words >> 8;
		data[3] = num_words & 0xff;

		buffer->SetRange(buffer->Offset(), buffer->Size() + offset);
	}

	// In case we're behind NAT, fire off two UDP packets to the remote
	// rtp/rtcp ports to poke a hole into the firewall for future incoming
	// packets. We're going to send an RR/SDES RTCP packet to both of them.
	bool PokeAHole(int rtp_socket, int rtcp_socket, const RString &transport)
	{
		struct sockaddr_in addr;
		memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
		addr.sin_family = AF_INET;

		RString source;
		RString server_port;
		if (!GetAttribute(transport.Str(),
						  "source",
						  &source)) {
			RTLOGW("Missing 'source' field in Transport response. Using "
				   "RTSP endpoint address.");

			struct hostent *ent = gethostbyname(session_host_.Str());
			if (ent == NULL) {
				RTLOGE("Failed to look up address of session host '%s'",
					   session_host_.Str());

				return false;
			}

			addr.sin_addr.s_addr = *(in_addr_t *)ent->h_addr;
		} else {
			addr.sin_addr.s_addr = inet_addr(source.Str());
		}

		if (!GetAttribute(transport.Str(),
						  "server_port",
						  &server_port)) {
			RTLOGI("Missing 'server_port' field in Transport response.");
			return false;
		}

		int rtp_port, rtcp_port;
		if (sscanf(server_port.Str(), "%d-%d", &rtp_port, &rtcp_port) != 2
			|| rtp_port <= 0 || rtp_port > 65535
			|| rtcp_port <= 0 || rtcp_port > 65535
			|| rtcp_port != rtp_port + 1) {
			RTLOGE("Server picked invalid RTP/RTCP port pair %s,"
				   " RTP port must be even, RTCP port must be one higher.",
				   server_port.Str());

			return false;
		}

		if (rtp_port & 1) {
			RTLOGW("Server picked an odd RTP port, it should've picked an "
				   "even one, we'll let it pass for now, but this may break "
				   "in the future.");
		}

		if (addr.sin_addr.s_addr == INADDR_NONE) {
			return true;
		}

#if 0//fixme yiyuan
		if (IN_LOOPBACK(ntohl(addr.sin_addr.s_addr))) {
			// No firewalls to traverse on the loopback interface.
			return true;
		}
#endif
		// Make up an RR/SDES RTCP packet.
		sptr<RBuffer> buf = new RBuffer(65536);
		buf->SetRange(0, 0);
		AddRR(buf);
		AddSDES(rtp_socket, buf);

		addr.sin_port = htons(rtp_port);

		ssize_t n = sendto(
						rtp_socket, buf->Data(), buf->Size(), 0,
						(const sockaddr *)&addr, sizeof(addr));

		if (n < (ssize_t)buf->Size()) {
			RTLOGE("failed to poke a hole for RTP packets");
			return false;
		}

		addr.sin_port = htons(rtcp_port);

		n = sendto(
				rtcp_socket, buf->Data(), buf->Size(), 0,
				(const sockaddr *)&addr, sizeof(addr));

		if (n < (ssize_t)buf->Size()) {
			RTLOGE("failed to poke a hole for RTCP packets");
			return false;
		}

		RTLOGV("successfully poked holes.");

		return true;
	}

	static bool IsLiveStream(const sptr<SessionDescription> &desc)
	{
		RString attr_live_stream;
		if (desc->FindAttribute(0, "a=LiveStream", &attr_live_stream)) {
			ssize_t semicolon_pos = attr_live_stream.Find(";", 2);

			const char *live_stream_value;
			if (semicolon_pos < 0) {
				live_stream_value = attr_live_stream.Str();
			} else {
				RString val_string;
				val_string.SetTo(attr_live_stream,
								 semicolon_pos + 1,
								 attr_live_stream.Size() - semicolon_pos - 1);
				live_stream_value = val_string.Str();
			}

			uint32_t value = strtoul(live_stream_value, NULL, 10);
			if (value == 1) {
				RTLOGV("found live stream");
				return true;
			}
		} else {
			// It is a live stream if no duration is returned
			int64_t duration_us;
			if (!desc->GetDurationUs(&duration_us)) {
				RTLOGV("No duration found, assume live stream");
				return true;
			}
		}

		return false;
	}

	virtual void OnMessage(const sptr<Message> &msg)
	{
		switch (msg->What()) {
		case kMsgConnected: {
			int32_t result;
			CHECK(msg->FindInt32("result", &result));

			RTLOGI("connection request completed with result %d (%s)",
				   result, strerror(-result));

			if (result == OK) {
				RString request;
				request = "DESCRIBE ";
				request.Append(session_url_);
				request.Append(" RTSP/1.0\r\n");
				request.Append("Accept: application/sdp\r\n");
				request.Append("\r\n");

				sptr<Message> reply = new Message('desc', this);
				rtsp_connection_->SendRequest(request.Str(), reply);
			} else {
				(new Message(kMsgDisconnected, this))->Post();
			}
			break;
		}

		case kMsgDisconnected: {
			++keep_alive_count_;

			int32_t reconnect;
			if (msg->FindInt32("reconnect", &reconnect) && reconnect) {
				sptr<Message> reply = new Message(kMsgConnected, this);
				rtsp_connection_->Connect(original_session_url_.Str(), reply);
			} else {
				(new Message('quit', this))->Post();
			}
			break;
		}

		case 'desc': {
			int32_t result;
			CHECK(msg->FindInt32("result", &result));

			RTLOGI("DESCRIBE completed with result %d (%s)",
				   result, strerror(-result));

			if (result == OK) {
				sptr<RefPtr> obj;
				CHECK(msg->FindObject("response", &obj));
				sptr<RTSPResponse> response =
					static_cast<RTSPResponse *>(obj.get());

				if (response->status_code_ == 301 || response->status_code_ == 302) {
#if 1
					std::map<RString, RString>::iterator it = response->headers_.find("location");
					if (it == response->headers_.end()) {
						original_session_url_ = "" ;
						RTLOGE("can not get the location url info");
					} else {
						original_session_url_ = it->second ;
					}
#else
					ssize_t i = response->headers_.indexOfKey("location");
					CHECK_GE(i, 0);

					original_session_url_ = response->headers_.valueAt(i);
#endif
					session_url_ = original_session_url_;

					// Strip any authentication info from the session url, we don't
					// want to transmit user/pass in cleartext.
					RString host, path, user, pass;
					unsigned port;
					if (RTSPConnection::ParseURL(
							session_url_.Str(), &host, &port, &path, &user, &pass)
						&& user.Size() > 0) {
						session_url_.Clear();
						session_url_.Append("rtsp://");
						session_url_.Append(host);
						session_url_.Append(":");
						session_url_.Append(RStringPrintf("%u", port));
						session_url_.Append(path);

						RTLOGI("rewritten session url: '%s'", session_url_.Str());
					}

					sptr<Message> reply = new Message(kMsgConnected, this);
					rtsp_connection_->Connect(original_session_url_.Str(), reply);
					break;
				}

				if (response->status_code_ != 200) {
					result = UNKNOWN_ERROR;
				} else if (response->content_ == NULL) {
					result = ERROR_MALFORMED;
					RTLOGE("The response has no content.");
				} else {
					session_description_ = new SessionDescription;

					session_description_->setTo(
						response->content_->Data(),
						response->content_->Size());

					if (!session_description_->IsValid()) {
						RTLOGE("Failed to parse session description.");
						result = ERROR_MALFORMED;
					} else {
#if 1
						std::map<RString, RString>::iterator it = response->headers_.find("content-base");
						if (it != response->headers_.end()) {
							base_url_ = it->second ;
						} else {
							it = response->headers_.find("content-location");
							if (it != response->headers_.end()) {
								base_url_ = it->second ;
							} else {
								base_url_ = session_url_;
							}
						}
#else
						ssize_t i = response->headers_.indexOfKey("content-base");
						if (i >= 0) {
							base_url_ = response->headers_.valueAt(i);
						} else {
							i = response->headers_.indexOfKey("content-location");
							if (i >= 0) {
								base_url_ = response->headers_.valueAt(i);
							} else {
								base_url_ = session_url_;
							}
						}
#endif

						rewindable_ = !IsLiveStream(session_description_);

						if (!base_url_.StartsWith("rtsp://")) {
							// Some misbehaving servers specify a relative
							// URL in one of the locations above, combine
							// it with the absolute session URL to get
							// something usable...

							RTLOGW("Server specified a non-absolute base URL"
								   ", combining it with the session URL to "
								   "get something usable...");

							RString tmp;
							CHECK(MakeURL(
									  session_url_.Str(),
									  base_url_.Str(),
									  &tmp));

							base_url_ = tmp;
						}

						control_url_ = GetControlURL();

						if (session_description_->GetTracksNum() < 2) {
							// There's no actual tracks in this session.
							// The first "track" is merely session meta
							// data.

							RTLOGW("Session doesn't contain any playable "
								   "tracks. Aborting.");
							result = ERROR_UNSUPPORTED;
						} else {
							SetupTrack(1);
						}
					}
				}
			}

			if (result != OK) {
				sptr<Message> reply = new Message(kMsgDisconnected, this);
				rtsp_connection_->Disconnect(reply);
			}
			break;
		}

		case 'sdpl': {
			int32_t result;
			CHECK(msg->FindInt32("result", &result));

			RTLOGI("SDP connection request completed with result %d (%s)",
				   result, strerror(-result));

			if (result == OK) {
				sptr<RefPtr> obj;
				CHECK(msg->FindObject("description", &obj));
				session_description_ =
					static_cast<SessionDescription *>(obj.get());

				if (!session_description_->IsValid()) {
					RTLOGE("Failed to parse session description.");
					result = ERROR_MALFORMED;
				} else {
					base_url_ = session_url_;

					rewindable_ = !IsLiveStream(session_description_);

					control_url_ = GetControlURL();

					if (session_description_->GetTracksNum() < 2) {
						// There's no actual tracks in this session.
						// The first "track" is merely session meta
						// data.

						RTLOGW("Session doesn't contain any playable "
							   "tracks. Aborting.");
						result = ERROR_UNSUPPORTED;
					} else {
						SetupTrack(1);
					}
				}
			}

			if (result != OK) {
				sptr<Message> reply = new Message(kMsgDisconnected, this);
				rtsp_connection_->Disconnect(reply);
			}
			break;
		}

		case 'setu': {
			size_t index;
			CHECK(msg->FindSize("index", &index));

			TrackInfo *track = NULL;
			size_t track_index;
			if (msg->FindSize("track-index", &track_index)) {
				track = &tracks_.at(track_index);
			}

			int32_t result;
			CHECK(msg->FindInt32("result", &result));

			RTLOGI("SETUP(%d) completed with result %d (%s)",
				   index, result, strerror(-result));

			if (result == OK) {
				CHECK(track != NULL);

				sptr<RefPtr> obj;
				CHECK(msg->FindObject("response", &obj));
				sptr<RTSPResponse> response =
					static_cast<RTSPResponse *>(obj.get());

				if (response->status_code_ != 200) {
					result = UNKNOWN_ERROR;
				} else {
#if 1
					ssize_t i = 0 ;
					std::map<RString, RString>::iterator it = response->headers_.find("session");
					if (it == response->headers_.end()) {
						session_id_ = "" ;
						RTLOGE("can not get the session info");
					} else {
						session_id_ = it->second ;
					}
#else
					ssize_t i = response->headers_.indexOfKey("session");
					CHECK_GE(i, 0);
					session_id_ = response->headers_.valueAt(i);
#endif

					keep_alive_timeout_us_ = kDefaultKeepAliveTimeoutUs;
					RString timeout_string;
					if (GetAttribute(
							session_id_.Str(), "timeout", &timeout_string)) {
						char *end;
						unsigned long timeout_s =
							strtoul(timeout_string.Str(), &end, 10);

						if (end == timeout_string.Str() || *end != '\0') {
							RTLOGW("server specified malformed timeout '%s'",
								   timeout_string.Str());

							keep_alive_timeout_us_ = kDefaultKeepAliveTimeoutUs;
						} else if (timeout_s < 15) {
							RTLOGW("server specified too short a timeout "
								   "(%lu secs), using default.",
								   timeout_s);

							keep_alive_timeout_us_ = kDefaultKeepAliveTimeoutUs;
						} else {
							keep_alive_timeout_us_ = timeout_s * 1000000ll;

							RTLOGI("server specified timeout of %lu secs.",
								   timeout_s);
						}
					}

					i = session_id_.Find(";");
					if (i >= 0) {
						// Remove properties, i.e. ";timeout=90"
						session_id_.Erase(i, session_id_.Size() - i);
					}

					sptr<Message> notify = new Message(kMsgDataChunk, this);
					notify->SetSize("track-index", track_index);
#if 1
					it = response->headers_.find("session");
#else
					i = response->headers_.indexOfKey("transport");
					CHECK_GE(i, 0);
#endif

					if (track->rtp_socket_ != -1 && track->rtcp_socket_ != -1) {
						if (!track->using_interleaved_tcp_) {
							RString transport = it->second ;
							//RString transport = response->headers_.valueAt(i);

							// We are going to continue even if we were
							// unable to poke a hole into the firewall...
							PokeAHole(
								track->rtp_socket_,
								track->rtcp_socket_,
								transport);
						}
						RTLOGW("[yiyuan]add stream ");
						rtp_connection_->AddStream(
							track->rtp_socket_, track->rtcp_socket_,
							session_description_, index,
							notify, track->using_interleaved_tcp_);

						setup_done_ = true;
					} else {
						result = BAD_VALUE;
					}
				}
			}

			if (result != OK) {
				if (track) {
					if (!track->using_interleaved_tcp_) {
						close(track->rtp_socket_);
						close(track->rtcp_socket_);
					}
					tracks_.erase(std::begin(tracks_) + track_index);
					//tracks_.removeItemsAt(track_index);
				}
			}

			++index;
			if (result == OK && index < session_description_->GetTracksNum()) {
				SetupTrack(index);
			} else if (setup_done_) {
				++keep_alive_count_;
				PostKeepAlive();

				RString request = "PLAY ";
				request.Append(control_url_);
				request.Append(" RTSP/1.0\r\n");

				request.Append("Session: ");
				request.Append(session_id_);
				request.Append("\r\n");

				request.Append("\r\n");

				RTLOGD("[debug1] request msg is= '%s'", request.Str());

				sptr<Message> reply = new Message('play', this);
				rtsp_connection_->SendRequest(request.Str(), reply);
			} else {
				sptr<Message> reply = new Message(kMsgDisconnected, this);
				rtsp_connection_->Disconnect(reply);
			}
			break;
		}

		case 'play': {
			int32_t result;
			CHECK(msg->FindInt32("result", &result));

			RTLOGI("PLAY completed with result %d (%s)",
				   result, strerror(-result));

			if (result == OK) {
				sptr<RefPtr> obj;
				CHECK(msg->FindObject("response", &obj));
				sptr<RTSPResponse> response =
					static_cast<RTSPResponse *>(obj.get());

				if (response->status_code_ != 200) {
					result = UNKNOWN_ERROR;
				} else {
					ParsePlayResponse(response);
					PostTimeout();
				}
			}

			if (result != OK) {
				sptr<Message> reply = new Message(kMsgDisconnected, this);
				rtsp_connection_->Disconnect(reply);
			}

			break;
		}

		case 'aliv': {
			int32_t count;
			CHECK(msg->FindInt32("count", &count));

			if (count != keep_alive_count_) {
				// obsolete event.
				break;
			}

			RString request;
			request.Append("OPTIONS ");
			request.Append(session_url_);
			request.Append(" RTSP/1.0\r\n");
			request.Append("Session: ");
			request.Append(session_id_);
			request.Append("\r\n");
			request.Append("\r\n");

			sptr<Message> reply = new Message('opts', this);
			reply->SetInt32("count", keep_alive_count_);
			rtsp_connection_->SendRequest(request.Str(), reply);
			break;
		}

		case 'opts': {
			int32_t result;
			CHECK(msg->FindInt32("result", &result));

			RTLOGI("OPTIONS completed with result %d (%s)",
				   result, strerror(-result));

			int32_t count;
			CHECK(msg->FindInt32("count", &count));

			if (count != keep_alive_count_) {
				// obsolete event.
				break;
			}

			PostKeepAlive();
			break;
		}

		case 'abor': {
			for (size_t i = 0; i < tracks_.size(); ++i) {
				TrackInfo *info = &tracks_.at(i);

				if (!first_data_chunk_) {
					PostQueueEOS(i, ERROR_END_OF_STREAM);
				}

				if (!info->using_interleaved_tcp_) {
					RTLOGW("[yiyuan]remove msg ");
					rtp_connection_->RemoveStream(info->rtp_socket_, info->rtcp_socket_);

					close(info->rtp_socket_);
					close(info->rtcp_socket_);
				}
			}
			tracks_.clear();
			setup_done_ = false;
			rewind_pending_ = false;
			first_data_chunk_ = true;
			all_tracks_have_time_ = false;
			ntp_anchor_us_ = -1;
			media_anchor_us_ = -1;
			num_data_chunks_received_ = 0;
			received_first_rtcp_packet_ = false;
			received_first_rtp_packet_ = false;
			pausing_ = false;
			rewindable_ = true;

			sptr<Message> reply = new Message('tear', this);

			int32_t reconnect;
			if (msg->FindInt32("reconnect", &reconnect) && reconnect) {
				reply->SetInt32("reconnect", true);
			}

			RString request;
			request = "TEARDOWN ";

			// XXX should use aggregate url from SDP here...
			request.Append(session_url_);
			request.Append(" RTSP/1.0\r\n");

			request.Append("Session: ");
			request.Append(session_id_);
			request.Append("\r\n");

			request.Append("\r\n");

			rtsp_connection_->SendRequest(request.Str(), reply);
			break;
		}

		case 'tear': {
			int32_t result;
			CHECK(msg->FindInt32("result", &result));

			RTLOGI("TEARDOWN completed with result %d (%s)",
				   result, strerror(-result));

			sptr<Message> reply = new Message(kMsgDisconnected, this);

			int32_t reconnect;
			if (msg->FindInt32("reconnect", &reconnect) && reconnect) {
				reply->SetInt32("reconnect", true);
			}

			rtsp_connection_->Disconnect(reply);
			break;
		}

		case 'quit': {
			sptr<Message> msg = notify_->Duplicate();
			msg->SetInt32("what", kMsgDisconnected);
			msg->SetInt32("result", UNKNOWN_ERROR);
			msg->Post();
			break;
		}

		case 'chek': {
			int32_t count;
			CHECK(msg->FindInt32("count", &count));
			if (count != check_count_) {
				// This is an outdated message. Ignore.
				break;
			}

			if (num_data_chunks_received_ == 0) {
#if 1
				RTLOGI("stream ended? aborting.");
				(new Message('abor', this))->Post();
				break;
#else
				RTLOGI("haven't seen an AU in a looong time.");
#endif
			}

			num_data_chunks_received_ = 0;
			msg->Post(kDataChunkTimeoutUs);
			break;
		}

		case kMsgDataChunk: {
			if (rewind_pending_) {
				RTLOGV("Stale access unit.");
				break;
			}

			int32_t time_update;
			if (msg->FindInt32("time-update", &time_update) && time_update) {
				size_t track_index;
				CHECK(msg->FindSize("track-index", &track_index));

				uint32_t rtp_time;
				uint64_t ntp_time;
				CHECK(msg->FindInt32("rtp-time", (int32_t *)&rtp_time));
				CHECK(msg->FindInt64("ntp-time", (int64_t *)&ntp_time));

				OnTimeUpdate(track_index, rtp_time, ntp_time);
				break;
			}

			int32_t first;
			if (msg->FindInt32("first-rtcp", &first)) {
				received_first_rtcp_packet_ = true;
				break;
			}

			if (msg->FindInt32("first-rtp", &first)) {
				received_first_rtp_packet_ = true;
				break;
			}

			++num_data_chunks_received_;
			PostDataChunkTimeoutCheck();

			size_t track_index;
			CHECK(msg->FindSize("track-index", &track_index));

			if (track_index >= tracks_.size()) {
				RTLOGV("late packets ignored.");
				break;
			}

			TrackInfo *track = &tracks_.at(track_index);

			int32_t eos;
			if (msg->FindInt32("eos", &eos)) {
				RTLOGI("received BYE on track index %d", track_index);
				if (!all_tracks_have_time_ && DataReceivedOnAllChannels()) {
					RTLOGI("No time established => fake existing data");

					track->eos_received_ = true;
					try_fake_rtcp_ = true;
					received_first_rtcp_packet_ = true;
					FakeTimestamps();
				} else {
					PostQueueEOS(track_index, ERROR_END_OF_STREAM);
				}
				return;
			}

			if (rewind_pending_) {
				RTLOGV("we're rewinding, dropping stale packet.");
				break;
			}

			sptr<RBuffer> data_block;
			CHECK(msg->FindBuffer("access-unit", &data_block));
			OnDataChunkComplete(track_index, data_block);
			break;
		}

		case 'paus': {
			int32_t count;
			CHECK(msg->FindInt32("pausecheck", &count));
			if (count != pause_count_) {
				RTLOGV("Ignoring outdated pause message.");
				break;
			}

			if (!rewindable_) {
				RTLOGW("This is a live stream, ignoring pause request.[rewindable_=%d]", rewindable_);
				break;
			}

			if (pausing_) {
				RTLOGV("This stream is already paused.");
				break;
			}

			check_pending_ = true;
			++check_count_;
			pausing_ = true;

			RString request = "PAUSE ";
			request.Append(control_url_);
			request.Append(" RTSP/1.0\r\n");

			request.Append("Session: ");
			request.Append(session_id_);
			request.Append("\r\n");

			request.Append("\r\n");

			sptr<Message> reply = new Message('pau2', this);
			rtsp_connection_->SendRequest(request.Str(), reply);
			break;
		}

		case 'pau2': {
			int32_t result;
			CHECK(msg->FindInt32("result", &result));
			check_timeout_count_++;

			RTLOGI("PAUSE completed with result %d (%s)",
				   result, strerror(-result));
			break;
		}

		case 'resu': {
			if (pausing_ && rewind_pending_) {
				// If rewinding, Play will be sent from see1 instead
				break;
			}

			if (!pausing_) {
				// Dont send PLAY if we have not paused
				break;
			}
			RString request = "PLAY ";
			request.Append(control_url_);
			request.Append(" RTSP/1.0\r\n");

			request.Append("Session: ");
			request.Append(session_id_);
			request.Append("\r\n");

			request.Append("\r\n");

			RTLOGW("[debug3] request msg is= '%s'", request.Str());

			sptr<Message> reply = new Message('res2', this);
			rtsp_connection_->SendRequest(request.Str(), reply);
			break;
		}

		case 'res2': {
			int32_t result;
			CHECK(msg->FindInt32("result", &result));

			RTLOGI("PLAY (for resume) completed with result %d (%s)",
				   result, strerror(-result));

			check_pending_ = false;
			++check_count_;
			PostDataChunkTimeoutCheck();

			if (result == OK) {
				sptr<RefPtr> obj;
				CHECK(msg->FindObject("response", &obj));
				sptr<RTSPResponse> response =
					static_cast<RTSPResponse *>(obj.get());

				if (response->status_code_ != 200) {
					result = UNKNOWN_ERROR;
				} else {
					ParsePlayResponse(response);

					// Post new timeout in order to make sure to use
					// fake timestamps if no new Sender Reports arrive
					PostTimeout();
				}
			}

			if (result != OK) {
				RTLOGE("resume failed, aborting.");
				(new Message('abor', this))->Post();
			}

			pausing_ = false;
			break;
		}

		case 'rwd': {
			if (!rewindable_) {
				RTLOGW("This is a live stream, ignoring rewind request.");

				sptr<Message> msg = notify_->Duplicate();
				msg->SetInt32("what", kMsgRewindDone);
				msg->Post();
				break;
			}

			int64_t time_us;
			CHECK(msg->FindInt64("time", &time_us));

			rewind_pending_ = true;

			// Disable the access unit timeout until we resumed
			// playback again.
			check_pending_ = true;
			++check_count_;

			sptr<Message> reply = new Message('see0', this);
			reply->SetInt64("time", time_us);

			if (pausing_) {
				// PAUSE already sent
				RTLOGI("Pause already sent");
				reply->Post();
				break;
			}
			RString request = "PAUSE ";
			request.Append(control_url_);
			request.Append(" RTSP/1.0\r\n");

			request.Append("Session: ");
			request.Append(session_id_);
			request.Append("\r\n");

			request.Append("\r\n");

			rtsp_connection_->SendRequest(request.Str(), reply);
			break;
		}

		case 'see0': {
			// Session is paused now.
			res_t err = OK;
			msg->FindInt32("result", &err);

			int64_t time_us;
			CHECK(msg->FindInt64("time", &time_us));

			sptr<Message> notify = notify_->Duplicate();
			notify->SetInt32("what", kMsgRewindPaused);
			notify->SetInt32("err", err);
			notify->SetInt64("time", time_us);
			notify->Post();
			break;

		}

		case 'see1': {
			for (size_t i = 0; i < tracks_.size(); ++i) {
				TrackInfo *info = &tracks_.at(i);

				PostQueueRewindDiscontinuity(i);
				info->eos_received_ = false;

				info->rtp_anchor_ = 0;
				info->ntp_anchor_us_ = -1;
			}

			all_tracks_have_time_ = false;
			ntp_anchor_us_ = -1;

			// Start new timeoutcount to avoid getting timeout
			// before PLAY response arrive
			PostTimeout();

			int64_t time_us;
			CHECK(msg->FindInt64("time", &time_us));

			RString request = "PLAY ";
			request.Append(control_url_);
			request.Append(" RTSP/1.0\r\n");

			request.Append("Session: ");
			request.Append(session_id_);
			request.Append("\r\n");

			request.Append(
				RStringPrintf(
					"Range: npt=%lld-\r\n", time_us / 1000000ll));

			request.Append("\r\n");

			RTLOGW("[debug2] request msg is= '%s'", request.Str());

			sptr<Message> reply = new Message('see2', this);
			rtsp_connection_->SendRequest(request.Str(), reply);
			break;
		}

		case 'see2': {
			if (tracks_.size() == 0) {
				// We have already hit abor, break
				break;
			}

			int32_t result;
			CHECK(msg->FindInt32("result", &result));

			RTLOGI("PLAY (for rewind) completed with result %d (%s)",
				   result, strerror(-result));

			check_pending_ = false;
			++check_count_;
			PostDataChunkTimeoutCheck();

			if (result == OK) {
				sptr<RefPtr> obj;
				CHECK(msg->FindObject("response", &obj));
				sptr<RTSPResponse> response =
					static_cast<RTSPResponse *>(obj.get());

				if (response->status_code_ != 200) {
					result = UNKNOWN_ERROR;
				} else {
					ParsePlayResponse(response);

					// Post new timeout in order to make sure to use
					// fake timestamps if no new Sender Reports arrive
					PostTimeout();
#if 1
					ssize_t i = 0 ;
					std::map<RString, RString>::iterator it = response->headers_.find("rtp-info");
					if (it == response->headers_.end()) {
						RTLOGE("can not get the rtp-info ");
					} else {
						RTLOGV("rtp-info: %s", it->second.Str());
					}
#else
					ssize_t i = response->headers_.indexOfKey("rtp-info");
					CHECK_GE(i, 0);
					RTLOGV("rtp-info: %s", response->headers_.valueAt(i).Str());
#endif
					RTLOGI("rewind completed.");
				}
			}

			if (result != OK) {
				RTLOGE("rewind failed, aborting.");
				(new Message('abor', this))->Post();
			}

			pausing_ = false;
			rewind_pending_ = false;

			// Discard all stale access units.
			for (size_t i = 0; i < tracks_.size(); ++i) {
				TrackInfo *track = &tracks_.at(i);
				track->packets_.clear();
			}

			sptr<Message> msg = notify_->Duplicate();
			msg->SetInt32("what", kMsgRewindDone);
			msg->Post();
			break;
		}

		case 'biny': {
			sptr<RBuffer> buffer;
			CHECK(msg->FindBuffer("buffer", &buffer));

			int32_t index;
			CHECK(buffer->Meta()->FindInt32("index", &index));
			RTLOGD("[yiyuan]index=%d", index);
			rtp_connection_->InjectPacket(index, buffer);
			break;
		}

		case 'tiou': {
			int32_t timeout_count_check;
			CHECK(msg->FindInt32("tioucheck", &timeout_count_check));
			if (timeout_count_check != check_timeout_count_) {
				// This is an outdated message. Ignore.
				// This typically happens if a lot of rewinds are
				// performed, since new timeout messages now are
				// posted at rewind as well.
				break;
			}
			if (!received_first_rtcp_packet_) {
				if (DataReceivedOnAllChannels() && !try_fake_rtcp_) {
					RTLOGW("We received RTP packets but no RTCP packets, "
						   "using fake timestamps.");

					try_fake_rtcp_ = true;

					received_first_rtcp_packet_ = true;

					FakeTimestamps();
				} else if (!received_first_rtp_packet_ && !try_tcp_interleaving_) {
					RTLOGW("Never received any data, switching transports.");

					try_tcp_interleaving_ = true;

					sptr<Message> msg = new Message('abor', this);
					msg->SetInt32("reconnect", true);
					msg->Post();
				} else {
					RTLOGW("Never received any data, disconnecting.");
					(new Message('abor', this))->Post();
				}
			} else {
				if (!all_tracks_have_time_) {
					RTLOGW("We received some RTCP packets, but time "
						   "could not be established on all tracks, now "
						   "using fake timestamps");

					FakeTimestamps();
				}
			}
			break;
		}

		default:
			TRESPASS();
			break;
		}
	}

	void PostKeepAlive()
	{
		sptr<Message> msg = new Message('aliv', this);
		msg->SetInt32("count", keep_alive_count_);
		msg->Post((keep_alive_timeout_us_ * 9) / 10);
	}

	void cancelDataChunkTimeoutCheck()
	{
		RTLOGV("cancelDataChunkTimeoutCheck");
		++check_count_;
	}

	void PostDataChunkTimeoutCheck()
	{
		if (check_pending_) {
			return;
		}

		check_pending_ = true;
		sptr<Message> check = new Message('chek', this);
		check->SetInt32("count", check_count_);
		check->Post(kDataChunkTimeoutUs);
	}

	static void SplitString(
		const RString &s, const char *separator, List<RString> *items)
	{
		items->clear();
		size_t start = 0;
		while (start < s.Size()) {
			ssize_t offset = s.Find(separator, start);

			if (offset < 0) {
				items->push_back(RString(s, start, s.Size() - start));
				break;
			}

			items->push_back(RString(s, start, offset - start));
			start = offset + strlen(separator);
		}
	}

	void ParsePlayResponse(const sptr<RTSPResponse> &response)
	{
		play_response_parsed_ = true;
		if (tracks_.size() == 0) {
			RTLOGV("ParsePlayResponse: late packets ignored.");
			return;
		}

		std::map<RString, RString>::iterator i = response->headers_.find("range");
		if (i == response->headers_.end()) {
			// Server doesn't even tell use what range it is going to
			// play, therefore we won't support rewinding.
			return;
		}

		RString range = i->second;
		RTLOGV("Range: %s", range.Str());

		RString val;
		CHECK(GetAttribute(range.Str(), "npt", &val));

		float npt1, npt2;
		if (!SessionDescription::ParseNTPRange(val.Str(), &npt1, &npt2)) {
			// This is a live stream and therefore not rewindable.

			RTLOGI("This is a live stream");
			return;
		}

		//i = response->headers_.indexOfKey("rtp-info");
		i = response->headers_.find("rtp-info");
		//CHECK_GE(i, 0);

		RString rtp_info = i->second ;
		List<RString> stream_infos;
		SplitString(rtp_info, ",", &stream_infos);

		int n = 1;
		for (List<RString>::iterator it = stream_infos.begin();
			 it != stream_infos.end(); ++it) {
			(*it).Trim();
			RTLOGV("streamInfo[%d] = %s", n, (*it).Str());

			CHECK(GetAttribute((*it).Str(), "url", &val));

			size_t track_index = 0;
			while (track_index < tracks_.size()
				   && !(val == tracks_.at(track_index).url_)) {
				++track_index;
			}
			CHECK_LT(track_index, tracks_.size());

			CHECK(GetAttribute((*it).Str(), "seq", &val));

			char *end;
			unsigned long seq = strtoul(val.Str(), &end, 10);

			TrackInfo *info = &tracks_.at(track_index);
			//TrackInfo *info = &tracks_.editItemAt(track_index);
			info->first_seq_num_in_segment_ = seq;
			info->new_segment_ = true;
			info->allowed_stale_data_chunk_num_ = kMaxAllowedStaleDataChunks;

			CHECK(GetAttribute((*it).Str(), "rtptime", &val));

			uint32_t rtp_time = strtoul(val.Str(), &end, 10);

			RTLOGV("track #%d: rtp_time=%u <=> npt=%.2f, first_data_chunk_=%d", n, rtp_time, npt1, first_data_chunk_);

			info->normal_play_time_rtp_ = rtp_time;
			info->normal_play_time_us_ = (int64_t)(npt1 * 1E6);

			if (!first_data_chunk_) {
				PostNormalPlayTimeMapping(
					track_index,
					info->normal_play_time_rtp_, info->normal_play_time_us_);
			}

			++n;
		}
	}

	sptr<MetaData> GetTrackFormat(size_t index, int32_t *time_scale)
	{
		CHECK_GE(index, 0u);
		CHECK_LT(index, tracks_.size());

		const TrackInfo &info = tracks_.at(index);
		//const TrackInfo &info = tracks_.itemAt(index);

		*time_scale = info.time_scale_;

		return info.packet_source_->GetFormat();
	}

	size_t GetTracksNum() const
	{
		return tracks_.size();
	}

private:
	struct TrackInfo {
		RString url_;
		int rtp_socket_;
		int rtcp_socket_;
		bool using_interleaved_tcp_;
		uint32_t first_seq_num_in_segment_;
		bool new_segment_;
		int32_t allowed_stale_data_chunk_num_;

		uint32_t rtp_anchor_;
		int64_t ntp_anchor_us_;
		int32_t time_scale_;
		bool eos_received_;

		uint32_t normal_play_time_rtp_;
		int64_t normal_play_time_us_;

		sptr<PacketSource> packet_source_;

		// Stores packets temporarily while no notion of time
		// has been established yet.
		List<sptr<RBuffer> > packets_;
	};

	sptr<Message> notify_;
	sptr<MessageLooper> net_looper_;
	sptr<RTSPConnection> rtsp_connection_;
	sptr<RTPConnection> rtp_connection_;
	sptr<SessionDescription> session_description_;
	RString original_session_url_;  // This one still has user:pass@
	RString session_url_;
	RString session_host_;
	RString base_url_;
	RString control_url_;
	RString session_id_;
	bool setup_done_;
	bool rewind_pending_;
	bool first_data_chunk_;

	bool all_tracks_have_time_;
	int64_t ntp_anchor_us_;
	int64_t media_anchor_us_;
	int64_t last_media_time_us_;

	int64_t num_data_chunks_received_;
	bool check_pending_;
	int32_t check_count_;
	int32_t check_timeout_count_;
	bool try_tcp_interleaving_;
	bool try_fake_rtcp_;
	bool received_first_rtcp_packet_;
	bool received_first_rtp_packet_;
	bool rewindable_;
	int64_t keep_alive_timeout_us_;
	int32_t keep_alive_count_;
	bool pausing_;
	int32_t pause_count_;

	std::vector<TrackInfo> tracks_;
	//Vector<TrackInfo> tracks_;

	bool play_response_parsed_;

	void SetupTrack(size_t index)
	{
		sptr<PacketSource> source =
			new PacketSource(session_description_, index);

		if (source->Check() != OK) {
			RTLOGW("Unsupported format. Ignoring track #%d.", index);

			sptr<Message> reply = new Message('setu', this);
			reply->SetSize("index", index);
			reply->SetInt32("result", ERROR_UNSUPPORTED);
			reply->Post();
			return;
		}

		RString url;
		CHECK(session_description_->FindAttribute(index, "a=control", &url));

		RString track_url;
		CHECK(MakeURL(base_url_.Str(), url.Str(), &track_url));

		tracks_.push_back(TrackInfo());
		TrackInfo *info = &tracks_.at(tracks_.size() - 1);//get the last item
		//tracks_.push(TrackInfo());
		//TrackInfo *info = &tracks_.editItemAt(tracks_.size() - 1);
		info->url_ = track_url;
		info->packet_source_ = source;
		info->using_interleaved_tcp_ = false;
		info->first_seq_num_in_segment_ = 0;
		info->new_segment_ = true;
		info->allowed_stale_data_chunk_num_ = kMaxAllowedStaleDataChunks;
		info->rtp_socket_ = -1;
		info->rtcp_socket_ = -1;
		info->rtp_anchor_ = 0;
		info->ntp_anchor_us_ = -1;
		info->normal_play_time_rtp_ = 0;
		info->normal_play_time_us_ = 0ll;

		unsigned long PT;
		RString format_desc;
		RString format_params;
		session_description_->GetFormatType(index, &PT, &format_desc, &format_params);

		int32_t time_scale;
		int32_t num_channels;
		SessionDescription::ParseFormatDesc(
			format_desc.Str(), &time_scale, &num_channels);

		info->time_scale_ = time_scale;
		info->eos_received_ = false;

		RTLOGE("track #%d URL=%s", tracks_.size(), track_url.Str());

		RString request = "SETUP ";
		request.Append(track_url);
		request.Append(" RTSP/1.0\r\n");

		if (try_tcp_interleaving_) {
			size_t interleave_index = 2 * (tracks_.size() - 1);
			info->using_interleaved_tcp_ = true;
			info->rtp_socket_ = interleave_index;
			info->rtcp_socket_ = interleave_index + 1;

			request.Append("Transport: RTP/AVP/TCP;interleaved=");
			request.Append(interleave_index);
			request.Append("-");
			request.Append(interleave_index + 1);
		} else {
			unsigned rtp_port;
			RTPConnection::MakePortPair(
				&info->rtp_socket_, &info->rtcp_socket_, &rtp_port);

			//request.Append("Transport: RTP/AVP/UDP;unicast;client_port=");
			request.Append("Transport: RTP/AVP;unicast;client_port=");
			request.Append(rtp_port);
			request.Append("-");
			request.Append(rtp_port + 1);
		}

		request.Append("\r\n");

		if (index > 1) {
			request.Append("Session: ");
			request.Append(session_id_);
			request.Append("\r\n");
		}

		request.Append("\r\n");

		sptr<Message> reply = new Message('setu', this);
		reply->SetSize("index", index);
		reply->SetSize("track-index", tracks_.size() - 1);
		rtsp_connection_->SendRequest(request.Str(), reply);
	}

	static bool MakeURL(const char *base_url, const char *url, RString *out)
	{
		out->Clear();

		if (strncasecmp("rtsp://", base_url, 7)) {
			// Base URL must be absolute
			return false;
		}

		if (!strncasecmp("rtsp://", url, 7)) {
			// "url" is already an absolute URL, ignore base URL.
			out->SetTo(url);
			return true;
		}

		size_t n = strlen(base_url);
		out->SetTo(base_url);
		if (base_url[n - 1] != '/') {
			out->Append("/");
		}
		out->Append(url);

		return true;
	}

	void FakeTimestamps()
	{
		ntp_anchor_us_ = -1ll;
		for (size_t i = 0; i < tracks_.size(); ++i) {
			OnTimeUpdate(i, 0, 0ll);
		}
	}

	bool DataReceivedOnAllChannels()
	{
		TrackInfo *track;
		for (size_t i = 0; i < tracks_.size(); ++i) {
			track = &tracks_.at(i);
			//track = &tracks_.editItemAt(i);
			if (track->packets_.empty()) {
				return false;
			}
		}
		return true;
	}

	void HandleFirstDataChunk()
	{
		if (first_data_chunk_) {
			sptr<Message> msg = notify_->Duplicate();
			msg->SetInt32("what", kMsgConnected);
			msg->Post();

			if (rewindable_) {
				for (size_t i = 0; i < tracks_.size(); ++i) {
					TrackInfo *info = &tracks_.at(i);
					//TrackInfo *info = &tracks_.editItemAt(i);

					PostNormalPlayTimeMapping(
						i,
						info->normal_play_time_rtp_, info->normal_play_time_us_);
				}
			}

			first_data_chunk_ = false;
		}
	}

	void OnTimeUpdate(int32_t track_index, uint32_t rtp_time, uint64_t ntp_time)
	{
		RTLOGV("onTimeUpdate track %d, rtp_time = 0x%08x, ntp_time = %#016llx",
			   track_index, rtp_time, (long long)ntp_time);

		int64_t ntp_time_us = (int64_t)(ntp_time * 1E6 / (1ll << 32));

		TrackInfo *track = &tracks_.at(track_index);
		//TrackInfo *track = &tracks_.editItemAt(track_index);

		track->rtp_anchor_ = rtp_time;
		track->ntp_anchor_us_ = ntp_time_us;

		if (ntp_anchor_us_ < 0) {
			ntp_anchor_us_ = ntp_time_us;
			media_anchor_us_ = last_media_time_us_;
		}

		if (!all_tracks_have_time_) {
			bool all_tracks_have_time = (tracks_.size() > 0);
			for (size_t i = 0; i < tracks_.size(); ++i) {
				TrackInfo *track = &tracks_.at(i);
				//TrackInfo *track = &tracks_.editItemAt(i);
				if (track->ntp_anchor_us_ < 0) {
					all_tracks_have_time = false;
					break;
				}
			}
			if (all_tracks_have_time) {
				all_tracks_have_time_ = true;
				RTLOGI("Time now established for all tracks.");
			}
		}
		if (all_tracks_have_time_ && DataReceivedOnAllChannels()) {
			HandleFirstDataChunk();

			// Time is now established, lets start timestamping immediately
			for (size_t i = 0; i < tracks_.size(); ++i) {
				if (OK != ProcessDataChunkQueue(i)) {
					return;
				}
			}
			for (size_t i = 0; i < tracks_.size(); ++i) {
				TrackInfo *trackInfo = &tracks_.at(i);
				//TrackInfo *trackInfo = &tracks_.editItemAt(i);
				if (trackInfo->eos_received_) {
					PostQueueEOS(i, ERROR_END_OF_STREAM);
					trackInfo->eos_received_ = false;
				}
			}
		}
	}

	res_t ProcessDataChunkQueue(int32_t track_index)
	{
		TrackInfo *track = &tracks_.at(track_index);
		//TrackInfo *track = &tracks_.editItemAt(track_index);
		while (!track->packets_.empty()) {
			sptr<RBuffer> data_block = *track->packets_.begin();
			track->packets_.erase(track->packets_.begin());

			uint32_t seq_num = (uint32_t)data_block->Int32Data();
			if (track->new_segment_) {
				// The sequence number from RTP packet has only 16 bits and is extended
				// by RTPData. Only the low 16 bits of seq in RTP-Info of reply of
				// RTSP "PLAY" command should be used to detect the first RTP packet
				// after rewinding.
				if (rewindable_) {
					if (track->allowed_stale_data_chunk_num_ > 0) {
						uint32_t seq_num16 = seq_num & 0xffff;
						uint32_t first_seq_num_in_segment16 = track->first_seq_num_in_segment_ & 0xffff;
						if (seq_num16 > first_seq_num_in_segment16 + kMaxAllowedStaleDataChunks
							|| seq_num16 < first_seq_num_in_segment16) {
							// Not the first rtp packet of the stream after rewinding, discarding.
							track->allowed_stale_data_chunk_num_--;
							RTLOGV("discarding stale access unit (0x%x : 0x%x)",
								   seq_num, track->first_seq_num_in_segment_);
							continue;
						}
						RTLOGW_IF(seq_num16 != first_seq_num_in_segment16,
								  "Missing the first packet(%u), now take packet(%u) as first one",
								  track->first_seq_num_in_segment_, seq_num);
					} else { // track->allowed_stale_data_chunk_num_ <= 0
						num_data_chunks_received_ = 0;
						RTLOGW_IF(track->allowed_stale_data_chunk_num_ == 0,
								  "Still no first rtp packet after %d stale ones",
								  kMaxAllowedStaleDataChunks);
						track->allowed_stale_data_chunk_num_ = -1;
						return UNKNOWN_ERROR;
					}
				}

				// Now found the first rtp packet of the stream after rewinding.
				track->first_seq_num_in_segment_ = seq_num;
				track->new_segment_ = false;
			}

			if (seq_num < track->first_seq_num_in_segment_) {
				RTLOGV("dropping stale access-unit (%d < %d)",
					   seq_num, track->first_seq_num_in_segment_);
				continue;
			}

			if (AddMediaTimestamp(track_index, track, data_block)) {
				PostQueueDataChunk(track_index, data_block);
			}
		}
		return OK;
	}

	void OnDataChunkComplete(
		int32_t track_index, const sptr<RBuffer> &data_block)
	{
		TrackInfo *track = &tracks_.at(track_index);
		//TrackInfo *track = &tracks_.editItemAt(track_index);
		track->packets_.push_back(data_block);

		uint32_t seq_num = (uint32_t)data_block->Int32Data();
		RTLOGV("OnDataChunkComplete track %d storing accessunit %u", track_index, seq_num);

		if (!play_response_parsed_) {
			RTLOGV("play response is not parsed");
			return;
		}

		HandleFirstDataChunk();

		if (!all_tracks_have_time_) {
			RTLOGV("storing data_block, no time established yet");
			return;
		}

		if (OK != ProcessDataChunkQueue(track_index)) {
			return;
		}

		if (track->eos_received_) {
			PostQueueEOS(track_index, ERROR_END_OF_STREAM);
			track->eos_received_ = false;
		}
	}

	bool AddMediaTimestamp(
		int32_t track_index, const TrackInfo *track,
		const sptr<RBuffer> &data_block)
	{
		UNUSED_UNLESS_VERBOSE(track_index);

		uint32_t rtp_time;
		CHECK(data_block->Meta()->FindInt32(
				  "rtp-time", (int32_t *)&rtp_time));

		int64_t rel_rtp_time_us =
			(((int64_t)rtp_time - (int64_t)track->rtp_anchor_) * 1000000ll)
			/ track->time_scale_;

		int64_t ntp_time_us = track->ntp_anchor_us_ + rel_rtp_time_us;

		int64_t media_time_us = media_anchor_us_ + ntp_time_us - ntp_anchor_us_;

		if (media_time_us > last_media_time_us_) {
			last_media_time_us_ = media_time_us;
		}

		if (media_time_us < 0) {
			RTLOGV("dropping early data_block.");
			return false;
		}

		RTLOGV("track %d rtp_time=%u media_time_us = %lld us (%.2f secs)",
			   track_index, rtp_time, (long long)media_time_us, media_time_us / 1E6);

		data_block->Meta()->SetInt64("time_us", media_time_us);

		return true;
	}

	void PostQueueDataChunk(
		size_t track_index, const sptr<RBuffer> &data_block)
	{
		sptr<Message> msg = notify_->Duplicate();
		msg->SetInt32("what", kMsgDataChunk);
		msg->SetSize("track_index", track_index);
		msg->SetBuffer("data_block", data_block);
		msg->Post();
	}

	void PostQueueEOS(size_t track_index, res_t final_result)
	{
		sptr<Message> msg = notify_->Duplicate();
		msg->SetInt32("what", kMsgEOS);
		msg->SetSize("track_index", track_index);
		msg->SetInt32("final_result", final_result);
		msg->Post();
	}

	void PostQueueRewindDiscontinuity(size_t track_index)
	{
		sptr<Message> msg = notify_->Duplicate();
		msg->SetInt32("what", kMsgRewindDiscontinuity);
		msg->SetSize("track_index", track_index);
		msg->Post();
	}

	void PostNormalPlayTimeMapping(
		size_t track_index, uint32_t rtp_time, int64_t npt_us)
	{
		sptr<Message> msg = notify_->Duplicate();
		msg->SetInt32("what", kMsgNormalPlayTimeMapping);
		msg->SetSize("track_index", track_index);
		msg->SetInt32("rtp_time", rtp_time);
		msg->SetInt64("npt_us", npt_us);
		msg->Post();
	}

	void PostTimeout()
	{
		sptr<Message> timeout = new Message('tiou', this);
		check_timeout_count_++;
		timeout->SetInt32("tioucheck", check_timeout_count_);

		int64_t startup_timeout_us;
		startup_timeout_us = kStartupTimeoutUs;
		timeout->Post(startup_timeout_us);
	}

	DISALLOW_COPY_AND_MOVE(RTSPHandler);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_RTSP_MY_HANDLER_H_