/*
 * Buzzer.h
 *
 *  Created on: Mar 21, 2022
 *      Author: Abdelrahman Elshiemy
 */

#ifndef BUZZER_H_
#define BUZZER_H_


#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define Buzzer_PORT_ID		PORTA_ID
#define Buzzer_PIN_ID		PIN0_ID

void Buzzer_init();
void Buzzer_ON();
void Buzzer_OFF();


#endif /* BUZZER_H_ */
