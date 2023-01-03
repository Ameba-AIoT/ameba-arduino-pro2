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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTP_CONNECTION_H

#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTP_CONNECTION_H

#include "utils/list.h"

#include "media/utils/message_handler.h"

namespace ameba::media
{

class RBuffer;
class RTPData;
class SessionDescription;

class RTPConnection : public MessageHandler
{
public:
	enum Flags {
		kRegularlyRequestFIR = 2,
	};

	explicit RTPConnection(uint32_t flags = 0);

	void AddStream(
		int rtp_socket, int rtcp_socket,
		const sptr<SessionDescription> &session_desc, size_t index,
		const sptr<Message> &notify,
		bool injected);

	void RemoveStream(int rtp_socket, int rtcp_socket);

	void InjectPacket(int index, const sptr<RBuffer> &buffer);

	// Creates a pair of UDP datagram sockets bound to adjacent ports
	// (the rtp_socket is bound to an even port, the rtcp_socket to the
	// next higher port).
	static void MakePortPair(int *rtp_socket, int *rtcp_socket, unsigned *rtp_port);

protected:
	virtual ~RTPConnection();
	virtual void OnMessage(const sptr<Message> &msg);

private:
	enum {
		kMsgAddStream,
		kMsgRemoveStream,
		kMsgPollStreams,
		kMsgInjectPacket,
	};

	static const int64_t kSelectTimeoutUs;

	uint32_t flags_;

	struct StreamInfo;
	List<StreamInfo> stream_infos_;

	bool poll_event_pending_;
	int64_t last_receiver_report_time_us_;

	void OnAddStream(const sptr<Message> &msg);
	void OnRemoveStream(const sptr<Message> &msg);
	void OnPollStreams();
	void OnInjectPacket(const sptr<Message> &msg);
	void OnSendReceiverReports();

	res_t Receive(StreamInfo *info, bool receiveRTP);

	res_t ParseRTP(StreamInfo *info, const sptr<RBuffer> &buffer);
	res_t ParseRTCP(StreamInfo *info, const sptr<RBuffer> &buffer);
	res_t ParseSR(StreamInfo *info, const uint8_t *data, size_t size);
	res_t ParseBYE(StreamInfo *info, const uint8_t *data, size_t size);

	sptr<RTPData> GetRTPData(StreamInfo *info, uint32_t id);

	void PostPollEvent();

	DISALLOW_COPY_AND_MOVE(RTPConnection);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTP_CONNECTION_H
