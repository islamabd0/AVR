 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the AVR ICU driver
 *
 * Author: Islam Abdo
 *
 *******************************************************************************/

#include "uart.h"

#define BAUD_PRESCALE ((F_CPU / (USART_BAUDRATE * 8UL)) - 1)
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void UART_init(void)
{
	/* Enable U2X bit for Double Transmission Speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART TX Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN = 1 Receiver Enable
	 * TXEN = 1	Transmitter Enable
	 * UCSZ2 =0 For 8-bit data Mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1<<TXEN) | (1<<RXEN);

	/************************** UCSRB Description **************************
	 * URSEL = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL = 0 Asynchronous Operation
	 * UPM1:0 = 00 Disable parity bit
	 * USBS = 0 One Stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH */
	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;
}

void UART_sendByte(const uint8 data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	UDR = data;
	/************************* Another Method *************************
		UDR = data;
		while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transimission is complete TXC = 1
		SET_BIT(UCSRA,TXC); // Clear the TXC flag
	 *******************************************************************/
}

uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
	return UDR;
}

void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
*******************************************************************/
}

void UART_recieveString(uint8 *Str)
{
	uint8 i = 0;
	Str[i] = UART_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';
}
