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
 * @file refptr.h
 *
 * @brief Declares smart pointers.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_REFPTR_H
#define AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_REFPTR_H

#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#include "log/log.h"

namespace ameba
{

/**
 * @brief Smart pointer base class. It supports strong/weak pointers.
 * When using RefPtr object, you need to use sptr<> and wptr<>.
 *
 * @see sptr
 * @see wptr
 * @since 1.0
 * @version 1.0
 */
class RefPtr
{
public:
	/**
	 * @brief Provides interfaces for weak pointer count.
	 *
	 * @since 1.0
	 * @version 1.0
	 */
	class WeakRefCounter
	{
	public:
		RefPtr *getRefPtr() const;

		void incWeakCount();
		void decWeakCount();

		bool tryIncStrongCount();
		bool tryIncWeakCount();
	};

public:
	void incStrongCount() const;
	void decStrongCount() const;

	void forceIncStrongCount() const;

	int32_t getStrongCount() const;

	WeakRefCounter *createWeakRef() const;
	WeakRefCounter *getWeakRefs() const;

protected:
	RefPtr();
	virtual ~RefPtr();

	//! Flags for extendObjectLifetime()
	enum {
		OBJECT_LIFETIME_STRONG  = 0x0000,
		OBJECT_LIFETIME_WEAK    = 0x0001,
		OBJECT_LIFETIME_MASK    = 0x0001
	};

	void extendObjectLifetime(int32_t mode);

	//! Flags for onIncStrongAttempted()
	enum {
		FIRST_INC_STRONG = 0x0001
	};

	virtual void onFirstRef();
	virtual void onLastStrongRef();
	virtual bool onIncStrongAttempted(uint32_t flags);
	virtual void onLastWeakRef();

private:
	friend class WeakRefCounter;
	class RefCounter;

	RefPtr(const RefPtr &o);
	RefPtr &operator=(const RefPtr &o);

private:
	RefCounter *const mRefs;
};


template<typename T> class wptr;

/**
 * @brief Strong pointer class to reference a RefPtr object
 *
 * @see RefPtr
 * @since 1.0
 * @version 1.0
 */
template<typename T>
class sptr
{
public:
	inline sptr() : mPtr(0) { }
	~sptr();

	sptr(T *other);
	sptr(const sptr<T> &other);
	sptr(sptr<T> &&other);

	template<typename U> sptr(U *other);
	template<typename U> sptr(const sptr<U> &other);
	template<typename U> sptr(sptr<U> &&other);

	sptr &operator=(T *other);
	sptr &operator=(const sptr<T> &other);
	sptr &operator=(sptr<T> &&other);

	void clear();

	inline T *get() const
	{
		return mPtr;
	}
	inline T &operator*() const
	{
		return *mPtr;
	}
	inline T *operator->() const
	{
		return mPtr;
	}
	inline explicit operator bool() const
	{
		return mPtr != nullptr;
	}


	inline bool operator==(const sptr<T> &other) const
	{
		return mPtr == other.mPtr;
	}

	inline bool operator==(const T *other) const
	{
		return mPtr == other;
	}

	inline bool operator==(const wptr<T> &other) const
	{
		return mPtr == other.mPtr;
	}

	inline bool operator!=(const sptr<T> &other) const
	{
		return mPtr != other.mPtr;
	}

	inline bool operator!=(const T *other) const
	{
		return mPtr != other;
	}

	inline bool operator!=(const wptr<T> &other) const
	{
		return mPtr != other.mPtr;
	}

private:
	template<typename V> friend class sptr;
	template<typename V> friend class wptr;

	void setPointer(T *ptr);
	T *mPtr;
};

// ---------------------------------------------------
// sptr<> implementation

template<typename T>
sptr<T>::sptr(T *other)
	: mPtr(other)
{
	if (other) {
		other->incStrongCount();
	}
}

template<typename T>
sptr<T>::sptr(const sptr<T> &other)
	: mPtr(other.mPtr)
{
	if (mPtr) {
		mPtr->incStrongCount();
	}
}

template<typename T>
sptr<T>::sptr(sptr<T> &&other)
	: mPtr(other.mPtr)
{
	other.mPtr = nullptr;
}

template<typename T> template<typename U>
sptr<T>::sptr(U *other)
	: mPtr(other)
{
	if (other) {
		(static_cast<T *>(other))->incStrongCount();
	}
}

template<typename T> template<typename U>
sptr<T>::sptr(const sptr<U> &other)
	: mPtr(other.mPtr)
{
	if (mPtr) {
		mPtr->incStrongCount();
	}
}

template<typename T> template<typename U>
sptr<T>::sptr(sptr<U> &&other)
	: mPtr(other.mPtr)
{
	other.mPtr = nullptr;
}

template<typename T>
sptr<T>::~sptr()
{
	if (mPtr) {
		mPtr->decStrongCount();
	}
}

template<typename T>
sptr<T> &sptr<T>::operator=(const sptr<T> &other)
{
	T *oldPtr(*const_cast<T *volatile *>(&mPtr));
	T *newPtr(other.mPtr);

	if (newPtr) {
		newPtr->incStrongCount();
	}
	if (oldPtr) {
		oldPtr->decStrongCount();
	}
	if (oldPtr != *const_cast<T *volatile *>(&mPtr)) {
		LOG_ALWAYS_FATAL("sptr<> assignment data race");
	}

	mPtr = newPtr;
	return *this;
}

template<typename T>
sptr<T> &sptr<T>::operator=(sptr<T> &&other)
{
	T *oldPtr(*const_cast<T *volatile *>(&mPtr));

	if (oldPtr) {
		oldPtr->decStrongCount();
	}
	if (oldPtr != *const_cast<T *volatile *>(&mPtr)) {
		LOG_ALWAYS_FATAL("sptr<> assignment data race");
	}

	mPtr = other.mPtr;
	other.mPtr = nullptr;
	return *this;
}

template<typename T>
sptr<T> &sptr<T>::operator=(T *other)
{
	T *oldPtr(*const_cast<T *volatile *>(&mPtr));

	if (other) {
		other->incStrongCount();
	}
	if (oldPtr) {
		oldPtr->decStrongCount();
	}
	if (oldPtr != *const_cast<T *volatile *>(&mPtr)) {
		LOG_ALWAYS_FATAL("sptr<> assignment data race");
	}

	mPtr = other;
	return *this;
}

template<typename T>
void sptr<T>::clear()
{
	if (mPtr) {
		mPtr->decStrongCount();
		mPtr = nullptr;
	}
}

template<typename T>
void sptr<T>::setPointer(T *ptr)
{
	mPtr = ptr;
}


/**
 * @brief Weak pointer class to reference a RefPtr object
 *
 * @see RefPtr
 * @since 1.0
 * @version 1.0
 */
template <typename T>
class wptr
{
public:
	typedef typename RefPtr::WeakRefCounter WeakRefCounter;

	inline wptr() : mPtr(nullptr) { }
	~wptr();

	wptr(T *other);
	wptr(const wptr<T> &other);
	explicit wptr(const sptr<T> &other);

	template<typename U> wptr(U *other);
	template<typename U> wptr(const sptr<U> &other);
	template<typename U> wptr(const wptr<U> &other);

	wptr &operator=(T *other);
	wptr &operator=(const wptr<T> &other);
	wptr &operator=(const sptr<T> &other);


	sptr<T> promote() const;
	void clear();
	inline WeakRefCounter *get_refs() const
	{
		return mRefs;
	}


	// sptr<T> and T operator
	inline bool operator==(const sptr<T> &other) const
	{
		return mPtr == other.mPtr;
	}

	inline bool operator==(const T *other) const
	{
		return mPtr == other;
	}

	template<typename U>
	inline bool operator==(const sptr<U> &other) const
	{
		return mPtr == other.mPtr;
	}

	template<typename U>
	inline bool operator==(const U *other) const
	{
		return mPtr == other;
	}

	inline bool operator!=(const sptr<T> &other) const
	{
		return mPtr != other.mPtr;
	}

	inline bool operator!=(const T *other) const
	{
		return mPtr != other;
	}

	template<typename U>
	inline bool operator!=(const sptr<U> &other) const
	{
		return mPtr != other.mPtr;
	}

	template<typename U>
	inline bool operator!=(const U *other) const
	{
		return mPtr != other;
	}


	// wptr<T> operator
	inline bool operator==(const wptr<T> &other) const
	{
		return (mPtr == other.mPtr) && (mRefs == other.mRefs);
	}

	inline bool operator!=(const wptr<T> &other) const
	{
		return mRefs != other.mRefs;
	}

	inline bool operator>(const wptr<T> &other) const
	{
		return (mPtr == other.mPtr) ? (mRefs > other.mRefs) : (mPtr > other.mPtr);
	}

	inline bool operator<(const wptr<T> &other) const
	{
		return (mPtr == other.mPtr) ? (mRefs < other.mRefs) : (mPtr < other.mPtr);
	}

	inline bool operator>=(const wptr<T> &other) const
	{
		return !operator < (other);
	}

	inline bool operator<=(const wptr<T> &other) const
	{
		return !operator > (other);
	}

private:
	template<typename V> friend class sptr;
	template<typename V> friend class wptr;

	T *mPtr;
	WeakRefCounter *mRefs;
};

// ---------------------------------------------------
// sptr<> implementation

template<typename T>
wptr<T>::wptr(T *other)
	: mPtr(other)
{
	if (other) {
		mRefs = other->createWeakRef();
	}
}

template<typename T>
wptr<T>::wptr(const wptr<T> &other)
	: mPtr(other.mPtr), mRefs(other.mRefs)
{
	if (mPtr) {
		mRefs->incWeakCount();
	}
}

template<typename T>
wptr<T>::wptr(const sptr<T> &other)
	: mPtr(other.mPtr)
{
	if (mPtr) {
		mRefs = mPtr->createWeakRef();
	}
}

template<typename T> template<typename U>
wptr<T>::wptr(U *other)
	: mPtr(other)
{
	if (other) {
		mRefs = other->createWeakRef();
	}
}

template<typename T> template<typename U>
wptr<T>::wptr(const wptr<U> &other)
	: mPtr(other.mPtr)
{
	if (mPtr) {
		mRefs = other.mRefs;
		mRefs->incWeakCount();
	}
}

template<typename T> template<typename U>
wptr<T>::wptr(const sptr<U> &other)
	: mPtr(other.mPtr)
{
	if (mPtr) {
		mRefs = mPtr->createWeakRef();
	}
}

template<typename T>
wptr<T>::~wptr()
{
	if (mPtr) {
		mRefs->decWeakCount();
	}
}

template<typename T>
wptr<T> &wptr<T>::operator = (T *other)
{
	WeakRefCounter *newRefs =
		other ? other->createWeakRef() : nullptr;
	if (mPtr) {
		mRefs->decWeakCount();
	}
	mPtr = other;
	mRefs = newRefs;
	return *this;
}

template<typename T>
wptr<T> &wptr<T>::operator = (const wptr<T> &other)
{
	WeakRefCounter *otherRefs(other.mRefs);
	T *otherPtr(other.mPtr);
	if (otherPtr) {
		otherRefs->incWeakCount();
	}
	if (mPtr) {
		mRefs->decWeakCount();
	}
	mPtr = otherPtr;
	mRefs = otherRefs;
	return *this;
}

template<typename T>
wptr<T> &wptr<T>::operator = (const sptr<T> &other)
{
	WeakRefCounter *newRefs =
		other != nullptr ? other->createWeakRef() : nullptr;
	T *otherPtr(other.mPtr);
	if (mPtr) {
		mRefs->decWeakCount();
	}
	mPtr = otherPtr;
	mRefs = newRefs;
	return *this;
}

template<typename T>
sptr<T> wptr<T>::promote() const
{
	sptr<T> result;
	if (mPtr && mRefs->tryIncStrongCount()) {
		result.setPointer(mPtr);
	}
	return result;
}

template<typename T>
void wptr<T>::clear()
{
	if (mPtr) {
		mRefs->decWeakCount();
		mPtr = nullptr;
	}
}

}; // namespace ameba

#endif // AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_REFPTR_H
/** @} */