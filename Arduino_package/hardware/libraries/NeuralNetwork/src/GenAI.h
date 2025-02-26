#ifndef __NN_GENAIVISION_H__
#define __NN_GENAIVISION_H__

#include "WiFi.h"
#include <ArduinoJson.h>
#include "Base64.h"
#include "AmebaFatFS.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

class GenAI {
public:
    GenAI();
    ~GenAI();

    String openaivision(String key, String model, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client);
    String geminivision(String key, String model, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client);
    String llamavision(String key, String model, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client);
    String whisperaudio(String api_key, char* api_server, String api_path, String model, String filename, WiFiSSLClient client);
    void googletts(String filename_mp3, String message, String lang);

private:
    String urlencode(String str);
};

#endif
