#include "i2c.h"

static void send_i2c3(char bits);

void send_i2c3(char bits) 
{
  // At the start:
    // RUN, START 0x3
  // Not at the end:
    // ACK, RUN  0x9
  // At the end:
    // STOP, RUN = 0x5
  // REGISTER: HS, ACKM, STOP, START, RUN
  //while (I2C3_MCS_R & 0x01); // WAIT
  int mcs_curr = I2C3_MCS_R; // READ
  I2C3_MCS_R = 0x00;          // CLEAR REGISTER
  I2C3_MCS_R = (bits & 0x16) | 0x01; // PREP BITS & SEND
  // TODO: add timeout for the wait
  //while (I2C3_MCS_R & 0x01); // WAIT
  if (ENABLE_DEL) { wait_for_timer(); }
}

// setup for i2c3
void i2c3_init()
{
  // enable i2c on clock rcgci2c
  SYSCTL_RCGCI2C_R |= 0x8; 
 
  // enable clock of gpio D
  SYSCTL_RCGCGPIO_R |= 0x8;
  
  // change function of gpio D with AFSEL
  GPIO_PORTD_AFSEL_R = 0x3;
  GPIO_PORTD_DEN_R = 0x3;
   
  // enable i2csda for open-drain sda pin
  GPIO_PORTD_ODR_R |= 0x2;
  
  // configure pctl
  GPIO_PORTD_PCTL_R = 0X33;
  
  // enable master with i2cmcr
  I2C3_MCR_R = 0x10;
  
  // set clock speed
  I2C3_MTPR_R = 7;
}

// transimit data by i2c to slav_addr sincle version
uint32_t i2c3_single_send(unsigned short slav_addr, unsigned short data) 
{
  // set up addr for i2c standard
  short addr = (slav_addr << 1) & ~0x1;
  
  // specify slave address
  I2C3_MSA_R = addr;
  
  // setup data to be sent
  I2C3_MDR_R = data;
  
  // wait until bus is not busy polling iscmcs busbsy bit
  while (I2C3_MCS_R & 0x40); 
  
  // send data to slave device
  I2C3_MCS_R = 0x7;
  
  // wait until done by polling iscmcs busy bit
  while (I2C3_MCS_R & 0x01) {} 
  
  // check for errors in i2cmcs
  return (I2C3_MCS_R & 0X2);
}

// recieve data from slav_addr single version
uint32_t i2c3_single_recieve(unsigned short slav_addr)
{
  // set up addr for i2c standard
  short addr = (slav_addr << 1) | 0x1;
  
  // specify slave address
  I2C3_MSA_R = addr;
  
  // specify config of communication
  I2C3_MCS_R = 0x7;
  
  // wait until bus is not busy polling iscmcs busbsy bit
  //while (I2C3_MCS_R & 0x40) {} 
  
  // send data to slave device
  //I2C3_MCS_R = 0x7;
  
  // wait until done by polling iscmcs busy bit
  while (!(I2C3_MCS_R & 0x01)) {} 
  
  // check for errors in i2cmcs
  return (I2C3_MCS_R & 0X2) ? 0xDEADBEEF : I2C3_MDR_R;
  
}

uint32_t i2c3_read_registers(unsigned short slav_addr, 
                            unsigned short reg, 
                            unsigned short len, // in bytes
                            char* data) 
{
  // Clip length
  if (len > 4) { len = 4; }
  if (len < 1) { len = 1; }

  int multiple_read = len > 1;

  // Write to address
  short addr = (slav_addr << 1) & ~0x1;
  
  // wait until bus is not busy polling iscmcs busbsy bit
  while (I2C3_MCS_R & 0x40);
  
  // Specify slave address & RW mode (writing)
  I2C3_MSA_R = addr;
  // Send read register
  I2C3_MDR_R = reg;
  
  // send data to slave device
  send_i2c3(0x0B);
    
  // check for errors in i2cmcs
  int write_error = I2C3_MCS_R & 0x02;
  if (write_error) { return write_error; }

  // Read from the bus (set slave address to read mode)
  I2C3_MSA_R = (slav_addr << 1) | 0x01;

  // Read first byte with ACK
  int MCS = 0x08;
  if (multiple_read) { MCS = 0x08; }
  else { MCS = 0x05; }
  send_i2c3(MCS | 0x02);
  data[0] = I2C3_MDR_R & 0xFF;
  
  if (multiple_read) {
    int error = 0;
    int i;
    for (i = 1; i < len; i++) 
    {
      if (i == (len - 1)) { send_i2c3(0x05); } // Transmit last NOACK and STOP
      else { send_i2c3(0x08); } // ACK if not last byte
      data[i] = I2C3_MDR_R & 0xFF;
      error |= I2C3_MCS_R & 0x02;
    }
    if (error) { return error; }
  }

  return 0;

}

void i2c3_write_register(unsigned short slav_addr,
                      unsigned short reg,
                      char data) 
{
  // Write slave address
  short addr = (slav_addr << 1) & ~0x1;
  
  // wait until bus is not busy polling iscmcs busbsy bit
  while (I2C3_MCS_R & 0x40);
  
  // specify slave address
  I2C3_MSA_R = addr;
  
  // setup data to be sent
  I2C3_MDR_R = reg;
  
  // send data to slave device
  send_i2c3(0x03);

  // Send register data
  I2C3_MDR_R = data;
  send_i2c3(0x05);

  // wait until bus is not busy polling iscmcs busbsy bit
  while (I2C3_MCS_R & 0x40);
}

void setup_timer() 
{
  SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;
  TIMER0_CTL_R = 0x00;
  TIMER0_TAMR_R = 0x00;
  TIMER0_TAMR_R |= 0x02;
  TIMER0_TAILR_R = SEND_DEL;
  TIMER0_IMR_R |= 0x01;
  TIMER0_CTL_R |= 0x01;
  
  //while (!(TIMER0_RIS_R & 0x01));
}

void wait_for_timer()
{
  TIMER0_TAILR_R = SEND_DEL;
  TIMER0_ICR_R |= 0x01;
  while (!(TIMER0_RIS_R & 0x01));
  TIMER0_TAILR_R = SEND_DEL;
}

