/******************************************************************************
 *
 * Module      : APP
 *
 * File Name   : app.c
 *
 * Description : Source file for the Application
 *
 * Author      : Sohaib Dar
 *
 *******************************************************************************/

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/
#include "app.h"
#include "../HAL/LED/led.h"
#include "../MCAL/TIMER/timer.h"
#include "../MCAL/EXT_INT/ext_int.h"

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

extern uint8 volatile Button_Flag;
uint8 count;

/*******************************************************************************
 *                      Functions                                              *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name] : app_start
 *
 * [Description]   : Function to start the program
 *
 * [Parameter in]       : NONE
 * [Parameter out]      : NONE
 *******************************************************************************/
void AppStart(void){
	while(1){
		normal_mode();
	}
}

/*******************************************************************************
 * [Function Name] : normal_mode
 *
 * [Description]   : Function to be called when normal routine and also has the routine
 * 					 to happen when external interrupt by INT0
 *
 * [Parameter in]       : NONE
 * [Parameter out]      : NONE
 *******************************************************************************/
void NormalMode(void){
	//normal 1
	Led_ON(PED_RED);
	Led_ON(CAR_GREEN);
	for(count = 0; count < 20; count++){
		if(Button_Flag==SINGLE_PRESSED){
			Led_OFF(CAR_GREEN);
			for(count = 0; count < 10; count++){
				Led_ON(CAR_YELLOW);
				Led_ON(PED_YELLOW);
				Timer0_Delay();
				Led_OFF(CAR_YELLOW);
				Led_OFF(PED_YELLOW);
				Timer0_Delay();
			}
			Led_OFF(CAR_YELLOW);
			Led_OFF(PED_YELLOW);

			Led_OFF(PED_RED);
			Led_ON(CAR_RED);
			Led_ON(PED_GREEN);
			for(count = 0; count < 20; count++){
				Timer0_Delay();
			}
			Led_OFF(CAR_RED);

			for(count = 0; count < 10; count++){
				Led_ON(CAR_YELLOW);
				Led_ON(PED_YELLOW);
				Timer0_Delay();
				Led_OFF(CAR_YELLOW);
				Led_OFF(PED_YELLOW);
				Timer0_Delay();
			}
			Led_OFF(CAR_YELLOW);
			Led_OFF(PED_YELLOW);
			Led_OFF(PED_GREEN);

			Button_Flag=NOT_PRESSED;

			app_start();
		}
		Timer0_Delay();
	}
	Led_OFF(CAR_GREEN);

	/*****************************************************************************/

	//normal 2
	for(count = 0; count < 10; count++){
		if(Button_Flag==SINGLE_PRESSED){
			for(count = 0; count < 10; count++){
				Led_ON(CAR_YELLOW);
				Led_ON(PED_YELLOW);
				Timer0_Delay();
				Led_OFF(CAR_YELLOW);
				Led_OFF(PED_YELLOW);
				Timer0_Delay();
			}
			Led_OFF(CAR_YELLOW);
			Led_OFF(PED_YELLOW);

			Led_OFF(PED_RED);
			Led_ON(CAR_RED);
			Led_ON(PED_GREEN);
			for(count = 0; count < 20; count++){
				Timer0_Delay();
			}
			Led_OFF(CAR_RED);

			for(count = 0; count < 10; count++){
				Led_ON(CAR_YELLOW);
				Led_ON(PED_YELLOW);
				Timer0_Delay();
				Led_OFF(CAR_YELLOW);
				Led_OFF(PED_YELLOW);
				Timer0_Delay();
			}
			Led_OFF(CAR_YELLOW);
			Led_OFF(PED_YELLOW);
			Led_OFF(PED_GREEN);

			Button_Flag=NOT_PRESSED;

			app_start();

		}

		Led_ON(CAR_YELLOW);
		Timer0_Delay();
		Led_OFF(CAR_YELLOW);
		Timer0_Delay();
	}
	Led_OFF(CAR_YELLOW);

	/*****************************************************************************/

	//normal 3
	Led_ON(CAR_RED);
	for(count = 0; count < 20; count++){
		if(Button_Flag==SINGLE_PRESSED){
			Led_ON(PED_GREEN);
			for(count = 0; count < 20; count++){
				Timer0_Delay();
			}
			Led_OFF(CAR_RED);
			Led_OFF(PED_RED);

			for(count = 0; count < 10; count++){
				Led_ON(CAR_YELLOW);
				Led_ON(PED_YELLOW);
				Timer0_Delay();
				Led_OFF(CAR_YELLOW);
				Led_OFF(PED_YELLOW);
				Timer0_Delay();
			}
			Led_OFF(CAR_YELLOW);
			Led_OFF(PED_YELLOW);
			Led_OFF(PED_GREEN);

			Button_Flag=NOT_PRESSED;

			app_start();

		}
		Timer0_Delay();
	}
	Led_OFF(CAR_RED);

	/*****************************************************************************/

	//normal 2
	for(count = 0; count < 10; count++){
		if(Button_Flag==SINGLE_PRESSED){
			for(count = 0; count < 10; count++){
				Led_ON(CAR_YELLOW);
				Led_ON(PED_YELLOW);
				Timer0_Delay();
				Led_OFF(CAR_YELLOW);
				Led_OFF(PED_YELLOW);
				Timer0_Delay();
			}
			Led_OFF(CAR_YELLOW);
			Led_OFF(PED_YELLOW);

			Led_OFF(PED_RED);
			Led_ON(CAR_RED);
			Led_ON(PED_GREEN);
			for(count = 0; count < 20; count++){
				Timer0_Delay();
			}
			Led_OFF(CAR_RED);

			for(count = 0; count < 10; count++){
				Led_ON(CAR_YELLOW);
				Led_ON(PED_YELLOW);
				Timer0_Delay();
				Led_OFF(CAR_YELLOW);
				Led_OFF(PED_YELLOW);
				Timer0_Delay();
			}
			Led_OFF(CAR_YELLOW);
			Led_OFF(PED_YELLOW);
			Led_OFF(PED_GREEN);

			Button_Flag=NOT_PRESSED;

			app_start();

		}

		Led_ON(CAR_YELLOW);
		Timer0_Delay();
		Led_OFF(CAR_YELLOW);
		Timer0_Delay();
	}
	Led_OFF(CAR_YELLOW);
}
