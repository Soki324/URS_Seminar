#include "fan_handler.h"

uint16_t currentFanRPM = 0;

FanSpeed selectedFanspeed = FAN_OFF;

bool FanHandlerInit(void) {
    bool ret = false;
    // Initialize TIM2 for PWM control of the fan
    MX_TIM2_Init();
    // Start PWM on TIM2 Channel 1
    if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) == HAL_OK) {
        ret = true;
    }
    return ret;
}

bool SetFanSpeed(FanSpeed speed) {
    switch (speed)
    {
    case FAN_OFF:
        // Set PWM duty cycle to 0%
        TIM2->CCMR1=0;
        selectedFanspeed = FAN_OFF;
        break;
    case FAN_LOW:
        // Set PWM duty cycle to 25%
        TIM2->CCMR1=25;
        selectedFanspeed = FAN_LOW;
        break;
    case FAN_MEDIUM:
        // Set PWM duty cycle to 50%
        TIM2->CCMR1=50;
        selectedFanspeed = FAN_MEDIUM;
        break;
    case FAN_HIGH:
        // Set PWM duty cycle to 100%
        TIM2->CCMR1=100;
        selectedFanspeed = FAN_HIGH;
        break;
    default:
        break;
    }
    return true;
}

FanSpeed GetFanSpeed(void) {
    return selectedFanspeed;
}

void UpdateFanRPM(void) {
    // Update the fan RPM based on hall sensor interrupts
}