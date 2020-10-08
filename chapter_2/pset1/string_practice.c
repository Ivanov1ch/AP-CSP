#include <stdio.h>
#include <cs50.h>
#include <string.h>

bool check_for_duplicates(string message);

int main(void)
{
    string message = get_string("Give me a message: ");

    bool has_duplicates = check_for_duplicates(message);

    if (has_duplicates)
    {
        printf("There are duplicate characters in this string!\n");
    }
    else
    {
        printf("There are no duplicate characters in this string!\n");
    }

}

bool check_for_duplicates(string message)
{
    int string_length = strlen(message);

    for (int i = 0; i < string_length; i++)
    {
        char current_char = message[i];

        for (int j = i + 1; j < string_length; j++)
        {
            char this_char = message[j];

            if (this_char == current_char)
            {
                return true;
            }
        }
    }

    return false;
}