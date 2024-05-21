from cs50 import get_int

middle_spaces = 2


def main():
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    spaces = height - 1

    for i in range(height):
        print_characters(" ", spaces)
        print_characters("#", i + 1)

        print_characters(" ", middle_spaces)

        print_characters("#", i + 1)
        print()

        spaces -= 1


def print_characters(c, n):
    print(c * n, end="")


main()
