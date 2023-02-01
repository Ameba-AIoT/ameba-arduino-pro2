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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_LOOPER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_LOOPER_H

#include "osal_cxx/errors.h"
#include "utils/list.h"
#include "osal_cxx/refptr.h"
#include "osal_cxx/mutex.h"
#include "osal_cxx/condition.h"
#include "osal_cxx/threads.h"

#include "utils/nocopyable.h"
#include "media/utils/rstring.h"

namespace ameba::media
{

class MessageHandler;
class Message;
class ReplyMessage;

class MessageLooper : public RefPtr
{
public:
	typedef int32_t HandlerID;

	MessageLooper();

	void SetName(const char *name);

	const char *GetName() const
	{
		return name_.Str();
	}

	HandlerID RegisterHandler(const sptr<MessageHandler> &handler);
	void UnregisterHandler(HandlerID handler_id);

	res_t Start(bool run_in_call_thread = false, int32_t priority = PRIORITY_DEFAULT, size_t stack_size = 0);
	res_t Stop();

	static int64_t GetCurrentTimeUs();

protected:
	virtual ~MessageLooper();

private:
	bool Loop();

private:
	friend class Message;

	void Post(const sptr<Message> &msg, int64_t delay_us);
	sptr<ReplyMessage> CreateReplyMessage();
	res_t WaitResponse(const sptr<ReplyMessage> &reply_token, sptr<Message> *response);
	res_t PostReply(const sptr<ReplyMessage> &reply_token, const sptr<Message> &msg);

private:
	struct Event {
		int64_t when_us_;
		sptr<Message> message_;
	};

	Mutex lock_;
	Condition queue_condition_;

	RString name_;
	List<Event> event_queue_;

	class LooperThread;
	sptr<LooperThread> thread_;
	bool running_locally_;

	Mutex replay_lock_;
	Condition replay_condition_;

	DISALLOW_COPY_AND_MOVE(MessageLooper);
};

} // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_MESSAGE_LOOPER_H