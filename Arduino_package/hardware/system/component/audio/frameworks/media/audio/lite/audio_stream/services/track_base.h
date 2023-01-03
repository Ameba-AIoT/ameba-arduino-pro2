#ifndef AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_TRACK_BASE_H
#define AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_TRACK_BASE_H

#include "osal_cxx/refptr.h"
#include "osal_cxx/errors.h"

#include "streaming_threads.h"
#include "track_shared.h"
#include "extended_audio_buffer_agent.h"

static const int64_t kInvalidPTS = 0x7FFFFFFFFFFFFFFFLL;

namespace ameba::audio
{

class ThreadBase::TrackBase: public ExtendedServerBufferAgent, public RefPtr
{

public:
	enum track_state {
		IDLE,
		FLUSHED,
		STOPPED,
		STOPPING_1,
		STOPPING_2,
		RESUMING,
		ACTIVE,
		PAUSING,
		PAUSED,
		STARTING_1,
		STARTING_2,
	};

	enum {
		TRACK_NAME_PENDING = -1,
		TRACK_NAME_FAILURE = -2,
	};

	TrackBase(ThreadBase *thread, uint32_t sample_rate,
			  uint32_t format, uint32_t channel_count,
			  size_t frame_count, bool is_out);

	virtual                ~TrackBase();

	virtual     res_t       GetNextAvailBuffer(TrackServerBufferAgent::Buffer *buffer, int64_t pts) = 0;
	virtual     void        ReleaseHandledBuffer(TrackServerBufferAgent::Buffer *buffer);

	virtual     size_t      ReadyFramesSize() const
	{
		return SIZE_MAX;
	}
	uint32_t GetFormat() const
	{
		return audio_format_;
	}
	uint32_t    GetChannelCount() const
	{
		return channel_count_;
	}
	virtual     uint32_t    GetSampleRate()  const
	{
		return sample_rate_;
	}

	audio_track_cblk_t *GetCblk() const
	{
		return track_cblk_;
	}

	bool        IsTrackStopped() const
	{
		return (track_state_ == STOPPED || track_state_ == FLUSHED);
	}

	bool        IsTrackTerminated() const
	{
		return track_terminated_;
	}
	void        Terminate()
	{
		track_terminated_ = true;
	}
	void        CblkInit();   //jackie add

	const wptr<ThreadBase> track_in_thread_;
	audio_track_cblk_t    *track_cblk_;
	void                  *real_share_data_buffer_;
	track_state            track_state_;
	const uint32_t         sample_rate_;
	const uint32_t         audio_format_;
	const uint32_t         channel_count_;
	const size_t           frame_size_;
	const size_t           frame_count_;
	const bool             is_output_;
	bool                   track_terminated_;
	AudioIoId              track_in_thread_io_id_;

	ServerProxy           *server_proxy_;

protected:
	TrackBase(const TrackBase &);
	TrackBase &operator=(const TrackBase &);
};

}  // namespace ameba::audio

#endif  // AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_TRACK_BASE_H
