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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_UTILS_H
#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_UTILS_H

#include <memory>
#include <stdint.h>

namespace ameba::media
{

class MetaData;
class MetaDataBase;
class Message;

res_t ConvertMetaDataToMessage(const sptr<MetaData> &meta, sptr<Message> *format);

bool MakeAACCodecSpecificData(MetaDataBase &meta, unsigned profile, unsigned sampling_freq_index,
							  unsigned channel_cfg);

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_UTILS_H