/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */
#ifndef _RTK_LEGACY_GAP_IMPL_H_
#define _RTK_LEGACY_GAP_IMPL_H_

/* -------------------------------- Includes -------------------------------- */
#include <stdint.h>
#include <gap.h>
#include <rtk_bt_a2dp.h>
#include <rtk_legacy_gap.h>

/* -------------------------------- Defines -------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @defgroup APP_MAIN_Exported_Macros App Main Macros
    * @{
    */
#define UART_BUD_RX     (P3_0)

#define RWS_PRIMARY_VALID_OK             0x01
#define RWS_SECONDARY_VALID_OK           0x02

#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif
#define MAX_NUMBER_OF_GAP_TIMER         0x10    //!< indicate gap timer queue size
/** max BR/EDR link num */
#define MAX_BR_LINK_NUM                 1
/** bitmask of profiles */
#define A2DP_PROFILE_MASK               0x00000001    /**< A2DP profile bitmask */
#define AVRCP_PROFILE_MASK              0x00000002    /**< AVRCP profile bitmask */
#define HFP_PROFILE_MASK                0x00000004    /**< HFP profile bitmask */
#define RDTP_PROFILE_MASK               0x00000008    /**< Remote Control vendor profile bitmask */
#define SPP_PROFILE_MASK                0x00000010    /**< SPP profile bitmask */
#define IAP_PROFILE_MASK                0x00000020    /**< iAP profile bitmask */
#define PBAP_PROFILE_MASK               0x00000040    /**< PBAP profile bitmask */
#define HSP_PROFILE_MASK                0x00000080    /**< HSP profile bitmask */
#define GATT_PROFILE_MASK               0x00000100    /**< GATT profile bitmask */
#define GFPS_PROFILE_MASK               0x00010000    /**< GFPS profile bitmask */
#define XIAOAI_PROFILE_MASK             0x00020000    /**< XIAOAI profile bitmask */
#define AMA_PROFILE_MASK                0x00040000    /**< AMA profile bitmask */
#define AVP_PROFILE_MASK                0x00080000    /**< AVP profile bitmask */

#define ALL_PROFILE_MASK                (A2DP_PROFILE_MASK | AVRCP_PROFILE_MASK | HFP_PROFILE_MASK | \
                                         HSP_PROFILE_MASK | RDTP_PROFILE_MASK | SPP_PROFILE_MASK | \
                                         IAP_PROFILE_MASK | PBAP_PROFILE_MASK)

#define DEFAULT_SUPVISIONTIMEOUT        0x1f40 //0x7D00

/* ------------------------------- Data Types ------------------------------- */
/**  @brief  APP's Bluetooth BR/EDR link connection database */
typedef struct {
	void                *timer_handle_role_switch;
	void                *timer_handle_later_avrcp;
	uint8_t             bd_addr[6];
	bool                used;
	uint8_t             id;
	uint32_t            connected_profile;
	uint8_t             a2dp_codec_type;
	union {
		struct {
			uint8_t sampling_frequency;
			uint8_t channel_mode;
			uint8_t block_length;
			uint8_t subbands;
			uint8_t allocation_method;
			uint8_t min_bitpool;
			uint8_t max_bitpool;
		} sbc;
		struct {
			uint8_t  object_type;
			uint16_t sampling_frequency;
			uint8_t  channel_number;
			bool     vbr_supported;
			uint32_t bit_rate;
		} aac;
		struct {
			uint8_t  info[12];
		} vendor;
	} a2dp_codec_info;

	uint8_t             streaming_fg;
	uint8_t             avrcp_play_status;

} T_APP_BR_LINK;

typedef struct {
	T_APP_BR_LINK       br_link[MAX_BR_LINK_NUM];
	uint8_t                      factory_addr[6];            /**< local factory address */
} T_APP_DB;

/* ------------------------------- Variables ---------------------------------*/
extern T_APP_DB app_db;
extern void *audio_evt_queue_handle;
extern void *audio_io_queue_handle;

/**
 * @brief  process legacy gap initialization.
 * @param  evt_msg_q[in] event queue handle
 * @return none.
 */
void rtk_lagacy_gap_init(void *evt_msg_q);

/**
 * @brief  process legacy framework initialization.
 * @param  evt_msg_q[in] event queue handle
 * @return none.
 */
void rtk_legacy_framework_init(void *evt_msg_q);

/**
 * @brief  process legacy app gap initialization.
 * @param  none.
 * @return none.
 */
void rtk_legacy_app_gap_init(void);

/**
 * @brief  process app gap deinit.
 * @param  none.
 * @return none.
 */
void rtk_legacy_app_gap_deinit(void);

/**
 * @brief  process framework deinit.
 * @param  none.
 * @return none.
 */
void rtk_legacy_framework_deinit(void);

/**
 * @brief  process gap deinit.
 * @param  none.
 * @return none.
 */
void rtk_lagacy_gap_deinit(void);

T_APP_RESULT rtk_legacy_gap_callback(uint8_t type, void *data);

rtk_bt_err_t rtk_legacy_gap_set_default_param_impl(rtk_legacy_gap_default_param_type_t type, 
												rtk_legacy_gap_default_param_value_t *param);

rtk_bt_err_t rtk_legacy_gap_get_address_impl(rtk_legacy_bd_addr_t* addr);

rtk_bt_evt_status_t rtk_legacy_gap_set_device_name_impl(const uint8_t* name);

rtk_bt_evt_status_t rtk_legacy_gap_set_page_param_impl(rtk_legacy_page_param_t *page_param);

rtk_bt_evt_status_t rtk_legacy_gap_set_inquiry_param_impl(rtk_legacy_inquiry_param_t *inquiry_param);

uint32_t app_connected_profiles(void);

/**
    * @brief  get BR/EDR link num wich connected with phone by the mask profile
    * @param  profile_mask the mask profile
    * @return BR/EDR link num
    */
uint8_t app_connected_profile_link_num(uint32_t profile_mask);

/**
    * @brief  get the BR/EDR link by bluetooth address
    * @param  bd_addr bluetooth address
    * @return the BR/EDR link
    */
T_APP_BR_LINK *app_find_br_link(uint8_t *bd_addr);

/**
    * @brief  alloc the BR/EDR link by bluetooth address
    * @param  bd_addr bluetooth address
    * @return the BR/EDR link
    */
T_APP_BR_LINK *app_alloc_br_link(uint8_t *bd_addr);

/**
    * @brief  free the BR/EDR link
    * @param  p_link the BR/EDR link
    * @return true: success; false: fail
    */
bool app_free_br_link(T_APP_BR_LINK *p_link);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RTK_LEGACY_GAP_IMPL_H_ */
