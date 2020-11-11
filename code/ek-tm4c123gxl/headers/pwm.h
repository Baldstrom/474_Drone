#ifndef __PWM__
#define __PWM__

#include "data.h"

#define PID_X_P 0.0001f
#define PID_X_I 0.0001f
#define PID_X_D 0.00f

#define PID_Y_P 0.0001f
#define PID_Y_I 0.0001f
#define PID_Y_D 0.00f

#define PID_Z_P 0.01f
#define PID_Z_I 0.01f
#define PID_Z_D 0.0f

uint32_t PWM_task_init(void);

#endif
