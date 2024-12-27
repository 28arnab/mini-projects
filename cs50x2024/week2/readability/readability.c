#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
int main()
{
    // defining variables used to store no of words sentences and letters
    float letters = 0, sentences = 0,
          words = 1; // last word doesnt have a space after it so take 1
    // promp user for input
    string text = get_string("TEXT: ");

    // loop through each character in text
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
        else if (isspace(text[i]))
        {
            words++;
        }
    }

    // average words per 100 words
    float L = letters / words;
    L *= 100;
    float S = sentences / words;
    S *= 100;

    // calculate Coleman-Liau index
    int grade = round(0.0588 * L - 0.296 * S - 15.8);

    // print grade lvl
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    return 0;
}