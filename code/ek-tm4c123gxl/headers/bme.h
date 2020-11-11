#ifndef __BME_CUSTOM_H__
#define __BME_CUSTOM_H__

#include <stdlib.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "stdint.h"
//#include "data.h"

#define BME_ADDR 0x76

#define BME_DEV_ID_REG              0xD0
#define BME_RESET_REG               0xE0
#define BME_CALIBRATION_LOW_REG     0x88
#define BME_CALIBRATION_HIGH_REG    0xE1
#define BME_CTRL_HUM_REG            0xF2 // Sets humidity acquisition options: Must write to CTRL_MEAS before changes are applied.
#define BME_STATUS_REG              0xF3
#define BME_CTRL_MEAS_REG           0xF4 // Sets pressure and temperature acquisition options
#define BME_CONFIG_REG              0xF5 // Must be in sleep mode
#define BME_PRESSURE_MSB_REG        0xF7
#define BME_PRESSURE_LSB_REG        0xF8
#define BME_PRESSURE_XLSB_REG       0xF9
#define BME_TEMPERATURE_MSB_REG     0xFA
#define BME_TEMPERATURE_LSB_REG     0xFB
#define BME_TEMPERATURE_XLSB_REG    0xFC
#define BME_HUMIDITY_MSB_REG        0xFD
#define BME_HUMIDITY_LSB_REG        0xFE

typedef struct
{
    uint16_t T1;
    short    T2;
    short    T3;
    uint16_t P1;
    short    P2;
    short    P3;
    short    P4;
    short    P5;
    short    P6;
    short    P7;
    short    P8;
    short    P9;
    char     H1;
    short    H2;
    char     H3;
    short    H4;
    short    H5;
    int8_t   H6;
} compensation_params;

typedef enum
{
    SLEEP,
    FORCE,
    NORMAL
} mode;

typedef enum os_enum
{
    OS_1X,
    OS_2X,
    OS_4X,
    OS_8X,
    OS_16X,
} oversampling;

extern void bme_init();
extern void bme_set_mode(mode newmode);
extern void bme_update_readings();
extern float bme_temperature();
extern float bme_pressure();
extern float bme_humidity();

#endif
