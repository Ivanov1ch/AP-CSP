#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cs50.h>
#include <ctype.h>

void encrypt(string plaintext, int shift);

int is_uppercase(char c);

int main(int argc, char *argv[])
{

    // Validate number of arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // How much to shift the encrypted message by and the length of the provided argument
    int shift = 0, argument_size = strlen(argv[1]);

    // Validate that each character in the provided argument is a digit, calculating shift as it goes.
    // Gives an error and returns if a character is found that is not a digit
    for (int char_index = 0; char_index < argument_size; char_index++)
    {
        char current_char = argv[1][char_index];

        if (current_char >= '0' && current_char <= '9')
        {
            // Appends the current digit properly. For example, if the argument was 4321 and this was the first execution
            // (char_index = 0), this would add 4000. The next iterations would add 300, then 20, then 1.
            shift += pow(10, argument_size - char_index - 1) * (current_char - '0');
        }
        else
        {
            // Not a decimal character. Therefore this is not valid!
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // We have validated the argument and extracted the value of the shift
    string plaintext = get_string("Plaintext: ");

    // Encrypt the string
    encrypt(plaintext, shift);

    // Output
    printf("ciphertext: %s\n", plaintext);
}

// Returns the encrypted form of the given plaintext when encrypted with the provided shift
void encrypt(string plaintext, int shift)
{
    int text_len = strlen(plaintext);

    for (int char_index = 0; char_index < text_len; char_index++)
    {
        char current_char = plaintext[char_index];

        // Ignore non-letters
        if (current_char < 'A' || (current_char > 'Z' && current_char < 'a') || current_char > 'z')
        {
            continue;
        }

        // Set the minimum ASCII value for this character, based off of case
        int min_ascii = 'a';

        if (is_uppercase(current_char))
        {
            min_ascii = 'A';
        }

        // Shift the char by ASCII Value
        int ASCII_diff = (current_char - min_ascii + shift) % 26; // How far the result should be from the min
        int final_ASCII = min_ascii + ASCII_diff;

        plaintext[char_index] = final_ASCII;
    }
}

// Returns 1 if the provided character is uppercase
int is_uppercase(char c)
{
    return c >= 'A' && c <= 'Z';
}