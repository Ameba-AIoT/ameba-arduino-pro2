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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_BUFFER_H
#define AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_BUFFER_H

#include "media/codec/omxil/OMX_Core.h"

namespace ameba::media
{

class CodecBufferInfo;
class OMXNode;

class OMXBuffer
{
public:
	// sOMXBufferPreset is used in places where we are referring to a pre-registered
	// buffer on a port. It has type kBufferTypePreset and range_length_ of 0.
	static OMXBuffer sOMXBufferPreset;

	// Default constructor, constructs a buffer of type kBufferTypeInvalid.
	OMXBuffer();

	// Constructs a buffer of type kBufferTypePreset with range_offset_ set to
	// |codec_buffer|'s offset and range_length_ set to |codec_buffer|'s size (or 0
	// if |codec_buffer| is NULL).
	OMXBuffer(const sptr<CodecBufferInfo> &codec_buffer);

	~OMXBuffer();

private:
	friend class OMXNode;

	enum BufferType {
		kBufferTypeInvalid = 0,
		kBufferTypePreset,
	};

	BufferType buffer_type_;

	OMX_U8  *ptr_;
	OMX_U32 range_offset_;
	OMX_U32 range_length_;

	// Move assignment
	OMXBuffer &operator=(OMXBuffer &&);

	// Deleted copy constructor and assignment.
	OMXBuffer(const OMXBuffer &) = delete;
	OMXBuffer &operator=(const OMXBuffer &) = delete;
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_CODEC_MEDIA_CODEC_OMX_OMX_BUFFER_H