#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int height = 0;
    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }
    int row = 1;
    for (int i = 1; i <= height; i++)
    {
        for (int j = -(height); j < (height + 1); j++)
        {
            if (abs(j) <= row && abs(j) > 0)
            {
                printf("#");
            }
            else if (abs(j) == 0)
            {
                printf("  ");
            }
            else if (j < 0)
            {
                printf(" ");
            }
        }
        printf("\n");
        row++;
    }
}
