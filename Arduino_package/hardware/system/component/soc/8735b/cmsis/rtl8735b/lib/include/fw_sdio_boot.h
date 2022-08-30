/**************************************************************************//**
 * @file     fw_sdio_boot.h
 * @brief    Define the data structure for SDIO Boot functions.
 * @version  V1.00
 * @date     2018-05-30
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#ifndef _FW_SDIO_BOOT_H_
#define _FW_SDIO_BOOT_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#define SDIO_BOOT_TX_BD_NUM                 2
#define SDIO_BOOT_RX_PKT_NUM                3
#define SDIO_BOOT_RX_BD_NUM                 (SDIO_BOOT_RX_PKT_NUM*2)
#define SDIO_BOOT_TX_PKT_SIZE               2048
#define SDIO_BOOT_TX_BD_BUF_SIZE            ((((SDIO_BOOT_TX_PKT_SIZE + sizeof(sdiod_tx_desc_t) - 1) >> 6) + 1) << 6)

#if !defined(container_of)
#define container_of(ptr, type, member) \
            ((type *)((char *)(ptr)-(SIZE_T)(&((type *)0)->member)))
#endif

// CCPWM2 bit map definition for SDIO boot
#define SDIO_BOOT_INIT_DONE                         (BIT0)
#define SDIO_BOOT_MEM_WR_DONE                       (BIT1)
#define SDIO_BOOT_MEM_RD_DONE                       (BIT2)
#define SDIO_BOOT_MEM_ST_DONE                       (BIT3)
#define SDIO_BOOT_CPWM2_TOGGLE                      (BIT15)

/**
 * @brief  Defines the packet type of a SDIO device's packet
 */
enum sdio_bbot_pkt_type_e {
	SDIO_BOOT_CMD_MEMRD_RSP      = 0x50,    ///< response to memory block read command
	SDIO_BOOT_CMD_MEMRD          = 0x51,    ///< request to read a block of memory data
	SDIO_BOOT_CMD_MEMWR_RSP      = 0x52,    ///< response to memory write command
	SDIO_BOOT_CMD_MEMWR          = 0x53,    ///< request to write a block of memory
	SDIO_BOOT_CMD_MEMST_RSP      = 0x54,    ///< response to memory set command
	SDIO_BOOT_CMD_MEMST          = 0x55,    ///< request to set a block of memory with a value
	SDIO_BOOT_CMD_STARTED        = 0x60,    ///< indicate the program has jumped to the given function
	SDIO_BOOT_CMD_STARTUP        = 0x61     ///< request to jump to the start up function
};

#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)

/**
 * @brief  The data type of TX descriptor for Memory Write command.
 */
typedef struct sdiod_tx_desc_mw_s {
	// u4Byte 0
	uint32_t txpktsize: 16;      // bit[15:0]
	uint32_t offset: 8;         // bit[23:16], store the sizeof(SDIO_TX_DESC)
	uint32_t bus_agg_num: 8;    // bit[31:24], the bus aggregation number

	// u4Byte 1
	uint32_t type: 8;            // bit[7:0], the packet type
	uint32_t reply: 1;           // bit[8], request to send a reply message
	uint32_t rsvd0: 23;

	// u4Byte 2
	uint32_t start_addr;         // memory write start address

	// u4Byte 3
	uint32_t write_len: 16;      // bit[15:0], the length to write
	uint32_t is_raw_dat: 1;      // bit[16], is a raw data packet
	uint32_t rsvd2: 15;          // bit[31:17]

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_tx_desc_mw_t, *psdiod_tx_desc_mw_t;

/**
 * @brief  The data type of TX descriptor for Memory Read command.
 */
typedef struct sdiod_tx_desc_mr_s {
	// u4Byte 0
	uint32_t    txpktsize: 16;      // bit[15:0]
	uint32_t    offset: 8;          // bit[23:16], store the sizeof(SDIO_TX_DESC)
	uint32_t    bus_agg_num: 8;     // bit[31:24], the bus aggregation number

	// u4Byte 1
	uint32_t type: 8;            // bit[7:0], the packet type
	uint32_t rsvd0: 24;

	// u4Byte 2
	uint32_t    start_addr;         // memory write start address

	// u4Byte 3
	uint32_t read_len: 16;       // bit[15:0], the length to read
	uint32_t rsvd2: 16;          // bit[31:16]

	// u4Byte 4
	uint32_t    rsvd3;

	// u4Byte 5
	uint32_t    rsvd4;
} sdiod_tx_desc_mr_t, *psdiod_tx_desc_mr_t;

/**
 * @brief  The data type of TX descriptor for Memory Set command.
 */
typedef struct sdiod_tx_desc_ms_s {
	// u4Byte 0
	uint32_t    txpktsize: 16;      // bit[15:0]
	uint32_t    offset: 8;          // bit[23:16], store the sizeof(SDIO_TX_DESC)
	uint32_t    bus_agg_num: 8;     // bit[31:24], the bus aggregation number

	// u4Byte 1
	uint32_t type: 8;            // bit[7:0], the packet type
	uint32_t data: 8;            // bit[8:15], the value to be written to the memory
	uint32_t reply: 1;           // bit[16], request to send a reply message
	uint32_t rsvd0: 15;

	// u4Byte 2
	uint32_t    start_addr;         // memory write start address

	// u4Byte 3
	uint32_t write_len: 16;      // bit[15:0], the length to write
	uint32_t rsvd2: 16;          // bit[31:16]

	// u4Byte 4
	uint32_t    rsvd3;

	// u4Byte 5
	uint32_t    rsvd4;
} sdiod_tx_desc_ms_t, *psdiod_tx_desc_ms_t;

/**
 * @brief  The data type of TX descriptor for Jump to RAM Start command.
 */
typedef struct sdiod_tx_desc_js_s {
	// u4Byte 0
	uint32_t txpktsize: 16;      // bit[15:0]
	uint32_t offset: 8;         // bit[23:16], store the sizeof(SDIO_TX_DESC)
	uint32_t bus_agg_num: 8;    // bit[31:24], the bus aggregation number

	// u4Byte 1
	uint32_t type: 8;           // bit[7:0], the packet type
	uint32_t start_valid: 1;    // bit[8], is the start function address is valid
	uint32_t disconnect: 1;     // bit[9], disconnect (SDIO boot end)
	uint32_t rsvd0: 22;

	// u4Byte 2
	uint32_t start_fun;         // the pointer of the startup function

	// u4Byte 3
	uint32_t rsvd2;

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_tx_desc_js_t, *psdiod_tx_desc_js_t;

/**
 * @brief  The data type of RX descriptor for memory read command.
 */
typedef struct sdiod_rx_desc_mr_s {
	// u4Byte 0
	uint32_t pkt_len: 16;    // bit[15:0], the packet size
	uint32_t offset: 8;     // bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
	uint32_t rsvd0: 8;       // bit[31:24]

	// u4Byte 1
	uint32_t type: 8;        // bit[7:0], the type of this packet
	uint32_t rsvd1: 24;      // bit[31:8]

	// u4Byte 2
	uint32_t start_addr;

	// u4Byte 3
	uint32_t rsvd2;

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_rx_desc_mr_t, *psdiod_rx_desc_mr_t;

/**
 * @brief  The data type of RX descriptor for memory write reply command.
 */
typedef struct sdiod_rx_desc_mw_s {
	// u4Byte 0
	uint32_t pkt_len: 16;    // bit[15:0], the packet size
	uint32_t offset: 8;     // bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
	uint32_t rsvd0: 8;       // bit[31:24]

	// u4Byte 1
	uint32_t type: 8;        // bit[7:0], the type of this packet
	uint32_t rsvd1: 24;      // bit[31:8]

	// u4Byte 2
	uint32_t start_addr;

	// u4Byte 3
	uint32_t write_len: 16;  // bit[15:0], the type of this packet
	uint32_t result: 8;     // bit[23:16], the result of memory write command
	uint32_t rsvd2: 8;      // bit[31:24]

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_rx_desc_mw_t, *psdiod_rx_desc_mw_t;

/**
 * @brief  The data type of RX descriptor for memory set reply command.
 */
typedef struct sdiod_rx_desc_ms_s {
	// u4Byte 0
	uint32_t pkt_len: 16;    // bit[15:0], the packet size
	uint32_t offset: 8;     // bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
	uint32_t rsvd0: 8;       // bit[31:24]

	// u4Byte 1
	uint32_t type: 8;        // bit[7:0], the type of this packet
	uint32_t rsvd1: 24;      // bit[31:8]

	// u4Byte 2
	uint32_t start_addr;

	// u4Byte 3
	uint32_t write_len: 16;  // bit[15:0], the type of this packet
	uint32_t result: 8;     // bit[23:16], the result of memory write command
	uint32_t rsvd2: 8;      // bit[31:24]

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_rx_desc_ms_t, *psdiod_rx_desc_ms_t;

#else

/**
 * @brief  The data type of TX descriptor for Memory Write command.
 */
typedef struct sdiod_tx_desc_mw_s {
	// u4Byte 0
	uint32_t bus_agg_num: 8;     // bit[31:24], the bus aggregation number
	uint32_t offset: 8;          // bit[23:16], store the sizeof(SDIO_TX_DESC)
	uint32_t txpktsize: 16;      // bit[15:0]

	// u4Byte 1
	uint32_t rsvd0: 23;
	uint32_t reply: 1;           // bit[8], request to send a reply message
	uint32_t type: 8;            // bit[7:0], the packet type

	// u4Byte 2
	uint32_t start_addr;         // memory write start address

	// u4Byte 3
	uint32_t rsvd2: 15;          // bit[31:17]
	uint32_t is_raw_dat: 1;      // bit[16], is a raw data packet
	uint32_t write_len: 16;      // bit[15:0], the length to write

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_tx_desc_mw_t, *psdiod_tx_desc_mw_t;

/**
 * @brief  The data type of TX descriptor for Memory Read command.
 */
typedef struct sdiod_tx_desc_mr_s {
	// u4Byte 0
	uint32_t bus_agg_num: 8;     // bit[31:24], the bus aggregation number
	uint32_t offset: 8;          // bit[23:16], store the sizeof(SDIO_TX_DESC)
	uint32_t txpktsize: 16;      // bit[15:0]

	// u4Byte 1
	uint32_t rsvd0: 24;
	uint32_t type: 8;            // bit[7:0], the packet type

	// u4Byte 2
	uint32_t start_addr;         // memory write start address

	// u4Byte 3
	uint32_t rsvd2: 16;          // bit[31:16]
	uint32_t read_len: 16;       // bit[15:0], the length to read

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_tx_desc_mr_t, *psdiod_tx_desc_mr_t;

/**
 * @brief  The data type of TX descriptor for Memory Set command.
 */
typedef struct sdiod_tx_desc_ms_s {
	// u4Byte 0
	uint32_t bus_agg_num: 8;     // bit[31:24], the bus aggregation number
	uint32_t offset: 8;          // bit[23:16], store the sizeof(SDIO_TX_DESC)
	uint32_t txpktsize: 16;      // bit[15:0]

	// u4Byte 1
	uint32_t rsvd0: 15;
	uint32_t reply: 1;           // bit[16], request to send a reply message
	uint32_t data: 8;            // bit[8:15], the value to be written to the memory
	uint32_t type: 8;            // bit[7:0], the packet type

	// u4Byte 2
	uint32_t start_addr;         // memory write start address

	// u4Byte 3
	uint32_t rsvd2: 16;          // bit[31:16]
	uint32_t write_len: 16;      // bit[15:0], the length to write

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_tx_desc_ms_t, *psdiod_tx_desc_ms_t;

/**
 * @brief  The data type of TX descriptor for Jump to RAM Start command.
 */
typedef struct sdiod_tx_desc_js_s {
	// u4Byte 0
	uint32_t bus_agg_num: 8;     // bit[31:24], the bus aggregation number
	uint32_t offset: 8;          // bit[23:16], store the sizeof(SDIO_TX_DESC)
	uint32_t txpktsize: 16;      // bit[15:0]

	// u4Byte 1
	uint32_t rsvd0: 22;
	uint32_t disconnect: 1;     // bit[9], disconnect (SDIO boot end)
	uint32_t start_valid: 1;    // bit[8], is the start function address is valid
	uint32_t type: 8;           // bit[7:0], the packet type

	// u4Byte 2
	uint32_t start_fun;         // the pointer of the startup function

	// u4Byte 3
	uint32_t rsvd2;

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_tx_desc_js_t, *psdiod_tx_desc_js_t;

/**
 * @brief  The data type of RX descriptor for memory read command.
 */
typedef struct sdiod_rx_desc_mr_s {
	// u4Byte 0
	uint32_t rsvd0: 8;       // bit[31:24]
	uint32_t offset: 8;     // bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
	uint32_t pkt_len: 16;    // bit[15:0], the packet size

	// u4Byte 1
	uint32_t rsvd1: 24;      // bit[31:8]
	uint32_t type: 8;        // bit[7:0], the type of this packet

	// u4Byte 2
	uint32_t start_addr;

	// u4Byte 3
	uint32_t rsvd2;

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_rx_desc_mr_t, *psdiod_rx_desc_mr_t;

/**
 * @brief  The data type of RX descriptor for memory write reply command.
 */
typedef struct sdiod_rx_desc_mw_s {
	// u4Byte 0
	uint32_t rsvd0: 8;       // bit[31:24]
	uint32_t offset: 8;     // bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
	uint32_t pkt_len: 16;    // bit[15:0], the packet size

	// u4Byte 1
	uint32_t rsvd1: 24;      // bit[31:8]
	uint32_t type: 8;        // bit[7:0], the type of this packet

	// u4Byte 2
	uint32_t start_addr;

	// u4Byte 3
	uint32_t rsvd2: 8;      // bit[31:24]
	uint32_t result: 8;     // bit[23:16], the result of memory write command
	uint32_t write_len: 16;  // bit[15:0], the type of this packet

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_rx_desc_mw_t, *psdiod_rx_desc_mw_t;

/**
 * @brief  The data type of RX descriptor for memory set reply command.
 */
typedef struct sdiod_rx_desc_ms_s {
	// u4Byte 0
	uint32_t rsvd0: 8;       // bit[31:24]
	uint32_t offset: 8;     // bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
	uint32_t pkt_len: 16;    // bit[15:0], the packet size

	// u4Byte 1
	uint32_t rsvd1: 24;      // bit[31:8]
	uint32_t type: 8;        // bit[7:0], the type of this packet

	// u4Byte 2
	uint32_t start_addr;

	// u4Byte 3
	uint32_t rsvd2: 8;      // bit[31:24]
	uint32_t result: 8;     // bit[23:16], the result of memory write command
	uint32_t write_len: 16;  // bit[15:0], the type of this packet

	// u4Byte 4
	uint32_t rsvd3;

	// u4Byte 5
	uint32_t rsvd4;
} sdiod_rx_desc_ms_t, *psdiod_rx_desc_ms_t;

#endif

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _FW_SDIO_BOOT_H_"


