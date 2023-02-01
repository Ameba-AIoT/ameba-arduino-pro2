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

#ifndef AMEBA_UTILS_MEMORY_BASE_H
#define AMEBA_UTILS_MEMORY_BASE_H

#include <stdlib.h>
#include <stdint.h>

#include "osal_cxx/refptr.h"
#include "osal_cxx/errors.h"
#include "if_memory.h"


namespace ameba
{

// ---------------------------------------------------------------------------

class AshMemBase : public virtual AshMemBaseStub
{
public:
	enum {
		READ_ONLY = IAshMemBase::READ_ONLY,
		// memory won't be mapped locally, but will be mapped in the remote
		// process.
		DONT_MAP_LOCALLY = 0x00000100,
		NO_CACHING = 0x00000200
	};

	/*
	 * maps the memory referenced by fd. but DOESN'T take ownership
	 * of the filedescriptor (it makes a copy with dup()
	 */
	//AshMemBase(int fd, size_t size, uint32_t flags = 0, uint32_t offset = 0);

	/*
	 * maps memory from the given device
	 */
	//AshMemBase(const char* device, size_t size = 0, uint32_t flags = 0);

	/*
	 * maps memory from ashmem, with the given name for debugging
	 */
	AshMemBase(size_t size, uint32_t flags = 0, char const *name = NULL);

	virtual ~AshMemBase();

	/* implement IMemoryHeap interface */
	int         GetHeapID() const;
	void       *GetBase() const; //virtual address of the heap. returns MAP_FAILED in case of error
	size_t      GetSize() const;
	uint32_t    GetFlags() const;
	uint32_t    GetOffset() const;

	const char         *getDevice() const;

	/* this closes this heap -- use carefully */
	void dispose();

	/* this is only needed as a workaround, use only if you know
	 * what you are doing */
	res_t setDevice(const char *device)
	{
		if (device_ == 0) {
			device_ = device;
		}
		return device_ ? NO_ERROR : ALREADY_EXISTS;
	}

protected:
	AshMemBase();
	// init() takes ownership of fd
	res_t init(int fd, void *base, int size,
			   int flags = 0, const char *device = NULL);

private:
	res_t mapfd(int fd, size_t size, uint32_t offset = 0);

	int         fd_;
	size_t      size_;
	void       *base_;
	uint32_t    flags_;
	const char *device_;
	bool        needUnmap_;
	uint32_t    offset_;
};

// ---------------------------------------------------------------------------
}; // namespace ameba

#endif // AMEBA_UTILS_MEMORY_BASE_H
