/*
 * Buzzer.c
 *
 *  Created on: Mar 21, 2022
 *      Author: Abdelrahman Elshiemy
 */

#include "Buzzer.h"
#include "gpio.h"
#include "TIMER.h"

void Buzzer_init()
{
	GPIO_setupPinDirection(Buzzer_PORT_ID,Buzzer_PIN_ID, PIN_OUTPUT);
}
void Buzzer_ON()
{
	GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_HIGH);
}
void Buzzer_OFF()
{
	GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_LOW);

}
