#ifndef __AHT10_HANDLER_H__
#define __AHT10_HANDLER_H__

#include "aht10.h"
#include "usart.h"
#include "project_config.h"

extern int32_t sensor_temperature;
extern uint32_t sensor_humidity;

/**
 * Handler level initialization function for AHT10 sensor.
 * This function initializes the AHT10 sensor and starts measurement if successful.
 * @param None
 * @return bool - true if reading is successful, false otherwise
 */
bool InitTempAndHumSensor(void);

/**
 * Gets the temperature and humidity readings from the sensor.
 * @param None
 * @return None
 */
void RunTempAndHumSensorMeasurement(void);


#endif /* AHT10_HANDLER_H */