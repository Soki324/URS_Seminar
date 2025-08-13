#ifndef __DISPLAY_HANDLER_H__
#define __DISPLAY_HANDLER_H__
#include "usart.h"
#include "i2c.h"
#include "ssd1306.h"
#include "project_config.h"

typedef enum DisplayFSMStates{
    INIT = 0,
    SENSOR_INIT = 1,
    MAIN_MENU = 2,
    SCREEN_SLEEP = 3,
    SCREEN_SPLASH_BOOT = 4
};

#endif /* __DISPLAY_HANDLER_H__ */