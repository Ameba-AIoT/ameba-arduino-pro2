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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_DATA_SOURCE_BASE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_DATA_SOURCE_BASE_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <string>

#include "osal_cxx/errors.h"

namespace ameba::media
{

class DataSourceBase
{
public:
	enum Flags {
		kCachedSource   = 1,
		kHttpSource     = 1 << 1,
		kLocalSource    = 1 << 2,
		kBufferSource   = 1 << 3,
	};

	DataSourceBase() {}

	virtual res_t Check() const = 0;

	// Returns the number of bytes read, or -1 on failure. It's not an error if
	// this returns zero; it just means the given offset is equal to, or
	// beyond, the end of the source.
	virtual ssize_t ReadAt(off64_t offset, void *data, size_t size) = 0;

	// Convenience methods:
	bool GetUInt16(off64_t offset, uint16_t *x);
	bool GetUInt24(off64_t offset, uint32_t *x); // 3 byte int, returned as a 32-bit int
	bool GetUInt32(off64_t offset, uint32_t *x);
	bool GetUInt64(off64_t offset, uint64_t *x);

	// read either int<N> or int<2N> into a uint<2N>_t, size is the int size in bytes.
	bool GetUInt16Var(off64_t offset, uint16_t *x, size_t size);
	bool GetUInt32Var(off64_t offset, uint32_t *x, size_t size);
	bool GetUInt64Var(off64_t offset, uint64_t *x, size_t size);

	// May return ERROR_UNSUPPORTED.
	virtual res_t GetLength(off64_t *size);

	virtual uint32_t GetSourceFlags()
	{
		return 0;
	}

	virtual std::string ToString()
	{
		return "<unspecified>";
	}

	virtual void Close() {}

protected:
	virtual ~DataSourceBase() {}

private:
	DataSourceBase(const DataSourceBase &);
	DataSourceBase &operator=(const DataSourceBase &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_DATA_SOURCE_BASE_H
