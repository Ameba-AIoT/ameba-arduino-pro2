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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_COMBINATION_BASE_H

#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_COMBINATION_BASE_H

#include "utils/nocopyable.h"
#include "utils/list.h"
#include "osal_cxx/refptr.h"

namespace ameba::media
{

class RBuffer;
class RTPData;

class CombinationBase : public RefPtr
{
public:
	enum CombinationStatus {
		COMBINATION_STATUS_MALFORMED_PACKET,
		COMBINATION_STATUS_WRONG_SEQUENCE_NUM,
		COMBINATION_STATUS_NOT_ENOUGH_DATA,
		COMBINATION_STATUS_OK
	};

	CombinationBase();

	void OnPacketReceived(const sptr<RTPData> &rtp_data);
	virtual void OnByeReceived() = 0;

protected:
	virtual CombinationStatus CombineMore(const sptr<RTPData> &rtp_data) = 0;
	virtual void PacketLost() = 0;

	static void CopyRTPTime(const sptr<RBuffer> &to, const sptr<RBuffer> &from);

	static sptr<RBuffer> MakeADTSCompoundFromAACFrames(
		unsigned profile,
		unsigned sampling_freq_idx,
		unsigned channel_config,
		const List<sptr<RBuffer> > &frames);

	static sptr<RBuffer> MakeCompoundFromPackets(
		const List<sptr<RBuffer> > &frames);

private:
	int64_t first_fail_time_us_;

	DISALLOW_COPY_AND_MOVE(CombinationBase);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_COMBINATION_BASE_H
