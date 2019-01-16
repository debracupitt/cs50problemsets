// Integer Arithmatic

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for x
    int x = get_int("x: ");

    // Prompt user for y
    int y = get_int("y: ");

    // Perform arithmetic
    printf("%i plus %i is %i\n", x, y, x + y);
    printf("%i minus %i is %i\n", x, y, x - y);
    printf("%i times %i is %i\n", x, y, x * y);
    printf("%i divided by %i is %i\n", x, y, x / y);
    printf("remainder of %i divided by %i is %i\n", x, y, x % y);

    if (x < y)
    {
      printf("x is less than y\n");
    }

    else if (x > y)
    {
      printf("x is greater than y\n");
    }

    else
    {
      printf("x is equal to y\n");
    }
}