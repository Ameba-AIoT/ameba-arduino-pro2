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

#ifndef AMEBA_FWK_MEDIA_PLAYER_LIBMEDIA_EFFECT_PLAYER_IMPL_H
#define AMEBA_FWK_MEDIA_PLAYER_LIBMEDIA_EFFECT_PLAYER_IMPL_H

#include <map>
#include <list>
#include <memory>
#include <string>

#include "osal_cxx/threads.h"
#include "osal_cxx/refptr.h"
#include "audio/audio_track.h"
#include "audio/audio_type.h"
#include "media/rteffect_player.h"

#define MAX_CHANNEL_NUM 8

namespace ameba::media
{

static const int IDLE_PRIORITY = -1;

class SoundEvent;
class EffectPlayerThread;
class EffectPlayerImpl;

class Sample  : public RefPtr
{
public:
	enum sample_state { UNLOADED, LOADING, READY, UNLOADING };
	Sample(int sample_id, const char *path);
	~Sample();
	int      SampleID()
	{
		return sample_id_;
	}
	int      NumChannels()
	{
		return num_channels_;
	}
	int      SampleRate()
	{
		return sample_rate_;
	}
	uint32_t Format()
	{
		return format_;
	}
	size_t   Size()
	{
		return size_;
	}
	int      State()
	{
		return state_;
	}
	uint8_t *Data()
	{
		return data_buffer_;
	}
	res_t    DoLoad();
	void     StartLoad()
	{
		state_ = LOADING;
	}
	void     SetChannelId(int id)
	{
		channel_id_ = id;
	}
	int      GetChannelId()
	{
		return channel_id_;
	}

private:
	void Init();

	int64_t             size_;
	volatile int32_t    ref_count_;
	uint16_t            sample_id_;
	uint16_t            sample_rate_;
	uint8_t             state_;
	uint8_t             num_channels_;
	uint32_t            format_;
	const char         *path_;
	uint8_t            *write_pos_;
	uint8_t            *data_buffer_;
	int                 channel_id_;
};

class SoundEvent
{
public:
	SoundEvent() : channel_id_(0), left_volume_(0), right_volume_(0),
		priority_(IDLE_PRIORITY), rate_(0) {}
	void Set(const sptr<Sample> &sample, int channel_id, float left_volume,
			 float right_volume, int priority, float rate);
	sptr<Sample>    GetSample()
	{
		return sample_;
	}
	int             ChannelID()
	{
		return channel_id_;
	}
	float           LeftVolume()
	{
		return left_volume_;
	}
	float           RightVolume()
	{
		return right_volume_;
	}
	int             Priority()
	{
		return priority_;
	}
	float           Rate()
	{
		return rate_;
	}
	void            Clear()
	{
		channel_id_ = 0;
		sample_.clear();
	}
protected:
	sptr<Sample>    sample_;
	int             channel_id_;
	float           left_volume_;
	float           right_volume_;
	int             priority_;
	float           rate_;
};

class SoundChannel : public SoundEvent
{
public:
	enum state { IDLE, RESUMING, STATE_STOPPING, PAUSED, PLAYING };
	SoundChannel() : state_(IDLE), num_channels_(1),
		pos_(0), auto_paused_(false), muted_(false) {}
	~SoundChannel();
	void Init(EffectPlayerImpl *effect_player);
	void Play(const sptr<Sample> &sample, int channel_id, float left_volume, float right_volume,
			  int priority, float rate);
	res_t SetVolume_l(float left_volume, float right_volume);
	res_t SetVolume(float left_volume, float right_volume);
	void Mute(bool muting);
	void Stop_l();
	void Stop();
	void Pause();
	void AutoPause();
	void Resume();
	void AutoResume();
	void SetRate(float rate);
	int  State()
	{
		return state_;
	}
	void SetPriority(int priority)
	{
		priority_ = priority;
	}
	int  NumChannels()
	{
		return num_channels_;
	}
	void ClearNextEvent()
	{
		next_event_.Clear();
	}
	void NextEvent();
	int  NextChannelID()
	{
		return next_event_.ChannelID();
	}
	void Dump();
	int  GetPrevSampleID(void)
	{
		return prev_sample_id_;
	}
	res_t WriteSample();
private:
	static void Callback(int event, void *user, void *info);
	void Process(int event, void *info, unsigned long toggle);
	bool DoStop_l();

	EffectPlayerImpl                          *effect_player_;

#if ENABLE_USE_AUDIO_LITE
	ameba::audio::AudioTrack                  *audio_track_;
#else
	struct RTAudioTrack                       *audio_track_;
#endif

	int                                        track_buf_size_;
	int                                        write_divider_;
	SoundEvent                                 next_event_;
	Mutex                                      lock_;
	int                                        state_;
	int                                        num_channels_;
	unsigned int                               pos_;
	bool                                       auto_paused_;
	int                                        prev_sample_id_;
	bool                                       muted_;
};


class EffectPlayerImpl
{
	friend class EffectPlayerThread;
	friend class SoundChannel;
public:
	EffectPlayerImpl(int max_channels);
	~EffectPlayerImpl();
	int Load(const char *path, int priority);
	int Load_l(const char *path, int priority);
	bool UnLoad(int sample_id);
	int Play(int sample_id, float left_volume, float right_volume, int priority,
			 float rate);
	void Pause(int channel_id);
	void Mute(bool muting);
	void AutoPause();
	void Resume(int channel_id);
	void AutoResume();
	void Stop(int channel_id);
	void Halt(int sample_id);
	res_t SetVolume(int channel_id, float left_volume, float right_volume);
	void SetPriority(int channel_id, int priority);
	void SetRate(int channel_id, float rate);

	void SampleLoaded(int sample_id);
	sptr<Sample> FindSample(int sample_id);

	void Done_l(SoundChannel *channel);

	void RegisterCallback(struct RTEffectPlayerCallback *callback);
	void *GetUserData()
	{
		return user_data_;
	}
	struct RTEffectPlayerCallback *GetCallback()
	{
		return effect_player_cb_;
	}

private:
	bool CreateAndRunRestartThread();
	bool StartThreads();
	sptr<Sample> FindSample_l(int sample_id);
	SoundChannel *FindChannel(int channel_id);
	SoundChannel *FindNextChannel(int channel_id);
	SoundChannel *AllocateChannel_l(int priority, int sample_id);
	void MoveToFront_l(SoundChannel *channel);
	void Dump();

	void AddToRestartList(SoundChannel *channel);
	void AddToStopList(SoundChannel *channel);
	static void *BeginThread(void *arg);
	int Run();
	void Quit();

	ameba::Mutex                   lock_;
	ameba::Mutex                   restart_lock_;
	Condition                      condition_;
	sptr<EffectPlayerThread>       decode_thread_;
	sptr<EffectPlayerThread>       write_thread_;
	OsalThread                    *restart_thread_;
	SoundChannel                  *channel_pool_;
	std::list<SoundChannel *>       channels_;
	std::list<SoundChannel *>       restart_;
	std::list<SoundChannel *>       stop_;
	std::map< int, sptr<Sample> >  sample_s;
	int                            max_channels_;
	int                            allocated_;
	int                            next_sample_id_;
	int                            next_channel_id_;
	bool                           quit_;
	bool                           muted_;

	ameba::Mutex                   callback_lock_;
	struct RTEffectPlayerCallback *effect_player_cb_;

	void                          *user_data_;
};

} // end namespace ameba::media

#endif /*AMEBA_FWK_MEDIA_PLAYER_LIBMEDIA_EFFECT_PLAYER_IMPL_H*/
