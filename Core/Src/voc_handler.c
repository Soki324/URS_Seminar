#include "voc_handler.h"


I2C_TypeDef* SPG40Intake = I2C1;
I2C_TypeDef* SPG40Exaust = I2C2;


int16_t error = 0;
uint16_t serial_number[3];
uint8_t serial_number_size = 3;

bool init_voc_system(void) {

    if(!init_temp_and_hum_sensor()) {
        temp_and_hum_sensor_initialized = false;
    } else {
        temp_and_hum_sensor_initialized = true;
    }

    printf("Starting SGP40 Intake sensor...\n\n");
    if (!sgp40_init(SPG40Intake)) {
        printf("SGP40 Intake initialization failed.\n");
        sgp40_intake_initialized = false;
    } else {
        sgp40_intake_initialized = true;
        printf("SGP40 Intake initialized successfully.\n\n");
    }

    printf("Starting SGP40 Exaust sensor...\n\n");
    if (!sgp40_init(SPG40Exaust)) {
        printf("SGP40 Exaust initialization failed.\n");
        sgp40_exaust_initialized = false;
    } else {
        sgp40_exaust_initialized = true;
        printf("SGP40 Exaust initialized successfully.\n\n");
    }

    if (!sgp40_intake_initialized || !sgp40_exaust_initialized || !temp_and_hum_sensor_initialized) {
        printf("Hardware initialization failed.\n");
        hardware_initialized = false;
    } else {
        hardware_initialized = true;
        printf("Hardware initialized successfully.\n\n");
    }

    return hardware_initialized;
}


uint8_t run_voc_measurement(void) {

    uint8_t return_value = 0;

    sensirion_i2c_hal_sleep_usec(SPG40_SLEEP_TIME_US);
    if(temp_and_hum_sensor_initialized) {
        run_temp_and_hum_sensor_measurement();
        t = sensor_temperature;
        rh = sensor_humidity;
    } else {
        printf("Warning temperature and humidity sensor not initialized properly, using default values\n");
        return_value |= 0x01; // Set bit 0 to indicate temperature and humidity sensor failure
        t = SPG40_DEFAULT_T;
        rh = SPG40_DEFAULT_RH;
    }

    if(sgp40_intake_initialized) {
        sensirion_i2c_hal_select_bus(SPG40Intake);
        error = sgp40_measure_raw_signal(t, rh, &sraw_voc_intake);
        if (error) {
            printf("Error executing sgp40_measure_raw_signal() for intake: %i\n", error);
            return_value |= 0x02; // Set bit 2 to indicate SGP40 Intake sensor failure
            sraw_voc_intake = 0;
            calculated_voc_intake = -1;
        } else {
            printf("SRAW VOC Intake: %d\n", sraw_voc_intake);
            // Calculate gas index using the Gas Index Algorithm
            GasIndexAlgorithm_process(&gas_index_algorithm_intake_params, sraw_voc_intake, &calculated_voc_intake);
            printf("Calculated VOC Intake: %d\n\n", calculated_voc_intake);
        }
    } else {
        printf("Warning SGP40 Intake sensor not initialized properly, using default values\n");
        return_value |= 0x02; // Set bit 1 to indicate SGP40 Intake sensor failure
        sraw_voc_intake = 0;
        calculated_voc_intake = -1;
    }

    if(sgp40_exaust_initialized) {
        sensirion_i2c_hal_select_bus(SPG40Exaust);
        error = sgp40_measure_raw_signal(t, rh, &sraw_voc_exaust);
        if (error) {
            printf("Error executing sgp40_measure_raw_signal() for exaust: %i\n", error);
            return_value |= 0x04; // Set bit 3 to indicate SGP40 Exaust sensor failure
            sraw_voc_exaust = 0;
            calculated_voc_exaust = -1;
        } else {
            printf("SRAW VOC Exaust: %d\n", sraw_voc_exaust);
            // Calculate gas index using the Gas Index Algorithm
            GasIndexAlgorithm_process(&gas_index_algorithm_exaust_params, sraw_voc_exaust, &calculated_voc_exaust);
            printf("Calculated VOC Exaust: %d\n\n", calculated_voc_exaust);
        }
    } else {
        printf("Warning SGP40 Exaust sensor not initialized properly, using default values\n");
        return_value |= 0x04; // Set bit 2 to indicate SGP40 Exaust sensor failure
        sraw_voc_exaust = 0;
        calculated_voc_exaust = -1;
    }
    return return_value;
}