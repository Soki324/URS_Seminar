#include "temp_and_hum_sens.h"

bool init_temp_and_hum_sensor() {
    bool hardware_initialized = true;
    printf("Starting temperature and humidity sensor...\n\n");
    if (!aht10_Init()) {
        printf("AHT10 initialization failed.\n");
        hardware_initialized = false;
    } else {
        printf("Temperature and humidity sensor initialized successfully.\n\n");
        if(!aht10_StartMeasurement()) {
            printf("Temperature and humidity sensor start measurement failed.\n");
            hardware_initialized = false;
        } else {
            printf("temperature and humidity sensor measurement started successfully.\n\n");
        }
    }
    return hardware_initialized;
}


void run_temp_and_hum_sensor_measurement(void) {

    if (aht10_ReadTemperatureAndHumidity(&sensor_temperature, &sensor_humidity)) {
        printf("Temperature: %d, Humidity: %d\n", sensor_temperature, sensor_temperature);
    } else {
        printf("Error reading temperature and humidity.\n");
    }

}