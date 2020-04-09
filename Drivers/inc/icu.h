 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for the AVR ICU driver
 *
 * Author: Islam Abdo
 *
 *******************************************************************************/

#ifndef ICU_H_
#define ICU_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8, F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_clock;

typedef enum
{
	FALLING,RISING
}Icu_EdgeType;

typedef struct
{
	Icu_clock clock;
	Icu_EdgeType edge;
}Icu_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 *Description : Function to initial the ICU driver
 * 1. Set the required clock.
 * 2. Set the required edge detection.
 * 3. Enable the Input Capture Interrupt.
 * 4. Initialize Timer1 Registers.
 */
void ICU_init(const Icu_ConfigType * Config_Ptr);

/*
 * Description : Function to set Call Back function address
 */
void ICU_setCallBack(void(*a_ptr)(void));

/*
 * Description : Function to set the required edge type in ICES1 bit in TCCR1B Register
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType a_edgeType);

/*
 * Description : Function to get the Timer1 value when the input is Captured
 * 				 The Value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description : Function to clear Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void);

/*
 * Description : Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void);

#endif /* ICU_H_ */
