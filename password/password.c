// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool is_num = false;
    bool is_up = false;
    bool is_low = false;
    bool is_spec = false;
    int l = strlen(password);
    while (is_num == false || is_up == false || is_low == false || is_spec == false)
    {
        for (int i = 0; i < l; i++)
        {
            // printf("Current char is %c\n", password[i]);
            if (isupper(password[i]))
            {
                // printf("The character %c is upper-case!\n", password[i]);
                is_up = true;
            }
            else if (islower(password[i]))
            {
                // printf("The character %c is lower-case!\n", password[i]);
                is_low = true;
            }
            else if (isdigit(password[i]))
            {
                // printf("The character %c is a number!\n", password[i]);
                is_num = true;
            }
            else if (isalnum(password[i]) == 0)
            {
                // printf("The character %c is a special character!\n", password[i]);
                is_spec = true;
            }
        }
        return is_num && is_up && is_low && is_spec;
    }
    return false;
}
