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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_EXTRACTOR_H
#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_EXTRACTOR_H

#include <stdio.h>

#include "osal_c/osal_compat.h"

#include "media/demux/media_extractor.h"
#include "media/common/meta_data_base.h"

namespace ameba::media
{

class DataSourceBase;
class MP3Seeker;
struct Mp3Meta;

class MP3Extractor : public MediaExtractor
{
public:
	MP3Extractor(DataSourceBase *source, Mp3Meta *meta);
	~MP3Extractor();

	virtual size_t GetTracksNum();
	virtual MediaTrack *GetTrack(size_t index);
	virtual res_t GetTrackMetaData(MetaDataBase &meta, size_t index, uint32_t flags);

	virtual res_t GetMetaData(MetaDataBase &meta);
	virtual const char *Name()
	{
		return "MP3Extractor";
	}

private:
	res_t init_check_;

	DataSourceBase *data_source_;
	off64_t first_frame_pos_;
	MetaDataBase meta_;
	uint32_t fixed_header_;
	MP3Seeker *mp3_seeker_;

	MP3Extractor(const MP3Extractor &);
	MP3Extractor &operator=(const MP3Extractor &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_EXTRACTOR_H
