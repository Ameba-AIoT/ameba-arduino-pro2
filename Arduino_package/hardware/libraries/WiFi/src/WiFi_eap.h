#ifndef WiFi_eap_h
#define WiFi_eap_h

#include <Arduino.h>
#include <inttypes.h>

extern "C" {
#include "wifi_fast_connect.h"
}

class WiFi_eapClass {
public:
    WiFi_eapClass();
    WiFi_eapClass(char *method, char *ssid, char *identity, char *password, const unsigned char *client_cert, const unsigned char *client_key, const unsigned char *ca_cert);

    ~WiFi_eapClass();

    int begin();
    int begin(char *method, char *ssid, char *identity, char *password, const unsigned char *client_cert, const unsigned char *client_key, const unsigned char *ca_cert);

private:
    char *_wifi_eap_target_ssid;
    char *_wifi_eap_identity;
    char *_wifi_eap_password;
    const unsigned char *_wifi_eap_client_cert;
    const unsigned char *_wifi_eap_client_key;
    const unsigned char *_wifi_eap_ca_cert;
    char *_wifi_eap_methord = "tls";
};

extern WiFi_eapClass WiFi_eap;

#endif
