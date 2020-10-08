#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number;

    while(1)
    {
        number = get_int("Please enter a positive number that is less than 5,000,000: ");

        if(number >= 0 && number < 5000000)
            break;
    }

    // Now analuze the digits to see if any are odd
    bool hasOdd = false;

    while(number > 0)
    {
        int currentDigit = number % 10;

        if(currentDigit % 2 == 1)
        {
            hasOdd = true;
            break;
        }

        number /= 10;
    }

    if(hasOdd)
        printf("Odd");
    else
        printf("All even");
}