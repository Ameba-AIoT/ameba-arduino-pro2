#ifndef USBD_NEW_DFU_H
#define USBD_NEW_DFU_H
#include "osdep_service.h"
#include "usbd.h"
struct dfu_status {
	u8				bStatus;
	u8				bwPollTimeout[3];
	u8				bState;
	u8				iString;
} __attribute__((packed));

#define USB_REQ_DFU_DETACH		0x00
#define USB_REQ_DFU_DNLOAD		0x01
#define USB_REQ_DFU_UPLOAD		0x02
#define USB_REQ_DFU_GETSTATUS	0x03
#define USB_REQ_DFU_CLRSTATUS	0x04
#define USB_REQ_DFU_GETSTATE	0x05
#define USB_REQ_DFU_ABORT		0x06

#define DFU_STATUS_OK				0x00
#define DFU_STATUS_errTARGET		0x01
#define DFU_STATUS_errFILE			0x02
#define DFU_STATUS_errWRITE			0x03
#define DFU_STATUS_errERASE			0x04
#define DFU_STATUS_errCHECK_ERASED	0x05
#define DFU_STATUS_errPROG			0x06
#define DFU_STATUS_errVERIFY		0x07
#define DFU_STATUS_errADDRESS		0x08
#define DFU_STATUS_errNOTDONE		0x09
#define DFU_STATUS_errFIRMWARE		0x0a
#define DFU_STATUS_errVENDOR		0x0b
#define DFU_STATUS_errUSBR			0x0c
#define DFU_STATUS_errPOR			0x0d
#define DFU_STATUS_errUNKNOWN		0x0e
#define DFU_STATUS_errSTALLEDPKT	0x0f

#define RET_STALL			-1
#define RET_ZLP				0
#define RET_STAT_LEN		6

#define DFU_POLL_TIMEOUT_MASK           (0xFFFFFFUL)

#define OTA_BUF (2*1024*1024)

enum dfu_state {
	DFU_STATE_appIDLE			= 0,
	DFU_STATE_appDETACH			= 1,
	DFU_STATE_dfuIDLE			= 2,
	DFU_STATE_dfuDNLOAD_SYNC	= 3,
	DFU_STATE_dfuDNBUSY			= 4,
	DFU_STATE_dfuDNLOAD_IDLE	= 5,
	DFU_STATE_dfuMANIFEST_SYNC	= 6,
	DFU_STATE_dfuMANIFEST		= 7,
	DFU_STATE_dfuMANIFEST_WAIT_RST	= 8,
	DFU_STATE_dfuUPLOAD_IDLE	= 9,
	DFU_STATE_dfuERROR			= 10,
};
typedef struct {
	u8 is_open;
	usb_dev_t *dev;
	/////
	enum dfu_state			dfu_state;
	unsigned int			dfu_status;
	/* Send/received block number is handy for data integrity check */
	int                     blk_seq_num;
	unsigned int            poll_timeout;
	unsigned char *ota_buf;
	unsigned int ota_size;
	unsigned int ota_send_index;
	unsigned int ota_send_size;
	_sema wakeup_sema;

	unsigned int ctrl_req;
	unsigned int ctrl_data_len;
	TaskHandle_t task_usb_dfu;
	////
} usbd_dfu_dev_t;

struct dfu_opts {
	int (*write)(unsigned char *buf, unsigned int size, int index);
	int (*checksum)(void *parm);//
	int (*reset)(void *parm);
};

int usbd_new_dfu_init(struct dfu_opts *dfu_cb);
void usbd_new_dfu_deinit(void);
#endif