/*
 * Copyright (c) 2022 Realtek, LLC.
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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_AMR_AMR_EXTRACTOR_H
#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_AMR_AMR_EXTRACTOR_H

#include <string>
#include <vector>

#include "media/demux/media_extractor.h"
#include "media/common/meta_data_base.h"

namespace ameba::media
{

class Message;

#define OFFSET_TABLE_LEN    300

class AMRExtractor : public MediaExtractor
{
public:
	explicit AMRExtractor(DataSourceBase *source);

	virtual size_t GetTracksNum();
	virtual MediaTrack *GetTrack(size_t index);
	virtual res_t GetTrackMetaData(MetaDataBase &meta, size_t index, uint32_t flags);

	virtual res_t GetMetaData(MetaDataBase &meta);
	virtual const char *Name()
	{
		return "AMRExtractor";
	}

protected:
	virtual ~AMRExtractor();

private:
	DataSourceBase *data_source_;
	MetaDataBase meta_;
	res_t init_check_;
	bool is_wide_;

	off64_t offset_table_[OFFSET_TABLE_LEN]; //5 min
	size_t offset_table_length_;

	AMRExtractor(const AMRExtractor &);
	AMRExtractor &operator=(const AMRExtractor &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_AMR_AMR_EXTRACTOR_H
