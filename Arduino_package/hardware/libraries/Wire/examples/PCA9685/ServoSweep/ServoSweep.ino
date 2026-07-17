/*

 Example guide:
 TBD
 */

#include <Wire.h>
#include <Adafruit_libs.h>
#include "Adafruit-PWM-Servo-Driver-Library/Adafruit_PWMServoDriver.h"

#undef BUSIO_USE_FAST_PINIO

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVO_MIN 102    // ~500us
#define SERVO_MID 307    // ~1500us
#define SERVO_MAX 511    // ~2500us
#define SERVO_CH  0

void setup()
{
    Serial.begin(115200);
    Wire.begin();    // D12=SDA, D13=SCL

    pwm.begin();
    pwm.setPWMFreq(50);
    delay(10);

    Serial.println("PCA9685 ready — starting sweep on CH0");
}

void loop()
{
    Serial.println("-> Sweep forward");
    for (int tick = SERVO_MIN; tick <= SERVO_MAX; tick++) {
        pwm.setPWM(SERVO_CH, 0, tick);
        delay(15);
    }

    delay(500);

    Serial.println("<- Sweep back");
    for (int tick = SERVO_MAX; tick >= SERVO_MIN; tick--) {
        pwm.setPWM(SERVO_CH, 0, tick);
        delay(15);
    }

    delay(500);
}
