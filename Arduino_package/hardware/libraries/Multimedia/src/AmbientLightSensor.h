#ifndef __AMBIENTLIGHTSENSOR_H__
#define __AMBIENTLIGHTSENSOR_H__

void sensor_thread_hw(void *param);
void sensor_thread_sw(void *param);
void init_sensor_service_ALS(void);

class AmbientLightSensor {

public:
    AmbientLightSensor(void);
    AmbientLightSensor(int als_type);
    ~AmbientLightSensor(void);

    void init(void);
    void setColorThreshold(int threshold);
    void setGrayThreshold(int threshold);
    void debugEnableOSD(void);
    void setDebugLog(int debugLevel);
    void enableAutoPWM(void);
};

#endif
