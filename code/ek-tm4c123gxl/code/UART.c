#include "data.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include <cse474.h>
#include <UART.h>
#include "queue.h"


#ifndef UART_BUFFERED
  #define UART_BUFFERED
#endif


#define UARTTASKSTACKSIZE  2048

const char * run_s =  "RUN";
const char * stop_s = "STOP";
const char * arm_s = "ARM";

//extern volatile xSemaphoreHandle uart_sem;


// setup:
//        RxD = PC6
//        TxD = PC7

void uart_configure()
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    //
    // Enable UART3
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PC6_U3RX);
    ROM_GPIOPinConfigure(GPIO_PC7_U3TX);
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART3_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(3, 115200, 16000000);
}

int float_int (float num)
{
  return (int) (num * 1000);
}

void uart_task()
{
  
  uart_configure();
  //xSemaphoreHandle sensor_sem;
  //xSemaphoreHandle control_sem;
  //xSemaphoreHandle uart_sem;  
  //sensor_data s_data;
  //control c_data;
  
  // commands START, STOP, ARM
   //g_pUARTSemaphore = xSemaphoreCreateMutex();

  char s[9];
  
  //bool action[3];
  for(;;) 
  {
    int accel[] = {float_int(s_data->accelx ), 
                 float_int(s_data->accely), 
                 float_int(s_data->accelz)};
    UARTprintf("AX:%d\nAY:%d\nAZ:%d\n", accel[0], accel[1], accel[2]);
    vTaskDelay(1000);
    if (UARTRxBytesAvail() > 0) {
     int chars_written;
      //UARTprintf("Action:");
      chars_written = UARTgets(s, 8);
    }
    int action[] = {strcmp(s, stop_s), strcmp(s, run_s), strcmp(s, arm_s)};
    
    if (action[0] == 0) 
    {
      //UARTprintf("saw STOP \n");
      // do run stop 
      if (run)
      {
        UARTprintf("stopping ... \n");
        run = false;
      }
      else
      {
        UARTprintf("you are already stopped \n");
        //stop = false;
      }
    }
    else if (action[1] == 0) 
    {
      //UARTprintf("saw RUN \n");
      // do run action 
      if (!run)
      {
        UARTprintf("running ... \n");
        run = true;
      }
      else 
      {
        UARTprintf("you are already running \n");
        //run = false;
      }
    }
    else if (action[2] == 0) 
    {
      //UARTprintf("saw ARM \n");
      
      if (!armed)
      {
        UARTprintf("arming ... \n");
        //arm = true;
        //arm_mcs();
      }
      else 
      {
        UARTprintf("you are already armed \n");
        //arm = false;
      }
    }
    else 
    {
      UARTprintf("No commands given \n");
    }
  
    vTaskDelay(1000);
        //for (int i=0; i< 100000; i++) {}
    //UARTprintf("next string \n");
    //free(s);
    UARTFlushTx(false);
  }
}

//void uart_task() {}

uint32_t uart_task_init()
{
  // uart configuration
  uart_configure();
  
  // create the task for rtos
  if (xTaskCreate((TaskFunction_t) uart_task,
                  (const portCHAR *)"UARTTASK",
                  UARTTASKSTACKSIZE,
                  NULL,
                  tskIDLE_PRIORITY + 2,
                  NULL) != pdTRUE) return 1;
  return 0;
}
