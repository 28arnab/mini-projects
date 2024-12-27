#include <cs50.h>
#include <stdio.h>

int main()
{
    int height_user;
    do
    {
        height_user = get_int("Height ");
    }
    while (height_user <= 0 || height_user >= 9);
    for (int height = 1; height <= height_user; height++)
    {
        for (int space = 0; space < height_user - height; space++)
        {
            printf(" ");
        }
        for (int line = 0; line < height; line++)
        {
            printf("#");
        }
        printf("  ");
        for (int line = 0; line < height; line++)
        {
            printf("#");
        }
        printf("\n");
    }
}
