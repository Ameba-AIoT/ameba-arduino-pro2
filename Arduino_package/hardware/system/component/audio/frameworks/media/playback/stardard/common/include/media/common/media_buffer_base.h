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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BUFFER_BASE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BUFFER_BASE_H

#include "osal_cxx/refptr.h"

namespace ameba::media
{

class MediaBufferBase;
class MetaDataBase;
class RBuffer;

class MediaBufferObserver
{
public:
	MediaBufferObserver() {}
	virtual ~MediaBufferObserver() {}

	virtual void SignalBufferReturned(MediaBufferBase *buffer) = 0;

private:
	MediaBufferObserver(const MediaBufferObserver &);
	MediaBufferObserver &operator=(const MediaBufferObserver &);
};

class MediaBufferBase
{
public:
	static MediaBufferBase *Create(size_t size);

	// If MediaBufferGroup is set, decrement the local reference count;
	// if the local reference count drops to 0, return the buffer to the
	// associated MediaBufferGroup.
	//
	// If no MediaBufferGroup is set, the local reference count must be zero
	// when called, whereupon the MediaBuffer is deleted.
	virtual void Release() = 0;

	// Increments the local reference count.
	// Use only when MediaBufferGroup is set.
	virtual void AddRef() = 0;

	virtual void *Data() const = 0;
	virtual size_t Size() const = 0;

	virtual size_t RangeOffset() const = 0;
	virtual size_t RangeLength() const = 0;

	virtual void SetRange(size_t offset, size_t length) = 0;

	virtual MetaDataBase &GetMetaData() = 0;

	virtual sptr<RBuffer> Buffer() const = 0;

	// Clears meta data and resets the range to the full extent.
	virtual void Reset() = 0;

	virtual void SetObserver(MediaBufferObserver *group) = 0;

	// Returns a clone of this MediaBufferBase increasing its reference
	// count. The clone references the same data but has its own range and
	// MetaData.
	virtual MediaBufferBase *Clone() = 0;

	virtual int Refcount() const = 0;

	virtual int LocalRefcount() const = 0;
	virtual int RemoteRefcount() const = 0;

	virtual ~MediaBufferBase() {};
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BUFFER_BASE_H