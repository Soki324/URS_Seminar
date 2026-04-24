#ifndef IRQ_HANDLER_H
#define IRQ_HANDLER_H
#include "tim.h"
#include "fan_handler.h"
#include "state_machine_main.h"

/**
  ******************************************************************************
  * @file    irq_handler.h
  * @brief   This file contains declarations of the interrupt handlers.
  ******************************************************************************
*/

uint32_t sleep_wakeup_count = 0; // Counter to track the number of wakeups from sleep mode
uint32_t sleep_wakeup_limit = PROJECT_CONFIG_SLEEP_TIMEOUT_WAKEUP_COUNT; // Limit for wakeups before going back to sleep

#endif // IRQ_HANDLER_H
