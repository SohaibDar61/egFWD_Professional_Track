/******************************************************************************
 *
 * Module: Server
 *
 * File Name: server.h
 *
 * Description: Header file for the Server module
 *
 * Author: Sohaib Dar
 *
 *******************************************************************************/

#ifndef SERVER_H_
#define SERVER_H_


/*******************************************************************************
 *                               INCLUDES                                      *
 *******************************************************************************/
#include "../Terminal/terminal.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

typedef enum EN_accountState_t
{
	RUNNING,
	BLOCKED
}EN_accountState_t;

typedef struct ST_savedTransactions_t{
	EN_accountState_t state;


}ST_savedTransactions_t;


typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : A function that helps the server to get all transaction data
 *
 */
EN_transState_t recieveTransactionData(ST_transaction_t *transData);

/*
 * Description : A function to check if the card PAN is in the server Database or not
 *
 */
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);

/*
 * Description : A function to check if the account is blocked or not
 *
 */
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);

/*
 * Description : A function to check if the transaction amount is available in
 * 				 the client account or not
 *
 */
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);

/*
 * Description : A function to check that everything is right to give a permission
 * 				 of saving transaction or not
 *
 */
EN_serverError_t saveTransaction(ST_transaction_t *transData);

/*
 * Description : A function to list all previous transactions details
 *
 */
void listSavedTransactions(void);

/*
 * Description : A function to compare 2 strings 16 in length
 *
 */
uint8_t my_strcmp(uint8_t *str1,uint8_t *str2);


#endif /* SERVER_H_ */
