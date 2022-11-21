/******************************************************************************
 *
 * Module      : EXT_INT0
 *
 * File Name   : ext_int.h
 *
 * Description : Source file for the INT0 AVR Interrupt
 *
 * Author      : Sohaib Dar
 *
 *******************************************************************************/



/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ext_int.h"
#include "../../std_types.h"

#if TEST_MODE==1
#include "../../HAL/LED/led.h"
#include "../../MCAL/TIMER/timer.h"
#endif

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

uint8 volatile Button_Flag=NOT_PRESSED;

/*******************************************************************************
 *                      Functions                                              *
 *******************************************************************************/

/************************************************************************************
 * Service Name    : INT0_Init + Its ISR
 * Parameters (in) : None
 * Parameters (out): None
 * Return value    : None
 * Description     : A function to initialize INT0 external interrupt by:
 * 				    - Configure INT0/PD2 as input pin
 * 				    - Enable external interrupt pin INT0
 * 				    - Trigger INT0 with the falling edge
 *                   so it only waits until the interrupt flag is raised when
 *                   the button is pressed then generate the interrupt and call the
 *                   ISR of that interrupt
 ************************************************************************************/
void INT0_Init(void){
	DDRD  &= (~(1<<PD2));                // Configure INT0/PD2 as input pin
	PORTD |= (1<<PD2);					 //enabling Pull-up for the pin
	GICR  |= (1<<INT0);                  // Enable external interrupt pin INT0
	MCUCR |= (1<<ISC01);  				 // Trigger INT0 with the falling edge
	GIFR   = (1<<INTF0);				 // Disabling INT0 flag manually to avoid any errors
}

/************************************************************************************
                       ISR when external interrupt occurs
/************************************************************************************/

ISR(INT0_vect){
#if TEST_MODE!=1
	if(Button_Flag==NOT_PRESSED){        //to avoid long and double presses
		Button_Flag=SINGLE_PRESSED;
	}
#endif

#if TEST_MODE==1
	uint8 count;
	if(Button_Flag==NOT_PRESSED){        //to avoid long and double presses
		while(1){
			Led_ON(CAR_YELLOW);
			Led_ON(PED_YELLOW);
			for(count = 0; count < 4; count++){
				Timer0_Delay();
			}
			Led_OFF(CAR_YELLOW);
			Led_OFF(PED_YELLOW);
			for(count = 0; count < 4; count++){
				Timer0_Delay();
			}
		}
	}
#endif
}
