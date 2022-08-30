#ifndef __DPP_H__
#define __DPP_H__

#include "wifi_structures.h"
#include "osdep_service.h"

/******************************************************
 *                    Macros
 ******************************************************/
//#define SSL_VERIFY_CLIENT_CA	//for ssl verify ca
#define DPP_ERROR		0
#define DPP_WARNING		1
#define DPP_INFO		2
#define DPP_DEBUG		3
#define DPP_CRYPTO_DEBUG	4
#define DPP_NONE		0xFF
#define DPP_DEBUG_LEVEL DPP_DEBUG

#if (DPP_DEBUG_LEVEL== DPP_NONE)
#define dpp_printf(level, fmt, arg...)
#define dpp_print_data(level, _TitleString, _HexData, _HexDataLen)
#else
#define dpp_printf(level, fmt, arg...)     \
do {\
	if (level <= DPP_DEBUG_LEVEL) {\
		if (level <= DPP_ERROR) {\
			printf("\r\nERROR: " fmt, ##arg);\
		} \
		else {\
			printf("\r\n"fmt, ##arg);\
		} \
	}\
}while(0)

#define dpp_print_data(level, _TitleString, _HexData, _HexDataLen)			\
do	{\
		if(level <= DPP_DEBUG_LEVEL){\
			{									\
				int __i;								\
				u8	*ptr = (u8 *)_HexData;				\
				printf(_TitleString "--------Len=%d\n\r", _HexDataLen);						\
				for( __i=0; __i<(int)_HexDataLen; __i++ )				\
				{								\
					printf("%02X%s", ptr[__i], (((__i + 1) % 4) == 0)?"  ":" ");	\
					if (((__i + 1) % 16) == 0)	printf("\n\r");			\
				}								\
				printf("\n\r");							\
			}\
		}\
}while(0)
#endif

#define AUTH_NO_STATUS					-1
#define AUTH_REQUEST_NO_BR				-2
#define AUTH_REQUEST_BR_ERROR			-3
#define AUTH_REQUEST_NO_BI				-4
#define AUTH_REQUEST_BI_ERROR			-5
#define AUTH_REQUEST_CHANNEL_ERROR		-6
#define AUTH_AES_SIV_ERROR				-7
#define IE_LENGTH_ERROR					-8
#define CAPABILITY_NOT_MATCH			-9

//DPP public Action frame type
#define DPP_AUTHENTICATION_REQUEST		0
#define DPP_AUTHENTICATION_RESPONSE		1
#define DPP_AUTHENTICATION_CONFIRM		2
#define DPP_PEER_DISCOVERY_REQUEST		5
#define DPP_PEER_DISCOVERY_RESPONSE		6
#define DPP_PKEX_EXCHANGE_REQUEST		7
#define DPP_PKEX_EXCHANGE_RESPONSE		8
#define DPP_PKEX_COMMOT_REVEAL_REQUEST	9
#define DPP_PKEX_COMMIT_REVEAL_RESPONSE	10

//DPP attribute ID definitions
#define DPP_ATTRIBUTE_ID_DPP_STATUS										0x1000
#define DPP_ATTRIBUTE_ID_INITIATOR_BOOTSTRAPPING_KEY_HASH				0x1001
#define DPP_ATTRIBUTE_ID_RESPONDER_BOOTSTRAPPING_KEY_HASH				0x1002
#define DPP_ATTRIBUTE_ID_INITIATOR_PROTOCOL_KEY							0x1003
#define DPP_ATTRIBUTE_ID_WRAPPED_DATA									0x1004
#define DPP_ATTRIBUTE_ID_INITIATOR_NONCE								0x1005
#define DPP_ATTRIBUTE_ID_INITIATOR_CAPABILITIES							0x1006
#define DPP_ATTRIBUTE_ID_RESPONDER_NONCE								0x1007
#define DPP_ATTRIBUTE_ID_RESPONDER_CAPABILITIES							0x1008
#define DPP_ATTRIBUTE_ID_RESPONDER_PROTOCOL_KEY							0x1009
#define DPP_ATTRIBUTE_ID_INITIATOR_AUTHENTICATING_TAG					0x100A
#define DPP_ATTRIBUTE_ID_RESPONDER_AUTHENTICATING_TAG					0x100B
#define DPP_ATTRIBUTE_ID_INITIATOR_DPP_CONFIGURATION_OBJECT				0x100C
#define DPP_ATTRIBUTE_ID_DPP_CONNECTOR									0x100D
#define DPP_ATTRIBUTE_ID_DPP_CONFIGURATION_ATTRIBUTES_OBJECT			0x100E
#define DPP_ATTRIBUTE_ID_BOOTSTRAPPING_KEY								0x100F
#define DPP_ATTRIBUTE_ID_HASH_OF_NK										0x1011
#define DPP_ATTRIBUTE_ID_FINITE_CYCLIC_GROUP							0x1012
#define DPP_ATTRIBUTE_ID_ENCRYPTED_KEY									0x1013
#define DPP_ATTRIBUTE_ID_ENROLLEE_NONCE									0x1014
#define DPP_ATTRIBUTE_ID_CODE_IDENTIFIER								0x1015
#define DPP_ATTRIBUTE_ID_TRANSACTION_ID									0x1016
#define DPP_ATTRIBUTE_ID_BOOTSTRAPPING_INFO								0x1017
#define DPP_ATTRIBUTE_ID_CHANNEL										0x1018

//DPP status and error codes
#define DPP_STATUS_OK					0	//No errors or abnormal behavior
#define DPP_STATUS_NOT_COMPATIBLE		1	//The DPP Initiator and Responder have incompatible capabilities
#define DPP_STATUS_AUTH_FAILURE			2	//Authentication failed
#define DPP_STATUS_BAD_CODE				3	//The code used in PKEX is bad
#define DPP_STATUS_BAD_GROUP			4	//An unsupported group was offered
#define DPP_STATUS_CONFIGURE_FAILURE	5	//Configurator refused to configure Enrollee
#define DPP_STATUS_RESPONSE_PENDING		6	//Responder will reply later
#define DPP_STATUS_INVALID_CONNECTOR	7	//Received Connector is invalid for some reason. The sending device needs to be reconfigured.
#define DPP_STATUS_NO_MATCH				8	//Received Connector is verified and valid but no matching Connector could be found. The receiving device needs to be reconfigured.

#define DPP_IEEE_HEADER			24
#define DPP_PUBLIC_ACTION_FRAME	8
#define DPP_AUTH_HEAD_LEN		(24 + DPP_PUBLIC_ACTION_FRAME)
#define DPP_AAD_BEGIN			(24 + 2)

#define DPP_BR_HASH_LEN						32
#define DPP_BI_HASH_LEN						32
#define DPP_MAX_BOOTSTRAPING_KEY_LEN		66 //64*8=512bits
#define DPP_MAX_ENCRYPTION_KEY_LEN			64
#define DPP_MAX_HASH_LEN					64
#define DPP_BOOTSTRAPING_KEY_LEN_LEVEL1		32 //32*8=256
#define DPP_BOOTSTARPING_KEY_LEN_LEVEL2		48 //48*8=384
#define DPP_MAX_NONCE_LEN					32
#define DPP_NONCE_LEN_LEVEL1	16
#define DPP_NONCE_LEN_LEVEL2	24
#define DPP_NONCE_LEN_LEVEL3	32
#define DPP_NONCE_SIZE			16

#define DPP_ASN_MAX_LEN			256

#define DPP_CATEGORY			0x04
#define DPP_PUBLIC_ACTION_FIELD	0x09
#define DPP_WFA_OUI_SIZE		0x03
#define DPP_WLAN_HDR_A3_LEN       24


#define MAX_SEND_NUM		5
#define SEND_TIME			3000
#define RETRY_COUNT              3

typedef enum {
	DPP_QR_SCAN = 0,
	DPP_PKEX,
} dpp_bootstrapping_method;

typedef enum {
	DPP_CONFIGURATOR_INITIATOR = 0,
	DPP_CONFIGURATOR_RESPONDER,
	DPP_ENROLLEE_INITIATOR,
	DPP_ENROLLEE_RESPONDER,
} dpp_role;

typedef enum {
	DPP_AUTH_SINGLE = 0,
	DPP_AUTH_MUTUAL,
} dpp_auth;

typedef enum {
	DPP_AP_PSK = 0,
	DPP_AP_DPP,
} dpp_ap;

typedef enum {
	DPP_INIT = 0,
	DPP_START,
	DPP_AUTH,
	DPP_CONFIG,
	DPP_CONFIG_SUCCESS,
	DPP_FINISH,
} dpp_state;

typedef enum {
	DPP_INIT_C = 0,
	DPP_START_C,
	DPP_BOOTSTRAPPED_C,
	DPP_AUTHENTICATING_C,
	DPP_AUTHENTICATED_C,
	DPP_FINISHED_C,
} dpp_state_config;

typedef struct {
	dpp_bootstrapping_method bootstrapping_method;
	dpp_role role;
	dpp_auth auth;
	dpp_ap ap_mode;
	u8 ecc_id;
} dpp_para;

typedef struct {
	u8 category;
	u8 action_field;
	u8 OUI[DPP_WFA_OUI_SIZE];
	u8 OUI_type;
	u8 crypto_suite;
	u8 dpp_frame_type;
} dpp_public_action_frame;

#define DPP_CONFIGURATION_REQUEST_FRAME_HEAD_LENGTH	15
typedef struct {
	u8 category;
	u8 action_field;
	u8 dialog_token;
	u8 advertisement_protocol_element[3];
	u8 advertisement_protocol_ID[7];
	u8 query_request_length[2];
} dpp_configuration_request_frame_head;

#define DPP_CONFIGURATION_RESPONSE_FRAME_HEAD_LENGTH	19
typedef struct {
	u8 category;
	u8 action_field;
	u8 dialog_token;
	u8 status_code[2];
	u8 GAS_comback_delay[2];
	u8 advertisement_protocol_element[3];
	u8 advertisement_protocol_ID[7];
	u8 query_response_length[2];
} dpp_configuration_response_frame_head;

typedef enum {
	DPP_AUTH_REQ = 0,
	DPP_AUTH_RSP,
	DPP_CONFIG_REQ,
	DPP_CONFIG_RSP,
} dpp_type;

typedef struct {
	u32 QR_code_set_channel;
	u32 channel;
	u8	Enrollee_QR_code_set_channel;
	u8	Enrollee_QR_code_set_mac;
	u8	bI_private[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u32 bI_key_len;
	u8	BI_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	BI_y[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	BI_hash_out[DPP_BR_HASH_LEN];
	u8	asn1_encode_out_base64[256];
	u32 asn1_encode_out_base64_len;
	u8	BR_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	BR_y[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	BR_hash_out[DPP_BR_HASH_LEN];
	u8	BR_get;
	u8	pI_private[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	PI_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	PI_y[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	PR_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	PR_y[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	I_nonce[DPP_MAX_NONCE_LEN];
	u8	R_nonce[DPP_MAX_NONCE_LEN];
	u8	E_nonce[DPP_MAX_NONCE_LEN];
	u8	I_capabilities;
	u8	R_capabilities;
	u8	secure_M_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	secure_N_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8	k1[DPP_MAX_ENCRYPTION_KEY_LEN];
	u8	k2[DPP_MAX_ENCRYPTION_KEY_LEN];
	u8	ke[DPP_MAX_ENCRYPTION_KEY_LEN];
	u8	R_auth[DPP_MAX_HASH_LEN];
	u8	I_auth[DPP_MAX_HASH_LEN];
} dpp_configurator_para;

typedef struct {
	u32 channel;
	u8 QR_code_set_channel;
	u8 bR_private[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u32 bR_key_len;
	u8 BR_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 BR_y[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 pR_private[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 PR_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 PR_y[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 R_nonce[DPP_MAX_NONCE_LEN];
	u8 R_capabilities;
	u8 PI_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 PI_y[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 channel_attribute[2];
	u8 I_nonce[DPP_MAX_NONCE_LEN];
	u8 I_capabilities;
	u8 E_nonce[DPP_MAX_NONCE_LEN];
	u8 secure_M_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 k1[DPP_MAX_ENCRYPTION_KEY_LEN];
	u8 k2[DPP_MAX_ENCRYPTION_KEY_LEN];
	u8 ke[DPP_MAX_ENCRYPTION_KEY_LEN];
	u8 R_auth[DPP_MAX_HASH_LEN];
	u8 I_auth[DPP_MAX_HASH_LEN];
	u8 asn1_encode_out_base64[256];
	u32 asn1_encode_out_base64_len;
	u8 BR_hash_out_put[DPP_BR_HASH_LEN];
	u8 BI_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 BI_y[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 BI_hash_out[DPP_BI_HASH_LEN];
	u8 BI_get;
} dpp_enrollee_para;

#define CONFIG_CONNECT_KID_SIZE 64
typedef struct {
	u8 kid[CONFIG_CONNECT_KID_SIZE];
	u8 sig_alg;
	u8 C_sign_key_x[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u8 C_sign_key_y[DPP_MAX_BOOTSTRAPING_KEY_LEN];
	u32 C_sign_ken_len;
} dpp_connect_para;

typedef struct _dpp_adapter {
	_sema connect_sema;
	dpp_state state;
	dpp_state_config state_config;
	int channel;
	u8 QR_code_set_mac;
	u8 mac[6];
	u8 bootstrap_mac[6];
	u8 password[65];
	rtw_network_info_t sta_info;
	rtw_network_info_t ap_info;
	u8 dpp_responder_status;
	dpp_para para_set;
	u8 start;
//for enrollee para
	dpp_enrollee_para dpp_enrollee;
	dpp_configurator_para	dpp_configuration;
	u8	private_key_len;
	u8	private_encryption_key_len;
	u8	ecc_key_len;
	u32 hash_alg_len;
	u32 nonce_len;
	u8	dpp_status;
	u8	dialog_token;
	dpp_connect_para dpp_connect;
	_timer auth_timer;
	u8  auth_count;
	_timer configuration_timer;
	u8 configuration_count;
} dpp_adapter;

#endif





