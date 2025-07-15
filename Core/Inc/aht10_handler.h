#ifndef __AHT10_HANDLER_H__
#define __AHT10_HANDLER_H__

#include "aht10.h"
#include "usart.h"

/**
 * Handler level initialization function for AHT10 sensor.
 * This function initializes the AHT10 sensor and starts measurement if successful.
 * @param None
 * @return bool - true if reading is successful, false otherwise
 */
bool init_aht10_sensor(void);



#endif /* AHT10_HANDLER_H */