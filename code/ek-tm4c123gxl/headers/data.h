#ifndef __DATA__
#define __DATA__

#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

// struct for sensor data
typedef struct sensor_data_struct {
  // accelerometer
  float accelx;
  float accely;
  float accelz;

  // gyrometer
  float gyrox;
  float gyroy;
  float gyroz;
  
  // magnometer
  float magx;
  float magy;
  float magz;
 
  // gps
  uint32_t gps_long;
  uint32_t gps_lat;

  // other
  uint32_t baro_pressure;
  float alt;
} * sensor_data ;

// struct for control data
typedef struct control_struct {
  float alt_desired;
  float fx;
  float fy;
  float fz;
} * control;

typedef struct motor_v_struct {
  float fr;
  float br;
  float fl;
  float bl;
} * motor_v;

// semaphores for controling copter
//xSemaphoreHandle sensor_sem;
//xSemaphoreHandle control_sem;
//xSemaphoreHandle uart_sem;

// struct defs for controling copter
//sensor_data s_data;
//control c_data;

//uint32_t data_init(void);


#endif
