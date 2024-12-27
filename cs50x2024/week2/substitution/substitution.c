#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
int main(int argc, string argv[]) {
  // to check no of command line arguments
  if (argc != 2) {
    printf("Usage: ./substitution Key\n");
    return 1;
  }
  // to check no of characters in the key is equal to 26 or not
  if (strlen(argv[1]) != 26) {
    printf("Key must contain 26 characters\n");
    return 1;
  }
  // to check if there is any digit in the key provided
  for (int i = 0; i < 26; i++) {
    if (!isalpha(argv[1][i])) {
      printf("Usage: ./substitution Key\n");
      return 1;
    }
  }
  // to check duplicate alphabets *case insensitive* in the key
  for (int i = 0; i < 26; i++) {
    for (int j = i + 1; j < 26; j++) {
      if (tolower(argv[1][i]) == tolower(argv[1][j])) {
        printf("Usage: ./substitution Key\n");
        return 1;
      }
    }
  }
  // prompts user for plain text
  string plaintext = get_string("plaintext: ");
  char ciphertext[strlen(plaintext) + 1]; // +1 for null
  // substiutes characters in key with characters in plaintext
  for (int i = 0, string_length = strlen(plaintext); i < string_length; i++) {
    // if and else if is used to keep the case intact
    if (isupper(plaintext[i])) {
      ciphertext[i] = toupper(argv[1][plaintext[i] - 'A']);
    } else if (islower(plaintext[i])) {
      ciphertext[i] = tolower(argv[1][plaintext[i] - 'a']);
    } else {
      ciphertext[i] = plaintext[i]; // non-alphabetical characters remain same
    }
  }
  // to prevent assigning things outside memory
  ciphertext[strlen(plaintext)] = '\0';
  printf("ciphertext: %s\n", ciphertext);
  return 0;
}
