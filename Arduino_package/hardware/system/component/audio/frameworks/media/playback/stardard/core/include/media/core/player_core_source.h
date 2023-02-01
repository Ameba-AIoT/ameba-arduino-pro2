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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_SOURCE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_SOURCE_H

#include "media/utils/message.h"
#include "media/common/meta_data.h"

#include "player_core.h"

namespace ameba::media
{

class RBuffer;
class MediaBuffer;

class PlayerCore::Source : public MessageHandler
{
public:
	enum Flags {
		FLAG_CAN_PAUSE          = 1 << 0,
		FLAG_CAN_REWIND_BACKWARD  = 1 << 1, // the "10 sec back button"
		FLAG_CAN_REWIND_FORWARD   = 1 << 2, // the "10 sec forward button"
		FLAG_CAN_REWIND           = 1 << 3, // the "rewind bar"
		FLAG_DYNAMIC_DURATION   = 1 << 4,
	};

	enum {
		kMsgPrepared  = 0x00530102,

		kMsgFlagsChanged = 0x00530305,
		kMsgBufferingInfoUpdate = 0x00530307,
		kMsgPauseOnBufferingStart = 0x00530308,
		kMsgResumeOnBufferingEnd = 0x00530309,
	};

	// The provides message is used to notify the player about various
	// events.
	explicit Source(const sptr<Message> &notify)
		: notify_(notify)
	{
	}

	virtual void PrepareAsync() = 0;

	virtual void Start() = 0;
	virtual void Stop() {}
	virtual void Pause() {}
	virtual void Resume() {}

	// Explicitly disconnect the underling data source
	virtual void Disconnect() {}

	// Returns OK iff more data was available,
	// an error or ERROR_END_OF_STREAM if not.
	virtual res_t FeedMoreTSData() = 0;

	// Returns non-NULL format when the specified track exists.
	// When the format has "err" set to -EWOULDBLOCK, source needs more time to get valid meta data.
	// Returns NULL if the specified track doesn't exist or is invalid;
	virtual sptr<Message> GetFormat();

	virtual sptr<MetaData> GetFormatMeta()
	{
		return NULL;
	}

	virtual res_t DequeueDataChunk(MediaBufferBase **data_block) = 0;

	virtual res_t GetDuration(int64_t * /* duration_us */)
	{
		return INVALID_OPERATION;
	}

	virtual res_t Rewind(
		int64_t /* rewind_time_us */)
	{
		return INVALID_OPERATION;
	}

	virtual bool IsStreaming() const
	{
		return true;
	}

protected:
	virtual ~Source() {}

	virtual void OnMessage(const sptr<Message> &msg);

	sptr<Message> DuplicateNotify() const
	{
		return notify_->Duplicate();
	}

	void NotifyFlagsChanged(uint32_t flags);
	void NotifyPrepared(res_t err = OK);

private:
	sptr<Message> notify_;

	DISALLOW_COPY_AND_MOVE(Source);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CORE_MEDIA_CORE_PLAYER_CORE_SOURCE_H