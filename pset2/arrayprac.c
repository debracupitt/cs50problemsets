#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    for (int i = 1; i < argc; i++)
    {
        printf("At index %i we have: %s\n", i, argv[i]);
    }
}
