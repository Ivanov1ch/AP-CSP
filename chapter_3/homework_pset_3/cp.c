#include <stdio.h>

int main(int argc, char *argv[])
{
    // Validate number of arguments
    if (argc != 3)
    {
        printf("Usage: ./cp {source} {destination}\n");
        return -1;
    }

    char *src = argv[1], *dest = argv[2];

    // Validate source file exists
    FILE *source = fopen(src, "r");

    if (source == NULL)
    {
        printf("Error: source file %s not found\n", src);
        return -1;
    }

    // Open destination file
    FILE *destination = fopen(dest, "w");

    // Character-by-character copy source -> destination
    for (int c = fgetc(source); c != EOF; c = fgetc(source))
    {
        fputc(c, destination);
    }

    // Close files
    fclose(source);
    fclose(destination);

    // Output status
    printf("%s successfully copied to %s\n", src, dest);
}