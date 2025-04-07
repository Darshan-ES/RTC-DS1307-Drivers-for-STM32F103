#include "ds1307.h"


extern I2C_HandleTypeDef hi2c1;

// Convert decimal to BCD
static uint8_t decToBcd(uint8_t val) {
    return ((val / 10 * 16) + (val % 10));
}

// Convert BCD to decimal
static uint8_t bcdToDec(uint8_t val) {
    return ((val / 16 * 10) + (val % 16));
}

HAL_StatusTypeDef DS1307_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t ctrl_data[2] = {DS1307_REG_CONTROL, 0x00}; // Disable square wave output
    return HAL_I2C_Master_Transmit(hi2c, DS1307_ADDRESS, ctrl_data, 2, HAL_MAX_DELAY);
}

HAL_StatusTypeDef DS1307_SetTime(I2C_HandleTypeDef *hi2c, RTC_Time *time) {
    uint8_t buffer[8];
    buffer[0] = DS1307_REG_SECONDS;
    buffer[1] = decToBcd(time->seconds);
    buffer[2] = decToBcd(time->minutes);
    buffer[3] = decToBcd(time->hours);
    buffer[4] = decToBcd(time->day);
    buffer[5] = decToBcd(time->date);
    buffer[6] = decToBcd(time->month);
    buffer[7] = decToBcd(time->year);

    return HAL_I2C_Master_Transmit(hi2c, DS1307_ADDRESS, buffer, 8, HAL_MAX_DELAY);
}

HAL_StatusTypeDef DS1307_GetTime(I2C_HandleTypeDef *hi2c, RTC_Time *time) {
    uint8_t buffer[7];
    uint8_t reg = DS1307_REG_SECONDS;

    if (HAL_I2C_Master_Transmit(hi2c, DS1307_ADDRESS, &reg, 1, HAL_MAX_DELAY) != HAL_OK)
        return HAL_ERROR;

    if (HAL_I2C_Master_Receive(hi2c, DS1307_ADDRESS, buffer, 7, HAL_MAX_DELAY) != HAL_OK)
        return HAL_ERROR;

    time->seconds = bcdToDec(buffer[0] & 0x7F); // Mask CH bit
    time->minutes = bcdToDec(buffer[1]);
    time->hours = bcdToDec(buffer[2] & 0x3F);   // 24-hour format
    time->day = bcdToDec(buffer[3]);
    time->date = bcdToDec(buffer[4]);
    time->month = bcdToDec(buffer[5]);
    time->year = bcdToDec(buffer[6]);

    return HAL_OK;
}



