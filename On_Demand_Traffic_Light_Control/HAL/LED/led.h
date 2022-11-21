/******************************************************************************
 *
 * Module      : LED
 *
 * File Name   : led.h
 *
 * Description : Header file for the LED peripheral
 *
 * Author      : Sohaib Dar
 *
 *******************************************************************************/

/*******************************************************************************
 *                           INCLUDES                                          *
 *******************************************************************************/
#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_
#include "../../MCAL/GPIO/gpio.h"


/*******************************************************************************
 *                           MACROS                                            *
 *******************************************************************************/
#define CAR_PORT     PORTA_ID
#define PED_PORT     PORTB_ID
#define GREEN_PIN    PIN0_ID
#define YELLOW_PIN   PIN1_ID
#define RED_PIN      PIN2_ID


/*******************************************************************************
 *                      Types Definition                                       *
 *******************************************************************************/

typedef enum
{
	CAR_GREEN, CAR_YELLOW, CAR_RED, PED_GREEN, PED_YELLOW, PED_RED
}EN_Led_Id_t;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function responsible for Initializing all required pins for Leds
 * 				 as output pins
 */
void Led_Init(void);

/*
 * Description : Function responsible for Turning on any given Led
 */
void Led_ON(EN_Led_Id_t LED_ID);

/*
 * Description : Function responsible for Turning off any given Led
 */
void Led_OFF(EN_Led_Id_t LED_ID);

#endif /* HAL_LED_LED_H_ */
