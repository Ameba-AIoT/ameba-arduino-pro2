#ifndef __SPARKFUN_BMI270_H__
#define __SPARKFUN_BMI270_H__

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>

#include "bmi270_api/bmi270.h"

// The BMI270 API distinguishes between "data" and "feature" interrupt sources.
// This mapInterruptToPin() function does not distinguish between those sources,
// and automatically determines whether the provided interrupt source is "data"
// or a "feature". However a couple of the "data" and "feature" macros have the
// same value, so these macros help distinguish between them
#define BMI2_FEATURE_DATA_OFFSET    UINT8_C(128)
#define BMI2_SIG_MOTION_INT         (BMI2_SIG_MOTION + BMI2_FEATURE_DATA_OFFSET)
#define BMI2_WRIST_GESTURE_INT      (BMI2_WRIST_GESTURE + BMI2_FEATURE_DATA_OFFSET)
#define BMI2_ANY_MOTION_INT         (BMI2_ANY_MOTION + BMI2_FEATURE_DATA_OFFSET)
#define BMI2_NO_MOTION_INT          (BMI2_NO_MOTION + BMI2_FEATURE_DATA_OFFSET)
#define BMI2_STEP_COUNTER_INT       (BMI2_STEP_COUNTER + BMI2_FEATURE_DATA_OFFSET)
#define BMI2_STEP_DETECTOR_INT      (BMI2_STEP_DETECTOR + BMI2_FEATURE_DATA_OFFSET)
#define BMI2_STEP_ACTIVITY_INT      (BMI2_STEP_ACTIVITY + BMI2_FEATURE_DATA_OFFSET)
#define BMI2_WRIST_WEAR_WAKE_UP_INT (BMI2_WRIST_WEAR_WAKE_UP + BMI2_FEATURE_DATA_OFFSET)

// FIFO down sampling factors
#define BMI2_FIFO_DOWN_SAMPLE_1   UINT8_C(0)
#define BMI2_FIFO_DOWN_SAMPLE_2   UINT8_C(1)
#define BMI2_FIFO_DOWN_SAMPLE_4   UINT8_C(2)
#define BMI2_FIFO_DOWN_SAMPLE_8   UINT8_C(3)
#define BMI2_FIFO_DOWN_SAMPLE_16  UINT8_C(4)
#define BMI2_FIFO_DOWN_SAMPLE_32  UINT8_C(5)
#define BMI2_FIFO_DOWN_SAMPLE_64  UINT8_C(6)
#define BMI2_FIFO_DOWN_SAMPLE_128 UINT8_C(7)

// Macros to help define bmi2_accel_foc_g_value structs
#define BMI2_GRAVITY_X     UINT8_C(0x01)
#define BMI2_GRAVITY_Y     UINT8_C(0x02)
#define BMI2_GRAVITY_Z     UINT8_C(0x04)
#define BMI2_GRAVITY_POS   UINT8_C(0x08)
#define BMI2_GRAVITY_POS_X (BMI2_GRAVITY_X | BMI2_GRAVITY_POS)
#define BMI2_GRAVITY_POS_Y (BMI2_GRAVITY_Y | BMI2_GRAVITY_POS)
#define BMI2_GRAVITY_POS_Z (BMI2_GRAVITY_Z | BMI2_GRAVITY_POS)
#define BMI2_GRAVITY_NEG_X (BMI2_GRAVITY_X)
#define BMI2_GRAVITY_NEG_Y (BMI2_GRAVITY_Y)
#define BMI2_GRAVITY_NEG_Z (BMI2_GRAVITY_Z)

// Redefined macros for axis remapping with more clear names
#define BMI2_AXIS_POS_X (BMI2_X)
#define BMI2_AXIS_NEG_X (BMI2_NEG_X)
#define BMI2_AXIS_POS_Y (BMI2_Y)
#define BMI2_AXIS_NEG_Y (BMI2_NEG_Y)
#define BMI2_AXIS_POS_Z (BMI2_Z)
#define BMI2_AXIS_NEG_Z (BMI2_NEG_Z)

// Macros for step activities
#define BMI2_STEP_ACTIVITY_STILL   UINT8_C(0)
#define BMI2_STEP_ACTIVITY_WALKING UINT8_C(1)
#define BMI2_STEP_ACTIVITY_RUNNING UINT8_C(2)
#define BMI2_STEP_ACTIVITY_UNKNOWN UINT8_C(3)

// Macros for wrist gestures
#define BMI2_WRIST_GESTURE_UNKNOWN      UINT8_C(0)
#define BMI2_WRIST_GESTURE_ARM_DOWN     UINT8_C(1)
#define BMI2_WRIST_GESTURE_ARM_UP       UINT8_C(2)
#define BMI2_WRIST_GESTURE_SHAKE_JIGGLE UINT8_C(3)
#define BMI2_WRIST_GESTURE_FLICK_IN     UINT8_C(4)
#define BMI2_WRIST_GESTURE_FLICK_OUT    UINT8_C(5)

// Struct to hold data about the communication interface being used (I2C or SPI)
struct BMI270_InterfaceData {
    // Communication interface (I2C or SPI)
    bmi2_intf interface;

    // I2C settings
    uint8_t i2cAddress;
    TwoWire* i2cPort;

    // SPI settings
    uint8_t spiCSPin;
    uint32_t spiClockFrequency;
    SPIClass* spiPort;
};

// Struct to hold acceleration data
struct BMI270_SensorData {
    // Acceleration in g's
    float accelX;
    float accelY;
    float accelZ;

    // Rotation in deg/sec
    float gyroX;
    float gyroY;
    float gyroZ;

    // Auxiliary sensor data, raw bytes
    uint8_t auxData[BMI2_AUX_NUM_BYTES];

    // Time of this data in milliseconds, measured by sensor
    uint32_t sensorTimeMillis;
};

// Struct to hold FIFO config data
struct BMI270_FIFOConfig {
    // Which features to enable, can include:
    //     BMI2_FIFO_STOP_ON_FULL
    //     BMI2_FIFO_TIME_EN
    //     BMI2_FIFO_TAG_INT1
    //     BMI2_FIFO_TAG_INT2
    //     BMI2_FIFO_HEADER_EN
    //     BMI2_FIFO_AUX_EN
    //     BMI2_FIFO_ACC_EN
    //     BMI2_FIFO_GYR_EN
    //     BMI2_FIFO_ALL_EN
    uint16_t flags;

    // Number of measurements to store before triggering the watermark inteerupt
    uint16_t watermark;

    // Downsampling factor for the accelerometer and gyroscope, possible values:
    //     BMI2_FIFO_DOWN_SAMPLE_1
    //     BMI2_FIFO_DOWN_SAMPLE_2
    //     BMI2_FIFO_DOWN_SAMPLE_4
    //     BMI2_FIFO_DOWN_SAMPLE_8
    //     BMI2_FIFO_DOWN_SAMPLE_16
    //     BMI2_FIFO_DOWN_SAMPLE_32
    //     BMI2_FIFO_DOWN_SAMPLE_64
    //     BMI2_FIFO_DOWN_SAMPLE_128
    uint8_t accelDownSample;
    uint8_t gyroDownSample;

    // Whether to enable or disable the accelerometer an gyroscope filters
    bool accelFilter;
    bool gyroFilter;

    // Whether to enable or disable the self wake up feature, which allows the
    // FIFO to be read in low power mode
    bool selfWakeUp;
};

class BMI270 {
public:
    // Constructor
    BMI270();

    // Sensor initialization, must specify communication interface
    int8_t beginI2C(uint8_t address = BMI2_I2C_PRIM_ADDR, TwoWire& wirePort = Wire);
    int8_t beginSPI(uint8_t csPin, uint32_t clockFrequency = 100000, SPIClass& spiPort = SPI);

    // Sensor control
    int8_t reset();
    int8_t getStatus(uint8_t* status);
    int8_t remapAxes(bmi2_remap axes);

    // Data acquisistion
    int8_t getSensorData();
    int8_t getTemperature(float* tempC);

    // Accelerometer and gyroscope parameters
    int8_t setAccelODR(uint8_t odr);
    int8_t setGyroODR(uint8_t odr);
    int8_t setAccelPowerMode(uint8_t filterMode);
    int8_t setGyroPowerMode(uint8_t filterMode, uint8_t noiseMode);
    int8_t setAccelFilterBandwidth(uint8_t bandwidthParam);
    int8_t setGyroFilterBandwidth(uint8_t bandwidthParam);

    // Power save feature for low power consumption
    int8_t enableAdvancedPowerSave(bool enable = BMI2_ENABLE);
    int8_t disableAdvancedPowerSave();

    // Sensor and feature config control
    int8_t setConfigs(bmi2_sens_config* configs, uint8_t numConfigs);
    int8_t setConfig(bmi2_sens_config config);
    int8_t getConfigs(bmi2_sens_config* configs, uint8_t numConfigs);
    int8_t getConfig(bmi2_sens_config* config);

    // Enable or disabled features of the sensor
    int8_t enableFeatures(uint8_t* features, uint8_t numFeatures);
    int8_t enableFeature(uint8_t feature);
    int8_t disableFeatures(uint8_t* features, uint8_t numFeatures);
    int8_t disableFeature(uint8_t feature);

    // Get data for specific features
    int8_t getFeatureData(bmi2_feat_sensor_data* featureData, uint8_t numFeatures);
    int8_t getFeatureData(bmi2_feat_sensor_data* featureData);

    // Interrupt control
    int8_t mapInterruptToPin(uint8_t interruptSource, bmi2_hw_int_pin pin);
    int8_t setInterruptPinConfig(bmi2_int_pin_config config);
    int8_t getInterruptPinConfig(bmi2_int_pin_config* config);
    int8_t getInterruptStatus(uint16_t* status);

    // FIFO control
    int8_t setFIFOConfig(BMI270_FIFOConfig config);
    int8_t setFIFOFlags(uint16_t flags, bool enable);
    int8_t setFIFODownSample(uint8_t sensorSelect, uint8_t downSample);
    int8_t setFIFOFilter(uint8_t sensorSelect, bool filter);
    int8_t setFIFOSelfWakeup(bool selfWakeUp);
    int8_t setFIFOWatermark(uint16_t numData);
    int8_t getFIFOLengthBytes(uint16_t* length);
    int8_t getFIFOLength(uint16_t* length);
    int8_t getFIFOData(BMI270_SensorData* data, uint16_t* numData);
    int8_t flushFIFO();

    // Step counter features
    int8_t getStepCount(uint32_t* count);
    int8_t resetStepCount();
    int8_t setStepCountWatermark(uint16_t watermark);
    int8_t getStepActivity(uint8_t* activity);

    // Wrist gesture
    int8_t getWristGesture(uint8_t* gesture);

    // Sensor calibration
    int8_t performAccelOffsetCalibration(uint8_t gravityDirection);
    int8_t performGyroOffsetCalibration();
    int8_t performComponentRetrim();
    int8_t saveNVM();
    int8_t selfTest();

    int8_t setAuxPullUps(uint8_t pullUpValue);
    int8_t readAux(uint8_t addr, uint8_t numBytes);
    int8_t writeAux(uint8_t addr, uint8_t* data, uint8_t numBytes);
    int8_t writeAux(uint8_t addr, uint8_t data);

    // Latest measurement from the sensor
    BMI270_SensorData data;

private:
    // Sensor initialization, after communication interface has been selected
    int8_t begin();

    // Convert from raw data (bmi2_sens_data) to g's (BMI270_SensorData)
    void convertRawAccelData(bmi2_sens_axes_data* rawData, BMI270_SensorData* data);
    void convertRawGyroData(bmi2_sens_axes_data* rawData, BMI270_SensorData* data);
    void convertRawData(bmi2_sens_data* rawData, BMI270_SensorData* data);
    void convertRawTemperature(uint16_t tempRaw, float* tempC);

    // FIFO helper functions
    int8_t extractFIFOData(BMI270_SensorData* data, bmi2_fifo_frame* fifoData, uint16_t* numFrames, uint8_t sensorSelect);

    // Read/write helper functions
    static BMI2_INTF_RETURN_TYPE readRegisters(uint8_t regAddress, uint8_t* dataBuffer, uint32_t numBytes, void* interfacePtr);
    static BMI2_INTF_RETURN_TYPE readRegistersI2C(uint8_t regAddress, uint8_t* dataBuffer, uint32_t numBytes, BMI270_InterfaceData* interfaceData);
    static BMI2_INTF_RETURN_TYPE readRegistersSPI(uint8_t regAddress, uint8_t* dataBuffer, uint32_t numBytes, BMI270_InterfaceData* interfaceData);
    static BMI2_INTF_RETURN_TYPE writeRegisters(uint8_t regAddress, const uint8_t* dataBuffer, uint32_t numBytes, void* interfacePtr);
    static BMI2_INTF_RETURN_TYPE writeRegistersI2C(uint8_t regAddress, const uint8_t* dataBuffer, uint32_t numBytes, BMI270_InterfaceData* interfaceData);
    static BMI2_INTF_RETURN_TYPE writeRegistersSPI(uint8_t regAddress, const uint8_t* dataBuffer, uint32_t numBytes, BMI270_InterfaceData* interfaceData);

    // Deley helper function
    static void usDelay(uint32_t period, void* interfacePtr);

    float convertRawToGsScalar(uint8_t accRange);
    float convertRawToDegSecScalar(uint8_t gyrRange);

    // Reference to the sensor
    struct bmi2_dev sensor;

    // Information about the selected communication interface (I2C or SPI)
    BMI270_InterfaceData interfaceData;

    // Need to track the range of each sensor for converting raw data
    float rawToGs;
    float rawToDegSec;

    // Need to track the FIFO config for some FIFO functions
    uint16_t fifoConfigFlags;
    uint8_t bytesPerFIFOData;
};

#endif /*__SPARKFUN_BMI270_H__*/
