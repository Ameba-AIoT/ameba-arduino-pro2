#ifndef RX_OQPSK_H
#define RX_OQPSK_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <arm_neon.h>
#include <stdlib.h>
#include "rx_packet_detect.h"
#include "rx_interpolator.h"
#include "rx_dagc.h"
#include "rx_phase_rot.h"
#include "rx_coarse_cfo.h"
#include "rx_ch_est.h"
#include "rx_sbd.h"
#include "rx_ml_detect.h"
#include "rx_sco_tracking.h"
#include "rx_cfo_tracking.h"
#include "ameba_soc.h"

/* testchip */
#ifdef CONFIG_RLE1080_A_CUT
#define ZGB_RX_DATA_SIZE 9600  //600 blocks * 64byte
#define RX_DATA_SAMPLE_SIZE 14400 // 9600 * 3 / 2
#define CONVERT_DATA_SIZE 28800 //9600 * 3
#else
#define ZGB_RX_DATA_SIZE 19200  //600 blocks * 128bte  19200
#define RX_DATA_SAMPLE_SIZE 28800 // 9600*2*3/2  28800
#define CONVERT_DATA_SIZE 57600 //9600*2*3  57600
#endif

#define RX_EXT_DATA_SIZE 3600 // 14400 / 4 because even and odd


typedef enum _RX_STATE {
	RX_STATE_PD = 0,
	RX_STATE_AAGC,
	RX_STATE_DAGC,
	RX_STATE_INTERP,
	RX_STATE_ML,
	RX_STATE_OVER,
} RX_STATE;

struct RX_OQPSK {
	volatile int32_t wl_cca;
	int32_t aagc_done;
	int32_t symb_pre;
	int32_t is_data_valid;
	int32_t is_sfd_found;
	int32_t is_len_found;
	int32_t is_payload_done;
	int32_t data_cnt_octet;
	int32_t sample_cnt;
	volatile int32_t is_fa;
	uint8_t *data_decoded;
	int32_t crc16_fail;
	int32_t sfd;
	int32_t data_len;
	struct pkt_detect *pkt_det;
	INTERPOLATOR *interpolator;
	struct rx_dagc *dagc;
	PHASE_ROT *phase_rot;
	COARSE_CFO *coarse_cfo;
	struct rx_sbd *sbd;
	struct rx_ch_est *ch_est;
	struct rx_ml_detect *ml_det;
	struct cfo_track *cfo_tracking;
	struct sco_track *sco_tracking;
	volatile int32_t state;
	int32_t cca;
	int32x2_t *rx_buf;
	int32_t *rx_buf_re;
	int32_t *rx_buf_im;
	uint32_t rx_buf_idx;
	int32_t rx_len;
	int32_t rx_total;
	int32_t rx_is_over;
	int32_t rssi;
	int32_t ed;
	int32_t lqi;

	uint32_t rx_pkt_cnt;
	uint32_t cca_cnt;
	uint32_t crc_ok_cnt;
	uint32_t crc_fail_cnt;
	uint32_t sfd_not_found_cnt;
	uint32_t len_illegal_cnt;
} ;

struct rx_state_machine {
	RX_STATE state;
	void (*func)(struct RX_OQPSK *obj);
};

void rx_state_pd(struct RX_OQPSK *obj);
void rx_state_aagc(struct RX_OQPSK *obj);
void rx_state_dagc(struct RX_OQPSK *obj);
void rx_state_interp(struct RX_OQPSK *obj);
void rx_state_ml(struct RX_OQPSK *obj);

extern struct rx_state_machine g_rx_call[];

void rx_oqpsk_init(struct RX_OQPSK *obj);
void rx_oqpsk_reset(struct RX_OQPSK *obj);
void rx_decoded(struct RX_OQPSK *obj);

void rx_oqpsk_test_20bytes(void);
void rx_oqpsk_test_127bytes(void);


#ifdef  __cplusplus
}
#endif

#endif
