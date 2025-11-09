#include "fan_handler.h"

volatile uint32_t fan_pulse_count = 0;
uint32_t currentFanRPM = 0;

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

bool RunFanSelfTest(void) {
    // Perform a self-test on the fan hardware
    return true;
}

void UpdateFanRPM(void) {
    // Clear the previous pulse count
    fan_pulse_count = 0;
    // Set the fan speed to medium for testing
    SetFanSpeed(FAN_MEDIUM);
    // Start tachometer interrupt
    StartTachInterrupt();
    // Start non blocking timer for 15 seconds

}

void StartTachInterrupt(void) {
    // Enable EXTI interrupt for fan tachometer pin
    HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

void StopTachInterrupt(void) {
    // Disable EXTI interrupt for fan tachometer pin
    HAL_NVIC_DisableIRQ(EXTI1_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == FanTach_Pin) {
        fan_pulse_count++;
    }
}