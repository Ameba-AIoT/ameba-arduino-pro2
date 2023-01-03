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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP4_MP4_EXTRACTOR_H
#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP4_MP4_EXTRACTOR_H

#include <vector>
#include <map>
#include <string>

//#include <arpa/inet.h>

#include "osal_cxx/refptr.h"
#include "osal_cxx/errors.h"

#include "media/demux/media_extractor.h"
#include "media/utils/rstring.h"
#include "media/common/meta_data_base.h"

using namespace std;

namespace ameba::media
{
class DataSourceBase;
struct CachedRangedDataSource;
class SampleTable;

struct SidxEntry {
	size_t size;
	uint32_t duration_us;
};

struct Trex {
	uint32_t track_ID;
	uint32_t default_sample_description_index;
	uint32_t default_sample_duration;
	uint32_t default_sample_size;
	uint32_t default_sample_flags;
};
class MPEG4Extractor : public MediaExtractor
{
public:
	explicit MPEG4Extractor(DataSourceBase *source, const char *mime = NULL);

	virtual size_t GetTracksNum();
	virtual MediaTrack *GetTrack(size_t index);
	virtual res_t GetTrackMetaData(MetaDataBase &meta, size_t index, uint32_t flags);

	virtual res_t GetMetaData(MetaDataBase &meta);
	virtual const char *Name()
	{
		return "MPEG4Extractor";
	}

protected:
	virtual ~MPEG4Extractor();

private:

	struct PsshInfo {
		uint8_t uuid[16];
		uint32_t datalen;
		uint8_t *data;
	};
	struct Track {
		Track *next;
		MetaDataBase meta;
		uint32_t timescale;
		sptr<SampleTable> sample_table;
		bool includes_expensive_metadata;
		bool skip_track;
		bool has_elst;
		int64_t elst_media_time;
		uint64_t elst_segment_duration;
		bool subsample_encryption;
	};
	vector<SidxEntry> sidx_entries_;
	off64_t moof_offset_;
	bool moof_found_;
	bool mdat_found_;

	vector<PsshInfo> pssh_;

	vector<Trex> trex_;

	DataSourceBase *data_source_;
	CachedRangedDataSource *cached_source_;
	res_t init_check_;
	uint32_t header_timescale_;
	bool has_moov_box_;

	Track *first_track_, *last_track_;

	MetaDataBase file_meta_data_;

	vector<uint32_t> path_;
	RString last_comment_mean_;
	RString last_comment_name_;
	RString last_comment_data_;

	map<uint32_t, RString> meta_key_map_;

	res_t ReadMetaData();
	res_t ParseChunk(off64_t *offset, int depth);

	res_t UpdateAudioTrackInfoFromESDS_MPEG4Audio(
		const void *esds_data, size_t esds_size);

	static res_t VerifyTrack(Track *track);

	res_t ParseTrackHeader(off64_t data_offset, off64_t data_size);

	res_t ParseSegmentIndex(off64_t data_offset, size_t data_size);

	Track *FindTrackByMimePrefix(const char *mime_prefix);

	res_t ParseAC3SampleEntry(off64_t offset);
	res_t ParseAC3SpecificBox(off64_t offset, uint16_t sample_rate);

	MPEG4Extractor(const MPEG4Extractor &);
	MPEG4Extractor &operator=(const MPEG4Extractor &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP4_MP4_EXTRACTOR_H
