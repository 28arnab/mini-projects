import csv
import sys

def main():
    """
    Main function to identify a person based on DNA STR (Short Tandem Repeat) matching.
    """

    # Check if the correct number of command-line arguments are provided
    if len(sys.argv) != 3:
        print("Usage: python dna.py databases/small.csv sequences/1.txt")
        sys.exit(1)

    # Read the DNA database file (CSV format) into a list of dictionaries
    with open(sys.argv[1], mode='r') as file:
        csvFile = csv.DictReader(file)  # Read the CSV as a dictionary
        database = [row for row in csvFile]  # Store each row of the CSV in a list

    # Read the DNA sequence file (text format) into a string
    with open(sys.argv[2], mode='r') as file:
        seqFile = file.read().strip()  # Remove any leading/trailing whitespace from the file content

    # Extract STRs (column headers after the first column) from the database file
    str_keys = csvFile.fieldnames[1:]  # Skip the first column as it contains names

    # Dictionary to store the count of longest runs for each STR in the DNA sequence
    str_counts = {}
    for str_key in str_keys:
        # Use the longest_match function to find the longest sequence of each STR
        str_counts[str_key] = longest_match(seqFile, str_key)

    # Compare the STR counts with each person in the database to find a match
    for person in database:
        # Check if the STR counts match exactly for the current person
        match = all(str_counts[str_key] == int(person[str_key]) for str_key in str_keys)
        if match:
            # If all STR counts match, print the person's name and exit
            print(person["name"])
            return

    # If no match is found after checking all people in the database
    print("No match")
    return


def longest_match(sequence, subsequence):
    """
    Returns the length of the longest run of a subsequence in the given sequence.
    """

    # Initialize the variable to track the longest consecutive run of the subsequence
    longest_run = 0

    # Length of the subsequence to match
    subsequence_length = len(subsequence)

    # Total length of the main DNA sequence
    sequence_length = len(sequence)

    # Iterate through each character in the sequence
    for i in range(sequence_length):

        # Variable to count the number of consecutive matches
        count = 0

        # Keep checking for consecutive matches of the subsequence
        while True:
            # Calculate the start and end indices for the substring to check
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If the substring matches the subsequence, increase the count
            if sequence[start:end] == subsequence:
                count += 1
            else:
                # Break the loop if the substring does not match
                break

        # Update the longest run if the current count is greater
        longest_run = max(longest_run, count)

    # Return the longest run found in the sequence
    return longest_run


# Call the main function to execute the program
main()