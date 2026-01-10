#ifndef __STATE_MACHINE_MAIN_H__
#define __STATE_MACHINE_MAIN_H__

#include <stdbool.h>
#include <stdint.h>
#include "usart.h"
#include "project_config.h"
#include "display_handler.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "fan_handler.h"
#include "voc_handler.h"

/*
 * Finite State Machine (FSM) states for the system
 */
typedef enum {
    OFF,
    INIT_SYSTEM,
    CALIBRATION,
    IDLE_MEASUREMENT,
    SLEEP,
    FILTER_AND_MEASURE,
    FAULT,
    NOTIFY_FILTER
} kSystemFSMStates;

/*
 * Events for FSM transitions
 */
typedef enum {
    /* System initialization successful */
    SYSTEM_INIT_SUCCESS_EVENT = 0,
    /* System initialization failed */
    SYSTEM_ERROR_EVENT = 1,
    /* Calibration complete */
    CALIBRATION_COMPLETE_EVENT = 2,
    /* VOC concentration is within safe threshold */
    VOC_SAFE_EVENT = 3,
    /* VOC concentration is above safe threshold */
    VOC_UNSAFE_EVENT = 4,
    /* System woken up by timer interrupt */
    SLEEP_TIMEOUT_EVENT = 5,
    /* Filter VOC scrubbing low or filter replacement timeout */
    FILTER_WARNING_EVENT = 6,
    /* Notification for filter replacement done */
    NOTIFY_FILTER_COMPLETE = 7
} kSystemEvent;

typedef struct{
    kSystemFSMStates currentState;
    kSystemFSMStates previousState;
} SystemStateMachine;

extern SystemStateMachine stateMachine;

extern bool FilterWarningActive;

/**
 * Initialize the state machine, starting without a defined state and goes to INIT_STATE
 * @param None
 * @return None
 */
void StateMachineInit(void);

/**
 * Handle events and trigger state transitions
 * @param event The event to handle
 * @return None
 */
void HandleEvent(kSystemEvent event);


/********************************************************************************************
 * State functions
 *
 ********************************************************************************************/
void StateFunctionInit(void);
void StateFunctionCalibration(void);
void StateFunctionIdleMeasurement(void);
void StateFunctionSleep(void);
void StateFunctionFilterAndMeasure(void);
void StateFunctionFault(void);
void StateFunctionFilterError(void);

/********************************************************************************************
 * External function declarations
 *
 ********************************************************************************************/
extern uint8_t RunVocMeasurement(void);
extern bool RunSensorsCalibration(void);


#endif /* __STATE_MACHINE_MAIN_H__ */
