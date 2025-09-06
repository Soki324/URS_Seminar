#include "state_machine_main.h"

SystemStateMachine stateMachine;

void StateMachineInit(void) {
    stateMachine.previousState = OFF;
    // Call the initial state function
    StateFunctionInit();
}

void StateFunctionInit(void) {
    bool ret = false;
    stateMachine.currentState = INIT_SYSTEM;
    if(InitVocSystem /*&& init_display_system*/) {
        ret = true;
    }
    if(ret) {
        HandleEvent(SYSTEM_INIT_SUCCESS_EVENT);
    } else {
        HandleEvent(SYSTEM_ERROR_EVENT);
    }
}

void StateFunctionCalibration(void) {
    stateMachine.currentState = CALIBRATION;
    // Start calibration process
    RunSensorsCalibration();
}

void StateFunctionIdleMeasurement(void) {
    stateMachine.currentState = IDLE_MEASUREMENT;
    // Start idle measurement process
    StartIdleMeasurement();
}

void StateFunctionSleep(void) {
    stateMachine.currentState = SLEEP;
    // Enter sleep mode
    EnterSleepMode();
}

void StateFunctionFilterAndMeasure(void) {
    stateMachine.currentState = FILTER_AND_MEASURE;
    // Start filter and measure process
    StartFilterAndMeasure();
}

void StateFunctionFault(void) {
    stateMachine.currentState = FAULT;
    // Handle fault state
    HandleFault();
}

void StateFunctionFilterError(void){
    stateMachine.currentState = FILTER_ERROR;
    // Handle filter error state
    HandleFilterError();
}

void HandleEvent(kSystemEvent event) {
    stateMachine.previousState = stateMachine.currentState;
    switch (event) {
        case SYSTEM_INIT_SUCCESS_EVENT:
            StateFunctionCalibration();
            break;
        case SYSTEM_ERROR_EVENT:
            StateFunctionFault();
            break;
        case CALIBRATION_COMPLETE_EVENT:
            // Handle calibration complete event
            break;
        case VOC_SAFE_EVENT:
            // Handle safe VOC levels
            break;
        case VOC_UNSAFE_EVENT:
            // Handle unsafe VOC levels
            break;
        case SLEEP_TIMEOUT_EVENT:
            // Handle sleep timeout event
            break;
        case FILTER_WARNING_EVENT:
            // Handle filter warning event
            break;
        case FILTER_ERROR_EVENT:
            // Handle filter error event
            break;
        default:
            // Handle unknown events
            break;
    }
}