 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.h
 *
 * Description: Header file for the AVR spi driver
 *
 * Author: Islam Abdo
 *
 *******************************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_sendByte(const uint8 data);
uint8 SPI_recieveByte(void);
void SPI_sendString(const uint8 *str);
void SPI_recieveString(uint8 *str);


#endif /* SPI_H_ */
