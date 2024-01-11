
#include "nvic.h"



void configNVIC(void) {
	
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4); 
	
//	NVIC_SetPriority(EXTI2_IRQn, 1); 

//	NVIC_EnableIRQ(EXTI2_IRQn); 
	
	NVIC_SetPriority(TIM1_UP_IRQn, 2); 
	
	NVIC_EnableIRQ(TIM1_UP_IRQn); 
	
		NVIC_SetPriority( USART1_IRQn, 1); 
	NVIC_EnableIRQ( USART1_IRQn); 
}
