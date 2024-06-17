#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool keyCheck(string);
char substituted(string, char);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You must provide a key as command line argument!\n");
        return 1;
    }
    bool keyValid = keyCheck(argv[1]);
    if (!keyValid)
    {
        return 1;
    }
    string plain = get_string("plaintext: ");
    int textlen = strlen(plain);
    string converted = plain;
    for (int i = 0; i < textlen; i++)
    {
        converted[i] = substituted(argv[1], plain[i]);
    }
    printf("ciphertext: %s\n", converted);
    return 0;
}

bool keyCheck(string input)
{
    int l = strlen(input);
    if (l != 26)
    {
        printf("Key must be 26 characters in length!\n");
        return false;
    }
    // Iterate through string to check for invalid characters or the same characters
    // We want to look for duplicates of either case
    // Going to set up nested loops even if it's inefficient
    for (int i = 0; i < 26; i++)
    {
        // Check whether char at current index of the input key is an alpha character
        if (isalpha(input[i]))
        {
            for (int j = 0; j < 26; j++)
            {
                char i_char = toupper(input[i]);
                printf("Character i = %c\n", i_char);
                if (i != j)
                {
                    // If the indeces are not the same, then the values should not be the same.
                    char j_char = toupper(input[j]);
                    printf("Character j = %c\n", j_char);
                    if (i_char == j_char)
                    {
                        printf("Key must not contain duplicate characters!\n");
                        return false;
                    }
                }
            }
        }
        else
        {
            printf("Key must not contain special characters!\n");
            return false;
        }
    }
    return true;
}

char substituted(string key, char c)
{
    // Inputs to this function are a (valid) key of 26 letters and an arbitrary character c
    // Should return a substituted character based off of the key
    if (isalpha(c))
    {
        if (isupper(c))
        {
            // If c is an uppercase char, then casting c to an int gives us a decimal value corresponding to the index of the key +
            // 65
            int index = (int) c - 65;
            return toupper(key[index]);
        }
        else if (islower(c))
        {
            // If c is a lowercase char, then casting c to get an int gives us a dec value corresponding to key index + 97
            int index = (int) c - 97;
            return tolower(key[index]);
        }
    }
    return c;
}
