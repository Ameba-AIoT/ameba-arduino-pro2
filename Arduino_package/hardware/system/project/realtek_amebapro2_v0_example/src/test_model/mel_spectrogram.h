#ifndef __MEL_SPECTROGRAM__
#define __MEL_SPECTROGRAM__
#include "arm_math.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SAMP_FREQ       16000
#define MEL_FILTER_BIN  64
#define WINDOW_SIZE     400
#define HOP_SIZE        160
#define MEL_LOW_FREQ    125
#define MEL_HIGH_FREQ   7500
#define M_2PI           6.283185307179586476925286766559005

typedef struct _mel_spectrogram {
	int num_fbank;
	int frame_len;
	int fft_length;
	float *frame;
	float *buffer;
	float *mel_energies;
	float *window_func;
	int32_t *fbank_filter_first;
	int32_t *fbank_filter_last;
	float **mel_fbank;
	arm_rfft_fast_instance_f32 *rfft;
} mel_spectrogram_t;

static inline float InverseMelScale(float mel_freq)
{
	return 700.0f * (expf(mel_freq / 1127.0f) - 1.0f);
}

static inline float MelScale(float freq)
{
	return 1127.0f * logf(1.0f + freq / 700.0f);
}

float **create_mel_fbank(mel_spectrogram_t *mel_spec);
mel_spectrogram_t *mel_spec_create(int num_fbank, int frame_len);
void mel_spec_delete(mel_spectrogram_t *mel_spec);
void mel_compute(mel_spectrogram_t *mel_spec, const float *audio_data);

#ifdef __cplusplus
}
#endif

#endif
