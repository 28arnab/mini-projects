#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points linked to alphabets
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // prompt players
    string player1_word1 = get_string("Player 1: ");
    string player2_word2 = get_string("Player 2: ");

    // score for words
    int player1_score1 = compute_score(player1_word1);
    int player2_score2 = compute_score(player2_word2);

    // print winner
    if (player1_score1 > player2_score2)
    {
        printf("Player 1 wins !!\n");
    }
    else if (player2_score2 > player1_score1)
    {
        printf("Player 2 wins !!\n");
    }
    else
    {
        printf("Tie !!\n");
    }
}

int compute_score(string word)
{
    // track score
    int initial_score = 0;

    // score of each alphabet
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        if (isupper(word[i]))
        {
            initial_score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            initial_score += POINTS[word[i] - 'a'];
        }
    }

    return initial_score;
}
