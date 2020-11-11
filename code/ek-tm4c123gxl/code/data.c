#include "data.h"
#include <SSD2119.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "drivers/buttons.h"
#include "utils/uartstdio.h"
#include "switch_task.h"
#include "led_task.h"
#include "priorities.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "data.h"

uint32_t data_init()
{
  // make struct for sensor data
  sensor_data s_data = (sensor_data) pvPortMalloc(sizeof(struct sensor_data_struct));
  if (s_data == NULL) return 1;
  
  // make struct for control data
  control c_data = (control) pvPortMalloc(sizeof(struct control_struct));
  if (c_data == NULL) return 1;
  
  //  make struct for lcd display 
  motor_v m_data = (motor_v) pvPortMalloc(sizeof(struct motor_v_struct));
  if (m_data == NULL) return 1;
  
  
  // create semaphore for sensor data
  xSemaphoreHandle sensor_sem = xSemaphoreCreateMutex();
  if (sensor_sem == NULL) return 1;
  
  // create semaphore for control data
  xSemaphoreHandle control_sem = xSemaphoreCreateMutex();
  if (control_sem == NULL) return 1;
  
  // create semaphore for uart
  xSemaphoreHandle uart_sem = xSemaphoreCreateMutex();
  if (uart_sem == NULL) return 1;
  
  // give each semaphore a count
  xSemaphoreGive(uart_sem);
  xSemaphoreGive(control_sem);
  xSemaphoreGive(sensor_sem);
  
  
  return 0;
}