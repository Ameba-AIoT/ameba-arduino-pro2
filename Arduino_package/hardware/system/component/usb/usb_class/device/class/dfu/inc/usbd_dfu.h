#ifndef USBD_DFU_H
#define USBD_DFU_H
struct dfu_opts {
	int (*write)(unsigned char *buf, unsigned int size, int index);
	int (*checksum)(void *parm);//
	int (*reset)(void *parm);
};
int usbd_dfu_init(struct dfu_opts *dfu_cb);
void usbd_dfu_setup_serial_number(char *str);
#endif