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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_AMR_COMBINATION_H

#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_AMR_COMBINATION_H

#include <stdint.h>

#include "utils/list.h"

#include "combination_base.h"

namespace ameba::media
{

class Message;
class RString;

class AMRCombination : public CombinationBase
{
public:
	AMRCombination(
		const sptr<Message> &notify, bool is_wide,
		const RString &params);

protected:
	virtual ~AMRCombination();

	virtual CombinationStatus CombineMore(const sptr<RTPData> &rtp_data);
	virtual void OnByeReceived();
	virtual void PacketLost();

private:
	bool is_wide_;

	sptr<Message> notify_msg_;
	bool next_expected_seq_no_valid_;
	uint32_t next_expected_seq_no_;

	CombinationStatus AddPacket(const sptr<RTPData> &rtp_data);

	DISALLOW_COPY_AND_MOVE(AMRCombination);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_AMR_COMBINATION_H

