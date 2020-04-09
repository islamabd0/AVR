 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for the AVR ICU driver
 *
 * Author: Islam Abdo
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResult;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(void);

void ADC_readChannel(uint8 channal_num);

#endif /* ADC_H_ */
