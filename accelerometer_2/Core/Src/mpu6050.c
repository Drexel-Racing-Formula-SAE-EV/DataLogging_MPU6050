/*
 * mpu6050.c
 *
 *  Created on: Aug 7, 2023
 *      Author: azmain
 */


#include "mpu6050.h"
#include <main.h>
#include <stdio.h>

extern	I2C_HandleTypeDef hi2c1;
extern float x_acc;
extern float y_acc;
extern float z_acc;
extern float x_gyro;
extern float y_gyro;
extern float z_gyro;
extern float temp;

void mpu6050_init(){
	uint8_t temp_data;
	HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c1, (MPU6050_ADDR<<1), 1,100);
	  if (ret==HAL_OK){
		  printf("The device is ready\n");
	  }
	  else{
		  printf("The device is not ready. Check configurations\n");
	  }

	  temp_data = 0;
	  ret = HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR<<1), REG_SMPLRT_DIV,1, &temp_data, 1, 200);
	  if (ret==HAL_OK){
		  printf("Configuring Sample Rate Divider\n");
	  }
	  else{
		  printf("Failed to configure Sample Rate Divider\n");
	  }

	  temp_data = 2;
	  ret = HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR<<1), REG_CONFIG,1, &temp_data, 1, 200);
	  if (ret==HAL_OK){
		  printf("Configuring Configuration Register\n");
	  }
	  else{
		  printf("Failed to configure Configuration Register\n");
	  }

	  temp_data = FS_GYRO_500;
	  ret = HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR<<1), REG_CONFIG_GYRO,1, &temp_data, 1, 200);
	  if (ret==HAL_OK){
		  printf("Configuring Gyroscope\n");
	  }
	  else{
		  printf("Failed to configure Gyroscope\n");
	  }

	  temp_data = FS_ACC_4G;
	  ret = HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR<<1), REG_CONFIG_ACC,1, &temp_data, 1, 200);
	  if (ret==HAL_OK){
	  	  printf("Configuring Accelerometer \n");
	  }
	  else{
	  	  printf("Failed to Configure Accelerometer \n");
	  }

	  temp_data = 0;
	  ret = HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR<<1), REG_USR_CTRL,1, &temp_data, 1, 200);
	  if (ret==HAL_OK){
	  	  printf("Exiting from Sleep Mode\n");
	  }
	  else{
	      printf("Failed to Exit from Sleep Mode \n");
	  }
}

void mpu6050_read(){
	uint16_t x_accR, y_accR, z_accR, x_gyroR, y_gyroR, z_gyroR;
	HAL_StatusTypeDef ret;
	uint8_t data[14];
	uint8_t read_reg[14] = {ACCEL_XOUT_H,
							ACCEL_XOUT_H + 1,
							ACCEL_XOUT_H + 2,
							ACCEL_XOUT_H + 3,
							ACCEL_XOUT_H + 4,
							ACCEL_XOUT_H + 5,
							ACCEL_XOUT_H + 6,
							ACCEL_XOUT_H + 7,
							ACCEL_XOUT_H + 8,
							ACCEL_XOUT_H + 9,
							ACCEL_XOUT_H + 10,
							ACCEL_XOUT_H + 11,
							ACCEL_XOUT_H + 12,
							ACCEL_XOUT_H + 13};

	ret = HAL_I2C_Mem_Read(&hi2c1, (MPU6050_ADDR<<1), ACCEL_XOUT_H, 1, data, 14, 200);
	if(ret != HAL_OK){
		printf("Error reading MPU6050\n");
		while(1);
	}

	// ret = HAL_I2C_Master_Transmit(&hi2c1, (MPU6050_ADDR<<1), read_reg, 6, 1000);
	// ret = HAL_I2C_Master_Receive(&hi2c1,(MPU6050_ADDR<<1), data, 6, 1000);

	// x_acc = ((((int16_t)data[0])<<8)+data[1])/16384.0;
	// y_acc = ((((int16_t)data[2])<<8)+data[3])/16384.0;
	// z_acc = ((((int16_t)data[4])<<8)+data[5])/16384.0;
	// //printf("x axis acceleration: %d \n",x_acc);

	//HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(&hi2c1, (MPU6050_ADDR<<1), read_reg, 14, 1000);
    //ret = HAL_I2C_Master_Receive(&hi2c1, (MPU6050_ADDR<<1), data, 14, 1000);


    temp = ((float)(((uint16_t)data[6] << 8) | data[7]) / 340.0) + 36.53;

    x_accR = ((uint16_t)data[0] << 8) | data[1];
    y_accR = ((uint16_t)data[2] << 8) | data[3];
    z_accR = ((uint16_t)data[4] << 8) | data[5];

    x_gyroR = (uint16_t)data[8];
    x_gyroR = (x_gyroR << 8) | data[9];
    y_gyroR = (uint16_t)data[10];
    y_gyroR = (y_gyroR << 8) | data[11];
    z_gyroR = (uint16_t)data[12];
    z_gyroR = (z_gyroR << 8) | data[13];

    x_acc = (float)x_accR/ 8192;
    y_acc = (float)y_accR / 8192;
    z_acc = (float)z_accR / 8192;

    x_gyro = (float)x_gyroR / 65.5f;
    y_gyro = (float)y_gyroR / 65.5f;
    z_gyro = (float)z_gyroR / 65.5f;

    //(void)ret;
}

