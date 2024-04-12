/*
 Example guide:
 TBD
*/

#define ARDUINOJSON_STRING_LENGTH_SIZE 4

#include "StreamIO.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"
#include "VideoStream.h"
#include "WiFi.h"
#include "AmebaFatFS.h"
#include "Base64.h"
#include "ArduinoJson.h"

#define CHANNEL       0
#define AUDIOFILENAME "TestRecordingAudioOnly.mp4"

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

char server[] = "192.168.3.4";    // your server IP running HTTP server on PC

AmebaFatFS fs;
WiFiClient wifiClient;

char buf_two[512];
String audiofilepath;
File audiofile;

AudioSetting configA(0);
Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO audioStreamer1(1, 1);    // 1 Input Audio -> 1 Output AAC
StreamIO audioStreamer2(1, 1);    // 1 Input AAC -> 1 Output MP4

int encodedLen;
char *encodedData;

JsonDocument doc;

int encodedAudioLen;
char *encodedAudioData;

uint32_t img_addr = 0;
uint32_t img_len = 0;

VideoSetting config(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);

const int buttonPin = 2;    // the number of the pushbutton pin

int buttonState;                          // variable for reading the pushbutton status
unsigned long buttonPressTime = 0;        // variable to store the time when button was pressed
bool buttonPressedFor2Seconds = false;    // flag to indicate if button is pressed for at least 2 seconds
int recordingstate = -1;
int previousRecordingState = -1;


void setup()
{
    Serial.begin(115200);

    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);

    // Connection to internet
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);
        delay(2000);
    }

    // list files under root directory
    fs.begin();

    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_G, OUTPUT);

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);
    audio.begin();
    // Configure AAC audio encoder
    aac.configAudio(configA);
    aac.begin();

    // Configure MP4 recording settings
    mp4.configAudio(configA, CODEC_AAC);
    mp4.setRecordingDuration(5);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingFileName("TestRecordingAudioOnly");
    mp4.setRecordingDataType(STORAGE_AUDIO);    // Set MP4 to record audio only

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer1.registerInput(audio);
    audioStreamer1.registerOutput(aac);
    if (audioStreamer1.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from AAC encoder to MP4
    audioStreamer2.registerInput(aac);
    audioStreamer2.registerOutput(mp4);
    if (audioStreamer2.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }
}

void loop()
{
    // Button state
    int newButtonState = digitalRead(buttonPin);
    if (newButtonState != buttonState) {
        buttonPressTime = millis();
    }
    // update button state
    buttonState = newButtonState;

    // update recording state
    recordingstate = (int)(mp4.getRecordingState());

    // check if the button has been held for at least 2 seconds
    if (buttonState == HIGH && millis() - buttonPressTime >= 2000) {
        // button has been pressed for at least 2 seconds
        buttonPressedFor2Seconds = true;
    } else {
        // button was released before 2 seconds
        buttonPressedFor2Seconds = false;
    }
    // if button has been pressed for at least 2 seconds
    if (buttonPressedFor2Seconds) {
        Camera.getImage(CHANNEL, &img_addr, &img_len);
        encodejpg();

        if (recordingstate == 0) {
            mp4.begin();
            Serial.println("Recording");
        }
    }
    if (recordingstate == 1) {
        digitalWrite(LED_BUILTIN, HIGH);
    }

    if (recordingstate == 0 && previousRecordingState == 1) {
        // Change from 1 to 0
        digitalWrite(LED_BUILTIN, LOW);
        encodeMP4andsendHttpPostRequest();
    }


    // Check if there are incoming bytes available from the server
    while (wifiClient.available()) {
        char c = wifiClient.read();
        Serial.write(c);
    }
    previousRecordingState = recordingstate;
    delay(10);
}

void encodejpg()
{
    // Encode the file data as Base64
    encodedLen = base64_enc_len(img_len);
    encodedData = (char *)malloc(encodedLen);
    base64_encode(encodedData, (char *)img_addr, img_len);
}

void encodeMP4andsendHttpPostRequest()
{
    memset(buf_two, 0, sizeof(buf_two));
    fs.readDir(fs.getRootPath(), buf_two, sizeof(buf_two));
    audiofilepath = String(fs.getRootPath()) + String(AUDIOFILENAME);

    uint8_t *audiofileinput;
    audiofile = fs.open(audiofilepath);
    unsigned int audiofileSize = audiofile.size();
    audiofileinput = (uint8_t *)malloc(audiofileSize + 1);
    audiofile.read(audiofileinput, audiofileSize);
    audiofileinput[audiofileSize] = '\0';
    audiofile.close();

    // Encode the file data as Base64
    encodedAudioLen = base64_enc_len(audiofileSize);
    encodedAudioData = (char *)malloc(encodedLen);
    base64_encode(encodedAudioData, (char *)audiofileinput, audiofileSize);

    doc["audio_base64_string"] = encodedAudioData;
    doc["image_base64_string"] = encodedData;

    String jsonString;
    serializeJson(doc, jsonString);

    if (wifiClient.connect(server, 8000)) {
        wifiClient.println("POST /audio HTTP/1.1");
        wifiClient.println("Host: " + String(server));
        wifiClient.println("Content-Type: application/json");                    // Use appropriate content type
        wifiClient.println("Content-Length: " + String(jsonString.length()));    // Specify the length of the content
        wifiClient.println("Connection: keep-alive");
        wifiClient.println();            // Empty line indicates the end of headers
        wifiClient.print(jsonString);    // Send the Base64 encoded audio data directly
        Serial.println("Binary sent");
    }

    Serial.println("Prompt and Image sent");
}
