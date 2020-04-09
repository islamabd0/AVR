/******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.C
 *
 * Description: Source file for the AVR SPI driver
 *
 * Author: Islam Abdo
 *
 *******************************************************************************/

#include "spi.h"

void SPI_initMaster(void)
{
	/******** Configure SPI Master Pins *********
	 * SS(PB4) -> OUTPUT
	 * MOSI(PB5) -> OUTPUT
	 * MISO(PB6) -> INPUT
	 * SCK(PB7) -> OUTPUT
	 ********************************************/
	DDRB |= (1<<PB4) | (1<<PB5) | (1<<PB7);
	DDRB &= ~(1<<PB6);
	/* enable SPI + enable Master + choose SPI clock = Fosc/4 */
	SPCR |= (1<<SPE) | (1<<MSTR);
}

void SPI_initSlave(void)
{
	/******** Configure SPI Slave Pins *********
	 * SS(PB4) -> INPUT
	 * MOSI(PB5) -> INPUT
	 * MISO(PB6) -> OUTPUT
	 * SCK(PB7) -> INPUT
	 ********************************************/
	DDRB &= ~(1<<PB4) | (1<<PB5) | (1<<PB7);
	DDRB |= (1<<PB6);
	/* enable SPI + choose SPI clock = Fosc/4 */
	SPCR |= (1<<SPE);
}

void SPI_sendByte(const uint8 data)
{
	SPDR = data; //send data by SPI
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is sent correctly)
}

uint8 SPI_recieveByte(void)
{
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is receive correctly)
	return SPDR;
}

void SPI_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		SPI_sendByte(Str[i]);
		i++;
	}
}

void SPI_recieveString(uint8 *Str)
{
	uint8 i = 0;
	Str[i] = SPI_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = SPI_recieveByte();
	}
	Str[i] = '\0';
}
