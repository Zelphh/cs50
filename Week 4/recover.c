#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BITE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    FILE *img = NULL;
    char filename[8];

    BITE buffer[512];
    int jpgCounter = 0;

    while (fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {

            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", jpgCounter);

            img = fopen(filename, "w");

            fwrite(buffer, 1, 512, img);

            jpgCounter++;
        }
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }

    fclose(img);
    fclose(card);
}
