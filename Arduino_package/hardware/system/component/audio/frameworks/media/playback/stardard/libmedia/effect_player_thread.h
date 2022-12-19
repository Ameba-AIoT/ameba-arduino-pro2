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

#ifndef AMEBA_FWK_MEDIA_PLAYER_LIBMEDIA_EFFECT_PLAYER_THREAD_H
#define AMEBA_FWK_MEDIA_PLAYER_LIBMEDIA_EFFECT_PLAYER_THREAD_H

#include <vector>

#include "osal_cxx/threads.h"
#include "effect_player_impl.h"

namespace ameba::media
{

class EffectPlayerMsg
{
public:
	enum MessageType { INVALID, KILL, LOAD_SAMPLE, WRITE_SAMPLE };
	EffectPlayerMsg() : message_type_(INVALID), data_(0) {}
	EffectPlayerMsg(MessageType message_type, int data) :
		message_type_(message_type), data_(data) {}
	uint16_t         message_type_;
	uint16_t         data_;
};

/**
 * @brief This provides the underlying Thread used by EffectPlayerImpl.
 */
class EffectPlayerThread : public Thread
{
public:
	explicit EffectPlayerThread(EffectPlayerImpl *effect_player);
	~EffectPlayerThread();
	void LoadSample(int sample_id);
	void WriteSample(int channel_id);
	void Quit();
	void Write(EffectPlayerMsg msg);
	void RegisterCallback(struct RTEffectPlayerCallback *callback);

private:
	static const size_t maxMessages = 128;

	bool ThreadLoop();
	void DoLoadSample(int sample_id);
	void DoWriteSample(int channel_id);
	const EffectPlayerMsg Read();

	Mutex                           player_thread_lock_;
	Condition                       condition_;
	std::vector<EffectPlayerMsg>    msg_queue_;
	EffectPlayerImpl               *effect_player_;
	bool                            in_quit_;
	struct RTEffectPlayerCallback  *effect_player_cb_;
};

} // end namespace ameba::media

#endif /*AMEBA_FWK_MEDIA_PLAYER_LIBMEDIA_EFFECT_PLAYER_THREAD_H*/
