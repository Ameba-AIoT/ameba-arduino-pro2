#ifndef __NN_GENAIVISION_H__
#define __NN_GENAIVISION_H__

#include "WiFi.h"
#include <ArduinoJson.h>
#include "Base64.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

class NNGenAIVision {
public:
    NNGenAIVision();
    ~NNGenAIVision();

    String openaivision(String key, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client);
    String geminivision(String key, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client);
    String llamavision(String key, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client);
};

#endif
