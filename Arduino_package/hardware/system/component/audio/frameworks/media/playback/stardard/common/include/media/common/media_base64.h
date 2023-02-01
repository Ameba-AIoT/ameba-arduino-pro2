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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BASE_64_H_

#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BASE_64_H_

#include "media/utils/rstring.h"
#include "utils/nocopyable.h"
#include "osal_cxx/refptr.h"
#include "media/utils/rbuffer.h"


namespace ameba::media
{

class RBuffer;
class RString;

sptr<RBuffer> DecodeBase64(const RString &s);
void EncodeBase64(const void *data, size_t size, RString *out);

void EncodeBase64Url(const void *data, size_t size, RString *out);

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BASE_64_H_
