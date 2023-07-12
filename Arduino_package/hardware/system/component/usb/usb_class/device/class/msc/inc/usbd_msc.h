#ifndef USBD_MSC_H
#define USBD_MSC_H
#include "usbd_default.h"
#include "sd.h"

/* config usb MSC device buffer resource */
#define MSC_NBR_BUFHD	2 /* number of buffer header for bulk in/out data*/
#define MSC_BUFLEN	(20*512)/* Default size of buffer length. Minmun of 512 byte*/

struct msc_opts {
	int (*disk_init)(void);
	int (*disk_deinit)(void);
	int (*disk_getcapacity)(u32 *sectors);
	int (*disk_read)(u32 sector, u8 *buffer, u32 count);
	int (*disk_write)(u32 sector, const u8 *buffer, u32 count);
};
/*
* N_bh : number of buffer header
* Size_bh: buffer size per buffer
* disk_op:disk operation function pointer
*/
int usbd_msc_init(int N_bh, int Size_bh, struct msc_opts *disk_op);
void usbd_msc_deinit(void);

#endif
