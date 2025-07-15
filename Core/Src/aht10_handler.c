#include "aht10_handler.h"

bool init_aht10_sensor() {
    bool hardware_initialized = true;
    printf("Starting AHT10 sensor...\n\n");
    if (!aht10_Init()) {
        printf("AHT10 initialization failed.\n");
        hardware_initialized = false;
    } else {
        printf("AHT10 initialized successfully.\n\n");
        if(!aht10_StartMeasurement()) {
            printf("AHT10 measurement start failed.\n");
            hardware_initialized = false;
        } else {
            printf("AHT10 measurement started successfully.\n\n");
        }
    }
    return hardware_initialized;
}