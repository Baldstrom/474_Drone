#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "pwm.h"
#include "tm4c123gh6pm.h"
#include "data.h"
#include "FreeRTOS.h"
#include "task.h"

/*
  motor2 PF1
  motor1 PF3
  motor2 PC5
  motor3 PC4

*/

#define PWMTASKSTACKSIZE 128
#define PWM_FREQ         0x128B + (0x128B / 2 )
#define PWM_INIT_FREQ    PWM_FREQ * 2

static float PID_X_VAL = 0.0f;
static float PID_Y_VAL = 0.0f;
static float PID_Z_VAL = 0.0f;

static void run_pid(void);

//sensor_data s_data;
//control c_data;

void run_pid(void)
{ 
  static float XE = 0.0f;
  static float lastXE = 0.0f;
  static float sumXE = 0.0f;
  
  static float YE = 0.0f;
  static float lastYE = 0.0f;
  static float sumYE = 0.0f;
  
  static float ZE = 0.0f;
  static float lastZE = 0.0f;
  static float sumZE = 0.0f;
  
  // Error
  XE = c_data->fx - (s_data->accelx / 100.0f);
  YE = c_data->fy - (s_data->accely / 100.0f);
  ZE = c_data->fz - (s_data->accelz / 100.0f);
  
  // Calculate P, I, D
  PID_X_VAL = (PID_X_P * XE) + (PID_X_I * sumXE) + (PID_X_D * (XE - lastXE));
  PID_Y_VAL = (PID_Y_P * YE) + (PID_Y_I * sumYE) + (PID_Y_D * (YE - lastYE));
  PID_Z_VAL = (PID_Z_P * ZE) + (PID_Z_I * sumZE) + (PID_Z_D * (ZE - lastZE));
  
  // Limit outputs
  if (PID_X_VAL >= 1.0f) PID_X_VAL = 0.99f;
  if (PID_Y_VAL >= 1.0f) PID_Y_VAL = 0.99f;
  if (PID_Z_VAL >= 1.0f) PID_Z_VAL = 0.99f;
 
  // Set vars
  lastXE = XE;
  sumXE += XE;
  
  lastYE = YE;
  sumYE += YE;
  
  lastZE = ZE;
  sumZE += ZE;
}

void pwm_init()
{
  // enable pwm clock
  //SYSCTL_RCGC0_R |= 0x100000;
  SYSCTL_RCGCPWM_R |= 0x3;
  
  // enable gpio module PC
  //SYSCTL_RCGC2_R |= 0x6; // port f and port c
  SYSCTL_RCGCGPIO_R |= 0x3F; //change to only use port f and c 
  GPIO_PORTF_LOCK_R=0x4C4F434B;
  
  // enable alternate function
  GPIO_PORTC_AFSEL_R |= 0x30;
  GPIO_PORTC_DEN_R |= 0x30;
  //GPIO_PORTB_AFSEL_R |= 0xC0;
  //GPIO_PORTB_DEN_R |= 0xC0;
  GPIO_PORTF_AFSEL_R = 0xA;
  GPIO_PORTF_DEN_R = 0xA;
  //GPIO_PORTF_DIR_R = 0xA;
 
  //GPIO_PORTE_AFSEL_R |= 0x30;
  //GPIO_PORTE_DIR_R = 0x30;
  

  
  // configure function of gpio with value 4
  GPIO_PORTC_PCTL_R |= 0x440000;
  GPIO_PORTF_PCTL_R |= 0x5050;
  //GPIO_PORTE_PCTL_R |= 0x550000;
  //GPIO_PORTB_PCTL_R |= 0x44000000;
  
  // configure rcc to USEPWMDIV and set PWMDIV to 2 divide 
  SYSCTL_RCC_R |= 0x100000;
  SYSCTL_RCC_R &= ~0xE0000; 
  
  //  setting for pwm gnerator 3 
  // configure pwm 0 gen 3 A and B;
  PWM0_3_CTL_R = 0x0;
  PWM0_3_GENA_R = 0x8C;
  PWM0_3_GENB_R = 0x80C;
  
  // configure pwm 1 gen 2 B
  PWM1_2_CTL_R = 0x0;
  PWM1_2_GENA_R = 0x8C;
  PWM1_2_GENB_R = 0x80C;
  
  // configure pwm 1 gen 3 B
  PWM1_3_CTL_R = 0x0;
  PWM1_3_GENA_R = 0x8C;
  PWM1_3_GENB_R = 0x80C;
  
  // start timer for gen3 with pwmctl
  PWM0_3_CTL_R = 0x1;
  PWM1_2_CTL_R = 0x1;
  PWM1_3_CTL_R = 0x1;

  
  // enable pwm outputs
  PWM0_ENABLE_R = 0xC3;
  PWM1_ENABLE_R = 0xFF;
  
}

// set duty cycle of pwms
void PWM_setduty(uint32_t pwm_freq, 
                    float motor2, 
                    float motor3, 
                    float motor0,
                    float motor1)
{
  // Handle inputs
  if (motor2 >= 1.0f) motor2 = 0.99f;
  if (motor2 <= 0.0f) motor2 = 0.01f;
  if (motor3 >= 1.0f) motor3 = 0.99f;
  if (motor3 <= 0.0f) motor3 = 0.01f;
  if (motor0 >= 1.0f) motor0 = 0.99f;
  if (motor0 <= 0.0f) motor0 = 0.01f;
  if (motor1 >= 1.0f) motor1 = 0.99f;
  if (motor1 <= 0.0f) motor1 = 0.01f;
  

  // set period for PWM LOADs
  PWM0_3_LOAD_R = pwm_freq;
  PWM1_2_LOAD_R = pwm_freq;
  PWM1_3_LOAD_R = pwm_freq;
  
  // put values into struct for lcd display
  m_data->fr = motor1;
  m_data->br = motor3;
  m_data->fl = motor0;
  m_data->bl = motor2;
  
  // convert dut to apporiate value for pwm
  float value_0_3a = pwm_freq - (pwm_freq * motor2);
  float value_0_3b = pwm_freq - (pwm_freq * motor3);
  float value_1_2b = pwm_freq - (pwm_freq * motor0);
  float value_1_3b = pwm_freq - (pwm_freq * motor1);
  
  
  // set pulse of gen3A
  PWM0_3_CMPA_R = (uint32_t) value_0_3a;
  
  // set pulse of gen3B
  PWM0_3_CMPB_R = (uint32_t) value_0_3b;
  
  // set pulse of gen3B
  PWM1_2_CMPB_R = (uint32_t) value_1_2b;
  
  // set pulse of gen3B
  PWM1_3_CMPB_R = (uint32_t) value_1_3b;
  
}

/*void init()
{
  static int init = 0;
  if (init) { return; }
  s_data = (sensor_data) pvPortMalloc(sizeof(struct sensor_data_struct));
  c_data = (control) pvPortMalloc(sizeof(struct control_struct));
  init = 1;
}*/

void accel_pwm (float motor2, 
               float motor3, 
               float motor0,
               float motor1)
{
  
  // might be some problems from flipping between sub and add 
  float bl_accel_const = ((motor2 >= m_data->bl) ?  0.000001f : -0.000001f);
  float br_accel_const = ((motor3 >= m_data->br) ?  0.000001f : -0.000001f);
  float fl_accel_const = ((motor0 >= m_data->fl) ?  0.000001f : -0.000001f);
  float fr_accel_const = ((motor1 >= m_data->fr) ?  0.000001f : -0.000001f);
  
  PWM_setduty(PWM_FREQ, 
              m_data->bl + bl_accel_const,
              m_data->br + br_accel_const,
              m_data->fl + fl_accel_const,
              m_data->fr + fr_accel_const);
  
}

void stop_pwm ()
{
  float bl, br, fl, fr;
  bl = m_data->bl - 0.000001f;
  br = m_data->br - 0.000001f;
  fl = m_data->fl - 0.000001f;
  fr = m_data->fr - 0.000001f;
  
  
  PWM_setduty(PWM_FREQ, bl, br, fl, fr);
}

void pwm_task()
{
  //init();
  float i = 0.0f;
  while (1) 
  {
    if (!run) 
    {
      stop_pwm();
      continue;
    }
    run_pid();
    i += 0.000001f;
    
    /*float motor2, 
    float motor3, 
    float motor0,
    float motor1*/
    accel_pwm
    (
            //i, i, i, i
            PID_Z_VAL - PID_X_VAL,
            PID_Z_VAL + PID_X_VAL,
            PID_Z_VAL - PID_Y_VAL,
            PID_Z_VAL + PID_Y_VAL
    );
    // TEST CODE
    //s_data->accelz += 0.001f / 10.0;
    #ifdef DEBUG
        printf("PID VAL X: %i, ", (int)(PID_X_VAL*1000));
        printf("PID VAL Y: %i, ", (int)(PID_Y_VAL*1000));
        printf("PID VAL Z: %i, ", (int)(PID_Z_VAL*1000));
        printf("PID IN: %i\n", (int)(s_data->accelz*1000));
    #endif
    // TEST CODE
    //if (s_data->accelz > 5.0f) s_data->accelz = 0.0f;
  }
  /*
  float i = 0.0f;
  while(1)
  {
    if (SYSCTL_PPPWM_R |= 0x2) {
      
      PWM_setduty(PWM_FREQ, i, i, i, i);
      for (int n=0; n<300000;n++){}
      if (i >= 0.999f) i = 0.0f;
      else i += 0.01f;
    }
    //PMW0_3_setduty(0x140, 0.50, 0.50);
    //for (int i=0; i<100000;i++){}
    //PMW0_3_setduty(0x140, 0.75, 0.50);
    //for (int i=0; i<100000;i++){}
  
  }  
*/
}

void arm_mcs()
{
  PWM_setduty(PWM_FREQ, 0.01, 0.01, 0.01, 0.01);
  // DELAY A BUNCH
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  for (int i=0; i<3000000;i++);
  armed = true;

  // RUN MCs at low DUTY to prevent inrush current?
}


uint32_t PWM_task_init()
{
  // TEST CODE
  c_data->fz = 1.0f;
  c_data->fx = 0.0f;
  c_data->fy = 0.0f;
  
  // initialize the pwm
  pwm_init();
 // vTaskDelay(3000);
  // Arm Motor Controllers
  arm_mcs();
  // TODO: Use actual task delay instead of for loop delay
  
  // create the task for rtos
  int taskCreateFailed = xTaskCreate((TaskFunction_t) pwm_task,
                  (const portCHAR *)"PWMTASK",
                  PWMTASKSTACKSIZE,
                  NULL,
                  tskIDLE_PRIORITY + 2,
                  NULL);
  
  if (taskCreateFailed != pdTRUE) return 1;
  return 0;
}