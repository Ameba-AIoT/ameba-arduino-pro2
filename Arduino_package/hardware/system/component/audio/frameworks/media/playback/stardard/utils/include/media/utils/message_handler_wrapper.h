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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_HANDLER_WRAPPER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_HANDLER_WRAPPER_H

#include "media/utils/message_handler.h"

namespace ameba::media
{

template<class T>
class MessageHandlerWrapper : public MessageHandler
{
public:
	MessageHandlerWrapper(T *target)
		: target_(target)
	{
	}

protected:
	virtual void OnMessage(const sptr<Message> &msg)
	{
		sptr<T> target = target_.promote();
		if (target != NULL) {
			target->OnMessage(msg);
		}
	}

private:
	wptr<T> target_;

	DISALLOW_COPY_AND_MOVE(MessageHandlerWrapper<T>);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_HANDLER_WRAPPER_H