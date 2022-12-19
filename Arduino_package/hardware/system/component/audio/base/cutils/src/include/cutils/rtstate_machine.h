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

#ifndef AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_STATE_MACHINE_H
#define AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_STATE_MACHINE_H

#include "osal_c/osal_types.h"

#include "cutils/rtmessage_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RTState RTState;
typedef struct RTStateMachine RTStateMachine;

struct RTState {
	RTState *parent_state;

	void (*StateEnter)(RTState *state);
	void (*StateExit)(RTState *state);

	bool (*OnMessage)(RTState *state, const RTMessage *msg);
};

rt_status_t RTState_Construct(RTState *state, RTState *parent_state);
rt_status_t RTState_Destruct(RTState *state);
RTState *RTState_GetParentState(const RTState *state);

struct RTStateMachine {
	RTState *cur_state;

	void (*HandleMessage)(RTStateMachine *state_machine, const RTMessage *msg);
};

rt_status_t RTStateMachine_Construct(RTStateMachine *state_machine);
rt_status_t RTStateMachine_Destruct(RTStateMachine *state_machine);
rt_status_t RTStateMachine_TransferState(RTStateMachine *state_machine, RTState *state);
void RTStateMachine_HandleMessage(RTStateMachine *state_machine, const RTMessage *msg);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_CUTILS_SRC_INCLUDE_CUTILS_RT_STATE_MACHINE_H
