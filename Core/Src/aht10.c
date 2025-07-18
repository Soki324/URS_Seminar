#include "aht10.h"
#include "i2c.h"

bool aht10_Init(){

    uint8_t initCommand[3] = {AHT10_INIT_CMD, AHT10_INIT_NORMAL_MODE | AHT10_INIT_CYCLE_MODE | AHT10_INIT_CMD_MODE | AHT10_INIT_CAL_ENABLE, 0x00};
    initCommand[0] = AHT10_INIT_CMD; // Initialization command
    initCommand[1] = AHT10_INIT_CAL_ENABLE; // Enable factory calibration
    initCommand[2] = AHT10_INIT_NORMAL_MODE; // Set normal mode 
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c3, AHT10_ADDRESS, initCommand, sizeof(initCommand), HAL_MAX_DELAY);
    
    if (status != HAL_OK) {
        return false; // Initialization failed
    }
    
    HAL_Delay(AHT10_POWER_ON_DELAY); // Wait for the sensor to power up
    return true; // Initialization successful
}

bool aht10_SoftReset(void) {

    uint8_t resetCommand = AHT10_SOFT_RESET_CMD;
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c3, AHT10_ADDRESS, &resetCommand, 1, HAL_MAX_DELAY);
    
    if (status != HAL_OK) {
        return false; // Soft reset failed
    }
    
    HAL_Delay(AHT10_SOFT_RESET_DELAY); // Wait for the soft reset to complete
    return true; // Soft reset successful

}

bool aht10_StartMeasurement(void) {

    uint8_t startCommand[3];
    startCommand[0] = AHT10_START_MEASURMENT_CMD; // Start measurement command
    startCommand[1] = AHT10_DATA_MEASURMENT_CMD; // Data measurement command
    startCommand[2] = AHT10_DATA_NOP; // No operation command, can be set to 0x00 or any other value as per the datasheet
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c3, AHT10_ADDRESS, startCommand, sizeof(startCommand), HAL_MAX_DELAY);
    
    if (status != HAL_OK) {
        return false; // Measurement start failed
    }
    
    HAL_Delay(AHT10_MEASURMENT_DELAY); // Wait for the measurement to complete
    return true; // Measurement started successfully

}

bool aht10_ReadTemperatureAndHumidity(int32_t *temperature, uint32_t *humidity) {

    if (temperature == NULL || humidity == NULL) {
        return false; // Invalid pointers
    }
    if(!aht10_StartMeasurement()) {
        return false; // Failed to start measurement
    }
    uint8_t data[6]; // Buffer to hold the received data
    HAL_StatusTypeDef status = HAL_I2C_Master_Receive(&hi2c3, AHT10_ADDRESS, data, sizeof(data), HAL_MAX_DELAY);
    if (status != HAL_OK) {
        return false; // Read failed
    }
    
    // Process the received data
    // Based on AHT10 driver by Adafruit: https://github.com/adafruit/Adafruit_AHTX0/blob/master/Adafruit_AHTX0.cpp
    uint32_t rawHumidity = data[1];
    rawHumidity <<= 8;
    rawHumidity |= data[2];
    rawHumidity <<= 4;
    rawHumidity |= data[3] >> 4;
    *humidity = (rawHumidity * 100) / 1048576; // Convert raw humidity to percentage

    uint32_t rawTemperature = data[3] & 0x0F;
    rawTemperature <<= 8;
    rawTemperature |= data[4];
    rawTemperature <<= 8;
    rawTemperature |= data[5];
    *temperature = (rawTemperature * 200) / 1048576 - 50; // Convert raw temperature to degrees Celsius
    
    // Convert raw values to actual temperature and humidity
    *humidity = (rawHumidity * 100) / 1048576; // Humidity in percentage
    *temperature = ((rawTemperature * 200) / 1048576) - 50; // Temperature in degrees Celsius
    
    return true; // Read successful
}
