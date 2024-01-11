
#include "timer.h"

void configTIM1(void) {
	
	// interrupt timer 1 50 ms 
	RCC->APB2ENR |= 1<<11;
	TIM1->ARR = 1000-1; 
	TIM1->PSC = 72-1; 
	TIM1->EGR |= 1; 
	
	TIM1->CR1 |= 1; 
}



void configTIM4(void) {
	// config TIM4
	RCC->APB1ENR |= 1<<2;	 
	TIM4->ARR = 2000-1; 
	TIM4->PSC = 72-1; 
	TIM4->EGR |= 1; 
	TIM4->CR1 |= 1; 
	
}

void delayMs(uint32_t ms) {
	
	while(ms--) {
		
		TIM4->CNT = 0; 
		while(TIM4->CNT != 1000); 
		
	}
	
}