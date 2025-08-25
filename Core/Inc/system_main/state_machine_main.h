#ifndef __STATE_MACHINE_MAIN_H__
#define __STATE_MACHINE_MAIN_H__

#include <stdbool.h>
#include <stdint.h>
#include "usart.h"
#include "project_config.h"

/*
 * Finite State Machine (FSM) states for the system
 */
typedef enum kSystemFSMStates{
    INIT_SYSTEM,
    CALIBRATION,
    IDLE_MEASUREMENT,
    SLEEP,
    FILTER_AND_MEASURE,
    FAULT,
    FILTER_ERROR
};


/**
 * State functions
 */
void state_init(void);
void state_calibration(void);
void state_idle_measurement(void);
void state_sleep(void);
void state_filter_and_measure(void);
void state_fault(void);
void state_filter_error(void);

/*
 * Events for FSM transitions
 */
typedef enum kSystemEvent {
    /* System initialization successful */
    SYSTEM_INIT_SUCCESS = 0,
    /* System initialization failed */
    SYSTEM_ERROR = 1,
    /* Calibration complete */
    CALIBRATION_COMPLETE = 2,
    /* VOC concentration is within safe threshold */
    VOC_SAFE = 3,
    /* VOC concentration is above safe threshold */
    VOC_UNSAFE = 4,
    /* System woken up by timer interrupt */
    SLEEP_TIMEOUT = 5,
    /* Filter VOC scrubbing low or filter replacement timeout */
    FILTER_WARNING = 6,
    /* Filter VOC scrubbing below threshold or fan failure */
    FILTER_ERROR = 7
};

typedef struct{
    SystemFSMStates currentState;
    SystemFSMStates previousState;
} SystemStateMachine;


/**
 * Initialize the state machine, starting without a defined state and goes to INIT_STATE
 * @param None
 * @return None
 */
void StateMachineInit();

/**
 * Handle events and trigger state transitions
 * @param event The event to handle
 * @return None
 */
void HandleEvent(kSystemEvent event);

#endif /* __STATE_MACHINE_MAIN_H__ */