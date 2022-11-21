/******************************************************************************
 *
 * Module      : LED
 *
 * File Name   : led.c
 *
 * Description : Source file for the LED peripheral
 *
 * Author      : Sohaib Dar
 *
 *******************************************************************************/


#include "led.h"

/*******************************************************************************
 *                      Functions                                              *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name] : Led_Init
 *
 * [Description]   : Function responsible for Initializing all required pins for Leds
 * 					 as output pins
 *
 * [Parameter in]       : NONE
 * [Parameter out]      : NONE
 *******************************************************************************/
void Led_Init(void){
	GPIO_setupPinDirection(CAR_PORT ,GREEN_PIN  ,PIN_OUTPUT);
	GPIO_setupPinDirection(CAR_PORT ,YELLOW_PIN ,PIN_OUTPUT);
	GPIO_setupPinDirection(CAR_PORT ,RED_PIN    ,PIN_OUTPUT);
	GPIO_setupPinDirection(PED_PORT ,GREEN_PIN  ,PIN_OUTPUT);
	GPIO_setupPinDirection(PED_PORT ,YELLOW_PIN ,PIN_OUTPUT);
	GPIO_setupPinDirection(PED_PORT ,RED_PIN    ,PIN_OUTPUT);
}

/*******************************************************************************
 * [Function Name] : Led_ON
 *
 * [Description]   : Function responsible for Turning on any given Led
 *
 * [Parameter in]       : EN_Led_Id_t LED_ID
 * [Parameter out]      : NONE
 *******************************************************************************/
void Led_ON(EN_Led_Id_t LED_ID){
	switch(LED_ID){
	case CAR_GREEN :
		GPIO_writePin(CAR_PORT,GREEN_PIN,LOGIC_HIGH);
		break;

	case CAR_YELLOW :
		GPIO_writePin(CAR_PORT,YELLOW_PIN,LOGIC_HIGH);
		break;

	case CAR_RED :
		GPIO_writePin(CAR_PORT,RED_PIN,LOGIC_HIGH);
		break;

	case PED_GREEN :
		GPIO_writePin(PED_PORT,GREEN_PIN,LOGIC_HIGH);
		break;

	case PED_YELLOW :
		GPIO_writePin(PED_PORT,YELLOW_PIN,LOGIC_HIGH);
		break;

	case PED_RED :
		GPIO_writePin(PED_PORT,RED_PIN,LOGIC_HIGH);
		break;
	}
}

/*******************************************************************************
 * [Function Name] : Led_OFF
 *
 * [Description]   : Function responsible for Turning off any given Led
 *
 * [Parameter in]       : EN_Led_Id_t LED_ID
 * [Parameter out]      : NONE
 *******************************************************************************/
void Led_OFF(EN_Led_Id_t LED_ID){
	switch(LED_ID){
	case CAR_GREEN :
		GPIO_writePin(CAR_PORT,GREEN_PIN,LOGIC_LOW);
		break;

	case CAR_YELLOW :
		GPIO_writePin(CAR_PORT,YELLOW_PIN,LOGIC_LOW);
		break;

	case CAR_RED :
		GPIO_writePin(CAR_PORT,RED_PIN,LOGIC_LOW);
		break;

	case PED_GREEN :
		GPIO_writePin(PED_PORT,GREEN_PIN,LOGIC_LOW);
		break;

	case PED_YELLOW :
		GPIO_writePin(PED_PORT,YELLOW_PIN,LOGIC_LOW);
		break;

	case PED_RED :
		GPIO_writePin(PED_PORT,RED_PIN,LOGIC_LOW);
		break;
	}
}
