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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_XING_SEEKER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_XING_SEEKER_H

#include "mp3_seeker.h"

namespace ameba::media
{

class DataSourceBase;

class XINGSeeker : public MP3Seeker
{
public:
	static XINGSeeker *CreateFromSource(
		DataSourceBase *source, off64_t first_frame_pos);

	virtual bool GetDuration(int64_t *duration_us);
	virtual bool GetOffsetForTime(int64_t *time_us, off64_t *pos);

	virtual int32_t GetEncoderDelay();
	virtual int32_t GetEncoderPadding();

private:
	int64_t first_frame_pos_;
	int64_t duration_us_;
	int32_t size_bytes_;
	int32_t encoder_delay_;
	int32_t encoder_padding_;

	// TOC entries in XING header. Skip the first one since it's always 0.
	unsigned char toc_[99];
	bool toc_valid_;

	XINGSeeker();

	DISALLOW_COPY_AND_MOVE(XINGSeeker);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_XING_SEEKER_H

