/* Copyright (c) 2017 - 2018, Realtek
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this
 *      list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *
 *   3. Neither the name of Realtek nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * @brief Module that contains core of the Realtek IEEE 802.15.4 radio driver.
 *
 */

#ifndef RTW_802154_CORE_H_
#define RTW_802154_CORE_H_

#include <stdbool.h>
#include <stdint.h>

#include "rtw_802154_config.h"
#include "rtw_802154_notification.h"
//#include "rtw_802154_rx_buffer.h"
#include "rtw_802154_const.h"
#include "rtw_802154_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the 802.15.4 driver core.
 */
void rtw_802154_core_init(void);

/**
 * @brief Deinitializes the 802.15.4 driver core.
 */
void rtw_802154_core_deinit(void);

/**
 * @brief Gets the current state of the Realtek 802.15.4 driver.
 *
 * @returns  Current state of the 802.15.4 driver.
 */
rtw_radio_func_t rtw_802154_core_state_get(void);

/***************************************************************************************************
 * @section State machine transition requests
 **************************************************************************************************/

/**
 * @brief Requests the transition to the @ref RADIO_STATE_SLEEP state.
 *
 * @param[in]  term_lvl  Termination level of this request. Selects procedures to abort.
 *
 * @retval  true   Entering the sleep state succeeded.
 * @retval  false  Entering the sleep state failed (the driver is performing other procedure).
 */
bool rtw_802154_core_sleep(rtw_802154_term_t term_lvl);

/**
 * @brief Requests the transition to the @ref RADIO_STATE_RX state.
 *
 * @param[in]  term_lvl         Termination level of this request. Selects procedures to abort.
 * @param[in]  req_orig         Module that originates this request.
 * @param[in]  notify_function  Function called to notify the status of this procedure. May be NULL.
 * @param[in]  notify_abort     If abort notification is to be triggered.
 *
 * @retval  true   Entering the receive state succeeded.
 * @retval  false  Entering the receive state failed (the driver is performing other procedure).
 */
bool rtw_802154_core_receive(rtw_802154_term_t              term_lvl,
							 req_originator_t               req_orig,
							 rtw_802154_notification_func_t notify_function,
							 bool                           notify_abort);

/**
 * @brief Requests the transition to the @ref RADIO_STATE_TX state.
 *
 * @param[in]  term_lvl         Termination level of this request. Selects procedures to abort.
 * @param[in]  req_orig         Module that originates this request.
 * @param[in]  p_data           Pointer to a frame to transmit.
 * @param[in]  cca              If the driver is to perform CCA procedure before transmission.
 * @param[in]  immediate        If true, the driver schedules transmission immediately or never.
 *                              If false, the transmission may be postponed until
 *                              the TX preconditions are met.
 * @param[in]  notify_function  Function called to notify the status of this procedure. May be NULL.
 *
 * @retval  true   Entering the transmit state succeeded.
 * @retval  false  Entering the transmit state failed (the driver is performing other procedure).
 */
bool rtw_802154_core_transmit(rtw_802154_term_t              term_lvl,
							  req_originator_t               req_orig,
							  const uint8_t                 *p_data,
							  bool                           cca,
							  bool                           immediate,
							  rtw_802154_notification_func_t notify_function);

/**
 * @brief Requests the transition to the @ref RADIO_STATE_ED state.
 *
 * When the energy detection procedure is finished, the driver transitions
 * to the @ref RADIO_STATE_RX state.
 *
 * @param[in]  term_lvl  Termination level of this request. Selects procedures to abort.
 * @param[in]  time_us   Minimal time of energy detection procedure.
 *
 * @retval  true   Entering the energy detection state succeeded.
 * @retval  false  Entering the energy detection state failed
 *                 (the driver is performing other procedure).
 */
bool rtw_802154_core_energy_detection(rtw_802154_term_t term_lvl, uint32_t time_us);

/**
 * @brief Requests the transition to the @ref RADIO_STATE_CCA state.
 *
 * @param[in]  term_lvl  Termination level of this request. Selects procedures to abort.
 *
 * @retval  true   Entering the CCA state succeeded.
 * @retval  false  Entering the CCA state failed (the driver is performing other procedure).
 */
bool rtw_802154_core_cca(rtw_802154_term_t term_lvl);

/**
 * @brief Requests the transition to the @ref RADIO_STATE_CONTINUOUS_CARRIER state.
 *
 * When the CCA procedure is finished, the driver transitions to the @ref RADIO_STATE_RX state.
 *
 * @param[in]  term_lvl  Termination level of this request. Selects procedures to abort.
 *
 * @retval  true   Entering the continuous carrier state succeeded.
 * @retval  false  Entering the continuous carrier state failed
 *                 (the driver is performing other procedure).
 */
bool rtw_802154_core_continuous_carrier(rtw_802154_term_t term_lvl);

/***************************************************************************************************
 * @section State machine notifications
 **************************************************************************************************/

/**
 * @brief Notifies the core module that a higher layer freed a frame buffer.
 *
 * When there are no free buffers available, the core does not start the receiver.
 * If the core receives this notification, it changes the internal state to make sure
 * the receiver is started if requested.
 *
 * @param[in]  p_data  Pointer to buffer that has been freed.
 */
bool rtw_802154_core_notify_buffer_free(uint8_t *p_data);

/**
 * @brief Notifies the core module that the next higher layer requested the change of the channel.
 *
 * The core is expected to update the frequency register of the peripheral and, if it is
 * in the @ref RADIO_STATE_RX or in the @ref RADIO_STATE_CONTINUOUS_CARRIER state, the transceiver
 * is disabled and enabled again to use the new channel.
 *
 */
bool rtw_802154_core_channel_update(void);

/**
 * @brief Notifies the core module that the next higher layer requested the change
 * of the CCA configuration.
 */
bool rtw_802154_core_cca_cfg_update(void);

/**
 * @brief Notifies the core module that the next higher layer requested the RSSI measurement.
 */
bool rtw_802154_core_rssi_measure(void);

/**
 * @brief Gets the last RSSI measurement.
 *
 * @param[out]  p_rssi  RSSI measurement value in dBm.
 */
bool rtw_802154_core_last_rssi_measurement_get(int8_t *p_rssi);

#ifdef __cplusplus
}
#endif

#endif /* RTW_802154_CORE_H_ */
