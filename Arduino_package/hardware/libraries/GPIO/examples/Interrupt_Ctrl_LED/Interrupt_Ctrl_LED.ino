/*
 This sketch shows how to use GPIO interrupt and doing task in interrupt handler

 At first we light on LED.
 As button pin meets voltage rise signal, then interrupt happen and invoke interrupt handler.
 Then we change LED state.
    If LED was light on, then turn it off.
    If LED was light off, then turn it on.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/GPIO/Interrupt%20Control%20LED.html
*/

int button = PUSH_BTN;
int led = LED_BUILTIN;

int ledState = 1;

void button_handler(uint32_t id, uint32_t event)
{
    if (ledState == 0) {
        // turn on LED
        ledState = 1;
        digitalWrite(led, ledState);
    } else {
        // turn off LED
        ledState = 0;
        digitalWrite(led, ledState);
    }
}

void setup()
{
    pinMode(led, OUTPUT);
    digitalWrite(led, ledState);

    pinMode(button, INPUT_IRQ_RISE);
    digitalSetIrqHandler(button, button_handler);
}

void loop()
{
    delay(1000);
}
