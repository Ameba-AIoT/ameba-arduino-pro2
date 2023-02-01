#ifndef __RX_OQPSK_H__
#define __RX_OQPSK_H__
#include "trx_common.h"
#include "pd_imp.h"
#include "dagc.h"
#include "coarse_cfo.h"
#include "sbd.h"
#include "ch_est.h"
#include "interpltr.h"
#include "phase_rot.h"
#include "ml_detect_imp.h"
#include "sco_track.h"

typedef enum _RX_STATE {
	RX_STATE_PD,
	RX_STATE_AAGC,
	RX_STATE_DAGC,
	RX_STATE_INTERP,
	RX_STATE_ML,
	RX_STATE_OVER
} RX_STATE;

typedef struct rx_oqpsk {
	ae_int32x2 din;
	int32_t aagc_done;
	int32_t symb_pre;
	int32_t is_data_valid;
	int32_t is_sfd_found;
	int32_t is_len_found;
	int32_t is_payload_done;
	int32_t data_cnt_octet;
	int32_t sample_cnt;
	int32_t is_fa;
	uint8_t *data_decoded;
	int32_t crc16_fail;
	int32_t sfd;
	int32_t data_len;
	struct pkt_detect_imp pkt_det;
	struct rx_interpolator interpltr;
	struct rx_dagc dagc;
	struct phase_rot phase_rot;
	struct coarse_cfo coarse_cfo;
	struct rx_sbd sbd;
	struct rx_ch_est ch_est;
	struct rx_ml_detect_imp ml_det;
	struct sco_track sco;
	int32_t state;
	int32_t cca;
	ae_int16x2 *rx_buf;
	int32_t rx_len;
	int32_t rx_total;
	int32_t rx_is_over;
	int32_t rx_buf_idx;
	int32_t rssi;
	int32_t ed;
	int32_t lqi;
	volatile int32_t wl_cca;

	uint32_t rx_pkt_cnt;
	uint32_t cca_cnt;
	uint32_t crc_ok_cnt;
	uint32_t crc_fail_cnt;
	uint32_t sfd_not_found_cnt;
	uint32_t len_illegal_cnt;

} RX_OQPSK;

struct rx_state_machine {
	RX_STATE state;
	void (*func)(struct rx_oqpsk *obj);
};

void rx_oqpsk_init(struct rx_oqpsk *rx);
void rx_oqpsk_reset(struct rx_oqpsk *rx);
void rx_state_pd(struct rx_oqpsk *rx);
void rx_state_aagc(struct rx_oqpsk *rx);
void rx_state_dagc(struct rx_oqpsk *rx);
void rx_state_interp(struct rx_oqpsk *rx);
void rx_state_ml(struct rx_oqpsk *rx);

#endif
