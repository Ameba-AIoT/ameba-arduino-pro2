#include "mel_spectrogram.h"

extern unsigned char *rtw_malloc(unsigned int sz);
extern void *rtw_mfree(unsigned char *pbuf, unsigned int sz);

static void *arm_dsp_malloc(size_t size)
{
	void *p = rtw_malloc(size);
	if (p == NULL) {
		return NULL;
	}
	memset(p, 0, size);
	return p;
}

static void arm_dsp_free(void *p)
{
	if (p != NULL) {
		rtw_mfree(p, 0);
	}
}

mel_spectrogram_t *mel_spec_create(int num_fbank, int frame_len)
{
	mel_spectrogram_t *mel_spec;
	mel_spec = arm_dsp_malloc(sizeof(mel_spectrogram_t));

	mel_spec->num_fbank = num_fbank;
	mel_spec->frame_len = frame_len;

	// Round-up to nearest power of 2.
	mel_spec->fft_length = (int)powf(2, ceilf((logf(frame_len) / logf(2))));

	mel_spec->frame = arm_dsp_malloc(sizeof(float) * mel_spec->fft_length);
	mel_spec->buffer = arm_dsp_malloc(sizeof(float) * mel_spec->fft_length);
	mel_spec->mel_energies = arm_dsp_malloc(sizeof(float) * mel_spec->num_fbank);

	//create window function, hanning
	mel_spec->window_func = arm_dsp_malloc(sizeof(float) * frame_len);
	for (int i = 0; i < frame_len; i++) {
		mel_spec->window_func[i] = 0.5f - 0.5f * cosf((float)M_2PI * ((float)i) / (frame_len));
	}

	//create mel filterbank
	mel_spec->fbank_filter_first = arm_dsp_malloc(sizeof(int32_t) * mel_spec->num_fbank);
	mel_spec->fbank_filter_last = arm_dsp_malloc(sizeof(int32_t) * mel_spec->num_fbank);
	mel_spec->mel_fbank = create_mel_fbank(mel_spec);

	//initialize FFT
	mel_spec->rfft = arm_dsp_malloc(sizeof(arm_rfft_fast_instance_f32));
	arm_rfft_fast_init_f32(mel_spec->rfft, mel_spec->fft_length);

	return mel_spec;
}

float **create_mel_fbank(mel_spectrogram_t *mel_spec)
{
	int32_t bin, i;
	int32_t num_fft_bins = mel_spec->fft_length / 2;
	float fft_bin_width = ((float)SAMP_FREQ) / mel_spec->fft_length;
	float mel_low_freq = MelScale(MEL_LOW_FREQ);
	float mel_high_freq = MelScale(MEL_HIGH_FREQ);
	float mel_freq_delta = (mel_high_freq - mel_low_freq) / (mel_spec->num_fbank + 1);
	float *this_bin = arm_dsp_malloc(sizeof(float) * num_fft_bins);
	float **mel_fbank =  arm_dsp_malloc(sizeof(float *) * mel_spec->num_fbank);

	for (bin = 0; bin < mel_spec->num_fbank ; bin++) {
		float left_mel = mel_low_freq + bin * mel_freq_delta;
		float center_mel = mel_low_freq + (bin + 1) * mel_freq_delta;
		float right_mel = mel_low_freq + (bin + 2) * mel_freq_delta;
		int32_t first_index = -1, last_index = -1;
		for (i = 0; i < num_fft_bins; i++) {
			float freq = (fft_bin_width * i);  // center freq of this fft bin.
			float mel = MelScale(freq);
			this_bin[i] = 0.0;
			if (mel > left_mel && mel < right_mel) {
				float weight;
				if (mel <= center_mel) {
					weight = (mel - left_mel) / (center_mel - left_mel);
				} else {
					weight = (right_mel - mel) / (right_mel - center_mel);
				}
				this_bin[i] = weight;
				if (first_index == -1) {
					first_index = i;
				}

				last_index = i;
			}
		}
		mel_spec->fbank_filter_first[bin] = first_index;
		mel_spec->fbank_filter_last[bin] = last_index;
		mel_fbank[bin] = arm_dsp_malloc(sizeof(float) * ((size_t)last_index - first_index + 1));

		int32_t j = 0;
		//copy the part we care about
		for (i = first_index; i <= last_index; i++) {
			mel_fbank[bin][j++] = this_bin[i];
		}
	}

	arm_dsp_free(this_bin);
	return mel_fbank;
}

void mel_spec_delete(mel_spectrogram_t *mel_spec)
{
	arm_dsp_free(mel_spec->frame);
	arm_dsp_free(mel_spec->buffer);
	arm_dsp_free(mel_spec->mel_energies);
	arm_dsp_free(mel_spec->window_func);
	arm_dsp_free(mel_spec->fbank_filter_first);
	arm_dsp_free(mel_spec->fbank_filter_last);

	for (int i = 0; i < mel_spec->num_fbank ; i++) {
		arm_dsp_free(mel_spec->mel_fbank[i]);
	}

	arm_dsp_free(mel_spec->mel_fbank);
	arm_dsp_free(mel_spec->rfft);
	arm_dsp_free(mel_spec);
}

void mel_compute(mel_spectrogram_t *mel_spec, const float *audio_data)
{
	int32_t i, j, bin;

	for (i = 0; i < mel_spec->frame_len; i++) {
		mel_spec->frame[i] = (float)audio_data[i];
	}

	//Fill up remaining with zeros
	if (mel_spec->fft_length - mel_spec->frame_len) {
		memset(&mel_spec->frame[mel_spec->frame_len], 0, sizeof(float) * (mel_spec->fft_length - mel_spec->frame_len));
	}

	// apply hann window
#if 0 // pure C
	for (i = 0; i < mel_spec->frame_len; i++) {
		mel_spec->frame[i] *= mel_spec->window_func[i];
	}
#else
	arm_mult_f32(mel_spec->frame, mel_spec->window_func, mel_spec->frame, mel_spec->frame_len);
#endif

	//Compute FFT
	arm_rfft_fast_f32(mel_spec->rfft, mel_spec->frame, mel_spec->buffer, 0);

	//Convert to power spectrum
#if 0 // pure C
	//frame is stored as [real0, realN/2-1, real1, im1, real2, im2, ...]
	int32_t half_dim = mel_spec->fft_length / 2;
	float first_energy = mel_spec->buffer[0] * mel_spec->buffer[0];
	float last_energy = mel_spec->buffer[1] * mel_spec->buffer[1];  // handle this special case
	for (i = 1; i < half_dim; i++) {
		float real = mel_spec->buffer[i * 2];
		float im = mel_spec->buffer[i * 2 + 1];
		mel_spec->buffer[i] = sqrtf(real * real + im * im);
	}
	mel_spec->buffer[0] = first_energy;
	mel_spec->buffer[half_dim] = last_energy;
#else
	arm_cmplx_mag_f32(mel_spec->buffer, mel_spec->buffer, mel_spec->fft_length);
#endif

	//Apply mel filterbanks
	for (bin = 0; bin < mel_spec->num_fbank ; bin++) {
		j = 0;
		float mel_energy = 0.001;
		int32_t first_index = mel_spec->fbank_filter_first[bin];
		int32_t last_index = mel_spec->fbank_filter_last[bin];
		for (i = first_index; i <= last_index; i++) {
			float tmp = mel_spec->mel_fbank[bin][j++];
			mel_energy += mel_spec->buffer[i] * tmp;
		}
		mel_spec->mel_energies[bin] = mel_energy;
	}

	//Take log
	for (bin = 0; bin < mel_spec->num_fbank; bin++) {
		mel_spec->mel_energies[bin] = logf(mel_spec->mel_energies[bin]);
		//printf("%f\r\n", bin, mel_spec->mel_energies[bin]);
	}
}
