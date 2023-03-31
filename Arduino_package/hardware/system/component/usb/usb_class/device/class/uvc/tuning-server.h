
#ifndef TUNING_SERVER_H
#define TUNING_SERVER_H /* TUNING_SERVER_H */


#include <stdio.h>
//#include <linux/types.h>
#include "rts_errno.h"

#define TCP_LISTEN_PORT			6666
#define TCP_BACKLOG			10
#define MAXEVENTS 16

#define MAX_DATA_LEN			0x80000
#define BUFFER_SIZE			(512 + MAX_DATA_LEN)
#define nojmp

#define print_dbg(fmt, arg...)			\
	RTS_DEBUG("%s: " fmt, __func__, ##arg)
#define print_info(fmt, arg...)			\
	RTS_INFO("%s: " fmt, __func__, ##arg)
#define print_err(fmt, arg...)			\
	RTS_ERR("%s: ERROR: " fmt, __func__, ##arg)
#define print_txt(fmt, arg...)			\
	RTS_OPT(fmt, ##arg)

#define cond_dbg(cond, cmd, fmt, arg...)	\
	if (cond) {				\
		print_dbg(fmt, ##arg);		\
		cmd;				\
	}					\

#define cond_err(cond, cmd, fmt, arg...)	\
	if (cond) {				\
		print_err(fmt, ##arg);		\
		cmd;				\
	}					\

#define MCU_RESET_REBOOT_MAGIC_ADDR 0x12345678

#ifndef MIN
#define MIN(a, b) (((a) < (b))?(a):(b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b))?(a):(b))
#endif

#define TUNING_IQ_MAX_SIZE (256 * 1024)
#define TUNING_IQ_MIN_SIZE (10  * 1024)

enum tuning_opcode {
	MEM_READ = 0,
	MEM_WRITE = 1,
	MCU_FW_BURN = 2,
	MCU_FW_RESET = 3,
	MCU_GET_RAW_HEADER = 4,
	MCU_GET_RAW_DATA = 5,
	MCU_ISP_CMD = 6,
	ISP_LDC = 7,
	ISP_TDNR = 8,
	ISP_DEHAZE = 9,
	IQ_TABLE = 10,
	FW_DUMP = 11,
	SRV_VERSION = 12,
	MCU_FW_VERSION = 13,
	SDK_VERSION = 14,
	MCU_IC_NAME = 15,
	ISP_ROLL_CMD = 16,
	ISP_MODE_CMD = 17,
	ISP_GET_FRAME = 18,
	ISP_STREAM_CTL = 19,
	ISP_VIDEO_CTL = 20,

	SENSOR_I2C_READ = 21,
	SENSOR_I2C_WRITE = 22,

	ISP_STATIS = 23,
	ISP_ALGO_PARAM = 24,
	ISP_IQ_TABLE = 25,

	ISP_STATIS_SIZE = 26,
	ISP_ALGO_PARAM_SIZE = 27,
	ISP_IQ_TABLE_SIZE = 28,
	ISP_IQ_FW_SIZE = 29,

	ISP_CTRL_READ = 30,
	ISP_CTRL_WRITE = 31,
	BAYER_MODE_CMD = 32,
	ERRCODE_READ = 33,
	CUSTOMIZED_SET_CMD = 34,
	CUSTOMIZED_GET_CMD = 35,
	CUSTOMIZED_GET_SIZE_CMD = 36,
};

#define UVC_MEM_READ 0xC2
#define UVC_MEM_WRITE 0x82
#define UVC_ISP_CTRL_READ 0xC3
#define UVC_ISP_CTRL_WRITE 0x83
#define UVC_MCU_GET_RAW_HEADER 0xF4
#define UVC_MCU_IC_NAME 0xF9
#define UVC_SRV_VERSION 0xFA

#define UVC_SENSOR_I2C_READ 0xCA
#define UVC_SENSOR_I2C_WRITE 0x8A

#define UVC_ISP_IQ_TABLE_WRITE 0xB5
#define UVC_ISP_IQ_TABLE_READ 0xF5
#define UVC_ISP_ALGO_PARAM_WRITE 0xB6
#define UVC_ISP_ALGO_PARAM_READ 0xF6
#define UVC_ISP_STATIS 0xF7
#define UVC_ISP_IQ_FW_WRITE 0xB8
#define UVC_ISP_IQ_FW_READ 0xF8
#define UVC_ISP_BAYER_FORMAT_SET 0xB9

#define UVC_ISP_IQ_TABLE_SIZE 0xF0
#define UVC_ISP_ALGO_PARAM_SIZE 0xF1
#define UVC_ISP_STATIS_SIZE 0xF2
#define UVC_ISP_IQ_FW_SIZE 0xF3
#define UVC_ERRCODE_READ 0xFB
#define UVC_CUSTOMIZED_SET_CMD 0xBC
#define UVC_CUSTOMIZED_GET_CMD 0xFC
#define UVC_CUSTOMIZED_GET_SIZE_CMD 0xFD

#define UVC_MCU_ISP_CMD 0xFF
//1. MEM_READ                        (bySubCmd : 0xC2, addr : 0xD100)
//2. MEM_WRITE                       (bySubCmd : 0x82, addr : 0xD100)
//3. SENSOR_I2C_READ             (bySubCmd : 0xCA, addr : 0x3908)
//4. SENSOR_I2C_WRITE           (bySubCmd : 0x8A, addr : 0x3908)
//5. MCU_GET_RAW_HEADER  (bySubCmd : 0xF4)
//6. ISP_IQ_TABLE(Write)           (bySubCmd : 0xB5)
//7. ISP_IQ_TABLE(Read)           (bySubCmd : 0xF5)
//8. ISP_ALGO_PARAM(Read)   (bySubCmd : 0xF6)
//9. ISP_STATIS(Read)                (bySubCmd : 0xF7)
//1. ISP_IQ_TABLE_LENGTH               (bySubCmd : 0xF0)
//2. ISP_ALGO_PARAM_LENGTH       (bySubCmd : 0xF1)
//3. ISP_STATIS_LENGTH                    (bySubCmd : 0xF2)

enum tuning_status {
	TUNING_FINISH,
	TUNING_FAILED,
};

struct tuning_cmd {
	uint16_t		opcode;
	uint16_t		status;
	uint32_t		addr;
	uint32_t		len;		/* only data */
	union {
		uint8_t	data[1];
		void	*ptr[1];
	};
} __attribute__((packed));

typedef unsigned char BYTE;
struct tuning_cmd_uvc {
	BYTE byCmd;
	BYTE bySubCmd;
	BYTE byarAddr[2];
	BYTE byarLen[2];
	union {
		BYTE byReserved[2];
		BYTE byarAddrH[2];
	};
} __attribute__((packed));



struct tuning_isp_cmd {
	uint16_t		cmdcode;
	uint8_t		index;
	uint8_t		len;
	uint16_t		param;
	uint16_t		addr;
} __attribute__((packed));

enum RTS_USBDEXT_LOG_TYPE {
	RTS_USBDEXT_LOG_IDX_STATUS = 0,
	RTS_USBDEXT_LOG_IDX_DATADUMP
};

#define RTS_USBDEXT_LOG_MASK_IDX_STATUS		(0x1 << RTS_USBDEXT_LOG_IDX_STATUS)
#define RTS_USBDEXT_LOG_MASK_IDX_DATADUMP	(0x1 << RTS_USBDEXT_LOG_IDX_DATADUMP)

enum RTS_TUNING_LOG_TYPE {
	RTS_TUNING_LOG_IDX_STATUS = 0,
	RTS_TUNING_LOG_IDX_XMEM,
	RTS_TUNING_LOG_IDX_TABLE_STA,
	RTS_TUNING_LOG_IDX_TABLE_PARA,
	RTS_TUNING_LOG_IDX_TABLE_IQ
};

#define RTS_TUNING_LOG_MASK_IDX_STATUS		(0x1 << RTS_TUNING_LOG_IDX_STATUS)
#define RTS_TUNING_LOG_MASK_IDX_XMEM		(0x1 << RTS_TUNING_LOG_IDX_XMEM)
#define RTS_TUNING_LOG_MASK_IDX_TABLE_STA	(0x1 << RTS_TUNING_LOG_IDX_TABLE_STA)
#define RTS_TUNING_LOG_MASK_IDX_TABLE_PARA	(0x1 << RTS_TUNING_LOG_IDX_TABLE_PARA)
#define RTS_TUNING_LOG_MASK_IDX_TABLE_IQ	(0x1 << RTS_TUNING_LOG_IDX_TABLE_IQ)


void tuning_init(void);
void tuning_deinit(void);
void usbd_ext_init(void);
void tuning_set_iq_heap(void *iq_heap);
void tuning_set_max_resolution(int width, int height);
void tuning_set_log_level(int level);
void usbd_set_log_level(int level);
void tuning_set_custom_cmd_cb(int set_addr_cb, int get_addr_cb, int get_size_addr_cb);
void tuning_set_custom_iq_addr(unsigned int iq_addr);


static inline int resp_size(struct tuning_cmd *cmd)
{
	int len = sizeof(*cmd);

	if (cmd->status == TUNING_FAILED) {
		return len;
	}

	if (cmd->opcode == MEM_READ) {
		return len + cmd->len;
	}

	return len;
}

#endif /* TUNING_SERVER_H */
