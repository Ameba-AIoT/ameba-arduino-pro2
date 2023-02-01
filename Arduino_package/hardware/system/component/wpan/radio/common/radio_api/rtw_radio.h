#ifndef RTW_RADIO_H__
#define RTW_RADIO_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#if RTW_802154_HOST_IPC || RTW_802154_RADIO_IPC
#ifdef CONFIG_PLATFORM_AMEBAD2
#define RTW_802154_RADIO_IPC_HOST_TO_RADIO		IPC_NP_TO_AP
#define RTW_802154_RADIO_IPC_RADIO_TO_HOST		IPC_AP_TO_NP
#define RTW_802154_RADIO_IPC_HOST_TO_RADIO_CHAN		IPC_N2A_802154_TRAN
#define RTW_802154_RADIO_IPC_RADIO_TO_HOST_CHAN		IPC_A2N_802154_TRAN
#elif defined(CONFIG_PLATFORM_AMEBALITE)
#define RTW_802154_RADIO_IPC_HOST_TO_RADIO		IPC_KM4_TO_DSP
#define RTW_802154_RADIO_IPC_RADIO_TO_HOST		IPC_DSP_TO_KM4
#define RTW_802154_RADIO_IPC_HOST_TO_RADIO_CHAN		IPC_M2D_802154_TRAN
#define RTW_802154_RADIO_IPC_RADIO_TO_HOST_CHAN		IPC_D2M_802154_TRAN
#if RTW_802154_RADIO_IPC
#ifndef CMD_TABLE_DATA_SECTION
#define CMD_TABLE_DATA_SECTION __attribute__ ((section(".command")))
#endif
#ifndef IPC_TABLE_DATA_SECTION
#define IPC_TABLE_DATA_SECTION __attribute__ ((section(".ipc_table")))
#endif
static inline uint32_t DTimestamp_Get(void)
{
	return (*((volatile uint32_t *)(0x4011E004)));
}
#endif
#else
#error "undefine 802154 radio IPC!!!!!!!!!!!"
#endif
#endif

#define RTW_802154_RADIO_MP_INCLUDE			1
#define RTW_802154_RADIO_CACHE_PACKET_SIZE	128
/*only three cases:
RTW_802154_HOST_IPC 1 RTW_802154_RADIO_IPC 0, 802154 host ipc make, like amebalite km4
RTW_802154_HOST_IPC 0 RTW_802154_RADIO_IPC 1, 802154 radio ipc make, like amebalite hifi5
RTW_802154_HOST_IPC 0 RTW_802154_RADIO_IPC 0, like amebasmart ca32
*/
#ifndef RTW_802154_HOST_IPC
#define RTW_802154_HOST_IPC 0
#endif
#ifndef RTW_802154_RADIO_IPC
#define RTW_802154_RADIO_IPC 0
#endif
#if RTW_802154_HOST_IPC && RTW_802154_RADIO_IPC
#error "can't define RTW_802154_HOST_IPC and RTW_802154_RADIO_IPC as 1 at the same time!!!!!"
#endif

#if RTW_802154_HOST_IPC || RTW_802154_RADIO_IPC
#if !defined(RTW_802154_RADIO_IPC_HOST_TO_RADIO)\
	|| !defined(RTW_802154_RADIO_IPC_RADIO_TO_HOST)\
	|| !defined(RTW_802154_RADIO_IPC_HOST_TO_RADIO_CHAN)\
	|| !defined(RTW_802154_RADIO_IPC_RADIO_TO_HOST_CHAN)
#error "undefine 802154 radio IPC!!!!!!!!!!!"
#endif
#endif

#define TX_ACK_TIME_DELAY 1
#define RX_RESET_TIME_DEBUG 0
#define MEASURE_RX_HANDLER_TIME 0
#define MEASURE_RX_IPC_TIME 0
#define MEASURE_TX_ACK_TIME 0
#define MEASURE_RX_RESTART_TIME 0
#if RTW_802154_RADIO_IPC
#define RADIO_TASK_PRIORITY (configMAX_PRIORITIES - 3)
#else
#define RADIO_TASK_PRIORITY (configMAX_PRIORITIES - 1)
#endif
/* Dtime from rtw_802154_radio_callback_handler to rtw_radio_tx_frame 114-150 in ipc mode*/

/** @brief RADIO Clear Channel Assessment modes. */
typedef enum {
	RTW_RADIO_CCA_MODE_ED             = 0,           /**< Energy Above Threshold. Will report busy whenever energy is detected above set threshold. */
	RTW_RADIO_CCA_MODE_CARRIER,      /**< Carrier Seen. Will report busy whenever compliant IEEE 802.15.4 signal is seen. */
	RTW_RADIO_CCA_MODE_CARRIER_AND_ED, /**< Energy Above Threshold AND Carrier Seen. */
	RTW_RADIO_CCA_MODE_CARRIER_OR_ED,  /**< Energy Above Threshold OR Carrier Seen. */
	RTW_RADIO_CCA_MODE_ED_TEST1,      /**< Energy Above Threshold test mode that will abort when first ED measurement over threshold is seen. No averaging. */
} rtw_radio_cca_mode_t;

/** @brief RADIO task steps. */
typedef enum {
	RTW_RADIO_TASK_TX_STEP_CCA = 1,
	RTW_RADIO_TASK_TX_STEP_TX,
	RTW_RADIO_TASK_TX_STEP_END,

	RTW_RADIO_TASK_RX_STEP_CCA,
	RTW_RADIO_TASK_RX_STEP_RX,
	RTW_RADIO_TASK_RX_STEP_END,

	RTW_RADIO_TASK_ED_STEP_END,
} rtw_radio_task_setp_t;

/** @brief RADIO ctl ID. */
typedef enum {
	//radio task ctl
	RTW_RADIO_FUNC_TASK_TERMINATE = 1,/*set as 1 used in ipc*/
	RTW_RADIO_FUNC_TX_EN,
	RTW_RADIO_FUNC_CCA_TX_EN,
	RTW_RADIO_FUNC_TX_ACK_EN,
	RTW_RADIO_FUNC_RX_EN,
	RTW_RADIO_FUNC_RX_ACK_EN,
	RTW_RADIO_FUNC_RSSI_EN,
	RTW_RADIO_FUNC_CCA_EN,
	RTW_RADIO_FUNC_ED_EN,
	RTW_RADIO_FUNC_CONTINUOUS_CARRIER_EN,
	RTW_RADIO_FUNC_MP_TX_EN,
	RTW_RADIO_FUNC_MP_RX_EN,
	RTW_RADIO_FUNC_MP_RX_EN_2,//used for mp rx simulate normal rx, will hal_radio_rx_start/stop every receive
	RTW_RADIO_FUNC_SLEEP_EN,

	//radio func
	RTW_RADIO_FUNC_CHANNEL_SET,
	RTW_RADIO_FUNC_BANDWIDTH_SET,
	RTW_RADIO_FUNC_TXPOWER_SET,
	RTW_RADIO_FUNC_RSSI_GET,
	RTW_RADIO_FUNC_CCA_CONFIGURE,
	RTW_RADIO_FUNC_RADIO_ON,
	RTW_RADIO_FUNC_RADIO_OFF,
	RTW_RADIO_FUNC_RADIO_INIT,
	RTW_RADIO_FUNC_RADIO_DEINIT,
} rtw_radio_func_t;

/* total 128 byte, last two byte used for lqi and used flag
	byte0 byte1......byte126,byte127
	len,  .. .....   crc,    crc
->  len,  .. .....   lqi,    rssi	*/

#if RTW_802154_RADIO_MP_INCLUDE
typedef struct rtw_radio_mp {
	uint32_t tx_pkt_cnt;//total tx pkt cnt, continus: 0
	uint32_t tx_pkt_num;//the num of pkt has been transmitted
	uint32_t tx_pkt_len;//max 127 + 2(crc)
	uint32_t tx_psdu_type;
	uint32_t tx_pkt_intv;
	uint8_t tx_payload[RTW_802154_RADIO_CACHE_PACKET_SIZE];//127 + 1(length)
	uint32_t rx_crc_ok_cnt;//total cnt, continus: 0, terminate rx if match
	uint32_t rx_crc_fail_cnt;//total cnt, continus: 0, terminate rx if match
	uint32_t rx_sfd_not_found_cnt;//total cnt, continus: 0, terminate rx if match
	uint32_t rx_len_illegal_cnt;//total cnt, continus: 0, terminate rx if match
	uint32_t rx_cca_cnt;//total cnt, continus: 0, terminate rx if match
} rtw_radio_mp_t;
extern rtw_radio_mp_t rtw_radio_mp_obj;
#endif

typedef struct rtw_radio_ctl {
	volatile uint8_t packet[RTW_802154_RADIO_CACHE_PACKET_SIZE] __attribute__((aligned(64)));
	volatile uint32_t ed_time;
	volatile rtw_radio_func_t radio_task_ctl;
	volatile rtw_radio_func_t radio_task_state;
}
rtw_radio_ctl_t;

void rtw_radio_task_terminate(void);
void rtw_radio_task_enable(rtw_radio_func_t radio_func);
void rtw_radio_tx_enable(rtw_radio_func_t radio_func, uint8_t *pkt_ptr);
void rtw_radio_ed_enable(rtw_radio_func_t radio_func, uint32_t time_us);
void rtw_radio_channel_set(uint8_t channel);
void rtw_radio_bw_set(uint8_t bw);
void rtw_radio_cca_configure(void);
void rtw_radio_txpower_set(int8_t txpower);
int8_t rtw_radio_rssi_value_get();
void rtw_radio_on(void);
void rtw_radio_off(void);
void rtw_radio_task_init(void);
void rtw_radio_task_deinit(void);
void rtw_802154_radio_callback_handler(rtw_radio_task_setp_t callback_step, uint32_t temp);
inline void rtw_radio_task_state_wait(rtw_radio_func_t state);
uint32_t rtw_radio_func_ipc(rtw_radio_func_t func, uint32_t temp);
inline rtw_radio_func_t rtw_radio_task_state_get(void);
inline void rtw_radio_task_state_set(rtw_radio_func_t new_state);
bool rtw_radio_task_state_mismatch(rtw_radio_func_t state);
inline bool rtw_radio_task_state_match(rtw_radio_func_t state);
inline void rtw_radio_task_ctl_set(rtw_radio_func_t radio_func);
inline rtw_radio_func_t rtw_radio_task_ctl_get(void);
inline bool rtw_radio_task_ctl_match(rtw_radio_func_t ctl);
bool rtw_radio_task_ctl_mismatch(rtw_radio_func_t ctl);
bool rtw_radio_rx_frame(rtw_radio_func_t radio_func);
bool rtw_radio_tx_cca_check(void);
static void rtw_radio_rssi_task(rtw_radio_func_t radio_func);
static void rtw_radio_cca_task(rtw_radio_func_t radio_func);
static void rtw_radio_continuous_carrier_task(rtw_radio_func_t radio_func);
static void rtw_radio_ed_task(rtw_radio_func_t radio_func);
static void rtw_radio_sleep_task(rtw_radio_func_t radio_func);
static void rtw_radio_rx_task(rtw_radio_func_t radio_func);
static void rtw_radio_mp_tx_task(rtw_radio_func_t radio_func);
static void rtw_radio_tx_task(rtw_radio_func_t radio_func);
void rtw_radio_thread(void);

#endif //RTW_RADIO_H__
