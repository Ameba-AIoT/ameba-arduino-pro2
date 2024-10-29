#ifndef _MODULE_I2S_H
#define _MODULE_I2S_H

#include "mmf2_module.h"
#include "i2s_api.h"

#define I2S_DMA_PAGE_NUM 4
#define I2S_DMA_PAGE_SIZE (640 * 2)	//64*N bytes, max: 4095. 128, 4032

#define CMD_I2S_SET_PARAMS              MM_MODULE_CMD(0x00) // set parameter
#define CMD_I2S_GET_PARAMS              MM_MODULE_CMD(0x01) // get parameter
#define CMD_I2S_SET_SAMPLERATE          MM_MODULE_CMD(0x02)
#define CMD_I2S_SET_TRX                 MM_MODULE_CMD(0x03)
#define CMD_I2S_SET_RX                  MM_MODULE_CMD(0x04)
#define CMD_I2S_SET_TX                  MM_MODULE_CMD(0x05)
#define CMD_I2S_SET_RESET               MM_MODULE_CMD(0x06)
#define CMD_I2S_FORCE_DEINIT            MM_MODULE_CMD(0x07)
#define CMD_I2S_SET_FORMAT              MM_MODULE_CMD(0x08)
#define CMD_I2S_SET_ROLE                MM_MODULE_CMD(0x09)
#define CMD_I2S_SET_DATA_EDGE           MM_MODULE_CMD(0x0A)
#define CMD_I2S_SET_WS_EDGE             MM_MODULE_CMD(0x0B)
#define CMD_I2S_SET_TIMESTAMP_OFFSET    MM_MODULE_CMD(0x0C)
#define CMD_I2S_APPLY                   MM_MODULE_CMD(0x20) // for hardware module


// 24 bits RX
/*
P == padding

I2S bytes normal
addr0                     addr32
N, N-1, ...., 0, P, P, P, P

Inverse bytes
addr0                     addr32
P, P, P, P, 0, ..., N-1, N
*/
typedef struct i2s_tx_cache_s {
	xQueueHandle    queue;
	uint16_t        idx;
	uint8_t         buffer[I2S_DMA_PAGE_SIZE];	// for sw output cache handler
	uint8_t         txbuf[I2S_DMA_PAGE_SIZE];	// for interrupt
} i2s_tx_cache_t;

typedef struct i2s_rx_s {
	uint32_t        timestamp;
	uint32_t        hw_timestamp;
	uint8_t         data[I2S_DMA_PAGE_SIZE];
} i2s_rx_t;

typedef struct i2s_rx_cache_s {
	xQueueHandle    queue;
	uint16_t        idx;
	i2s_rx_t        buffer;
	i2s_rx_t        rxbuf;
} i2s_rx_cache_t;

typedef enum {
	WS_NEGATIVE_EDGE,       // WS (LRCK) triggered in negative edge
	WS_POSITIVE_EDGE,       // WS (LRCK) triggered in positive edge
} i2s_ws_trig_edge;

typedef enum {
	I2S_LEFT_CHANNEL,
	I2S_RIGHT_CHANNEL,
	I2S_STEREO_CHANNEL,
} i2s_channel_type;

typedef enum {
	I2S_RX_ONLY,
	I2S_TX_ONLY,
	I2S_TRX_BOTH,
} i2s_direction_type;

typedef struct i2s_param_s {
	uint32_t                sample_rate;
	uint8_t                 i2s_word_length;
	uint8_t                 rx_word_length;
	uint8_t                 tx_word_length;
	i2s_format              i2s_format;         // define i2s transforming format, FORMAT_I2S, FORMAT_LEFT_JUST, FORMAT_RIGHT_JUST
	i2s_ms_mode             i2s_role;           // define i2s role, I2S_MASTER, I2S_SLAVE
	i2s_ws_trig_edge        i2s_ws_edge;        // define i2s WS trigger edge, WS_NEGATIVE_EDGE, WS_POSITIVE_EDGE
	i2s_edge_sw             i2s_data_edge;      // define i2s data trigger edge, NEGATIVE_EDGE, POSITIVE_EDGE
	uint8_t                 i2s_channel;
	i2s_channel_type        rx_channel;
	i2s_channel_type        tx_channel;
	i2s_direction_type      i2s_direction;
	uint8_t                 rx_byte_swap;
	uint8_t                 tx_byte_swap;
	uint8_t                 pin_group_num;
} i2s_params_t;

typedef struct i2s_ctx_s {
	void                    *parent;
	i2s_t                   *i2s_obj;
	i2s_params_t            params;
	uint8_t                 i2s_inited;
	uint32_t                sample_rate;
	uint8_t                 i2s_word_length;
	uint8_t                 rx_word_length;
	uint8_t                 tx_word_length;
	uint8_t                 i2s_channel;
	i2s_ws_trig_edge        i2s_ws_edge;
	i2s_edge_sw             i2s_data_edge;
	i2s_channel_type        rx_channel;
	i2s_channel_type        tx_channel;
	i2s_direction_type      i2s_direction;
	uint8_t                 rx_byte_swap;
	uint8_t                 tx_byte_swap;
	uint8_t                 pin_group_num;
	uint32_t                i2s_timestamp_offset;
	i2s_tx_cache_t          i2s_tx_cache;
	i2s_rx_cache_t          i2s_rx_cache;
	TaskHandle_t            i2s_rx_task;
} i2s_ctx_t;

extern i2s_params_t default_i2s_params;
extern mm_module_t i2s_module;
#endif
