#include <stdio.h>
#include <cs50.h>

#define NUM_ENTRIES 5

// Finds the maximum value in the given array of integers
int find_max(int numbers[]);
// Calculates the average value (int) of the given array of integers
float find_ave(int numbers[]);

int main(void)
{
    int entries[NUM_ENTRIES];

    // Get inputs
    for (int i = 0; i < NUM_ENTRIES; i++)
    {
        do
        {
            entries[i] = get_int("Please enter a positive integer: ");
        }
        while (entries[i] <= 0);
    }

    // Output
    printf("Maximum value: %d\n", find_max(entries));
    printf("Average value: %.2f\n", find_ave(entries));
}

int find_max(int numbers[])
{
    int currentMax = 0; // We know all numbers will be > 0 so this is a fine starting point

    for (int i = 0; i < NUM_ENTRIES; i++)
    {
        int currentNum = numbers[i];

        if (currentNum > currentMax)
        {
            currentMax = currentNum;
        }
    }

    return currentMax;
}

float find_ave(int numbers[])
{
    float sum = 0;

    for (int i = 0; i < NUM_ENTRIES; i++)
    {
        sum += numbers[i];
    }

    return sum / NUM_ENTRIES;
}