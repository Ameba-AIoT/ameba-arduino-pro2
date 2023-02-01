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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_BUFFER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_BUFFER_H

#include <sys/types.h>
#include <stdint.h>

#include "osal_cxx/refptr.h"

namespace ameba::media
{

class Message;

class RBuffer : public RefPtr
{
public:
	explicit RBuffer(size_t capacity);
	RBuffer(void *data, size_t capacity);

	uint8_t *Base()
	{
		return (uint8_t *)data_;
	}
	uint8_t *Data()
	{
		return (uint8_t *)data_ + range_offset_;
	}
	size_t Capacity() const
	{
		return capacity_;
	}
	size_t Size() const
	{
		return range_length_;
	}
	size_t Offset() const
	{
		return range_offset_;
	}

	void SetRange(size_t offset, size_t size);

	// create buffer from dup of some memory block
	static sptr<RBuffer> CreateAsCopy(const void *data, size_t capacity);

	void SetInt32Data(int32_t data)
	{
		int32_data_ = data;
	}
	int32_t Int32Data() const
	{
		return int32_data_;
	}

	sptr<Message> Meta();

protected:
	virtual ~RBuffer();

private:
	sptr<Message> meta_;

	void *data_;
	size_t capacity_;
	size_t range_offset_;
	size_t range_length_;

	int32_t int32_data_;

	bool owns_data_;

	// DISALLOW_COPY_AND_MOVE(RBuffer);
	RBuffer(const RBuffer &) = delete;
	RBuffer &operator= (const RBuffer &) = delete;

	RBuffer(RBuffer &&) = delete;
	RBuffer &operator= (RBuffer &&) = delete;
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_BUFFER_H