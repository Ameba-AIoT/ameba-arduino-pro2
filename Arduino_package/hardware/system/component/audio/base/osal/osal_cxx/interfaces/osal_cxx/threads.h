/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from PanKore
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
 * @file threads.h
 *
 * @brief Declares thread interfaces.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_THREADS_H
#define AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_THREADS_H

#include "osal_c/osal_thread.h"

#include "osal_cxx/errors.h"
#include "osal_cxx/condition.h"
#include "osal_cxx/mutex.h"
#include "osal_cxx/refptr.h"

namespace ameba
{

/**
 * @brief Enumerates thread priorities.
 *
 * @since 1.0
 * @version 1.0
 */
enum {
	PRIORITY_LOWEST         = OSAL_THREAD_PRI_LOWEST,
	PRIORITY_BACKGROUND     = OSAL_THREAD_PRI_BACKGROUND,
	PRIORITY_NORMAL         = OSAL_THREAD_PRI_BACKGROUND,
	PRIORITY_FOREGROUND     = OSAL_THREAD_PRI_BACKGROUND,
	PRIORITY_DISPLAY        = OSAL_THREAD_PRI_DISPLAY,
	PRIORITY_URGENT_DISPLAY = OSAL_THREAD_PRI_URGENT_DISPLAY,
	PRIORITY_AUDIO          = OSAL_THREAD_PRI_AUDIO,
	PRIORITY_URGENT_AUDIO   = OSAL_THREAD_PRI_URGENT_AUDIO,
	PRIORITY_HIGHEST        = OSAL_THREAD_PRI_HIGHEST,
	PRIORITY_DEFAULT        = OSAL_THREAD_PRI_DEFAULT,
	PRIORITY_MORE_FAVORABLE = OSAL_THREAD_PRI_MORE_FAVORABLE,
	PRIORITY_LESS_FAVORABLE = OSAL_THREAD_PRI_LESS_FAVORABLE,
};

/**
 * @brief Defines a thread id
 *
 * @since 1.0
 * @version 1.0
 */
typedef osal_thread_id_t thread_id_t;

/**
 * @brief Defines a thread routine function type.
 *
 * @since 1.0
 * @version 1.0
 */
typedef OsalThreadFunc thread_func_t;

/**
 * @brief Defines a thread class
 *
 * @since 1.0
 * @version 1.0
 */
class Thread : virtual public RefPtr
{
public:
	/**
	 * @brief Create a Thread object.
	 *
	 * This function just create a object, doesn't start a thread
	 *
	 * @since 1.0
	 * @version 1.0
	 */
	explicit Thread();
	virtual ~Thread();

	/**
	 * @brief Start to run a thread
	 *
	 * This function is called only when the power status of the OS is changed. \n
	 * The input service or the power management module can call this function to set the power status
	 * for the input device when the OS is in the Resume or Suspend status, so that the driver integrated circuit (IC)
	 * of the device can normally enter the specified status.
	 *
	 * @param name Indicates the name of the thread.
	 * The name buffer is allow space for up to 16 bytes.
	 * @param priority Indicates the priority of the thread.
	 * @param stack Indicates the thread stack size. Too small size may cause thread stack overflow
	 * @return Returns a value listed below: \n
	 * res_t | Description
	 * ----------------------| -----------------------
	 * NO_ERROR | Thread start operation is successful.
	 * INVALID_OPERATION | Invalid state of the Thread object.
	 * OPERATION_FAIL | Start thread failed.

	 * @since 1.0
	 * @version 1.0
	 */
	virtual res_t Start(const char *name,
						int32_t priority = PRIORITY_DEFAULT,
						size_t stack = 0);

	/**
	 * @brief Thread one-time initialization override interface.
	 *
	 * This function is used for override to do some thread initialzation actions.
	 * Return a NO_ERROR value will let the thread continue to run the threadLoop.
	 * Otherwise, threadLoop will be dropped due to this function failed.
	 *
	 * @return Returns a value listed below: \n
	 * res_t | Description
	 * ----------------------| -----------------------
	 * NO_ERROR | Return this value when
	 * others | Return other value will make thread start break.

	 * @since 1.0
	 * @version 1.0
	 */
	virtual res_t PrepareToRun();

	/**
	 * @brief Request this thread to exit
	 *
	 * This function is asynchronous, when the function returns
	 * the thread might still be running.
	 *
	 * @since 1.0
	 * @version 1.0
	 */
	virtual void  RequestExit();

	/**
	 * @brief Request this thread to exit and wait until it exit.
	 *
	 * This function is synchronous, it will blocked until thread
	 * exit. DON'T call this function in this object thread loop,
	 * it will cause a deadlock.
	 *
	 * @return Returns a thread running status in normal state. If
	 * the function is called in thread loop, it will return WOULD_BLOCK
	 *
	 * @since 1.0
	 * @version 1.0
	 */
	res_t RequestExitAndWait();

	/**
	 * @brief Join this thread until it exit.
	 *
	 * This function is synchronous, it will blocked until thread
	 * exit. Normally, this function is called after the caller exit
	 * it's threadLoop. DON'T call this function in this object thread
	 * loop, it will cause a deadlock.
	 *
	 * @return Returns a thread running status in normal state. If
	 * the function is called in thread loop, it will return WOULD_BLOCK
	 *
	 * @since 1.0
	 * @version 1.0
	 */
	res_t Join();

	/**
	 * @brief Indicates whether this thread is running.
	 *
	 * @return Indicates whether the thread is running.

	 * @since 1.0
	 * @version 1.0
	 */
	bool  IsRunning() const;

protected:
	/**
	 * @brief Indicates whether this thread is exiting.
	 *
	 * @return Indicates whether the thread is running.

	 * @since 1.0
	 * @version 1.0
	 */
	bool  IsExiting() const;

private:
	/**
	 * @brief It's a function the derived class to implement.
	 *
	 * The derived class need to implement threadLoop(). The thread will
	 * start looper of this function.
	 *
	 * @return Returns a value listed below: \n
	 * bool | Description
	 * ----------------------| -----------------------
	 * true | It will be called again until outside requestExit.
	 * false | The thread will exit when return.

	 * @since 1.0
	 * @version 1.0
	 */
	virtual bool  ThreadLoop() = 0;

	static  void *ThreadEntry(void *param);

private:
	OsalThread   *handle_;
	thread_id_t  thread_id_;

	mutable  Mutex        lock_;
	Condition    exit_condition_;

	volatile bool         exit_;
	volatile bool         running_;
	res_t        status_;

	sptr<Thread> self_ptr_;

	// Thread cannot be copied
	Thread(const Thread &) = delete;
	Thread &operator= (const Thread &) = delete;

	Thread(Thread &&) = delete;
	Thread &operator= (Thread &&) = delete;
};

}; // namespace ameba

#endif // AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_THREADS_H
/** @} */
