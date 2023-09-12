/*
 * mpu6050.h
 *
 *  Created on: Aug 7, 2023
 *      Author: azmai
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#define DEVICE_ADDRESS 0x68
#define MPU6050_ADDR 0b1101001
#define FS_GYRO_250 0
#define FS_GYRO_500 8
#define FS_GYRO_1000 16
#define FS_GYRO_2000 24

#define FS_ACC_2G 0
#define FS_ACC_4G 8
#define FS_ACC_8G 16
#define FS_ACC_16G 24

#define REG_CONFIG 0x1A
#define REG_SMPLRT_DIV 0x19
#define REG_CONFIG_GYRO 27
#define REG_CONFIG_ACC 28
#define REG_USR_CTRL 107
#define REG_DATA 59
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H_REG 0x43
void mpu6050_init();
void mpu6050_read();
#endif /* INC_MPU6050_H_ */
