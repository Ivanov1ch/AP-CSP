#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Returns the number of digits in num
int countDigits(long long num)
{
    int digitCount = 0;

    while (num > 0)
    {
        digitCount++;
        num /= 10;
    }

    return digitCount;
}

int main(void)
{
    long long cardNumber = get_long("Number: ");
    int numDigits = countDigits(cardNumber);

    // Is this a valid length for a credit card number from AmEx, Visa, or Mastercard?
    if (numDigits != 13 && numDigits != 15 && numDigits != 16)
    {
        printf("INVALID\n");
    }
    else
    {
        // Validate the card number with Luhn's Algorithm
        int sum = 0;

        // Starting from the second-to-last digit, multiply every other digit by 2

        // Start by removing the first digit
        long long cardNumCopy = cardNumber / 10;

        while (cardNumCopy > 0)
        {
            int currentDigit = cardNumCopy % 10;

            int product = currentDigit * 2;

            // Now that we have 2 * the current digit, add the sum of this product's digits to sum
            while (product > 0)
            {
                sum += product % 10;
                product /= 10;
            }

            // Remove this digit and the next digit
            cardNumCopy /= 100;
        }


        // Now add the sum of the digits that were not included (every other digit starting from the last digit)
        cardNumCopy = cardNumber;

        while (cardNumCopy > 0)
        {
            sum += cardNumCopy % 10;

            // Remove this digit and the next digit
            cardNumCopy /= 100;
        }

        // The moment of truth: is it valid? That is, is the last digit of sum 0?
        if (sum % 10 == 0)
        {
            // Now identify the card type - this is determined by the first two digits, so we need to remove all other digits from cardNumber
            int firstTwoDigits = cardNumber / (long long)(pow(10, numDigits - 2));

            // MasterCards are 16 digits long and start with 51, 52, 53, 54, or 55 - in the context of this problem, at least
            if (firstTwoDigits >= 51 && firstTwoDigits <= 55 && numDigits == 16)
            {
                printf("MASTERCARD\n");
            }
            else if ((firstTwoDigits == 34 || firstTwoDigits == 37) && numDigits == 15)
            {
                // American Express cards start with a 14 or a 37 and are 15 dgits long
                printf("AMEX\n");
            }
            else if (firstTwoDigits / 10 == 4 && (numDigits == 13 || numDigits == 16))
            {
                // Visa cards start with a 4 and are either 13 or 16 digits long
                printf("VISA\n");
            }
            else
            {
                // It does not match any of the formats, it is invalid
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

