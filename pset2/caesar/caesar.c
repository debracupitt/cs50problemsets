#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    int key;

    // Check number of command lind arguments passed
    if (argc == 2)
    {
        key = atoi(argv[1]);
    }
    else
    {
        // Print error if incorrect number of arguments
        printf("error: too many arguments entered.");
        return 1;
    }

    // Get remainder of key after division by 26 to prevent repeated looping over alphabet
    int rem = key % 26;

    // Prompt the user for a string of plaintext
    string plaintext = get_string("plaintext: ");

    // Initialise cipher array and counter
    char cipher[strlen(plaintext) + 1];
    int counter = 0;

    // Iterate over plaintext input
    for (int i = 0; i < strlen(plaintext); i++)
    {
        int chari;
        char charc;

        // If uppercase, move 'key' places along
        if (plaintext[i] > 64 && plaintext[i] < 91)
        {
            if ((plaintext[i] + rem) >= 90)
            {
                chari = ((plaintext[i] + rem) - 90) + 64;
                charc = chari;
                cipher[counter] = charc;
                counter++;
            }
            else
            {
                charc = plaintext[i] + rem;
                cipher[counter] = charc;
                counter++;
            }
        }

        // If lowercase, move 'key' places along
        else if (plaintext[i] > 96 && plaintext[i] < 123)
        {
            if ((plaintext[i] + rem) >= 122)
            {
                charc = ((plaintext[i] + rem) - 122) + 96;
                cipher[counter] = charc;
                counter++;
            }
            else
            {
                charc = plaintext[i] + rem;
                cipher[counter] = charc;
                counter++;
            }
        }

        // If any other character (e.g. ' ' or ',', keep the character the same
        else
        {
            cipher[counter] = plaintext[i];
            counter++;
        }
    }

    // End the string
    cipher[counter] = '\0';

    // Output the cipher text
    printf("ciphertext: %s\n", cipher);
}