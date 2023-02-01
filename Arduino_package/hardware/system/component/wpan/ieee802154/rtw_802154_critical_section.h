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

#ifndef RTW_802154_CRITICAL_SECTION_H__
#define RTW_802154_CRITICAL_SECTION_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
#define CRITICAL_SECTION_DEBUG 0
/**
 * @defgroup rtw_802154_critical_section 802.15.4 driver critical section
 * @{
 * @ingroup rtw_802154
 * @brief Critical section used with requests to the 802.15.4 driver.
 */

/**
 * @brief Initializes the critical section module.
 */
void rtw_802154_critical_section_init(void);

/**
 * @brief Function for entering a critical section in the 802.15.4 driver.
 *
 * @retval true   The critical section is entered.
 * @retval false  The critical section could not be entered.
 */
#if CRITICAL_SECTION_DEBUG
#define rtw_802154_critical_section_enter() rtw_802154_critical_section_enter_debug(__func__)
bool rtw_802154_critical_section_enter_debug(char *func);
#else
bool rtw_802154_critical_section_enter(void);
#endif

/**
 * @brief Function for exiting a critical section in the 802.15.4 driver.
 */
#if CRITICAL_SECTION_DEBUG
#define rtw_802154_critical_section_exit() rtw_802154_critical_section_exit_debug(__func__)
void rtw_802154_critical_section_exit_debug(char *func);
#else
void rtw_802154_critical_section_exit(void);
#endif

/**
 * @brief Function for forcefully entering a critical section in the 802.15.4 driver.
 *
 * With this function, the critical section is entered regardless of whether
 * it has been already entered before.
 *
 * This function is intended to be used by RADIO IRQ handler and RSCH notifications handlers to
 * prevent interrupting of these procedures by FSM requests from higher priority IRQ handlers.
 */
#if CRITICAL_SECTION_DEBUG
#define rtw_802154_critical_section_forcefully_enter() rtw_802154_critical_section_forcefully_enter_debug(__func__)
void rtw_802154_critical_section_forcefully_enter_debug(char *func);
#else
void rtw_802154_critical_section_forcefully_enter(void);
#endif

/**
 * @brief Allows entry to a nested critical section.
 *
 * This function is intended to be used with the notification module to allow processing
 * requests called from the notification context.
 */
void rtw_802154_critical_section_nesting_allow(void);

/**
 * @brief Denies entry to a nested critical section.
 */
void rtw_802154_critical_section_nesting_deny(void);

/**
 * @brief Checks if the critical section is nested.
 *
 * @retval true   Critical section is nested.
 * @retval false  Critical section is not nested.
 */
bool rtw_802154_critical_section_is_nested(void);
/**
 *@}
 **/

#ifdef __cplusplus
}
#endif

#endif // RTW_802154_CRITICAL_SECTION_H__
