/*
 * Copyright (C) 2021 The Ameba Project
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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_TS_PARSER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_TS_PARSER_H

#include "osal_cxx/refptr.h"

namespace ameba::media
{

class TSParser : public RefPtr
{
public:
	enum DiscontinuityType {
		DISCONTINUITY_NONE              = 0,
		DISCONTINUITY_TIME              = 1,
		DISCONTINUITY_AUDIO_FORMAT      = 2,
		DISCONTINUITY_VIDEO_FORMAT      = 4,
		DISCONTINUITY_ABSOLUTE_TIME     = 8,
		DISCONTINUITY_TIME_OFFSET       = 16,

		// For legacy reasons this also implies a time discontinuity.
		DISCONTINUITY_FORMATCHANGE      =
			DISCONTINUITY_AUDIO_FORMAT
			| DISCONTINUITY_VIDEO_FORMAT
			| DISCONTINUITY_TIME,
		DISCONTINUITY_FORMAT_ONLY       =
			DISCONTINUITY_AUDIO_FORMAT
			| DISCONTINUITY_VIDEO_FORMAT,
	};

	DISALLOW_COPY_AND_MOVE(TSParser);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_TS_PARSER_H