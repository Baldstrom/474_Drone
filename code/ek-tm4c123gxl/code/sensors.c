#include "sensors.h"
#include "data.h"
//#include  "exter_var.h"
#include "stdlib.h"
#include "utils/uartstdio.h"
#include "semphr.h"
//#include "bme.h"
#include "imu.h"
#include "FreeRTOS.h"
#include "task.h"

#define SENSORTASKSTACKSIZE 2048

//static float aX, aY, aZ;
//static float mX, mY, mZ;
//static float pressure;

//static int sensors_init = 0;



void init_sensors()
{
  i2c3_init();
  bme_init();
  imu_init();
    
}

void sensors_task()
{
  //sensor_data s_data = (sensor_data) malloc(sizeof(struct sensor_data_struct));
  //sensor_data s_data;
  //if (!sensors_init) { init_sensors(); }
  //sensors_init = 1;
  //xSemaphoreHandle sensor_sem;
  //xSemaphoreHandle control_sem;
  //xSemaphoreHandle uart_sem;
  
  //sensor_data s_data;
  //control c_data;
  for(;;)
  {
    bme_update_readings();
    imu_update_readings();

      //bme_update_readings();
      //imu_update_readings();
    s_data->accelx = imu_accelX();
    s_data->accely = imu_accelY();
    s_data->accelz = imu_accelZ();
    s_data->magx = imu_magX();
    s_data->magy = imu_magY();
    s_data->magz = imu_magZ();
    s_data->alt = bme_pressure();
    s_data->gps_long = 1;
  }
}

uint32_t sensors_taskinit()
{
  // initialize sensors
  init_sensors();
  
  // make task for rtos
    if (xTaskCreate((TaskFunction_t)sensors_task,
                  (const portCHAR *)"SENSORSTASK",
                  SENSORTASKSTACKSIZE,
                  NULL,
                  tskIDLE_PRIORITY + 2,
                  NULL) != pdTRUE) return 1;
  return 0;
}