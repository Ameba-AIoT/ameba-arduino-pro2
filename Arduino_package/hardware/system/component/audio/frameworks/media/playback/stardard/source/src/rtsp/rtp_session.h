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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTP_SESSION_H
#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTP_SESSION_H

#include <vector>
#include "media/utils/message_handler.h"

namespace ameba::media
{

class PacketSource;
class RTPConnection;
class SessionDescription;

class RTPSession : public MessageHandler
{
public:
	RTPSession();

	res_t Setup(const sptr<SessionDescription> &desc);

	size_t GetTracksNum();

protected:
	virtual void OnMessage(const sptr<Message> &msg);

	virtual ~RTPSession();

private:
	enum {
		kMsgDataChunkComplete = 'accu'
	};

	struct TrackInfo {
		int rtp_socket_;
		int rtcp_socket_;

		sptr<PacketSource> packet_source_;
	};

	res_t init_check_;
	sptr<SessionDescription> session_description_;
	sptr<RTPConnection> rtp_connection_;

	std::vector<TrackInfo> tracks_;

	bool VerifyMediaFormat(size_t index, unsigned *port) const;
	static int MakeUDPSocket(unsigned port);

	DISALLOW_COPY_AND_MOVE(RTPSession);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTP_SESSION_H
