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
    if(InitVocSystem() /*&& init_display_system()*/) {
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
    if(RunSensorsCalibration()) {
        HandleEvent(CALIBRATION_COMPLETE_EVENT);
    } else {
        HandleEvent(SYSTEM_ERROR_EVENT);
    }
}

void StateFunctionIdleMeasurement(void) {
    stateMachine.currentState = IDLE_MEASUREMENT;
    uint8_t measurement_ret = RunVocMeasurement();
    if(measurement_ret < 5) {
        if(calculated_voc_intake < PROJECT_CONFIG_VOC_SAFE_THRESHOLD && calculated_voc_exaust < PROJECT_CONFIG_VOC_SAFE_THRESHOLD) {
            // VOC levels are safe
            global_air_quality_safe = true;
            HandleEvent(VOC_SAFE_EVENT);
        } else {
            // VOC levels are unsafe
            global_air_quality_safe = false;
            HandleEvent(VOC_UNSAFE_EVENT);
        }
    } else {
        // Measurement failed
        HandleEvent(SYSTEM_ERROR_EVENT);
    }
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
    stateMachine.currentState = NOTIFY_FILTER;
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
            StateFunctionIdleMeasurement();
            break;
        case VOC_SAFE_EVENT:
            StateFunctionSleep();
            break;
        case VOC_UNSAFE_EVENT:
            StateFunctionFilterAndMeasure();
            break;
        case SLEEP_TIMEOUT_EVENT:
            StateFunctionIdleMeasurement();
            break;
        case FILTER_WARNING_EVENT:
            // Handle filter warning event
            break;
        case NOTIFY_FILTER_COMPLETE:
            // Handle filter replacement notification
            break;
        default:
            // Handle unknown events
            break;
    }
}