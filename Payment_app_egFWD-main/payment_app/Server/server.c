/******************************************************************************
 *
 * Module: Server
 *
 * File Name: server.c
 *
 * Description: Source file for the Server module
 *
 * Author: Sohaib Dar
 *
 *******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "server.h"

/***************************************************************************
 *                             MACROS                                      *
 ***************************************************************************/
#define PAN_NUMBER_WITH_NO_SPACES 16
#define SUCCESS					  0
#define FAILURE					  1

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8_t seq_no=1,account_no=0;

ST_accountsDB_t accountsDB[255]     ={
		{2000.0   , RUNNING, "8989374615436851"},
		{100000.0 , BLOCKED, "5807007076043875"},
		{15000.0  , RUNNING, "6203493828861897"},
		{200000.0 , BLOCKED, "6522847435138615"},
		{30000.0  , RUNNING, "8841727611108162"},
		{12345.0  , BLOCKED, "3001216964370998"},
		{705500.0 , RUNNING, "6369037155701133"},
		{1000.0   , BLOCKED, "6763503604627296"},
		{800.0    , RUNNING, "6224877468146186"},
		{14500.0  , RUNNING, "6362010928510773"}};

ST_transaction_t transactions[255] = {0};  //an array to save transaction history details

uint8_t st=0;                  //to save transaction state
uint8_t savedTrans_no=0;	   //saved transaction number

/*******************************************************************************
 *                      Functions                                              *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name] : recieveTransactionData
 *
 * [Description]   : A function that helps the server to get all transaction data
 * 					 and check if they valid and approved or not and save that state
 * 					 in the transaction array(DB)
 *
 * [Args in]       : ST_transaction_t *transData
 * [Args out]      : APPROVED OR DECLINED_INSUFFECIENT_FUND OR DECLINED_STOLEN_CARD OR FRAUD_CARD OR INTERNAL_SERVER_ERROR
 *******************************************************************************/
EN_transState_t recieveTransactionData(ST_transaction_t *transData){

	transData->transState=APPROVED;
	st=transData->transState;
	if(isValidAccount(&transData->cardHolderData,&accountsDB)!=SERVER_OK){
		printf("Request Declined: This PAN doesn't exist!!\n");
		transData->transState=FRAUD_CARD;
		st=transData->transState;
		transactions[savedTrans_no].transState = transData->transState;
		return FRAUD_CARD;
	}
	//------------------------------------------------------------------------

	else if(isBlockedAccount(accountsDB)!=SERVER_OK){
		printf("Stolen Card!!!!\n");
		transData->transState=DECLINED_STOLEN_CARD;
		st=transData->transState;
		transactions[savedTrans_no].transState = transData->transState;
		return DECLINED_STOLEN_CARD;
	}
	//------------------------------------------------------------------------
	else if(isAmountAvailable((&transData->terminalData),&accountsDB)!=SERVER_OK){
		printf("Sorry, You don't have that cash!!\n");
		transData->transState=DECLINED_INSUFFECIENT_FUND;
		st=transData->transState;
		transactions[savedTrans_no].transState = transData->transState;
		return DECLINED_INSUFFECIENT_FUND;
	}
	//------------------------------------------------------------------------
	else if(saveTransaction(&(transData))!=SERVER_OK){
		printf("Error while saving transaction!!\n");
		transData->transState=INTERNAL_SERVER_ERROR;
		st=transData->transState;
		transactions[savedTrans_no].transState = transData->transState;
		return INTERNAL_SERVER_ERROR;
	}

	printf("###Transaction have been saved successfully###\n");
#if (TESTING_MODE ==0)
	printf("\n");
	printf("\n");
    printf("/////////////////////////////////////////////////\n");
    printf("Balance Before Transaction   = %.3f\n" , accountsDB[account_no].balance);
    printf("withdraw amount              = %.3f\n", transData->terminalData.transAmount);
	accountsDB[account_no].balance -= transData->terminalData.transAmount;
    printf("Balance After Transaction    = %.3f\n", accountsDB[account_no].balance);
    printf("/////////////////////////////////////////////////");
	printf("\n");
	printf("\n");
#endif
	return APPROVED;
}

/*******************************************************************************
 * [Function Name] : isValidAccount
 *
 * [Description]   : A function to check if the card PAN is in the server Database or not
 *
 * [Args in]       : ST_cardData_t *cardData , ST_accountsDB_t *accountRefrence
 * [Args out]      : ACCOUNT_NOT_FOUND OR SERVER_OK
 *******************************************************************************/
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
	uint8_t i,j;
	uint8_t sumArray[25];
#if (TESTING_MODE == 1)
	accountRefrence = &accountsDB;
#endif
	/*to erase any spaces in the PAN*/
	i=0,j=0;
	while(cardData->primaryAccountNumber[i]!='\n'){
		if(cardData->primaryAccountNumber[i]!=' '){
			sumArray[j]=cardData->primaryAccountNumber[i];
			i++;
			j++;
		}
		else{
			i++;
		}

	}

	uint8_t equal;
	account_no=0;
	for(i=0;i<10;i++){
		equal = my_strcmp(sumArray,(&accountRefrence[account_no])->primaryAccountNumber);
		if(equal==SUCCESS){
			i=0;
			//saving card name in transaction DB
			while(cardData->cardHolderName[i]!='\n'){
				transactions[savedTrans_no].cardHolderData.cardHolderName[i]  = cardData->cardHolderName[i];
				i++;
			}
			i=0;
			//saving card PAN in transaction DB
			while(accountsDB[account_no].primaryAccountNumber[i]!='\0'){
				transactions[savedTrans_no].cardHolderData.primaryAccountNumber[i]  = accountsDB[account_no].primaryAccountNumber[i];
				i++;
			}
			i=0;
			//saving card expiration date in transaction DB
			while(cardData->cardExpirationDate[i]!='\0'){
				transactions[savedTrans_no].cardHolderData.cardExpirationDate[i]  = cardData->cardExpirationDate[i];
				i++;
			}
			return SERVER_OK;
		}
		account_no++;
	}
	return ACCOUNT_NOT_FOUND;
}

/*******************************************************************************
 * [Function Name] : my_strcmp
 *
 * [Description]   : A function to compare 2 strings 16 in length
 *
 * [Parameter in]       : uint8_t *str1 , uint8_t *str2
 * [Parameter out]      : FAILURE OR SUCCESS
 *******************************************************************************/
uint8_t my_strcmp(uint8_t *str1,uint8_t *str2){
	uint8_t i;
	for(i=0;i<PAN_NUMBER_WITH_NO_SPACES;i++){
		if(str1[i]==str2[i]){
			continue;
		}
		else{
			return FAILURE;
		}
	}
	return SUCCESS;
}

/*******************************************************************************
 * [Function Name] : isBlockedAccount
 *
 * [Description]   : A function to check if the account is blocked or not
 *
 * [Parameter in]       : ST_accountsDB_t *accountRefrence
 * [Parameter out]      : BLOCKED_ACCOUNT OR SERVER_OK
 *******************************************************************************/
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
#if (TESTING_MODE == 1)
	accountRefrence = &accountsDB;
#endif
	if((&accountRefrence[account_no])->state!=RUNNING){
		return BLOCKED_ACCOUNT;
	}
	return SERVER_OK;
}

/*******************************************************************************
 * [Function Name] : isAmountAvailable
 *
 * [Description]   : A function to check if the transaction amount is available in
 * 				     the client account or not
 *
 * [Args in]       : ST_terminalData_t *termData , ST_accountsDB_t *accountRefrence
 * [Args out]      : LOW_BALANCE OR SERVER_OK
 *******************************************************************************/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){

#if (TESTING_MODE == 1)
	accountRefrence = &accountsDB;
#endif
	if(termData->transAmount > (&accountRefrence[account_no])->balance){
		return LOW_BALANCE;
	}
	//saving transaction amount in transaction DB
	transactions[savedTrans_no].terminalData.transAmount  = termData->transAmount;

	//saving transaction maximum amount in transaction DB
	transactions[savedTrans_no].terminalData.maxTransAmount  = termData->maxTransAmount;

	uint8_t i=0;
	//saving transaction date in transaction DB
	while(termData->transactionDate[i]!='\0'){
		transactions[savedTrans_no].terminalData.transactionDate[i]  = termData->transactionDate[i];
		i++;
	}
	return SERVER_OK;
}

/*******************************************************************************
 * [Function Name] : saveTransaction
 *
 * [Description]   : A function to check that everything is right to give a permission
 * 				     of saving transaction or not
 *
 * [Parameter in]       : ST_transaction_t *transData
 * [Parameter out]      : SAVING_FAILED OR SERVER_OK
 *******************************************************************************/
EN_serverError_t saveTransaction(ST_transaction_t *transData){

	transData->transactionSequenceNumber = seq_no;
	transData->transState=st;
	seq_no++;

	if (
			transData->transState == DECLINED_INSUFFECIENT_FUND ||
			transData->transState == DECLINED_STOLEN_CARD       ||
			transData->transState == FRAUD_CARD
	)
	{
		return SAVING_FAILED;
	}
	transactions[savedTrans_no].transactionSequenceNumber = transData->transactionSequenceNumber;
	return SERVER_OK;
}

/*******************************************************************************
 * [Function Name] : listSavedTransactions
 *
 * [Description]   : A function to list all previous transactions details
 *
 * [Parameter in]       : NONE
 * [Parameter out]      : NONE
 *******************************************************************************/
void listSavedTransactions(void){
	uint8_t i;
	if(seq_no==1){
		printf("There are no saved transactions!!!\n");
		printf("\n");
		printf("\n");
		return;
	}
	for(i=0;i<savedTrans_no;i++){
		printf("------------------------------------------------------------\n");
		printf("Transaction Sequence Number   : %d \n",transactions[i].transactionSequenceNumber);
		printf("Transaction Date              : ");
		puts(transactions[i].terminalData.transactionDate);
		printf("Transaction Amount            : %.3f\n",transactions[i].terminalData.transAmount);

		switch(st){
		case 0:
			printf("Transaction State             : Approved\n");
			break;
		case 1:
			printf("Transaction State             : DECLINED_INSUFFECIENT_FUND\n");
			break;
		case 2:
			printf("Transaction State             : DECLINED_STOLEN_CARD\n");
			break;
		case 3:
			printf("Transaction State             : FRAUD_CARD\n");
			break;
		case 4:
			printf("Transaction State             : INTERNAL_SERVER_ERROR\n");
			break;
		}
		printf("Terminal Max Amount           : %.3f\n",transactions[i].terminalData.maxTransAmount);
		printf("Card-holder Name              : ");
		puts(transactions[i].cardHolderData.cardHolderName);
		printf("PAN                           : ");
		puts(transactions[i].cardHolderData.primaryAccountNumber);

		printf("Card Expiration Date          : ");
		puts(transactions[i].cardHolderData.cardExpirationDate);
		printf("------------------------------------------------------------\n");
		printf("\n");
		printf("\n");
	}
}
