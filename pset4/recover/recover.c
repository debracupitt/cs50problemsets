// Resizes a BMP file by a factor of n
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// #include "jpg.h"

#define BUFFER_SIZE 512

int main (int argc, char *argv[])
{
    // Check for number of command line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: Please enter one file.\n");
        return 1;
    }

    // Open memory card file
    FILE *infile = fopen(argv[1], "r");

    // If file = NULL, return error
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
        return 2;
    }

    // Create outfile for picture
    FILE *img = NULL;

    // Create buffer and filename arrays
    unsigned char buffer[BUFFER_SIZE];
    char filename[8];

    // Set counter for filename
    int filename_counter = 0;

    // Set flag for when jpg is found or not found
    bool found = false;

    // Read the file while it is not at the end of the file
    while (fread(buffer, BUFFER_SIZE, 1, infile) == 1)
    {
        // At the beginning of a JPEG - check first 3 bytes and 4th as a bitwise and operater:
        // the fourth byte’s first four bits are 1110
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close current jpg to start reading the next
            if (found == true)
            {
                fclose(img);
            }

            // new jpg found
            else
            {
                found = true;
            }

            // Create new filename for new jpg
            sprintf(filename, "%03i.jpg", filename_counter);
            img = fopen(filename, "w");
            filename_counter++;
        }

        // Write the 512 characters to the new image file
        if (found == true)
        {
            fwrite(&buffer, BUFFER_SIZE, 1, img);
        }
    }

    // close infile
    fclose(infile);

    // success
    return 0;
}
