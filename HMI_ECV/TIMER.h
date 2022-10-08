/*
 * TIMER.h
 *
 *  Created on: Mar 13, 2022
 *      Author: Abdelrahman Elshiemy
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
#include "avr\io.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PWM_OUTPUT 		(DDRB | (1<<PB3))


/*******************************************************************************
 *                                Type Declaration                                   *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXT_CLK_FAILLING_EDGE,EXT_CLK_RAISING_EDGE
}Timer_Clock;

typedef enum
{
	Timer0,
	Timer1,
	Timer2
}Timer_ID;

typedef enum
{
	normalMode,PWM,CTC,fastPWM
}Timer_Mode;



typedef struct
{

	Timer_ID Timer_no;
	Timer_Mode mode;
	Timer_Clock clk;
	uint8 init_value;
	uint8 comp_value;
}Timer_ConfigType;

/*******************************************************************************
 *                                Function Prototype                           *
 *******************************************************************************/

void Timer_init(const Timer_ConfigType * timerConfig);

void Timer0_De_init();
void Timer1_De_init();
void Timer2_De_init();


void Timer0_setCallBack(void(*a_ptr)(void));

void Timer1_setCallBack(void(*a_ptr)(void));

void Timer2_setCallBack(void(*a_ptr)(void));


#endif /* TIMER_H_ */
