/******************************************************************************
 *
 * File Name   : main.c
 *
 * Description : Source file for the main function
 *
 * Author      : Sohaib Dar
 *
 *******************************************************************************/

/******************************************************************************
*                              INCLUDES                                       *
*******************************************************************************/
#include "APP/app.h"
#include "avr/io.h"
#include "MCAL/EXT_INT/ext_int.h"
#include "HAL/LED/led.h"

/******************************************************************************
*                             GLOBAL AREA                                      *
*******************************************************************************/
#if TEST_MODE==1
#include <avr/interrupt.h>
#endif



int main(void){

	INT0_Init();				/*to initialize external interrupt*/
	Led_Init();					/*to initialize Leds*/
	SREG|=(1<<7);               /*Enabling Global interrupt*/


#if TEST_MODE!=1
	app_start();				/*start of the application*/
#endif

#if TEST_MODE==1
	while(1);
#endif
}
