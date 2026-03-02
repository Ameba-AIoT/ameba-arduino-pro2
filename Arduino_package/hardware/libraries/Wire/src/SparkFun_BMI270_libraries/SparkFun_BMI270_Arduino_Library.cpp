// Modified 24 Nov 2025 by Realtek SG

#include "SparkFun_BMI270_Arduino_Library.h"

/// @brief Default constructor
BMI270::BMI270()
{
    // Nothing to do
}

/// @brief Checks whether sensor is connected, initializes sensor, then sets
/// default config parameters
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::begin()
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Set helper function pointers
    sensor.read = readRegisters;
    sensor.write = writeRegisters;
    sensor.delay_us = usDelay;
    sensor.intf_ptr = &interfaceData;
    sensor.read_write_len = 32;

    // Initialize the sensor
    err = bmi270_init(&sensor);
    if (err != BMI2_OK) {
        return err;
    }

    // Enable the accelerometer and gyroscope
    uint8_t features[] = {BMI2_ACCEL, BMI2_GYRO};
    err = enableFeatures(features, 2);
    if (err != BMI2_OK) {
        return err;
    }

    // Get the accelerometer and gyroscope configs
    bmi2_sens_config configs[2];
    configs[0].type = BMI2_ACCEL;
    configs[1].type = BMI2_GYRO;
    err = getConfigs(configs, 2);
    if (err != BMI2_OK) {
        return err;
    }

    // Store the accelerometer and gyroscope ranges, these are needed elsewhere
    rawToGs = convertRawToGsScalar(configs[0].cfg.acc.range);
    rawToDegSec = convertRawToDegSecScalar(configs[1].cfg.gyr.range);

    // Done!
    return BMI2_OK;
}

/// @brief Begin communication with the sensor over I2C, initialize it, and set
/// default config parameters
/// @param address I2C address of sensor
/// @param wirePort I2C port to use for communication, defaults to Wire
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::beginI2C(uint8_t address, TwoWire& wirePort)
{
    // Check whether address is valid option
    if (address != BMI2_I2C_PRIM_ADDR && address != BMI2_I2C_SEC_ADDR) {
        // Invalid option, don't do anything
        return BMI2_E_INVALID_INPUT;
    }

    // Address is valid option
    interfaceData.i2cAddress = address;
    interfaceData.i2cPort = &wirePort;

    // Set interface
    sensor.intf = BMI2_I2C_INTF;
    interfaceData.interface = BMI2_I2C_INTF;

    // Initialize sensor
    return begin();
}

/// @brief Begin communication with the sensor over SPI, initialize it, and set
/// default config parameters
/// @param csPin Chip select pin of sensor
/// @param clockFrequency SPI clock frequency
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::beginSPI(uint8_t csPin, uint32_t clockFrequency, SPIClass& spiPort)
{
    // Set up chip select pin
    interfaceData.spiCSPin = csPin;
    digitalWrite(csPin, HIGH);    // Write high now to ensure pin doesn't go low
    pinMode(csPin, OUTPUT);

    // Set desired clock frequency
    interfaceData.spiClockFrequency = clockFrequency;
    interfaceData.spiPort = &spiPort;

    // Set interface
    sensor.intf = BMI2_SPI_INTF;
    interfaceData.interface = BMI2_SPI_INTF;

    sensor.dummy_byte = 1;

    // Initialize sensor
    return begin();
}

/// @brief Performs a soft reset of the sensor
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::reset()
{
    return bmi2_soft_reset(&sensor);
}

/// @brief Gets status bits, such as data ready
/// @param status Collection of status bits, can include:
///     BMI2_DRDY_ACC
///     BMI2_DRDY_GYR
///     BMI2_DRDY_AUX
///     BMI2_CMD_RDY
///     BMI2_AUX_BUSY
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getStatus(uint8_t* status)
{
    return bmi2_get_status(status, &sensor);
}

/// @brief Remaps each axis to another axis
/// @param axes Where to map each axis, possible values for each axis:
///     BMI2_AXIS_POS_X
///     BMI2_AXIS_NEG_X
///     BMI2_AXIS_POS_Y
///     BMI2_AXIS_NEG_Y
///     BMI2_AXIS_POS_Z
///     BMI2_AXIS_NEG_Z
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::remapAxes(bmi2_remap axes)
{
    return bmi2_set_remap_axes(&axes, &sensor);
}

/// @brief Converts raw acceleration data to floating point value in g's
/// @param rawData Raw sensor data
/// @param data Output data
void BMI270::convertRawAccelData(bmi2_sens_axes_data* rawData, BMI270_SensorData* data)
{
    // Compute conversion factor from raw to g's. Raw data are signed 16-bit
    // integers, so resolution is gRange / 2^15 = 32768
    data->accelX = rawData->x * rawToGs;
    data->accelY = rawData->y * rawToGs;
    data->accelZ = rawData->z * rawToGs;
}

/// @brief Converts raw gyroscope data to floating point value in deg/sec
/// @param rawData Raw sensor data
/// @param data Output data
void BMI270::convertRawGyroData(bmi2_sens_axes_data* rawData, BMI270_SensorData* data)
{
    // Compute conversion factor from raw to deg/sec. Raw data are signed 16-bit
    // integers, so resolution is dpsRange / 2^15 = 32768
    data->gyroX = rawData->x * rawToDegSec;
    data->gyroY = rawData->y * rawToDegSec;
    data->gyroZ = rawData->z * rawToDegSec;
}

/// @brief Converts raw sensor data to floating point values
/// @param rawData Raw sensor data
/// @param data Output data
void BMI270::convertRawData(bmi2_sens_data* rawData, BMI270_SensorData* data)
{
    // Convert raw data for each sensor
    convertRawAccelData(&(rawData->acc), data);
    convertRawGyroData(&(rawData->gyr), data);

    memcpy(data->auxData, rawData->aux_data, BMI2_AUX_NUM_BYTES);

    // Convert raw sensor time to milliseconds
    data->sensorTimeMillis = rawData->sens_time * 1000 * BMI2_SENSORTIME_RESOLUTION;
}

/// @brief Converts raw temperature to degrees Celsius
/// @param tempRaw Raw temperature from sensor
/// @param tempC Converted temperature in degrees Celsius
void BMI270::convertRawTemperature(uint16_t tempRaw, float* tempC)
{
    // Convert raw temperature to deg C as defined by datasheet
    *tempC = ((int16_t)tempRaw) / 512.0 + 23.0;
}

/// @brief Gets data from the sensor. Must be called to update the data struct
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getSensorData()
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get raw data from sensor
    bmi2_sens_data rawData;
    err = bmi2_get_sensor_data(&rawData, &sensor);
    if (err != BMI2_OK) {
        return err;
    }

    // Convert raw data to g's and deg/sec
    convertRawData(&rawData, &data);

    return BMI2_OK;
}

/// @brief Gets temperature measured by the sensor
/// @param tempC Temperature in degrees Celsius
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getTemperature(float* tempC)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get raw temperature from sensor
    uint16_t tempRaw;
    err = bmi2_get_temperature_data(&tempRaw, &sensor);
    if (err != BMI2_OK) {
        return err;
    }

    // Convert raw temperature to degrees Celsius
    convertRawTemperature(tempRaw, tempC);

    return BMI2_OK;
}

/// @brief Sets output data rate of accelerometer
/// @param odr Output data rate, assignable values are:
///     BMI2_ACC_ODR_0_78HZ
///     BMI2_ACC_ODR_1_56HZ
///     BMI2_ACC_ODR_3_12HZ
///     BMI2_ACC_ODR_6_25HZ
///     BMI2_ACC_ODR_12_5HZ
///     BMI2_ACC_ODR_25HZ
///     BMI2_ACC_ODR_50HZ
///     BMI2_ACC_ODR_100HZ (default)
///     BMI2_ACC_ODR_200HZ
///     BMI2_ACC_ODR_400HZ
///     BMI2_ACC_ODR_800HZ
///     BMI2_ACC_ODR_1600HZ
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setAccelODR(uint8_t odr)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get current accelerometer config
    bmi2_sens_config config;
    config.type = BMI2_ACCEL;
    err = getConfig(&config);
    if (err != BMI2_OK) {
        return err;
    }

    // Update config
    config.cfg.acc.odr = odr;
    return setConfig(config);
}

/// @brief Sets output data rate of gyroscope
/// @param odr Output data rate, assignable values are:
///     BMI2_GYR_ODR_25HZ
///     BMI2_GYR_ODR_50HZ
///     BMI2_GYR_ODR_100HZ
///     BMI2_GYR_ODR_200HZ (default)
///     BMI2_GYR_ODR_400HZ
///     BMI2_GYR_ODR_800HZ
///     BMI2_GYR_ODR_1600HZ
///     BMI2_GYR_ODR_3200HZ
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setGyroODR(uint8_t odr)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get current gyro config
    bmi2_sens_config config;
    config.type = BMI2_GYRO;
    err = getConfig(&config);
    if (err != BMI2_OK) {
        return err;
    }

    // Update config
    config.cfg.gyr.odr = odr;
    return setConfig(config);
}

/// @brief Sets filter power mode of accelerometer
/// @param filterMode Filter power mode, assignable values are:
///     BMI2_POWER_OPT_MODE
///     BMI2_PERF_OPT_MODE (default)
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setAccelPowerMode(uint8_t filterMode)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get current accelerometer config
    bmi2_sens_config config;
    config.type = BMI2_ACCEL;
    err = getConfig(&config);
    if (err != BMI2_OK) {
        return err;
    }

    // Update config
    config.cfg.acc.filter_perf = filterMode;
    return setConfig(config);
}

/// @brief Sets filter power mode of gyroscope
/// @param filterMode Filter power mode, assignable values are:
///     BMI2_POWER_OPT_MODE
///     BMI2_PERF_OPT_MODE (default)
/// @param noiseMode Noise power mode, assignable values are:
///     BMI2_POWER_OPT_MODE
///     BMI2_PERF_OPT_MODE (default)
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setGyroPowerMode(uint8_t filterMode, uint8_t noiseMode)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get current gyro config
    bmi2_sens_config config;
    config.type = BMI2_GYRO;
    err = getConfig(&config);
    if (err != BMI2_OK) {
        return err;
    }

    // Update config
    config.cfg.gyr.filter_perf = filterMode;
    config.cfg.gyr.noise_perf = noiseMode;
    return setConfig(config);
}

/// @brief Sets filter bandwidth parameter of accelerometer. Behavior depends on
/// the filter power mode:
///     Performance mode: Normal, OSR2, OSR4, CIC
///     Power mode:       Averaging from 1 to 128 samples
/// @param bandwidthParam Filter bandwidth parameter, assignable values are:
///     BMI2_ACC_OSR4_AVG1
///     BMI2_ACC_OSR2_AVG2
///     BMI2_ACC_NORMAL_AVG4 (default)
///     BMI2_ACC_CIC_AVG8
///     BMI2_ACC_RES_AVG16
///     BMI2_ACC_RES_AVG32
///     BMI2_ACC_RES_AVG64
///     BMI2_ACC_RES_AVG128
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setAccelFilterBandwidth(uint8_t bandwidthParam)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get current accelerometer config
    bmi2_sens_config config;
    config.type = BMI2_ACCEL;
    err = getConfig(&config);
    if (err != BMI2_OK) {
        return err;
    }

    // Update config
    config.cfg.acc.bwp = bandwidthParam;
    return setConfig(config);
}

/// @brief Sets filter bandwidth parameter of gyroscope
/// @param bandwidthParam Filter bandwidth parameter, assignable values are:
///     BMI2_GYR_OSR4_MODE
///     BMI2_GYR_OSR2_MODE
///     BMI2_GYR_NORMAL_MODE (default)
///     BMI2_GYR_CIC_MODE
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setGyroFilterBandwidth(uint8_t bandwidthParam)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get current gyro config
    bmi2_sens_config config;
    config.type = BMI2_GYRO;
    err = getConfig(&config);
    if (err != BMI2_OK) {
        return err;
    }

    // Update config
    config.cfg.gyr.bwp = bandwidthParam;
    return setConfig(config);
}

/// @brief Enables advanced power save mode
/// @param enable Whether to enable or disable advanced power save
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::enableAdvancedPowerSave(bool enable)
{
    if (enable) {
        return bmi2_set_adv_power_save(BMI2_ENABLE, &sensor);
    } else {
        return bmi2_set_adv_power_save(BMI2_DISABLE, &sensor);
    }
}

/// @brief Disables advanced power save mode
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::disableAdvancedPowerSave()
{
    return enableAdvancedPowerSave(BMI2_DISABLE);
}

/// @brief Sets configuration parameters for sensor features, such as the
/// sensors or interrupts
/// @param configs Array of configs to be set. Possible types include:
///     BMI2_ACCEL
///     BMI2_GYRO
///     BMI2_AUX
///     BMI2_GYRO_GAIN_UPDATE
///     BMI2_ANY_MOTION
///     BMI2_NO_MOTION
///     BMI2_SIG_MOTION
///     BMI2_STEP_COUNTER_PARAMS
///     BMI2_STEP_DETECTOR
///     BMI2_STEP_COUNTER
///     BMI2_STEP_ACTIVITY
///     BMI2_WRIST_GESTURE
///     BMI2_WRIST_WEAR_WAKE_UP
/// @param numConfigs Size of configs array
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setConfigs(bmi2_sens_config* configs, uint8_t numConfigs)
{
    // Check to see if the accelerometer or gyro configs are being updated,
    // these are needed elsewhere
    for (int i = 0; i < numConfigs; i++) {
        if (configs[i].type == BMI2_ACCEL) {
            rawToGs = convertRawToGsScalar(configs[i].cfg.acc.range);
        } else if (configs[i].type == BMI2_GYRO) {
            rawToDegSec = convertRawToDegSecScalar(configs[i].cfg.gyr.range);
        }
    }

    return bmi270_set_sensor_config(configs, numConfigs, &sensor);
}

/// @brief Sets configuration parameters for a sensor feature, such as a
/// sensor or interrupt
/// @param configs Config to be set. Possible types include:
///     BMI2_ACCEL
///     BMI2_GYRO
///     BMI2_AUX
///     BMI2_GYRO_GAIN_UPDATE
///     BMI2_ANY_MOTION
///     BMI2_NO_MOTION
///     BMI2_SIG_MOTION
///     BMI2_STEP_COUNTER_PARAMS
///     BMI2_STEP_DETECTOR
///     BMI2_STEP_COUNTER
///     BMI2_STEP_ACTIVITY
///     BMI2_WRIST_GESTURE
///     BMI2_WRIST_WEAR_WAKE_UP
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setConfig(bmi2_sens_config config)
{
    return setConfigs(&config, 1);
}


/// @brief Gets configuration parameters for sensor features, such as the
/// sensors or interrupts
/// @param configs Array of configs to be set. Possible types include:
///     BMI2_ACCEL
///     BMI2_GYRO
///     BMI2_AUX
///     BMI2_GYRO_GAIN_UPDATE
///     BMI2_ANY_MOTION
///     BMI2_NO_MOTION
///     BMI2_SIG_MOTION
///     BMI2_STEP_COUNTER_PARAMS
///     BMI2_STEP_DETECTOR
///     BMI2_STEP_COUNTER
///     BMI2_STEP_ACTIVITY
///     BMI2_WRIST_GESTURE
///     BMI2_WRIST_WEAR_WAKE_UP
/// @param numConfigs Size of configs array
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getConfigs(bmi2_sens_config* configs, uint8_t numConfigs)
{
    return bmi270_get_sensor_config(configs, numConfigs, &sensor);
}

/// @brief Gets configuration parameters for a sensor feature, such as a
/// sensor or interrupt
/// @param configs Config to be set. Possible types include:
///     BMI2_ACCEL
///     BMI2_GYRO
///     BMI2_AUX
///     BMI2_GYRO_GAIN_UPDATE
///     BMI2_ANY_MOTION
///     BMI2_NO_MOTION
///     BMI2_SIG_MOTION
///     BMI2_STEP_COUNTER_PARAMS
///     BMI2_STEP_DETECTOR
///     BMI2_STEP_COUNTER
///     BMI2_STEP_ACTIVITY
///     BMI2_WRIST_GESTURE
///     BMI2_WRIST_WEAR_WAKE_UP
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getConfig(bmi2_sens_config* config)
{
    return getConfigs(config, 1);
}

/// @brief Enables features of the sensor, such as the accelerometer, auxiliary
/// I2C bus, or interrupts
/// @param features Array of features to be enabled, see bmi270_sensor_enable
/// for possible values
/// @param numFeatures Size of features array
/// @param enable Whether to enable or disable the provided features
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::enableFeatures(uint8_t* features, uint8_t numFeatures)
{
    return bmi270_sensor_enable(features, numFeatures, &sensor);
}

/// @brief Enables a single feature of the sensor, such as the accelerometer,
/// auxiliary I2C bus, or interrupts
/// @param feature Feature to be enabled, see bmi270_sensor_enable for possible
/// values
/// @param enable Whether to enable or disable the provided feature
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::enableFeature(uint8_t feature)
{
    return enableFeatures(&feature, 1);
}

/// @brief Disables features of the sensor, such as the accelerometer, auxiliary
/// I2C bus, or interrupts
/// @param features Array of features to be disabled, see bmi270_sensor_enable
/// for possible values
/// @param numFeatures Size of features array
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::disableFeatures(uint8_t* features, uint8_t numFeatures)
{
    return bmi270_sensor_disable(features, numFeatures, &sensor);
}

/// @brief Disables a single feature of the sensor, such as the accelerometer,
/// auxiliary I2C bus, or interrupts
/// @param feature Feature to be disabled, see bmi270_sensor_enable for possible
/// values
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::disableFeature(uint8_t feature)
{
    return disableFeatures(&feature, 1);
}

/// @brief Gets data of sensor features, such as step count or wrist gesture
/// @param featureData Array of features to get data from, see
/// bmi2_feat_sensor_data for possible values
/// @param numFeatures Size of featureData array
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getFeatureData(bmi2_feat_sensor_data* featureData, uint8_t numFeatures)
{
    return bmi270_get_feature_data(featureData, numFeatures, &sensor);
}

/// @brief Gets data of a sensor feature, such as step count or wrist gesture
/// @param featureData Feature to get data from, see bmi2_feat_sensor_data for
/// possible values
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getFeatureData(bmi2_feat_sensor_data* featureData)
{
    return getFeatureData(featureData, 1);
}

/// @brief Configures an interrupt to output on an interrupt pin
/// @param interruptSource Which interrupt trigger to map, possible values:
///     BMI2_FFULL_INT
///     BMI2_FWM_INT
///     BMI2_DRDY_INT
///     BMI2_ERR_INT
///     BMI2_SIG_MOTION_INT
///     BMI2_WRIST_GESTURE_INT
///     BMI2_ANY_MOTION_INT
///     BMI2_NO_MOTION_INT
///     BMI2_STEP_COUNTER_INT
///     BMI2_STEP_DETECTOR_INT
///     BMI2_STEP_ACTIVITY_INT
///     BMI2_WRIST_WEAR_WAKE_UP_INT
/// @param pin Which pin to output on, see bmi2_hw_int_pin for possible values
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::mapInterruptToPin(uint8_t interruptSource, bmi2_hw_int_pin pin)
{
    // The BMI270 API distinguishes between "data" and "feature" interrupt
    // sources, whereas this function handles both. Need to determine whether
    // this source is "data" or a "feature"
    switch (interruptSource) {
        // Data interrupt sources
        case BMI2_FFULL_INT:
        case BMI2_FWM_INT:
        case BMI2_DRDY_INT:
        case BMI2_ERR_INT:
            return bmi2_map_data_int(interruptSource, pin, &sensor);
            break;

        // Feature interrupt sources
        case BMI2_SIG_MOTION_INT:
        case BMI2_WRIST_GESTURE_INT:
        case BMI2_ANY_MOTION_INT:
        case BMI2_NO_MOTION_INT:
        case BMI2_STEP_COUNTER_INT:
        case BMI2_STEP_DETECTOR_INT:
        case BMI2_STEP_ACTIVITY_INT:
        case BMI2_WRIST_WEAR_WAKE_UP_INT:
            // A couple of the "data" and "feature" macros have the same value,
            // so this offset helps distinguish between them
            interruptSource -= BMI2_FEATURE_DATA_OFFSET;
            return bmi2_map_feat_int(interruptSource, pin, &sensor);
            break;

        // Invalid interrupt source
        default:
            return BMI2_E_INVALID_INPUT;
            break;
    }
}

/// @brief Sets configuration parameters for the interrupt pins
/// @param config Configuration parameters, see bmi2_int_pin_config
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setInterruptPinConfig(bmi2_int_pin_config config)
{
    return bmi2_set_int_pin_config(&config, &sensor);
}

/// @brief Gets configuration parameters for the interrupt pins
/// @param config Configuration parameters, see bmi2_int_pin_config
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getInterruptPinConfig(bmi2_int_pin_config* config)
{
    return bmi2_get_int_pin_config(config, &sensor);
}

/// @brief Gets interrupt status bits, such as data ready
/// @param status Collection of interrupt status bits, can include:
///     BMI2_FFULL_INT_STATUS_MASK
///     BMI2_FWM_INT_STATUS_MASK
///     BMI2_ERR_INT_STATUS_MASK
///     BMI2_AUX_DRDY_INT_MASK
///     BMI2_GYR_DRDY_INT_MASK
///     BMI2_ACC_DRDY_INT_MASK
///     BMI270_SIG_MOT_STATUS_MASK
///     BMI270_STEP_CNT_STATUS_MASK
///     BMI270_STEP_ACT_STATUS_MASK
///     BMI270_WRIST_WAKE_UP_STATUS_MASK
///     BMI270_WRIST_GEST_STATUS_MASK
///     BMI270_NO_MOT_STATUS_MASK
///     BMI270_ANY_MOT_STATUS_MASK
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getInterruptStatus(uint16_t* status)
{
    return bmi2_get_int_status(status, &sensor);
}

/// @brief Sets configuration parameters for the FIFO
/// @param config Configuration parameters, see BMI270_FIFOConfig
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setFIFOConfig(BMI270_FIFOConfig config)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Set flag bits
    err = setFIFOFlags(config.flags, BMI2_ENABLE);
    if (err != BMI2_OK) {
        return err;
    }

    // Clear unused flag bits
    err = setFIFOFlags(~config.flags, BMI2_DISABLE);
    if (err != BMI2_OK) {
        return err;
    }

    // Set accelerometer downsampling factor
    err = setFIFODownSample(BMI2_ACCEL, config.accelDownSample);
    if (err != BMI2_OK) {
        return err;
    }

    // Set gyroscope downsampling factor
    err = setFIFODownSample(BMI2_GYRO, config.gyroDownSample);
    if (err != BMI2_OK) {
        return err;
    }

    // Set accelerometer filtering
    err = setFIFOFilter(BMI2_ACCEL, config.accelFilter);
    if (err != BMI2_OK) {
        return err;
    }

    // Set gyroscope filtering
    err = setFIFOFilter(BMI2_GYRO, config.gyroFilter);
    if (err != BMI2_OK) {
        return err;
    }

    // Set gyroscope filtering
    err = setFIFOSelfWakeup(config.selfWakeUp);
    if (err != BMI2_OK) {
        return err;
    }

    // Set watermark
    err = setFIFOWatermark(config.watermark);
    if (err != BMI2_OK) {
        return err;
    }

    return BMI2_OK;
}

/// @brief Enables or disables FIFO features
/// @param flags Which flags to set, can include:
///     BMI2_FIFO_STOP_ON_FULL
///     BMI2_FIFO_TIME_EN
///     BMI2_FIFO_TAG_INT1
///     BMI2_FIFO_TAG_INT2
///     BMI2_FIFO_HEADER_EN
///     BMI2_FIFO_AUX_EN
///     BMI2_FIFO_ACC_EN
///     BMI2_FIFO_GYR_EN
///     BMI2_FIFO_ALL_EN
/// @param enable Whether to enable or disable the selected features
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setFIFOFlags(uint16_t flags, bool enable)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Attempt to set value
    err = bmi2_set_fifo_config(flags, enable, &sensor);
    if (err != BMI2_OK) {
        return err;
    }

    // Value got set correctly, save for later use
    if (enable) {
        fifoConfigFlags |= flags;
    } else {
        fifoConfigFlags &= ~flags;
    }

    // Compute number of bytes per FIFO frame
    bytesPerFIFOData = 0;
    bytesPerFIFOData += ((fifoConfigFlags & BMI2_FIFO_ACC_EN) != 0) * 6;
    bytesPerFIFOData += ((fifoConfigFlags & BMI2_FIFO_GYR_EN) != 0) * 6;
    bytesPerFIFOData += ((fifoConfigFlags & BMI2_FIFO_HEADER_EN) != 0) * 1;

    return BMI2_OK;
}

/// @brief Sets FIFO down sampling factor for the selected sensor
/// @param sensorSelect Which sensor to set, can be either:
///     BMI2_ACCEL
///     BMI2_GYRO
/// @param downSample Down sampling factor, possible values:
///     BMI2_FIFO_DOWN_SAMPLE_1
///     BMI2_FIFO_DOWN_SAMPLE_2
///     BMI2_FIFO_DOWN_SAMPLE_4
///     BMI2_FIFO_DOWN_SAMPLE_8
///     BMI2_FIFO_DOWN_SAMPLE_16
///     BMI2_FIFO_DOWN_SAMPLE_32
///     BMI2_FIFO_DOWN_SAMPLE_64
///     BMI2_FIFO_DOWN_SAMPLE_128
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setFIFODownSample(uint8_t sensorSelect, uint8_t downSample)
{
    return bmi2_set_fifo_down_sample(sensorSelect, downSample, &sensor);
}

/// @brief Enables filtered data for the selected sensor in the FIFO buffer
/// @param sensorSelect Which sensor to set, can be either:
///     BMI2_ACCEL
///     BMI2_GYRO
/// @param filter Whether to enable or disable filtered data
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setFIFOFilter(uint8_t sensorSelect, bool filter)
{
    return bmi2_set_fifo_filter_data(sensorSelect, filter, &sensor);
}

/// @brief Enables the self wake up feature of the FIFO buffer, which allows the
/// data to be read in low power mode
/// @param selfWakeUp Whether to enable or disable the self wake up feature
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setFIFOSelfWakeup(bool selfWakeUp)
{
    return bmi2_set_fifo_self_wake_up(selfWakeUp, &sensor);
}

/// @brief Sets the number of measurements to store in the FIFO buffer before
/// triggering the watermark interrupt
/// @param numData Number of measurements to store
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setFIFOWatermark(uint16_t numData)
{
    return bmi2_set_fifo_wm(numData * bytesPerFIFOData, &sensor);
}

/// @brief Gets the number of bytes currently in the FIFO buffer
/// @param length Number of bytes in the FIFO buffer
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getFIFOLengthBytes(uint16_t* length)
{
    return bmi2_get_fifo_length(length, &sensor);
}

/// @brief Gets the number of measurements currently in the FIFO buffer
/// @param length Number of measurements in the FIFO buffer
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getFIFOLength(uint16_t* length)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    err = getFIFOLengthBytes(length);
    if (err != BMI2_OK) {
        return err;
    }

    *length /= bytesPerFIFOData;

    return BMI2_OK;
}

/// @brief Assuming raw bytes have been read from the FIFO buffer, this extracts
/// the sensor data corresponding to the selected sensor
/// @param data Array of data structs, see BMI270_SensorData
/// @param fifoData FIFO struct, see bmi2_fifo_frame
/// @param numFrames Number of measurements in buffer
/// @param sensorSelect Which sensor data to extract, can be either:
///     BMI2_ACCEL
///     BMI2_GYRO
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::extractFIFOData(BMI270_SensorData* data, bmi2_fifo_frame* fifoData, uint16_t* numFrames, uint8_t sensorSelect)
{
    // Check whether the sensor is actually enabled in the FIFO
    if ((sensorSelect == BMI2_ACCEL && (fifoConfigFlags & BMI2_FIFO_ACC_EN) == 0) || (sensorSelect == BMI2_GYRO && (fifoConfigFlags & BMI2_FIFO_GYR_EN) == 0)) {
        // Sensor is disabled in FIFO, just return
        return BMI2_OK;
    }

    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Create buffer to hold raw data
    bmi2_sens_axes_data* rawData = (bmi2_sens_axes_data*)malloc((*numFrames) * sizeof(bmi2_sens_axes_data));

    // Extract raw data from the FIFO data
    if (sensorSelect == BMI2_ACCEL) {
        err = bmi2_extract_accel(rawData, numFrames, fifoData, &sensor);
    } else {
        err = bmi2_extract_gyro(rawData, numFrames, fifoData, &sensor);
    }
    if (err < BMI2_OK) {
        free(rawData);
        return err;
    }

    // Convert raw data
    for (int i = 0; i < (*numFrames); i++) {
        if (sensorSelect == BMI2_ACCEL) {
            convertRawAccelData(&(rawData[i]), &(data[i]));
        } else {
            convertRawGyroData(&(rawData[i]), &(data[i]));
        }
    }

    free(rawData);
    return err;
}

/// @brief Gets sensor data out of the FIFO buffer
/// @param data Array of data structs, see BMI270_SensorData
/// @param numData Number of measurements to read
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getFIFOData(BMI270_SensorData* data, uint16_t* numData)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get number of bytes in the FIFO
    uint16_t numFIFOBytes = 0;
    getFIFOLengthBytes(&numFIFOBytes);

    // Create a byte buffer to hold raw FIFO data
    uint8_t* fifoBuffer = (uint8_t*)malloc(numFIFOBytes);

    // Computer how many data frames should be in the FIFO
    uint8_t numFrames = numFIFOBytes / bytesPerFIFOData;

    // Ensure we have enough frames to fill the requested data
    if (*numData > numFrames) {
        *numData = numFrames;
    }

    // Create a struct for handling FIFO
    bmi2_fifo_frame fifoData;
    fifoData.length = numFIFOBytes + sensor.dummy_byte;
    fifoData.data = fifoBuffer;

    // Read data out of the FIFO into the byte buffer
    err = bmi2_read_fifo_data(&fifoData, &sensor);
    if (err != BMI2_OK) {
        free(fifoBuffer);
        return err;
    }

    // Extract the raw acceleration data from the buffer
    err = extractFIFOData(data, &fifoData, numData, BMI2_ACCEL);
    if (err < BMI2_OK) {
        free(fifoBuffer);
        return err;
    }

    // Extract the raw gyroscope data from the buffer
    err = extractFIFOData(data, &fifoData, numData, BMI2_GYRO);
    if (err < BMI2_OK) {
        free(fifoBuffer);
        return err;
    }

    free(fifoBuffer);
    return BMI2_OK;
}

/// @brief Clears all data in FIFO buffer
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::flushFIFO()
{
    return bmi2_set_command_register(BMI2_FIFO_FLUSH_CMD, &sensor);
}

/// @brief Gets number of steps counted by the sensor
/// @param count Number of steps
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getStepCount(uint32_t* count)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get step count
    bmi2_feat_sensor_data featureData;
    featureData.type = BMI2_STEP_COUNTER;
    err = getFeatureData(&featureData);
    if (err) {
        return err;
    }

    *count = featureData.sens_data.step_counter_output;
    return BMI2_OK;
}

/// @brief Resets the number of steps counted by the sensor
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::resetStepCount()
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get step count
    bmi2_sens_config config;
    config.type = BMI2_STEP_COUNTER;
    err = getConfig(&config);
    if (err) {
        return err;
    }

    config.cfg.step_counter.reset_counter = true;
    return setConfig(config);
}

/// @brief Sets step counter watermark, which triggers the step counter
/// interrupt every number of steps
/// @param watermark Number of steps divided by 20 (eg. 1 equals 20 steps)
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setStepCountWatermark(uint16_t watermark)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get step count
    bmi2_sens_config config;
    config.type = BMI2_STEP_COUNTER;
    err = getConfig(&config);
    if (err) {
        return err;
    }

    config.cfg.step_counter.watermark_level = watermark;
    return setConfig(config);
}

/// @brief Gets the step activity measured by the sensor
/// @param activity Measured activity, possible values:
///     BMI2_STEP_ACTIVITY_STILL
///     BMI2_STEP_ACTIVITY_WALKING
///     BMI2_STEP_ACTIVITY_RUNNING
///     BMI2_STEP_ACTIVITY_UNKNOWN
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getStepActivity(uint8_t* activity)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get step count
    bmi2_feat_sensor_data featureData;
    featureData.type = BMI2_STEP_ACTIVITY;
    err = getFeatureData(&featureData);
    if (err) {
        return err;
    }

    *activity = featureData.sens_data.activity_output;
    return BMI2_OK;
}

/// @brief Gets the wrist gesture measured by the sensor
/// @param gesture Measured gesture, possible values:
///     BMI2_WRIST_GESTURE_UNKNOWN
///     BMI2_WRIST_GESTURE_ARM_DOWN
///     BMI2_WRIST_GESTURE_ARM_UP
///     BMI2_WRIST_GESTURE_SHAKE_JIGGLE
///     BMI2_WRIST_GESTURE_FLICK_IN
///     BMI2_WRIST_GESTURE_FLICK_OUT
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::getWristGesture(uint8_t* gesture)
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Get step count
    bmi2_feat_sensor_data featureData;
    featureData.type = BMI2_WRIST_GESTURE;
    err = getFeatureData(&featureData);
    if (err) {
        return err;
    }

    *gesture = featureData.sens_data.wrist_gesture_output;
    return BMI2_OK;
}

/// @brief Performs the built-in fast offset calibration for the accelerometer.
/// Sensor must remain motionless, and one axis aligned with gravity
/// @param gravityDirection Direction of gravity, possible values:
///     BMI2_GRAVITY_POS_X
///     BMI2_GRAVITY_POS_Y
///     BMI2_GRAVITY_POS_Z
///     BMI2_GRAVITY_NEG_X
///     BMI2_GRAVITY_NEG_Y
///     BMI2_GRAVITY_NEG_Z
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::performAccelOffsetCalibration(uint8_t gravityDirection)
{
    // Determine which direction gravity is pointing
    bmi2_accel_foc_g_value gDir;
    gDir.x = (gravityDirection & BMI2_GRAVITY_X) != 0;
    gDir.y = (gravityDirection & BMI2_GRAVITY_Y) != 0;
    gDir.z = (gravityDirection & BMI2_GRAVITY_Z) != 0;
    gDir.sign = (gravityDirection & BMI2_GRAVITY_POS) != 0;

    return bmi2_perform_accel_foc(&gDir, &sensor);
}

/// @brief Performs the built-in fast offset calibration for the gyroscope.
/// Sensor must remain motionless
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::performGyroOffsetCalibration()
{
    return bmi2_perform_gyro_foc(&sensor);
}

/// @brief Performs the built-in component retrimming for the gyroscope.
/// Sensor must remain motionless
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::performComponentRetrim()
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Perform the gyro component retrimming
    err = bmi2_do_crt(&sensor);
    if (err != BMI2_OK) {
        return err;
    }

    // The gyro is disabled when the CRT is performed, so re-enable it
    return enableFeature(BMI2_GYRO);
}

/// @brief Save all NVM-backed registers to the NVM. WARNING!!! The BMI270's
/// NVM only supports 14 write cycles max!
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::saveNVM()
{
    return bmi2_nvm_prog(&sensor);
}

/// @brief Perform the built-in self test for the sensor
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::selfTest()
{
    // Variable to track errors returned by API calls
    int8_t err = BMI2_OK;

    // Run accelerometer self test
    err = bmi2_perform_accel_self_test(&sensor);
    if (err != BMI2_OK) {
        return err;
    }

    // It's recommended to reset the sensor after performing the self test
    err = reset();
    if (err != BMI2_OK) {
        return err;
    }

    // Run gyroscope self test
    err = bmi2_do_gyro_st(&sensor);
    if (err != BMI2_OK) {
        return err;
    }

    // Re-initialize sensor to ensure all settings are back to default
    return begin();
}

/// @brief Sets pull up resistors on auxiliary I2C pins
/// @param pullUpValue Pull up resistor values, can be one of the following:
///     BMI2_ASDA_PUPSEL_OFF
///     BMI2_ASDA_PUPSEL_40K
///     BMI2_ASDA_PUPSEL_10K
///     BMI2_ASDA_PUPSEL_2K
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::setAuxPullUps(uint8_t pullUpValue)
{
    return writeRegisters(BMI2_AUX_IF_TRIM, &pullUpValue, 1, &interfaceData);
}

/// @brief Reads data from device on auxiliary I2C bus. Regardless of the value
/// of numBytes, this will always read man_rd_burst bytes from the sensor, then
/// numBytes will be copied into the auxData buffer. This is only supported in
/// manual mode
/// @param addr Register address to read from
/// @param numBytes Number of bytes to read
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::readAux(uint8_t addr, uint8_t numBytes)
{
    return bmi2_read_aux_man_mode(addr, data.auxData, numBytes, &sensor);
}

/// @brief Writes bytes to device on auxiliary I2C bus. Note that burst writing
/// is not supported by the BMI270's aux interface, data is instead sent 1 byte
/// at a time in register data pairs (register address is auto incremented).
/// This is only supported in manual mode
/// @param addr Register address to start writing data
/// @param data Data to write
/// @param numBytes Number of bytes to write
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::writeAux(uint8_t addr, uint8_t* data, uint8_t numBytes)
{
    return bmi2_write_aux_man_mode(addr, data, numBytes, &sensor);
}

/// @brief Writes a single byte to device on auxiliary I2C bus. This is only
/// supported in manual mode
/// @param addr Register address to write
/// @param data Value to write
/// @return Error code (0 is success, negative is failure, positive is warning)
int8_t BMI270::writeAux(uint8_t addr, uint8_t data)
{
    return writeAux(addr, &data, 1);
}

/// @brief Helper function to read sensor registers
/// @param regAddress Start address to read
/// @param dataBuffer Buffer to store register values
/// @param numBytes Number of bytes to read
/// @param interfacePtr Pointer to interface data, see BMI270_InterfaceData
/// @return Error code (0 is success, negative is failure, positive is warning)
BMI2_INTF_RETURN_TYPE BMI270::readRegisters(uint8_t regAddress, uint8_t* dataBuffer, uint32_t numBytes, void* interfacePtr)
{
    // Make sure the number of bytes is valid
    if (numBytes == 0) {
        return BMI2_E_COM_FAIL;
    }

    // Get interface data
    BMI270_InterfaceData* interfaceData = (BMI270_InterfaceData*)interfacePtr;

    switch (interfaceData->interface) {
        case BMI2_I2C_INTF:
            return readRegistersI2C(regAddress, dataBuffer, numBytes, interfaceData);
            break;
        case BMI2_SPI_INTF:
            return readRegistersSPI(regAddress, dataBuffer, numBytes, interfaceData);
            break;
        default:
            return BMI2_E_COM_FAIL;
            break;
    }
}

/// @brief Helper function to read sensor registers over I2C
/// @param regAddress Start address to read
/// @param dataBuffer Buffer to store register values
/// @param numBytes Number of bytes to read
/// @param interfaceData Pointer to interface data, see BMI270_InterfaceData
/// @return Error code (0 is success, negative is failure, positive is warning)
BMI2_INTF_RETURN_TYPE BMI270::readRegistersI2C(uint8_t regAddress, uint8_t* dataBuffer, uint32_t numBytes, BMI270_InterfaceData* interfaceData)
{
    // Jump to desired register address
    interfaceData->i2cPort->beginTransmission(interfaceData->i2cAddress);
    interfaceData->i2cPort->write(regAddress);
    if (interfaceData->i2cPort->endTransmission()) {
        return BMI2_E_COM_FAIL;
    }

    // Read bytes from these registers
    interfaceData->i2cPort->requestFrom(interfaceData->i2cAddress, numBytes);
    // hal_delay_ms(10);

    // Store all requested bytes
    for (uint32_t i = 0; i < numBytes && interfaceData->i2cPort->available(); i++) {
        dataBuffer[i] = interfaceData->i2cPort->read();
    }

    return BMI2_OK;
}

/// @brief Helper function to read sensor registers over SPI
/// @param regAddress Start address to read
/// @param dataBuffer Buffer to store register values
/// @param numBytes Number of bytes to read
/// @param interfaceData Pointer to interface data, see BMI270_InterfaceData
/// @return Error code (0 is success, negative is failure, positive is warning)
BMI2_INTF_RETURN_TYPE BMI270::readRegistersSPI(uint8_t regAddress, uint8_t* dataBuffer, uint32_t numBytes, BMI270_InterfaceData* interfaceData)
{
    // Start transmission
    interfaceData->spiPort->beginTransaction(SPISettings(interfaceData->spiClockFrequency, MSBFIRST, SPI_MODE0));
    digitalWrite(interfaceData->spiCSPin, LOW);
    interfaceData->spiPort->transfer(regAddress | 0x80);

    // Read all requested bytes
    for (uint32_t i = 0; i < numBytes; i++) {
        dataBuffer[i] = interfaceData->spiPort->transfer(0);
    }

    // End transmission
    digitalWrite(interfaceData->spiCSPin, HIGH);
    interfaceData->spiPort->endTransaction();

    return BMI2_OK;
}

/// @brief Helper function to write sensor registers
/// @param regAddress Start address to write
/// @param dataBuffer Buffer to store register values
/// @param numBytes Number of bytes to write
/// @param interfacePtr Pointer to interface data, see BMI270_InterfaceData
/// @return Error code (0 is success, negative is failure, positive is warning)
BMI2_INTF_RETURN_TYPE BMI270::writeRegisters(uint8_t regAddress, const uint8_t* dataBuffer, uint32_t numBytes, void* interfacePtr)
{
    // Make sure the number of bytes is valid
    if (numBytes == 0) {
        return BMI2_E_COM_FAIL;
    }
    // Get interface data
    BMI270_InterfaceData* interfaceData = (BMI270_InterfaceData*)interfacePtr;

    // Determine which interface we're using
    switch (interfaceData->interface) {
        case BMI2_I2C_INTF:
            return writeRegistersI2C(regAddress, dataBuffer, numBytes, interfaceData);
            break;
        case BMI2_SPI_INTF:
            return writeRegistersSPI(regAddress, dataBuffer, numBytes, interfaceData);
            break;
        default:
            return BMI2_E_COM_FAIL;
            break;
    }
}

/// @brief Helper function to write sensor registers over I2C
/// @param regAddress Start address to write
/// @param dataBuffer Buffer to store register values
/// @param numBytes Number of bytes to write
/// @param interfaceData Pointer to interface data, see BMI270_InterfaceData
/// @return Error code (0 is success, negative is failure, positive is warning)
BMI2_INTF_RETURN_TYPE BMI270::writeRegistersI2C(uint8_t regAddress, const uint8_t* dataBuffer, uint32_t numBytes, BMI270_InterfaceData* interfaceData)
{
    // Begin transmission
    interfaceData->i2cPort->beginTransmission(interfaceData->i2cAddress);

    // Write the address
    interfaceData->i2cPort->write(regAddress);

    // Write all the data
    for (uint32_t i = 0; i < numBytes; i++) {
        interfaceData->i2cPort->write(dataBuffer[i]);
    }

    // End transmission
    if (interfaceData->i2cPort->endTransmission()) {
        return BMI2_E_COM_FAIL;
    }

    return BMI2_OK;
}

/// @brief Helper function to write sensor registers over SPI
/// @param regAddress Start address to write
/// @param dataBuffer Buffer to store register values
/// @param numBytes Number of bytes to write
/// @param interfaceData Pointer to interface data, see BMI270_InterfaceData
/// @return Error code (0 is success, negative is failure, positive is warning)
BMI2_INTF_RETURN_TYPE BMI270::writeRegistersSPI(uint8_t regAddress, const uint8_t* dataBuffer, uint32_t numBytes, BMI270_InterfaceData* interfaceData)
{
    // Begin transmission
    interfaceData->spiPort->beginTransaction(SPISettings(interfaceData->spiClockFrequency, MSBFIRST, SPI_MODE0));
    digitalWrite(interfaceData->spiCSPin, LOW);

    // Write the address
    interfaceData->spiPort->transfer(regAddress);

    // Write all the data
    for (uint32_t i = 0; i < numBytes; i++) {
        interfaceData->spiPort->transfer(dataBuffer[i]);
    }

    // End transmission
    digitalWrite(interfaceData->spiCSPin, HIGH);
    interfaceData->spiPort->endTransaction();

    return BMI2_OK;
}

/// @brief Helper function to delay for some amount of time
/// @param period Number of microseconds to delay
/// @param interfacePtr Pointer to interface data, see BMI270_InterfaceData
void BMI270::usDelay(uint32_t period, void* interfacePtr)
{
    delayMicroseconds(period);
}

/// @brief Helper function to generate the correct conversion value for accelerometer data
/// @param accRange Accelerometer range enum value
/// @return float conversion scalar
float BMI270::convertRawToGsScalar(uint8_t accRange)
{
    // accRange             | return value
    // -----------------------------------
    // BMI2_ACC_RANGE_2G    | 2
    // BMI2_ACC_RANGE_4G    | 4
    // BMI2_ACC_RANGE_8G    | 8
    // BMI2_ACC_RANGE_16G   | 16
    return ((2 << accRange) / 32768.0);
}

/// @brief Helper function to generate the correct conversion value for gyro data
/// @param gyrRange Gyro range enum value
/// @return float conversion scalar
float BMI270::convertRawToDegSecScalar(uint8_t gyrRange)
{
    // gyrRange             | return value
    // -----------------------------------
    // BMI2_GYR_RANGE_2000  | 2000
    // BMI2_GYR_RANGE_1000  | 1000
    // BMI2_GYR_RANGE_500   | 500
    // BMI2_GYR_RANGE_250   | 250
    // BMI2_GYR_RANGE_125   | 125
    return ((125 * (1 << (BMI2_GYR_RANGE_125 - gyrRange))) / 32768.0);
}
