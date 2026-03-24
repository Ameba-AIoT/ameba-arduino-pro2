/******************************************************************************
 * Sound detector sample sketch
 * Byron Jacquot @ SparkFun Electronics
 * February 19, 2014
 * https://github.com/sparkfun/Sound_Detector
 *
 * This sketch demonstrates the use of the Sparkfun Sound Detector board.
 *
 * The Sound Detector is a small board that combines a microphone and some
 * processing circuitry.  It provides not only an audio output, but also a
 * binary indication of the presence of sound and an analog representation
 * of it's amplitude.
 *
 * This sketch demonstrates two different modes of usage for the Sound
 * Detector.  The gate output (a binary indication that is high when sound
 * is present, and low when conditions are quiet) is used to fire a pin-change
 * ISR, which lights an LED when the sound is present.  The envelope output
 * (an analog voltage to rises to indicate the amplitude of the sound) is
 * sampled in the loop(), and it prints an indication of the level to the
 * serial terminal.
 *
 * For more details about the Sound Detector, please check the hookup guide.
 *
 * Connections:
 * The Sound Detector is connected to the AMB82-mini as follows:
 * (Sound Detector -> AMB82-mini pin)
 * GND → GND
 * VCC → 3.3V
 * Gate → Pin 0, Pin 1
 * Envelope → Pin 21
 *
 * Modified 23 Mar 2026
 * by Realtek SG
 *
 * Example guide:
 * https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/Audio/Sound%20Detector.html
 ******************************************************************************/

// Define hardware connections
#define PIN_GATE_IN   1
#define IRQ_GATE_IN   0
#define PIN_LED_OUT   LED_G
#define PIN_ANALOG_IN A2

// soundISR()
// This function is installed as an interrupt service routine for the pin
// change interrupt.  When digital input pin 0 changes state, this routine
// is called.
// It queries the state of pin 1, and sets the onboard LED to reflect that
// pin's state.
void soundISR(uint32_t id, uint32_t event)
{
    int pin_val;

    pin_val = digitalRead(PIN_GATE_IN);
    // Serial.println("ISR:");
    // Serial.println(pin_val);
    digitalWrite(PIN_LED_OUT, pin_val);
}

void setup()
{
    Serial.begin(115200);

    //  Configure LED pin as output
    pinMode(PIN_LED_OUT, OUTPUT);

    //  Configure digital pin as input
    pinMode(PIN_GATE_IN, INPUT);

    // // configure input to interrupt
    pinMode(IRQ_GATE_IN, INPUT_IRQ_CHANGE);
    digitalSetIrqHandler(IRQ_GATE_IN, soundISR);

    // Display status
    Serial.println("Initialized");
}

void loop()
{
    int value;

    // Check the envelope input
    value = analogRead(PIN_ANALOG_IN);

    // Convert envelope value into a message
    Serial.print("Status: ");
    if (value <= 10) {
        Serial.println("Quiet.");
    } else if ((value > 10) && (value <= 30)) {
        Serial.println("Moderate.");
    } else if (value > 30) {
        Serial.println("Loud.");
    }

    // pause for 1 second
    delay(1000);
}
