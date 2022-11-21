/******************************************************************************
 *
 * Module: Terminal
 *
 * File Name: terminal.h
 *
 * Description: Header file for the Terminal module
 *
 * Author: Sohaib Dar
 *
 *******************************************************************************/

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "../Card/card.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : A function to ask for transaction date(the date of the day)
 *
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

/*
 * Description : A function to check if the card is expired or not
 *
 */
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);

/*
 * Description : A function to ask for the client transaction amount
 *
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);

/*
 * Description : A function to check if the transaction amount is below the maximum amount or not
 *
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);

/*
 * Description : A function to set the maximum amount
 *
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);

/*
 * Description : A function to check if card PAN is valid or not
 *
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional

/*
 * Description : A function to calculate array summation
 *
 */
uint8_t arraySum(uint8_t *arr,uint8_t size);


#endif /* TERMINAL_H_ */
