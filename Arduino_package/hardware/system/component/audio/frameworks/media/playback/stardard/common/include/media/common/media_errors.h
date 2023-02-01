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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_ERRORS_H
#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_ERRORS_H

#include "osal_cxx/errors.h"

namespace ameba::media
{

enum {
	// Media errors
	MEDIA_ERROR_BASE        = -1000,
	ERROR_IO                = MEDIA_ERROR_BASE,
	ERROR_MALFORMED         = MEDIA_ERROR_BASE - 1,
	ERROR_BUFFER_TOO_SMALL  = MEDIA_ERROR_BASE - 2,
	ERROR_UNSUPPORTED       = MEDIA_ERROR_BASE - 3,
	ERROR_END_OF_STREAM     = MEDIA_ERROR_BASE - 4,
	ERROR_READ_AGAIN     = MEDIA_ERROR_BASE - 5,
	ERROR_BAD_NETWORK_CONDITION = MEDIA_ERROR_BASE - 6,

	// Not technically an error.
	INFO_FORMAT_CHANGED    = MEDIA_ERROR_BASE - 5,
	INFO_DISCONTINUITY     = MEDIA_ERROR_BASE - 6,
	INFO_OUTPUT_BUFFERS_CHANGED = MEDIA_ERROR_BASE - 7,
	ERROR_OUT_OF_RANGE      = MEDIA_ERROR_BASE - 8,

	// Codec errors are permitted from 0x80001000 through 0x9000FFFF
	ERROR_CODEC_MAX    = (signed)0x9000FFFF,
	ERROR_CODEC_MIN    = (signed)0x80001000,
};

// action codes for MediaCodecs that tell the upper layer and application
// the severity of any error.
enum CodecAction {
	CODEC_ACTION_FATAL,
	CODEC_ACTION_TRANSIENT,
	CODEC_ACTION_RECOVERABLE,
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_ERRORS_H