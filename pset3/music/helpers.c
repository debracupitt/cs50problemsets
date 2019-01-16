// Helper functions for music
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    char a = fraction[0];
    char b = fraction[2];
    int x = a - '0';
    int y = b - '0';
    int multiplier = 8 / y;
    int eighths = x * multiplier;
    return eighths;

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int frequency = 0;
    int stringlen = 0;
    float semitone = 0.083333;
    int semitones = 0;

    // Get the length of the string 'note'
    for (int i = 0; i < strlen(note); i++)
    {
        stringlen += 1;
    }
    // Return 440 if note is A4
    if (note[0] == 'A' && note[1] == '4')
    {
        frequency = 440;
    }

    // Adjust hz for octave
    if (note[stringlen - 1] >= '0' && note[stringlen - 1] < '9')
    {
        float octave = note[stringlen - 1] - '0';
        float octpower = octave - 4;
        float octfreq = 440 * powf(2, octpower);
        frequency = round(octfreq);
    }

    // Get the number of semitones between note A and the note entered
    if (note[0] == 'B')
    {
        semitones = 2;
    }
    if (note[0] == 'C')
    {
        semitones = -9;
    }
    if (note[0] == 'D')
    {
        semitones = -7;
    }
    if (note[0] == 'E')
    {
        semitones = -5;
    }
    if (note[0] == 'F')
    {
        semitones = -4;
    }
    if (note[0] == 'G')
    {
        semitones = -2;
    }

    // Add semitone for #
    if (note[1] == '#')
    {
        semitones = semitones + 1;
    }

    // Subtract semitone for b
    if (note[1] == 'b')
    {
        semitones = semitones - 1;
    }

    // Adjust according to semitones for different notes
    float semi = 0.08333333333;
    double semitone_fraction = semi * semitones;
    double accfreq = pow(2, semitone_fraction) * frequency;
    frequency = round(accfreq);

    return frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    int rest = strcmp(s, "");
    if (!rest)
    {
        return true;
    }
    else
    {
        return false;
    }
}
