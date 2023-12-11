/**************************************************************************//**
 * @file     transport.h
 * @brief     Transport Functions Header File.
 *
 * @version  V1.00
 * @date     2020-11-25
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/


#ifndef _US_TRANSPORT_H_
#define _US_TRANSPORT_H_

/*
 * usb_stor_bulk_transfer_xxx() return codes, in order of severity
 */

#define USB_STOR_XFER_GOOD  0   /* good transfer                 */
#define USB_STOR_XFER_SHORT 1   /* transferred less than expected */
#define USB_STOR_XFER_STALLED   2   /* endpoint stalled              */
#define USB_STOR_XFER_LONG  3   /* device tried to send too much */
#define USB_STOR_XFER_ERROR 4   /* transfer died in the middle   */

/*
 * Transport return codes
 */

#define USB_STOR_TRANSPORT_GOOD    0   /* Transport good, command good     */
#define USB_STOR_TRANSPORT_FAILED  1   /* Transport good, command failed   */
#define USB_STOR_TRANSPORT_NO_SENSE 2  /* Command failed, no auto-sense    */
#define USB_STOR_TRANSPORT_ERROR   3   /* Transport bad (i.e. device dead) */


/*
 * CBI accept device specific command
 */
#define US_CBI_ADSC     0


#endif
