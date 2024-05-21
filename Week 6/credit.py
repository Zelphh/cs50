from cs50 import get_int


def main():
    number = str(get_int("Number: "))
    if validation(number):
        print(card_type(number))
    else:
        print("INVALID")


def card_type(num):
    l = len(num)

    if (l == 13 or l == 16) and num[0] == "4":
        return "VISA"
    elif l == 15 and (num[0:2] == "34" or num[0:2] == "37"):
        return "AMEX"
    elif l == 16 and (int(num[0:2]) > 50 and int(num[0:2]) <= 55):
        return "MASTERCARD"
    else:
        return "INVALID"


def validation(num):
    sum = 0
    l = len(num)

    pair = True if l % 2 == 0 else False

    for i in range(l):
        n = int(num[i])

        if (pair):
            if i % 2 == 0:
                n *= 2
                sum += n if n < 10 else n - 9
            else:
                sum += n
        else:
            if i % 2 == 0:
                sum += n
            else:
                n *= 2
                sum += n if n < 10 else n - 9

    return True if sum % 10 == 0 else False


main()
