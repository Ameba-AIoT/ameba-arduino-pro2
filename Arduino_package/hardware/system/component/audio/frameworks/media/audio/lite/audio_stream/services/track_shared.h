/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from PanKore
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_TRACK_SHARED_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_TRACK_SHARED_H

#include <stdint.h>
#include <sys/types.h>

#include "minifloat.h"
#include "single_state_queue.h"
//#include "osal_c/osal_sem.h"
#include "osal_c/osal_condition.h"
#include "osal_c/osal_time.h"
#include "osal_cxx/threads.h"
#include "log/log.h"
#include "osal_cxx/refptr.h"
#include "raw_resampler_public.h"

//#define	INT_MAX		0x7fffffff

//#define USE_SYSCALL;

namespace ameba::audio
{

// ----------------------------------------------------------------------------

#define CBLK_UNDERRUN   0x01
#define CBLK_FORCEREADY 0x02
#define CBLK_INVALID    0x04
#define CBLK_DISABLED   0x08
#define CBLK_LOOP_CYCLE 0x20
#define CBLK_LOOP_FINAL 0x40
#define CBLK_BUFFER_END 0x80
#define CBLK_OVERRUN   0x100
#define CBLK_INTERRUPT 0x200
#define CBLK_STREAM_END_DONE 0x400

#define MAX_RUN_OFFLOADED_TIMEOUT_MS 20000

struct AudioTrackSharedStreaming {
	volatile uint32_t read_ptr;
	volatile uint32_t write_ptr;
	volatile uint32_t flush_;
	//volatile int32_t read_ptr;
	//volatile int32_t write_ptr;
	//volatile int32_t flush_;
	volatile uint32_t underrun_frames;
};

typedef SingleStateQueue<AudioPlaybackRate> PlaybackRateQueue;

// ----------------------------------------------------------------------------

struct audio_track_cblk_t {
//                            audio_track_cblk_t();
//                /*virtual*/ ~audio_track_cblk_t() { }

	uint32_t    server;
	uint32_t    pad1_;
	volatile    uint32_t     futex_;
	//volatile    int32_t     futex_;

#define CBLK_FUTEX_WAKE 1

//private:

	uint32_t    minimun;
	gain_minifloat_packed_t left_right_volume;
	uint32_t    sample_rate;
	PlaybackRateQueue::Shared playback_rate_queue;

	uint16_t    send_level;
	uint16_t    pad2_;

public:

	volatile    uint32_t     flags;
	//volatile    int32_t     flags;
	//OsalSem     cblk_sem_;
	OsalMutex   cblk_mutex_;
	OsalCondition cblk_cond_;

public:
	union {
		AudioTrackSharedStreaming   streaming;
		//AudioTrackSharedStatic      shared_static;
		int                         align[8];
	} u;

};


class Proxy : public RefPtr
{
protected:
	Proxy(audio_track_cblk_t *cblk, void *buffers, size_t frame_count, size_t frame_size, bool is_out,
		  bool client_in_server);
	virtual ~Proxy() { }

public:
	struct Buffer {
		size_t  frame_count;
		void   *raw_data;
		size_t  non_config;
	};

protected:

	audio_track_cblk_t *const   cblk_;
	void *const     buffers_;
	const size_t    frame_count_;
	const size_t    frame_size_;
	const size_t    frame_count_p2_;
	const bool      is_out_;
	const bool      client_in_server_;
	bool            is_shut_down_;
	size_t          unreleased_;
};

class ClientProxy : public Proxy
{
public:
	ClientProxy(audio_track_cblk_t *cblk, void *buffers, size_t frame_count, size_t frame_size,
				bool is_out, bool client_in_server);
	virtual ~ClientProxy() { }

	//static const struct timespec forever_;
	//static const struct timespec non_blocking_;
	static const OsalTimespec forever_;
	static const OsalTimespec non_blocking_;

	res_t    GetAvailableBuffer(Buffer *buffer, const OsalTimespec *requested = NULL,
								OsalTimespec *elapsed = NULL);
	void        ReleaseBuffer(Buffer *buffer);
	//void        IPCDied();
	void        Interrupt();
	size_t      GetPosition()
	{
		return epoch_ + cblk_->server;
	}
	void        SetEpoch(size_t epoch)
	{
		epoch_ = epoch;
	}
	void        SetMinimum(size_t minimum)
	{
		if (minimum > UINT32_MAX) {
			minimum = UINT32_MAX;
		}
		cblk_->minimun = (uint32_t) minimum;
	}
	virtual size_t  GetMisalignment();
	size_t      GetEpoch() const
	{
		return epoch_;
	}
	size_t      GetFramesFilled();

private:
	size_t      epoch_;
};

class AudioTrackClientProxy : public ClientProxy
{
public:
	AudioTrackClientProxy(audio_track_cblk_t *cblk, void *buffers, size_t frame_count,
						  size_t frame_size, bool client_in_server = false)
		: ClientProxy(cblk, buffers, frame_count, frame_size, true /*is_out*/,
					  client_in_server),
		  playback_rate_mutator_(&cblk->playback_rate_queue) { }
	virtual ~AudioTrackClientProxy() { }

	void        SetSendLevel(float sendLevel)
	{
		cblk_->send_level = uint16_t(sendLevel * 0x1000);
	}

	void        SetVolumeLR(gain_minifloat_packed_t volumeLR)
	{
		cblk_->left_right_volume = volumeLR;
	}

	void        SetSampleRate(uint32_t sample_rate)
	{
		cblk_->sample_rate = sample_rate;
	}

	void        SetPlaybackRate(const AudioPlaybackRate &playbackRate)
	{
		playback_rate_mutator_.push(playbackRate);
	}

	virtual void Flush();

	virtual uint32_t    GetUnderrunFrames() const
	{
		return cblk_->u.streaming.underrun_frames;
	}

	bool        ClearStreamEndDone();

	bool        GetStreamEndDone() const;

	res_t    WaitStreamEndDone(const OsalTimespec *requested);

private:
	PlaybackRateQueue::Mutator   playback_rate_mutator_;
};


class AudioRecordClientProxy : public ClientProxy
{
public:
	AudioRecordClientProxy(audio_track_cblk_t *cblk, void *buffers, size_t frame_count,
						   size_t frame_size)
		: ClientProxy(cblk, buffers, frame_count, frame_size,
					  false /*is_out*/, false /*client_in_server*/) { }
	~AudioRecordClientProxy() { }
};

class ServerProxy : public Proxy
{
protected:
	ServerProxy(audio_track_cblk_t *cblk, void *buffers, size_t frame_count, size_t frame_size,
				bool is_out, bool client_in_server);
public:
	virtual ~ServerProxy() { }

	virtual res_t    GetAvailableBuffer(Buffer *buffer, bool ack_flush = false);

	virtual void        ReleaseBuffer(Buffer *buffer);

protected:
	size_t      avail_to_client_;
	int32_t     flush_;
};

class AudioTrackServerProxy : public ServerProxy
{
public:
	AudioTrackServerProxy(audio_track_cblk_t *cblk, void *buffers, size_t frame_count,
						  size_t frame_size, bool client_in_server = false, uint32_t sample_rate = 0)
		: ServerProxy(cblk, buffers, frame_count, frame_size, true /*is_out*/, client_in_server),
		  playback_rate_observer_(&cblk->playback_rate_queue)
	{
		cblk_->sample_rate = sample_rate;
		playback_rate_ = AUDIO_PLAYBACK_RATE_DEFAULT;
	}
protected:
	virtual ~AudioTrackServerProxy() { }

public:
	uint32_t    GetSampleRate() const
	{
		return cblk_->sample_rate;
	}
	uint16_t    GetSendLevel_U4_12() const
	{
		return cblk_->send_level;
	}
	gain_minifloat_packed_t GetVolumeLR() const
	{
		return cblk_->left_right_volume;
	}

	virtual size_t      FramesReady();

	virtual void        FramesReadyIsCalledByMultipleThreads() { }

	bool     SetStreamEndDone();

	virtual void        TallyUnderrunFrames(uint32_t frame_count);

	virtual uint32_t    GetUnderrunFrames() const
	{
		return cblk_->u.streaming.underrun_frames;
	}

	virtual size_t      FramesReleased() const
	{
		return cblk_->server;
	}

	AudioPlaybackRate GetPlaybackRate();

private:
	AudioPlaybackRate             playback_rate_;
	PlaybackRateQueue::Observer   playback_rate_observer_;
};

class AudioRecordServerProxy : public ServerProxy
{
public:
	AudioRecordServerProxy(audio_track_cblk_t *cblk, void *buffers, size_t frame_count,
						   size_t frame_size, bool client_in_server)
		: ServerProxy(cblk, buffers, frame_count, frame_size, false /*is_out*/, client_in_server) { }
protected:
	virtual ~AudioRecordServerProxy() { }
};

// ----------------------------------------------------------------------------

}; // namespace ameba::audio

#endif // AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_FWK_INCLUDE_TRACK_SHARED_H
