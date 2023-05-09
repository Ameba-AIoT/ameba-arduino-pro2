/*

 Example guide:
 */

#include <WiFi.h>
#include <PubSubClient.h>

char ssid[] = "Network_SSID";       // your network SSID (name)
char pass[] = "Password";           // your network password
int status = WL_IDLE_STATUS;        // Indicater of Wifi status

int keepAliveTimer = 30;

char mqttServer[]     = "test.mosquitto.org";
char clientId[]       = "amebaClient";
char publishTopic[]   = "outTopic";
char publishPayload[] = "hello world";
char subscribeTopic[] = "inTopic";

WiFiSSLClient wifiClient;
PubSubClient client(wifiClient);

/* Mosquitto Root CA can be download here:
 * https://test.mosquitto.org/
 */
char* rootCABuff = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIEAzCCAuugAwIBAgIUBY1hlCGvdj4NhBXkZ/uLUZNILAwwDQYJKoZIhvcNAQEL\n" \
"BQAwgZAxCzAJBgNVBAYTAkdCMRcwFQYDVQQIDA5Vbml0ZWQgS2luZ2RvbTEOMAwG\n" \
"A1UEBwwFRGVyYnkxEjAQBgNVBAoMCU1vc3F1aXR0bzELMAkGA1UECwwCQ0ExFjAU\n" \
"BgNVBAMMDW1vc3F1aXR0by5vcmcxHzAdBgkqhkiG9w0BCQEWEHJvZ2VyQGF0Y2hv\n" \
"by5vcmcwHhcNMjAwNjA5MTEwNjM5WhcNMzAwNjA3MTEwNjM5WjCBkDELMAkGA1UE\n" \
"BhMCR0IxFzAVBgNVBAgMDlVuaXRlZCBLaW5nZG9tMQ4wDAYDVQQHDAVEZXJieTES\n" \
"MBAGA1UECgwJTW9zcXVpdHRvMQswCQYDVQQLDAJDQTEWMBQGA1UEAwwNbW9zcXVp\n" \
"dHRvLm9yZzEfMB0GCSqGSIb3DQEJARYQcm9nZXJAYXRjaG9vLm9yZzCCASIwDQYJ\n" \
"KoZIhvcNAQEBBQADggEPADCCAQoCggEBAME0HKmIzfTOwkKLT3THHe+ObdizamPg\n" \
"UZmD64Tf3zJdNeYGYn4CEXbyP6fy3tWc8S2boW6dzrH8SdFf9uo320GJA9B7U1FW\n" \
"Te3xda/Lm3JFfaHjkWw7jBwcauQZjpGINHapHRlpiCZsquAthOgxW9SgDgYlGzEA\n" \
"s06pkEFiMw+qDfLo/sxFKB6vQlFekMeCymjLCbNwPJyqyhFmPWwio/PDMruBTzPH\n" \
"3cioBnrJWKXc3OjXdLGFJOfj7pP0j/dr2LH72eSvv3PQQFl90CZPFhrCUcRHSSxo\n" \
"E6yjGOdnz7f6PveLIB574kQORwt8ePn0yidrTC1ictikED3nHYhMUOUCAwEAAaNT\n" \
"MFEwHQYDVR0OBBYEFPVV6xBUFPiGKDyo5V3+Hbh4N9YSMB8GA1UdIwQYMBaAFPVV\n" \
"6xBUFPiGKDyo5V3+Hbh4N9YSMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQEL\n" \
"BQADggEBAGa9kS21N70ThM6/Hj9D7mbVxKLBjVWe2TPsGfbl3rEDfZ+OKRZ2j6AC\n" \
"6r7jb4TZO3dzF2p6dgbrlU71Y/4K0TdzIjRj3cQ3KSm41JvUQ0hZ/c04iGDg/xWf\n" \
"+pp58nfPAYwuerruPNWmlStWAXf0UTqRtg4hQDWBuUFDJTuWuuBvEXudz74eh/wK\n" \
"sMwfu1HFvjy5Z0iMDU8PUDepjVolOCue9ashlS4EB5IECdSR2TItnAIiIwimx839\n" \
"LdUdRudafMu5T5Xma182OC0/u/xRlEm+tvKGGmfFcN0piqVl8OrSPBgIlb+1IKJE\n" \
"m/XriWr/Cq4h/JfB7NTsezVslgkBaoU=\n" \
"-----END CERTIFICATE-----\n";

char* certificateBuff = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDpTCCAo2gAwIBAgIBADANBgkqhkiG9w0BAQsFADCBkDELMAkGA1UEBhMCR0Ix\n" \
"FzAVBgNVBAgMDlVuaXRlZCBLaW5nZG9tMQ4wDAYDVQQHDAVEZXJieTESMBAGA1UE\n" \
"CgwJTW9zcXVpdHRvMQswCQYDVQQLDAJDQTEWMBQGA1UEAwwNbW9zcXVpdHRvLm9y\n" \
"ZzEfMB0GCSqGSIb3DQEJARYQcm9nZXJAYXRjaG9vLm9yZzAeFw0yMzAxMTMwNTM3\n" \
"MzdaFw0yMzA0MTMwNTM3MzdaMH8xCzAJBgNVBAYTAlNHMQswCQYDVQQIDAJTRzES\n" \
"MBAGA1UEBwwJU2luZ2Fwb3JlMRQwEgYDVQQKDAtPV0wgQ29tcGFueTELMAkGA1UE\n" \
"CwwCU0QxDDAKBgNVBAMMA09XTDEeMBwGCSqGSIb3DQEJARYPb3dsOThAZ21haWwu\n" \
"Y29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAujUYtKub+pdRFhGP\n" \
"Q1KaKBGOgN1PmPR7fcRg5GasCfa9lI3ZPpNNqm1IAMMy3hIYgK+/Fgascpat0AMM\n" \
"Zc0WwHUkw+y8LwwyxuG2EXbCfEjrkvRl+qqtGdYZBD34cGPSyX94PqPAqRc2VSWT\n" \
"W7UiKc1QGElmTKGzEQ89sSnNN4o+QjM4lbQYw3ZR/VL3FVK26E6TRkcDHsnXU0on\n" \
"zNPki4nuJmNlOMEtfNV4dJg3PvntWSURm0BGbdj9y0Ks3fcpvdYWoqzj9ixXJc3V\n" \
"sNwlmd7TlsM1uUL5otud4PebEkF3/3biVoyl6trWmC0FdtT0KvnCMiMD/l9zOHoS\n" \
"CpzJfwIDAQABoxowGDAJBgNVHRMEAjAAMAsGA1UdDwQEAwIF4DANBgkqhkiG9w0B\n" \
"AQsFAAOCAQEAPFbIrl5PlYs7xP6oZ7CuSQqRUkFfmidAWW3hqR8g+gjAdaPmCSbi\n" \
"k6RmPVA1+/Mr0rnXHP6fC1RP/Q6T6UFayDrFI1DDB9LYGFxMh7jwpKJXkCYu3QPg\n" \
"32xKVPvf84FHnemcFa5+03ia1rS4fHbELhyo/glNVIG58NNBK9fRtfWT3oHzpKY9\n" \
"h8nTBnKOI4zoX7IwsyQNVJe9Lho/3QYmtOtE3unmDfMznWPe9G27nfJnqOZkHnFb\n" \
"+HFDBr/rF7wdCpQ2FXhsBwA69aiBuKvevL+puh+LWuv6N3MJWEn5VlwooHuJGOoB\n" \
"RXpxix8XjfCWXy7FFCDPc32aFRfjyXE2Hw==\n" \
"-----END CERTIFICATE-----\n";

char* privateKeyBuff = \
"-----BEGIN PRIVATE KEY-----\n" \
"MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC6NRi0q5v6l1EW\n" \
"EY9DUpooEY6A3U+Y9Ht9xGDkZqwJ9r2Ujdk+k02qbUgAwzLeEhiAr78WBqxylq3Q\n" \
"AwxlzRbAdSTD7LwvDDLG4bYRdsJ8SOuS9GX6qq0Z1hkEPfhwY9LJf3g+o8CpFzZV\n" \
"JZNbtSIpzVAYSWZMobMRDz2xKc03ij5CMziVtBjDdlH9UvcVUrboTpNGRwMeyddT\n" \
"SifM0+SLie4mY2U4wS181Xh0mDc++e1ZJRGbQEZt2P3LQqzd9ym91hairOP2LFcl\n" \
"zdWw3CWZ3tOWwzW5Qvmi253g95sSQXf/duJWjKXq2taYLQV21PQq+cIyIwP+X3M4\n" \
"ehIKnMl/AgMBAAECggEAEIjhej2Y2q4wHZkOkyhVFwTEFi5QwKDJDHhxMCbr1PCr\n" \
"kfLsnRFgfqc4kxTCQhTyRw8UFUUfcAdwRL3YjnuhLxLX4mv1o+nd4motjCxzBa1F\n" \
"+eUo3xLjzx0DWKyWEIjUsV7X0xwgYgN1KCdvh9+0OmkIWTe/VUOwjm2/iSlQl0NR\n" \
"DoQVp8RyckmxH5n9CwAkn+Kz9rSHleRdxpItWDMTHc6KIgZadhAWA4//5HGciEDm\n" \
"MzQAiqGIHc5Nhtk6Ib5Vpy9TZfF/RixhSsFxGrI71vmp+MGXOXQvsiruxH/EXLEL\n" \
"YRF+15Ag3zZO/BmwQVY6mANIGiSrEmGnr5jkY+RB5QKBgQDewtbeUB9rsDt/rRFW\n" \
"jTXJNhfpGqt0SdKykm1W6yI79cHzBPycvqwNTVadE6HRWpwHbRxQ/gwZNY9a306C\n" \
"dOvXF043zyQQcoSUToNAzG1jWinvx0BQz+3cZArnW9YO8galJbMQD7ccVNHQtCM6\n" \
"sreX2dIHzXR5AfQctzBL4xPQrQKBgQDV/fU14GYw8mg5IJaWZHkPZCkqmnDaUn46\n" \
"xexqBC+LSv3C7iz7F1KkdP/LMWMZM41HBod/uRF6yAz1o2ctsFqCbD6weJFUJ9dh\n" \
"v78SySTanDILOqsUdnTYsX3cT3vSLo16UNRX9bfCUXgF8FNqbUHPNVZDtiOzbsLr\n" \
"SkwVhZ+MWwKBgQDRroNE5hR9cHjBGK5+UxNy3/kn0ZPcNXUf49cJ/vDNkepLj8Ec\n" \
"5hnbt5W063rhLrI6B0mlL01CGXlkJ1imUdqBL43P2Kpw1OrZEwJXZ1X8NC3PZzWy\n" \
"G9chIgZleruGe+knYNIpZzGMeIa7NiUHJpzMUhtyfsGI+f7HXOQYOpo3TQKBgGMF\n" \
"TxCNM/x2T1AQCl6xQ2uh14LFUG9WON8NcyZjpXR5UQ+AkwPlePJsyWjHA6pHtpol\n" \
"JVIu2y3LoGOSJ053CorLd/7E68rbXMj4p3wT45/dIzMbBMtFPTCAgVMO3KcXr5Po\n" \
"Dzpck5mxhS6KVK8su4Uckzxl7gM7v6qNCMP0vy19AoGAPV18JClNFApl9r7bXgUO\n" \
"FK9eGnUwsKUOzKmDUyHFTA4+O9XSeuYDzqzbWh6gKGX0AZSC87dFBqtW+8e1W8FO\n" \
"NmBuquFrv1XQH2COQXctetEcilw6PxPdUy25W5RtL5liJ/5oVoRV8P42WxU3TFzq\n" \
"SuawFmNxTsDsKvCygQPETzU=\n" \
"-----END PRIVATE KEY-----\n";

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)(payload[i]));
    }
    Serial.println();
}

void reconnect() {
    // Loop until we're reconnected
    while (!(client.connected())) {
        Serial.println("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(clientId)) {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish(publishTopic, publishPayload);
            // ... and resubscribe
            client.subscribe(subscribeTopic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void setup() {
  Serial.begin(115200);

  while (status != WL_CONNECTED) {
    Serial.print("\r\n Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }

  client.setKeepAlive(keepAliveTimer);

  /*/
  wifiClient.setRootCA((unsigned char*)rootCABuff);
  wifiClient.setClientCertificate((unsigned char*)certificateBuff, (unsigned char*)privateKeyBuff);
  client.setServer(mqttServer, 8884);
  /*/
  wifiClient.setRootCA((unsigned char*)rootCABuff);
  client.setServer(mqttServer, 8883);
  
  client.setCallback(callback);

  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(1000);
}
