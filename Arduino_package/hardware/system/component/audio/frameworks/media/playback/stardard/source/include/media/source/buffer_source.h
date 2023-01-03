/*
 * Copyright (c) 2022 Realtek, LLC.
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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_BUFFER_SOURCE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_BUFFER_SOURCE_H

#include <stdio.h>
#include <string>

#include "osal_cxx/mutex.h"
#include "media/source/data_source.h"

namespace ameba::media
{

class BufferSource : public DataSource
{
public:
	BufferSource(const char *name);

	virtual res_t Check() const;

	virtual ssize_t ReadAt(off64_t offset, void *data, size_t size);

	virtual res_t GetLength(off64_t *size);

	virtual uint32_t GetSourceFlags()
	{
		return kBufferSource;
	}

	virtual std::string ToString()
	{
		return name_;
	}

protected:
	virtual ~BufferSource();
	char InitState(void);

private:
	char *buffer_;
	int64_t length_;

	Mutex lock_;
	std::string name_;
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_BUFFER_SOURCE_H