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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_MEDIA_RTMEDIA_FORMAT_H
#define AMEBA_FWK_MEDIA_PLAYBACK_MEDIA_RTMEDIA_FORMAT_H

#include "media/utils/message.h"

using namespace ameba;
using namespace ameba::media;

__BEGIN_DECLS

struct RTMediaFormat;
typedef struct RTMediaFormat RTMediaFormat;

struct RTMediaFormat *RTMediaFormat_MediaFormatFromMsg(sptr<Message> &src);
sptr<Message> RTMediaFormat_GetFormat(struct RTMediaFormat *media_format);
void RTMediaFormat_Destory(struct RTMediaFormat *media_format);

__END_DECLS

#endif // AMEBA_FWK_MEDIA_PLAYBACK_MEDIA_RTMEDIA_FORMAT_H