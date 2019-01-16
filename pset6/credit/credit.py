# Get the credit card number
card = input("Number: ")

while card.isalnum() == False or card.isalpha():
    card = input("Number: ")

# Ask again if c is empty, is not a number, or is less than 0
for n in range(len(card)):
    while card == "" or card[n].isalpha() or card[n].isalnum() == False or card[n].isspace():
        card = input("Number: ")

while int(card) < 0:
    card = input("Number: ")

def card_type(c):
    validity = check_validity(c)
    card_type = "INVALID"
    length = len(c)

    if validity == True:
        # Start Type Check
        if len(c) == 16:
            if c[0] == "5" and (int(c[1]) > 0) and (int(c[1]) < 6):
                card_type = "MASTERCARD"

            if c[0] == "4":
                card_type = "VISA"

        if len(c) == 15:
            if c[0] == "3" and (c[1] == "4" or c[1] == "7"):
                card_type = "AMEX"

        if len(c) == 13:
            if c[0] == "4":
                card_type = "VISA"

    print(f"{card_type}")
    return card_type


# Returns valilidity of card
def check_validity(num):

    # Initialise variables
    total = 0
    sub_total_str = ""
    sub_total_one = 0
    sub_total_two = 0
    length = len(num)
    validity = False

    # Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together
    for n in range(length - 2, -1, -2):
        digit = int(num[n]) * 2
        sub_total_str += str(digit)

    for n in range(0, len(sub_total_str), 1):
        sub_total_one += int(sub_total_str[n])

    # Get the sum of the digits that weren’t multiplied by 2
    for n in range(length - 1, -1, -2):
        sub_total_two += int(num[n])

    # Add the sum to the sum of the digits that weren’t multiplied by 2
    total = sub_total_one + sub_total_two

    # If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid
    if total % 10 != 0:
        validity = False

    else:
        validity = True

    return validity

card_type(card)
