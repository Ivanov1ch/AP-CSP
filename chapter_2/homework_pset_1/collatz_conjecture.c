#include <cs50.h>
#include <stdio.h>

// Recurse through the steps of the Collatz conjecture
int collatz(int n);

int main(void)
{
    int number;

    // Get a positive integer
    do
    {
        number = get_int("Enter number: ");
    }
    while (number < 1);

    // Call collatz
    printf("%d\n", collatz(number));
}

// Apply the steps of the Collatz conjecture
int collatz(int n)
{
    if (n == 1)
    {
        // Base case
        return 0;
    }

    // Add a step to the counter and recurse
    if (n % 2 == 0)
    {
        return 1 + collatz(n / 2);
    }
    else
    {
        return 1 + collatz(3 * n + 1);
    }
}
