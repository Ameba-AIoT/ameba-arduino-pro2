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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_TRACK_H
#define AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_TRACK_H

#include <vector>
#include <sys/types.h>

#include "log/log.h"
#include "osal_cxx/refptr.h"

#include "media/common/media_errors.h"

namespace ameba::media
{

class MediaBufferBase;
class MetaDataBase;
class MetaData;

class MediaTrack : public RefPtr
{
public:
	MediaTrack();

	// To be called before any other methods on this object, except
	// GetFormat().
	virtual res_t Start(MetaDataBase *params = NULL) = 0;

	// Any blocking read call returns immediately with a result of NO_INIT.
	// It is an error to call any methods other than start after this call
	// returns. Any buffers the object may be holding onto at the time of
	// the Stop() call are released.
	// Also, it is imperative that any buffers output by this object and
	// held onto by callers be released before a call to Stop() !!!
	virtual res_t Stop() = 0;

	// Returns the format of the data output by this media track.
	virtual res_t GetFormat(MetaDataBase &format) = 0;

	// Options that modify Read() behaviour. The default is to
	// a) not request a rewind
	// b) not be late, i.e. lateness_us = 0
	struct ReadProperties {
		ReadProperties();

		// Reset everything back to defaults.
		void Reset();

		void SetRewind(int64_t time_us);
		void ClearRewind();
		bool GetRewind(int64_t *time_us) const;

		void SetNonBlocking();
		void ClearNonBlocking();
		bool GetNonBlocking() const;

		// Used to clear all non-persistent properties for multiple buffer reads.
		void ClearNonPersistent()
		{
			ClearRewind();
		}

	private:
		enum Properties {
			kRewindProperty      = 1,
		};

		uint32_t properties_;
		int64_t rewind_time_us_;
		bool non_blocking_;
	} __attribute__((packed)); // sent through Binder

	// Returns a new buffer of data. Call blocks until a
	// buffer is available, an error is encountered of the end of the stream
	// is reached.
	virtual res_t Read(
		MediaBufferBase **buffer, const ReadProperties *properties = NULL) = 0;

	virtual ~MediaTrack();

	sptr<MetaData> GetFormat();
	bool SupportReadMultiple();
	res_t ReadMultiple(
		std::vector<MediaBufferBase *> * /* buffers */, uint32_t /* max_num_buffers = 1 */,
		const ReadProperties * /* properties = nullptr */);

private:
	MediaTrack(const MediaTrack &);
	MediaTrack &operator=(const MediaTrack &);
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_COMMON_MEDIA_COMMON_MEDIA_TRACK_H
