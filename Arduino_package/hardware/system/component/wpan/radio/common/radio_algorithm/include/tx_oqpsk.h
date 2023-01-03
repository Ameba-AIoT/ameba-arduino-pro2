#ifndef TX_OQPSK_H
#define TX_OQPSK_H
#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <arm_neon.h>
#include <stdlib.h>
#define IQ_BUF_ZIE 42565

#define INT8_HALF_SIN

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

static __inline void de2bi(uint8_t decimal, char *msb_right, int32_t nbits)
{
	int32_t i = 0;
	for (i = 0; i < nbits; i++) {
		msb_right[i] = decimal & 0x1;
		decimal >>= 1;
	}
	return;
}

int32_t tx_oqpsk_run(struct tx_oqpsk *obj);
int32_t tx_oqpsk_init(struct tx_oqpsk *obj);
int32_t tx_oqpsk_reset(struct tx_oqpsk *obj);
void tx_oqpsk_test_run(void);


#ifdef  __cplusplus
}
#endif
#endif


