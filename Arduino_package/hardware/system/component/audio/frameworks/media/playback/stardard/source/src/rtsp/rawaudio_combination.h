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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RAW_AUDIO_COMBINATION_H

#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RAW_AUDIO_COMBINATION_H

#include "combination_base.h"

namespace ameba::media
{

class Message;
class RString;
class MetaData;

class RawAudioCombination : public CombinationBase
{
public:
	RawAudioCombination(
		const sptr<Message> &notify,
		const char *desc, const RString &params);

	static bool Supports(const char *desc);

	static void MakeFormat(
		const char *desc, const sptr<MetaData> &format);

protected:
	virtual ~RawAudioCombination();

	virtual CombinationStatus CombineMore(const sptr<RTPData> &rtp_data);
	virtual void OnByeReceived();
	virtual void PacketLost();

private:
	bool is_wide_;

	sptr<Message> notify_msg_;
	bool next_expected_seq_no_valid_;
	uint32_t next_expected_seq_no_;

	CombinationStatus AddPacket(const sptr<RTPData> &rtp_data);

	DISALLOW_COPY_AND_MOVE(RawAudioCombination);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_RAW_AUDIO_COMBINATION_H
