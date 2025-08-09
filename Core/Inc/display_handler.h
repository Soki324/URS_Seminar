#ifndef __DISPLAY_HANDLER_H__
#define __DISPLAY_HANDLER_H__
#include "usart.h"
#include "i2c.h"
#include "ssd1306.h"

enum class {
    Init,
    SensorInit,
    MainMenu,
    ScreenSleep,
    ScreenSplashBoot
} DisplayFSMStates;

#endif /* __DISPLAY_HANDLER_H__ */