

#ifndef		__INTERRUPT__

#define	__INTERRUPT__

#include <stm32f10x.h> 
#include "mpu_6050.h" 
extern int check; 

extern int16_t xAngle, yAngle, zAngle; 
extern driff_t  driffVal;
extern int16_t Gyro_X_RAW , Gyro_Y_RAW, Gyro_Z_RAW; 

void TIM1_UP_IRQHandler (void); 

// void EXTI2_IRQHandler (void); 


#endif
