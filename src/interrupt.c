
#include "interrupt.h"
#include <math.h>
#include <stdlib.h>

uint8_t tx; 
uint8_t rx_buff[4]; 
uint8_t i = 0; 

float xLastVal, yLastVal, zLastVal; 
volatile int16_t  xVal, yVal, zVal,  xS, yS, zS, xA, yA, zA; 

int16_t z;  

void TIM1_UP_IRQHandler (void) {

	if(TIM1->SR & 1) {
		z = (int16_t)Flash_Read_Int(SAVE_Z_AXIS_ADDR); 
		
		mpuReadGyro(); 
		
		// roll 
		xVal =  (int16_t)Gyro_X_RAW; 
		if(abs(zVal + (int16_t)driffVal.x_Axis) < 100) 
			xA = 0; 
		else 
			xA = ( xVal  + (int16_t)driffVal.x_Axis);	
		xLastVal = xLastVal + ((float)xA * 0.00006);				// 0.001 = timer 1ms Tinh theo fOSC = 72Mhz
		xAngle = (int16_t)xLastVal;
		
		// pitch
		yVal =  (int16_t)Gyro_Y_RAW; 
		if(abs(yVal + (int16_t)driffVal.y_Axis) < 100) 
			yA = 0; 
		else 
			yA = ( yVal  + (int16_t)driffVal.y_Axis);	
		yLastVal = yLastVal + ((float)yA * 0.00006);				// 0.001 = timer 1ms Tinh theo fOSC = 72Mhz
		yAngle = (int16_t)yLastVal;
		
		// yaw 
		zVal =  (int16_t)Gyro_Z_RAW; 
		if(abs(zVal + (int16_t)driffVal.z_Axis) < 10) 
			zA = 0; 
		else 
			zA = ( zVal  + (int16_t)driffVal.z_Axis);	
		zLastVal = zLastVal + ((float)zA * 0.00006);				// 0.001 = timer 1ms Tinh theo fOSC = 72Mhz
		zAngle = (int16_t)round(zLastVal);
		
		TIM1->SR &= (~1); 
	}

}	


// void EXTI2_IRQHandler (void) {
//	 if(EXTI->PR & 1<<2) {
//		 uint8_t tem; 
//		 mpuRead(MPU6050_ADDR, INT_STATUS, &tem, 1); 
//		 if(tem & 1) {
//				mpuReadAccel(); 
//				mpuReadGyro(); 
//				mpuRead(MPU6050_ADDR, INT_STATUS, &tem, 1); 
//		 }
//		 EXTI->PR |= 1<<2; 
//	 }
//	 
// }


void USART1_IRQHandler (void) {
	
	if(USART1->SR & (1<<5)) {
		tx = USART1->DR; 
		if(tx == 'z') {
			rx_buff[0] = 'z'; 
			rx_buff[1] = 'z'; 
			rx_buff[2] = (zAngle & 0xFF); 
			rx_buff[3] = ((zAngle >> 8) & 0xFF); 
			USART1->DR = rx_buff[0]; 
		}
		USART1->CR1 |= 1<<7; 
	}
	if(USART1->SR & (1<<7)) {

		i++; 
		if(i == 4) {
			i = 0; 
			USART1->CR1 &= (~(1<<7));
		}
		else 
			USART1->DR = rx_buff[i]; 
	}
	
}









 
 