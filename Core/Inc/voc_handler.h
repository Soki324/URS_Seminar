#ifndef __VOC_HANDLER_H__
#define __VOC_HANDLER_H__
#include "usart.h"
#include "i2c.h"
#include "sensirion_common.h"
#include "sgp40_i2c.h"
#include "sensirion_i2c_hal.h"
#include "sensirion_gas_index_algorithm.h"
#include "aht10_handler.h"

    uint16_t sraw_voc;
    int32_t calculated_voc;
    sensirion_i2c_hal_sleep_usec(1000000);
    uint32_t rh;
    int32_t t;

/**
 * Handler level initialization function for VOC sensor.
 * This function initializes the SGP40 sensor and starts measurement if successful.
 * @param None
 * @return bool - true if reading is successful, false otherwise
 */
bool init_voc_system(void);


void run_voc_measurement(void) {
    for (int i = 0; i < 60; i++) {
        sensirion_i2c_hal_sleep_usec(1000000);
        aht10_ReadTemperatureAndHumidity(&t, &rh);

        error = sgp40_measure_raw_signal(t, rh, &sraw_voc);
        if (error) {
            printf("Error executing sgp40_measure_raw_signal(): %i\n", error);
        } else {
            printf("SRAW VOC: %d\n", sraw_voc);
            // Calculate gas index using the Gas Index Algorithm
            GasIndexAlgorithm_process(&gas_index_algorithm_params, &sraw_voc, &calculated_voc);
            printf("Calculated VOC: %d\n\n", calculated_voc);
        }
    }
}

#endif /* __VOC_HANDLER_H__ */