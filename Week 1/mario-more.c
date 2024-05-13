#include <cs50.h>
#include <stdio.h>

void printCharacters(int qntt, string character);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    const int FIX_SPACE = 2;

    int spaces = height - 1;
    int hashes = 1;

    for (int i = 0; i < height; i++)
    {
        printCharacters(spaces, " ");

        printCharacters(hashes, "#");

        printCharacters(FIX_SPACE, " ");

        printCharacters(hashes, "#");

        spaces--;
        hashes++;

        printf("\n");
    }
}

void printCharacters(int qntt, string character)
{
    for (int i = 0; i < qntt; i++)
    {
        printf("%s", character);
    }
}
