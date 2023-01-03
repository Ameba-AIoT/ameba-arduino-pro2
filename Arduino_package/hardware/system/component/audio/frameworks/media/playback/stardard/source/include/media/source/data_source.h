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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_DATA_SOURCE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_DATA_SOURCE_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

#include "osal_c/osal_compat.h"
#include "osal_cxx/refptr.h"
#include "media/source/data_source_base.h"

namespace ameba::media
{

class DataSource : public DataSourceBase, public virtual RefPtr
{
public:
	DataSource() {}

	virtual size_t GetCachedDataSize(res_t *status)
	{
		*status = NO_INIT;
		return 0;
	}

	virtual res_t GetEstimatedBandwidth(int32_t *kbps)
	{
		*kbps = 0;
		return NO_INIT;
	}

	virtual void Disconnect() {}

protected:
	virtual ~DataSource() {}

private:
	DataSource(const DataSource &);
	DataSource &operator=(const DataSource &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_MEDIA_SOURCE_DATA_SOURCE_H
