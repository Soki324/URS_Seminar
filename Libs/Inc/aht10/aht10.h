#ifndef __AHT10_H__
#define __AHT10_H__

#include <stdbool.h>
#include <stdint.h>
#include "i2c.h"

/*
* Datasheet for this IC is afwul, I pulled some information from different sources
* and made some assumptions, so please use this code at your own risk.
* Init sequece is not well documented, so I had to use examples from other projects.
* I've used this example as a reference: https://github.com/W-Linus/AHT10_STM32_HAL/blob/master/Drivers/AHT10/Inc/AHT10.h
*/

/* AHT10 I2C address and commands
* I've found these somewhere on the internet, but I can't find the source anymore
*/
#define AHT10_ADDRESS              0x38<<1  //chip I2C address no.1 for AHT10/AHT15/AHT20, address pin connected to GND

#define AHT10_INIT_CMD             0xE1     //initialization command for AHT10/AHT15
#define AHT10_START_MEASURMENT_CMD 0xAC     //start measurment command
#define AHT10_NORMAL_CMD           0xA8     //normal cycle mode command, no info in datasheet!!!
#define AHT10_SOFT_RESET_CMD       0xBA     //soft reset command

#define AHT10_INIT_NORMAL_MODE     0x00     //enable normal mode
#define AHT10_INIT_CYCLE_MODE      0x20     //enable cycle mode
#define AHT10_INIT_CMD_MODE        0x40     //enable command mode
#define AHT10_INIT_CAL_ENABLE      0x08     //load factory calibration coeff


#define AHT10_DATA_MEASURMENT_CMD  0x33     //no info in datasheet!!! my guess it is DAC resolution, saw someone send 0x00 instead
#define AHT10_DATA_NOP             0x00     //no info in datasheet!!!


#define AHT10_MEASURMENT_DELAY     80       //at least 75 milliseconds
#define AHT10_POWER_ON_DELAY       40       //at least 20..40 milliseconds
#define AHT10_CMD_DELAY            350      //at least 300 milliseconds, no info in datasheet!!!
#define AHT10_SOFT_RESET_DELAY     20       //less than 20 milliseconds

#define AHT10_FORCE_READ_DATA      true     //force to read data
#define AHT10_USE_READ_DATA        false    //force to use data from previous read
#define AHT10_ERROR                0xFF     //returns 255, if communication error is occurred

/**
* AHT10 Initialization Function
* @param None
* @return bool - true if initialization is successful, false otherwise
*/
bool aht10_Init(void);

/**
 * AHT10 Read Temperature and Humidity Function
 * @param temperature Pointer to store the temperature value
 * @param humidity Pointer to store the humidity value
 * @return bool - true if reading is successful, false otherwise
 */
bool aht10_ReadTemperatureAndHumidity(int32_t *temperature, uint32_t *humidity);

/**
* AHT10 Soft Reset Function
* @param None
* @return bool - true if soft reset is successful, false otherwise
*/
bool aht10_SoftReset(void);

/**
* AHT10 Start Measurement Function
* @param None
* @return bool - true if measurement start is successful, false otherwise
*/
bool aht10_StartMeasurement(void);

#endif /* __AHT10_H__ */