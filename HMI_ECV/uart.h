#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */

typedef enum
{
	Buad_rate_1200 = 1200 ,Buad_rate_2400 = 2400 ,Buad_rate_4800 = 4800 ,Buad_rate_9600 = 96000,
	Buad_rate_19200 = 19200 ,Buad_rate_115200 = 115200
}Baud_rate;

typedef enum
{
	Async_normal_mode,Async_Double_Speed_mode
}sync_mode;

typedef enum
{
	No_parity,Reserved,ODD_parity, EVEN_parity
}Parity_Mode;

typedef enum
{
	BIT_5,BIT_6,BIT_7,BIT_8,
	BIT_9 = 7
}Data_Size;

typedef enum
{
	Disable, Enable
}stop_bit_select;





typedef struct
{
	Baud_rate buadRate;
	sync_mode syncMode;
	Parity_Mode parityMode;
	Data_Size bitSize;
	stop_bit_select stopBit;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * uartConfig);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
