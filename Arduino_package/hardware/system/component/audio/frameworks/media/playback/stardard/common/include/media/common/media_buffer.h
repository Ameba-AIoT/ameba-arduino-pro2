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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BUFFER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BUFFER_H

#include <atomic>
#include <list>

#include <pthread.h>

#include "osal_cxx/errors.h"
#include "osal_cxx/refptr.h"

#include "media/common/media_buffer_base.h"

namespace ameba::media
{

class RBuffer;
class MediaBuffer;
class MediaBufferObserver;
class MetaDataBase;

class MediaBuffer : public MediaBufferBase
{
public:
	// The underlying data remains the responsibility of the caller!
	MediaBuffer(void *data, size_t size);

	explicit MediaBuffer(size_t size);

	explicit MediaBuffer(const sptr<RBuffer> &buffer);

	// If MediaBufferGroup is set, decrement the local reference count;
	// if the local reference count drops to 0, return the buffer to the
	// associated MediaBufferGroup.
	//
	// If no MediaBufferGroup is set, the local reference count must be zero
	// when called, whereupon the MediaBuffer is deleted.
	virtual void Release();

	// Increments the local reference count.
	// Use only when MediaBufferGroup is set.
	virtual void AddRef();

	virtual void *Data() const;
	virtual size_t Size() const;

	virtual sptr<RBuffer> Buffer() const;

	virtual size_t RangeOffset() const;
	virtual size_t RangeLength() const;

	virtual void SetRange(size_t offset, size_t length);

	MetaDataBase &GetMetaData();

	// Clears meta data and resets the range to the full extent.
	virtual void Reset();

	virtual void SetObserver(MediaBufferObserver *group);

	// Returns a clone of this MediaBuffer increasing its reference count.
	// The clone references the same data but has its own range and
	// MetaData.
	virtual MediaBufferBase *Clone();

	// sum of LocalRefcount() and RemoteRefcount()
	virtual int Refcount() const
	{
		return LocalRefcount() + RemoteRefcount();
	}

	virtual int LocalRefcount() const
	{
		return ref_count_;
	}

	virtual int RemoteRefcount() const
	{
		return 0;
	}

	// returns old value
	int AddRemoteRefcount(int32_t value)
	{
		if (value) {
			return 0;
		}
		return 0;
	}

protected:
	// true if MediaBuffer is observed (part of a MediaBufferGroup).
	//inline bool isObserved() const {
	//    return observer_ != nullptr;
	//}

	virtual ~MediaBuffer();

private:
	friend class MediaBufferGroup;

	// For use by OMXDecoder, reference count must be 1, drop reference
	// count to 0 without signalling the observer.
	//void claim();

	MediaBufferObserver *observer_;
	int ref_count_;

	void *data_;
	size_t size_;
	size_t range_offset_;
	size_t range_length_;
	sptr<RBuffer> buffer_;

	bool owns_data_;

	MetaDataBase *meta_data_;

	MediaBuffer *original_;

	MediaBuffer(const MediaBuffer &);
	MediaBuffer &operator=(const MediaBuffer &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BUFFER_H