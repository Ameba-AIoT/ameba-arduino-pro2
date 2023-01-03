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

/**
 * @addtogroup OSAL
 * @{
 *
 * @brief Declares the structures and interfaces for the Operating System Abstraction Layer (OSAL) module.
 *
 * The OSAL module provide a unified interfaces that adapter to different OS. The interfaces include the
 * memory management, thread, mutex, semaphore, time.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file condition.h
 *
 * @brief Declares Condition types and interfaces.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_CONDITION_H
#define AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_CONDITION_H

#include <stdint.h>

#include "osal_cxx/errors.h"
#include "osal_cxx/mutex.h"

namespace ameba
{

#ifdef __linux__
#define OSALCXX_COND_HANLDE_SIZE 52
#else
#define OSALCXX_COND_HANLDE_SIZE 12
#endif

/**
 * @brief Provides interfaces for signal function.
 *
 */
class Condition
{
public:
	enum WakeUpType {
		WAKE_UP_ONE = 0,
		WAKE_UP_ALL = 1
	};

	Condition();
	virtual ~Condition();

	// Condition cannot be copied
	Condition(const Condition &) = delete;
	Condition &operator=(const Condition &) = delete;


	/**
	 * @brief Wait on the condition variable.
	 *
	 * Lock the mutex before calling. Note that spurious wake-ups may happen.
	 *
	 * @return Returns <b>OK</b> for success; returns a negative value otherwise.
	 */
	res_t Wait(Mutex &mutex);

	/**
	 * @brief Wait on the condition variable with relative timeout.
	 *
	 * Lock the mutex before calling. Note that spurious wake-ups may happen.
	 *
	 * @return Returns <b>OK</b> for success; returns a negative value otherwise.
	 */
	res_t WaitRelative(Mutex &mutex, int64_t nanosec);

	/**
	 * @brief Signal the condition variable, allow one thread to continue.
	 *
	 */
	void Signal();

	/**
	 * @brief Signal or broadcast the condition variable
	 *
	 */
	void  Signal(WakeUpType type)
	{
		if (type == WAKE_UP_ONE) {
			Signal();
		} else {
			Broadcast();
		}
	}

	/**
	 * @brief Signal the condition variable, allowing all threads to continue.
	 *
	 */
	void Broadcast();

private:
	uint8_t real_cond_[OSALCXX_COND_HANLDE_SIZE] __attribute__((aligned(4)));
	bool inited_;
};

}; // namespace ameba

#endif // AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_CONDITION_H
/** @} */