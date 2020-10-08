#include <stdio.h>
#include <string.h>

void insert_swap(char arr[], int from_index, int to_index);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please enter one command-line argument (a string you want alphabetized)!\n");
        return 1;
    }

    char *to_alphabetize = argv[1];

    // Implement an insertion sort algorithm based off of ASCII values
    int string_length = strlen(to_alphabetize);
    for (int starting_index = 1; starting_index < string_length; starting_index++)
    {
        int index_to_swap_to = starting_index - 1;

        // Find where this character belongs in the new string
        while (index_to_swap_to >= 0 && to_alphabetize[index_to_swap_to] >= to_alphabetize[starting_index])
        {
            index_to_swap_to--;
        }

        insert_swap(to_alphabetize, starting_index, index_to_swap_to + 1);
    }

    // Output the new, alphabetized string
    printf("%s\n", to_alphabetize);
}

/*
 * Inserts the character at arr[from_index] into the arr[to_index] as follows:
 * 1) Shift all elements between to_index and from_index - 1 to the right one
 * 2) Replace the element at index to_index with the original arr[from_index]
 */
void insert_swap(char arr[], int from_index, int to_index)
{
    char char_to_insert = arr[from_index];

    // Shift all elements to the right one
    for (int i = from_index; i > to_index; i--)
    {
        arr[i] = arr[i-1];
    }

    arr[to_index] = char_to_insert;
}