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

#ifndef AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_MIXER_H
#define AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_MIXER_H

#include <stdint.h>
#include <sys/types.h>

#include "osal_c/osal_compat.h"
#include "osal_cxx/threads.h"

#include "hardware/audio/audio_hw_types.h"
#include "track_server_buffer_agent.h"
#include "buffer_agents.h"
#include "raw_resampler.h"


namespace ameba::audio
{

class RawMixer
{
public:
	RawMixer(size_t frame_count, uint32_t sample_rate,
			 uint32_t max_track_num = MAX_TRACKS_NUM);
	~RawMixer();

	void        SetTrackVolume(int track_mask, uint32_t channel, float volume, bool should_ramp);
	void        SetEffectVolume(int track_mask, float volume, bool should_ramp);
	int         GetTrackMask(uint32_t channel_count, uint32_t format);
	void        SetTrackWorkBuffer(int track_mask, void *buffer);
	void        SetTrackFormat(int track_mask, uint32_t format);
	void        SetTrackMixerFormat(int track_mask, uint32_t format);
	void        SetTrackChannelCount(int track_mask, uint32_t channel_count);
	void        SetTrackMixerChannelCount(int track_mask, uint32_t channel_count);
	void        SetTrackSampleRate(int track_mask, uint32_t rate);
	void        SetTrackTimeStretch(int track_mask, const AudioPlaybackRate &playbackRate);
	void        ReSetTrackResampler(int track_mask);
	void        RemoveTrackResampler(int track_mask);
	void        RemoveTrackMask(int track_mask);
	void        Enable(int track_mask);
	void        Disable(int track_mask);
	void        SetBufferAgent(int track_mask, TrackServerBufferAgent *buffer_agent);
	void        MixData(int64_t pts);
	uint32_t    TrackMasks() const
	{
		return track_masks_;
	}
	size_t      GetFrameSizeUnreleased(int track_mask) const;

	static inline bool IsRawMixerSupportedFormat(uint32_t format)
	{
		switch (format) {
		case AUDIO_HW_FORMAT_PCM_8_BIT:
		case AUDIO_HW_FORMAT_PCM_16_BIT:
		case AUDIO_HW_FORMAT_PCM_24_BIT_PACKED:
		case AUDIO_HW_FORMAT_PCM_32_BIT:
		case AUDIO_HW_FORMAT_PCM_FLOAT:
			return true;
		default:
			return false;
		}
	}

	enum {
		VOLUME_LEFT = 0,
		VOLUME_RIGHT = 1,
	};

	static const uint32_t                    TRACK0 = 0x1000;
	//static const uint32_t                    MAX_TRACKS_NUM = 32;
	static const uint32_t                    MAX_TRACKS_NUM = 4;
	static const uint32_t                    MAX_CHANNELS_NUM = 8;
	static const uint32_t                    MAX_VOLUMES_NUM = 2;
	static const uint16_t                    INT_VOLUME_GAIN = 0x1000;
	static const CONSTEXPR float             FLOAT_VOLUME_GAIN = 1.0f;

private:
	struct MixerWorker;
	struct TrackInMixer;

	typedef void (*TrackProcessFn)(TrackInMixer *t, int32_t *output_buffer, size_t out_frames_num, int32_t *temp,
								   int32_t *aux);
	static const int ONE_TIME_MIX_DATA_SIZE_PER_CHANNEL = 16;
	struct TrackInMixer {
		bool           ShouldVolumeGradualChange()
		{
			return (int_volume_change_per_frame[0] | int_volume_change_per_frame[1] | int_aux_level_change_per_frame) != 0;
		}
		bool           SetRawResampler(uint32_t track_sample_rate, uint32_t dev_sample_rate);
		bool           ShouldResample() const
		{
			return audio_resampler != NULL;
		}
		void           ResetRawResampler()
		{
			if (audio_resampler != NULL) {
				audio_resampler->Reset();
			}
		}
		void           ProcessVolumeGradualChange(bool aux, bool useFloat = false);
		size_t         GetFrameSizeUnreleased() const
		{
			return audio_resampler != NULL ? audio_resampler->GetFrameSizeUnreleased() : 0;
		};
		void           ReconfigureBufferAgents();
		res_t          PrepareForReformat();
		void           UnprepareForReformat();
		bool           SetPlaybackRate(const AudioPlaybackRate &playbackRate);

		AudioPlaybackRate                      mPlaybackRate;
		union {
			int16_t                            current_int_volume[MAX_VOLUMES_NUM];
			int32_t                            left_right_volume;
		};
		bool                                   need_mute;
		bool                                   need_effect;
		int32_t                                last_int_volume[MAX_VOLUMES_NUM];
		int32_t                                int_volume_change_per_frame[MAX_VOLUMES_NUM];
		int32_t                                int_aux_level_change_per_frame;
		int32_t                                last_int_aux_level;
		int16_t                                current_int_aux_level;
		uint16_t                               frame_count;
		uint8_t                                channel_count;
		uint16_t                               track_enabled;
		/*provides data for resampler....volume mixer...*/
		TrackServerBufferAgent                *buffer_agent;
		/*origin track server buf agent...*/
		TrackServerBufferAgent                *input_buffer_agent;    // externally provided buffer provider.
		/*get buf from input_buffer_provider and reformat...*/
		PassthruBufferAgent                   *reformat_buffer_agent; // provider wrapper for reformatting.
		PassthruBufferAgent                   *time_stretch_buffer_agent;
		mutable TrackServerBufferAgent::Buffer buffer;
		TrackProcessFn                         track_process_data_func;
		const void                            *data_in;
		RawResampler                          *audio_resampler;
		uint32_t                               sample_rate;
		int32_t                               *work_buffer;
		int32_t                               *effect_buffer;
		uint32_t                               mixer_format;
		uint32_t                               track_format;
		uint32_t                               mixer_format_for_track;
		float                                  current_float_volume[MAX_VOLUMES_NUM];
		float                                  last_float_volume[MAX_VOLUMES_NUM];
		float                                  float_volume_change_per_frame[MAX_VOLUMES_NUM];
		float                                  current_float_aux_level;
		float                                  last_float_aux_level;
		float                                  float_aux_level_change_per_frame;
		uint32_t                               mixer_channel_count;
	};

	typedef void (*MixerProcessDataFn)(MixerWorker *state, int64_t pts);
	struct MixerWorker {
		uint32_t                                enabled_track_masks;
		uint32_t                                needs_changed_mask;
		size_t                                  frame_count;
		MixerProcessDataFn                      mixer_process_data_func;
		int32_t                                *buffer_ready_mix_to_work_buffer;
		int32_t                                *buffer_after_resample;
		TrackInMixer                            tracks[MAX_TRACKS_NUM] __attribute__((aligned(32)));
	};

	uint32_t                                    track_masks_;
	const uint32_t                              configured_masks_;
	const uint32_t                              sample_rate_;

private:
	enum {
		MIXER_BEHAVIOR_ONETRACK_NORESAMPLE,
	};

	enum {
		TRACK_BEHAVIOR_DONOTHING,
		TRACK_BEHAVIOR_RESAMPLE,
		TRACK_BEHAVIOR_NORESAMPLE,
		TRACK_BEHAVIOR_NORESAMPLEMONO,
	};

	/*
	*******TRACK process funcs *******************************************************************
	*/
	static TrackProcessFn     GetTrackProcessFn(int track_behavior, uint32_t channel_count, uint32_t format_for_track, uint32_t mixerOutFormat);
	static void        TrackProcessFnDoNothing(TrackInMixer *t, int32_t *out, size_t frames_num, int32_t *temp, int32_t *aux);

	template <int MIXTYPE, typename TYPE_OUTPUT, typename TYPE_INPUT, typename TYPE_EFFECT>
	static void        TrackProcessFnDoResample(TrackInMixer *t, TYPE_OUTPUT *out, size_t frame_count, TYPE_OUTPUT *temp, TYPE_EFFECT *aux);

	template <int MIXTYPE, typename TYPE_OUTPUT, typename TYPE_INPUT, typename TYPE_EFFECT>
	static void        TrackProcessFnNoResample(TrackInMixer *t, TYPE_OUTPUT *out, size_t frame_count, TYPE_OUTPUT *temp, TYPE_EFFECT *aux);

	/*
	*******MIXER process funcs *******************************************************************
	*/
	static MixerProcessDataFn GetMixerProcessFn(int mixer_behavior, uint32_t channel_count, uint32_t format_for_track, uint32_t mixerOutFormat);
	static void        MixerProcessFnBegin(MixerWorker *state, int64_t pts);
	static void        MixerProcessDoNothing(MixerWorker *state, int64_t pts);
	static void        MixerProcessNoResample(MixerWorker *state, int64_t pts);
	static void        MixerProcessDoResample(MixerWorker *state, int64_t pts);

	template <int MIXTYPE, typename TYPE_OUTPUT, typename TYPE_INPUT, typename TYPE_EFFECT>
	static void        MixerProcessFnOneTrackNoResample(MixerWorker *state, int64_t pts);

	/*
	*******VOLUME process funcs *******************************************************************
	*/
	template <int MIXTYPE, bool USEFLOATVOL, bool ADJUSTVOL, typename TYPE_OUTPUT, typename TYPE_INPUT, typename TYPE_EFFECT>
	static void        MixVolumeToData(TYPE_OUTPUT *out, size_t outFrames, const TYPE_INPUT *in, TYPE_EFFECT *aux, bool ramp, RawMixer::TrackInMixer *t);

	/*
	*******format process funcs *******************************************************************
	*/
	static void        Transfer32To16BitAndSum(void *out, uint32_t mixerOutFormat, void *in, uint32_t format_for_track, size_t sampleCount);

	MixerWorker                                 mixer_worker_ __attribute__((aligned(32)));
	static uint64_t                             time_freq_;
	//static pthread_once_t                       run_once_;
	static bool                                 run_once_;   //jackie_ren add

	/*
	*******other process funcs *******************************************************************
	*/
	void        ChangeMixerWorkerMask(uint32_t mask);
	bool        SetChannelCount(int track_mask, uint32_t track_channel_count, uint32_t mixer_channel_count);
	static int64_t     CalculatePTSOut(const TrackInMixer &t, int64_t base_pts, int output_frame_index);
	//static void        TimeFreqInit();

};

} // namespace ameba::audio

#endif // AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_AUDIO_MIXER_H
