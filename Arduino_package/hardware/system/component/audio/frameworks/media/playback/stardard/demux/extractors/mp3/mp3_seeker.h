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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_SEEKER_H_

#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_SEEKER_H_

#include <stdio.h>
#include <stdint.h>
#include "utils/nocopyable.h"
#include "osal_c/osal_compat.h"

namespace ameba::media
{

class MP3Seeker
{
public:
	MP3Seeker() {}

	virtual bool GetDuration(int64_t *duration_us) = 0;

	// Given a request seek time in "*time_us", find the byte offset closest
	// to that position and return it in "*pos". Update "*time_us" to reflect
	// the actual time that seekpoint represents.
	virtual bool GetOffsetForTime(int64_t *time_us, off64_t *pos) = 0;

	virtual ~MP3Seeker() {}

private:
	DISALLOW_COPY_AND_MOVE(MP3Seeker);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_SEEKER_H_

