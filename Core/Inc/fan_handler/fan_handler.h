#ifndef __FAN_HANDLER_H__
#define __FAN_HANDLER_H__

#include <stdint.h>
#include <stdbool.h>
#include "project_config.h"

/**
 * @brief Fan speed levels
 */
typedef enum {
    FAN_OFF = 0,
    FAN_LOW = 1,
    FAN_MEDIUM = 2,
    FAN_HIGH = 3
} FanSpeed;

/**
 * @brief Current fan RPM
 */
uint16_t currentFanRPM;

/**
 * @brief Initialize the fan handler module
 * @return true if initialization is successful, false otherwise
 */
bool FanHandlerInit(void);

/**
 * @brief Set the fan speed
 * @param speed The desired fan speed level
 * @return true if the speed is set successfully, false otherwise
 */
bool SetFanSpeed(FanSpeed speed);

/**
 * @brief Get the current fan speed level
 * @return The current fan speed level
 */
FanSpeed GetFanSpeed(void);

/**
 * @brief Update the fan RPM based on hall sensor interrupts
 */
void UpdateFanRPM(void);
#endif // __FAN_HANDLER_H__