#ifndef __TX_OQPSK_H__
#define __TX_OQPSK_H__
#include "ameba_common.h"

#define IQ_BUF_ZIE 42565
#define INT8_HALF_SIN

typedef enum _RET {
	RET_ERROR = -1,
	RET_SUCCESS,
	RET_FAIL,
	RET_INVALID_PARAM,
} RET_VAL;

struct tx_frame {
	uint8_t preamble[4];
	uint8_t sfd;
	uint8_t frm_len;
};

struct tx_oqpsk {
	/*float32_t tc;
	int32_t fs;
	int32_t fs_ifmod;
	int32_t chip_rate;
	int32_t fc_offset;
	int32_t dac_clk;*/
	uint8_t *psdu;
	int32_t psdu_len;
#ifdef INT8_HALF_SIN
	uint16_t *dout;
#else
	float32x2_t *dout;
#endif
	//int32_t iq_len;
	uint32_t tx_ok_cnt;
};

int32_t tx_oqpsk_run(struct tx_oqpsk *obj);
int32_t tx_oqpsk_init(struct tx_oqpsk *obj);
int32_t tx_oqpsk_reset(struct tx_oqpsk *obj);

#endif
