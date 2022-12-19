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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_MPEG4_COMBINATION_H

#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_MPEG4_COMBINATION_H

#include "utils/list.h"
#include "utils/nocopyable.h"
#include <OMX_Audio.h>

#include "media/utils/rstring.h"
#include "combination_base.h"

namespace ameba::media
{

class RBuffer;
class Message;

class MPEG4Combination : public CombinationBase
{
public:
	MPEG4Combination(
		const sptr<Message> &notify, const RString &desc,
		const RString &params);

protected:
	virtual ~MPEG4Combination();

	virtual CombinationStatus CombineMore(const sptr<RTPData> &rtp_data);
	virtual void OnByeReceived();
	virtual void PacketLost();

private:
	sptr<Message> notify_msg_;
	bool is_generic_;
	RString params_;

	unsigned size_length_;
	unsigned idx_length_;
	unsigned idx_delta_length_;
	unsigned cts_delta_length_;
	unsigned dts_delta_length_;
	bool random_access_indication_;
	unsigned stream_state_indication_;
	unsigned auxiliary_data_size_length_;
	bool has_au_header_;

	int32_t channel_config_;
	size_t sample_rate_Index;

	uint32_t data_chunk_rtp_time_;
	bool next_expected_seq_no_valid_;
	uint32_t next_expected_seq_no_;
	bool data_chunk_damaged_;
	List<sptr<RBuffer> > packets_;

	CombinationStatus AddPacket(const sptr<RTPData> &rtp_data);
	void TransferDataChunk();

	DISALLOW_COPY_AND_MOVE(MPEG4Combination);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_MPEG4_COMBINATION_H
