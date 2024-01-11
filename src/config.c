

#include "config.h"


void config(void) {
	// config GPIO
	configGPIO(); 
	//config AFIO
	configAFIO(); 
	
//	// cofig NVIC
	configNVIC(); 
//	// config EXTI
//	configEXTI(); 
	
	// config TIM4
	configTIM4(); 
	configTIM1(); 
	
	// config I2C
	configI2c(); 
	
//	configFlash(); 
	
	configUART1(); 
	
	// config MPU
	configMpu(); 
	delayMs(2000); 
	initMPU(); 
	
}