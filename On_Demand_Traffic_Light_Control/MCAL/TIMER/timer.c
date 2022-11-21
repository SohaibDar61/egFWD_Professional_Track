/******************************************************************************
 *
 * Module      : TIMER
 *
 * File Name   : timer.c
 *
 * Description : Source file for the TIMER0 AVR peripheral
 *
 * Author      : Sohaib Dar
 *
 *******************************************************************************/


/*******************************************************************************
 *                       INCLUDES                                              *
 *******************************************************************************/
#include <avr/io.h>
#include "timer.h"


/*******************************************************************************
 *                      Functions Definition                                              *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name] : Timer0_Delay
 *
 * [Description]   : Function responsible for Initialize the Timer0 and make a delay
 * 					 using polling technique
 *
 * [Parameter in]       : NONE
 * [Parameter out]      : NONE
 *******************************************************************************/

void Timer0_Delay(void)
{
	TCNT0 = 6; // Set Timer0 initial value to 6

	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);

	while(!(TIFR & (1<<TOV0))); // Wait until the Timer0 Overflow occurs (wait until TOV0 = 1)

	TIFR |= (1<<TOV0); // Clear TOV0 bit by set its value

	TCCR0 = 0; // Stop Timer0 by clear the Clock bits (CS00, CS01 and CS02)
}
