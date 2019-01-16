// Helper functions for music
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int duration(string fraction);
int frequency(string note);
bool is_rest(string s);


int main(void)
{
    printf("duration: %d \n", duration("1/2"));
    // duration("1/2");
    printf("is_rest (1 = true): %d \n", is_rest(""));
    printf("is_rest (0 = false): %d \n", is_rest("A2"));
    // is_rest("A2");
    printf("frequency A0: %d \n", frequency("A0"));
    printf("frequency A1: %d \n", frequency("A1"));
    printf("frequency B1: %d \n", frequency("B1"));
    printf("frequency A2: %d \n", frequency("A2"));
    printf("frequency A3: %d \n", frequency("A3"));
    printf("frequency A4b: %d \n", frequency("Ab4"));
    printf("frequency A4: %d \n", frequency("A4"));
    printf("frequency A4#: %d \n", frequency("A#4"));
    printf("frequency A5: %d \n", frequency("A5"));
    printf("frequency A6b: %d \n", frequency("Ab6"));
    printf("frequency A6: %d \n", frequency("A6"));
    printf("frequency A6#: %d \n", frequency("A#6"));
    printf("frequency A7: %d \n", frequency("A7"));
    printf("frequency A8: %d \n", frequency("A8"));

    return 0;
}

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    char a = fraction[0];
    char b = fraction[2];
    // printf("chars: %c %c\n", a, b);

    int x = a - '0';
    int y = b - '0';
    // printf("ints: %i %i\n", x, y);

    int multiplier = 8 / y;
    int eighths = x * multiplier;
    // printf("%i\n", x);
    // printf("%i/8\n", eighths);
    return eighths;

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int frequency = 0;
    int stringlen = 0;
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
    printf("%i\n", semitones);
    double semitone_fraction = semi * semitones;
    double accfreq = pow(2, semitone_fraction) * frequency;
    printf("%f\n", semitone_fraction);
    frequency = round(accfreq);

    // if (note[1] == '#')
    // {
    //     float accfreq = powf(2, semitone) * frequency;
    //     frequency = round(accfreq);
    // }

    // // Subtract semitone for b
    // if (note[1] == 'b')
    // {
    //     float accfreq = powf(2, -semitone) * frequency;
    //     frequency = round(accfreq);
    // }

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
