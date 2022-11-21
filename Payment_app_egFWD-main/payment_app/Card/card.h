/******************************************************************************
 *
 * Module: Card
 *
 * File Name: card.h
 *
 * Description: Header file for the Card module
 *
 * Author: Sohaib Dar
 *
 *******************************************************************************/

#ifndef CARD_H_
#define CARD_H_

/***************************************************************************
 *                    Includes                                          *
 ***************************************************************************/
#include "../std_types.h"

/***************************************************************************
 *                    Definitions                                          *
 ***************************************************************************/
#define LESS         55
#define MORE         65
#define VALID        1

#define TESTING_MODE 0

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[50];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;


typedef enum EN_cardError_t
{
	CARD_OK,
	WRONG_NAME,
	WRONG_EXP_DATE,
	WRONG_PAN
}EN_cardError_t;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : A function to ask for the client card name
 *
 */
EN_cardError_t GetCardHolderName(ST_cardData_t *cardData);

/*
 * Description : A function to ask for the client card expiry date
 *
 */
EN_cardError_t GetCardExpiryDate(ST_cardData_t *cardData);

/*
 * Description : A function to ask for the client card PAN number
 *
 */
EN_cardError_t GetCardPAN(ST_cardData_t *cardData);

/*
 * Description : A function to check if the input length is right, Max or Min
 *
 */
uint8_t Max_OR_Min(uint8_t len,uint8_t Max, uint8_t Min);



#endif /* CARD_H_ */
