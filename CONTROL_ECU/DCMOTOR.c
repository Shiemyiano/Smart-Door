#include "PMW.h"
#include "gpio.h"
#include "DCMOTOR.h"

/*Functions initiate the DC_MOTOR (H/W layer) to configure with MC */
void DcMotor_Init(void){
	/* configure DC_MOTOR pins (PB0,PB1) as output pins */
	GPIO_setupPinDirection(MOTOR1_PORT_ID,MOTOR1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR2_PORT_ID,MOTOR2_PIN_ID, PIN_OUTPUT);
	/*
	 * Motor is stop at the beginning
	 * ideal case Motor is stopped
	 * */
	GPIO_writePin(MOTOR1_PORT_ID,MOTOR1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR2_PORT_ID,MOTOR2_PIN_ID,LOGIC_LOW);
}


/*
 * Function definition to control direction and speed of motor
 * speed of motor depend on current temperature
 * we make all direction possible for motor but in our case we work only with CW
 * */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	/*
	 * DutyCycle is a local var to store Duty_Cycle
	 * This equation convert from (0 to 100 ) speed into ( 0 to 255 ) Bits
	 * */
	uint8 DutyCycle = (speed*TOTAL_NUMBER_OF_ROTATE)/100;
	/*
	 * we have 3 states ( clock_wise, Anti_CW, Stopped)
	 * first we check the direction then apply speed to motor
	 * configure Motor pins depend on direction
	 * applying high to one pin and zero to other pin
	 *
	 * in case stop, applying zero to both of pins
	 * */
	if (state == CW){
		Timer0_PWM_Init(DutyCycle);
		GPIO_writePin(MOTOR2_PORT_ID,MOTOR1_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(MOTOR1_PORT_ID,MOTOR2_PIN_ID,LOGIC_LOW);
	}
	else if (state == A_CW){
		Timer0_PWM_Init(DutyCycle );
		GPIO_writePin(MOTOR2_PORT_ID,MOTOR2_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(MOTOR1_PORT_ID,MOTOR1_PIN_ID,LOGIC_LOW);
	}
	else if (state == Stop)
	{
		GPIO_writePin(MOTOR1_PORT_ID,MOTOR1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR2_PORT_ID,MOTOR2_PIN_ID,LOGIC_LOW);
	}
}

void DcMotor_DE_Init()
{
	GPIO_writePin(MOTOR2_PORT_ID,MOTOR1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR1_PORT_ID,MOTOR2_PIN_ID,LOGIC_LOW);
}
