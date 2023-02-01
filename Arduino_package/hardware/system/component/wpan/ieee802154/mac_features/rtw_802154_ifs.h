/*
 * Copyright (c) 2017 - 2021, Realtek
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Realtek nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef RTW_802154_IFS_H
#define RTW_802154_IFS_H

#include <stdbool.h>
#include <stdint.h>

#include "rtw_802154_const.h"
#include "rtw_802154_types.h"

/**
 * @brief Examines the frame before transmission and checks if it needs to be delayed.
 *
 * @param[in]  p_frame          Pointer to the buffer that contains the PHR and PSDU
 *                              of the transmitted frame.
 * @param[in]  p_params         Pointer to the transmission parameters.
 * @param[in]  notify_function  Function to be called to notify transmission failure.
 *
 * @retval     true      Frame will be transmitted right away.
 * @retval     false     Frame is delayed and will be transmistted after a needed IFS.
 */
bool rtw_802154_ifs_pretransmission(
	const uint8_t	 *p_frame,
	bool	cca,
	bool	immediate);

/**
 * @brief Captures the timestamp, length and destination address of the transmitted
 *        frame for the sake of future analysis by the @ref rtw_802154_ifs_pretransmission
 *
 * @param[in]  p_frame  Pointer to the buffer that contains the PHR and PSDU of the transmitted frame.
 */
void rtw_802154_ifs_transmitted_hook(const uint8_t *p_frame);

/**
 * @brief Aborts an ongoing IFS-delayed transmission.
 *
 * @param[in]  term_lvl  Termination level set by the request to abort the ongoing operation.
 * @param[in]  req_orig  Module that originates this request.
 *
 * @retval  true   Transmission procedure have been stopped.
 * @retval  false  Transmission procedure were not running.
 *
 */
bool rtw_802154_ifs_abort(rtw_802154_term_t term_lvl, req_originator_t req_orig);

#endif // RTW_802154_IFS_H
