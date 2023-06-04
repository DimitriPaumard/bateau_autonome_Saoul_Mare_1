/*
 * CMPS12_lib.c
 *
 *  Created on: May 23, 2023
 *      Author: Dimitri
 */

#include "CMPS12_lib.h"

char wait_CMPS12_ready() {
	HAL_StatusTypeDef i2c_error_status;

	char transmit_buf[2];
	char receive_buf[2];

	transmit_buf[0] = CMPS12_CALIBRATION_STATUS_ADDRESS;
	i2c_error_status = HAL_I2C_Master_Transmit(&hi2c1, CMPS12_ADDRESS,
			transmit_buf, 1, HAL_MAX_DELAY);

	if (i2c_error_status == HAL_ERROR)
		return -1;

	HAL_I2C_Master_Receive(&hi2c1, CMPS12_ADDRESS, receive_buf, 1,
	HAL_MAX_DELAY);
	if (i2c_error_status == HAL_ERROR)
		return -1;

	return receive_buf[0];

}
char get_CMPS12_angle(unsigned int *angle) {
	HAL_StatusTypeDef i2c_error_status;

	unsigned char transmit_buf[2];
	unsigned char receive_buf[2];
	unsigned int temp_buf = 0;
	//printf("begin transmission\r\n");
	transmit_buf[0] = CMPS12_16_BIT_L_ADDRESS;
	i2c_error_status = HAL_I2C_Master_Transmit(&hi2c1, CMPS12_ADDRESS,
			transmit_buf, 1, HAL_MAX_DELAY);

	if (i2c_error_status == HAL_ERROR)
		return -1;

	HAL_I2C_Master_Receive(&hi2c1, CMPS12_ADDRESS, receive_buf, 1,
	HAL_MAX_DELAY);
	if (i2c_error_status == HAL_ERROR)
		return -1;

	temp_buf = (int)receive_buf[0];

	transmit_buf[0] = CMPS12_16_BIT_H_ADDRESS;
	i2c_error_status = HAL_I2C_Master_Transmit(&hi2c1, CMPS12_ADDRESS,
			transmit_buf, 1, HAL_MAX_DELAY);

	if (i2c_error_status == HAL_ERROR)
		return -1;

	HAL_I2C_Master_Receive(&hi2c1, CMPS12_ADDRESS, receive_buf, 1,
	HAL_MAX_DELAY);
	if (i2c_error_status == HAL_ERROR)
		return -1;

	temp_buf |= receive_buf[0]<<8;

	*angle = temp_buf;

	return 0;
}
