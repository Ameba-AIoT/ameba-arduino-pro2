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

void RtwAlarmInit(void);

/**
 * Deinitialization of Alarm driver.
 *
 */
void RtwAlarmDeinit(void);

/**
 * Function for processing Alarm.
 *
 */
void RtwAlarmProcess(otInstance *aInstance);

/**
 * Function for geting current time in mircosecond.
 *
 */
uint64_t RtwAlarmGetCurrentTime(void);

/**
 * Function for getting raw counter value in RTC ticks.
 *
 */
uint64_t RtwAlarmGetRawCounter(void);

/**
 * Initialization of Random Number Generator.
 *
 */
void RtwRandomInit(void);

/**
 * Deinitialization of Random Number Generator.
 *
 */
void RtwRandomDeinit(void);

/**
 * Initialization of Logger driver.
 *
 */
void RtwLogInit(void);

/**
 * Deinitialization of Logger driver.
 *
 */
void RtwLogDeinit(void);

/**
 * Initialization of Misc module.
 *
 */
void RtwMiscInit(void);

/**
 * Deinitialization of Misc module.
 *
 */
void RtwMiscDeinit(void);

/**
 * Initialization of Radio driver.
 *
 */
void RtwRadioInit(void);

/**
 * Deinitialization of Radio driver.
 *
 */
void RtwRadioDeinit(void);

/**
 * Function for processing Radio.
 *
 */
void RtwRadioProcess(otInstance *aInstance);

/**
 * Function for clearing Radio driver pending events.
 *
 */
void RtwRadioClearPendingEvents(void);

/**
 * Initialization of hardware crypto engine.
 *
 */
void RtwCryptoInit(void);

/**
 * Deinitialization of hardware crypto engine.
 *
 */
void RtwCryptoDeinit(void);

/**
 * Function for erasing page in flash.
 *
 */
otError RtwFlashPageErase(uint32_t aAddress);

/**
 * Function for checking state of flash driver.
 *
 */
bool RtwFlashIsBusy(void);

/**
 * Function for writing data into flash.
 *
 */
otError RtwFlashWrite(uint32_t aAddress, const uint8_t *aData, uint32_t aSize);

/**
 * Initialization of temperature controller.
 *
 */
void RtwTempInit(void);

/**
 * Deinitialization of temperature controller.
 *
 */
void RtwTempDeinit(void);

/**
 * Function for processing temperature controller.
 *
 */
void RtwTempProcess(void);

/**
 * Function for measuring internal temperature.
 *
 * @return Temperature value measured.
 *
 */
int32_t RtwTempGet(void);


int8_t RtwGetChannelMaxTransmitPower(uint8_t aChannel);

/**
 * Callback function for region changed.
 *
 */
void RtwHandleRegionChanged(uint16_t aRegionCode);

#endif // PLATFORM_AMEBAD2_H_
