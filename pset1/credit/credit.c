#include <cs50.h>
#include <stdio.h>

int check_validity(long long n);

int main(void)
{
    string type;
    long long c;
    // Get card number and validate
    do
    {
        printf("Please enter your credit card number: \n");
        c = get_long_long("");
    }
    // Ask again if h is less than 0
    while (c < 0);

    int validity = check_validity(c);

    if (validity == 0)
    {
        type = "INVALID";
    }
    else if (validity == 1)
    {
        // Get the number of digits
        // 16 digits
        if (c > 1000000000000000)
        {
            // Get the first two numbers on the card
            int f = ((c % 10000000000000000) - (c % 100000000000000)) / 100000000000000;

            if (f >= 40 && f < 50)
            {
                type = "VISA";
            }
            else if (f >= 51 && f < 56)
            {
                type = "MASTERCARD";
            }
            else
            {
                type = "INVALID";
            }
        }

        // 15 digits
        else if (c > 100000000000000)
        {
            // Get the first two numbers on the card
            int f = ((c % 1000000000000000) - (c % 10000000000000)) / 10000000000000;

            if (f == 34 || f == 37)
            {
                type = "AMEX";
            }
            else
            {
                type = "INVALID";
            }
        }

        // 14 digits
        else if (c > 10000000000000)
        {
            type = "INVALID";
        }

        // 13 digits
        else if (c > 1000000000000)
        {
            // Get the first two numbers on the card
            int f = ((c % 10000000000000) - (c % 100000000000)) / 100000000000;

            if (f >= 40 || f < 50)
            {
                type = "VISA";
            }
            else
            {
                type = "INVALID";
            }
        }
        else
        {
            type = "INVALID";
        }
    }

    else
    {
        type = "INVALID";
    }

    printf("%s\n", type);
}


int check_validity(long long n)
{

    // Initialise the totals of the card numbers at 0.
    long long total = 0;
    long long sub_total_one = 0;
    long long sub_total_two = 0;

    // Get every second digit, starting from the second last one
    for (long long i = 100; i < 100000000000000000; i *= 100)
    {
        long long x;
        long long j = i / 10;
        long long m = n % i;

        if (m < j)
        {
            x = 0;
        }
        else
        {
            x = (m - (n % j)) / j;
        }

        // Multiply the digit by 2
        x = x * 2;

        // Add the products' digits together
        // If the number has one digit, add it to the total
        if ((x % 100) < 10)
        {
            sub_total_one = sub_total_one + x;
        }

        // If the number has two digits, add the last digit plus 1 to the total
        else
        {
            sub_total_one = sub_total_one + (x % 10) + 1;
        }
    }

    // Get the sum of the digits that weren’t multiplied by 2.
    for (long long k = 10; k < 10000000000000000; k *= 100)
    {
        long long y;
        long long j = k / 10;
        long long m = n % k;

        if (m < j)
        {
            y = 0;
        }
        else
        {
            y = (m - (n % j)) / j;
        }

        sub_total_two = sub_total_two + y;
    }

    // Add the sum of the digits that weren’t multiplied by 2.
    total = sub_total_one + sub_total_two;

    // Check if the total’s last digit is 0
    if (total % 10 != 0)
    {
        string validity = "INVALID";
        return 0;
    }
    else
    {
        string validity = "VALID";
        return 1;
    }
}

// American Express numbers all start with 34 or 37
// American Express uses 15 digit numbers
// valid eg's:
// 378282246310005
// 371449635398431

// MasterCard numbers start with 51, 52, 53, 54, or 55
// MasterCard uses 16 digit numbers
// valid eg's:
// 5555555555554444
// 5105105105105100

// Visa numbers all start with 4
// Visa uses 13 and 16 digit numbers
// valid eg's:
// 4111111111111111
// 4012888888881881

// Invalid eg's:
// 1234567890
// 369421438430814
// 4062901840
// 5673598276138003
// 4111111111111113
// rejects a non-numeric input of "foo"
// rejects a non-numeric input of ""
