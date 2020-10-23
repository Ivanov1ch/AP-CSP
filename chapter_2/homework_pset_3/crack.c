#include <stdio.h>
#include <crypt.h>
#include <string.h>

#define PASSWORD_LENGTH 5

int is_number(char c);

int is_letter(char c);

// Ensures that there is a salt at the beginning of the hash and returns how many characters are in the salt
int validate_salt(char password[]);

// Initializes ciphertext to have the '\0' at the right place and nothing after it
void setup_ciphertext_arr(int ciphertext_length, char ciphertext[]);

// Increments the potential password by changing the rightmost character and working its way left once A-z is cycled through
int increment(int ciphertext_length, char ciphertext[]);

char get_incremented_char(char c);

int attempt(char ciphertext[], char salt[], char password[])
{
    return strcmp(crypt(ciphertext, salt), password) == 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    char *password = argv[1];

    // Ensure that this hash is of the right format: starts with salt, then has hash (chunk of numbers, then chunk of letters)
    int num_salt_characters = validate_salt(password);

    if (num_salt_characters == 0)
    {
        printf("Hash must start with salt\n");
        return 1;
    }

    // Construct salt from the first num_salt_characters of password, then append the ending \0 to indicate the end
    char salt[num_salt_characters + 1];
    for (int index = 0; index < num_salt_characters; index++)
    {
        salt[index] = password[index];
    }
    salt[num_salt_characters] = '\0';

    // Brute force all ciphertexts up to PASSWORD_LENGTH characters in length
    char ciphertext[PASSWORD_LENGTH + 1];

    for (int ciphertext_length = 1; ciphertext_length <= PASSWORD_LENGTH; ciphertext_length++)
    {
        // Initialize the array with all As
        setup_ciphertext_arr(ciphertext_length, ciphertext);
        // Attempt initial ciphertext
        int result = attempt(ciphertext, salt, password);
//        printf("Attempting %s...\n", ciphertext);

        if (result == 1)
        {
            printf("%s\n", ciphertext);
            return 0;
        }

        int is_done = increment(ciphertext_length, ciphertext); // Is_done will equal -1 if no more incrementing

        while (is_done != -1 && result != 1)
        {
//            printf("Attempting %s...\n", ciphertext);
            result = attempt(ciphertext, salt, password);

            if (result == 1)
            {
                break;
            }

            is_done = increment(ciphertext_length, ciphertext);
        }

        if (result == 1)
        {
            printf("%s\n", ciphertext);
            return 0;
        }
    }

    printf("No cracks found :(\n");
}

int is_number(char c)
{
    return c >= '0' && c <= '9';
}

int is_letter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int validate_salt(char password[])
{
    int first_char_index = 0;

    while (is_number(password[first_char_index]))
    {
        first_char_index++;
    }

    return first_char_index;
}

void setup_ciphertext_arr(int ciphertext_length, char ciphertext[])
{
    for (int i = 0; i < ciphertext_length; i++)
    {
        ciphertext[i] = 'A';
    }

    for (int i = ciphertext_length; i < PASSWORD_LENGTH + 1; i++)
    {
        ciphertext[i] = '\0';
    }
}

char get_incremented_char(char c)
{
    if (c < 'Z' || (c >= 'a' && c < 'z'))
    {
        return c + 1;
    }
    else if (c == 'Z')
    {
        // Z -> a
        return 'a';
    }
    else
    {
        // z -> A
        return 'A';
    }
}

int increment(int ciphertext_length, char ciphertext[])
{
    char rightmost_char = ciphertext[ciphertext_length - 1];

    char new_char = get_incremented_char(rightmost_char);

    // Do we need to deal with the shifting?
    ciphertext[ciphertext_length - 1] = new_char;

    if (new_char == 'A')
    {
        if (ciphertext_length == 1)
        {
            return -1; // No more characters to increment
        }

        // Shifting
        for (int index = ciphertext_length - 2; index >= 0; index--)
        {
            char this_char = ciphertext[index];
            char this_new_char = get_incremented_char(this_char);
            ciphertext[index] = this_new_char;

            if (this_new_char != 'A')
            {
                break; // No need to keep working left
            }
            else if (index == 0)
            {
                // The leftmost character has run through all 52 of its possibilities.
                // Continuing from this point would be repeating passwords, so we cannot increment further
                return -1;
            }
        }
    }

    return 0;
}