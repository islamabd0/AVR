 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the AVR ICU driver
 *
 * Author: Islam Abdo
 *
 *******************************************************************************/


#ifndef UART_H_
#define UART_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void UART_init(void);
void UART_sendByte(const uint8 data);
uint8 UART_recieveByte(void);
void UART_sendString(const uint8 *str);
void UART_recieveString(uint8 *str);
void UART_recieveString(uint8 *Str);

#endif /* UART_H_ */
