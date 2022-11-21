/******************************************************************************
 *
 * Module: Application
 *
 * File Name: app.h
 *
 * Description: Header file for the Application module
 *
 * Author: Sohaib Dar
 *
 *******************************************************************************/
#ifndef APP_H_
#define APP_H_




/*******************************************************************************
 *                             MACROS                                          *
 *******************************************************************************/
#define MaxAmount   2000


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : A function to start the application and proceed in the transaction process
 *
 */
void AppStart(void);

//-------------------------------card test--------------------------------------------//
void GetCardHolderNameTest(void);
void GetCardExpiryDateTest(void);
void GetCardPANTest(void);

//-------------------------------terminal test--------------------------------------------//
void GetTransactionDateTest(void);
void IsCardExpriedTest(void);
void GetTransactionAmountTest(void);
void IsBelowMaxAmountTest(void);
void SetMaxAmountTest(void);
void IsValidCardPANTest(void);

//-------------------------------server test--------------------------------------------//
void RecieveTransactionDataTest(void);
void IsValidAccountTest(void);
void IsBlockedAccountTest(void);
void IsAmountAvailableTest(void);
void SaveTransactionTest(void);

#endif /* APP_H_ */
