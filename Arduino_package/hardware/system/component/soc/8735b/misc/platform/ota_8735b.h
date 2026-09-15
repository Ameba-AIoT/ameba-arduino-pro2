#ifndef OTA_8735B_H
#define OTA_8735B_H

#include <FreeRTOS.h>
#include <task.h>
#include <platform_stdlib.h>
#include <flash_api.h>
#include <lwipconf.h>

/************************Related setting****************************/
#define HTTP_OTA_UPDATE

#ifdef ARDUINO_SDK
#define HTTPS_OTA_UPDATE
#endif

#define EXT_STORAGE_OTA_UPDATE
#define HEAP_OTA_UPDATE

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

/****************Callback function types for OTA status reporting***/
/**
 * @brief Callback function type for reporting OTA upgrade progress
 * @param device_id: Device identifier (1=WiFi FW, 2=BT FW)
 * @param progress: Progress percentage (0-100)
 * @return void
 */
typedef void (*ota_status_callback_t)(uint8_t device_id, uint8_t progress);



/**************************************************************************/

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

#ifdef ARDUINO_SDK

#ifdef HTTPS_OTA_UPDATE
/*************************************************************************************************
** Function Name  : https_update_ota
** Description    : The process of OTA updating through https protocol
** Input          : host: server hostname or IP string
**                  port: server port (typically 443)
**                  resource: firmware file path on server
** Return         : 0: OTA success, -1: OTA failed
**************************************************************************************************/
int https_update_ota(char *host, int port, char *resource);
#endif

#endif

#ifdef EXT_STORAGE_OTA_UPDATE
/*************************************************************************************************
** Function Name  : ext_storage_update_ota
** Description    : The process of OTA updating through selection between SDCard or EMMC
** Input          : filename: target OTA file name. e.g. ota_is_realtek.bin
** Return         : 0: OTA success
**************************************************************************************************/
int ext_storage_update_ota(char *filename);
int ext_storage_update_boot_ota(char *filename);
#endif

#ifdef HEAP_OTA_UPDATE
/*************************************************************************************************
** Function Name  : heap_update_ota
** Description    : Performs OTA firmware update using binary data stored in heap memory.
**                  The binary OTA file is passed directly via buffer without relying on
**                  file system.
** Input          : buffer - Pointer to OTA binary data in heap
**                  length - Length of the binary data
** Return         : 0      - OTA success
**                  < 0    - OTA failure
**************************************************************************************************/
int heap_update_ota(uint8_t *buffer, uint32_t length);
int heap_update_boot_ota(uint8_t *buffer, uint32_t length);
int heap_update_nn_ota(uint8_t *buffer, uint32_t length);
int heap_update_isp_iq_ota(uint8_t *buffer, uint32_t length);
#endif

/***************Callback Management Functions***********************/
/**
 * @brief Register a callback for reporting OTA upgrade status
 * @param callback: Pointer to callback function, or NULL to unregister
 * @return 0 on success, -1 on failure
 */
int ota_register_status_callback(ota_status_callback_t callback);

/**
 * @brief Invoke the status callback to report upgrade progress
 * @param device_id: Device identifier (1=WiFi FW, 2=BT FW)
 * @param progress: Progress percentage (0-100)
 * @return void
 */
void ota_invoke_status_callback(uint8_t device_id, uint8_t progress);

/**
 * @brief Set an OTA cancellation request for the given device
 * @param device_id: Device identifier (1=WiFi FW, 2=BT FW)
 * @return 1 if upgrade should be cancelled, 0 otherwise
 */
uint8_t ota_set_cancel(uint8_t device_id);

/**
 * @brief Get the OTA cancellation status for the given device
 * @param device_id: Device identifier (1=WiFi FW, 2=BT FW)
 * @return 1 if upgrade should be cancelled, 0 otherwise
 */
uint8_t ota_get_cancel_status(uint8_t device_id);

/**
 * @brief Clear the OTA cancellation status for the given device
 * @param device_id: Device identifier (1=WiFi FW, 2=BT FW)
 */
void ota_clear_cancel_status(uint8_t device_id);

/**************************************************************************/

#endif