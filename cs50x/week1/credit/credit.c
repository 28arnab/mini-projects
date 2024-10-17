#include <stdio.h>

int main()
{
    long credit_card_number;
    printf("Enter credit card number: ");
    scanf("%li", &credit_card_number);

    int sum = 0;
    int multiplier = 1;
    long tempNumber = credit_card_number;

    // Process every digit from the end
    while (tempNumber > 0)
    {
        int digit = tempNumber % 10;
        tempNumber /= 10;

        if (multiplier % 2 == 0)
        {
            int product = digit * 2;
            if (product > 9)
            {
                sum += product / 10 + product % 10; // Add the digits of the product
            }
            else
            {
                sum += product;
            }
        }
        else
        {
            sum += digit;
        }

        multiplier++;
    }

    // Check if the sum ends with zero
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Determine the card type
    int length = 0;
    long temp = credit_card_number;
    while (temp > 0)
    {
        temp /= 10;
        length++;
    }

    // Check card type based on length and starting digits
    if (length == 15 &&
        (credit_card_number / 10000000000000 == 34 || credit_card_number / 10000000000000 == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (credit_card_number / 100000000000000 == 51 ||
                              credit_card_number / 100000000000000 == 52 ||
                              credit_card_number / 100000000000000 == 53 ||
                              credit_card_number / 100000000000000 == 54 ||
                              credit_card_number / 100000000000000 == 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && (credit_card_number / 1000000000000 == 4 ||
                                                credit_card_number / 1000000000000000 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
