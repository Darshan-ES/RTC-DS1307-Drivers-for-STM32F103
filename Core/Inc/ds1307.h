#ifndef __DS1307_H__
#define __DS1307_H__

#include "stm32f1xx_hal.h"

// DS1307 I2C Address
#define DS1307_ADDRESS       (0x68 << 1)

// Register Addresses
#define DS1307_REG_SECONDS   0x00
#define DS1307_REG_MINUTES   0x01
#define DS1307_REG_HOURS     0x02
#define DS1307_REG_DAY       0x03
#define DS1307_REG_DATE      0x04
#define DS1307_REG_MONTH     0x05
#define DS1307_REG_YEAR      0x06
#define DS1307_REG_CONTROL   0x07

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} RTC_Time;

HAL_StatusTypeDef DS1307_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef DS1307_SetTime(I2C_HandleTypeDef *hi2c, RTC_Time *time);
HAL_StatusTypeDef DS1307_GetTime(I2C_HandleTypeDef *hi2c, RTC_Time *time);

#endif // __DS1307_H__

