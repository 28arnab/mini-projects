'''
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
'''

# Get input
credit_number = str(input("enter credit card number: "))
