/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#if defined(ARDUINO) && !defined(ARDUINO_AMBPRO2)
#define ARDUINO_EXCLUDE_CODE
#endif

#ifndef ARDUINO_EXCLUDE_CODE

#include "Arduino.h"
#include "audio_provider.h"
#include "micro_features_micro_model_settings.h"

#include "audio_api.h"

#define DEFAULT_BUFFER_SIZE 512

#define AD_PAGE_SIZE 512 //64*N bytes 
#define TX_AD_PAGE_SIZE AD_PAGE_SIZE
#define RX_AD_PAGE_SIZE AD_PAGE_SIZE
#define DMA_AD_PAGE_NUM AUDIO_PNUM_4 //4

static audio_t audio_obj;
static uint8_t ad_dma_txdata[TX_AD_PAGE_SIZE * DMA_AD_PAGE_NUM]__attribute__((aligned(0x20)));
static uint8_t ad_dma_rxdata[RX_AD_PAGE_SIZE * DMA_AD_PAGE_NUM]__attribute__((aligned(0x20)));

namespace {
    bool g_is_audio_initialized = false;
    // An internal buffer able to fit 16x our sample size
    constexpr int kAudioCaptureBufferSize = DEFAULT_BUFFER_SIZE * 16;
    int16_t g_audio_capture_buffer[kAudioCaptureBufferSize];
    // A buffer that holds our output
    int16_t g_audio_output_buffer[kMaxAudioSampleSize];
    // Mark as volatile so we can check in a while loop to see if
    // any samples have arrived yet.
    volatile int32_t g_latest_audio_timestamp = 0;
}    // namespace

#if 0
void CaptureSamples()
{
    // This is how many bytes of new data we have each time this is called
    const int number_of_samples = DEFAULT_BUFFER_SIZE;
    // Calculate what timestamp the last audio sample represents
    const int32_t time_in_ms = g_latest_audio_timestamp + (number_of_samples / (kAudioSampleFrequency / 1000));
    // Determine the index, in the history of all samples, of the last sample
    const int32_t start_sample_offset = g_latest_audio_timestamp * (kAudioSampleFrequency / 1000);
    // Determine the index of this sample in our ring buffer
    const int capture_index = start_sample_offset % kAudioCaptureBufferSize;
    // Read the data to the correct place in our buffer
    Codec.readDataPage((g_audio_capture_buffer + capture_index), DEFAULT_BUFFER_SIZE);
    // This is how we let the outside world know that new audio data has arrived.
    g_latest_audio_timestamp = time_in_ms;
}
#endif

void audio_tx_irq(uint32_t arg, uint8_t *pbuf)
{
	audio_t *obj = (audio_t *)arg;

	if (audio_get_tx_error_cnt(obj) != 0x00) {
		dbg_printf("tx page error !!! \r\n");
	}

}

void audio_rx_irq(uint32_t arg, uint8_t *pbuf)
{
    // This is how many bytes of new data we have each time this is called
    const int number_of_samples = DEFAULT_BUFFER_SIZE;
    // Calculate what timestamp the last audio sample represents
    const int32_t time_in_ms = g_latest_audio_timestamp + (number_of_samples / (kAudioSampleFrequency / 1000));
    // Determine the index, in the history of all samples, of the last sample
    const int32_t start_sample_offset = g_latest_audio_timestamp * (kAudioSampleFrequency / 1000);
    // Determine the index of this sample in our ring buffer
    const int capture_index = start_sample_offset % kAudioCaptureBufferSize;
    // Read the data to the correct place in our buffer

	audio_t *obj = (audio_t *)arg;
	uint8_t *ptx_addre;
	uint32_t j;

	if (audio_get_rx_error_cnt(obj) != 0x00) {
		// dbg_printf("rx page error !!! \r\n");
	}

	ptx_addre = audio_get_tx_page_adr(obj);

#if 0
    memcpy((void *)ptx_addre, (void *)pbuf, TX_AD_PAGE_SIZE);
#else
    memcpy((void *)ptx_addre, (g_audio_capture_buffer + capture_index), DEFAULT_BUFFER_SIZE);
#endif

    audio_set_tx_page(obj, ptx_addre);

	audio_set_rx_page(obj); // submit a new page for receive

    g_latest_audio_timestamp = time_in_ms;
}


TfLiteStatus InitAudioRecording(tflite::ErrorReporter* error_reporter)
{


#if 1

	uint32_t i;
	uint8_t *ptx_buf;
	printf("Start audio AMic\r\n");

	//Audio Init
	audio_init(&audio_obj, OUTPUT_SINGLE_EDNED, MIC_SINGLE_EDNED, AUDIO_CODEC_2p8V);

	audio_set_param_adv(&audio_obj, ASR_16KHZ, WL_16BIT, A_MONO, A_MONO);

	audio_set_dma_buffer(&audio_obj, ad_dma_txdata, ad_dma_rxdata, AD_PAGE_SIZE, DMA_AD_PAGE_NUM);

	//Init RX dma
	audio_rx_irq_handler(&audio_obj, (audio_irq_handler)audio_rx_irq, (uint32_t *)&audio_obj);

	//Init TX dma
	//audio_tx_irq_handler(&audio_obj, (audio_irq_handler)audio_tx_irq, (uint32_t *)&audio_obj);

	/* Use (DMA page count -1) because occur RX interrupt in first */
	for (i = 0; i < (DMA_AD_PAGE_NUM - 1); i++) {
		ptx_buf = audio_get_tx_page_adr(&audio_obj);
		if (ptx_buf) {
			audio_set_tx_page(&audio_obj, ptx_buf);
		}
		audio_set_rx_page(&audio_obj);
	}

	audio_mic_analog_gain(&audio_obj, ENABLE, MIC_20DB);

	audio_trx_start(&audio_obj);

#endif

    // Block until we have our first audio sample
    while (!g_latest_audio_timestamp) {
        delay(1);
    }

    return kTfLiteOk;
}

TfLiteStatus GetAudioSamples(tflite::ErrorReporter* error_reporter,
                             int start_ms, int duration_ms,
                             int* audio_samples_size, int16_t** audio_samples)
{
    // Set everything up to start receiving audio
    if (!g_is_audio_initialized) {
        TfLiteStatus init_status = InitAudioRecording(error_reporter);
        if (init_status != kTfLiteOk) {
            return init_status;
        }
        g_is_audio_initialized = true;
    }
    // This next part should only be called when the main thread notices that the
    // latest audio sample data timestamp has changed, so that there's new data
    // in the capture ring buffer. The ring buffer will eventually wrap around and
    // overwrite the data, but the assumption is that the main thread is checking
    // often enough and the buffer is large enough that this call will be made
    // before that happens.

    // Determine the index, in the history of all samples, of the first
    // sample we want
    const int start_offset = start_ms * (kAudioSampleFrequency / 1000);
    // Determine how many samples we want in total
    const int duration_sample_count =
        duration_ms * (kAudioSampleFrequency / 1000);
    for (int i = 0; i < duration_sample_count; ++i) {
        // For each sample, transform its index in the history of all samples into
        // its index in g_audio_capture_buffer
        const int capture_index = (start_offset + i) % kAudioCaptureBufferSize;
        // Write the sample to the output buffer
        g_audio_output_buffer[i] = g_audio_capture_buffer[capture_index];
    }

    // Set pointers to provide access to the audio
    *audio_samples_size = kMaxAudioSampleSize;
    *audio_samples = g_audio_output_buffer;

    return kTfLiteOk;
}

int32_t LatestAudioTimestamp()
{
    return g_latest_audio_timestamp;
}

#endif    // ARDUINO_EXCLUDE_CODE
