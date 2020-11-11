#include "control.h"
#include <SSD2119.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <cse474.h>
#include <stdbool.h>
#include <stdint.h>
#include <lcd_task.h>
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
//#include "data.h"


uint32_t control_task_init()
{
  return 0;
}


