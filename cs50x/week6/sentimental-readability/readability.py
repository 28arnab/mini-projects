"""
Specifications:
1. Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8
2. L = avg no of letters per 100 words and S = avg no of sentences per 100 words
3. should count no of letters, word and sentences
4. case insensitive
5. spaces means end of a word 
6. punctuation means end of a sentence
7. round the value from the algorithm
8. prints Grade {grade number}
9. when algorithm returns 16:w
or higher "Grade 16+" for less then 1 "Before Grade 1
"""

import re


def coleman_liau_index(text):
    # count letters, words, and sentences
    letters = sum(1 for char in text if char.isalpha())
    words = len(text.split())
    sentences = len(re.findall(r"[.!?]", text))

    # calculate L and S
    L = (letters / words) * 100
    S = (sentences / words) * 100

    # Apply the coleman-liau formula
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Determine the grade level to print
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


# prompt the user for text input
text = input("Enter text: ")
coleman_liau_index(text)
