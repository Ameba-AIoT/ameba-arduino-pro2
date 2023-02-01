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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTSP_CONNECTION_H
#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTSP_CONNECTION_H

#include <map>
#include "media/utils/message_handler.h"
#include "media/utils/rstring.h"

namespace ameba::media
{

class RBuffer;

class RTSPResponse : public RefPtr
{
public:
	unsigned long status_code_;
	RString status_line_;
	std::map<RString, RString> headers_;
	sptr<RBuffer> content_;
};

class RTSPConnection : public MessageHandler
{
public:
	explicit RTSPConnection();

	void Connect(const char *url, const sptr<Message> &reply);
	void Disconnect(const sptr<Message> &reply);

	void SendRequest(const char *request, const sptr<Message> &reply);

	void ObserveBinaryData(const sptr<Message> &reply);

	static bool ParseURL(
		const char *url, RString *host, unsigned *port, RString *path,
		RString *user, RString *pass);

protected:
	virtual ~RTSPConnection();
	virtual void OnMessage(const sptr<Message> &msg);

private:
	enum RTSPConnectionState {
		RTSP_CONNECTION_STATE_DISCONNECTED,
		RTSP_CONNECTION_STATE_CONNECTING,
		RTSP_CONNECTION_STATE_CONNECTED,
	};

	enum {
		kMsgConnect            = 0x00140201,//'conn',
		kMsgCompleteConnection = 0x00140202,//'comc',
		kMsgSendRequest        = 0x00140203,//'sreq',
		kMsgReceiveResponse    = 0x00140204,//'rres',
		kMsgObserveBinaryData  = 0x00140205,//'obin',
		kMsgDisconnect         = 0x00140206,//'disc',
	};

	enum AuthType {
		AUTH_TYPE_NONE,
		AUTH_TYPE_BASIC,
		AUTH_TYPE_DIGEST
	};

	static const int64_t kSelectTimeoutUs;

	static const RString sUserAgent;

	RTSPConnectionState state_;
	RString user_, pass_;
	AuthType auth_type_;
	RString nonce_;
	int socket_;
	int32_t connection_id_;
	int32_t next_c_seq_;
	bool receive_response_event_pending_;

	std::map<int32_t, sptr<Message> > pending_messages_;

	sptr<Message> observe_binary_message_;

	void ActDisconnect();

	void OnConnect(const sptr<Message> &msg);
	void OnDisconnect(const sptr<Message> &msg);
	void OnCompleteConnection(const sptr<Message> &msg);
	void OnSendRequest(const sptr<Message> &msg);
	void OnReceiveResponse();

	void FlushPendingMessages();
	void PostReceiveReponseEvent();

	// Return false iff something went unrecoverably wrong.
	bool ReceiveRTSPReponse();
	res_t Receive(void *data, size_t size);
	bool ReceiveLine(RString *line);
	sptr<RBuffer> ReceiveBinaryData();
	bool NotifyListener(const sptr<RTSPResponse> &response);

	bool ParseAuthenticationMethod(const sptr<RTSPResponse> &response);
	void AddAuthentication(RString *request);

	void AddUserAgent(RString *request) const;

	res_t FindPendingRequest(
		const sptr<RTSPResponse> &response, ssize_t *index) ;

	bool HandleServerRequest(const sptr<RTSPResponse> &request);

	static bool ParseSingleUnsignedLong(
		const char *from, unsigned long *x);

	DISALLOW_COPY_AND_MOVE(RTSPConnection);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTSP_CONNECTION_H
