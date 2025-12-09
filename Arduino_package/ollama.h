void sendollama() {

 // String model = "moondream:1.8b";

    String model = "llava:34b";

  const char *myDomain = "10.0.0.190";

  String getResponse = "", Feedback = "";

  Serial.println("Connect to " + String(myDomain));


  if (client2.connect(myDomain, 11434)) {

    Serial.println("Connection successful");

     Camera.getImage(0, &img_addr, &img_len);

       Serial.println("Image Capture");

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

    Serial.println("POST");

    client2.println("POST /v1/chat/completions HTTP/1.1");

    client2.println("Host: " + String(myDomain));

    client2.println("Authorization: Bearer " + ollama_key);

    client2.println("Content-Type: application/json; charset=utf-8");

    client2.println("Content-Length: " + String(Data.length()));

    client2.println("Connection: close");

    Serial.println("Close");

    client2.println();




    unsigned int Index;

    for (Index = 0; Index < Data.length(); Index = Index + 1024) {

      client2.print(Data.substring(Index, Index + 1024));

    }




    Serial.println("Receive");

    startTime = millis();

    boolean state = false;

    boolean markState = false;





    while ((startTime + waitTime) > millis()) {

      Serial.print(".");

        delay(1000);

    }

    while (client2.available()) {

      char c = client2.read();

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

      // startTime = millis();

    }

    if (Feedback.length() > 0) {

      // break;

    }

    // }

    Serial.println();

    client2.stop();
