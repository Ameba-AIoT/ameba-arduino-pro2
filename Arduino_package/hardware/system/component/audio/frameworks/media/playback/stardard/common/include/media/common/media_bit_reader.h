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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BIT_READER_H

#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BIT_READER_H

#include "utils/nocopyable.h"

#include <sys/types.h>
#include <stdint.h>

namespace ameba::media
{

class MediaBitReader
{
public:
	MediaBitReader(const uint8_t *data, size_t size);
	virtual ~MediaBitReader();

	// Tries to get |n| bits. If not successful, returns |fallback|. Otherwise, returns result.
	// Reading 0 bits will always succeed and return 0.
	uint32_t GetBitsWithFallback(size_t n, uint32_t fallback);

	// Tries to get |n| bits. If not successful, returns false. Otherwise, stores result in |out|
	// and returns true. Use !OverRead() to determine if this call was successful. Reading 0 bits
	// will always succeed and write 0 in |out|.
	bool GetBitsGraceful(size_t n, uint32_t *out);

	// Gets |n| bits and returns result. ABORTS if unsuccessful. Reading 0 bits will always
	// succeed.
	uint32_t GetBits(size_t n);

	// Tries to skip |n| bits. Returns true iff successful. Skipping 0 bits will always succeed.
	bool SkipBits(size_t n);

	// "Puts" |n| bits with the value |x| back virtually into the bit stream. The put-back bits
	// are not actually written into the data, but are tracked in a separate buffer that can
	// store at most 32 bits. This is a no-op if the stream has already been over-read.
	void PutBits(uint32_t x, size_t n);

	size_t NumBitsLeft() const;

	const uint8_t *Data() const;

	// Returns true iff the stream was over-read (e.g. any GetBits operation has been unsuccessful
	// due to overread (and not trying to read >32 bits).)
	bool OverRead() const
	{
		return over_read_;
	}

protected:
	const uint8_t *data_;
	size_t size_;

	uint32_t pond_;  // left-aligned bits
	size_t num_bits_left_;
	bool over_read_;

	virtual bool FillReservoir();

	DISALLOW_COPY_AND_MOVE(MediaBitReader);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_BIT_READER_H
