/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include "mmf2_module.h"
#include "i2s_api.h"
#include "module_i2s.h"
#include "avcodec.h"
//------------------------------------------------------------------------------

#define TX_PAGE_SIZE    I2S_DMA_PAGE_SIZE //64*N bytes, max: 4095. 128, 4032
#define TX_PAGE_NUM     I2S_DMA_PAGE_NUM
#define RX_PAGE_SIZE    I2S_DMA_PAGE_SIZE //64*N bytes, max: 4095. 128, 4032
#define RX_PAGE_NUM     I2S_DMA_PAGE_NUM

#if IS_CUT_TEST(CONFIG_CHIP_VER)
#define I2S_SCLK_PIN    PE_0
#define I2S_WS_PIN      PE_3
#define I2S_TX_PIN      PE_1
#define I2S_RX_PIN      PE_4
#define I2S_MCK_PIN     PE_2 // or NC
#define I2S_TX1_PIN     NC
#define I2S_TX2_PIN     NC
#else
//Group pin 0
#define I2S_SCLK_PIN0   PD_14
#define I2S_WS_PIN0     PD_17
#define I2S_TX_PIN0     PD_15
#define I2S_RX_PIN0     PD_18
#define I2S_MCK_PIN0    PD_16 // or NC
//Group pin 1
#define I2S_SCLK_PIN1   PF_13
#define I2S_WS_PIN1     PF_15
#define I2S_TX_PIN1     PF_14
#define I2S_RX_PIN1     PF_12
#define I2S_MCK_PIN1    PF_11 // or NC
#endif

//Group pin 0
static uint8_t dma_txdata0[TX_PAGE_SIZE * TX_PAGE_NUM]__attribute__((aligned(0x20)));
static uint8_t dma_rxdata0[RX_PAGE_SIZE * RX_PAGE_NUM]__attribute__((aligned(0x20)));
//Group pin 1
static uint8_t dma_txdata1[TX_PAGE_SIZE * TX_PAGE_NUM]__attribute__((aligned(0x20)));
static uint8_t dma_rxdata1[RX_PAGE_SIZE * RX_PAGE_NUM]__attribute__((aligned(0x20)));

#define AUDIO_TX_I2S_QUEUE_LENGTH (20)
#define AUDIO_RX_I2S_QUEUE_LENGTH (20)

static uint32_t byteSwap32(uint32_t num)
{
	return ((num >> 24) & 0x000000FF) | ((num >> 8) & 0x0000FF00) | ((num << 8) & 0x00FF0000) | ((num << 24) & 0xFF000000);
}

static uint16_t byteSwap16(uint16_t num)
{
	return ((num >> 8) & 0x00FF) | ((num << 8) & 0xFF00);
}

static uint32_t byteCopy32(uint32_t num)
{
	return num;
}

static uint16_t byteCopy16(uint16_t num)
{
	return num;
}

static int i2s_samplerate2index(int samplerate)
{
	switch (samplerate) {
	case 8000:
		return SR_8KHZ;
	case 16000:
		return SR_16KHZ;
	case 32000:
		return SR_32KHZ;
	case 44100:
		return SR_44p1KHZ;
	case 48000:
		return SR_48KHZ;
	case 88200:
		return SR_88p2KHZ;
	case 96000:
		return SR_96KHZ;
	default:
		printf("wrong i2s samplerate %d for audio i2s set to default value SR_16KHZ\n\r", samplerate);
		return SR_16KHZ;
	}
}

static int i2s_index2samplerate(int index)
{
	switch (index) {
	case SR_8KHZ:
		return 8000;
	case SR_16KHZ:
		return 16000;
	case SR_32KHZ:
		return 32000;
	case SR_44p1KHZ:
		return 44100;
	case SR_48KHZ:
		return 48000;
	case SR_88p2KHZ:
		return 88200;
	case SR_96KHZ:
		return 96000;
	default:
		printf("wrong i2s index index %d set to default value 16000\n\r", index);
		return 16000;
	}
}

static int i2s_wordlength2index(int wordlength)
{
	switch (wordlength) {
	case 16:
		return WL_16b;
	case 24:
		return WL_24b;
	case 32:
		return WL_32b;
	default:
		printf("wrong wordlength %d for audio i2s set to default value WL_16b\n\r", wordlength);
		return WL_16b;
	}
}

static int i2s_index2wordlength(int index)
{
	switch (index) {
	case WL_16b:
		return 16;
	case WL_24b:
		return 24;
	case WL_32b:
		return 32;
	default:
		printf("wrong index %d for audio i2s set to default value 16\n\r", index);
		return 16;
	}
}

static void i2s_tx_complete(uint32_t arg, uint8_t *pbuf)
{
	i2s_ctx_t *ctx = (i2s_ctx_t *)arg;
	i2s_t *obj = (i2s_t *)ctx->i2s_obj;
	uint8_t *ptx_buf;
	ptx_buf = (uint8_t *)i2s_get_tx_page(obj);
	if (xQueueReceiveFromISR(ctx->i2s_tx_cache.queue, (void *)(ctx->i2s_tx_cache.txbuf), NULL) != pdPASS) {
		memset(ptx_buf, 0, I2S_DMA_PAGE_SIZE);
	} else {
		memcpy(ptx_buf, ctx->i2s_tx_cache.txbuf, I2S_DMA_PAGE_SIZE);
	}
	i2s_send_page(obj, (uint32_t *)ptx_buf);
}

static void i2s_rx_complete(uint32_t arg, uint8_t *pbuf)
{
	i2s_ctx_t *ctx = (i2s_ctx_t *)arg;
	i2s_t *obj = (i2s_t *)ctx->i2s_obj;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if (ctx->i2s_direction != I2S_TX_ONLY) { //since there is no tx only mode in low layer
		uint32_t rx_ts = mm_read_mediatime_ms_fromisr();
		// set timestamp to the first sample
		int frame_bytes = ((ctx->i2s_word_length + 8) / 16) * 2; //16bits = 2, 24bits = 4, 32bits = 4
		if (ctx->i2s_channel == CH_STEREO) {
			frame_bytes *= 2;
		}
		rx_ts -= 1000 * (I2S_DMA_PAGE_SIZE / frame_bytes) / ctx->sample_rate;
		uint32_t i2s_rx_ts = rx_ts + ctx->i2s_timestamp_offset;

		memcpy((void *)ctx->i2s_rx_cache.rxbuf.data, (void *)pbuf, I2S_DMA_PAGE_SIZE);
		ctx->i2s_rx_cache.rxbuf.hw_timestamp = rx_ts;
		ctx->i2s_rx_cache.rxbuf.timestamp = i2s_rx_ts;
		xQueueSendFromISR(ctx->i2s_rx_cache.queue, &(ctx->i2s_rx_cache.rxbuf), &xHigherPriorityTaskWoken);
	}
	i2s_recv_page(obj);
	if (xHigherPriorityTaskWoken) {
		taskYIELD();
	}
}

typedef struct {
	uint8_t btye0;
	uint8_t btye1;
	uint8_t btye2;
} int24_t;

//little endian system
static void process_16_to_24(int16_t in_buf16, int24_t *out_buf24)
{
	int32_t temp24 = (int32_t)(in_buf16) << 8;
	out_buf24->btye0 = (uint8_t)(temp24 & 0xFF);
	out_buf24->btye1 = (uint8_t)((temp24 >> 8) & 0xFF);
	out_buf24->btye2 = (uint8_t)((temp24 >> 16) & 0xFF);
}

static void process_16_to_32(int16_t in_buf16, int32_t *out_buf32)
{
	*out_buf32 = (int32_t)(in_buf16) << 16;
}

static void process_24h_to_16(uint32_t in_buf32, int16_t *out_buf16)
{
	int32_t temp24 = (uint32_t)((in_buf32) >> 8);
	temp24 = (temp24 << 8) >> 8;
	*out_buf16 = temp24 >> 8;
}

static void process_24h_to_32(uint32_t in_buf32, int32_t *out_buf32)
{
	int32_t temp24 = (uint32_t)((in_buf32) >> 8);
	temp24 = temp24 << 8;
	*out_buf32 = temp24;
}

static void process_32_to_16(int32_t in_buf32, int16_t *out_buf16)
{
	*out_buf16 = (int32_t)(in_buf32) >> 16;
}

static void process_32_to_24(int32_t in_buf32, int24_t *out_buf24)
{
	int32_t temp24 = (int32_t)(in_buf32) >> 8;
	out_buf24->btye0 = (uint8_t)(temp24 & 0xFF);
	out_buf24->btye1 = (uint8_t)((temp24 >> 8) & 0xFF);
	out_buf24->btye2 = (uint8_t)((temp24 >> 16) & 0xFF);
}

static int convert_rx_data(uint8_t *rx_buffer, const uint8_t *i2s_buffer, uint32_t *rx_byte, uint32_t *i2s_byte, i2s_ctx_t *ctx)
{
	if (rx_buffer == NULL) {
		printf("[I2S Tx process] rx buffer is NULL");
		return -1;
	}
	if (i2s_buffer == NULL) {
		printf("[I2S Tx process] i2s buffer is NULL");
		return -1;
	}
	uint32_t in_byte = *i2s_byte;
	uint32_t out_byte = *rx_byte;
	memset(rx_buffer, 0, out_byte);

	int16_t *in_buf16 = (int16_t *) i2s_buffer;
	int32_t *in_buf32 = (int32_t *) i2s_buffer;
	uint8_t *out_buf8 = (uint8_t *) rx_buffer;
	int16_t *out_buf16 = (int16_t *) rx_buffer;
	int32_t *out_buf32 = (int32_t *) rx_buffer;

	uint32_t in_wl = ((ctx->i2s_word_length + 8) / 16) * 2; //16bits = 2, 24bits = 4, 32bits = 4
	uint32_t out_wl = ctx->rx_word_length / 8;

	uint32_t in_idx_start = 0;
	uint32_t out_byte_stride = out_wl;
	uint32_t out_idx_stride = 1;
	uint32_t in_idx_stride = 1;

	if ((ctx->rx_channel == I2S_STEREO_CHANNEL) && (ctx->i2s_channel == CH_MONO)) {
		out_idx_stride = 2;
	} else if ((ctx->rx_channel == I2S_RIGHT_CHANNEL) && (ctx->i2s_channel == CH_STEREO)) {
		in_idx_stride = 2;
		in_idx_start = 1;
	} else if ((ctx->rx_channel == I2S_LEFT_CHANNEL) && (ctx->i2s_channel == CH_STEREO)) {
		in_idx_stride = 2;
	}

	int i, j;
	if (ctx->i2s_word_length == 32 && ctx->rx_word_length == 32) {
		for (i = in_idx_start, j = 0; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			out_buf32[j] = ctx->rxbyteProc32(in_buf32[i]);
			*i2s_byte -= in_wl;
			*rx_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 32 && ctx->rx_word_length == 24) {
		for (i = in_idx_start, j = 0; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			process_32_to_24(ctx->rxbyteProc32(in_buf32[i]), (int24_t *)(&out_buf8[out_byte_stride * j]));
			*i2s_byte -= in_wl;
			*rx_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 32 && ctx->rx_word_length == 16) {
		for (i = in_idx_start, j = 0; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			process_32_to_16(ctx->rxbyteProc32(in_buf32[i]), &out_buf16[j]);
			*i2s_byte -= in_wl;
			*rx_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 24 && ctx->rx_word_length == 32) {
		for (i = in_idx_start, j = 0; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			process_24h_to_32(ctx->rxbyteProc32(in_buf32[i]), &out_buf32[j]);
			*i2s_byte -= in_wl;
			*rx_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 24 && ctx->rx_word_length == 24) {
		for (i = in_idx_start, j = 0; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			uint32_t temp24 = (uint32_t)(ctx->rxbyteProc32(in_buf32[i])) >> 8;
			out_buf8[out_byte_stride * j + 0] = (uint8_t)(temp24 & 0xFF);
			out_buf8[out_byte_stride * j + 1] = (uint8_t)((temp24 >> 8) & 0xFF);
			out_buf8[out_byte_stride * j + 2] = (uint8_t)((temp24 >> 16) & 0xFF);
			*i2s_byte -= in_wl;
			*rx_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 24 && ctx->rx_word_length == 16) {
		for (i = in_idx_start, j = 0; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			process_24h_to_16(ctx->rxbyteProc32(in_buf32[i]), &out_buf16[j]);
			*i2s_byte -= in_wl;
			*rx_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 16 && ctx->rx_word_length == 32) {
		for (i = in_idx_start, j = 0; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			process_16_to_32(ctx->rxbyteProc16(in_buf16[i]), &out_buf32[j]);
			*i2s_byte -= in_wl;
			*rx_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 16 && ctx->rx_word_length == 24) {
		for (i = in_idx_start, j = 0; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			process_16_to_24(ctx->rxbyteProc16(in_buf16[i]), (int24_t *)(&out_buf8[out_byte_stride * j]));
			*i2s_byte -= in_wl;
			*rx_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 16 && ctx->rx_word_length == 16) {
		for (i = in_idx_start, j = 0; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			out_buf16[j] = ctx->rxbyteProc16(in_buf16[i]);
			*i2s_byte -= in_wl;
			*rx_byte -= out_byte_stride * out_idx_stride;
		}
	}
	return 0;
}

static void i2s_rx_handle_thread(void *param)
{
	i2s_ctx_t *ctx = (i2s_ctx_t *)param;
	mm_context_t *mctx = (mm_context_t *)ctx->parent;
	mm_queue_item_t *output_item;

	while (1) {
		vTaskDelay(1);
		if (xQueueReceive(ctx->i2s_rx_cache.queue, &(ctx->i2s_rx_cache.buffer), 40) != pdTRUE) {
			//printf("[I2S RX Handle] Can not get i2s buffer\r\n");
			continue;
		}
		uint32_t i2s_rx_byte = I2S_DMA_PAGE_SIZE;
		while (i2s_rx_byte) {
			if (xQueueReceive(mctx->output_recycle, &output_item, 0xFFFFFFFF) == pdTRUE) {
				uint32_t i2s_start_idx = I2S_DMA_PAGE_SIZE - i2s_rx_byte;
				uint32_t output_buf_size = RX_PAGE_SIZE;
				convert_rx_data((uint8_t *)output_item->data_addr, &(ctx->i2s_rx_cache.buffer.data[i2s_start_idx]), &(output_buf_size), &(i2s_rx_byte), ctx);
				output_item->size = RX_PAGE_SIZE - output_buf_size;
				output_item->timestamp = ctx->i2s_rx_cache.buffer.timestamp;
				output_item->hw_timestamp = ctx->i2s_rx_cache.buffer.hw_timestamp;
				output_item->type = AV_CODEC_ID_PCM_RAW;
				xQueueSend(mctx->output_ready, (void *)&output_item, 0xFFFFFFFF);
			}
		}
	}
	printf("[I2S RX Handle] Task Jump Out!!\r\n");
	vTaskDelete(NULL);
}

static int set_i2s_module_init(void *p)
{
	i2s_ctx_t *ctx = (i2s_ctx_t *)p;
	uint8_t *i2s_tx_buffer = 0;
	uint8_t *i2s_rx_buffer = 0;

	if (!ctx->i2s_inited) {
		ctx->sample_rate = i2s_index2samplerate(ctx->params.sample_rate);
		ctx->i2s_word_length = ctx->params.i2s_word_length;
		ctx->rx_word_length = ctx->params.rx_word_length;
		ctx->tx_word_length = ctx->params.tx_word_length;
		ctx->rx_channel = ctx->params.rx_channel;
		ctx->tx_channel = ctx->params.tx_channel;
		ctx->i2s_direction = ctx->params.i2s_direction;
		ctx->pin_group_num = ctx->params.pin_group_num;
		ctx->i2s_ws_edge = ctx->params.i2s_ws_edge;
		ctx->i2s_data_edge = ctx->params.i2s_data_edge;
		ctx->rxbyteProc32 = ctx->params.rx_byte_swap ? byteSwap32 : byteCopy32;
		ctx->rxbyteProc16 = ctx->params.rx_byte_swap ? byteSwap16 : byteCopy16;
		//I2S with word length only support stereo channel
		if (ctx->i2s_word_length == 24 || ctx->rx_channel == I2S_STEREO_CHANNEL || ctx->tx_channel == I2S_STEREO_CHANNEL) {
			ctx->i2s_channel = CH_STEREO;
		} else {
			ctx->i2s_channel = CH_MONO;
		}
		if (ctx->pin_group_num == 0) {
			// I2S init
			i2s_init(ctx->i2s_obj, I2S_SCLK_PIN0, I2S_WS_PIN0, I2S_TX_PIN0, I2S_RX_PIN0, I2S_MCK_PIN0);
			i2s_tx_buffer = dma_txdata0;
			i2s_rx_buffer = dma_rxdata0;
		} else if (ctx->pin_group_num == 1) {
			i2s_init(ctx->i2s_obj, I2S_SCLK_PIN1, I2S_WS_PIN1, I2S_TX_PIN1, I2S_RX_PIN1, I2S_MCK_PIN1);
			i2s_tx_buffer = dma_txdata1;
			i2s_rx_buffer = dma_rxdata1;
		} else {
			printf("[I2S Ctrl Err]unknown pin group num\n\r");
			return -1;
		}
		if (ctx->i2s_tx_cache.queue) {
			xQueueReset(ctx->i2s_tx_cache.queue);
		}
		if (ctx->i2s_rx_cache.queue) {
			xQueueReset(ctx->i2s_rx_cache.queue);
		}

		if (ctx->i2s_obj->i2s_initialized) {
			i2s_set_dma_buffer(ctx->i2s_obj, (char *)i2s_tx_buffer, (char *)i2s_rx_buffer, I2S_DMA_PAGE_NUM, I2S_DMA_PAGE_SIZE);
			// Init i2s TX,RX dma
			i2s_rx_irq_handler(ctx->i2s_obj, (i2s_irq_handler)i2s_rx_complete, (uint32_t)ctx);
			i2s_tx_irq_handler(ctx->i2s_obj, (i2s_irq_handler)i2s_tx_complete, (uint32_t)ctx);
			//if (ctx->tx_channel == I2S_LEFT_CHANNEL) {
			//i2s_set_ws_swap(ctx->i2s_obj, 0);
			//} else if (ctx->tx_channel == I2S_RIGHT_CHANNEL) {
			//i2s_set_ws_swap(ctx->i2s_obj, 1);
			//}
			i2s_set_format(ctx->i2s_obj, ctx->params.i2s_format);
			i2s_set_master(ctx->i2s_obj, ctx->params.i2s_role);
			//i2s_set_byte_swap(ctx->i2s_obj, 1);
			// Since the sck is inverted, we need to inverted the trigger for the setting
			if (ctx->i2s_ws_edge == WS_NEGATIVE_EDGE) {
				i2s_set_sck_inv(ctx->i2s_obj, 0);
				i2s_set_data_start_edge(ctx->i2s_obj, ctx->i2s_data_edge);
			} else {
				i2s_set_sck_inv(ctx->i2s_obj, 1);
				i2s_set_data_start_edge(ctx->i2s_obj, !ctx->i2s_data_edge);
			}
			i2s_set_param(ctx->i2s_obj, ctx->i2s_channel, i2s_samplerate2index(ctx->sample_rate), i2s_wordlength2index(ctx->i2s_word_length));

			// Since the TX only support loop back mode in driver, blocking the RX in TX RX mode to implement TX only mode
			if (ctx->i2s_direction == I2S_RX_ONLY) {
				i2s_set_direction(ctx->i2s_obj, I2S_DIR_RX);
			} else {
				i2s_set_direction(ctx->i2s_obj, I2S_DIR_TXRX);
			}
			for (int j = 0; j < I2S_DMA_PAGE_NUM; j++) {
				i2s_recv_page(ctx->i2s_obj); //all mode need this process
				if (ctx->i2s_direction == I2S_TX_ONLY || ctx->i2s_direction == I2S_TRX_BOTH) {
					uint8_t *ptx_buf_reset = (uint8_t *)i2s_get_tx_page(ctx->i2s_obj);
					if (ptx_buf_reset) {
						i2s_send_page(ctx->i2s_obj, (uint32_t *)ptx_buf_reset);
					}
				}
			}
			i2s_enable(ctx->i2s_obj);
		} else {
			return -1;
		}
		ctx->i2s_inited = 1;
	}
	return 0;
}

static int set_i2s_module_deinit(void *p)
{
	i2s_ctx_t *ctx = (i2s_ctx_t *)p;

	if (ctx->i2s_inited == 1) {
		i2s_deinit(ctx->i2s_obj);
		ctx->i2s_inited = 0;
		return 0;
	}
	return -1;
}

int i2s_control(void *p, int cmd, int arg)
{
	i2s_ctx_t  *ctx = (i2s_ctx_t *)p;

	switch (cmd) {
	case CMD_I2S_SET_PARAMS:
		memcpy(&ctx->params, (void *)arg, sizeof(i2s_params_t));
		break;
	case CMD_I2S_GET_PARAMS:
		memcpy((void *)arg, &ctx->params, sizeof(i2s_params_t));
		break;
	case CMD_I2S_SET_SAMPLERATE:
		ctx->params.sample_rate = arg;
		break;
	case CMD_I2S_SET_TRX:
		if (arg == 0) {
			i2s_disable(ctx->i2s_obj);
		} else {
			ctx->i2s_direction = I2S_TRX_BOTH;
			ctx->params.i2s_direction = I2S_TRX_BOTH;
			i2s_set_direction(ctx->i2s_obj, I2S_DIR_TXRX);
		}
		break;
	case CMD_I2S_SET_RX:
		if (arg == 0) {
			if (ctx->i2s_direction == I2S_RX_ONLY) {
				i2s_disable(ctx->i2s_obj);
			} else {
				ctx->i2s_direction = I2S_TX_ONLY;
				ctx->params.i2s_direction = I2S_TX_ONLY;
				i2s_set_direction(ctx->i2s_obj, I2S_DIR_TXRX);
			}
		} else {
			if (ctx->i2s_direction == I2S_TX_ONLY) {
				ctx->i2s_direction = I2S_TRX_BOTH;
				ctx->params.i2s_direction = I2S_TRX_BOTH;
				i2s_set_direction(ctx->i2s_obj, I2S_DIR_TXRX);
			}
		}
		break;
	case CMD_I2S_SET_TX:
		if (arg == 0) {
			if (ctx->i2s_direction == I2S_TX_ONLY) {
				i2s_disable(ctx->i2s_obj);
			} else {
				ctx->i2s_direction = I2S_RX_ONLY;
				ctx->params.i2s_direction = I2S_RX_ONLY;
				i2s_set_direction(ctx->i2s_obj, I2S_DIR_RX);
			}
		} else {
			if (ctx->i2s_direction == I2S_RX_ONLY) {
				ctx->i2s_direction = I2S_TRX_BOTH;
				ctx->params.i2s_direction = I2S_TRX_BOTH;
				i2s_set_direction(ctx->i2s_obj, I2S_DIR_TXRX);
			}
		}
		break;
	case CMD_I2S_SET_TIMESTAMP_OFFSET:
		ctx->i2s_timestamp_offset = arg;
		break;
	case CMD_I2S_SET_FORMAT:
		ctx->params.i2s_format = arg;
		i2s_set_format(ctx->i2s_obj, ctx->params.i2s_format);
		break;
	case CMD_I2S_SET_ROLE:
		ctx->params.i2s_role = arg;
		i2s_set_master(ctx->i2s_obj, ctx->params.i2s_role);
		break;
	case CMD_I2S_SET_DATA_EDGE:
		ctx->params.i2s_data_edge = arg;
		ctx->i2s_data_edge = ctx->params.i2s_data_edge;
		if (ctx->i2s_ws_edge == WS_NEGATIVE_EDGE) {
			i2s_set_data_start_edge(ctx->i2s_obj, ctx->i2s_data_edge);
		} else {
			i2s_set_data_start_edge(ctx->i2s_obj, !ctx->i2s_data_edge);
		}
		break;
	case CMD_I2S_SET_WS_EDGE:
		ctx->params.i2s_ws_edge = arg;
		ctx->i2s_ws_edge = ctx->params.i2s_ws_edge;
		if (ctx->i2s_ws_edge == WS_NEGATIVE_EDGE) {
			i2s_set_sck_inv(ctx->i2s_obj, 0);
			i2s_set_data_start_edge(ctx->i2s_obj, ctx->i2s_data_edge);
		} else {
			i2s_set_sck_inv(ctx->i2s_obj, 1);
			i2s_set_data_start_edge(ctx->i2s_obj, !ctx->i2s_data_edge);
		}
		break;
	case CMD_I2S_FORCE_DEINIT:
		set_i2s_module_deinit(ctx);
		break;
	case CMD_I2S_SET_RESET:
		set_i2s_module_deinit(ctx);
		if (set_i2s_module_init(ctx)) {
			goto i2s_control_fail;
		}
		break;
	case CMD_I2S_APPLY:
		if (set_i2s_module_init(ctx)) {
			goto i2s_control_fail;
		}
		break;
	}
	return 0;

i2s_control_fail:
	mm_printf("i2s_control fail\n\r");
	return -1;
}

//output: remain btye
static int convert_tx_data(const uint8_t *tx_buffer, uint8_t *i2s_buffer, uint32_t *tx_byte, uint32_t *i2s_byte, i2s_ctx_t *ctx)
{
	if (tx_buffer == NULL) {
		printf("[I2S Tx process] tx buffer is NULL");
		return -1;
	}
	if (i2s_buffer == NULL) {
		printf("[I2S Tx process] i2s buffer is NULL");
		return -1;
	}
	uint32_t in_byte = *tx_byte;
	uint32_t out_byte = *i2s_byte;
	memset(i2s_buffer, 0, out_byte);

	uint8_t *in_buf8 = (uint8_t *) tx_buffer;
	int16_t *in_buf16 = (int16_t *) tx_buffer;
	int32_t *in_buf32 = (int32_t *) tx_buffer;
	uint8_t *out_buf8 = (uint8_t *) i2s_buffer;
	int16_t *out_buf16 = (int16_t *) i2s_buffer;
	int32_t *out_buf32 = (int32_t *) i2s_buffer;

	uint32_t in_wl = ctx->tx_word_length / 8;
	uint32_t out_wl = ctx->i2s_word_length / 8;

	uint32_t in_idx_stride = 1;
	uint32_t out_idx_start = 0;
	uint32_t out_byte_stride = 4;
	uint32_t out_idx_stride = 1;

	if (out_wl == 2) {
		out_byte_stride = 2;
	}
	if ((ctx->tx_channel == I2S_STEREO_CHANNEL) && (ctx->i2s_channel == CH_MONO)) {
		in_idx_stride = 2;
	} else if ((ctx->tx_channel == I2S_RIGHT_CHANNEL) && (ctx->i2s_channel == CH_STEREO)) {
		out_idx_start = 1;
		out_idx_stride = 2;
	} else if ((ctx->tx_channel == I2S_LEFT_CHANNEL) && (ctx->i2s_channel == CH_STEREO)) {
		out_idx_stride = 2;
	}

	int i, j;
	if (ctx->tx_word_length == 32 && ctx->i2s_word_length == 32) {
		for (i = 0, j = out_idx_start; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			out_buf32[j] = in_buf32[i];
			*tx_byte -= in_wl;
			*i2s_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->tx_word_length == 32 && ctx->i2s_word_length == 24) {
		for (i = 0, j = out_idx_start; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			process_32_to_24(in_buf32[i], (int24_t *)(&out_buf8[out_byte_stride * j + 1]));
			*tx_byte -= in_wl;
			*i2s_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->tx_word_length == 32 && ctx->i2s_word_length == 16) {
		for (i = 0, j = out_idx_start; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			process_32_to_16(in_buf32[i], &out_buf16[j]);
			*tx_byte -= in_wl;
			*i2s_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 24 && ctx->rx_word_length == 32) {
		for (i = 0, j = out_idx_start; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			uint32_t temp24 = (uint32_t)in_buf8[3 * i + 0] << 8 | (uint32_t)in_buf8[3 * i + 1] << 16 | (uint32_t)in_buf8[3 * i + 2] << 24;
			process_24h_to_32(temp24, &out_buf32[j]);
			*tx_byte -= in_wl;
			*i2s_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 24 && ctx->rx_word_length == 24) {
		for (i = 0, j = out_idx_start; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			uint32_t temp24 = (uint32_t)in_buf8[3 * i + 0] << 8 | (uint32_t)in_buf8[3 * i + 1] << 16 | (uint32_t)in_buf8[3 * i + 2] << 24;
			out_buf32[j] = temp24;
			*tx_byte -= in_wl;
			*i2s_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 24 && ctx->rx_word_length == 16) {
		for (i = 0, j = out_idx_start; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			uint32_t temp24 = (uint32_t)in_buf8[3 * i + 0] << 8 | (uint32_t)in_buf8[3 * i + 1] << 16 | (uint32_t)in_buf8[3 * i + 2] << 24;
			process_24h_to_16(temp24, &out_buf16[j]);
			*tx_byte -= in_wl;
			*i2s_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 16 && ctx->rx_word_length == 32) {
		for (i = 0, j = out_idx_start; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			process_16_to_32(in_buf16[i], &out_buf32[j]);
			*tx_byte -= in_wl;
			*i2s_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 16 && ctx->rx_word_length == 24) {
		for (i = 0, j = out_idx_start; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			process_16_to_24(byteSwap16(in_buf16[i]), (int24_t *)(&out_buf8[out_byte_stride * j + 1]));
			*tx_byte -= in_wl;
			*i2s_byte -= out_byte_stride * out_idx_stride;
		}
	} else if (ctx->i2s_word_length == 16 && ctx->rx_word_length == 16) {
		for (i = 0, j = out_idx_start; i < (in_byte / in_wl) && j < (out_byte / out_byte_stride); i += in_idx_stride, j += out_idx_stride) {
			out_buf16[j] = in_buf16[i];
			*tx_byte -= in_wl;
			*i2s_byte -= out_byte_stride * out_idx_stride;
		}
	}
	return 0;
}

int i2s_handle(void *p, void *input, void *output)
{
	i2s_ctx_t *ctx = (i2s_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;

	uint8_t *input_data = (uint8_t *)input_item->data_addr;

	(void)output;

	i2s_tx_cache_t *cache = &(ctx->i2s_tx_cache);
	uint32_t input_size = input_item->size;
	uint32_t output_size = I2S_DMA_PAGE_SIZE - cache->idx;

	for (int i = 0; i < input_item->size;) {
		if (convert_tx_data(input_data, &(cache->buffer[cache->idx]), &input_size, &output_size, ctx)) {
			printf("tx convert fail\r\n");
			break;
		}
		cache->idx += (I2S_DMA_PAGE_SIZE - cache->idx) - output_size;
		i += input_item->size - input_size;
		if (cache->idx == I2S_DMA_PAGE_SIZE) {
			if (xQueueSend(cache->queue, (void *)(cache->buffer), 1000) != pdTRUE) {
				printf("fail to send tx queue\r\n");
			}
			cache->idx = 0;
		}
	}
	return 0;
}

void *i2s_destroy(void *p)
{
	i2s_ctx_t *ctx = (i2s_ctx_t *)p;

	if (ctx) {
		set_i2s_module_deinit(ctx);
		if (ctx->i2s_rx_cache.queue) {
			vQueueDelete(ctx->i2s_rx_cache.queue);
			ctx->i2s_rx_cache.queue = NULL;
		}
		if (ctx->i2s_tx_cache.queue) {
			vQueueDelete(ctx->i2s_tx_cache.queue);
			ctx->i2s_tx_cache.queue = NULL;
		}
		if (ctx->i2s_rx_task) {
			vTaskDelete(ctx->i2s_rx_task);
			ctx->i2s_rx_task = NULL;
		}
		if (ctx->i2s_obj) {
			free(ctx->i2s_obj);
		}
		free(ctx);
		ctx = NULL;
	}
	return NULL;
}

void *i2s_create(void *parent)
{
	i2s_ctx_t *ctx = malloc(sizeof(i2s_ctx_t));
	if (!ctx) {
		printf("[I2S Create Err] i2s contex malloc error\n\r");
		return NULL;
	}
	memset(ctx, 0, sizeof(i2s_ctx_t));
	ctx->parent = parent;
	ctx->i2s_obj = malloc(sizeof(i2s_t));
	if (!ctx->i2s_obj)	{
		goto i2s_create_fail;
	}
	memset(ctx->i2s_obj, 0, sizeof(i2s_t));
	//i2s default setting
	memcpy((void *)&ctx->params, (void *)&default_i2s_params, sizeof(i2s_params_t));
	ctx->i2s_tx_cache.queue = xQueueCreate(AUDIO_TX_I2S_QUEUE_LENGTH, I2S_DMA_PAGE_SIZE);
	if (ctx->i2s_tx_cache.queue == NULL) {
		printf("\r\n[I2S Create Err] pcm tx cache queue: Create Error\n");
		goto i2s_create_fail;
	}
	ctx->i2s_rx_cache.queue = xQueueCreate(AUDIO_RX_I2S_QUEUE_LENGTH, sizeof(i2s_rx_t));
	if (ctx->i2s_rx_cache.queue == NULL) {
		printf("\r\n[I2S Create Err] pcm rx cache queue: Create Error\n");
		goto i2s_create_fail;
	}
	if (xTaskCreate(i2s_rx_handle_thread, ((const char *)"i2s_rx"), 1024, (void *)ctx, tskIDLE_PRIORITY + 5, &ctx->i2s_rx_task) != pdPASS) {
		printf("\r\n[I2S Create Err] i2s_rx_handle_thread: Create Task Error\n");
		goto i2s_create_fail;
	}

	return ctx;

i2s_create_fail:

	i2s_destroy((void *)ctx);
	return NULL;
}

void *i2s_new_item(void *p)
{
	return malloc(I2S_DMA_PAGE_SIZE);
}

void *i2s_del_item(void *p, void *d)
{
	if (d) {
		free(d);
	}
	return NULL;
}

mm_module_t i2s_module = {
	.create = i2s_create,
	.destroy = i2s_destroy,
	.control = i2s_control,
	.handle = i2s_handle,

	.new_item = i2s_new_item,
	.del_item = i2s_del_item,
	.rsz_item = NULL,

	.output_type = MM_TYPE_ADSP | MM_TYPE_ASINK,
	.module_type = MM_TYPE_ASRC | MM_TYPE_ASINK,
	.name = "I2S"
};

i2s_params_t default_i2s_params = {
	.sample_rate        = SR_8KHZ,
	.i2s_word_length    = 16,
	.rx_word_length     = 16,
	.tx_word_length     = 16,
	.i2s_format         = FORMAT_I2S,
	.i2s_role           = I2S_MASTER,
	.i2s_data_edge      = NEGATIVE_EDGE,
	.i2s_ws_edge        = WS_NEGATIVE_EDGE,
	.rx_channel         = I2S_LEFT_CHANNEL,
	.tx_channel         = I2S_LEFT_CHANNEL,
	.i2s_direction      = I2S_TRX_BOTH,
	.rx_byte_swap       = 0,
	.tx_byte_swap       = 0,
	.pin_group_num      = 0,
};