#ifndef __HIFI_RTW_RADIO_H__
#define __HIFI_RTW_RADIO_H__

void rtw_radio_rx_task(void);
void rtw_radio_tx_task(uint32_t pkt_cnt, uint32_t pkt_len, uint32_t psdu_type, uint32_t pkt_intv);
#endif
