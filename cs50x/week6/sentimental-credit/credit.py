"""
PSEUDO-CODE
    Get Input:
        Prompt the user to input the credit card number as a string or integer.
    Luhn’s Algorithm for Validity Check:
        Initialize a variable for the sum as 0.
        Starting from the second-to-last digit, multiply every other digit by 2.
        If multiplying a digit by 2 results in a number greater than 9, sum the individual digits of that product.
        Add the results to the sum.
        For the remaining digits (that were not multiplied by 2), just add them to the sum.
        If the total sum is divisible by 10, the card is potentially valid; otherwise, it’s invalid.
Check Card Type Based on Starting Digits and Length:

AMEX:
Card length is 15 digits.
Starts with 34 or 37.
MASTERCARD:
Card length is 16 digits.
Starts with 51, 52, 53, 54, or 55.
VISA:
Card length is either 13 or 16 digits.
Starts with 4.
Output:

If the card number is valid and meets the criteria for AMEX, print "AMEX".
If the card number is valid and meets the criteria for MASTERCARD, print "MASTERCARD".
If the card number is valid and meets the criteria for VISA, print "VISA".
Otherwise, print "INVALID".
"""

try:

    credit_number_str = input("Enter credit card number: ")  # Get input as a string

    if not credit_number_str.isdigit():

        raise ValueError


except ValueError:

    print("Please enter a valid credit card number")

    exit()


luhn_algorithm, digit_multiplied_by_two, digit_not_multiplied_by_two = 0, 0, 0


# apply Luhn algorithm

for i in range(len(credit_number_str) - 1, -1, -1):

    digit = int(credit_number_str[i])

    # check if the position is one that should be doubled

    if (len(credit_number_str) - i) % 2 == 0:  # Double every second digit from right

        digit *= 2

        if digit > 9:

            digit = digit // 10 + digit % 10  # If double digit, sum the two digits

    digit_multiplied_by_two += digit  # Add either the doubled or original digit


luhn_algorithm = digit_multiplied_by_two


# check if the card number is valid

if luhn_algorithm % 10 != 0:

    print("INVALID")

    exit()


# determine the card type

length_of_credit_number = len(credit_number_str)  # stores the lenght of the credit card


# checks for AMERICAN EXPRESS credit card
if length_of_credit_number == 15 and (
    int(credit_number_str[:2]) == 34 or int(credit_number_str[:2]) == 37
):
    print("AMEX")
    # checks for MASTERCARD credit card
elif length_of_credit_number == 16 and (
    int(credit_number_str[:2]) == 51
    or int(credit_number_str[:2]) == 52
    or int(credit_number_str[:2]) == 53
    or int(credit_number_str[:2]) == 54
    or int(credit_number_str[:2]) == 55
):
    print("MASTERCARD")
    # checks for VISA credit card
elif (length_of_credit_number == 13 or length_of_credit_number == 16) and (
    int(credit_number_str[:1]) == 4
):

    print("VISA")
else:
    print("INVALID")
