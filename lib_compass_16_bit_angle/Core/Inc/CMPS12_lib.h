/*
 * CMPS12_lib.h
 *
 *  Created on: May 23, 2023
 *      Author: Dimitri
 */

#ifndef INC_CMPS12_LIB_H_
#define INC_CMPS12_LIB_H_

#include "i2c.h"


#define CMPS12_16_BIT_H_ADDRESS 		  0x1A
#define CMPS12_16_BIT_L_ADDRESS 		  0x1B
#define CMPS12_CALIBRATION_STATUS_ADDRESS 0X1E
#define CMPS12_ADDRESS 					  0xC0




char wait_CMPS12_ready();
char get_CMPS12_angle(unsigned int * angle);


#endif /* INC_CMPS12_LIB_H_ */
