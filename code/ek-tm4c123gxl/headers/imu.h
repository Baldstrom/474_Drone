#ifndef __IMU_CUSTOM_H__
#define __IMU_CUSTOM_H__

#include <stdlib.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "data.h"
#include "i2c.h"

#define IMU_ADDR 0x1D // 0x1E if SA0 pulled low

// REGISTERS
#define IMU_TEMP_OUT_L_ADDR                 0x05
#define IMU_TEMP_OUT_H_ADDR                 0x06
#define IMU_STATUS_M_ADDR                   0x07
#define IMU_OUT_X_L_M_ADDR                  0x08
#define IMU_OUT_X_H_M_ADDR                  0x09
#define IMU_OUT_Y_L_M_ADDR                  0x0A
#define IMU_OUT_Y_H_M_ADDR                  0x0B
#define IMU_OUT_Z_L_M_ADDR                  0x0C
#define IMU_OUT_Z_H_M_ADDR                  0x0D
#define IMU_WHO_AM_I_ADDR                   0x0E
#define IMU_INT_CTRL_M_ADDR                 0x0F
#define IMU_INT_SRC_M_ADDR                  0x12
#define IMU_THS_L_M_ADDR                    0x14
#define IMU_THS_H_M_ADDR                    0x15
#define IMU_OFFSET_X_L_M_ADDR               0x16
#define IMU_OFFSET_X_H_M_ADDR               0x17
#define IMU_OFFSET_Y_L_M_ADDR               0x18
#define IMU_OFFSET_Y_H_M_ADDR               0x19
#define IMU_OFFSET_Z_L_M_ADDR               0x1A
#define IMU_OFFSET_Z_H_M_ADDR               0x1B
#define IMU_REFERENCE_X_ADDR                0x1C
#define IMU_REFERENCE_Y_ADDR                0x1D
#define IMU_REFERENCE_Z_ADDR                0x1E
#define IMU_CTRL0_ADDR                      0x1F
#define IMU_CTRL1_ADDR                      0x20
#define IMU_CTRL2_ADDR                      0x21
#define IMU_CTRL3_ADDR                      0x22
#define IMU_CTRL4_ADDR                      0x23
#define IMU_CTRL5_ADDR                      0x24
#define IMU_CTRL6_ADDR                      0x25
#define IMU_CTRL7_ADDR                      0x26
#define IMU_STATUS_A_ADDR                   0x27
#define IMU_OUT_X_L_A_ADDR                  0x28
#define IMU_OUT_X_H_A_ADDR                  0x29
#define IMU_OUT_Y_L_A_ADDR                  0x2A
#define IMU_OUT_Y_H_A_ADDR                  0x2B
#define IMU_OUT_Z_L_A_ADDR                  0x2C
#define IMU_OUT_Z_H_A_ADDR                  0x2D
#define IMU_FIFO_CTRL_ADDR                  0x2E
#define IMU_FIFO_SRC_ADDR                   0x2F
#define IMU_IG_CFG1_ADDR                    0x30
#define IMU_IG_SRC1_ADDR                    0x31
#define IMU_IG_THS1_ADDR                    0x32
#define IMU_IG_DUR1_ADDR                    0x33
#define IMU_IG_CFG2_ADDR                    0x34
#define IMU_IG_SRC2_ADDR                    0x35
#define IMU_IG_THS2_ADDR                    0x36
#define IMU_IG_DUR2_ADDR                    0x37
#define IMU_CLICK_CFG_ADDR                  0x38
#define IMU_CLICK_SRC_ADDR                  0x39
#define IMU_CLICK_THS_ADDR                  0x3A
#define IMU_TIME_LIMIT_ADDR                 0x3B
#define IMU_TIME_LATENCY_ADDR               0x3C
#define IMU_TIME_WINDOW_ADDR                0x3D
#define IMU_ACT_THS_ADDR                    0x3E
#define IMU_ACT_DUR_ADDR                    0x3F

// Functions
extern void imu_init();
extern void imu_update_readings();

extern float imu_accelX();
extern float imu_accelY();
extern float imu_accelZ();

extern float imu_magX();
extern float imu_magY();
extern float imu_magZ();

#endif
