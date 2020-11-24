#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_MESSAGE_LENGTH 100

int is_letter(char c);

char *strip_non_letters(char *text);

char *encode(char *original_text);

int main(void)
{
    // Define string
    char original_text[MAX_MESSAGE_LENGTH + 1];

    // Get use input
    printf("Enter message (will be truncated at %i characters): ", MAX_MESSAGE_LENGTH);
    fgets(original_text, MAX_MESSAGE_LENGTH + 1, stdin);

    char *cipher_text = encode(original_text);

    // Output result
    printf("Encoded Message: %s\n", cipher_text);

    // Free memory obtained by malloc in strip_non_letters
    free(cipher_text);
}

char *encode(char *original_text)
{
    // Strip all characters that are not letters
    char *plaintext = strip_non_letters(original_text);

    // Calculate number of rows and columns
    int num_characters = strlen(plaintext) - 1;
    int num_rows = sqrt(num_characters), num_cols = num_characters / num_rows + 1;

    // Initialize 2D array
    char square_form[num_rows][num_cols];

    char *current_char_pointer = plaintext;
    for (int row = 0; row < num_rows; row++)
    {
        for (int col = 0; col < num_cols; col++)
        {
            char current_char = *(current_char_pointer++);
            square_form[row][col] = current_char;

            if (current_char == '\0')
            {
                break;
            }
        }
    }

    // Alter plaintext based off of the table
    int max_row_to_visit = num_rows;
    int current_char_index = 0;
    for (int col = 0; col < num_cols; col++)
    {
        for (int row = 0; row < max_row_to_visit; row++)
        {
            char current_char = square_form[row][col];

            if(current_char == '\0')
            {
                // There are elements to the right of this element in the current row.
                // Do not come back to this row in future iterations to prevent going out of bounds
                max_row_to_visit--;
                break;
            }

            plaintext[current_char_index++] = current_char;
        }
    }

    plaintext[current_char_index] = '\0';
    return plaintext;
}

char *strip_non_letters(char *text)
{
    int original_num_chars = strlen(text);
    char *stripped_text = malloc((original_num_chars) * sizeof(char));

    int current_index = 0;
    for (int i = 0; i < original_num_chars; i++)
    {
        char current_original_char = text[i];
        if (current_original_char == '\0' || is_letter(current_original_char))
        {
            stripped_text[current_index++] = current_original_char;

            if (current_original_char == '\0')
                return stripped_text;
        }
    }

    return stripped_text;
}

int is_letter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}