#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    string key;

    // Check number of command line arguments passed
    if (argc == 2)
    {
        // Assign command line argument to 'key' variable
        key = argv[1];

        // Check all characters in key are alphabetic
        for (int i = 0; i < strlen(key); i++)
        {
            if (!isalpha(key[i]))
            {
                printf("error: non-alphabetic character input.\n");
                return 1;
            }
        }
    }
    else
    {
        // Print error if incorrect number of arguments
        printf("error: too many arguments entered.\n");
        return 1;
    }

    // Prompt the user for a string of plaintext
    string plaintext = get_string("plaintext: ");

    // Initialise key array and counter
    int keyarray[strlen(key)];
    int keyarray_counter = 0;

    // Create array of integers that align with key characters to match with all plaintext characters
    for (int i = 0; i < strlen(key); i++)
    {
        // If char at key[index] is uppercase
        if (isupper(key[i]))
        {
            keyarray[keyarray_counter] = key[i] - 65;
            // printf("%i\n", keyarray[keyarray_counter])
            keyarray_counter++;
        }
        // If char at key[index] is lowercase
        else if (islower(key[i]))
        {
            keyarray[keyarray_counter] = key[i] - 97;
            keyarray_counter++;
        }
    }

    for (int d = 0; d < strlen(key); d++)
    {
        printf("%i\n", keyarray[d]);
    }

    // Initialise cipher array and counter
    int cipher_num[strlen(plaintext) + 1];
    char cipher[strlen(plaintext) + 1];
    int cipher_counter = 0;

    // Initialise keyarray index counter at 0
    int keyarray_index = 0;

    // Iterate over plaintext input and create array of key related numerals
    for (int x = 0; x < strlen(plaintext); x++)
    {
        int chari;
        char charc;
        int add = keyarray[keyarray_index];

        // If uppercase, move 'add' places along
        if (plaintext[x] > 64 && plaintext[x] < 91)
        {
            if ((plaintext[x] + add) > 90)
            {
                chari = ((plaintext[x] + add) - 90) + 64;
                charc = chari;
                cipher[cipher_counter] = charc;
            }
            else
            {
                chari = plaintext[x] + add;
                charc = chari;
                cipher[cipher_counter] = charc;
            }
            cipher_counter++;
            keyarray_index++;
        }

        // If lowercase, move 'add' places along
        else if (plaintext[x] > 96 && plaintext[x] < 123)
        {
            if ((plaintext[x] + add) > 122)
            {
                charc = ((plaintext[x] + add) - 122) + 96;
                cipher[cipher_counter] = charc;
            }
            else
            {
                charc = plaintext[x] + add;
                cipher[cipher_counter] = charc;
            }
            cipher_counter++;
            keyarray_index++;
        }

        // If not alpha, keep character
        else
        {
            cipher[cipher_counter] = plaintext[x];
            cipher_counter++;
        }

        // Check whether keyarray_index has reached the length of keyarray
        if (keyarray_index == strlen(key))
        {
            // Restart keyarray_index counter if reached the end of keyarray
            keyarray_index = 0;
        }
    }

    // End the string
    cipher[cipher_counter] = '\0';

    // Output the cipher text
    printf("ciphertext: %s\n", cipher);
}
