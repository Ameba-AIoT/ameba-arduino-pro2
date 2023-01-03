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

#ifndef AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_GENERAL_AUDIO_H
#define AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_GENERAL_AUDIO_H

#include <map>

#include "osal_cxx/refptr.h"
#include "osal_cxx/errors.h"
#include "osal_cxx/mutex.h"
#include "osal_cxx/threads.h"

#include "hardware/audio/audio_hw_types.h"
#include "hardware/audio/audio_hw_adapter.h"


#include "output_track.h"

#ifdef CONFIG_AUDIO_MIXER_RECORD
#include "record_track.h"
#endif

namespace ameba::audio
{

class OutputThreadBase;

#define AUDIO_DEFAULT_ADAPTER_ID ((AudioHwAdapterId)0)

class GeneralAudio
{

public:
	static GeneralAudio    *GetInstance();

	void                    Init();

	//playback interfaces
	sptr<OutTrack>          CreateTrackInThread(uint32_t category_type, uint32_t sample_rate,
			uint32_t format, uint32_t channel_count,
			size_t *frame_count, pid_t tid, res_t *status);
	size_t                  GetMinBufferFrames(uint32_t category_type, uint32_t sample_rate);
	res_t                   SetHardwareVolume(float left_volume, float right_volume);
	res_t                   GetHardwareVolume(float *left_volume, float *right_volume);
	res_t                   SetHardwareMute(bool left_mute, bool right_mute);
	res_t                   IsHardwareMuted(bool *left_muted, bool *right_muted);
	res_t                   SetCategoryVolume(uint32_t audio_type, float value);
	float                   GetCategoryVolume(uint32_t audio_type);
	res_t                   SetCategoryMute(uint32_t audio_type, bool mute);
	bool                    IsCategoryMuted(uint32_t audio_type);

#ifdef CONFIG_AUDIO_MIXER_RECORD
	size_t                  GetInputBufferFrame(uint32_t sampleRate, uint32_t format, uint32_t channel_count);
	//record interfaces
	sptr<RecordTrack>       CreateRecordTrackInThread(uint32_t category_type, uint32_t sample_rate,
			uint32_t format, uint32_t channel_count,
			size_t *frame_count, pid_t tid, res_t *status);
	res_t 					CloseInput(AudioIoId audio_io_id);
#endif

private:
	GeneralAudio();
	~GeneralAudio();
	res_t                   LoadHalAdapters();

	//playback interfaces
	res_t                   StartUpOutputs();
	res_t                   CreateOuput(AudioHwAdapterId adapter_id,
										AudioHwDeviceDescriptor *desc,
										AudioHwSampleAttributes *attr,
										AudioIoId *audio_io_id);
	res_t                   CreateOuputLock(AudioHwAdapterId adapter_id,
											AudioHwDeviceDescriptor *desc,
											AudioHwSampleAttributes *attr,
											AudioIoId *audio_io_id);
	AudioHwPortPin          GetPortPinByCategoryType(uint32_t category_type);
	AudioIoId               getOutputByPin(AudioHwPortPin pin);
	sptr<OutputThreadBase>  getOutputThreadBaseByOutput(AudioIoId output);
	uint32_t                allocAudioIoId();

#ifdef CONFIG_AUDIO_MIXER_RECORD
	sptr<RecordThread>      getRecordThreadByInput(AudioIoId input);
	//record interfaces
	uint32_t				allocAudioRecordIoId();
	AudioIoId               OpenInput(AudioHwPortPin pin);
	res_t                   OpenInputLock(AudioHwAdapterId adapter_id,
										  AudioHwDeviceDescriptor *desc,
										  AudioHwSampleAttributes *attr,
										  AudioIoId *audio_io_id);



	AudioHwPortPin          GetRecordPortPin(uint32_t category_type);
	AudioIoId               getInputByPin(AudioHwPortPin pin);
	res_t                   RemoveInputFromThreads(AudioIoId input);
#endif

private:
	static const int32_t            s_max_audio_adapter_num_ = 4; //jackie add to decrease
	static GeneralAudio            *s_instance_;
	static Mutex                    s_mutex_;
	static bool                     s_service_inited;
	int32_t                         audio_adapter_num_;
	struct AudioHwAdapterDescriptor  *audio_adapter_descs_;
	AudioHwAdapter                   *audio_adapters_[s_max_audio_adapter_num_];

	//for playback values
	using OutputThreadBaseMap = std::map<AudioIoId, sptr<OutputThreadBase>>;
	using OutputThreadBasePair = std::pair<AudioIoId, sptr<OutputThreadBase>>;
	using OutputThreadBaseIterator = std::map<AudioIoId, sptr<OutputThreadBase>>::iterator;

	OutputThreadBaseMap              playback_threads_;

	using OutputDescMap = std::map<AudioHwPortPin, AudioIoId>;
	using OutputDescPair = std::pair<AudioHwPortPin, AudioIoId>;
	using OutputDescIterator = std::map<AudioHwPortPin, AudioIoId>::iterator;

	OutputDescMap                    output_desc_;

	volatile int32_t                 audio_io_id_;
	mutable  Mutex                   lock_;
	float                            hardware_left_volume_;
	float                            hardware_right_volume_;
	bool                             hardware_left_mute_;
	bool                             hardware_right_mute_;
#ifdef CONFIG_AUDIO_MIXER_RECORD
	//for record values
	using RecordThreadMap = std::map<AudioIoId, sptr<RecordThread>>;
	using RecordThreadPair = std::pair<AudioIoId, sptr<RecordThread>>;
	using RecordThreadIterator = std::map<AudioIoId, sptr<RecordThread>>::iterator;
	RecordThreadMap                  record_threads_;

	using InputDescMap = std::map<AudioHwPortPin, AudioIoId>;
	using InputDescPair = std::pair<AudioHwPortPin, AudioIoId>;
	using InputDescIterator = std::map<AudioHwPortPin, AudioIoId>::iterator;

	InputDescMap                     input_desc_;
	volatile int32_t                 audio_record_io_id_;
	mutable  Mutex                   record_lock_;
#endif

};

} // namespace ameba::audio

#endif // AMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_GENERAL_AUDIO_H
