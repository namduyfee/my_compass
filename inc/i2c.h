
#ifndef		__I2C__

#define	__I2C__


#include <stm32f10x.h> 
//#include "config.h"

#define I2C_CR1_PE_Set            ((uint16_t)0x0001)  // Peripheral enable
#define I2C_CR1_ACK_Set           ((uint16_t)0x0400)  // Acknowledge enable
#define I2C_CR1_START_Set         ((uint16_t)0x0100)  // Start generation
#define I2C_CR1_STOP_Set          ((uint16_t)0x0200)  // Stop generation
#define I2C_FLAG_RXNE             ((uint32_t)0x10008040) // Receive data register not empty
#define I2C_FLAG_BTF              ((uint32_t)0x00000004) // Data transfer finished

extern uint8_t xoa; 



void configI2c(void); 
void startI2c(void); 
void addressI2c(uint8_t add); 
void writeI2c(uint8_t data); 
void writeMutiI2c (uint8_t *data, uint8_t size); 
void stopI2c(void); 
void readI2c(uint8_t Address, uint8_t* buffer, uint8_t size); 

#endif
