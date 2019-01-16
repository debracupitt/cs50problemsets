import sys
import getopt

# Get the secret keyword
keyword = str(sys.argv[1])

# Ensure the keyword is alphabetic
if len(sys.argv) is not 2 or keyword.isalpha() == False:
    raise ValueError('Please check the keyword you passed in as a command line argument then run the code again')

# Get the secret message
secret_message = input("plaintext: ")

# Create a numeric list from keyword
secret_numbers = []

for c in keyword:
    if c.isupper():
        secret_numbers.append(ord(c) - 65)
    elif c.islower():
        secret_numbers.append(ord(c) - 97)

# Initialise keyarray index counter at 0

# Returns ciphered secret message


def cypher(secret_message, secret_numbers):
    counter = 0
    coded_numbers = []
    coded_message = ""

    # Iterate over characters in secret message
    for s in secret_message:
        index = counter % len(secret_numbers)
        move = secret_numbers[index]

        # Check if character is alphabetical
        if s.isalpha():
            number = ord(s) + move

            # if the character is uppercase
            if s.isupper() == True:
                if number > 90:
                    number = (number % 90) + 64
                else:
                    number = ord(s) + move

            # if the character is lowercase
            elif s.islower() == True:
                if number > 122:
                    number = (number % 122) + 96
                else:
                    number = ord(s) + move

            # Add new ciphered char to coded_message string
            coded_message += chr(number)
            counter += 1
        # just add non alphabetic characters
        else:
            coded_message += s

    print(f"ciphertext: {coded_message}")
    return coded_message


# Run the code
cypher(secret_message, secret_numbers)

