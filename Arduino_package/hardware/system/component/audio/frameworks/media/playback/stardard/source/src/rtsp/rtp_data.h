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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTP_DATA_H

#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTP_DATA_H

#include <stdint.h>

#include "utils/nocopyable.h"
#include "utils/list.h"
#include "osal_cxx/refptr.h"

namespace ameba::media
{

class RBuffer;
class Message;
class CombinationBase;
class SessionDescription;

class RTPData : public RefPtr
{
public:
	RTPData(
		uint32_t id,
		const sptr<SessionDescription> &session_desc, size_t index,
		const sptr<Message> &notify);

	void ManageRTPPacket(const sptr<RBuffer> &buffer);
	void TimeUpdate(uint32_t rtp_time, uint64_t ntp_time);
	void ByeReceived();

	List<sptr<RBuffer> > *GetBufferQueue()
	{
		return &buffer_queue_;
	}

	void AddReceiverReport(const sptr<RBuffer> &buffer);
	void AddFIR(const sptr<RBuffer> &buffer);

private:
	uint32_t id_;
	uint32_t highest_seq_num_;
	uint32_t prev_expected_;
	uint32_t base_seq_num_;
	int32_t num_buffers_received_;
	int32_t prev_num_buffers_received_;

	List<sptr<RBuffer> > buffer_queue_;
	sptr<CombinationBase> combiner_;

	uint64_t last_ntp_time_;
	int64_t last_ntp_time_update_us_;

	bool issue_fir_requests_;
	int64_t last_fir_request_us_;
	uint8_t next_fir_seq_no_;

	sptr<Message> notify_;

	bool QueuePacket(const sptr<RBuffer> &buffer);

	DISALLOW_COPY_AND_MOVE(RTPData);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RTP_DATA_H
