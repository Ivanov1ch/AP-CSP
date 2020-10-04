#include <stdio.h>

// Prints out a pyramid with num_rows rows
void mario(int num_rows);

// Returns the largest digit in the provided integer, number
int get_largest(int number);

// Sums the digits of the provided integer, number
int sum_digits(int number);

// Recursive implementations of the above methods and their starter methods
void mario_recursive(int current_row, int num_rows);

int get_largest_recursive(int number, int current_largest);

int sum_digits_recursive(int number);

// main: driver function for testing
int main(void)
{
    // Non-recursive functions
    printf("-----CALLING NON-RECURSIVE-----\n");

    printf("mario(3):\n");
    mario(3);
    printf("mario(5):\n");
    mario(5);

    printf("get_largest(7823): %d\n", get_largest(7823));
    printf("get_largest(12923): %d\n", get_largest(12923));

    printf("sum_digits(1234): %d\n", get_largest(1234));
    printf("get_largest(12344321): %d\n", get_largest(12344321));

    // Recursive functions
    printf("\n-----CALLING RECURSIVE-----\n");

    printf("mario_recursive(1, 3):\n");
    mario_recursive(1, 3);
    printf("mario_recursive(1, 5):\n");
    mario_recursive(1, 5);

    printf("get_largest_recursive(7823, 0): %d\n", get_largest_recursive(7823, 0));
    printf("get_largest_recursive(12923, 0): %d\n", get_largest_recursive(12923, 0));

    printf("sum_digits_recursive(1234): %d\n", sum_digits_recursive(1234));
    printf("sum_digits_recursive(12344321): %d\n", sum_digits_recursive(12344321));
}

/********OTHER FUNCTION DEFINITIONS********/

void mario(int num_rows)
{
    for (int row_num = 1; row_num <= num_rows; row_num++)
    {
        for (int i = 0; i < row_num; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}

int get_largest(int number)
{
    // Use the smallest possible digit as a starting point
    int current_largest = 0;

    while (number > 0)
    {
        int current_digit = number % 10;

        if (current_largest < current_digit)
        {
            current_largest = current_digit;
        }

        number /= 10;
    }

    return current_largest;
}

int sum_digits(int number)
{
    int sum = 0;

    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }

    return sum;
}

void mario_recursive(int current_row, int num_rows)
{
    for (int i = 1; i <= current_row; i++)
    {
        printf("#");
    }

    printf("\n");

    if (current_row != num_rows)
    {
        // Recurse
        mario_recursive(current_row + 1, num_rows);
    }
}

int get_largest_recursive(int number, int current_largest)
{
    if (number == 0)
    {
        return current_largest;
    }

    int new_current_largest = number % 10; // The current digit
    number /= 10;

    if (new_current_largest < current_largest)
    {
        new_current_largest = current_largest; // Not larger than the current largest
    }

    // Recurse
    return get_largest_recursive(number, new_current_largest);
}

int sum_digits_recursive(int number)
{
    if (number == 0)
    {
        return 0;
    }

    int current_digit = number % 10;
    number /= 10;

    // Recurse
    return current_digit + sum_digits_recursive(number);
}