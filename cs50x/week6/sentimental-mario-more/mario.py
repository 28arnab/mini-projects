from cs50 import get_int

# Initialize height
height = 0

# Prompt user for height until valid input (1 to 8)
while height < 1 or height > 8:
    height = get_int("Height: ")

# Generate the pyramid
for i in range(1, height + 1):
    # Print spaces before the hashes for each row
    for j in range(height):
        if j < (height - i):
            print(" ", end="")  # Print spaces
        else:
            print("#", end="")  # Print left hashes

    # Print the gap and right hashes
    print(" ", "#" * i)
