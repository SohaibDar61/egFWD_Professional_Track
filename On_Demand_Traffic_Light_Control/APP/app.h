/******************************************************************************
 *
 * Module      : APP
 *
 * File Name   : app.h
 *
 * Description : Header file for the Application
 *
 * Author      : Sohaib Dar
 *
 *******************************************************************************/


#ifndef APP_APP_H_
#define APP_APP_H_

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to start the program
 */
void AppStart(void);

/*
 * Description : Function to be called when normal routine and also has the routine
 * 			     to happen when external interrupt by INT0
 */
void NormalMode(void);

#endif /* APP_APP_H_ */
