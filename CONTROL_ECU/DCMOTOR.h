/*
 * DCMOTOR.h
 *
 *  Created on: Feb 25, 2022
 *      Author: Abdelrahman Elshiemy
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

/************************************Definitions*************************/

#define TOTAL_NUMBER_OF_ROTATE			255
#define MOTOR1_PORT_ID                 PORTB_ID
#define MOTOR1_PIN_ID                  PIN0_ID

#define MOTOR2_PORT_ID                 PORTB_ID
#define MOTOR2_PIN_ID                  PIN1_ID

#define CW 		0
#define A_CW 	1
#define Stop 	3


/*************************************Declaration**************************/
typedef unsigned char DcMotor_State;

void DcMotor_Init();
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
void DcMotor_DE_Init();
#endif /* DCMOTOR_H_ */
