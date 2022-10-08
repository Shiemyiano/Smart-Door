/*
 * TIMER.c
 *
 *  Created on: Mar 13, 2022
 *      Author: Abdelrahman Adel ELlshiemy
 */

#include "TIMER.h"
#include <avr\io.h>
#include <avr/interrupt.h>


static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;
uint8 tick =0;

ISR(TIMER0_OVF_vect)
{
	tick++;
	if(tick == 100){
		if(g_callBackPtr0 != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
			TIFR |= (1<<TOV0);
			Timer0_De_init();

		}
	}
}
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */

	}
}
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

void Timer_init(const Timer_ConfigType * timerConfig)
{
	if(timerConfig->Timer_no == Timer0){
		if(timerConfig->mode == normalMode)
		{
			//initial value
			TCNT0 = timerConfig->init_value;
			TIMSK |= (1<<TOIE0);
			TCCR0 = (TCCR0 & 0xF0) | (timerConfig->clk & 0x07);


		}
		else if(timerConfig->mode == CTC)
		{
			//initial value
			TCNT0 = timerConfig->init_value;
			//final value
			OCR0 = timerConfig->comp_value;
			// ctc mode and non inverting mode
			TCCR0 = (1<<FOC0) | (1<<WGM01);
			TIMSK |= (1<<OCIE0);
			TCCR0 = (TCCR0 & 0xF0) | (timerConfig->clk & 0x07);
		}
	}
	else if(timerConfig->Timer_no == Timer1){
		if(timerConfig->mode == normalMode)
		{
			TCNT1 = timerConfig->init_value;
			TIMSK |= (1<<TOIE1);
			TCCR1B = (TCCR1B & 0xF0) | (timerConfig->clk & 0x07);


		}
		else if(timerConfig->mode == CTC)
		{
			TCNT1 = timerConfig->init_value;		/* Set timer1 initial count to zero */
			OCR1A = timerConfig->comp_value;    /* Set the Compare value to 125 ((125/500) * 100 = 25%) */
			TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */
			/* Configure timer control register TCCR1A
			 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
			 * 2. FOC1A=1 FOC1B=0
			 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
			 */
			TCCR1A = (1<<FOC1A);

			/* Configure timer control register TCCR1B
			 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
			 * 2. Prescaler =
			 */
			TCCR1B = (1<<WGM12) | (timerConfig->clk & 0x07);


		}
	}
	else if(timerConfig->Timer_no == Timer2){
		if(timerConfig->mode == normalMode)
		{
			//initial value
			TCNT2 = timerConfig->init_value;
			TIMSK |= (1<<TOIE2);
			TCCR2 = (TCCR2 & 0xF0) | (timerConfig->clk & 0x0F);
		}
		else if(timerConfig->mode == CTC)
		{
			//initial value
			TCNT2 = timerConfig->init_value;
			//final value
			OCR2 = timerConfig->comp_value;
			// ctc mode and non inverting mode
			TCCR2 = (1<<FOC2) | (1<<WGM21);
			TIMSK |= (1<<OCIE2);
			TCCR2 = (TCCR2 & 0xF0) | (timerConfig->clk & 0x0F);
		}
	}
}

void Timer0_De_init()
{
	TCCR0 = 0;
}
void Timer1_De_init()
{
	TCCR1B = 0;
}
void Timer2_De_init()
{
	TCCR2  = 0;
}
void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr0 = a_ptr;
}
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr1 = a_ptr;
}
void Timer2_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr2 = a_ptr;
}
