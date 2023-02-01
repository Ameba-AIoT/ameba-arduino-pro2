/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright (c) 2017 - 2022 Vivante Corporation
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#ifndef _VIP_COMMON_H
#define _VIP_COMMON_H

#ifdef  __cplusplus
extern "C" {
#endif

/*!
 *\brief The VIP lite API for Convolution Neural Network application on CPU/MCU/DSP type of embedded environment.
 *\details This VIP lite APIs is not thread-safe if vpmdENABLE_MULTIPLE_TASK is set to 0,
           user must guarantee to call these APIs in a proper way.
           But defines vpmdENABLE_MULTIPLE_TASK 1, VIPLite can support multiple task(multiple thread/process).
           and it's thread-safe.
 *Memory allocation and file io functions used inside driver internal would depend on working enviroment.
 *\defgroup group_global Data Type Definitions and Global APIs
 *\brief Data type definition and global APIs that are used in the VIP lite
 *\defgroup group_buffer Buffer API
 *\brief The API to manage input/output buffers
 *\defgroup group_network  Network API
 *\brief The API to manage networks
 */

/*! \brief An 8-bit unsigned value.
 * \ingroup group_global
 * \version 1.0
 */
typedef unsigned char       vip_uint8_t;

/*! \brief An 16-bit unsigned value.
 * \ingroup group_global
 * \version 1.0
 */
typedef unsigned short      vip_uint16_t;

/*! \brief An 32-bit unsigned value.
 * \ingroup group_global
 * \version 1.0
 */
typedef unsigned int        vip_uint32_t;

/*! \brief An 64-bit unsigned value.
 * \ingroup group_global
 * \version 1.0
 */
typedef unsigned long long  vip_uint64_t;

/*! \brief An 8-bit signed value.
 * \ingroup group_global
 * \version 1.0
 */
typedef signed char         vip_int8_t;

/*! \brief An 16-bit signed value.
 * \ingroup group_global
 * \version 1.0
 */
typedef signed short        vip_int16_t;

/*! \brief An 32-bit signed value.
 * \ingroup group_global
 * \version 1.0
 */
typedef signed int          vip_int32_t;

/*! \brief An 64-bit signed value.
 * \ingroup group_global
 * \version 1.0
 */
typedef signed long long    vip_int64_t;

/*! \brief An 8 bit ASCII character.
 * \ingroup group_global
 * \version 1.0
 */
typedef char                vip_char_t;

/*! \brief An 32 bit float value.
 * \ingroup group_global
 * \version 1.0
 */
typedef float               vip_float_t;

/*! \brief Sets the standard enumeration type size to be a fixed quantity.
 * \ingroup group_global
 * \version 1.0
 */
typedef vip_int32_t         vip_enum;

/*! \brief a void pointer.
 * \ingroup group_global
 * \version 1.0
 */
typedef void               *vip_ptr;

/*! \brief A 64-bit float value (aka double).
 * \ingroup group_basic_features
 */
typedef double              vip_float64_t;

/*! \brief address type.
 * \ingroup group_global
 * \version 1.0
 */
typedef unsigned long long  vip_address_t;

/*! \brief A zero value for pointer
 *\ingroup group_global
 *\version 1.0
 */
#ifndef VIP_NULL
#define VIP_NULL 0
#endif

/***** Helper Macros. *****/
#define VIP_API

#define IN
#define OUT

/*! \brief A invalid value if a property is not avaialbe for the query.
 *\ingroup group_global
 *\version 1.0
 */
#define VIP_INVALID_VALUE       ~0UL

/*! \brief  A Boolean value.
 *\details  This allows 0 to be FALSE, as it is in C, and any non-zero to be TRUE.
 *\ingroup group_global
 *\version 1.0
 */
typedef enum _vip_bool_e {
	/*! \brief The "false" value. */
	vip_false_e = 0,
	/*! \brief The "true" value. */
	vip_true_e,
} vip_bool_e;

/*! \brief The enumeration of all status codes.
 * \ingroup group_global
 * \version 1.0
 */
typedef enum _vip_status {
	/*!< \brief Indicates the network is canceld */
	VIP_ERROR_CANCELED               = -15,
	/*!< \brief Indicates the lower bound of status codes in VIP lite. Used for bounds checks only */
	VIP_ERROR_RECOVERY              = -14,
	/*!< \brief Indicates the hardware is recovery done after hang*/
	VIP_ERROR_POWER_STOP            = -13,
	/*!< \brief Indicates the hardware is in power off status */
	VIP_ERROR_POWER_OFF             = -12,
	/*!< \brief Indicates the failure */
	VIP_ERROR_FAILURE               = -11,
	/*!< \brief Indicates the binary is not compatible with the current runtime hardware */
	VIP_ERROR_NETWORK_INCOMPATIBLE  = -10,
	/*!< \brief Indicates the network is not prepared so current function call can't go through */
	VIP_ERROR_NETWORK_NOT_PREPARED  = -9,
	/*!< \brief Indicates the network misses either input or output when running the network */
	VIP_ERROR_MISSING_INPUT_OUTPUT  = -8,
	/*!< \brief Indicates the network binary is invalid */
	VIP_ERROR_INVALID_NETWORK       = -7,
	/*!< \brief Indicates driver is running out of memory of system */
	VIP_ERROR_OUT_OF_MEMORY         = -6,
	/*!< \brief Indicates there is no enough resource */
	VIP_ERROR_OUT_OF_RESOURCE       = -5,
	/*!< \brief Indicates it's supported by driver implementation */
	VIP_ERROR_NOT_SUPPORTED         = -4,
	/*!< \brief Indicates some arguments are not valid */
	VIP_ERROR_INVALID_ARGUMENTS     = -3,
	/*!< \brief Indicates there are some IO related error */
	VIP_ERROR_IO                    = -2,
	/*!< \brief Indicates VIP timeout, could be VIP stuck somewhere */
	VIP_ERROR_TIMEOUT               = -1,
	/*!< \brief Indicates the execution is successfuly */
	VIP_SUCCESS                     =  0,
} vip_status_e;

#ifdef  __cplusplus
}
#endif

#endif
