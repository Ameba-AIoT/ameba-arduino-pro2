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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP4_SAMPLE_TABLE_H
#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP4_SAMPLE_TABLE_H

#include <sys/types.h>
#include <stdint.h>

#include "osal_cxx/refptr.h"
#include "osal_cxx/mutex.h"
#include "media/common/media_errors.h"

#define SAVE_CHUNK_OFFSET
#define SAVE_SAMPLE_SIZE

namespace ameba::media
{

class DataSourceBase;
struct SampleIterator;

class SampleTable : public RefPtr
{
public:
	explicit SampleTable(DataSourceBase *source);

	bool IsValid() const;

	// type can be 'stco' or 'co64'.
	res_t SetChunkOffsetParams(
		uint32_t type, off64_t data_offset, size_t data_size);

	res_t SetSampleToChunkParams(off64_t data_offset, size_t data_size);

	// type can be 'stsz' or 'stz2'.
	res_t SetSampleSizeParams(
		uint32_t type, off64_t data_offset, size_t data_size);

	res_t SetTimeToSampleParams(off64_t data_offset, size_t data_size);

	res_t SetCompositionTimeToSampleParams(
		off64_t data_offset, size_t data_size);

	res_t SetSyncSampleParams(off64_t data_offset, size_t data_size);

	////////////////////////////////////////////////////////////////////////////

	uint32_t CountChunkOffsets() const;

	uint32_t CountSamples() const;

	res_t GetMaxSampleSize(size_t *size);

	res_t GetMetaDataForSample(
		uint32_t sample_index,
		off64_t *offset,
		size_t *size,
		uint32_t *composition_time,
		bool *is_sync_sample = NULL,
		uint32_t *sample_duration = NULL);

	enum {
		kFlagBefore,
		kFlagAfter,
		kFlagClosest,
		kFlagFrameIndex,
	};
	res_t FindSampleAtTime(
		uint64_t req_time, uint64_t scale_num, uint64_t scale_den,
		uint32_t *sample_index, uint32_t flags);

	res_t FindSyncSampleNear(
		uint32_t start_sample_index, uint32_t *sample_index,
		uint32_t flags);

	res_t FindThumbnailSample(uint32_t *sample_index);

protected:
	~SampleTable();

private:
	struct CompositionDeltaLookup;

	static const uint32_t kChunkOffsetType32;
	static const uint32_t kChunkOffsetType64;
	static const uint32_t kSampleSizeType32;
	static const uint32_t kSampleSizeTypeCompact;

	// Limit the total size of all internal tables to 200MiB.
	static const size_t kMaxTotalSize = 200 * (1 << 20);

	DataSourceBase *data_source_;
	Mutex lock_;

	off64_t chunk_offset_offset_;
	uint32_t chunk_offset_type_;
	uint32_t num_chunk_offsets_;

	off64_t sample_to_chunk_offset_;
	uint32_t num_sample_to_chunk_offsets_;

	off64_t sample_size_offset_;
	uint32_t sample_size_field_size_;
	uint32_t default_sample_size_;
	uint32_t num_sample_sizes_;

	bool has_time_to_sample_;
	uint32_t time_to_sample_count_;
	uint32_t *time_to_sample_;

	struct SampleTimeEntry {
		uint32_t sample_index;
		uint32_t composition_time;
	};
	SampleTimeEntry *sample_time_entries_;

	int32_t *composition_time_delta_entries_;
	size_t num_composition_time_delta_entries_;
	CompositionDeltaLookup *composition_delta_lookup_;

	off64_t sync_sample_offset_;
	uint32_t num_sync_samples_;
	uint32_t *sync_samples_;
	size_t last_sync_sample_index_;

	uint8_t *chunk_offsets_;
	uint8_t *sample_sizes_;

	struct SampleToChunkEntry {
		uint32_t start_chunk;
		uint32_t samples_perChunk;
		uint32_t chunk_desc;
	};
	SampleToChunkEntry *sample_to_chunk_entries_;

	// Approximate size of all tables combined.
	uint64_t total_size_;

	SampleIterator *sample_iterator_;

	friend struct SampleIterator;

	// normally we don't round
	inline uint64_t GetSampleTime(
		size_t sample_index, uint64_t scale_num, uint64_t scale_den) const
	{
		return (sample_index < (size_t)num_sample_sizes_ && sample_time_entries_ != NULL
				&& scale_den != 0)
			   ? (sample_time_entries_[sample_index].composition_time * scale_num) / scale_den : 0;
	}

	res_t GetSampleSize_l(uint32_t sample_index, size_t *sample_size);
	int32_t GetCompositionTimeOffset(uint32_t sample_index);

	static int CompareIncreasingTime(const void *, const void *);

	void BuildSampleEntriesTable();

	SampleTable(const SampleTable &);
	SampleTable &operator=(const SampleTable &);
};

}  // namespace ameba media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP4_SAMPLE_TABLE_H
