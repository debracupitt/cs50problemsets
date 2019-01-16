#include <cs50.h>
#include <stdio.h>

int pyramid(int n);

int main(void)
{
    int h;
    // Get height of pyramid
    do
    {
        printf("Choose a height for mario's pyramid. The minimum height is 1 block high and the maximum height is 23 blocks.\n");
        h = get_int("Height: ");
    }
    // Ask again if h is less than 0 or greater than 23.
    while (h < 0 || h > 23);

    // print pyramid
    pyramid(h);
}

int pyramid(int n)
{
    int x = n;
    int b;
    int s;

    for (int i = 1; i <= n; i++)
    {
        b = i;
        s = x - 1;
        // print spaces
        for (int j = 1; j <= s; j++)
        {
            printf(" ");
        }

        // print the left pyramid
        for (int k = 1; k <= b; k++)
        {
            printf("#");
        }

        // print the gap
        printf("  ");

        // print the right pyramid
        for (int l = 1; l <= b; l++)
        {
            printf("#");
        }
        printf("\n");

        // reduce x by 1
        x = x - 1;
    }

    // End function
    return n;
}
