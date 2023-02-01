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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_ESDS_H
#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_ESDS_H

#include <stdint.h>

#include "media/common/media_errors.h"

namespace ameba::media
{

class ESDS
{
public:
	ESDS(const void *data, size_t size);
	~ESDS();

	res_t InitCheck() const;

	res_t GetObjectTypeIndication(uint8_t *object_type_Indication) const;
	res_t GetCodecSpecificInfo(const void **data, size_t *size) const;
	res_t GetCodecSpecificOffset(size_t *offset, size_t *size) const;
	res_t GetBitRate(uint32_t *brateMax, uint32_t *brateAvg) const;
	res_t GetStreamType(uint8_t *stream_type) const;

private:
	enum {
		kTagESDescriptor            = 0x03,
		kTagDecoderConfigDescriptor = 0x04,
		kTagDecoderSpecificInfo     = 0x05
	};

	uint8_t *data_;
	size_t size_;

	res_t init_check_;

	size_t decoder_specific_offset_;
	size_t decoder_specific_length_;
	uint8_t object_type_indication_;
	uint8_t stream_type_;
	uint32_t bit_rate_max_;
	uint32_t bit_rate_avg_;

	res_t SkipDescriptorHeader(
		size_t offset, size_t size,
		uint8_t *tag, size_t *data_offset, size_t *data_size) const;

	res_t Parse();
	res_t ParseESDescriptor(size_t offset, size_t size);
	res_t ParseDecoderConfigDescriptor(size_t offset, size_t size);

	ESDS(const ESDS &);
	ESDS &operator=(const ESDS &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_ESDS_H