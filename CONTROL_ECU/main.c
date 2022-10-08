#include "external_eeprom.h"
#include "gpio.h"
#include "util/delay.h"
#include "twi.h"
#include "uart.h"
#include "Buzzer.h"
#include "DCMOTOR.h"
union fullPass
{
	uint16 fullPass;
	unsigned char oct[2];
};

UART_ConfigType uartConfig = {9600 , 1 , 0 , BIT_8 , 0};

int main(void)
{
	// var for pass
	union fullPass Password;
	union fullPass checkPassword;
	uint8 wrong = 0 ;
	uint16 val ;
	uint8 optionVar;
	UART_init(&uartConfig);
	_delay_ms(1000);
	TWI_init();
	Buzzer_init();
	DcMotor_Init();
	_delay_ms(100);

	EEPROM_readByte(0x0311,&Password.oct[0]);
	_delay_ms(100);
	EEPROM_readByte(0x0319,&Password.oct[1]);
	_delay_ms(100);
	val = Password.fullPass;

	while(1)
	{
		if(val == 0xFFFF)
		{
			UART_sendByte(0);
			Password.oct[0] = UART_recieveByte();
			_delay_ms(100);
			Password.oct[1] = UART_recieveByte();
			_delay_ms(100);
			EEPROM_writeByte(0x0311,Password.oct[0]);
			_delay_ms(100);
			EEPROM_writeByte(0x0319,Password.oct[1]);
			_delay_ms(100);

			val = Password.fullPass;

		}
		else
		{
			UART_sendByte(1);
			optionVar = UART_recieveByte();
		}

		if(optionVar == '+')
		{
			//check pass
			checkPassword.oct[0] = UART_recieveByte();
			_delay_ms(100);
			checkPassword.oct[1] = UART_recieveByte();
			_delay_ms(100);

			// han3mel do while 3shan net2ked mn right pass 3 marat
			//if correct sent 2
			// open door for 5 sec
			do{

				if(checkPassword.fullPass == Password.fullPass)
				{
					UART_sendByte(2);
					_delay_ms(500);
					wrong = 0;
					// Motor On
					DcMotor_Rotate(A_CW,100);
					_delay_ms(9000);
					DcMotor_Rotate(CW,100);
					_delay_ms(9000);
					DcMotor_Rotate(Stop,100);
					break;
				}

				else if(wrong <2)
				{
					UART_sendByte(3);
					wrong++;
					break;
				}
				else if(wrong == 2)
				{
					UART_sendByte(4);
					//Buzzer_ON();
					// alarm on for 15 sec
					Buzzer_ON();
					_delay_ms(1000000);
					Buzzer_OFF();
					_delay_ms(1000000);
					wrong = 0;
					break;
				}

				// if * = 3 then alarm sent 5
				//

			}while(checkPassword.fullPass != Password.fullPass);


		}
		else if(optionVar == '-')
		{
			// sent (3)
			//receive pass
			// rewrite pass inside eeprom
			//check pass
			checkPassword.oct[0] = UART_recieveByte();
			_delay_ms(100);
			checkPassword.oct[1] = UART_recieveByte();
			_delay_ms(100);
			UART_sendByte(5);
			_delay_ms(500);
			Password.oct[0] = UART_recieveByte();
			_delay_ms(100);
			Password.oct[1] = UART_recieveByte();
			_delay_ms(100);
			EEPROM_writeByte(0x0311,Password.oct[0]);
			_delay_ms(100);
			EEPROM_writeByte(0x0319,Password.oct[1]);
			_delay_ms(100);


		}
		else if (optionVar == '=')
		{
			//reset
			// rewrite xFFFF inside eeprom
		}

	}
}
