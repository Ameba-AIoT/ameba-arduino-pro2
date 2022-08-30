#ifndef OTA_8735B_H
#define OTA_8735B_H

#include <stdint.h>


/*******************Functions called by AT CMD**********************/
void atcmd_fwfs_ota_init(void);
/*******************************************************************/


/*************************************************************************************************
** Function Name  : update_ota_local
** Description    : Starting a thread of OTA updating through socket
** Input          : fw_name: The Firmware partition name
**                : ip     : The IP address of OTA server
**					port   : The Port of OTA server
** Return         : 0      : Task created OK
**					-1     : Task created failed
**************************************************************************************************/
int ota_update_fwfs(char *fw_name, char *ip, int port);


#endif
