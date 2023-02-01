/*
 *  Copyright (c) 2016, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file includes the platform-specific initializers.
 *
 */

#ifndef PLATFORM_AMEBAD2_H_
#define PLATFORM_AMEBAD2_H_

#include <stdint.h>

#include <openthread/instance.h>

#include "openthread-core-config.h"
#include <openthread/config.h>

#include <osdep_service.h>
#include <sys_api.h>
#include <debug.h>


/*******************************************************************************
 * @section Radio driver configuration.
 ******************************************************************************/

/**
 * @def RTW_802154_PENDING_SHORT_ADDRESSES
 *
 * Number of slots containing short addresses of nodes for which pending data is stored.
 *
 */
#ifndef RTW_802154_PENDING_SHORT_ADDRESSES
#define RTW_802154_PENDING_SHORT_ADDRESSES OPENTHREAD_CONFIG_MLE_MAX_CHILDREN
#endif

/**
 * @def RTW_802154_PENDING_EXTENDED_ADDRESSES
 *
 * Number of slots containing extended addresses of nodes for which pending data is stored.
 *
 */
#ifndef RTW_802154_PENDING_EXTENDED_ADDRESSES
#define RTW_802154_PENDING_EXTENDED_ADDRESSES OPENTHREAD_CONFIG_MLE_MAX_CHILDREN
#endif

/**
 * @def RTW_802154_CSMA_CA_ENABLED
 *
 * If CSMA-CA procedure should be enabled by the driver. Disabling CSMA-CA procedure improves
 * driver performance.
 *
 */
#ifndef RTW_802154_CSMA_CA_ENABLED
#define RTW_802154_CSMA_CA_ENABLED 1
#endif

/**
 * @def RTW_802154_ACK_TIMEOUT_ENABLED
 *
 * If ACK timeout feature should be enabled in the driver.
 *
 */
#ifndef RTW_802154_ACK_TIMEOUT_ENABLED
#define RTW_802154_ACK_TIMEOUT_ENABLED 1
#endif

/**
 * @def RTW_802154_TX_STARTED_NOTIFY_ENABLED
 *
 * If notification of started transmission should be enabled in the driver.
 *
 * @note This feature must be enabled to support Header IE related features.
 *
 */
#ifndef RTW_802154_TX_STARTED_NOTIFY_ENABLED
#define RTW_802154_TX_STARTED_NOTIFY_ENABLED 1
#endif

//TODO: not define this macro in nrf
#ifndef RTW_802154_IFS_ENABLED
#define RTW_802154_IFS_ENABLED 0
#endif

#endif // PLATFORM_AMEBAD2_H_
