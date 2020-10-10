#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

// Checks if the provided character signifies the end of a sentence
int is_ending_punctuation(char c)
{
    return c == '.' || c == '?' || c == '!';
}

int main(void)
{
    string text;

    // Get a non-empty input
    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) == 0);

    int length = strlen(text), starting_index = 0;

    // Increase starting_index to trim starting white space
    while (isspace(text[starting_index]))
    {
        starting_index++;
    }

    // Iterate over every remaining character in the string, keeping track of each counter accordingly
    int num_letters = 0, num_words = 0, num_sentences = 0;
    for (int char_index = starting_index; char_index < length; char_index++)
    {
        char current_char = text[char_index];

        if ((current_char >= 'a' && current_char <= 'z') || (current_char >= 'A' && current_char <= 'Z'))
        {
            num_letters++;
        }

        int is_ending = is_ending_punctuation(current_char);

        if (is_ending || isspace(current_char))
        {
            num_words++;

            if (is_ending)
            {
                num_sentences++;
                char_index++;
            }
        }
    }

    // Calculate the Coleman-Liau index
    float letters_per_hundred = (float) num_letters / num_words * 100;
    float sentences_per_hundred = (float) num_sentences / num_words * 100;

    float index = 0.0588 * letters_per_hundred - 0.296 * sentences_per_hundred - 15.8;

    // Round to the nearest integer
    int rounded_index = (int)(index + 0.5);

    // Output in the proper format
    if (rounded_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (rounded_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", rounded_index);
    }
}
