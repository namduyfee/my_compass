
#ifndef		__MPU__

#define		__MPU__


//#include "config.h"

#include <math.h>
#include <stm32f10x.h>
#include "i2c.h"
#include "timer.h"
#include "flash.h" 

#define MPU6050_ADDR 0xD0

#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19



#define ACCEL_CONFIG_REG 0x1C
#define GYRO_CONFIG_REG 0x1B 


#define ACCEL_XOUT_H_REG 0x3B
#define ACCEL_XOUT_L_REG 0x3C

#define ACCEL_YOUT_H_REG 0x3D
#define ACCEL_YOUT_L_REG 0x3E

#define ACCEL_ZOUT_H_REG 0x3F
#define ACCEL_ZOUT_L_REG 0x40


#define GYRO_XOUT_H_REG 0x43
#define GYRO_XOUT_L_REG 0x44


#define GYRO_YOUT_H_REG 0x45
#define GYRO_YOUT_L_REG 0x46

#define GYRO_ZOUT_H_REG 0x47
#define GYRO_ZOUT_L_REG 0x48


#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define INT_STATUS 0x3A


#define SAVE_X_AXIS_ADDR	((uint32_t)0x0801FC00) // page 127
#define SAVE_Y_AXIS_ADDR	((uint32_t)(SAVE_X_AXIS_ADDR + 4)) // page 127
#define SAVE_Z_AXIS_ADDR	((uint32_t)(SAVE_Y_AXIS_ADDR + 4)) // page 127

extern int check; 
extern float Ax, Ay, Az; 
extern float Gx, Gy, Gz; 

typedef enum _AXIS_{
	AXIS_X = 0,
	AXIS_Y,
	AXIS_Z,
}axis_e;

typedef struct driff_t {
	int16_t x_Axis;
	int16_t y_Axis;
	int16_t z_Axis;
}driff_t;


void configMpu(void); 
void mpuWrite (uint8_t Address, uint8_t Reg, uint8_t Data); 
void mpuRead(uint8_t Address, uint8_t Reg, uint8_t *buffer, uint8_t size); 
void mpuReadAccel(void); 
void mpuReadGyro(void); 


void initMPU(void); 
float getAntiDriffCoefficient(uint8_t numSample, axis_e axis); 

#endif 


