/******************************************************************************
 *
 * Module: Terminal
 *
 * File Name: terminal.c
 *
 * Description: Source file for the Terminal module
 *
 * Author: Sohaib Dar
 *
 *******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "terminal.h"
#include "../Card/card.h"

/***************************************************************************
 *                         MACROS                                          *
 ***************************************************************************/
#define TRANSACTION_DATE_MAX_LENGTH   				   10
#define TRANSACTION_DATE_MIN_LENGTH   				   10
#define PAN_NUMBER_LENGTH_WITHOUT_THE_CHECKSUM_DIGIT   15
#define PAN_NUMBER_WITH_NO_SPACES 					   16

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8_t length;

/*******************************************************************************
 *                      Functions                                              *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name] : getTransactionDate
 *
 * [Description]   : A function to ask for transaction date(the date of the day)
 *            and check its length and you only have 2 trials
 *
 * [Parameter in]       : ST_terminalData_t *termData
 * [Parameter out]      : WRONG_DATE OR TERMINAL_OK
 *******************************************************************************/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
  if(termData == NULL){
    return WRONG_DATE;
  }
  uint8_t check,trial=0;
#if (TESTING_MODE==0)
  printf("Please Enter The Transaction Date(DD/MM/YYYY, e.g 25/06/2022) : ");
#endif
  do{
#if (TESTING_MODE==0)
    scanf("%s",&termData->transactionDate);
    getchar();
#endif
    printf("\n");
	  length = strlen(termData->transactionDate);
    check = Max_OR_Min(length,TRANSACTION_DATE_MAX_LENGTH,TRANSACTION_DATE_MIN_LENGTH);

    if(trial<2){
    switch(check){
    case LESS:
      trial++;
      printf("The Date length is less than the minimum(10 chars), Please try gain: ");
      break;
    case MORE:
      trial++;
      printf("The Date length is more than the maximum(10 chars), Please try gain: ");
      break;
    }
    }trial++;
  }
  while(check!=1 && trial<3);

  if(check == 1 &&
    ( (termData->transactionDate[0] >='0' && termData->transactionDate[0] <='9')   &&
      (termData->transactionDate[1] >='0' && termData->transactionDate[1] <='9')   &&
      (termData->transactionDate[2] == '/'                                 )     &&
      (termData->transactionDate[3] >='0' && termData->transactionDate[3] <='9')   &&
      (termData->transactionDate[4] >='0' && termData->transactionDate[4] <='9')   &&
      (termData->transactionDate[5] == '/'                                 )      &&
      (termData->transactionDate[6] >='0' && termData->transactionDate[6] <='9')   &&
      (termData->transactionDate[7] >='0' && termData->transactionDate[7] <='9')   &&
      (termData->transactionDate[8] >='0' && termData->transactionDate[8] <='9')   &&
      (termData->transactionDate[9] >='0' && termData->transactionDate[9] <='9') )

  ){
    return TERMINAL_OK;
  }
  else{
    printf("WRONG_DATE Format\n");
    return WRONG_DATE;
  }
}

/*******************************************************************************
 * [Function Name] : isCardExpired
 *
 * [Description]   : A function to check if the card is expired or not and print
 *            card and transaction date on screen
 *
 * [Parameter in]       : ST_cardData_t *cardData , ST_terminalData_t *termData
 * [Parameter out]      : EXPIRED_CARD OR TERMINAL_OK
 *******************************************************************************/
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
  if(cardData == NULL || termData==NULL){
    return EXPIRED_CARD;
  }
  uint8_t trans_year_val;
  uint8_t card_year_val;

  uint8_t trans_month_val;
  uint8_t card_month_val;

  uint8_t trans_day_val;

  uint8_t trans_year[3];
/*
0|1|2|3|4|5|6|7|8|9 :indices
1|2|/|1|1|/|2|0|2|2 :Transaction date
0|6|2|5				:Card expiration date
*/
  trans_year[0]=termData->transactionDate[8];
  trans_year[1]=termData->transactionDate[9];

  uint8_t card_year[3];
  card_year[0]=cardData->cardExpirationDate[3];
  card_year[1]=cardData->cardExpirationDate[4];

  uint8_t trans_month[3];
  trans_month[0]=termData->transactionDate[3];
  trans_month[1]=termData->transactionDate[4];

  uint8_t card_month[3];
  card_month[0]=cardData->cardExpirationDate[0];
  card_month[1]=cardData->cardExpirationDate[1];

  uint8_t trans_day[3];
  trans_day[0]=termData->transactionDate[0];
  trans_day[1]=termData->transactionDate[1];


  trans_year_val  = atoi(trans_year );
  card_year_val   = atoi(card_year  );
  trans_month_val = atoi(trans_month);
  card_month_val  = atoi(card_month );
  trans_day_val   = atoi(trans_day  );


  printf("Card Exp. Date   :    %d/%d\n",card_month_val,card_year_val);
  printf("Transaction Date : %d/%d/%d\n",trans_day_val,trans_month_val,trans_year_val);


  if(card_year_val>trans_year_val || ((card_year_val-trans_year_val)==0 && (card_month_val-trans_month_val)>0)){
    return TERMINAL_OK;
  }
  else{
    return EXPIRED_CARD;
  }
}

/*******************************************************************************
 * [Function Name] : getTransactionAmount
 *
 * [Description]   : A function to ask for the client transaction amount which
 *            must be more than 0
 *
 * [Parameter in]       : ST_terminalData_t *termData
 * [Parameter out]      : INVALID_AMOUNT OR TERMINAL_OK
 *******************************************************************************/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
#if (TESTING_MODE==0)
  printf("Please Enter The Transaction amount (not less than 1): ");
  scanf("%f",&termData->transAmount);
#endif

  if(termData->transAmount<=0){
    return INVALID_AMOUNT;
  }
  return TERMINAL_OK;
}

/*******************************************************************************
 * [Function Name] : isBelowMaxAmount
 *
 * [Description]   : A function to check if the transaction amount is below the
 *                   maximum amount or not
 *
 * [Parameter in]       : ST_terminalData_t *termData
 * [Parameter out]      : EXCEED_MAX_AMOUNT OR TERMINAL_OK
 *******************************************************************************/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
  if(termData->transAmount > termData->maxTransAmount){
    return EXCEED_MAX_AMOUNT;
  }
  return TERMINAL_OK;
}

/*******************************************************************************
 * [Function Name] : setMaxAmount
 *
 * [Description]   : A function to set the maximum amount
 *
 * [Parameter in]       : ST_terminalData_t *termData , float maxAmount
 * [Parameter out]      : INVALID_MAX_AMOUNT OR TERMINAL_OK
 *******************************************************************************/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){

  if(maxAmount<=0){
    return INVALID_MAX_AMOUNT;
  }
  termData->maxTransAmount = maxAmount;
  return TERMINAL_OK;
}

/*******************************************************************************
 * [Function Name] : isValidCardPAN
 *
 * [Description]   : A function to check if card PAN is valid or not by checking
 *            if the checksum number is right or not and assure that card
 *            PAN is 16 digit or not
 *
 * [Parameter in]       : ST_cardData_t *cardData
 * [Parameter out]      : INVALID_CARD OR TERMINAL_OK
 *******************************************************************************/
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){

  uint8_t i,j=0,sum=0;
  uint16_t res,Check_SumNumber;
  uint8_t sumArray[25];
  uint8_t pan_no_space_length=0;


  i=0;
  while(cardData->primaryAccountNumber[i]!='\n'){
    if(((cardData->primaryAccountNumber[i]>='0') && (cardData->primaryAccountNumber[i]<='9'))){
      pan_no_space_length++;
      i++;
    }
    else{
      i++;
      continue;
    }
  }

  i=0;j=0;
  while(cardData->primaryAccountNumber[i]!='\0'&&i<20){
    if(cardData->primaryAccountNumber[i]!=' '){
      sumArray[j]=cardData->primaryAccountNumber[i];
      i++;
      j++;
    }
    else{
      i++;
    }

  }

  /*
   * converting string array to integers to make some calculations on it
   * to calculate checksum number
  */
  i=0;
  while(sumArray[i]!='\0'){
    sumArray[i]=sumArray[i]-48;

    i++;
  }

  i=0;
  while(i<16){
    if((i+1)%2!=0){
      sumArray[i]*=2;
      if(sumArray[i]>=10){
        sum=sumArray[i]%10+sumArray[i]/10;
        sumArray[i]=sum;
      }
      i++;
      j++;
    }
    else{
      i++;
      j++;
    }
  }
  res=arraySum(sumArray,PAN_NUMBER_LENGTH_WITHOUT_THE_CHECKSUM_DIGIT);
  Check_SumNumber=((res*9)%10);
 if(pan_no_space_length!=PAN_NUMBER_WITH_NO_SPACES || Check_SumNumber!=sumArray[PAN_NUMBER_WITH_NO_SPACES-1]){
    return INVALID_CARD;
  }
  return TERMINAL_OK;


}



/*******************************************************************************
 * [Function Name] : arraySum
 *
 * [Description]   : A function to calculate array summation
 *
 * [Parameter in]       : uint8_t *arr , uint8_t size
 * [Parameter out]      : uint8_t sum
 *******************************************************************************/
uint8_t arraySum(uint8_t *arr,uint8_t size){
	uint8_t i=0,sum=0;
	while(i<size){
		sum+=arr[i];
		i++;
	}
	return sum;
}
