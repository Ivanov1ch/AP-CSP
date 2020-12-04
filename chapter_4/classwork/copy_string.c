#include <stdio.h>
#include <stdlib.h>

char *copy_str(char *s);


int main(void)
{
    char *temp = "Hello World!";
    char *copy = copy_str(temp);
    printf("%s\n", copy);

    free(copy);
}

char *copy_str(char *s)
{
    // Calculate s's length
    int string_length = 0;

    while (s[string_length] != '\0')
    {
        string_length++;
    }

    // Allocate Memory
    char *copy = malloc(sizeof(char) * (string_length + 1));

    // Copy characters (including the ending null character)
    for (int i = 0; i <= string_length; i++)
    {
        copy[i] = s[i];
    }

    // Return pointer
    return copy;
}