//Helper functions for the sort race

#include <cs50.h>
#include "helpers.h"

void swap(int arr[], int index_one, int index_two)
{
    int temp = arr[index_one];
    arr[index_one] = arr[index_two];
    arr[index_two] = temp;
}

//Returns true if str is a valid flag (-a, -b, -r, or -s), false otherwise
bool check_flag(char *str)
{
    if (strcmp(str, "-a") == 0)
    {
        return 1;
    }
    else if (strcmp(str, "-r") == 0)
    {
        return 1;
    }
    else if (strcmp(str, "-b") == 0)
    {
        return 1;
    }
    else if (strcmp(str, "-s") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Sorts array of n values using bubble sort.
void bubble(int values[], int n)
{
    int made_move = 1;

    while (made_move)
    {
        made_move = 0;

        for (int i = 0; i < n - 1; i++)
        {
            if (values[i] > values[i + 1])
            {
                swap(values, i, i + 1);
                made_move = 1;
            }
        }
    }
}

//Sorts array of n values using selection sort.
void selection(int values[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int current_min = values[i], min_index = i;
        for(int j = i + 1; j < n; j++)
        {
            if(values[j] < current_min)
            {
                current_min = values[j];
                min_index = j;
            }
        }

        swap(values, i, min_index);
    }
}

//Sorts array of n values using insertion sort.
void insertion(int values[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int value_to_insert = values[i], j = i - 1;

        while(j >= 0 && values[j] > value_to_insert)
        {
            values[j + 1] = values[j];
            j--;
        }

        values[j + 1] = value_to_insert;
    }
}
