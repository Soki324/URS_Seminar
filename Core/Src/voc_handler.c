#include "voc_handler.h"

I2C_TypeDef* SPG40Intake = I2C1;
I2C_TypeDef* SPG40Exaust = I2C2;

int16_t error = 0;
uint16_t serial_number[3];
uint8_t serial_number_size = 3;
uint16_t default_rh = 0x8000;
uint16_t default_t = 0x6666;
GasIndexAlgorithmParams gas_index_algorithm_params;

bool init_voc_system(void) {
    bool hardware_initialized = true;

    if(!init_aht10_sensor){
        hardware_initialized = false;
    }

    printf("Starting SGP40 Intake sensor...\n\n");
    if (!sgp40_init(SPG40Intake)) {
        printf("SGP40 Intake initialization failed.\n");
        hardware_initialized = false;
    } else {
        printf("SGP40 Intake initialized successfully.\n\n");
    }

    printf("Starting SGP40 Exaust sensor...\n\n");
    if (!sgp40_init(SPG40Exaust)) {
        printf("SGP40 Exaust initialization failed.\n");
        hardware_initialized = false;
    } else {
        printf("SGP40 Exaust initialized successfully.\n\n");
    }

    if (!init_aht10_sensor()) {
        printf("AHT10 initialization failed.\n");
        hardware_initialized = false;
    } else {
        printf("AHT10 initialized successfully.\n\n");
    }

    return hardware_initialized;
}