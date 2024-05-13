#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_score(string word);
string string_toupper(string word);

const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    int score1 = calculate_score(string_toupper(p1));
    int score2 = calculate_score(string_toupper(p2));

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

string string_toupper(string word)
{
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        word[i] = toupper(word[i]);
    }

    return word;
}

int calculate_score(string word)
{
    int score = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        score += POINTS[(int) (word[i] - 'A')];
    }

    return score;
}
