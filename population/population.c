#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start = 0;
    int end = 0;
    while (start < 9)
    {
        start = get_int("Input population starting size: ");
    }
    // Prompt for end size
    while (end < start)
    {
        end = get_int("Input population ending size: ");
    }
    // Calculate number of years until we reach threshold
    // Each year, n/3 new llamas are born, n/4 llamas die
    int popCurrent = start;
    int year = 0;
    while (popCurrent < end)
    {
        popCurrent += ((popCurrent / 3) - (popCurrent / 4));
        year++;
    }

    // Print number of years
    printf("Years: %i\n", year);
}
