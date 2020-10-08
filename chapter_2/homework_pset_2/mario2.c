#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Please enter one command-line argument (height, an integer)!\n");
        return 1;
    }

    int height = atoi(argv[1]);

    if(height <= 0)
    {
        printf("The height must be greater than 0!\n");
        return 1;
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

        // New line
        printf("\n");
    }
}