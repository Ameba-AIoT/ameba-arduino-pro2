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

#ifndef AMEBA_UTILS_MEMORY_H
#define AMEBA_UTILS_MEMORY_H

#include <stdlib.h>
#include <stdint.h>

#include "osal_cxx/refptr.h"
#include "if_memory.h"

namespace ameba
{

class AshMem : public AshMemStub
{
public:
	AshMem(const OHOS::sptr<IAshMemBase> &heap, ssize_t offset, size_t size);
	virtual ~AshMem();

	/* IAshMem binder interface */
	virtual OHOS::sptr<IAshMemBase> GetMemory(ssize_t *offset = 0, size_t *size = 0);

protected:
	size_t GetSize() const
	{
		return size_;
	}
	ssize_t GetOffset() const
	{
		return offset_;
	}
	const OHOS::sptr<IAshMemBase> &GetAshMem() const
	{
		return ash_mem_;
	}

private:
	size_t          size_;
	ssize_t         offset_;
	OHOS::sptr<IAshMemBase> ash_mem_;
};

}; // namespace ameba

#endif // AMEBA_UTILS_MEMORY_H
