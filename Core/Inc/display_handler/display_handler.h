#ifndef __DISPLAY_HANDLER_H__
#define __DISPLAY_HANDLER_H__
#include "usart.h"
#include "i2c.h"
#include "ssd1306.h"
#include "project_config.h"

typedef enum {
    kINIT = 0,
    kSENSOR_INIT = 1,
    kMAIN_MENU = 2,
    kSCREEN_SLEEP = 3,
    kSCREEN_SPLASH_BOOT = 4
} DisplayFSMStates;



#endif /* __DISPLAY_HANDLER_H__ */