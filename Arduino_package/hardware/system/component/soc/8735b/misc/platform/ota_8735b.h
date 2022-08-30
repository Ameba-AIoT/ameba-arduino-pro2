#ifndef OTA_8735B_H
#define OTA_8735B_H

#include <FreeRTOS.h>
#include <task.h>
#include <platform_stdlib.h>
#include <flash_api.h>
#include <lwipconf.h>

/************************Related setting****************************/
#define HTTP_OTA_UPDATE

#define NOR_BLOCK_SIZE		4096
#define NAND_BLOCK_SIZE		(64 * 2048)
#define HEADER_BAK_LEN		32

#define OTA_FW1		1
#define OTA_FW2 	2
#define OTA_BL_PRI 	3
#define OTA_ISP_IQ 	4
#define OTA_NN_MDL 	5
#define OTA_CER 	6

/*******************************************************************/


/****************Define the structures used*************************/
typedef struct {
	uint32_t	ip_addr;
	uint16_t	port;
} update_cfg_local_t;

typedef struct {
	uint32_t	status_code;
	uint32_t	header_len;
	uint8_t		*body;
	uint32_t	body_len;
	uint8_t		*header_bak;
	uint32_t	parse_status;
} http_response_result_t;

typedef union {
	uint32_t u;
	unsigned char c[4];
} _file_checksum;
/*******************************************************************/


/****************General functions used by ota update***************/
void *update_malloc(unsigned int size);
void update_free(void *buf);
void ota_platform_reset(void);
int update_ota_connect_server(update_cfg_local_t *cfg);
/*******************************************************************/


/*******************Functions called by AT CMD**********************/
void cmd_update(int argc, char **argv);
void cmd_ota_image(bool cmd);
/*******************************************************************/


/*************************************************************************************************
** Function Name  : update_ota_local
** Description    : Starting a thread of OTA updating through socket
** Input          : ip:The IP address of OTA server
**					port:The Port of OTA server
** Return         : 0: Task created OK
**					-1: Task created failed
**************************************************************************************************/
int update_ota_local(char *ip, int port);


#ifdef HTTP_OTA_UPDATE
int update_ota_http_connect_server(int server_socket, char *host, int port);

/*************************************************************************************************
** Function Name  : http_update_ota
** Description    : The process of OTA updating through http protocol
** Input          : cfg:struct update_cfg_local_t
** Return         : NULL
**************************************************************************************************/
int http_update_ota(char *host, int port, char *resource);
#endif

#endif
