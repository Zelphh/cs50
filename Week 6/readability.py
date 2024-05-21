def main():
    text = input("Text: ")

    letters = letters_count(text)
    words = words_counter(text)
    sentences = sentences_counter(text)

    L = (letters / words) * 100
    S = (sentences / words) * 100

    index = 0.0588 * L - 0.296 * S - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


def letters_count(text):
    count = 0
    for c in text:
        if c.isalpha():
            count += 1
    return count


def sentences_counter(text):
    count = 0
    for c in text:
        if c == "!" or c == "?" or c == ".":
            count += 1
    return count


def words_counter(text):
    count = 0
    for c in text:
        if c == " ":
            count += 1
    return count + 1


main()
