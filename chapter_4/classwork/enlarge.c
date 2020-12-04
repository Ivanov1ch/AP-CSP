// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define FACTOR 2

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Determine padding for scanlines
    int original_width = bi.biWidth, original_height = bi.biHeight;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int new_width = bi.biWidth * FACTOR, new_height = bi.biHeight * 2;
    int new_padding = (4 - (new_width * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biWidth = new_width;
    bi.biHeight = new_height;

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Iterate over infile's scanlines
    for (int i = 0, biHeight = abs(original_height); i < biHeight; i++)
    {
        for(int j = 0; j < FACTOR; j++)
        {
            for (int k = 0; k < original_width; k++)
            {
                // Temporary storage
                RGBTRIPLE triple;

                // Read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // Write RGB triple to outfile FACTOR times
                for(int l = 0; l < FACTOR; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Skip over original padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // Then add back new padding
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }

            if(j != FACTOR - 1)
            {
                // Seek backwards
                int to_seek_backwards = padding + sizeof(RGBTRIPLE) * original_width;
                fseek(inptr, -1 * to_seek_backwards, SEEK_CUR);
            }
        }
    }

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Success
    return 0;
}
