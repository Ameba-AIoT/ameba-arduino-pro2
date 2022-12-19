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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_STATE_MACHINE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_STATE_MACHINE_H

#include "media/utils/message_handler.h"

namespace ameba::media
{

class RState : public RefPtr
{
public:
	RState(const sptr<RState> &parent_state = NULL);

	sptr<RState> GetParentState();

protected:
	virtual ~RState();

	virtual void StateEnter();
	virtual void StateExit();

	virtual bool OnMessage(const sptr<Message> &msg) = 0;

private:
	friend class RStateMachine;

	sptr<RState> parent_state_;

	DISALLOW_COPY_AND_MOVE(RState);
};

class RStateMachine
{
public:
	RStateMachine();

protected:
	virtual ~RStateMachine();

	virtual void HandleMessage(const sptr<Message> &msg);

	// Only to be called in response to a message.
	void TransferState(const sptr<RState> &state);

private:
	sptr<RState> state_;

	DISALLOW_COPY_AND_MOVE(RStateMachine);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_STATE_MACHINE_H