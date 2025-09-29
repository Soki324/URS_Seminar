#include "voc_handler.h"


I2C_HandleTypeDef* SPG40Intake = &hi2c1;
I2C_HandleTypeDef* SPG40Exaust = &hi2c2;

uint16_t sraw_voc_intake;
uint16_t sraw_voc_exaust;
int32_t calculated_voc_intake;
int32_t calculated_voc_exaust;
uint32_t rh;
int32_t t;

bool temp_and_hum_sensor_initialized ;
bool sgp40_intake_initialized;
bool sgp40_exaust_initialized;
bool hardware_initialized;

GasIndexAlgorithmParams gas_index_algorithm_intake_params;
GasIndexAlgorithmParams gas_index_algorithm_exaust_params;

bool voc_sensors_calibrated = false;

int16_t error = 0;
uint16_t serial_number[3];
uint8_t serial_number_size = 3;

bool InitVocSystem(void) {

    printf("Initializing VOC system...\n\n");
    if(!InitTempAndHumSensor()) {
        temp_and_hum_sensor_initialized = false;
    } else {
        temp_and_hum_sensor_initialized = true;
    }

    printf("Starting SGP40 Intake sensor...\n\n");
    error = sensirion_i2c_hal_select_bus(SPG40Intake);
    if (error) {
        printf("Error selecting I2C bus for SGP40 Intake: %i\n", error);
        sgp40_intake_initialized = false;
        return false;
    } else {
        printf("I2C bus for SGP40 Intake selected successfully.\n\n");
        error = sgp40_get_serial_number(serial_number, serial_number_size);
        if (error) {
            printf("SGP40 Intake initialization failed, error code: %d\n", error);
            sgp40_intake_initialized = false;
        } else {
            /* Turn off heater for SGP40 Intake
            * Found this in init of nevermore-controller, not sure if it's necessary
            */
            error = sgp40_turn_heater_off();
            if (error) {
                printf("Error turning off heater for SGP40 Intake: %i\n", error);
                sgp40_intake_initialized = false;
            } else {
                sgp40_intake_initialized = true;
                printf("SGP40 Intake initialized successfully.\n\n");
            }
        }
    }

    printf("Starting SGP40 Exaust sensor...\n\n");
    error = sensirion_i2c_hal_select_bus(SPG40Exaust);
    if (error) {
        printf("Error selecting I2C bus for SGP40 Exaust: %i\n", error);
        sgp40_exaust_initialized = false;
        return false;
    } else {
        printf("I2C bus for SGP40 Exaust selected successfully.\n\n");
        error = sgp40_get_serial_number(serial_number, serial_number_size);
        if (error) {
            printf("SGP40 Exaust initialization failed, error code: %d\n", error);
            sgp40_exaust_initialized = false;
        } else {
            /* Turn off heater for SGP40 Exaust
            * Found this in init of nevermore-controller, not sure if it's necessary
            */
            error = sgp40_turn_heater_off();
            if (error) {
                printf("Error turning off heater for SGP40 Exaust: %i\n", error);
                sgp40_exaust_initialized = false;
            } else {
                sgp40_exaust_initialized = true;
                printf("SGP40 Exaust initialized successfully.\n\n");
            }
        }
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


uint8_t RunVocMeasurement(void) {

    uint8_t return_value = 0;

    sensirion_i2c_hal_sleep_usec(SPG40_SLEEP_TIME_US);
    if(temp_and_hum_sensor_initialized) {
        /* Add check to return status */
        RunTempAndHumSensorMeasurement();
        t = sensor_temperature_c;
        rh = sensor_humidity_percent;
    } else {
        printf("Warning temperature and humidity sensor not initialized properly, using default values\n");
        return_value |= 0x01; // Set bit 0 to indicate temperature and humidity sensor failure
        t = SPG40_DEFAULT_T;
        rh = SPG40_DEFAULT_RH;
    }

    ConvertTemperatureAndHumidityToTicks();

    if(sgp40_intake_initialized) {
        sensirion_i2c_hal_select_bus(SPG40Intake);
        error = sgp40_measure_raw_signal(temperature_ticks, humidity_ticks, &sraw_voc_intake);
        if (error) {
            printf("Error executing sgp40_measure_raw_signal() for intake: %i\n", error);
            return_value |= 0x02; // Set bit 2 to indicate SGP40 Intake sensor failure
            sraw_voc_intake = 0;
            calculated_voc_intake = -1;
        } else {
            printf("SRAW VOC Intake: %d\n", sraw_voc_intake);
            // Calculate gas index using the Gas Index Algorithm
            GasIndexAlgorithm_process(&gas_index_algorithm_intake_params, sraw_voc_intake, &calculated_voc_intake);
            printf("Calculated VOC Intake: %ld\n\n", calculated_voc_intake);
        }
    } else {
        printf("Warning SGP40 Intake sensor not initialized properly, using default values\n");
        return_value |= 0x02; // Set bit 1 to indicate SGP40 Intake sensor failure
        sraw_voc_intake = 0;
        calculated_voc_intake = -1;
    }

    if(sgp40_exaust_initialized) {
        sensirion_i2c_hal_select_bus(SPG40Exaust);
        error = sgp40_measure_raw_signal(temperature_ticks, humidity_ticks, &sraw_voc_exaust);
        if (error) {
            printf("Error executing sgp40_measure_raw_signal() for exaust: %i\n", error);
            return_value |= 0x04; // Set bit 3 to indicate SGP40 Exaust sensor failure
            sraw_voc_exaust = 0;
            calculated_voc_exaust = -1;
        } else {
            printf("SRAW VOC Exaust: %d\n", sraw_voc_exaust);
            // Calculate gas index using the Gas Index Algorithm
            GasIndexAlgorithm_process(&gas_index_algorithm_exaust_params, sraw_voc_exaust, &calculated_voc_exaust);
            printf("Calculated VOC Exaust: %ld\n\n", calculated_voc_exaust);
        }
    } else {
        printf("Warning SGP40 Exaust sensor not initialized properly, using default values\n");
        return_value |= 0x04; // Set bit 3 to indicate SGP40 Exaust sensor failure
        sraw_voc_exaust = 0;
        calculated_voc_exaust = -1;
    }
    return return_value;
}

bool RunSensorSelfTest(uint8_t sensor_number) {
    uint16_t test_result;
    int16_t error;

    if (sensor_number == 0) { // SGP40 Intake
        sensirion_i2c_hal_select_bus(SPG40Intake);
        error = sgp40_execute_self_test(&test_result);
        if (error) {
            printf("Error executing self-test for SGP40 Intake: %i\n", error);
            return false;
        }
    } else if (sensor_number == 1) { // SGP40 Exaust
        sensirion_i2c_hal_select_bus(SPG40Exaust);
        error = sgp40_execute_self_test(&test_result);
        if (error) {
            printf("Error executing self-test for SGP40 Exaust: %i\n", error);
            return false;
        }
    } else {
        printf("Invalid sensor number for self-test.\n");
        return false;
    }

    if( test_result == 0xD400) {
        printf("SGP40 Intake Self-Test Passed.\n");
    } else {
        printf("SGP40 Intake Self-Test Failed: 0x%04X\n", test_result);
        return false;
    }

    return true;
}

bool RunSensorsCalibration(void) {
    bool ret = false;
    printf("Calibrating VOC sensors...\n\n");
    if(hardware_initialized) {
        GasIndexAlgorithm_reset(&gas_index_algorithm_intake_params);
        GasIndexAlgorithm_reset(&gas_index_algorithm_exaust_params);
        RunVocMeasurement();
        uint8_t voc_measurement_status = RunVocMeasurement();
    if(voc_measurement_status < 5) {
        ret = true;
        voc_sensors_calibrated = true;
    }
    } else {
        printf("Hardware not initialized properly, cannot calibrate VOC sensors.\n");
    }
    return ret;
}

void ConvertTemperatureAndHumidityToTicks() {
    // Calculate ticks using the formula from SGP40 datasheet, table 10
    temperature_ticks = (uint16_t)((t + 45) * 65535 / 175);
    humidity_ticks = (uint16_t)((rh * 65535) / 100);
}