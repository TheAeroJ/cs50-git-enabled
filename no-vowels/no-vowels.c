// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string in);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Please provide exactly one word as argument!\n");
        return 1;
    }
    else
    {
        string converted = replace(argv[1]);
        printf("%s\n", converted);
    }
}

string replace(string in)
{
    int l = strlen(in);
    for (int i = 0; i < l; i++)
    {
        switch (in[i])
        {
            case 'a':
                in[i] = '6';
                break;
            case 'e':
                in[i] = '3';
                break;
            case 'i':
                in[i] = '1';
                break;
            case 'o':
                in[i] = '0';
                break;
            case 'u':
                in[i] = 'u';
                break;
            default:
                break;
        }
    }
    return in;
}
