/*
 This sketch shows how to use hardware timer and invoke interrupt handler periodically

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-periodic-timer/
 */

#include <GTimer.h>

// Use timer 0 for this demo
#define TIMER_ID 0

int counter = 0;

void myhandler(uint32_t data) {
    data = data;
    counter ++;
    Serial.println();
    Serial.print("counter: ");
    Serial.println(counter);

    if (counter >= 10) {
        Serial.println("stop timer");
        GTimer.stop(TIMER_ID);
        // stop program here
        while(1);
    }
}

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    // timer id 0, period 1s, invoke myhander
    GTimer.begin(TIMER_ID, (1 * 1000 * 1000), myhandler);
}

void loop() {
    // reload timer once it's stopped
    Serial.print("Timer fire in : ");
    Serial.print(GTimer.read_us(TIMER_ID));
    Serial.println("us");
    delay(500);

    // When count to 5, reload the timer with a 2-seconds period
    if (counter == 5) {
        GTimer.reload(TIMER_ID, (2 * 1000 * 1000));
    }
}
