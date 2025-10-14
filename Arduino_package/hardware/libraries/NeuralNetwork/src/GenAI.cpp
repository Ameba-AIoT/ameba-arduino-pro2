#include "GenAI.h"
#include <ArduinoJson.h>
#include "Base64.h"

GenAI::GenAI()
{
}

GenAI::~GenAI()
{
}

// Server: openAI Platform
String GenAI::openaivision(String key, String model, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client)
{
    const char *myDomain = "api.openai.com";
    String getResponse = "", Feedback = "";
    Serial.println("Connect to " + String(myDomain));
    if (client.connect(myDomain, 443)) {
        Serial.println("Connection successful");

        uint8_t *fbBuf = (uint8_t *)img_addr;
        uint32_t fbLen = img_len;

        char *input = (char *)fbBuf;
        char output[base64_enc_len(3)];
        String imageFile = "data:image/jpeg;base64,";
        for (uint32_t i = 0; i < fbLen; i++) {
            base64_encode(output, (input++), 3);
            if (i % 3 == 0) {
                imageFile += String(output);
            }
        }
        String Data = "{\"model\": \"" + model + "\", \"messages\": [{\"role\": \"user\",\"content\": [{ \"type\": \"text\", \"text\": \"" + message + "\"},{\"type\": \"image_url\", \"image_url\": {\"url\": \"" + imageFile + "\"}}]}]}";

        client.println("POST /v1/chat/completions HTTP/1.1");
        client.println("Host: " + String(myDomain));
        client.println("Authorization: Bearer " + key);
        client.println("Content-Type: application/json; charset=utf-8");
        client.println("Content-Length: " + String(Data.length()));
        client.println("Connection: close");
        client.println();

        unsigned int Index;
        for (Index = 0; Index < Data.length(); Index = Index + 1024) {
            client.print(Data.substring(Index, Index + 1024));
        }

        uint32_t waitTime = 10000;
        uint32_t startTime = millis();
        boolean state = false;
        boolean markState = false;
        while ((startTime + waitTime) > millis()) {
            Serial.print(".");
            delay(100);
            while (client.available()) {
                char c = client.read();
                if (String(c) == "{") {
                    markState = true;
                }
                if (state == true && markState == true) {
                    Feedback += String(c);
                }
                if (c == '\n') {
                    if (getResponse.length() == 0) {
                        state = true;
                    }
                    getResponse = "";
                } else if (c != '\r') {
                    getResponse += String(c);
                }
                startTime = millis();
            }
            if (Feedback.length() > 0) {
                break;
            }
        }
        Serial.println();
        client.stop();

        JsonObject obj;
        JsonDocument doc;
        deserializeJson(doc, Feedback);
        obj = doc.as<JsonObject>();
        getResponse = obj["choices"][0]["message"]["content"].as<String>();
        if (getResponse == "null") {
            getResponse = obj["error"]["message"].as<String>();
        }
    } else {
        getResponse = "Connected to " + String(myDomain) + " failed.";
    }
    Serial.println("Response from GPT:");
    Serial.println(getResponse);
    return getResponse;
}

// Server: Google AI Studio
String GenAI::geminivision(String key, String model, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client)
{
    const char *myDomain = "generativelanguage.googleapis.com";
    String getResponse = "", Feedback = "";
    Serial.println("Connect to " + String(myDomain));
    if (client.connect(myDomain, 443)) {
        Serial.println("Connection successful");

        uint8_t *fbBuf = (uint8_t *)img_addr;
        uint32_t fbLen = img_len;
        char *input = (char *)fbBuf;
        char output[base64_enc_len(3)];
        String imageFile = "";
        for (uint32_t i = 0; i < fbLen; i++) {
            base64_encode(output, (input++), 3);
            if (i % 3 == 0) {
                imageFile += String(output);
            }
        }
        String Data = "{\"contents\": [{\"parts\": [{\"text\": \"" + message + "\"}, {\"inline_data\": {\"mime_type\":\"image/jpeg\",\"data\":\"" + imageFile + "\"}}]}]}";
        // String Data = "{\"contents\": [{\"parts\": [{\"text\": \""+message+"\"}]}]}";

        client.println("POST /v1beta/models/" + model + ":generateContent?key=" + key + " HTTP/1.1");
        client.println("Host: " + String(myDomain));
        client.println("Content-Type: application/json; charset=utf-8");
        client.println("Content-Length: " + String(Data.length()));
        client.println("Connection: close");
        client.println();

        unsigned int Index;
        for (Index = 0; Index < Data.length(); Index = Index + 1024) {
            client.print(Data.substring(Index, Index + 1024));
        }

        uint32_t waitTime = 10000;
        uint32_t startTime = millis();
        boolean state = false;
        boolean markState = false;
        while ((startTime + waitTime) > millis()) {
            Serial.print(".");
            delay(100);
            while (client.available()) {
                char c = client.read();
                if (String(c) == "{") {
                    markState = true;
                }
                if (state == true && markState == true) {
                    Feedback += String(c);
                }
                if (c == '\n') {
                    if (getResponse.length() == 0) {
                        state = true;
                    }
                    getResponse = "";
                } else if (c != '\r') {
                    getResponse += String(c);
                }
                startTime = millis();
            }
            if (Feedback.length() > 0) {
                break;
            }
        }
        Serial.println();
        client.stop();

        JsonObject obj;
        JsonDocument doc;
        deserializeJson(doc, Feedback);
        obj = doc.as<JsonObject>();
        getResponse = obj["candidates"][0]["content"]["parts"][0]["text"].as<String>();
        if (getResponse == "null") {
            getResponse = obj["error"]["message"].as<String>();
        }
    } else {
        getResponse = "Connected to " + String(myDomain) + " failed.";
    }
    Serial.println("Response from Gemini:");
    Serial.println(getResponse);
    return getResponse;
}

// Server: groq
String GenAI::llamavision(String key, String model, String message, uint32_t img_addr, uint32_t img_len, WiFiSSLClient client)
{
    const char *myDomain = "api.groq.com";
    String getResponse = "", Feedback = "";
    Serial.println("Connect to " + String(myDomain));
    if (client.connect(myDomain, 443)) {
        Serial.println("Connection successful");

        uint8_t *fbBuf = (uint8_t *)img_addr;
        uint32_t fbLen = img_len;

        char *input = (char *)fbBuf;
        char output[base64_enc_len(3)];
        String imageFile = "data:image/jpeg;base64,";
        for (uint32_t i = 0; i < fbLen; i++) {
            base64_encode(output, (input++), 3);
            if (i % 3 == 0) {
                imageFile += String(output);
            }
        }
        String Data = "{\"model\": \"" + model + "\", \"messages\": [{\"role\": \"user\",\"content\": [{ \"type\": \"text\", \"text\": \"" + message + "\"},{\"type\": \"image_url\", \"image_url\": {\"url\": \"" + imageFile + "\"}}]}]}";

        client.println("POST /openai/v1/chat/completions HTTP/1.1");
        client.println("Host: " + String(myDomain));
        client.println("Authorization: Bearer " + key);
        client.println("Content-Type: application/json; charset=utf-8");
        client.println("Content-Length: " + String(Data.length()));
        client.println("Connection: close");
        client.println();

        unsigned int Index;
        for (Index = 0; Index < Data.length(); Index = Index + 1024) {
            client.print(Data.substring(Index, Index + 1024));
        }

        uint32_t waitTime = 10000;
        uint32_t startTime = millis();
        boolean state = false;
        boolean markState = false;
        while ((startTime + waitTime) > millis()) {
            Serial.print(".");
            delay(100);
            while (client.available()) {
                char c = client.read();
                if (String(c) == "{") {
                    markState = true;
                }
                if (state == true && markState == true) {
                    Feedback += String(c);
                }
                if (c == '\n') {
                    if (getResponse.length() == 0) {
                        state = true;
                    }
                    getResponse = "";
                } else if (c != '\r') {
                    getResponse += String(c);
                }
                startTime = millis();
            }
            if (Feedback.length() > 0) {
                break;
            }
        }
        Serial.println();
        client.stop();

        JsonObject obj;
        JsonDocument doc;
        deserializeJson(doc, Feedback);
        obj = doc.as<JsonObject>();
        getResponse = obj["choices"][0]["message"]["content"].as<String>();
        if (getResponse == "null") {
            getResponse = obj["error"]["message"].as<String>();
        }
    } else {
        getResponse = "Connected to " + String(myDomain) + " failed.";
    }
    Serial.println("Response from Llama:");
    Serial.println(getResponse);
    return getResponse;
}

String GenAI::whisperaudio(String api_key, char *api_server, String api_path, String model, String filename, WiFiSSLClient client)
{
    char buf[512];
    char *p;
    AmebaFatFS fs;
    String filepath;
    File file;

    fs.begin();
    memset(buf, 0, sizeof(buf));
    fs.readDir(fs.getRootPath(), buf, sizeof(buf));
    filepath = String(fs.getRootPath()) + filename;
    p = buf;
    while (strlen(p) > 0) {
        /* list out file name image will be saved as FILENAME */
        if (strstr(p, filename.c_str()) != NULL) {
            Serial.println("[INFO] Found '" + filename + "' in the string.");
            Serial.println("[INFO] Processing file...");
        } else {
            // Serial.println("Substring 'image.jpg' not found in the
            // string.");
        }
        p += strlen(p) + 1;
    }
    uint8_t *fileinput;
    file = fs.open(filepath);
    unsigned int fileSize = file.size();
    fileinput = (uint8_t *)malloc(fileSize + 1);
    file.read(fileinput, fileSize);
    fileinput[fileSize] = '\0';
    file.close();

    Serial.println("Connect to " + String(api_server));
    if (client.connect(api_server, 443)) {
        Serial.println("Connection successful");

        String head = "--Taiwan\r\nContent-Disposition: form-data; name=\"model\"\r\n\r\n" + model + "\r\n--Taiwan\r\nContent-Disposition: form-data; name=\"response_format\"\r\n\r\nverbose_json\r\n--Taiwan\r\nContent-Disposition: form-data; name=\"file\"; filename=\"" + filename + "\"\r\nContent-Type: video/mp4\r\n\r\n";
        Serial.println(head);
        String tail = "\r\n--Taiwan--\r\n";

        uint16_t totalLen = head.length() + fileSize + tail.length();

        client.println("POST " + api_path + " HTTP/1.1");
        client.println("Connection: keep-alive");
        client.println("Host: " + String(api_server));
        client.println("Authorization: Bearer " + api_key);
        client.println("Content-Length: " + String(totalLen));
        client.println("Content-Type: multipart/form-data; boundary=Taiwan");
        client.println();
        client.print(head);

        for (size_t n = 0; n < fileSize; n = n + 1024) {
            if (n + 1024 < fileSize) {
                client.write(fileinput, 1024);
                fileinput += 1024;
            } else if (fileSize % 1024 > 0) {
                size_t remainder = fileSize % 1024;
                client.write(fileinput, remainder);
            }
        }

        client.print(tail);

        String getResponse = "", Feedback = "";
        uint32_t waitTime = 20000;    // timeout 20 seconds
        uint32_t startTime = millis();
        boolean state = false;

        while ((startTime + waitTime) > millis()) {
            Serial.print(".");
            delay(100);
            while (client.available()) {
                char c = client.read();
                if (state == true) {
                    Feedback += String(c);
                }
                if (c == '\n') {
                    if (getResponse.length() == 0) {
                        state = true;
                    }
                    getResponse = "";
                } else if (c != '\r') {
                    getResponse += String(c);
                }
                startTime = millis();
            }
            if (Feedback.length() > 0) {
                break;
            }
        }

        client.stop();
        JsonObject obj;
        JsonDocument doc;
        deserializeJson(doc, Feedback);
        obj = doc.as<JsonObject>();
        String getText = obj["text"].as<String>();
        if (getText == "null") {
            getText = obj["error"]["message"].as<String>();
        }
        Serial.println(getText);
        return getText;
    } else {
        return "Connected to " + String(api_server) + " failed.";
    }
}

void GenAI::googletts(String filename_mp3, String message, String lang)
{
    AmebaFatFS fs;
    fs.begin();
    String filepath_MP3 = String(fs.getRootPath()) + "temp.MP3";
    String filepath_mp3 = String(fs.getRootPath()) + filename_mp3;
    File file = fs.open(filepath_MP3);
    if (!file) {
        Serial.println("Failed to open file for reading");
        fs.end();
        return;
    } else {

        WiFiSSLClient client;

        Serial.println("Connecting to translate.google.com");
        if (client.connect("translate.google.com", 443)) {
            client.println("GET /translate_tts?ie=UTF-8&client=tw-ob&tl=" + lang + "&op=translate&ttsspeed=1&q=" + urlencode(message) + " HTTP/1.1");
            client.println("Host: translate.google.com");
            client.println("Content-Type: text/html; charset=utf-8");
            client.println("Connection: close");
            client.println();

            String getResponse = "";
            boolean state = false;
            int waitTime = 20000;    // timeout 10 seconds
            uint32_t startTime = millis();
            boolean headState = false;
            while ((startTime + waitTime) > millis()) {
                while (client.available()) {
                    char c = client.read();
                    if (state == true) {
                        file.print(c);
                    }
                    if (c == '\n') {
                        if (getResponse.length() == 0) {
                            if (!headState) {
                                client.readStringUntil('\n');
                                headState = true;
                            }
                            state = true;
                        }
                        if (getResponse == "0") {
                            waitTime = 0;
                            break;
                        }
                        getResponse = "";
                    } else if (c != '\r') {
                        getResponse += String(c);
                    }
                    startTime = millis();
                }
            }
            client.stop();
        } else {
            Serial.println("Connecting to translate.google.com failed.");
        }
    }
    file.close();
    Serial.println("Save finish");

    if (fs.exists(filepath_mp3)) {
        fs.remove(filepath_mp3);
    }
    fs.rename(filepath_MP3, filepath_mp3);
    fs.end();
}

String GenAI::urlencode(String str)
{
    const char *msg = str.c_str();
    const char *hex = "0123456789ABCDEF";
    String encodedMsg = "";
    while (*msg != '\0') {
        if (('a' <= *msg && *msg <= 'z') || ('A' <= *msg && *msg <= 'Z') || ('0' <= *msg && *msg <= '9') || *msg == '-' || *msg == '_' || *msg == '.' || *msg == '~') {
            encodedMsg += *msg;
        } else {
            encodedMsg += '%';
            encodedMsg += hex[(unsigned char)*msg >> 4];
            encodedMsg += hex[*msg & 0xf];
        }
        msg++;
    }
    return encodedMsg;
}

String GenAI::geminiaudio(String apikey, String filename, String model, MP4Recording &mp4, String message, WiFiSSLClient client)
{
    AmebaFatFS fs;
    String file_path;
    fs.begin();
    file_path = String(fs.getRootPath()) + "/" + filename + ".mp4";

    // begin mp4 recording
    mp4.begin();
    mp4.printInfo();
    int duration = mp4.getRecordingDuration();
    delay(duration * 1000 + 2000);

    Serial.println("File: " + file_path);
    uint8_t *fileinput;
    File file = fs.open(file_path);
    unsigned int fileSize = file.size();
    fileinput = (uint8_t *)malloc(fileSize + 1);
    file.read(fileinput, fileSize);
    fileinput[fileSize] = '\0';
    file.close();
    int encodedLen = base64_enc_len(fileSize);
    char *encodedData = (char *)malloc(encodedLen);
    base64_encode(encodedData, (char *)fileinput, fileSize);
    Serial.println("Connect to generativelanguage.googleapis.com");
    if (client.connect("generativelanguage.googleapis.com", 443)) {
        Serial.println("Connection successful");
        String filePart = "{\"inline_data\": {\"data\": \"" + String(encodedData) + "\", \"mime_type\": \"audio/mp4\",},}";
        String textPart = "{\"text\": \"" + message + "\",}";
        String request = "{\"contents\": [{\"role\": \"user\", \"parts\": [" + filePart + ", " + textPart + "]}],}";
        client.println("POST /v1beta/models/" + model + ":generateContent?key=" + apikey + " HTTP/1.1");
        client.println("Connection: close");
        client.println("Host: generativelanguage.googleapis.com");
        client.println("Content-Type: application/json; charset=utf-8");
        client.println("Content-Length: " + String(request.length()));
        client.println();
        for (uint32_t i = 0; i < request.length(); i += 1024) {
            client.print(request.substring(i, i + 1024));
        }
        String getResponse = "", Feedback = "";
        uint32_t waitTime = 20000;
        uint32_t startTime = millis();
        boolean state = false;
        boolean headState = false;
        while ((startTime + waitTime) > millis()) {
            Serial.print(".");
            delay(100);
            while (client.available()) {
                char c = client.read();
                if (state == true) {
                    Feedback += String(c);
                }
                if (c == '\n') {
                    if (getResponse.length() == 0) {
                        if (!headState) {
                            client.readStringUntil('\n');
                            headState = true;
                        }
                        state = true;
                    }
                    getResponse = "";
                } else if (c != '\r') {
                    getResponse += String(c);
                }
                startTime = millis();
            }
            if (Feedback.length() > 0) {
                break;
            }
        }
        client.stop();
        JsonObject obj;
        JsonDocument doc;
        deserializeJson(doc, Feedback);
        obj = doc.as<JsonObject>();
        String getText = obj["candidates"][0]["content"]["parts"][0]["text"].as<String>();
        if (getText == "null") {
            getText = obj["error"]["message"].as<String>();
        }
        getText.replace("\n", "");
        if (fs.exists(file_path)) {
            fs.remove(file_path);
        }
        fs.end();
        return getText;
    } else {
        fs.end();
        return "Connected to generativelanguage.googleapis.com failed.";
    }
}

String GenAI::geminivideo(String apikey, String filename, String model, MP4Recording &mp4, String message, WiFiSSLClient client)
{
    AmebaFatFS fs;
    String file_path;
    fs.begin();
    file_path = String(fs.getRootPath()) + "/" + filename + ".mp4";

    // begin mp4 recording
    mp4.begin();
    mp4.printInfo();
    int duration = mp4.getRecordingDuration();
    delay(duration * 1000 + 2000);

    Serial.println("File: " + file_path);
    uint8_t *fileinput;
    File file = fs.open(file_path);
    unsigned int fileSize = file.size();
    fileinput = (uint8_t *)malloc(fileSize + 1);
    file.read(fileinput, fileSize);
    fileinput[fileSize] = '\0';
    file.close();
    int encodedLen = base64_enc_len(fileSize);
    char *encodedData = (char *)malloc(encodedLen);
    base64_encode(encodedData, (char *)fileinput, fileSize);

    Serial.println("Connect to generativelanguage.googleapis.com");
    if (client.connect("generativelanguage.googleapis.com", 443)) {
        Serial.println("Connection successful");
        String filePart = "{\"inline_data\": {\"data\": \"" + String(encodedData) + "\", \"mime_type\": \"video/mp4\",},}";
        String textPart = "{\"text\": \"" + message + "\",}";
        String request = "{\"contents\": [{\"role\": \"user\", \"parts\": [" + filePart + ", " + textPart + "]}],}";
        client.println("POST /v1beta/models/gemini-2.0-flash:generateContent?key=" + apikey + " HTTP/1.1");
        client.println("Connection: close");
        client.println("Host: generativelanguage.googleapis.com");
        client.println("Content-Type: application/json; charset=utf-8");
        client.println("Content-Length: " + String(request.length()));
        client.println();
        for (uint32_t i = 0; i < request.length(); i += 1024) {
            client.print(request.substring(i, i + 1024));
        }
        String getResponse = "", Feedback = "";
        uint32_t waitTime = 20000;
        uint32_t startTime = millis();
        boolean state = false;
        boolean headState = false;
        while ((startTime + waitTime) > millis()) {
            Serial.print(".");
            delay(100);
            while (client.available()) {
                char c = client.read();
                if (state == true) {
                    Feedback += String(c);
                }
                if (c == '\n') {
                    if (getResponse.length() == 0) {
                        if (!headState) {
                            client.readStringUntil('\n');
                            headState = true;
                        }
                        state = true;
                    }
                    getResponse = "";
                } else if (c != '\r') {
                    getResponse += String(c);
                }
                startTime = millis();
            }
            if (Feedback.length() > 0) {
                break;
            }
        }
        client.stop();
        JsonObject obj;
        JsonDocument doc;
        deserializeJson(doc, Feedback);
        obj = doc.as<JsonObject>();
        String getText = obj["candidates"][0]["content"]["parts"][0]["text"].as<String>();
        if (getText == "null") {
            getText = obj["error"]["message"].as<String>();
        }
        getText.replace("\n", "");
        return getText;
    } else {
        return "Connected to generativelanguage.googleapis.com failed.";
    }
}
