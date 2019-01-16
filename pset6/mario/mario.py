from cs50 import get_int

# Get height of pyramid, ask until h is less than 0 or greater than 23
p_height = get_int("Height: ")

while p_height < 0 or p_height > 23:
    p_height = get_int("Height: ")

# print pyramid
def print_pyramid(height):

    s = height - 1;

    for i in range(1, height + 1):
        row = ""
        # add spaces
        for j in range(0, s):
            row+= " "

        # add the left pyramid
        for k in range(0, i):
            row += "#"

        # print the spaces
        row += "  "

        # print the right pyramid
        for k in range(0,i):
            row += "#"

        # reduce s by 1
        print(f"{row}")
        s -= 1

print_pyramid(p_height)
