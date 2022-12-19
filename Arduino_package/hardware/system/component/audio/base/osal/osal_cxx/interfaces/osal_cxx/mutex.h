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
 * @file mutex.h
 *
 * @brief Declares Mutex types and interfaces.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_MUTEX_H
#define AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_MUTEX_H

#include <stdint.h>

#include "osal_cxx/errors.h"

namespace ameba
{

class Condition;

#ifdef __linux__
#define OSALCXX_MUTEX_HANLDE_SIZE 44
#else
#define OSALCXX_MUTEX_HANLDE_SIZE 8
#endif

/**
 * @brief Provides interfaces for mutex function.
 *
 * @since 1.0
 * @version 1.0
 */
class Mutex
{
public:
	Mutex();
	~Mutex();

	/**
	 * @brief Lock the mutex.
	 *
	 * @return Returns <b>OK</b> if lock successfully; returns a negative value otherwise.
	 */
	res_t Lock();

	/**
	 * @brief Try to lock the mutex. It returns is the mutex is in locked state.
	 *
	 * @return Returns <b>OK</b> if lock successfully; returns a negative value otherwise.
	 */
	res_t TryLock();

	/**
	 * @brief Unlock the mutex.
	 *
	 */
	void Unlock();

	/**
	 * @brief Provides interfaces for auto lock.
	 *
	 * @since 1.0
	 * @version 1.0
	 */
	class Autolock
	{
	public:
		inline explicit Autolock(Mutex &mutex) : lock_(mutex)
		{
			lock_.Lock();
		}
		inline explicit Autolock(Mutex *mutex) : lock_(*mutex)
		{
			lock_.Lock();
		}
		inline ~Autolock()
		{
			lock_.Unlock();
		}

	private:
		// Disallow copy or move
		Autolock(const Autolock &) = delete;
		Autolock &operator=(const Autolock &) = delete;

		Mutex &lock_;
	};
	// -------------------------------------------------------------------------

private:
	friend class Condition;

	// Disallow copy or move
	Mutex(const Mutex &) = delete;
	Mutex &operator=(const Mutex &) = delete;

	uint8_t real_mutex_[OSALCXX_MUTEX_HANLDE_SIZE] __attribute__((aligned(4)));
	bool inited_;
};

}; // namespace ameba

#endif // AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_MUTEX_H
/** @} */