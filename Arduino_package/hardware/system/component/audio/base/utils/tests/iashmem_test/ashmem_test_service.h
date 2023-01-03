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

#ifndef AMEBA_UTILS_TESTS_IASHMEM_TEST_ASHMEM_TEST_SERVICE_H
#define AMEBA_UTILS_TESTS_IASHMEM_TEST_ASHMEM_TEST_SERVICE_H

#include "utils/threads.h"
#include "system_ability.h"

#include "if_ashmem_test.h"

using OHOS::SystemAbility;

namespace ameba
{

class IAshMem;
class AshMem;
//class AshMemTestStub;
//class IAshMemTest;

class AshMemTestService : public SystemAbility, public AshMemTestStub
{
	DECLARE_SYSTEM_ABILITY(AshMemTestService);
public:
	DISALLOW_COPY_AND_MOVE(AshMemTestService);
	explicit AshMemTestService(int32_t systemAbilityId, bool runOnCreate = true);
	~AshMemTestService();

	void OnDump() override;
	void OnStart() override;
	void OnStop() override;

	OHOS::sptr<IAshMem> GetBuffer() override;

private:
	bool Init();

private:
	OHOS::sptr<AshMem> ash_mem_;
};

}  // namespace ameba
#endif  // AMEBA_UTILS_TESTS_IASHMEM_TEST_ASHMEM_TEST_SERVICE_H