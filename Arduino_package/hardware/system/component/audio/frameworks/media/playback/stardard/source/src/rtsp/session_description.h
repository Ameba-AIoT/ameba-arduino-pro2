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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_SESSION_DESCRIPTION_H

#define AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_SESSION_DESCRIPTION_H

#include <map>
#include <vector>
#include <sys/types.h>
#include "utils/nocopyable.h"
#include "osal_cxx/refptr.h"

namespace ameba::media
{

class RString;

class SessionDescription : public RefPtr
{
public:
	SessionDescription();

	bool setTo(const void *data, size_t size);
	bool IsValid() const;

	// Actually, 1 + number of tracks, as index 0 is reserved for the
	// session description root-level attributes.
	size_t GetTracksNum() const;
	void GetFormat(size_t index, RString *value) const;

	void GetFormatType(
		size_t index, unsigned long *PT,
		RString *desc, RString *params) const;

	bool GetDimensions(
		size_t index, unsigned long PT,
		int32_t *width, int32_t *height) const;

	bool GetDurationUs(int64_t *duration_us) const;

	static void ParseFormatDesc(
		const char *desc, int32_t *time_scale, int32_t *num_channels);

	bool FindAttribute(size_t index, const char *key, RString *value) const;

	// parses strings of the form
	//   npt      := npt-time "-" npt-time? | "-" npt-time
	//   npt-time := "now" | [0-9]+("." [0-9]*)?
	//
	// Returns true iff both "npt1" and "npt2" times were available,
	// i.e. we have a fixed duration, otherwise this is live streaming.
	static bool ParseNTPRange(const char *s, float *npt1, float *npt2);

protected:
	virtual ~SessionDescription();

private:
	typedef std::map<RString, RString> Attribs;

	bool is_valid_;
	std::vector<Attribs> tracks_;
	std::vector<RString> formats_;

	bool Parse(const void *data, size_t size);

	DISALLOW_COPY_AND_MOVE(SessionDescription);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_SOURCE_RTSP_SESSION_DESCRIPTION_H
