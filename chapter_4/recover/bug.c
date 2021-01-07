#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: forensicImage\n");
        return 1;
    }

    char *forensic = argv[1];

     // Open forensic file
    FILE *f = fopen(forensic, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", forensic);
        return 2;
    }

    unsigned char bytes[512];
    int jpegs = 0;
    char filename[7] = {'\0'};
//    char filename[8] = {'\0'};

    FILE *newF = NULL;

    while (fread(bytes, 512, 1, f) == 1)
    {
         if(bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && bytes[3] >= 0xe0 && bytes[3] <= 0xef){
            if(newF != NULL){
                fclose(newF);
                jpegs = jpegs + 1;
            }
            
            sprintf(filename, "%03d.jpg", jpegs);
            newF = fopen(filename, "w+");
         }

        if (newF != NULL)
        {
            fwrite(bytes, 512, 1, newF);
        }
    }

    fclose(newF);
    fclose(f);

    return 0;
}