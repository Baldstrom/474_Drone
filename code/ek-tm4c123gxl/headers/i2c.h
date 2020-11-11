#ifndef __I2C_CUSTOM_H__
#define __I2C_CUSTOM_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
//#include "data.h"

#define SEND_DEL 4000
#define ENABLE_DEL 0

extern void i2c3_init();
extern void setup_timer();
extern void wait_for_timer();

// Change to pointer?
extern uint32_t i2c3_read_registers(unsigned short slav_addr, 
                            unsigned short reg, 
                            unsigned short len, // in bytes
                            char* data);
                            
extern void i2c3_write_registers(unsigned short slav_addr,
                            unsigned short reg,
                            unsigned short len, // in bytes
                            uint32_t* data);

extern void i2c3_write_register(unsigned short slav_addr,
                            unsigned short reg,
                            char data);

extern char i2c3_read_register(unsigned short slav_addr,
                            unsigned short reg);

extern uint32_t i2c3_read_registers_1(unsigned short slav_addr, 
                            unsigned short reg, 
                            unsigned short len, // in bytes
                            uint32_t* data);

#endif
