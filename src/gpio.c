
#include "gpio.h"


void configGPIO(void) {
	
// PORT A

//	RCC->APB2ENR |= 1<<2; 
//	GPIOA->CRL &= 0; 
//	// input
//	GPIOA->CRL |= (0x08<<8); 
//	// pull up 
//	GPIOA->ODR |= 1<<2; 
	
// PORT B
	
	RCC->APB2ENR |= 1<<3;
	// CRH = 0
	GPIOB->CRH &= 0; 
	// PB8, PB9 output alternate open drain 
	GPIOB->CRH |= 0xFF; 
	
}

void configAFIO(void) {
	
	RCC->APB2ENR |= 1; 
	// I2C remap 
	AFIO->MAPR |= 1<<1; 
	
//	AFIO->EXTICR[0] &= 0xF0FF; 
	
}

