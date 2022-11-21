/******************************************************************************
 *
 * Module      : TIMER
 *
 * File Name   : timer.h
 *
 * Description : Header file for the TIMER0 AVR peripheral
 *
 * Author      : Sohaib Dar
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function responsible for Initialize the Timer by:
 * 				 - Choose timer number
 * 				 - Choose timer mode
 * 				 - Enabling Clock
 */
void Timer0_Delay(void);


#endif /* TIMER_H_ */
