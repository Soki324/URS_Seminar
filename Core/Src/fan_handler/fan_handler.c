#include "fan_handler.h"

uint16_t currentFanRPM = 0;

bool FanHandlerInit(void) {
    // Initialize fan hardware and settings
    return true;
}

bool SetFanSpeed(FanSpeed speed) {
    // Set the fan speed
    return true;
}

FanSpeed GetFanSpeed(void) {
    // Get the current fan speed
    return 0;
}

void UpdateFanRPM(void) {
    // Update the fan RPM based on hall sensor interrupts
}