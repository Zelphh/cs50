#include <cs50.h>
#include <stdio.h>

int countDigits(long n);
int getId(long n, int digits);
int luhnValidation(long n, int digits);
void typeOfCard(int digits, int id);

int main(void)
{
    long n = get_long("Number: ");

    int digits = countDigits(n);

    int id = getId(n, digits);

    if (luhnValidation(n, digits))
    {
        typeOfCard(digits, id);
    }
    else
    {
        printf("INVALID\n");
    }
}

int countDigits(long n)
{
    int c = 0;

    while (n != 0)
    {
        c++;
        n = n / 10;
    }

    return c;
}

int getId(long n, int digits)
{
    long divider = 1;

    for (int i = 0; i < digits - 2; i++)
    {
        divider = divider * 10;
    }

    return n / divider;
}

int luhnValidation(long n, int digits)
{
    int sum = 0;

    long modDiv = 100; // module divider
    long div = 10;     // integer divider
    int mult = 100;    // comon multiplyer

    for (int i = 0; i < digits / 2; i++)
    {
        int value = 2 * ((n % modDiv) / div);

        if (value > 9)
        {
            value -= 9;
        }

        sum += value;

        modDiv = modDiv * mult;
        div = div * mult;
    }

    modDiv = 10;
    div = 1;
    int times;

    if (digits % 2 == 0)
    {
        times = digits / 2;
    }
    else
    {
        times = digits / 2 + 1;
    }

    for (int i = 0; i < times; i++)
    {
        sum += (n % modDiv) / div;

        modDiv = modDiv * mult;
        div = div * mult;
    }

    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void typeOfCard(int digits, int id)
{
    if ((digits == 15) && (id == 33 || id == 37))
    {
        printf("AMEX\n");
    }
    else if ((digits == 16) && (id >= 51 && id <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((digits == 13 || digits == 16) && (id >= 40 && id <= 49))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
