/**
 * helpers.c
 *
 * CS50 AP
 * Problem 3-6
 *
 * Helper functions.
 */
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false. Uses binary search.
 */
bool search(int value, int values[], int n)
{
    // Implement binary search
    int mid, low = 0, high = n;

    while (low < high - 1)
    {
        // Update midpoint
        mid = (low + high) / 2;

        if (values[mid] == value)
        {
            // Found value
            return 1;
        }
        else if (values[mid] > value)
        {
            // Looking too high
            high = mid;
        }
        else
        {
            // Looking too low
            low = mid;
        }
    }

    return 0;
}

/**
 * Sorts array of n values. Uses insertion sort.
 */
void sort(int values[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int current_value = values[i];

        int index_to_insert_into = i;

        // Shift until it is in the right location
        while (index_to_insert_into > 0 && values[index_to_insert_into - 1] >= current_value)
        {
            values[index_to_insert_into] = values[index_to_insert_into - 1];
            index_to_insert_into--;
        }

        values[index_to_insert_into] = current_value;
    }
}