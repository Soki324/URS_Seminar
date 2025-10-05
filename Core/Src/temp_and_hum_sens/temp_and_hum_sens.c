#include "temp_and_hum_sens.h"

int32_t sensor_temperature_c;
uint32_t sensor_humidity_percent;

bool InitTempAndHumSensor() {
    bool hardware_initialized = true;
    printf("Starting temperature and humidity sensor...\n\n");
    if (!AHT10Init()) {
        printf("AHT10 initialization failed.\n");
        hardware_initialized = false;
    } else {
        printf("Temperature and humidity sensor initialized successfully.\n\n");
        if(!AHT10StartMeasurement()) {
            printf("Temperature and humidity sensor start measurement failed.\n");
            hardware_initialized = false;
        } else {
            printf("temperature and humidity sensor measurement started successfully.\n\n");
        }
    }
    return hardware_initialized;
}


bool RunTempAndHumSensorMeasurement(void) {

    if (AHT10ReadTemperatureAndHumidity(&sensor_temperature_c, &sensor_humidity_percent)) {
        printf("Temperature: %ld, Humidity: %lu\n", sensor_temperature_c, sensor_humidity_percent);
    } else {
        printf("Error reading temperature and humidity.\n");
    }

}