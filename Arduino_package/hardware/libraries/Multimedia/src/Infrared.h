#ifndef __INFRARED_H__
#define __INFRARED_H__

class Infrared {

public:
    Infrared(void);
    ~Infrared(void);

    void cutInit(void);
    void setCut(int value);
    int getCut(void);
    void ledInit(void);
    void setLedBrightness(int value);
    int getLedBrightness(void);

private:
    int ir_cut_value = 0;
    int ir_led_brightness = 0;
};
#endif
