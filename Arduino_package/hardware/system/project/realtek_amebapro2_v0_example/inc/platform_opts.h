/**
 ******************************************************************************
 *This file contains general configurations for ameba platform
 ******************************************************************************
*/

#ifndef __PLATFORM_OPTS_H__
#define __PLATFORM_OPTS_H__

/*For MP mode setting*/
#define SUPPORT_MP_MODE		1

/**
* User data for common flash usage
*/
#define USER_DATA_BASE          0xF00000
#define FAST_RECONNECT_DATA		USER_DATA_BASE // 4KB		Using flt and NAND block 120
#define BT_FTL_BKUP_ADDR		(USER_DATA_BASE + 0x01000) // 12KB
#define SECURE_STORAGE_BASS		(USER_DATA_BASE + 0x04000) // 4KB
#define FACE_FEATURE_DATA		(USER_DATA_BASE + 0x05000) /*!< FACE data begin address, default size used is 32KB (can be adjusted based on user requirement)*/
#define ISP_FW_LOCATION		    (USER_DATA_BASE + 0x0C000) //Store the ISP index
#define NOR_FLASH_FCS           (USER_DATA_BASE + 0x0D000) //Store the FCS data
#define TUNING_IQ_FW            (USER_DATA_BASE + 0x10000) //Store the Tuning IQ data(max size: 256K, 0xF10000~0xF50000)
#define NAND_APP_BASE			0x4000000 /*NAND FLASH FILESYSTEM begin address It need to alignment block size, the default is 512 BLOCK*/
#define FLASH_APP_BASE			0xE00000  //TODO: configure flash file system size here
#define NAND_FLASH_FCS          0x7080000 //900*128*1024

/**
 * For AT cmd Log service configurations
 */
#define SUPPORT_LOG_SERVICE	        1
#define SUPPORT_UART_LOG_SERVICE	0 // For UART Module AT command //
// For For AT cmd Log service //
#if SUPPORT_LOG_SERVICE
#define LOG_SERVICE_BUFLEN              100 //can't larger than UART_LOG_CMD_BUFLEN(127)
#define CONFIG_LOG_SERVICE_LOCK		    0
#define CONFIG_ATCMD_MP			        0   //support MP AT command
#define CONFIG_ISP						1   //support ISP AT command
#define CONFIG_TUNING					0   //support IQ Tuning
#define CONFIG_FTL						0   //support FTL AT command
#define USE_MODE                        1   //for test
// For UART Module AT command //
#elif SUPPORT_UART_LOG_SERVICE
#define CONFIG_OTA_UPDATE		        1
#define CONFIG_TRANSPORT				1
#define LOG_SERVICE_BUFLEN				1600
#define CONFIG_LOG_SERVICE_LOCK
#endif

/**
 * For FreeRTOS tickless configurations
 */
#define FREERTOS_PMU_TICKLESS_PLL_RESERVED   0   // In sleep mode, 0: close PLL clock, 1: reserve PLL clock

/******************************************************************************/

/**
 * For Wlan configurations
 */
#define CONFIG_WLAN		1
#if CONFIG_WLAN
#define CONFIG_LWIP_LAYER	1
#define CONFIG_INIT_NET		1 //init lwip layer when start up
#define CONFIG_ENABLE_AP_POLLING_CLIENT_ALIVE 0 // on or off AP POLLING CLIENT

//on/off relative commands in log service

// this two must be enabled when SUPPORT_UART_LOG_SERVICE is on
#define CONFIG_OTA_UPDATE	    0
#define CONFIG_TRANSPORT	    0//on or off the at command for transport socket

#define CONFIG_SSL_CLIENT	    0
#define CONFIG_BSD_TCP		    0//NOTE : Enable CONFIG_BSD_TCP will increase about 11KB code size
#define CONFIG_AIRKISS		    0//on or off tencent airkiss
#define CONFIG_UART_SOCKET	    0
#define CONFIG_JD_SMART		    0//on or off for jdsmart
#define CONFIG_JOYLINK		    0//on or off for jdsmart2.0
#define CONFIG_QQ_LINK		    0//on or off for qqlink
#define CONFIG_AIRKISS_CLOUD	0//on or off for weixin hardware cloud
#define CONFIG_UART_YMODEM	    0//support uart ymodem upgrade or not
#define CONFIG_ALINK		    0//on or off for alibaba alink

#define CONFIG_VIDEO_APPLICATION 1	// make lwip use large buffer

/* For WPS and P2P */
#define CONFIG_ENABLE_WPS		1
#define CONFIG_ENABLE_P2P		0
#if CONFIG_ENABLE_WPS
#define CONFIG_ENABLE_WPS_DISCOVERY	1
#endif
#if CONFIG_ENABLE_P2P
#define CONFIG_ENABLE_WPS_AP		1
#endif
#if (CONFIG_ENABLE_P2P && ((CONFIG_ENABLE_WPS_AP == 0) || (CONFIG_ENABLE_WPS == 0)))
#error "If CONFIG_ENABLE_P2P, need to define CONFIG_ENABLE_WPS_AP 1"
#endif

#if CONFIG_ENABLE_WPS
#define WPS_CONNECT_RETRY_COUNT		4
#define WPS_CONNECT_RETRY_INTERVAL	5000 // in ms
#endif


/* AUTO RECONNECT Setting */
#define AUTO_RECONNECT_COUNT	8
#define AUTO_RECONNECT_INTERVAL	5 // in sec

/* For SSL/TLS */
#define CONFIG_USE_POLARSSL     0 //polarssl is no longer suppported for AmebaZ2
#define CONFIG_USE_MBEDTLS      1
#if ((CONFIG_USE_POLARSSL == 0) && (CONFIG_USE_MBEDTLS == 0)) || ((CONFIG_USE_POLARSSL == 1) && (CONFIG_USE_MBEDTLS == 1))
#undef CONFIG_USE_POLARSSL
#define CONFIG_USE_POLARSSL 1
#undef CONFIG_USE_MBEDTLS
#define CONFIG_USE_MBEDTLS  0
#endif
#define CONFIG_SSL_CLIENT_PRIVATE_IN_TZ 0

/* For Simple Link */
#define CONFIG_INCLUDE_DPP_CONFIG		0
/*For fast dhcp*/
#define CONFIG_FAST_DHCP    1
/*For fast connect*/
#define ENABLE_FAST_CONNECT 1

#if defined(ENABLE_FAST_CONNECT) && ENABLE_FAST_CONNECT
#define ENABLE_FAST_CONNECT_NAND 1
#endif

#endif //end of #if CONFIG_WLAN
/*******************************************************************************/

/**
 * For Ethernet configurations
 */
#define CONFIG_ETHERNET     0
#if CONFIG_ETHERNET
//Choice the different interface for Ethernet
#define MII_INTERFACE       0
#define USB_INTERFACE       1
#define ETHERNET_INTERFACE  USB_INTERFACE //Default MII_INTERFACE
#define CONFIG_LWIP_LAYER	1
#define CONFIG_INIT_NET     1 //init lwip layer when start up

//on/off relative commands in log service
#define CONFIG_SSL_CLIENT	0
#define CONFIG_BSD_TCP		0//NOTE : Enable CONFIG_BSD_TCP will increase about 11KB code size

#endif


/* For LWIP configuration */
#ifdef ARDUINO_SDK
#ifdef CONFIG_LWIP_DHCP_COARSE_TIMER
#undef CONFIG_LWIP_DHCP_COARSE_TIMER
#define CONFIG_LWIP_DHCP_COARSE_TIMER 60
#endif
#endif
#define CONFIG_LWIP_TCP_RESUME        1

/****************** For EAP method example *******************/
//#define CONFIG_EXAMPLE_EAP	0

// on/off specified eap method
#define CONFIG_ENABLE_PEAP	1
#define CONFIG_ENABLE_TLS	1
#define CONFIG_ENABLE_TTLS	1

// optional feature: whether to verify the cert of radius server
#define ENABLE_EAP_SSL_VERIFY_SERVER	1

#if CONFIG_ENABLE_PEAP || CONFIG_ENABLE_TLS || CONFIG_ENABLE_TTLS
#define CONFIG_ENABLE_EAP
#endif

#if CONFIG_ENABLE_TLS
#define ENABLE_EAP_SSL_VERIFY_CLIENT	1
#else
#define ENABLE_EAP_SSL_VERIFY_CLIENT	0
#endif
/******************End of EAP configurations*******************/

/* FATFS definition */
#define CONFIG_FATFS_EN	  1
#if CONFIG_FATFS_EN
// fatfs supproted disk interface
#define FATFS_DISK_USB	  1
#define FATFS_DISK_SD 	  1
#define FATFS_DISK_FLASH  1
#define FATFS_DISK_RAM    1
#endif

#define CONFIG_FTL_EN 1

#endif
