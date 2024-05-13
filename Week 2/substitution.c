#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int check_key(int argc, string key);
string cipher(string plaintext, string key);

int main(int argc, string argv[])
{
    if (check_key(argc, argv[1]) == 1)
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    string ciphertext = cipher(plaintext, argv[1]);
    printf("ciphertext: %s\n", ciphertext);
}

int check_key(int argc, string key)
{
    // Check the number of comand line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int key_length = strlen(key);

    // Check the length of the key
    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check if there is a number in the key
    for (int i = 0; i < key_length; i++)
    {
        if (!(isalpha(key[i])))
        {
            printf("Key must contain only alphabeticals values.\n");
            return 1;
        }
    }

    // Key to upper (makes it easier to check for duplicate characters)
    for (int i = 0; i < key_length; i++)
    {
        key[i] = toupper(key[i]);
    }

    // Check for repeated characters in the key
    for (int i = 0; i < key_length; i++)
    {
        int count = 0;
        for (int j = 0; j < key_length; j++)
        {
            if (key[i] == key[j])
                count++;

            if (count == 2)
            {
                printf("Key must not contain repeated letters.\n");
                return 1;
            }
        }
    }

    return 0;
}

string cipher(string plaintext, string key)
{
    int p_length = strlen(plaintext);

    string ciphertext = plaintext;

    for (int i = 0; i < p_length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                int key_index = plaintext[i] - 'A';
                ciphertext[i] = key[key_index];
            }
            else
            {
                int key_index = plaintext[i] - 'a';
                ciphertext[i] = tolower(key[key_index]);
            }
        }
    }

    return ciphertext;
}
