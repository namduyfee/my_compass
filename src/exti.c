

#include "exti.h"


void configEXTI(void) {
	
	EXTI->IMR &= 0; 
	EXTI->FTSR &= 0; 
	
	
	EXTI->IMR |= 1<<2; 
	EXTI->FTSR |= 1<<2; 
	
	
}
