

#include "uart.h"


void configUART1(void) {
	// enable clock UART1 
	RCC->APB2ENR |= 1<<14; 
	
	// remap = 1 Uart1 , PB6_TX, PB7_RX 
	// enable uart,  8 bit data, enable DMA1_channel 5 
	// enable trans , recive
	
	
	// uart mode trans , recevi interrupt 
	
	USART1->CR1 = 0x202C; 
	
//	USART1->BRR = 0x1D4C; 				// 9600
	USART1->BRR = 0x271; 				// 115200

}

void configUART2 (void) {
	RCC->APB1ENR |= 1<<17; 
	// 8 bit data, enable trans, receive, dma1_channel 6
	
	USART2->CR3 |= 1<<6; 
	
	USART2->CR3 |= 1<<7;						// enable DMA trans
	
	USART2->CR1 = 0x200C; 
	
//	USART2->BRR = 0xEA6;					// 9600
	USART2->BRR = 0x138; 				// 115200
	// enable UART use bit 13 
	
}
void configUART3(void) {
	// enable clock UART3
	RCC->APB1ENR |= 1<<18;
	
	// remap = 0
	
	// enable trans, receive, dma1_channel 3, 8 bit data
	USART3->CR3 |= 1<<6; 
	
	USART3->CR3 |= 1<<7;						// enable DMA trans
	
	USART3->CR1 = 0x200C; 
	
//	USART3->BRR = 0xEA6;					// 9600
	USART3->BRR = 0x138; 				// 115200
	// enable UART use bit 13 
}

