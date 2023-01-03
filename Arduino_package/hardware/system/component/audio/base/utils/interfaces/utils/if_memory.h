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

#ifndef AMEBA_UTILS_IF_MEMORY_H
#define AMEBA_UTILS_IF_MEMORY_H

#include "osal_cxx/refptr.h"
#include "osal_cxx/errors.h"
#include "ipc_types.h"
#include "iremote_broker.h"
#include "iremote_proxy.h"
#include "iremote_stub.h"

using OHOS::IRemoteBroker;
using OHOS::IRemoteStub;
using OHOS::IRemoteObject;
using OHOS::MessageParcel;
using OHOS::MessageOption;

namespace ameba
{

// ----------------------------------------------------------------------------

class IAshMemBase : public IRemoteBroker
{
public:
	DECLARE_INTERFACE_DESCRIPTOR(u"memory.IAshmemBase");

	// flags returned by GetFlags()
	enum {
		READ_ONLY   = 0x00000001
	};

	/* IMemoryHeap binder interface */
	virtual int         GetHeapID() const = 0;
	virtual void       *GetBase() const = 0;
	virtual size_t      GetSize() const = 0;
	virtual uint32_t    GetFlags() const = 0;
	virtual uint32_t    GetOffset() const = 0;

	/* upper layer interfaces */
	// these are there just for backward source compatibility
	int32_t HeapID() const
	{
		return GetHeapID();
	}
	void   *Base() const
	{
		return GetBase();
	}
	size_t  VirtualSize() const
	{
		return GetSize();
	}

	enum {
		HEAP_ID = 0
	};
};

class AshMemBaseStub : public IRemoteStub<IAshMemBase>
{
public:
	virtual int OnRemoteRequest(uint32_t code, MessageParcel &data,
								MessageParcel &reply, MessageOption &option) override;

	AshMemBaseStub();
protected:
	virtual ~AshMemBaseStub();
};

// ----------------------------------------------------------------------------

class IAshMem : public IRemoteBroker
{
public:
	DECLARE_INTERFACE_DESCRIPTOR(u"memory.IAshmem");

	/* IAshMem binder interface */
	virtual OHOS::sptr<IAshMemBase> GetMemory(ssize_t *offset = 0, size_t *size = 0) = 0;

	/* upper layer interfaces */
	//void* fastPointer(const sptr<IRemoteObject>& heap, ssize_t offset) const;
	void *Pointer();
	size_t Size();
	ssize_t Offset();

	enum {
		GET_MEMORY = 0
	};
};

class AshMemStub : public IRemoteStub<IAshMem>
{
public:
	virtual int OnRemoteRequest(uint32_t code, MessageParcel &data,
								MessageParcel &reply, MessageOption &option) override;

	AshMemStub();
protected:
	virtual ~AshMemStub();
};

// ----------------------------------------------------------------------------

}; // namespace ameba

#endif // AMEBA_UTILS_MEMORY_H
