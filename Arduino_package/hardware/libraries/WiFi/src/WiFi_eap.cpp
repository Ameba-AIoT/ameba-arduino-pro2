#include "WiFi_eap.h"

extern "C" {
extern char *eap_target_ssid;
extern char *eap_identity;
extern char *eap_password;
extern const unsigned char *eap_ca_cert;
extern const unsigned char *eap_client_cert;
extern const unsigned char *eap_client_key;
extern char *eap_client_key_pwd;
extern int eap_ca_cert_len;
extern int eap_client_cert_len;
extern int eap_client_key_len;

extern int eap_start(char *method);
extern void LwIP_Init(void);
extern int wifi_on(rtw_mode_t mode);
}

WiFi_eapClass::WiFi_eapClass()
{
}

WiFi_eapClass::WiFi_eapClass(char *method, char *ssid, char *identity, char *password, const unsigned char *client_cert, const unsigned char *client_key, const unsigned char *ca_cert)
{
    _wifi_eap_target_ssid = ssid;
    _wifi_eap_identity = identity;
    _wifi_eap_password = password;

    _wifi_eap_client_cert = client_cert;
    _wifi_eap_client_key = client_key;
    _wifi_eap_ca_cert = ca_cert;

    _wifi_eap_methord = method;
}

WiFi_eapClass::~WiFi_eapClass()
{
    _wifi_eap_target_ssid = (char *)"";
    _wifi_eap_identity = (char *)"";
    _wifi_eap_password = (char *)"";
    _wifi_eap_client_cert = (const unsigned char *)"";
    _wifi_eap_client_key = (const unsigned char *)"";
    _wifi_eap_ca_cert = (const unsigned char *)"";
    _wifi_eap_methord = (char *)"tls";
}

int WiFi_eapClass::begin()
{
    LwIP_Init();
    wifi_on(RTW_MODE_STA);

    wifi_fast_connect_enable(0);

    eap_target_ssid = _wifi_eap_target_ssid;
    eap_identity = _wifi_eap_identity;
    eap_password = _wifi_eap_password;

    eap_client_cert = _wifi_eap_client_cert;
    eap_client_key = _wifi_eap_client_key;
    eap_ca_cert = _wifi_eap_ca_cert;

    eap_client_cert_len = strlen((char *)eap_client_cert) + 1;
    eap_client_key_len = strlen((char *)eap_client_key) + 1;
    eap_ca_cert_len = strlen((char *)eap_ca_cert) + 1;

    // amb_ard_printf(ARD_LOG_INF, "\r\n %s \n", eap_target_ssid);
    // amb_ard_printf(ARD_LOG_INF, "\r\n %s \n", eap_identity);
    // amb_ard_printf(ARD_LOG_INF, "\r\n %s \n", eap_password);
    // amb_ard_printf(ARD_LOG_INF, "\r\n %s \n", eap_client_cert);
    // amb_ard_printf(ARD_LOG_INF, "\r\n %s \n", eap_client_key);
    // amb_ard_printf(ARD_LOG_INF, "\r\n %s \n", eap_ca_cert);

    if (strcmp(_wifi_eap_methord, (char *)"tls") == 0) {
        // tls must present client_cert, client_key
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] WiFi_eap.cpp eap_methord - tls\n");
        eap_start((char *)"tls");
    } else if (strcmp(_wifi_eap_methord, (char *)"peap") == 0) {
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] WiFi_eap.cpp eap_methord - peap\n");
        eap_start((char *)"peap");
    } else if (strcmp(_wifi_eap_methord, (char *)"ttls") == 0) {
        // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] WiFi_eap.cpp eap_methord - ttls\n");
        eap_start((char *)"ttls");
    } else {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] WiFi_eap.cpp Invalid _wifi_eap_methord\n");
        return -1;
    }

    return 0;
}

int WiFi_eapClass::begin(char *method, char *ssid, char *identity, char *password, const unsigned char *client_cert, const unsigned char *client_key, const unsigned char *ca_cert)
{
    _wifi_eap_methord = method;
    _wifi_eap_target_ssid = ssid;
    _wifi_eap_identity = identity;
    _wifi_eap_password = password;
    _wifi_eap_client_cert = client_cert;
    _wifi_eap_client_key = client_key;
    _wifi_eap_ca_cert = ca_cert;
    return begin();
}

WiFi_eapClass WiFi_eap;
