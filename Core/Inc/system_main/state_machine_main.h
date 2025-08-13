#ifndef __STATE_MACHINE_MAIN_H__
#define __STATE_MACHINE_MAIN_H__

#include <stdbool.h>
#include <stdint.h>
#include "project_config.h"

/*
 * Finite State Machine (FSM) states for the system
 */
typedef enum SystemFSMStates{
    INIT_SYSTEM,
    CALIBRATION,
    IDLE_MEASUREMENT,
    SLEEP,
    FILTER_AND_MEASURE,
    FAULT,
    FILTER_ERROR
};

/*
 * Events for FSM transitions
 */
typedef enum SystemEvent {
    SYSTEM_INIT_SUCCESS = 0,
    SYSTEM_ERROR = 1,
    CALIBRATION_COMPLETE = 2,
    VOC_SAFE = 3,
    VOC_UNSAFE = 4,
    SLEEP_TIMEOUT = 5,
    FILTER_ISSUE = 6
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
void state_machine_init();

#endif /* __STATE_MACHINE_MAIN_H__ */