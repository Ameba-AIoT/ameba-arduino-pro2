#ifndef CONSOLE_XMODEM_H
#define CONSOLE_XMODEM_H

int console_xmodem_tx_buffer(uint8_t *buf, int len);
int console_xmodem_rx_buffer(uint8_t *buf, int len);
int console_xmodem_tx_file(char *file);
int console_xmodem_rx_file(char *file);

void console_dump_memory(uint8_t *buf, int len);

#endif
