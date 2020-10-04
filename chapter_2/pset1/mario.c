#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Begin input validation loop
    while (1)
    {
        height = get_int("Height: ");

        if (height > 0 && height <= 8)
        {
            break;
        }
    }

    // Begin printing
    for (int row = 1; row <= height; row++)
    {
        // How many spaces to the left of the first # of this row
        int numSpaces = height - row;

        // Print spaces
        for (int i = 0; i < numSpaces; i++)
        {
            printf(" ");
        }

        // Print #s
        for (int i = 0; i < row; i++)
        {
            printf("#");
        }

        // Separating spaces
        printf("  ");

        // Print other side #s
        for (int i = 0; i < row; i++)
        {
            printf("#");
        }

        // New line
        printf("\n");
    }
}