/*
 This sketch shows how to use several hardware timers in invoke handler only once for each timer.

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-singleuse-timer/
 */

#include <GTimer.h>

void myhandler(uint32_t data) {
    Serial.print("I am timer!");
    Serial.println(data);

    if (data >= 7) {
        Serial.println("End of the timer demo\r\n");
    }
}

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    // User can access 8 timers on Ameba Pro2, this sketch will init all of them and let them fire 1 by 1
    // timerid 0, period 1s, invoke myhandler, invoke only once, user data is 0
    GTimer.begin(0, 1 * 1000 * 1000, myhandler, false, 0);
    GTimer.begin(1, 2 * 1000 * 1000, myhandler, false, 1);
    GTimer.begin(2, 3 * 1000 * 1000, myhandler, false, 2);
    GTimer.begin(3, 4 * 1000 * 1000, myhandler, false, 3);
    GTimer.begin(4, 5 * 1000 * 1000, myhandler, false, 4);
    GTimer.begin(5, 6 * 1000 * 1000, myhandler, false, 5);
    GTimer.begin(6, 7 * 1000 * 1000, myhandler, false, 6);
    GTimer.begin(7, 8 * 1000 * 1000, myhandler, false, 7);
}

void loop() {
    delay(1000);
}
