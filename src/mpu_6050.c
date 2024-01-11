
#include "mpu_6050.h"

#define DIV_GYRO 16.4; 
#define DIV_ACCEL 8192

driff_t  driffVal;

int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;

int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;

void configMpu(void) {
	
	uint8_t check;
	uint8_t Data;

	// check device ID WHO_AM_I

	mpuRead(MPU6050_ADDR,WHO_AM_I_REG, &check, 1);

	if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		mpuWrite(MPU6050_ADDR, PWR_MGMT_1_REG, Data);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		mpuWrite(MPU6050_ADDR, SMPLRT_DIV_REG, Data);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ? 4g
		Data = 0x08;
		mpuWrite(MPU6050_ADDR, ACCEL_CONFIG_REG, Data);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=1 -> ? 2000 ?/s
		Data = 0x18;
		mpuWrite(MPU6050_ADDR, GYRO_CONFIG_REG, Data);
		
//		// config interrupt 
//		Data = 0x20; 
//		mpuWrite(MPU6050_ADDR, INT_PIN_CFG, Data);
//		// enable interupt when data ready 
//		Data = 0x01; 
//		mpuWrite(MPU6050_ADDR, INT_ENABLE, Data);
	}
	
}


void mpuWrite (uint8_t Address, uint8_t Reg, uint8_t Data)
{
	startI2c();
	addressI2c(Address);
	writeI2c(Reg);
	writeI2c(Data);
	stopI2c();
}


void mpuRead(uint8_t Address, uint8_t Reg, uint8_t *buffer, uint8_t size)
{
	startI2c();
	addressI2c(Address);
	writeI2c(Reg);
	startI2c();  // repeated start
	readI2c(Address+0x01, buffer, size);
	stopI2c();
	
}



void mpuReadAccel(void)
{
	// g 
	
	uint8_t Rx_data[6];
	
	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	mpuRead(MPU6050_ADDR, ACCEL_XOUT_H_REG, Rx_data, 6);

	Accel_X_RAW = (int16_t)(Rx_data[0] << 8 | Rx_data [1]);
	Accel_Y_RAW = (int16_t)(Rx_data[2] << 8 | Rx_data [3]);
	Accel_Z_RAW = (int16_t)(Rx_data[4] << 8 | Rx_data [5]);

// ACCEL +-2 => /16384
	
	
	Ax = (Accel_X_RAW * 1.0)/DIV_ACCEL;
	Ay = (Accel_Y_RAW * 1.0)/DIV_ACCEL;
	Az = (Accel_Z_RAW * 1.0)/DIV_ACCEL;
	
}


void mpuReadGyro(void)
{
	// speed angle 
	
	uint8_t Rx_data[6];
	
	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	mpuRead(MPU6050_ADDR, GYRO_XOUT_H_REG, Rx_data, 6);

	Gyro_X_RAW = (int16_t)(Rx_data[0] << 8 | Rx_data [1]);
	Gyro_Y_RAW = (int16_t)(Rx_data[2] << 8 | Rx_data [3]);
	Gyro_Z_RAW = (int16_t)(Rx_data[4] << 8 | Rx_data [5]);

// GYRO +- 500 => /65.5
	
	Gx = (Gyro_X_RAW * 1.0)/DIV_GYRO;
	Gy = (Gyro_Y_RAW * 1.0)/DIV_GYRO;
	Gz = (Gyro_Z_RAW *1.0)/DIV_GYRO;
}


float getAntiDriffCoefficient(uint8_t numSample, axis_e axis){

	int32_t sumAntiDriffVal = 0;
	float avgDriff = 0;
	TIM1->DIER &= (~1); 

	switch(axis){
		case AXIS_X:
			for(uint8_t i_cnt = 0; i_cnt < numSample; i_cnt++){
				mpuReadGyro(); 
				sumAntiDriffVal +=  Gyro_X_RAW; 
				delayMs(5); 
			}
			break;

		case AXIS_Y:
			for(uint8_t i_cnt = 0; i_cnt < numSample; i_cnt++){
				mpuReadGyro();
				sumAntiDriffVal += Gyro_Y_RAW;
				delayMs(5); 
			}
			break;

		case AXIS_Z:
			for(uint8_t i_cnt = 0; i_cnt < numSample; i_cnt++){
				mpuReadGyro();
				sumAntiDriffVal +=  Gyro_Z_RAW;
				delayMs(5); 
			}
			break;
		default:
			break;
	}

	avgDriff = (1.0*sumAntiDriffVal)/ numSample;
	TIM1->DIER |= 1; 
	return avgDriff;
}


void initMPU(void){
	
	Flash_Erase(SAVE_X_AXIS_ADDR);
	driffVal.x_Axis = (int16_t)Flash_Read_Int(SAVE_X_AXIS_ADDR);
	driffVal.y_Axis = (int16_t)Flash_Read_Int(SAVE_Y_AXIS_ADDR);
	driffVal.z_Axis = (int16_t)Flash_Read_Int(SAVE_Z_AXIS_ADDR);

	
	if((driffVal.x_Axis == (int16_t)0xFFFF) || (driffVal.y_Axis ==  (int16_t)0xFFFF) || (driffVal.z_Axis ==  (int16_t)0xFFFF)){
		
		driffVal.x_Axis = (int16_t)getAntiDriffCoefficient(100, AXIS_X);
		driffVal.x_Axis = -driffVal.x_Axis;

		driffVal.y_Axis = (int16_t)getAntiDriffCoefficient(100, AXIS_Y);
		driffVal.y_Axis = -driffVal.y_Axis;

		driffVal.z_Axis = (int16_t)getAntiDriffCoefficient(100, AXIS_Z);
		driffVal.z_Axis = -driffVal.z_Axis;

		Flash_Erase(SAVE_X_AXIS_ADDR);
		Flash_Write_Int(SAVE_X_AXIS_ADDR, driffVal.x_Axis);
		Flash_Write_Int(SAVE_Y_AXIS_ADDR, driffVal.y_Axis);
		Flash_Write_Int(SAVE_Z_AXIS_ADDR, driffVal.z_Axis);
		TIM1->DIER |= 1; 
		check = 2; 
	}
	else {
		check = 3; 
		TIM1->DIER |= 1; 
	}
}

