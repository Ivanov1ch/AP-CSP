#include <stdio.h>
#include <string.h>
#include <cs50.h>

// Encrypts the provided plaintext using the provided key. Assumes key is uppercase and is 26 characters in length.
void encrypt(string plaintext, string key);

// Returns 1 if the given character is a letter of the alphabet and 0 otherwise
int is_letter(char c);

// Returns 1 if the given chatacter is uppercase
int is_uppercase(char c);

int main(int argc, char *argv[])
{
    // Validate number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Validate length of argument
    int argument_size = strlen(argv[1]);

    if (argument_size != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Convert every letter in the key to uppercase while also validating the key format
    for (int char_index = 0; char_index < argument_size; char_index++)
    {
        char current_char = argv[1][char_index];

        if (is_letter(current_char))
        {
            if (!is_uppercase(current_char))
            {
                // Convert it to uppercase
                int ASCII_difference = current_char - 'a';
                argv[1][char_index] = 'A' + ASCII_difference;
            }
        }
        else
        {
            // Not a letter. This is an invalid substitution key!
            printf("Key must contain 26 letters.\n");
            return 1;
        }
    }

    // Check to make sure that each letter is used (no duplicates used)
    for (int i = 0; i < argument_size; i++)
    {
        for (int j = i + 1; j < argument_size; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must contain 26 unique letters.\n");
                return 1;
            }
        }
    }

    // Key has been validated and transformed to uppercase. Take in input, encrypt, and output.
    string plaintext = get_string("Plaintext: ");

    // Encrypt
    encrypt(plaintext, argv[1]);

    // Output
    printf("ciphertext: %s\n", plaintext);
}

void encrypt(string plaintext, string key)
{
    int text_length = strlen(plaintext);

    for (int char_index = 0; char_index < text_length; char_index++)
    {
        char current_char = plaintext[char_index];

        if (is_letter(current_char))
        {
            // The capital form of the letter that this letter should be swapped with
            int to_swap_index = current_char - 'A';

            if (!is_uppercase(current_char))
            {
                to_swap_index = current_char - 'a';
            }

            char to_swap_to = key[to_swap_index];

            if (is_uppercase(current_char))
            {
                // No need to handle swapping cases
                plaintext[char_index] = to_swap_to;
            }
            else
            {
                // Add the lowercase form of to_swap_to
                plaintext[char_index] = (to_swap_to - 'A') + 'a';
            }
        }
    }
}

int is_letter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int is_uppercase(char c)
{
    return c >= 'A' && c <= 'Z';
}