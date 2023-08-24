#ifndef CONSOLE_AUTH_H
#define CONSOLE_AUTH_H

#include <stdint.h>
#include <lwip_netconf.h>

#define CONSOLE_AUTH_FAIL	0
#define CONSOLE_AUTH_BLOCK	0x1234
#define CONSOLE_AUTH_PASS	0x9455
#define CONSOLE_AUTH_MAGIC 0X12345678

#define AUTH_BUF_SIZE 128

char *console_auth_get_password(void);
void auth_key_handling(char c);
int auth_check(void);

#define CONSOLE_AUTH_STDOUT_RESTRICTED 1
#define CONSOLE_AUTH_FAIL_BLOCK 	   1
#define CONSOLE_AUTH 0
#define CONSOLE_AUTH_WARM_BOOT_RECORD 0

#endif
