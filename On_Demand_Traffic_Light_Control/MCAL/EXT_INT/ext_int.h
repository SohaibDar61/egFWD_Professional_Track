
/******************************************************************************
 *
 * Module      : EXT_INT0
 *
 * File Name   : ext_int.h
 *
 * Description : Header file for the INT0 AVR Interrupt
 *
 * Author      : Sohaib Dar
 *
 *******************************************************************************/

#ifndef MCAL_EXT_INT_EXT_INT_H_
#define MCAL_EXT_INT_EXT_INT_H_

/*******************************************************************************
 *                      Definitions                                            *
 *******************************************************************************/
#define TEST_MODE       0

#define NOT_PRESSED     0
#define SINGLE_PRESSED  1


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : A function to initialize INT0 external interrupt by:
 * 				- Configure INT0/PD2 as input pin
 * 				- Enable external interrupt pin INT0
 * 				- Trigger INT0 with the falling edge
 */
void INT0_Init(void);


#endif /* MCAL_EXT_INT_EXT_INT_H_ */
