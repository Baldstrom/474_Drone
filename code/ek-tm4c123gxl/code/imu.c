#include "imu.h"

static float aX, aY, aZ, mX, mY, mZ;

const int ACCEL_FS = 2; // +/- g's
const int MAG_FS = 4; // +/- guass
const int RESOLUTION = 32768;

void imu_init()
{
    // Initialize readings
    aX = 0.0f;
    aY = 0.0f;
    aZ = 0.0f;
    mX = 0.0f;
    mY = 0.0f;
    mZ = 0.0f;
    // Configure

    // Write to CTRL1
    i2c3_write_register(IMU_ADDR, IMU_CTRL1_ADDR, 0xA7);
    i2c3_write_register(IMU_ADDR, IMU_CTRL2_ADDR, 0x08);
    i2c3_write_register(IMU_ADDR, IMU_CTRL5_ADDR, 0xF8);
    i2c3_write_register(IMU_ADDR, IMU_CTRL7_ADDR, 0x82);

    // Update readings
    imu_update_readings();
}

void imu_update_readings()
{
    char accelx_data[2];
    char accely_data[2];
    char accelz_data[2];
    char magx_data[2];
    char magy_data[2];
    char magz_data[2];
    
    i2c3_read_registers(IMU_ADDR, IMU_OUT_X_L_A_ADDR, 1, (char *)(accelx_data + 0));
    i2c3_read_registers(IMU_ADDR, IMU_OUT_X_H_A_ADDR, 1, (char *)(accelx_data + 1));

    i2c3_read_registers(IMU_ADDR, IMU_OUT_Y_L_A_ADDR, 1, (char *)(accely_data + 0));
    i2c3_read_registers(IMU_ADDR, IMU_OUT_Y_H_A_ADDR, 1, (char *)(accely_data + 1));

    i2c3_read_registers(IMU_ADDR, IMU_OUT_Z_L_A_ADDR, 1, (char *)(accelz_data + 0));
    i2c3_read_registers(IMU_ADDR, IMU_OUT_Z_H_A_ADDR, 1, (char *)(accelz_data + 1));

    i2c3_read_registers(IMU_ADDR, IMU_OUT_X_L_M_ADDR, 1, (char *)(magx_data + 0));
    i2c3_read_registers(IMU_ADDR, IMU_OUT_X_H_M_ADDR, 1, (char *)(magx_data + 1));

    i2c3_read_registers(IMU_ADDR, IMU_OUT_Y_L_M_ADDR, 1, (char *)(magy_data + 0));
    i2c3_read_registers(IMU_ADDR, IMU_OUT_Y_H_M_ADDR, 1, (char *)(magy_data + 1));

    i2c3_read_registers(IMU_ADDR, IMU_OUT_Z_L_M_ADDR, 1, (char *)(magz_data + 0));
    i2c3_read_registers(IMU_ADDR, IMU_OUT_Z_H_M_ADDR, 1, (char *)(magz_data + 1));


    int16_t accelX_full = (accelx_data[1] << 8) |  accelx_data[0];
    int16_t accelY_full = (accely_data[1] << 8) |  accely_data[0];
    int16_t accelZ_full = (accely_data[1] << 8) |  accelz_data[0];
    int16_t magX_full = (magx_data[1] << 8) |  magx_data[0];
    int16_t magY_full = (magy_data[1] << 8) |  magy_data[0];
    int16_t magZ_full = (magz_data[1] << 8) |  magz_data[0];

    aX = accelX_full * ((float) ACCEL_FS / RESOLUTION);
    aY = accelY_full * ((float) ACCEL_FS / RESOLUTION); 
    aZ = accelZ_full * ((float) ACCEL_FS / RESOLUTION); 
    mX = magX_full * ((float) MAG_FS / RESOLUTION); 
    mY = magY_full * ((float) MAG_FS / RESOLUTION); 
    mZ = magZ_full * ((float) MAG_FS / RESOLUTION); 
}

float imu_accelX() { return aX; }
float imu_accelY() { return aY; }
float imu_accelZ() { return aZ; }
float imu_magX() { return mX; }
float imu_magY() { return mY; }
float imu_magZ() { return mZ; }