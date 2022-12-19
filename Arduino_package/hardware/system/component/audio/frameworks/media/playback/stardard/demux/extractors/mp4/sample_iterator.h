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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP4_SAMPLE_ITERATOR_H
#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP4_SAMPLE_ITERATOR_H

#include <vector>
#include <stdint.h>

#include "osal_cxx/errors.h"

using namespace std;

namespace ameba::media
{

class SampleTable;

struct SampleIterator {
	explicit SampleIterator(SampleTable *table);

	res_t SeekTo(uint32_t sample_index);

	uint32_t GetChunkIndex() const
	{
		return current_chunk_index_;
	}
	uint32_t GetDescIndex() const
	{
		return chunk_desc_;
	}
	off64_t GetSampleOffset() const
	{
		return current_sample_offset_;
	}
	size_t GetSampleSize() const
	{
		return current_sample_size_;
	}
	uint32_t GetSampleTime() const
	{
		return current_sample_time_;
	}
	uint32_t GetSampleDuration() const
	{
		return current_sample_duration_;
	}

	res_t GetSampleSizeDirect(
		uint32_t sample_index, size_t *size);

private:
	SampleTable *table_;

	bool initialized_;

	uint32_t sample_to_chunk_index_;
	uint32_t first_chunk_;
	uint32_t first_chunk_sample_index_;
	uint32_t stop_chunk_;
	uint32_t stop_chunk_Sample_index_;
	uint32_t samples_per_chunk_;
	uint32_t chunk_desc_;

	uint32_t current_chunk_index_;
	off64_t current_chunk_offset_;
	vector<size_t> current_chunk_sample_sizes_;

	uint32_t time_to_sample_Index_;
	uint32_t TTS_sample_index_;
	uint32_t TTS_sample_time_;
	uint32_t TTS_count_;
	uint32_t TTS_duration_;

	uint32_t current_sample_index_;
	off64_t current_sample_offset_;
	size_t current_sample_size_;
	uint32_t current_sample_time_;
	uint32_t current_sample_duration_;

	void Reset();
	res_t FindChunkRange(uint32_t sample_index);
	res_t GetChunkOffset(uint32_t chunk, off64_t *offset);
	res_t FindSampleTimeAndDuration(uint32_t sample_index, uint32_t *time, uint32_t *duration);

	SampleIterator(const SampleIterator &);
	SampleIterator &operator=(const SampleIterator &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP4_SAMPLE_ITERATOR_H
