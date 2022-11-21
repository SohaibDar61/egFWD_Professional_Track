/******************************************************************************
 *
 * Module: Card
 *
 * File Name: card.c
 *
 * Description: Source file for the Card module
 *
 * Author: Sohaib Dar
 *
 *******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "card.h"

/***************************************************************************
 *                                MACROS                                   *
 ***************************************************************************/
#define CARD_HOLDER_NAME_SIZE             50
#define CARD_PRIMARY_ACCOUNT_NUMBER_SIZE  25

#define CARD_HOLDER_NAME_MAX_LENGTH       24
#define CARD_HOLDER_NAME_MIN_LENGTH       20
#define EXPIRY_DATE_MAX_LENGTH            5
#define EXPIRY_DATE_MIN_LENGTH            5
#define PAN_MAX_LENGTH                    19
#define PAN_MIN_LENGTH                    16


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8_t length;				//To hold all input lengths during the program
uint8_t pan_length;			//To hold input PAN length

/*******************************************************************************
 *                      Functions                                              *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name] : getCardHolderName
 *
 * [Description]   : A function to ask for card holder name and check its length
 *            and you only have 2 trials
 *
 * [Parameter in]       : ST_cardData_t *cardData
 * [Parameter out]      : uint8_t check
 *******************************************************************************/
EN_cardError_t GetCardHolderName(ST_cardData_t *cardData)
{
    if(cardData == NULL)
    {
        return WRONG_NAME;
    }
    uint8_t check,trial=0;
#if (TESTING_MODE==0)
    printf("Please Enter The Card-Holder name: ");
#endif
    do
    {
#if (TESTING_MODE==0)
        fgets(cardData->cardHolderName, CARD_HOLDER_NAME_SIZE,stdin);             //getting array input from user using fgets to include spaces
#endif
        printf("\n");
        length = strlen(cardData->cardHolderName)-1;

        check = Max_OR_Min(length, CARD_HOLDER_NAME_MAX_LENGTH, CARD_HOLDER_NAME_MIN_LENGTH);

        if(trial<2)
        {
            switch(check)
            {
            case LESS:
                trial++;
                printf("The Name length is less than the minimum(20 Letters), Please try gain: ");

                break;
            case MORE:
                trial++;
                printf("The Name length is more than the maximum(24 Letters), Please try gain: ");
                break;
            }
        }
        trial++;
    }
    while(check!=1 && trial<3);

    if(check!=1)
    {
        check = WRONG_NAME;
    }
    else if(1==check)
    {
        check = CARD_OK;
    }
    return check;
}


/*******************************************************************************
 * [Function Name] : getCardExpiryDate
 *
 * [Description]   : A function to ask for card expiry date and check its length
 *            and format and you only have 2 trials
 *
 * [Parameter in]       : ST_cardData_t *cardData
 * [Parameter out]      : uint8_t check
 *******************************************************************************/
EN_cardError_t GetCardExpiryDate(ST_cardData_t *cardData)
{
    if(cardData == NULL)
    {
        return WRONG_EXP_DATE;
    }
    uint8_t check,trial=0;
#if (TESTING_MODE==0)
    printf("Please Enter The Card Expiry Date (MM/YY): ");
#endif

    do
    {
#if (TESTING_MODE==0)
        scanf("%s",&cardData->cardExpirationDate);
        getchar();
#endif

        printf("\n");
        length = strlen(cardData->cardExpirationDate);
        check = Max_OR_Min(length, EXPIRY_DATE_MAX_LENGTH, EXPIRY_DATE_MIN_LENGTH);

        if(trial<2)
        {
            switch(check)
            {
            case LESS:
                trial++;
                printf("The Card E Date length is less than the minimum(5 characters), Please try gain: ");
                break;
            case MORE:
                trial++;
                printf("The Card E Date length is more than the maximum(5 characters), Please try gain: ");
                break;
            }
        }
        trial++;
    }
    while(check!=1 && trial<3);

    if(check ==1 &&
            ( (cardData->cardExpirationDate[0]>='0'&&cardData->cardExpirationDate[0]<='9') &&
              (cardData->cardExpirationDate[1]>='0'&&cardData->cardExpirationDate[1]<='9') &&
              (cardData->cardExpirationDate[2]==      '/'       )              &&
              (cardData->cardExpirationDate[3]>='0'&&cardData->cardExpirationDate[3]<='9') &&
              (cardData->cardExpirationDate[4]>='0'&&cardData->cardExpirationDate[4]<='9') )
      )
    {
        check = CARD_OK;
    }
    else
    {
        check = WRONG_EXP_DATE;
    }
    return check;
}

/*******************************************************************************
 * [Function Name] : getCardPAN
 *
 * [Description]   : A function to ask for card PAN number and check its length
 *            and you only have 2 trials
 *
 * [Args in]       : ST_cardData_t *cardData
 * [Args out]      : WRONG_PAN OR CARD_OK
 *******************************************************************************/
EN_cardError_t GetCardPAN(ST_cardData_t *cardData)
{
    if(cardData == NULL)
    {
        return WRONG_PAN;
    }
    uint8_t check,trial=0;
#if (TESTING_MODE==0)
    printf("Please Enter The Card PAN: ");
#endif

    do
    {
#if (TESTING_MODE==0)
        fgets(cardData->primaryAccountNumber, CARD_PRIMARY_ACCOUNT_NUMBER_SIZE, stdin);             //getting array input from user using fgets to include spaces
#endif

        printf("\n");
        pan_length = strlen(cardData->primaryAccountNumber)-1;
        check = Max_OR_Min(pan_length, PAN_MAX_LENGTH,PAN_MIN_LENGTH);
        if(trial<2)
        {
            switch(check)
            {
            case LESS:
                trial++;
                printf("The PAN length is less than the minimum(16 characters), Please try gain: ");
                break;
            case MORE:
                trial++;
                printf("The PAN length is more than the maximum(19 characters), Please try gain: ");
                break;
            }
        }
        trial++;
    }
    while(check!=1 && trial<3);

    if(check!=1 && trial>=3)
    {
        return WRONG_PAN;
    }

    return CARD_OK;
}




/*******************************************************************************
 * [Function Name] : Max_OR_Min
 *
 * [Description]   : A function to check if the input length is right, Max or Min
 *
 * [Args in]       : uint8_t len , uint8_t Max , uint8_t Min
 * [Args out]      : LESS , MORE , VALID
 *******************************************************************************/
uint8_t Max_OR_Min(uint8_t len,uint8_t Max, uint8_t Min)
{
    if(len<Min)
    {
        return LESS;
    }
    else if(len>Max)
    {
        return MORE;
    }
    else
    {
        return VALID;
    }
}
