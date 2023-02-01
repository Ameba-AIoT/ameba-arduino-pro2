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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_HANDLER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_HANDLER_H

#include <map>

#include "osal_cxx/refptr.h"

#include "media/utils/message_looper.h"

namespace ameba::media
{

class Message;

class MessageHandler : public RefPtr
{
public:
	MessageHandler()
		: handler_id_(0),
		  message_count_(0)
	{
	}

	~MessageHandler()
	{
	}

	MessageLooper::HandlerID GetID() const
	{
		return handler_id_;
	}

	sptr<MessageLooper> GetStrongLooper() const
	{
		return looper_.promote();
	}

	wptr<MessageLooper> GetWeakLooper() const
	{
		return looper_;
	}

	wptr<MessageHandler> GetHandler() const
	{
		return const_cast<MessageHandler *>(this);
	}

protected:
	virtual void OnMessage(const sptr<Message> &msg) = 0;

private:
	friend class Message;
	friend class MessageLooperManager;

	void DeliverMessage(const sptr<Message> &msg);

	inline void SetHandlerID(MessageLooper::HandlerID id, const wptr<MessageLooper> &looper)
	{
		handler_id_ = id;
		looper_ = NULL;
		looper_ = looper;
	}

	MessageLooper::HandlerID handler_id_;
	wptr<MessageLooper> looper_;

	uint32_t message_count_;
	std::map<uint32_t, uint32_t> messages_;

	DISALLOW_COPY_AND_MOVE(MessageHandler);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_HANDLER_H