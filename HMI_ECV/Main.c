#include "keypad.h"
#include "lcd.h"
#include "TIMER.h"
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

union fullPass
{
	uint16 fullPass;
	unsigned char oct[2];

};
union fullPass firstPass;
union fullPass secPass;
uint8 option;

void PasswordFun(union fullPass *passvar,char * string)
{
	uint8 password =0;
	uint8 counter = 0;
	uint16 passComb = 1000;
	(*passvar).fullPass = 0;
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString(string);

	while(counter < 4 )
	{
		password =KEYPAD_getPressedKey();
		LCD_moveCursor(1,counter);
		counter++;
		_delay_ms(1500);
		(*passvar).fullPass =(*passvar).fullPass +  (password* passComb);
		LCD_displayCharacter('*');
		passComb = passComb/10;
	}
	LCD_clearScreen();
	LCD_intgerToString((*passvar).fullPass);
	_delay_ms(100);
}
void first_pass()
{
	PasswordFun(&firstPass, "Enter Password");
}
void access()
{
	first_pass();
	UART_sendByte(firstPass.oct[0]);
	_delay_ms(100);
	UART_sendByte(firstPass.oct[1]);
	_delay_ms(100);
}
void PassConfirm()
{
	PasswordFun(&secPass,"ReEnter Password");
}
void mainOption(uint8 * var)
{
	do {
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayString("+ for open Door");
		LCD_moveCursor(1,0);
		LCD_displayString("- for change password");
		*var = KEYPAD_getPressedKey();
		_delay_ms(1500);
	}while(!(*var == '+' || *var == '-' ));
}
void MSG(const char * string)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString(string);
	_delay_ms(3000);
}
void error_msg()
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("e2fesh 7aramy! ");
}
void createPass()
{
	do{
		first_pass();
		PassConfirm();
	}while(firstPass.fullPass != secPass.fullPass);

	UART_sendByte(firstPass.oct[0]);
	UART_sendByte(firstPass.oct[1]);
	_delay_ms(1000);
}
UART_ConfigType uartConfig = {9600 , 1 , 0 , BIT_8 , 0};

int main()
{
	uint8 optionVar;
	uint8 val ;
	UART_init(&uartConfig);
	_delay_ms(500);
	LCD_init();
	_delay_ms(500);
	MSG("Hello, there!");
	while(1)
	{
		val = UART_recieveByte();
		if(val == 0)
		{
			createPass();
			UART_sendByte(secPass.oct[0]);
			_delay_ms(100);
			UART_sendByte(secPass.oct[1]);
			_delay_ms(100);
			MSG("Password is saved.");
		}
		else if (val == 1)
		{
			//option
			mainOption(&option);
			UART_sendByte(option);

			if(option == '+')
			{
				//open door
				access();
				optionVar = UART_recieveByte();
				_delay_ms(1500);
				//do while 3 marat 34an net2ked optionVar == 2
				do{
					if(optionVar == 2)
					{
						LCD_clearScreen();
						LCD_moveCursor(0,0);
						LCD_displayString("Correct Password!");
						LCD_moveCursor(1,0);
						LCD_displayString("Door is opening.");
						_delay_ms(15000);
						LCD_displayString("Door is closing.");
						_delay_ms(15000);
						break;
					}
					else if(optionVar == 3)
					{
						//wrong
						MSG("InCorrect Password!");
						break;


						//LCD_clearScreen();
					}
					else if(optionVar == 4)
					{
						//alarm
						MSG("e2fesh 7aramy");
						_delay_ms(1000000);
						break;
					}
					else
					{
						break;
					}

				}while(optionVar != 2);

			}
			if(option == '-')
			{
				access();
				optionVar = UART_recieveByte();
				_delay_ms(1500);
				if(optionVar == 5)
				{
					createPass();
					UART_sendByte(secPass.oct[0]);
					_delay_ms(100);
					UART_sendByte(secPass.oct[1]);
					_delay_ms(100);
					MSG("Password is saved.");
				}
			}
		}
		_delay_ms(200);
	}
}
