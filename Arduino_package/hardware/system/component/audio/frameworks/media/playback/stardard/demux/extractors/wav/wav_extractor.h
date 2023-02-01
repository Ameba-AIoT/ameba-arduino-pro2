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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_WAV_WAV_EXTRACTOR_H
#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_WAV_WAV_EXTRACTOR_H

#include "osal_cxx/errors.h"
#include "media/demux/media_extractor.h"
#include "media/common/meta_data_base.h"

namespace ameba::media
{

class DataSourceBase;

class WAVExtractor : public MediaExtractor
{
public:
	explicit WAVExtractor(DataSourceBase *source);

	virtual size_t GetTracksNum();
	virtual MediaTrack *GetTrack(size_t index);
	virtual res_t GetTrackMetaData(MetaDataBase &meta, size_t index, uint32_t flags);

	virtual res_t GetMetaData(MetaDataBase &meta);
	virtual const char *Name()
	{
		return "WAVExtractor";
	}

	virtual ~WAVExtractor();

private:
	DataSourceBase *data_source_;
	res_t init_check_;
	bool valid_format_;
	uint16_t wave_format_;
	uint16_t num_channels_;
	uint32_t channel_mask_;
	uint32_t sample_rate_;
	uint16_t bits_per_sample_;
	off64_t data_offset_;
	size_t data_size_;
	MetaDataBase meta_data_;

	res_t Init();

	WAVExtractor(const WAVExtractor &);
	WAVExtractor &operator=(const WAVExtractor &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_WAV_WAV_EXTRACTOR_H

