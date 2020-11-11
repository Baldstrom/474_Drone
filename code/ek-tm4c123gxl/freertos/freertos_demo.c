//*****************************************************************************
//
// freertos_demo.c - Simple FreeRTOS example.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "led_task.h"
#include "switch_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "pwm.h"
#include "sensors.h"
#include "lcd_task.h"
#include "UART.h"
#include "control.h"
#include "data.h"
//#include "data.c"
//#include "UART.c"



#define UARTTASKSTACKSIZE  2048 * 2

sensor_data s_data;
control c_data;
motor_v m_data;

xSemaphoreHandle uart_sem;
xSemaphoreHandle sensor_sem;
xSemaphoreHandle control_sem;

bool armed = false;
bool run = false;
//bool stop = false;

/////////////////////////////////////////////data.c /////////////////////////////////////
uint32_t data_init()
{
  // make struct for sensor data
  s_data = (sensor_data) pvPortMalloc(sizeof(struct sensor_data_struct));
  if (s_data == NULL) return 1;
  
  // make struct for control data
  c_data = (control) pvPortMalloc(sizeof(struct control_struct));
  if (c_data == NULL) return 1;
  
  //  make struct for lcd display 
  m_data = (motor_v) pvPortMalloc(sizeof(struct motor_v_struct));
  if (m_data == NULL) return 1;
  
  // create semaphore for sensor data
  sensor_sem = xSemaphoreCreateMutex();
  if (sensor_sem == NULL) return 1;
  
  // create semaphore for control data
  control_sem = xSemaphoreCreateMutex();
  if (control_sem == NULL) return 1;
  
  // create semaphore for uart
  uart_sem = xSemaphoreCreateMutex();
  if (uart_sem == NULL) return 1;
  
  // give each semaphore a count
  xSemaphoreGive(uart_sem);
  xSemaphoreGive(control_sem);
  xSemaphoreGive(sensor_sem);
  
  
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////


#include "pwm.c"
#include "lcd_task.c"
#include "sensors.c"
#include "UART.c"


//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>FreeRTOS Example (freertos_demo)</h1>
//!
//! This application demonstrates the use of FreeRTOS on Launchpad.
//!
//! The application blinks the user-selected LED at a user-selected frequency.
//! To select the LED press the left button and to select the frequency press
//! the right button.  The UART outputs the application status at 115,200 baud,
//! 8-n-1 mode.
//!
//! This application utilizes FreeRTOS to perform the tasks in a concurrent
//! fashion.  The following tasks are created:
//!
//! - An LED task, which blinks the user-selected on-board LED at a
//!   user-selected rate (changed via the buttons).
//!
//! - A Switch task, which monitors the buttons pressed and passes the
//!   information to LED task.
//!
//! In addition to the tasks, this application also uses the following FreeRTOS
//! resources:
//!
//! - A Queue to enable information transfer between tasks.
//!
//! - A Semaphore to guard the resource, UART, from access by multiple tasks at
//!   the same time.
//!
//! - A non-blocking FreeRTOS Delay to put the tasks in blocked state when they
//!   have nothing to do.
//!
//! For additional details on FreeRTOS, refer to the FreeRTOS web page at:
//! http://www.freertos.org/
//
//*****************************************************************************


//*****************************************************************************
//
// The mutex that protects concurrent access of UART from multiple tasks.
//
//*****************************************************************************
//xSemaphoreHandle g_pUARTSemaphore;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
/*void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}*/

//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************
int
main(void)
{
    //
    // Set the clocking to run at 50 MHz from the PLL.
    //
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);

    // 
    // Initialize structs for control and data and semphores for them
    //
    if(data_init() != 0) for(;;) {}
    
    //
    // Initialize the UART and configure it for 115,200, 8-N-1 operation.
    //
    //ConfigureUART();

    //
    // Print demo introduction.
    //
    //UARTprintf("\n\nWelcome to the EK-TM4C123GXL FreeRTOS Demo!\n");
    
     //
    // Create the uart task
    //
    if(uart_task_init() != 0) for(;;) {}

    //
    // Create a mutex to guard the UART.
    //
    //g_pUARTSemaphore = xSemaphoreCreateMutex();
    
    //
    // Create the pwm task.
    //
    if(PWM_task_init() != 0) for(;;) {} 
    
    //
    // Create the sensors task
    //
    if(sensors_taskinit() != 0) for(;;) {}
    
    //
    // Create the LCD task
    //
    if(lcdTaskInit() != 0) for(;;) {}
    
    //
    // Create the LED task.
    //
    /*if(LEDTaskInit() != 0)
    {

        while(1)
        {
        }
    }

    //
    // Create the switch task.
    //
    if(SwitchTaskInit() != 0)
    {

        while(1)
        {
        }
    }*/

    //
    // Start the scheduler.  This should not return.
    //
    vTaskStartScheduler();

    //
    // In case the scheduler returns for some reason, print an error and loop
    // forever.
    //

    while(1)
    {
    }
}
