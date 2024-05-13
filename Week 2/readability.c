#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calculate_letters(string text);
int calculate_words(string text);
int calculate_sentences(string text);
float get_index(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");

    int words = calculate_words(text);
    int letters = calculate_letters(text);
    int sentences = calculate_sentences(text);

    float index = get_index(letters, words, sentences);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}

int calculate_letters(string text)
{
    int letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

int calculate_words(string text)
{
    int spaces = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            spaces++;
        }
    }

    return spaces + 1;
}

int calculate_sentences(string text)
{
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}

float get_index(int letters, int words, int sentences)
{
    float L = ((float) letters / words) * 100.0;
    float S = ((float) sentences / words) * 100.0;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    return index;
}
