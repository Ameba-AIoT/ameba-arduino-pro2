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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_ID3_H_
#define AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_ID3_H_

#include <string>

#include "osal_c/osal_compat.h"
#include "osal_cxx/refptr.h"

namespace ameba::media
{

class DataSourceBase;

class ID3
{
public:
	enum Version {
		ID3_UNKNOWN,
		ID3_V1,
		ID3_V1_1,
		ID3_V2_2,
		ID3_V2_3,
		ID3_V2_4,
	};

	explicit ID3(DataSourceBase *source, bool ignore_v1 = false, off64_t offset = 0);
	ID3(const uint8_t *data, size_t size, bool ignore_v1 = false);
	~ID3();

	bool IsValid() const;

	Version GetVersion() const;

	const void *GetAlbumArt(size_t *length, std::string &mime) const;

	struct Iterator {
		Iterator(const ID3 &parent, const char *id);
		~Iterator();

		bool Done() const;
		void GetID(std::string &id) const;
		void GetString(std::string &s) const;
		void GetString(std::string &s, std::string &ss) const;
		const uint8_t *GetData(size_t *length) const;
		void Next();

	private:
		const ID3 &parent_;
		char *id_;
		size_t offset_;

		const uint8_t *frame_data_;
		size_t frame_size_;

		void FindFrame();

		size_t GetHeaderLength() const;
		void Getstring(std::string &s, bool secondhalf) const;

		Iterator(const Iterator &);
		Iterator &operator=(const Iterator &);
	};

	size_t GetRawSize() const
	{
		return raw_size_;
	}

private:
	bool is_valid_;
	uint8_t *data_;
	size_t size_;
	size_t first_frame_offset_;
	Version version_;

	// size of the ID3 tag including header before any unsynchronization.
	// only valid for IDV2+
	size_t raw_size_;

	bool ParseV1(DataSourceBase *source);
	bool ParseV2(DataSourceBase *source, off64_t offset);
	void RemoveUnsynchronization();
	bool RemoveUnsynchronizationV2_4(bool i_tunes_hack);

	static bool ParseSyncsafeInteger(const uint8_t encoded[4], size_t *x);

	ID3(const ID3 &);
	ID3 &operator=(const ID3 &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_DEMUX_EXTRACTORS_MP3_MP3_ID3_H_

