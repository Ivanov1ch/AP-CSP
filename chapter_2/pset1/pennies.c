#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int days_in_month;

    // Keep prompting for the amount of days in the month until it is valid
    while (1)
    {
        days_in_month = get_int("Days in month: ");

        if (days_in_month >= 28 && days_in_month <= 31)
        {
            break;
        }
    }

    int pennies_on_first_day;

    // Keep prompting for the amount of pennis on the first day until it is at least one
    while (1)
    {
        pennies_on_first_day = get_int("Pennies on first day: ");

        if (pennies_on_first_day >= 1)
        {
            break;
        }
    }

    // Loop through every day, adding the proper amount of pennies
    long long total = 0, pennies_to_add = pennies_on_first_day;

    for (int i = 0; i < days_in_month; i++)
    {
        total += pennies_to_add;
        pennies_to_add *= 2;
    }

    // Convert the total amount of cents into dollars
    double dollars = total / 100.0;

    // Output with 2 decimal places
    printf("$%.2f\n", dollars);
}