#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int is_jpeg_header(BYTE bytes[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover {image}\n");
        return 1;
    }

    char *image_path = argv[1];
    FILE *forensic_image = fopen(image_path, "r");

    if (forensic_image == NULL)
    {
        printf("The image %s cannot be opened!\n", image_path);
        fclose(forensic_image);
        return 1;
    }

    // Find the starting point of the first JPEG
    BYTE opening_bytes[4];
    fread(opening_bytes, 1, 4, forensic_image);

    while (!is_jpeg_header(opening_bytes))
    {
        // Shift the window of 4 bytes forward one byte
        fseek(forensic_image, -3, SEEK_CUR);
        fread(opening_bytes, 1, 4, forensic_image);
    }

    // opening_bytes now contains the JPEG header of the first JPEG in forensic_image
    // Begin going block by block, exporting JPEGs
    int current_jpeg_number = 0;

    // Move SEEK_CUR to the beginning of the file header
    fseek(forensic_image, -4, SEEK_CUR);

    // Open the file
    char current_jpeg_path[50];
    sprintf(current_jpeg_path, "%03d.jpg", current_jpeg_number);
    FILE *current_jpeg = fopen(current_jpeg_path, "w");

    BYTE block[BLOCK_SIZE], first_four_bytes[4];

    // Read in and print out first block
    fread(block, 1, BLOCK_SIZE, forensic_image);

    fwrite(block, 1, BLOCK_SIZE, current_jpeg);

    while (1)
    {
        // Read in a block at a time
        fread(block, 1, BLOCK_SIZE, forensic_image);

        if (feof(forensic_image))
        {
            break;
        }

        // Transfer over
        for (int i = 0; i < 4; i++)
        {
            first_four_bytes[i] = block[i];
        }

        // Is this the start of a new image?
        if (is_jpeg_header(first_four_bytes))
        {
            // New image => close this file, open the next file
            fclose(current_jpeg);

            current_jpeg_number++;
            sprintf(current_jpeg_path, "%03d.jpg", current_jpeg_number);
            current_jpeg = fopen(current_jpeg_path, "w");
        }

        // Output block
        fwrite(block, 1, BLOCK_SIZE, current_jpeg);
    }

    fclose(current_jpeg);
    fclose(forensic_image);
}

int is_jpeg_header(BYTE bytes[])
{
    return bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && 0xe0 <= bytes[3] && bytes[3] <= 0xef;
}