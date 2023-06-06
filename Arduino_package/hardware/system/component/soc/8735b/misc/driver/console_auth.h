#ifndef CONSOLE_AUTH_H
#define CONSOLE_AUTH_H

#include <stdint.h>
#include <lwip_netconf.h>

#define CONSOLE_AUTH_FAIL	0
#define CONSOLE_AUTH_BLOCK	0x1234
#define CONSOLE_AUTH_PASS	0x9455

#define AUTH_BUF_SIZE 128

char *console_auth_get_password(void);
void auth_key_handling(char c);
int auth_check(void);

#define CONSOLE_AUTH 0

#endif
