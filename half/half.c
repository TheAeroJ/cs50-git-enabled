// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    float tax_multi = tax / 100;
    float tip_multi = (float) tip / 100;
    float bill_tax = bill * tax_multi;
    float bill_pretip = bill + bill_tax;
    float bill_tip = tip_multi * bill_pretip;
    float bill_with_tip = bill_pretip + bill_tip;
    return bill_with_tip / 2;
}
