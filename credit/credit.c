#include <cs50.h>
#include <math.h>
#include <stdio.h>

int getDegree();
int getDigit();
void cardType();

int main(void)
{
    // Get from user prompt a number to validate
    long ccNum = get_long("Number: ");
    // Ascertain length of the number
    int cardDegree = getDegree(ccNum);

    /* Check validity of card using Luhn's Algorithm
    We need to get every digit of the card number individually, and based on the degree of that digit, either double it and add to
    one sum, or add it singularly to another sum
    */
    int evenSum = 0;
    int oddSum = 0;
    for (int i = 0; i <= cardDegree; i++)
    {
        int currentDigit = getDigit(ccNum, i);
        int j = i + 1;
        if (j % 2 == 0)
        {
            if (currentDigit > 4)
            {
                evenSum += 1;
                evenSum += (currentDigit * 2) - 10;
            }
            else
            {
                evenSum += (currentDigit * 2);
            }
        }
        else
        {
            oddSum += currentDigit;
        }
    }
    // printf("The sum of the digits of the doubles of the even numbered digits is %i\n", evenSum);
    // printf("The sum of the digits of the odd numbered digits is %i\n", oddSum);
    int checkSum = evenSum + oddSum;

    // Determine the card type
    // We already have the degree of the card (i.e. number of digits in the card number, minus one since the first number is at
    // degree 0) Length: AMEX = 15, MC = 16, VISA = 13 || 16 Starting Codes: AMEX = 34, 37; MC 51, 52, 53, 54, 55; VISA = 4
    int firstNum = getDigit(ccNum, cardDegree);
    int secondNum = getDigit(ccNum, cardDegree - 1);
    if (checkSum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if (cardDegree + 1 == 15 && firstNum == 3 && (secondNum == 4 || secondNum == 7))
        {
            printf("AMEX\n");
        }
        else if (cardDegree + 1 == 13)
        {
            printf("VISA\n");
        }
        else if (cardDegree + 1 == 16)
        {
            // printf("The first digit of the card is %i\n", firstNum);
            if (firstNum == 4)
            {
                printf("VISA\n");
            }
            else if (firstNum == 5 && (secondNum == 1 || secondNum == 2 || secondNum == 3 || secondNum == 4 || secondNum == 5))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

int getDegree(long input)
{
    long degree = 0;
    int length = 1;
    long inMod = input;
    // Loop through by dividing input by increasing factors of 10
    while ((inMod) > 9)
    {
        length++;
        degree++;
        inMod = inMod / 10;
    }
    // printf("The input number is %i digits long, with a degree of %li\n", length, degree);
    return degree;
}

int getDigit(long input, int power)
{
    // Given some input number and a degree (integer), return the value of the digit at that degree within the input
    // e.g. getDigit(1429520, 4) should return 9; getDigit(738201294502, 11) should return 3
    long inMod = input;
    // Quick arithmetic to divide the input by the 10^degree
    long divisor = pow(10, power);
    inMod = inMod / divisor;
    // If the new modified input is greater than 10, we want to return the modified input mod 10,
    // otherwise we should return the modified input, since we've input a degree greater than
    if (inMod > 10)
    {
        inMod = inMod % 10;
        // printf("The value of the digit at degree %i is %li\n", power, inMod);
        return inMod;
    }
    else
    {
        // printf("The value of the digit at degree %i is %li\n", power, inMod);
        return inMod;
    }
    return 0;
}
