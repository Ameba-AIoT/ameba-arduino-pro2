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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_DATA_CONVERTER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_DATA_CONVERTER_H

#include "osal_cxx/errors.h"
#include "osal_cxx/refptr.h"

#include "media/common/media_defs.h"

namespace ameba::media
{

class CodecBufferInfo;

// DataConverter base class, defaults to memcpy
class DataConverter : public RefPtr
{
public:
	virtual size_t SourceSize(size_t dest_size); // will clamp to SIZE_MAX
	virtual size_t DestSize(size_t src_size); // will clamp to SIZE_MAX

	res_t Convert(const sptr<CodecBufferInfo> &src, sptr<CodecBufferInfo> &dest);
	virtual ~DataConverter();

protected:
	virtual res_t HandleConvert(const sptr<CodecBufferInfo> &src, sptr<CodecBufferInfo> &dest);
};

// SampleConverterBase uses a ratio to calculate the src and dest sizes
// based on src and dest sample sizes.
class SampleConverterBase : public DataConverter
{
public:
	virtual size_t SourceSize(size_t dest_size);
	virtual size_t DestSize(size_t src_size);

protected:
	virtual res_t HandleConvert(const sptr<CodecBufferInfo> &src, sptr<CodecBufferInfo> &dest) = 0;

	// src_size = src_sample_size / dest_sample_size * dest_size
	SampleConverterBase(uint32_t src_sample_size, uint32_t dest_sample_size)
		: src_sample_size_(src_sample_size),
		  dest_sample_size_(dest_sample_size) { }
	size_t src_sample_size_;
	size_t dest_sample_size_;
};

// AudioConverter converts between audio PCM formats
class AudioConverter : public SampleConverterBase
{
public:
	// return nullptr if conversion is not needed or not supported
	static AudioConverter *Create(AudioEncoding src, AudioEncoding dest);

protected:
	virtual res_t HandleConvert(const sptr<CodecBufferInfo> &src, sptr<CodecBufferInfo> &dest);

private:
	AudioConverter(
		AudioEncoding src, size_t src_sample_size,
		AudioEncoding dest, size_t dest_sample_size)
		: SampleConverterBase(src_sample_size, dest_sample_size),
		  src_encoding_(src),
		  dest_encoding_(dest) { }
	AudioEncoding src_encoding_;
	AudioEncoding dest_encoding_;
};

} // namespace ameba::media

#endif
