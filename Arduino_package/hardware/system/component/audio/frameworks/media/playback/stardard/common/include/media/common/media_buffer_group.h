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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BUFFER_GROUP_H
#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BUFFER_GROUP_H

#include <list>

#include "osal_cxx/errors.h"
#include "osal_cxx/mutex.h"
#include "osal_cxx/condition.h"

#include "media/common/media_buffer_base.h"

namespace ameba::media
{

class MediaBufferBase;

class MediaBufferGroup : public MediaBufferObserver
{
public:
	MediaBufferGroup(size_t growth_limit = 0);
	MediaBufferGroup(size_t buffer_num, size_t buffer_size, size_t growth_limit = 0);

	~MediaBufferGroup();

	void AddBuffer(MediaBufferBase *buffer);

	bool HasBuffers();

	// If non_blocking is false, it blocks until a buffer is available and
	// passes it to the caller in *buffer, while returning OK.
	// The returned buffer will have a reference count of 1.
	// If non_blocking is true and a buffer is not immediately available,
	// buffer is set to NULL and it returns WOULD_BLOCK.
	// If requested_size is 0, any free MediaBuffer will be returned.
	// If requested_size is > 0, the returned MediaBuffer should have buffer
	// size of at least requstedSize.
	res_t AcquireBuffer(
		MediaBufferBase **buffer, bool non_blocking = false, size_t requested_size = 0);

	size_t GetBufferNum() const;

	// If buffer is nullptr, have acquire_Buffer() check for remote release.
	virtual void SignalBufferReturned(MediaBufferBase *buffer);

private:
	struct InternalData;
	InternalData *internal_data_;

	MediaBufferGroup(const MediaBufferGroup &);
	MediaBufferGroup &operator=(const MediaBufferGroup &);
};

}  // namespace ameba::media

#endif  // MEDIA_BUFFER_GROUP_H_
