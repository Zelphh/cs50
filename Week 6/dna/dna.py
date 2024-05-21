import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Error in command line argumnets")
        sys.exit(1)

    # TODO: Read database file into a variable
    db = []
    strs = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)

        for row in reader:
            db.append(row)

        for i in range(len(reader.fieldnames)):
            if i != 0:
                strs.append(reader.fieldnames[i])

    # TODO: Read DNA sequence file into a variable
    txt = open(sys.argv[2])
    dna = txt.read()

    # TODO: Find longest match of each STR in DNA sequence
    dna_str_counter = []
    for str in range(len(strs)):
        dna_str_counter.append(longest_match(dna, strs[str]))

    # TODO: Check database for matching profiles
    result = match_profiles(db, dna_str_counter)

    print(result)

    sys.exit(0)


def match_profiles(db, dna_str_counter):
    for p in db:
        p_strs = []
        i = 0
        for row in p:
            if row != "name":
                p_strs.append(int(p[row]))
        if p_strs == dna_str_counter:
            return p["name"]
    else:
        return "No match"


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches

        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
