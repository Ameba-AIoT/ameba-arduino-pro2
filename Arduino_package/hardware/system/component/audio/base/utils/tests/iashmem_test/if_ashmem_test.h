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

#ifndef AMEBA_UTILS_TESTS_IASHMEM_TEST_IF_ASHMEM_TEST_H
#define AMEBA_UTILS_TESTS_IASHMEM_TEST_IF_ASHMEM_TEST_H

#include "utils/refptr.h"
#include "utils/errors.h"
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

class IAshMem;

class IAshMemTest : public IRemoteBroker
{
public:
	DECLARE_INTERFACE_DESCRIPTOR(u"memory.IAshMemTest");
	//DECLARE_INTERFACE_DESCRIPTOR(u"audio.audiofocus.IAudioFocus");
	/* IAshMemTest binder interface */
	virtual OHOS::sptr<IAshMem> GetBuffer() = 0;

	enum {
		GET_BUFFER,
	};
};

class AshMemTestStub : public IRemoteStub<IAshMemTest>
{
public:
	virtual int OnRemoteRequest(uint32_t code, MessageParcel &data,
								MessageParcel &reply, MessageOption &option) override;

	AshMemTestStub();
protected:
	virtual ~AshMemTestStub();
};

}; // namespace ameba

#endif // AMEBA_UTILS_TESTS_IASHMEM_TEST_IF_ASHMEM_TEST_H