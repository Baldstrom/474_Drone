#include "data.h"
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

/*xSemaphoreHandle sensor_sem;
xSemaphoreHandle control_sem;
xSemaphoreHandle uart_sem;*/

#define red    0xE0A2
#define green  0x1742
#define blue   0x11FC
#define pink   0xF01A
#define yellow 0xF780

#define LCDTASKSTACKSIZE        128
#define FSMTASKSTACKSIZE        128  


/*
  Setup:
         R = PE1
         G = PE2
         Y = PE3
*/

const TickType_t xDelay = 1000;

short cir[] = {170, 90, 200, 120, 170, 150, 140, 120}; 
short r = 15;
long x, y;
int c_sep = 25;

short get_color(float dut) {
  int num = (int) (dut * 100);
  if (num <= 25) return blue;
  else if (num > 25 && num <= 50) return green;
  else if (num > 50  && num <= 75) return yellow;
  else return red;
}

// get raw touch readings from lcd
long get_touch()
{
    // get touch reading 
    Touch_ReadX();
    Touch_ReadY();
    Touch_ReadZ1();
    return Touch_GetCoords(); 
}

// get value from cords and sets them to x and y values
void get_xy(long cord)
{
    y = (cord & 0xFFFF);
    if (y > 240) y = 0;
    x = ((cord >> 16) & 0xFFFF);
    if (x > 320) x = 0;
}

double distance(long x1, long y1, long x2, long y2)
{
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool P_button_pressed()
{
  get_xy(get_touch());
  //LCD_Goto(0, 1);
  //LCD_PrintInteger(x);
  //LCD_PrintInteger(y);
  return (distance(350 - cir[0], 20 + cir[1], x, y) < r);
}

bool O_button_pressed()
{
  get_xy(get_touch());
  //LCD_Goto(0, 1);
  //LCD_PrintInteger(x);
  //LCD_PrintInteger(y);
  return (distance(350 - cir[2], 20 + cir[3], x, y) < r);
}

int readPed() { return P_button_pressed(); }
int readOnOff() { return O_button_pressed(); }

int getGPTMRIS() { return GPTMRIS_1 & 0x01; }
void clearGPTMICR() { GPTMICR_1 |= 0x01; }

// Draw skeleton of cube
void Draw_Cube(short arr1[], short arr2[])
{
    LCD_DrawRect(arr1[0], arr1[2], 50, 50, 0xFFFF);
    LCD_DrawRect(arr2[0], arr2[2], 50, 50, 0xFFFF);
    LCD_DrawLine(arr1[0], arr1[2], arr2[0], arr2[2], 0xFFFF); // top left
    LCD_DrawLine(arr1[1], arr1[2], arr2[1], arr2[2], 0xFFFF); // top right
    LCD_DrawLine(arr1[0], arr1[3], arr2[0], arr2[3], 0xFFFF);  // bottom left
    LCD_DrawLine(arr1[1], arr1[3], arr2[1], arr2[3], 0xFFFF);  // bottom right
}

// Draw filled shifted cube
void Draw_FilledCube(short arr1[], short arr2[], short color)
{
  // TODO: just use three dont have to go all the way 
  for (int i=0; i <= c_sep; i++)
  {
     LCD_DrawFilledRect(arr1[0] - i, arr1[2] + i, 50, 50, color);
  }
}

// Draw buttons for FSM pink = p yellow = O/F
void Draw_buttons()
{
  // br, fr, fl, bl
  // 2, 3, 0, 1
  LCD_DrawFilledCircle(cir[0], cir[1], r, get_color(m_data->br)); // fl
  LCD_DrawFilledCircle(cir[2], cir[3], r, get_color(m_data->fr)); // bl
  LCD_DrawFilledCircle(cir[4], cir[5], r, get_color(m_data->fl)); // br
  LCD_DrawFilledCircle(cir[6], cir[7], r, get_color(m_data->bl)); // fr
}

// set offboard leds according to LEDs
void setLEDs(char LEDs) 
{
    GPIODATA_PE = LEDs;
}


/**
 * 
 **/
int waitForInput()
{
  int startStopCnts = 0;
  int pedCnts = 0;
  int btnCounts = 0;

  while(1) 
  {   
    
    int btns = 0x03;
    
    // Clear the interrupt
    // clearGPTMICR();
    // Check ths raw interrupt status
    vTaskDelay(xDelay);
    int ped = readPed();
    int onOff = readOnOff();
    btns &= ((ped << 1) | onOff);
    
    // Check the status of the buttons after 1 second
    if (btns & 0x01) { startStopCnts++; } else { startStopCnts = 0; }
    if (btns & 0x02) { pedCnts++; } else { pedCnts = 0; }
    
    // print held seconds of O button
    //LCD_Goto(0, 22);
    //LCD_PrintString("O_button held for: ");
    //LCD_PrintInteger(startStopCnts);
    
    // print held seconds of P button
    //LCD_Goto(0, 23);
    //LCD_PrintString("P_button held for: ");
    //LCD_PrintInteger(pedCnts);

    // See if they have been held for 2 seconds
    if (startStopCnts == 2) { return 0x01; }
    if (pedCnts == 2) { return 0x02; }

    btnCounts++;
    if (btnCounts == 5) { return 0x00; }
  }
}

int GPIOE_init()
{
  // stuff for the outside led port E//////////////
  // enable GPIO clock
  SC_RCGCGPIO |= SC_GPIOE_CGC_ENABLE;
  
  // disable analog and set port control
  GPIOAMSEL_PE &= ~0x0E;
  GPIOPCTL_PE &= ~0x0000FFF0;
  
  // direction
  GPIODIR_PE |= 0x0E;
  
  // gpio control 
  GPIOAFSEL_PE &= ~0x0E;
 
  // digital output
  GPIODEN_PE |= 0x0E;
  
  return 0;
}

void lcd_task()
{
  bool touch, release;
  long cord;

  // box stuff  
  //short arr1[] = {135, 185, 95, 145}; // x1, x2, y1, y2
  //short arr2[] = {arr1[0] - c_sep, arr1[1] - c_sep, arr1[2] + c_sep, arr1[3] + c_sep};
  
  // colors of box
  //short color[] = {red, blue, green};
  
  // used to print strings
  char str[70];
  char motor[70];
  
  while (1) 
  {
    // display the state of the motors
    Draw_buttons();
    
    // get touch reading 
    cord = get_touch();
    
    // convert data for touch 
    get_xy(cord);
    
    unsigned long z = Touch_ReadZ2();
    
    // determine touch state of screen
    if (z < 3300) touch = true;
    
    if (touch && !(z < 3300))
    {
      release = true;
      touch = false;
    }
      
    // print position of touch  
    sprintf(str, "Cords: x=%d, y=%d, z=%d   \r", x, y, z);
    LCD_Goto(0, 5);
    LCD_PrintString(str);
      
    /*// print temperature
    sprintf(str, "Temperature: %f\r", get_temp());
    LCD_Goto(0, 0);
    LCD_PrintString(str);*/
    
    // printf if armed
    LCD_Goto(0, 6);
    if (armed) LCD_PrintString("copter is armed       \r");
    else LCD_PrintString("copter is not armed         \r");
    
    // br, fr, fl, bl
    // 2, 3, 0, 1
    
    // print motor value 
    
    sprintf(motor, "motor0 value: %d    \r", (int)(m_data->fl * 100));
    LCD_Goto(0, 10);
    LCD_PrintString(motor);
    
    sprintf(motor, "motor1 value: %d    \r", (int)(m_data->bl * 100));
    LCD_Goto(0, 11);
    LCD_PrintString(motor);
    
    sprintf(motor, "motor2 value: %d    \r", (int)(m_data->br * 100));
    LCD_Goto(0, 12);
    LCD_PrintString(motor);
    
    sprintf(motor, "motor3 value: %d    \r", (int)(m_data->fr * 100));
    LCD_Goto(0, 13);
    LCD_PrintString(motor);
      
    
    
    // print that the P button was pressed
    /*LCD_Goto(0, 10);
    if (P_button_pressed()) LCD_PrintString("p_button pressed");
    else LCD_PrintString("                  ");
    
    // print that the O button was pressed
    LCD_Goto(0, 11);
    if (O_button_pressed()) LCD_PrintString("O_button pressed");
    else LCD_PrintString("                  ");*/
    
  }
}

/*void fsm_task()
{
  // draw buttons once
  Draw_buttons();
  
  // states of fsm
  typedef enum { off, go, stop, warn } state;
  state curState = off;  
  
  // data for leds 
  char OFF = 0x00;
  char R =   0x02;
  char G =   0x04;
  char Y =   0x08;
  
  // FSM uncomment to use FSM
  setLEDs(OFF);
  
  int warnStop = 0;
  
  for ( ;; )
  {
    switch (curState) {
      case off: 
        setLEDs(OFF);
        while(1) { 
          int period = waitForInput();
          if (period == 0x01) { break; }
        }
        curState = stop;
        break;
      case stop:
        setLEDs(R);
        warnStop = waitForInput();
        if (warnStop == 0x01) { curState = off; }
        else { curState = go; }
        break;
      case go:
        setLEDs(G);
        warnStop = waitForInput();
        if (warnStop == 0x01) { curState = off; }
        else if (warnStop == 0x02) { curState = warn; }
        else { curState = stop; }
        break;
      case warn:
        setLEDs(Y);
        warnStop = waitForInput();
        if (warnStop == 0x01) { curState = off; }
        else { curState = stop; }
        break;
    }
  }
}*/

uint32_t lcdTaskInit()
{
    // Initialize the LED
  LCD_Init();
  
  // Initialize the Touchpad
  Touch_Init();
    
  // Initialize the Temperature Sensor
  //TS_Init();
  
  // Initialize timer
  //clock1_init();
  
  // Initialize GPIOE
  // GPIOE_init();
  
  
  // def of xTaskCreate in task.h line
  if (xTaskCreate((TaskFunction_t)lcd_task,
                  (const portCHAR *)"LCDDISP",
                  LCDTASKSTACKSIZE,
                  NULL,
                  tskIDLE_PRIORITY + 2, // priority of task
                  NULL) != pdTRUE) return 1; // error
  
  return 0; // success
    
  
}

/*uint32_t FSMTaskInit()
{
  // Initialize the LED
  LCD_Init();
  
  // Initialize the Touchpad
  Touch_Init();
    
  // Initialize the Temperature Sensor
  //TS_Init();
  
  // Initialize timer
  //clock1_init();
  
  // Initialize GPIOE
  GPIOE_init();
  
  if (xTaskCreate((TaskFunction_t)fsm_task,
                  (const portCHAR *)"FSMDISP",
                  FSMTASKSTACKSIZE,
                  NULL,
                  tskIDLE_PRIORITY + 2,
                  NULL) != pdTRUE) return 1;
  return 0;
}*/

