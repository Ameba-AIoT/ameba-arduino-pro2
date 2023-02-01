#ifndef XMODEM_H
#define XMODEM_H

#define M_START		0x1
#define M_MIDDLE	0x2
#define M_FINAL		0x4

void xmodemSetInterface(int (*in_cb)(unsigned short), void (*out_cb)(int));
void xmodemSetInterface4(int (*tx_in_cb)(unsigned short), void (*tx_out_cb)(int), int (*rx_in_cb)(unsigned short), void (*rx_out_cb)(int));
int xmodemReceive(unsigned char *dest, int destsz, int mode, int *eot);
int xmodemTransmit(unsigned char *src, int srcsz, int mode);

#endif