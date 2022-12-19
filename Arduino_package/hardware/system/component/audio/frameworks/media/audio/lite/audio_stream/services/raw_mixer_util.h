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

#ifndef AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_RAW_MIXER_UTIL_H
#define AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_RAW_MIXER_UTIL_H

#include "audio/utils/primitives.h"
#include "audio/utils/format.h"

namespace ameba::audio
{


template<typename T, typename U>
struct IS_SAME_TYPE {
	static const bool value = false;
};

template<typename T>
struct IS_SAME_TYPE<T, T> {
	static const bool value = true;
};

void TransferDataTypeAndMix(int32_t *out, const int32_t *sums, size_t c)
{
	size_t i;
	for (i = 0 ; i < c ; i++) {
		int32_t l = *sums++;
		int32_t r = *sums++;
		int32_t nl = l >> 12;
		int32_t nr = r >> 12;
		l = clamp16(nl);
		r = clamp16(nr);
		*out++ = (r << 16) | (l & 0xFFFF);
	}
}

template <typename TYPE_OUTPUT, typename TYPE_INPUT, typename TYPE_VOLUME>
TYPE_OUTPUT MixVolume(TYPE_INPUT raw_data, TYPE_VOLUME volume);

template <>
inline int32_t MixVolume<int32_t, int16_t, int16_t>(int16_t raw_data, int16_t volume)
{
	return raw_data * volume;
}

template <>
inline int32_t MixVolume<int32_t, int32_t, int16_t>(int32_t raw_data, int16_t volume)
{
	return (raw_data >> 12) * volume;
}

template <>
inline int32_t MixVolume<int32_t, int16_t, int32_t>(int16_t raw_data, int32_t volume)
{
	return raw_data * (volume >> 16);
}

template <>
inline int32_t MixVolume<int32_t, int32_t, int32_t>(int32_t raw_data, int32_t volume)
{
	return (raw_data >> 12) * (volume >> 16);
}

template <>
inline float MixVolume<float, float, int16_t>(float raw_data, int16_t volume)
{
	static const float norm = 1. / (1 << 12);
	return raw_data * volume * norm;
}

template <>
inline float MixVolume<float, float, int32_t>(float raw_data, int32_t volume)
{
	static const float norm = 1. / (1 << 28);
	return raw_data * volume * norm;
}

template <>
inline int16_t MixVolume<int16_t, float, int16_t>(float raw_data, int16_t volume)
{
	return clamp16_from_float(MixVolume<float, float, int16_t>(raw_data, volume));
}

template <>
inline int16_t MixVolume<int16_t, float, int32_t>(float raw_data, int32_t volume)
{
	return clamp16_from_float(MixVolume<float, float, int32_t>(raw_data, volume));
}

template <>
inline float MixVolume<float, int16_t, int16_t>(int16_t raw_data, int16_t volume)
{
	static const float norm = 1. / (1 << (15 + 12));
	return static_cast<float>(raw_data) * static_cast<float>(volume) * norm;
}

template <>
inline float MixVolume<float, int16_t, int32_t>(int16_t raw_data, int32_t volume)
{
	static const float norm = 1. / (1ULL << (15 + 28));
	return static_cast<float>(raw_data) * static_cast<float>(volume) * norm;
}

template <>
inline int16_t MixVolume<int16_t, int16_t, int16_t>(int16_t raw_data, int16_t volume)
{
	return clamp16(MixVolume<int32_t, int16_t, int16_t>(raw_data, volume) >> 12);
}

template <>
inline int16_t MixVolume<int16_t, int32_t, int16_t>(int32_t raw_data, int16_t volume)
{
	return clamp16(MixVolume<int32_t, int32_t, int16_t>(raw_data, volume) >> 12);
}

template <>
inline int16_t MixVolume<int16_t, int16_t, int32_t>(int16_t raw_data, int32_t volume)
{
	return clamp16(MixVolume<int32_t, int16_t, int32_t>(raw_data, volume) >> 12);
}

template <>
inline int16_t MixVolume<int16_t, int32_t, int32_t>(int32_t raw_data, int32_t volume)
{
	return clamp16(MixVolume<int32_t, int32_t, int32_t>(raw_data, volume) >> 12);
}

template <>
inline float MixVolume<float, float, float>(float raw_data, float volume)
{
	return raw_data * volume;
}

template <>
inline float MixVolume<float, int16_t, float>(int16_t raw_data, float volume)
{
	static const float float_from_q_15 = 1. / (1 << 15);
	return raw_data * volume * float_from_q_15;
}

template <>
inline int32_t MixVolume<int32_t, int32_t, float>(int32_t raw_data, float volume)
{
	LOG_ALWAYS_FATAL("MixVolume<int32_t, int32_t, float> Should not be here");
	return raw_data * volume;
}

template <>
inline int32_t MixVolume<int32_t, int16_t, float>(int16_t raw_data, float volume)
{
	static const float u4_12_from_float = (1 << 12);
	return raw_data * volume * u4_12_from_float;
}

template <>
inline int16_t MixVolume<int16_t, int16_t, float>(int16_t raw_data, float volume)
{
	LOG_ALWAYS_FATAL("MixVolume<int16_t, int16_t, float> Runtime Should not be here");
	return clamp16_from_float(MixVolume<float, int16_t, float>(raw_data, volume));
}

template <>
inline int16_t MixVolume<int16_t, float, float>(float raw_data, float volume)
{
	return clamp16_from_float(raw_data * volume);
}

template <typename TYPE_OUTPUT, typename TYPE_INPUT>
inline void MixEffect(TYPE_OUTPUT *raw_effect_data, TYPE_INPUT raw_data)
{
	if (!IS_SAME_TYPE<TYPE_OUTPUT, TYPE_INPUT>::value) {
		LOG_ALWAYS_FATAL("MixEffect type not right: %u %u\n", sizeof(TYPE_OUTPUT), sizeof(TYPE_INPUT));
	}
	*raw_effect_data += raw_data;
}

template<>
inline void MixEffect<float, int16_t>(float *raw_effect_data, int16_t raw_data)
{
	static const float norm = 1. / (1 << 15);
	*raw_effect_data += norm * raw_data;
}

template<>
inline void MixEffect<float, int32_t>(float *raw_effect_data, int32_t raw_data)
{
	static const float norm = 1. / (1 << 27);
	*raw_effect_data += norm * raw_data;
}

template<>
inline void MixEffect<int32_t, int16_t>(int32_t *raw_effect_data, int16_t raw_data)
{
	*raw_effect_data += raw_data << 12;
}

template<>
inline void MixEffect<int32_t, float>(int32_t *raw_effect_data, float raw_data)
{
	RTLOGV("%d:to do", __LINE__);
}

template <typename TYPE_OUTPUT, typename TYPE_INPUT, typename TYPE_VOLUME, typename TYPE_EFFECT>
inline TYPE_OUTPUT MixVolumeAndEffect(TYPE_INPUT raw_data, TYPE_VOLUME volume, TYPE_EFFECT *raw_effect_data)
{
	MixEffect<TYPE_EFFECT, TYPE_INPUT>(raw_effect_data, raw_data);
	return MixVolume<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME>(raw_data, volume);
}

enum {
	TYPE_MIX_STEREO,
	TYPE_MIX_MONO,
	TYPE_MIX_STEREO_ONLY_SAVE,
};


template <int TYPE_MIX, int CHANNEL_COUNT, typename TYPE_OUTPUT, typename TYPE_INPUT, typename TYPE_VOLUME, typename TYPE_EFFECT, typename TYPE_EFFECT_VOLUME>
inline void GradualVolumeMix(TYPE_OUTPUT *out_data, size_t frame_count, const TYPE_INPUT *data_in, TYPE_EFFECT *effect_data,
							 TYPE_VOLUME *volume, const TYPE_VOLUME *volume_change_per_frame, TYPE_EFFECT_VOLUME *effect_volume, TYPE_EFFECT_VOLUME effect_volume_change_per_frame)
{
	if (effect_data != NULL) {
		do {
			TYPE_EFFECT raw_effect_data = 0;
			switch (TYPE_MIX) {
			case TYPE_MIX_STEREO:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ += MixVolumeAndEffect<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME, TYPE_EFFECT>(*data_in++, volume[i], &raw_effect_data);
					volume[i] += volume_change_per_frame[i];
				}
				break;
			case TYPE_MIX_MONO:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ += MixVolumeAndEffect<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME, TYPE_EFFECT>(*data_in, volume[i], &raw_effect_data);
					volume[i] += volume_change_per_frame[i];
				}
				data_in++;
				break;
			case TYPE_MIX_STEREO_ONLY_SAVE:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ = MixVolumeAndEffect<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME, TYPE_EFFECT>(*data_in++, volume[i], &raw_effect_data);
					volume[i] += volume_change_per_frame[i];
				}
				break;
			default:
				LOG_ALWAYS_FATAL("invalid mixtype %d", TYPE_MIX);
				break;
			}
			raw_effect_data /= CHANNEL_COUNT;
			*effect_data++ += MixVolume<TYPE_EFFECT, TYPE_EFFECT, TYPE_EFFECT_VOLUME>(raw_effect_data, *effect_volume);
			effect_volume[0] += effect_volume_change_per_frame;
		} while (--frame_count);
	} else {
		do {
			switch (TYPE_MIX) {
			case TYPE_MIX_STEREO:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ += MixVolume<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME>(*data_in++, volume[i]);
					volume[i] += volume_change_per_frame[i];
				}
				break;
			case TYPE_MIX_MONO:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ += MixVolume<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME>(*data_in, volume[i]);
					volume[i] += volume_change_per_frame[i];
				}
				data_in++;
				break;
			case TYPE_MIX_STEREO_ONLY_SAVE:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ = MixVolume<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME>(*data_in++, volume[i]);
					volume[i] += volume_change_per_frame[i];
				}
				break;
			default:
				LOG_ALWAYS_FATAL("invalid mixtype %d", TYPE_MIX);
				break;
			}
		} while (--frame_count);
	}
}

template <int TYPE_MIX, int CHANNEL_COUNT, typename TYPE_OUTPUT, typename TYPE_INPUT, typename TYPE_VOLUME, typename TYPE_EFFECT, typename TYPE_EFFECT_VOLUME>
inline void volumeMulti(TYPE_OUTPUT *out_data, size_t frame_count, const TYPE_INPUT *data_in, TYPE_EFFECT *effect_data, const TYPE_VOLUME *volume,
						TYPE_EFFECT_VOLUME effect_volume)
{
	if (effect_data != NULL) {
		do {
			TYPE_EFFECT raw_effect_data = 0;
			switch (TYPE_MIX) {
			case TYPE_MIX_STEREO:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ += MixVolumeAndEffect<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME, TYPE_EFFECT>(*data_in++, volume[i], &raw_effect_data);
				}
				break;
			case TYPE_MIX_MONO:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ += MixVolumeAndEffect<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME, TYPE_EFFECT>(*data_in, volume[i], &raw_effect_data);
				}
				data_in++;
				break;
			case TYPE_MIX_STEREO_ONLY_SAVE:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ = MixVolumeAndEffect<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME, TYPE_EFFECT>(*data_in++, volume[i], &raw_effect_data);
				}
				break;
			default:
				LOG_ALWAYS_FATAL("invalid mixtype %d", TYPE_MIX);
				break;
			}
			raw_effect_data /= CHANNEL_COUNT;
			*effect_data++ += MixVolume<TYPE_EFFECT, TYPE_EFFECT, TYPE_EFFECT_VOLUME>(raw_effect_data, effect_volume);
		} while (--frame_count);
	} else {
		do {
			switch (TYPE_MIX) {
			case TYPE_MIX_STEREO:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ += MixVolume<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME>(*data_in++, volume[i]);
				}
				break;
			case TYPE_MIX_MONO:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ += MixVolume<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME>(*data_in, volume[i]);
				}
				data_in++;
				break;
			case TYPE_MIX_STEREO_ONLY_SAVE:
				for (int i = 0; i < CHANNEL_COUNT; ++i) {
					*out_data++ = MixVolume<TYPE_OUTPUT, TYPE_INPUT, TYPE_VOLUME>(*data_in++, volume[i]);
				}
				break;
			default:
				LOG_ALWAYS_FATAL("invalid mixtype %d", TYPE_MIX);
				break;
			}
		} while (--frame_count);
	}
}

};

#endif /* AMEBA_AUAMEBA_FWK_MEDIA_AUDIO_AUDIO_LITE_AUDIO_STREAM_SERVICES_RAW_MIXER_UTIL_H */
