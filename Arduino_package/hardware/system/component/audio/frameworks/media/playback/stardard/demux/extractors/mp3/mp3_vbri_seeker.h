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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_VBRI_SEEKER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_VBRI_SEEKER_H

#include <vector>

#include "mp3_seeker.h"

#include "osal_c/osal_compat.h"

namespace ameba::media
{

class DataSourceBase;

class VBRISeeker : public MP3Seeker
{
public:
	static VBRISeeker *CreateFromSource(
		DataSourceBase *source, off64_t post_id3_pos);

	virtual bool GetDuration(int64_t *duration_us);
	virtual bool GetOffsetForTime(int64_t *time_us, off64_t *pos);

private:
	off64_t base_pos_;
	int64_t duration_us_;
	std::vector<uint32_t> segments_;

	VBRISeeker();

	DISALLOW_COPY_AND_MOVE(VBRISeeker);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_VBRI_SEEKER_H
