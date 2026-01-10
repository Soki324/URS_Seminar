#ifndef __VOC_HANDLER_H__
#define __VOC_HANDLER_H__
#include "usart.h"
#include "i2c.h"
#include "sensirion_common.h"
#include "sgp40_i2c.h"
#include "sensirion_i2c_hal.h"
#include "sensirion_gas_index_algorithm.h"
#include "temp_and_hum_sens.h"

/* SGP40 sensor sleep time in microseconds */
#define SPG40_SLEEP_TIME_US 1000000
/* Default temperature and humidity values for SGP40 sensor, value represents 50% */
#define SPG40_DEFAULT_RH 0x8000
/* Default temperature value for SGP40 sensor, value represents 20C */
#define SPG40_DEFAULT_T 0x6666

extern uint16_t sraw_voc_intake;
extern uint16_t sraw_voc_exaust;
extern int32_t calculated_voc_intake;
extern int32_t calculated_voc_exaust;
extern uint32_t rh;
extern int32_t t;
extern uint16_t temperature_ticks;
extern uint16_t humidity_ticks;

extern bool global_air_quality_safe;

extern bool temp_and_hum_sensor_initialized ;
extern bool sgp40_intake_initialized;
extern bool sgp40_exaust_initialized;
extern bool hardware_initialized;
extern bool voc_sensors_calibrated;

extern GasIndexAlgorithmParams gas_index_algorithm_intake_params;
extern GasIndexAlgorithmParams gas_index_algorithm_exaust_params;

/**
 * Handler level initialization function for VOC sensor.
 * This function initializes the SGP40 sensor and starts measurement if successful.
 * @param None
 * @return bool - true if reading is successful, false otherwise
 */
bool InitVocSystem(void);

/**
 * Handler level initialization function for VOC sensor.
 * This function initializes the SGP40 sensor and starts measurement if successful.
 * @param None
 * @note return values are:
 *  0 byte -> temperature and humidity sensor status:
 *      0 - success, used measured temperature and humidity, 1 - fail, used default temperature and humidity
 *  1 byte -> intake sensor status:
 *      0 - success, 1 - fail
 *  2 byte -> exaust sensor status:
 *     0 - success, 1 - fail
 * 
 *  0 - success, used measured temperature and humidity, both voc sensors values read
 *  1 - success, used default temperature and humidity (temperature and humidity sensor not working), both voc sensors values read
 *  2 - success, used measured temperature and humidity, intake not working, only exaust voc sensor value read
 *  3 - success, used default temperature and humidity (temperature and humidity sensor not working), only intake voc sensor value read, exaust sensor not working
 *  4 - success, used measured temperature and humidity, only intake voc sensor value read, exaust not working
 *  5 - success, used default temperature and humidity (temperature and humidity sensor not working), intake voc sensor not working, only exaust voc sensor value read
 *  6 - fail, used measured temperature and humidity, no voc sensor values read
 *  7 - fail, used default temperature and humidity (temperature and humidity sensor not working), no voc sensor values read
 * @return Returns 0 on success, 1 - 5 on partial success, 6 - 7 on failure
 */
uint8_t RunVocMeasurement(void);

/**
 * Converts temperature and humidity values to ticks.
 * Ticks are formatted values required by SGP40 sensor for compensation.
 * Formula found in SGP40 datasheet, table 10.
 * @param None
 * @return None
 */
void ConvertTemperatureAndHumidityToTicks(void);

/**
 * Runs self-test for specified SGP40 sensor.
 * @param sensor_number - 0 for intake sensor, 1 for exaust sensor
 * @return bool - true if self-test passed, false otherwise
 */
bool RunSensorSelfTest(uint8_t sensor_number);

#endif /* __VOC_HANDLER_H__ */
